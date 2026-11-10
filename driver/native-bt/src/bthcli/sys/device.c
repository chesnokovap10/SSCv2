/*++

Copyright (c) Microsoft Corporation.  All rights reserved.

    THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
    KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
    PURPOSE.

Module Name:

    Device.c

Abstract:

    Device and file object related functionality for bthecho client device

Environment:

    Kernel mode only


--*/

#include "clisrv.h"
#include "device.h"

#ifdef SSC_LOCAL_PROFILE
static const GUID SscAvdtpProbeInterface = {0xc713148a, 0x3218, 0x4755, {0xb1, 0x03, 0x7a, 0xee, 0x51, 0xc9, 0xd3, 0x13}};
#else
static const GUID SscAvdtpProbeInterface = {0x105bdfd9, 0x73ce, 0x4bcf, {0xb2, 0xe9, 0xc5, 0xd6, 0x11, 0xf6, 0x9a, 0x23}};
#endif
#include "client.h"
#include "queue.h"

#define INITGUID
#include "public.h"

#if defined(EVENT_TRACING)
#include "device.tmh"
#endif

#ifdef ALLOC_PRAGMA
#pragma alloc_text (PAGE, BthEchoCliEvtDriverDeviceAdd)
#pragma alloc_text (PAGE, BthEchoCliEvtDeviceFileCreate)
#pragma alloc_text (PAGE, BthEchoCliEvtFileClose)
#endif

NTSTATUS
BthEchoCliEvtDriverDeviceAdd(
    _In_ WDFDRIVER  Driver,
    _Inout_ PWDFDEVICE_INIT  DeviceInit
)
/*++
Routine Description:

    BthEchoCliEvtDeviceAdd is called by the framework in response to AddDevice
    call from the PnP manager. We create and initialize a device object to
    represent a new instance of the device. All the software resources
    should be allocated in this callback.

Arguments:

    Driver - Handle to a framework driver object created in DriverEntry

    DeviceInit - Pointer to a framework-allocated WDFDEVICE_INIT structure.

Return Value:

    NTSTATUS

--*/
{
    NTSTATUS                        status;
    WDFDEVICE                       device;    
    WDF_OBJECT_ATTRIBUTES           deviceAttributes;
    WDF_PNPPOWER_EVENT_CALLBACKS    pnpPowerCallbacks;
    WDF_FILEOBJECT_CONFIG           fileobjectConfig;
    WDF_OBJECT_ATTRIBUTES           fileAttributes, requestAttributes;
    WDF_IO_QUEUE_CONFIG             ioQueueConfig;
    WDFQUEUE                        queue;
    PBTHECHOSAMPLE_CLIENT_CONTEXT   devCtx;
    
    UNREFERENCED_PARAMETER(Driver);

    PAGED_CODE();

    //
    // Configure Pnp/power callbacks
    //
    WDF_PNPPOWER_EVENT_CALLBACKS_INIT(&pnpPowerCallbacks);
    pnpPowerCallbacks.EvtDeviceSelfManagedIoInit = BthEchoCliEvtDeviceSelfManagedIoInit;

    WdfDeviceInitSetPnpPowerEventCallbacks(
       DeviceInit,
       &pnpPowerCallbacks
       );

    //
    // Configure file callbacks
    //    

    WDF_FILEOBJECT_CONFIG_INIT(
        &fileobjectConfig,
        BthEchoCliEvtDeviceFileCreate,
        BthEchoCliEvtFileClose,
        WDF_NO_EVENT_CALLBACK // Cleanup
        );

    //
    // Inform framework to create context area in every fileobject
    // so that we can track information per open handle by the
    // application.
    //
    WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&fileAttributes, BTHECHOSAMPLE_CLIENT_FILE_CONTEXT);

    WdfDeviceInitSetFileObjectConfig(
        DeviceInit,
        &fileobjectConfig,
        &fileAttributes
        );

    //
    // Inform framework to create context area in every request object.
    //
    // We make BRB as the context since we need BRB for all the requests
    // we handle (Create, Read, Write).
    //

    WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(
        &requestAttributes,
        BRB
        );

    WdfDeviceInitSetRequestAttributes(
        DeviceInit,
        &requestAttributes
        );

    //
    // Set device attributes
    //
    WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&deviceAttributes, BTHECHOSAMPLE_CLIENT_CONTEXT);
    
    status = WdfDeviceCreate(
        &DeviceInit,
        &deviceAttributes,
        &device
        );

    if (!NT_SUCCESS(status))
    {
        TraceEvents(TRACE_LEVEL_ERROR, DBG_PNP, 
            "WdfDeviceCreate failed with Status code %!STATUS!\n", status);

        goto exit;
    }

    devCtx = GetClientDeviceContext(device);

    //
    // Initialize our context
    //
    status = BthEchoCliContextInit(devCtx, device);

    if (!NT_SUCCESS(status))
    {
        TraceEvents(TRACE_LEVEL_ERROR, DBG_PNP, 
            "Initialization of context failed with Status code %!STATUS!\n", status);

        goto exit;       
    }

    status = BthEchoCliBthQueryInterfaces(devCtx);        
    if (!NT_SUCCESS(status))
    {
        goto exit;
    }

    //
    // Set up our queue
    //

    WDF_IO_QUEUE_CONFIG_INIT_DEFAULT_QUEUE(
        &ioQueueConfig,
        WdfIoQueueDispatchParallel
        );

    ioQueueConfig.EvtIoRead     = BthEchoCliEvtQueueIoRead;
    ioQueueConfig.EvtIoWrite    = BthEchoCliEvtQueueIoWrite;
    ioQueueConfig.EvtIoStop     = BthEchoCliEvtQueueIoStop;

    status = WdfIoQueueCreate(
        device,
        &ioQueueConfig,
        WDF_NO_OBJECT_ATTRIBUTES,
        &queue
        );
    
    if (!NT_SUCCESS(status))
    {
        TraceEvents(TRACE_LEVEL_ERROR, DBG_PNP,
                            "WdfIoQueueCreate failed  %!STATUS!\n", status);
        goto exit;
    }

    //
    // Enable device interface so that app can open a handle to our device
    // and talk to it
    //
    
    status = WdfDeviceCreateDeviceInterface(
        device,
        &SscAvdtpProbeInterface,
        NULL
        );

    if (!NT_SUCCESS(status))
    {
        TraceEvents(TRACE_LEVEL_ERROR, DBG_PNP, 
            "Enabling device interface failed with Status code %!STATUS!\n", status);

        goto exit;       
    }

exit:    
    //
    // We don't need to worry about deleting any objects on failure
    // because all the object created so far are parented to device and when
    // we return an error, framework will delete the device and as a 
    // result all the child objects will get deleted along with that.
    //
    return status;
}

NTSTATUS
BthEchoCliEvtDeviceSelfManagedIoInit(
    _In_ WDFDEVICE  Device
    )
/*++

Description:

    This routine is called by the framework only once
    and hence we use it for our one time initialization.

    Bth addresses for both our local device and server device
    do not change, hence we retrieve them here.

    Features that the local device supports also do not change,
    so checking for local L2cap support is done here and saved in the
    device context header

    Please note that retrieveing server bth address does not
    require presence of the server. It is remembered from
    the installation time when the client gets installed for a
    specific server.

Arguments:

    Device - Framework device object

Return Value:

    NTSTATUS Status code.

--*/
{
    NTSTATUS status;
    PBTHECHOSAMPLE_CLIENT_CONTEXT devCtx = GetClientDeviceContext(Device);

    status = BthEchoSharedRetrieveLocalInfo(&devCtx->Header);
    if (!NT_SUCCESS(status))
    {
        goto exit;
    }

#ifndef SSC_LOCAL_PROFILE
    status = BthEchoCliRetrieveServerBthAddress(devCtx);
    if (!NT_SUCCESS(status))
    {
        goto exit;
    }

#endif

exit:
    return status;
}

NTSTATUS
BthEchoCliConnectionStateConnected(
    _In_ WDFFILEOBJECT  FileObject,
    _In_ PBTHECHO_CONNECTION Connection
    )
/*++
Description:

    This routine is invoked by BthEchoCliRemoteConnectCompletion
    function in client.c when opening a remote
    connection is completed.

    In this routine we set the file context to the connection passed in.

Arguments:

    FileObject - File object whose open resulted in open connection
    Connection - Our data strucutre to track open connection

Return Value:

    NTSTATUS Status code.
--*/
{
    GetFileContext(FileObject)->Connection = Connection;    

    return STATUS_SUCCESS;
}

#ifdef SSC_LOCAL_PROFILE
static PVOID volatile SscIncomingHandle;
static volatile LONG SscProbeBusy;

NTSTATUS SscAcceptIncoming(PBTHECHOSAMPLE_CLIENT_CONTEXT dev, WDFFILEOBJECT file,
    WDFREQUEST request, BTH_ADDR address, L2CAP_CHANNEL_HANDLE handle);

static VOID SscProbeIncoming(PVOID context, INDICATION_CODE code, PINDICATION_PARAMETERS parameters)
{
    UNREFERENCED_PARAMETER(context);
    if (code == IndicationRemoteConnect && parameters != NULL) {
        InterlockedCompareExchangePointer(&SscIncomingHandle, parameters->ConnectionHandle, NULL);
    }
}

static NTSTATUS SscProbeRegistration(PBTHECHOSAMPLE_CLIENT_CONTEXT dev, WDFFILEOBJECT file, BTH_ADDR address)
{
    if (InterlockedCompareExchange(&SscProbeBusy, 1, 0)) {
        return STATUS_DEVICE_BUSY;
    }
    WDFREQUEST request;
    NTSTATUS status = WdfRequestCreate(WDF_NO_OBJECT_ATTRIBUTES, dev->Header.IoTarget, &request);
    if (!NT_SUCCESS(status)) {
        InterlockedExchange(&SscProbeBusy, 0);
        return status;
    }

    union {
        struct _BRB_L2CA_REGISTER_SERVER reg;
        struct _BRB_L2CA_UNREGISTER_SERVER unreg;
    } brb;
    dev->Header.ProfileDrvInterface.BthInitializeBrb((PBRB)&brb, BRB_L2CA_REGISTER_SERVER);
    brb.reg.BtAddress = address;
    brb.reg.PSM = 0x0017;
    brb.reg.IndicationCallback = SscProbeIncoming;
    brb.reg.ReferenceObject = WdfDeviceWdmGetDeviceObject(dev->Header.Device);
    InterlockedExchangePointer(&SscIncomingHandle, NULL);
    status = BthEchoSharedSendBrbSynchronously(dev->Header.IoTarget, request, (PBRB)&brb, sizeof(brb.reg));
    if (NT_SUCCESS(status)) {
        L2CAP_SERVER_HANDLE server = brb.reg.ServerHandle;
        LARGE_INTEGER interval;
        interval.QuadPart = -1000000;
        L2CAP_CHANNEL_HANDLE incoming = NULL;
        for (ULONG i = 0; i < 80; i++) {
            incoming = InterlockedCompareExchangePointer(&SscIncomingHandle, NULL, NULL);
            if (incoming != NULL) {
                break;
            }
            KeDelayExecutionThread(KernelMode, FALSE, &interval);
        }
        status = incoming == NULL ? STATUS_IO_TIMEOUT : SscAcceptIncoming(dev, file, request, address, incoming);
        dev->Header.ProfileDrvInterface.BthInitializeBrb((PBRB)&brb, BRB_L2CA_UNREGISTER_SERVER);
        brb.unreg.BtAddress = address;
        brb.unreg.Psm = 0x0017;
        brb.unreg.ServerHandle = server;
        BthEchoSharedSendBrbSynchronously(dev->Header.IoTarget, request, (PBRB)&brb, sizeof(brb.unreg));
    }
    WdfObjectDelete(request);
    InterlockedExchange(&SscProbeBusy, 0);
    return status;
}
#endif

VOID
BthEchoCliEvtDeviceFileCreate(
    _In_ WDFDEVICE  Device,
    _In_ WDFREQUEST  Request,
    _In_ WDFFILEOBJECT  FileObject
    )
/*++
Description:

    This routine is invoked by Framework when an application opens a handle
    to our device.

    In response we open a remote connection to the server.

Arguments:

    Device - Framework device object
    Request - Create request
    FileObject - File object corresponding to Create
--*/
{
    NTSTATUS status;
    PBTHECHOSAMPLE_CLIENT_CONTEXT devCtx = GetClientDeviceContext(Device);
    PBTHECHOSAMPLE_CLIENT_FILE_CONTEXT fileCtx = GetFileContext(FileObject);

    PAGED_CODE();

#ifdef SSC_LOCAL_PROFILE
    // Each handle selects its peer with a twelve-digit hexadecimal suffix.
    const UNICODE_STRING *name = WdfFileObjectGetFileName(FileObject);
    BTH_ADDR address = 0;
    if (!name || (name->Length != 13 * sizeof(WCHAR) && name->Length != 15 * sizeof(WCHAR)) || name->Buffer[0] != L'\\')
    {
        WdfRequestComplete(Request, STATUS_OBJECT_NAME_INVALID);
        return;
    }
    for (USHORT i = 1; i < 13; i++)
    {
        WCHAR digit = name->Buffer[i];
        if (digit >= L'0' && digit <= L'9')
            digit -= L'0';
        else if (digit >= L'A' && digit <= L'F')
            digit = digit - L'A' + 10;
        else
        {
            WdfRequestComplete(Request, STATUS_OBJECT_NAME_INVALID);
            return;
        }
        address = (address << 4) | digit;
    }
    if (!address)
    {
        WdfRequestComplete(Request, STATUS_INVALID_PARAMETER);
        return;
    }
    fileCtx->ServerBthAddress = address;
    if (name->Length == 15 * sizeof(WCHAR)) {
        if (name->Buffer[13] != L'-' || name->Buffer[14] != L'R') {
            WdfRequestComplete(Request, STATUS_OBJECT_NAME_INVALID);
            return;
        }
        WdfRequestComplete(Request, SscProbeRegistration(devCtx, FileObject, address));
        return;
    }
#else
    fileCtx->ServerBthAddress = devCtx->ServerBthAddress;
#endif
    fileCtx->ServerPsm = 0x0019;
    status = BthEchoCliOpenRemoteConnection(devCtx, FileObject, Request);

    // If it succeeds RemoteConnectCompletion will complete the request
    //

    if (!NT_SUCCESS(status))
    {
        WdfRequestComplete(Request, status);        
    }
}

VOID
BthEchoCliEvtFileClose(
    _In_ WDFFILEOBJECT  FileObject
    )
/*++
Description:

    This routine is invoked by Framework when I/O manager sends Close
    IRP for a file.

    In response we close the remote connection to the server.

Arguments:

    FileObject - File object corresponding to Close

--*/
{    
    PBTHECHOSAMPLE_CLIENT_CONTEXT devCtx;
    PBTHECHO_CONNECTION connection;

    PAGED_CODE();

    devCtx = GetClientDeviceContext(WdfFileObjectGetDevice(FileObject));

    connection = GetFileContext(FileObject)->Connection;
    if (connection == NULL) {
        return;
    }

    //
    // Since this routine is called at passive level we can disconnect
    // synchronously.
    //
    BthEchoConnectionObjectRemoteDisconnectSynchronously(
        &(devCtx->Header),
        connection
        );
}



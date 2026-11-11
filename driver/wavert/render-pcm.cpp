extern "C" {
#include <ntifs.h>
}
#include "definitions.h"
#include "render-pcm.h"

namespace {
// 80 ms of stereo 48 kHz signed 16-bit PCM. All data is nonpaged.
constexpr ULONG capacity = 15360;
constexpr ULONG frameSize = 4;
KSPIN_LOCK pcmLock;
BYTE pcm[capacity];
ULONG readOffset;
ULONG queued;
}

void SscPcmInitialize()
{
    KeInitializeSpinLock(&pcmLock);
}

void SscPcmWrite(const BYTE* data, ULONG size)
{
    if (size > capacity - frameSize) {
        const ULONG skip = (size - (capacity - frameSize) + frameSize - 1) & ~(frameSize - 1);
        data += skip;
        size -= skip;
    }

    KIRQL previous;
    KeAcquireSpinLock(&pcmLock, &previous);
    if (size > capacity - queued) {
        const ULONG discard = (size - (capacity - queued) + frameSize - 1) & ~(frameSize - 1);
        readOffset = (readOffset + discard) % capacity;
        queued -= discard;
    }
    const ULONG writeOffset = (readOffset + queued) % capacity;
    const ULONG first = min(size, capacity - writeOffset);
    RtlCopyMemory(pcm + writeOffset, data, first);
    RtlCopyMemory(pcm, data + first, size - first);
    queued += size;
    KeReleaseSpinLock(&pcmLock, previous);
}

NTSTATUS SscPcmRead(PPCPROPERTY_REQUEST request)
{
    PAGED_CODE();
    if (request->Verb != KSPROPERTY_TYPE_GET || request->ValueSize < frameSize ||
        request->Value == nullptr || request->Irp == nullptr) {
        return STATUS_INVALID_PARAMETER;
    }
    PEPROCESS process = IoGetRequestorProcess(request->Irp);
    if (process == nullptr) {
        return STATUS_ACCESS_DENIED;
    }
    PACCESS_TOKEN token = PsReferencePrimaryToken(process);
    const BOOLEAN admin = SeTokenIsAdmin(token);
    PsDereferencePrimaryToken(token);
    if (!admin) {
        return STATUS_ACCESS_DENIED;
    }

    KIRQL previous;
    KeAcquireSpinLock(&pcmLock, &previous);
    const ULONG count = min(queued, request->ValueSize) & ~(frameSize - 1);
    const ULONG first = min(count, capacity - readOffset);
    auto output = static_cast<BYTE*>(request->Value);
    RtlCopyMemory(output, pcm + readOffset, first);
    RtlCopyMemory(output + first, pcm, count - first);
    readOffset = (readOffset + count) % capacity;
    queued -= count;
    KeReleaseSpinLock(&pcmLock, previous);

    request->ValueSize = count;
    return STATUS_SUCCESS;
}

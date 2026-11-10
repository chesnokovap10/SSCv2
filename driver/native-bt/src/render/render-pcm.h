#pragma once

// {CBF893B1-A248-4B4C-8435-9078798C7E23}
static const GUID SscPcmPropertySet =
    {0xcbf893b1, 0xa248, 0x4b4c, {0x84, 0x35, 0x90, 0x78, 0x79, 0x8c, 0x7e, 0x23}};

void SscPcmInitialize();
void SscPcmWrite(const BYTE* data, ULONG size);
NTSTATUS SscPcmRead(PPCPROPERTY_REQUEST request);

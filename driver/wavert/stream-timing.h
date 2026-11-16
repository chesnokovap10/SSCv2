#pragma once

// carry is the fractional sample in units of 1/10,000,000 of a frame.
inline ULONGLONG SscElapsedFrames(ULONGLONG elapsed100ns, ULONG rate, ULONGLONG* carry)
{
    const ULONGLONG scaled = elapsed100ns * rate + *carry;
    *carry = scaled % 10000000ull;
    return scaled / 10000000ull;
}

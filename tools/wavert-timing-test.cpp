#include <cassert>
#include <cstdint>
using ULONGLONG = std::uint64_t;
using ULONG = std::uint32_t;
#include "../driver/wavert/stream-timing.h"

int main() {
    ULONGLONG carry = 0, frames = 0;
    // Fractional packet duration: 441 frames = 9.1875 ms at 48 kHz.
    for (int i = 0; i < 10000; ++i) frames += SscElapsedFrames(91875, 48000, &carry);
    assert(frames == 4410000 && carry == 0);
    // A delayed 30 ms callback accounts for three 480-frame packets.
    assert(SscElapsedFrames(300000, 48000, &carry) / 480 == 3);
    // Frequent polls preserve fractional samples at 44.1 kHz.
    frames = 0;
    for (int i = 0; i < 10000; ++i) frames += SscElapsedFrames(1000, 44100, &carry);
    assert(frames == 44100 && carry == 0);
}

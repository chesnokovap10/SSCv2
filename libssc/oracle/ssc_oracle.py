#!/usr/bin/env python3
"""SSC oracle: runs Samsung's libScalable_Encoder.so (aarch64) under Unicorn.

No WSL2/qemu and no Qiling. The blob only imports 8 libc functions, so a tiny
ELF loader plus Python stubs is enough. Every Oracle instance is a fresh
"process": the blob keeps encoder state in .bss globals, so one stream = one
instance.

The call sequence mirrors ssc_blob_helper.c from the old D:\\2\\SSC daemon
exactly (get_size -> init on a warm-up state -> create -> encode...), so the
output is byte-identical to the WSL2/Qiling daemons and to libssc/testdata.

Tracing: Oracle(trace=True) records every call to an exported blob function
(name, depth, x0..x7, return x0). Probes (on_enter/on_exit callbacks per
function name) can read emulator memory to dump intermediate buffers.

Usage:
  py -3.14 libssc/oracle/ssc_oracle.py check-golden            # all 6 goldens
  py -3.14 libssc/oracle/ssc_oracle.py trace --bitrate 229000 --frame 1
"""

import argparse
import math
import random
import struct
import sys
from pathlib import Path

from unicorn import (UC_ARCH_ARM64, UC_HOOK_CODE, UC_HOOK_MEM_INVALID,
                     UC_MODE_ARM, UC_PROT_ALL, Uc, UcError)
from unicorn import arm64_const as A

LIBSSC = Path(__file__).resolve().parents[1]
DEFAULT_BLOB = LIBSSC / "ref" / "libScalable_Encoder.so"
TESTDATA = LIBSSC / "testdata"
GOLDEN_SEED = 0x5A5C_2026
PCM_SCALE = 1 << 29

# Memory layout (all arbitrary, just non-overlapping).
IMAGE_BASE = 0x1000_0000
STUB_BASE = 0x2000_0000      # one `ret` per import + the halt address
HEAP_BASE = 0x3000_0000
HEAP_SIZE = 64 << 20
STACK_TOP = 0x5000_0000
STACK_SIZE = 8 << 20
TLS_BASE = 0x6000_0000       # bionic: stack guard at [tpidr_el0 + 0x28]
IO_BASE = 0x7000_0000        # PCM in / bitstream out scratch
IO_SIZE = 1 << 20

STACK_GUARD = 0x5EC0_DE00_C0FF_EE00

R_AARCH64_ABS64 = 257
R_AARCH64_GLOB_DAT = 1025
R_AARCH64_JUMP_SLOT = 1026
R_AARCH64_RELATIVE = 1027

RET_INSN = struct.pack("<I", 0xD65F03C0)

IMPORTS = ("malloc", "free", "memcpy", "memset", "__stack_chk_fail",
           "__cxa_finalize", "__cxa_atexit", "__register_atfork")

FRAME_SAMPLES = 864
MAX_ENCODE = 4096
BIT_DEPTH = 24


def _align(x, a):
    return (x + a - 1) & ~(a - 1)


class BlobError(RuntimeError):
    pass


class Elf:
    """Just enough ELF64 parsing for one aarch64 shared object."""

    def __init__(self, data: bytes):
        if data[:4] != b"\x7fELF" or data[4] != 2:
            raise BlobError("not an ELF64 file")
        self.data = data
        (e_phoff, e_shoff) = struct.unpack_from("<QQ", data, 0x20)
        (e_phentsize, e_phnum, e_shentsize, e_shnum,
         e_shstrndx) = struct.unpack_from("<HHHHH", data, 0x36)

        self.loads = []
        for i in range(e_phnum):
            (p_type, _flags, off, vaddr, _paddr, filesz, memsz,
             _align_) = struct.unpack_from("<IIQQQQQQ", data, e_phoff + i * e_phentsize)
            if p_type == 1:  # PT_LOAD
                self.loads.append((off, vaddr, filesz, memsz))

        shdrs = [struct.unpack_from("<IIQQQQIIQQ", data, e_shoff + i * e_shentsize)
                 for i in range(e_shnum)]
        shstr_off = shdrs[e_shstrndx][4]

        def secname(sh):
            o = shstr_off + sh[0]
            return data[o:data.index(b"\0", o)].decode()

        self.sections = {secname(sh): sh for sh in shdrs}

        dynsym = self.sections[".dynsym"]
        dynstr_off = self.sections[".dynstr"][4]
        self.symbols = []
        for i in range(dynsym[5] // 24):
            (st_name, st_info, _other, shndx, value,
             size) = struct.unpack_from("<IBBHQQ", data, dynsym[4] + i * 24)
            o = dynstr_off + st_name
            name = data[o:data.index(b"\0", o)].decode()
            self.symbols.append((name, st_info, shndx, value, size))

        self.relocs = []
        for name in (".rela.dyn", ".rela.plt"):
            sh = self.sections.get(name)
            if not sh:
                continue
            for i in range(sh[5] // 24):
                r_off, r_info, r_add = struct.unpack_from("<QQq", data, sh[4] + i * 24)
                self.relocs.append((r_off, r_info & 0xFFFFFFFF, r_info >> 32, r_add))

    def image_size(self):
        return _align(max(v + m for (_o, v, _f, m) in self.loads), 0x1000)


class CallRecord:
    __slots__ = ("name", "depth", "args", "ret", "children")

    def __init__(self, name, depth, args):
        self.name, self.depth, self.args = name, depth, args
        self.ret = None
        self.children = []

    def __repr__(self):
        a = ", ".join(hex(x) for x in self.args[:4])
        r = "?" if self.ret is None else hex(self.ret)
        return f"{'  ' * self.depth}{self.name}({a}) -> {r}"


class Oracle:
    def __init__(self, blob_path=DEFAULT_BLOB, trace=False):
        self.elf = Elf(Path(blob_path).read_bytes())
        self.uc = Uc(UC_ARCH_ARM64, UC_MODE_ARM)
        try:  # LSE atomics etc.; harmless if the model constant is missing
            self.uc.ctl_set_cpu_model(A.UC_CPU_ARM64_MAX)
        except Exception:
            pass

        self.heap_next = HEAP_BASE
        self.exports = {}          # name -> absolute address (functions + objects)
        self.func_at = {}          # absolute entry address -> name
        self.stub_at = {}          # absolute stub address -> import name
        self.trace_enabled = trace
        self.calls = []            # top-level CallRecords (current frame)
        self._stack = []           # (record, lr, sp)
        self.probes_enter = {}     # name -> fn(oracle, record)
        self.probes_exit = {}

        self._map_and_load()
        self._install_stubs()
        self._relocate()
        self._setup_cpu()
        if trace:
            self._install_trace()

        self.state = None
        self.bitrate = None

    # ---------------------------------------------------------------- loader
    def _map_and_load(self):
        uc = self.uc
        uc.mem_map(IMAGE_BASE, self.elf.image_size(), UC_PROT_ALL)
        for off, vaddr, filesz, _memsz in self.elf.loads:
            uc.mem_write(IMAGE_BASE + vaddr, self.elf.data[off:off + filesz])
        uc.mem_map(STUB_BASE, 0x1000, UC_PROT_ALL)
        uc.mem_map(HEAP_BASE, HEAP_SIZE, UC_PROT_ALL)
        uc.mem_map(STACK_TOP - STACK_SIZE, STACK_SIZE, UC_PROT_ALL)
        uc.mem_map(TLS_BASE, 0x1000, UC_PROT_ALL)
        uc.mem_map(IO_BASE, IO_SIZE, UC_PROT_ALL)
        uc.mem_write(TLS_BASE + 0x28, struct.pack("<Q", STACK_GUARD))

        for name, info, shndx, value, _size in self.elf.symbols:
            if name and shndx != 0:
                self.exports[name] = IMAGE_BASE + value
                if info & 0xF == 2:  # STT_FUNC
                    self.func_at[IMAGE_BASE + value] = name

    def _install_stubs(self):
        names = list(IMPORTS) + ["<halt>"]
        for i, name in enumerate(names):
            addr = STUB_BASE + i * 4
            self.uc.mem_write(addr, RET_INSN)
            self.stub_at[addr] = name
        self.halt_addr = STUB_BASE + (len(names) - 1) * 4
        self.uc.hook_add(UC_HOOK_CODE, self._on_stub, begin=STUB_BASE,
                         end=STUB_BASE + len(names) * 4 - 1)
        self.uc.hook_add(UC_HOOK_MEM_INVALID, self._on_bad_mem)

    def _relocate(self):
        stub_by_name = {v: k for k, v in self.stub_at.items()}
        for r_off, r_type, r_sym, r_add in self.elf.relocs:
            where = IMAGE_BASE + r_off
            if r_type == R_AARCH64_RELATIVE:
                val = IMAGE_BASE + r_add
            elif r_type in (R_AARCH64_GLOB_DAT, R_AARCH64_JUMP_SLOT, R_AARCH64_ABS64):
                name, _info, shndx, value, _size = self.elf.symbols[r_sym]
                if shndx != 0:
                    val = IMAGE_BASE + value + r_add
                elif name in stub_by_name:
                    val = stub_by_name[name] + r_add
                else:
                    raise BlobError(f"unresolved import {name}")
            else:
                raise BlobError(f"unsupported relocation type {r_type}")
            self.uc.mem_write(where, struct.pack("<Q", val & 0xFFFF_FFFF_FFFF_FFFF))

    def _setup_cpu(self):
        self.uc.reg_write(A.UC_ARM64_REG_TPIDR_EL0, TLS_BASE)
        # Make sure FP/SIMD is enabled (CPACR_EL1.FPEN = 0b11).
        cpacr = self.uc.reg_read(A.UC_ARM64_REG_CPACR_EL1)
        self.uc.reg_write(A.UC_ARM64_REG_CPACR_EL1, cpacr | (3 << 20))

    # ----------------------------------------------------------- libc stubs
    def _on_stub(self, uc, address, _size, _user):
        name = self.stub_at.get(address)
        if name is None or name == "<halt>":
            return
        x0 = uc.reg_read(A.UC_ARM64_REG_X0)
        x1 = uc.reg_read(A.UC_ARM64_REG_X1)
        x2 = uc.reg_read(A.UC_ARM64_REG_X2)
        if name == "malloc":
            size = max(1, x0)
            addr = self.heap_next
            self.heap_next = _align(addr + size, 16)
            if self.heap_next > HEAP_BASE + HEAP_SIZE:
                raise BlobError("oracle heap exhausted")
            uc.reg_write(A.UC_ARM64_REG_X0, addr)  # fresh memory is zeroed
        elif name == "free":
            pass                                   # bump allocator, never reused
        elif name == "memcpy":
            if x2:
                uc.mem_write(x0, bytes(uc.mem_read(x1, x2)))
        elif name == "memset":
            if x2:
                uc.mem_write(x0, bytes([x1 & 0xFF]) * x2)
        elif name == "__stack_chk_fail":
            uc.emu_stop()
            raise BlobError("blob reported stack corruption (__stack_chk_fail)")
        else:  # __cxa_finalize / __cxa_atexit / __register_atfork
            uc.reg_write(A.UC_ARM64_REG_X0, 0)

    def _on_bad_mem(self, uc, access, address, size, _value, _user):
        pc = uc.reg_read(A.UC_ARM64_REG_PC)
        print(f"oracle: invalid memory access type={access} addr={address:#x} "
              f"size={size} pc={pc:#x} ({self.describe(pc)})", file=sys.stderr)
        return False

    def describe(self, addr):
        """Nearest exported function at or below addr, as 'name+0xoff'."""
        best = None
        for a, n in self.func_at.items():
            if a <= addr and (best is None or a > best[0]):
                best = (a, n)
        return f"{best[1]}+{addr - best[0]:#x}" if best else "?"

    # ---------------------------------------------------------------- trace
    def _install_trace(self):
        for addr in self.func_at:
            self.uc.hook_add(UC_HOOK_CODE, self._on_enter, begin=addr, end=addr)
        # Return sites: every BL/BLR in the image returns to its address + 4.
        text = self.elf.sections[".text"]
        lo, hi = text[3], text[3] + text[5]
        test = self.elf.sections.get("test")
        if test:
            hi = max(hi, test[3] + test[5])
        code = self.elf.data
        ret_sites = set()
        for va in range(lo, hi, 4):
            w = struct.unpack_from("<I", code, va)[0]  # .text: vaddr == file offset
            if (w >> 26) == 0b100101 or (w & 0xFFFFFC1F) == 0xD63F0000:
                ret_sites.add(IMAGE_BASE + va + 4)
        for addr in ret_sites:
            self.uc.hook_add(UC_HOOK_CODE, self._on_return, begin=addr, end=addr)
        self.uc.hook_add(UC_HOOK_CODE, self._on_return, begin=self.halt_addr,
                         end=self.halt_addr)

    def _on_enter(self, uc, address, _size, _user):
        name = self.func_at[address]
        args = [uc.reg_read(getattr(A, f"UC_ARM64_REG_X{i}")) for i in range(8)]
        rec = CallRecord(name, len(self._stack), args)
        if self._stack:
            self._stack[-1][0].children.append(rec)
        else:
            self.calls.append(rec)
        self._stack.append((rec, uc.reg_read(A.UC_ARM64_REG_LR),
                            uc.reg_read(A.UC_ARM64_REG_SP)))
        probe = self.probes_enter.get(name)
        if probe:
            probe(self, rec)

    def _on_return(self, uc, address, _size, _user):
        sp = uc.reg_read(A.UC_ARM64_REG_SP)
        # Pops tail-called frames too (they share the caller's return site).
        while self._stack and self._stack[-1][1] == address and self._stack[-1][2] == sp:
            rec = self._stack.pop()[0]
            rec.ret = uc.reg_read(A.UC_ARM64_REG_X0)
            probe = self.probes_exit.get(rec.name)
            if probe:
                probe(self, rec)

    # ---------------------------------------------------------------- calls
    def call(self, name, *args, max_insns=0):
        """Call an exported blob function with up to 8 integer args.
        max_insns > 0 bounds runaway loops (Unicorn's wall-clock timeout costs
        ~15 ms per call on Windows, an instruction count does not)."""
        if len(args) > 8:
            raise BlobError("more than 8 integer args not supported")
        uc = self.uc
        for i, a in enumerate(args):
            uc.reg_write(getattr(A, f"UC_ARM64_REG_X{i}"), a & 0xFFFF_FFFF_FFFF_FFFF)
        uc.reg_write(A.UC_ARM64_REG_SP, STACK_TOP - 0x100)
        uc.reg_write(A.UC_ARM64_REG_LR, self.halt_addr)
        self._stack = []
        try:
            uc.emu_start(self.exports[name], self.halt_addr, count=max_insns)
        except UcError as e:
            pc = uc.reg_read(A.UC_ARM64_REG_PC)
            raise BlobError(f"{name}: {e} at pc={pc:#x} ({self.describe(pc)})") from e
        pc = uc.reg_read(A.UC_ARM64_REG_PC)
        if pc != self.halt_addr:
            raise BlobError(f"{name}: timed out at pc={pc:#x} ({self.describe(pc)})")
        # emu_start stops *before* the halt address, so its hook never fires:
        # close the outermost frame(s) here.
        self._on_return(uc, self.halt_addr, 0, None)
        return uc.reg_read(A.UC_ARM64_REG_X0)

    @staticmethod
    def s32(v):
        v &= 0xFFFF_FFFF
        return v - (1 << 32) if v & 0x8000_0000 else v

    def read(self, addr, n):
        return bytes(self.uc.mem_read(addr, n))

    def read_i32(self, addr, n):
        return list(struct.unpack(f"<{n}i", self.read(addr, 4 * n)))

    def read_i16(self, addr, n):
        return list(struct.unpack(f"<{n}h", self.read(addr, 2 * n)))

    # ------------------------------------------------- encoder (helper.c order)
    def open(self, sample_rate, channels, bitrate, bit_depth=BIT_DEPTH):
        size = self.s32(self.call("ssc_encoder_get_size", channels, sample_rate))
        if size <= 0 or size > 16 << 20:
            raise BlobError(f"ssc_encoder_get_size returned {size}")
        warm = self._alloc(size)
        ret = self.s32(self.call("ssc_encoder_init", warm, sample_rate, channels, bit_depth))
        if ret != 0:
            raise BlobError(f"ssc_encoder_init returned {ret}")
        err_ptr = IO_BASE + IO_SIZE - 16
        self.uc.mem_write(err_ptr, struct.pack("<i", -1))
        state = self.call("ssc_encoder_create", sample_rate, channels, bit_depth, err_ptr)
        err = struct.unpack("<i", self.read(err_ptr, 4))[0]
        if not state or err != 0:
            raise BlobError(f"ssc_encoder_create failed err={err} state={state:#x}")
        self.state, self.channels, self.bitrate = state, channels, bitrate
        self.calls = []
        return self

    def _alloc(self, size):
        """Zeroed host-side allocation from the blob heap (helper used calloc)."""
        addr = self.heap_next
        self.heap_next = _align(addr + max(1, size), 16)
        return addr

    def encode(self, pcm_bytes: bytes, frame_samples=FRAME_SAMPLES):
        """Encode one frame of interleaved int32 PCM (2^29 scale) -> bytes."""
        if self.state is None:
            raise BlobError("open() first")
        pcm_addr = IO_BASE
        out_addr = IO_BASE + 0x80000
        self.uc.mem_write(pcm_addr, pcm_bytes)
        self.uc.mem_write(out_addr, b"\0" * MAX_ENCODE)  # helper memsets `out`
        self.calls = []
        ret = self.s32(self.call("ssc_encode", self.state, pcm_addr, frame_samples,
                                 out_addr, self.bitrate))
        if ret <= 0 or ret > MAX_ENCODE:
            raise BlobError(f"ssc_encode returned {ret}")
        return self.read(out_addr, ret)


# ------------------------------------------------------------------- golden
def golden_pcm(seed, frame_index, rate, channels=2):
    """The deterministic test frame used by the goldens (copied from the old
    repo's tools/golden/ssc_golden.py gen_frame_pcm): a 440 Hz +-110 Hz tone at
    half scale plus uniform dither, 864 x 2ch int32 at 2^29."""
    r = random.Random(seed + frame_index * 0x10000)
    vals = []
    for i in range(FRAME_SAMPLES * channels):
        tone = PCM_SCALE * 0.5 * math.sin(
            2.0 * math.pi * (440.0 + 110.0 * math.sin(frame_index)) * (i % FRAME_SAMPLES) / rate
        )
        dither = r.uniform(-0.06, 0.06) * PCM_SCALE
        vals.append(int(tone + dither))
    return struct.pack("<%di" % (FRAME_SAMPLES * channels), *vals)


def read_golden(path):
    d = Path(path).read_bytes()
    magic, ver, rate, ch, bitrate, frames, seed = struct.unpack_from("<4sIIIIII", d, 0)
    if magic != b"SSCG" or ver != 1:
        raise BlobError(f"{path}: not an SSCG v1 golden")
    off, payloads = 28, []
    for _ in range(frames):
        n = struct.unpack_from("<I", d, off)[0]
        payloads.append(d[off + 4:off + 4 + n])
        off += 4 + n
    return dict(rate=rate, channels=ch, bitrate=bitrate, frames=frames, seed=seed,
                payloads=payloads)


def check_golden(path, blob):
    g = read_golden(path)
    o = Oracle(blob).open(g["rate"], g["channels"], g["bitrate"])
    for i, want in enumerate(g["payloads"]):
        got = o.encode(golden_pcm(g["seed"], i, g["rate"], g["channels"]))
        if got != want:
            diff = next((k for k in range(min(len(got), len(want))) if got[k] != want[k]),
                        min(len(got), len(want)))
            return False, (f"frame {i}: {len(got)} vs {len(want)} bytes, "
                           f"first diff at byte {diff}")
    return True, f"{g['frames']} frames"


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--blob", default=str(DEFAULT_BLOB))
    sub = ap.add_subparsers(dest="cmd", required=True)

    c = sub.add_parser("check-golden", help="byte-compare against libssc/testdata/*.golden")
    c.add_argument("goldens", nargs="*")

    t = sub.add_parser("trace", help="print the call tree of one frame")
    t.add_argument("--rate", type=int, default=48000)
    t.add_argument("--bitrate", type=int, default=229000)
    t.add_argument("--frame", type=int, default=0, help="frame index to trace")
    t.add_argument("--seed", type=int, default=GOLDEN_SEED)
    t.add_argument("--max-depth", type=int, default=99)

    args = ap.parse_args(argv)

    if args.cmd == "check-golden":
        files = args.goldens or sorted(str(p) for p in TESTDATA.glob("*.golden"))
        bad = 0
        for f in files:
            ok, msg = check_golden(f, args.blob)
            print(f"{'PASS' if ok else 'FAIL'}  {Path(f).name}: {msg}")
            bad += not ok
        print(f"{len(files) - bad}/{len(files)} passed")
        return 1 if bad else 0

    if args.cmd == "trace":
        o = Oracle(args.blob, trace=True).open(args.rate, 2, args.bitrate)
        for i in range(args.frame + 1):
            out = o.encode(golden_pcm(args.seed, i, args.rate))

        def walk(recs):
            for r in recs:
                if r.depth <= args.max_depth:
                    print(r)
                    walk(r.children)
        walk(o.calls)
        print(f"-- frame {args.frame}: {len(out)} bytes, head {out[:8].hex()}")
        return 0


if __name__ == "__main__":
    sys.exit(main())

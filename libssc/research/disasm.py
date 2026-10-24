#!/usr/bin/env python3
"""Disassemble blob functions with symbol-annotated branches and ADRP targets.

  py -3.14 libssc/research/disasm.py ssc_custom_mode_create ssc_encoder_init
  py -3.14 libssc/research/disasm.py 0xd168:0xd400        # raw va range
"""

import struct
import sys
from pathlib import Path

from capstone import CS_ARCH_ARM64, CS_MODE_ARM, Cs

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "oracle"))
from ssc_oracle import DEFAULT_BLOB, Elf  # noqa: E402


class Blob:
    def __init__(self, path=DEFAULT_BLOB):
        self.elf = Elf(Path(path).read_bytes())
        self.data = self.elf.data
        self.funcs = {}   # name -> (va, size)
        self.objs = {}    # va -> name
        for name, info, shndx, value, size in self.elf.symbols:
            if not name or shndx == 0:
                continue
            if info & 0xF == 2:
                self.funcs[name] = (value, size)
            else:
                self.objs[value] = name
        self.by_va = sorted((va, n, sz) for n, (va, sz) in self.funcs.items())
        # PLT slot -> symbol, via .rela.plt GOT entries and the PLT stubs.
        self.got_sym = {}
        for r_off, r_type, r_sym, _ in self.elf.relocs:
            if r_type in (1025, 1026):
                self.got_sym[r_off] = self.elf.symbols[r_sym][0]
        self.relative = {r_off: add for r_off, r_type, _s, add in self.elf.relocs if r_type == 1027}
        self.plt = {}
        plt = self.elf.sections.get(".plt")
        if plt:
            md = Cs(CS_ARCH_ARM64, CS_MODE_ARM)
            insns = list(md.disasm(self.data[plt[4]:plt[4] + plt[5]], plt[3]))
            for i, ins in enumerate(insns):
                if ins.mnemonic == "adrp" and i + 1 < len(insns):
                    page = int(ins.op_str.split("#")[1], 16)
                    nxt = insns[i + 1]
                    if nxt.mnemonic == "ldr" and "#" in nxt.op_str:
                        off = int(nxt.op_str.split("#")[1].rstrip("]!"), 16)
                        slot = page + off
                        if slot in self.got_sym:
                            self.plt[ins.address] = self.got_sym[slot]

    def name_at(self, va):
        if va in self.plt:
            return self.plt[va] + "@plt"
        for fva, n, sz in self.by_va:
            if fva <= va < fva + max(sz, 4):
                return n if va == fva else f"{n}+{va - fva:#x}"
        if va in self.objs:
            return self.objs[va]
        best = None
        for ova, n in self.objs.items():
            if ova <= va and (best is None or ova > best[0]):
                best = (ova, n)
        if best and va - best[0] < 0x4000:
            return f"{best[1]}+{va - best[0]:#x}"
        return None

    def disasm(self, start, end, out=sys.stdout):
        md = Cs(CS_ARCH_ARM64, CS_MODE_ARM)
        regs = {}
        for ins in md.disasm(self.data[start:end], start):
            note = ""
            ops = ins.op_str
            if ins.mnemonic in ("bl", "b") or ins.mnemonic.startswith("b."):
                try:
                    tgt = int(ops.split("#")[-1], 16)
                    n = self.name_at(tgt)
                    if n and (ins.mnemonic == "bl" or not n.startswith(self.name_at(start) or "?")):
                        note = n
                except ValueError:
                    pass
            if ins.mnemonic == "adrp":
                rd = ops.split(",")[0]
                regs[rd] = int(ops.split("#")[1], 16)
            elif ins.mnemonic in ("add", "ldr", "ldrsw", "ldrh", "ldrsh", "ldrb", "str") and "#" in ops:
                parts = [p.strip() for p in ops.replace("[", "").replace("]", "").split(",")]
                base = parts[1] if ins.mnemonic == "add" else parts[1]
                if base in regs:
                    try:
                        imm = int(parts[-1].lstrip("#").rstrip("!"), 16)
                        va = regs[base] + imm
                        n = self.name_at(va)
                        note = f"{va:#x}" + (f" {n}" if n else "")
                        if va in self.relative:
                            t = self.relative[va]
                            tn = self.name_at(t)
                            note += f" -> {t:#x}" + (f" {tn}" if tn else "")
                    except ValueError:
                        pass
            print(f"  {ins.address:6x}: {ins.mnemonic:8s} {ops}" + (f"   ; {note}" if note else ""), file=out)

    def function(self, name, out=sys.stdout):
        va, size = self.funcs[name]
        print(f"{name} @ {va:#x} size {size}", file=out)
        self.disasm(va, va + size, out)


def main():
    b = Blob()
    for arg in sys.argv[1:]:
        if ":" in arg:
            lo, hi = (int(x, 16) for x in arg.split(":"))
            b.disasm(lo, hi)
        else:
            b.function(arg)
        print()


if __name__ == "__main__":
    main()

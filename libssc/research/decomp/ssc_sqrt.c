/* ssc_sqrt @ 001115c0 size 176 */

ulong ssc_sqrt(ulong param_1)

{
  uint uVar1;
  int iVar2;
  short sVar3;
  uint uVar4;
  uint uVar5;
  
  uVar5 = (uint)param_1;
  if (uVar5 != 0) {
    if (0x3fffffff < (int)uVar5) {
      return 0x7fff;
    }
    uVar1 = (uint)LZCOUNT(uVar5) & 0x1e;
    uVar4 = (uint)LZCOUNT(uVar5) >> 1;
    sVar3 = (short)((int)uVar5 >> (0x10 - uVar1 & 0x1f));
    if (uVar5 >> 0x10 == 0) {
      sVar3 = (short)(uVar5 << (ulong)(uVar1 - 0x10 & 0x1f));
    }
    uVar1 = (int)sVar3 ^ 0xffff8000;
    iVar2 = (int)(uVar1 * 2 *
                  ((((int)(uVar1 * 2 * ((uVar1 * -0x298 >> 0xf) + 0x6a3 & 0xffff) + -0xbc30000) >>
                    0x10) * uVar1 >> 0xf) + 0x2d29 & 0xffff) + 0x5a870000) >> 0x10;
    uVar1 = iVar2 >> (uVar4 - 1 & 0x1f);
    if (uVar5 >> 0x1c != 0) {
      uVar1 = iVar2 << (ulong)(1 - uVar4 & 0x1f);
    }
    param_1 = (ulong)uVar1;
  }
  return param_1;
}


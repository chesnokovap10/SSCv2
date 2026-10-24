/* ssc_sqrt @ 00106bec size 232 */

ulong ssc_sqrt(ulong param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = (int)param_1;
  if (iVar4 != 0) {
    if (iVar4 < 0x40000000) {
      iVar5 = ec_ilog(param_1 & 0xffffffff);
      iVar5 = (iVar5 + -1) * 0x10000 >> 0x11;
      iVar2 = iVar5 + -7;
      uVar3 = 0xe - iVar5;
      iVar5 = iVar4 >> (iVar2 * 2 & 0x1fU);
      if (iVar2 < 1) {
        iVar5 = iVar4 << (ulong)(iVar2 * -2 & 0x1f);
      }
      iVar4 = (int)(iVar5 << 0x10 ^ 0x80000000U) >> 0x10;
      iVar4 = (int)((((int)((((int)((((iVar4 * -0x298 >> 0xf) + 0x6a3) * iVar4 * 2 & 0xffff0000U) +
                                   0xf43d0000) >> 0x10) * iVar4 * 2 & 0xffff0000U) + 0x2d290000) >>
                     0x10) * iVar4 * 2 & 0xffff0000U) + 0x5a870000) >> 0x10;
      uVar1 = iVar4 >> (uVar3 & 0x1f);
      if ((int)uVar3 < 1) {
        uVar1 = iVar4 << (ulong)(-uVar3 & 0x1f);
      }
      return (ulong)uVar1;
    }
    param_1 = 0x7fff;
  }
  return param_1;
}


/* frac_div32 @ 00106910 size 416 */

int frac_div32(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  ushort uVar7;
  int iVar8;
  int iVar9;
  
  iVar8 = ec_ilog(param_2);
  iVar8 = iVar8 * 0x10000 + -0x10000 >> 0x10;
  uVar5 = iVar8 - 0x1d;
  uVar6 = 0x1d - iVar8;
  iVar8 = param_2 >> (uVar5 & 0x1f);
  if ((int)uVar5 < 1) {
    iVar8 = param_2 << (ulong)(uVar6 & 0x1f);
  }
  iVar1 = iVar8 + 0x8000 >> 0x10;
  uVar3 = param_1 >> (uVar5 & 0x1f);
  if ((int)uVar5 < 1) {
    uVar3 = param_1 << (ulong)(uVar6 & 0x1f);
  }
  iVar9 = ec_ilog(iVar1);
  iVar9 = iVar9 * 0x10000 + -0x10000 >> 0x10;
  iVar2 = iVar1 >> (iVar9 - 0xfU & 0x1f);
  if ((int)(iVar9 - 0xfU) < 1) {
    iVar2 = iVar1 << (ulong)(0xfU - iVar9 & 0x1f);
  }
  iVar1 = (int)(iVar2 << 0x10 ^ 0x80000000U) >> 0x10;
  iVar4 = iVar1 * -0x7878 + 0x78780000;
  iVar2 = iVar4 >> 0x10;
  uVar7 = (ushort)((uint)iVar4 >> 0x10);
  uVar7 = uVar7 - (short)((uint)((short)((uVar7 ^ 0x8000) + (short)((uint)(iVar2 * iVar1) >> 0xf)) *
                                iVar2) >> 0xf);
  iVar2 = (int)(short)(uVar7 - (short)(((int)(short)((uVar7 ^ 0x8000) +
                                                    (short)((uint)((short)uVar7 * iVar1) >> 0xf)) *
                                        (int)(short)uVar7 * 2 & 0xffff0000U) + 0x10000 >> 0x10));
  iVar1 = iVar2 >> (iVar9 - 0x10U & 0x1f);
  if ((int)(iVar9 - 0x10U) < 1) {
    iVar1 = iVar2 << (ulong)(0x10U - iVar9 & 0x1f);
  }
  iVar9 = iVar1 * 0x2000 + 0x8000 >> 0x10;
  iVar1 = ((int)(iVar9 * (uVar3 & 0xffff)) >> 0xf) + ((int)uVar3 >> 0x10) * iVar9 * 2;
  uVar5 = ((int)(uVar3 + 2) >> 2) - (int)((ulong)((long)iVar1 * (long)iVar8) >> 0x1f);
  iVar1 = iVar1 + (((int)((uVar5 & 0xffff) * iVar9) >> 0xf) + iVar9 * ((int)uVar5 >> 0x10) * 2) * 4;
  if (0x1fffffff < iVar1) {
    return 0x7fffffff;
  }
  iVar8 = -0x7fffffff;
  if (-0x20000000 < iVar1) {
    iVar8 = iVar1 * 4;
  }
  return iVar8;
}


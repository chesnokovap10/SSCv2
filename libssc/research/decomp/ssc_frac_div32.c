/* ssc_frac_div32 @ 00111370 size 332 */

int ssc_frac_div32(int param_1,uint param_2)

{
  int iVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  ushort uVar8;
  bool bVar9;
  int iVar10;
  
  uVar5 = (int)LZCOUNT(param_2) - 2;
  uVar6 = 2 - (int)LZCOUNT(param_2);
  bVar9 = param_2 >> 0x1e == 0;
  iVar3 = (int)param_2 >> (uVar6 & 0x1f);
  if (bVar9) {
    iVar3 = param_2 << (ulong)(uVar5 & 0x1f);
  }
  iVar1 = iVar3 + 0x8000 >> 0x10;
  uVar6 = param_1 >> (uVar6 & 0x1f);
  if (bVar9) {
    uVar6 = param_1 << (ulong)(uVar5 & 0x1f);
  }
  iVar10 = (int)LZCOUNT(iVar1);
  sVar2 = (short)(iVar1 >> (0x10U - iVar10 & 0x1f));
  if (-0x8001 < iVar3) {
    sVar2 = (short)(iVar1 << (ulong)(iVar10 - 0x10U & 0x1f));
  }
  uVar5 = (int)sVar2 ^ 0xffff8000;
  iVar4 = uVar5 * -0x7878 + 0x78780000;
  iVar1 = iVar4 >> 0x10;
  uVar7 = iVar1 - ((uint)((short)(((ushort)((uint)iVar4 >> 0x10) ^ 0x8000) +
                                 (short)(iVar1 * uVar5 >> 0xf)) * iVar1) >> 0xf);
  uVar8 = (ushort)uVar7;
  iVar4 = (int)(short)(uVar8 - (short)((int)(short)((uVar8 ^ 0x8000) +
                                                   (short)((int)(short)uVar8 * uVar5 >> 0xf)) *
                                       (-(uVar7 >> 0xf & 1) & 0xfffe0000 | (uVar7 & 0xffff) << 1) +
                                       0x10000 >> 0x10));
  iVar1 = iVar4 << (ulong)(iVar10 - 0xfU & 0x1f);
  if (iVar3 < -0x8000) {
    iVar1 = iVar4 >> (0xfU - iVar10 & 0x1f);
  }
  iVar10 = iVar1 * 0x2000 + 0x8000 >> 0x10;
  iVar1 = ((int)uVar6 >> 0xf & 0xfffffffeU) * iVar10 + ((int)(iVar10 * (uVar6 & 0xffff)) >> 0xf);
  uVar5 = ((int)(uVar6 + 2) >> 2) - (int)((ulong)((long)iVar1 * (long)iVar3) >> 0x1f);
  iVar1 = iVar1 + (((int)((uVar5 & 0xffff) * iVar10) >> 0xf) + iVar10 * ((int)uVar5 >> 0x10) * 2) *
                  4;
  iVar3 = -0x7fffffff;
  if (-0x20000000 < iVar1) {
    iVar3 = iVar1 * 4;
  }
  iVar10 = 0x7fffffff;
  if (iVar1 < 0x20000000) {
    iVar10 = iVar3;
  }
  return iVar10;
}


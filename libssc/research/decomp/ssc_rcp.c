/* ssc_rcp @ 00106ab0 size 196 */

int ssc_rcp(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  ushort uVar4;
  int iVar5;
  
  iVar5 = ec_ilog();
  iVar5 = iVar5 * 0x10000 + -0x10000 >> 0x10;
  iVar1 = param_1 >> (iVar5 - 0xfU & 0x1f);
  if ((int)(iVar5 - 0xfU) < 1) {
    iVar1 = param_1 << (ulong)(0xfU - iVar5 & 0x1f);
  }
  iVar1 = (int)(iVar1 << 0x10 ^ 0x80000000U) >> 0x10;
  iVar3 = iVar1 * -0x7878 + 0x78780000;
  iVar2 = iVar3 >> 0x10;
  uVar4 = (ushort)((uint)iVar3 >> 0x10);
  uVar4 = uVar4 - (short)((uint)((short)((uVar4 ^ 0x8000) + (short)((uint)(iVar2 * iVar1) >> 0xf)) *
                                iVar2) >> 0xf);
  iVar2 = (int)(short)(uVar4 - (short)(((int)(short)((uVar4 ^ 0x8000) +
                                                    (short)((uint)((short)uVar4 * iVar1) >> 0xf)) *
                                        (int)(short)uVar4 * 2 & 0xffff0000U) + 0x10000 >> 0x10));
  iVar1 = iVar2 >> (iVar5 - 0x10U & 0x1f);
  if ((int)(iVar5 - 0x10U) < 1) {
    iVar1 = iVar2 << (ulong)(0x10U - iVar5 & 0x1f);
  }
  return iVar1;
}


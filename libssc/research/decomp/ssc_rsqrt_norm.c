/* ssc_rsqrt_norm @ 00106b74 size 120 */

int ssc_rsqrt_norm(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = (int)(param_1 << 0x10 ^ 0x80000000U) >> 0x10;
  iVar1 = (((iVar2 * 0x1a39 >> 0xf) + -0x34b2) * iVar2 * 2 & 0xffff0000U) + 0x5c050000;
  iVar3 = iVar1 >> 0x10;
  iVar1 = (iVar1 >> 0xf) * iVar3;
  iVar1 = (int)(short)(((short)((uint)iVar1 >> 0x10) +
                       (short)((uint)((iVar1 >> 0x10) * iVar2) >> 0xf)) * 2 ^ 0x8000);
  return iVar3 + ((uint)((iVar1 * (iVar1 * 0x6000 + -0x40000000 >> 0x10) * 2 >> 0x10) * iVar3) >>
                 0xf);
}


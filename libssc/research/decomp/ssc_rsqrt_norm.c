/* ssc_rsqrt_norm @ 00111558 size 104 */

int ssc_rsqrt_norm(short param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  uVar2 = (int)param_1 ^ 0xffff8000;
  iVar1 = (int)(uVar2 * (((int)(uVar2 * 0x1a39) >> 0xf) + -0x34b2) * 2 + 0x5c050000) >> 0x10;
  iVar3 = iVar1 * iVar1 * 2;
  iVar3 = (int)(short)(((short)((uint)iVar3 >> 0x10) + (short)((iVar3 >> 0x10) * uVar2 >> 0xf)) * 2
                      ^ 0x8000);
  return iVar1 + ((uint)(((iVar3 * 0x6000 + -0x40000000 >> 0x10) * iVar3 >> 0xf) * iVar1) >> 0xf);
}


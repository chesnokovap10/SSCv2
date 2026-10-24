/* ssc_bitexact_cos_asm @ 00117400 size 116 */

void ssc_bitexact_cos_asm(int param_1,int param_2,int *param_3,int *param_4)

{
  int iVar1;
  undefined8 uVar2;
  int iVar3;
  
  uVar2 = NEON_srshr(CONCAT44(param_2 * param_2,param_1 * param_1),0xd,4);
  iVar1 = (int)uVar2;
  iVar3 = (int)((ulong)uVar2 >> 0x20);
  uVar2 = NEON_srshr(CONCAT44(iVar3 * -0x272,iVar1 * -0x272),0xf,4);
  uVar2 = NEON_srshr(CONCAT44(iVar3 * ((int)((ulong)uVar2 >> 0x20) + 0x2055),
                              iVar1 * ((int)uVar2 + 0x2055)),0xf,4);
  uVar2 = NEON_srshr(CONCAT44(iVar3 * ((int)((ulong)uVar2 >> 0x20) + -0x1de3),
                              iVar1 * ((int)uVar2 + -0x1de3)),0xf,4);
  *param_3 = ((int)uVar2 - iVar1) + 0x8000;
  *param_4 = ((int)((ulong)uVar2 >> 0x20) - iVar3) + 0x8000;
  return;
}


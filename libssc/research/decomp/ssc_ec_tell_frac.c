/* ssc_ec_tell_frac @ 0010f7c0 size 100 */

int ssc_ec_tell_frac(long param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = (int)LZCOUNT(*(uint *)(param_1 + 0x20));
  uVar1 = *(uint *)(param_1 + 0x20) >> (ulong)(0x10U - iVar4 & 0x1f);
  uVar1 = uVar1 * uVar1;
  uVar2 = (uVar1 >> 0xf) >> (ulong)(uVar1 >> 0x1f);
  uVar2 = uVar2 * uVar2;
  uVar3 = (uVar2 >> 0xf) >> (ulong)(uVar2 >> 0x1f);
  return (iVar4 * 2 + ((int)uVar1 >> 0x1f)) * 4 + *(int *)(param_1 + 0x18) * 8 +
         ((int)uVar2 >> 0x1f & 0xfffffffeU) + ((int)(uVar3 * uVar3) >> 0x1f) + -0x100;
}


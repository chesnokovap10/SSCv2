/* ssc_ec_enc_icdf @ 0010fa00 size 76 */

void ssc_ec_enc_icdf(long param_1,uint param_2,long param_3,uint param_4)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *(uint *)(param_1 + 0x20);
  uVar2 = uVar1 >> (ulong)(param_4 & 0x1f);
  if (0 < (int)param_2) {
    *(uint *)(param_1 + 0x24) =
         (*(int *)(param_1 + 0x24) + uVar1) - uVar2 * *(byte *)(param_3 + (ulong)(param_2 - 1));
    *(uint *)(param_1 + 0x20) =
         ((uint)*(byte *)(param_3 + (ulong)(param_2 - 1)) -
         (uint)*(byte *)(param_3 + (ulong)param_2)) * uVar2;
    FUN_0010f88c();
    return;
  }
  *(uint *)(param_1 + 0x20) = uVar1 - uVar2 * *(byte *)(param_3 + (int)param_2);
  FUN_0010f88c();
  return;
}


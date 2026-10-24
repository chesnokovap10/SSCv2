/* ssc_ec_enc_bit_logp @ 0010f9d8 size 40 */

void ssc_ec_enc_bit_logp(long param_1,int param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *(uint *)(param_1 + 0x20) >> (ulong)(param_3 & 0x1f);
  uVar2 = *(uint *)(param_1 + 0x20) - uVar1;
  if (param_2 != 0) {
    *(uint *)(param_1 + 0x24) = *(int *)(param_1 + 0x24) + uVar2;
    uVar2 = uVar1;
  }
  *(uint *)(param_1 + 0x20) = uVar2;
  FUN_0010f88c();
  return;
}


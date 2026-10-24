/* ssc_ec_encode @ 0010f850 size 60 */

void ssc_ec_encode(long param_1,int param_2,int param_3,uint param_4)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *(uint *)(param_1 + 0x20);
  uVar2 = 0;
  if (param_4 != 0) {
    uVar2 = uVar1 / param_4;
  }
  if (param_2 != 0) {
    *(uint *)(param_1 + 0x20) = uVar2 * (param_3 - param_2);
    *(uint *)(param_1 + 0x24) = uVar1 + uVar2 * (param_2 - param_4) + *(int *)(param_1 + 0x24);
    FUN_0010f88c();
    return;
  }
  *(uint *)(param_1 + 0x20) = uVar1 + uVar2 * (param_3 - param_4);
  FUN_0010f88c();
  return;
}


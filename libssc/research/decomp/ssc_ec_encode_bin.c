/* ssc_ec_encode_bin @ 0010f994 size 68 */

void ssc_ec_encode_bin(long param_1,int param_2,int param_3,uint param_4)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  uVar1 = *(uint *)(param_1 + 0x20);
  iVar2 = -1 << (ulong)(param_4 & 0x1f);
  uVar3 = uVar1 >> (ulong)(param_4 & 0x1f);
  if (param_2 != 0) {
    *(uint *)(param_1 + 0x20) = uVar3 * (param_3 - param_2);
    *(uint *)(param_1 + 0x24) = uVar1 + uVar3 * (iVar2 + param_2) + *(int *)(param_1 + 0x24);
    FUN_0010f88c();
    return;
  }
  *(uint *)(param_1 + 0x20) = uVar1 + uVar3 * (iVar2 + param_3);
  FUN_0010f88c();
  return;
}


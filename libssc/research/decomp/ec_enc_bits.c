/* ec_enc_bits @ 00105940 size 168 */

void ec_enc_bits(long *param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  uVar3 = *(uint *)(param_1 + 2);
  uVar4 = *(uint *)((long)param_1 + 0x14);
  uVar5 = uVar4 + param_3;
  if (0x20 < uVar5) {
    iVar2 = 7 - uVar4;
    if (iVar2 < -7) {
      iVar2 = -8;
    }
    uVar5 = uVar4;
    do {
      if ((uint)(*(int *)((long)param_1 + 0xc) + *(int *)((long)param_1 + 0x1c)) <
          *(uint *)(param_1 + 1)) {
        iVar1 = *(int *)((long)param_1 + 0xc) + 1;
        uVar6 = 0;
        *(int *)((long)param_1 + 0xc) = iVar1;
        *(char *)(*param_1 + (ulong)(*(uint *)(param_1 + 1) - iVar1)) = (char)uVar3;
      }
      else {
        uVar6 = 0xffffffff;
      }
      uVar5 = uVar5 - 8;
      uVar3 = uVar3 >> 8;
      *(uint *)(param_1 + 6) = *(uint *)(param_1 + 6) | uVar6;
    } while (7 < (int)uVar5);
    uVar4 = (uVar4 - 8) - (uVar4 + iVar2 & 0xfffffff8);
    uVar5 = uVar4 + param_3;
  }
  *(uint *)(param_1 + 2) = param_2 << (ulong)(uVar4 & 0x1f) | uVar3;
  *(uint *)((long)param_1 + 0x14) = uVar5;
  *(int *)(param_1 + 3) = (int)param_1[3] + param_3;
  return;
}


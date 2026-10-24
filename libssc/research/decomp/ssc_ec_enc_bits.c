/* ssc_ec_enc_bits @ 0010fba4 size 140 */

void ssc_ec_enc_bits(long *param_1,int param_2,int param_3)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  uVar3 = *(uint *)(param_1 + 2);
  uVar6 = *(uint *)((long)param_1 + 0x14);
  uVar5 = uVar6 + param_3;
  uVar4 = uVar6;
  if (0x20 < uVar5) {
    do {
      if ((uint)(*(int *)((long)param_1 + 0xc) + *(int *)((long)param_1 + 0x1c)) <
          *(uint *)(param_1 + 1)) {
        iVar2 = *(int *)((long)param_1 + 0xc) + 1;
        uVar5 = 0;
        *(int *)((long)param_1 + 0xc) = iVar2;
        *(char *)(*param_1 + (ulong)(*(uint *)(param_1 + 1) - iVar2)) = (char)uVar3;
      }
      else {
        uVar5 = 0xffffffff;
      }
      uVar6 = uVar4 - 8;
      uVar3 = uVar3 >> 8;
      *(uint *)(param_1 + 6) = *(uint *)(param_1 + 6) | uVar5;
      bVar1 = 0xf < (int)uVar4;
      uVar4 = uVar6;
    } while (bVar1);
    uVar5 = param_3 + uVar6;
  }
  *(uint *)(param_1 + 2) = param_2 << (ulong)(uVar6 & 0x1f) | uVar3;
  *(uint *)((long)param_1 + 0x14) = uVar5;
  *(int *)(param_1 + 3) = (int)param_1[3] + param_3;
  return;
}


/* ssc_ec_enc_uint @ 0010fa4c size 344 */

void ssc_ec_enc_uint(long *param_1,uint param_2,uint param_3)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  
  uVar7 = param_3 - 1;
  if (uVar7 < 0x100) {
    uVar5 = *(uint *)(param_1 + 4);
    uVar7 = 0;
    if (param_3 != 0) {
      uVar7 = uVar5 / param_3;
    }
    if (param_2 == 0) {
      uVar7 = (uVar7 - uVar7 * param_3) + uVar5;
    }
    else {
      *(uint *)((long)param_1 + 0x24) =
           uVar5 + uVar7 * (param_2 - param_3) + *(int *)((long)param_1 + 0x24);
    }
    *(uint *)(param_1 + 4) = uVar7;
    FUN_0010f88c(param_1);
    return;
  }
  uVar3 = 0x18 - (int)LZCOUNT(uVar7);
  uVar8 = *(uint *)(param_1 + 4);
  uVar7 = uVar7 >> (ulong)(uVar3 & 0x1f);
  uVar6 = param_2 >> (ulong)(uVar3 & 0x1f);
  uVar5 = uVar7 + 1;
  uVar4 = 0;
  if (uVar5 != 0) {
    uVar4 = uVar8 / uVar5;
  }
  if (uVar6 == 0) {
    uVar4 = uVar8 - uVar7 * uVar4;
  }
  else {
    *(uint *)((long)param_1 + 0x24) =
         uVar8 + uVar4 * (uVar6 - uVar5) + *(int *)((long)param_1 + 0x24);
  }
  *(uint *)(param_1 + 4) = uVar4;
  FUN_0010f88c(param_1);
  uVar5 = *(uint *)(param_1 + 2);
  uVar8 = *(uint *)((long)param_1 + 0x14);
  uVar7 = uVar8 + uVar3;
  uVar6 = uVar8;
  if (0x20 < uVar7) {
    do {
      if ((uint)(*(int *)((long)param_1 + 0xc) + *(int *)((long)param_1 + 0x1c)) <
          *(uint *)(param_1 + 1)) {
        iVar2 = *(int *)((long)param_1 + 0xc) + 1;
        uVar7 = 0;
        *(int *)((long)param_1 + 0xc) = iVar2;
        *(char *)(*param_1 + (ulong)(*(uint *)(param_1 + 1) - iVar2)) = (char)uVar5;
      }
      else {
        uVar7 = 0xffffffff;
      }
      uVar8 = uVar6 - 8;
      uVar5 = uVar5 >> 8;
      *(uint *)(param_1 + 6) = *(uint *)(param_1 + 6) | uVar7;
      bVar1 = 0xf < (int)uVar6;
      uVar6 = uVar8;
    } while (bVar1);
    uVar7 = uVar3 + uVar8;
  }
  *(uint *)(param_1 + 2) =
       (param_2 & (-1 << (ulong)(uVar3 & 0x1f) ^ 0xffffffffU)) << (ulong)(uVar8 & 0x1f) | uVar5;
  *(uint *)((long)param_1 + 0x14) = uVar7;
  *(uint *)(param_1 + 3) = (int)param_1[3] + uVar3;
  return;
}


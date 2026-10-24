/* ec_enc_uint @ 00105814 size 300 */

void ec_enc_uint(long *param_1,uint param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  iVar3 = ec_ilog(param_3 - 1U);
  if (8 < iVar3) {
    uVar2 = iVar3 - 8;
    uVar6 = param_2 >> (ulong)(uVar2 & 0x1f);
    ec_encode(param_1,uVar6,uVar6 + 1,(param_3 - 1U >> (ulong)(uVar2 & 0x1f)) + 1);
    uVar4 = *(uint *)(param_1 + 2);
    uVar5 = *(uint *)((long)param_1 + 0x14);
    uVar6 = uVar5 + uVar2;
    if (0x20 < uVar6) {
      iVar3 = 7 - uVar5;
      if (iVar3 < -7) {
        iVar3 = -8;
      }
      uVar6 = uVar5;
      do {
        if ((uint)(*(int *)((long)param_1 + 0xc) + *(int *)((long)param_1 + 0x1c)) <
            *(uint *)(param_1 + 1)) {
          iVar1 = *(int *)((long)param_1 + 0xc) + 1;
          uVar7 = 0;
          *(int *)((long)param_1 + 0xc) = iVar1;
          *(char *)(*param_1 + (ulong)(*(uint *)(param_1 + 1) - iVar1)) = (char)uVar4;
        }
        else {
          uVar7 = 0xffffffff;
        }
        uVar6 = uVar6 - 8;
        uVar4 = uVar4 >> 8;
        *(uint *)(param_1 + 6) = *(uint *)(param_1 + 6) | uVar7;
      } while (7 < (int)uVar6);
      uVar5 = (uVar5 - 8) - (iVar3 + uVar5 & 0xfffffff8);
      uVar6 = uVar5 + uVar2;
    }
    *(uint *)(param_1 + 2) =
         (param_2 & (-1 << (ulong)(uVar2 & 0x1f) ^ 0xffffffffU)) << (ulong)(uVar5 & 0x1f) | uVar4;
    *(uint *)((long)param_1 + 0x14) = uVar6;
    *(uint *)(param_1 + 3) = (int)param_1[3] + uVar2;
    return;
  }
  ec_encode(param_1,param_2,param_2 + 1,param_3);
  return;
}


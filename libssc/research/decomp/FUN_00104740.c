/* FUN_00104740 @ 00104740 size 1196 */

void FUN_00104740(long param_1,long param_2,uint param_3,uint param_4,int param_5,int param_6,
                 short param_7,uint param_8)

{
  byte *pbVar1;
  long lVar2;
  uint uVar3;
  uint uVar4;
  byte bVar5;
  int iVar6;
  int iVar7;
  long lVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  undefined8 uVar13;
  ulong uVar14;
  ulong uVar15;
  int iVar16;
  long lVar17;
  undefined1 auStack_88 [4];
  short local_84;
  short sStack_80;
  uint local_7c;
  uint uStack_78;
  int local_74;
  uint local_70;
  uint local_6c;
  long local_68;
  
  lVar8 = tpidr_el0;
  local_68 = *(long *)(lVar8 + 0x28);
  lVar17 = *(long *)(param_1 + 8);
  pbVar1 = (byte *)(*(long *)(lVar17 + 0x78) +
                   (long)*(short *)(*(long *)(lVar17 + 0x70) +
                                   (long)(*(int *)(param_1 + 0x10) +
                                         *(int *)(lVar17 + 8) * (param_6 + 1)) * 2));
  bVar5 = *pbVar1;
  local_70 = param_8;
  local_6c = param_4;
  if (((param_6 == -1) || ((int)param_3 < 3)) || ((int)param_4 <= (int)(pbVar1[bVar5] + 0xc))) {
    uVar3 = bVar5 + 1 >> 1;
    iVar12 = param_4 - 1;
    uVar4 = (uint)bVar5;
    uVar10 = uVar3;
    if (iVar12 <= (int)(uint)pbVar1[uVar3]) {
      uVar10 = 0;
      uVar4 = uVar3;
    }
    uVar3 = uVar10 + uVar4 + 1 >> 1;
    if (iVar12 <= (int)(uint)pbVar1[uVar3]) {
      uVar4 = uVar3;
      uVar3 = uVar10;
    }
    uVar10 = (int)(uVar3 + uVar4 + 1) >> 1;
    if (iVar12 <= (int)(uint)pbVar1[(int)uVar10]) {
      uVar4 = uVar10;
      uVar10 = uVar3;
    }
    uVar3 = (int)(uVar10 + uVar4 + 1) >> 1;
    if (iVar12 <= (int)(uint)pbVar1[(int)uVar3]) {
      uVar4 = uVar3;
      uVar3 = uVar10;
    }
    uVar10 = (int)(uVar3 + uVar4 + 1) >> 1;
    if (iVar12 <= (int)(uint)pbVar1[(int)uVar10]) {
      uVar4 = uVar10;
      uVar10 = uVar3;
    }
    uVar3 = (int)(uVar10 + uVar4 + 1) >> 1;
    if (iVar12 <= (int)(uint)pbVar1[(int)uVar3]) {
      uVar4 = uVar3;
      uVar3 = uVar10;
    }
    if (uVar3 == 0) {
      uVar10 = 0xffffffff;
    }
    else {
      uVar10 = (uint)pbVar1[(int)uVar3];
    }
    if ((int)(iVar12 - uVar10) <= (int)((uint)pbVar1[(int)uVar4] - iVar12)) {
      uVar4 = uVar3;
    }
    uVar14 = (ulong)uVar4;
    if (uVar4 == 0) {
      iVar12 = 0;
      iVar16 = *(int *)(param_1 + 0x28);
      *(int *)(param_1 + 0x28) = iVar16;
    }
    else {
      iVar12 = pbVar1[(int)uVar4] + 1;
      iVar16 = *(int *)(param_1 + 0x28) - iVar12;
      *(int *)(param_1 + 0x28) = iVar16;
    }
    if ((iVar16 < 0) && (uVar4 != 0)) {
      uVar15 = (ulong)(int)uVar4;
      do {
        uVar15 = uVar15 - 1;
        uVar14 = uVar15 & 0xffffffff;
        iVar16 = iVar12 + iVar16;
        *(int *)(param_1 + 0x28) = iVar16;
        if (uVar15 == 0) {
          *(int *)(param_1 + 0x28) = iVar16;
          goto LAB_001049a4;
        }
        iVar12 = pbVar1[uVar15] + 1;
        iVar16 = iVar16 - iVar12;
        *(int *)(param_1 + 0x28) = iVar16;
      } while (iVar16 < 0);
    }
    uVar10 = (uint)uVar14;
    if (uVar10 == 0) {
LAB_001049a4:
      uVar14 = 0;
    }
    else {
      if (7 < (int)uVar10) {
        uVar14 = (ulong)((uVar10 & 7 | 8) << (ulong)((uVar10 >> 3) - 1 & 0x1f));
      }
      uVar14 = alg_quant(param_2,param_3,uVar14,*(undefined4 *)(param_1 + 0x18),param_5);
    }
  }
  else {
    param_3 = param_3 >> 1;
    lVar2 = param_2 + (ulong)(param_3 << 1);
    iVar12 = param_6 + -1;
    if (param_5 == 1) {
      local_70 = param_8 & 1 | param_8 << 1;
      uVar13 = *(undefined8 *)(lVar17 + 0x38);
      uVar10 = 1;
      iVar16 = 1;
    }
    else {
      uVar13 = *(undefined8 *)(lVar17 + 0x38);
      uVar10 = param_5 + 1 >> 1;
      iVar16 = param_5;
    }
    FUN_00104bec(uVar13,*(int *)(param_1 + 0x10),*(undefined8 *)(param_1 + 0x20),auStack_88,param_2,
                 lVar2,param_3,&local_6c,uVar10,iVar16,iVar12,&local_70);
    uVar4 = local_70;
    if ((1 < param_5) && ((uStack_78 & 0x3fff) != 0)) {
      if ((int)uStack_78 < 0x2001) {
        local_7c = local_7c + ((int)(param_3 << 3) >> (6U - param_6 & 0x1f));
        local_7c = local_7c & (int)local_7c >> 0x1f;
      }
      else {
        local_7c = local_7c - ((int)local_7c >> (5U - param_6 & 0x1f));
      }
    }
    iVar7 = (int)param_7;
    iVar16 = local_6c - local_7c;
    if (iVar16 < 0) {
      iVar16 = iVar16 + 1;
    }
    uVar3 = local_6c;
    if (iVar16 >> 1 <= (int)local_6c) {
      uVar3 = iVar16 >> 1;
    }
    uVar3 = uVar3 & ((int)uVar3 >> 0x1f ^ 0xffffffffU);
    iVar16 = local_6c - uVar3;
    iVar6 = *(int *)(param_1 + 0x28) - local_74;
    *(int *)(param_1 + 0x28) = iVar6;
    if ((int)uVar3 < iVar16) {
      iVar9 = FUN_00104740(param_1,lVar2,param_3,iVar16,uVar10,iVar12,
                           sStack_80 * iVar7 + 0x4000U >> 0xf,(int)local_70 >> (uVar10 & 0x1f));
      iVar16 = (*(int *)(param_1 + 0x28) - iVar6) + iVar16;
      iVar6 = iVar16 + -0x18;
      if ((iVar6 == 0 || iVar16 < 0x18) || uStack_78 == 0x4000) {
        iVar6 = 0;
      }
      uVar10 = FUN_00104740(param_1,param_2,param_3,iVar6 + uVar3,uVar10,iVar12,
                            local_84 * iVar7 + 0x4000U >> 0xf,uVar4);
      uVar14 = (ulong)(uVar10 | iVar9 << (ulong)(param_5 >> 1 & 0x1f));
    }
    else {
      uVar11 = FUN_00104740(param_1,param_2,param_3,uVar3,uVar10,iVar12,
                            local_84 * iVar7 + 0x4000U >> 0xf,local_70);
      iVar6 = (*(int *)(param_1 + 0x28) - iVar6) + uVar3;
      iVar9 = iVar6 + -0x18;
      if ((iVar9 == 0 || iVar6 < 0x18) || uStack_78 == 0) {
        iVar9 = 0;
      }
      iVar12 = FUN_00104740(param_1,lVar2,param_3,iVar9 + iVar16,uVar10,iVar12,
                            sStack_80 * iVar7 + 0x4000U >> 0xf,(int)uVar4 >> (uVar10 & 0x1f));
      uVar14 = (ulong)(iVar12 << (ulong)(param_5 >> 1 & 0x1f) | uVar11);
    }
  }
  if (*(long *)(lVar8 + 0x28) == local_68) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar14);
}


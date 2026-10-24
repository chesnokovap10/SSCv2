/* ssc_mdct_forward @ 0011176c size 860 */

void ssc_mdct_forward(int *param_1,long param_2,undefined4 *param_3,uint param_4,uint param_5,
                     uint param_6)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  long lVar5;
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  int iVar10;
  int *piVar11;
  int *piVar12;
  undefined *puVar13;
  long lVar14;
  undefined4 *puVar15;
  long lVar16;
  int *piVar17;
  undefined8 *puVar18;
  ulong uVar19;
  long lVar20;
  int *piVar21;
  int iVar22;
  int *piVar23;
  int iVar24;
  long lVar25;
  int iVar27;
  int iVar28;
  undefined8 uVar26;
  int iVar29;
  undefined8 uVar30;
  
  uVar2 = *param_1 >> (param_5 & 0x1f);
  lVar16 = param_2 + (long)((int)uVar2 >> 1) * 4;
  iVar3 = 0xee4bb;
  iVar10 = 0x7fffff22;
  if (param_5 != 0) {
    iVar3 = 0x7725c6;
    iVar10 = 0x7fffc88c;
  }
  iVar28 = (int)(param_4 + 3) >> 2;
  iVar24 = (int)uVar2 >> 2;
  lVar20 = lVar16 + -4;
  piVar12 = &_pre_shared;
  puVar15 = &DAT_00103d80;
  if ((int)param_4 < 1) {
    iVar22 = 0;
    uVar19 = -(ulong)((uint)((int)param_4 >> 1) >> 0x1f) & 0xfffffffc00000000 |
             (ulong)(uint)((int)param_4 >> 1) << 2;
    piVar17 = (int *)(param_2 + uVar19);
    piVar21 = (int *)(lVar20 + uVar19);
  }
  else {
    iVar22 = iVar28;
    if (iVar28 < 2) {
      iVar22 = 1;
    }
    lVar5 = (long)((ulong)param_4 << 0x20) >> 0x21;
    puVar13 = &DAT_00103d7c;
    lVar14 = param_2 + -4;
    piVar17 = &_pre_shared;
    iVar27 = iVar22;
    do {
      lVar25 = lVar5 * 4;
      iVar27 = iVar27 + -1;
      piVar12 = (int *)(lVar20 + lVar25);
      lVar20 = lVar20 + -8;
      iVar4 = puVar15[lVar5];
      puVar15 = puVar15 + 2;
      piVar21 = (int *)(lVar16 + lVar25);
      lVar16 = lVar16 + 8;
      iVar29 = *(int *)(puVar13 + lVar25);
      puVar13 = puVar13 + -8;
      *piVar17 = (int)((long)iVar4 * (long)*piVar12 + (long)iVar29 * (long)*piVar21 + 0x40000000U >>
                      0x1f);
      piVar21 = (int *)(lVar14 + lVar25);
      lVar14 = lVar14 + -8;
      piVar11 = (int *)(param_2 + lVar25);
      param_2 = param_2 + 8;
      piVar12 = piVar17 + 2;
      piVar17[1] = (int)(((long)*piVar11 * (long)iVar4 - (long)*piVar21 * (long)iVar29) +
                         0x40000000U >> 0x1f);
      piVar17 = piVar12;
    } while (iVar27 != 0);
    piVar17 = (int *)(param_2 + lVar25);
    piVar21 = (int *)(lVar20 + lVar25);
  }
  lVar16 = (long)((ulong)uVar2 << 0x20) >> 0x21;
  iVar27 = iVar22;
  for (; iVar22 < iVar24 - iVar28; iVar22 = iVar22 + 1) {
    *piVar12 = *piVar21;
    piVar12[1] = *piVar17;
    piVar17 = piVar17 + 2;
    piVar12 = piVar12 + 2;
    piVar21 = piVar21 + -2;
    iVar27 = iVar24 - iVar28;
  }
  if (iVar27 < iVar24) {
    iVar27 = iVar24 - iVar27;
    piVar11 = &DAT_00103d80;
    piVar23 = (int *)(&DAT_00103d7c + (long)(int)param_4 * 4);
    do {
      iVar27 = iVar27 + -1;
      iVar28 = *piVar11;
      iVar22 = *piVar23;
      *piVar12 = (int)(((long)iVar22 * (long)*piVar21 - (long)iVar28 * (long)piVar17[-lVar16]) +
                       0x40000000U >> 0x1f);
      piVar1 = piVar21 + lVar16;
      piVar21 = piVar21 + -2;
      iVar4 = *piVar17;
      piVar17 = piVar17 + 2;
      piVar12[1] = (int)((long)*piVar1 * (long)iVar28 + (long)iVar4 * (long)iVar22 + 0x40000000U >>
                        0x1f);
      piVar12 = piVar12 + 2;
      piVar11 = piVar11 + 2;
      piVar23 = piVar23 + -2;
    } while (iVar27 != 0);
  }
  iVar28 = iVar24 << (ulong)(param_5 & 0x1f);
  lVar16 = (long)(1 << (ulong)(param_5 & 0x1f));
  if (3 < (int)uVar2) {
    piVar12 = *(int **)(param_1 + 6);
    iVar22 = iVar24;
    if (iVar24 < 2) {
      iVar22 = 1;
    }
    piVar17 = piVar12 + iVar28;
    puVar18 = (undefined8 *)&_pre_shared;
    do {
      uVar26 = *puVar18;
      iVar22 = iVar22 + -1;
      iVar27 = *piVar12;
      piVar12 = piVar12 + lVar16;
      iVar4 = *piVar17;
      piVar17 = piVar17 + -lVar16;
      uVar30 = NEON_rev64(uVar26,4);
      iVar29 = -(int)((ulong)uVar26 >> 0x20);
      auVar9._8_8_ = (long)(int)((ulong)uVar30 >> 0x20) * (long)iVar4 + (long)iVar29 * (long)iVar27;
      auVar9._0_8_ = (long)(int)uVar30 * (long)iVar4 + (long)(int)uVar26 * (long)iVar27;
      uVar26 = NEON_rshrn(CONCAT44(iVar29,(int)uVar26),auVar9,0x1f,8);
      iVar27 = (int)((ulong)uVar26 >> 0x20);
      uVar30 = NEON_rev64(uVar26,4);
      auVar7._8_8_ = (long)(int)((ulong)uVar30 >> 0x20) * (long)iVar3 + (long)iVar27 * (long)iVar10;
      auVar7._0_8_ = (long)(int)uVar30 * (long)iVar3 + (long)-(int)uVar26 * (long)iVar10;
      uVar26 = NEON_rshrn(CONCAT44(iVar27,-(int)uVar26),auVar7,0x1f,8);
      *puVar18 = uVar26;
      puVar18 = puVar18 + 1;
    } while (iVar22 != 0);
  }
  ssc_fft(*(undefined8 *)(param_1 + (long)((int)param_5 >> 1) * 2 + 2),&_pre_shared,&DAT_001212ac);
  piVar17 = *(int **)(param_1 + 6);
  uVar19 = -(ulong)((param_6 & 0x7fffffff) >> 0x1e) & 0xfffffffc00000000 |
           (ulong)(param_6 << 1) << 2;
  piVar12 = piVar17 + iVar28;
  puVar15 = param_3 + (int)((((int)uVar2 >> 1) + -1) * param_6);
  puVar18 = &DAT_001212ac;
  do {
    uVar30 = *puVar18;
    iVar28 = *piVar17;
    piVar17 = piVar17 + lVar16;
    iVar22 = *piVar12;
    piVar12 = piVar12 + -lVar16;
    uVar26 = NEON_rev64(uVar30,4);
    iVar27 = -(int)((ulong)uVar30 >> 0x20);
    iVar24 = iVar24 + -1;
    auVar8._8_8_ = (long)(int)((ulong)uVar26 >> 0x20) * (long)iVar22 + (long)iVar27 * (long)iVar28;
    auVar8._0_8_ = (long)(int)uVar26 * (long)iVar22 + (long)(int)uVar30 * (long)iVar28;
    uVar30 = NEON_rshrn(CONCAT44(iVar27,(int)uVar30),auVar8,0x1f,8);
    iVar28 = (int)((ulong)uVar30 >> 0x20);
    uVar26 = NEON_rev64(CONCAT44(-iVar28,(int)uVar30),4);
    auVar6._8_8_ = (long)(int)((ulong)uVar26 >> 0x20) * (long)iVar3 + (long)iVar28 * (long)iVar10;
    auVar6._0_8_ = (long)(int)uVar26 * (long)iVar3 + (long)(int)uVar30 * (long)iVar10;
    uVar26 = NEON_rshrn(uVar30,auVar6,0x1f,8);
    *param_3 = (int)uVar26;
    param_3 = (undefined4 *)((long)param_3 + uVar19);
    *puVar15 = (int)((ulong)uVar26 >> 0x20);
    puVar15 = (undefined4 *)((long)puVar15 - uVar19);
    puVar18 = puVar18 + 1;
  } while (iVar24 != 0);
  return;
}


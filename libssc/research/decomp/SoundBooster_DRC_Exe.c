/* SoundBooster_DRC_Exe @ 0010b5dc size 712 */

void SoundBooster_DRC_Exe(uint *param_1,int param_2)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  uint *puVar5;
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined8 uVar8;
  ulong uVar9;
  ulong uVar10;
  long lVar11;
  long lVar12;
  long lVar13;
  int iVar14;
  uint *puVar15;
  long lVar16;
  uint *puVar17;
  long lVar18;
  ulong uVar19;
  ulong uVar20;
  uint uVar21;
  undefined1 auVar22 [16];
  long lVar23;
  uint uVar24;
  long lVar25;
  long lVar26;
  undefined1 auVar27 [16];
  int iVar28;
  int iVar29;
  int iVar30;
  int iVar31;
  int iVar32;
  int iVar33;
  int iVar34;
  int iVar35;
  int iVar36;
  int iVar37;
  int iVar38;
  int iVar39;
  int iVar40;
  int iVar41;
  int iVar42;
  int iVar43;
  
  iVar14 = DRC_ChNum * param_2;
  iVar28 = -1;
  if (-1 < -(DRC_ChNum * param_2)) {
    iVar28 = -iVar14;
  }
  uVar9 = (ulong)(uint)(iVar28 + iVar14) + 1;
  if (uVar9 < 8) {
    uVar24 = 0;
    puVar15 = param_1;
    uVar21 = 0;
  }
  else {
    uVar2 = iVar28 + iVar14 + 1U & 7;
    lVar13 = uVar9 - uVar2;
    puVar17 = param_1 + 4;
    auVar22 = ZEXT816(0);
    auVar27 = ZEXT816(0);
    iVar28 = 0;
    iVar29 = 0;
    iVar30 = 0;
    iVar31 = 0;
    iVar14 = iVar14 - (int)lVar13;
    puVar15 = param_1 + lVar13;
    iVar32 = 0;
    iVar33 = 0;
    iVar34 = 0;
    iVar35 = 0;
    do {
      puVar1 = puVar17 + -4;
      puVar4 = puVar17 + -2;
      puVar5 = puVar17 + 2;
      uVar8 = *(undefined8 *)puVar17;
      lVar13 = lVar13 + -8;
      puVar17 = puVar17 + 8;
      iVar36 = MP_INT_ABS((int)*(undefined8 *)puVar1);
      iVar37 = MP_INT_ABS((int)((ulong)*(undefined8 *)puVar1 >> 0x20));
      iVar38 = MP_INT_ABS((int)*(undefined8 *)puVar4);
      iVar39 = MP_INT_ABS((int)((ulong)*(undefined8 *)puVar4 >> 0x20));
      iVar40 = MP_INT_ABS((int)uVar8);
      iVar41 = MP_INT_ABS((int)((ulong)uVar8 >> 0x20));
      iVar42 = MP_INT_ABS((int)*(undefined8 *)puVar5);
      iVar43 = MP_INT_ABS((int)((ulong)*(undefined8 *)puVar5 >> 0x20));
      auVar6._4_4_ = iVar37;
      auVar6._0_4_ = iVar36;
      auVar6._8_4_ = iVar38;
      auVar6._12_4_ = iVar39;
      auVar22 = NEON_smax(auVar22,auVar6,4);
      auVar7._4_4_ = iVar41;
      auVar7._0_4_ = iVar40;
      auVar7._8_4_ = iVar42;
      auVar7._12_4_ = iVar43;
      auVar27 = NEON_smax(auVar27,auVar7,4);
      iVar28 = iVar28 + (uint)(drc_struct < iVar36);
      iVar29 = iVar29 + (uint)(drc_struct < iVar37);
      iVar30 = iVar30 + (uint)(drc_struct < iVar38);
      iVar31 = iVar31 + (uint)(drc_struct < iVar39);
      iVar32 = iVar32 + (uint)(drc_struct < iVar40);
      iVar33 = iVar33 + (uint)(drc_struct < iVar41);
      iVar34 = iVar34 + (uint)(drc_struct < iVar42);
      iVar35 = iVar35 + (uint)(drc_struct < iVar43);
    } while (lVar13 != 0);
    auVar22 = NEON_smax(auVar22,auVar27,4);
    uVar24 = iVar32 + iVar28 + iVar33 + iVar29 + iVar34 + iVar30 + iVar35 + iVar31;
    uVar21 = NEON_smaxv(auVar22,4);
    if (uVar2 == 0) goto LAB_0010b6d8;
  }
  do {
    uVar3 = *puVar15;
    iVar14 = iVar14 + -1;
    uVar2 = -uVar3;
    if (-1 < (int)uVar3) {
      uVar2 = uVar3;
    }
    uVar3 = uVar2;
    if ((int)uVar2 <= (int)uVar21) {
      uVar3 = uVar21;
    }
    if (drc_struct < (int)uVar2) {
      uVar24 = uVar24 + 1;
    }
    puVar15 = puVar15 + 1;
    uVar21 = uVar3;
  } while (0 < iVar14);
LAB_0010b6d8:
  iVar28 = 0x400000;
  if (0x18 < uVar24) {
    iVar28 = 0;
    if ((ulong)uVar21 != 0) {
      iVar28 = (int)(((long)drc_struct << 0x1f) / (long)(ulong)uVar21);
    }
    iVar28 = iVar28 >> 9;
  }
  iVar14 = DAT_001295d8;
  if (iVar28 <= DAT_001295dc) {
    iVar14 = DAT_001295d4;
  }
  lVar13 = (long)(int)DAT_001295e0;
  iVar28 = (int)((ulong)((long)iVar14 * (long)DAT_001295dc +
                        (long)(0x400000 - iVar14) * (long)iVar28) >> 0x16);
  if (iVar28 <= DAT_001295e0._4_4_) {
    DAT_001295e0._4_4_ = iVar28;
  }
  iVar14 = 0;
  if (param_2 != 0) {
    iVar14 = (DAT_001295e0._4_4_ - (int)DAT_001295e0) / param_2;
  }
  DAT_001295dc = iVar28;
  if (((int)DAT_001295e0 != 0x400000) || (iVar14 != 0)) {
    iVar29 = -1;
    if (-1 < -param_2) {
      iVar29 = -param_2;
    }
    uVar9 = (ulong)(uint)(iVar29 + param_2) + 1;
    lVar11 = (long)iVar14;
    if (3 < uVar9) {
      uVar2 = iVar29 + param_2 + 1U & 3;
      lVar18 = lVar11 * 4;
      lVar16 = uVar9 - uVar2;
      lVar23 = lVar13 + lVar11;
      lVar12 = lVar13 + lVar16 * lVar11;
      puVar17 = param_1 + lVar16 * 2;
      param_2 = param_2 - (int)lVar16;
      lVar25 = lVar13 + lVar11 * 2;
      lVar26 = lVar13 + lVar11 * 3;
      do {
        lVar16 = lVar16 + -4;
        uVar10 = lVar13 * (int)*param_1;
        uVar9 = lVar23 * (int)param_1[2];
        uVar20 = lVar13 * (int)param_1[1];
        uVar19 = lVar23 * (int)param_1[3];
        lVar13 = lVar13 + lVar18;
        lVar23 = lVar23 + lVar18;
        *param_1 = (uint)(uVar10 >> 0x16);
        param_1[1] = (uint)(uVar20 >> 0x16);
        param_1[2] = (uint)(uVar9 >> 0x16);
        param_1[3] = (uint)(uVar19 >> 0x16);
        param_1[4] = (uint)((ulong)(lVar25 * (int)param_1[4]) >> 0x16);
        param_1[5] = (uint)((ulong)(lVar25 * (int)param_1[5]) >> 0x16);
        param_1[6] = (uint)((ulong)(lVar26 * (int)param_1[6]) >> 0x16);
        param_1[7] = (uint)((ulong)(lVar26 * (int)param_1[7]) >> 0x16);
        param_1 = param_1 + 8;
        lVar25 = lVar25 + lVar18;
        lVar26 = lVar26 + lVar18;
      } while (lVar16 != 0);
      lVar13 = lVar12;
      param_1 = puVar17;
      if (uVar2 == 0) {
        DAT_001295e0._0_4_ = DAT_001295e0._4_4_;
        DAT_001295e0._4_4_ = iVar28;
        return;
      }
    }
    do {
      param_2 = param_2 + -1;
      *(ulong *)param_1 =
           CONCAT44((int)((ulong)(lVar13 * (int)((ulong)*(undefined8 *)param_1 >> 0x20)) >> 0x16),
                    (int)((ulong)(lVar13 * (int)*(undefined8 *)param_1) >> 0x16));
      lVar13 = lVar13 + lVar11;
      param_1 = param_1 + 2;
    } while (0 < param_2);
  }
  DAT_001295e0._0_4_ = DAT_001295e0._4_4_;
  DAT_001295e0._4_4_ = iVar28;
  return;
}


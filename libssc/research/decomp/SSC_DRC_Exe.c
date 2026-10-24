/* SSC_DRC_Exe @ 001070c4 size 696 */

void SSC_DRC_Exe(uint *param_1,int param_2)

{
  uint *puVar1;
  uint uVar2;
  uint *puVar3;
  uint *puVar4;
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined8 uVar7;
  int *piVar8;
  int iVar9;
  uint *puVar10;
  long lVar11;
  long lVar12;
  uint uVar13;
  uint *puVar14;
  ulong uVar15;
  ulong uVar16;
  ulong uVar17;
  long lVar18;
  uint uVar19;
  long lVar20;
  undefined1 auVar21 [16];
  long lVar22;
  uint uVar23;
  long lVar24;
  undefined1 auVar25 [16];
  long lVar26;
  int iVar27;
  char cVar28;
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
  
  iVar9 = DRC_ChNum * param_2;
  iVar27 = iVar9;
  if (0 < iVar9) {
    iVar27 = 1;
  }
  if ((uint)(iVar9 - iVar27) < 7) {
    uVar19 = 0;
    uVar23 = 0;
    puVar10 = param_1;
  }
  else {
    uVar16 = (ulong)(uint)(iVar9 - iVar27) + 1;
    puVar14 = param_1 + 4;
    uVar15 = uVar16 & 0x1fffffff8;
    auVar21 = ZEXT816(0);
    iVar9 = iVar9 - (int)uVar15;
    auVar25 = ZEXT816(0);
    puVar10 = param_1 + uVar15;
    iVar27 = 0;
    iVar29 = 0;
    iVar30 = 0;
    iVar31 = 0;
    iVar32 = 0;
    iVar33 = 0;
    iVar34 = 0;
    iVar35 = 0;
    uVar17 = uVar15;
    do {
      puVar1 = puVar14 + -4;
      puVar3 = puVar14 + -2;
      puVar4 = puVar14 + 2;
      uVar7 = *(undefined8 *)puVar14;
      puVar14 = puVar14 + 8;
      uVar17 = uVar17 - 8;
      iVar36 = MP_INT_ABS((int)*(undefined8 *)puVar1);
      iVar37 = MP_INT_ABS((int)((ulong)*(undefined8 *)puVar1 >> 0x20));
      iVar38 = MP_INT_ABS((int)*(undefined8 *)puVar3);
      iVar39 = MP_INT_ABS((int)((ulong)*(undefined8 *)puVar3 >> 0x20));
      iVar40 = MP_INT_ABS((int)uVar7);
      iVar41 = MP_INT_ABS((int)((ulong)uVar7 >> 0x20));
      iVar42 = MP_INT_ABS((int)*(undefined8 *)puVar4);
      iVar43 = MP_INT_ABS((int)((ulong)*(undefined8 *)puVar4 >> 0x20));
      auVar5._4_4_ = iVar37;
      auVar5._0_4_ = iVar36;
      auVar5._8_4_ = iVar38;
      auVar5._12_4_ = iVar39;
      auVar21 = NEON_smax(auVar21,auVar5,4);
      auVar6._4_4_ = iVar41;
      auVar6._0_4_ = iVar40;
      auVar6._8_4_ = iVar42;
      auVar6._12_4_ = iVar43;
      auVar25 = NEON_smax(auVar25,auVar6,4);
      iVar27 = iVar27 + (uint)(drc_struct < iVar36);
      iVar29 = iVar29 + (uint)(drc_struct < iVar37);
      iVar30 = iVar30 + (uint)(drc_struct < iVar38);
      iVar31 = iVar31 + (uint)(drc_struct < iVar39);
      iVar32 = iVar32 + (uint)(drc_struct < iVar40);
      iVar33 = iVar33 + (uint)(drc_struct < iVar41);
      iVar34 = iVar34 + (uint)(drc_struct < iVar42);
      iVar35 = iVar35 + (uint)(drc_struct < iVar43);
    } while (uVar17 != 0);
    auVar21 = NEON_smax(auVar21,auVar25,4);
    uVar23 = iVar32 + iVar27 + iVar33 + iVar29 + iVar34 + iVar30 + iVar35 + iVar31;
    uVar19 = NEON_smaxv(auVar21,4);
    if (uVar16 == uVar15) goto LAB_001071b4;
  }
  iVar9 = iVar9 + 1;
  uVar13 = uVar19;
  do {
    uVar19 = *puVar10;
    iVar9 = iVar9 + -1;
    uVar2 = -uVar19;
    if (-1 < (int)uVar19) {
      uVar2 = uVar19;
    }
    uVar19 = uVar2;
    if ((int)uVar2 <= (int)uVar13) {
      uVar19 = uVar13;
    }
    if (drc_struct < (int)uVar2) {
      uVar23 = uVar23 + 1;
    }
    puVar10 = puVar10 + 1;
    uVar13 = uVar19;
  } while (1 < iVar9);
LAB_001071b4:
  iVar9 = 0x400000;
  if (0x18 < uVar23) {
    if (uVar19 == 0) {
      iVar9 = 0x2000;
    }
    else {
      iVar9 = 0;
      if ((ulong)uVar19 != 0) {
        iVar9 = (int)(((long)drc_struct << 0x1f) / (long)(ulong)uVar19);
      }
      iVar9 = iVar9 >> 9;
    }
  }
  piVar8 = &DAT_00120508;
  if (iVar9 <= DAT_0012050c) {
    piVar8 = &DAT_00120504;
  }
  lVar12 = (long)DAT_00120510;
  iVar9 = (int)((ulong)((long)*piVar8 * (long)DAT_0012050c +
                       (long)(0x400000 - *piVar8) * (long)iVar9) >> 0x16);
  if (iVar9 <= DAT_00120514) {
    DAT_00120514 = iVar9;
  }
  iVar27 = 0;
  if (param_2 != 0) {
    iVar27 = (DAT_00120514 - DAT_00120510) / param_2;
  }
  DAT_0012050c = iVar9;
  if ((DAT_00120510 != 0x400000) || (iVar27 != 0)) {
    lVar11 = (long)iVar27;
    iVar29 = param_2;
    if (0 < param_2) {
      iVar29 = 1;
    }
    if (2 < (uint)(param_2 - iVar29)) {
      lVar18 = lVar11 * 4;
      uVar16 = (ulong)(uint)(param_2 - iVar29) + 1;
      uVar15 = uVar16 & 0x1fffffffc;
      param_2 = param_2 - (int)uVar15;
      cVar28 = (char)(iVar27 >> 0x1f);
      puVar14 = param_1 + uVar15 * 2;
      uVar17 = uVar15;
      lVar24 = lVar12;
      lVar26 = lVar12 + CONCAT17(cVar28,CONCAT16(cVar28,CONCAT15(cVar28,(int5)iVar27)));
      lVar20 = lVar12 + lVar11 * 2;
      lVar22 = lVar12 + lVar11 * 3;
      do {
        uVar17 = uVar17 - 4;
        *param_1 = (uint)((ulong)(lVar24 * (int)*param_1) >> 0x16);
        param_1[1] = (uint)((ulong)(lVar24 * (int)param_1[1]) >> 0x16);
        param_1[2] = (uint)((ulong)(lVar26 * (int)param_1[2]) >> 0x16);
        param_1[3] = (uint)((ulong)(lVar26 * (int)param_1[3]) >> 0x16);
        param_1[4] = (uint)((ulong)(lVar20 * (int)param_1[4]) >> 0x16);
        param_1[5] = (uint)((ulong)(lVar20 * (int)param_1[5]) >> 0x16);
        param_1[6] = (uint)((ulong)(lVar22 * (int)param_1[6]) >> 0x16);
        param_1[7] = (uint)((ulong)(lVar22 * (int)param_1[7]) >> 0x16);
        param_1 = param_1 + 8;
        lVar24 = lVar24 + lVar18;
        lVar26 = lVar26 + lVar18;
        lVar20 = lVar20 + lVar18;
        lVar22 = lVar22 + lVar18;
      } while (uVar17 != 0);
      lVar12 = lVar12 + uVar15 * lVar11;
      param_1 = puVar14;
      if (uVar16 == uVar15) {
        DAT_00120510 = DAT_00120514;
        DAT_00120514 = iVar9;
        return;
      }
    }
    param_2 = param_2 + 1;
    do {
      param_2 = param_2 + -1;
      uVar16 = lVar12 * (int)*param_1;
      uVar17 = lVar12 * (int)param_1[1];
      lVar12 = lVar12 + lVar11;
      *param_1 = (uint)(uVar16 >> 0x16);
      param_1[1] = (uint)(uVar17 >> 0x16);
      param_1 = param_1 + 2;
    } while (1 < param_2);
  }
  DAT_00120510 = DAT_00120514;
  DAT_00120514 = iVar9;
  return;
}


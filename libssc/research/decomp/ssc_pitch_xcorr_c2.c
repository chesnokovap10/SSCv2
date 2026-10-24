/* ssc_pitch_xcorr_c2 @ 001130dc size 296 */

int ssc_pitch_xcorr_c2(undefined8 *param_1,long param_2,long param_3,int param_4,int param_5)

{
  undefined8 *puVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  int iVar5;
  ulong uVar6;
  undefined1 (*pauVar7) [16];
  ulong uVar8;
  undefined1 (*pauVar9) [16];
  undefined8 *puVar10;
  short sVar11;
  short sVar12;
  short sVar13;
  short sVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  int iVar24;
  int iVar25;
  int iVar26;
  int iVar27;
  int iVar28;
  int iVar29;
  int iVar30;
  short sVar31;
  short sVar32;
  short sVar33;
  short sVar34;
  undefined8 uVar35;
  undefined8 uVar36;
  short sVar37;
  short sVar39;
  short sVar40;
  undefined8 uVar38;
  short sVar41;
  undefined8 uVar42;
  undefined1 auVar43 [16];
  undefined1 auVar44 [16];
  undefined1 auVar45 [16];
  
  if (param_5 < 4) {
    return 1;
  }
  iVar2 = param_4 >> 3;
  uVar6 = 0;
  if (iVar2 < 2) {
    iVar2 = 1;
  }
  pauVar7 = (undefined1 (*) [16])(param_2 + 0x10);
  iVar5 = 1;
  do {
    iVar15 = 0;
    iVar16 = 0;
    iVar19 = 0;
    iVar20 = 0;
    iVar27 = 0;
    iVar28 = 0;
    iVar23 = 0;
    iVar24 = 0;
    iVar25 = iVar23;
    iVar26 = iVar24;
    iVar29 = iVar27;
    iVar30 = iVar28;
    iVar21 = iVar19;
    iVar22 = iVar20;
    iVar17 = iVar15;
    iVar18 = iVar16;
    if (7 < param_4) {
      puVar1 = (undefined8 *)(param_2 + uVar6 * 2);
      iVar23 = 0;
      iVar24 = 0;
      iVar25 = 0;
      iVar26 = 0;
      iVar27 = 0;
      iVar28 = 0;
      iVar29 = 0;
      iVar30 = 0;
      iVar19 = 0;
      iVar20 = 0;
      iVar21 = 0;
      iVar22 = 0;
      uVar35 = *puVar1;
      sVar31 = (short)uVar35;
      sVar32 = (short)((ulong)uVar35 >> 0x10);
      sVar33 = (short)((ulong)uVar35 >> 0x20);
      sVar34 = (short)((ulong)uVar35 >> 0x30);
      iVar15 = 0;
      iVar16 = 0;
      iVar17 = 0;
      iVar18 = 0;
      pauVar9 = pauVar7;
      puVar10 = param_1;
      uVar35 = puVar1[1];
      iVar3 = iVar2;
      do {
        puVar4 = *pauVar9;
        uVar36 = *(undefined8 *)*pauVar9;
        uVar42 = puVar10[1];
        uVar38 = *puVar10;
        iVar3 = iVar3 + -1;
        auVar43._2_2_ = sVar32;
        auVar43._0_2_ = sVar31;
        auVar43._4_2_ = sVar33;
        auVar43._6_2_ = sVar34;
        auVar43._8_8_ = uVar35;
        auVar43 = NEON_ext(auVar43,*pauVar9,2,1);
        auVar44._2_2_ = sVar32;
        auVar44._0_2_ = sVar31;
        auVar44._4_2_ = sVar33;
        auVar44._6_2_ = sVar34;
        auVar44._8_8_ = uVar35;
        auVar44 = NEON_ext(auVar44,*pauVar9,4,1);
        auVar45._2_2_ = sVar32;
        auVar45._0_2_ = sVar31;
        auVar45._4_2_ = sVar33;
        auVar45._6_2_ = sVar34;
        auVar45._8_8_ = uVar35;
        auVar45 = NEON_ext(auVar45,*pauVar9,6,1);
        sVar37 = (short)uVar38;
        sVar39 = (short)((ulong)uVar38 >> 0x10);
        sVar40 = (short)((ulong)uVar38 >> 0x20);
        sVar41 = (short)((ulong)uVar38 >> 0x30);
        sVar11 = (short)uVar42;
        sVar12 = (short)((ulong)uVar42 >> 0x10);
        sVar13 = (short)((ulong)uVar42 >> 0x20);
        sVar14 = (short)((ulong)uVar42 >> 0x30);
        iVar23 = iVar23 + (int)sVar37 * (int)sVar31 + (int)sVar11 * (int)(short)uVar35;
        iVar24 = iVar24 + (int)sVar39 * (int)sVar32 +
                 (int)sVar12 * (int)(short)((ulong)uVar35 >> 0x10);
        iVar25 = iVar25 + (int)sVar40 * (int)sVar33 +
                 (int)sVar13 * (int)(short)((ulong)uVar35 >> 0x20);
        iVar26 = iVar26 + (int)sVar41 * (int)sVar34 +
                 (int)sVar14 * (int)(short)((ulong)uVar35 >> 0x30);
        iVar27 = iVar27 + (int)sVar37 * (int)auVar43._0_2_ + (int)sVar11 * (int)auVar43._8_2_;
        iVar28 = iVar28 + (int)sVar39 * (int)auVar43._2_2_ + (int)sVar12 * (int)auVar43._10_2_;
        iVar29 = iVar29 + (int)sVar40 * (int)auVar43._4_2_ + (int)sVar13 * (int)auVar43._12_2_;
        iVar30 = iVar30 + (int)sVar41 * (int)auVar43._6_2_ + (int)sVar14 * (int)auVar43._14_2_;
        iVar19 = iVar19 + (int)sVar37 * (int)auVar44._0_2_ + (int)sVar11 * (int)auVar44._8_2_;
        iVar20 = iVar20 + (int)sVar39 * (int)auVar44._2_2_ + (int)sVar12 * (int)auVar44._10_2_;
        iVar21 = iVar21 + (int)sVar40 * (int)auVar44._4_2_ + (int)sVar13 * (int)auVar44._12_2_;
        iVar22 = iVar22 + (int)sVar41 * (int)auVar44._6_2_ + (int)sVar14 * (int)auVar44._14_2_;
        iVar15 = iVar15 + (int)sVar37 * (int)auVar45._0_2_ + (int)sVar11 * (int)auVar45._8_2_;
        iVar16 = iVar16 + (int)sVar39 * (int)auVar45._2_2_ + (int)sVar12 * (int)auVar45._10_2_;
        iVar17 = iVar17 + (int)sVar40 * (int)auVar45._4_2_ + (int)sVar13 * (int)auVar45._12_2_;
        iVar18 = iVar18 + (int)sVar41 * (int)auVar45._6_2_ + (int)sVar14 * (int)auVar45._14_2_;
        sVar31 = (short)uVar36;
        sVar32 = (short)((ulong)uVar36 >> 0x10);
        sVar33 = (short)((ulong)uVar36 >> 0x20);
        sVar34 = (short)((ulong)uVar36 >> 0x30);
        pauVar9 = pauVar9 + 1;
        puVar10 = puVar10 + 2;
        uVar35 = *(undefined8 *)(puVar4 + 8);
      } while (iVar3 != 0);
    }
    iVar23 = iVar23 + iVar24 + iVar25 + iVar26;
    uVar8 = uVar6 * 4;
    iVar28 = iVar27 + iVar28 + iVar29 + iVar30;
    iVar27 = iVar19 + iVar20 + iVar21 + iVar22;
    uVar6 = uVar6 + 4;
    iVar24 = iVar15 + iVar16 + iVar17 + iVar18;
    *(int *)(param_3 + uVar8) = iVar23;
    *(int *)(param_3 + (uVar8 | 4)) = iVar28;
    pauVar7 = (undefined1 (*) [16])(*pauVar7 + 8);
    if (iVar23 <= iVar28) {
      iVar23 = iVar28;
    }
    iVar28 = iVar27;
    if (iVar27 <= iVar24) {
      iVar28 = iVar24;
    }
    if (iVar23 <= iVar28) {
      iVar23 = iVar28;
    }
    if (iVar5 <= iVar23) {
      iVar5 = iVar23;
    }
    *(int *)(param_3 + (uVar8 | 8)) = iVar27;
    *(int *)(param_3 + (uVar8 | 0xc)) = iVar24;
  } while (uVar6 < param_5 - 3);
  return iVar5;
}


/* ssc_compute_band_energies_for_lastband @ 00107cb4 size 1524 */

void ssc_compute_band_energies_for_lastband
               (long param_1,long param_2,int *param_3,uint param_4,int param_5,uint param_6)

{
  undefined8 *puVar1;
  undefined1 (*pauVar2) [16];
  short sVar3;
  undefined *puVar4;
  uint uVar5;
  short sVar6;
  uint uVar7;
  undefined8 *puVar8;
  undefined1 auVar9 [16];
  undefined8 uVar10;
  undefined8 *puVar11;
  undefined4 *puVar12;
  uint uVar13;
  ulong uVar14;
  undefined1 (*pauVar15) [16];
  int *piVar16;
  long lVar17;
  long lVar18;
  long lVar19;
  uint *puVar20;
  undefined4 *puVar21;
  ulong uVar22;
  undefined8 *puVar23;
  ulong uVar24;
  long lVar25;
  int *piVar26;
  ulong uVar27;
  uint uVar28;
  ulong uVar29;
  uint uVar30;
  undefined1 auVar31 [16];
  undefined1 auVar32 [16];
  undefined1 auVar33 [16];
  undefined1 auVar34 [16];
  int iVar35;
  int iVar40;
  int iVar42;
  int iVar44;
  undefined1 auVar36 [16];
  undefined1 auVar37 [16];
  undefined1 auVar38 [16];
  int iVar41;
  int iVar43;
  undefined1 auVar39 [16];
  undefined1 auVar45 [16];
  undefined1 auVar46 [16];
  undefined1 auVar47 [16];
  undefined1 auVar48 [16];
  undefined1 auVar49 [16];
  undefined4 uVar50;
  undefined4 uVar51;
  undefined4 uVar52;
  undefined4 uVar53;
  undefined1 auVar54 [16];
  undefined1 auVar55 [16];
  undefined1 auVar56 [16];
  undefined1 auVar57 [16];
  undefined1 auVar58 [16];
  undefined1 auVar59 [16];
  undefined1 auVar60 [16];
  undefined1 auVar61 [16];
  
  puVar4 = &DAT_001027f8;
  if (param_5 != 0) {
    puVar4 = &DAT_00102840 + (long)(int)param_6 * 0x10;
  }
  uVar13 = 0xffffffff;
  if (param_5 != 0) {
    uVar13 = ~param_6;
  }
  if (0 < (int)param_4) {
    uVar29 = 0;
    uVar27 = (ulong)param_4;
    uVar13 = (int)*(short *)(*(long *)(param_1 + 0x10) +
                            (long)(int)(*(int *)(param_1 + 8) + uVar13) * 2) << 3;
    uVar14 = (ulong)uVar13;
    piVar26 = param_3;
    do {
      auVar31 = ZEXT816(0);
      sVar6 = *(short *)(puVar4 + uVar29 * 2);
      auVar46._0_4_ = (int)uVar14;
      uVar7 = sVar6 - auVar46._0_4_;
      uVar30 = uVar7 + 3;
      if (-1 < (int)uVar7) {
        uVar30 = uVar7;
      }
      auVar60._0_4_ = (int)sVar6 + ((uVar30 & 0xfffffffc) - uVar7);
      if (auVar46._0_4_ < auVar60._0_4_) {
        auVar31 = ZEXT816(0);
        uVar14 = (ulong)auVar46._0_4_;
        puVar21 = (undefined4 *)(param_2 + (long)auVar46._0_4_ * 4);
        do {
          uVar14 = uVar14 + 4;
          auVar58._0_4_ = MP_INT_ABS(*puVar21);
          auVar58._4_4_ = MP_INT_ABS(puVar21[1]);
          auVar58._8_4_ = MP_INT_ABS(puVar21[2]);
          auVar58._12_4_ = MP_INT_ABS(puVar21[3]);
          auVar31 = NEON_smax(auVar31,auVar58,4);
          puVar21 = puVar21 + 4;
        } while ((long)uVar14 < (long)auVar60._0_4_);
      }
      uVar30 = NEON_smaxv(auVar31,4);
      iVar41 = (int)sVar6;
      iVar43 = (int)sVar6;
      if ((int)uVar14 < iVar41) {
        lVar25 = (long)(int)uVar14;
        uVar14 = iVar43 - lVar25;
        if (7 < uVar14) {
          auVar31._0_8_ = CONCAT44(uVar30,uVar30);
          auVar31._8_4_ = uVar30;
          auVar31._12_4_ = uVar30;
          uVar22 = uVar14 & 0xfffffffffffffff8;
          puVar23 = (undefined8 *)(param_2 + 0x10 + lVar25 * 4);
          auVar59._8_8_ = auVar31._8_8_;
          auVar59._0_8_ = auVar31._0_8_;
          uVar24 = uVar22;
          do {
            puVar1 = puVar23 + -2;
            puVar21 = (undefined4 *)((long)puVar23 + -0xc);
            puVar11 = puVar23 + -1;
            puVar12 = (undefined4 *)((long)puVar23 + -4);
            puVar8 = puVar23 + 1;
            uVar10 = *puVar23;
            uVar24 = uVar24 - 8;
            puVar23 = puVar23 + 4;
            auVar45._0_4_ = MP_INT_ABS(*(undefined4 *)puVar1);
            auVar45._4_4_ = MP_INT_ABS(*puVar21);
            auVar45._8_4_ = MP_INT_ABS(*(undefined4 *)puVar11);
            auVar45._12_4_ = MP_INT_ABS(*puVar12);
            uVar50 = MP_INT_ABS((int)uVar10);
            uVar51 = MP_INT_ABS((int)((ulong)uVar10 >> 0x20));
            uVar52 = MP_INT_ABS((int)*puVar8);
            uVar53 = MP_INT_ABS((int)((ulong)*puVar8 >> 0x20));
            auVar31 = NEON_smax(auVar31,auVar45,4);
            auVar61._4_4_ = uVar51;
            auVar61._0_4_ = uVar50;
            auVar61._8_4_ = uVar52;
            auVar61._12_4_ = uVar53;
            auVar59 = NEON_smax(auVar59,auVar61,4);
          } while (uVar24 != 0);
          auVar31 = NEON_smax(auVar31,auVar59,4);
          uVar30 = NEON_smaxv(auVar31,4);
          lVar25 = uVar22 + lVar25;
          if (uVar14 == uVar22) goto LAB_00107e70;
        }
        lVar18 = iVar43 - lVar25;
        puVar20 = (uint *)(param_2 + lVar25 * 4);
        do {
          uVar28 = *puVar20;
          uVar7 = -uVar28;
          if (-1 < (int)uVar28) {
            uVar7 = uVar28;
          }
          if ((int)uVar30 <= (int)uVar7) {
            uVar30 = uVar7;
          }
          lVar18 = lVar18 + -1;
          puVar20 = puVar20 + 1;
        } while (lVar18 != 0);
      }
LAB_00107e70:
      if ((int)uVar30 < 1) {
        auVar46._0_4_ = 1;
      }
      else {
        uVar7 = (int)LZCOUNT(uVar30) - 0x15;
        iVar35 = 0;
        iVar40 = 0;
        iVar42 = 0;
        iVar44 = 0;
        auVar32._4_4_ = uVar7;
        auVar32._0_4_ = uVar7;
        auVar32._8_4_ = uVar7;
        auVar32._12_4_ = uVar7;
        if (auVar46._0_4_ < auVar60._0_4_) {
          iVar35 = 0;
          iVar40 = 0;
          iVar42 = 0;
          iVar44 = 0;
          lVar25 = (long)auVar46._0_4_;
          pauVar15 = (undefined1 (*) [16])(param_2 + (long)auVar46._0_4_ * 4);
          do {
            lVar25 = lVar25 + 4;
            auVar46 = NEON_sshl(*pauVar15,auVar32,4);
            iVar35 = iVar35 + (int)auVar46._0_2_ * (int)auVar46._0_2_;
            iVar40 = iVar40 + (int)auVar46._4_2_ * (int)auVar46._4_2_;
            iVar42 = iVar42 + (int)auVar46._8_2_ * (int)auVar46._8_2_;
            iVar44 = iVar44 + (int)auVar46._12_2_ * (int)auVar46._12_2_;
            pauVar15 = pauVar15 + 1;
          } while (lVar25 < auVar60._0_4_);
          auVar46._0_4_ = (int)lVar25;
        }
        auVar60._0_4_ = iVar35 + iVar40 + iVar42 + iVar44;
        uVar28 = 0x15 - (int)LZCOUNT(uVar30);
        if (auVar46._0_4_ < iVar43) {
          lVar25 = (long)auVar46._0_4_;
          uVar14 = iVar41 - lVar25;
          if (7 < uVar14) {
            uVar22 = uVar14 & 0xfffffffffffffff8;
            pauVar15 = (undefined1 (*) [16])(param_2 + 0x10 + lVar25 * 4);
            auVar60._4_12_ = SUB1612(ZEXT816(0),4);
            uVar24 = uVar22;
            auVar46 = ZEXT816(0);
            do {
              pauVar2 = pauVar15 + -1;
              auVar31 = *pauVar15;
              uVar24 = uVar24 - 8;
              auVar56._0_4_ = -uVar28;
              auVar56._4_4_ = -uVar28;
              auVar56._8_4_ = -uVar28;
              auVar56._12_4_ = -uVar28;
              pauVar15 = pauVar15 + 2;
              auVar54._0_4_ = -(uint)(0x7ff < uVar30);
              auVar61 = NEON_ushl(*pauVar2,auVar32,4);
              auVar59 = NEON_sshl(*pauVar2,auVar56,4);
              auVar58 = NEON_sshl(auVar31,auVar56,4);
              auVar31 = NEON_ushl(auVar31,auVar32,4);
              auVar54._4_4_ = auVar54._0_4_;
              auVar54._8_4_ = auVar54._0_4_;
              auVar54._12_4_ = auVar54._0_4_;
              auVar59 = auVar59 ^ (auVar59 ^ auVar61) & ~auVar54;
              auVar31 = auVar31 ^ (auVar31 ^ auVar58) & auVar54;
              auVar36._0_4_ = auVar60._0_4_ + (int)auVar59._0_2_ * (int)auVar59._0_2_;
              auVar36._4_4_ = auVar60._4_4_ + (int)auVar59._4_2_ * (int)auVar59._4_2_;
              auVar36._8_4_ = auVar60._8_4_ + (int)auVar59._8_2_ * (int)auVar59._8_2_;
              auVar36._12_4_ = auVar60._12_4_ + (int)auVar59._12_2_ * (int)auVar59._12_2_;
              auVar47._0_4_ = auVar46._0_4_ + (int)auVar31._0_2_ * (int)auVar31._0_2_;
              auVar47._4_4_ = auVar46._4_4_ + (int)auVar31._4_2_ * (int)auVar31._4_2_;
              auVar47._8_4_ = auVar46._8_4_ + (int)auVar31._8_2_ * (int)auVar31._8_2_;
              auVar47._12_4_ = auVar46._12_4_ + (int)auVar31._12_2_ * (int)auVar31._12_2_;
              auVar60 = auVar36;
              auVar46 = auVar47;
            } while (uVar24 != 0);
            auVar60._0_4_ =
                 auVar47._0_4_ + auVar36._0_4_ + auVar47._4_4_ + auVar36._4_4_ +
                 auVar47._8_4_ + auVar36._8_4_ + auVar47._12_4_ + auVar36._12_4_;
            lVar25 = uVar22 + lVar25;
            if (uVar14 == uVar22) goto LAB_00107d48;
          }
          lVar18 = iVar41 - lVar25;
          piVar16 = (int *)(param_2 + lVar25 * 4);
          do {
            sVar3 = (short)(*piVar16 >> (uVar28 & 0x1f));
            if (uVar30 < 0x800) {
              sVar3 = (short)(*piVar16 << (ulong)(uVar7 & 0x1f));
            }
            lVar18 = lVar18 + -1;
            auVar60._0_4_ = auVar60._0_4_ + (int)sVar3 * (int)sVar3;
            piVar16 = piVar16 + 1;
          } while (lVar18 != 0);
        }
LAB_00107d48:
        auVar60._0_4_ = ssc_sqrt(auVar60._0_4_);
        auVar46._0_4_ = auVar60._0_4_ >> (uVar7 & 0x1f);
        if (0x3ff < uVar30) {
          auVar46._0_4_ = auVar60._0_4_ << (ulong)(uVar28 & 0x1f);
        }
        auVar46._0_4_ = auVar46._0_4_ + 1;
      }
      uVar29 = uVar29 + 1;
      uVar14 = (long)sVar6 & 0xffffffff;
      *piVar26 = auVar46._0_4_;
      piVar26 = piVar26 + 1;
    } while (uVar29 != uVar27);
    uVar29 = 0;
    auVar46._0_4_ = *(int *)(param_1 + 0x1c) << 3;
    lVar18 = (long)auVar46._0_4_;
    lVar25 = param_2 + (long)auVar46._0_4_ * 4;
    piVar26 = param_3 + uVar27;
    do {
      auVar31 = ZEXT816(0);
      uVar28 = (uint)*(short *)(puVar4 + uVar29 * 2);
      uVar7 = uVar28 - uVar13;
      uVar30 = uVar7 + 3;
      if (-1 < (int)uVar7) {
        uVar30 = uVar7;
      }
      uVar14 = (ulong)uVar13;
      auVar46._0_4_ = uVar28 + ((uVar30 & 0xfffffffc) - uVar7);
      if ((int)uVar13 < auVar46._0_4_) {
        auVar31 = ZEXT816(0);
        uVar14 = (ulong)(int)uVar13;
        puVar21 = (undefined4 *)(lVar25 + (long)(int)uVar13 * 4);
        do {
          uVar14 = uVar14 + 4;
          auVar37._0_4_ = MP_INT_ABS(*puVar21);
          auVar37._4_4_ = MP_INT_ABS(puVar21[1]);
          auVar37._8_4_ = MP_INT_ABS(puVar21[2]);
          auVar37._12_4_ = MP_INT_ABS(puVar21[3]);
          auVar31 = NEON_smax(auVar31,auVar37,4);
          puVar21 = puVar21 + 4;
        } while ((long)uVar14 < (long)auVar46._0_4_);
      }
      uVar30 = NEON_smaxv(auVar31,4);
      if ((int)uVar14 < (int)uVar28) {
        lVar19 = (long)(int)uVar14;
        uVar14 = (int)uVar28 - lVar19;
        if (7 < uVar14) {
          auVar33._0_8_ = CONCAT44(uVar30,uVar30);
          auVar33._8_4_ = uVar30;
          auVar33._12_4_ = uVar30;
          lVar17 = lVar18 + lVar19;
          uVar22 = uVar14 & 0xfffffffffffffff8;
          auVar38._8_8_ = auVar33._8_8_;
          auVar38._0_8_ = auVar33._0_8_;
          lVar19 = uVar22 + lVar19;
          puVar23 = (undefined8 *)(param_2 + 0x10 + lVar17 * 4);
          uVar24 = uVar22;
          do {
            puVar1 = puVar23 + -2;
            puVar21 = (undefined4 *)((long)puVar23 + -0xc);
            puVar11 = puVar23 + -1;
            puVar12 = (undefined4 *)((long)puVar23 + -4);
            puVar8 = puVar23 + 1;
            uVar10 = *puVar23;
            uVar24 = uVar24 - 8;
            puVar23 = puVar23 + 4;
            auVar48._0_4_ = MP_INT_ABS(*(undefined4 *)puVar1);
            auVar48._4_4_ = MP_INT_ABS(*puVar21);
            auVar48._8_4_ = MP_INT_ABS(*(undefined4 *)puVar11);
            auVar48._12_4_ = MP_INT_ABS(*puVar12);
            uVar50 = MP_INT_ABS((int)uVar10);
            uVar51 = MP_INT_ABS((int)((ulong)uVar10 >> 0x20));
            uVar52 = MP_INT_ABS((int)*puVar8);
            uVar53 = MP_INT_ABS((int)((ulong)*puVar8 >> 0x20));
            auVar33 = NEON_smax(auVar33,auVar48,4);
            auVar9._4_4_ = uVar51;
            auVar9._0_4_ = uVar50;
            auVar9._8_4_ = uVar52;
            auVar9._12_4_ = uVar53;
            auVar38 = NEON_smax(auVar38,auVar9,4);
          } while (uVar24 != 0);
          auVar31 = NEON_smax(auVar33,auVar38,4);
          uVar30 = NEON_smaxv(auVar31,4);
          if (uVar14 == uVar22) goto LAB_0010812c;
        }
        lVar17 = (int)uVar28 - lVar19;
        puVar20 = (uint *)(param_2 + (lVar18 + lVar19) * 4);
        do {
          uVar5 = *puVar20;
          uVar7 = -uVar5;
          if (-1 < (int)uVar5) {
            uVar7 = uVar5;
          }
          if ((int)uVar30 <= (int)uVar7) {
            uVar30 = uVar7;
          }
          lVar17 = lVar17 + -1;
          puVar20 = puVar20 + 1;
        } while (lVar17 != 0);
      }
LAB_0010812c:
      if ((int)uVar30 < 1) {
        auVar46._0_4_ = 1;
      }
      else {
        uVar7 = (int)LZCOUNT(uVar30) - 0x15;
        auVar60._0_4_ = 0;
        iVar41 = 0;
        iVar43 = 0;
        iVar35 = 0;
        auVar34._4_4_ = uVar7;
        auVar34._0_4_ = uVar7;
        auVar34._8_4_ = uVar7;
        auVar34._12_4_ = uVar7;
        if ((int)uVar13 < auVar46._0_4_) {
          lVar19 = (long)(int)uVar13;
          auVar60._0_4_ = 0;
          iVar41 = 0;
          iVar43 = 0;
          iVar35 = 0;
          pauVar15 = (undefined1 (*) [16])(lVar25 + (long)(int)uVar13 * 4);
          do {
            lVar19 = lVar19 + 4;
            auVar31 = NEON_sshl(*pauVar15,auVar34,4);
            auVar60._0_4_ = auVar60._0_4_ + (int)auVar31._0_2_ * (int)auVar31._0_2_;
            iVar41 = iVar41 + (int)auVar31._4_2_ * (int)auVar31._4_2_;
            iVar43 = iVar43 + (int)auVar31._8_2_ * (int)auVar31._8_2_;
            iVar35 = iVar35 + (int)auVar31._12_2_ * (int)auVar31._12_2_;
            pauVar15 = pauVar15 + 1;
          } while (lVar19 < auVar46._0_4_);
          uVar13 = (uint)lVar19;
        }
        auVar46._0_4_ = auVar60._0_4_ + iVar41 + iVar43 + iVar35;
        uVar5 = 0x15 - (int)LZCOUNT(uVar30);
        if ((int)uVar13 < (int)uVar28) {
          lVar19 = (long)(int)uVar13;
          uVar14 = (int)uVar28 - lVar19;
          if (7 < uVar14) {
            lVar17 = lVar18 + lVar19;
            uVar22 = uVar14 & 0xfffffffffffffff8;
            lVar19 = uVar22 + lVar19;
            pauVar15 = (undefined1 (*) [16])(param_2 + 0x10 + lVar17 * 4);
            auVar46._4_12_ = SUB1612(ZEXT816(0),4);
            uVar24 = uVar22;
            auVar31 = ZEXT816(0);
            do {
              pauVar2 = pauVar15 + -1;
              auVar60 = *pauVar15;
              uVar24 = uVar24 - 8;
              auVar57._0_4_ = -uVar5;
              auVar57._4_4_ = -uVar5;
              auVar57._8_4_ = -uVar5;
              auVar57._12_4_ = -uVar5;
              pauVar15 = pauVar15 + 2;
              auVar55._0_4_ = -(uint)(0x7ff < uVar30);
              auVar61 = NEON_ushl(*pauVar2,auVar34,4);
              auVar59 = NEON_sshl(*pauVar2,auVar57,4);
              auVar58 = NEON_sshl(auVar60,auVar57,4);
              auVar60 = NEON_ushl(auVar60,auVar34,4);
              auVar55._4_4_ = auVar55._0_4_;
              auVar55._8_4_ = auVar55._0_4_;
              auVar55._12_4_ = auVar55._0_4_;
              auVar59 = auVar59 ^ (auVar59 ^ auVar61) & ~auVar55;
              auVar60 = auVar60 ^ (auVar60 ^ auVar58) & auVar55;
              auVar39._0_4_ = auVar46._0_4_ + (int)auVar59._0_2_ * (int)auVar59._0_2_;
              auVar39._4_4_ = auVar46._4_4_ + (int)auVar59._4_2_ * (int)auVar59._4_2_;
              auVar39._8_4_ = auVar46._8_4_ + (int)auVar59._8_2_ * (int)auVar59._8_2_;
              auVar39._12_4_ = auVar46._12_4_ + (int)auVar59._12_2_ * (int)auVar59._12_2_;
              auVar49._0_4_ = auVar31._0_4_ + (int)auVar60._0_2_ * (int)auVar60._0_2_;
              auVar49._4_4_ = auVar31._4_4_ + (int)auVar60._4_2_ * (int)auVar60._4_2_;
              auVar49._8_4_ = auVar31._8_4_ + (int)auVar60._8_2_ * (int)auVar60._8_2_;
              auVar49._12_4_ = auVar31._12_4_ + (int)auVar60._12_2_ * (int)auVar60._12_2_;
              auVar46 = auVar39;
              auVar31 = auVar49;
            } while (uVar24 != 0);
            auVar46._0_4_ =
                 auVar49._0_4_ + auVar39._0_4_ + auVar49._4_4_ + auVar39._4_4_ +
                 auVar49._8_4_ + auVar39._8_4_ + auVar49._12_4_ + auVar39._12_4_;
            if (uVar14 == uVar22) goto LAB_00107ffc;
          }
          lVar17 = (int)uVar28 - lVar19;
          piVar16 = (int *)(param_2 + (lVar18 + lVar19) * 4);
          do {
            sVar6 = (short)(*piVar16 >> (uVar5 & 0x1f));
            if (uVar30 < 0x800) {
              sVar6 = (short)(*piVar16 << (ulong)(uVar7 & 0x1f));
            }
            lVar17 = lVar17 + -1;
            auVar46._0_4_ = auVar46._0_4_ + (int)sVar6 * (int)sVar6;
            piVar16 = piVar16 + 1;
          } while (lVar17 != 0);
        }
LAB_00107ffc:
        auVar60._0_4_ = ssc_sqrt(auVar46._0_4_);
        auVar46._0_4_ = auVar60._0_4_ >> (uVar7 & 0x1f);
        if (0x3ff < uVar30) {
          auVar46._0_4_ = auVar60._0_4_ << (ulong)(uVar5 & 0x1f);
        }
        auVar46._0_4_ = auVar46._0_4_ + 1;
      }
      uVar29 = uVar29 + 1;
      *piVar26 = auVar46._0_4_;
      piVar26 = piVar26 + 1;
      uVar13 = uVar28;
    } while (uVar29 != uVar27);
  }
  return;
}


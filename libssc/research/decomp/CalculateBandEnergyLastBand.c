/* CalculateBandEnergyLastBand @ 001079b8 size 764 */

void CalculateBandEnergyLastBand
               (long param_1,long param_2,long param_3,ulong param_4,uint param_5,int param_6,
               int param_7)

{
  undefined8 *puVar1;
  undefined1 (*pauVar2) [16];
  long lVar3;
  uint uVar4;
  short sVar5;
  uint uVar6;
  undefined8 *puVar7;
  undefined8 uVar8;
  undefined8 *puVar9;
  undefined4 *puVar10;
  int iVar11;
  uint uVar12;
  long lVar13;
  int *piVar14;
  long lVar15;
  undefined4 *puVar16;
  ulong uVar17;
  uint *puVar18;
  undefined1 (*pauVar19) [16];
  ulong uVar20;
  ulong uVar21;
  undefined8 *puVar22;
  ulong uVar23;
  long lVar24;
  int *piVar25;
  uint uVar26;
  undefined1 auVar27 [16];
  undefined1 auVar28 [16];
  int iVar29;
  int iVar33;
  int iVar34;
  undefined1 auVar30 [16];
  int iVar35;
  undefined1 auVar31 [16];
  undefined1 auVar32 [16];
  undefined1 auVar36 [16];
  undefined4 uVar37;
  undefined4 uVar38;
  undefined4 uVar39;
  undefined4 uVar40;
  undefined1 auVar41 [16];
  undefined1 auVar42 [16];
  undefined1 auVar43 [16];
  undefined1 auVar44 [16];
  undefined1 auVar45 [16];
  
  if (0 < (int)param_5) {
    lVar24 = (long)param_6;
    uVar23 = 0;
    lVar3 = param_2 + lVar24 * 4;
    piVar25 = (int *)(param_1 + (long)param_7 * 4);
    do {
      sVar5 = *(short *)(param_3 + uVar23 * 2);
      auVar27 = ZEXT816(0);
      iVar11 = (int)param_4;
      uVar12 = sVar5 - iVar11;
      uVar26 = uVar12 + 3;
      if (-1 < (int)uVar12) {
        uVar26 = uVar12;
      }
      param_4 = param_4 & 0xffffffff;
      auVar31._0_4_ = (int)sVar5 + ((uVar26 & 0xfffffffc) - uVar12);
      if (iVar11 < auVar31._0_4_) {
        auVar27 = ZEXT816(0);
        param_4 = (ulong)iVar11;
        puVar16 = (undefined4 *)(lVar3 + (long)iVar11 * 4);
        do {
          param_4 = param_4 + 4;
          auVar44._0_4_ = MP_INT_ABS(*puVar16);
          auVar44._4_4_ = MP_INT_ABS(puVar16[1]);
          auVar44._8_4_ = MP_INT_ABS(puVar16[2]);
          auVar44._12_4_ = MP_INT_ABS(puVar16[3]);
          auVar27 = NEON_smax(auVar27,auVar44,4);
          puVar16 = puVar16 + 4;
        } while ((long)param_4 < (long)auVar31._0_4_);
      }
      uVar26 = NEON_smaxv(auVar27,4);
      uVar12 = (uint)sVar5;
      if ((int)param_4 < (int)sVar5) {
        lVar15 = (long)(int)param_4;
        uVar17 = (int)uVar12 - lVar15;
        if (7 < uVar17) {
          auVar27._0_8_ = CONCAT44(uVar26,uVar26);
          auVar27._8_4_ = uVar26;
          auVar27._12_4_ = uVar26;
          lVar13 = lVar24 + lVar15;
          uVar20 = uVar17 & 0xfffffffffffffff8;
          auVar30._8_8_ = auVar27._8_8_;
          auVar30._0_8_ = auVar27._0_8_;
          lVar15 = uVar20 + lVar15;
          puVar22 = (undefined8 *)(param_2 + 0x10 + lVar13 * 4);
          uVar21 = uVar20;
          do {
            puVar1 = puVar22 + -2;
            puVar16 = (undefined4 *)((long)puVar22 + -0xc);
            puVar9 = puVar22 + -1;
            puVar10 = (undefined4 *)((long)puVar22 + -4);
            puVar7 = puVar22 + 1;
            uVar8 = *puVar22;
            uVar21 = uVar21 - 8;
            puVar22 = puVar22 + 4;
            auVar45._0_4_ = MP_INT_ABS(*(undefined4 *)puVar1);
            auVar45._4_4_ = MP_INT_ABS(*puVar16);
            auVar45._8_4_ = MP_INT_ABS(*(undefined4 *)puVar9);
            auVar45._12_4_ = MP_INT_ABS(*puVar10);
            uVar37 = MP_INT_ABS((int)uVar8);
            uVar38 = MP_INT_ABS((int)((ulong)uVar8 >> 0x20));
            uVar39 = MP_INT_ABS((int)*puVar7);
            uVar40 = MP_INT_ABS((int)((ulong)*puVar7 >> 0x20));
            auVar27 = NEON_smax(auVar27,auVar45,4);
            auVar43._4_4_ = uVar38;
            auVar43._0_4_ = uVar37;
            auVar43._8_4_ = uVar39;
            auVar43._12_4_ = uVar40;
            auVar30 = NEON_smax(auVar30,auVar43,4);
          } while (uVar21 != 0);
          auVar27 = NEON_smax(auVar27,auVar30,4);
          uVar26 = NEON_smaxv(auVar27,4);
          if (uVar17 == uVar20) goto LAB_00107b3c;
        }
        lVar13 = (int)uVar12 - lVar15;
        puVar18 = (uint *)(param_2 + (lVar24 + lVar15) * 4);
        do {
          uVar4 = *puVar18;
          uVar6 = -uVar4;
          if (-1 < (int)uVar4) {
            uVar6 = uVar4;
          }
          if ((int)uVar26 <= (int)uVar6) {
            uVar26 = uVar6;
          }
          lVar13 = lVar13 + -1;
          puVar18 = puVar18 + 1;
        } while (lVar13 != 0);
      }
LAB_00107b3c:
      if ((int)uVar26 < 1) {
        iVar11 = 1;
        param_4 = (ulong)uVar12;
      }
      else {
        uVar6 = (int)LZCOUNT(uVar26) - 0x15;
        iVar29 = 0;
        iVar33 = 0;
        iVar34 = 0;
        iVar35 = 0;
        auVar28._4_4_ = uVar6;
        auVar28._0_4_ = uVar6;
        auVar28._8_4_ = uVar6;
        auVar28._12_4_ = uVar6;
        if (iVar11 < auVar31._0_4_) {
          iVar29 = 0;
          iVar33 = 0;
          iVar34 = 0;
          iVar35 = 0;
          lVar15 = (long)iVar11;
          pauVar19 = (undefined1 (*) [16])(lVar3 + (long)iVar11 * 4);
          do {
            lVar15 = lVar15 + 4;
            auVar27 = NEON_sshl(*pauVar19,auVar28,4);
            iVar29 = iVar29 + (int)auVar27._0_2_ * (int)auVar27._0_2_;
            iVar33 = iVar33 + (int)auVar27._4_2_ * (int)auVar27._4_2_;
            iVar34 = iVar34 + (int)auVar27._8_2_ * (int)auVar27._8_2_;
            iVar35 = iVar35 + (int)auVar27._12_2_ * (int)auVar27._12_2_;
            pauVar19 = pauVar19 + 1;
          } while (lVar15 < auVar31._0_4_);
          iVar11 = (int)lVar15;
        }
        auVar31._0_4_ = iVar29 + iVar33 + iVar34 + iVar35;
        uVar4 = 0x15 - (int)LZCOUNT(uVar26);
        if (iVar11 < sVar5) {
          lVar15 = (long)iVar11;
          uVar17 = (int)uVar12 - lVar15;
          if (7 < uVar17) {
            lVar13 = lVar24 + lVar15;
            uVar20 = uVar17 & 0xfffffffffffffff8;
            lVar15 = uVar20 + lVar15;
            pauVar19 = (undefined1 (*) [16])(param_2 + 0x10 + lVar13 * 4);
            auVar31._4_12_ = SUB1612(ZEXT816(0),4);
            uVar21 = uVar20;
            auVar27 = ZEXT816(0);
            do {
              pauVar2 = pauVar19 + -1;
              auVar44 = *pauVar19;
              uVar21 = uVar21 - 8;
              auVar42._0_4_ = -uVar4;
              auVar42._4_4_ = -uVar4;
              auVar42._8_4_ = -uVar4;
              auVar42._12_4_ = -uVar4;
              pauVar19 = pauVar19 + 2;
              auVar41._0_4_ = -(uint)(0x7ff < uVar26);
              auVar45 = NEON_ushl(*pauVar2,auVar28,4);
              auVar43 = NEON_sshl(*pauVar2,auVar42,4);
              auVar30 = NEON_sshl(auVar44,auVar42,4);
              auVar44 = NEON_ushl(auVar44,auVar28,4);
              auVar41._4_4_ = auVar41._0_4_;
              auVar41._8_4_ = auVar41._0_4_;
              auVar41._12_4_ = auVar41._0_4_;
              auVar43 = auVar43 ^ (auVar43 ^ auVar45) & ~auVar41;
              auVar44 = auVar44 ^ (auVar44 ^ auVar30) & auVar41;
              auVar32._0_4_ = auVar31._0_4_ + (int)auVar43._0_2_ * (int)auVar43._0_2_;
              auVar32._4_4_ = auVar31._4_4_ + (int)auVar43._4_2_ * (int)auVar43._4_2_;
              auVar32._8_4_ = auVar31._8_4_ + (int)auVar43._8_2_ * (int)auVar43._8_2_;
              auVar32._12_4_ = auVar31._12_4_ + (int)auVar43._12_2_ * (int)auVar43._12_2_;
              auVar36._0_4_ = auVar27._0_4_ + (int)auVar44._0_2_ * (int)auVar44._0_2_;
              auVar36._4_4_ = auVar27._4_4_ + (int)auVar44._4_2_ * (int)auVar44._4_2_;
              auVar36._8_4_ = auVar27._8_4_ + (int)auVar44._8_2_ * (int)auVar44._8_2_;
              auVar36._12_4_ = auVar27._12_4_ + (int)auVar44._12_2_ * (int)auVar44._12_2_;
              auVar31 = auVar32;
              auVar27 = auVar36;
            } while (uVar21 != 0);
            auVar31._0_4_ =
                 auVar36._0_4_ + auVar32._0_4_ + auVar36._4_4_ + auVar32._4_4_ +
                 auVar36._8_4_ + auVar32._8_4_ + auVar36._12_4_ + auVar32._12_4_;
            if (uVar17 == uVar20) goto LAB_00107a14;
          }
          lVar13 = (int)uVar12 - lVar15;
          piVar14 = (int *)(param_2 + (lVar24 + lVar15) * 4);
          do {
            sVar5 = (short)(*piVar14 >> (uVar4 & 0x1f));
            if (uVar26 < 0x800) {
              sVar5 = (short)(*piVar14 << (ulong)(uVar6 & 0x1f));
            }
            lVar13 = lVar13 + -1;
            auVar31._0_4_ = auVar31._0_4_ + (int)sVar5 * (int)sVar5;
            piVar14 = piVar14 + 1;
          } while (lVar13 != 0);
        }
LAB_00107a14:
        auVar31._0_4_ = ssc_sqrt(auVar31._0_4_);
        param_4 = (ulong)*(short *)(param_3 + uVar23 * 2);
        iVar11 = auVar31._0_4_ >> (uVar6 & 0x1f);
        if (0x3ff < uVar26) {
          iVar11 = auVar31._0_4_ << (ulong)(uVar4 & 0x1f);
        }
        iVar11 = iVar11 + 1;
      }
      uVar23 = uVar23 + 1;
      *piVar25 = iVar11;
      piVar25 = piVar25 + 1;
    } while (uVar23 != param_5);
  }
  return;
}


/* compute_band_energies_for_lastband @ 00102d88 size 1240 */

void compute_band_energies_for_lastband
               (long param_1,long param_2,long param_3,uint param_4,int param_5,uint param_6)

{
  undefined1 (*pauVar1) [16];
  undefined8 *puVar2;
  short sVar3;
  int iVar4;
  uint uVar5;
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  int iVar12;
  int iVar13;
  long lVar14;
  long lVar15;
  ulong uVar16;
  long lVar17;
  ulong uVar18;
  uint uVar19;
  undefined1 (*pauVar20) [16];
  ulong uVar21;
  ulong uVar22;
  ulong uVar23;
  long lVar24;
  int iVar25;
  int iVar26;
  int iVar27;
  int iVar28;
  int iVar29;
  int iVar30;
  undefined1 auVar31 [16];
  undefined1 auVar32 [16];
  
  puVar2 = &cutoff_start_index;
  if (param_5 != 0) {
    puVar2 = (undefined8 *)(cutoff_start_uhq_index + (long)(int)param_6 * 0x10);
  }
  if (0 < (int)param_4) {
    uVar19 = 0xffffffff;
    if (param_5 != 0) {
      uVar19 = ~param_6;
    }
    iVar4 = *(int *)(param_1 + 0x1c) << 3;
    uVar23 = 0;
    uVar22 = (ulong)param_4;
    iVar12 = (int)*(short *)(*(long *)(param_1 + 0x10) +
                            (long)(int)(*(int *)(param_1 + 8) + uVar19) * 2) << 3;
    do {
      while( true ) {
        sVar3 = *(short *)((long)puVar2 + uVar23 * 2);
        lVar24 = (long)iVar12;
        iVar12 = 0;
        lVar17 = lVar24;
        do {
          iVar13 = *(int *)(param_2 + lVar17 * 4);
          lVar17 = lVar17 + 1;
          if (iVar12 <= iVar13) {
            iVar12 = iVar13;
          }
          if (iVar12 <= -iVar13) {
            iVar12 = -iVar13;
          }
        } while (lVar17 < sVar3);
        if (iVar12 < 1) break;
        iVar12 = ec_ilog();
        lVar14 = (long)*(short *)((long)puVar2 + uVar23 * 2);
        iVar12 = iVar12 * 0x10000 + -0x10000 >> 0x10;
        uVar19 = iVar12 - 10;
        uVar5 = 10 - iVar12;
        lVar17 = lVar24 + 1;
        if ((int)uVar19 < 1) {
          if (lVar17 <= lVar14) {
            lVar17 = lVar14;
          }
          uVar16 = lVar17 - lVar24;
          if (uVar16 < 8) {
            iVar12 = 0;
          }
          else {
            uVar18 = uVar16 & 0xfffffffffffffff8;
            pauVar20 = (undefined1 (*) [16])(param_2 + 0x10 + lVar24 * 4);
            iVar12 = 0;
            iVar13 = 0;
            iVar25 = 0;
            iVar26 = 0;
            lVar24 = uVar18 + lVar24;
            iVar27 = 0;
            iVar28 = 0;
            iVar29 = 0;
            iVar30 = 0;
            uVar21 = uVar18;
            do {
              pauVar1 = pauVar20 + -1;
              auVar10 = *pauVar20;
              uVar21 = uVar21 - 8;
              pauVar20 = pauVar20 + 2;
              auVar32._4_4_ = uVar5;
              auVar32._0_4_ = uVar5;
              auVar32._8_4_ = uVar5;
              auVar32._12_4_ = uVar5;
              auVar32 = NEON_ushl(*pauVar1,auVar32,4);
              auVar31._4_4_ = uVar5;
              auVar31._0_4_ = uVar5;
              auVar31._8_4_ = uVar5;
              auVar31._12_4_ = uVar5;
              auVar31 = NEON_ushl(auVar10,auVar31,4);
              iVar12 = iVar12 + (int)auVar32._0_2_ * (int)auVar32._0_2_;
              iVar13 = iVar13 + (int)auVar32._4_2_ * (int)auVar32._4_2_;
              iVar25 = iVar25 + (int)auVar32._8_2_ * (int)auVar32._8_2_;
              iVar26 = iVar26 + (int)auVar32._12_2_ * (int)auVar32._12_2_;
              iVar27 = iVar27 + (int)auVar31._0_2_ * (int)auVar31._0_2_;
              iVar28 = iVar28 + (int)auVar31._4_2_ * (int)auVar31._4_2_;
              iVar29 = iVar29 + (int)auVar31._8_2_ * (int)auVar31._8_2_;
              iVar30 = iVar30 + (int)auVar31._12_2_ * (int)auVar31._12_2_;
            } while (uVar21 != 0);
            iVar12 = iVar27 + iVar12 + iVar28 + iVar13 + iVar29 + iVar25 + iVar30 + iVar26;
            if (uVar16 == uVar18) goto LAB_00102fd0;
          }
          do {
            lVar17 = lVar24 * 4;
            lVar24 = lVar24 + 1;
            iVar13 = (int)(short)(*(int *)(param_2 + lVar17) << (ulong)(uVar5 & 0x1f));
            iVar12 = iVar12 + iVar13 * iVar13;
          } while (lVar24 < lVar14);
        }
        else {
          if (lVar17 <= lVar14) {
            lVar17 = lVar14;
          }
          uVar16 = lVar17 - lVar24;
          if (uVar16 < 8) {
            iVar12 = 0;
          }
          else {
            uVar18 = uVar16 & 0xfffffffffffffff8;
            pauVar20 = (undefined1 (*) [16])(param_2 + 0x10 + lVar24 * 4);
            iVar12 = 0;
            iVar13 = 0;
            iVar25 = 0;
            iVar26 = 0;
            lVar24 = uVar18 + lVar24;
            iVar27 = 0;
            iVar28 = 0;
            iVar29 = 0;
            iVar30 = 0;
            uVar21 = uVar18;
            do {
              pauVar1 = pauVar20 + -1;
              auVar32 = *pauVar20;
              uVar21 = uVar21 - 8;
              pauVar20 = pauVar20 + 2;
              auVar10._4_4_ = -uVar19;
              auVar10._0_4_ = -uVar19;
              auVar10._8_4_ = -uVar19;
              auVar10._12_4_ = -uVar19;
              auVar31 = NEON_sshl(*pauVar1,auVar10,4);
              auVar11._4_4_ = -uVar19;
              auVar11._0_4_ = -uVar19;
              auVar11._8_4_ = -uVar19;
              auVar11._12_4_ = -uVar19;
              auVar32 = NEON_sshl(auVar32,auVar11,4);
              iVar12 = iVar12 + (int)auVar31._0_2_ * (int)auVar31._0_2_;
              iVar13 = iVar13 + (int)auVar31._4_2_ * (int)auVar31._4_2_;
              iVar25 = iVar25 + (int)auVar31._8_2_ * (int)auVar31._8_2_;
              iVar26 = iVar26 + (int)auVar31._12_2_ * (int)auVar31._12_2_;
              iVar27 = iVar27 + (int)auVar32._0_2_ * (int)auVar32._0_2_;
              iVar28 = iVar28 + (int)auVar32._4_2_ * (int)auVar32._4_2_;
              iVar29 = iVar29 + (int)auVar32._8_2_ * (int)auVar32._8_2_;
              iVar30 = iVar30 + (int)auVar32._12_2_ * (int)auVar32._12_2_;
            } while (uVar21 != 0);
            iVar12 = iVar27 + iVar12 + iVar28 + iVar13 + iVar29 + iVar25 + iVar30 + iVar26;
            if (uVar16 == uVar18) goto LAB_00102fd0;
          }
          do {
            lVar17 = lVar24 * 4;
            lVar24 = lVar24 + 1;
            iVar13 = (int)(short)(*(int *)(param_2 + lVar17) >> (uVar19 & 0x1f));
            iVar12 = iVar12 + iVar13 * iVar13;
          } while (lVar24 < lVar14);
        }
LAB_00102fd0:
        iVar13 = ssc_sqrt(iVar12);
        iVar12 = iVar13 >> (uVar5 & 0x1f);
        if ((int)uVar5 < 1) {
          iVar12 = iVar13 << (ulong)(uVar19 & 0x1f);
        }
        *(int *)(param_3 + uVar23 * 4) = iVar12 + 1;
        lVar17 = uVar23 * 2;
        uVar23 = uVar23 + 1;
        iVar12 = (int)*(short *)((long)puVar2 + lVar17);
        if (uVar23 == uVar22) goto LAB_00103000;
      }
      *(undefined4 *)(param_3 + uVar23 * 4) = 1;
      uVar23 = uVar23 + 1;
      iVar12 = (int)sVar3;
    } while (uVar23 != uVar22);
LAB_00103000:
    if (0 < (int)param_4) {
      uVar23 = 0;
      lVar17 = param_2 + (long)iVar4 * 4;
      iVar12 = (int)*(short *)(*(long *)(param_1 + 0x10) + (long)*(int *)(param_1 + 8) * 2 + -2) <<
               3;
      do {
        while( true ) {
          sVar3 = *(short *)((long)puVar2 + uVar23 * 2);
          lVar14 = (long)iVar12;
          iVar12 = 0;
          lVar24 = lVar14;
          do {
            iVar13 = *(int *)(lVar17 + lVar24 * 4);
            lVar24 = lVar24 + 1;
            if (iVar12 <= iVar13) {
              iVar12 = iVar13;
            }
            if (iVar12 <= -iVar13) {
              iVar12 = -iVar13;
            }
          } while (lVar24 < sVar3);
          if (iVar12 < 1) break;
          iVar12 = ec_ilog();
          lVar15 = (long)*(short *)((long)puVar2 + uVar23 * 2);
          iVar12 = iVar12 * 0x10000 + -0x10000 >> 0x10;
          uVar19 = iVar12 - 10;
          uVar5 = 10 - iVar12;
          lVar24 = lVar14 + 1;
          if ((int)uVar19 < 1) {
            if (lVar24 <= lVar15) {
              lVar24 = lVar15;
            }
            uVar16 = lVar24 - lVar14;
            if (uVar16 < 8) {
              iVar12 = 0;
            }
            else {
              uVar18 = uVar16 & 0xfffffffffffffff8;
              iVar12 = 0;
              iVar13 = 0;
              iVar25 = 0;
              iVar26 = 0;
              lVar24 = iVar4 + lVar14;
              lVar14 = uVar18 + lVar14;
              pauVar20 = (undefined1 (*) [16])(param_2 + 0x10 + lVar24 * 4);
              iVar27 = 0;
              iVar28 = 0;
              iVar29 = 0;
              iVar30 = 0;
              uVar21 = uVar18;
              do {
                pauVar1 = pauVar20 + -1;
                auVar32 = *pauVar20;
                uVar21 = uVar21 - 8;
                pauVar20 = pauVar20 + 2;
                auVar6._4_4_ = uVar5;
                auVar6._0_4_ = uVar5;
                auVar6._8_4_ = uVar5;
                auVar6._12_4_ = uVar5;
                auVar31 = NEON_ushl(*pauVar1,auVar6,4);
                auVar7._4_4_ = uVar5;
                auVar7._0_4_ = uVar5;
                auVar7._8_4_ = uVar5;
                auVar7._12_4_ = uVar5;
                auVar32 = NEON_ushl(auVar32,auVar7,4);
                iVar12 = iVar12 + (int)auVar31._0_2_ * (int)auVar31._0_2_;
                iVar13 = iVar13 + (int)auVar31._4_2_ * (int)auVar31._4_2_;
                iVar25 = iVar25 + (int)auVar31._8_2_ * (int)auVar31._8_2_;
                iVar26 = iVar26 + (int)auVar31._12_2_ * (int)auVar31._12_2_;
                iVar27 = iVar27 + (int)auVar32._0_2_ * (int)auVar32._0_2_;
                iVar28 = iVar28 + (int)auVar32._4_2_ * (int)auVar32._4_2_;
                iVar29 = iVar29 + (int)auVar32._8_2_ * (int)auVar32._8_2_;
                iVar30 = iVar30 + (int)auVar32._12_2_ * (int)auVar32._12_2_;
              } while (uVar21 != 0);
              iVar12 = iVar27 + iVar12 + iVar28 + iVar13 + iVar29 + iVar25 + iVar30 + iVar26;
              if (uVar16 == uVar18) goto LAB_0010320c;
            }
            do {
              lVar24 = lVar14 * 4;
              lVar14 = lVar14 + 1;
              iVar13 = (int)(short)(*(int *)(lVar17 + lVar24) << (ulong)(uVar5 & 0x1f));
              iVar12 = iVar12 + iVar13 * iVar13;
            } while (lVar14 < lVar15);
          }
          else {
            if (lVar24 <= lVar15) {
              lVar24 = lVar15;
            }
            uVar16 = lVar24 - lVar14;
            if (uVar16 < 8) {
              iVar12 = 0;
            }
            else {
              uVar18 = uVar16 & 0xfffffffffffffff8;
              iVar12 = 0;
              iVar13 = 0;
              iVar25 = 0;
              iVar26 = 0;
              lVar24 = iVar4 + lVar14;
              lVar14 = uVar18 + lVar14;
              pauVar20 = (undefined1 (*) [16])(param_2 + 0x10 + lVar24 * 4);
              iVar27 = 0;
              iVar28 = 0;
              iVar29 = 0;
              iVar30 = 0;
              uVar21 = uVar18;
              do {
                pauVar1 = pauVar20 + -1;
                auVar32 = *pauVar20;
                uVar21 = uVar21 - 8;
                pauVar20 = pauVar20 + 2;
                auVar8._4_4_ = -uVar19;
                auVar8._0_4_ = -uVar19;
                auVar8._8_4_ = -uVar19;
                auVar8._12_4_ = -uVar19;
                auVar31 = NEON_sshl(*pauVar1,auVar8,4);
                auVar9._4_4_ = -uVar19;
                auVar9._0_4_ = -uVar19;
                auVar9._8_4_ = -uVar19;
                auVar9._12_4_ = -uVar19;
                auVar32 = NEON_sshl(auVar32,auVar9,4);
                iVar12 = iVar12 + (int)auVar31._0_2_ * (int)auVar31._0_2_;
                iVar13 = iVar13 + (int)auVar31._4_2_ * (int)auVar31._4_2_;
                iVar25 = iVar25 + (int)auVar31._8_2_ * (int)auVar31._8_2_;
                iVar26 = iVar26 + (int)auVar31._12_2_ * (int)auVar31._12_2_;
                iVar27 = iVar27 + (int)auVar32._0_2_ * (int)auVar32._0_2_;
                iVar28 = iVar28 + (int)auVar32._4_2_ * (int)auVar32._4_2_;
                iVar29 = iVar29 + (int)auVar32._8_2_ * (int)auVar32._8_2_;
                iVar30 = iVar30 + (int)auVar32._12_2_ * (int)auVar32._12_2_;
              } while (uVar21 != 0);
              iVar12 = iVar27 + iVar12 + iVar28 + iVar13 + iVar29 + iVar25 + iVar30 + iVar26;
              if (uVar16 == uVar18) goto LAB_0010320c;
            }
            do {
              lVar24 = lVar14 * 4;
              lVar14 = lVar14 + 1;
              iVar13 = (int)(short)(*(int *)(lVar17 + lVar24) >> (uVar19 & 0x1f));
              iVar12 = iVar12 + iVar13 * iVar13;
            } while (lVar14 < lVar15);
          }
LAB_0010320c:
          iVar13 = ssc_sqrt(iVar12);
          iVar12 = iVar13 >> (uVar5 & 0x1f);
          if ((int)uVar5 < 1) {
            iVar12 = iVar13 << (ulong)(uVar19 & 0x1f);
          }
          *(int *)(param_3 + (long)(int)((int)uVar23 + param_4) * 4) = iVar12 + 1;
          lVar24 = uVar23 * 2;
          uVar23 = uVar23 + 1;
          iVar12 = (int)*(short *)((long)puVar2 + lVar24);
          if (uVar23 == uVar22) {
            return;
          }
        }
        *(undefined4 *)(param_3 + (long)(int)((int)uVar23 + param_4) * 4) = 1;
        uVar23 = uVar23 + 1;
        iVar12 = (int)sVar3;
      } while (uVar23 != uVar22);
    }
  }
  return;
}


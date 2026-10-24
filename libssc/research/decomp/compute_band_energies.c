/* compute_band_energies @ 00102908 size 1152 */

void compute_band_energies(long param_1,long param_2,long param_3,uint param_4)

{
  undefined1 (*pauVar1) [16];
  ulong uVar2;
  uint uVar3;
  uint uVar4;
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  int iVar11;
  int iVar12;
  long lVar13;
  long lVar14;
  ulong uVar15;
  ulong uVar16;
  ulong uVar17;
  long lVar18;
  ulong uVar19;
  long lVar20;
  ulong uVar21;
  undefined1 (*pauVar22) [16];
  long lVar23;
  ulong uVar24;
  int iVar25;
  int iVar26;
  int iVar27;
  int iVar28;
  int iVar29;
  int iVar30;
  undefined1 auVar31 [16];
  undefined1 auVar32 [16];
  
  if (0 < (int)param_4) {
    lVar23 = *(long *)(param_1 + 0x10);
    lVar13 = (long)(*(int *)(param_1 + 0x1c) << 3);
    uVar24 = 0;
    do {
      while( true ) {
        uVar2 = uVar24 + 1;
        iVar11 = 0;
        lVar14 = (long)*(short *)(lVar23 + uVar24 * 2) << 3;
        do {
          iVar12 = *(int *)(param_2 + lVar14 * 4);
          lVar14 = lVar14 + 1;
          if (iVar11 <= iVar12) {
            iVar11 = iVar12;
          }
          if (iVar11 <= -iVar12) {
            iVar11 = -iVar12;
          }
        } while (lVar14 < (long)*(short *)(lVar23 + uVar2 * 2) * 8);
        if (iVar11 < 1) break;
        iVar11 = ec_ilog();
        lVar18 = (long)*(short *)(lVar23 + uVar24 * 2);
        iVar11 = iVar11 * 0x10000 + -0x10000 >> 0x10;
        uVar3 = iVar11 - 10;
        uVar4 = 10 - iVar11;
        lVar14 = lVar18 * 8;
        uVar15 = (long)*(short *)(lVar23 + uVar2 * 2) * 8;
        uVar17 = lVar18 << 3 | 1;
        if ((int)uVar3 < 1) {
          if ((long)uVar17 <= (long)uVar15) {
            uVar17 = uVar15;
          }
          uVar17 = uVar17 + lVar18 * -8;
          if (uVar17 < 8) {
            iVar11 = 0;
          }
          else {
            uVar19 = uVar17 & 0xfffffffffffffff8;
            pauVar22 = (undefined1 (*) [16])(param_2 + 0x10 + lVar18 * 0x20);
            iVar11 = 0;
            iVar12 = 0;
            iVar25 = 0;
            iVar26 = 0;
            lVar14 = uVar19 + lVar14;
            iVar27 = 0;
            iVar28 = 0;
            iVar29 = 0;
            iVar30 = 0;
            uVar16 = uVar19;
            do {
              pauVar1 = pauVar22 + -1;
              auVar9 = *pauVar22;
              uVar16 = uVar16 - 8;
              pauVar22 = pauVar22 + 2;
              auVar32._4_4_ = uVar4;
              auVar32._0_4_ = uVar4;
              auVar32._8_4_ = uVar4;
              auVar32._12_4_ = uVar4;
              auVar32 = NEON_ushl(*pauVar1,auVar32,4);
              auVar31._4_4_ = uVar4;
              auVar31._0_4_ = uVar4;
              auVar31._8_4_ = uVar4;
              auVar31._12_4_ = uVar4;
              auVar31 = NEON_ushl(auVar9,auVar31,4);
              iVar11 = iVar11 + (int)auVar32._0_2_ * (int)auVar32._0_2_;
              iVar12 = iVar12 + (int)auVar32._4_2_ * (int)auVar32._4_2_;
              iVar25 = iVar25 + (int)auVar32._8_2_ * (int)auVar32._8_2_;
              iVar26 = iVar26 + (int)auVar32._12_2_ * (int)auVar32._12_2_;
              iVar27 = iVar27 + (int)auVar31._0_2_ * (int)auVar31._0_2_;
              iVar28 = iVar28 + (int)auVar31._4_2_ * (int)auVar31._4_2_;
              iVar29 = iVar29 + (int)auVar31._8_2_ * (int)auVar31._8_2_;
              iVar30 = iVar30 + (int)auVar31._12_2_ * (int)auVar31._12_2_;
            } while (uVar16 != 0);
            iVar11 = iVar27 + iVar11 + iVar28 + iVar12 + iVar29 + iVar25 + iVar30 + iVar26;
            if (uVar17 == uVar19) goto LAB_00102b30;
          }
          do {
            lVar18 = lVar14 * 4;
            lVar14 = lVar14 + 1;
            iVar12 = (int)(short)(*(int *)(param_2 + lVar18) << (ulong)(uVar4 & 0x1f));
            iVar11 = iVar11 + iVar12 * iVar12;
          } while (lVar14 < (long)uVar15);
        }
        else {
          if ((long)uVar17 <= (long)uVar15) {
            uVar17 = uVar15;
          }
          uVar17 = uVar17 + lVar18 * -8;
          if (uVar17 < 8) {
            iVar11 = 0;
          }
          else {
            uVar19 = uVar17 & 0xfffffffffffffff8;
            pauVar22 = (undefined1 (*) [16])(param_2 + 0x10 + lVar18 * 0x20);
            iVar11 = 0;
            iVar12 = 0;
            iVar25 = 0;
            iVar26 = 0;
            lVar14 = uVar19 + lVar14;
            iVar27 = 0;
            iVar28 = 0;
            iVar29 = 0;
            iVar30 = 0;
            uVar16 = uVar19;
            do {
              pauVar1 = pauVar22 + -1;
              auVar32 = *pauVar22;
              uVar16 = uVar16 - 8;
              pauVar22 = pauVar22 + 2;
              auVar9._4_4_ = -uVar3;
              auVar9._0_4_ = -uVar3;
              auVar9._8_4_ = -uVar3;
              auVar9._12_4_ = -uVar3;
              auVar31 = NEON_sshl(*pauVar1,auVar9,4);
              auVar10._4_4_ = -uVar3;
              auVar10._0_4_ = -uVar3;
              auVar10._8_4_ = -uVar3;
              auVar10._12_4_ = -uVar3;
              auVar32 = NEON_sshl(auVar32,auVar10,4);
              iVar11 = iVar11 + (int)auVar31._0_2_ * (int)auVar31._0_2_;
              iVar12 = iVar12 + (int)auVar31._4_2_ * (int)auVar31._4_2_;
              iVar25 = iVar25 + (int)auVar31._8_2_ * (int)auVar31._8_2_;
              iVar26 = iVar26 + (int)auVar31._12_2_ * (int)auVar31._12_2_;
              iVar27 = iVar27 + (int)auVar32._0_2_ * (int)auVar32._0_2_;
              iVar28 = iVar28 + (int)auVar32._4_2_ * (int)auVar32._4_2_;
              iVar29 = iVar29 + (int)auVar32._8_2_ * (int)auVar32._8_2_;
              iVar30 = iVar30 + (int)auVar32._12_2_ * (int)auVar32._12_2_;
            } while (uVar16 != 0);
            iVar11 = iVar27 + iVar11 + iVar28 + iVar12 + iVar29 + iVar25 + iVar30 + iVar26;
            if (uVar17 == uVar19) goto LAB_00102b30;
          }
          do {
            lVar18 = lVar14 * 4;
            lVar14 = lVar14 + 1;
            iVar12 = (int)(short)(*(int *)(param_2 + lVar18) >> (uVar3 & 0x1f));
            iVar11 = iVar11 + iVar12 * iVar12;
          } while (lVar14 < (long)uVar15);
        }
LAB_00102b30:
        iVar12 = ssc_sqrt(iVar11);
        iVar11 = iVar12 >> (uVar4 & 0x1f);
        if ((int)uVar4 < 1) {
          iVar11 = iVar12 << (ulong)(uVar3 & 0x1f);
        }
        *(int *)(param_3 + (-(uVar24 >> 0x1f & 1) & 0xfffffffc00000000 | (uVar24 & 0xffffffff) << 2)
                ) = iVar11 + 1;
        uVar24 = uVar2;
        if (uVar2 == param_4) goto LAB_00102b58;
      }
      *(undefined4 *)
       (param_3 + (-(uVar24 >> 0x1f & 1) & 0xfffffffc00000000 | (uVar24 & 0xffffffff) << 2)) = 1;
      uVar24 = uVar2;
    } while (uVar2 != param_4);
LAB_00102b58:
    lVar14 = param_2 + lVar13 * 4;
    uVar24 = 0;
    do {
      uVar17 = uVar24 + 1;
      iVar11 = 0;
      lVar18 = (long)*(short *)(lVar23 + uVar24 * 2) << 3;
      do {
        iVar12 = *(int *)(lVar14 + lVar18 * 4);
        lVar18 = lVar18 + 1;
        if (iVar11 <= iVar12) {
          iVar11 = iVar12;
        }
        if (iVar11 <= -iVar12) {
          iVar11 = -iVar12;
        }
      } while (lVar18 < (long)*(short *)(lVar23 + uVar17 * 2) * 8);
      if (iVar11 < 1) {
        iVar11 = 1;
      }
      else {
        iVar11 = ec_ilog();
        lVar20 = (long)*(short *)(lVar23 + uVar24 * 2);
        iVar11 = iVar11 * 0x10000 + -0x10000 >> 0x10;
        uVar3 = iVar11 - 10;
        uVar4 = 10 - iVar11;
        lVar18 = lVar20 * 8;
        uVar16 = (long)*(short *)(lVar23 + uVar17 * 2) * 8;
        uVar15 = lVar20 << 3 | 1;
        if ((int)uVar3 < 1) {
          if ((long)uVar15 <= (long)uVar16) {
            uVar15 = uVar16;
          }
          uVar15 = uVar15 + lVar20 * -8;
          if (uVar15 < 8) {
            iVar11 = 0;
          }
          else {
            uVar21 = uVar15 & 0xfffffffffffffff8;
            iVar11 = 0;
            iVar12 = 0;
            iVar25 = 0;
            iVar26 = 0;
            lVar20 = lVar13 + lVar18;
            lVar18 = uVar21 + lVar18;
            pauVar22 = (undefined1 (*) [16])(param_2 + 0x10 + lVar20 * 4);
            iVar27 = 0;
            iVar28 = 0;
            iVar29 = 0;
            iVar30 = 0;
            uVar19 = uVar21;
            do {
              pauVar1 = pauVar22 + -1;
              auVar32 = *pauVar22;
              uVar19 = uVar19 - 8;
              pauVar22 = pauVar22 + 2;
              auVar5._4_4_ = uVar4;
              auVar5._0_4_ = uVar4;
              auVar5._8_4_ = uVar4;
              auVar5._12_4_ = uVar4;
              auVar31 = NEON_ushl(*pauVar1,auVar5,4);
              auVar6._4_4_ = uVar4;
              auVar6._0_4_ = uVar4;
              auVar6._8_4_ = uVar4;
              auVar6._12_4_ = uVar4;
              auVar32 = NEON_ushl(auVar32,auVar6,4);
              iVar11 = iVar11 + (int)auVar31._0_2_ * (int)auVar31._0_2_;
              iVar12 = iVar12 + (int)auVar31._4_2_ * (int)auVar31._4_2_;
              iVar25 = iVar25 + (int)auVar31._8_2_ * (int)auVar31._8_2_;
              iVar26 = iVar26 + (int)auVar31._12_2_ * (int)auVar31._12_2_;
              iVar27 = iVar27 + (int)auVar32._0_2_ * (int)auVar32._0_2_;
              iVar28 = iVar28 + (int)auVar32._4_2_ * (int)auVar32._4_2_;
              iVar29 = iVar29 + (int)auVar32._8_2_ * (int)auVar32._8_2_;
              iVar30 = iVar30 + (int)auVar32._12_2_ * (int)auVar32._12_2_;
            } while (uVar19 != 0);
            iVar11 = iVar27 + iVar11 + iVar28 + iVar12 + iVar29 + iVar25 + iVar30 + iVar26;
            if (uVar15 == uVar21) goto LAB_00102d3c;
          }
          do {
            lVar20 = lVar18 * 4;
            lVar18 = lVar18 + 1;
            iVar12 = (int)(short)(*(int *)(lVar14 + lVar20) << (ulong)(uVar4 & 0x1f));
            iVar11 = iVar11 + iVar12 * iVar12;
          } while (lVar18 < (long)uVar16);
        }
        else {
          if ((long)uVar15 <= (long)uVar16) {
            uVar15 = uVar16;
          }
          uVar15 = uVar15 + lVar20 * -8;
          if (uVar15 < 8) {
            iVar11 = 0;
          }
          else {
            uVar21 = uVar15 & 0xfffffffffffffff8;
            iVar11 = 0;
            iVar12 = 0;
            iVar25 = 0;
            iVar26 = 0;
            lVar20 = lVar13 + lVar18;
            lVar18 = uVar21 + lVar18;
            pauVar22 = (undefined1 (*) [16])(param_2 + 0x10 + lVar20 * 4);
            iVar27 = 0;
            iVar28 = 0;
            iVar29 = 0;
            iVar30 = 0;
            uVar19 = uVar21;
            do {
              pauVar1 = pauVar22 + -1;
              auVar32 = *pauVar22;
              uVar19 = uVar19 - 8;
              pauVar22 = pauVar22 + 2;
              auVar7._4_4_ = -uVar3;
              auVar7._0_4_ = -uVar3;
              auVar7._8_4_ = -uVar3;
              auVar7._12_4_ = -uVar3;
              auVar31 = NEON_sshl(*pauVar1,auVar7,4);
              auVar8._4_4_ = -uVar3;
              auVar8._0_4_ = -uVar3;
              auVar8._8_4_ = -uVar3;
              auVar8._12_4_ = -uVar3;
              auVar32 = NEON_sshl(auVar32,auVar8,4);
              iVar11 = iVar11 + (int)auVar31._0_2_ * (int)auVar31._0_2_;
              iVar12 = iVar12 + (int)auVar31._4_2_ * (int)auVar31._4_2_;
              iVar25 = iVar25 + (int)auVar31._8_2_ * (int)auVar31._8_2_;
              iVar26 = iVar26 + (int)auVar31._12_2_ * (int)auVar31._12_2_;
              iVar27 = iVar27 + (int)auVar32._0_2_ * (int)auVar32._0_2_;
              iVar28 = iVar28 + (int)auVar32._4_2_ * (int)auVar32._4_2_;
              iVar29 = iVar29 + (int)auVar32._8_2_ * (int)auVar32._8_2_;
              iVar30 = iVar30 + (int)auVar32._12_2_ * (int)auVar32._12_2_;
            } while (uVar19 != 0);
            iVar11 = iVar27 + iVar11 + iVar28 + iVar12 + iVar29 + iVar25 + iVar30 + iVar26;
            if (uVar15 == uVar21) goto LAB_00102d3c;
          }
          do {
            lVar20 = lVar18 * 4;
            lVar18 = lVar18 + 1;
            iVar12 = (int)(short)(*(int *)(lVar14 + lVar20) >> (uVar3 & 0x1f));
            iVar11 = iVar11 + iVar12 * iVar12;
          } while (lVar18 < (long)uVar16);
        }
LAB_00102d3c:
        iVar12 = ssc_sqrt(iVar11);
        iVar11 = iVar12 >> (uVar4 & 0x1f);
        if ((int)uVar4 < 1) {
          iVar11 = iVar12 << (ulong)(uVar3 & 0x1f);
        }
        iVar11 = iVar11 + 1;
      }
      *(int *)(param_3 + (long)(*(int *)(param_1 + 8) + (int)uVar24) * 4) = iVar11;
      uVar24 = uVar17;
    } while (uVar17 != uVar2);
  }
  return;
}


/* ssc_compute_band_energies @ 0010776c size 588 */

void ssc_compute_band_energies(long param_1,long param_2,long param_3,uint param_4)

{
  undefined1 (*pauVar1) [16];
  ulong uVar2;
  uint uVar3;
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 (*pauVar10) [16];
  undefined1 *puVar11;
  undefined1 *puVar12;
  undefined1 *puVar13;
  undefined1 *puVar14;
  long lVar15;
  long lVar16;
  undefined1 (*pauVar17) [16];
  long lVar18;
  undefined1 (*pauVar19) [16];
  long lVar20;
  ulong uVar21;
  uint uVar22;
  int iVar23;
  int iVar26;
  int iVar27;
  int iVar28;
  undefined1 auVar24 [16];
  undefined1 auVar25 [16];
  int iVar29;
  int iVar30;
  undefined4 uVar31;
  undefined4 uVar32;
  undefined4 uVar33;
  undefined4 uVar34;
  
  if (0 < (int)param_4) {
    lVar20 = *(long *)(param_1 + 0x10);
    uVar21 = 0;
    do {
      uVar2 = uVar21 + 1;
      auVar25 = ZEXT816(0);
      lVar16 = (long)*(short *)(lVar20 + uVar21 * 2);
      lVar15 = lVar16 << 3;
      pauVar17 = (undefined1 (*) [16])(param_2 + 0x10 + lVar16 * 0x20);
      lVar18 = (long)*(short *)(lVar20 + uVar2 * 2) * 8;
      pauVar19 = pauVar17;
      lVar16 = lVar15;
      do {
        pauVar1 = pauVar19 + -1;
        pauVar10 = pauVar19 + -1;
        puVar11 = *pauVar19;
        puVar12 = *pauVar19;
        puVar13 = *pauVar19;
        puVar14 = *pauVar19;
        lVar16 = lVar16 + 8;
        pauVar19 = pauVar19 + 2;
        uVar31 = MP_INT_ABS((int)*(undefined8 *)*pauVar1);
        uVar32 = MP_INT_ABS((int)((ulong)*(undefined8 *)*pauVar1 >> 0x20));
        uVar33 = MP_INT_ABS((int)*(undefined8 *)(*pauVar10 + 8));
        uVar34 = MP_INT_ABS((int)((ulong)*(undefined8 *)(*pauVar10 + 8) >> 0x20));
        auVar24._4_4_ = uVar32;
        auVar24._0_4_ = uVar31;
        auVar24._8_4_ = uVar33;
        auVar24._12_4_ = uVar34;
        auVar24 = NEON_smax(auVar25,auVar24,4);
        uVar31 = MP_INT_ABS(*(undefined4 *)puVar11);
        uVar32 = MP_INT_ABS(*(undefined4 *)(puVar12 + 4));
        uVar33 = MP_INT_ABS(*(undefined4 *)(puVar13 + 8));
        uVar34 = MP_INT_ABS(*(undefined4 *)(puVar14 + 0xc));
        auVar25._4_4_ = uVar32;
        auVar25._0_4_ = uVar31;
        auVar25._8_4_ = uVar33;
        auVar25._12_4_ = uVar34;
        auVar25 = NEON_smax(auVar24,auVar25,4);
      } while (lVar16 < lVar18);
      uVar22 = NEON_smaxv(auVar25,4);
      if ((int)uVar22 < 1) {
        iVar23 = 1;
      }
      else {
        uVar3 = (int)LZCOUNT(uVar22) - 0x15;
        iVar23 = 0;
        iVar26 = 0;
        iVar27 = 0;
        iVar29 = 0;
        do {
          pauVar19 = pauVar17 + -1;
          auVar25 = *pauVar17;
          lVar15 = lVar15 + 8;
          pauVar17 = pauVar17 + 2;
          auVar4._4_4_ = uVar3;
          auVar4._0_4_ = uVar3;
          auVar4._8_4_ = uVar3;
          auVar4._12_4_ = uVar3;
          auVar24 = NEON_sshl(*pauVar19,auVar4,4);
          auVar5._4_4_ = uVar3;
          auVar5._0_4_ = uVar3;
          auVar5._8_4_ = uVar3;
          auVar5._12_4_ = uVar3;
          auVar25 = NEON_sshl(auVar25,auVar5,4);
          iVar23 = iVar23 + (int)auVar24._0_2_ * (int)auVar24._0_2_ +
                   (int)auVar25._0_2_ * (int)auVar25._0_2_;
          iVar26 = iVar26 + (int)auVar24._4_2_ * (int)auVar24._4_2_ +
                   (int)auVar25._4_2_ * (int)auVar25._4_2_;
          iVar27 = iVar27 + (int)auVar24._8_2_ * (int)auVar24._8_2_ +
                   (int)auVar25._8_2_ * (int)auVar25._8_2_;
          iVar29 = iVar29 + (int)auVar24._12_2_ * (int)auVar24._12_2_ +
                   (int)auVar25._12_2_ * (int)auVar25._12_2_;
        } while (lVar15 < lVar18);
        iVar23 = iVar23 + iVar26 + iVar27 + iVar29;
        if (uVar22 < 0x400) {
          iVar23 = ssc_sqrt(iVar23);
          iVar23 = iVar23 >> (uVar3 & 0x1f);
        }
        else {
          iVar23 = ssc_sqrt(iVar23);
          iVar23 = iVar23 << (ulong)(0x15U - (int)LZCOUNT(uVar22) & 0x1f);
        }
        iVar23 = iVar23 + 1;
      }
      *(int *)(param_3 + uVar21 * 4) = iVar23;
      uVar21 = uVar2;
    } while (uVar2 != param_4);
    iVar23 = *(int *)(param_1 + 0x1c);
    iVar26 = *(int *)(param_1 + 8);
    lVar20 = *(long *)(param_1 + 0x10);
    uVar21 = 0;
    do {
      uVar2 = uVar21 + 1;
      auVar25 = ZEXT816(0);
      lVar16 = (long)*(short *)(lVar20 + uVar21 * 2);
      lVar15 = lVar16 << 3;
      pauVar17 = (undefined1 (*) [16])(param_2 + (long)(iVar23 << 3) * 4 + 0x10 + lVar16 * 0x20);
      lVar18 = (long)*(short *)(lVar20 + uVar2 * 2) * 8;
      pauVar19 = pauVar17;
      lVar16 = lVar15;
      do {
        pauVar1 = pauVar19 + -1;
        pauVar10 = pauVar19 + -1;
        puVar11 = *pauVar19;
        puVar12 = *pauVar19;
        puVar13 = *pauVar19;
        puVar14 = *pauVar19;
        lVar16 = lVar16 + 8;
        pauVar19 = pauVar19 + 2;
        uVar31 = MP_INT_ABS((int)*(undefined8 *)*pauVar1);
        uVar32 = MP_INT_ABS((int)((ulong)*(undefined8 *)*pauVar1 >> 0x20));
        uVar33 = MP_INT_ABS((int)*(undefined8 *)(*pauVar10 + 8));
        uVar34 = MP_INT_ABS((int)((ulong)*(undefined8 *)(*pauVar10 + 8) >> 0x20));
        auVar6._4_4_ = uVar32;
        auVar6._0_4_ = uVar31;
        auVar6._8_4_ = uVar33;
        auVar6._12_4_ = uVar34;
        auVar25 = NEON_smax(auVar25,auVar6,4);
        uVar31 = MP_INT_ABS(*(undefined4 *)puVar11);
        uVar32 = MP_INT_ABS(*(undefined4 *)(puVar12 + 4));
        uVar33 = MP_INT_ABS(*(undefined4 *)(puVar13 + 8));
        uVar34 = MP_INT_ABS(*(undefined4 *)(puVar14 + 0xc));
        auVar7._4_4_ = uVar32;
        auVar7._0_4_ = uVar31;
        auVar7._8_4_ = uVar33;
        auVar7._12_4_ = uVar34;
        auVar25 = NEON_smax(auVar25,auVar7,4);
      } while (lVar16 < lVar18);
      uVar22 = NEON_smaxv(auVar25,4);
      if ((int)uVar22 < 1) {
        iVar27 = 1;
      }
      else {
        uVar3 = (int)LZCOUNT(uVar22) - 0x15;
        iVar27 = 0;
        iVar29 = 0;
        iVar28 = 0;
        iVar30 = 0;
        do {
          pauVar19 = pauVar17 + -1;
          auVar25 = *pauVar17;
          lVar15 = lVar15 + 8;
          pauVar17 = pauVar17 + 2;
          auVar8._4_4_ = uVar3;
          auVar8._0_4_ = uVar3;
          auVar8._8_4_ = uVar3;
          auVar8._12_4_ = uVar3;
          auVar24 = NEON_sshl(*pauVar19,auVar8,4);
          auVar9._4_4_ = uVar3;
          auVar9._0_4_ = uVar3;
          auVar9._8_4_ = uVar3;
          auVar9._12_4_ = uVar3;
          auVar25 = NEON_sshl(auVar25,auVar9,4);
          iVar27 = iVar27 + (int)auVar24._0_2_ * (int)auVar24._0_2_ +
                   (int)auVar25._0_2_ * (int)auVar25._0_2_;
          iVar29 = iVar29 + (int)auVar24._4_2_ * (int)auVar24._4_2_ +
                   (int)auVar25._4_2_ * (int)auVar25._4_2_;
          iVar28 = iVar28 + (int)auVar24._8_2_ * (int)auVar24._8_2_ +
                   (int)auVar25._8_2_ * (int)auVar25._8_2_;
          iVar30 = iVar30 + (int)auVar24._12_2_ * (int)auVar24._12_2_ +
                   (int)auVar25._12_2_ * (int)auVar25._12_2_;
        } while (lVar15 < lVar18);
        iVar27 = iVar27 + iVar29 + iVar28 + iVar30;
        if (uVar22 < 0x400) {
          iVar27 = ssc_sqrt(iVar27);
          iVar27 = iVar27 >> (uVar3 & 0x1f);
        }
        else {
          iVar27 = ssc_sqrt(iVar27);
          iVar27 = iVar27 << (ulong)(0x15U - (int)LZCOUNT(uVar22) & 0x1f);
        }
        iVar27 = iVar27 + 1;
      }
      *(int *)(param_3 + (long)iVar26 * 4 + uVar21 * 4) = iVar27;
      uVar21 = uVar2;
    } while (uVar2 != param_4);
  }
  return;
}


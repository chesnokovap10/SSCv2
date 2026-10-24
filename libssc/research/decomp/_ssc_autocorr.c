/* _ssc_autocorr @ 00111044 size 812 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint _ssc_autocorr(undefined2 *param_1,uint *param_2)

{
  long lVar1;
  uint uVar2;
  short *psVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  uint uVar8;
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  uint uVar11;
  long lVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  int iVar24;
  int iVar28;
  int iVar29;
  int iVar30;
  undefined1 auVar25 [16];
  undefined1 auVar26 [16];
  undefined1 auVar27 [16];
  undefined1 auVar31 [16];
  undefined1 auVar32 [16];
  undefined1 auVar33 [16];
  undefined1 auVar34 [16];
  undefined1 auVar35 [16];
  undefined1 auVar36 [16];
  undefined1 auVar37 [16];
  
  iVar17 = 0;
  iVar18 = 0;
  iVar19 = 0;
  iVar20 = 0;
  iVar21 = 0;
  iVar22 = 0;
  iVar23 = 0;
  iVar24 = 0;
  lVar12 = 0;
  auVar32 = ZEXT816(0);
  auVar26 = _DAT_001027e0;
  do {
    psVar3 = (short *)((long)param_1 + lVar12);
    lVar12 = lVar12 + 0x40;
    iVar28 = auVar26._4_4_;
    iVar29 = auVar26._8_4_;
    iVar30 = auVar26._12_4_;
    auVar26._0_4_ =
         auVar26._0_4_ + ((uint)((int)*psVar3 * (int)*psVar3) >> 9) +
         ((uint)((int)psVar3[1] * (int)psVar3[1]) >> 9);
    auVar26._4_4_ =
         iVar28 + ((uint)((int)psVar3[2] * (int)psVar3[2]) >> 9) +
         ((uint)((int)psVar3[3] * (int)psVar3[3]) >> 9);
    auVar26._8_4_ =
         iVar29 + ((uint)((int)psVar3[4] * (int)psVar3[4]) >> 9) +
         ((uint)((int)psVar3[5] * (int)psVar3[5]) >> 9);
    auVar26._12_4_ =
         iVar30 + ((uint)((int)psVar3[6] * (int)psVar3[6]) >> 9) +
         ((uint)((int)psVar3[7] * (int)psVar3[7]) >> 9);
    iVar17 = iVar17 + ((uint)((int)psVar3[8] * (int)psVar3[8]) >> 9) +
             ((uint)((int)psVar3[9] * (int)psVar3[9]) >> 9);
    iVar18 = iVar18 + ((uint)((int)psVar3[10] * (int)psVar3[10]) >> 9) +
             ((uint)((int)psVar3[0xb] * (int)psVar3[0xb]) >> 9);
    iVar19 = iVar19 + ((uint)((int)psVar3[0xc] * (int)psVar3[0xc]) >> 9) +
             ((uint)((int)psVar3[0xd] * (int)psVar3[0xd]) >> 9);
    iVar20 = iVar20 + ((uint)((int)psVar3[0xe] * (int)psVar3[0xe]) >> 9) +
             ((uint)((int)psVar3[0xf] * (int)psVar3[0xf]) >> 9);
    iVar28 = auVar32._4_4_;
    iVar29 = auVar32._8_4_;
    iVar30 = auVar32._12_4_;
    auVar32._0_4_ =
         auVar32._0_4_ + ((uint)((int)psVar3[0x18] * (int)psVar3[0x18]) >> 9) +
         ((uint)((int)psVar3[0x19] * (int)psVar3[0x19]) >> 9);
    auVar32._4_4_ =
         iVar28 + ((uint)((int)psVar3[0x1a] * (int)psVar3[0x1a]) >> 9) +
         ((uint)((int)psVar3[0x1b] * (int)psVar3[0x1b]) >> 9);
    auVar32._8_4_ =
         iVar29 + ((uint)((int)psVar3[0x1c] * (int)psVar3[0x1c]) >> 9) +
         ((uint)((int)psVar3[0x1d] * (int)psVar3[0x1d]) >> 9);
    auVar32._12_4_ =
         iVar30 + ((uint)((int)psVar3[0x1e] * (int)psVar3[0x1e]) >> 9) +
         ((uint)((int)psVar3[0x1f] * (int)psVar3[0x1f]) >> 9);
    iVar21 = iVar21 + ((uint)((int)psVar3[0x10] * (int)psVar3[0x10]) >> 9) +
             ((uint)((int)psVar3[0x11] * (int)psVar3[0x11]) >> 9);
    iVar22 = iVar22 + ((uint)((int)psVar3[0x12] * (int)psVar3[0x12]) >> 9) +
             ((uint)((int)psVar3[0x13] * (int)psVar3[0x13]) >> 9);
    iVar23 = iVar23 + ((uint)((int)psVar3[0x14] * (int)psVar3[0x14]) >> 9) +
             ((uint)((int)psVar3[0x15] * (int)psVar3[0x15]) >> 9);
    iVar24 = iVar24 + ((uint)((int)psVar3[0x16] * (int)psVar3[0x16]) >> 9) +
             ((uint)((int)psVar3[0x17] * (int)psVar3[0x17]) >> 9);
  } while (lVar12 != 0x740);
  uVar16 = iVar21 + auVar26._0_4_ + auVar32._0_4_ + iVar17 +
           iVar22 + auVar26._4_4_ + auVar32._4_4_ + iVar18 +
           iVar23 + auVar26._8_4_ + auVar32._8_4_ + iVar19 +
           iVar24 + auVar26._12_4_ + auVar32._12_4_ + iVar20 +
           ((uint)((int)(short)param_1[0x3a0] * (int)(short)param_1[0x3a0]) >> 9) +
           ((uint)((int)(short)param_1[0x3a1] * (int)(short)param_1[0x3a1]) >> 9) +
           ((uint)((int)(short)param_1[0x3a2] * (int)(short)param_1[0x3a2]) >> 9) +
           ((uint)((int)(short)param_1[0x3a3] * (int)(short)param_1[0x3a3]) >> 9) +
           ((uint)((int)(short)param_1[0x3a4] * (int)(short)param_1[0x3a4]) >> 9) +
           ((uint)((int)(short)param_1[0x3a5] * (int)(short)param_1[0x3a5]) >> 9) +
           ((uint)((int)(short)param_1[0x3a6] * (int)(short)param_1[0x3a6]) >> 9) +
           ((uint)((int)(short)param_1[0x3a7] * (int)(short)param_1[0x3a7]) >> 9) +
           ((uint)((int)(short)param_1[0x3a8] * (int)(short)param_1[0x3a8]) >> 9) +
           ((uint)((int)(short)param_1[0x3a9] * (int)(short)param_1[0x3a9]) >> 9) +
           ((uint)((int)(short)param_1[0x3aa] * (int)(short)param_1[0x3aa]) >> 9) +
           ((uint)((int)(short)param_1[0x3ab] * (int)(short)param_1[0x3ab]) >> 9) +
           ((uint)((int)(short)param_1[0x3ac] * (int)(short)param_1[0x3ac]) >> 9) +
           ((uint)((int)(short)param_1[0x3ad] * (int)(short)param_1[0x3ad]) >> 9) +
           ((uint)((int)(short)param_1[0x3ae] * (int)(short)param_1[0x3ae]) >> 9) +
           ((uint)((int)(short)param_1[0x3af] * (int)(short)param_1[0x3af]) >> 9);
  if (uVar16 < 0x400000) {
    uVar16 = 0;
  }
  else {
    uVar16 = 0xb - (int)LZCOUNT(uVar16);
    uVar14 = (int)uVar16 >> 1;
    iVar17 = (1 << (ulong)(uVar14 & 0x1f)) >> 1;
    if ((param_1 + 0x3b0 < (undefined2 *)((long)&in_shared + 1)) ||
       ((undefined2 *)((long)&DAT_0012478a + 1) < param_1)) {
      iVar18 = -uVar14;
      iVar19 = -uVar14;
      iVar20 = -uVar14;
      iVar21 = -uVar14;
      lVar12 = 0;
      do {
        psVar3 = (short *)((long)param_1 + lVar12);
        lVar1 = lVar12 + 0x20;
        auVar34._0_4_ = iVar17 + psVar3[4];
        auVar34._4_4_ = iVar17 + psVar3[5];
        auVar34._8_4_ = iVar17 + psVar3[6];
        auVar34._12_4_ = iVar17 + psVar3[7];
        auVar25._0_4_ = iVar17 + *psVar3;
        auVar25._4_4_ = iVar17 + psVar3[1];
        auVar25._8_4_ = iVar17 + psVar3[2];
        auVar25._12_4_ = iVar17 + psVar3[3];
        auVar36._0_4_ = iVar17 + psVar3[0xc];
        auVar36._4_4_ = iVar17 + psVar3[0xd];
        auVar36._8_4_ = iVar17 + psVar3[0xe];
        auVar36._12_4_ = iVar17 + psVar3[0xf];
        auVar31._0_4_ = iVar17 + psVar3[8];
        auVar31._4_4_ = iVar17 + psVar3[9];
        auVar31._8_4_ = iVar17 + psVar3[10];
        auVar31._12_4_ = iVar17 + psVar3[0xb];
        auVar35._4_4_ = iVar19;
        auVar35._0_4_ = iVar18;
        auVar35._8_4_ = iVar20;
        auVar35._12_4_ = iVar21;
        auVar35 = NEON_sshl(auVar34,auVar35,4);
        auVar37._4_4_ = iVar19;
        auVar37._0_4_ = iVar18;
        auVar37._8_4_ = iVar20;
        auVar37._12_4_ = iVar21;
        auVar26 = NEON_sshl(auVar25,auVar37,4);
        auVar9._4_4_ = iVar19;
        auVar9._0_4_ = iVar18;
        auVar9._8_4_ = iVar20;
        auVar9._12_4_ = iVar21;
        auVar37 = NEON_sshl(auVar36,auVar9,4);
        auVar10._4_4_ = iVar19;
        auVar10._0_4_ = iVar18;
        auVar10._8_4_ = iVar20;
        auVar10._12_4_ = iVar21;
        auVar32 = NEON_sshl(auVar31,auVar10,4);
        auVar27._0_8_ =
             CONCAT26(auVar26._12_2_,CONCAT24(auVar26._8_2_,CONCAT22(auVar26._4_2_,auVar26._0_2_)));
        auVar27._8_2_ = auVar35._0_2_;
        auVar27._10_2_ = auVar35._4_2_;
        auVar27._12_2_ = auVar35._8_2_;
        auVar27._14_2_ = auVar35._12_2_;
        auVar33._0_8_ =
             CONCAT26(auVar32._12_2_,CONCAT24(auVar32._8_2_,CONCAT22(auVar32._4_2_,auVar32._0_2_)));
        auVar33._8_2_ = auVar37._0_2_;
        auVar33._10_2_ = auVar37._4_2_;
        auVar33._12_2_ = auVar37._8_2_;
        auVar33._14_2_ = auVar37._12_2_;
        *(long *)((long)&DAT_00124034 + lVar12) = auVar27._8_8_;
        *(undefined8 *)((long)&in_shared + lVar12) = auVar27._0_8_;
        *(long *)(lVar12 + 0x124044) = auVar33._8_8_;
        *(undefined8 *)(&DAT_0012403c + lVar12) = auVar33._0_8_;
        lVar12 = lVar1;
      } while (lVar1 != 0x760);
    }
    else {
      lVar12 = 0;
      do {
        *(short *)((long)&in_shared + lVar12) =
             (short)(iVar17 + *(short *)((long)param_1 + lVar12) >> (uVar14 & 0x1f));
        lVar12 = lVar12 + 2;
      } while (lVar12 != 0x760);
    }
    uVar16 = uVar16 & 0xfffffffe;
    param_1 = &in_shared;
  }
  ssc_pitch_xcorr_c1(param_1,param_1,param_2);
  sVar4 = param_1[0x3ac];
  sVar5 = param_1[0x3ad];
  sVar6 = param_1[0x3ae];
  sVar7 = param_1[0x3af];
  iVar17 = (int)sVar4;
  iVar18 = (int)sVar6;
  iVar19 = (int)sVar7;
  uVar14 = (int)sVar4 * (int)sVar4 + (int)sVar5 * (int)sVar5 + iVar18 * iVar18 + *param_2 +
           iVar19 * iVar19;
  uVar2 = (int)sVar7 * (int)sVar6 + (sVar6 + iVar17) * (int)sVar5 + param_2[1];
  uVar11 = param_2[3] + iVar19 * iVar17;
  uVar13 = iVar18 * iVar17 + (int)sVar7 * (int)sVar5 + param_2[2];
  *param_2 = uVar14;
  param_2[1] = uVar2;
  param_2[2] = uVar13;
  param_2[3] = uVar11;
  if ((int)uVar16 < 1) {
    uVar14 = uVar14 + 1;
    *param_2 = uVar14;
  }
  if ((int)uVar14 < 0x10000000) {
    uVar8 = (int)LZCOUNT(uVar14) - 3;
    uVar15 = -uVar8;
    uVar13 = uVar13 << (ulong)(uVar8 & 0x1f);
    uVar11 = uVar11 << (ulong)(uVar8 & 0x1f);
    *param_2 = uVar14 << (ulong)(uVar8 & 0x1f);
    param_2[1] = uVar2 << (ulong)(uVar8 & 0x1f);
    uVar14 = param_2[4] << (ulong)(uVar8 & 0x1f);
  }
  else {
    if (uVar14 >> 0x1d == 0) {
      return uVar16;
    }
    uVar15 = 1;
    if (uVar14 >> 0x1e != 0) {
      uVar15 = 2;
    }
    uVar13 = (int)uVar13 >> uVar15;
    uVar11 = (int)uVar11 >> uVar15;
    *param_2 = uVar14 >> (ulong)uVar15;
    param_2[1] = (int)uVar2 >> uVar15;
    uVar14 = (int)param_2[4] >> uVar15;
  }
  param_2[2] = uVar13;
  param_2[3] = uVar11;
  param_2[4] = uVar14;
                    /* WARNING: Read-only address (ram,0x001027e0) is written */
  return uVar16 + uVar15;
}


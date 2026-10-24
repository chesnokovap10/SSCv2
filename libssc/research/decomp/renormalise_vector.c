/* renormalise_vector @ 00112d04 size 480 */

void renormalise_vector(short *param_1,uint param_2,short param_3)

{
  ulong uVar1;
  uint uVar2;
  uint uVar3;
  undefined1 auVar4 [16];
  undefined8 uVar5;
  undefined1 auVar6 [16];
  short sVar7;
  int iVar8;
  short *psVar9;
  uint uVar10;
  short *psVar11;
  long lVar12;
  uint uVar13;
  uint uVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  short sVar20;
  undefined2 uVar21;
  short sVar22;
  undefined2 uVar23;
  int iVar24;
  int iVar25;
  undefined8 uVar26;
  undefined1 auVar27 [16];
  undefined1 auVar28 [16];
  undefined1 auVar29 [16];
  undefined1 auVar30 [16];
  undefined1 auVar31 [16];
  undefined1 auVar32 [16];
  
  uVar13 = param_2 - 1;
  if ((int)param_2 < 1) {
    uVar14 = 1;
  }
  else {
    if ((ulong)uVar13 + 1 < 8) {
      uVar14 = 1;
      psVar9 = param_1;
      uVar10 = uVar13;
    }
    else {
      iVar16 = 0;
      iVar24 = 0;
      iVar8 = 1;
      iVar15 = 0;
      lVar12 = ((ulong)uVar13 + 1) - (ulong)(param_2 & 7);
      psVar9 = param_1 + lVar12;
      uVar10 = uVar13 - (int)lVar12;
      psVar11 = param_1 + 4;
      iVar25 = 0;
      iVar17 = 0;
      iVar18 = 0;
      iVar19 = 0;
      do {
        uVar5 = *(undefined8 *)(psVar11 + -4);
        sVar7 = (short)((ulong)uVar5 >> 0x10);
        sVar20 = (short)((ulong)uVar5 >> 0x20);
        sVar22 = (short)((ulong)uVar5 >> 0x30);
        uVar26 = *(undefined8 *)psVar11;
        lVar12 = lVar12 + -8;
        psVar11 = psVar11 + 8;
        iVar8 = iVar8 + (int)(short)uVar5 * (int)(short)uVar5;
        iVar15 = iVar15 + (int)sVar7 * (int)sVar7;
        iVar16 = iVar16 + (int)sVar20 * (int)sVar20;
        iVar24 = iVar24 + (int)sVar22 * (int)sVar22;
        sVar7 = (short)((ulong)uVar26 >> 0x10);
        sVar20 = (short)((ulong)uVar26 >> 0x20);
        sVar22 = (short)((ulong)uVar26 >> 0x30);
        iVar25 = iVar25 + (int)(short)uVar26 * (int)(short)uVar26;
        iVar17 = iVar17 + (int)sVar7 * (int)sVar7;
        iVar18 = iVar18 + (int)sVar20 * (int)sVar20;
        iVar19 = iVar19 + (int)sVar22 * (int)sVar22;
      } while (lVar12 != 0);
      uVar14 = iVar25 + iVar8 + iVar17 + iVar15 + iVar18 + iVar16 + iVar19 + iVar24;
      if ((param_2 & 7) == 0) goto LAB_00112db0;
    }
    iVar8 = uVar10 + 1;
    do {
      iVar8 = iVar8 + -1;
      uVar14 = uVar14 + (int)*psVar9 * (int)*psVar9;
      psVar9 = psVar9 + 1;
    } while (0 < iVar8);
  }
LAB_00112db0:
  iVar8 = ec_ilog(uVar14);
  uVar10 = (int)(short)(iVar8 + -1) & 0xfffffffe;
  uVar3 = uVar10 - 0xe;
  uVar2 = uVar14 >> (ulong)(uVar3 & 0x1f);
  if ((int)uVar3 < 1) {
    uVar2 = uVar14 << (ulong)(0xe - uVar10 & 0x1f);
  }
  sVar7 = ssc_rsqrt_norm(uVar2);
  if (0 < (int)param_2) {
    uVar1 = (ulong)(param_2 - 1) + 1;
    uVar14 = ((iVar8 + -1) * 0x10000 >> 0x11) + 1;
    iVar8 = (int)param_3 * (int)sVar7 * 2 + 0x8000 >> 0x10;
    iVar15 = (1 << (ulong)(uVar14 & 0x1f)) >> 1;
    if (0xf < uVar1) {
      lVar12 = uVar1 - (param_2 & 0xf);
      psVar11 = param_1 + 8;
      param_1 = param_1 + lVar12;
      uVar13 = uVar13 - (int)lVar12;
      iVar16 = -uVar14;
      uVar21 = (undefined2)-uVar14;
      uVar23 = (undefined2)(-uVar14 >> 0x10);
      iVar24 = -uVar14;
      iVar25 = -uVar14;
      do {
        lVar12 = lVar12 + -0x10;
        auVar30._0_4_ = iVar15 + iVar8 * psVar11[-8];
        auVar30._4_4_ = iVar15 + iVar8 * psVar11[-7];
        auVar30._8_4_ = iVar15 + iVar8 * psVar11[-6];
        auVar30._12_4_ = iVar15 + iVar8 * psVar11[-5];
        auVar29._0_4_ = iVar15 + iVar8 * psVar11[-4];
        auVar29._4_4_ = iVar15 + iVar8 * psVar11[-3];
        auVar29._8_4_ = iVar15 + iVar8 * psVar11[-2];
        auVar29._12_4_ = iVar15 + iVar8 * psVar11[-1];
        auVar27._0_4_ = iVar15 + iVar8 * psVar11[4];
        auVar27._4_4_ = iVar15 + iVar8 * psVar11[5];
        auVar27._8_4_ = iVar15 + iVar8 * psVar11[6];
        auVar27._12_4_ = iVar15 + iVar8 * psVar11[7];
        auVar28._4_2_ = uVar21;
        auVar28._0_4_ = iVar16;
        auVar28._6_2_ = uVar23;
        auVar28._8_4_ = iVar24;
        auVar28._12_4_ = iVar25;
        auVar29 = NEON_sshl(auVar29,auVar28,4);
        auVar31._4_2_ = uVar21;
        auVar31._0_4_ = iVar16;
        auVar31._6_2_ = uVar23;
        auVar31._8_4_ = iVar24;
        auVar31._12_4_ = iVar25;
        auVar31 = NEON_sshl(auVar30,auVar31,4);
        auVar32._4_2_ = uVar21;
        auVar32._0_4_ = iVar16;
        auVar32._6_2_ = uVar23;
        auVar32._8_4_ = iVar24;
        auVar32._12_4_ = iVar25;
        auVar6._4_4_ = iVar15 + iVar8 * psVar11[1];
        auVar6._0_4_ = iVar15 + iVar8 * *psVar11;
        auVar6._8_4_ = iVar15 + iVar8 * psVar11[2];
        auVar6._12_4_ = iVar15 + iVar8 * psVar11[3];
        auVar32 = NEON_sshl(auVar6,auVar32,4);
        auVar4._4_2_ = uVar21;
        auVar4._0_4_ = iVar16;
        auVar4._6_2_ = uVar23;
        auVar4._8_4_ = iVar24;
        auVar4._12_4_ = iVar25;
        auVar28 = NEON_sshl(auVar27,auVar4,4);
        psVar11[-4] = auVar29._0_2_;
        psVar11[-3] = auVar29._4_2_;
        psVar11[-2] = auVar29._8_2_;
        psVar11[-1] = auVar29._12_2_;
        psVar11[-8] = auVar31._0_2_;
        psVar11[-7] = auVar31._4_2_;
        psVar11[-6] = auVar31._8_2_;
        psVar11[-5] = auVar31._12_2_;
        psVar11[4] = auVar28._0_2_;
        psVar11[5] = auVar28._4_2_;
        psVar11[6] = auVar28._8_2_;
        psVar11[7] = auVar28._12_2_;
        *psVar11 = auVar32._0_2_;
        psVar11[1] = auVar32._4_2_;
        psVar11[2] = auVar32._8_2_;
        psVar11[3] = auVar32._12_2_;
        psVar11 = psVar11 + 0x10;
      } while (lVar12 != 0);
      if ((param_2 & 0xf) == 0) {
        return;
      }
    }
    iVar16 = uVar13 + 1;
    do {
      iVar16 = iVar16 + -1;
      *param_1 = (short)(iVar15 + iVar8 * *param_1 >> (uVar14 & 0x1f));
      param_1 = param_1 + 1;
    } while (0 < iVar16);
  }
  return;
}


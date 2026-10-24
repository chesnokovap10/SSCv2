/* _ssc_autocorr @ 0011191c size 632 */

int _ssc_autocorr(undefined2 *param_1,undefined1 (*param_2) [16])

{
  long lVar1;
  short *psVar2;
  uint uVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  long lVar8;
  undefined1 auVar9 [16];
  long lVar10;
  uint uVar11;
  int iVar12;
  int iVar14;
  int iVar15;
  int iVar16;
  undefined1 auVar13 [16];
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  undefined1 auVar21 [16];
  undefined1 auVar22 [16];
  undefined1 auVar23 [16];
  undefined1 auVar24 [16];
  undefined2 local_7a8 [944];
  long local_48;
  
  lVar8 = tpidr_el0;
  local_48 = *(long *)(lVar8 + 0x28);
  iVar12 = 0x1d801;
  iVar14 = 0;
  iVar15 = 0;
  iVar16 = 0;
  lVar10 = 0;
  iVar17 = 0;
  iVar18 = 0;
  iVar19 = 0;
  iVar20 = 0;
  do {
    psVar2 = (short *)((long)param_1 + lVar10);
    lVar10 = lVar10 + 0x20;
    iVar12 = iVar12 + ((uint)((int)*psVar2 * (int)*psVar2) >> 9) +
             ((uint)((int)psVar2[1] * (int)psVar2[1]) >> 9);
    iVar14 = iVar14 + ((uint)((int)psVar2[2] * (int)psVar2[2]) >> 9) +
             ((uint)((int)psVar2[3] * (int)psVar2[3]) >> 9);
    iVar15 = iVar15 + ((uint)((int)psVar2[4] * (int)psVar2[4]) >> 9) +
             ((uint)((int)psVar2[5] * (int)psVar2[5]) >> 9);
    iVar16 = iVar16 + ((uint)((int)psVar2[6] * (int)psVar2[6]) >> 9) +
             ((uint)((int)psVar2[7] * (int)psVar2[7]) >> 9);
    iVar17 = iVar17 + ((uint)((int)psVar2[8] * (int)psVar2[8]) >> 9) +
             ((uint)((int)psVar2[9] * (int)psVar2[9]) >> 9);
    iVar18 = iVar18 + ((uint)((int)psVar2[10] * (int)psVar2[10]) >> 9) +
             ((uint)((int)psVar2[0xb] * (int)psVar2[0xb]) >> 9);
    iVar19 = iVar19 + ((uint)((int)psVar2[0xc] * (int)psVar2[0xc]) >> 9) +
             ((uint)((int)psVar2[0xd] * (int)psVar2[0xd]) >> 9);
    iVar20 = iVar20 + ((uint)((int)psVar2[0xe] * (int)psVar2[0xe]) >> 9) +
             ((uint)((int)psVar2[0xf] * (int)psVar2[0xf]) >> 9);
  } while (lVar10 != 0x760);
  iVar12 = ec_ilog(iVar17 + iVar12 + iVar18 + iVar14 + iVar19 + iVar15 + iVar20 + iVar16);
  iVar12 = iVar12 * 0x10000 + -0x10000 >> 0x10;
  iVar14 = iVar12 + -0x14;
  iVar12 = iVar12 + -0x13;
  if (-1 < iVar14) {
    iVar12 = iVar14;
  }
  if (iVar14 < 2) {
    iVar12 = 0;
  }
  else {
    uVar3 = iVar12 >> 1;
    iVar12 = (1 << (ulong)(uVar3 & 0x1f)) >> 1;
    auVar13._0_4_ = -uVar3;
    auVar13._4_4_ = -uVar3;
    auVar13._8_4_ = -uVar3;
    auVar13._12_4_ = -uVar3;
    lVar10 = 0;
    do {
      psVar2 = (short *)((long)param_1 + lVar10);
      lVar1 = lVar10 + 0x20;
      auVar23._0_4_ = iVar12 + *psVar2;
      auVar23._4_4_ = iVar12 + psVar2[1];
      auVar23._8_4_ = iVar12 + psVar2[2];
      auVar23._12_4_ = iVar12 + psVar2[3];
      auVar24._0_4_ = iVar12 + psVar2[8];
      auVar24._4_4_ = iVar12 + psVar2[9];
      auVar24._8_4_ = iVar12 + psVar2[10];
      auVar24._12_4_ = iVar12 + psVar2[0xb];
      auVar21._0_4_ = iVar12 + psVar2[4];
      auVar21._4_4_ = iVar12 + psVar2[5];
      auVar21._8_4_ = iVar12 + psVar2[6];
      auVar21._12_4_ = iVar12 + psVar2[7];
      auVar22._0_4_ = iVar12 + psVar2[0xc];
      auVar22._4_4_ = iVar12 + psVar2[0xd];
      auVar22._8_4_ = iVar12 + psVar2[0xe];
      auVar22._12_4_ = iVar12 + psVar2[0xf];
      auVar23 = NEON_sshl(auVar23,auVar13,4);
      auVar24 = NEON_sshl(auVar24,auVar13,4);
      auVar21 = NEON_sshl(auVar21,auVar13,4);
      auVar22 = NEON_sshl(auVar22,auVar13,4);
      *(short *)((long)local_7a8 + lVar10 + 8) = auVar21._0_2_;
      *(short *)((long)local_7a8 + lVar10 + 10) = auVar21._4_2_;
      *(short *)((long)local_7a8 + lVar10 + 0xc) = auVar21._8_2_;
      *(short *)((long)local_7a8 + lVar10 + 0xe) = auVar21._12_2_;
      *(short *)((long)local_7a8 + lVar10) = auVar23._0_2_;
      *(short *)((long)local_7a8 + lVar10 + 2) = auVar23._4_2_;
      *(short *)((long)local_7a8 + lVar10 + 4) = auVar23._8_2_;
      *(short *)((long)local_7a8 + lVar10 + 6) = auVar23._12_2_;
      *(short *)((long)local_7a8 + lVar10 + 0x18) = auVar22._0_2_;
      *(short *)((long)local_7a8 + lVar10 + 0x1a) = auVar22._4_2_;
      *(short *)((long)local_7a8 + lVar10 + 0x1c) = auVar22._8_2_;
      *(short *)((long)local_7a8 + lVar10 + 0x1e) = auVar22._12_2_;
      *(short *)((long)local_7a8 + lVar10 + 0x10) = auVar24._0_2_;
      *(short *)((long)local_7a8 + lVar10 + 0x12) = auVar24._4_2_;
      *(short *)((long)local_7a8 + lVar10 + 0x14) = auVar24._8_2_;
      *(short *)((long)local_7a8 + lVar10 + 0x16) = auVar24._12_2_;
      lVar10 = lVar1;
    } while (lVar1 != 0x760);
    param_1 = local_7a8;
    iVar12 = uVar3 << 1;
  }
  ssc_pitch_xcorr_c1(param_1,param_1,param_2);
  sVar4 = param_1[0x3ac];
  sVar5 = param_1[0x3ae];
  sVar6 = param_1[0x3af];
  sVar7 = param_1[0x3ad];
  iVar17 = (int)sVar4;
  iVar16 = *(int *)(*param_2 + 0xc) + sVar6 * iVar17;
  iVar18 = (int)sVar5;
  iVar19 = (int)sVar6;
  iVar14 = (int)sVar6 * (int)sVar5 + ((int)sVar5 + (int)sVar4) * (int)sVar7 + *(int *)(*param_2 + 4)
  ;
  iVar15 = iVar18 * iVar17 + iVar19 * sVar7 + *(int *)(*param_2 + 8);
  uVar3 = sVar4 * iVar17 + (int)sVar7 * (int)sVar7 + iVar18 * iVar18 + *(int *)*param_2 +
          iVar19 * iVar19;
  *(int *)(*param_2 + 4) = iVar14;
  *(int *)(*param_2 + 8) = iVar15;
  *(uint *)*param_2 = uVar3;
  *(int *)(*param_2 + 0xc) = iVar16;
  if (iVar12 < 1) {
    uVar3 = uVar3 + (1 << (ulong)(-iVar12 & 0x1f));
    *(uint *)*param_2 = uVar3;
  }
  if ((int)uVar3 < 0x10000000) {
    iVar15 = ec_ilog();
    iVar14 = *(int *)param_2[1];
    uVar3 = 0x1d - iVar15;
    auVar9._4_4_ = uVar3;
    auVar9._0_4_ = uVar3;
    auVar9._8_4_ = uVar3;
    auVar9._12_4_ = uVar3;
    auVar13 = NEON_ushl(*param_2,auVar9,4);
    *(long *)(*param_2 + 8) = auVar13._8_8_;
    *(long *)*param_2 = auVar13._0_8_;
    *(int *)param_2[1] = iVar14 << (ulong)(uVar3 & 0x1f);
    if (*(long *)(lVar8 + 0x28) == local_48) {
      return iVar12 - uVar3;
    }
  }
  else {
    if (0x1fffffff < (int)uVar3) {
      iVar17 = *(int *)param_2[1];
      uVar11 = 1;
      if (0x3fffffff < (int)uVar3) {
        uVar11 = 2;
      }
      *(int *)(*param_2 + 8) = iVar15 >> uVar11;
      *(int *)(*param_2 + 0xc) = iVar16 >> uVar11;
      iVar12 = uVar11 + iVar12;
      *(uint *)*param_2 = uVar3 >> (ulong)uVar11;
      *(int *)(*param_2 + 4) = iVar14 >> uVar11;
      *(int *)param_2[1] = iVar17 >> uVar11;
    }
    if (*(long *)(lVar8 + 0x28) == local_48) {
      return iVar12;
    }
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


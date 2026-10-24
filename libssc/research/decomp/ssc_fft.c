/* ssc_fft @ 00105df8 size 904 */

void ssc_fft(int *param_1,int *param_2,int *param_3)

{
  int *piVar1;
  long lVar2;
  long lVar3;
  short *psVar4;
  long lVar5;
  long lVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  ulong uVar11;
  int iVar13;
  int iVar14;
  ulong uVar15;
  undefined1 auVar12 [16];
  int iVar16;
  int iVar22;
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  undefined1 auVar21 [16];
  ulong uVar23;
  ulong uVar24;
  
  iVar7 = *param_1;
  iVar8 = param_1[1];
  psVar4 = *(short **)(param_1 + 2);
  do {
    iVar7 = iVar7 + -1;
    piVar1 = param_3 + *psVar4;
    *piVar1 = *param_2;
    piVar1[1] = param_2[1];
    param_2 = param_2 + (*param_1 << 1);
    piVar1[2] = *param_2;
    piVar1[3] = param_2[1];
    param_2 = param_2 + 1 + (*param_1 << 1);
    piVar1[4] = param_2[-1];
    piVar1[5] = *param_2;
    param_2 = param_2 + (1 - (long)(*param_1 << 2));
    psVar4 = psVar4 + 1;
  } while (iVar7 != 0);
  lVar5 = 0;
  if (iVar8 == 0) {
    do {
      piVar1 = (int *)((long)param_3 + lVar5);
      uVar23 = (long)(int)*(undefined8 *)(piVar1 + 2) * 0x2aaaaaab + 0x40000000;
      uVar24 = (long)(int)((ulong)*(undefined8 *)(piVar1 + 2) >> 0x20) * 0x2aaaaaab + 0x40000000;
      uVar11 = (long)(int)*(undefined8 *)(piVar1 + 4) * 0x2aaaaaab + 0x40000000;
      uVar15 = (long)(int)((ulong)*(undefined8 *)(piVar1 + 4) >> 0x20) * 0x2aaaaaab + 0x40000000;
      iVar7 = (int)((long)(int)*(undefined8 *)piVar1 * 0x2aaaaaab + 0x40000000U >> 0x1f);
      iVar8 = (int)((long)(int)((ulong)*(undefined8 *)piVar1 >> 0x20) * 0x2aaaaaab + 0x40000000U >>
                   0x1f);
      iVar9 = (int)(uVar11 >> 0x1f) + (int)(uVar23 >> 0x1f);
      iVar13 = (int)(uVar15 >> 0x1f) + (int)(uVar24 >> 0x1f);
      iVar10 = iVar7 - (iVar9 >> 1);
      iVar14 = iVar8 - (iVar13 >> 1);
      auVar20._0_8_ =
           (long)((int)(uVar23 >> 0x1f) - (int)(uVar11 >> 0x1f)) * -0x6ed9eba1 + 0x40000000U >> 0x1f
      ;
      auVar20._8_8_ =
           (long)((int)(uVar24 >> 0x1f) - (int)(uVar15 >> 0x1f)) * -0x6ed9eba1 + 0x40000000U >> 0x1f
      ;
      auVar17 = NEON_ext(auVar20,auVar20,8,1);
      iVar16 = auVar17._0_4_;
      iVar22 = auVar17._8_4_;
      auVar21._0_4_ = iVar10 - iVar16;
      auVar21._4_4_ = iVar14 - iVar22;
      auVar21._8_4_ = iVar10 - iVar16;
      auVar21._12_4_ = iVar14 - iVar22;
      auVar12._0_4_ = iVar10 + iVar16;
      auVar12._4_4_ = iVar14 + iVar22;
      auVar12._8_4_ = iVar10 + iVar16;
      auVar12._12_4_ = iVar14 + iVar22;
      auVar17 = NEON_ext(auVar21,auVar12,0xc,1);
      lVar5 = lVar5 + 0x18;
      auVar19 = NEON_ext(auVar17,auVar21,4,1);
      auVar17 = NEON_ext(auVar17,auVar17,8,1);
      auVar17 = NEON_ext(auVar19,auVar17,0xc,1);
      *piVar1 = iVar9 + iVar7;
      piVar1[1] = iVar13 + iVar8;
      *(long *)(piVar1 + 4) = auVar17._8_8_;
      *(long *)(piVar1 + 2) = auVar17._0_8_;
    } while ((int)lVar5 != 0xd80);
    FUN_00106180(param_3,param_1,0x30);
    FUN_0010644c(param_3,param_1,0x10);
    FUN_0010664c(param_3,8,*(undefined8 *)(param_1 + 4),0x36,0);
    FUN_0010664c(param_3,8,*(undefined8 *)(param_1 + 4),0x36,0xd8);
    FUN_0010664c(param_3,8,*(undefined8 *)(param_1 + 4),0x36,0x1b0);
    FUN_0010664c(param_3,8,*(undefined8 *)(param_1 + 4),0x36,0x288);
    FUN_0010664c(param_3,2,*(undefined8 *)(param_1 + 4),0xd8,0);
    return;
  }
  do {
    piVar1 = (int *)((long)param_3 + lVar5);
    uVar23 = (long)(int)*(undefined8 *)(piVar1 + 2) * 0x2aaaaaab + 0x40000000;
    uVar24 = (long)(int)((ulong)*(undefined8 *)(piVar1 + 2) >> 0x20) * 0x2aaaaaab + 0x40000000;
    uVar11 = (long)(int)*(undefined8 *)(piVar1 + 4) * 0x2aaaaaab + 0x40000000;
    uVar15 = (long)(int)((ulong)*(undefined8 *)(piVar1 + 4) >> 0x20) * 0x2aaaaaab + 0x40000000;
    iVar7 = (int)((long)(int)*(undefined8 *)piVar1 * 0x2aaaaaab + 0x40000000U >> 0x1f);
    iVar8 = (int)((long)(int)((ulong)*(undefined8 *)piVar1 >> 0x20) * 0x2aaaaaab + 0x40000000U >>
                 0x1f);
    iVar9 = (int)(uVar11 >> 0x1f) + (int)(uVar23 >> 0x1f);
    iVar13 = (int)(uVar15 >> 0x1f) + (int)(uVar24 >> 0x1f);
    iVar10 = iVar7 - (iVar9 >> 1);
    iVar14 = iVar8 - (iVar13 >> 1);
    auVar19._0_8_ =
         (long)((int)(uVar23 >> 0x1f) - (int)(uVar11 >> 0x1f)) * -0x6ed9eba1 + 0x40000000U >> 0x1f;
    auVar19._8_8_ =
         (long)((int)(uVar24 >> 0x1f) - (int)(uVar15 >> 0x1f)) * -0x6ed9eba1 + 0x40000000U >> 0x1f;
    auVar17 = NEON_ext(auVar19,auVar19,8,1);
    iVar16 = auVar17._0_4_;
    iVar22 = auVar17._8_4_;
    auVar18._0_4_ = iVar10 - iVar16;
    auVar18._4_4_ = iVar14 - iVar22;
    auVar18._8_4_ = iVar10 - iVar16;
    auVar18._12_4_ = iVar14 - iVar22;
    auVar17._0_4_ = iVar10 + iVar16;
    auVar17._4_4_ = iVar14 + iVar22;
    auVar17._8_4_ = iVar10 + iVar16;
    auVar17._12_4_ = iVar14 + iVar22;
    auVar17 = NEON_ext(auVar18,auVar17,0xc,1);
    lVar5 = lVar5 + 0x18;
    auVar19 = NEON_ext(auVar17,auVar18,4,1);
    auVar17 = NEON_ext(auVar17,auVar17,8,1);
    auVar17 = NEON_ext(auVar19,auVar17,0xc,1);
    *piVar1 = iVar9 + iVar7;
    piVar1[1] = iVar13 + iVar8;
    *(long *)(piVar1 + 4) = auVar17._8_8_;
    *(long *)(piVar1 + 2) = auVar17._0_8_;
  } while ((int)lVar5 != 0x1b0);
  FUN_00106180(param_3,param_1,6);
  FUN_0010644c(param_3,param_1,2);
  lVar6 = *(long *)(param_1 + 4);
  lVar5 = 0;
  do {
    lVar2 = (long)*(int *)(lVar6 + lVar5);
    lVar3 = (long)((int *)(lVar6 + lVar5))[1];
    lVar5 = lVar5 + 0x40;
    iVar7 = (int)((ulong)((lVar2 * param_3[0x36] + 0x40000000) - lVar3 * param_3[0x37]) >> 0x1f);
    iVar8 = (int)(lVar3 * param_3[0x36] + param_3[0x37] * lVar2 + 0x40000000U >> 0x1f);
    param_3[0x36] = (*param_3 + 1) - iVar7 >> 1;
    param_3[0x37] = (param_3[1] + 1) - iVar8 >> 1;
    *param_3 = iVar7 + *param_3 + 1 >> 1;
    param_3[1] = param_3[1] + 1 + iVar8 >> 1;
    param_3 = param_3 + 2;
  } while ((int)lVar5 != 0x6c0);
  return;
}


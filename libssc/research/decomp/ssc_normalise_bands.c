/* ssc_normalise_bands @ 001082a8 size 772 */

void ssc_normalise_bands(long param_1,undefined1 (*param_2) [16],undefined8 *param_3,uint *param_4,
                        int param_5)

{
  uint uVar1;
  uint uVar2;
  short sVar3;
  undefined1 (*pauVar4) [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  short sVar7;
  int iVar8;
  int iVar9;
  undefined8 *puVar10;
  undefined1 (*pauVar11) [16];
  uint *puVar12;
  undefined8 *puVar13;
  int iVar14;
  short *psVar15;
  short *psVar16;
  int iVar17;
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  undefined1 auVar21 [16];
  
  psVar15 = *(short **)(param_1 + 0x10);
  puVar10 = param_3;
  pauVar11 = param_2;
  psVar16 = psVar15;
  puVar12 = param_4;
  iVar17 = param_5;
  do {
    uVar2 = *puVar12;
    iVar14 = (int)LZCOUNT(uVar2);
    uVar1 = (int)uVar2 >> (0x12U - iVar14 & 0x1f);
    if (uVar2 >> 0xe == 0) {
      uVar1 = uVar2 << (ulong)(iVar14 - 0x12U & 0x1f);
    }
    sVar7 = ssc_rcp(-(uVar1 >> 0xf & 1) & 0xfff80000 | (uVar1 & 0xffff) << 3);
    sVar3 = *psVar16;
    psVar16 = psVar16 + 1;
    iVar9 = (int)sVar7;
    if (uVar2 >> 0xf == 0) {
      iVar14 = iVar14 + -0x11;
      iVar8 = *psVar16 * 8 + sVar3 * -8 + 8;
      puVar13 = puVar10;
      do {
        auVar21 = *pauVar11;
        pauVar4 = pauVar11 + 1;
        pauVar11 = pauVar11 + 2;
        puVar10 = puVar13 + 2;
        iVar8 = iVar8 + -8;
        auVar19._4_4_ = iVar14;
        auVar19._0_4_ = iVar14;
        auVar19._8_4_ = iVar14;
        auVar19._12_4_ = iVar14;
        auVar19 = NEON_ushl(auVar21,auVar19,4);
        auVar21._4_4_ = iVar14;
        auVar21._0_4_ = iVar14;
        auVar21._8_4_ = iVar14;
        auVar21._12_4_ = iVar14;
        auVar21 = NEON_ushl(*pauVar4,auVar21,4);
        *puVar13 = CONCAT26((short)((uint)(auVar19._12_2_ * iVar9) >> 0xf),
                            CONCAT24((short)((uint)(auVar19._8_2_ * iVar9) >> 0xf),
                                     CONCAT22((short)((uint)(auVar19._4_2_ * iVar9) >> 0xf),
                                              (short)((uint)(auVar19._0_2_ * iVar9) >> 0xf))));
        puVar13[1] = CONCAT26((short)((uint)(auVar21._12_2_ * iVar9) >> 0xf),
                              CONCAT24((short)((uint)(auVar21._8_2_ * iVar9) >> 0xf),
                                       CONCAT22((short)((uint)(auVar21._4_2_ * iVar9) >> 0xf),
                                                (short)((uint)(auVar21._0_2_ * iVar9) >> 0xf))));
        puVar13 = puVar10;
      } while (8 < iVar8);
    }
    else {
      iVar14 = 0x11 - iVar14;
      iVar8 = *psVar16 * 8 + sVar3 * -8 + 8;
      puVar13 = puVar10;
      do {
        auVar19 = *pauVar11;
        pauVar4 = pauVar11 + 1;
        auVar18._0_4_ = -iVar14;
        auVar18._4_4_ = -iVar14;
        auVar18._8_4_ = -iVar14;
        auVar18._12_4_ = -iVar14;
        pauVar11 = pauVar11 + 2;
        puVar10 = puVar13 + 2;
        iVar8 = iVar8 + -8;
        auVar21 = NEON_sshl(auVar19,auVar18,4);
        auVar19 = NEON_sshl(*pauVar4,auVar18,4);
        *puVar13 = CONCAT26((short)((uint)(auVar21._12_2_ * iVar9) >> 0xf),
                            CONCAT24((short)((uint)(auVar21._8_2_ * iVar9) >> 0xf),
                                     CONCAT22((short)((uint)(auVar21._4_2_ * iVar9) >> 0xf),
                                              (short)((uint)(auVar21._0_2_ * iVar9) >> 0xf))));
        puVar13[1] = CONCAT26((short)((uint)(auVar19._12_2_ * iVar9) >> 0xf),
                              CONCAT24((short)((uint)(auVar19._8_2_ * iVar9) >> 0xf),
                                       CONCAT22((short)((uint)(auVar19._4_2_ * iVar9) >> 0xf),
                                                (short)((uint)(auVar19._0_2_ * iVar9) >> 0xf))));
        puVar13 = puVar10;
      } while (8 < iVar8);
    }
    iVar17 = iVar17 + -1;
    puVar12 = puVar12 + 1;
  } while (iVar17 != 0);
  psVar15 = psVar15 + (((ulong)(param_5 - 1) + 1) - (long)param_5);
  param_2 = param_2 + 0xd8;
  param_3 = param_3 + 0xd8;
  puVar12 = param_4 + 0x16;
  do {
    uVar2 = *puVar12;
    iVar17 = (int)LZCOUNT(uVar2);
    uVar1 = (int)uVar2 >> (0x12U - iVar17 & 0x1f);
    if (uVar2 >> 0xe == 0) {
      uVar1 = uVar2 << (ulong)(iVar17 - 0x12U & 0x1f);
    }
    sVar7 = ssc_rcp(-(uVar1 >> 0xf & 1) & 0xfff80000 | (uVar1 & 0xffff) << 3);
    sVar3 = *psVar15;
    psVar15 = psVar15 + 1;
    iVar14 = (int)sVar7;
    if (uVar2 >> 0xf == 0) {
      iVar17 = iVar17 + -0x11;
      iVar9 = *psVar15 * 8 + sVar3 * -8 + 8;
      puVar10 = param_3;
      do {
        auVar19 = *param_2;
        pauVar11 = param_2 + 1;
        param_2 = param_2 + 2;
        param_3 = puVar10 + 2;
        iVar9 = iVar9 + -8;
        auVar5._4_4_ = iVar17;
        auVar5._0_4_ = iVar17;
        auVar5._8_4_ = iVar17;
        auVar5._12_4_ = iVar17;
        auVar19 = NEON_ushl(auVar19,auVar5,4);
        auVar6._4_4_ = iVar17;
        auVar6._0_4_ = iVar17;
        auVar6._8_4_ = iVar17;
        auVar6._12_4_ = iVar17;
        auVar21 = NEON_ushl(*pauVar11,auVar6,4);
        *puVar10 = CONCAT26((short)((uint)(auVar19._12_2_ * iVar14) >> 0xf),
                            CONCAT24((short)((uint)(auVar19._8_2_ * iVar14) >> 0xf),
                                     CONCAT22((short)((uint)(auVar19._4_2_ * iVar14) >> 0xf),
                                              (short)((uint)(auVar19._0_2_ * iVar14) >> 0xf))));
        puVar10[1] = CONCAT26((short)((uint)(auVar21._12_2_ * iVar14) >> 0xf),
                              CONCAT24((short)((uint)(auVar21._8_2_ * iVar14) >> 0xf),
                                       CONCAT22((short)((uint)(auVar21._4_2_ * iVar14) >> 0xf),
                                                (short)((uint)(auVar21._0_2_ * iVar14) >> 0xf))));
        puVar10 = param_3;
      } while (8 < iVar9);
    }
    else {
      iVar17 = 0x11 - iVar17;
      iVar9 = *psVar15 * 8 + sVar3 * -8 + 8;
      puVar10 = param_3;
      do {
        auVar19 = *param_2;
        pauVar11 = param_2 + 1;
        auVar20._0_4_ = -iVar17;
        auVar20._4_4_ = -iVar17;
        auVar20._8_4_ = -iVar17;
        auVar20._12_4_ = -iVar17;
        param_2 = param_2 + 2;
        param_3 = puVar10 + 2;
        iVar9 = iVar9 + -8;
        auVar21 = NEON_sshl(auVar19,auVar20,4);
        auVar19 = NEON_sshl(*pauVar11,auVar20,4);
        *puVar10 = CONCAT26((short)((uint)(auVar21._12_2_ * iVar14) >> 0xf),
                            CONCAT24((short)((uint)(auVar21._8_2_ * iVar14) >> 0xf),
                                     CONCAT22((short)((uint)(auVar21._4_2_ * iVar14) >> 0xf),
                                              (short)((uint)(auVar21._0_2_ * iVar14) >> 0xf))));
        puVar10[1] = CONCAT26((short)((uint)(auVar19._12_2_ * iVar14) >> 0xf),
                              CONCAT24((short)((uint)(auVar19._8_2_ * iVar14) >> 0xf),
                                       CONCAT22((short)((uint)(auVar19._4_2_ * iVar14) >> 0xf),
                                                (short)((uint)(auVar19._0_2_ * iVar14) >> 0xf))));
        puVar10 = param_3;
      } while (8 < iVar9);
    }
    param_5 = param_5 + -1;
    puVar12 = puVar12 + 1;
  } while (param_5 != 0);
  return;
}


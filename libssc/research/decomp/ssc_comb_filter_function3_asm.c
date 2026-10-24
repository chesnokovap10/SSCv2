/* ssc_comb_filter_function3_asm @ 00116dac size 412 */

void ssc_comb_filter_function3_asm
               (int *param_1,int *param_2,long param_3,int param_4,int param_5,int param_6,
               uint *param_7)

{
  bool bVar1;
  undefined1 (*pauVar2) [16];
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined1 auVar10 [16];
  undefined8 uVar11;
  undefined8 uVar12;
  undefined1 (*pauVar13) [16];
  int iVar14;
  int iVar15;
  int iVar16;
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  int iVar20;
  int iVar21;
  int iVar22;
  undefined8 uVar23;
  undefined8 uVar24;
  int iVar25;
  int iVar26;
  int iVar27;
  int iVar28;
  int iVar29;
  int iVar30;
  int iVar31;
  int iVar32;
  uint uVar33;
  uint uVar34;
  uint uVar35;
  uint uVar36;
  int iVar37;
  int iVar38;
  int iVar39;
  uint uVar40;
  uint uVar41;
  uint uVar42;
  uint uVar43;
  
  iVar3 = param_4 * 0x2740 >> 0xf;
  iVar4 = param_5 * 0x2740 >> 0xf;
  iVar5 = param_4 * 0x1bc8 >> 0xf;
  iVar6 = param_5 * 0x1bc8 >> 0xf;
  iVar7 = param_4 * 0x1098 >> 0xf;
  iVar8 = param_5 * 0x1098 >> 0xf;
  pauVar13 = (undefined1 (*) [16])(param_2 + -(param_3 + 2));
  uVar23 = *(undefined8 *)*pauVar13;
  uVar24 = *(undefined8 *)(*pauVar13 + 8);
  do {
    pauVar2 = pauVar13 + 1;
    uVar40 = *param_7;
    uVar41 = param_7[1];
    uVar42 = param_7[2];
    uVar43 = param_7[3];
    iVar25 = (int)(0x7fffffff - uVar40) >> 0x10;
    iVar27 = (int)(0x7fffffff - uVar41) >> 0x10;
    iVar29 = (int)(0x7fffffff - uVar42) >> 0x10;
    iVar31 = (int)(0x7fffffff - uVar43) >> 0x10;
    uVar33 = 0x7fffffff - uVar40 & 0xffff;
    uVar34 = 0x7fffffff - uVar41 & 0xffff;
    uVar35 = 0x7fffffff - uVar42 & 0xffff;
    uVar36 = 0x7fffffff - uVar43 & 0xffff;
    iVar14 = *(int *)(pauVar13[1] + 4);
    uVar11 = *(undefined8 *)*pauVar2;
    iVar15 = *(int *)(pauVar13[1] + 8);
    iVar16 = *(int *)(pauVar13[1] + 0xc);
    uVar12 = *(undefined8 *)(pauVar13[1] + 8);
    iVar21 = (int)uVar24;
    iVar22 = (int)((ulong)uVar24 >> 0x20);
    iVar20 = (int)((ulong)uVar23 >> 0x20);
    auVar17._8_4_ = iVar21;
    auVar17._0_8_ = uVar23;
    auVar17._12_4_ = iVar22;
    auVar18 = NEON_ext(auVar17,*pauVar2,8,1);
    auVar19._8_4_ = iVar21;
    auVar19._0_8_ = uVar23;
    auVar19._12_4_ = iVar22;
    auVar17 = NEON_ext(auVar19,*pauVar2,0xc,1);
    auVar10._8_4_ = iVar21;
    auVar10._0_8_ = uVar23;
    auVar10._12_4_ = iVar22;
    auVar19 = NEON_ext(auVar10,*pauVar2,4,1);
    iVar26 = (int)uVar40 >> 0x10;
    iVar28 = (int)uVar41 >> 0x10;
    iVar30 = (int)uVar42 >> 0x10;
    iVar32 = (int)uVar43 >> 0x10;
    uVar40 = uVar40 & 0xffff;
    uVar41 = uVar41 & 0xffff;
    uVar42 = uVar42 & 0xffff;
    uVar43 = uVar43 & 0xffff;
    iVar37 = param_2[1];
    iVar38 = param_2[2];
    iVar39 = param_2[3];
    iVar9 = param_6 + -4;
    *param_1 = (int)((long)(iVar3 * iVar25 * 2 + ((int)(uVar33 * iVar3) >> 0xf)) *
                     (long)auVar18._0_4_ +
                     (long)(iVar5 * iVar25 * 2 + ((int)(uVar33 * iVar5) >> 0xf)) *
                     (long)(auVar17._0_4_ + auVar19._0_4_) +
                     (long)(iVar7 * iVar25 * 2 + ((int)(uVar33 * iVar7) >> 0xf)) *
                     (long)(*(int *)*pauVar2 + (int)uVar23) +
                     (long)(iVar4 * iVar26 * 2 + ((int)(uVar40 * iVar4) >> 0xf)) *
                     (long)auVar18._0_4_ +
                     (long)(iVar6 * iVar26 * 2 + ((int)(uVar40 * iVar6) >> 0xf)) *
                     (long)(auVar17._0_4_ + auVar19._0_4_) +
                     (long)(iVar8 * iVar26 * 2 + ((int)(uVar40 * iVar8) >> 0xf)) *
                     (long)(*(int *)*pauVar2 + (int)uVar23) + 0x40000000U >> 0x1f) + *param_2;
    param_1[1] = (int)((long)(iVar3 * iVar27 * 2 + ((int)(uVar34 * iVar3) >> 0xf)) *
                       (long)auVar18._4_4_ +
                       (long)(iVar5 * iVar27 * 2 + ((int)(uVar34 * iVar5) >> 0xf)) *
                       (long)(auVar17._4_4_ + auVar19._4_4_) +
                       (long)(iVar7 * iVar27 * 2 + ((int)(uVar34 * iVar7) >> 0xf)) *
                       (long)(iVar14 + iVar20) +
                       (long)(iVar4 * iVar28 * 2 + ((int)(uVar41 * iVar4) >> 0xf)) *
                       (long)auVar18._4_4_ +
                       (long)(iVar6 * iVar28 * 2 + ((int)(uVar41 * iVar6) >> 0xf)) *
                       (long)(auVar17._4_4_ + auVar19._4_4_) +
                       (long)(iVar8 * iVar28 * 2 + ((int)(uVar41 * iVar8) >> 0xf)) *
                       (long)(iVar14 + iVar20) + 0x40000000U >> 0x1f) + iVar37;
    param_1[2] = (int)((long)(iVar3 * iVar29 * 2 + ((int)(uVar35 * iVar3) >> 0xf)) *
                       (long)auVar18._8_4_ +
                       (long)(iVar5 * iVar29 * 2 + ((int)(uVar35 * iVar5) >> 0xf)) *
                       (long)(auVar17._8_4_ + auVar19._8_4_) +
                       (long)(iVar7 * iVar29 * 2 + ((int)(uVar35 * iVar7) >> 0xf)) *
                       (long)(iVar15 + iVar21) +
                       (long)(iVar4 * iVar30 * 2 + ((int)(uVar42 * iVar4) >> 0xf)) *
                       (long)auVar18._8_4_ +
                       (long)(iVar6 * iVar30 * 2 + ((int)(uVar42 * iVar6) >> 0xf)) *
                       (long)(auVar17._8_4_ + auVar19._8_4_) +
                       (long)(iVar8 * iVar30 * 2 + ((int)(uVar42 * iVar8) >> 0xf)) *
                       (long)(iVar15 + iVar21) + 0x40000000U >> 0x1f) + iVar38;
    param_1[3] = (int)((long)(iVar3 * iVar31 * 2 + ((int)(uVar36 * iVar3) >> 0xf)) *
                       (long)auVar18._12_4_ +
                       (long)(iVar5 * iVar31 * 2 + ((int)(uVar36 * iVar5) >> 0xf)) *
                       (long)(auVar17._12_4_ + auVar19._12_4_) +
                       (long)(iVar7 * iVar31 * 2 + ((int)(uVar36 * iVar7) >> 0xf)) *
                       (long)(iVar16 + iVar22) +
                       (long)(iVar4 * iVar32 * 2 + ((int)(uVar43 * iVar4) >> 0xf)) *
                       (long)auVar18._12_4_ +
                       (long)(iVar6 * iVar32 * 2 + ((int)(uVar43 * iVar6) >> 0xf)) *
                       (long)(auVar17._12_4_ + auVar19._12_4_) +
                       (long)(iVar8 * iVar32 * 2 + ((int)(uVar43 * iVar8) >> 0xf)) *
                       (long)(iVar16 + iVar22) + 0x40000000U >> 0x1f) + iVar39;
    param_2 = param_2 + 4;
    param_1 = param_1 + 4;
    param_7 = param_7 + 4;
    bVar1 = 3 < param_6;
    pauVar13 = pauVar2;
    uVar23 = uVar11;
    uVar24 = uVar12;
    param_6 = iVar9;
  } while (iVar9 != 0 && bVar1);
  return;
}


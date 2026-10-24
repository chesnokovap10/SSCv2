/* ssc_comb_filter_function4_asm @ 00116f48 size 448 */

void ssc_comb_filter_function4_asm
               (int *param_1,int *param_2,long param_3,long param_4,int param_5,int param_6,
               int param_7,uint *param_8)

{
  bool bVar1;
  undefined1 (*pauVar2) [16];
  undefined1 (*pauVar3) [16];
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined8 uVar13;
  undefined8 uVar14;
  undefined1 (*pauVar15) [16];
  undefined1 (*pauVar16) [16];
  int iVar17;
  int iVar18;
  int iVar19;
  undefined1 auVar20 [16];
  undefined1 auVar21 [16];
  undefined1 auVar22 [16];
  undefined1 auVar23 [16];
  undefined1 auVar24 [16];
  undefined1 auVar25 [16];
  int iVar26;
  int iVar27;
  int iVar28;
  int iVar29;
  int iVar30;
  int iVar31;
  int iVar32;
  int iVar33;
  int iVar34;
  int iVar35;
  int iVar36;
  int iVar37;
  int iVar38;
  int iVar39;
  int iVar40;
  int iVar41;
  int iVar42;
  int iVar43;
  int iVar44;
  int iVar45;
  uint uVar46;
  uint uVar47;
  uint uVar48;
  uint uVar49;
  int iVar50;
  int iVar51;
  int iVar52;
  uint uVar53;
  uint uVar54;
  uint uVar55;
  uint uVar56;
  
  iVar4 = param_5 * 0x2740 >> 0xf;
  iVar5 = param_6 * 0x2740 >> 0xf;
  iVar6 = param_5 * 0x1bc8 >> 0xf;
  iVar7 = param_6 * 0x1bc8 >> 0xf;
  iVar8 = param_5 * 0x1098 >> 0xf;
  iVar9 = param_6 * 0x1098 >> 0xf;
  pauVar15 = (undefined1 (*) [16])(param_2 + -(param_3 + 2));
  pauVar16 = (undefined1 (*) [16])(param_2 + -(param_4 + 2));
  iVar26 = *(int *)*pauVar15;
  iVar27 = *(int *)(*pauVar15 + 4);
  iVar28 = *(int *)(*pauVar15 + 8);
  iVar29 = *(int *)(*pauVar15 + 0xc);
  iVar30 = *(int *)*pauVar16;
  iVar31 = *(int *)(*pauVar16 + 4);
  iVar32 = *(int *)(*pauVar16 + 8);
  iVar33 = *(int *)(*pauVar16 + 0xc);
  do {
    pauVar2 = pauVar15 + 1;
    pauVar3 = pauVar16 + 1;
    uVar53 = *param_8;
    uVar54 = param_8[1];
    uVar55 = param_8[2];
    uVar56 = param_8[3];
    iVar38 = (int)(0x7fffffff - uVar53) >> 0x10;
    iVar40 = (int)(0x7fffffff - uVar54) >> 0x10;
    iVar42 = (int)(0x7fffffff - uVar55) >> 0x10;
    iVar44 = (int)(0x7fffffff - uVar56) >> 0x10;
    uVar46 = 0x7fffffff - uVar53 & 0xffff;
    uVar47 = 0x7fffffff - uVar54 & 0xffff;
    uVar48 = 0x7fffffff - uVar55 & 0xffff;
    uVar49 = 0x7fffffff - uVar56 & 0xffff;
    iVar17 = *(int *)(pauVar15[1] + 4);
    uVar13 = *(undefined8 *)*pauVar2;
    iVar18 = *(int *)(pauVar15[1] + 8);
    iVar19 = *(int *)(pauVar15[1] + 0xc);
    uVar14 = *(undefined8 *)(pauVar15[1] + 8);
    iVar34 = *(int *)*pauVar3;
    iVar35 = *(int *)(pauVar16[1] + 4);
    iVar36 = *(int *)(pauVar16[1] + 8);
    iVar37 = *(int *)(pauVar16[1] + 0xc);
    auVar20._4_4_ = iVar27;
    auVar20._0_4_ = iVar26;
    auVar20._8_4_ = iVar28;
    auVar20._12_4_ = iVar29;
    auVar22 = NEON_ext(auVar20,*pauVar2,8,1);
    auVar21._4_4_ = iVar27;
    auVar21._0_4_ = iVar26;
    auVar21._8_4_ = iVar28;
    auVar21._12_4_ = iVar29;
    auVar20 = NEON_ext(auVar21,*pauVar2,0xc,1);
    auVar23._4_4_ = iVar27;
    auVar23._0_4_ = iVar26;
    auVar23._8_4_ = iVar28;
    auVar23._12_4_ = iVar29;
    auVar24 = NEON_ext(auVar23,*pauVar2,4,1);
    iVar39 = (int)uVar53 >> 0x10;
    iVar41 = (int)uVar54 >> 0x10;
    iVar43 = (int)uVar55 >> 0x10;
    iVar45 = (int)uVar56 >> 0x10;
    uVar53 = uVar53 & 0xffff;
    uVar54 = uVar54 & 0xffff;
    uVar55 = uVar55 & 0xffff;
    uVar56 = uVar56 & 0xffff;
    auVar25._4_4_ = iVar31;
    auVar25._0_4_ = iVar30;
    auVar25._8_4_ = iVar32;
    auVar25._12_4_ = iVar33;
    auVar23 = NEON_ext(auVar25,*pauVar3,8,1);
    auVar11._4_4_ = iVar31;
    auVar11._0_4_ = iVar30;
    auVar11._8_4_ = iVar32;
    auVar11._12_4_ = iVar33;
    auVar21 = NEON_ext(auVar11,*pauVar3,0xc,1);
    auVar12._4_4_ = iVar31;
    auVar12._0_4_ = iVar30;
    auVar12._8_4_ = iVar32;
    auVar12._12_4_ = iVar33;
    auVar25 = NEON_ext(auVar12,*pauVar3,4,1);
    iVar50 = param_2[1];
    iVar51 = param_2[2];
    iVar52 = param_2[3];
    iVar10 = param_7 + -4;
    *param_1 = (int)((long)(iVar4 * iVar38 * 2 + ((int)(uVar46 * iVar4) >> 0xf)) *
                     (long)auVar22._0_4_ +
                     (long)(iVar6 * iVar38 * 2 + ((int)(uVar46 * iVar6) >> 0xf)) *
                     (long)(auVar20._0_4_ + auVar24._0_4_) +
                     (long)(iVar8 * iVar38 * 2 + ((int)(uVar46 * iVar8) >> 0xf)) *
                     (long)(*(int *)*pauVar2 + iVar26) +
                     (long)(iVar5 * iVar39 * 2 + ((int)(uVar53 * iVar5) >> 0xf)) *
                     (long)auVar23._0_4_ +
                     (long)(iVar7 * iVar39 * 2 + ((int)(uVar53 * iVar7) >> 0xf)) *
                     (long)(auVar21._0_4_ + auVar25._0_4_) +
                     (long)(iVar9 * iVar39 * 2 + ((int)(uVar53 * iVar9) >> 0xf)) *
                     (long)(iVar34 + iVar30) + 0x40000000U >> 0x1f) + *param_2;
    param_1[1] = (int)((long)(iVar4 * iVar40 * 2 + ((int)(uVar47 * iVar4) >> 0xf)) *
                       (long)auVar22._4_4_ +
                       (long)(iVar6 * iVar40 * 2 + ((int)(uVar47 * iVar6) >> 0xf)) *
                       (long)(auVar20._4_4_ + auVar24._4_4_) +
                       (long)(iVar8 * iVar40 * 2 + ((int)(uVar47 * iVar8) >> 0xf)) *
                       (long)(iVar17 + iVar27) +
                       (long)(iVar5 * iVar41 * 2 + ((int)(uVar54 * iVar5) >> 0xf)) *
                       (long)auVar23._4_4_ +
                       (long)(iVar7 * iVar41 * 2 + ((int)(uVar54 * iVar7) >> 0xf)) *
                       (long)(auVar21._4_4_ + auVar25._4_4_) +
                       (long)(iVar9 * iVar41 * 2 + ((int)(uVar54 * iVar9) >> 0xf)) *
                       (long)(iVar35 + iVar31) + 0x40000000U >> 0x1f) + iVar50;
    param_1[2] = (int)((long)(iVar4 * iVar42 * 2 + ((int)(uVar48 * iVar4) >> 0xf)) *
                       (long)auVar22._8_4_ +
                       (long)(iVar6 * iVar42 * 2 + ((int)(uVar48 * iVar6) >> 0xf)) *
                       (long)(auVar20._8_4_ + auVar24._8_4_) +
                       (long)(iVar8 * iVar42 * 2 + ((int)(uVar48 * iVar8) >> 0xf)) *
                       (long)(iVar18 + iVar28) +
                       (long)(iVar5 * iVar43 * 2 + ((int)(uVar55 * iVar5) >> 0xf)) *
                       (long)auVar23._8_4_ +
                       (long)(iVar7 * iVar43 * 2 + ((int)(uVar55 * iVar7) >> 0xf)) *
                       (long)(auVar21._8_4_ + auVar25._8_4_) +
                       (long)(iVar9 * iVar43 * 2 + ((int)(uVar55 * iVar9) >> 0xf)) *
                       (long)(iVar36 + iVar32) + 0x40000000U >> 0x1f) + iVar51;
    param_1[3] = (int)((long)(iVar4 * iVar44 * 2 + ((int)(uVar49 * iVar4) >> 0xf)) *
                       (long)auVar22._12_4_ +
                       (long)(iVar6 * iVar44 * 2 + ((int)(uVar49 * iVar6) >> 0xf)) *
                       (long)(auVar20._12_4_ + auVar24._12_4_) +
                       (long)(iVar8 * iVar44 * 2 + ((int)(uVar49 * iVar8) >> 0xf)) *
                       (long)(iVar19 + iVar29) +
                       (long)(iVar5 * iVar45 * 2 + ((int)(uVar56 * iVar5) >> 0xf)) *
                       (long)auVar23._12_4_ +
                       (long)(iVar7 * iVar45 * 2 + ((int)(uVar56 * iVar7) >> 0xf)) *
                       (long)(auVar21._12_4_ + auVar25._12_4_) +
                       (long)(iVar9 * iVar45 * 2 + ((int)(uVar56 * iVar9) >> 0xf)) *
                       (long)(iVar37 + iVar33) + 0x40000000U >> 0x1f) + iVar52;
    param_2 = param_2 + 4;
    param_1 = param_1 + 4;
    param_8 = param_8 + 4;
    iVar28 = (int)uVar14;
    iVar29 = (int)((ulong)uVar14 >> 0x20);
    iVar26 = (int)uVar13;
    iVar27 = (int)((ulong)uVar13 >> 0x20);
    bVar1 = 3 < param_7;
    pauVar15 = pauVar2;
    pauVar16 = pauVar3;
    iVar30 = iVar34;
    iVar31 = iVar35;
    iVar32 = iVar36;
    iVar33 = iVar37;
    param_7 = iVar10;
  } while (iVar10 != 0 && bVar1);
  return;
}


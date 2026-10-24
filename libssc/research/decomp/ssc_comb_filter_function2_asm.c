/* ssc_comb_filter_function2_asm @ 00116c98 size 276 */

void ssc_comb_filter_function2_asm
               (int *param_1,int *param_2,long param_3,int param_4,int param_5,int *param_6)

{
  bool bVar1;
  undefined1 (*pauVar2) [16];
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined1 auVar7 [16];
  undefined8 uVar8;
  undefined8 uVar9;
  undefined1 (*pauVar10) [16];
  int iVar11;
  int iVar12;
  int iVar13;
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  int iVar17;
  int iVar18;
  undefined8 uVar19;
  undefined8 uVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  int iVar24;
  int iVar25;
  int iVar26;
  int iVar27;
  uint uVar28;
  uint uVar29;
  uint uVar30;
  uint uVar31;
  
  iVar3 = param_4 * 0x2740 >> 0xf;
  iVar4 = param_4 * 0x1bc8 >> 0xf;
  iVar5 = param_4 * 0x1098 >> 0xf;
  pauVar10 = (undefined1 (*) [16])(param_2 + -(param_3 + 2));
  uVar19 = *(undefined8 *)*pauVar10;
  uVar20 = *(undefined8 *)(*pauVar10 + 8);
  do {
    pauVar2 = pauVar10 + 1;
    iVar24 = (int)(0x7fffffffU - *param_6) >> 0x10;
    iVar25 = (int)(0x7fffffffU - param_6[1]) >> 0x10;
    iVar26 = (int)(0x7fffffffU - param_6[2]) >> 0x10;
    iVar27 = (int)(0x7fffffffU - param_6[3]) >> 0x10;
    uVar28 = 0x7fffffffU - *param_6 & 0xffff;
    uVar29 = 0x7fffffffU - param_6[1] & 0xffff;
    uVar30 = 0x7fffffffU - param_6[2] & 0xffff;
    uVar31 = 0x7fffffffU - param_6[3] & 0xffff;
    iVar11 = *(int *)(pauVar10[1] + 4);
    uVar8 = *(undefined8 *)*pauVar2;
    iVar12 = *(int *)(pauVar10[1] + 8);
    iVar13 = *(int *)(pauVar10[1] + 0xc);
    uVar9 = *(undefined8 *)(pauVar10[1] + 8);
    iVar17 = (int)uVar20;
    iVar18 = (int)((ulong)uVar20 >> 0x20);
    auVar14._8_4_ = iVar17;
    auVar14._0_8_ = uVar19;
    auVar14._12_4_ = iVar18;
    auVar15 = NEON_ext(auVar14,*pauVar2,8,1);
    auVar16._8_4_ = iVar17;
    auVar16._0_8_ = uVar19;
    auVar16._12_4_ = iVar18;
    auVar14 = NEON_ext(auVar16,*pauVar2,0xc,1);
    auVar7._8_4_ = iVar17;
    auVar7._0_8_ = uVar19;
    auVar7._12_4_ = iVar18;
    auVar16 = NEON_ext(auVar7,*pauVar2,4,1);
    iVar21 = param_2[1];
    iVar22 = param_2[2];
    iVar23 = param_2[3];
    iVar6 = param_5 + -4;
    *param_1 = (int)((long)(iVar3 * iVar24 * 2 + ((int)(uVar28 * iVar3) >> 0xf)) *
                     (long)auVar15._0_4_ +
                     (long)(iVar4 * iVar24 * 2 + ((int)(uVar28 * iVar4) >> 0xf)) *
                     (long)(auVar14._0_4_ + auVar16._0_4_) +
                     (long)(iVar5 * iVar24 * 2 + ((int)(uVar28 * iVar5) >> 0xf)) *
                     (long)(*(int *)*pauVar2 + (int)uVar19) + 0x40000000U >> 0x1f) + *param_2;
    param_1[1] = (int)((long)(iVar3 * iVar25 * 2 + ((int)(uVar29 * iVar3) >> 0xf)) *
                       (long)auVar15._4_4_ +
                       (long)(iVar4 * iVar25 * 2 + ((int)(uVar29 * iVar4) >> 0xf)) *
                       (long)(auVar14._4_4_ + auVar16._4_4_) +
                       (long)(iVar5 * iVar25 * 2 + ((int)(uVar29 * iVar5) >> 0xf)) *
                       (long)(iVar11 + (int)((ulong)uVar19 >> 0x20)) + 0x40000000U >> 0x1f) + iVar21
    ;
    param_1[2] = (int)((long)(iVar3 * iVar26 * 2 + ((int)(uVar30 * iVar3) >> 0xf)) *
                       (long)auVar15._8_4_ +
                       (long)(iVar4 * iVar26 * 2 + ((int)(uVar30 * iVar4) >> 0xf)) *
                       (long)(auVar14._8_4_ + auVar16._8_4_) +
                       (long)(iVar5 * iVar26 * 2 + ((int)(uVar30 * iVar5) >> 0xf)) *
                       (long)(iVar12 + iVar17) + 0x40000000U >> 0x1f) + iVar22;
    param_1[3] = (int)((long)(iVar3 * iVar27 * 2 + ((int)(uVar31 * iVar3) >> 0xf)) *
                       (long)auVar15._12_4_ +
                       (long)(iVar4 * iVar27 * 2 + ((int)(uVar31 * iVar4) >> 0xf)) *
                       (long)(auVar14._12_4_ + auVar16._12_4_) +
                       (long)(iVar5 * iVar27 * 2 + ((int)(uVar31 * iVar5) >> 0xf)) *
                       (long)(iVar13 + iVar18) + 0x40000000U >> 0x1f) + iVar23;
    param_2 = param_2 + 4;
    param_1 = param_1 + 4;
    param_6 = param_6 + 4;
    bVar1 = 3 < param_5;
    pauVar10 = pauVar2;
    uVar19 = uVar8;
    uVar20 = uVar9;
    param_5 = iVar6;
  } while (iVar6 != 0 && bVar1);
  return;
}


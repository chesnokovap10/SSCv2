/* ssc_patch_transient_decision @ 0010a170 size 508 */

void ssc_patch_transient_decision(long param_1,long param_2,int param_3,uint param_4)

{
  bool bVar1;
  undefined1 (*pauVar2) [16];
  short sVar3;
  uint uVar4;
  short sVar5;
  long lVar6;
  ulong uVar7;
  ulong uVar8;
  short *psVar9;
  undefined2 *puVar10;
  ulong uVar11;
  short *psVar12;
  long lVar13;
  undefined1 (*pauVar14) [16];
  undefined1 (*pauVar15) [16];
  ulong uVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  int iVar24;
  int iVar25;
  int iVar26;
  int iVar27;
  int iVar28;
  int iVar29;
  int iVar30;
  int iVar31;
  int iVar32;
  undefined1 auVar33 [16];
  undefined1 auVar34 [16];
  undefined1 auVar35 [16];
  undefined1 auVar36 [16];
  undefined1 auVar37 [16];
  undefined1 auVar38 [16];
  undefined1 auVar39 [16];
  short asStack_4c [13];
  short local_32;
  undefined2 auStack_30 [7];
  undefined1 auStack_22 [10];
  long local_18;
  
  lVar6 = tpidr_el0;
  local_18 = *(long *)(lVar6 + 0x28);
  sVar3 = *(short *)(param_2 + (long)(param_3 + 0xd) * 2);
  local_32 = *(short *)(param_2 + 0x1a);
  if (*(short *)(param_2 + 0x1a) <= sVar3) {
    local_32 = sVar3;
  }
  iVar17 = (int)local_32;
  if (0xe < (int)param_4) {
    psVar9 = (short *)(param_2 + 0x1c);
    lVar13 = (ulong)param_4 - 0xe;
    puVar10 = auStack_30;
    do {
      psVar12 = psVar9 + param_3;
      sVar5 = (short)iVar17;
      sVar3 = *psVar9;
      psVar9 = psVar9 + 1;
      if (sVar3 <= *psVar12) {
        sVar3 = *psVar12;
      }
      iVar17 = iVar17 + -0x400;
      if (sVar5 + -0x400 <= (int)sVar3) {
        iVar17 = (int)sVar3;
      }
      lVar13 = lVar13 + -1;
      *puVar10 = (short)iVar17;
      puVar10 = puVar10 + 1;
    } while (lVar13 != 0);
    if (0xe < (int)param_4) {
      uVar8 = (ulong)(param_4 - 2);
      do {
        sVar3 = asStack_4c[uVar8];
        iVar17 = (int)sVar3;
        if ((int)sVar3 <= asStack_4c[uVar8 + 1] + -0x400) {
          iVar17 = asStack_4c[uVar8 + 1] + -0x400;
        }
        asStack_4c[uVar8] = (short)iVar17;
        bVar1 = 0xd < uVar8;
        uVar8 = uVar8 - 1;
      } while (bVar1);
      if (0xe < (int)param_4) {
        uVar8 = (ulong)(param_4 - 1) - 0xd;
        if (uVar8 < 0x10) {
          iVar17 = 0;
          uVar7 = 0xd;
        }
        else {
          uVar11 = uVar8 & 0xfffffffffffffff0;
          pauVar14 = (undefined1 (*) [16])(param_1 + 0x2a);
          uVar7 = uVar11 | 0xd;
          iVar17 = 0;
          iVar18 = 0;
          iVar19 = 0;
          iVar20 = 0;
          pauVar15 = (undefined1 (*) [16])auStack_22;
          iVar21 = 0;
          iVar22 = 0;
          iVar23 = 0;
          iVar24 = 0;
          iVar25 = 0;
          iVar26 = 0;
          iVar27 = 0;
          iVar28 = 0;
          iVar29 = 0;
          iVar30 = 0;
          iVar31 = 0;
          iVar32 = 0;
          uVar16 = uVar11;
          do {
            pauVar2 = pauVar14 + -1;
            auVar34 = *pauVar14;
            pauVar14 = pauVar14 + 2;
            uVar16 = uVar16 - 0x10;
            auVar33 = NEON_smax(*pauVar2,ZEXT816(0),2);
            pauVar2 = pauVar15 + -1;
            auVar36 = *pauVar15;
            auVar34 = NEON_smax(auVar34,ZEXT816(0),2);
            pauVar15 = pauVar15 + 2;
            auVar37 = NEON_smax(*pauVar2,ZEXT816(0),2);
            auVar39 = NEON_smax(auVar36,ZEXT816(0),2);
            auVar36._0_4_ = (uint)auVar33._0_2_ - (uint)auVar37._0_2_;
            auVar36._4_4_ = (uint)auVar33._2_2_ - (uint)auVar37._2_2_;
            auVar36._8_4_ = (uint)auVar33._4_2_ - (uint)auVar37._4_2_;
            auVar36._12_4_ = (uint)auVar33._6_2_ - (uint)auVar37._6_2_;
            auVar38._0_4_ = (uint)auVar34._8_2_ - (uint)auVar39._8_2_;
            auVar38._4_4_ = (uint)auVar34._10_2_ - (uint)auVar39._10_2_;
            auVar38._8_4_ = (uint)auVar34._12_2_ - (uint)auVar39._12_2_;
            auVar38._12_4_ = (uint)auVar34._14_2_ - (uint)auVar39._14_2_;
            auVar35._0_4_ = (uint)auVar34._0_2_ - (uint)auVar39._0_2_;
            auVar35._4_4_ = (uint)auVar34._2_2_ - (uint)auVar39._2_2_;
            auVar35._8_4_ = (uint)auVar34._4_2_ - (uint)auVar39._4_2_;
            auVar35._12_4_ = (uint)auVar34._6_2_ - (uint)auVar39._6_2_;
            auVar34._4_4_ = (uint)auVar33._10_2_ - (uint)auVar37._10_2_;
            auVar34._0_4_ = (uint)auVar33._8_2_ - (uint)auVar37._8_2_;
            auVar34._8_4_ = (uint)auVar33._12_2_ - (uint)auVar37._12_2_;
            auVar34._12_4_ = (uint)auVar33._14_2_ - (uint)auVar37._14_2_;
            auVar37 = NEON_smax(auVar34,ZEXT816(0),4);
            auVar34 = NEON_smax(auVar36,ZEXT816(0),4);
            auVar33 = NEON_smax(auVar38,ZEXT816(0),4);
            auVar36 = NEON_smax(auVar35,ZEXT816(0),4);
            iVar21 = auVar37._0_4_ + iVar21;
            iVar22 = auVar37._4_4_ + iVar22;
            iVar23 = auVar37._8_4_ + iVar23;
            iVar24 = auVar37._12_4_ + iVar24;
            iVar17 = auVar34._0_4_ + iVar17;
            iVar18 = auVar34._4_4_ + iVar18;
            iVar19 = auVar34._8_4_ + iVar19;
            iVar20 = auVar34._12_4_ + iVar20;
            iVar29 = auVar33._0_4_ + iVar29;
            iVar30 = auVar33._4_4_ + iVar30;
            iVar31 = auVar33._8_4_ + iVar31;
            iVar32 = auVar33._12_4_ + iVar32;
            iVar25 = auVar36._0_4_ + iVar25;
            iVar26 = auVar36._4_4_ + iVar26;
            iVar27 = auVar36._8_4_ + iVar27;
            iVar28 = auVar36._12_4_ + iVar28;
          } while (uVar16 != 0);
          iVar17 = iVar25 + iVar17 + iVar29 + iVar21 + iVar26 + iVar18 + iVar30 + iVar22 +
                   iVar27 + iVar19 + iVar31 + iVar23 + iVar28 + iVar20 + iVar32 + iVar24;
          if (uVar8 == uVar11) goto LAB_0010a258;
        }
        lVar13 = (param_4 - 1) - uVar7;
        psVar9 = asStack_4c + uVar7;
        psVar12 = (short *)(param_1 + uVar7 * 2);
        do {
          lVar13 = lVar13 + -1;
          uVar4 = ((int)*psVar12 & ((uint)(int)*psVar12 >> 0xf ^ 0xffffffff) & 0xffff) -
                  ((int)*psVar9 & ((uint)(int)*psVar9 >> 0xf ^ 0xffffffff) & 0xffff);
          iVar17 = (uVar4 & ((int)uVar4 >> 0x1f ^ 0xffffffffU)) + iVar17;
          psVar9 = psVar9 + 1;
          psVar12 = psVar12 + 1;
        } while (lVar13 != 0);
        goto LAB_0010a258;
      }
    }
  }
  iVar17 = 0;
LAB_0010a258:
  iVar18 = 0;
  if (param_4 - 0xe != 0) {
    iVar18 = iVar17 / (int)(param_4 - 0xe);
  }
  if (*(long *)(lVar6 + 0x28) != local_18) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(0x400 < iVar18);
  }
  return;
}


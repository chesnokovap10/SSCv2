/* FUN_001126bc @ 001126bc size 724 */

void FUN_001126bc(undefined8 *param_1,int param_2,uint param_3,undefined8 *param_4,uint param_5,
                 uint param_6)

{
  short *psVar1;
  ulong uVar2;
  uint uVar3;
  undefined1 auVar4 [16];
  short *psVar5;
  short *psVar6;
  short *psVar7;
  short *psVar8;
  short *psVar9;
  short *psVar10;
  short *psVar11;
  short *psVar12;
  short *psVar13;
  short *psVar14;
  short *psVar15;
  short *psVar16;
  short *psVar17;
  short *psVar18;
  uint uVar19;
  long lVar20;
  uint uVar21;
  short *psVar22;
  uint uVar23;
  undefined4 uVar24;
  undefined8 *puVar25;
  undefined4 uVar26;
  ulong uVar27;
  ulong uVar28;
  ulong uVar29;
  uint uVar30;
  int iVar31;
  int iVar32;
  int iVar33;
  int iVar34;
  uint uVar35;
  int iVar37;
  int iVar38;
  undefined1 auVar36 [16];
  int iVar39;
  short sVar43;
  short sVar44;
  undefined8 uVar40;
  short sVar45;
  undefined1 auVar41 [16];
  undefined1 auVar42 [16];
  int iVar46;
  undefined8 uVar47;
  int iVar49;
  int iVar50;
  undefined1 auVar48 [16];
  int iVar51;
  int iVar52;
  int iVar53;
  int iVar54;
  int iVar55;
  undefined1 auVar56 [16];
  undefined1 auVar57 [16];
  undefined1 auVar58 [16];
  undefined1 auVar59 [16];
  undefined1 auVar60 [16];
  
  *param_4 = 0x100000000;
  if (param_2 < 1) {
    iVar31 = 0;
    iVar32 = 0;
    iVar33 = 0;
    iVar34 = 0;
    uVar23 = 0;
  }
  else {
    iVar38 = -param_5;
    iVar37 = 0;
    iVar31 = 0;
    iVar32 = 0;
    iVar33 = 0;
    iVar34 = 0;
    auVar36._4_4_ = iVar38;
    auVar36._0_4_ = iVar38;
    auVar36._8_4_ = iVar38;
    auVar36._12_4_ = iVar38;
    puVar25 = param_1;
    do {
      uVar40 = *puVar25;
      uVar47 = puVar25[1];
      iVar37 = iVar37 + 8;
      sVar43 = (short)((ulong)uVar40 >> 0x10);
      sVar44 = (short)((ulong)uVar40 >> 0x20);
      sVar45 = (short)((ulong)uVar40 >> 0x30);
      auVar41._0_4_ = (int)(short)uVar40 * (int)(short)uVar40;
      auVar41._4_4_ = (int)sVar43 * (int)sVar43;
      auVar41._8_4_ = (int)sVar44 * (int)sVar44;
      auVar41._12_4_ = (int)sVar45 * (int)sVar45;
      sVar43 = (short)((ulong)uVar47 >> 0x10);
      sVar44 = (short)((ulong)uVar47 >> 0x20);
      sVar45 = (short)((ulong)uVar47 >> 0x30);
      auVar48._0_4_ = (int)(short)uVar47 * (int)(short)uVar47;
      auVar48._4_4_ = (int)sVar43 * (int)sVar43;
      auVar48._8_4_ = (int)sVar44 * (int)sVar44;
      auVar48._12_4_ = (int)sVar45 * (int)sVar45;
      auVar41 = NEON_sshl(auVar41,auVar36,4);
      auVar48 = NEON_sshl(auVar48,auVar36,4);
      iVar31 = auVar41._0_4_ + iVar31 + auVar48._0_4_;
      iVar32 = auVar41._4_4_ + iVar32 + auVar48._4_4_;
      iVar33 = auVar41._8_4_ + iVar33 + auVar48._8_4_;
      iVar34 = auVar41._12_4_ + iVar34 + auVar48._12_4_;
      puVar25 = puVar25 + 2;
    } while (iVar37 < param_2);
    uVar23 = param_2 + 7U & 0xfffffff8;
  }
  auVar60._4_4_ = iVar32;
  auVar60._0_4_ = iVar31;
  auVar60._8_4_ = iVar33;
  auVar60._12_4_ = iVar34;
  auVar4._4_4_ = iVar32;
  auVar4._0_4_ = iVar31;
  auVar4._8_4_ = iVar33;
  auVar4._12_4_ = iVar34;
  auVar36 = NEON_ext(auVar60,auVar4,8,1);
  uVar35 = auVar36._0_4_ + auVar36._4_4_ + iVar31 + iVar32 + 1;
  if ((int)uVar23 < param_2) {
    uVar28 = (ulong)uVar23;
    if (0xe < ~uVar23 + param_2) {
      uVar2 = (ulong)(~uVar23 + param_2) + 1;
      uVar27 = uVar2 & 0x1fffffff0;
      iVar31 = 0;
      iVar32 = 0;
      iVar33 = 0;
      iVar34 = 0;
      auVar42._0_4_ = -param_5;
      auVar42._4_4_ = -param_5;
      auVar42._8_4_ = -param_5;
      auVar42._12_4_ = -param_5;
      iVar37 = 0;
      iVar38 = 0;
      iVar39 = 0;
      psVar22 = (short *)((long)param_1 + uVar28 * 2 + 0x10);
      iVar46 = 0;
      iVar49 = 0;
      iVar50 = 0;
      iVar51 = 0;
      iVar52 = 0;
      iVar53 = 0;
      iVar54 = 0;
      iVar55 = 0;
      uVar29 = uVar27;
      do {
        psVar1 = psVar22 + -8;
        psVar5 = psVar22 + -7;
        psVar6 = psVar22 + -6;
        psVar7 = psVar22 + -5;
        psVar8 = psVar22 + -4;
        psVar9 = psVar22 + -3;
        psVar10 = psVar22 + -2;
        psVar11 = psVar22 + -1;
        sVar43 = *psVar22;
        psVar12 = psVar22 + 1;
        psVar13 = psVar22 + 2;
        psVar14 = psVar22 + 3;
        psVar15 = psVar22 + 4;
        psVar16 = psVar22 + 5;
        psVar17 = psVar22 + 6;
        psVar18 = psVar22 + 7;
        uVar29 = uVar29 - 0x10;
        psVar22 = psVar22 + 0x10;
        auVar58._0_4_ = (int)*psVar8 * (int)*psVar8;
        auVar58._4_4_ = (int)*psVar9 * (int)*psVar9;
        auVar58._8_4_ = (int)*psVar10 * (int)*psVar10;
        auVar58._12_4_ = (int)*psVar11 * (int)*psVar11;
        auVar56._0_4_ = (int)*psVar1 * (int)*psVar1;
        auVar56._4_4_ = (int)*psVar5 * (int)*psVar5;
        auVar56._8_4_ = (int)*psVar6 * (int)*psVar6;
        auVar56._12_4_ = (int)*psVar7 * (int)*psVar7;
        auVar59._0_4_ = (int)*psVar15 * (int)*psVar15;
        auVar59._4_4_ = (int)*psVar16 * (int)*psVar16;
        auVar59._8_4_ = (int)*psVar17 * (int)*psVar17;
        auVar59._12_4_ = (int)*psVar18 * (int)*psVar18;
        auVar57._0_4_ = (int)sVar43 * (int)sVar43;
        auVar57._4_4_ = (int)*psVar12 * (int)*psVar12;
        auVar57._8_4_ = (int)*psVar13 * (int)*psVar13;
        auVar57._12_4_ = (int)*psVar14 * (int)*psVar14;
        auVar48 = NEON_ushl(auVar58,auVar42,4);
        auVar36 = NEON_ushl(auVar56,auVar42,4);
        auVar60 = NEON_ushl(auVar59,auVar42,4);
        auVar41 = NEON_ushl(auVar57,auVar42,4);
        iVar31 = auVar48._0_4_ + iVar31;
        iVar32 = auVar48._4_4_ + iVar32;
        iVar33 = auVar48._8_4_ + iVar33;
        iVar34 = auVar48._12_4_ + iVar34;
        uVar35 = auVar36._0_4_ + uVar35;
        iVar37 = auVar36._4_4_ + iVar37;
        iVar38 = auVar36._8_4_ + iVar38;
        iVar39 = auVar36._12_4_ + iVar39;
        iVar52 = auVar60._0_4_ + iVar52;
        iVar53 = auVar60._4_4_ + iVar53;
        iVar54 = auVar60._8_4_ + iVar54;
        iVar55 = auVar60._12_4_ + iVar55;
        iVar46 = auVar41._0_4_ + iVar46;
        iVar49 = auVar41._4_4_ + iVar49;
        iVar50 = auVar41._8_4_ + iVar50;
        iVar51 = auVar41._12_4_ + iVar51;
      } while (uVar29 != 0);
      uVar35 = iVar46 + uVar35 + iVar52 + iVar31 + iVar49 + iVar37 + iVar53 + iVar32 +
               iVar50 + iVar38 + iVar54 + iVar33 + iVar51 + iVar39 + iVar55 + iVar34;
      uVar28 = uVar27 + uVar28;
      if (uVar2 == uVar27) goto LAB_00112814;
    }
    do {
      uVar2 = uVar28 + 1;
      iVar31 = (int)*(short *)((long)param_1 + uVar28 * 2);
      uVar35 = ((uint)(iVar31 * iVar31) >> (ulong)(param_5 & 0x1f)) + uVar35;
      uVar28 = uVar2;
    } while ((int)uVar2 < param_2);
  }
LAB_00112814:
  if (0 < (int)param_3) {
    uVar26 = 0;
    uVar28 = 0;
    uVar21 = 0;
    uVar30 = 0;
    uVar23 = 0xffff;
    uVar19 = 0xffff;
    do {
      uVar3 = (&DAT_00124d18)[uVar28];
      if (0 < (int)uVar3) {
        sVar43 = (short)(uVar3 >> (ulong)(0x11U - (int)LZCOUNT(param_6) & 0x1f));
        if (param_6 >> 0xf == 0) {
          sVar43 = (short)(uVar3 << (ulong)((int)LZCOUNT(param_6) - 0x11U & 0x1f));
        }
        uVar3 = (int)sVar43 * (int)sVar43;
        iVar31 = (int)(uVar3 * 2) >> 0x10;
        if (((int)((uVar35 & 0xffff) * (int)(short)uVar23) >> 0xf) +
            (int)(short)uVar23 * ((int)uVar35 >> 0x10) * 2 <
            (int)(((int)uVar21 >> 0xf & 0xfffffffeU) * iVar31 +
                 ((int)(iVar31 * (uVar21 & 0xffff)) >> 0xf))) {
          uVar24 = (undefined4)uVar28;
          if (((int)((uVar35 & 0xffff) * (int)(short)uVar19) >> 0xf) +
              (int)(short)uVar19 * ((int)uVar35 >> 0x10) * 2 <
              (int)(((int)uVar30 >> 0xf & 0xfffffffeU) * iVar31 +
                   ((int)(iVar31 * (uVar30 & 0xffff)) >> 0xf))) {
            *(undefined4 *)param_4 = uVar24;
            *(undefined4 *)((long)param_4 + 4) = uVar26;
            uVar26 = uVar24;
            uVar21 = uVar30;
            uVar23 = uVar19;
            uVar19 = uVar3 >> 0xf;
            uVar30 = uVar35;
          }
          else {
            uVar23 = uVar3 >> 0xf;
            *(undefined4 *)((long)param_4 + 4) = uVar24;
            uVar21 = uVar35;
          }
        }
      }
      lVar20 = uVar28 * 2;
      uVar28 = uVar28 + 1;
      iVar32 = (int)*(short *)((long)param_1 + lVar20 + (long)param_2 * 2);
      iVar31 = (int)*(short *)((long)param_1 + lVar20);
      uVar35 = (((uint)(iVar32 * iVar32) >> (ulong)(param_5 & 0x1f)) -
               ((uint)(iVar31 * iVar31) >> (ulong)(param_5 & 0x1f))) + uVar35;
      if ((int)uVar35 < 2) {
        uVar35 = 1;
      }
    } while (param_3 != uVar28);
  }
  return;
}


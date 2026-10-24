/* FUN_00107ddc @ 00107ddc size 1036 */

void FUN_00107ddc(undefined8 *param_1,uint param_2,uint param_3,int *param_4,uint param_5,
                 undefined4 param_6)

{
  uint uVar1;
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  int iVar4;
  uint uVar5;
  undefined8 *puVar6;
  uint uVar7;
  long lVar8;
  ulong uVar9;
  ulong uVar10;
  short *psVar11;
  ulong uVar12;
  ulong uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  uint uVar21;
  int iVar23;
  int iVar24;
  undefined1 auVar22 [16];
  int iVar25;
  short sVar29;
  short sVar30;
  undefined8 uVar26;
  short sVar31;
  undefined1 auVar27 [16];
  undefined1 auVar28 [16];
  undefined8 uVar32;
  undefined1 auVar33 [16];
  undefined1 auVar34 [16];
  undefined1 auVar35 [16];
  
  iVar4 = ec_ilog(param_6);
  param_4[0] = 0;
  param_4[1] = 1;
  if ((int)param_2 < 1) {
    uVar7 = 0;
    iVar17 = 0;
    iVar18 = 0;
    iVar19 = 0;
    iVar20 = 0;
  }
  else {
    iVar17 = -param_5;
    iVar23 = 0;
    auVar22._4_4_ = iVar17;
    auVar22._0_4_ = iVar17;
    auVar22._8_4_ = iVar17;
    auVar22._12_4_ = iVar17;
    iVar17 = 0;
    iVar18 = 0;
    iVar19 = 0;
    iVar20 = 0;
    puVar6 = param_1;
    do {
      uVar26 = *puVar6;
      uVar32 = puVar6[1];
      iVar23 = iVar23 + 8;
      sVar29 = (short)((ulong)uVar26 >> 0x10);
      sVar30 = (short)((ulong)uVar26 >> 0x20);
      sVar31 = (short)((ulong)uVar26 >> 0x30);
      auVar27._0_4_ = (int)(short)uVar26 * (int)(short)uVar26;
      auVar27._4_4_ = (int)sVar29 * (int)sVar29;
      auVar27._8_4_ = (int)sVar30 * (int)sVar30;
      auVar27._12_4_ = (int)sVar31 * (int)sVar31;
      sVar29 = (short)((ulong)uVar32 >> 0x10);
      sVar30 = (short)((ulong)uVar32 >> 0x20);
      sVar31 = (short)((ulong)uVar32 >> 0x30);
      auVar33._0_4_ = (int)(short)uVar32 * (int)(short)uVar32;
      auVar33._4_4_ = (int)sVar29 * (int)sVar29;
      auVar33._8_4_ = (int)sVar30 * (int)sVar30;
      auVar33._12_4_ = (int)sVar31 * (int)sVar31;
      auVar27 = NEON_sshl(auVar27,auVar22,4);
      auVar33 = NEON_sshl(auVar33,auVar22,4);
      iVar17 = auVar27._0_4_ + iVar17 + auVar33._0_4_;
      iVar18 = auVar27._4_4_ + iVar18 + auVar33._4_4_;
      iVar19 = auVar27._8_4_ + iVar19 + auVar33._8_4_;
      iVar20 = auVar27._12_4_ + iVar20 + auVar33._12_4_;
      puVar6 = puVar6 + 2;
    } while (iVar23 < (int)param_2);
    uVar7 = param_2 + 7 & 0xfffffff8;
  }
  auVar2._4_4_ = iVar18;
  auVar2._0_4_ = iVar17;
  auVar2._8_4_ = iVar19;
  auVar2._12_4_ = iVar20;
  auVar3._4_4_ = iVar18;
  auVar3._0_4_ = iVar17;
  auVar3._8_4_ = iVar19;
  auVar3._12_4_ = iVar20;
  auVar22 = NEON_ext(auVar2,auVar3,8,1);
  uVar21 = auVar22._0_4_ + auVar22._4_4_ + iVar17 + iVar18 + 1;
  if ((int)uVar7 < (int)param_2) {
    uVar9 = (ulong)uVar7;
    uVar10 = param_2 - uVar9;
    if (7 < uVar10) {
      uVar12 = uVar10 & 0xfffffffffffffff8;
      lVar8 = uVar9 * 2;
      iVar17 = 0;
      iVar18 = 0;
      iVar19 = 0;
      iVar20 = 0;
      uVar9 = uVar12 + uVar9;
      iVar23 = 0;
      iVar24 = 0;
      iVar25 = 0;
      puVar6 = (undefined8 *)((long)param_1 + lVar8 + 8);
      auVar28._0_4_ = -param_5;
      auVar28._4_4_ = -param_5;
      auVar28._8_4_ = -param_5;
      auVar28._12_4_ = -param_5;
      uVar13 = uVar12;
      do {
        uVar26 = puVar6[-1];
        uVar32 = *puVar6;
        uVar13 = uVar13 - 8;
        puVar6 = puVar6 + 2;
        sVar29 = (short)((ulong)uVar26 >> 0x10);
        sVar30 = (short)((ulong)uVar26 >> 0x20);
        sVar31 = (short)((ulong)uVar26 >> 0x30);
        auVar34._0_4_ = (int)(short)uVar26 * (int)(short)uVar26;
        auVar34._4_4_ = (int)sVar29 * (int)sVar29;
        auVar34._8_4_ = (int)sVar30 * (int)sVar30;
        auVar34._12_4_ = (int)sVar31 * (int)sVar31;
        sVar29 = (short)((ulong)uVar32 >> 0x10);
        sVar30 = (short)((ulong)uVar32 >> 0x20);
        sVar31 = (short)((ulong)uVar32 >> 0x30);
        auVar35._0_4_ = (int)(short)uVar32 * (int)(short)uVar32;
        auVar35._4_4_ = (int)sVar29 * (int)sVar29;
        auVar35._8_4_ = (int)sVar30 * (int)sVar30;
        auVar35._12_4_ = (int)sVar31 * (int)sVar31;
        auVar22 = NEON_ushl(auVar34,auVar28,4);
        auVar27 = NEON_ushl(auVar35,auVar28,4);
        uVar21 = auVar22._0_4_ + uVar21;
        iVar23 = auVar22._4_4_ + iVar23;
        iVar24 = auVar22._8_4_ + iVar24;
        iVar25 = auVar22._12_4_ + iVar25;
        iVar17 = auVar27._0_4_ + iVar17;
        iVar18 = auVar27._4_4_ + iVar18;
        iVar19 = auVar27._8_4_ + iVar19;
        iVar20 = auVar27._12_4_ + iVar20;
      } while (uVar13 != 0);
      uVar21 = iVar17 + uVar21 + iVar18 + iVar23 + iVar19 + iVar24 + iVar20 + iVar25;
      if (uVar10 == uVar12) goto LAB_00107f28;
    }
    lVar8 = param_2 - uVar9;
    psVar11 = (short *)((long)param_1 + uVar9 * 2);
    do {
      lVar8 = lVar8 + -1;
      uVar21 = ((uint)((int)*psVar11 * (int)*psVar11) >> (ulong)(param_5 & 0x1f)) + uVar21;
      psVar11 = psVar11 + 1;
    } while (lVar8 != 0);
  }
LAB_00107f28:
  if (0 < (int)param_3) {
    iVar4 = iVar4 * 0x10000 + -0x10000 >> 0x10;
    uVar7 = iVar4 - 0xe;
    if ((int)uVar7 < 1) {
      iVar17 = 0;
      uVar9 = 0;
      uVar16 = 0;
      uVar15 = 0;
      uVar7 = 0xffff;
      uVar5 = 0xffff;
      do {
        if (0 < (int)(&DAT_0012bddc)[uVar9]) {
          iVar18 = (int)(short)((&DAT_0012bddc)[uVar9] << (ulong)(0xeU - iVar4 & 0x1f));
          uVar14 = iVar18 * iVar18;
          iVar18 = (int)(uVar14 * 2) >> 0x10;
          if (((int)((uVar21 & 0xffff) * (int)(short)uVar7) >> 0xf) +
              (int)(short)uVar7 * ((int)uVar21 >> 0x10) * 2 <
              ((int)(iVar18 * (uVar16 & 0xffff)) >> 0xf) + ((int)uVar16 >> 0x10) * iVar18 * 2) {
            iVar19 = (int)uVar9;
            if (((int)((uVar21 & 0xffff) * (int)(short)uVar5) >> 0xf) +
                (int)(short)uVar5 * ((int)uVar21 >> 0x10) * 2 <
                ((int)(iVar18 * (uVar15 & 0xffff)) >> 0xf) + ((int)uVar15 >> 0x10) * iVar18 * 2) {
              *param_4 = iVar19;
              param_4[1] = iVar17;
              iVar17 = iVar19;
              uVar16 = uVar15;
              uVar7 = uVar5;
              uVar5 = uVar14 >> 0xf;
              uVar15 = uVar21;
            }
            else {
              uVar7 = uVar14 >> 0xf;
              param_4[1] = iVar19;
              uVar16 = uVar21;
            }
          }
        }
        lVar8 = uVar9 * 2;
        uVar9 = uVar9 + 1;
        iVar18 = (int)*(short *)((long)param_1 + lVar8 + (long)(int)param_2 * 2);
        iVar19 = (int)*(short *)((long)param_1 + lVar8);
        uVar21 = (((uint)(iVar18 * iVar18) >> (ulong)(param_5 & 0x1f)) -
                 ((uint)(iVar19 * iVar19) >> (ulong)(param_5 & 0x1f))) + uVar21;
        if ((int)uVar21 < 2) {
          uVar21 = 1;
        }
      } while (param_3 != uVar9);
    }
    else {
      iVar4 = 0;
      uVar9 = 0;
      uVar5 = 0;
      uVar14 = 0;
      uVar16 = 0xffff;
      uVar15 = 0xffff;
      do {
        iVar17 = (int)uVar9;
        if (0 < (int)(&DAT_0012bddc)[uVar9]) {
          iVar18 = (int)(short)((uint)(&DAT_0012bddc)[uVar9] >> (ulong)(uVar7 & 0x1f));
          uVar1 = iVar18 * iVar18;
          iVar18 = (int)(uVar1 * 2) >> 0x10;
          if (((int)((uVar21 & 0xffff) * (int)(short)uVar16) >> 0xf) +
              (int)(short)uVar16 * ((int)uVar21 >> 0x10) * 2 <
              ((int)(iVar18 * (uVar5 & 0xffff)) >> 0xf) + ((int)uVar5 >> 0x10) * iVar18 * 2) {
            if (((int)((uVar21 & 0xffff) * (int)(short)uVar15) >> 0xf) +
                (int)(short)uVar15 * ((int)uVar21 >> 0x10) * 2 <
                ((int)(iVar18 * (uVar14 & 0xffff)) >> 0xf) + ((int)uVar14 >> 0x10) * iVar18 * 2) {
              *param_4 = iVar17;
              param_4[1] = iVar4;
              iVar4 = iVar17;
              uVar5 = uVar14;
              uVar16 = uVar15;
              uVar15 = uVar1 >> 0xf;
              uVar14 = uVar21;
            }
            else {
              uVar16 = uVar1 >> 0xf;
              param_4[1] = iVar17;
              uVar5 = uVar21;
            }
          }
        }
        lVar8 = uVar9 * 2;
        uVar9 = uVar9 + 1;
        iVar18 = (int)*(short *)((long)param_1 + lVar8);
        iVar17 = (int)*(short *)((long)param_1 + (long)(int)(param_2 + iVar17) * 2);
        uVar21 = (((uint)(iVar17 * iVar17) >> (ulong)(param_5 & 0x1f)) -
                 ((uint)(iVar18 * iVar18) >> (ulong)(param_5 & 0x1f))) + uVar21;
        if ((int)uVar21 < 2) {
          uVar21 = 1;
        }
      } while (param_3 != uVar9);
    }
  }
  return;
}


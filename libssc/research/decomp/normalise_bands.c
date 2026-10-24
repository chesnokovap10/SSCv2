/* normalise_bands @ 00103260 size 1088 */

void normalise_bands(long param_1,long param_2,long param_3,long param_4,int param_5)

{
  undefined1 (*pauVar1) [16];
  long lVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  short sVar12;
  int iVar13;
  long lVar14;
  ulong uVar15;
  long lVar16;
  undefined8 *puVar17;
  long lVar18;
  long lVar19;
  ulong uVar20;
  long lVar21;
  ulong uVar22;
  undefined1 (*pauVar23) [16];
  long lVar24;
  ulong uVar25;
  ulong uVar26;
  undefined1 auVar27 [16];
  undefined1 auVar28 [16];
  
  lVar24 = *(long *)(param_1 + 0x10);
  uVar26 = 0;
  lVar14 = (long)(*(int *)(param_1 + 0x1c) << 3);
  do {
    uVar25 = -(uVar26 >> 0x1f & 1) & 0xfffffffc00000000 | (uVar26 & 0xffffffff) << 2;
    iVar13 = ec_ilog(*(undefined4 *)(param_4 + uVar25));
    iVar3 = *(int *)(param_4 + uVar25);
    iVar13 = iVar13 * 0x10000 + -0x10000 >> 0x10;
    uVar5 = iVar3 >> (iVar13 - 0xdU & 0x1f);
    if ((int)(iVar13 - 0xdU) < 1) {
      uVar5 = iVar3 << (ulong)(0xdU - iVar13 & 0x1f);
    }
    uVar4 = iVar13 - 0xe;
    sVar12 = ssc_rcp(-(uVar5 >> 0xf & 1) & 0xfff80000 | (uVar5 & 0xffff) << 3);
    lVar19 = (long)*(short *)(lVar24 + uVar26 * 2);
    uVar26 = uVar26 + 1;
    iVar3 = (int)sVar12;
    lVar16 = lVar19 * 8;
    uVar15 = (long)*(short *)(lVar24 + uVar26 * 2) * 8;
    uVar25 = lVar19 << 3 | 1;
    if ((int)uVar4 < 1) {
      if ((long)uVar25 <= (long)uVar15) {
        uVar25 = uVar15;
      }
      uVar25 = uVar25 + lVar19 * -8;
      uVar5 = 0xe - iVar13;
      if (7 < uVar25) {
        uVar20 = uVar25 & 0xfffffffffffffff8;
        pauVar23 = (undefined1 (*) [16])(param_2 + 0x10 + lVar19 * 0x20);
        lVar16 = uVar20 + lVar16;
        puVar17 = (undefined8 *)(param_3 + 8 + lVar19 * 0x10);
        uVar22 = uVar20;
        do {
          pauVar1 = pauVar23 + -1;
          auVar8 = *pauVar23;
          pauVar23 = pauVar23 + 2;
          uVar22 = uVar22 - 8;
          auVar28._4_4_ = uVar5;
          auVar28._0_4_ = uVar5;
          auVar28._8_4_ = uVar5;
          auVar28._12_4_ = uVar5;
          auVar28 = NEON_ushl(*pauVar1,auVar28,4);
          auVar27._4_4_ = uVar5;
          auVar27._0_4_ = uVar5;
          auVar27._8_4_ = uVar5;
          auVar27._12_4_ = uVar5;
          auVar27 = NEON_ushl(auVar8,auVar27,4);
          puVar17[-1] = CONCAT26((short)((uint)(auVar28._12_2_ * iVar3) >> 0xf),
                                 CONCAT24((short)((uint)(auVar28._8_2_ * iVar3) >> 0xf),
                                          CONCAT22((short)((uint)(auVar28._4_2_ * iVar3) >> 0xf),
                                                   (short)((uint)(auVar28._0_2_ * iVar3) >> 0xf))));
          *puVar17 = CONCAT26((short)((uint)(auVar27._12_2_ * iVar3) >> 0xf),
                              CONCAT24((short)((uint)(auVar27._8_2_ * iVar3) >> 0xf),
                                       CONCAT22((short)((uint)(auVar27._4_2_ * iVar3) >> 0xf),
                                                (short)((uint)(auVar27._0_2_ * iVar3) >> 0xf))));
          puVar17 = puVar17 + 2;
        } while (uVar22 != 0);
        if (uVar25 == uVar20) goto LAB_00103478;
      }
      do {
        *(short *)(param_3 + lVar16 * 2) =
             (short)((uint)((short)(*(int *)(param_2 + lVar16 * 4) << (ulong)(uVar5 & 0x1f)) * iVar3
                           ) >> 0xf);
        lVar16 = lVar16 + 1;
      } while (lVar16 < (long)uVar15);
    }
    else {
      if ((long)uVar25 <= (long)uVar15) {
        uVar25 = uVar15;
      }
      uVar25 = uVar25 + lVar19 * -8;
      if (7 < uVar25) {
        uVar20 = uVar25 & 0xfffffffffffffff8;
        pauVar23 = (undefined1 (*) [16])(param_2 + 0x10 + lVar19 * 0x20);
        lVar16 = uVar20 + lVar16;
        puVar17 = (undefined8 *)(param_3 + 8 + lVar19 * 0x10);
        uVar22 = uVar20;
        do {
          pauVar1 = pauVar23 + -1;
          auVar28 = *pauVar23;
          pauVar23 = pauVar23 + 2;
          uVar22 = uVar22 - 8;
          auVar8._4_4_ = -uVar4;
          auVar8._0_4_ = -uVar4;
          auVar8._8_4_ = -uVar4;
          auVar8._12_4_ = -uVar4;
          auVar27 = NEON_sshl(*pauVar1,auVar8,4);
          auVar9._4_4_ = -uVar4;
          auVar9._0_4_ = -uVar4;
          auVar9._8_4_ = -uVar4;
          auVar9._12_4_ = -uVar4;
          auVar28 = NEON_sshl(auVar28,auVar9,4);
          puVar17[-1] = CONCAT26((short)((uint)(auVar27._12_2_ * iVar3) >> 0xf),
                                 CONCAT24((short)((uint)(auVar27._8_2_ * iVar3) >> 0xf),
                                          CONCAT22((short)((uint)(auVar27._4_2_ * iVar3) >> 0xf),
                                                   (short)((uint)(auVar27._0_2_ * iVar3) >> 0xf))));
          *puVar17 = CONCAT26((short)((uint)(auVar28._12_2_ * iVar3) >> 0xf),
                              CONCAT24((short)((uint)(auVar28._8_2_ * iVar3) >> 0xf),
                                       CONCAT22((short)((uint)(auVar28._4_2_ * iVar3) >> 0xf),
                                                (short)((uint)(auVar28._0_2_ * iVar3) >> 0xf))));
          puVar17 = puVar17 + 2;
        } while (uVar22 != 0);
        if (uVar25 == uVar20) goto LAB_00103478;
      }
      do {
        *(short *)(param_3 + lVar16 * 2) =
             (short)((uint)((short)(*(int *)(param_2 + lVar16 * 4) >> (uVar4 & 0x1f)) * iVar3) >>
                    0xf);
        lVar16 = lVar16 + 1;
      } while (lVar16 < (long)uVar15);
    }
LAB_00103478:
  } while ((long)uVar26 < (long)param_5);
  lVar16 = 0;
  lVar19 = param_3 + lVar14 * 2;
  lVar2 = param_2 + lVar14 * 4;
  do {
    iVar13 = ec_ilog(*(undefined4 *)(param_4 + (long)(*(int *)(param_1 + 8) + (int)lVar16) * 4));
    iVar13 = iVar13 * 0x10000 + -0x10000 >> 0x10;
    iVar3 = *(int *)(param_4 + (long)(*(int *)(param_1 + 8) + (int)lVar16) * 4);
    uVar5 = iVar3 >> (iVar13 - 0xdU & 0x1f);
    if ((int)(iVar13 - 0xdU) < 1) {
      uVar5 = iVar3 << (ulong)(0xdU - iVar13 & 0x1f);
    }
    uVar4 = iVar13 - 0xe;
    sVar12 = ssc_rcp(-(uVar5 >> 0xf & 1) & 0xfff80000 | (uVar5 & 0xffff) << 3);
    lVar21 = (long)*(short *)(lVar24 + lVar16 * 2);
    lVar16 = lVar16 + 1;
    iVar3 = (int)sVar12;
    lVar18 = lVar21 * 8;
    uVar25 = (long)*(short *)(lVar24 + lVar16 * 2) * 8;
    uVar26 = lVar21 << 3 | 1;
    if ((int)uVar4 < 1) {
      if ((long)uVar26 <= (long)uVar25) {
        uVar26 = uVar25;
      }
      uVar26 = uVar26 + lVar21 * -8;
      uVar5 = 0xe - iVar13;
      if (7 < uVar26) {
        uVar22 = uVar26 & 0xfffffffffffffff8;
        lVar21 = lVar14 + lVar18;
        lVar18 = uVar22 + lVar18;
        puVar17 = (undefined8 *)(param_3 + 8 + lVar21 * 2);
        pauVar23 = (undefined1 (*) [16])(param_2 + 0x10 + lVar21 * 4);
        uVar15 = uVar22;
        do {
          pauVar1 = pauVar23 + -1;
          auVar28 = *pauVar23;
          uVar15 = uVar15 - 8;
          pauVar23 = pauVar23 + 2;
          auVar6._4_4_ = uVar5;
          auVar6._0_4_ = uVar5;
          auVar6._8_4_ = uVar5;
          auVar6._12_4_ = uVar5;
          auVar27 = NEON_ushl(*pauVar1,auVar6,4);
          auVar7._4_4_ = uVar5;
          auVar7._0_4_ = uVar5;
          auVar7._8_4_ = uVar5;
          auVar7._12_4_ = uVar5;
          auVar28 = NEON_ushl(auVar28,auVar7,4);
          puVar17[-1] = CONCAT26((short)((uint)(auVar27._12_2_ * iVar3) >> 0xf),
                                 CONCAT24((short)((uint)(auVar27._8_2_ * iVar3) >> 0xf),
                                          CONCAT22((short)((uint)(auVar27._4_2_ * iVar3) >> 0xf),
                                                   (short)((uint)(auVar27._0_2_ * iVar3) >> 0xf))));
          *puVar17 = CONCAT26((short)((uint)(auVar28._12_2_ * iVar3) >> 0xf),
                              CONCAT24((short)((uint)(auVar28._8_2_ * iVar3) >> 0xf),
                                       CONCAT22((short)((uint)(auVar28._4_2_ * iVar3) >> 0xf),
                                                (short)((uint)(auVar28._0_2_ * iVar3) >> 0xf))));
          puVar17 = puVar17 + 2;
        } while (uVar15 != 0);
        if (uVar26 == uVar22) goto LAB_00103678;
      }
      do {
        *(short *)(lVar19 + lVar18 * 2) =
             (short)((uint)((short)(*(int *)(lVar2 + lVar18 * 4) << (ulong)(uVar5 & 0x1f)) * iVar3)
                    >> 0xf);
        lVar18 = lVar18 + 1;
      } while (lVar18 < (long)uVar25);
    }
    else {
      if ((long)uVar26 <= (long)uVar25) {
        uVar26 = uVar25;
      }
      uVar26 = uVar26 + lVar21 * -8;
      if (7 < uVar26) {
        uVar22 = uVar26 & 0xfffffffffffffff8;
        lVar21 = lVar14 + lVar18;
        lVar18 = uVar22 + lVar18;
        puVar17 = (undefined8 *)(param_3 + 8 + lVar21 * 2);
        pauVar23 = (undefined1 (*) [16])(param_2 + 0x10 + lVar21 * 4);
        uVar15 = uVar22;
        do {
          pauVar1 = pauVar23 + -1;
          auVar28 = *pauVar23;
          uVar15 = uVar15 - 8;
          pauVar23 = pauVar23 + 2;
          auVar10._4_4_ = -uVar4;
          auVar10._0_4_ = -uVar4;
          auVar10._8_4_ = -uVar4;
          auVar10._12_4_ = -uVar4;
          auVar27 = NEON_sshl(*pauVar1,auVar10,4);
          auVar11._4_4_ = -uVar4;
          auVar11._0_4_ = -uVar4;
          auVar11._8_4_ = -uVar4;
          auVar11._12_4_ = -uVar4;
          auVar28 = NEON_sshl(auVar28,auVar11,4);
          puVar17[-1] = CONCAT26((short)((uint)(auVar27._12_2_ * iVar3) >> 0xf),
                                 CONCAT24((short)((uint)(auVar27._8_2_ * iVar3) >> 0xf),
                                          CONCAT22((short)((uint)(auVar27._4_2_ * iVar3) >> 0xf),
                                                   (short)((uint)(auVar27._0_2_ * iVar3) >> 0xf))));
          *puVar17 = CONCAT26((short)((uint)(auVar28._12_2_ * iVar3) >> 0xf),
                              CONCAT24((short)((uint)(auVar28._8_2_ * iVar3) >> 0xf),
                                       CONCAT22((short)((uint)(auVar28._4_2_ * iVar3) >> 0xf),
                                                (short)((uint)(auVar28._0_2_ * iVar3) >> 0xf))));
          puVar17 = puVar17 + 2;
        } while (uVar15 != 0);
        if (uVar26 == uVar22) goto LAB_00103678;
      }
      do {
        *(short *)(lVar19 + lVar18 * 2) =
             (short)((uint)((short)(*(int *)(lVar2 + lVar18 * 4) >> (uVar4 & 0x1f)) * iVar3) >> 0xf)
        ;
        lVar18 = lVar18 + 1;
      } while (lVar18 < (long)uVar25);
    }
LAB_00103678:
    if (param_5 <= lVar16) {
      return;
    }
  } while( true );
}


/* ssc_pitch_xcorr_c1 @ 00113204 size 316 */

undefined8 ssc_pitch_xcorr_c1(long param_1,undefined1 (*param_2) [16],undefined8 *param_3)

{
  undefined1 (*pauVar1) [16];
  undefined1 auVar2 [16];
  long lVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  int iVar22;
  int iVar23;
  int iVar24;
  undefined1 auVar21 [16];
  int iVar25;
  int iVar26;
  int iVar27;
  int iVar28;
  undefined8 uVar29;
  undefined1 auVar30 [16];
  short sVar31;
  short sVar35;
  short sVar36;
  undefined8 uVar32;
  short sVar37;
  undefined8 uVar33;
  undefined8 uVar34;
  undefined4 uVar38;
  undefined8 uVar39;
  undefined1 auVar40 [16];
  undefined1 auVar41 [16];
  undefined1 auVar42 [16];
  
  iVar8 = 0;
  iVar9 = 0;
  iVar10 = 0;
  iVar11 = 0;
  lVar3 = 0;
  iVar16 = 0;
  iVar17 = 0;
  iVar18 = 0;
  iVar19 = 0;
  iVar20 = 0;
  iVar22 = 0;
  iVar23 = 0;
  iVar24 = 0;
  iVar25 = 0;
  iVar26 = 0;
  iVar27 = 0;
  iVar28 = 0;
  iVar12 = 0;
  iVar13 = 0;
  iVar14 = 0;
  iVar15 = 0;
  auVar30 = *param_2;
  do {
    uVar29 = ((undefined8 *)(param_1 + lVar3))[1];
    uVar32 = *(undefined8 *)(param_1 + lVar3);
    pauVar1 = (undefined1 (*) [16])(param_2[1] + lVar3);
    uVar38 = (undefined4)((ulong)*(undefined8 *)(*pauVar1 + 8) >> 0x20);
    lVar3 = lVar3 + 0x10;
    sVar31 = (short)uVar32;
    sVar35 = (short)((ulong)uVar32 >> 0x10);
    sVar36 = (short)((ulong)uVar32 >> 0x20);
    sVar37 = (short)((ulong)uVar32 >> 0x30);
    auVar40._12_4_ = uVar38;
    auVar40._0_12_ = *(undefined1 (*) [12])*pauVar1;
    auVar40 = NEON_ext(auVar30,auVar40,2,1);
    auVar41._12_4_ = uVar38;
    auVar41._0_12_ = *(undefined1 (*) [12])*pauVar1;
    auVar41 = NEON_ext(auVar30,auVar41,4,1);
    auVar42._12_4_ = uVar38;
    auVar42._0_12_ = *(undefined1 (*) [12])*pauVar1;
    auVar42 = NEON_ext(auVar30,auVar42,6,1);
    sVar4 = (short)uVar29;
    sVar5 = (short)((ulong)uVar29 >> 0x10);
    sVar6 = (short)((ulong)uVar29 >> 0x20);
    sVar7 = (short)((ulong)uVar29 >> 0x30);
    iVar8 = iVar8 + (int)sVar31 * (int)auVar30._0_2_ + (int)sVar4 * (int)auVar30._8_2_;
    iVar9 = iVar9 + (int)sVar35 * (int)auVar30._2_2_ + (int)sVar5 * (int)auVar30._10_2_;
    iVar10 = iVar10 + (int)sVar36 * (int)auVar30._4_2_ + (int)sVar6 * (int)auVar30._12_2_;
    iVar11 = iVar11 + (int)sVar37 * (int)auVar30._6_2_ + (int)sVar7 * (int)auVar30._14_2_;
    auVar2._12_4_ = uVar38;
    auVar2._0_12_ = *(undefined1 (*) [12])*pauVar1;
    auVar30 = NEON_ext(auVar30,auVar2,8,1);
    iVar16 = iVar16 + (int)sVar31 * (int)auVar40._0_2_ + (int)sVar4 * (int)auVar40._8_2_;
    iVar17 = iVar17 + (int)sVar35 * (int)auVar40._2_2_ + (int)sVar5 * (int)auVar40._10_2_;
    iVar18 = iVar18 + (int)sVar36 * (int)auVar40._4_2_ + (int)sVar6 * (int)auVar40._12_2_;
    iVar19 = iVar19 + (int)sVar37 * (int)auVar40._6_2_ + (int)sVar7 * (int)auVar40._14_2_;
    iVar20 = iVar20 + (int)sVar31 * (int)auVar41._0_2_ + (int)sVar4 * (int)auVar41._8_2_;
    iVar22 = iVar22 + (int)sVar35 * (int)auVar41._2_2_ + (int)sVar5 * (int)auVar41._10_2_;
    iVar23 = iVar23 + (int)sVar36 * (int)auVar41._4_2_ + (int)sVar6 * (int)auVar41._12_2_;
    iVar24 = iVar24 + (int)sVar37 * (int)auVar41._6_2_ + (int)sVar7 * (int)auVar41._14_2_;
    iVar25 = iVar25 + (int)sVar31 * (int)auVar42._0_2_ + (int)sVar4 * (int)auVar42._8_2_;
    iVar26 = iVar26 + (int)sVar35 * (int)auVar42._2_2_ + (int)sVar5 * (int)auVar42._10_2_;
    iVar27 = iVar27 + (int)sVar36 * (int)auVar42._4_2_ + (int)sVar6 * (int)auVar42._12_2_;
    iVar28 = iVar28 + (int)sVar37 * (int)auVar42._6_2_ + (int)sVar7 * (int)auVar42._14_2_;
    iVar12 = iVar12 + (int)sVar31 * (int)auVar30._0_2_ + (int)sVar4 * (int)auVar30._8_2_;
    iVar13 = iVar13 + (int)sVar35 * (int)auVar30._2_2_ + (int)sVar5 * (int)auVar30._10_2_;
    iVar14 = iVar14 + (int)sVar36 * (int)auVar30._4_2_ + (int)sVar6 * (int)auVar30._12_2_;
    iVar15 = iVar15 + (int)sVar37 * (int)auVar30._6_2_ + (int)sVar7 * (int)auVar30._14_2_;
    auVar30 = *pauVar1;
  } while ((int)lVar3 != 0x750);
  uVar29 = *(undefined8 *)(param_1 + 0x750);
  uVar33 = *(undefined8 *)param_2[0x75];
  uVar32 = *(undefined8 *)(param_2[0x75] + 2);
  uVar39 = *(undefined8 *)(param_2[0x75] + 4);
  sVar4 = (short)uVar29;
  sVar5 = (short)((ulong)uVar29 >> 0x10);
  sVar6 = (short)((ulong)uVar29 >> 0x20);
  sVar7 = (short)((ulong)uVar29 >> 0x30);
  uVar34 = *(undefined8 *)(param_2[0x75] + 6);
  uVar29 = *(undefined8 *)(param_2[0x75] + 8);
  iVar22 = iVar22 + (int)sVar5 * (int)(short)((ulong)uVar39 >> 0x10);
  iVar23 = iVar23 + (int)sVar6 * (int)(short)((ulong)uVar39 >> 0x20);
  iVar24 = iVar24 + (int)sVar7 * (int)(short)((ulong)uVar39 >> 0x30);
  iVar26 = iVar26 + (int)sVar5 * (int)(short)((ulong)uVar34 >> 0x10);
  iVar27 = iVar27 + (int)sVar6 * (int)(short)((ulong)uVar34 >> 0x20);
  iVar28 = iVar28 + (int)sVar7 * (int)(short)((ulong)uVar34 >> 0x30);
  auVar21._0_4_ = iVar20 + (int)sVar4 * (int)(short)uVar39 + iVar22 + iVar23 + iVar24;
  auVar21._4_4_ = iVar22 * 2 + iVar23 + iVar24;
  auVar21._8_4_ = iVar23 * 2 + iVar22 + iVar24;
  auVar21._12_4_ = iVar24 * 2 + iVar22 + iVar23;
  auVar30._4_4_ = iVar25 + (int)sVar4 * (int)(short)uVar34 + iVar26 + iVar27 + iVar28;
  auVar30._0_4_ = auVar21._0_4_;
  auVar30._8_4_ = auVar21._4_4_;
  auVar30._12_4_ = iVar26 * 2 + iVar27 + iVar28;
  auVar30 = NEON_ext(auVar21,auVar30,8,1);
  param_3[1] = auVar30._8_8_;
  *param_3 = CONCAT44(iVar16 + (int)sVar4 * (int)(short)uVar32 +
                      iVar17 + (int)sVar5 * (int)(short)((ulong)uVar32 >> 0x10) +
                      iVar18 + (int)sVar6 * (int)(short)((ulong)uVar32 >> 0x20) +
                      iVar19 + (int)sVar7 * (int)(short)((ulong)uVar32 >> 0x30),
                      iVar8 + (int)sVar4 * (int)(short)uVar33 +
                      iVar9 + (int)sVar5 * (int)(short)((ulong)uVar33 >> 0x10) +
                      iVar10 + (int)sVar6 * (int)(short)((ulong)uVar33 >> 0x20) +
                      iVar11 + (int)sVar7 * (int)(short)((ulong)uVar33 >> 0x30));
  *(int *)(param_3 + 2) =
       iVar12 + (int)sVar4 * (int)(short)uVar29 +
       iVar13 + (int)sVar5 * (int)(short)((ulong)uVar29 >> 0x10) +
       iVar14 + (int)sVar6 * (int)(short)((ulong)uVar29 >> 0x20) +
       iVar15 + (int)sVar7 * (int)(short)((ulong)uVar29 >> 0x30);
  return 0;
}


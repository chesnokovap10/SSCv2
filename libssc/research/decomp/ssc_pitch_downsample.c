/* ssc_pitch_downsample @ 00111b2c size 1372 */

void ssc_pitch_downsample(int *param_1,int *param_2,short *param_3,uint param_4)

{
  int iVar1;
  uint uVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short *psVar7;
  long lVar8;
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  int *piVar12;
  int *piVar13;
  int *piVar14;
  int *piVar15;
  int *piVar16;
  int *piVar17;
  int *piVar18;
  bool bVar19;
  short *psVar20;
  uint uVar21;
  long lVar22;
  int *piVar23;
  ulong uVar24;
  long lVar25;
  int *piVar26;
  ulong uVar27;
  int iVar28;
  ulong uVar29;
  int iVar30;
  undefined8 uVar31;
  undefined1 auVar32 [16];
  undefined1 auVar33 [16];
  int iVar35;
  undefined1 auVar34 [16];
  undefined1 auVar36 [16];
  undefined1 auVar37 [16];
  undefined1 auVar38 [16];
  short sVar39;
  undefined1 auVar40 [16];
  undefined1 auVar41 [16];
  undefined1 auVar42 [16];
  short sVar46;
  short sVar47;
  short sVar48;
  undefined1 auVar43 [16];
  undefined1 auVar44 [16];
  undefined1 auVar45 [16];
  undefined1 auVar49 [16];
  undefined1 auVar50 [16];
  undefined8 uVar51;
  undefined8 uVar52;
  undefined8 uVar53;
  undefined8 uVar54;
  undefined8 uVar55;
  short sVar57;
  short sVar58;
  undefined8 uVar56;
  short sVar59;
  short sVar60;
  short sVar61;
  short sVar62;
  short sVar64;
  short sVar65;
  undefined8 uVar63;
  short sVar66;
  undefined8 uVar67;
  undefined8 uVar68;
  undefined8 uVar69;
  short local_48;
  short local_46;
  short local_44;
  short local_42;
  undefined8 local_40;
  undefined8 local_38;
  int local_30;
  long local_28;
  
  lVar8 = tpidr_el0;
  local_28 = *(long *)(lVar8 + 0x28);
  uVar21 = 0;
  auVar33 = ZEXT816(0);
  uVar2 = param_4 * 2;
  local_40 = 0;
  local_38 = 0;
  local_30 = 0;
  piVar23 = param_1;
  if (0xf < (int)uVar2) {
    do {
      uVar21 = uVar21 + 0x10;
      auVar32._0_4_ = MP_INT_ABS(*piVar23);
      auVar32._4_4_ = MP_INT_ABS(piVar23[1]);
      auVar32._8_4_ = MP_INT_ABS(piVar23[2]);
      auVar32._12_4_ = MP_INT_ABS(piVar23[3]);
      auVar50._0_4_ = MP_INT_ABS(piVar23[4]);
      auVar50._4_4_ = MP_INT_ABS(piVar23[5]);
      auVar50._8_4_ = MP_INT_ABS(piVar23[6]);
      auVar50._12_4_ = MP_INT_ABS(piVar23[7]);
      auVar32 = NEON_smax(auVar33,auVar32,4);
      piVar26 = piVar23 + 8;
      piVar12 = piVar23 + 9;
      piVar13 = piVar23 + 10;
      piVar14 = piVar23 + 0xb;
      auVar33 = *(undefined1 (*) [16])(piVar23 + 0xc);
      piVar23 = piVar23 + 0x10;
      auVar32 = NEON_smax(auVar32,auVar50,4);
      auVar45._0_4_ = MP_INT_ABS(*piVar26);
      auVar45._4_4_ = MP_INT_ABS(*piVar12);
      auVar45._8_4_ = MP_INT_ABS(*piVar13);
      auVar45._12_4_ = MP_INT_ABS(*piVar14);
      auVar40._0_4_ = MP_INT_ABS(auVar33._0_4_);
      auVar40._4_4_ = MP_INT_ABS(auVar33._4_4_);
      auVar40._8_4_ = MP_INT_ABS(auVar33._8_4_);
      auVar40._12_4_ = MP_INT_ABS(auVar33._12_4_);
      auVar33 = NEON_smax(auVar32,auVar45,4);
      auVar33 = NEON_smax(auVar33,auVar40,4);
    } while ((int)uVar21 < (int)(uVar2 - 0xf));
    uVar21 = uVar2 & 0xfffffff0;
  }
  auVar32 = NEON_ext(auVar33,auVar33,8,1);
  uVar31 = NEON_smax(auVar32._0_8_,auVar33._0_8_,4);
  iVar35 = (int)((ulong)uVar31 >> 0x20);
  iVar30 = (int)uVar31;
  if ((int)uVar31 <= iVar35) {
    iVar30 = iVar35;
  }
  if ((int)uVar21 < (int)uVar2) {
    uVar2 = (uVar2 - uVar21) - 2;
    if (5 < uVar2) {
      uVar24 = (ulong)uVar2 + 2;
      auVar33._0_8_ = CONCAT44(iVar30,iVar30);
      auVar33._8_4_ = iVar30;
      auVar33._12_4_ = iVar30;
      uVar29 = uVar24 & 0x1fffffff8;
      auVar36._8_8_ = auVar33._8_8_;
      auVar36._0_8_ = auVar33._0_8_;
      uVar21 = uVar21 + (int)uVar29;
      piVar26 = piVar23 + 4;
      uVar27 = uVar29;
      do {
        piVar12 = piVar26 + -4;
        piVar13 = piVar26 + -3;
        piVar14 = piVar26 + -2;
        piVar15 = piVar26 + -1;
        iVar30 = *piVar26;
        piVar16 = piVar26 + 1;
        piVar17 = piVar26 + 2;
        piVar18 = piVar26 + 3;
        piVar26 = piVar26 + 8;
        uVar27 = uVar27 - 8;
        auVar41._0_4_ = MP_INT_ABS(*piVar12);
        auVar41._4_4_ = MP_INT_ABS(*piVar13);
        auVar41._8_4_ = MP_INT_ABS(*piVar14);
        auVar41._12_4_ = MP_INT_ABS(*piVar15);
        auVar43._0_4_ = MP_INT_ABS(iVar30);
        auVar43._4_4_ = MP_INT_ABS(*piVar16);
        auVar43._8_4_ = MP_INT_ABS(*piVar17);
        auVar43._12_4_ = MP_INT_ABS(*piVar18);
        auVar33 = NEON_smax(auVar33,auVar41,4);
        auVar36 = NEON_smax(auVar36,auVar43,4);
      } while (uVar27 != 0);
      auVar33 = NEON_smax(auVar33,auVar36,4);
      iVar30 = NEON_smaxv(auVar33,4);
      piVar23 = piVar23 + uVar29;
      if (uVar24 == uVar29) goto LAB_00111c60;
    }
    iVar35 = uVar21 + param_4 * -2;
    do {
      iVar1 = *piVar23;
      iVar28 = -iVar1;
      if (-1 < iVar1) {
        iVar28 = iVar1;
      }
      if (iVar30 <= iVar28) {
        iVar30 = iVar28;
      }
      bVar19 = iVar35 != -1;
      iVar35 = iVar35 + 1;
      piVar23 = piVar23 + 1;
    } while (bVar19);
  }
LAB_00111c60:
  if (iVar30 < 2) {
    iVar30 = 1;
  }
  uVar21 = 0x15 - (int)LZCOUNT(iVar30);
  uVar21 = (uVar21 & ((int)uVar21 >> 0x1f ^ 0xffffffffU)) + 1;
  *param_3 = (short)((*param_1 + (param_1[1] >> 1) >> 1) >> (uVar21 & 0x1f)) +
             (short)((*param_2 + (param_2[1] >> 1) >> 1) >> (uVar21 & 0x1f));
  if (3 < (int)param_4) {
    uVar24 = (ulong)(param_4 >> 1) - 1;
    if (uVar24 < 9) {
      lVar25 = 1;
    }
    else {
      uVar27 = 8;
      if ((uVar24 & 7) != 0) {
        uVar27 = uVar24 & 7;
      }
      lVar22 = uVar24 - uVar27;
      auVar34._0_4_ = -uVar21;
      auVar34._4_4_ = -uVar21;
      auVar34._8_4_ = -uVar21;
      auVar34._12_4_ = -uVar21;
      lVar25 = lVar22 + 1;
      piVar23 = param_2 + 2;
      piVar26 = param_1 + 2;
      psVar20 = param_3 + 1;
      do {
        lVar22 = lVar22 + -8;
        auVar37._0_4_ = *piVar26 + (piVar26[1] + piVar26[-1] >> 1) >> 1;
        auVar37._4_4_ = piVar26[2] + (piVar26[3] + piVar26[1] >> 1) >> 1;
        auVar37._8_4_ = piVar26[4] + (piVar26[5] + piVar26[3] >> 1) >> 1;
        auVar37._12_4_ = piVar26[6] + (piVar26[7] + piVar26[5] >> 1) >> 1;
        auVar33 = NEON_sshl(auVar37,auVar34,4);
        auVar42._0_4_ = piVar26[8] + (piVar26[9] + piVar26[7] >> 1) >> 1;
        auVar42._4_4_ = piVar26[10] + (piVar26[0xb] + piVar26[9] >> 1) >> 1;
        auVar42._8_4_ = piVar26[0xc] + (piVar26[0xd] + piVar26[0xb] >> 1) >> 1;
        auVar42._12_4_ = piVar26[0xe] + (piVar26[0xf] + piVar26[0xd] >> 1) >> 1;
        auVar32 = NEON_sshl(auVar42,auVar34,4);
        auVar49._0_4_ = *piVar23 + (piVar23[1] + piVar23[-1] >> 1) >> 1;
        auVar49._4_4_ = piVar23[2] + (piVar23[3] + piVar23[1] >> 1) >> 1;
        auVar49._8_4_ = piVar23[4] + (piVar23[5] + piVar23[3] >> 1) >> 1;
        auVar49._12_4_ = piVar23[6] + (piVar23[7] + piVar23[5] >> 1) >> 1;
        auVar50 = NEON_sshl(auVar49,auVar34,4);
        auVar44._0_4_ = piVar23[8] + (piVar23[9] + piVar23[7] >> 1) >> 1;
        auVar44._4_4_ = piVar23[10] + (piVar23[0xb] + piVar23[9] >> 1) >> 1;
        auVar44._8_4_ = piVar23[0xc] + (piVar23[0xd] + piVar23[0xb] >> 1) >> 1;
        auVar44._12_4_ = piVar23[0xe] + (piVar23[0xf] + piVar23[0xd] >> 1) >> 1;
        auVar45 = NEON_sshl(auVar44,auVar34,4);
        auVar38._0_8_ =
             CONCAT26((short)(auVar50._12_4_ + auVar33._12_4_),
                      CONCAT24(auVar50._8_2_ + auVar33._8_2_,
                               CONCAT22(auVar50._4_2_ + auVar33._4_2_,auVar50._0_2_ + auVar33._0_2_)
                              ));
        auVar38._8_2_ = auVar45._0_2_ + auVar32._0_2_;
        auVar38._10_2_ = auVar45._4_2_ + auVar32._4_2_;
        auVar38._12_2_ = auVar45._8_2_ + auVar32._8_2_;
        auVar38._14_2_ = auVar45._12_2_ + auVar32._12_2_;
        *(long *)(psVar20 + 4) = auVar38._8_8_;
        *(undefined8 *)psVar20 = auVar38._0_8_;
        piVar23 = piVar23 + 0x10;
        piVar26 = piVar26 + 0x10;
        psVar20 = psVar20 + 8;
      } while (lVar22 != 0);
    }
    lVar22 = (ulong)(param_4 >> 1) - lVar25;
    param_1 = param_1 + lVar25 * 2;
    param_2 = param_2 + lVar25 * 2;
    psVar20 = param_3 + lVar25;
    do {
      piVar12 = param_1 + -1;
      iVar30 = *param_1;
      piVar13 = param_2 + -1;
      iVar35 = *param_2;
      piVar23 = param_2 + 1;
      lVar22 = lVar22 + -1;
      piVar26 = param_1 + 1;
      param_1 = param_1 + 2;
      param_2 = param_2 + 2;
      *psVar20 = (short)((iVar35 + (*piVar23 + *piVar13 >> 1) >> 1) >> (uVar21 & 0x1f)) +
                 (short)((iVar30 + (*piVar26 + *piVar12 >> 1) >> 1) >> (uVar21 & 0x1f));
      psVar20 = psVar20 + 1;
    } while (lVar22 != 0);
  }
  _ssc_autocorr(param_3,&local_40);
  uVar31 = NEON_sshl(local_40,0xfffffff2fffffff3,4);
  local_40 = CONCAT44((int)((ulong)local_40 >> 0x20) - (int)((ulong)uVar31 >> 0x20),
                      (int)local_40 + (int)uVar31);
  local_30 = local_30 - (local_30 >> 10);
  local_38 = CONCAT44((local_38._4_4_ + ((int)local_38._4_4_ >> 0x10) * -0x24) -
                      ((local_38._4_4_ & 0xffff) + (local_38._4_4_ & 0xffff) * 8 >> 0xe),
                      (int)local_38 - ((int)local_38 >> 0xc));
  _ssc_lpc(&local_48,&local_40);
  sVar39 = param_3[1];
  sVar3 = (short)((uint)(local_48 * 0x7332) >> 0xf) + 0xccd;
  sVar4 = (short)((uint)(local_46 * 0x67ac) >> 0xf) +
          (short)((uint)((local_48 * 0xe664 >> 0x10) * 0x6666) >> 0xf);
  sVar46 = *param_3;
  iVar30 = (int)sVar3;
  sVar47 = param_3[2];
  sVar5 = (short)((uint)(local_44 * 0x5d4d) >> 0xf) +
          (short)((uint)((local_46 * 0xcf58 >> 0x10) * 0x6666) >> 0xf);
  iVar35 = (int)sVar4;
  sVar6 = (short)((uint)(local_42 * 0x53f8) >> 0xf) +
          (short)((uint)((local_44 * 0xba9a >> 0x10) * 0x6666) >> 0xf);
  iVar28 = (int)sVar46;
  uVar55 = CONCAT26(param_3[3] +
                    (short)(sVar47 * iVar30 + sVar39 * iVar35 + sVar5 * iVar28 + 0x800U >> 0xc),
                    CONCAT24(sVar47 + (short)(sVar39 * iVar30 + iVar35 * iVar28 + 0x800U >> 0xc),
                             CONCAT22(sVar39 + (short)(sVar46 * iVar30 + 0x800U >> 0xc),sVar46)));
  lVar25 = (ulong)(ushort)(param_3[4] +
                          (short)((int)sVar5 * (int)sVar39 + sVar47 * iVar35 + param_3[3] * iVar30 +
                                  sVar6 * iVar28 + 0x800U >> 0xc)) << 0x30;
  psVar20 = param_3 + 0xc;
  uVar24 = 0xfffffffffffffffd;
  sVar39 = (short)((uint)((local_42 * 0xa7f0 >> 0x10) * 0x6666) >> 0xf);
  uVar51 = *(undefined8 *)(param_3 + 4);
  uVar52 = *(undefined8 *)(param_3 + 8);
  uVar31 = *(undefined8 *)param_3;
  do {
    uVar54 = uVar52;
    *(undefined8 *)(psVar20 + -0xc) = uVar55;
    uVar24 = uVar24 + 8;
    uVar55 = NEON_ext(uVar31,uVar51,6,1);
    uVar52 = NEON_ext(uVar51,uVar54,6,1);
    uVar63 = NEON_ext(uVar51,uVar54,2,1);
    uVar53 = *(undefined8 *)psVar20;
    psVar7 = psVar20 + 4;
    sVar64 = (short)((ulong)uVar63 >> 0x10);
    sVar65 = (short)((ulong)uVar63 >> 0x20);
    sVar66 = (short)((ulong)uVar63 >> 0x30);
    sVar60 = (short)((ulong)uVar51 >> 0x10);
    sVar61 = (short)((ulong)uVar51 >> 0x20);
    sVar62 = (short)((ulong)uVar51 >> 0x30);
    uVar56 = NEON_ext(uVar54,uVar53,2,1);
    sVar46 = (short)((ulong)uVar54 >> 0x10);
    sVar47 = (short)((ulong)uVar54 >> 0x20);
    sVar48 = (short)((ulong)uVar54 >> 0x30);
    uVar67 = NEON_ext(uVar31,uVar51,4,1);
    sVar57 = (short)((ulong)uVar56 >> 0x10);
    sVar58 = (short)((ulong)uVar56 >> 0x20);
    sVar59 = (short)((ulong)uVar56 >> 0x30);
    uVar68 = NEON_ext(uVar31,uVar51,2,1);
    uVar69 = NEON_ext(uVar51,uVar54,4,1);
    iVar30 = (int)sVar4 * (int)(short)((ulong)uVar52 >> 0x10) + (int)sVar3 * (int)sVar46 +
             sVar57 * 0x1000 + (int)sVar5 * (int)(short)((ulong)uVar69 >> 0x10) +
             (int)sVar6 * (int)sVar64 + (int)sVar39 * (int)sVar60;
    auVar11._4_4_ =
         (int)sVar4 * (int)(short)((ulong)uVar55 >> 0x10) + (int)sVar3 * (int)sVar60 +
         sVar64 * 0x1000 + (int)sVar5 * (int)(short)((ulong)uVar67 >> 0x10) +
         (int)sVar6 * (int)(short)((ulong)uVar68 >> 0x10) +
         (int)sVar39 * (int)(short)((ulong)uVar31 >> 0x10);
    auVar11._0_4_ =
         (int)sVar4 * (int)(short)uVar55 + (int)sVar3 * (int)(short)uVar51 + (short)uVar63 * 0x1000
         + (int)sVar5 * (int)(short)uVar67 + (int)sVar6 * (int)(short)uVar68 +
         (int)sVar39 * (int)(short)uVar31;
    auVar11._8_4_ =
         (int)sVar4 * (int)(short)((ulong)uVar55 >> 0x20) + (int)sVar3 * (int)sVar61 +
         sVar65 * 0x1000 + (int)sVar5 * (int)(short)((ulong)uVar67 >> 0x20) +
         (int)sVar6 * (int)(short)((ulong)uVar68 >> 0x20) +
         (int)sVar39 * (int)(short)((ulong)uVar31 >> 0x20);
    auVar11._12_4_ =
         (int)sVar4 * (int)(short)((ulong)uVar55 >> 0x30) + (int)sVar3 * (int)sVar62 +
         sVar66 * 0x1000 + (int)sVar5 * (int)(short)((ulong)uVar67 >> 0x30) +
         (int)sVar6 * (int)(short)((ulong)uVar68 >> 0x30) +
         (int)sVar39 * (int)(short)((ulong)uVar31 >> 0x30);
    auVar33 = NEON_srshr(auVar11,0xc,4);
    auVar10._4_2_ = (short)iVar30;
    auVar10._0_4_ =
         (int)sVar4 * (int)(short)uVar52 + (int)sVar3 * (int)(short)uVar54 + (short)uVar56 * 0x1000
         + (int)sVar5 * (int)(short)uVar69 + (int)sVar6 * (int)(short)uVar63 +
         (int)sVar39 * (int)(short)uVar51;
    auVar10._6_2_ = (short)((uint)iVar30 >> 0x10);
    auVar10._8_4_ =
         (int)sVar4 * (int)(short)((ulong)uVar52 >> 0x20) + (int)sVar3 * (int)sVar47 +
         sVar58 * 0x1000 + (int)sVar5 * (int)(short)((ulong)uVar69 >> 0x20) +
         (int)sVar6 * (int)sVar65 + (int)sVar39 * (int)sVar61;
    auVar10._12_4_ =
         (int)sVar4 * (int)(short)((ulong)uVar52 >> 0x30) + (int)sVar3 * (int)sVar48 +
         sVar59 * 0x1000 + (int)sVar5 * (int)(short)((ulong)uVar69 >> 0x30) +
         (int)sVar6 * (int)sVar66 + (int)sVar39 * (int)sVar62;
    auVar32 = NEON_srshr(auVar10,0xc,4);
    uVar51 = CONCAT26(auVar33._12_2_,CONCAT24(auVar33._8_2_,CONCAT22(auVar33._4_2_,auVar33._0_2_)));
    uVar31 = NEON_ext(lVar25,uVar51,6,1);
    lVar25 = CONCAT26(auVar32._12_2_,CONCAT24(auVar32._8_2_,CONCAT22(auVar32._4_2_,auVar32._0_2_)));
    uVar55 = NEON_ext(uVar51,lVar25,6,1);
    *(undefined8 *)(psVar20 + -8) = uVar31;
    psVar20 = psVar20 + 8;
    uVar51 = uVar53;
    uVar52 = *(undefined8 *)psVar7;
    uVar31 = uVar54;
  } while (uVar24 < 0x3a5);
  uVar31 = NEON_ext(uVar53,*(undefined8 *)psVar7,2,1);
  uVar52 = NEON_ext(uVar54,uVar53,4,1);
  *(undefined8 *)(param_3 + 0x3a8) = uVar55;
  uVar51 = NEON_ext(uVar54,uVar53,6,1);
  iVar30 = (short)((ulong)uVar31 >> 0x10) * 0x1000 +
           (int)sVar3 * (int)(short)((ulong)uVar53 >> 0x10) +
           (int)sVar4 * (int)(short)((ulong)uVar51 >> 0x10) +
           (int)sVar5 * (int)(short)((ulong)uVar52 >> 0x10) + (int)sVar6 * (int)sVar57 +
           (int)sVar39 * (int)sVar46;
  auVar9._4_2_ = (short)iVar30;
  auVar9._0_4_ = (short)uVar31 * 0x1000 + (int)sVar3 * (int)(short)uVar53 +
                 (int)sVar4 * (int)(short)uVar51 + (int)sVar5 * (int)(short)uVar52 +
                 (int)sVar6 * (int)(short)uVar56 + (int)sVar39 * (int)(short)uVar54;
  auVar9._6_2_ = (short)((uint)iVar30 >> 0x10);
  auVar9._8_4_ = (short)((ulong)uVar31 >> 0x20) * 0x1000 +
                 (int)sVar3 * (int)(short)((ulong)uVar53 >> 0x20) +
                 (int)sVar4 * (int)(short)((ulong)uVar51 >> 0x20) +
                 (int)sVar5 * (int)(short)((ulong)uVar52 >> 0x20) + (int)sVar6 * (int)sVar58 +
                 (int)sVar39 * (int)sVar47;
  auVar9._12_4_ =
       (short)((ulong)uVar31 >> 0x30) * 0x1000 + (int)sVar3 * (int)(short)((ulong)uVar53 >> 0x30) +
       (int)sVar4 * (int)(short)((ulong)uVar51 >> 0x30) +
       (int)sVar5 * (int)(short)((ulong)uVar52 >> 0x30) + (int)sVar6 * (int)sVar59 +
       (int)sVar39 * (int)sVar48;
  auVar33 = NEON_srshr(auVar9,0xc,4);
  uVar31 = NEON_ext(lVar25,CONCAT26(auVar33._12_2_,
                                    CONCAT24(auVar33._8_2_,CONCAT22(auVar33._4_2_,auVar33._0_2_))),6
                    ,1);
  *(undefined8 *)(param_3 + 0x3ac) = uVar31;
  if (*(long *)(lVar8 + 0x28) != local_28) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}


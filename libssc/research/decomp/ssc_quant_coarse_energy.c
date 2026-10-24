/* ssc_quant_coarse_energy @ 00113340 size 1012 */

void ssc_quant_coarse_energy
               (long param_1,undefined8 param_2,int param_3,long param_4,long param_5,uint param_6,
               undefined8 param_7,long *param_8,int param_9,int param_10,uint *param_11)

{
  bool bVar1;
  void *__src;
  uint uVar2;
  uint uVar3;
  long lVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined8 uVar9;
  undefined8 uVar10;
  short *psVar11;
  short *psVar12;
  short *psVar13;
  short *psVar14;
  short *psVar15;
  short *psVar16;
  short *psVar17;
  short *psVar18;
  short *psVar19;
  short *psVar20;
  short *psVar21;
  short *psVar22;
  short *psVar23;
  short *psVar24;
  int iVar25;
  int iVar26;
  int iVar27;
  ulong uVar28;
  long lVar29;
  ulong uVar30;
  short *psVar31;
  undefined8 *puVar32;
  short *psVar33;
  ulong uVar34;
  long *plVar35;
  long lVar36;
  uint uVar37;
  long lVar38;
  int iVar39;
  long lVar40;
  int iVar41;
  int iVar42;
  int iVar43;
  int iVar44;
  int iVar45;
  int iVar46;
  int iVar47;
  int iVar48;
  int iVar49;
  int iVar50;
  int iVar51;
  int iVar52;
  short sVar53;
  short sVar54;
  short sVar55;
  short sVar56;
  short sVar57;
  short sVar58;
  short sVar59;
  short sVar60;
  short sVar61;
  short sVar62;
  short sVar63;
  short sVar64;
  short sVar65;
  short sVar66;
  short sVar67;
  short sVar68;
  undefined1 auVar69 [16];
  undefined1 auVar70 [16];
  undefined1 auStack_228 [152];
  long local_190;
  long lStack_188;
  long local_180;
  long local_170;
  long lStack_168;
  long local_160;
  long local_150;
  undefined4 uStack_148;
  undefined4 uStack_144;
  undefined4 uStack_140;
  undefined8 uStack_13c;
  undefined1 auStack_130 [92];
  undefined1 auStack_d4 [92];
  long local_78;
  
  uVar37 = param_3 * 2;
  uVar28 = (ulong)uVar37;
  lVar4 = tpidr_el0;
  local_78 = *(long *)(lVar4 + 0x28);
  if ((int)uVar37 < 1) {
    uVar37 = 0;
  }
  else {
    if (uVar37 < 0x10) {
      uVar30 = 0;
      uVar37 = 0;
LAB_00113440:
      lVar29 = uVar28 - uVar30;
      psVar31 = (short *)(param_5 + uVar30 * 2);
      psVar33 = (short *)(param_4 + uVar30 * 2);
      do {
        lVar29 = lVar29 + -1;
        iVar25 = ((int)*psVar33 >> 3) - ((int)*psVar31 >> 3);
        uVar37 = uVar37 + iVar25 * iVar25;
        psVar31 = psVar31 + 1;
        psVar33 = psVar33 + 1;
      } while (lVar29 != 0);
    }
    else {
      uVar30 = uVar28 & 0xfffffff0;
      puVar32 = (undefined8 *)(param_4 + 0x10);
      iVar25 = 0;
      iVar27 = 0;
      iVar39 = 0;
      iVar26 = 0;
      psVar31 = (short *)(param_5 + 0x10);
      iVar41 = 0;
      iVar42 = 0;
      iVar43 = 0;
      iVar44 = 0;
      iVar45 = 0;
      iVar46 = 0;
      iVar47 = 0;
      iVar48 = 0;
      iVar49 = 0;
      iVar50 = 0;
      iVar51 = 0;
      iVar52 = 0;
      uVar34 = uVar30;
      do {
        uVar6 = puVar32[-1];
        uVar5 = puVar32[-2];
        uVar10 = puVar32[1];
        uVar9 = *puVar32;
        puVar32 = puVar32 + 4;
        uVar34 = uVar34 - 0x10;
        psVar33 = psVar31 + -8;
        psVar11 = psVar31 + -7;
        psVar12 = psVar31 + -6;
        psVar13 = psVar31 + -5;
        psVar14 = psVar31 + -4;
        psVar15 = psVar31 + -3;
        psVar16 = psVar31 + -2;
        psVar17 = psVar31 + -1;
        sVar61 = *psVar31;
        psVar18 = psVar31 + 1;
        psVar19 = psVar31 + 2;
        psVar20 = psVar31 + 3;
        psVar21 = psVar31 + 4;
        psVar22 = psVar31 + 5;
        psVar23 = psVar31 + 6;
        psVar24 = psVar31 + 7;
        psVar31 = psVar31 + 0x10;
        sVar53 = ((short)uVar5 >> 3) - (*psVar33 >> 3);
        sVar54 = ((short)((ulong)uVar5 >> 0x10) >> 3) - (*psVar11 >> 3);
        sVar55 = ((short)((ulong)uVar5 >> 0x20) >> 3) - (*psVar12 >> 3);
        sVar56 = (short)((long)uVar5 >> 0x33) - (*psVar13 >> 3);
        sVar57 = ((short)uVar6 >> 3) - (*psVar14 >> 3);
        sVar58 = ((short)((ulong)uVar6 >> 0x10) >> 3) - (*psVar15 >> 3);
        sVar59 = ((short)((ulong)uVar6 >> 0x20) >> 3) - (*psVar16 >> 3);
        sVar60 = (short)((long)uVar6 >> 0x33) - (*psVar17 >> 3);
        sVar61 = ((short)uVar9 >> 3) - (sVar61 >> 3);
        sVar62 = ((short)((ulong)uVar9 >> 0x10) >> 3) - (*psVar18 >> 3);
        sVar63 = ((short)((ulong)uVar9 >> 0x20) >> 3) - (*psVar19 >> 3);
        sVar64 = (short)((long)uVar9 >> 0x33) - (*psVar20 >> 3);
        sVar65 = ((short)uVar10 >> 3) - (*psVar21 >> 3);
        sVar66 = ((short)((ulong)uVar10 >> 0x10) >> 3) - (*psVar22 >> 3);
        sVar67 = ((short)((ulong)uVar10 >> 0x20) >> 3) - (*psVar23 >> 3);
        sVar68 = (short)((long)uVar10 >> 0x33) - (*psVar24 >> 3);
        auVar69._2_2_ = sVar54;
        auVar69._0_2_ = sVar53;
        auVar69._4_2_ = sVar55;
        auVar69._6_2_ = sVar56;
        auVar69._8_2_ = sVar57;
        auVar69._10_2_ = sVar58;
        auVar69._12_2_ = sVar59;
        auVar69._14_2_ = sVar60;
        auVar70._2_2_ = sVar54;
        auVar70._0_2_ = sVar53;
        auVar70._4_2_ = sVar55;
        auVar70._6_2_ = sVar56;
        auVar70._8_2_ = sVar57;
        auVar70._10_2_ = sVar58;
        auVar70._12_2_ = sVar59;
        auVar70._14_2_ = sVar60;
        auVar69 = NEON_ext(auVar69,auVar70,8,1);
        iVar25 = iVar25 + (int)sVar53 * (int)sVar53;
        iVar27 = iVar27 + (int)sVar54 * (int)sVar54;
        iVar39 = iVar39 + (int)sVar55 * (int)sVar55;
        iVar26 = iVar26 + (int)sVar56 * (int)sVar56;
        auVar7._2_2_ = sVar62;
        auVar7._0_2_ = sVar61;
        auVar7._4_2_ = sVar63;
        auVar7._6_2_ = sVar64;
        auVar7._8_2_ = sVar65;
        auVar7._10_2_ = sVar66;
        auVar7._12_2_ = sVar67;
        auVar7._14_2_ = sVar68;
        auVar8._2_2_ = sVar62;
        auVar8._0_2_ = sVar61;
        auVar8._4_2_ = sVar63;
        auVar8._6_2_ = sVar64;
        auVar8._8_2_ = sVar65;
        auVar8._10_2_ = sVar66;
        auVar8._12_2_ = sVar67;
        auVar8._14_2_ = sVar68;
        auVar70 = NEON_ext(auVar7,auVar8,8,1);
        iVar45 = iVar45 + (int)sVar61 * (int)sVar61;
        iVar46 = iVar46 + (int)sVar62 * (int)sVar62;
        iVar47 = iVar47 + (int)sVar63 * (int)sVar63;
        iVar48 = iVar48 + (int)sVar64 * (int)sVar64;
        iVar41 = iVar41 + (int)auVar69._0_2_ * (int)auVar69._0_2_;
        iVar42 = iVar42 + (int)auVar69._2_2_ * (int)auVar69._2_2_;
        iVar43 = iVar43 + (int)auVar69._4_2_ * (int)auVar69._4_2_;
        iVar44 = iVar44 + (int)auVar69._6_2_ * (int)auVar69._6_2_;
        iVar49 = iVar49 + (int)auVar70._0_2_ * (int)auVar70._0_2_;
        iVar50 = iVar50 + (int)auVar70._2_2_ * (int)auVar70._2_2_;
        iVar51 = iVar51 + (int)auVar70._4_2_ * (int)auVar70._4_2_;
        iVar52 = iVar52 + (int)auVar70._6_2_ * (int)auVar70._6_2_;
      } while (uVar34 != 0);
      uVar37 = iVar45 + iVar25 + iVar49 + iVar41 + iVar46 + iVar27 + iVar50 + iVar42 +
               iVar47 + iVar39 + iVar51 + iVar43 + iVar48 + iVar26 + iVar52 + iVar44;
      if (uVar30 != uVar28) goto LAB_00113440;
    }
    if (uVar37 >> 0x11 < 0x19) {
      uVar37 = uVar37 >> 0xe;
    }
    else {
      uVar37 = 200;
    }
  }
  local_150 = *param_8;
  param_9 = param_9 * 0x80;
  plVar35 = param_8 + 4;
  if (0x3fff < param_9) {
    param_9 = 0x4000;
  }
  uStack_148 = (undefined4)param_8[1];
  uVar2 = *(uint *)((long)param_8 + 0x1c);
  uStack_13c = *(undefined8 *)((long)param_8 + 0x14);
  uStack_144 = (undefined4)*(undefined8 *)((long)param_8 + 0xc);
  uStack_140 = (undefined4)((ulong)*(undefined8 *)((long)param_8 + 0xc) >> 0x20);
  iVar25 = (int)param_8[3] + (int)LZCOUNT((int)*plVar35);
  local_160 = param_8[6];
  lStack_168 = param_8[5];
  local_170 = *plVar35;
  iVar27 = iVar25 + -0x20;
  uVar3 = iVar25 - 0x1d;
  SSC_COPY16(auStack_d4,param_5,*(int *)(param_1 + 8) << 1);
  bVar1 = param_6 > uVar3 || uVar3 == param_6;
  if (param_6 <= uVar3 && uVar3 != param_6) {
    iVar25 = 0;
LAB_00113578:
    iVar26 = ssc_ec_tell_frac(param_8);
    lVar29 = param_8[3];
    iVar39 = *(int *)((long)param_8 + 0x1c);
    lVar36 = *param_8;
    lVar40 = param_8[2];
    lVar38 = param_8[1];
    local_180 = param_8[6];
    lStack_188 = param_8[5];
    local_190 = *plVar35;
    __src = (void *)(lVar36 + (ulong)uVar2);
    uVar3 = iVar39 - uVar2;
    if (uVar3 < 0x96) {
      if (uVar3 != 0) {
        memcpy(auStack_228,__src,(ulong)(iVar39 + ~uVar2) + 1);
      }
    }
    else {
      bVar1 = false;
    }
    *(uint *)((long)param_8 + 0x1c) = uVar2;
    param_8[1] = CONCAT44(uStack_144,uStack_148);
    *param_8 = local_150;
    *(undefined8 *)((long)param_8 + 0x14) = uStack_13c;
    *(ulong *)((long)param_8 + 0xc) = CONCAT44(uStack_140,uStack_144);
    param_8[5] = lStack_168;
    *plVar35 = local_170;
    param_8[6] = local_160;
    iVar27 = FUN_00113734(param_1,param_3,param_4,param_5,param_6,iVar27,&DAT_00105dbf,param_7,
                          param_8,0,(short)param_9);
    if ((!bVar1) ||
       ((iVar27 <= iVar25 &&
        ((iVar25 != iVar27 || (iVar25 = ssc_ec_tell_frac(param_8), iVar25 <= iVar26)))))) {
      uVar37 = uVar37 + ((int)*param_11 >> 2);
      goto LAB_001136f4;
    }
    *param_8 = lVar36;
    *(int *)((long)param_8 + 0x1c) = iVar39;
    param_8[2] = lVar40;
    param_8[1] = lVar38;
    *(int *)(param_8 + 3) = (int)lVar29;
    param_8[5] = lStack_188;
    *plVar35 = local_190;
    param_8[6] = local_180;
    if (uVar3 - 1 < 0x95) {
      memcpy(__src,auStack_228,(ulong)uVar3);
    }
    SSC_COPY16(param_5,auStack_d4,*(int *)(param_1 + 8) << 1);
    iVar25 = *(int *)(param_1 + 8);
  }
  else {
    iVar25 = FUN_00113734(param_1,param_3,param_4,auStack_d4,param_6,iVar27,&DAT_00105d91,
                          auStack_130,param_8,1,(short)param_9);
    if ((param_10 == 0) || (param_6 < uVar3)) goto LAB_00113578;
    SSC_COPY16(param_5,auStack_d4,*(int *)(param_1 + 8) << 1);
    iVar25 = *(int *)(param_1 + 8);
  }
  SSC_COPY16(param_7,auStack_130,iVar25 << 1);
LAB_001136f4:
  *param_11 = uVar37;
  if (*(long *)(lVar4 + 0x28) != local_78) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}


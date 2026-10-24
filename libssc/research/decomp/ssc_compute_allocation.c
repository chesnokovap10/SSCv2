/* ssc_compute_allocation @ 001149d8 size 2696 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint ssc_compute_allocation(long *param_1,uint *param_2,undefined8 param_3,uint param_4,int param_5)

{
  bool bVar1;
  undefined1 (*pauVar2) [12];
  long lVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  long lVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined8 uVar14;
  undefined8 uVar15;
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  unkbyte9 Var19;
  bool bVar20;
  int iVar21;
  uint uVar22;
  int *piVar23;
  ulong uVar24;
  long lVar25;
  int iVar26;
  uint uVar27;
  long lVar28;
  int iVar29;
  int iVar30;
  uint *puVar31;
  uint uVar32;
  uint uVar33;
  long lVar34;
  short *psVar35;
  long lVar36;
  ulong uVar37;
  int iVar38;
  int iVar39;
  uint uVar40;
  ulong uVar41;
  ulong uVar42;
  short *psVar43;
  int iVar44;
  undefined8 *puVar45;
  int *piVar46;
  long lVar47;
  long lVar48;
  int iVar49;
  uint uVar50;
  short sVar51;
  short sVar52;
  short sVar53;
  short sVar54;
  short sVar55;
  short sVar56;
  short sVar57;
  short sVar58;
  byte bVar59;
  undefined1 uVar60;
  byte bVar61;
  undefined1 uVar62;
  byte bVar63;
  undefined1 uVar64;
  byte bVar65;
  undefined1 uVar66;
  byte bVar67;
  undefined1 uVar68;
  byte bVar69;
  undefined1 uVar70;
  byte bVar71;
  undefined1 uVar72;
  byte bVar73;
  undefined1 uVar74;
  byte bVar75;
  undefined1 uVar76;
  byte bVar77;
  undefined1 uVar78;
  byte bVar79;
  undefined1 uVar80;
  byte bVar81;
  undefined1 uVar82;
  byte bVar83;
  undefined1 uVar84;
  byte bVar85;
  undefined1 uVar86;
  byte bVar87;
  undefined1 uVar88;
  byte bVar89;
  undefined1 uVar90;
  undefined1 auVar91 [16];
  undefined1 auVar92 [16];
  undefined1 auVar93 [16];
  undefined4 uVar94;
  undefined1 auVar95 [16];
  undefined1 auVar96 [16];
  byte bVar97;
  byte bVar98;
  byte bVar99;
  byte bVar100;
  byte bVar101;
  byte bVar102;
  byte bVar103;
  byte bVar104;
  byte bVar105;
  byte bVar106;
  byte bVar107;
  byte bVar108;
  byte bVar109;
  byte bVar110;
  byte bVar111;
  byte bVar112;
  undefined1 auVar113 [12];
  undefined1 auVar115 [16];
  undefined1 auVar116 [16];
  undefined1 auVar117 [16];
  int local_1e0 [2];
  undefined8 uStack_1d8;
  int aiStack_1d0 [18];
  int iStack_188;
  undefined8 auStack_184 [11];
  uint local_128 [23];
  int local_cc [23];
  long local_70;
  undefined1 auVar114 [16];
  
  lVar9 = tpidr_el0;
  local_70 = *(long *)(lVar9 + 0x28);
  lVar28 = (long)(int)param_4;
  lVar48 = *(long *)(param_2 + 0x2e);
  uVar50 = *param_2 & ((int)*param_2 >> 0x1f ^ 0xffffffffU);
  uVar32 = (uint)(7 < uVar50);
  iVar8 = uVar50 + uVar32 * -8;
  uVar33 = (uint)(byte)(&DAT_00105df0)[lVar28];
  uVar50 = 0;
  if ((int)uVar33 <= iVar8) {
    uVar50 = uVar33;
  }
  uVar40 = (uint)(byte)(&DAT_00105df0)[lVar28];
  uVar33 = (uint)(7 < (int)(iVar8 - uVar33));
  iVar39 = 0;
  if ((int)uVar40 <= iVar8) {
    iVar39 = uVar33 * 8;
  }
  iVar49 = iVar8;
  if ((int)uVar40 <= iVar8) {
    iVar49 = (iVar8 - uVar40) + uVar33 * -8;
  }
  lVar25 = 0x28;
  if (param_2[0x60] != 0) {
    lVar25 = 0x30;
  }
  lVar34 = *param_1;
  lVar25 = *(long *)(lVar34 + lVar25);
  if (0 < (int)param_4) {
    uVar33 = param_2[0x5c];
    psVar35 = *(short **)(lVar34 + 0x10);
    uVar37 = (ulong)param_4;
    iVar38 = uVar33 * 2 + -0x10;
    sVar52 = *psVar35;
    if (param_4 < 8) {
      uVar42 = 0;
      sVar51 = sVar52;
    }
    else {
      uVar42 = uVar37 & 0xfffffff8;
      bVar75 = 6;
      bVar77 = 0;
      bVar79 = 0;
      bVar81 = 0;
      bVar83 = 7;
      bVar85 = 0;
      bVar87 = 0;
      bVar89 = 0;
      bVar59 = 4;
      bVar61 = 0;
      bVar63 = 0;
      bVar65 = 0;
      bVar67 = 5;
      bVar69 = 0;
      bVar71 = 0;
      bVar73 = 0;
      uVar24 = uVar42;
      psVar43 = psVar35 + 1;
      puVar45 = auStack_184;
      piVar23 = local_1e0;
      sVar53 = sVar52;
      sVar54 = sVar52;
      sVar55 = sVar52;
      sVar56 = sVar52;
      sVar57 = sVar52;
      sVar58 = sVar52;
      sVar51 = sVar52;
      auVar95 = _DAT_001027d0;
      do {
        auVar96._10_2_ = sVar57;
        auVar96._8_2_ = sVar56;
        auVar96._12_2_ = sVar58;
        auVar96._14_2_ = sVar51;
        auVar96._2_2_ = sVar53;
        auVar96._0_2_ = sVar52;
        auVar96._4_2_ = sVar54;
        auVar96._6_2_ = sVar55;
        uVar24 = uVar24 - 8;
        uVar10 = *(undefined8 *)(psVar43 + 4);
        sVar56 = (short)uVar10;
        sVar57 = (short)((ulong)uVar10 >> 0x10);
        sVar58 = (short)((ulong)uVar10 >> 0x20);
        sVar51 = (short)((ulong)uVar10 >> 0x30);
        uVar10 = *(undefined8 *)psVar43;
        sVar52 = (short)uVar10;
        sVar53 = (short)((ulong)uVar10 >> 0x10);
        sVar54 = (short)((ulong)uVar10 >> 0x20);
        sVar55 = (short)((ulong)uVar10 >> 0x30);
        bVar97 = ~bVar59;
        bVar98 = ~bVar61;
        bVar99 = ~bVar63;
        bVar100 = ~bVar65;
        bVar101 = ~bVar67;
        bVar102 = ~bVar69;
        bVar103 = ~bVar71;
        bVar104 = ~bVar73;
        bVar105 = ~bVar75;
        bVar106 = ~bVar77;
        bVar107 = ~bVar79;
        bVar108 = ~bVar81;
        bVar109 = ~bVar83;
        bVar110 = ~bVar85;
        bVar111 = ~bVar87;
        bVar112 = ~bVar89;
        iVar30 = CONCAT13(~auVar95[3],CONCAT12(~auVar95[2],CONCAT11(~auVar95[1],~auVar95[0])));
        auVar113._0_8_ =
             CONCAT17(~auVar95[7],
                      CONCAT16(~auVar95[6],CONCAT15(~auVar95[5],CONCAT14(~auVar95[4],iVar30))));
        auVar113[8] = ~auVar95[8];
        auVar113[9] = ~auVar95[9];
        auVar113[10] = ~auVar95[10];
        auVar113[0xb] = ~auVar95[0xb];
        auVar114[0xc] = ~auVar95[0xc];
        auVar114._0_12_ = auVar113;
        auVar114[0xd] = ~auVar95[0xd];
        auVar114[0xe] = ~auVar95[0xe];
        auVar114[0xf] = ~auVar95[0xf];
        auVar93._10_2_ = sVar57;
        auVar93._0_10_ = *(unkbyte10 *)psVar43;
        auVar93._12_2_ = sVar58;
        auVar93._14_2_ = sVar51;
        auVar93 = NEON_ext(auVar96,auVar93,0xe,1);
        auVar115._10_2_ = sVar57;
        auVar115._0_10_ = *(unkbyte10 *)psVar43;
        auVar115._12_2_ = sVar58;
        auVar115._14_2_ = sVar51;
        auVar117._10_2_ = sVar57;
        auVar117._0_10_ = *(unkbyte10 *)psVar43;
        auVar117._12_2_ = sVar58;
        auVar117._14_2_ = sVar51;
        auVar115 = NEON_ext(auVar115,auVar117,8,1);
        auVar117 = NEON_ext(auVar93,auVar93,8,1);
        auVar116._0_4_ = auVar115._0_2_ * 0xc + auVar117._0_2_ * -0xc;
        auVar116._4_4_ = auVar115._2_2_ * 0xc + auVar117._2_2_ * -0xc;
        auVar116._8_4_ = auVar115._4_2_ * 0xc + auVar117._4_2_ * -0xc;
        auVar116._12_4_ = auVar115._6_2_ * 0xc + auVar117._6_2_ * -0xc;
        iVar29 = iVar38 * (param_4 + (int)((ulong)auVar113._0_8_ >> 0x20)) *
                 ((int)sVar53 - (int)auVar93._2_2_);
        iVar44 = iVar38 * (param_4 + auVar114._12_4_) * ((int)sVar55 - (int)auVar93._6_2_);
        auVar16._8_4_ = 0x10;
        auVar16._0_8_ = 0x1000000010;
        auVar16._12_4_ = 0x10;
        auVar18._4_4_ = sVar53 * 0xc + auVar93._2_2_ * -0xc;
        auVar18._0_4_ = sVar52 * 0xc + auVar93._0_2_ * -0xc;
        auVar18._8_4_ = sVar54 * 0xc + auVar93._4_2_ * -0xc;
        auVar18._12_4_ = sVar55 * 0xc + auVar93._6_2_ * -0xc;
        auVar115 = NEON_smax(auVar18,auVar16,4);
        auVar17._8_4_ = 0x10;
        auVar17._0_8_ = 0x1000000010;
        auVar17._12_4_ = 0x10;
        auVar117 = NEON_smax(auVar116,auVar17,4);
        auVar91._0_4_ = auVar95._0_4_ + 8;
        auVar91._4_4_ = auVar95._4_4_ + 8;
        auVar91._8_4_ = auVar95._8_4_ + 8;
        auVar91._12_4_ = auVar95._12_4_ + 8;
        iVar7 = CONCAT13(bVar65,CONCAT12(bVar63,CONCAT11(bVar61,bVar59))) + 8;
        bVar59 = (byte)iVar7;
        bVar61 = (byte)((uint)iVar7 >> 8);
        bVar63 = (byte)((uint)iVar7 >> 0x10);
        bVar65 = (byte)((uint)iVar7 >> 0x18);
        iVar7 = CONCAT13(bVar73,CONCAT12(bVar71,CONCAT11(bVar69,bVar67))) + 8;
        bVar67 = (byte)iVar7;
        bVar69 = (byte)((uint)iVar7 >> 8);
        bVar71 = (byte)((uint)iVar7 >> 0x10);
        bVar73 = (byte)((uint)iVar7 >> 0x18);
        iVar7 = CONCAT13(bVar81,CONCAT12(bVar79,CONCAT11(bVar77,bVar75))) + 8;
        bVar75 = (byte)iVar7;
        bVar77 = (byte)((uint)iVar7 >> 8);
        bVar79 = (byte)((uint)iVar7 >> 0x10);
        bVar81 = (byte)((uint)iVar7 >> 0x18);
        iVar7 = CONCAT13(bVar89,CONCAT12(bVar87,CONCAT11(bVar85,bVar83))) + 8;
        bVar83 = (byte)iVar7;
        bVar85 = (byte)((uint)iVar7 >> 8);
        bVar87 = (byte)((uint)iVar7 >> 0x10);
        bVar89 = (byte)((uint)iVar7 >> 0x18);
        *(ulong *)(piVar23 + 2) =
             CONCAT17((char)((uint)iVar44 >> 0x18),
                      CONCAT16((char)((uint)iVar44 >> 0x10),
                               CONCAT15((char)((uint)iVar44 >> 8),
                                        CONCAT14((char)iVar44,
                                                 iVar38 * (param_4 + auVar113._8_4_) *
                                                 ((int)sVar54 - (int)auVar93._4_2_)))));
        *(ulong *)piVar23 =
             CONCAT17((char)((uint)iVar29 >> 0x18),
                      CONCAT16((char)((uint)iVar29 >> 0x10),
                               CONCAT15((char)((uint)iVar29 >> 8),
                                        CONCAT14((char)iVar29,
                                                 iVar38 * (param_4 + iVar30) *
                                                 ((int)sVar52 - (int)auVar93._0_2_)))));
        piVar23[6] = iVar38 * (param_4 +
                              CONCAT13(bVar108,CONCAT12(bVar107,CONCAT11(bVar106,bVar105)))) *
                     ((int)sVar58 - (int)auVar93._12_2_);
        piVar23[7] = iVar38 * (param_4 +
                              CONCAT13(bVar112,CONCAT12(bVar111,CONCAT11(bVar110,bVar109)))) *
                     ((int)sVar51 - (int)auVar93._14_2_);
        piVar23[4] = iVar38 * (param_4 + CONCAT13(bVar100,CONCAT12(bVar99,CONCAT11(bVar98,bVar97))))
                     * ((int)sVar56 - (int)auVar93._8_2_);
        piVar23[5] = iVar38 * (param_4 +
                              CONCAT13(bVar104,CONCAT12(bVar103,CONCAT11(bVar102,bVar101)))) *
                     ((int)sVar57 - (int)auVar93._10_2_);
        puVar45[1] = auVar115._8_8_;
        *puVar45 = auVar115._0_8_;
        puVar45[3] = auVar117._8_8_;
        puVar45[2] = auVar117._0_8_;
        psVar43 = psVar43 + 8;
        puVar45 = puVar45 + 4;
        piVar23 = piVar23 + 8;
        auVar95 = auVar91;
      } while (uVar24 != 0);
      if (uVar42 == uVar37) goto LAB_00114bec;
    }
    iVar38 = (~(uint)uVar42 + param_4) * iVar38;
    psVar35 = psVar35 + uVar42;
    lVar36 = uVar37 - uVar42;
    piVar23 = (int *)((long)auStack_184 + uVar42 * 4);
    piVar46 = local_1e0 + uVar42;
    do {
      psVar35 = psVar35 + 1;
      sVar52 = *psVar35;
      iVar7 = (int)sVar52 - (int)sVar51;
      iVar29 = iVar38 * iVar7;
      iVar7 = iVar7 * 0xc;
      iVar38 = iVar38 + uVar33 * -2 + 0x10;
      if (iVar7 < 0x11) {
        iVar7 = 0x10;
      }
      lVar36 = lVar36 + -1;
      *piVar46 = iVar29;
      *piVar23 = iVar7;
      piVar23 = piVar23 + 1;
      piVar46 = piVar46 + 1;
      sVar51 = sVar52;
    } while (lVar36 != 0);
  }
LAB_00114bec:
  iVar7 = *(int *)((long)param_1 + 0x2c);
  iVar29 = *(int *)(lVar34 + 0x20);
  iVar38 = 1;
  lVar36 = (long)*(int *)(lVar34 + 8);
  iVar44 = iVar29 + -1;
  do {
    iVar30 = iVar38 + iVar44 >> 1;
    if ((int)param_4 < 1) {
      iVar26 = 0;
    }
    else {
      iVar26 = 0;
      bVar20 = false;
      lVar47 = lVar28;
      sVar52 = *(short *)(*(long *)(lVar34 + 0x10) + lVar28 * 2);
      do {
        sVar51 = *(short *)(*(long *)(lVar34 + 0x10) + -2 + lVar47 * 2);
        iVar21 = ((int)sVar52 - (int)sVar51) *
                 (uint)*(byte *)(lVar25 + -1 + iVar30 * lVar36 + lVar47);
        uVar33 = iVar21 * 4;
        if (0 < iVar21) {
          uVar33 = local_1e0[lVar47 + -1] + uVar33 &
                   ((int)(local_1e0[lVar47 + -1] + uVar33) >> 0x1f ^ 0xffffffffU);
        }
        iVar21 = param_2[lVar47 + 0x2f] + uVar33;
        if ((bVar20) || ((&iStack_188)[lVar47] <= iVar21)) {
          iVar4 = *(int *)(lVar48 + -4 + lVar47 * 4);
          bVar20 = true;
          if (iVar4 <= iVar21) {
            iVar21 = iVar4;
          }
          lVar3 = (long)iVar21 + (long)iVar26;
          if (0x7ffffffe < lVar3) {
            lVar3 = 0x7fffffff;
          }
          iVar4 = (int)lVar3;
          if (lVar3 < -0x7ffffffe) {
            iVar4 = -0x7fffffff;
          }
        }
        else {
          bVar20 = false;
          iVar4 = iVar26 + 0x10;
          if (iVar21 < 0x10) {
            iVar4 = iVar26;
          }
        }
        iVar26 = iVar4;
        bVar1 = 1 < lVar47;
        lVar47 = lVar47 + -1;
        sVar52 = sVar51;
      } while (bVar1);
    }
    iVar21 = iVar30 + -1;
    if (iVar26 <= iVar49) {
      iVar38 = iVar30 + 1;
      iVar21 = iVar44;
    }
    iVar44 = iVar21;
  } while (iVar38 <= iVar44);
  if ((int)param_4 < 1) {
    iVar44 = 0;
  }
  else {
    psVar35 = *(short **)(lVar34 + 0x10);
    uVar37 = 0;
    iVar30 = 0;
    sVar52 = *psVar35;
    do {
      sVar51 = psVar35[uVar37 + 1];
      iVar44 = (int)sVar51 - (int)sVar52;
      if (iVar38 < iVar29) {
        uVar33 = iVar44 * (uint)*(byte *)(lVar25 + iVar38 * lVar36 + uVar37) * 4;
      }
      else {
        uVar33 = *(uint *)(lVar48 + uVar37 * 4);
      }
      iVar44 = iVar44 * (uint)*(byte *)(lVar25 + ((long)iVar38 + -1) * lVar36 + uVar37);
      uVar22 = iVar44 * 4;
      if (0 < iVar44) {
        uVar22 = local_1e0[uVar37] + uVar22 &
                 ((int)(local_1e0[uVar37] + uVar22) >> 0x1f ^ 0xffffffffU);
      }
      if (0 < (int)uVar33) {
        uVar33 = local_1e0[uVar37] + uVar33 &
                 ((int)(local_1e0[uVar37] + uVar33) >> 0x1f ^ 0xffffffffU);
      }
      uVar27 = param_2[uVar37 + 0x30];
      uVar5 = uVar27;
      if (iVar38 < 2) {
        uVar5 = 0;
      }
      uVar24 = uVar37 + 1;
      iVar44 = (int)uVar37;
      if ((int)uVar27 < 1) {
        iVar44 = iVar30;
      }
      uVar27 = (uVar33 - (uVar22 + uVar5)) + uVar27;
      local_cc[uVar37] = uVar22 + uVar5;
      local_128[uVar37] = uVar27 & ((int)uVar27 >> 0x1f ^ 0xffffffffU);
      uVar37 = uVar24;
      iVar30 = iVar44;
      sVar52 = sVar51;
    } while (param_4 != uVar24);
  }
  uVar37 = (ulong)param_4;
  iVar29 = 0;
  iVar38 = 0;
  iVar30 = 0x40;
LAB_00114e60:
  do {
    iVar26 = iVar30 + iVar29 >> 1;
    if ((int)param_4 < 1) goto LAB_00114edc;
    bVar20 = false;
    lVar28 = uVar37 + 1;
    iVar21 = 0;
    do {
      uVar24 = (ulong)((int)lVar28 - 2);
      iVar4 = local_cc[uVar24] + ((int)(local_128[uVar24] * iVar26) >> 6);
      if ((bVar20) || (*(int *)((long)auStack_184 + uVar24 * 4) <= iVar4)) {
        iVar6 = *(int *)(lVar48 + uVar24 * 4);
        if (iVar6 <= iVar4) {
          iVar4 = iVar6;
        }
        bVar20 = true;
        iVar6 = iVar4 + iVar21;
      }
      else {
        bVar20 = false;
        iVar6 = iVar21 + 0x10;
        if (iVar4 < 0x10) {
          iVar6 = iVar21;
        }
      }
      lVar28 = lVar28 + -1;
      iVar21 = iVar6;
    } while (1 < lVar28);
    iVar38 = iVar38 + 1;
    if (iVar6 <= iVar49) {
      iVar29 = iVar26;
      iVar26 = iVar30;
    }
    iVar30 = iVar26;
  } while (iVar38 != 6);
  iVar38 = 0;
  lVar28 = uVar37 + 1;
  bVar20 = false;
  do {
    uVar24 = (ulong)((int)lVar28 - 2);
    lVar28 = lVar28 + -1;
    uVar22 = *(uint *)(lVar48 + uVar24 * 4);
    uVar33 = local_cc[uVar24] + ((int)(local_128[uVar24] * iVar29) >> 6);
    bVar1 = *(int *)((long)auStack_184 + uVar24 * 4) <= (int)uVar33;
    if (!bVar20 && !bVar1) {
      uVar33 = (uint)(0xf < (int)uVar33) << 4;
    }
    if ((int)uVar22 <= (int)uVar33) {
      uVar33 = uVar22;
    }
    iVar38 = uVar33 + iVar38;
    param_2[uVar24 + 0x17] = uVar33;
    bVar20 = bVar20 || bVar1;
  } while (1 < lVar28);
  goto LAB_00114f7c;
LAB_00114edc:
  iVar38 = iVar38 + 1;
  if (-1 < iVar49) {
    iVar29 = iVar26;
    iVar26 = iVar30;
  }
  iVar30 = iVar26;
  if (iVar38 == 6) goto code_r0x00114ef4;
  goto LAB_00114e60;
code_r0x00114ef4:
  iVar38 = 0;
LAB_00114f7c:
  uVar33 = param_4;
  if (iVar44 < (int)(param_4 - 1)) {
    lVar28 = (long)(int)(param_4 - 1);
    do {
      psVar35 = *(short **)(lVar34 + 0x10);
      uVar22 = param_2[lVar28 + 0x17];
      iVar30 = (int)psVar35[(int)uVar33] - (int)*psVar35;
      iVar29 = 0;
      if (iVar30 != 0) {
        iVar29 = (iVar49 - iVar38) / iVar30;
      }
      iVar21 = (int)psVar35[(int)uVar33] - (int)psVar35[lVar28];
      iVar26 = *(int *)((long)auStack_184 + lVar28 * 4);
      uVar27 = ((int)*psVar35 - (int)psVar35[lVar28]) + ((iVar49 - iVar38) - iVar30 * iVar29);
      iVar29 = uVar22 + iVar21 * iVar29 + (uVar27 & ((int)uVar27 >> 0x1f ^ 0xffffffffU));
      if (iVar26 < 0x19) {
        iVar26 = 0x18;
      }
      if (iVar26 <= iVar29) {
        if (2 < (int)uVar33) {
          iVar30 = 0x24;
          if ((int)uVar33 <= iVar7) {
            iVar30 = 0x1c;
          }
          if (iVar29 <= iVar21 * iVar30 || param_5 < lVar28) {
            ssc_ec_enc_bit_logp(param_3,0,1);
            uVar22 = param_2[lVar28 + 0x17];
            iVar38 = iVar38 + 8;
            iVar29 = iVar29 + -8;
            goto LAB_00114fb0;
          }
        }
        ssc_ec_enc_bit_logp(param_3,1,1);
        goto LAB_001150d8;
      }
LAB_00114fb0:
      if (uVar50 == 0) {
        uVar27 = 0;
      }
      else {
        uVar27 = (uint)(byte)(&DAT_00105df0)[lVar28];
      }
      iVar30 = (iVar38 - (uVar22 + uVar50)) + uVar27;
      uVar33 = uVar33 - 1;
      iVar38 = iVar30 + 0x10;
      if (iVar29 < 0x10) {
        iVar38 = iVar30;
      }
      param_2[lVar28 + 0x17] = (uint)(0xf < iVar29) << 4;
      lVar28 = lVar28 + -1;
      uVar50 = uVar27;
    } while (iVar44 < lVar28);
  }
  iVar49 = iVar49 + uVar32 * 8;
LAB_001150d8:
  if (uVar50 == 0) {
    *(undefined4 *)(param_1 + 10) = 0;
LAB_00115164:
    param_2[0x5d] = 0;
  }
  else {
    uVar50 = *(uint *)(param_1 + 10);
    if ((int)uVar33 <= (int)*(uint *)(param_1 + 10)) {
      uVar50 = uVar33;
    }
    *(uint *)(param_1 + 10) = uVar50;
    ssc_ec_enc_uint(param_3,uVar50,uVar33 + 1);
    if ((((int)param_1[10] < 1) || (iVar39 = 0, iVar8 < (int)uVar40)) || ((int)(iVar8 - uVar40) < 8)
       ) goto LAB_00115164;
    ssc_ec_enc_bit_logp(param_3,param_2[0x5d],1);
    iVar39 = 0;
  }
  if ((int)uVar33 < 1) {
                    /* WARNING: Read-only address (ram,0x001027d0) is written */
    uVar50 = 0;
    uVar32 = 0;
    goto LAB_001153e0;
  }
                    /* WARNING: Read-only address (ram,0x001027d0) is written */
  iVar39 = iVar39 + (iVar49 - iVar38);
  psVar35 = *(short **)(lVar34 + 0x10);
  sVar52 = *psVar35;
  iVar49 = (int)psVar35[(int)uVar33] - (int)sVar52;
  iVar8 = 0;
  if (iVar49 != 0) {
    iVar8 = iVar39 / iVar49;
  }
  iVar39 = iVar39 - iVar49 * iVar8;
  uVar24 = (ulong)uVar33;
  if (uVar33 < 0x10) {
    uVar41 = 0;
    sVar51 = sVar52;
LAB_00115220:
    psVar43 = psVar35 + uVar41;
    lVar28 = uVar24 - uVar41;
    puVar31 = param_2 + uVar41 + 0x17;
    do {
      psVar43 = psVar43 + 1;
      sVar53 = *psVar43;
      lVar28 = lVar28 + -1;
      *puVar31 = *puVar31 + ((int)sVar53 - (int)sVar51) * iVar8;
      puVar31 = puVar31 + 1;
      sVar51 = sVar53;
    } while (lVar28 != 0);
  }
  else {
    uVar41 = uVar24 & 0xfffffff0;
    psVar43 = psVar35 + 9;
    uVar60 = (undefined1)sVar52;
    uVar62 = (undefined1)((ushort)sVar52 >> 8);
    puVar31 = param_2 + 0x1f;
    uVar42 = uVar41;
    uVar64 = uVar60;
    uVar66 = uVar62;
    uVar68 = uVar60;
    uVar70 = uVar62;
    uVar72 = uVar60;
    uVar74 = uVar62;
    uVar76 = uVar60;
    uVar78 = uVar62;
    uVar80 = uVar60;
    uVar82 = uVar62;
    uVar84 = uVar60;
    uVar86 = uVar62;
    uVar88 = uVar60;
    uVar90 = uVar62;
    do {
      auVar92[9] = uVar78;
      auVar92[8] = uVar76;
      auVar92[10] = uVar80;
      auVar92[0xb] = uVar82;
      auVar92[0xc] = uVar84;
      auVar92[0xd] = uVar86;
      auVar92[0xe] = uVar88;
      auVar92[0xf] = uVar90;
      auVar92[1] = uVar62;
      auVar92[0] = uVar60;
      auVar92[2] = uVar64;
      auVar92[3] = uVar66;
      auVar92[4] = uVar68;
      auVar92[5] = uVar70;
      auVar92[6] = uVar72;
      auVar92[7] = uVar74;
      uVar42 = uVar42 - 0x10;
      pauVar2 = (undefined1 (*) [12])(psVar43 + -8);
      uVar15 = *(undefined8 *)(psVar43 + -4);
      uVar94 = (undefined4)((ulong)uVar15 >> 0x20);
      uVar14 = *(undefined8 *)*pauVar2;
      uVar11 = *(undefined8 *)(psVar43 + 4);
      uVar76 = (undefined1)uVar11;
      uVar78 = (undefined1)((ulong)uVar11 >> 8);
      uVar80 = (undefined1)((ulong)uVar11 >> 0x10);
      uVar82 = (undefined1)((ulong)uVar11 >> 0x18);
      uVar84 = (undefined1)((ulong)uVar11 >> 0x20);
      uVar86 = (undefined1)((ulong)uVar11 >> 0x28);
      uVar88 = (undefined1)((ulong)uVar11 >> 0x30);
      uVar90 = (undefined1)((ulong)uVar11 >> 0x38);
      uVar10 = *(undefined8 *)psVar43;
      Var19 = *(unkbyte9 *)psVar43;
      uVar60 = (undefined1)uVar10;
      uVar62 = (undefined1)((ulong)uVar10 >> 8);
      uVar64 = (undefined1)((ulong)uVar10 >> 0x10);
      uVar66 = (undefined1)((ulong)uVar10 >> 0x18);
      uVar68 = (undefined1)((ulong)uVar10 >> 0x20);
      uVar70 = (undefined1)((ulong)uVar10 >> 0x28);
      uVar72 = (undefined1)((ulong)uVar10 >> 0x30);
      uVar74 = (undefined1)((ulong)uVar10 >> 0x38);
      psVar43 = psVar43 + 0x10;
      auVar12._12_4_ = uVar94;
      auVar12._0_12_ = *pauVar2;
      auVar93 = NEON_ext(auVar92,auVar12,0xe,1);
      auVar95[9] = uVar78;
      auVar95._0_9_ = Var19;
      auVar95[10] = uVar80;
      auVar95[0xb] = uVar82;
      auVar95[0xc] = uVar84;
      auVar95[0xd] = uVar86;
      auVar95[0xe] = uVar88;
      auVar95[0xf] = uVar90;
      auVar13._12_4_ = uVar94;
      auVar13._0_12_ = *pauVar2;
      auVar95 = NEON_ext(auVar13,auVar95,0xe,1);
      sVar51 = (short)((ulong)uVar11 >> 0x30);
      *(ulong *)(puVar31 + -6) =
           CONCAT44((int)((ulong)*(undefined8 *)(puVar31 + -6) >> 0x20) +
                    ((int)(short)((ulong)uVar14 >> 0x30) - (int)auVar93._6_2_) * iVar8,
                    (int)*(undefined8 *)(puVar31 + -6) +
                    ((int)(short)((ulong)uVar14 >> 0x20) - (int)auVar93._4_2_) * iVar8);
      *(ulong *)(puVar31 + -8) =
           CONCAT44((int)((ulong)*(undefined8 *)(puVar31 + -8) >> 0x20) +
                    ((int)(short)((ulong)uVar14 >> 0x10) - (int)auVar93._2_2_) * iVar8,
                    (int)*(undefined8 *)(puVar31 + -8) +
                    ((int)(short)uVar14 - (int)auVar93._0_2_) * iVar8);
      *(ulong *)(puVar31 + -2) =
           CONCAT44((int)((ulong)*(undefined8 *)(puVar31 + -2) >> 0x20) +
                    ((int)(short)((ulong)uVar15 >> 0x30) - (int)auVar93._14_2_) * iVar8,
                    (int)*(undefined8 *)(puVar31 + -2) +
                    ((int)(short)((ulong)uVar15 >> 0x20) - (int)auVar93._12_2_) * iVar8);
      *(ulong *)(puVar31 + -4) =
           CONCAT44((int)((ulong)*(undefined8 *)(puVar31 + -4) >> 0x20) +
                    ((int)(short)((ulong)uVar15 >> 0x10) - (int)auVar93._10_2_) * iVar8,
                    (int)*(undefined8 *)(puVar31 + -4) +
                    ((int)(short)uVar15 - (int)auVar93._8_2_) * iVar8);
      puVar31[2] = puVar31[2] + ((int)(short)((ulong)uVar10 >> 0x20) - (int)auVar95._4_2_) * iVar8;
      puVar31[3] = puVar31[3] + ((int)(short)((ulong)uVar10 >> 0x30) - (int)auVar95._6_2_) * iVar8;
      *puVar31 = *puVar31 + ((int)(short)uVar10 - (int)auVar95._0_2_) * iVar8;
      puVar31[1] = puVar31[1] + ((int)(short)((ulong)uVar10 >> 0x10) - (int)auVar95._2_2_) * iVar8;
      *(ulong *)(puVar31 + 6) =
           CONCAT44((int)((ulong)*(undefined8 *)(puVar31 + 6) >> 0x20) +
                    ((int)sVar51 - (int)auVar95._14_2_) * iVar8,
                    (int)*(undefined8 *)(puVar31 + 6) +
                    ((int)(short)((ulong)uVar11 >> 0x20) - (int)auVar95._12_2_) * iVar8);
      *(ulong *)(puVar31 + 4) =
           CONCAT44((int)((ulong)*(undefined8 *)(puVar31 + 4) >> 0x20) +
                    ((int)(short)((ulong)uVar11 >> 0x10) - (int)auVar95._10_2_) * iVar8,
                    (int)*(undefined8 *)(puVar31 + 4) +
                    ((int)(short)uVar11 - (int)auVar95._8_2_) * iVar8);
      puVar31 = puVar31 + 0x10;
    } while (uVar42 != 0);
    if (uVar41 != uVar24) goto LAB_00115220;
  }
  puVar31 = param_2 + 0x17;
  uVar42 = uVar24;
  psVar43 = psVar35;
  sVar51 = sVar52;
  do {
    psVar43 = psVar43 + 1;
    sVar53 = *psVar43;
    iVar49 = (int)sVar53 - (int)sVar51;
    iVar8 = iVar39;
    if (iVar49 <= iVar39) {
      iVar8 = iVar49;
    }
    uVar42 = uVar42 - 1;
    iVar39 = iVar39 - iVar8;
    *puVar31 = iVar8 + *puVar31;
    puVar31 = puVar31 + 1;
    sVar51 = sVar53;
  } while (uVar42 != 0);
  uVar42 = 0;
  uVar50 = 0;
  lVar28 = *(long *)(lVar34 + 0x38);
  puVar31 = param_2;
  do {
    sVar51 = psVar35[uVar42 + 1];
    uVar40 = (puVar31[0x17] + uVar50) - *(int *)(lVar48 + uVar42 * 4);
    uVar32 = uVar40 & ((int)uVar40 >> 0x1f ^ 0xffffffffU);
    iVar8 = (int)sVar51 - (int)sVar52;
    uVar22 = (puVar31[0x17] + uVar50) - uVar32;
    puVar31[0x17] = uVar22;
    if ((iVar8 < 1) || (param_2[0x5d] != 0)) {
      uVar27 = 0;
    }
    else {
      uVar27 = (uint)((long)uVar42 < (long)(int)param_1[10]);
    }
    uVar27 = iVar8 * 0x10 | uVar27;
    iVar49 = (*(short *)(lVar28 + uVar42 * 2) + 0x18) * uVar27;
    iVar8 = uVar27 * -0x15 + (iVar49 >> 1);
    iVar39 = iVar8;
    if ((int)(iVar8 + uVar22) < (int)(uVar27 * 0x18)) {
      iVar39 = iVar8 + (iVar49 >> 3);
    }
    if ((int)(iVar8 + uVar22) < (int)(uVar27 * 0x10)) {
      iVar39 = iVar8 + (iVar49 >> 2);
    }
    iVar8 = uVar27 * 8;
    uVar5 = 0;
    if (iVar8 != 0) {
      uVar5 = (int)(iVar39 + uVar22 + uVar27 * 4) / iVar8;
    }
    uVar5 = uVar5 & ((int)uVar5 >> 0x1f ^ 0xffffffffU);
    uVar27 = (int)uVar22 >> 4;
    if ((int)(uVar5 * 2) <= (int)uVar22 >> 3) {
      uVar27 = uVar5;
    }
    if (7 < (int)uVar27) {
      uVar27 = 8;
    }
    puVar31[1] = uVar27;
    puVar31[0x17] = uVar22 + uVar27 * -0x10;
    puVar31[0x46] = (uint)((int)(iVar39 + uVar22) <= (int)(uVar27 * iVar8));
    if ((int)uVar40 < 1) {
      uVar50 = 0;
    }
    else {
      iVar8 = uVar32 - uVar50;
      uVar40 = uVar32 >> 4;
      if (8 - uVar27 <= uVar32 >> 4) {
        uVar40 = 8 - uVar27;
      }
      uVar50 = uVar32 + uVar40 * -0x10;
      puVar31[1] = uVar40 + uVar27;
      puVar31[0x46] = (uint)(iVar8 <= (int)(uVar40 * 0x10));
    }
    uVar42 = uVar42 + 1;
    puVar31 = puVar31 + 1;
    uVar32 = uVar33;
    sVar52 = sVar51;
  } while (uVar24 != uVar42);
LAB_001153e0:
  param_2[0x5e] = uVar50;
  if ((int)uVar32 < (int)param_4) {
    lVar28 = uVar37 - uVar32;
    puVar31 = param_2 + uVar32;
    do {
      uVar50 = puVar31[0x17];
      puVar31[0x17] = 0;
      lVar28 = lVar28 + -1;
      puVar31[1] = (int)uVar50 >> 4;
      puVar31[0x46] = (uint)((int)uVar50 < 0x10);
      puVar31 = puVar31 + 1;
    } while (lVar28 != 0);
  }
  if (*(long *)(lVar9 + 0x28) == local_70) {
    return uVar33;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


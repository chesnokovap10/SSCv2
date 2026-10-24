/* compute_allocation @ 00109938 size 3844 */

uint compute_allocation(long param_1,ulong param_2,long param_3,long param_4,int param_5,
                       uint *param_6,int *param_7,uint param_8,int *param_9,int *param_10,
                       long param_11,long param_12,undefined8 param_13,int param_14,int param_15,
                       int param_16)

{
  bool bVar1;
  int iVar2;
  byte bVar3;
  long lVar4;
  bool bVar5;
  int iVar6;
  int *piVar7;
  ulong uVar8;
  uint uVar9;
  long lVar10;
  uint uVar11;
  uint *puVar12;
  uint uVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int *piVar17;
  long lVar18;
  long lVar19;
  ulong uVar20;
  int iVar21;
  ulong uVar22;
  short *psVar23;
  int iVar24;
  long lVar25;
  undefined8 *puVar26;
  short *psVar27;
  short *psVar28;
  ulong *puVar29;
  uint uVar30;
  long lVar31;
  uint uVar32;
  ulong uVar33;
  ulong uVar34;
  uint uVar35;
  int iVar36;
  undefined8 uVar37;
  short sVar38;
  short sVar41;
  short sVar42;
  undefined8 uVar39;
  undefined8 uVar40;
  undefined8 uVar43;
  short sVar44;
  short sVar45;
  short sVar46;
  undefined1 auVar47 [16];
  undefined1 auVar48 [16];
  int local_21c;
  int local_1e0 [2];
  undefined8 auStack_1d8 [10];
  int iStack_188;
  undefined8 auStack_184 [11];
  uint auStack_12c [23];
  uint auStack_d0 [24];
  long local_70;
  
  lVar4 = tpidr_el0;
  uVar33 = param_2 & 0xffffffff;
  param_8 = param_8 & ((int)param_8 >> 0x1f ^ 0xffffffffU);
  uVar32 = (uint)param_2;
  lVar10 = (long)(int)uVar32;
  bVar3 = (&DAT_00116a90)[lVar10];
  uVar35 = (uint)bVar3;
  local_70 = *(long *)(lVar4 + 0x28);
  lVar18 = 0x28;
  if (param_16 != 0) {
    lVar18 = 0x30;
  }
  lVar18 = *(long *)(param_1 + lVar18);
  lVar19 = (long)*(int *)(param_1 + 8);
  uVar11 = (uint)(7 < (int)param_8);
  iVar36 = param_8 + uVar11 * -8;
  iVar14 = iVar36 - (uint)bVar3;
  if (iVar36 < (int)(uint)bVar3) {
    uVar35 = 0;
    local_21c = 0;
    if ((int)uVar32 < 1) goto LAB_001099d4;
LAB_001099fc:
    psVar23 = *(short **)(param_1 + 0x10);
    iVar14 = param_5 * 2 + -0x10;
    sVar42 = *psVar23;
    if (uVar32 < 4) {
      uVar20 = 0;
      iVar24 = 0;
LAB_00109aa8:
      psVar23 = psVar23 + uVar20;
      lVar25 = (param_2 & 0xffffffff) - uVar20;
      iVar14 = ((uVar32 - 1) - iVar24) * iVar14;
      piVar7 = local_1e0 + uVar20;
      piVar17 = (int *)((long)auStack_184 + uVar20 * 4);
      do {
        psVar23 = psVar23 + 1;
        sVar41 = *psVar23;
        iVar16 = (int)sVar41 - (int)sVar42;
        iVar24 = iVar16 * 0xc;
        *piVar7 = iVar14 * iVar16;
        if (iVar24 < 0x11) {
          iVar24 = 0x10;
        }
        lVar25 = lVar25 + -1;
        *piVar17 = iVar24;
        iVar14 = iVar14 + param_5 * -2 + 0x10;
        piVar7 = piVar7 + 1;
        piVar17 = piVar17 + 1;
        sVar42 = sVar41;
      } while (lVar25 != 0);
    }
    else {
      uVar39 = 0x300000002;
      uVar43 = 0x100000000;
      uVar20 = param_2 & 0xfffffffc;
      piVar7 = local_1e0;
      uVar34 = uVar20;
      psVar27 = psVar23 + 1;
      puVar26 = auStack_184;
      uVar37 = CONCAT26(sVar42,CONCAT24(sVar42,CONCAT22(sVar42,sVar42)));
      do {
        uVar40 = *(undefined8 *)psVar27;
        uVar37 = NEON_ext(uVar37,uVar40,6,1);
        sVar41 = (short)((ulong)uVar40 >> 0x10);
        sVar38 = (short)((ulong)uVar40 >> 0x20);
        sVar42 = (short)((ulong)uVar40 >> 0x30);
        sVar44 = (short)((ulong)uVar37 >> 0x10);
        sVar45 = (short)((ulong)uVar37 >> 0x20);
        sVar46 = (short)((ulong)uVar37 >> 0x30);
        auVar47._0_4_ = (short)uVar40 * 0xc + (short)uVar37 * -0xc;
        auVar47._4_4_ = sVar41 * 0xc + sVar44 * -0xc;
        auVar47._8_4_ = sVar38 * 0xc + sVar45 * -0xc;
        auVar47._12_4_ = sVar42 * 0xc + sVar46 * -0xc;
        auVar48._8_4_ = 0x10;
        auVar48._0_8_ = 0x1000000010;
        auVar48._12_4_ = 0x10;
        auVar48 = NEON_smax(auVar47,auVar48,4);
        uVar34 = uVar34 - 4;
        puVar26[1] = auVar48._8_8_;
        *puVar26 = auVar48._0_8_;
        *(ulong *)(piVar7 + 2) =
             CONCAT44(iVar14 * (uVar32 + CONCAT13(~(byte)((ulong)uVar39 >> 0x38),
                                                  CONCAT12(~(byte)((ulong)uVar39 >> 0x30),
                                                           CONCAT11(~(byte)((ulong)uVar39 >> 0x28),
                                                                    ~(byte)((ulong)uVar39 >> 0x20)))
                                                 )) * ((int)sVar42 - (int)sVar46),
                      iVar14 * (uVar32 + CONCAT13(~(byte)((ulong)uVar39 >> 0x18),
                                                  CONCAT12(~(byte)((ulong)uVar39 >> 0x10),
                                                           CONCAT11(~(byte)((ulong)uVar39 >> 8),
                                                                    ~(byte)uVar39)))) *
                      ((int)sVar38 - (int)sVar45));
        *(ulong *)piVar7 =
             CONCAT44(iVar14 * (uVar32 + CONCAT13(~(byte)((ulong)uVar43 >> 0x38),
                                                  CONCAT12(~(byte)((ulong)uVar43 >> 0x30),
                                                           CONCAT11(~(byte)((ulong)uVar43 >> 0x28),
                                                                    ~(byte)((ulong)uVar43 >> 0x20)))
                                                 )) * ((int)sVar41 - (int)sVar44),
                      iVar14 * (uVar32 + CONCAT13(~(byte)((ulong)uVar43 >> 0x18),
                                                  CONCAT12(~(byte)((ulong)uVar43 >> 0x10),
                                                           CONCAT11(~(byte)((ulong)uVar43 >> 8),
                                                                    ~(byte)uVar43)))) *
                      ((int)(short)uVar40 - (int)(short)uVar37));
        uVar43 = CONCAT44((int)((ulong)uVar43 >> 0x20) + 4,(int)uVar43 + 4);
        uVar39 = CONCAT44((int)((ulong)uVar39 >> 0x20) + 4,(int)uVar39 + 4);
        piVar7 = piVar7 + 4;
        psVar27 = psVar27 + 4;
        puVar26 = puVar26 + 2;
        uVar37 = uVar40;
      } while (uVar34 != 0);
      if (uVar20 != (param_2 & 0xffffffff)) {
        iVar24 = (int)uVar20;
        goto LAB_00109aa8;
      }
    }
    iVar14 = *(int *)(param_1 + 0x20);
    iVar24 = iVar14 + -1;
    if ((int)uVar32 < 1) goto LAB_00109c1c;
    iVar16 = 1;
    do {
      iVar21 = iVar16 + iVar24 >> 1;
      bVar5 = false;
      lVar25 = lVar10;
      sVar42 = *(short *)(*(long *)(param_1 + 0x10) + lVar10 * 2);
      iVar15 = 0;
      do {
        while( true ) {
          sVar41 = *(short *)(*(long *)(param_1 + 0x10) + lVar25 * 2 + -2);
          iVar2 = ((int)sVar42 - (int)sVar41) *
                  (uint)*(byte *)(lVar18 + ((long)((ulong)(uint)(iVar16 + iVar24) << 0x20) >> 0x21)
                                           * lVar19 + lVar25 + -1);
          uVar13 = iVar2 * 4;
          if (0 < iVar2) {
            uVar13 = local_1e0[lVar25 + -1] + uVar13 &
                     ((int)(local_1e0[lVar25 + -1] + uVar13) >> 0x1f ^ 0xffffffffU);
          }
          lVar31 = lVar25 + -1;
          iVar2 = *(int *)(param_3 + lVar25 * 4 + -4) + uVar13;
          sVar42 = sVar41;
          if ((bVar5) || ((&iStack_188)[lVar25] <= iVar2)) break;
          bVar5 = false;
          iVar6 = iVar15 + 0x10;
          if (iVar2 < 0x10) {
            iVar6 = iVar15;
          }
          lVar25 = lVar31;
          iVar15 = iVar6;
          if (lVar31 < 1) goto LAB_00109c00;
        }
        iVar6 = *(int *)(param_4 + lVar25 * 4 + -4);
        if (iVar6 <= iVar2) {
          iVar2 = iVar6;
        }
        iVar15 = iVar2 + iVar15;
        bVar5 = true;
        lVar25 = lVar31;
        iVar6 = iVar15;
      } while (0 < lVar31);
LAB_00109c00:
      iVar15 = iVar21 + -1;
      if (iVar6 <= iVar36) {
        iVar16 = iVar21 + 1;
        iVar15 = iVar24;
      }
      iVar24 = iVar15;
    } while (iVar16 <= iVar24);
  }
  else {
    uVar13 = (uint)(7 < iVar14);
    local_21c = uVar13 * 8;
    iVar36 = iVar14 + uVar13 * -8;
    if (0 < (int)uVar32) goto LAB_001099fc;
LAB_001099d4:
    iVar14 = *(int *)(param_1 + 0x20);
    iVar24 = iVar14 + -1;
LAB_00109c1c:
    iVar16 = 1;
    do {
      iVar15 = iVar16 + iVar24 >> 1;
      iVar21 = iVar15 + -1;
      if (-1 < iVar36) {
        iVar16 = iVar15 + 1;
        iVar21 = iVar24;
      }
      iVar24 = iVar21;
    } while (iVar16 <= iVar24);
  }
  if ((int)uVar32 < 1) {
    iVar14 = 0;
LAB_0010a3a0:
    iVar24 = 0;
  }
  else {
    psVar23 = *(short **)(param_1 + 0x10);
    lVar25 = (long)iVar16 + -1;
    lVar31 = lVar25 * lVar19;
    iVar24 = (int)lVar25;
    if (iVar16 < iVar14) {
      uVar34 = 0;
      iVar15 = 0;
      sVar42 = *psVar23;
      do {
        sVar41 = psVar23[uVar34 + 1];
        iVar21 = (int)sVar41 - (int)sVar42;
        iVar14 = iVar21 * (uint)*(byte *)(lVar18 + lVar31 + uVar34);
        uVar13 = iVar14 * 4;
        uVar9 = iVar21 * (uint)*(byte *)(lVar18 + iVar16 * lVar19 + uVar34) * 4;
        if (0 < iVar14) {
          uVar13 = local_1e0[uVar34] + uVar13 &
                   ((int)(local_1e0[uVar34] + uVar13) >> 0x1f ^ 0xffffffffU);
        }
        uVar20 = uVar34 + 1;
        if (0 < (int)uVar9) {
          uVar9 = local_1e0[uVar34] + uVar9 &
                  ((int)(local_1e0[uVar34] + uVar9) >> 0x1f ^ 0xffffffffU);
        }
        iVar2 = *(int *)(param_3 + uVar34 * 4);
        iVar21 = iVar2;
        if (iVar24 < 1) {
          iVar21 = 0;
        }
        iVar14 = (int)uVar34;
        if (iVar2 < 1) {
          iVar14 = iVar15;
        }
        uVar9 = (uVar9 - (uVar13 + iVar21)) + iVar2;
        auStack_12c[uVar34 + 1] = uVar9 & ((int)uVar9 >> 0x1f ^ 0xffffffffU);
        auStack_d0[uVar34 + 1] = uVar13 + iVar21;
        uVar34 = uVar20;
        iVar15 = iVar14;
        sVar42 = sVar41;
      } while ((param_2 & 0xffffffff) != uVar20);
    }
    else if (iVar24 < 1) {
      uVar34 = 0;
      iVar24 = 0;
      sVar42 = *psVar23;
      do {
        sVar41 = psVar23[uVar34 + 1];
        uVar9 = *(uint *)(param_4 + uVar34 * 4);
        iVar14 = ((int)sVar41 - (int)sVar42) * (uint)*(byte *)(lVar18 + lVar31 + uVar34);
        uVar13 = iVar14 * 4;
        if (0 < iVar14) {
          uVar13 = local_1e0[uVar34] + uVar13 &
                   ((int)(local_1e0[uVar34] + uVar13) >> 0x1f ^ 0xffffffffU);
        }
        uVar20 = uVar34 + 1;
        if (0 < (int)uVar9) {
          uVar9 = local_1e0[uVar34] + uVar9 &
                  ((int)(local_1e0[uVar34] + uVar9) >> 0x1f ^ 0xffffffffU);
        }
        iVar16 = *(int *)(param_3 + uVar34 * 4);
        auStack_d0[uVar34 + 1] = uVar13;
        uVar13 = (uVar9 - uVar13) + iVar16;
        iVar14 = (int)uVar34;
        if (iVar16 < 1) {
          iVar14 = iVar24;
        }
        auStack_12c[uVar34 + 1] = uVar13 & ((int)uVar13 >> 0x1f ^ 0xffffffffU);
        uVar34 = uVar20;
        iVar24 = iVar14;
        sVar42 = sVar41;
      } while ((param_2 & 0xffffffff) != uVar20);
    }
    else {
      uVar34 = 0;
      iVar24 = 0;
      sVar42 = *psVar23;
      do {
        sVar41 = psVar23[uVar34 + 1];
        uVar9 = *(uint *)(param_4 + uVar34 * 4);
        iVar14 = ((int)sVar41 - (int)sVar42) * (uint)*(byte *)(lVar18 + lVar31 + uVar34);
        uVar13 = iVar14 * 4;
        if (0 < iVar14) {
          uVar13 = local_1e0[uVar34] + uVar13 &
                   ((int)(local_1e0[uVar34] + uVar13) >> 0x1f ^ 0xffffffffU);
        }
        uVar20 = uVar34 + 1;
        if (0 < (int)uVar9) {
          uVar9 = local_1e0[uVar34] + uVar9 &
                  ((int)(local_1e0[uVar34] + uVar9) >> 0x1f ^ 0xffffffffU);
        }
        iVar16 = *(int *)(param_3 + uVar34 * 4);
        iVar14 = (int)uVar34;
        if (iVar16 < 1) {
          iVar14 = iVar24;
        }
        uVar9 = (uVar9 - (iVar16 + uVar13)) + iVar16;
        auStack_12c[uVar34 + 1] = uVar9 & ((int)uVar9 >> 0x1f ^ 0xffffffffU);
        auStack_d0[uVar34 + 1] = iVar16 + uVar13;
        uVar34 = uVar20;
        iVar24 = iVar14;
        sVar42 = sVar41;
      } while ((param_2 & 0xffffffff) != uVar20);
    }
    if ((int)uVar32 < 1) goto LAB_0010a3a0;
    lVar18 = lVar10 + -1;
    bVar5 = false;
    lVar19 = lVar18;
    iVar24 = 0;
    do {
      while( true ) {
        iVar16 = auStack_d0[lVar19 + 1] + ((int)auStack_12c[lVar19 + 1] >> 1);
        if ((bVar5) || (*(int *)((long)auStack_184 + lVar19 * 4) <= iVar16)) break;
        bVar5 = false;
        iVar15 = iVar24 + 0x10;
        if (iVar16 < 0x10) {
          iVar15 = iVar24;
        }
        bVar1 = lVar19 < 1;
        lVar19 = lVar19 + -1;
        iVar24 = iVar15;
        if (bVar1) goto LAB_00109eec;
      }
      iVar15 = *(int *)(param_4 + lVar19 * 4);
      if (iVar15 <= iVar16) {
        iVar16 = iVar15;
      }
      iVar24 = iVar16 + iVar24;
      bVar5 = true;
      bVar1 = 0 < lVar19;
      lVar19 = lVar19 + -1;
      iVar15 = iVar24;
    } while (bVar1);
LAB_00109eec:
    iVar24 = 0;
    bVar5 = false;
    uVar13 = 0x20;
    if (iVar15 <= iVar36) {
      uVar13 = 0x40;
    }
    uVar9 = 0x10;
    lVar19 = lVar18;
    if (iVar15 <= iVar36) {
      uVar9 = 0x30;
    }
    do {
      while( true ) {
        iVar16 = auStack_d0[lVar19 + 1] + ((int)(auStack_12c[lVar19 + 1] * uVar9) >> 6);
        if ((bVar5) || (*(int *)((long)auStack_184 + lVar19 * 4) <= iVar16)) break;
        bVar5 = false;
        iVar21 = iVar24 + 0x10;
        if (iVar16 < 0x10) {
          iVar21 = iVar24;
        }
        bVar1 = lVar19 < 1;
        lVar19 = lVar19 + -1;
        iVar24 = iVar21;
        if (bVar1) goto LAB_00109f84;
      }
      iVar21 = *(int *)(param_4 + lVar19 * 4);
      if (iVar21 <= iVar16) {
        iVar16 = iVar21;
      }
      iVar24 = iVar16 + iVar24;
      bVar5 = true;
      bVar1 = 0 < lVar19;
      lVar19 = lVar19 + -1;
      iVar21 = iVar24;
    } while (bVar1);
LAB_00109f84:
    uVar30 = 0;
    if (iVar15 <= iVar36) {
      uVar30 = 0x20;
    }
    if (iVar21 <= iVar36) {
      uVar30 = uVar9;
      uVar9 = uVar13;
    }
    bVar5 = false;
    uVar13 = uVar30 + uVar9 >> 1;
    lVar19 = lVar18;
    iVar24 = 0;
    do {
      while( true ) {
        iVar16 = auStack_d0[lVar19 + 1] + ((int)(auStack_12c[lVar19 + 1] * uVar13) >> 6);
        if ((bVar5) || (*(int *)((long)auStack_184 + lVar19 * 4) <= iVar16)) break;
        bVar5 = false;
        iVar15 = iVar24 + 0x10;
        if (iVar16 < 0x10) {
          iVar15 = iVar24;
        }
        bVar1 = lVar19 < 1;
        lVar19 = lVar19 + -1;
        iVar24 = iVar15;
        if (bVar1) goto LAB_0010a020;
      }
      iVar15 = *(int *)(param_4 + lVar19 * 4);
      if (iVar15 <= iVar16) {
        iVar16 = iVar15;
      }
      iVar24 = iVar16 + iVar24;
      bVar5 = true;
      bVar1 = 0 < lVar19;
      lVar19 = lVar19 + -1;
      iVar15 = iVar24;
    } while (bVar1);
LAB_0010a020:
    if (iVar15 <= iVar36) {
      uVar30 = uVar13;
      uVar13 = uVar9;
    }
    bVar5 = false;
    uVar9 = uVar30 + uVar13 >> 1;
    lVar19 = lVar18;
    iVar24 = 0;
    do {
      while( true ) {
        iVar16 = auStack_d0[lVar19 + 1] + ((int)(auStack_12c[lVar19 + 1] * uVar9) >> 6);
        if ((bVar5) || (*(int *)((long)auStack_184 + lVar19 * 4) <= iVar16)) break;
        bVar5 = false;
        iVar15 = iVar24 + 0x10;
        if (iVar16 < 0x10) {
          iVar15 = iVar24;
        }
        bVar1 = lVar19 < 1;
        lVar19 = lVar19 + -1;
        iVar24 = iVar15;
        if (bVar1) goto LAB_0010a0b0;
      }
      iVar15 = *(int *)(param_4 + lVar19 * 4);
      if (iVar15 <= iVar16) {
        iVar16 = iVar15;
      }
      iVar24 = iVar16 + iVar24;
      bVar5 = true;
      bVar1 = 0 < lVar19;
      lVar19 = lVar19 + -1;
      iVar15 = iVar24;
    } while (bVar1);
LAB_0010a0b0:
    if (iVar15 <= iVar36) {
      uVar30 = uVar9;
      uVar9 = uVar13;
    }
    bVar5 = false;
    uVar13 = uVar30 + uVar9 >> 1;
    lVar19 = lVar18;
    iVar24 = 0;
    do {
      while( true ) {
        iVar16 = auStack_d0[lVar19 + 1] + ((int)(auStack_12c[lVar19 + 1] * uVar13) >> 6);
        if ((bVar5) || (*(int *)((long)auStack_184 + lVar19 * 4) <= iVar16)) break;
        bVar5 = false;
        iVar15 = iVar24 + 0x10;
        if (iVar16 < 0x10) {
          iVar15 = iVar24;
        }
        bVar1 = lVar19 < 1;
        lVar19 = lVar19 + -1;
        iVar24 = iVar15;
        if (bVar1) goto LAB_0010a140;
      }
      iVar15 = *(int *)(param_4 + lVar19 * 4);
      if (iVar15 <= iVar16) {
        iVar16 = iVar15;
      }
      iVar24 = iVar16 + iVar24;
      bVar5 = true;
      bVar1 = 0 < lVar19;
      lVar19 = lVar19 + -1;
      iVar15 = iVar24;
    } while (bVar1);
LAB_0010a140:
    if (iVar15 <= iVar36) {
      uVar30 = uVar13;
      uVar13 = uVar9;
    }
    bVar5 = false;
    uVar13 = uVar30 + uVar13 >> 1;
    iVar24 = 0;
    do {
      while( true ) {
        iVar16 = auStack_d0[lVar18 + 1] + ((int)(auStack_12c[lVar18 + 1] * uVar13) >> 6);
        if ((bVar5) || (*(int *)((long)auStack_184 + lVar18 * 4) <= iVar16)) break;
        bVar5 = false;
        iVar15 = iVar24 + 0x10;
        if (iVar16 < 0x10) {
          iVar15 = iVar24;
        }
        bVar1 = lVar18 < 1;
        lVar18 = lVar18 + -1;
        iVar24 = iVar15;
        if (bVar1) goto LAB_0010a1cc;
      }
      iVar15 = *(int *)(param_4 + lVar18 * 4);
      if (iVar15 <= iVar16) {
        iVar16 = iVar15;
      }
      iVar24 = iVar16 + iVar24;
      bVar5 = true;
      bVar1 = 0 < lVar18;
      lVar18 = lVar18 + -1;
      iVar15 = iVar24;
    } while (bVar1);
LAB_0010a1cc:
    iVar24 = 0;
    bVar5 = false;
    if (iVar15 <= iVar36) {
      uVar30 = uVar13;
    }
    do {
      iVar21 = (&iStack_188)[lVar10];
      iVar16 = auStack_d0[lVar10] + ((int)(auStack_12c[lVar10] * uVar30) >> 6);
      iVar2 = *(int *)(param_4 + lVar10 * 4 + -4);
      iVar15 = iVar16;
      if (!bVar5 && iVar21 > iVar16) {
        iVar15 = (uint)(0xf < iVar16) << 4;
      }
      lVar18 = lVar10 + -1;
      if (iVar2 <= iVar15) {
        iVar15 = iVar2;
      }
      iVar24 = iVar15 + iVar24;
      param_10[lVar10 + -1] = iVar15;
      lVar10 = lVar18;
      bVar5 = (bool)(bVar5 | iVar21 <= iVar16);
    } while (0 < lVar18);
  }
  uVar13 = uVar32;
  if (iVar14 < (int)(uVar32 - 1)) {
    lVar18 = (long)(int)(uVar32 - 1);
    uVar34 = uVar33;
    do {
      psVar23 = *(short **)(param_1 + 0x10);
      iVar15 = param_10[lVar18];
      uVar13 = (uint)uVar34;
      iVar16 = *(int *)((long)auStack_184 + lVar18 * 4);
      iVar2 = (int)psVar23[(int)uVar13] - (int)*psVar23;
      iVar6 = (int)psVar23[(int)uVar13] - (int)psVar23[lVar18];
      iVar21 = 0;
      if (iVar2 != 0) {
        iVar21 = (iVar36 - iVar24) / iVar2;
      }
      uVar9 = ((iVar36 - iVar24) - iVar2 * iVar21) + ((int)*psVar23 - (int)psVar23[lVar18]);
      iVar21 = iVar15 + iVar6 * iVar21 + (uVar9 & ((int)uVar9 >> 0x1f ^ 0xffffffffU));
      if (iVar16 < 0x19) {
        iVar16 = 0x18;
      }
      if (iVar16 <= iVar21) {
        if (2 < (int)uVar13) {
          iVar16 = 0x24;
          if ((int)uVar13 <= param_14) {
            iVar16 = 0x1c;
          }
          if ((param_15 < lVar18) || (iVar21 <= iVar6 * iVar16)) {
            ec_enc_bit_logp(param_13,0,1);
            iVar15 = param_10[lVar18];
            iVar24 = iVar24 + 8;
            iVar21 = iVar21 + -8;
            goto LAB_0010a34c;
          }
        }
        ec_enc_bit_logp(param_13,1,1);
        goto LAB_0010a3dc;
      }
LAB_0010a34c:
      uVar9 = uVar35;
      if (uVar35 != 0) {
        uVar9 = (uint)(byte)(&DAT_00116a90)[lVar18];
      }
      iVar16 = (iVar24 - (iVar15 + uVar35)) + uVar9;
      param_10[lVar18] = (uint)(0xf < iVar21) << 4;
      lVar18 = lVar18 + -1;
      iVar24 = iVar16 + 0x10;
      if (iVar21 < 0x10) {
        iVar24 = iVar16;
      }
      uVar13 = uVar13 - 1;
      uVar34 = (ulong)uVar13;
      uVar35 = uVar9;
    } while (iVar14 < lVar18);
  }
  iVar36 = iVar36 + uVar11 * 8;
LAB_0010a3dc:
  if (uVar35 == 0) {
    *param_6 = 0;
LAB_0010a46c:
    *param_7 = 0;
    if ((int)uVar13 < 1) goto LAB_0010a44c;
LAB_0010a47c:
    psVar23 = *(short **)(param_1 + 0x10);
    local_21c = local_21c + (iVar36 - iVar24);
    sVar42 = *psVar23;
    iVar14 = (int)psVar23[(int)uVar13] - (int)sVar42;
    iVar36 = 0;
    if (iVar14 != 0) {
      iVar36 = local_21c / iVar14;
    }
    local_21c = local_21c - iVar14 * iVar36;
    uVar20 = (ulong)uVar13;
    uVar34 = uVar20;
    piVar7 = param_10;
    psVar27 = psVar23;
    sVar41 = sVar42;
    if (uVar13 < 8) {
      uVar22 = 0;
      sVar38 = sVar42;
LAB_0010a510:
      lVar18 = uVar20 - uVar22;
      psVar28 = psVar23 + uVar22;
      piVar17 = param_10 + uVar22;
      do {
        psVar28 = psVar28 + 1;
        sVar44 = *psVar28;
        lVar18 = lVar18 + -1;
        *piVar17 = *piVar17 + ((int)sVar44 - (int)sVar38) * iVar36;
        piVar17 = piVar17 + 1;
        sVar38 = sVar44;
      } while (lVar18 != 0);
    }
    else {
      uVar22 = uVar20 & 0xfffffff8;
      uVar37 = CONCAT26(sVar42,CONCAT24(sVar42,CONCAT22(sVar42,sVar42)));
      piVar17 = param_10 + 4;
      uVar8 = uVar22;
      psVar28 = psVar23 + 5;
      do {
        uVar39 = *(undefined8 *)(psVar28 + -4);
        uVar8 = uVar8 - 8;
        uVar43 = NEON_ext(uVar37,uVar39,6,1);
        uVar37 = *(undefined8 *)psVar28;
        uVar40 = NEON_ext(uVar39,uVar37,6,1);
        sVar38 = (short)((ulong)uVar37 >> 0x30);
        *(ulong *)(piVar17 + -2) =
             CONCAT44((int)((ulong)*(undefined8 *)(piVar17 + -2) >> 0x20) +
                      ((int)(short)((ulong)uVar39 >> 0x30) - (int)(short)((ulong)uVar43 >> 0x30)) *
                      iVar36,(int)*(undefined8 *)(piVar17 + -2) +
                             ((int)(short)((ulong)uVar39 >> 0x20) -
                             (int)(short)((ulong)uVar43 >> 0x20)) * iVar36);
        *(ulong *)(piVar17 + -4) =
             CONCAT44((int)((ulong)*(undefined8 *)(piVar17 + -4) >> 0x20) +
                      ((int)(short)((ulong)uVar39 >> 0x10) - (int)(short)((ulong)uVar43 >> 0x10)) *
                      iVar36,(int)*(undefined8 *)(piVar17 + -4) +
                             ((int)(short)uVar39 - (int)(short)uVar43) * iVar36);
        *(ulong *)(piVar17 + 2) =
             CONCAT44((int)((ulong)*(undefined8 *)(piVar17 + 2) >> 0x20) +
                      ((int)sVar38 - (int)(short)((ulong)uVar40 >> 0x30)) * iVar36,
                      (int)*(undefined8 *)(piVar17 + 2) +
                      ((int)(short)((ulong)uVar37 >> 0x20) - (int)(short)((ulong)uVar40 >> 0x20)) *
                      iVar36);
        *(ulong *)piVar17 =
             CONCAT44((int)((ulong)*(undefined8 *)piVar17 >> 0x20) +
                      ((int)(short)((ulong)uVar37 >> 0x10) - (int)(short)((ulong)uVar40 >> 0x10)) *
                      iVar36,(int)*(undefined8 *)piVar17 +
                             ((int)(short)uVar37 - (int)(short)uVar40) * iVar36);
        piVar17 = piVar17 + 8;
        psVar28 = psVar28 + 8;
      } while (uVar8 != 0);
      if (uVar22 != uVar20) goto LAB_0010a510;
    }
    do {
      sVar38 = psVar27[1];
      iVar14 = (int)sVar38 - (int)sVar41;
      iVar36 = local_21c;
      if (iVar14 <= local_21c) {
        iVar36 = iVar14;
      }
      uVar34 = uVar34 - 1;
      *piVar7 = iVar36 + *piVar7;
      local_21c = local_21c - iVar36;
      piVar7 = piVar7 + 1;
      psVar27 = psVar27 + 1;
      sVar41 = sVar38;
    } while (uVar34 != 0);
    lVar18 = *(long *)(param_1 + 0x38);
    iVar36 = 0;
    uVar34 = 0;
    do {
      while( true ) {
        lVar10 = uVar34 * 4;
        sVar41 = psVar23[uVar34 + 1];
        uVar11 = (param_10[uVar34] + iVar36) - *(int *)(param_4 + lVar10);
        uVar35 = uVar11 & ((int)uVar11 >> 0x1f ^ 0xffffffffU);
        iVar14 = (param_10[uVar34] + iVar36) - uVar35;
        param_10[uVar34] = iVar14;
        if (((int)sVar41 - (int)sVar42 < 1) || (*param_7 != 0)) {
          uVar9 = 0;
        }
        else {
          uVar9 = (uint)((long)uVar34 < (long)(int)*param_6);
        }
        uVar9 = ((int)sVar41 - (int)sVar42) * 0x10 | uVar9;
        iVar16 = (*(short *)(lVar18 + uVar34 * 2) + 0x18) * uVar9;
        iVar24 = uVar9 * -0x15 + (iVar16 >> 1);
        if (iVar24 + iVar14 < (int)(uVar9 * 0x10)) {
          iVar24 = iVar24 + (iVar16 >> 2);
        }
        else if (iVar24 + iVar14 < (int)(uVar9 * 0x18)) {
          iVar24 = iVar24 + (iVar16 >> 3);
        }
        iVar16 = uVar9 * 8;
        uVar30 = 0;
        if (iVar16 != 0) {
          uVar30 = (int)(iVar14 + uVar9 * 4 + iVar24) / iVar16;
        }
        uVar30 = uVar30 & ((int)uVar30 >> 0x1f ^ 0xffffffffU);
        *(uint *)(param_11 + lVar10) = uVar30;
        if (param_10[uVar34] >> 3 < (int)(uVar30 * 2)) {
          uVar30 = param_10[uVar34] >> 4;
          *(uint *)(param_11 + uVar34 * 4) = uVar30;
        }
        if (7 < (int)uVar30) {
          uVar30 = 8;
        }
        *(uint *)(param_11 + lVar10) = uVar30;
        uVar8 = uVar34 + 1;
        *(uint *)(param_12 + lVar10) = (uint)(param_10[uVar34] + iVar24 <= (int)(uVar30 * iVar16));
        param_10[uVar34] = param_10[uVar34] + *(int *)(param_11 + lVar10) * -0x10;
        uVar34 = uVar8;
        sVar42 = sVar41;
        if ((int)uVar11 < 1) break;
        uVar9 = 8 - *(int *)(param_11 + lVar10);
        uVar11 = uVar35 >> 4;
        if ((int)uVar9 <= (int)(uVar35 >> 4)) {
          uVar11 = uVar9;
        }
        *(uint *)(param_11 + lVar10) = uVar11 + *(int *)(param_11 + lVar10);
        *(uint *)(param_12 + lVar10) = (uint)((int)(uVar35 - iVar36) <= (int)(uVar11 * 0x10));
        iVar36 = uVar35 + uVar11 * -0x10;
        if (uVar20 == uVar8) goto LAB_0010a6e8;
      }
      iVar36 = 0;
    } while (uVar20 != uVar8);
LAB_0010a6e8:
    uVar34 = (ulong)uVar13;
    *param_9 = iVar36;
    if ((int)uVar32 <= (int)uVar13) goto LAB_0010a748;
  }
  else {
    uVar35 = *param_6;
    if ((int)uVar13 <= (int)*param_6) {
      uVar35 = uVar13;
    }
    *param_6 = uVar35;
    ec_enc_uint(param_13,uVar35,uVar13 + 1);
    if (((int)*param_6 < 1) || (local_21c == 0)) goto LAB_0010a46c;
    ec_enc_bit_logp(param_13,*param_7,1);
    local_21c = 0;
    if (0 < (int)uVar13) goto LAB_0010a47c;
LAB_0010a44c:
    uVar34 = 0;
    *param_9 = 0;
    if ((int)uVar32 < 1) goto LAB_0010a748;
  }
  uVar20 = uVar33 - uVar34;
  if (3 < uVar20) {
    lVar18 = uVar34 * 4;
    piVar7 = (int *)(param_11 + uVar33 * 4);
    piVar17 = (int *)(param_12 + uVar33 * 4);
    if (((param_10 + uVar33 <= (int *)(param_11 + lVar18) || piVar7 <= param_10 + uVar34) &&
        (piVar17 <= (int *)(param_11 + lVar18) || piVar7 <= (int *)(param_12 + lVar18))) &&
       (piVar17 <= param_10 + uVar34 || param_10 + uVar33 <= (int *)(param_12 + lVar18))) {
      uVar22 = uVar20 & 0xfffffffffffffffc;
      piVar7 = param_10 + uVar34;
      uVar34 = uVar22 + uVar34;
      puVar26 = (undefined8 *)(param_11 + lVar18);
      puVar29 = (ulong *)(param_12 + lVar18);
      uVar8 = uVar22;
      do {
        uVar37 = *(undefined8 *)piVar7;
        uVar8 = uVar8 - 4;
        puVar26[1] = CONCAT44((int)((long)*(undefined8 *)(piVar7 + 2) >> 0x24),
                              (int)*(undefined8 *)(piVar7 + 2) >> 4);
        *puVar26 = CONCAT44((int)((long)uVar37 >> 0x24),(int)uVar37 >> 4);
        piVar7[0] = 0;
        piVar7[1] = 0;
        piVar7[2] = 0;
        piVar7[3] = 0;
        uVar37 = *puVar26;
        puVar29[1] = (ulong)(CONCAT14(-((int)((ulong)puVar26[1] >> 0x20) < 1),
                                      (uint)(-((int)puVar26[1] < 1) & 1)) & 0x1ffffffff);
        *puVar29 = (ulong)(CONCAT14(-((int)((ulong)uVar37 >> 0x20) < 1),
                                    (uint)(-((int)uVar37 < 1) & 1)) & 0x1ffffffff);
        piVar7 = piVar7 + 4;
        puVar26 = puVar26 + 2;
        puVar29 = puVar29 + 2;
      } while (uVar8 != 0);
      if (uVar20 == uVar22) goto LAB_0010a748;
    }
  }
  lVar18 = uVar33 - uVar34;
  piVar7 = (int *)(param_11 + uVar34 * 4);
  puVar12 = (uint *)(param_12 + uVar34 * 4);
  piVar17 = param_10 + uVar34;
  do {
    *piVar7 = *piVar17 >> 4;
    *piVar17 = 0;
    lVar18 = lVar18 + -1;
    *puVar12 = (uint)(*piVar7 < 1);
    piVar7 = piVar7 + 1;
    puVar12 = puVar12 + 1;
    piVar17 = piVar17 + 1;
  } while (lVar18 != 0);
LAB_0010a748:
  if (*(long *)(lVar4 + 0x28) == local_70) {
    return uVar13;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


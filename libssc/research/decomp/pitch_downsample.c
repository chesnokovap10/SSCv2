/* pitch_downsample @ 00107230 size 1152 */

void pitch_downsample(long *param_1,short *param_2,ulong param_3)

{
  undefined8 *puVar1;
  short sVar2;
  uint uVar3;
  uint uVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  long lVar8;
  undefined4 uVar9;
  undefined8 uVar10;
  int *piVar11;
  int *piVar14;
  int *piVar21;
  int *piVar24;
  int iVar31;
  ulong uVar32;
  int *piVar33;
  int iVar34;
  ulong uVar35;
  undefined8 *puVar36;
  int *piVar37;
  int iVar38;
  ulong uVar39;
  long lVar40;
  int *piVar41;
  int *piVar42;
  short *psVar43;
  int *piVar44;
  int *piVar45;
  undefined2 uVar46;
  undefined2 uVar47;
  undefined2 uVar48;
  undefined2 uVar49;
  uint uVar50;
  uint uVar51;
  int iVar52;
  uint uVar53;
  undefined8 uVar54;
  undefined1 auVar55 [16];
  undefined1 auVar56 [16];
  undefined8 uVar57;
  undefined4 uVar60;
  undefined1 auVar58 [16];
  undefined1 auVar59 [16];
  undefined8 uVar61;
  undefined8 uVar62;
  int iVar63;
  undefined8 local_58;
  undefined8 local_50;
  undefined8 local_48;
  int local_40;
  long local_38;
  int *piVar12;
  int *piVar13;
  int *piVar15;
  int *piVar16;
  int *piVar17;
  int *piVar18;
  int *piVar19;
  int *piVar20;
  int *piVar22;
  int *piVar23;
  int *piVar25;
  int *piVar26;
  int *piVar27;
  int *piVar28;
  int *piVar29;
  int *piVar30;
  
  lVar8 = tpidr_el0;
  local_38 = *(long *)(lVar8 + 0x28);
  uVar3 = (uint)param_3;
  local_50 = 0;
  local_48 = 0;
  local_40 = 0;
  if ((int)uVar3 < 1) {
    iVar52 = 0;
    iVar63 = 0;
    iVar31 = 0;
    goto LAB_001073d8;
  }
  uVar32 = param_3 & 0xffffffff;
  if (uVar3 < 4) {
    uVar35 = 0;
    iVar31 = 0;
    iVar52 = 0;
LAB_00107300:
    lVar40 = uVar32 - uVar35;
    piVar33 = (int *)(*param_1 + uVar35 * 4);
    do {
      iVar63 = *piVar33;
      if (iVar52 <= iVar63) {
        iVar52 = iVar63;
      }
      if (iVar63 <= iVar31) {
        iVar31 = iVar63;
      }
      lVar40 = lVar40 + -1;
      piVar33 = piVar33 + 1;
    } while (lVar40 != 0);
  }
  else {
    uVar35 = param_3 & 0xfffffffc;
    uVar46 = 0;
    uVar47 = 0;
    uVar48 = 0;
    uVar49 = 0;
    puVar36 = (undefined8 *)(*param_1 + 8);
    uVar54 = 0;
    uVar57 = 0;
    uVar61 = 0;
    uVar39 = uVar35;
    do {
      puVar1 = puVar36 + -1;
      uVar62 = *puVar36;
      uVar39 = uVar39 - 4;
      puVar36 = puVar36 + 2;
      uVar57 = NEON_smax(uVar57,*puVar1,4);
      uVar61 = NEON_smax(uVar61,uVar62,4);
      uVar10 = NEON_smin(CONCAT26(uVar49,CONCAT24(uVar48,CONCAT22(uVar47,uVar46))),*puVar1,4);
      uVar46 = (undefined2)uVar10;
      uVar47 = (undefined2)((ulong)uVar10 >> 0x10);
      uVar48 = (undefined2)((ulong)uVar10 >> 0x20);
      uVar49 = (undefined2)((ulong)uVar10 >> 0x30);
      uVar54 = NEON_smin(uVar54,uVar62,4);
    } while (uVar39 != 0);
    uVar57 = NEON_smax(uVar57,uVar61,4);
    uVar54 = NEON_smin(uVar10,uVar54,4);
    uVar60 = (undefined4)((ulong)uVar57 >> 0x20);
    uVar9 = (undefined4)((ulong)uVar54 >> 0x20);
    uVar57 = NEON_smax(uVar57,CONCAT44(uVar60,uVar60),4);
    uVar54 = NEON_smin(uVar54,CONCAT44(uVar9,uVar9),4);
    iVar52 = (int)uVar57;
    iVar31 = (int)uVar54;
    if (uVar35 != uVar32) goto LAB_00107300;
  }
  if (iVar52 <= -iVar31) {
    iVar52 = -iVar31;
  }
  if (uVar3 < 4) {
    param_3 = 0;
    iVar31 = 0;
    iVar63 = 0;
LAB_001073b0:
    lVar40 = uVar32 - param_3;
    piVar33 = (int *)(param_1[1] + param_3 * 4);
    do {
      iVar34 = *piVar33;
      if (iVar63 <= iVar34) {
        iVar63 = iVar34;
      }
      if (iVar34 <= iVar31) {
        iVar31 = iVar34;
      }
      lVar40 = lVar40 + -1;
      piVar33 = piVar33 + 1;
    } while (lVar40 != 0);
  }
  else {
    param_3 = param_3 & 0xfffffffc;
    uVar46 = 0;
    uVar47 = 0;
    uVar48 = 0;
    uVar49 = 0;
    puVar36 = (undefined8 *)(param_1[1] + 8);
    uVar54 = 0;
    uVar57 = 0;
    uVar61 = 0;
    uVar39 = param_3;
    do {
      puVar1 = puVar36 + -1;
      uVar62 = *puVar36;
      uVar39 = uVar39 - 4;
      puVar36 = puVar36 + 2;
      uVar57 = NEON_smax(uVar57,*puVar1,4);
      uVar61 = NEON_smax(uVar61,uVar62,4);
      uVar10 = NEON_smin(CONCAT26(uVar49,CONCAT24(uVar48,CONCAT22(uVar47,uVar46))),*puVar1,4);
      uVar46 = (undefined2)uVar10;
      uVar47 = (undefined2)((ulong)uVar10 >> 0x10);
      uVar48 = (undefined2)((ulong)uVar10 >> 0x20);
      uVar49 = (undefined2)((ulong)uVar10 >> 0x30);
      uVar54 = NEON_smin(uVar54,uVar62,4);
    } while (uVar39 != 0);
    uVar57 = NEON_smax(uVar57,uVar61,4);
    uVar54 = NEON_smin(uVar10,uVar54,4);
    uVar60 = (undefined4)((ulong)uVar57 >> 0x20);
    uVar9 = (undefined4)((ulong)uVar54 >> 0x20);
    uVar57 = NEON_smax(uVar57,CONCAT44(uVar60,uVar60),4);
    uVar54 = NEON_smin(uVar54,CONCAT44(uVar9,uVar9),4);
    iVar63 = (int)uVar57;
    iVar31 = (int)uVar54;
    if (param_3 != uVar32) goto LAB_001073b0;
  }
  iVar31 = -iVar31;
LAB_001073d8:
  if (iVar63 <= iVar31) {
    iVar63 = iVar31;
  }
  if (iVar52 <= iVar63) {
    iVar52 = iVar63;
  }
  if (iVar52 < 2) {
    iVar52 = 1;
  }
  iVar31 = ec_ilog(iVar52);
  piVar33 = (int *)*param_1;
  piVar37 = (int *)param_1[1];
  uVar4 = (iVar31 * 0x10000 + -0x10000 >> 0x10) - 10;
  uVar4 = (uVar4 & ((int)uVar4 >> 0x1f ^ 0xffffffffU)) + 1;
  *param_2 = (short)((*piVar37 + (piVar37[1] >> 1) >> 1) >> (uVar4 & 0x1f)) +
             (short)((*piVar33 + (piVar33[1] >> 1) >> 1) >> (uVar4 & 0x1f));
  if (3 < (int)uVar3) {
    uVar3 = uVar3 >> 1;
    uVar32 = (ulong)uVar3;
    if (uVar3 < 3) {
      uVar32 = 2;
    }
    uVar32 = uVar32 - 1;
    if (uVar32 < 5) {
      uVar32 = 1;
    }
    else {
      uVar39 = 4;
      if ((uVar32 & 3) != 0) {
        uVar39 = uVar32 & 3;
      }
      lVar40 = uVar32 - uVar39;
      piVar41 = piVar37 + 2;
      piVar42 = piVar33 + 2;
      uVar32 = lVar40 + 1;
      uVar46 = (undefined2)-uVar4;
      uVar47 = (undefined2)(-uVar4 >> 0x10);
      psVar43 = param_2 + 1;
      do {
        piVar44 = piVar42 + -1;
        piVar11 = piVar42 + 1;
        piVar12 = piVar42 + 3;
        piVar13 = piVar42 + 5;
        piVar45 = piVar41 + -1;
        iVar31 = *piVar42;
        piVar14 = piVar42 + 1;
        piVar15 = piVar42 + 2;
        piVar16 = piVar42 + 3;
        piVar17 = piVar42 + 4;
        piVar18 = piVar42 + 5;
        piVar19 = piVar42 + 6;
        piVar20 = piVar42 + 7;
        piVar42 = piVar42 + 8;
        piVar21 = piVar41 + 1;
        piVar22 = piVar41 + 3;
        piVar23 = piVar41 + 5;
        iVar63 = *piVar41;
        piVar24 = piVar41 + 1;
        piVar25 = piVar41 + 2;
        piVar26 = piVar41 + 3;
        piVar27 = piVar41 + 4;
        piVar28 = piVar41 + 5;
        piVar29 = piVar41 + 6;
        piVar30 = piVar41 + 7;
        piVar41 = piVar41 + 8;
        lVar40 = lVar40 + -4;
        auVar55._0_4_ = iVar31 + (*piVar14 + *piVar44 >> 1) >> 1;
        auVar55._4_4_ = *piVar15 + (*piVar16 + *piVar11 >> 1) >> 1;
        auVar55._8_4_ = *piVar17 + (*piVar18 + *piVar12 >> 1) >> 1;
        auVar55._12_4_ = *piVar19 + (*piVar20 + *piVar13 >> 1) >> 1;
        auVar58._0_4_ = iVar63 + (*piVar24 + *piVar45 >> 1) >> 1;
        auVar58._4_4_ = *piVar25 + (*piVar26 + *piVar21 >> 1) >> 1;
        auVar58._8_4_ = *piVar27 + (*piVar28 + *piVar22 >> 1) >> 1;
        auVar58._12_4_ = *piVar29 + (*piVar30 + *piVar23 >> 1) >> 1;
        auVar56._4_2_ = uVar46;
        auVar56._0_4_ = -uVar4;
        auVar56._6_2_ = uVar47;
        auVar56._8_4_ = -uVar4;
        auVar56._12_4_ = -uVar4;
        auVar56 = NEON_sshl(auVar55,auVar56,4);
        auVar59._4_2_ = uVar46;
        auVar59._0_4_ = -uVar4;
        auVar59._6_2_ = uVar47;
        auVar59._8_4_ = -uVar4;
        auVar59._12_4_ = -uVar4;
        auVar59 = NEON_sshl(auVar58,auVar59,4);
        *(ulong *)psVar43 =
             CONCAT26(auVar59._12_2_ + auVar56._12_2_,
                      CONCAT24(auVar59._8_2_ + auVar56._8_2_,
                               CONCAT22(auVar59._4_2_ + auVar56._4_2_,auVar59._0_2_ + auVar56._0_2_)
                              ));
        psVar43 = psVar43 + 4;
      } while (lVar40 != 0);
    }
    piVar33 = piVar33 + uVar32 * 2;
    piVar37 = piVar37 + uVar32 * 2;
    do {
      piVar42 = piVar33 + -1;
      iVar31 = *piVar33;
      piVar41 = piVar33 + 1;
      piVar33 = piVar33 + 2;
      param_2[uVar32] =
           (short)((*piVar37 + (piVar37[1] + piVar37[-1] >> 1) >> 1) >> (uVar4 & 0x1f)) +
           (short)((iVar31 + (*piVar41 + *piVar42 >> 1) >> 1) >> (uVar4 & 0x1f));
      uVar32 = uVar32 + 1;
      piVar37 = piVar37 + 2;
    } while (uVar32 < uVar3);
  }
  _ssc_autocorr(param_2,&local_50);
  uVar54 = NEON_sshl(local_50,0xfffffff2fffffff3,4);
  sVar5 = (short)local_50;
  local_48 = CONCAT44((local_48._4_4_ + ((int)local_48._4_4_ >> 0x10) * -0x24) -
                      ((local_48._4_4_ & 0xffff) + (local_48._4_4_ & 0xffff) * 8 >> 0xe),
                      (int)local_48 - ((int)local_48 >> 0xc));
  local_50 = CONCAT44((int)((ulong)local_50 >> 0x20) - (int)((ulong)uVar54 >> 0x20),
                      (int)local_50 + (int)uVar54);
  local_40 = local_40 - (local_40 >> 10);
  _ssc_lpc(sVar5 - (short)uVar54,&local_58,&local_50);
  uVar3 = (short)local_58 * 0x7332;
  uVar4 = (short)((ulong)local_58 >> 0x10) * 0x67ac;
  uVar50 = (short)((ulong)local_58 >> 0x20) * 0x5d4d;
  uVar51 = (short)((ulong)local_58 >> 0x30) * 0x53f8;
  uVar53 = uVar3 >> 0xf;
  sVar5 = (short)(uVar4 >> 0xf);
  sVar6 = (short)(uVar50 >> 0xf);
  sVar7 = (short)(uVar51 >> 0xf);
  lVar40 = 2;
  local_58 = CONCAT26((short)(uVar51 >> 0xf),
                      CONCAT24((short)(uVar50 >> 0xf),
                               CONCAT22((short)(uVar4 >> 0xf),(short)(uVar3 >> 0xf))));
  iVar31 = 0;
  iVar63 = 0;
  iVar52 = 0;
  iVar34 = 0;
  iVar38 = (int)*param_2;
  do {
    sVar2 = *(short *)((long)param_2 + lVar40);
    *(short *)((long)param_2 + lVar40) =
         (short)(iVar63 * (short)(sVar7 + (short)((uint)(sVar6 * 0x6666) >> 0xf)) +
                 iVar31 * (sVar7 * 0xcccc >> 0x10) +
                 iVar52 * (short)(sVar6 + (short)((uint)(sVar5 * 0x6666) >> 0xf)) +
                 iVar34 * (short)(sVar5 + (short)((uint)((short)uVar53 * 0x6666) >> 0xf)) +
                 iVar38 * ((int)(uVar53 * 0x10000 + 0xccd0000) >> 0x10) + sVar2 * 0x1000 + 0x800U >>
                0xc);
    lVar40 = lVar40 + 2;
    iVar31 = iVar63;
    iVar63 = iVar52;
    iVar52 = iVar34;
    iVar34 = iVar38;
    iVar38 = (int)sVar2;
  } while (lVar40 != 0x760);
  if (*(long *)(lVar8 + 0x28) == local_38) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


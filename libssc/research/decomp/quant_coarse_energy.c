/* quant_coarse_energy @ 00108a84 size 1164 */

void quant_coarse_energy(long param_1,int param_2,ulong param_3,long param_4,long param_5,
                        uint param_6,undefined8 param_7,long *param_8,int param_9,int param_10,
                        uint *param_11)

{
  uint uVar1;
  uint uVar2;
  long lVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  long lVar8;
  ulong uVar9;
  short *psVar10;
  undefined8 *puVar11;
  ulong uVar12;
  long lVar13;
  undefined8 *puVar14;
  long lVar15;
  short *psVar16;
  ulong uVar17;
  long *plVar18;
  undefined2 uVar19;
  long lVar20;
  int iVar21;
  long lVar22;
  uint uVar23;
  int iVar24;
  int iVar25;
  int iVar26;
  int iVar27;
  short sVar28;
  short sVar30;
  short sVar31;
  undefined8 uVar29;
  short sVar32;
  short sVar33;
  short sVar35;
  short sVar36;
  undefined8 uVar34;
  short sVar37;
  undefined8 uVar38;
  undefined8 uVar39;
  undefined1 auStack_1f4 [100];
  long local_190;
  long lStack_188;
  long local_180;
  long local_170;
  long lStack_168;
  long local_160;
  long lStack_150;
  undefined4 uStack_148;
  undefined4 local_144;
  undefined4 uStack_140;
  undefined8 uStack_13c;
  undefined1 auStack_130 [92];
  undefined1 auStack_d4 [116];
  
  lVar3 = tpidr_el0;
  lVar8 = *(long *)(lVar3 + 0x28);
  uVar7 = (uint)param_3;
  if ((int)uVar7 < 1) {
    uVar23 = 0;
  }
  else {
    uVar9 = param_3 & 0xffffffff;
    if (uVar7 < 8) {
      uVar12 = 0;
      uVar23 = 0;
LAB_00108b64:
      lVar13 = uVar9 - uVar12;
      psVar10 = (short *)(param_5 + uVar12 * 2);
      psVar16 = (short *)(param_4 + uVar12 * 2);
      do {
        lVar13 = lVar13 + -1;
        iVar4 = ((int)*psVar16 >> 3) - ((int)*psVar10 >> 3);
        uVar23 = uVar23 + iVar4 * iVar4;
        psVar10 = psVar10 + 1;
        psVar16 = psVar16 + 1;
      } while (lVar13 != 0);
    }
    else {
      uVar12 = param_3 & 0xfffffff8;
      puVar11 = (undefined8 *)(param_4 + 8);
      iVar4 = 0;
      iVar6 = 0;
      iVar21 = 0;
      iVar5 = 0;
      puVar14 = (undefined8 *)(param_5 + 8);
      iVar24 = 0;
      iVar25 = 0;
      iVar27 = 0;
      iVar26 = 0;
      uVar17 = uVar12;
      do {
        uVar29 = puVar11[-1];
        uVar34 = *puVar11;
        uVar38 = puVar14[-1];
        uVar39 = *puVar14;
        puVar11 = puVar11 + 2;
        uVar17 = uVar17 - 8;
        sVar28 = ((short)uVar29 >> 3) - ((short)uVar38 >> 3);
        sVar30 = ((short)((ulong)uVar29 >> 0x10) >> 3) - ((short)((ulong)uVar38 >> 0x10) >> 3);
        sVar31 = ((short)((ulong)uVar29 >> 0x20) >> 3) - ((short)((ulong)uVar38 >> 0x20) >> 3);
        sVar32 = (short)((long)uVar29 >> 0x33) - (short)((long)uVar38 >> 0x33);
        sVar33 = ((short)uVar34 >> 3) - ((short)uVar39 >> 3);
        sVar35 = ((short)((ulong)uVar34 >> 0x10) >> 3) - ((short)((ulong)uVar39 >> 0x10) >> 3);
        sVar36 = ((short)((ulong)uVar34 >> 0x20) >> 3) - ((short)((ulong)uVar39 >> 0x20) >> 3);
        sVar37 = (short)((long)uVar34 >> 0x33) - (short)((long)uVar39 >> 0x33);
        iVar4 = iVar4 + (int)sVar28 * (int)sVar28;
        iVar6 = iVar6 + (int)sVar30 * (int)sVar30;
        iVar21 = iVar21 + (int)sVar31 * (int)sVar31;
        iVar5 = iVar5 + (int)sVar32 * (int)sVar32;
        iVar24 = iVar24 + (int)sVar33 * (int)sVar33;
        iVar25 = iVar25 + (int)sVar35 * (int)sVar35;
        iVar27 = iVar27 + (int)sVar36 * (int)sVar36;
        iVar26 = iVar26 + (int)sVar37 * (int)sVar37;
        puVar14 = puVar14 + 2;
      } while (uVar17 != 0);
      uVar23 = iVar24 + iVar4 + iVar25 + iVar6 + iVar27 + iVar21 + iVar26 + iVar5;
      if (uVar12 != uVar9) goto LAB_00108b64;
    }
    if (uVar7 < 8) {
      uVar12 = 0;
LAB_00108c18:
      lVar15 = (uVar12 + (long)*(int *)(param_1 + 8)) * 2;
      lVar13 = uVar9 - uVar12;
      psVar10 = (short *)(param_5 + lVar15);
      psVar16 = (short *)(param_4 + lVar15);
      do {
        lVar13 = lVar13 + -1;
        iVar4 = ((int)*psVar16 >> 3) - ((int)*psVar10 >> 3);
        uVar23 = uVar23 + iVar4 * iVar4;
        psVar10 = psVar10 + 1;
        psVar16 = psVar16 + 1;
      } while (lVar13 != 0);
    }
    else {
      iVar25 = 0;
      iVar27 = 0;
      iVar24 = 0;
      uVar12 = param_3 & 0xfffffff8;
      lVar13 = (long)*(int *)(param_1 + 8) * 2 + 8;
      iVar4 = 0;
      iVar6 = 0;
      iVar21 = 0;
      iVar5 = 0;
      puVar11 = (undefined8 *)(param_5 + lVar13);
      puVar14 = (undefined8 *)(param_4 + lVar13);
      uVar17 = uVar12;
      do {
        uVar29 = puVar14[-1];
        uVar34 = *puVar14;
        uVar38 = puVar11[-1];
        uVar39 = *puVar11;
        puVar11 = puVar11 + 2;
        uVar17 = uVar17 - 8;
        sVar28 = ((short)uVar29 >> 3) - ((short)uVar38 >> 3);
        sVar30 = ((short)((ulong)uVar29 >> 0x10) >> 3) - ((short)((ulong)uVar38 >> 0x10) >> 3);
        sVar31 = ((short)((ulong)uVar29 >> 0x20) >> 3) - ((short)((ulong)uVar38 >> 0x20) >> 3);
        sVar32 = (short)((long)uVar29 >> 0x33) - (short)((long)uVar38 >> 0x33);
        sVar33 = ((short)uVar34 >> 3) - ((short)uVar39 >> 3);
        sVar35 = ((short)((ulong)uVar34 >> 0x10) >> 3) - ((short)((ulong)uVar39 >> 0x10) >> 3);
        sVar36 = ((short)((ulong)uVar34 >> 0x20) >> 3) - ((short)((ulong)uVar39 >> 0x20) >> 3);
        sVar37 = (short)((long)uVar34 >> 0x33) - (short)((long)uVar39 >> 0x33);
        uVar23 = uVar23 + (int)sVar28 * (int)sVar28;
        iVar24 = iVar24 + (int)sVar30 * (int)sVar30;
        iVar25 = iVar25 + (int)sVar31 * (int)sVar31;
        iVar27 = iVar27 + (int)sVar32 * (int)sVar32;
        iVar4 = iVar4 + (int)sVar33 * (int)sVar33;
        iVar6 = iVar6 + (int)sVar35 * (int)sVar35;
        iVar21 = iVar21 + (int)sVar36 * (int)sVar36;
        iVar5 = iVar5 + (int)sVar37 * (int)sVar37;
        puVar14 = puVar14 + 2;
      } while (uVar17 != 0);
      uVar23 = iVar4 + uVar23 + iVar6 + iVar24 + iVar21 + iVar25 + iVar5 + iVar27;
      if (uVar12 != uVar9) goto LAB_00108c18;
    }
    if (uVar23 >> 0x11 < 0x19) {
      uVar23 = uVar23 >> 0xe;
    }
    else {
      uVar23 = 200;
    }
  }
  plVar18 = param_8 + 4;
  lVar13 = param_8[3];
  iVar4 = ec_ilog((int)*plVar18);
  iVar4 = (int)lVar13 - iVar4;
  uVar1 = iVar4 + 3;
  uVar19 = 0x4000;
  if (10 < param_2) {
    param_9 = param_9 * 0x80;
    if (0x3fff < param_9) {
      param_9 = 0x4000;
    }
    uVar19 = (undefined2)param_9;
  }
  uStack_13c = *(undefined8 *)((long)param_8 + 0x14);
  lStack_150 = *param_8;
  uStack_140 = (undefined4)((ulong)*(undefined8 *)((long)param_8 + 0xc) >> 0x20);
  uStack_148 = (undefined4)param_8[1];
  local_144 = (undefined4)((ulong)param_8[1] >> 0x20);
  local_160 = param_8[6];
  lStack_168 = param_8[5];
  local_170 = *plVar18;
  uVar2 = *(uint *)((long)param_8 + 0x1c);
  SSC_COPY16(auStack_d4,param_5,*(int *)(param_1 + 8) << 1);
  if (param_6 < uVar1) {
    iVar6 = 0;
  }
  else {
    iVar6 = FUN_00108f10(param_1,param_3 & 0xffffffff,param_4,auStack_d4,param_6,iVar4,&DAT_00116a47
                         ,auStack_130,param_8,1,uVar19);
    if ((param_10 != 0) && (uVar1 <= param_6)) {
      SSC_COPY16(param_5,auStack_d4,*(int *)(param_1 + 8) << 1);
      SSC_COPY16(param_7,auStack_130,*(int *)(param_1 + 8) << 1);
      goto LAB_00108ebc;
    }
  }
  iVar5 = ec_tell_frac(param_8);
  lVar13 = param_8[3];
  iVar21 = *(int *)((long)param_8 + 0x1c);
  lVar22 = param_8[2];
  lVar20 = param_8[1];
  lVar15 = *param_8;
  local_180 = param_8[6];
  lStack_188 = param_8[5];
  local_190 = *plVar18;
  SSC_COPY8(auStack_1f4);
  *(uint *)((long)param_8 + 0x1c) = uVar2;
  *(undefined8 *)((long)param_8 + 0x14) = uStack_13c;
  *(ulong *)((long)param_8 + 0xc) = CONCAT44(uStack_140,local_144);
  param_8[1] = CONCAT44(local_144,uStack_148);
  *param_8 = lStack_150;
  param_8[6] = local_160;
  param_8[5] = lStack_168;
  *plVar18 = local_170;
  iVar4 = FUN_00108f10(param_1,uVar7,param_4,param_5,param_6,iVar4,&DAT_00116a19,param_7,param_8,0,
                       uVar19);
  if ((param_6 < uVar1) ||
     ((iVar4 <= iVar6 && ((iVar6 != iVar4 || (iVar4 = ec_tell_frac(param_8), iVar4 <= iVar5)))))) {
    uVar23 = (*param_11 >> 2 & 0x3fff | ((int)*param_11 >> 0x10) << 0xe) + uVar23;
  }
  else {
    *param_8 = lVar15;
    *(int *)(param_8 + 3) = (int)lVar13;
    param_8[2] = lVar22;
    param_8[1] = lVar20;
    *(int *)((long)param_8 + 0x1c) = iVar21;
    param_8[6] = local_180;
    param_8[5] = lStack_188;
    *plVar18 = local_190;
    SSC_COPY8(lVar15 + (ulong)uVar2,auStack_1f4,iVar21 - uVar2);
    SSC_COPY16(param_5,auStack_d4,*(int *)(param_1 + 8) << 1);
    SSC_COPY16(param_7,auStack_130,*(int *)(param_1 + 8) << 1);
  }
LAB_00108ebc:
  *param_11 = uVar23;
  if (*(long *)(lVar3 + 0x28) != lVar8) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}


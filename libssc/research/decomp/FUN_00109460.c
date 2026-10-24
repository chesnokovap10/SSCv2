/* FUN_00109460 @ 00109460 size 2116 */

void FUN_00109460(long param_1,undefined1 (*param_2) [16],uint param_3,int param_4,
                 undefined8 param_5,int param_6,short param_7,uint param_8)

{
  short *psVar1;
  byte *pbVar2;
  byte bVar3;
  uint uVar4;
  ulong uVar5;
  long lVar6;
  undefined1 *puVar7;
  ushort uVar8;
  ushort uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  uint uVar14;
  ulong uVar15;
  int iVar16;
  short sVar17;
  uint uVar18;
  uint uVar19;
  long lVar20;
  ulong uVar21;
  long lVar22;
  short *psVar23;
  undefined1 (*pauVar24) [16];
  int iVar25;
  long lVar26;
  ulong uVar27;
  ulong uVar28;
  undefined1 (*pauVar29) [16];
  uint uVar30;
  undefined8 uVar31;
  int iVar32;
  int iVar33;
  int iVar34;
  int iVar35;
  int iVar36;
  int iVar37;
  int iVar38;
  int iVar39;
  int iVar40;
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
  int iVar53;
  int iVar54;
  int iVar55;
  int iVar56;
  int iVar57;
  int iVar58;
  int iVar59;
  int iVar60;
  undefined1 auVar61 [16];
  undefined1 auVar62 [16];
  undefined1 auVar63 [16];
  undefined1 auVar64 [16];
  uint local_74;
  int local_70;
  int iStack_6c;
  long local_68;
  
  lVar6 = tpidr_el0;
  local_68 = *(long *)(lVar6 + 0x28);
  lVar26 = *(long *)(param_1 + 8);
  uVar31 = *(undefined8 *)(param_1 + 0x20);
  lVar20 = (long)*(short *)(*(long *)(lVar26 + 0x68) +
                           (long)(*(int *)(param_1 + 0x10) + *(int *)(lVar26 + 8) * (param_6 + 1)) *
                           2);
  lVar22 = *(long *)(lVar26 + 0x70);
  pbVar2 = (byte *)(lVar22 + lVar20);
  bVar3 = *pbVar2;
  if (((param_6 == -1) || ((int)param_3 < 3)) || (param_4 <= (int)(pbVar2[bVar3] + 0xc))) {
    uVar18 = bVar3 + 1 >> 1;
    param_4 = param_4 + -1;
    uVar14 = (uint)bVar3;
    uVar13 = uVar18;
    if (param_4 <= (int)(uint)pbVar2[uVar18]) {
      uVar13 = 0;
      uVar14 = uVar18;
    }
    uVar18 = uVar13 + uVar14 + 1 >> 1;
    if (param_4 <= (int)(uint)pbVar2[uVar18]) {
      uVar14 = uVar18;
      uVar18 = uVar13;
    }
    uVar13 = uVar18 + uVar14 + 1 >> 1;
    if (param_4 <= (int)(uint)pbVar2[uVar13]) {
      uVar14 = uVar13;
      uVar13 = uVar18;
    }
    uVar18 = uVar13 + uVar14 + 1 >> 1;
    if (param_4 <= (int)(uint)pbVar2[uVar18]) {
      uVar14 = uVar18;
      uVar18 = uVar13;
    }
    uVar13 = uVar18 + uVar14 + 1 >> 1;
    if (param_4 <= (int)(uint)pbVar2[uVar13]) {
      uVar14 = uVar13;
      uVar13 = uVar18;
    }
    uVar18 = uVar13 + uVar14 + 1 >> 1;
    if (param_4 <= (int)(uint)pbVar2[uVar18]) {
      uVar14 = uVar18;
      uVar18 = uVar13;
    }
    if (uVar18 == 0) {
      uVar13 = 0xffffffff;
    }
    else {
      uVar13 = (uint)pbVar2[uVar18];
    }
    if ((int)(param_4 - uVar13) <= (int)((uint)pbVar2[uVar14] - param_4)) {
      uVar14 = uVar18;
    }
    uVar15 = (ulong)uVar14;
    if (uVar14 == 0) {
LAB_001096b0:
      uVar15 = 0;
    }
    else {
      iVar10 = pbVar2[uVar14] + 1;
      iVar25 = *(int *)(param_1 + 0x28) - iVar10;
      *(int *)(param_1 + 0x28) = iVar25;
      if (iVar25 < 0) {
        do {
          iVar25 = iVar10 + iVar25;
          uVar5 = uVar15 - 1;
          *(int *)(param_1 + 0x28) = iVar25;
          if (uVar5 == 0) goto LAB_001096b0;
          iVar10 = *(byte *)(lVar20 + lVar22 + -1 + uVar15) + 1;
          iVar25 = iVar25 - iVar10;
          *(int *)(param_1 + 0x28) = iVar25;
          uVar15 = uVar5;
        } while (iVar25 < 0);
        uVar14 = (uint)uVar5;
        if (uVar14 == 0) goto LAB_001096b0;
        uVar15 = uVar5 & 0xffffffff;
      }
      if (7 < uVar14) {
        uVar15 = (ulong)(((uint)uVar15 & 7 | 8) << (ulong)((int)(uVar15 >> 3) - 1U & 0x1f));
      }
      uVar15 = ssc_alg_quant(param_2,param_3,uVar15,*(undefined4 *)(param_1 + 0x18),param_5,uVar31);
    }
    goto LAB_00109b84;
  }
  iVar25 = param_6 + -1;
  iVar16 = (int)param_5;
  iVar11 = (param_3 & 0xfffffffe) - 1;
  uVar14 = param_3 >> 1;
  uVar15 = (ulong)uVar14;
  psVar1 = (short *)(*param_2 + uVar15 * 2);
  iVar10 = (int)*(short *)(*(long *)(lVar26 + 0x38) + (long)*(int *)(param_1 + 0x10) * 2) +
           iVar25 * 8;
  uVar13 = (param_4 - iVar10) - 0x20;
  uVar18 = 0;
  if (iVar11 != 0) {
    uVar18 = (param_4 + ((iVar10 >> 1) + -4) * iVar11) / iVar11;
  }
  uVar30 = param_8 & 1 | param_8 << 1;
  if (iVar16 != 1) {
    uVar30 = param_8;
  }
  if ((int)uVar18 <= (int)uVar13) {
    uVar13 = uVar18;
  }
  if (0x3f < (int)uVar13) {
    uVar13 = 0x40;
  }
  if ((int)uVar13 < 4) {
    uVar13 = 1;
  }
  else {
    uVar13 = ((int)(short)(&DAT_00102760)[uVar13 & 7] >> (0xe - (uVar13 >> 3) & 0x1f)) + 1U &
             0xfffffffe;
  }
  if (uVar14 - 1 < 0xf) {
    iVar10 = 1;
    iVar11 = 1;
    uVar21 = uVar15;
    psVar23 = psVar1;
    pauVar24 = param_2;
LAB_001097e0:
    do {
      uVar18 = (int)uVar21 - 1;
      uVar21 = (ulong)uVar18;
      iVar10 = iVar10 + (int)*(short *)*pauVar24 * (int)*(short *)*pauVar24;
      iVar11 = iVar11 + (int)*psVar23 * (int)*psVar23;
      psVar23 = psVar23 + 1;
      pauVar24 = (undefined1 (*) [16])(*pauVar24 + 2);
    } while (uVar18 != 0);
  }
  else {
    uVar5 = (ulong)(uVar14 - 1) + 1;
    uVar27 = uVar5 & 0x1fffffff0;
    uVar21 = (ulong)(uVar14 - (int)uVar27);
    iVar38 = 0;
    iVar39 = 0;
    iVar36 = 1;
    iVar37 = 0;
    psVar23 = psVar1 + uVar27;
    iVar32 = 0;
    iVar33 = 0;
    iVar34 = 0;
    iVar35 = 0;
    pauVar24 = (undefined1 (*) [16])(*param_2 + uVar27 * 2);
    iVar40 = 0;
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
    iVar53 = 0;
    iVar54 = 0;
    iVar55 = 0;
    iVar56 = 0;
    iVar57 = 0;
    iVar58 = 0;
    iVar59 = 0;
    uVar28 = uVar27;
    pauVar29 = param_2;
    iVar10 = iVar36;
    iVar11 = iVar37;
    iVar60 = iVar38;
    iVar12 = iVar39;
    do {
      auVar61 = *pauVar29;
      auVar62 = pauVar29[1];
      puVar7 = *pauVar29;
      pauVar29 = pauVar29 + 2;
      uVar28 = uVar28 - 0x10;
      auVar63 = NEON_ext(auVar61,auVar61,8,1);
      iVar36 = iVar36 + (int)auVar61._0_2_ * (int)auVar61._0_2_;
      iVar37 = iVar37 + (int)auVar61._2_2_ * (int)auVar61._2_2_;
      iVar38 = iVar38 + (int)auVar61._4_2_ * (int)auVar61._4_2_;
      iVar39 = iVar39 + (int)auVar61._6_2_ * (int)auVar61._6_2_;
      auVar64 = NEON_ext(auVar62,auVar62,8,1);
      iVar40 = iVar40 + (int)auVar62._0_2_ * (int)auVar62._0_2_;
      iVar41 = iVar41 + (int)auVar62._2_2_ * (int)auVar62._2_2_;
      iVar42 = iVar42 + (int)auVar62._4_2_ * (int)auVar62._4_2_;
      iVar43 = iVar43 + (int)auVar62._6_2_ * (int)auVar62._6_2_;
      auVar61 = *(undefined1 (*) [16])(puVar7 + uVar15 * 2);
      auVar62 = ((undefined1 (*) [16])(puVar7 + uVar15 * 2))[1];
      iVar32 = iVar32 + (int)auVar63._0_2_ * (int)auVar63._0_2_;
      iVar33 = iVar33 + (int)auVar63._2_2_ * (int)auVar63._2_2_;
      iVar34 = iVar34 + (int)auVar63._4_2_ * (int)auVar63._4_2_;
      iVar35 = iVar35 + (int)auVar63._6_2_ * (int)auVar63._6_2_;
      iVar44 = iVar44 + (int)auVar64._0_2_ * (int)auVar64._0_2_;
      iVar45 = iVar45 + (int)auVar64._2_2_ * (int)auVar64._2_2_;
      iVar46 = iVar46 + (int)auVar64._4_2_ * (int)auVar64._4_2_;
      iVar47 = iVar47 + (int)auVar64._6_2_ * (int)auVar64._6_2_;
      iVar10 = iVar10 + (int)auVar61._0_2_ * (int)auVar61._0_2_;
      iVar11 = iVar11 + (int)auVar61._2_2_ * (int)auVar61._2_2_;
      iVar60 = iVar60 + (int)auVar61._4_2_ * (int)auVar61._4_2_;
      iVar12 = iVar12 + (int)auVar61._6_2_ * (int)auVar61._6_2_;
      auVar61 = NEON_ext(auVar61,auVar61,8,1);
      iVar52 = iVar52 + (int)auVar62._0_2_ * (int)auVar62._0_2_;
      iVar53 = iVar53 + (int)auVar62._2_2_ * (int)auVar62._2_2_;
      iVar54 = iVar54 + (int)auVar62._4_2_ * (int)auVar62._4_2_;
      iVar55 = iVar55 + (int)auVar62._6_2_ * (int)auVar62._6_2_;
      auVar62 = NEON_ext(auVar62,auVar62,8,1);
      iVar48 = iVar48 + (int)auVar61._0_2_ * (int)auVar61._0_2_;
      iVar49 = iVar49 + (int)auVar61._2_2_ * (int)auVar61._2_2_;
      iVar50 = iVar50 + (int)auVar61._4_2_ * (int)auVar61._4_2_;
      iVar51 = iVar51 + (int)auVar61._6_2_ * (int)auVar61._6_2_;
      iVar56 = iVar56 + (int)auVar62._0_2_ * (int)auVar62._0_2_;
      iVar57 = iVar57 + (int)auVar62._2_2_ * (int)auVar62._2_2_;
      iVar58 = iVar58 + (int)auVar62._4_2_ * (int)auVar62._4_2_;
      iVar59 = iVar59 + (int)auVar62._6_2_ * (int)auVar62._6_2_;
    } while (uVar28 != 0);
    iVar11 = iVar52 + iVar10 + iVar56 + iVar48 + iVar53 + iVar11 + iVar57 + iVar49 +
             iVar54 + iVar60 + iVar58 + iVar50 + iVar55 + iVar12 + iVar59 + iVar51;
    iVar10 = iVar40 + iVar36 + iVar44 + iVar32 + iVar41 + iVar37 + iVar45 + iVar33 +
             iVar42 + iVar38 + iVar46 + iVar34 + iVar43 + iVar39 + iVar47 + iVar35;
    if (uVar5 != uVar27) goto LAB_001097e0;
  }
  uVar8 = ssc_sqrt(iVar11,param_2,uVar15,*(undefined4 *)(param_1 + 0x18));
  uVar9 = ssc_sqrt(iVar10);
  if ((short)uVar8 < (short)uVar9) {
    iVar10 = ssc_rcp((int)((uint)uVar9 << 0x10) >> 0x10);
    uVar18 = (uint)((ulong)((long)iVar10 * (long)((int)((uint)uVar8 << 0x10) >> 1)) >> 0x1f);
    if (0x7ffe < (int)uVar18) {
      uVar18 = 0x7fff;
    }
    uVar19 = -(uVar18 >> 0xf & 1) & 0xfffe0000 | (uVar18 & 0xffff) << 1;
    sVar17 = (short)(((int)(((int)(((short)uVar18 * 0x2690 + -0x2ea68000 >> 0x10) * uVar19 +
                                  -0x148000) >> 0x10) * uVar19 + 0x7fff8000) >> 0x10) *
                     (int)(short)uVar18 + 0x4000U >> 0xf) >> 1;
  }
  else {
    iVar10 = ssc_rcp((int)((uint)uVar8 << 0x10) >> 0x10);
    uVar18 = (uint)((ulong)((long)iVar10 * (long)((int)((uint)uVar9 << 0x10) >> 1)) >> 0x1f);
    if (0x7ffe < (int)uVar18) {
      uVar18 = 0x7fff;
    }
    uVar19 = -(uVar18 >> 0xf & 1) & 0xfffe0000 | (uVar18 & 0xffff) << 1;
    sVar17 = 0x6488 - (short)((((int)(((int)(((short)uVar18 * 0x2690 + -0x2ea68000 >> 0x10) * uVar19
                                            + -0x148000) >> 0x10) * uVar19 + 0x7fff8000) >> 0x10) *
                               (int)(short)uVar18 + 0x4000) * 2 >> 0x11);
  }
  local_74 = sVar17 * 0x517d >> 0xf;
  iVar10 = ssc_ec_tell_frac(uVar31);
  if (uVar13 != 1) {
    uVar18 = local_74 * uVar13 + 0x2000;
    iVar11 = (int)uVar18 >> 0xe;
    if (iVar16 < 2) {
      iVar12 = (int)uVar13 >> 1;
      iVar60 = (uVar13 - iVar11) + 1;
      iVar32 = iVar60 * ((uVar13 - iVar11) + 2);
      if (iVar11 <= iVar12) {
        iVar60 = iVar11 + 1;
      }
      iVar32 = (iVar12 + 1) * (iVar12 + 1) - (iVar32 >> 1);
      if (iVar11 <= iVar12) {
        iVar32 = (iVar11 + 1) * iVar11 >> 1;
      }
      ssc_ec_encode(uVar31,iVar32,iVar32 + iVar60);
    }
    else {
      ssc_ec_enc_uint(uVar31,iVar11,uVar13 + 1);
    }
    local_74 = 0;
    if (uVar13 != 0) {
      local_74 = (int)(uVar18 & 0xffffc000) / (int)uVar13;
    }
  }
  uVar13 = iVar16 + 1 >> 1;
  iVar11 = ssc_ec_tell_frac(uVar31);
  uVar18 = param_4 - (iVar11 - iVar10);
  if (local_74 == 0x4000) {
    iStack_6c = 0;
    local_70 = 0x7fff;
    uVar14 = ~(-1 << (ulong)(uVar13 & 0x1f)) << (ulong)(uVar13 & 0x1f);
    uVar19 = 0x4000;
LAB_001099f8:
    uVar30 = uVar14 & uVar30;
  }
  else {
    if (local_74 == 0) {
      local_70 = 0;
      iStack_6c = 0x7fff;
      uVar14 = ~(-1 << (ulong)(uVar13 & 0x1f));
      uVar19 = 0xffffc000;
      goto LAB_001099f8;
    }
    ssc_bitexact_cos_asm(local_74,0x4000 - local_74,&iStack_6c,&local_70);
    uVar19 = (int)LZCOUNT(local_70) - 0x11;
    uVar4 = (int)LZCOUNT(iStack_6c) - 0x11;
    iVar60 = (int)(short)(local_70 << (ulong)(uVar19 & 0x1f));
    iVar12 = (int)(short)(iStack_6c << (ulong)(uVar4 & 0x1f));
    uVar19 = (int)(short)(((short)(((iVar60 * -0xa25 + 0x4000 >> 0xf) + 0x1efc) * iVar60 + 0x4000U
                                  >> 0xf) + ((short)uVar4 - (short)uVar19) * 0x800) -
                         (short)(((iVar12 * -0xa25 + 0x4000 >> 0xf) + 0x1efc) * iVar12 + 0x4000U >>
                                0xf)) * (int)(short)(((ushort)param_3 & 0x3fe) * 0x40 + -0x80) +
             0x4000 >> 0xf;
    if ((1 < iVar16) && ((local_74 & 0x3fff) != 0)) {
      if ((int)local_74 < 0x2001) {
        uVar19 = uVar19 + (uVar14 >> (ulong)(3U - param_6 & 0x1f));
        uVar19 = uVar19 & (int)uVar19 >> 0x1f;
      }
      else {
        uVar19 = uVar19 - ((int)uVar19 >> (5U - param_6 & 0x1f));
      }
    }
  }
  uVar14 = (int)(uVar18 - uVar19) >> 1;
  iVar60 = (int)param_7;
  uVar19 = uVar18;
  if ((int)uVar14 <= (int)uVar18) {
    uVar19 = uVar14;
  }
  iVar11 = *(int *)(param_1 + 0x28) - (iVar11 - iVar10);
  uVar19 = uVar19 & ((int)uVar19 >> 0x1f ^ 0xffffffffU);
  iVar10 = uVar18 - uVar19;
  *(int *)(param_1 + 0x28) = iVar11;
  if ((int)uVar19 < iVar10) {
    iVar12 = FUN_00109460(param_1,psVar1,uVar15,iVar10,uVar13,iVar25,
                          (short)local_70 * iVar60 + 0x4000U >> 0xf,(int)uVar30 >> (uVar13 & 0x1f));
    iVar10 = (*(int *)(param_1 + 0x28) - iVar11) + iVar10;
    iVar11 = iVar10 + -0x18;
    if (local_74 == 0x4000 || iVar10 < 0x19) {
      iVar11 = 0;
    }
    uVar13 = FUN_00109460(param_1,param_2,uVar15,iVar11 + uVar19,uVar13,iVar25,
                          (short)iStack_6c * iVar60 + 0x4000U >> 0xf,uVar30);
    uVar15 = (ulong)(uVar13 | iVar12 << (ulong)(iVar16 >> 1 & 0x1f));
  }
  else {
    uVar14 = FUN_00109460(param_1,param_2,uVar15,uVar19,uVar13,iVar25,
                          (short)iStack_6c * iVar60 + 0x4000U >> 0xf,uVar30);
    iVar11 = (*(int *)(param_1 + 0x28) - iVar11) + uVar19;
    iVar12 = iVar11 + -0x18;
    if (local_74 == 0 || iVar11 < 0x19) {
      iVar12 = 0;
    }
    iVar10 = FUN_00109460(param_1,psVar1,uVar15,iVar12 + iVar10,uVar13,iVar25,
                          (short)local_70 * iVar60 + 0x4000U >> 0xf,(int)uVar30 >> (uVar13 & 0x1f));
    uVar15 = (ulong)(iVar10 << (ulong)(iVar16 >> 1 & 0x1f) | uVar14);
  }
LAB_00109b84:
  if (*(long *)(lVar6 + 0x28) == local_68) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar15);
}


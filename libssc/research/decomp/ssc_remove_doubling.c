/* ssc_remove_doubling @ 00112990 size 1868 */

uint ssc_remove_doubling(long param_1,uint param_2,uint param_3,int param_4,uint *param_5,
                        int param_6,short param_7)

{
  short *psVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  bool bVar9;
  bool bVar10;
  short sVar11;
  short sVar12;
  uint extraout_var;
  uint uVar13;
  uint uVar14;
  int iVar15;
  undefined8 *puVar16;
  ulong uVar17;
  short *psVar18;
  undefined8 *puVar19;
  int *piVar20;
  long lVar21;
  long lVar22;
  int iVar23;
  int iVar24;
  uint uVar25;
  int iVar26;
  int iVar27;
  short sVar28;
  int iVar29;
  int iVar30;
  int iVar31;
  int iVar32;
  int iVar33;
  int iVar34;
  int iVar35;
  short sVar38;
  short sVar39;
  undefined8 uVar36;
  short sVar40;
  undefined8 uVar37;
  undefined8 uVar41;
  int iVar42;
  int iVar43;
  int iVar44;
  int iVar45;
  undefined8 uVar46;
  long local_f0;
  uint local_e8;
  uint local_e4;
  
  iVar26 = (int)param_2 >> 1;
  iVar31 = 0;
  iVar33 = 0;
  iVar34 = 0;
  iVar35 = 0;
  iVar32 = param_4 >> 1;
  lVar22 = (long)((ulong)param_2 << 0x20) >> 0x21;
  uVar14 = (int)*param_5 >> 1;
  if (iVar26 <= (int)*param_5 >> 1) {
    uVar14 = iVar26 - 1;
  }
  puVar19 = (undefined8 *)(param_1 + (long)iVar26 * 2);
  iVar24 = 0;
  iVar27 = 0;
  iVar29 = 0;
  iVar30 = 0;
  *param_5 = uVar14;
  if (1 < param_4) {
    iVar24 = 0;
    iVar27 = 0;
    iVar29 = 0;
    iVar30 = 0;
    iVar42 = 0;
    iVar31 = 0;
    iVar33 = 0;
    iVar34 = 0;
    iVar35 = 0;
    puVar16 = puVar19;
    do {
      uVar41 = *(undefined8 *)((long)puVar16 + (long)(int)uVar14 * -2);
      iVar42 = iVar42 + 4;
      uVar36 = *puVar16;
      puVar16 = puVar16 + 1;
      sVar11 = (short)uVar36;
      sVar12 = (short)((ulong)uVar36 >> 0x10);
      sVar28 = (short)((ulong)uVar36 >> 0x20);
      sVar38 = (short)((ulong)uVar36 >> 0x30);
      iVar24 = iVar24 + (int)sVar11 * (int)sVar11;
      iVar27 = iVar27 + (int)sVar12 * (int)sVar12;
      iVar29 = iVar29 + (int)sVar28 * (int)sVar28;
      iVar30 = iVar30 + (int)sVar38 * (int)sVar38;
      iVar31 = iVar31 + (int)sVar11 * (int)(short)uVar41;
      iVar33 = iVar33 + (int)sVar12 * (int)(short)((ulong)uVar41 >> 0x10);
      iVar34 = iVar34 + (int)sVar28 * (int)(short)((ulong)uVar41 >> 0x20);
      iVar35 = iVar35 + (int)sVar38 * (int)(short)((ulong)uVar41 >> 0x30);
    } while (iVar42 < iVar32);
  }
  iVar24 = iVar24 + iVar27 + iVar29 + iVar30;
  local_e4 = iVar31 + iVar33 + iVar34 + iVar35;
  DAT_001247a0 = iVar24;
  if ((int)param_2 < 10) {
    uVar17 = 1;
    iVar31 = iVar24;
  }
  else {
    piVar20 = &DAT_001247b0;
    puVar16 = (undefined8 *)(param_1 + lVar22 * 2);
    uVar17 = 1;
    iVar31 = iVar24;
    do {
      puVar16 = puVar16 + -1;
      uVar36 = *puVar16;
      uVar17 = uVar17 + 4;
      uVar41 = *(undefined8 *)((long)puVar16 + (long)iVar32 * 2);
      sVar11 = (short)((ulong)uVar36 >> 0x10);
      sVar12 = (short)((ulong)uVar36 >> 0x20);
      sVar28 = (short)((ulong)uVar36 >> 0x30);
      sVar38 = (short)((ulong)uVar41 >> 0x10);
      sVar39 = (short)((ulong)uVar41 >> 0x20);
      sVar40 = (short)((ulong)uVar41 >> 0x30);
      iVar33 = ((int)sVar28 * (int)sVar28 - (int)sVar40 * (int)sVar40) + iVar31;
      iVar34 = iVar33 + ((int)sVar12 * (int)sVar12 - (int)sVar39 * (int)sVar39);
      iVar35 = iVar34 + ((int)sVar11 * (int)sVar11 - (int)sVar38 * (int)sVar38);
      iVar31 = iVar35 + ((int)(short)uVar36 * (int)(short)uVar36 -
                        (int)(short)uVar41 * (int)(short)uVar41);
      piVar20[-3] = iVar33;
      piVar20[-2] = iVar34;
      piVar20[-1] = iVar35;
      *piVar20 = iVar31;
      piVar20 = piVar20 + 4;
    } while ((long)uVar17 < (long)(iVar26 + -3));
  }
  if ((int)uVar17 <= iVar26) {
    lVar21 = (ulong)(iVar26 + 1) - (uVar17 & 0xffffffff);
    psVar18 = (short *)(param_1 + (lVar22 - (uVar17 & 0xffffffff)) * 2);
    piVar20 = &DAT_001247a0 + (uVar17 & 0xffffffff);
    do {
      sVar11 = *psVar18;
      lVar21 = lVar21 + -1;
      psVar1 = psVar18 + iVar32;
      psVar18 = psVar18 + -1;
      iVar31 = (iVar31 + (int)sVar11 * (int)sVar11) - (int)*psVar1 * (int)*psVar1;
      *piVar20 = iVar31;
      piVar20 = piVar20 + 1;
    } while (lVar21 != 0);
  }
  local_f0 = (long)(&DAT_001247a0)[(int)uVar14];
  iVar34 = (int)((ulong)(local_f0 * iVar24) >> 0x20);
  iVar31 = iVar34 + 1;
  uVar7 = 0x11 - (int)LZCOUNT(iVar31);
  iVar33 = iVar31 >> (uVar7 & 0x1e);
  if ((int)(uVar7 & 0xfffffffe) < 1) {
    iVar33 = iVar31 << (ulong)(-(uVar7 & 0xfffffffe) & 0x1f);
  }
  sVar11 = ssc_rsqrt_norm(iVar33);
  sVar12 = ssc_rsqrt_norm(iVar33);
  uVar7 = local_e4 & 0xffff;
  uVar2 = (int)local_e4 >> 0xf & 0xfffffffe;
  iVar35 = uVar2 * (int)sVar11 + ((int)(uVar7 * (int)sVar12) >> 0xf);
  if (iVar34 == -1) {
    if (iVar35 < 0x8000) {
      sVar11 = ssc_rsqrt_norm(iVar33);
      sVar12 = ssc_rsqrt_norm(iVar33);
      local_e8 = uVar2 * (int)sVar11 + ((int)(uVar7 * (int)sVar12) >> 0xf);
      goto LAB_00112c58;
    }
  }
  else {
    uVar13 = (0x1f - (int)LZCOUNT(iVar31) >> 1) + 1;
    if (iVar35 >> (uVar13 & 0x1f) < 0x8000) {
      sVar11 = ssc_rsqrt_norm(iVar33);
      sVar12 = ssc_rsqrt_norm(iVar33);
      local_e8 = (int)(uVar2 * (int)sVar11 + ((int)(uVar7 * (int)sVar12) >> 0xf)) >> (uVar13 & 0x1f)
      ;
      goto LAB_00112c58;
    }
  }
  local_e8 = 0x7fff;
LAB_00112c58:
  iVar33 = (int)(short)local_e8;
  lVar22 = 2;
  iVar31 = 2;
  uVar7 = uVar14;
  do {
    iVar35 = (int)lVar22;
    iVar34 = iVar35 << 1;
    uVar2 = 0;
    if (iVar34 != 0) {
      uVar2 = (int)(uVar14 * 2 + iVar35) / iVar34;
    }
    if ((int)uVar2 < (int)param_3 >> 1) break;
    if (lVar22 == 2) {
      uVar13 = uVar14;
      if ((int)(uVar2 + uVar14) <= iVar26) {
        uVar13 = uVar2 + uVar14;
      }
    }
    else {
      uVar13 = 0;
      if (iVar34 != 0) {
        uVar13 = (int)(iVar35 + uVar14 * 2 * (int)*(short *)(&UNK_00105d58 + lVar22 * 2)) / iVar34;
      }
    }
    iVar42 = 0;
    iVar43 = 0;
    iVar44 = 0;
    iVar45 = 0;
    iVar34 = 0;
    iVar27 = 0;
    iVar29 = 0;
    iVar30 = 0;
    if (1 < param_4) {
      iVar15 = 0;
      iVar34 = 0;
      iVar27 = 0;
      iVar29 = 0;
      iVar30 = 0;
      iVar42 = 0;
      iVar43 = 0;
      iVar44 = 0;
      iVar45 = 0;
      puVar16 = puVar19;
      do {
        uVar41 = *(undefined8 *)((long)puVar16 + (long)(int)uVar2 * -2);
        iVar15 = iVar15 + 4;
        uVar37 = *(undefined8 *)((long)puVar16 + (long)(int)uVar13 * -2);
        uVar36 = *puVar16;
        puVar16 = puVar16 + 1;
        sVar11 = (short)((ulong)uVar36 >> 0x10);
        sVar12 = (short)((ulong)uVar36 >> 0x20);
        sVar28 = (short)((ulong)uVar36 >> 0x30);
        iVar34 = iVar34 + (int)(short)uVar36 * (int)(short)uVar41;
        iVar27 = iVar27 + (int)sVar11 * (int)(short)((ulong)uVar41 >> 0x10);
        iVar29 = iVar29 + (int)sVar12 * (int)(short)((ulong)uVar41 >> 0x20);
        iVar30 = iVar30 + (int)sVar28 * (int)(short)((ulong)uVar41 >> 0x30);
        iVar42 = iVar42 + (int)(short)uVar36 * (int)(short)uVar37;
        iVar43 = iVar43 + (int)sVar11 * (int)(short)((ulong)uVar37 >> 0x10);
        iVar44 = iVar44 + (int)sVar12 * (int)(short)((ulong)uVar37 >> 0x20);
        iVar45 = iVar45 + (int)sVar28 * (int)(short)((ulong)uVar37 >> 0x30);
      } while (iVar15 < iVar32);
    }
    iVar5 = (&DAT_001247a0)[(int)uVar2];
    iVar6 = (&DAT_001247a0)[(int)uVar13];
    iVar23 = (int)((ulong)(((long)iVar6 + (long)iVar5) * (long)iVar24) >> 0x1f);
    iVar15 = iVar23 + 1;
    uVar13 = 0x11 - (int)LZCOUNT(iVar15);
    iVar4 = iVar15 >> (uVar13 & 0x1e);
    if ((int)(uVar13 & 0xfffffffe) < 1) {
      iVar4 = iVar15 << (ulong)(-(uVar13 & 0xfffffffe) & 0x1f);
    }
    sVar11 = ssc_rsqrt_norm(iVar4);
    sVar12 = ssc_rsqrt_norm(iVar4);
    uVar25 = iVar42 + iVar43 + iVar44 + iVar45 + iVar27 + iVar34 + iVar29 + iVar30;
    uVar13 = uVar25 & 0xffff;
    uVar3 = (int)uVar25 >> 0xf & 0xfffffffe;
    iVar34 = uVar3 * (int)sVar11 + ((int)(uVar13 * (int)sVar12) >> 0xf);
    if (iVar23 == -1) {
      if (iVar34 < 0x8000) {
        sVar11 = ssc_rsqrt_norm(iVar4);
        sVar12 = ssc_rsqrt_norm(iVar4);
        uVar13 = uVar3 * (int)sVar11 + ((int)(uVar13 * (int)sVar12) >> 0xf);
      }
      else {
LAB_00112eb0:
        uVar13 = 0x7fff;
      }
    }
    else {
      uVar8 = (0x1f - (int)LZCOUNT(iVar15) >> 1) + 1;
      if (0x7fff < iVar34 >> (uVar8 & 0x1f)) goto LAB_00112eb0;
      sVar11 = ssc_rsqrt_norm(iVar4);
      sVar12 = ssc_rsqrt_norm(iVar4);
      uVar13 = (int)(uVar3 * (int)sVar11 + ((int)(uVar13 * (int)sVar12) >> 0xf)) >> (uVar8 & 0x1f);
    }
    uVar8 = uVar2 - (param_6 >> 1);
    uVar3 = -uVar8;
    if (-1 < (int)uVar8) {
      uVar3 = uVar8;
    }
    sVar11 = param_7;
    if (1 < uVar3) {
      if (uVar3 == 2) {
        sVar11 = param_7 >> 1;
        if ((int)uVar14 <= iVar31 * iVar35 * 5) {
          sVar11 = 0;
        }
      }
      else {
        sVar11 = 0;
      }
    }
    iVar34 = (int)sVar11;
    if ((int)uVar2 < ((int)param_3 >> 1) * 3) {
      iVar35 = (iVar33 * 0x6ccd >> 0xf) - iVar34;
      iVar27 = 0x3333;
      bVar9 = SBORROW4(iVar35,0x3333);
      iVar34 = iVar35 + -0x3333;
      bVar10 = iVar35 == 0x3333;
LAB_00112f74:
      if (bVar10 || iVar34 < 0 != bVar9) {
        iVar35 = iVar27;
      }
    }
    else {
      iVar35 = (iVar33 * 0x599a >> 0xf) - iVar34;
      if (iVar35 < 0x2667) {
        iVar35 = 0x2666;
      }
      if ((int)uVar2 < (int)(param_3 & 0xfffffffe)) {
        iVar35 = (iVar33 * 0x7333 >> 0xf) - iVar34;
        iVar27 = 0x4000;
        bVar9 = SBORROW4(iVar35,0x4000);
        iVar34 = iVar35 + -0x4000;
        bVar10 = iVar35 == 0x4000;
        goto LAB_00112f74;
      }
    }
    if (iVar35 * 0x10000 < (int)(uVar13 * 0x10000)) {
      local_f0 = (long)iVar6 + (long)iVar5;
      local_e8 = uVar13;
      local_e4 = uVar25;
      uVar7 = uVar2;
    }
    lVar22 = lVar22 + 1;
    iVar31 = iVar31 + 1;
  } while (lVar22 != 0x10);
  local_e4 = local_e4 & ((int)local_e4 >> 0x1f ^ 0xffffffffU);
  if ((int)local_e4 < (int)local_f0) {
    ssc_frac_div32(local_e4,(int)local_f0 + 1);
    uVar14 = extraout_var & 0xffff;
  }
  else {
    uVar14 = 0x7fff;
  }
  iVar26 = 0;
  iVar31 = 0;
  iVar33 = 0;
  iVar34 = 0;
  iVar30 = 0;
  iVar42 = 0;
  iVar43 = 0;
  iVar44 = 0;
  iVar35 = 0;
  iVar24 = 0;
  iVar27 = 0;
  iVar29 = 0;
  if (1 < param_4) {
    iVar45 = 0;
    iVar35 = 0;
    iVar24 = 0;
    iVar27 = 0;
    iVar29 = 0;
    iVar30 = 0;
    iVar42 = 0;
    iVar43 = 0;
    iVar44 = 0;
    iVar26 = 0;
    iVar31 = 0;
    iVar33 = 0;
    iVar34 = 0;
    do {
      puVar16 = (undefined8 *)((long)puVar19 + (long)(int)uVar7 * -2);
      iVar45 = iVar45 + 4;
      uVar36 = *puVar19;
      uVar41 = *(undefined8 *)((long)puVar16 + 2);
      uVar37 = *puVar16;
      uVar46 = *(undefined8 *)((long)puVar16 + -2);
      sVar11 = (short)uVar36;
      sVar12 = (short)((ulong)uVar36 >> 0x10);
      sVar28 = (short)((ulong)uVar36 >> 0x20);
      sVar38 = (short)((ulong)uVar36 >> 0x30);
      iVar35 = iVar35 + (int)sVar11 * (int)(short)uVar41;
      iVar24 = iVar24 + (int)sVar12 * (int)(short)((ulong)uVar41 >> 0x10);
      iVar27 = iVar27 + (int)sVar28 * (int)(short)((ulong)uVar41 >> 0x20);
      iVar29 = iVar29 + (int)sVar38 * (int)(short)((ulong)uVar41 >> 0x30);
      iVar30 = iVar30 + (int)sVar11 * (int)(short)uVar37;
      iVar42 = iVar42 + (int)sVar12 * (int)(short)((ulong)uVar37 >> 0x10);
      iVar43 = iVar43 + (int)sVar28 * (int)(short)((ulong)uVar37 >> 0x20);
      iVar44 = iVar44 + (int)sVar38 * (int)(short)((ulong)uVar37 >> 0x30);
      iVar26 = iVar26 + (int)sVar11 * (int)(short)uVar46;
      iVar31 = iVar31 + (int)sVar12 * (int)(short)((ulong)uVar46 >> 0x10);
      iVar33 = iVar33 + (int)sVar28 * (int)(short)((ulong)uVar46 >> 0x20);
      iVar34 = iVar34 + (int)sVar38 * (int)(short)((ulong)uVar46 >> 0x30);
      puVar19 = puVar19 + 1;
    } while (iVar45 < iVar32);
  }
  iVar32 = iVar35 + iVar24 + iVar27 + iVar29;
  iVar35 = iVar30 + iVar42 + iVar43 + iVar44;
  iVar26 = iVar26 + iVar31 + iVar33 + iVar34;
  uVar2 = iVar35 - iVar32;
  if ((int)(((int)uVar2 >> 0x10) * 0xb334 + ((uVar2 & 0xffff) * 0x599a >> 0xf)) < iVar26 - iVar32) {
    iVar26 = 1;
  }
  else {
    uVar2 = iVar35 - iVar26;
    iVar26 = -(uint)((int)(((int)uVar2 >> 0x10) * 0xb334 + ((uVar2 & 0xffff) * 0x599a >> 0xf)) <
                    iVar32 - iVar26);
  }
  if ((short)uVar14 <= (short)local_e8) {
    local_e8 = uVar14;
  }
  uVar14 = iVar26 + uVar7 * 2;
  if ((int)param_3 <= (int)uVar14) {
    param_3 = uVar14;
  }
  *param_5 = param_3;
  return local_e8;
}


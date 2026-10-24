/* remove_doubling @ 001081e8 size 2204 */

uint remove_doubling(long param_1,uint param_2,uint param_3,int param_4,uint *param_5,int param_6,
                    short param_7)

{
  short *psVar1;
  short *psVar2;
  undefined8 *puVar3;
  long lVar4;
  uint uVar5;
  undefined8 *puVar6;
  undefined8 *puVar7;
  uint uVar8;
  long lVar9;
  uint uVar10;
  uint uVar11;
  bool bVar12;
  bool bVar13;
  short sVar14;
  short sVar15;
  int iVar16;
  int iVar17;
  uint extraout_var;
  ulong uVar18;
  uint uVar19;
  uint uVar20;
  uint uVar21;
  long lVar22;
  ulong uVar23;
  short *psVar24;
  ulong uVar25;
  long lVar26;
  undefined8 *puVar27;
  ulong uVar28;
  ulong uVar29;
  uint uVar30;
  uint uVar31;
  uint uVar32;
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
  short sVar48;
  short sVar50;
  int iVar49;
  int iVar51;
  int iVar52;
  short sVar53;
  short sVar55;
  int iVar54;
  short sVar56;
  short sVar58;
  int iVar57;
  int iVar59;
  int iVar60;
  undefined8 uVar61;
  undefined8 uVar62;
  undefined8 uVar63;
  undefined8 uVar64;
  undefined8 uVar65;
  undefined8 uVar66;
  
  iVar33 = (int)param_2 >> 1;
  puVar3 = (undefined8 *)(param_1 + (long)iVar33 * 2);
  uVar21 = (int)*param_5 >> 1;
  if (iVar33 <= (int)*param_5 >> 1) {
    uVar21 = iVar33 - 1;
  }
  uVar8 = param_4 >> 1;
  uVar18 = (ulong)uVar8;
  lVar9 = (long)((ulong)param_2 << 0x20) >> 0x21;
  *param_5 = uVar21;
  lVar22 = (long)(int)uVar21;
  if (param_4 < 2) {
    iVar39 = 0;
    uVar32 = 0;
  }
  else {
    if (uVar8 < 8) {
      uVar23 = 0;
      uVar32 = 0;
      iVar39 = 0;
    }
    else {
      uVar23 = uVar18 & 0xfffffff8;
      iVar47 = 0;
      iVar16 = 0;
      iVar34 = 0;
      iVar35 = 0;
      iVar36 = 0;
      iVar17 = 0;
      iVar37 = 0;
      iVar38 = 0;
      iVar39 = 0;
      iVar40 = 0;
      iVar41 = 0;
      iVar42 = 0;
      iVar43 = 0;
      iVar44 = 0;
      iVar45 = 0;
      iVar46 = 0;
      puVar27 = puVar3;
      uVar25 = uVar23;
      do {
        puVar7 = (undefined8 *)((long)puVar27 + lVar22 * -2);
        uVar61 = *puVar27;
        uVar62 = puVar27[1];
        uVar64 = *puVar7;
        uVar66 = puVar7[1];
        uVar25 = uVar25 - 8;
        puVar27 = puVar27 + 2;
        sVar14 = (short)uVar61;
        sVar15 = (short)((ulong)uVar61 >> 0x10);
        sVar48 = (short)((ulong)uVar61 >> 0x20);
        sVar50 = (short)((ulong)uVar61 >> 0x30);
        iVar39 = iVar39 + (int)sVar14 * (int)sVar14;
        iVar40 = iVar40 + (int)sVar15 * (int)sVar15;
        iVar41 = iVar41 + (int)sVar48 * (int)sVar48;
        iVar42 = iVar42 + (int)sVar50 * (int)sVar50;
        sVar53 = (short)uVar62;
        sVar55 = (short)((ulong)uVar62 >> 0x10);
        sVar56 = (short)((ulong)uVar62 >> 0x20);
        sVar58 = (short)((ulong)uVar62 >> 0x30);
        iVar43 = iVar43 + (int)sVar53 * (int)sVar53;
        iVar44 = iVar44 + (int)sVar55 * (int)sVar55;
        iVar45 = iVar45 + (int)sVar56 * (int)sVar56;
        iVar46 = iVar46 + (int)sVar58 * (int)sVar58;
        iVar47 = iVar47 + (int)(short)uVar64 * (int)sVar14;
        iVar16 = iVar16 + (int)(short)((ulong)uVar64 >> 0x10) * (int)sVar15;
        iVar34 = iVar34 + (int)(short)((ulong)uVar64 >> 0x20) * (int)sVar48;
        iVar35 = iVar35 + (int)(short)((ulong)uVar64 >> 0x30) * (int)sVar50;
        iVar36 = iVar36 + (int)(short)uVar66 * (int)sVar53;
        iVar17 = iVar17 + (int)(short)((ulong)uVar66 >> 0x10) * (int)sVar55;
        iVar37 = iVar37 + (int)(short)((ulong)uVar66 >> 0x20) * (int)sVar56;
        iVar38 = iVar38 + (int)(short)((ulong)uVar66 >> 0x30) * (int)sVar58;
      } while (uVar25 != 0);
      iVar39 = iVar43 + iVar39 + iVar44 + iVar40 + iVar45 + iVar41 + iVar46 + iVar42;
      uVar32 = iVar36 + iVar47 + iVar17 + iVar16 + iVar37 + iVar34 + iVar38 + iVar35;
      if (uVar23 == uVar18) goto LAB_00108314;
    }
    lVar26 = uVar18 - uVar23;
    psVar24 = (short *)(param_1 + (uVar23 + lVar9) * 2);
    do {
      sVar14 = *psVar24;
      psVar1 = psVar24 + -lVar22;
      lVar26 = lVar26 + -1;
      psVar24 = psVar24 + 1;
      iVar39 = iVar39 + (int)sVar14 * (int)sVar14;
      uVar32 = uVar32 + (int)*psVar1 * (int)sVar14;
    } while (lVar26 != 0);
  }
LAB_00108314:
  DAT_0012b864 = iVar39;
  if (1 < (int)param_2) {
    psVar24 = (short *)(param_1 + lVar9 * 2);
    lVar26 = 0;
    iVar47 = iVar39;
    do {
      psVar24 = psVar24 + -1;
      lVar4 = lVar26 + 1;
      iVar47 = (iVar47 + (int)*psVar24 * (int)*psVar24) -
               (int)psVar24[(int)uVar8] * (int)psVar24[(int)uVar8];
      (&DAT_0012b868)[lVar26] = iVar47;
      lVar26 = lVar4;
    } while (lVar4 < lVar9);
  }
  uVar25 = (ulong)(&DAT_0012b864)[lVar22];
  iVar47 = (int)(uVar25 * (long)iVar39 >> 0x20) + 1;
  iVar16 = ec_ilog(iVar47);
  uVar10 = (uint)(short)(iVar16 + -1);
  uVar30 = (iVar16 + -1) * 0x10000 >> 0x11;
  uVar31 = (uVar10 & 0xfffffffe) - 0xe;
  iVar16 = iVar47 >> (uVar31 & 0x1f);
  if ((int)uVar31 < 1) {
    iVar16 = iVar47 << (ulong)(0xe - (uVar10 & 0xfffffffe) & 0x1f);
  }
  uVar31 = uVar30 + 1;
  sVar14 = ssc_rsqrt_norm(iVar16);
  iVar35 = ((int)uVar32 >> 0x10) * 2;
  sVar15 = ssc_rsqrt_norm(iVar16);
  uVar30 = ~uVar30;
  iVar47 = iVar35 * sVar14 + ((int)((uVar32 & 0xffff) * (int)sVar15) >> 0xf);
  iVar34 = iVar47 >> (uVar31 & 0x1f);
  if ((int)uVar10 < 0) {
    iVar34 = iVar47 << (ulong)(uVar30 & 0x1f);
  }
  if (iVar34 < 0x8000) {
    sVar14 = ssc_rsqrt_norm(iVar16);
    sVar15 = ssc_rsqrt_norm(iVar16);
    iVar47 = iVar35 * sVar14 + ((int)((uVar32 & 0xffff) * (int)sVar15) >> 0xf);
    uVar31 = iVar47 >> (uVar31 & 0x1f);
    if ((int)uVar10 < 0) {
      uVar31 = iVar47 << (ulong)(uVar30 & 0x1f);
    }
  }
  else {
    uVar31 = 0x7fff;
  }
  uVar28 = uVar18 & 0xfffffff8;
  iVar34 = ((int)param_3 >> 1) * 3;
  iVar16 = (int)(short)uVar31;
  lVar22 = param_1 + lVar9 * 2;
  uVar23 = 2;
  iVar47 = 2;
  uVar30 = uVar21;
  do {
    iVar36 = (int)uVar23;
    iVar35 = iVar36 << 1;
    uVar10 = 0;
    if (iVar35 != 0) {
      uVar10 = (int)(uVar21 * 2 + iVar36) / iVar35;
    }
    uVar19 = (uint)uVar25;
    if ((int)uVar10 < (int)param_3 >> 1) break;
    if (uVar23 == 2) {
      uVar19 = uVar21;
      if ((int)(uVar10 + uVar21) <= iVar33) {
        uVar19 = uVar10 + uVar21;
      }
    }
    else {
      uVar19 = 0;
      if (iVar35 != 0) {
        uVar19 = (int)(iVar36 + uVar21 * 2 * *(int *)(&UNK_001169c0 + uVar23 * 4)) / iVar35;
      }
    }
    if (param_4 < 2) {
      iVar35 = 0;
      iVar17 = 0;
    }
    else {
      if (uVar8 < 8) {
        iVar17 = 0;
        iVar35 = 0;
        uVar29 = 0;
      }
      else {
        iVar17 = 0;
        iVar37 = 0;
        iVar38 = 0;
        iVar40 = 0;
        iVar41 = 0;
        iVar42 = 0;
        iVar43 = 0;
        iVar44 = 0;
        iVar35 = 0;
        iVar45 = 0;
        iVar46 = 0;
        iVar49 = 0;
        iVar51 = 0;
        iVar52 = 0;
        iVar54 = 0;
        iVar57 = 0;
        puVar27 = (undefined8 *)(lVar22 + 8);
        uVar29 = uVar28;
        do {
          puVar7 = (undefined8 *)((long)puVar27 + (long)(int)uVar10 * -2);
          puVar6 = (undefined8 *)((long)puVar27 + (long)(int)uVar19 * -2);
          uVar61 = puVar27[-1];
          uVar62 = *puVar27;
          uVar64 = puVar7[-1];
          uVar66 = *puVar7;
          uVar63 = puVar6[-1];
          uVar65 = *puVar6;
          uVar29 = uVar29 - 8;
          puVar27 = puVar27 + 2;
          sVar14 = (short)((ulong)uVar61 >> 0x10);
          sVar15 = (short)((ulong)uVar61 >> 0x20);
          sVar48 = (short)((ulong)uVar61 >> 0x30);
          iVar35 = iVar35 + (int)(short)uVar64 * (int)(short)uVar61;
          iVar45 = iVar45 + (int)(short)((ulong)uVar64 >> 0x10) * (int)sVar14;
          iVar46 = iVar46 + (int)(short)((ulong)uVar64 >> 0x20) * (int)sVar15;
          iVar49 = iVar49 + (int)(short)((ulong)uVar64 >> 0x30) * (int)sVar48;
          sVar50 = (short)((ulong)uVar62 >> 0x10);
          sVar53 = (short)((ulong)uVar62 >> 0x20);
          sVar55 = (short)((ulong)uVar62 >> 0x30);
          iVar51 = iVar51 + (int)(short)uVar66 * (int)(short)uVar62;
          iVar52 = iVar52 + (int)(short)((ulong)uVar66 >> 0x10) * (int)sVar50;
          iVar54 = iVar54 + (int)(short)((ulong)uVar66 >> 0x20) * (int)sVar53;
          iVar57 = iVar57 + (int)(short)((ulong)uVar66 >> 0x30) * (int)sVar55;
          iVar17 = iVar17 + (int)(short)uVar63 * (int)(short)uVar61;
          iVar37 = iVar37 + (int)(short)((ulong)uVar63 >> 0x10) * (int)sVar14;
          iVar38 = iVar38 + (int)(short)((ulong)uVar63 >> 0x20) * (int)sVar15;
          iVar40 = iVar40 + (int)(short)((ulong)uVar63 >> 0x30) * (int)sVar48;
          iVar41 = iVar41 + (int)(short)uVar65 * (int)(short)uVar62;
          iVar42 = iVar42 + (int)(short)((ulong)uVar65 >> 0x10) * (int)sVar50;
          iVar43 = iVar43 + (int)(short)((ulong)uVar65 >> 0x20) * (int)sVar53;
          iVar44 = iVar44 + (int)(short)((ulong)uVar65 >> 0x30) * (int)sVar55;
        } while (uVar29 != 0);
        iVar35 = iVar51 + iVar35 + iVar52 + iVar45 + iVar54 + iVar46 + iVar57 + iVar49;
        iVar17 = iVar41 + iVar17 + iVar42 + iVar37 + iVar43 + iVar38 + iVar44 + iVar40;
        uVar29 = uVar28;
        if (uVar28 == uVar18) goto LAB_00108650;
      }
      lVar26 = uVar18 - uVar29;
      psVar24 = (short *)(lVar22 + uVar29 * 2);
      do {
        sVar14 = *psVar24;
        psVar1 = psVar24 + -(long)(int)uVar10;
        psVar2 = psVar24 + -(long)(int)uVar19;
        lVar26 = lVar26 + -1;
        psVar24 = psVar24 + 1;
        iVar35 = iVar35 + (int)*psVar1 * (int)sVar14;
        iVar17 = iVar17 + (int)*psVar2 * (int)sVar14;
      } while (lVar26 != 0);
    }
LAB_00108650:
    uVar5 = iVar17 + iVar35;
    iVar37 = (&DAT_0012b864)[(int)uVar10];
    iVar38 = (&DAT_0012b864)[(int)uVar19];
    iVar35 = (int)((ulong)(((long)iVar38 + (long)iVar37) * (long)iVar39) >> 0x1f) + 1;
    iVar17 = ec_ilog(iVar35);
    uVar11 = (uint)(short)(iVar17 + -1);
    uVar19 = (iVar17 + -1) * 0x10000 >> 0x11;
    uVar20 = (uVar11 & 0xfffffffe) - 0xe;
    iVar17 = iVar35 >> (uVar20 & 0x1f);
    if ((int)uVar20 < 1) {
      iVar17 = iVar35 << (ulong)(0xe - (uVar11 & 0xfffffffe) & 0x1f);
    }
    uVar20 = uVar19 + 1;
    sVar14 = ssc_rsqrt_norm(iVar17);
    iVar41 = ((int)uVar5 >> 0x10) * 2;
    sVar15 = ssc_rsqrt_norm(iVar17);
    uVar19 = ~uVar19;
    iVar35 = iVar41 * sVar14 + ((int)((uVar5 & 0xffff) * (int)sVar15) >> 0xf);
    iVar40 = iVar35 >> (uVar20 & 0x1f);
    if ((int)uVar11 < 0) {
      iVar40 = iVar35 << (ulong)(uVar19 & 0x1f);
    }
    if (iVar40 < 0x8000) {
      sVar14 = ssc_rsqrt_norm(iVar17);
      sVar15 = ssc_rsqrt_norm(iVar17);
      iVar35 = iVar41 * sVar14 + ((int)((uVar5 & 0xffff) * (int)sVar15) >> 0xf);
      uVar20 = iVar35 >> (uVar20 & 0x1f);
      if ((int)uVar11 < 0) {
        uVar20 = iVar35 << (ulong)(uVar19 & 0x1f);
      }
    }
    else {
      uVar20 = 0x7fff;
    }
    iVar17 = uVar10 - (param_6 >> 1);
    iVar35 = -iVar17;
    if (-1 < iVar17) {
      iVar35 = iVar17;
    }
    sVar14 = param_7;
    if (iVar35 < 2) {
LAB_00108784:
      iVar35 = (int)sVar14;
      if ((int)uVar10 < iVar34) goto LAB_00108794;
LAB_001087bc:
      iVar36 = (iVar16 * 0x599a >> 0xf) - iVar35;
      if (iVar36 < 0x2667) {
        iVar36 = 0x2666;
      }
      if ((int)uVar10 < (int)(param_3 & 0xfffffffe)) {
        iVar36 = (iVar16 * 0x7333 >> 0xf) - iVar35;
        bVar12 = SBORROW4(iVar36,0x4000);
        iVar35 = iVar36 + -0x4000;
        bVar13 = iVar36 == 0x4000;
        iVar17 = 0x4000;
        goto LAB_001087ec;
      }
    }
    else {
      if (iVar35 == 2) {
        sVar14 = param_7 >> 1;
        if ((int)uVar21 <= iVar47 * iVar36 * 5) {
          sVar14 = 0;
        }
        goto LAB_00108784;
      }
      iVar35 = 0;
      if (iVar34 <= (int)uVar10) goto LAB_001087bc;
LAB_00108794:
      iVar36 = (iVar16 * 0x6ccd >> 0xf) - iVar35;
      iVar17 = 0x3333;
      bVar12 = SBORROW4(iVar36,0x3333);
      iVar35 = iVar36 + -0x3333;
      bVar13 = iVar36 == 0x3333;
LAB_001087ec:
      if (bVar13 || iVar35 < 0 != bVar12) {
        iVar36 = iVar17;
      }
    }
    uVar19 = (uint)((long)iVar38 + (long)iVar37);
    if ((int)(uVar20 * 0x10000) <= iVar36 * 0x10000) {
      uVar19 = (uint)uVar25;
      uVar5 = uVar32;
      uVar10 = uVar30;
      uVar20 = uVar31;
    }
    uVar31 = uVar20;
    uVar30 = uVar10;
    uVar32 = uVar5;
    uVar23 = uVar23 + 1;
    uVar25 = (ulong)uVar19;
    iVar47 = iVar47 + 1;
  } while (uVar23 < 0x10);
  uVar32 = uVar32 & ((int)uVar32 >> 0x1f ^ 0xffffffffU);
  if ((int)uVar32 < (int)uVar19) {
    frac_div32(uVar32,uVar19 + 1);
    uVar21 = extraout_var & 0xffff;
  }
  else {
    uVar21 = 0x7fff;
  }
  if (param_4 < 2) {
    iVar47 = 0;
    iVar39 = 0;
    iVar33 = 0;
  }
  else {
    uVar25 = (ulong)(int)uVar8;
    uVar18 = uVar25;
    if ((long)uVar25 < 2) {
      uVar18 = 1;
    }
    uVar8 = ~uVar30;
    if (uVar18 < 8) {
      uVar28 = 0;
      iVar33 = 0;
      iVar39 = 0;
      iVar47 = 0;
    }
    else {
      uVar23 = uVar25;
      if ((long)uVar25 < 2) {
        uVar23 = 1;
      }
      iVar39 = (int)(uVar23 - 1);
      iVar33 = 0;
      uVar28 = 0;
      if ((((int)((1 - uVar30) + iVar39) < (int)(1 - uVar30)) || (uVar23 - 1 >> 0x20 != 0)) ||
         ((int)(uVar8 + iVar39) < (int)uVar8)) {
        iVar39 = 0;
        iVar47 = 0;
      }
      else {
        uVar28 = uVar18 & 0x7ffffffffffffff8;
        iVar33 = 0;
        iVar16 = 0;
        iVar34 = 0;
        iVar35 = 0;
        iVar36 = 0;
        iVar17 = 0;
        iVar37 = 0;
        iVar38 = 0;
        iVar39 = 0;
        iVar40 = 0;
        iVar41 = 0;
        iVar42 = 0;
        iVar43 = 0;
        iVar44 = 0;
        iVar45 = 0;
        iVar46 = 0;
        iVar47 = 0;
        iVar49 = 0;
        iVar51 = 0;
        iVar52 = 0;
        puVar27 = (undefined8 *)(param_1 + lVar9 * 2 + 8);
        iVar54 = 0;
        iVar57 = 0;
        iVar59 = 0;
        iVar60 = 0;
        uVar23 = uVar28;
        uVar32 = uVar8;
        do {
          puVar7 = (undefined8 *)((long)puVar27 + (long)(int)uVar30 * -2);
          uVar61 = puVar27[-1];
          uVar62 = *puVar27;
          uVar64 = puVar7[-1];
          uVar66 = *puVar7;
          puVar7 = (undefined8 *)((long)puVar3 + (long)(int)uVar32 * 2);
          uVar23 = uVar23 - 8;
          puVar27 = puVar27 + 2;
          sVar14 = (short)uVar61;
          sVar15 = (short)((ulong)uVar61 >> 0x10);
          sVar48 = (short)((ulong)uVar61 >> 0x20);
          sVar50 = (short)((ulong)uVar61 >> 0x30);
          iVar39 = iVar39 + (int)(short)uVar64 * (int)sVar14;
          iVar40 = iVar40 + (int)(short)((ulong)uVar64 >> 0x10) * (int)sVar15;
          iVar41 = iVar41 + (int)(short)((ulong)uVar64 >> 0x20) * (int)sVar48;
          iVar42 = iVar42 + (int)(short)((ulong)uVar64 >> 0x30) * (int)sVar50;
          sVar53 = (short)uVar62;
          sVar55 = (short)((ulong)uVar62 >> 0x10);
          sVar56 = (short)((ulong)uVar62 >> 0x20);
          sVar58 = (short)((ulong)uVar62 >> 0x30);
          iVar43 = iVar43 + (int)(short)uVar66 * (int)sVar53;
          iVar44 = iVar44 + (int)(short)((ulong)uVar66 >> 0x10) * (int)sVar55;
          iVar45 = iVar45 + (int)(short)((ulong)uVar66 >> 0x20) * (int)sVar56;
          iVar46 = iVar46 + (int)(short)((ulong)uVar66 >> 0x30) * (int)sVar58;
          uVar61 = *puVar7;
          uVar62 = puVar7[1];
          puVar7 = (undefined8 *)((long)puVar3 + (long)(int)(uVar32 + 2) * 2);
          uVar32 = uVar32 + 8;
          iVar47 = iVar47 + (int)(short)uVar61 * (int)sVar14;
          iVar49 = iVar49 + (int)(short)((ulong)uVar61 >> 0x10) * (int)sVar15;
          iVar51 = iVar51 + (int)(short)((ulong)uVar61 >> 0x20) * (int)sVar48;
          iVar52 = iVar52 + (int)(short)((ulong)uVar61 >> 0x30) * (int)sVar50;
          iVar54 = iVar54 + (int)(short)uVar62 * (int)sVar53;
          iVar57 = iVar57 + (int)(short)((ulong)uVar62 >> 0x10) * (int)sVar55;
          iVar59 = iVar59 + (int)(short)((ulong)uVar62 >> 0x20) * (int)sVar56;
          iVar60 = iVar60 + (int)(short)((ulong)uVar62 >> 0x30) * (int)sVar58;
          uVar61 = *puVar7;
          uVar62 = puVar7[1];
          iVar33 = iVar33 + (int)(short)uVar61 * (int)sVar14;
          iVar16 = iVar16 + (int)(short)((ulong)uVar61 >> 0x10) * (int)sVar15;
          iVar34 = iVar34 + (int)(short)((ulong)uVar61 >> 0x20) * (int)sVar48;
          iVar35 = iVar35 + (int)(short)((ulong)uVar61 >> 0x30) * (int)sVar50;
          iVar36 = iVar36 + (int)(short)uVar62 * (int)sVar53;
          iVar17 = iVar17 + (int)(short)((ulong)uVar62 >> 0x10) * (int)sVar55;
          iVar37 = iVar37 + (int)(short)((ulong)uVar62 >> 0x20) * (int)sVar56;
          iVar38 = iVar38 + (int)(short)((ulong)uVar62 >> 0x30) * (int)sVar58;
        } while (uVar23 != 0);
        iVar47 = iVar54 + iVar47 + iVar57 + iVar49 + iVar59 + iVar51 + iVar60 + iVar52;
        iVar39 = iVar43 + iVar39 + iVar44 + iVar40 + iVar45 + iVar41 + iVar46 + iVar42;
        iVar33 = iVar36 + iVar33 + iVar17 + iVar16 + iVar37 + iVar34 + iVar38 + iVar35;
        if (uVar18 == uVar28) goto LAB_001089e8;
      }
    }
    do {
      iVar16 = (int)uVar28;
      lVar22 = uVar28 * 2;
      sVar14 = *(short *)((long)puVar3 + lVar22);
      uVar28 = uVar28 + 1;
      iVar39 = iVar39 + (int)*(short *)(param_1 + (lVar9 - (int)uVar30) * 2 + lVar22) * (int)sVar14;
      iVar33 = iVar33 + (int)*(short *)((long)puVar3 + (long)(int)(uVar8 + iVar16 + 2) * 2) *
                        (int)sVar14;
      iVar47 = iVar47 + (int)*(short *)((long)puVar3 + (long)(int)(uVar8 + iVar16) * 2) *
                        (int)sVar14;
    } while ((long)uVar28 < (long)uVar25);
  }
LAB_001089e8:
  if ((int)((iVar39 - iVar33 >> 0x10) * 0xb334 + ((iVar39 - iVar33 & 0xffffU) * 0x599a >> 0xf)) <
      iVar47 - iVar33) {
    iVar33 = 1;
  }
  else {
    iVar33 = -(uint)((int)((iVar39 - iVar47 >> 0x10) * 0xb334 +
                          ((iVar39 - iVar47 & 0xffffU) * 0x599a >> 0xf)) < iVar33 - iVar47);
  }
  if ((short)uVar21 <= (short)uVar31) {
    uVar31 = uVar21;
  }
  uVar21 = iVar33 + uVar30 * 2;
  if ((int)param_3 <= (int)uVar21) {
    param_3 = uVar21;
  }
  *param_5 = param_3;
  return uVar31;
}


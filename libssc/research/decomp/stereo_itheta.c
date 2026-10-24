/* stereo_itheta @ 00112ee4 size 936 */

int stereo_itheta(long param_1,long param_2,int param_3,uint param_4)

{
  ushort uVar1;
  ushort uVar2;
  int iVar3;
  ulong uVar4;
  ulong uVar5;
  ulong uVar6;
  ulong uVar7;
  undefined8 *puVar8;
  ushort *puVar9;
  long lVar10;
  undefined8 *puVar11;
  ushort *puVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  int iVar23;
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
  short sVar39;
  undefined8 uVar38;
  short sVar40;
  short sVar42;
  short sVar43;
  undefined8 uVar41;
  short sVar44;
  short sVar45;
  short sVar46;
  short sVar47;
  short sVar48;
  short sVar49;
  short sVar50;
  short sVar51;
  short sVar52;
  
  if (param_3 == 0) {
    if (0 < (int)param_4) {
      uVar4 = (ulong)(int)param_4;
      if (param_4 < 4) {
        iVar3 = 1;
        iVar20 = 1;
        uVar5 = uVar4;
      }
      else {
        iVar20 = 1;
        iVar13 = 0;
        uVar6 = uVar4 & 0xfffffffffffffffc;
        lVar10 = uVar4 * 2 + -4;
        iVar18 = 0;
        iVar19 = 0;
        uVar5 = uVar4 - uVar6;
        puVar9 = (ushort *)(param_1 + lVar10);
        puVar12 = (ushort *)(param_2 + lVar10);
        iVar14 = 0;
        iVar15 = 0;
        uVar7 = uVar6;
        iVar3 = iVar20;
        iVar17 = iVar13;
        do {
          uVar29 = NEON_rev64((ulong)CONCAT24(puVar9[1],(uint)*puVar9),4);
          uVar34 = NEON_rev64((ulong)CONCAT24(puVar9[-1],(uint)puVar9[-2]),4);
          uVar38 = NEON_rev64((ulong)CONCAT24(puVar12[1],(uint)*puVar12),4);
          uVar41 = NEON_rev64((ulong)CONCAT24(puVar12[-1],(uint)puVar12[-2]),4);
          iVar16 = (int)(short)((ulong)uVar29 >> 0x20);
          iVar21 = (int)(short)((ulong)uVar34 >> 0x20);
          iVar22 = (int)(short)((ulong)uVar38 >> 0x20);
          iVar23 = (int)(short)((ulong)uVar41 >> 0x20);
          puVar9 = puVar9 + -4;
          uVar7 = uVar7 - 4;
          iVar20 = iVar20 + (int)(short)uVar29 * (int)(short)uVar29;
          iVar13 = iVar13 + iVar16 * iVar16;
          iVar14 = iVar14 + (int)(short)uVar34 * (int)(short)uVar34;
          iVar15 = iVar15 + iVar21 * iVar21;
          iVar3 = iVar3 + (int)(short)uVar38 * (int)(short)uVar38;
          iVar17 = iVar17 + iVar22 * iVar22;
          iVar18 = iVar18 + (int)(short)uVar41 * (int)(short)uVar41;
          iVar19 = iVar19 + iVar23 * iVar23;
          puVar12 = puVar12 + -4;
        } while (uVar7 != 0);
        iVar20 = iVar14 + iVar20 + iVar15 + iVar13;
        iVar3 = iVar18 + iVar3 + iVar19 + iVar17;
        if (uVar6 == uVar4) goto LAB_00113134;
      }
      do {
        uVar5 = uVar5 - 1;
        iVar17 = (int)*(short *)(param_1 + uVar5 * 2);
        iVar20 = iVar20 + iVar17 * iVar17;
        iVar17 = (int)*(short *)(param_2 + uVar5 * 2);
        iVar3 = iVar3 + iVar17 * iVar17;
      } while (0 < (long)uVar5);
      goto LAB_00113134;
    }
  }
  else if (0 < (int)param_4) {
    uVar4 = (ulong)(int)param_4;
    if (param_4 < 8) {
      iVar3 = 1;
      iVar20 = 1;
      uVar5 = uVar4;
    }
    else {
      iVar22 = 0;
      iVar23 = 0;
      iVar20 = 1;
      iVar21 = 0;
      uVar6 = uVar4 & 0xfffffffffffffff8;
      lVar10 = uVar4 * 2 + -8;
      iVar13 = 0;
      iVar14 = 0;
      iVar15 = 0;
      iVar16 = 0;
      uVar5 = uVar4 - uVar6;
      puVar8 = (undefined8 *)(param_1 + lVar10);
      puVar11 = (undefined8 *)(param_2 + lVar10);
      iVar24 = 0;
      iVar25 = 0;
      iVar26 = 0;
      iVar27 = 0;
      uVar7 = uVar6;
      iVar3 = iVar20;
      iVar17 = iVar21;
      iVar18 = iVar22;
      iVar19 = iVar23;
      do {
        uVar34 = puVar8[-1];
        uVar29 = *puVar8;
        uVar41 = puVar11[-1];
        uVar38 = *puVar11;
        puVar8 = puVar8 + -2;
        uVar7 = uVar7 - 8;
        uVar29 = NEON_rev64(CONCAT26((short)((long)uVar29 >> 0x31),
                                     CONCAT24((short)((ulong)uVar29 >> 0x20) >> 1,
                                              CONCAT22((short)((ulong)uVar29 >> 0x10) >> 1,
                                                       (short)uVar29 >> 1))),2);
        uVar34 = NEON_rev64(CONCAT26((short)((long)uVar34 >> 0x31),
                                     CONCAT24((short)((ulong)uVar34 >> 0x20) >> 1,
                                              CONCAT22((short)((ulong)uVar34 >> 0x10) >> 1,
                                                       (short)uVar34 >> 1))),2);
        uVar38 = NEON_rev64(CONCAT26((short)((long)uVar38 >> 0x31),
                                     CONCAT24((short)((ulong)uVar38 >> 0x20) >> 1,
                                              CONCAT22((short)((ulong)uVar38 >> 0x10) >> 1,
                                                       (short)uVar38 >> 1))),2);
        uVar41 = NEON_rev64(CONCAT26((short)((long)uVar41 >> 0x31),
                                     CONCAT24((short)((ulong)uVar41 >> 0x20) >> 1,
                                              CONCAT22((short)((ulong)uVar41 >> 0x10) >> 1,
                                                       (short)uVar41 >> 1))),2);
        sVar45 = (short)uVar38 + (short)uVar29;
        sVar30 = (short)((ulong)uVar29 >> 0x10);
        sVar33 = (short)((ulong)uVar38 >> 0x10);
        sVar46 = sVar33 + sVar30;
        sVar31 = (short)((ulong)uVar29 >> 0x20);
        sVar39 = (short)((ulong)uVar38 >> 0x20);
        sVar47 = sVar39 + sVar31;
        sVar32 = (short)((ulong)uVar29 >> 0x30);
        sVar40 = (short)((ulong)uVar38 >> 0x30);
        sVar48 = sVar40 + sVar32;
        sVar49 = (short)uVar41 + (short)uVar34;
        sVar35 = (short)((ulong)uVar34 >> 0x10);
        sVar42 = (short)((ulong)uVar41 >> 0x10);
        sVar50 = sVar42 + sVar35;
        sVar36 = (short)((ulong)uVar34 >> 0x20);
        sVar43 = (short)((ulong)uVar41 >> 0x20);
        sVar51 = sVar43 + sVar36;
        sVar37 = (short)((ulong)uVar34 >> 0x30);
        sVar44 = (short)((ulong)uVar41 >> 0x30);
        sVar52 = sVar44 + sVar37;
        sVar28 = (short)uVar29 - (short)uVar38;
        sVar30 = sVar30 - sVar33;
        sVar31 = sVar31 - sVar39;
        sVar32 = sVar32 - sVar40;
        sVar33 = (short)uVar34 - (short)uVar41;
        sVar35 = sVar35 - sVar42;
        sVar36 = sVar36 - sVar43;
        sVar37 = sVar37 - sVar44;
        iVar20 = iVar20 + (int)sVar45 * (int)sVar45;
        iVar21 = iVar21 + (int)sVar46 * (int)sVar46;
        iVar22 = iVar22 + (int)sVar47 * (int)sVar47;
        iVar23 = iVar23 + (int)sVar48 * (int)sVar48;
        iVar24 = iVar24 + (int)sVar49 * (int)sVar49;
        iVar25 = iVar25 + (int)sVar50 * (int)sVar50;
        iVar26 = iVar26 + (int)sVar51 * (int)sVar51;
        iVar27 = iVar27 + (int)sVar52 * (int)sVar52;
        iVar3 = iVar3 + (int)sVar28 * (int)sVar28;
        iVar17 = iVar17 + (int)sVar30 * (int)sVar30;
        iVar18 = iVar18 + (int)sVar31 * (int)sVar31;
        iVar19 = iVar19 + (int)sVar32 * (int)sVar32;
        iVar13 = iVar13 + (int)sVar33 * (int)sVar33;
        iVar14 = iVar14 + (int)sVar35 * (int)sVar35;
        iVar15 = iVar15 + (int)sVar36 * (int)sVar36;
        iVar16 = iVar16 + (int)sVar37 * (int)sVar37;
        puVar11 = puVar11 + -2;
      } while (uVar7 != 0);
      iVar20 = iVar24 + iVar20 + iVar25 + iVar21 + iVar26 + iVar22 + iVar27 + iVar23;
      iVar3 = iVar13 + iVar3 + iVar14 + iVar17 + iVar15 + iVar18 + iVar16 + iVar19;
      if (uVar6 == uVar4) goto LAB_00113134;
    }
    do {
      uVar5 = uVar5 - 1;
      iVar18 = (int)*(short *)(param_1 + uVar5 * 2) >> 1;
      iVar19 = (int)*(short *)(param_2 + uVar5 * 2) >> 1;
      iVar17 = iVar19 + iVar18;
      iVar18 = iVar18 - iVar19;
      iVar20 = iVar20 + iVar17 * iVar17;
      iVar3 = iVar3 + iVar18 * iVar18;
    } while (0 < (long)uVar5);
    goto LAB_00113134;
  }
  iVar20 = 1;
  iVar3 = 1;
LAB_00113134:
  uVar1 = ssc_sqrt(iVar20);
  uVar2 = ssc_sqrt(iVar3);
  if ((short)uVar2 < (short)uVar1) {
    iVar3 = ssc_rcp((int)((uint)uVar1 << 0x10) >> 0x10);
    iVar3 = (int)((ulong)((long)iVar3 * (long)((int)((uint)uVar2 << 0x10) >> 1)) >> 0x1f);
    if (0x7ffe < iVar3) {
      iVar3 = 0x7fff;
    }
    iVar3 = (int)(short)iVar3;
    sVar28 = (short)(((int)((((int)((((int)((iVar3 * 0x2690 + 0x8000U & 0xffff0000) + 0xd1590000) >>
                                     0x10) * iVar3 * 2 + 0x8000U & 0xffff0000) - 0x150000) >> 0x10)
                             * iVar3 * 2 + 0x8000U & 0xffff0000) + 0x7fff0000) >> 0x10) * iVar3 +
                     0x4000U >> 0xf) >> 1;
  }
  else {
    iVar3 = ssc_rcp((int)((uint)uVar2 << 0x10) >> 0x10);
    iVar3 = (int)((ulong)((long)iVar3 * (long)((int)((uint)uVar1 << 0x10) >> 1)) >> 0x1f);
    if (0x7ffe < iVar3) {
      iVar3 = 0x7fff;
    }
    iVar3 = (int)(short)iVar3;
    sVar28 = 0x6488 - (short)((((int)((((int)((((int)((iVar3 * 0x2690 + 0x8000U & 0xffff0000) +
                                                     0xd1590000) >> 0x10) * iVar3 * 2 + 0x8000U &
                                              0xffff0000) - 0x150000) >> 0x10) * iVar3 * 2 + 0x8000U
                                      & 0xffff0000) + 0x7fff0000) >> 0x10) * iVar3 + 0x4000) * 2 >>
                             0x11);
  }
  return sVar28 * 0x517d >> 0xf;
}


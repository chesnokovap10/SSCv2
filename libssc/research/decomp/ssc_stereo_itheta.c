/* ssc_stereo_itheta @ 00116554 size 636 */

int ssc_stereo_itheta(long param_1,long param_2,uint param_3)

{
  short *psVar1;
  short *psVar2;
  uint uVar3;
  ushort uVar4;
  ushort uVar5;
  int iVar6;
  short sVar7;
  uint uVar8;
  ulong uVar9;
  ulong uVar10;
  ulong uVar11;
  long lVar12;
  ulong uVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  undefined8 uVar22;
  int iVar23;
  int iVar24;
  undefined8 uVar25;
  int iVar26;
  undefined8 uVar27;
  undefined8 uVar28;
  int iVar29;
  int iVar30;
  int iVar31;
  int iVar32;
  int iVar33;
  
  if ((int)param_3 < 1) {
    iVar20 = 1;
    iVar6 = 1;
  }
  else {
    uVar10 = (ulong)param_3;
    if (((param_3 < 4) || (uVar13 = uVar10 - 1, param_3 - 1 < (uint)uVar13)) ||
       (uVar13 >> 0x20 != 0)) {
      iVar6 = 1;
      iVar20 = 1;
      uVar11 = uVar10;
    }
    else {
      iVar16 = 0;
      iVar17 = 0;
      uVar11 = uVar10 & 3;
      iVar18 = 0;
      iVar19 = 0;
      iVar14 = 1;
      iVar15 = 0;
      uVar9 = uVar10 & 0xfffffffc;
      iVar6 = iVar14;
      iVar20 = iVar15;
      do {
        lVar12 = (uVar13 & 0xffffffff) * 2;
        uVar13 = uVar13 - 4;
        psVar1 = (short *)(param_1 + lVar12);
        psVar2 = (short *)(param_2 + lVar12);
        uVar9 = uVar9 - 4;
        uVar22 = NEON_rev64(CONCAT44((int)*psVar1 >> 1,(int)psVar1[-1] >> 1),4);
        uVar25 = NEON_rev64(CONCAT44((int)psVar1[-2] >> 1,(int)psVar1[-3] >> 1),4);
        uVar27 = NEON_rev64(CONCAT44((int)*psVar2 >> 1,(int)psVar2[-1] >> 1),4);
        uVar28 = NEON_rev64(CONCAT44((int)psVar2[-2] >> 1,(int)psVar2[-3] >> 1),4);
        iVar30 = (int)uVar27 + (int)uVar22;
        iVar23 = (int)((ulong)uVar22 >> 0x20);
        iVar24 = (int)((ulong)uVar27 >> 0x20);
        iVar31 = iVar24 + iVar23;
        iVar21 = (int)uVar22 - (int)uVar27;
        iVar23 = iVar23 - iVar24;
        iVar32 = (int)uVar28 + (int)uVar25;
        iVar26 = (int)((ulong)uVar25 >> 0x20);
        iVar29 = (int)((ulong)uVar28 >> 0x20);
        iVar33 = iVar29 + iVar26;
        iVar24 = (int)uVar25 - (int)uVar28;
        iVar26 = iVar26 - iVar29;
        iVar14 = iVar14 + iVar30 * iVar30;
        iVar15 = iVar15 + iVar31 * iVar31;
        iVar6 = iVar6 + iVar21 * iVar21;
        iVar20 = iVar20 + iVar23 * iVar23;
        iVar16 = iVar16 + iVar32 * iVar32;
        iVar17 = iVar17 + iVar33 * iVar33;
        iVar18 = iVar18 + iVar24 * iVar24;
        iVar19 = iVar19 + iVar26 * iVar26;
      } while (uVar9 != 0);
      iVar20 = iVar18 + iVar6 + iVar19 + iVar20;
      iVar6 = iVar16 + iVar14 + iVar17 + iVar15;
      if ((uVar10 & 0xfffffffc) == uVar10) goto LAB_001166bc;
    }
    uVar11 = uVar11 + 1;
    do {
      iVar14 = (int)uVar11;
      uVar11 = uVar11 - 1;
      lVar12 = (ulong)(iVar14 - 2) * 2;
      iVar15 = (int)*(short *)(param_1 + lVar12) >> 1;
      iVar16 = (int)*(short *)(param_2 + lVar12) >> 1;
      iVar14 = iVar16 + iVar15;
      iVar15 = iVar15 - iVar16;
      iVar6 = iVar6 + iVar14 * iVar14;
      iVar20 = iVar20 + iVar15 * iVar15;
    } while (1 < uVar11);
  }
LAB_001166bc:
  uVar4 = ssc_sqrt(iVar6);
  uVar5 = ssc_sqrt(iVar20);
  if ((short)uVar5 < (short)uVar4) {
    iVar6 = ssc_rcp((int)((uint)uVar4 << 0x10) >> 0x10);
    uVar8 = (uint)((ulong)((long)iVar6 * (long)((int)((uint)uVar5 << 0x10) >> 1)) >> 0x1f);
    if (0x7ffe < (int)uVar8) {
      uVar8 = 0x7fff;
    }
    uVar3 = -(uVar8 >> 0xf & 1) & 0xfffe0000 | (uVar8 & 0xffff) << 1;
    sVar7 = (short)(((int)(((int)(((short)uVar8 * 0x2690 + -0x2ea68000 >> 0x10) * uVar3 + -0x148000)
                           >> 0x10) * uVar3 + 0x7fff8000) >> 0x10) * (int)(short)uVar8 + 0x4000U >>
                   0xf) >> 1;
  }
  else {
    iVar6 = ssc_rcp((int)((uint)uVar5 << 0x10) >> 0x10);
    uVar8 = (uint)((ulong)((long)iVar6 * (long)((int)((uint)uVar4 << 0x10) >> 1)) >> 0x1f);
    if (0x7ffe < (int)uVar8) {
      uVar8 = 0x7fff;
    }
    uVar3 = -(uVar8 >> 0xf & 1) & 0xfffe0000 | (uVar8 & 0xffff) << 1;
    sVar7 = 0x6488 - (short)((((int)(((int)(((short)uVar8 * 0x2690 + -0x2ea68000 >> 0x10) * uVar3 +
                                           -0x148000) >> 0x10) * uVar3 + 0x7fff8000) >> 0x10) *
                              (int)(short)uVar8 + 0x4000) * 2 >> 0x11);
  }
  return sVar7 * 0x517d >> 0xf;
}


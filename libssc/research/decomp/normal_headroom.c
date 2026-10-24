/* normal_headroom @ 0010a36c size 1240 */

void normal_headroom(long param_1,int param_2,int param_3,long param_4,int param_5)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  uint uVar8;
  int iVar9;
  undefined8 *puVar10;
  uint *puVar11;
  ulong uVar12;
  undefined8 *puVar13;
  ulong uVar14;
  uint *puVar15;
  ulong uVar16;
  long lVar17;
  long lVar18;
  ulong uVar19;
  long lVar20;
  ulong uVar21;
  undefined8 uVar22;
  undefined8 uVar23;
  int iVar24;
  int iVar25;
  int iVar26;
  int iVar27;
  int iVar29;
  undefined8 uVar28;
  int iVar30;
  int iVar32;
  int iVar33;
  undefined8 uVar31;
  int iVar34;
  int iVar35;
  int iVar36;
  int iVar37;
  int iVar38;
  int iVar39;
  int iVar40;
  int iVar41;
  
  if (95999 < param_2) {
    sVar5 = *(short *)(param_4 + 0x28);
    uVar8 = (param_3 >> 2) * 0x22;
    iVar24 = uVar8 + sVar5 * param_3;
    lVar17 = (long)*(short *)(param_4 + 0x2c) * (long)param_3;
    if ((int)lVar17 <= iVar24) {
      return;
    }
    uVar16 = (ulong)iVar24;
    lVar18 = (long)param_5;
    uVar14 = lVar17 - uVar16;
    uVar21 = uVar16;
    if ((3 < uVar14) &&
       ((int)uVar8 <= (int)(uVar8 + (int)(~uVar16 + lVar17)) && ~uVar16 + lVar17 >> 0x20 == 0)) {
      puVar1 = (undefined1 *)(param_1 + uVar16 * 4);
      puVar2 = (undefined1 *)(param_1 + lVar17 * 4);
      puVar3 = (undefined1 *)(param_1 + (lVar18 + uVar16) * 4);
      puVar4 = (undefined1 *)(param_1 + (lVar18 + lVar17) * 4);
      if ((puVar4 <= puVar1 || puVar2 <= puVar3) &&
         ((headroom_gain + ((lVar17 + (int)uVar8) - uVar16) * 4 <= puVar1 ||
           puVar2 <= headroom_gain + (long)(int)uVar8 * 4 &&
          (headroom_gain + ((lVar17 + (int)uVar8) - uVar16) * 4 <= puVar3 ||
           puVar4 <= headroom_gain + (long)(int)uVar8 * 4)))) {
        uVar19 = uVar14 & 0xfffffffffffffffc;
        uVar21 = uVar19 + uVar16;
        uVar12 = uVar19;
        puVar10 = (undefined8 *)(param_1 + (lVar18 + uVar16) * 4);
        puVar13 = (undefined8 *)(param_1 + uVar16 * 4);
        do {
          uVar16 = -(ulong)(uVar8 >> 0x1f) & 0xfffffffc00000000 | (ulong)uVar8 << 2;
          uVar23 = puVar13[1];
          uVar22 = *puVar13;
          uVar31 = puVar10[1];
          uVar28 = *puVar10;
          uVar8 = uVar8 + 4;
          uVar12 = uVar12 - 4;
          iVar24 = (int)(short)*(undefined8 *)(headroom_gain + uVar16);
          iVar33 = (int)(short)((ulong)*(undefined8 *)(headroom_gain + uVar16) >> 0x20);
          iVar25 = (int)(short)*(undefined8 *)(headroom_gain + uVar16 + 8);
          iVar26 = (int)(short)((ulong)*(undefined8 *)(headroom_gain + uVar16 + 8) >> 0x20);
          puVar13[1] = CONCAT44(((uint)((long)uVar23 >> 0x2f) & 0xfffffffe) * iVar26 +
                                ((int)(iVar26 * (uint)(ushort)(CONCAT15((char)((ulong)uVar23 >> 0x28
                                                                              ),CONCAT14((char)((
                                                  ulong)uVar23 >> 0x20),(uint)(ushort)uVar23)) >>
                                                  0x20)) >> 0xf),
                                ((int)uVar23 >> 0xf & 0xfffffffeU) * iVar25 +
                                ((int)(iVar25 * (uint)(ushort)uVar23) >> 0xf));
          *puVar13 = CONCAT44(((uint)((long)uVar22 >> 0x2f) & 0xfffffffe) * iVar33 +
                              ((int)(iVar33 * (uint)(ushort)(CONCAT15((char)((ulong)uVar22 >> 0x28),
                                                                      CONCAT14((char)((ulong)uVar22
                                                                                     >> 0x20),
                                                                               (uint)(ushort)uVar22)
                                                                     ) >> 0x20)) >> 0xf),
                              ((int)uVar22 >> 0xf & 0xfffffffeU) * iVar24 +
                              ((int)(iVar24 * (uint)(ushort)uVar22) >> 0xf));
          puVar10[1] = CONCAT44(((uint)((long)uVar31 >> 0x2f) & 0xfffffffe) * iVar26 +
                                ((int)(iVar26 * (uint)(ushort)(CONCAT15((char)((ulong)uVar31 >> 0x28
                                                                              ),CONCAT14((char)((
                                                  ulong)uVar31 >> 0x20),(uint)(ushort)uVar31)) >>
                                                  0x20)) >> 0xf),
                                ((int)uVar31 >> 0xf & 0xfffffffeU) * iVar25 +
                                ((int)(iVar25 * (uint)(ushort)uVar31) >> 0xf));
          *puVar10 = CONCAT44(((uint)((long)uVar28 >> 0x2f) & 0xfffffffe) * iVar33 +
                              ((int)(iVar33 * (uint)(ushort)(CONCAT15((char)((ulong)uVar28 >> 0x28),
                                                                      CONCAT14((char)((ulong)uVar28
                                                                                     >> 0x20),
                                                                               (uint)(ushort)uVar28)
                                                                     ) >> 0x20)) >> 0xf),
                              ((int)uVar28 >> 0xf & 0xfffffffeU) * iVar24 +
                              ((int)(iVar24 * (uint)(ushort)uVar28) >> 0xf));
          puVar10 = puVar10 + 2;
          puVar13 = puVar13 + 2;
        } while (uVar12 != 0);
        if (uVar14 == uVar19) {
          return;
        }
      }
    }
    lVar18 = param_1 + lVar18 * 4;
    do {
      lVar20 = uVar21 * 4;
      uVar8 = (int)uVar21 - param_3 * sVar5;
      uVar16 = -(ulong)(uVar8 >> 0x1f) & 0xfffffffc00000000 | (ulong)uVar8 << 2;
      uVar21 = uVar21 + 1;
      *(uint *)(param_1 + lVar20) =
           ((int)*(uint *)(param_1 + lVar20) >> 0xf & 0xfffffffeU) *
           (int)*(short *)(headroom_gain + uVar16) +
           ((int)((int)*(short *)(headroom_gain + uVar16) * (*(uint *)(param_1 + lVar20) & 0xffff))
           >> 0xf);
      uVar8 = *(uint *)(lVar18 + lVar20);
      *(uint *)(lVar18 + lVar20) =
           ((int)uVar8 >> 0xf & 0xfffffffeU) * (int)*(short *)(headroom_gain + uVar16) +
           ((int)((int)*(short *)(headroom_gain + uVar16) * (uVar8 & 0xffff)) >> 0xf);
    } while ((long)uVar21 < lVar17);
    return;
  }
  sVar5 = *(short *)(param_4 + 0x22);
  sVar6 = *(short *)(param_4 + 0x28);
  sVar7 = *(short *)(param_4 + 0x2c);
  iVar24 = sVar5 * param_3;
  iVar33 = sVar6 * param_3;
  iVar25 = sVar7 * param_3;
  iVar26 = iVar33 + -0xf;
  iVar9 = iVar24;
  if (iVar24 < iVar26) {
    lVar17 = (long)iVar24;
    lVar18 = (long)iVar26;
    lVar20 = (long)param_5;
    uVar21 = lVar18 - lVar17;
    iVar9 = iVar26;
    if (3 < uVar21) {
      puVar10 = (undefined8 *)(param_1 + lVar17 * 4);
      puVar13 = (undefined8 *)(param_1 + (lVar20 + lVar17) * 4);
      if (((undefined8 *)(param_1 + (lVar20 + lVar18) * 4) <= puVar10) ||
         ((undefined8 *)(param_1 + lVar18 * 4) <= puVar13)) {
        uVar14 = uVar21 & 0xfffffffffffffffc;
        lVar17 = uVar14 + lVar17;
        iVar29 = iVar24 + 1;
        iVar30 = iVar24 + 2;
        iVar32 = iVar24 + 3;
        uVar16 = uVar14;
        iVar27 = iVar24;
        do {
          iVar34 = iVar27 - iVar24;
          iVar35 = iVar29 - iVar24;
          iVar36 = iVar30 - iVar24;
          iVar37 = iVar32 - iVar24;
          uVar31 = puVar10[1];
          uVar28 = *puVar10;
          uVar16 = uVar16 - 4;
          iVar27 = iVar27 + 4;
          iVar29 = iVar29 + 4;
          iVar30 = iVar30 + 4;
          iVar32 = iVar32 + 4;
          iVar34 = iVar34 * -0x30000 + 0x7fff0000;
          iVar35 = iVar35 * -0x30000 + 0x7fff0000;
          iVar36 = iVar36 * -0x30000 + 0x7fff0000;
          iVar37 = iVar37 * -0x30000 + 0x7fff0000;
          uVar23 = puVar13[1];
          uVar22 = *puVar13;
          iVar38 = iVar34 >> 0xf;
          iVar39 = iVar35 >> 0xf;
          iVar40 = iVar36 >> 0xf;
          iVar41 = iVar37 >> 0xf;
          iVar34 = iVar34 >> 0x10;
          iVar35 = iVar35 >> 0x10;
          iVar36 = iVar36 >> 0x10;
          iVar37 = iVar37 >> 0x10;
          puVar10[1] = CONCAT44(iVar41 * (int)((long)uVar31 >> 0x30) +
                                ((int)((uint)(ushort)(CONCAT15((char)((ulong)uVar31 >> 0x28),
                                                               CONCAT14((char)((ulong)uVar31 >> 0x20
                                                                              ),(uint)(ushort)uVar31
                                                                       )) >> 0x20) * iVar37) >> 0xf)
                                ,iVar40 * ((int)uVar31 >> 0x10) +
                                 ((int)((uint)(ushort)uVar31 * iVar36) >> 0xf));
          *puVar10 = CONCAT44(iVar39 * (int)((long)uVar28 >> 0x30) +
                              ((int)((uint)(ushort)(CONCAT15((char)((ulong)uVar28 >> 0x28),
                                                             CONCAT14((char)((ulong)uVar28 >> 0x20),
                                                                      (uint)(ushort)uVar28)) >> 0x20
                                                   ) * iVar35) >> 0xf),
                              iVar38 * ((int)uVar28 >> 0x10) +
                              ((int)((uint)(ushort)uVar28 * iVar34) >> 0xf));
          puVar13[1] = CONCAT44(iVar41 * (int)((long)uVar23 >> 0x30) +
                                ((int)((uint)(ushort)(CONCAT15((char)((ulong)uVar23 >> 0x28),
                                                               CONCAT14((char)((ulong)uVar23 >> 0x20
                                                                              ),(uint)(ushort)uVar23
                                                                       )) >> 0x20) * iVar37) >> 0xf)
                                ,iVar40 * ((int)uVar23 >> 0x10) +
                                 ((int)((uint)(ushort)uVar23 * iVar36) >> 0xf));
          *puVar13 = CONCAT44(iVar39 * (int)((long)uVar22 >> 0x30) +
                              ((int)((uint)(ushort)(CONCAT15((char)((ulong)uVar22 >> 0x28),
                                                             CONCAT14((char)((ulong)uVar22 >> 0x20),
                                                                      (uint)(ushort)uVar22)) >> 0x20
                                                   ) * iVar35) >> 0xf),
                              iVar38 * ((int)uVar22 >> 0x10) +
                              ((int)((uint)(ushort)uVar22 * iVar34) >> 0xf));
          puVar10 = puVar10 + 2;
          puVar13 = puVar13 + 2;
        } while (uVar16 != 0);
        if (uVar21 == uVar14) goto LAB_0010a4f8;
      }
    }
    iVar27 = (int)lVar17 * -0x30000 + param_3 * sVar5 * 0x30000 + 0x7fff0000;
    lVar18 = lVar18 - lVar17;
    puVar11 = (uint *)(param_1 + lVar17 * 4);
    puVar15 = (uint *)(param_1 + (lVar17 + lVar20) * 4);
    do {
      iVar29 = iVar27 >> 0x10;
      iVar30 = iVar27 >> 0xf;
      iVar27 = iVar27 + -0x30000;
      lVar18 = lVar18 + -1;
      *puVar11 = iVar30 * ((int)*puVar11 >> 0x10) + ((int)((*puVar11 & 0xffff) * iVar29) >> 0xf);
      *puVar15 = iVar30 * ((int)*puVar15 >> 0x10) + ((int)((*puVar15 & 0xffff) * iVar29) >> 0xf);
      puVar11 = puVar11 + 1;
      puVar15 = puVar15 + 1;
    } while (lVar18 != 0);
  }
LAB_0010a4f8:
  if (iVar26 < iVar25) {
    uVar8 = ((int)sVar7 - (int)sVar6) * param_3 + 0xe;
    uVar21 = (ulong)uVar8;
    lVar17 = (long)iVar26;
    if (2 < uVar8) {
      lVar18 = param_5 + lVar17;
      puVar10 = (undefined8 *)(param_1 + lVar17 * 4);
      puVar13 = (undefined8 *)(param_1 + lVar18 * 4);
      if (((undefined8 *)(param_1 + (lVar18 + uVar21) * 4 + 4) <= puVar10) ||
         ((undefined8 *)(param_1 + (lVar17 + uVar21) * 4 + 4) <= puVar13)) {
        iVar24 = (iVar9 - iVar24) * -3 + 0x7767;
        uVar14 = uVar21 + 1 & 0x1fffffffc;
        lVar17 = uVar14 + lVar17;
        iVar29 = iVar33 + -0xe;
        iVar30 = iVar33 + -0xd;
        iVar33 = iVar33 + -0xc;
        uVar16 = uVar14;
        iVar27 = iVar26;
        do {
          iVar32 = iVar27 - iVar26;
          iVar34 = iVar29 - iVar26;
          iVar35 = iVar30 - iVar26;
          iVar36 = iVar33 - iVar26;
          uVar31 = puVar13[1];
          uVar28 = *puVar13;
          uVar16 = uVar16 - 4;
          iVar27 = iVar27 + 4;
          iVar29 = iVar29 + 4;
          iVar30 = iVar30 + 4;
          iVar33 = iVar33 + 4;
          uVar23 = puVar10[1];
          uVar22 = *puVar10;
          iVar32 = (iVar24 + iVar32 * -5) * 0x10000;
          iVar34 = (iVar24 + iVar34 * -5) * 0x10000;
          iVar35 = (iVar24 + iVar35 * -5) * 0x10000;
          iVar36 = (iVar24 + iVar36 * -5) * 0x10000;
          iVar37 = iVar32 >> 0xf;
          iVar38 = iVar34 >> 0xf;
          iVar39 = iVar35 >> 0xf;
          iVar40 = iVar36 >> 0xf;
          iVar32 = iVar32 >> 0x10;
          iVar34 = iVar34 >> 0x10;
          iVar35 = iVar35 >> 0x10;
          iVar36 = iVar36 >> 0x10;
          puVar10[1] = CONCAT44(iVar40 * (int)((long)uVar23 >> 0x30) +
                                ((int)((uint)(ushort)(CONCAT15((char)((ulong)uVar23 >> 0x28),
                                                               CONCAT14((char)((ulong)uVar23 >> 0x20
                                                                              ),(uint)(ushort)uVar23
                                                                       )) >> 0x20) * iVar36) >> 0xf)
                                ,iVar39 * ((int)uVar23 >> 0x10) +
                                 ((int)((uint)(ushort)uVar23 * iVar35) >> 0xf));
          *puVar10 = CONCAT44(iVar38 * (int)((long)uVar22 >> 0x30) +
                              ((int)((uint)(ushort)(CONCAT15((char)((ulong)uVar22 >> 0x28),
                                                             CONCAT14((char)((ulong)uVar22 >> 0x20),
                                                                      (uint)(ushort)uVar22)) >> 0x20
                                                   ) * iVar34) >> 0xf),
                              iVar37 * ((int)uVar22 >> 0x10) +
                              ((int)((uint)(ushort)uVar22 * iVar32) >> 0xf));
          puVar13[1] = CONCAT44(iVar40 * (int)((long)uVar31 >> 0x30) +
                                ((int)((uint)(ushort)(CONCAT15((char)((ulong)uVar31 >> 0x28),
                                                               CONCAT14((char)((ulong)uVar31 >> 0x20
                                                                              ),(uint)(ushort)uVar31
                                                                       )) >> 0x20) * iVar36) >> 0xf)
                                ,iVar39 * ((int)uVar31 >> 0x10) +
                                 ((int)((uint)(ushort)uVar31 * iVar35) >> 0xf));
          *puVar13 = CONCAT44(iVar38 * (int)((long)uVar28 >> 0x30) +
                              ((int)((uint)(ushort)(CONCAT15((char)((ulong)uVar28 >> 0x28),
                                                             CONCAT14((char)((ulong)uVar28 >> 0x20),
                                                                      (uint)(ushort)uVar28)) >> 0x20
                                                   ) * iVar34) >> 0xf),
                              iVar37 * ((int)uVar28 >> 0x10) +
                              ((int)((uint)(ushort)uVar28 * iVar32) >> 0xf));
          puVar10 = puVar10 + 2;
          puVar13 = puVar13 + 2;
        } while (uVar16 != 0);
        if (uVar21 + 1 == uVar14) {
          return;
        }
      }
    }
    iVar25 = iVar25 - (int)lVar17;
    iVar24 = (iVar9 * -3 + param_3 * (sVar6 * 5 + sVar5 * 3) + (int)lVar17 * -5) * 0x10000 +
             0x771c0000;
    puVar11 = (uint *)(param_1 + (lVar17 + param_5) * 4);
    puVar15 = (uint *)(param_1 + lVar17 * 4);
    do {
      iVar33 = iVar24 >> 0x10;
      iVar26 = iVar24 >> 0xf;
      iVar24 = iVar24 + -0x50000;
      iVar25 = iVar25 + -1;
      *puVar15 = iVar26 * ((int)*puVar15 >> 0x10) + ((int)((*puVar15 & 0xffff) * iVar33) >> 0xf);
      *puVar11 = iVar26 * ((int)*puVar11 >> 0x10) + ((int)((*puVar11 & 0xffff) * iVar33) >> 0xf);
      puVar11 = puVar11 + 1;
      puVar15 = puVar15 + 1;
    } while (iVar25 != 0);
  }
  return;
}


/* normal_headroom @ 0010c424 size 1028 */

void normal_headroom(long param_1,int param_2,int param_3,long param_4)

{
  short sVar1;
  short sVar2;
  short sVar3;
  uint uVar4;
  undefined8 *puVar5;
  ulong uVar6;
  long lVar7;
  uint *puVar8;
  short *psVar9;
  ulong uVar10;
  undefined8 *puVar11;
  long lVar12;
  long lVar13;
  ulong uVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  int iVar24;
  int iVar25;
  int iVar26;
  int iVar27;
  int iVar28;
  undefined8 uVar29;
  int iVar30;
  int iVar31;
  undefined8 uVar32;
  int iVar33;
  int iVar34;
  
  if (95999 < param_2) {
    iVar23 = *(short *)(param_4 + 0x28) * param_3;
    param_3 = *(short *)(param_4 + 0x2c) * param_3;
    if (param_3 <= iVar23) {
      return;
    }
    lVar7 = (long)iVar23;
    lVar13 = (long)param_3;
    uVar14 = lVar13 - lVar7;
    lVar12 = lVar7;
    if ((3 < uVar14) &&
       ((puVar5 = (undefined8 *)(param_1 + lVar7 * 4), &headroom_gain + uVar14 * 2 <= puVar5 ||
        (param_1 + lVar13 * 4 + 0xd80U < (long)&headroom_gain + 1U)))) {
      uVar10 = uVar14 & 0xfffffffffffffffc;
      puVar11 = (undefined8 *)&headroom_gain;
      uVar6 = uVar10;
      do {
        uVar19 = puVar5[1];
        uVar18 = *puVar5;
        uVar6 = uVar6 - 4;
        iVar23 = (int)(short)*puVar11;
        iVar15 = (int)(short)((ulong)*puVar11 >> 0x20);
        iVar16 = (int)(short)puVar11[1];
        iVar17 = (int)(short)((ulong)puVar11[1] >> 0x20);
        puVar5[1] = CONCAT44((int)((long)uVar19 >> 0x30) * iVar17 * 2 +
                             ((int)(iVar17 * (uint)(ushort)(CONCAT15((char)((ulong)uVar19 >> 0x28),
                                                                     CONCAT14((char)((ulong)uVar19
                                                                                    >> 0x20),
                                                                              (uint)(ushort)uVar19))
                                                           >> 0x20)) >> 0xf),
                             ((int)uVar19 >> 0x10) * iVar16 * 2 +
                             ((int)(iVar16 * (uint)(ushort)uVar19) >> 0xf));
        *puVar5 = CONCAT44((int)((long)uVar18 >> 0x30) * iVar15 * 2 +
                           ((int)(iVar15 * (uint)(ushort)(CONCAT15((char)((ulong)uVar18 >> 0x28),
                                                                   CONCAT14((char)((ulong)uVar18 >>
                                                                                  0x20),
                                                                            (uint)(ushort)uVar18))
                                                         >> 0x20)) >> 0xf),
                           ((int)uVar18 >> 0x10) * iVar23 * 2 +
                           ((int)(iVar23 * (uint)(ushort)uVar18) >> 0xf));
        uVar19 = puVar5[0x1b1];
        uVar18 = puVar5[0x1b0];
        iVar23 = (int)(short)*puVar11;
        iVar15 = (int)(short)((ulong)*puVar11 >> 0x20);
        iVar16 = (int)(short)puVar11[1];
        iVar17 = (int)(short)((ulong)puVar11[1] >> 0x20);
        puVar5[0x1b1] =
             CONCAT44((int)((long)uVar19 >> 0x30) * iVar17 * 2 +
                      ((int)(iVar17 * (uint)(ushort)(CONCAT15((char)((ulong)uVar19 >> 0x28),
                                                              CONCAT14((char)((ulong)uVar19 >> 0x20)
                                                                       ,(uint)(ushort)uVar19)) >>
                                                    0x20)) >> 0xf),
                      ((int)uVar19 >> 0x10) * iVar16 * 2 +
                      ((int)(iVar16 * (uint)(ushort)uVar19) >> 0xf));
        puVar5[0x1b0] =
             CONCAT44((int)((long)uVar18 >> 0x30) * iVar15 * 2 +
                      ((int)(iVar15 * (uint)(ushort)(CONCAT15((char)((ulong)uVar18 >> 0x28),
                                                              CONCAT14((char)((ulong)uVar18 >> 0x20)
                                                                       ,(uint)(ushort)uVar18)) >>
                                                    0x20)) >> 0xf),
                      ((int)uVar18 >> 0x10) * iVar23 * 2 +
                      ((int)(iVar23 * (uint)(ushort)uVar18) >> 0xf));
        puVar5 = puVar5 + 2;
        puVar11 = puVar11 + 2;
      } while (uVar6 != 0);
      lVar12 = uVar10 + lVar7;
      if (uVar14 == uVar10) {
        return;
      }
    }
    puVar8 = (uint *)(param_1 + lVar12 * 4);
    lVar13 = lVar13 - lVar12;
    psVar9 = &headroom_gain + (lVar12 - lVar7) * 2;
    do {
      lVar13 = lVar13 + -1;
      *puVar8 = ((int)*puVar8 >> 0x10) * (int)*psVar9 * 2 +
                ((int)((int)*psVar9 * (*puVar8 & 0xffff)) >> 0xf);
      puVar8[0x360] =
           ((int)puVar8[0x360] >> 0x10) * (int)*psVar9 * 2 +
           ((int)((int)*psVar9 * (puVar8[0x360] & 0xffff)) >> 0xf);
      puVar8 = puVar8 + 1;
      psVar9 = psVar9 + 2;
    } while (lVar13 != 0);
    return;
  }
  sVar1 = *(short *)(param_4 + 0x28);
  sVar2 = *(short *)(param_4 + 0x22);
  sVar3 = *(short *)(param_4 + 0x2c);
  iVar23 = sVar1 * param_3;
  iVar15 = sVar2 * param_3;
  iVar17 = iVar23 + -0xf;
  iVar16 = sVar3 * param_3;
  if (iVar17 <= iVar15) {
    iVar15 = 0x7767;
    goto joined_r0x0010c4b8;
  }
  lVar13 = (long)iVar15;
  uVar14 = iVar17 - lVar13;
  if (uVar14 < 4) {
    uVar10 = 0;
LAB_0010c54c:
    puVar8 = (uint *)(param_1 + lVar13 * 4);
    lVar12 = iVar17 - lVar13;
    uVar4 = ((int)lVar13 + 1) - iVar15;
    do {
      iVar20 = (int)uVar10 * -0x30000 + 0x7fff0000;
      iVar15 = iVar20 >> 0xf;
      iVar20 = iVar20 >> 0x10;
      lVar12 = lVar12 + -1;
      uVar10 = (ulong)uVar4;
      *puVar8 = iVar15 * ((int)*puVar8 >> 0x10) + ((int)((*puVar8 & 0xffff) * iVar20) >> 0xf);
      puVar8[0x360] =
           iVar15 * ((int)puVar8[0x360] >> 0x10) + ((int)((puVar8[0x360] & 0xffff) * iVar20) >> 0xf)
      ;
      puVar8 = puVar8 + 1;
      uVar4 = uVar4 + 1;
    } while (lVar12 != 0);
  }
  else {
    iVar22 = 2;
    iVar24 = 3;
    iVar20 = 0;
    iVar21 = 1;
    uVar10 = uVar14 & 0xfffffffffffffffc;
    puVar5 = (undefined8 *)(param_1 + lVar13 * 4);
    lVar13 = uVar10 + lVar13;
    uVar6 = uVar10;
    do {
      uVar19 = puVar5[1];
      uVar18 = *puVar5;
      uVar32 = puVar5[0x1b1];
      uVar29 = puVar5[0x1b0];
      iVar25 = iVar20 * -0x30000 + 0x7fff0000;
      iVar26 = iVar21 * -0x30000 + 0x7fff0000;
      iVar27 = iVar22 * -0x30000 + 0x7fff0000;
      iVar28 = iVar24 * -0x30000 + 0x7fff0000;
      iVar30 = iVar25 >> 0xf;
      iVar31 = iVar26 >> 0xf;
      iVar33 = iVar27 >> 0xf;
      iVar34 = iVar28 >> 0xf;
      iVar25 = iVar25 >> 0x10;
      iVar26 = iVar26 >> 0x10;
      iVar27 = iVar27 >> 0x10;
      iVar28 = iVar28 >> 0x10;
      uVar6 = uVar6 - 4;
      iVar20 = iVar20 + 4;
      iVar21 = iVar21 + 4;
      iVar22 = iVar22 + 4;
      iVar24 = iVar24 + 4;
      puVar5[1] = CONCAT44(iVar34 * (int)((long)uVar19 >> 0x30) +
                           ((int)((uint)(ushort)(CONCAT15((char)((ulong)uVar19 >> 0x28),
                                                          CONCAT14((char)((ulong)uVar19 >> 0x20),
                                                                   (uint)(ushort)uVar19)) >> 0x20) *
                                 iVar28) >> 0xf),
                           iVar33 * ((int)uVar19 >> 0x10) +
                           ((int)((uint)(ushort)uVar19 * iVar27) >> 0xf));
      *puVar5 = CONCAT44(iVar31 * (int)((long)uVar18 >> 0x30) +
                         ((int)((uint)(ushort)(CONCAT15((char)((ulong)uVar18 >> 0x28),
                                                        CONCAT14((char)((ulong)uVar18 >> 0x20),
                                                                 (uint)(ushort)uVar18)) >> 0x20) *
                               iVar26) >> 0xf),
                         iVar30 * ((int)uVar18 >> 0x10) +
                         ((int)((uint)(ushort)uVar18 * iVar25) >> 0xf));
      puVar5[0x1b1] =
           CONCAT44(iVar34 * (int)((long)uVar32 >> 0x30) +
                    ((int)((uint)(ushort)(CONCAT15((char)((ulong)uVar32 >> 0x28),
                                                   CONCAT14((char)((ulong)uVar32 >> 0x20),
                                                            (uint)(ushort)uVar32)) >> 0x20) * iVar28
                          ) >> 0xf),
                    iVar33 * ((int)uVar32 >> 0x10) + ((int)((uint)(ushort)uVar32 * iVar27) >> 0xf));
      puVar5[0x1b0] =
           CONCAT44(iVar31 * (int)((long)uVar29 >> 0x30) +
                    ((int)((uint)(ushort)(CONCAT15((char)((ulong)uVar29 >> 0x28),
                                                   CONCAT14((char)((ulong)uVar29 >> 0x20),
                                                            (uint)(ushort)uVar29)) >> 0x20) * iVar26
                          ) >> 0xf),
                    iVar30 * ((int)uVar29 >> 0x10) + ((int)((uint)(ushort)uVar29 * iVar25) >> 0xf));
      puVar5 = puVar5 + 2;
    } while (uVar6 != 0);
    if (uVar14 != uVar10) goto LAB_0010c54c;
  }
  iVar15 = ((int)sVar1 - (int)sVar2) * param_3 * -3 + 0x7794;
joined_r0x0010c4b8:
  if (iVar17 < iVar16) {
    iVar20 = -(((int)sVar1 - (int)sVar3) * param_3);
    lVar13 = (long)iVar17;
    uVar14 = (ulong)(iVar20 + 0xe) + 1;
    if (3 < uVar14) {
      uVar4 = iVar20 + 0xfU & 3;
      lVar12 = uVar14 - uVar4;
      puVar5 = (undefined8 *)(param_1 + lVar13 * 4);
      lVar13 = lVar12 + lVar13;
      iVar21 = iVar23 + -0xe;
      iVar22 = iVar23 + -0xd;
      iVar23 = iVar23 + -0xc;
      iVar20 = iVar17;
      do {
        uVar19 = puVar5[1];
        uVar18 = *puVar5;
        uVar32 = puVar5[0x1b1];
        uVar29 = puVar5[0x1b0];
        iVar24 = (iVar15 + (iVar20 - iVar17) * -5) * 0x10000;
        iVar25 = (iVar15 + (iVar21 - iVar17) * -5) * 0x10000;
        iVar26 = (iVar15 + (iVar22 - iVar17) * -5) * 0x10000;
        iVar27 = (iVar15 + (iVar23 - iVar17) * -5) * 0x10000;
        iVar28 = iVar24 >> 0xf;
        iVar30 = iVar25 >> 0xf;
        iVar31 = iVar26 >> 0xf;
        iVar33 = iVar27 >> 0xf;
        iVar24 = iVar24 >> 0x10;
        iVar25 = iVar25 >> 0x10;
        iVar26 = iVar26 >> 0x10;
        iVar27 = iVar27 >> 0x10;
        iVar20 = iVar20 + 4;
        iVar21 = iVar21 + 4;
        iVar22 = iVar22 + 4;
        iVar23 = iVar23 + 4;
        lVar12 = lVar12 + -4;
        puVar5[1] = CONCAT44(iVar33 * (int)((long)uVar19 >> 0x30) +
                             ((int)((uint)(ushort)(CONCAT15((char)((ulong)uVar19 >> 0x28),
                                                            CONCAT14((char)((ulong)uVar19 >> 0x20),
                                                                     (uint)(ushort)uVar19)) >> 0x20)
                                   * iVar27) >> 0xf),
                             iVar31 * ((int)uVar19 >> 0x10) +
                             ((int)((uint)(ushort)uVar19 * iVar26) >> 0xf));
        *puVar5 = CONCAT44(iVar30 * (int)((long)uVar18 >> 0x30) +
                           ((int)((uint)(ushort)(CONCAT15((char)((ulong)uVar18 >> 0x28),
                                                          CONCAT14((char)((ulong)uVar18 >> 0x20),
                                                                   (uint)(ushort)uVar18)) >> 0x20) *
                                 iVar25) >> 0xf),
                           iVar28 * ((int)uVar18 >> 0x10) +
                           ((int)((uint)(ushort)uVar18 * iVar24) >> 0xf));
        puVar5[0x1b1] =
             CONCAT44(iVar33 * (int)((long)uVar32 >> 0x30) +
                      ((int)((uint)(ushort)(CONCAT15((char)((ulong)uVar32 >> 0x28),
                                                     CONCAT14((char)((ulong)uVar32 >> 0x20),
                                                              (uint)(ushort)uVar32)) >> 0x20) *
                            iVar27) >> 0xf),
                      iVar31 * ((int)uVar32 >> 0x10) + ((int)((uint)(ushort)uVar32 * iVar26) >> 0xf)
                     );
        puVar5[0x1b0] =
             CONCAT44(iVar30 * (int)((long)uVar29 >> 0x30) +
                      ((int)((uint)(ushort)(CONCAT15((char)((ulong)uVar29 >> 0x28),
                                                     CONCAT14((char)((ulong)uVar29 >> 0x20),
                                                              (uint)(ushort)uVar29)) >> 0x20) *
                            iVar25) >> 0xf),
                      iVar28 * ((int)uVar29 >> 0x10) + ((int)((uint)(ushort)uVar29 * iVar24) >> 0xf)
                     );
        puVar5 = puVar5 + 2;
      } while (lVar12 != 0);
      if (uVar4 == 0) {
        return;
      }
    }
    puVar8 = (uint *)(param_1 + lVar13 * 4);
    iVar23 = (iVar15 + param_3 * sVar1 * 5 + -0x4b + (int)lVar13 * -5) * 0x10000;
    iVar16 = iVar16 - (int)lVar13;
    do {
      iVar15 = iVar23 >> 0xf;
      iVar16 = iVar16 + -1;
      iVar17 = iVar23 >> 0x10;
      iVar23 = iVar23 + -0x50000;
      *puVar8 = iVar15 * ((int)*puVar8 >> 0x10) + ((int)((*puVar8 & 0xffff) * iVar17) >> 0xf);
      puVar8[0x360] =
           iVar15 * ((int)puVar8[0x360] >> 0x10) + ((int)((puVar8[0x360] & 0xffff) * iVar17) >> 0xf)
      ;
      puVar8 = puVar8 + 1;
    } while (iVar16 != 0);
  }
  return;
}


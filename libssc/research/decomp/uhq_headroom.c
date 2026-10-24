/* uhq_headroom @ 0010a844 size 1428 */

void uhq_headroom(long param_1,int param_2,int param_3,long param_4)

{
  uint *puVar1;
  long lVar2;
  undefined8 *puVar3;
  long lVar4;
  long lVar5;
  ulong uVar6;
  ulong uVar7;
  ulong uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  
  param_3 = *(short *)(param_4 + 0x24) * param_3;
  lVar5 = (long)param_3;
  lVar4 = lVar5 + 0x19;
  lVar2 = lVar4;
  if (lVar4 < lVar5 + 1) {
    lVar2 = lVar5 + 1;
  }
  uVar6 = lVar2 - lVar5;
  if (269999 < param_2) {
    if (uVar6 < 4) {
LAB_0010ab80:
      do {
        puVar1 = (uint *)(param_1 + lVar5 * 4);
        lVar5 = lVar5 + 1;
        *puVar1 = ((int)*puVar1 >> 0x10) * 0xf190 + ((*puVar1 & 0xffff) * 0x78c8 >> 0xf);
        puVar1[0x360] =
             ((int)puVar1[0x360] >> 0x10) * 0xf190 + ((puVar1[0x360] & 0xffff) * 0x78c8 >> 0xf);
      } while (lVar5 < lVar4);
    }
    else {
      uVar8 = uVar6 & 0xfffffffffffffffc;
      puVar3 = (undefined8 *)(param_1 + lVar5 * 4);
      lVar5 = uVar8 + lVar5;
      uVar7 = uVar8;
      do {
        uVar10 = puVar3[1];
        uVar9 = *puVar3;
        uVar7 = uVar7 - 4;
        uVar12 = puVar3[0x1b1];
        uVar11 = puVar3[0x1b0];
        puVar3[1] = CONCAT44((int)((long)uVar10 >> 0x30) * 0xf190 +
                             ((uint)(ushort)(CONCAT15((char)((ulong)uVar10 >> 0x28),
                                                      CONCAT14((char)((ulong)uVar10 >> 0x20),
                                                               (uint)(ushort)uVar10)) >> 0x20) *
                              0x78c8 >> 0xf),
                             ((int)uVar10 >> 0x10) * 0xf190 + ((uint)(ushort)uVar10 * 0x78c8 >> 0xf)
                            );
        *puVar3 = CONCAT44((int)((long)uVar9 >> 0x30) * 0xf190 +
                           ((uint)(ushort)(CONCAT15((char)((ulong)uVar9 >> 0x28),
                                                    CONCAT14((char)((ulong)uVar9 >> 0x20),
                                                             (uint)(ushort)uVar9)) >> 0x20) * 0x78c8
                           >> 0xf),((int)uVar9 >> 0x10) * 0xf190 +
                                   ((uint)(ushort)uVar9 * 0x78c8 >> 0xf));
        puVar3[0x1b1] =
             CONCAT44((int)((long)uVar12 >> 0x30) * 0xf190 +
                      ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                               CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                        (uint)(ushort)uVar12)) >> 0x20) * 0x78c8 >>
                      0xf),((int)uVar12 >> 0x10) * 0xf190 + ((uint)(ushort)uVar12 * 0x78c8 >> 0xf));
        puVar3[0x1b0] =
             CONCAT44((int)((long)uVar11 >> 0x30) * 0xf190 +
                      ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                               CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                        (uint)(ushort)uVar11)) >> 0x20) * 0x78c8 >>
                      0xf),((int)uVar11 >> 0x10) * 0xf190 + ((uint)(ushort)uVar11 * 0x78c8 >> 0xf));
        puVar3 = puVar3 + 2;
      } while (uVar7 != 0);
      if (uVar6 != uVar8) goto LAB_0010ab80;
    }
    if (param_3 < 0x149) {
      lVar5 = lVar4;
      if (2 < 0x148U - param_3) {
        uVar6 = (ulong)(0x148U - param_3) + 1;
        uVar8 = uVar6 & 0x1fffffffc;
        lVar5 = uVar8 + lVar4;
        puVar3 = (undefined8 *)(param_1 + lVar4 * 4);
        uVar7 = uVar8;
        do {
          uVar10 = puVar3[1];
          uVar9 = *puVar3;
          uVar7 = uVar7 - 4;
          uVar12 = puVar3[0x1b1];
          uVar11 = puVar3[0x1b0];
          puVar3[1] = CONCAT44((int)((long)uVar10 >> 0x30) * 0xf0c8 +
                               ((uint)(ushort)(CONCAT15((char)((ulong)uVar10 >> 0x28),
                                                        CONCAT14((char)((ulong)uVar10 >> 0x20),
                                                                 (uint)(ushort)uVar10)) >> 0x20) *
                                0x7864 >> 0xf),
                               ((int)uVar10 >> 0x10) * 0xf0c8 +
                               ((uint)(ushort)uVar10 * 0x7864 >> 0xf));
          *puVar3 = CONCAT44((int)((long)uVar9 >> 0x30) * 0xf0c8 +
                             ((uint)(ushort)(CONCAT15((char)((ulong)uVar9 >> 0x28),
                                                      CONCAT14((char)((ulong)uVar9 >> 0x20),
                                                               (uint)(ushort)uVar9)) >> 0x20) *
                              0x7864 >> 0xf),
                             ((int)uVar9 >> 0x10) * 0xf0c8 + ((uint)(ushort)uVar9 * 0x7864 >> 0xf));
          puVar3[0x1b1] =
               CONCAT44((int)((long)uVar12 >> 0x30) * 0xf0c8 +
                        ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                                 CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                          (uint)(ushort)uVar12)) >> 0x20) * 0x7864
                        >> 0xf),((int)uVar12 >> 0x10) * 0xf0c8 +
                                ((uint)(ushort)uVar12 * 0x7864 >> 0xf));
          puVar3[0x1b0] =
               CONCAT44((int)((long)uVar11 >> 0x30) * 0xf0c8 +
                        ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                                 CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                          (uint)(ushort)uVar11)) >> 0x20) * 0x7864
                        >> 0xf),((int)uVar11 >> 0x10) * 0xf0c8 +
                                ((uint)(ushort)uVar11 * 0x7864 >> 0xf));
          puVar3 = puVar3 + 2;
        } while (uVar7 != 0);
        if (uVar6 == uVar8) goto LAB_0010aca4;
      }
      do {
        puVar1 = (uint *)(param_1 + lVar5 * 4);
        lVar5 = lVar5 + 1;
        *puVar1 = ((int)*puVar1 >> 0x10) * 0xf0c8 + ((*puVar1 & 0xffff) * 0x7864 >> 0xf);
        puVar1[0x360] =
             ((int)puVar1[0x360] >> 0x10) * 0xf0c8 + ((puVar1[0x360] & 0xffff) * 0x7864 >> 0xf);
      } while ((int)lVar5 != 0x162);
    }
LAB_0010aca4:
    puVar3 = (undefined8 *)(param_1 + 0x588);
    lVar4 = 0x2c;
    do {
      uVar10 = puVar3[1];
      uVar9 = *puVar3;
      lVar4 = lVar4 + -4;
      uVar12 = puVar3[0x1b1];
      uVar11 = puVar3[0x1b0];
      puVar3[1] = CONCAT44((int)((long)uVar10 >> 0x30) * 0xf000 +
                           ((uint)(ushort)(CONCAT15((char)((ulong)uVar10 >> 0x28),
                                                    CONCAT14((char)((ulong)uVar10 >> 0x20),
                                                             (uint)(ushort)uVar10)) >> 0x20) *
                            0x7800 >> 0xf),
                           ((int)uVar10 >> 0x10) * 0xf000 + ((uint)(ushort)uVar10 * 0x7800 >> 0xf));
      *puVar3 = CONCAT44((int)((long)uVar9 >> 0x30) * 0xf000 +
                         ((uint)(ushort)(CONCAT15((char)((ulong)uVar9 >> 0x28),
                                                  CONCAT14((char)((ulong)uVar9 >> 0x20),
                                                           (uint)(ushort)uVar9)) >> 0x20) * 0x7800
                         >> 0xf),((int)uVar9 >> 0x10) * 0xf000 +
                                 ((uint)(ushort)uVar9 * 0x7800 >> 0xf));
      puVar3[0x1b1] =
           CONCAT44((int)((long)uVar12 >> 0x30) * 0xf000 +
                    ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                             CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                      (uint)(ushort)uVar12)) >> 0x20) * 0x7800 >>
                    0xf),((int)uVar12 >> 0x10) * 0xf000 + ((uint)(ushort)uVar12 * 0x7800 >> 0xf));
      puVar3[0x1b0] =
           CONCAT44((int)((long)uVar11 >> 0x30) * 0xf000 +
                    ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                             CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                      (uint)(ushort)uVar11)) >> 0x20) * 0x7800 >>
                    0xf),((int)uVar11 >> 0x10) * 0xf000 + ((uint)(ushort)uVar11 * 0x7800 >> 0xf));
      puVar3 = puVar3 + 2;
    } while (lVar4 != 0);
    *(uint *)(param_1 + 0x638) =
         ((int)*(uint *)(param_1 + 0x638) >> 0x10) * 0xf000 +
         ((*(uint *)(param_1 + 0x638) & 0xffff) * 0x7800 >> 0xf);
    *(uint *)(param_1 + 0x13b8) =
         ((int)*(uint *)(param_1 + 0x13b8) >> 0x10) * 0xf000 +
         ((*(uint *)(param_1 + 0x13b8) & 0xffff) * 0x7800 >> 0xf);
    lVar4 = 0x640;
    *(uint *)(param_1 + 0x63c) =
         ((int)*(uint *)(param_1 + 0x63c) >> 0x10) * 0xf000 +
         ((*(uint *)(param_1 + 0x63c) & 0xffff) * 0x7800 >> 0xf);
    *(uint *)(param_1 + 0x13bc) =
         ((int)*(uint *)(param_1 + 0x13bc) >> 0x10) * 0xf000 +
         ((*(uint *)(param_1 + 0x13bc) & 0xffff) * 0x7800 >> 0xf);
    do {
      puVar3 = (undefined8 *)(param_1 + lVar4);
      lVar4 = lVar4 + 0x10;
      uVar10 = puVar3[1];
      uVar9 = *puVar3;
      uVar12 = puVar3[0x1b1];
      uVar11 = puVar3[0x1b0];
      puVar3[1] = CONCAT44((int)((long)uVar10 >> 0x30) * 0xef38 +
                           ((uint)(ushort)(CONCAT15((char)((ulong)uVar10 >> 0x28),
                                                    CONCAT14((char)((ulong)uVar10 >> 0x20),
                                                             (uint)(ushort)uVar10)) >> 0x20) *
                            0x779c >> 0xf),
                           ((int)uVar10 >> 0x10) * 0xef38 + ((uint)(ushort)uVar10 * 0x779c >> 0xf));
      *puVar3 = CONCAT44((int)((long)uVar9 >> 0x30) * 0xef38 +
                         ((uint)(ushort)(CONCAT15((char)((ulong)uVar9 >> 0x28),
                                                  CONCAT14((char)((ulong)uVar9 >> 0x20),
                                                           (uint)(ushort)uVar9)) >> 0x20) * 0x779c
                         >> 0xf),((int)uVar9 >> 0x10) * 0xef38 +
                                 ((uint)(ushort)uVar9 * 0x779c >> 0xf));
      puVar3[0x1b1] =
           CONCAT44((int)((long)uVar12 >> 0x30) * 0xef38 +
                    ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                             CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                      (uint)(ushort)uVar12)) >> 0x20) * 0x779c >>
                    0xf),((int)uVar12 >> 0x10) * 0xef38 + ((uint)(ushort)uVar12 * 0x779c >> 0xf));
      puVar3[0x1b0] =
           CONCAT44((int)((long)uVar11 >> 0x30) * 0xef38 +
                    ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                             CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                      (uint)(ushort)uVar11)) >> 0x20) * 0x779c >>
                    0xf),((int)uVar11 >> 0x10) * 0xef38 + ((uint)(ushort)uVar11 * 0x779c >> 0xf));
    } while (lVar4 != 0xd80);
    return;
  }
  if (uVar6 < 4) {
LAB_0010a8fc:
    do {
      puVar1 = (uint *)(param_1 + lVar5 * 4);
      lVar5 = lVar5 + 1;
      *puVar1 = ((int)*puVar1 >> 0x10) * 0xf190 + ((*puVar1 & 0xffff) * 0x78c8 >> 0xf);
      puVar1[0x360] =
           ((int)puVar1[0x360] >> 0x10) * 0xf190 + ((puVar1[0x360] & 0xffff) * 0x78c8 >> 0xf);
    } while (lVar5 < lVar4);
  }
  else {
    uVar8 = uVar6 & 0xfffffffffffffffc;
    puVar3 = (undefined8 *)(param_1 + lVar5 * 4);
    lVar5 = uVar8 + lVar5;
    uVar7 = uVar8;
    do {
      uVar10 = puVar3[1];
      uVar9 = *puVar3;
      uVar7 = uVar7 - 4;
      uVar12 = puVar3[0x1b1];
      uVar11 = puVar3[0x1b0];
      puVar3[1] = CONCAT44((int)((long)uVar10 >> 0x30) * 0xf190 +
                           ((uint)(ushort)(CONCAT15((char)((ulong)uVar10 >> 0x28),
                                                    CONCAT14((char)((ulong)uVar10 >> 0x20),
                                                             (uint)(ushort)uVar10)) >> 0x20) *
                            0x78c8 >> 0xf),
                           ((int)uVar10 >> 0x10) * 0xf190 + ((uint)(ushort)uVar10 * 0x78c8 >> 0xf));
      *puVar3 = CONCAT44((int)((long)uVar9 >> 0x30) * 0xf190 +
                         ((uint)(ushort)(CONCAT15((char)((ulong)uVar9 >> 0x28),
                                                  CONCAT14((char)((ulong)uVar9 >> 0x20),
                                                           (uint)(ushort)uVar9)) >> 0x20) * 0x78c8
                         >> 0xf),((int)uVar9 >> 0x10) * 0xf190 +
                                 ((uint)(ushort)uVar9 * 0x78c8 >> 0xf));
      puVar3[0x1b1] =
           CONCAT44((int)((long)uVar12 >> 0x30) * 0xf190 +
                    ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                             CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                      (uint)(ushort)uVar12)) >> 0x20) * 0x78c8 >>
                    0xf),((int)uVar12 >> 0x10) * 0xf190 + ((uint)(ushort)uVar12 * 0x78c8 >> 0xf));
      puVar3[0x1b0] =
           CONCAT44((int)((long)uVar11 >> 0x30) * 0xf190 +
                    ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                             CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                      (uint)(ushort)uVar11)) >> 0x20) * 0x78c8 >>
                    0xf),((int)uVar11 >> 0x10) * 0xf190 + ((uint)(ushort)uVar11 * 0x78c8 >> 0xf));
      puVar3 = puVar3 + 2;
    } while (uVar7 != 0);
    if (uVar6 != uVar8) goto LAB_0010a8fc;
  }
  if (param_3 < 0x145) {
    lVar5 = lVar4;
    if (2 < 0x144U - param_3) {
      uVar6 = (ulong)(0x144U - param_3) + 1;
      uVar8 = uVar6 & 0x1fffffffc;
      lVar5 = uVar8 + lVar4;
      puVar3 = (undefined8 *)(param_1 + lVar4 * 4);
      uVar7 = uVar8;
      do {
        uVar10 = puVar3[1];
        uVar9 = *puVar3;
        uVar7 = uVar7 - 4;
        uVar12 = puVar3[0x1b1];
        uVar11 = puVar3[0x1b0];
        puVar3[1] = CONCAT44((int)((long)uVar10 >> 0x30) * 0xf03c +
                             ((uint)(ushort)(CONCAT15((char)((ulong)uVar10 >> 0x28),
                                                      CONCAT14((char)((ulong)uVar10 >> 0x20),
                                                               (uint)(ushort)uVar10)) >> 0x20) *
                              0x781e >> 0xf),
                             ((int)uVar10 >> 0x10) * 0xf03c + ((uint)(ushort)uVar10 * 0x781e >> 0xf)
                            );
        *puVar3 = CONCAT44((int)((long)uVar9 >> 0x30) * 0xf03c +
                           ((uint)(ushort)(CONCAT15((char)((ulong)uVar9 >> 0x28),
                                                    CONCAT14((char)((ulong)uVar9 >> 0x20),
                                                             (uint)(ushort)uVar9)) >> 0x20) * 0x781e
                           >> 0xf),((int)uVar9 >> 0x10) * 0xf03c +
                                   ((uint)(ushort)uVar9 * 0x781e >> 0xf));
        puVar3[0x1b1] =
             CONCAT44((int)((long)uVar12 >> 0x30) * 0xf03c +
                      ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                               CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                        (uint)(ushort)uVar12)) >> 0x20) * 0x781e >>
                      0xf),((int)uVar12 >> 0x10) * 0xf03c + ((uint)(ushort)uVar12 * 0x781e >> 0xf));
        puVar3[0x1b0] =
             CONCAT44((int)((long)uVar11 >> 0x30) * 0xf03c +
                      ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                               CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                        (uint)(ushort)uVar11)) >> 0x20) * 0x781e >>
                      0xf),((int)uVar11 >> 0x10) * 0xf03c + ((uint)(ushort)uVar11 * 0x781e >> 0xf));
        puVar3 = puVar3 + 2;
      } while (uVar7 != 0);
      if (uVar6 == uVar8) goto LAB_0010aa20;
    }
    do {
      puVar1 = (uint *)(param_1 + lVar5 * 4);
      lVar5 = lVar5 + 1;
      *puVar1 = ((int)*puVar1 >> 0x10) * 0xf03c + ((*puVar1 & 0xffff) * 0x781e >> 0xf);
      puVar1[0x360] =
           ((int)puVar1[0x360] >> 0x10) * 0xf03c + ((puVar1[0x360] & 0xffff) * 0x781e >> 0xf);
    } while ((int)lVar5 != 0x15e);
  }
LAB_0010aa20:
  puVar3 = (undefined8 *)(param_1 + 0x578);
  lVar4 = 0x200;
  do {
    uVar10 = puVar3[1];
    uVar9 = *puVar3;
    lVar4 = lVar4 + -4;
    uVar12 = puVar3[0x1b1];
    uVar11 = puVar3[0x1b0];
    puVar3[1] = CONCAT44((int)((long)uVar10 >> 0x30) * 0xef38 +
                         ((uint)(ushort)(CONCAT15((char)((ulong)uVar10 >> 0x28),
                                                  CONCAT14((char)((ulong)uVar10 >> 0x20),
                                                           (uint)(ushort)uVar10)) >> 0x20) * 0x779c
                         >> 0xf),((int)uVar10 >> 0x10) * 0xef38 +
                                 ((uint)(ushort)uVar10 * 0x779c >> 0xf));
    *puVar3 = CONCAT44((int)((long)uVar9 >> 0x30) * 0xef38 +
                       ((uint)(ushort)(CONCAT15((char)((ulong)uVar9 >> 0x28),
                                                CONCAT14((char)((ulong)uVar9 >> 0x20),
                                                         (uint)(ushort)uVar9)) >> 0x20) * 0x779c >>
                       0xf),((int)uVar9 >> 0x10) * 0xef38 + ((uint)(ushort)uVar9 * 0x779c >> 0xf));
    puVar3[0x1b1] =
         CONCAT44((int)((long)uVar12 >> 0x30) * 0xef38 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                           CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                    (uint)(ushort)uVar12)) >> 0x20) * 0x779c >> 0xf)
                  ,((int)uVar12 >> 0x10) * 0xef38 + ((uint)(ushort)uVar12 * 0x779c >> 0xf));
    puVar3[0x1b0] =
         CONCAT44((int)((long)uVar11 >> 0x30) * 0xef38 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                           CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                    (uint)(ushort)uVar11)) >> 0x20) * 0x779c >> 0xf)
                  ,((int)uVar11 >> 0x10) * 0xef38 + ((uint)(ushort)uVar11 * 0x779c >> 0xf));
    puVar3 = puVar3 + 2;
  } while (lVar4 != 0);
  *(uint *)(param_1 + 0xd78) =
       ((int)*(uint *)(param_1 + 0xd78) >> 0x10) * 0xef38 +
       ((*(uint *)(param_1 + 0xd78) & 0xffff) * 0x779c >> 0xf);
  *(uint *)(param_1 + 0x1af8) =
       ((int)*(uint *)(param_1 + 0x1af8) >> 0x10) * 0xef38 +
       ((*(uint *)(param_1 + 0x1af8) & 0xffff) * 0x779c >> 0xf);
  *(uint *)(param_1 + 0xd7c) =
       ((int)*(uint *)(param_1 + 0xd7c) >> 0x10) * 0xef38 +
       ((*(uint *)(param_1 + 0xd7c) & 0xffff) * 0x779c >> 0xf);
  *(uint *)(param_1 + 0x1afc) =
       ((int)*(uint *)(param_1 + 0x1afc) >> 0x10) * 0xef38 +
       ((*(uint *)(param_1 + 0x1afc) & 0xffff) * 0x779c >> 0xf);
  return;
}


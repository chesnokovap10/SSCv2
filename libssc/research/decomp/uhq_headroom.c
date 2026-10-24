/* uhq_headroom @ 0010c828 size 2056 */

void uhq_headroom(long param_1,int param_2,int param_3,long param_4)

{
  int iVar1;
  uint *puVar2;
  uint uVar3;
  long lVar4;
  undefined8 *puVar5;
  long lVar6;
  long lVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  
  param_3 = *(short *)(param_4 + 0x24) * param_3;
  iVar1 = param_3 + 0x19;
  lVar7 = (long)param_3;
  lVar6 = (long)iVar1;
  lVar4 = lVar6;
  if (lVar6 < lVar7 + 1) {
    lVar4 = lVar7 + 1;
  }
  uVar8 = lVar4 - lVar7;
  if (269999 < param_2) {
    if (uVar8 < 4) {
LAB_0010cb68:
      do {
        puVar2 = (uint *)(param_1 + lVar7 * 4);
        lVar7 = lVar7 + 1;
        *puVar2 = ((int)*puVar2 >> 0x10) * 0xf190 + ((*puVar2 & 0xffff) * 0x78c8 >> 0xf);
        puVar2[0x360] =
             ((int)puVar2[0x360] >> 0x10) * 0xf190 + ((puVar2[0x360] & 0xffff) * 0x78c8 >> 0xf);
      } while (lVar7 < lVar6);
    }
    else {
      uVar9 = uVar8 & 0xfffffffffffffffc;
      puVar5 = (undefined8 *)(param_1 + lVar7 * 4);
      lVar7 = uVar9 + lVar7;
      uVar10 = uVar9;
      do {
        uVar12 = puVar5[1];
        uVar11 = *puVar5;
        uVar14 = puVar5[0x1b1];
        uVar13 = puVar5[0x1b0];
        uVar10 = uVar10 - 4;
        puVar5[1] = CONCAT44((int)((long)uVar12 >> 0x30) * 0xf190 +
                             ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                                      CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                               (uint)(ushort)uVar12)) >> 0x20) *
                              0x78c8 >> 0xf),
                             ((int)uVar12 >> 0x10) * 0xf190 + ((uint)(ushort)uVar12 * 0x78c8 >> 0xf)
                            );
        *puVar5 = CONCAT44((int)((long)uVar11 >> 0x30) * 0xf190 +
                           ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                                    CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                             (uint)(ushort)uVar11)) >> 0x20) *
                            0x78c8 >> 0xf),
                           ((int)uVar11 >> 0x10) * 0xf190 + ((uint)(ushort)uVar11 * 0x78c8 >> 0xf));
        puVar5[0x1b1] =
             CONCAT44((int)((long)uVar14 >> 0x30) * 0xf190 +
                      ((uint)(ushort)(CONCAT15((char)((ulong)uVar14 >> 0x28),
                                               CONCAT14((char)((ulong)uVar14 >> 0x20),
                                                        (uint)(ushort)uVar14)) >> 0x20) * 0x78c8 >>
                      0xf),((int)uVar14 >> 0x10) * 0xf190 + ((uint)(ushort)uVar14 * 0x78c8 >> 0xf));
        puVar5[0x1b0] =
             CONCAT44((int)((long)uVar13 >> 0x30) * 0xf190 +
                      ((uint)(ushort)(CONCAT15((char)((ulong)uVar13 >> 0x28),
                                               CONCAT14((char)((ulong)uVar13 >> 0x20),
                                                        (uint)(ushort)uVar13)) >> 0x20) * 0x78c8 >>
                      0xf),((int)uVar13 >> 0x10) * 0xf190 + ((uint)(ushort)uVar13 * 0x78c8 >> 0xf));
        puVar5 = puVar5 + 2;
      } while (uVar10 != 0);
      if (uVar8 != uVar9) goto LAB_0010cb68;
    }
    if (iVar1 < 0x162) {
      uVar8 = (ulong)(-param_3 + 0x148) + 1;
      if (3 < uVar8) {
        uVar3 = -param_3 + 0x149U & 3;
        lVar7 = uVar8 - uVar3;
        puVar5 = (undefined8 *)(param_1 + lVar6 * 4);
        lVar6 = lVar7 + lVar6;
        do {
          uVar12 = puVar5[1];
          uVar11 = *puVar5;
          uVar14 = puVar5[0x1b1];
          uVar13 = puVar5[0x1b0];
          lVar7 = lVar7 + -4;
          puVar5[1] = CONCAT44((int)((long)uVar12 >> 0x30) * 0xf0c8 +
                               ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                                        CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                                 (uint)(ushort)uVar12)) >> 0x20) *
                                0x7864 >> 0xf),
                               ((int)uVar12 >> 0x10) * 0xf0c8 +
                               ((uint)(ushort)uVar12 * 0x7864 >> 0xf));
          *puVar5 = CONCAT44((int)((long)uVar11 >> 0x30) * 0xf0c8 +
                             ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                                      CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                               (uint)(ushort)uVar11)) >> 0x20) *
                              0x7864 >> 0xf),
                             ((int)uVar11 >> 0x10) * 0xf0c8 + ((uint)(ushort)uVar11 * 0x7864 >> 0xf)
                            );
          puVar5[0x1b1] =
               CONCAT44((int)((long)uVar14 >> 0x30) * 0xf0c8 +
                        ((uint)(ushort)(CONCAT15((char)((ulong)uVar14 >> 0x28),
                                                 CONCAT14((char)((ulong)uVar14 >> 0x20),
                                                          (uint)(ushort)uVar14)) >> 0x20) * 0x7864
                        >> 0xf),((int)uVar14 >> 0x10) * 0xf0c8 +
                                ((uint)(ushort)uVar14 * 0x7864 >> 0xf));
          puVar5[0x1b0] =
               CONCAT44((int)((long)uVar13 >> 0x30) * 0xf0c8 +
                        ((uint)(ushort)(CONCAT15((char)((ulong)uVar13 >> 0x28),
                                                 CONCAT14((char)((ulong)uVar13 >> 0x20),
                                                          (uint)(ushort)uVar13)) >> 0x20) * 0x7864
                        >> 0xf),((int)uVar13 >> 0x10) * 0xf0c8 +
                                ((uint)(ushort)uVar13 * 0x7864 >> 0xf));
          puVar5 = puVar5 + 2;
        } while (lVar7 != 0);
        if (uVar3 == 0) goto LAB_0010cc8c;
      }
      do {
        puVar2 = (uint *)(param_1 + lVar6 * 4);
        lVar6 = lVar6 + 1;
        *puVar2 = ((int)*puVar2 >> 0x10) * 0xf0c8 + ((*puVar2 & 0xffff) * 0x7864 >> 0xf);
        puVar2[0x360] =
             ((int)puVar2[0x360] >> 0x10) * 0xf0c8 + ((puVar2[0x360] & 0xffff) * 0x7864 >> 0xf);
      } while ((int)lVar6 != 0x162);
    }
LAB_0010cc8c:
    uVar12 = *(undefined8 *)(param_1 + 0x590);
    uVar11 = *(undefined8 *)(param_1 + 0x588);
    *(ulong *)(param_1 + 0x590) =
         CONCAT44((int)((long)uVar12 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                           CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                    (uint)(ushort)uVar12)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar12 >> 0x10) * 0xf000 + ((uint)(ushort)uVar12 * 0x7800 >> 0xf));
    *(undefined8 *)(param_1 + 0x588) =
         CONCAT44((int)((long)uVar11 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                           CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                    (uint)(ushort)uVar11)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar11 >> 0x10) * 0xf000 + ((uint)(ushort)uVar11 * 0x7800 >> 0xf));
    uVar12 = *(undefined8 *)(param_1 + 0x1310);
    uVar11 = *(undefined8 *)(param_1 + 0x1308);
    *(ulong *)(param_1 + 0x1310) =
         CONCAT44((int)((long)uVar12 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                           CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                    (uint)(ushort)uVar12)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar12 >> 0x10) * 0xf000 + ((uint)(ushort)uVar12 * 0x7800 >> 0xf));
    *(ulong *)(param_1 + 0x1308) =
         CONCAT44((int)((long)uVar11 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                           CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                    (uint)(ushort)uVar11)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar11 >> 0x10) * 0xf000 + ((uint)(ushort)uVar11 * 0x7800 >> 0xf));
    uVar12 = *(undefined8 *)(param_1 + 0x5a0);
    uVar11 = *(undefined8 *)(param_1 + 0x598);
    *(ulong *)(param_1 + 0x5a0) =
         CONCAT44((int)((long)uVar12 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                           CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                    (uint)(ushort)uVar12)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar12 >> 0x10) * 0xf000 + ((uint)(ushort)uVar12 * 0x7800 >> 0xf));
    *(undefined8 *)(param_1 + 0x598) =
         CONCAT44((int)((long)uVar11 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                           CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                    (uint)(ushort)uVar11)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar11 >> 0x10) * 0xf000 + ((uint)(ushort)uVar11 * 0x7800 >> 0xf));
    uVar12 = *(undefined8 *)(param_1 + 0x1320);
    uVar11 = *(undefined8 *)(param_1 + 0x1318);
    *(ulong *)(param_1 + 0x1320) =
         CONCAT44((int)((long)uVar12 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                           CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                    (uint)(ushort)uVar12)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar12 >> 0x10) * 0xf000 + ((uint)(ushort)uVar12 * 0x7800 >> 0xf));
    *(ulong *)(param_1 + 0x1318) =
         CONCAT44((int)((long)uVar11 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                           CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                    (uint)(ushort)uVar11)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar11 >> 0x10) * 0xf000 + ((uint)(ushort)uVar11 * 0x7800 >> 0xf));
    uVar12 = *(undefined8 *)(param_1 + 0x5b0);
    uVar11 = *(undefined8 *)(param_1 + 0x5a8);
    *(ulong *)(param_1 + 0x5b0) =
         CONCAT44((int)((long)uVar12 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                           CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                    (uint)(ushort)uVar12)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar12 >> 0x10) * 0xf000 + ((uint)(ushort)uVar12 * 0x7800 >> 0xf));
    *(undefined8 *)(param_1 + 0x5a8) =
         CONCAT44((int)((long)uVar11 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                           CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                    (uint)(ushort)uVar11)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar11 >> 0x10) * 0xf000 + ((uint)(ushort)uVar11 * 0x7800 >> 0xf));
    uVar12 = *(undefined8 *)(param_1 + 0x1330);
    uVar11 = *(undefined8 *)(param_1 + 0x1328);
    *(ulong *)(param_1 + 0x1330) =
         CONCAT44((int)((long)uVar12 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                           CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                    (uint)(ushort)uVar12)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar12 >> 0x10) * 0xf000 + ((uint)(ushort)uVar12 * 0x7800 >> 0xf));
    *(ulong *)(param_1 + 0x1328) =
         CONCAT44((int)((long)uVar11 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                           CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                    (uint)(ushort)uVar11)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar11 >> 0x10) * 0xf000 + ((uint)(ushort)uVar11 * 0x7800 >> 0xf));
    uVar12 = *(undefined8 *)(param_1 + 0x5c0);
    uVar11 = *(undefined8 *)(param_1 + 0x5b8);
    *(ulong *)(param_1 + 0x5c0) =
         CONCAT44((int)((long)uVar12 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                           CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                    (uint)(ushort)uVar12)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar12 >> 0x10) * 0xf000 + ((uint)(ushort)uVar12 * 0x7800 >> 0xf));
    *(undefined8 *)(param_1 + 0x5b8) =
         CONCAT44((int)((long)uVar11 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                           CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                    (uint)(ushort)uVar11)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar11 >> 0x10) * 0xf000 + ((uint)(ushort)uVar11 * 0x7800 >> 0xf));
    uVar12 = *(undefined8 *)(param_1 + 0x1340);
    uVar11 = *(undefined8 *)(param_1 + 0x1338);
    *(ulong *)(param_1 + 0x1340) =
         CONCAT44((int)((long)uVar12 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                           CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                    (uint)(ushort)uVar12)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar12 >> 0x10) * 0xf000 + ((uint)(ushort)uVar12 * 0x7800 >> 0xf));
    *(ulong *)(param_1 + 0x1338) =
         CONCAT44((int)((long)uVar11 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                           CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                    (uint)(ushort)uVar11)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar11 >> 0x10) * 0xf000 + ((uint)(ushort)uVar11 * 0x7800 >> 0xf));
    uVar12 = *(undefined8 *)(param_1 + 0x5d0);
    uVar11 = *(undefined8 *)(param_1 + 0x5c8);
    *(ulong *)(param_1 + 0x5d0) =
         CONCAT44((int)((long)uVar12 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                           CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                    (uint)(ushort)uVar12)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar12 >> 0x10) * 0xf000 + ((uint)(ushort)uVar12 * 0x7800 >> 0xf));
    *(undefined8 *)(param_1 + 0x5c8) =
         CONCAT44((int)((long)uVar11 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                           CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                    (uint)(ushort)uVar11)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar11 >> 0x10) * 0xf000 + ((uint)(ushort)uVar11 * 0x7800 >> 0xf));
    uVar12 = *(undefined8 *)(param_1 + 0x1350);
    uVar11 = *(undefined8 *)(param_1 + 0x1348);
    *(ulong *)(param_1 + 0x1350) =
         CONCAT44((int)((long)uVar12 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                           CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                    (uint)(ushort)uVar12)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar12 >> 0x10) * 0xf000 + ((uint)(ushort)uVar12 * 0x7800 >> 0xf));
    *(ulong *)(param_1 + 0x1348) =
         CONCAT44((int)((long)uVar11 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                           CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                    (uint)(ushort)uVar11)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar11 >> 0x10) * 0xf000 + ((uint)(ushort)uVar11 * 0x7800 >> 0xf));
    uVar12 = *(undefined8 *)(param_1 + 0x5e0);
    uVar11 = *(undefined8 *)(param_1 + 0x5d8);
    *(ulong *)(param_1 + 0x5e0) =
         CONCAT44((int)((long)uVar12 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                           CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                    (uint)(ushort)uVar12)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar12 >> 0x10) * 0xf000 + ((uint)(ushort)uVar12 * 0x7800 >> 0xf));
    *(undefined8 *)(param_1 + 0x5d8) =
         CONCAT44((int)((long)uVar11 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                           CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                    (uint)(ushort)uVar11)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar11 >> 0x10) * 0xf000 + ((uint)(ushort)uVar11 * 0x7800 >> 0xf));
    uVar12 = *(undefined8 *)(param_1 + 0x1360);
    uVar11 = *(undefined8 *)(param_1 + 0x1358);
    *(ulong *)(param_1 + 0x1360) =
         CONCAT44((int)((long)uVar12 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                           CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                    (uint)(ushort)uVar12)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar12 >> 0x10) * 0xf000 + ((uint)(ushort)uVar12 * 0x7800 >> 0xf));
    *(ulong *)(param_1 + 0x1358) =
         CONCAT44((int)((long)uVar11 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                           CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                    (uint)(ushort)uVar11)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar11 >> 0x10) * 0xf000 + ((uint)(ushort)uVar11 * 0x7800 >> 0xf));
    uVar12 = *(undefined8 *)(param_1 + 0x5f0);
    uVar11 = *(undefined8 *)(param_1 + 0x5e8);
    *(ulong *)(param_1 + 0x5f0) =
         CONCAT44((int)((long)uVar12 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                           CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                    (uint)(ushort)uVar12)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar12 >> 0x10) * 0xf000 + ((uint)(ushort)uVar12 * 0x7800 >> 0xf));
    *(undefined8 *)(param_1 + 0x5e8) =
         CONCAT44((int)((long)uVar11 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                           CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                    (uint)(ushort)uVar11)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar11 >> 0x10) * 0xf000 + ((uint)(ushort)uVar11 * 0x7800 >> 0xf));
    uVar12 = *(undefined8 *)(param_1 + 0x1370);
    uVar11 = *(undefined8 *)(param_1 + 0x1368);
    *(ulong *)(param_1 + 0x1370) =
         CONCAT44((int)((long)uVar12 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                           CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                    (uint)(ushort)uVar12)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar12 >> 0x10) * 0xf000 + ((uint)(ushort)uVar12 * 0x7800 >> 0xf));
    *(ulong *)(param_1 + 0x1368) =
         CONCAT44((int)((long)uVar11 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                           CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                    (uint)(ushort)uVar11)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar11 >> 0x10) * 0xf000 + ((uint)(ushort)uVar11 * 0x7800 >> 0xf));
    uVar12 = *(undefined8 *)(param_1 + 0x600);
    uVar11 = *(undefined8 *)(param_1 + 0x5f8);
    *(ulong *)(param_1 + 0x600) =
         CONCAT44((int)((long)uVar12 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                           CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                    (uint)(ushort)uVar12)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar12 >> 0x10) * 0xf000 + ((uint)(ushort)uVar12 * 0x7800 >> 0xf));
    *(undefined8 *)(param_1 + 0x5f8) =
         CONCAT44((int)((long)uVar11 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                           CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                    (uint)(ushort)uVar11)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar11 >> 0x10) * 0xf000 + ((uint)(ushort)uVar11 * 0x7800 >> 0xf));
    uVar12 = *(undefined8 *)(param_1 + 0x1380);
    uVar11 = *(undefined8 *)(param_1 + 0x1378);
    *(ulong *)(param_1 + 0x1380) =
         CONCAT44((int)((long)uVar12 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                           CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                    (uint)(ushort)uVar12)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar12 >> 0x10) * 0xf000 + ((uint)(ushort)uVar12 * 0x7800 >> 0xf));
    *(ulong *)(param_1 + 0x1378) =
         CONCAT44((int)((long)uVar11 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                           CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                    (uint)(ushort)uVar11)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar11 >> 0x10) * 0xf000 + ((uint)(ushort)uVar11 * 0x7800 >> 0xf));
    uVar12 = *(undefined8 *)(param_1 + 0x610);
    uVar11 = *(undefined8 *)(param_1 + 0x608);
    *(ulong *)(param_1 + 0x610) =
         CONCAT44((int)((long)uVar12 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                           CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                    (uint)(ushort)uVar12)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar12 >> 0x10) * 0xf000 + ((uint)(ushort)uVar12 * 0x7800 >> 0xf));
    *(undefined8 *)(param_1 + 0x608) =
         CONCAT44((int)((long)uVar11 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                           CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                    (uint)(ushort)uVar11)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar11 >> 0x10) * 0xf000 + ((uint)(ushort)uVar11 * 0x7800 >> 0xf));
    uVar12 = *(undefined8 *)(param_1 + 0x1390);
    uVar11 = *(undefined8 *)(param_1 + 5000);
    *(ulong *)(param_1 + 0x1390) =
         CONCAT44((int)((long)uVar12 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                           CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                    (uint)(ushort)uVar12)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar12 >> 0x10) * 0xf000 + ((uint)(ushort)uVar12 * 0x7800 >> 0xf));
    *(ulong *)(param_1 + 5000) =
         CONCAT44((int)((long)uVar11 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                           CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                    (uint)(ushort)uVar11)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar11 >> 0x10) * 0xf000 + ((uint)(ushort)uVar11 * 0x7800 >> 0xf));
    uVar12 = *(undefined8 *)(param_1 + 0x620);
    uVar11 = *(undefined8 *)(param_1 + 0x618);
    *(ulong *)(param_1 + 0x620) =
         CONCAT44((int)((long)uVar12 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                           CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                    (uint)(ushort)uVar12)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar12 >> 0x10) * 0xf000 + ((uint)(ushort)uVar12 * 0x7800 >> 0xf));
    *(undefined8 *)(param_1 + 0x618) =
         CONCAT44((int)((long)uVar11 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                           CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                    (uint)(ushort)uVar11)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar11 >> 0x10) * 0xf000 + ((uint)(ushort)uVar11 * 0x7800 >> 0xf));
    uVar12 = *(undefined8 *)(param_1 + 0x13a0);
    uVar11 = *(undefined8 *)(param_1 + 0x1398);
    *(ulong *)(param_1 + 0x13a0) =
         CONCAT44((int)((long)uVar12 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                           CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                    (uint)(ushort)uVar12)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar12 >> 0x10) * 0xf000 + ((uint)(ushort)uVar12 * 0x7800 >> 0xf));
    *(ulong *)(param_1 + 0x1398) =
         CONCAT44((int)((long)uVar11 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                           CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                    (uint)(ushort)uVar11)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar11 >> 0x10) * 0xf000 + ((uint)(ushort)uVar11 * 0x7800 >> 0xf));
    uVar12 = *(undefined8 *)(param_1 + 0x630);
    uVar11 = *(undefined8 *)(param_1 + 0x628);
    *(ulong *)(param_1 + 0x630) =
         CONCAT44((int)((long)uVar12 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                           CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                    (uint)(ushort)uVar12)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar12 >> 0x10) * 0xf000 + ((uint)(ushort)uVar12 * 0x7800 >> 0xf));
    *(undefined8 *)(param_1 + 0x628) =
         CONCAT44((int)((long)uVar11 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                           CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                    (uint)(ushort)uVar11)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar11 >> 0x10) * 0xf000 + ((uint)(ushort)uVar11 * 0x7800 >> 0xf));
    uVar12 = *(undefined8 *)(param_1 + 0x13b0);
    uVar11 = *(undefined8 *)(param_1 + 0x13a8);
    *(ulong *)(param_1 + 0x13b0) =
         CONCAT44((int)((long)uVar12 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                           CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                    (uint)(ushort)uVar12)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar12 >> 0x10) * 0xf000 + ((uint)(ushort)uVar12 * 0x7800 >> 0xf));
    *(ulong *)(param_1 + 0x13a8) =
         CONCAT44((int)((long)uVar11 >> 0x30) * 0xf000 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                           CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                    (uint)(ushort)uVar11)) >> 0x20) * 0x7800 >> 0xf)
                  ,((int)uVar11 >> 0x10) * 0xf000 + ((uint)(ushort)uVar11 * 0x7800 >> 0xf));
    *(uint *)(param_1 + 0x638) =
         ((int)*(uint *)(param_1 + 0x638) >> 0x10) * 0xf000 +
         ((*(uint *)(param_1 + 0x638) & 0xffff) * 0x7800 >> 0xf);
    lVar7 = 0x640;
    *(uint *)(param_1 + 0x13b8) =
         ((int)*(uint *)(param_1 + 0x13b8) >> 0x10) * 0xf000 +
         ((*(uint *)(param_1 + 0x13b8) & 0xffff) * 0x7800 >> 0xf);
    *(uint *)(param_1 + 0x63c) =
         ((int)*(uint *)(param_1 + 0x63c) >> 0x10) * 0xf000 +
         ((*(uint *)(param_1 + 0x63c) & 0xffff) * 0x7800 >> 0xf);
    *(uint *)(param_1 + 0x13bc) =
         ((int)*(uint *)(param_1 + 0x13bc) >> 0x10) * 0xf000 +
         ((*(uint *)(param_1 + 0x13bc) & 0xffff) * 0x7800 >> 0xf);
    do {
      puVar5 = (undefined8 *)(param_1 + lVar7);
      uVar12 = puVar5[1];
      uVar11 = *puVar5;
      uVar14 = puVar5[0x1b1];
      uVar13 = puVar5[0x1b0];
      lVar7 = lVar7 + 0x10;
      puVar5[1] = CONCAT44((int)((long)uVar12 >> 0x30) * 0xef38 +
                           ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                                    CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                             (uint)(ushort)uVar12)) >> 0x20) *
                            0x779c >> 0xf),
                           ((int)uVar12 >> 0x10) * 0xef38 + ((uint)(ushort)uVar12 * 0x779c >> 0xf));
      *puVar5 = CONCAT44((int)((long)uVar11 >> 0x30) * 0xef38 +
                         ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                                  CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                           (uint)(ushort)uVar11)) >> 0x20) * 0x779c
                         >> 0xf),((int)uVar11 >> 0x10) * 0xef38 +
                                 ((uint)(ushort)uVar11 * 0x779c >> 0xf));
      puVar5[0x1b1] =
           CONCAT44((int)((long)uVar14 >> 0x30) * 0xef38 +
                    ((uint)(ushort)(CONCAT15((char)((ulong)uVar14 >> 0x28),
                                             CONCAT14((char)((ulong)uVar14 >> 0x20),
                                                      (uint)(ushort)uVar14)) >> 0x20) * 0x779c >>
                    0xf),((int)uVar14 >> 0x10) * 0xef38 + ((uint)(ushort)uVar14 * 0x779c >> 0xf));
      puVar5[0x1b0] =
           CONCAT44((int)((long)uVar13 >> 0x30) * 0xef38 +
                    ((uint)(ushort)(CONCAT15((char)((ulong)uVar13 >> 0x28),
                                             CONCAT14((char)((ulong)uVar13 >> 0x20),
                                                      (uint)(ushort)uVar13)) >> 0x20) * 0x779c >>
                    0xf),((int)uVar13 >> 0x10) * 0xef38 + ((uint)(ushort)uVar13 * 0x779c >> 0xf));
    } while (lVar7 != 0xd80);
    return;
  }
  if (uVar8 < 4) {
LAB_0010c8e4:
    do {
      puVar2 = (uint *)(param_1 + lVar7 * 4);
      lVar7 = lVar7 + 1;
      *puVar2 = ((int)*puVar2 >> 0x10) * 0xf190 + ((*puVar2 & 0xffff) * 0x78c8 >> 0xf);
      puVar2[0x360] =
           ((int)puVar2[0x360] >> 0x10) * 0xf190 + ((puVar2[0x360] & 0xffff) * 0x78c8 >> 0xf);
    } while (lVar7 < lVar6);
  }
  else {
    uVar9 = uVar8 & 0xfffffffffffffffc;
    puVar5 = (undefined8 *)(param_1 + lVar7 * 4);
    lVar7 = uVar9 + lVar7;
    uVar10 = uVar9;
    do {
      uVar12 = puVar5[1];
      uVar11 = *puVar5;
      uVar14 = puVar5[0x1b1];
      uVar13 = puVar5[0x1b0];
      uVar10 = uVar10 - 4;
      puVar5[1] = CONCAT44((int)((long)uVar12 >> 0x30) * 0xf190 +
                           ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                                    CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                             (uint)(ushort)uVar12)) >> 0x20) *
                            0x78c8 >> 0xf),
                           ((int)uVar12 >> 0x10) * 0xf190 + ((uint)(ushort)uVar12 * 0x78c8 >> 0xf));
      *puVar5 = CONCAT44((int)((long)uVar11 >> 0x30) * 0xf190 +
                         ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                                  CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                           (uint)(ushort)uVar11)) >> 0x20) * 0x78c8
                         >> 0xf),((int)uVar11 >> 0x10) * 0xf190 +
                                 ((uint)(ushort)uVar11 * 0x78c8 >> 0xf));
      puVar5[0x1b1] =
           CONCAT44((int)((long)uVar14 >> 0x30) * 0xf190 +
                    ((uint)(ushort)(CONCAT15((char)((ulong)uVar14 >> 0x28),
                                             CONCAT14((char)((ulong)uVar14 >> 0x20),
                                                      (uint)(ushort)uVar14)) >> 0x20) * 0x78c8 >>
                    0xf),((int)uVar14 >> 0x10) * 0xf190 + ((uint)(ushort)uVar14 * 0x78c8 >> 0xf));
      puVar5[0x1b0] =
           CONCAT44((int)((long)uVar13 >> 0x30) * 0xf190 +
                    ((uint)(ushort)(CONCAT15((char)((ulong)uVar13 >> 0x28),
                                             CONCAT14((char)((ulong)uVar13 >> 0x20),
                                                      (uint)(ushort)uVar13)) >> 0x20) * 0x78c8 >>
                    0xf),((int)uVar13 >> 0x10) * 0xf190 + ((uint)(ushort)uVar13 * 0x78c8 >> 0xf));
      puVar5 = puVar5 + 2;
    } while (uVar10 != 0);
    if (uVar8 != uVar9) goto LAB_0010c8e4;
  }
  if (iVar1 < 0x15e) {
    uVar8 = (ulong)(-param_3 + 0x144) + 1;
    if (3 < uVar8) {
      uVar3 = -param_3 + 0x145U & 3;
      lVar7 = uVar8 - uVar3;
      puVar5 = (undefined8 *)(param_1 + lVar6 * 4);
      lVar6 = lVar7 + lVar6;
      do {
        uVar12 = puVar5[1];
        uVar11 = *puVar5;
        uVar14 = puVar5[0x1b1];
        uVar13 = puVar5[0x1b0];
        lVar7 = lVar7 + -4;
        puVar5[1] = CONCAT44((int)((long)uVar12 >> 0x30) * 0xf03c +
                             ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                                      CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                               (uint)(ushort)uVar12)) >> 0x20) *
                              0x781e >> 0xf),
                             ((int)uVar12 >> 0x10) * 0xf03c + ((uint)(ushort)uVar12 * 0x781e >> 0xf)
                            );
        *puVar5 = CONCAT44((int)((long)uVar11 >> 0x30) * 0xf03c +
                           ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                                    CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                             (uint)(ushort)uVar11)) >> 0x20) *
                            0x781e >> 0xf),
                           ((int)uVar11 >> 0x10) * 0xf03c + ((uint)(ushort)uVar11 * 0x781e >> 0xf));
        puVar5[0x1b1] =
             CONCAT44((int)((long)uVar14 >> 0x30) * 0xf03c +
                      ((uint)(ushort)(CONCAT15((char)((ulong)uVar14 >> 0x28),
                                               CONCAT14((char)((ulong)uVar14 >> 0x20),
                                                        (uint)(ushort)uVar14)) >> 0x20) * 0x781e >>
                      0xf),((int)uVar14 >> 0x10) * 0xf03c + ((uint)(ushort)uVar14 * 0x781e >> 0xf));
        puVar5[0x1b0] =
             CONCAT44((int)((long)uVar13 >> 0x30) * 0xf03c +
                      ((uint)(ushort)(CONCAT15((char)((ulong)uVar13 >> 0x28),
                                               CONCAT14((char)((ulong)uVar13 >> 0x20),
                                                        (uint)(ushort)uVar13)) >> 0x20) * 0x781e >>
                      0xf),((int)uVar13 >> 0x10) * 0xf03c + ((uint)(ushort)uVar13 * 0x781e >> 0xf));
        puVar5 = puVar5 + 2;
      } while (lVar7 != 0);
      if (uVar3 == 0) goto LAB_0010ca08;
    }
    do {
      puVar2 = (uint *)(param_1 + lVar6 * 4);
      lVar6 = lVar6 + 1;
      *puVar2 = ((int)*puVar2 >> 0x10) * 0xf03c + ((*puVar2 & 0xffff) * 0x781e >> 0xf);
      puVar2[0x360] =
           ((int)puVar2[0x360] >> 0x10) * 0xf03c + ((puVar2[0x360] & 0xffff) * 0x781e >> 0xf);
    } while ((int)lVar6 != 0x15e);
  }
LAB_0010ca08:
  puVar5 = (undefined8 *)(param_1 + 0x578);
  lVar7 = 0x200;
  do {
    uVar12 = puVar5[1];
    uVar11 = *puVar5;
    uVar14 = puVar5[0x1b1];
    uVar13 = puVar5[0x1b0];
    lVar7 = lVar7 + -4;
    puVar5[1] = CONCAT44((int)((long)uVar12 >> 0x30) * 0xef38 +
                         ((uint)(ushort)(CONCAT15((char)((ulong)uVar12 >> 0x28),
                                                  CONCAT14((char)((ulong)uVar12 >> 0x20),
                                                           (uint)(ushort)uVar12)) >> 0x20) * 0x779c
                         >> 0xf),((int)uVar12 >> 0x10) * 0xef38 +
                                 ((uint)(ushort)uVar12 * 0x779c >> 0xf));
    *puVar5 = CONCAT44((int)((long)uVar11 >> 0x30) * 0xef38 +
                       ((uint)(ushort)(CONCAT15((char)((ulong)uVar11 >> 0x28),
                                                CONCAT14((char)((ulong)uVar11 >> 0x20),
                                                         (uint)(ushort)uVar11)) >> 0x20) * 0x779c >>
                       0xf),((int)uVar11 >> 0x10) * 0xef38 + ((uint)(ushort)uVar11 * 0x779c >> 0xf))
    ;
    puVar5[0x1b1] =
         CONCAT44((int)((long)uVar14 >> 0x30) * 0xef38 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar14 >> 0x28),
                                           CONCAT14((char)((ulong)uVar14 >> 0x20),
                                                    (uint)(ushort)uVar14)) >> 0x20) * 0x779c >> 0xf)
                  ,((int)uVar14 >> 0x10) * 0xef38 + ((uint)(ushort)uVar14 * 0x779c >> 0xf));
    puVar5[0x1b0] =
         CONCAT44((int)((long)uVar13 >> 0x30) * 0xef38 +
                  ((uint)(ushort)(CONCAT15((char)((ulong)uVar13 >> 0x28),
                                           CONCAT14((char)((ulong)uVar13 >> 0x20),
                                                    (uint)(ushort)uVar13)) >> 0x20) * 0x779c >> 0xf)
                  ,((int)uVar13 >> 0x10) * 0xef38 + ((uint)(ushort)uVar13 * 0x779c >> 0xf));
    puVar5 = puVar5 + 2;
  } while (lVar7 != 0);
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


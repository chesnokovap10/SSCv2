/* alg_quant @ 00111c38 size 4300 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulong alg_quant(undefined2 *param_1,uint param_2,int param_3,int param_4,int param_5,
               undefined8 param_6)

{
  undefined1 (*pauVar1) [16];
  ushort uVar2;
  ushort uVar3;
  short sVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  short sVar8;
  int iVar9;
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  short sVar12;
  short sVar13;
  short sVar14;
  bool bVar15;
  short sVar16;
  short sVar17;
  int iVar18;
  uint uVar19;
  int iVar20;
  ushort *puVar21;
  short *psVar22;
  short *psVar23;
  short *psVar24;
  uint uVar25;
  undefined8 *puVar26;
  ushort *puVar27;
  long lVar28;
  short *psVar29;
  undefined8 *puVar30;
  ulong uVar31;
  ulong uVar32;
  undefined2 *puVar33;
  long lVar34;
  ulong uVar35;
  int iVar36;
  long lVar37;
  ushort *puVar38;
  undefined1 (*pauVar39) [16];
  long lVar40;
  long lVar41;
  long lVar42;
  long lVar43;
  ulong uVar44;
  short *psVar45;
  int iVar46;
  long lVar47;
  long lVar48;
  undefined1 (*pauVar49) [16];
  int iVar50;
  int iVar51;
  int iVar52;
  long lVar53;
  ulong uVar54;
  undefined1 uVar55;
  undefined1 uVar56;
  char cVar57;
  undefined1 uVar58;
  undefined1 uVar59;
  undefined1 uVar60;
  undefined1 uVar61;
  undefined1 uVar62;
  undefined1 uVar63;
  undefined1 uVar64;
  undefined1 uVar65;
  char cVar66;
  undefined1 uVar67;
  undefined1 uVar68;
  undefined1 uVar69;
  undefined1 uVar70;
  undefined1 uVar71;
  undefined1 uVar72;
  undefined1 auVar73 [16];
  undefined1 auVar74 [16];
  byte bVar75;
  byte bVar77;
  byte bVar78;
  byte bVar79;
  byte bVar80;
  byte bVar82;
  byte bVar83;
  int iVar81;
  undefined8 uVar76;
  byte bVar84;
  byte bVar85;
  byte bVar89;
  byte bVar90;
  int iVar86;
  int iVar87;
  byte bVar91;
  byte bVar92;
  byte bVar95;
  byte bVar96;
  int iVar93;
  int iVar94;
  undefined8 uVar88;
  byte bVar97;
  undefined1 auVar98 [16];
  undefined1 auVar99 [16];
  int iVar102;
  int iVar103;
  int iVar104;
  int iVar105;
  int iVar106;
  undefined1 auVar100 [16];
  undefined1 auVar101 [16];
  
  if ((param_3 * 2 < (int)param_2) && (param_4 != 0)) {
    iVar18 = ssc_rcp(param_2 + *(int *)((long)&DAT_00116be0 + (long)param_4 * 4 + 4) * param_3);
    iVar18 = (int)(short)((ulong)((long)iVar18 *
                                  (long)(int)((-(param_2 >> 0xf & 1) & 0x80000000 |
                                              (param_2 & 0xffff) << 0xf) - (int)(short)param_2) *
                                 0x20000) >> 0x30);
    uVar25 = (uint)(iVar18 * iVar18) >> 0x10;
    sVar16 = ssc_cos_norm(uVar25);
    sVar17 = ssc_cos_norm(uVar25 ^ 0x7fff);
    if ((int)param_2 < param_5 * 8) {
      if (0 < param_5) {
        iVar51 = (int)sVar16;
        iVar50 = (int)-sVar17;
        iVar18 = 0;
        if (param_5 != 0) {
          iVar18 = (int)param_2 / param_5;
        }
        iVar52 = iVar18 + -3;
        iVar36 = iVar18 + -2;
        if (iVar36 < 0) {
          if (-1 < iVar52) {
            lVar37 = (long)param_5;
            do {
              lVar37 = lVar37 + -1;
              psVar29 = param_1 + (long)iVar52 + lVar37 * iVar18;
              iVar20 = iVar36;
              do {
                sVar16 = psVar29[1];
                iVar20 = iVar20 + -1;
                psVar29[1] = (short)((uint)(*psVar29 * iVar50 + sVar16 * iVar51) >> 0xf);
                *psVar29 = (short)((uint)(*psVar29 * iVar51 - sVar16 * iVar50) >> 0xf);
                psVar29 = psVar29 + -1;
              } while (0 < iVar20);
            } while (0 < lVar37);
          }
        }
        else {
          lVar37 = (long)param_5;
          lVar40 = (long)iVar18;
          if (iVar52 < 0) {
            psVar29 = param_1 + (lVar37 + -1) * lVar40 + 1;
            do {
              lVar37 = lVar37 + -1;
              uVar25 = (uint)(ushort)param_1[lVar37 * lVar40];
              psVar24 = psVar29;
              iVar52 = iVar18 + -1;
              do {
                sVar16 = *psVar24;
                sVar17 = (short)uVar25;
                iVar52 = iVar52 + -1;
                uVar25 = (uint)(sVar17 * iVar50 + sVar16 * iVar51) >> 0xf;
                *psVar24 = (short)uVar25;
                psVar24[-1] = (short)((uint)(sVar17 * iVar51 - sVar16 * iVar50) >> 0xf);
                psVar24 = psVar24 + 1;
              } while (0 < iVar52);
              psVar29 = psVar29 + -lVar40;
            } while (0 < lVar37);
          }
          else {
            psVar29 = param_1 + (lVar37 + -1) * lVar40 + 1;
            do {
              lVar37 = lVar37 + -1;
              uVar25 = (uint)(ushort)param_1[lVar37 * lVar40];
              psVar24 = psVar29;
              iVar20 = iVar18 + -1;
              do {
                sVar16 = *psVar24;
                sVar17 = (short)uVar25;
                iVar20 = iVar20 + -1;
                uVar25 = (uint)(sVar17 * iVar50 + sVar16 * iVar51) >> 0xf;
                *psVar24 = (short)uVar25;
                psVar24[-1] = (short)((uint)(sVar17 * iVar51 - sVar16 * iVar50) >> 0xf);
                psVar24 = psVar24 + 1;
              } while (0 < iVar20);
              puVar38 = param_1 + lVar37 * lVar40 + iVar52;
              iVar20 = iVar36;
              do {
                uVar2 = puVar38[1];
                iVar20 = iVar20 + -1;
                puVar38[1] = (ushort)((uint)((short)*puVar38 * iVar50 + (short)uVar2 * iVar51) >>
                                     0xf);
                *puVar38 = (ushort)((uint)((short)*puVar38 * iVar51 - (short)uVar2 * iVar50) >> 0xf)
                ;
                puVar38 = puVar38 + -1;
              } while (0 < iVar20);
              psVar29 = psVar29 + -lVar40;
            } while (0 < lVar37);
          }
        }
      }
    }
    else {
      uVar32 = 1;
      iVar18 = 0;
      iVar51 = -3;
      iVar50 = -2;
      iVar52 = -1;
      puVar33 = param_1;
      do {
        iVar20 = iVar52;
        iVar46 = iVar50;
        iVar81 = iVar51;
        iVar36 = iVar18;
        uVar54 = uVar32;
        puVar33 = puVar33 + 1;
        uVar25 = (uint)uVar54;
        uVar32 = uVar54 + 1;
        iVar18 = iVar36 + -1;
        iVar51 = iVar81 + -2;
        iVar50 = iVar46 + -2;
        iVar52 = iVar20 + -1;
      } while ((int)((param_5 >> 2) + (uVar25 + uVar25 * uVar25) * param_5) < (int)param_2);
      if (0 < param_5) {
        iVar51 = (int)sVar17;
        iVar18 = 0;
        if (param_5 != 0) {
          iVar18 = (int)param_2 / param_5;
        }
        iVar6 = uVar25 - iVar18;
        lVar37 = (long)param_5;
        iVar94 = iVar18 + -3;
        iVar50 = iVar18 + (uVar25 << 1 ^ 0xffffffff);
        iVar103 = (int)-sVar17;
        iVar52 = iVar18 + ~uVar25;
        lVar40 = (long)iVar18;
        iVar87 = iVar6;
        if (iVar6 < 0) {
          iVar87 = -1;
        }
        lVar28 = (lVar37 + -1) * lVar40;
        lVar41 = -lVar40;
        lVar34 = lVar28 + (uVar54 & 0xffffffff);
        uVar25 = (iVar18 + iVar87) - uVar25;
        uVar44 = (ulong)uVar25;
        lVar47 = lVar34 + uVar44 + 1;
        uVar32 = uVar44 + 1;
        lVar48 = lVar28 + uVar44 + 1;
        sVar8 = -sVar16;
        uVar25 = uVar25 + 1 & 7;
        iVar9 = (int)sVar8;
        lVar42 = uVar32 - uVar25;
        iVar105 = (int)sVar16;
        iVar87 = iVar18 + -2;
        cVar57 = (char)(sVar17 >> 0xf);
        iVar7 = iVar52 - (int)lVar42;
        cVar66 = (char)(sVar8 >> 0xf);
        if (iVar87 < 0) {
          lVar53 = 0;
          if (iVar94 < 0) {
            psVar29 = puVar33 + lVar28;
            puVar30 = (undefined8 *)(param_1 + lVar28);
            if (iVar6 < 0) {
              iVar6 = -1;
            }
            psVar24 = psVar29 + (iVar18 + iVar81);
            do {
              lVar37 = lVar37 + -1;
              psVar45 = param_1 + lVar37 * lVar40;
              if (-1 < iVar52) {
                psVar22 = psVar45;
                iVar81 = iVar52;
                if ((7 < uVar32) &&
                   ((lVar43 = lVar53 * lVar41,
                    param_1 + lVar48 + lVar43 <= param_1 + lVar34 + lVar43 ||
                    (param_1 + lVar47 + lVar43 <= param_1 + lVar28 + lVar43)))) {
                  lVar43 = ((ulong)(uint)(iVar18 + iVar6 + iVar20) + 1) -
                           ((ulong)(uint)(iVar18 + iVar6 + iVar36) & 7);
                  psVar22 = psVar29;
                  puVar26 = puVar30;
                  do {
                    sVar16 = *psVar22;
                    sVar4 = psVar22[1];
                    sVar12 = psVar22[2];
                    sVar13 = psVar22[3];
                    sVar14 = psVar22[4];
                    uVar88 = puVar26[1];
                    uVar76 = *puVar26;
                    lVar43 = lVar43 + -8;
                    iVar103 = (int)(short)((ulong)uVar76 >> 0x10);
                    iVar105 = (int)(short)((ulong)uVar76 >> 0x20);
                    iVar86 = (int)(short)((ulong)uVar76 >> 0x30);
                    iVar81 = (int)(short)((ulong)uVar88 >> 0x10);
                    iVar87 = (int)(short)((ulong)uVar88 >> 0x20);
                    iVar94 = (int)(short)((ulong)uVar88 >> 0x30);
                    *(ulong *)(psVar22 + 4) =
                         CONCAT26((short)((uint)(CONCAT13(cVar57,(int3)sVar17) * (int)psVar22[7] +
                                                CONCAT13(cVar66,(int3)sVar8) * iVar94) >> 0xf),
                                  CONCAT24((short)((uint)(CONCAT13(cVar57,(int3)sVar17) *
                                                          (int)psVar22[6] +
                                                         CONCAT13(cVar66,(int3)sVar8) * iVar87) >>
                                                  0xf),
                                           CONCAT22((short)((uint)(CONCAT13(cVar57,(int3)sVar17) *
                                                                   (int)psVar22[5] +
                                                                  CONCAT13(cVar66,(int3)sVar8) *
                                                                  iVar81) >> 0xf),
                                                    (short)((uint)(CONCAT13(cVar57,(int3)sVar17) *
                                                                   (int)sVar14 +
                                                                  CONCAT13(cVar66,(int3)sVar8) *
                                                                  (int)(short)uVar88) >> 0xf))));
                    *(ulong *)psVar22 =
                         CONCAT26((short)((uint)(CONCAT13(cVar57,(int3)sVar17) * (int)sVar13 +
                                                CONCAT13(cVar66,(int3)sVar8) * iVar86) >> 0xf),
                                  CONCAT24((short)((uint)(CONCAT13(cVar57,(int3)sVar17) *
                                                          (int)sVar12 +
                                                         CONCAT13(cVar66,(int3)sVar8) * iVar105) >>
                                                  0xf),
                                           CONCAT22((short)((uint)(CONCAT13(cVar57,(int3)sVar17) *
                                                                   (int)sVar4 +
                                                                  CONCAT13(cVar66,(int3)sVar8) *
                                                                  iVar103) >> 0xf),
                                                    (short)((uint)(CONCAT13(cVar57,(int3)sVar17) *
                                                                   (int)sVar16 +
                                                                  CONCAT13(cVar66,(int3)sVar8) *
                                                                  (int)(short)uVar76) >> 0xf))));
                    puVar26[1] = CONCAT26((short)((uint)(CONCAT13(cVar57,(int3)sVar17) * iVar94 -
                                                        CONCAT13(cVar66,(int3)sVar8) *
                                                        (int)psVar22[7]) >> 0xf),
                                          CONCAT24((short)((uint)(CONCAT13(cVar57,(int3)sVar17) *
                                                                  iVar87 - CONCAT13(cVar66,(int3)
                                                  sVar8) * (int)psVar22[6]) >> 0xf),
                                                  CONCAT22((short)((uint)(CONCAT13(cVar57,(int3)
                                                  sVar17) * iVar81 -
                                                  CONCAT13(cVar66,(int3)sVar8) * (int)psVar22[5]) >>
                                                  0xf),(short)((uint)(CONCAT13(cVar57,(int3)sVar17)
                                                                      * (int)(short)uVar88 -
                                                                     CONCAT13(cVar66,(int3)sVar8) *
                                                                     (int)sVar14) >> 0xf))));
                    *puVar26 = CONCAT26((short)((uint)(CONCAT13(cVar57,(int3)sVar17) * iVar86 -
                                                      CONCAT13(cVar66,(int3)sVar8) * (int)sVar13) >>
                                               0xf),
                                        CONCAT24((short)((uint)(CONCAT13(cVar57,(int3)sVar17) *
                                                                iVar105 -
                                                               CONCAT13(cVar66,(int3)sVar8) *
                                                               (int)sVar12) >> 0xf),
                                                 CONCAT22((short)((uint)(CONCAT13(cVar57,(int3)
                                                  sVar17) * iVar103 -
                                                  CONCAT13(cVar66,(int3)sVar8) * (int)sVar4) >> 0xf)
                                                  ,(short)((uint)(CONCAT13(cVar57,(int3)sVar17) *
                                                                  (int)(short)uVar76 -
                                                                 CONCAT13(cVar66,(int3)sVar8) *
                                                                 (int)sVar16) >> 0xf))));
                    psVar22 = psVar22 + 8;
                    puVar26 = puVar26 + 2;
                  } while (lVar43 != 0);
                  psVar22 = psVar45 + lVar42;
                  iVar81 = iVar7;
                  if (uVar25 == 0) goto LAB_00112820;
                }
                iVar81 = iVar81 + 1;
                psVar23 = psVar22 + uVar54;
                do {
                  sVar16 = *psVar22;
                  sVar4 = *psVar23;
                  iVar81 = iVar81 + -1;
                  *psVar23 = (short)((uint)(sVar16 * iVar9 + sVar4 * iVar51) >> 0xf);
                  *psVar22 = (short)((uint)(sVar16 * iVar51 - sVar4 * iVar9) >> 0xf);
                  psVar22 = psVar22 + 1;
                  psVar23 = psVar23 + 1;
                } while (0 < iVar81);
              }
LAB_00112820:
              if (-1 < iVar50) {
                psVar22 = psVar24;
                psVar45 = psVar45 + iVar50;
                iVar81 = iVar18 + iVar46;
                do {
                  sVar16 = *psVar45;
                  sVar4 = *psVar22;
                  iVar81 = iVar81 + -1;
                  *psVar22 = (short)((uint)(sVar16 * iVar9 + sVar4 * iVar51) >> 0xf);
                  *psVar45 = (short)((uint)(sVar16 * iVar51 - sVar4 * iVar9) >> 0xf);
                  psVar22 = psVar22 + -1;
                  psVar45 = psVar45 + -1;
                } while (0 < iVar81);
              }
              lVar53 = lVar53 + 1;
              puVar30 = (undefined8 *)((long)puVar30 + lVar40 * -2);
              psVar29 = psVar29 + -lVar40;
              psVar24 = psVar24 + -lVar40;
            } while (0 < lVar37);
          }
          else {
            psVar29 = puVar33 + lVar28;
            puVar30 = (undefined8 *)(param_1 + lVar28);
            if (iVar6 < 0) {
              iVar6 = -1;
            }
            psVar24 = psVar29 + (iVar18 + iVar81);
            do {
              lVar37 = lVar37 + -1;
              lVar43 = lVar53 * lVar41;
              psVar45 = param_1 + lVar37 * lVar40;
              psVar22 = psVar45 + iVar94;
              iVar81 = iVar87;
              do {
                sVar16 = psVar22[1];
                iVar81 = iVar81 + -1;
                psVar22[1] = (short)((uint)(*psVar22 * iVar103 + sVar16 * iVar105) >> 0xf);
                *psVar22 = (short)((uint)(*psVar22 * iVar105 - sVar16 * iVar103) >> 0xf);
                psVar22 = psVar22 + -1;
              } while (0 < iVar81);
              if (-1 < iVar52) {
                psVar22 = psVar45;
                iVar81 = iVar52;
                if ((7 < uVar32) &&
                   ((param_1 + lVar48 + lVar43 <= param_1 + lVar34 + lVar43 ||
                    (param_1 + lVar47 + lVar43 <= param_1 + lVar28 + lVar43)))) {
                  lVar43 = ((ulong)(uint)(iVar18 + iVar6 + iVar20) + 1) -
                           ((ulong)(uint)(iVar18 + iVar6 + iVar36) & 7);
                  psVar22 = psVar29;
                  puVar26 = puVar30;
                  do {
                    sVar16 = *psVar22;
                    sVar4 = psVar22[1];
                    sVar12 = psVar22[2];
                    sVar13 = psVar22[3];
                    sVar14 = psVar22[4];
                    uVar88 = puVar26[1];
                    uVar76 = *puVar26;
                    lVar43 = lVar43 + -8;
                    iVar102 = (int)(short)((ulong)uVar76 >> 0x10);
                    iVar104 = (int)(short)((ulong)uVar76 >> 0x20);
                    iVar106 = (int)(short)((ulong)uVar76 >> 0x30);
                    iVar81 = (int)(short)((ulong)uVar88 >> 0x10);
                    iVar86 = (int)(short)((ulong)uVar88 >> 0x20);
                    iVar93 = (int)(short)((ulong)uVar88 >> 0x30);
                    *(ulong *)(psVar22 + 4) =
                         CONCAT26((short)((uint)(CONCAT13(cVar57,(int3)sVar17) * (int)psVar22[7] +
                                                CONCAT13(cVar66,(int3)sVar8) * iVar93) >> 0xf),
                                  CONCAT24((short)((uint)(CONCAT13(cVar57,(int3)sVar17) *
                                                          (int)psVar22[6] +
                                                         CONCAT13(cVar66,(int3)sVar8) * iVar86) >>
                                                  0xf),
                                           CONCAT22((short)((uint)(CONCAT13(cVar57,(int3)sVar17) *
                                                                   (int)psVar22[5] +
                                                                  CONCAT13(cVar66,(int3)sVar8) *
                                                                  iVar81) >> 0xf),
                                                    (short)((uint)(CONCAT13(cVar57,(int3)sVar17) *
                                                                   (int)sVar14 +
                                                                  CONCAT13(cVar66,(int3)sVar8) *
                                                                  (int)(short)uVar88) >> 0xf))));
                    *(ulong *)psVar22 =
                         CONCAT26((short)((uint)(CONCAT13(cVar57,(int3)sVar17) * (int)sVar13 +
                                                CONCAT13(cVar66,(int3)sVar8) * iVar106) >> 0xf),
                                  CONCAT24((short)((uint)(CONCAT13(cVar57,(int3)sVar17) *
                                                          (int)sVar12 +
                                                         CONCAT13(cVar66,(int3)sVar8) * iVar104) >>
                                                  0xf),
                                           CONCAT22((short)((uint)(CONCAT13(cVar57,(int3)sVar17) *
                                                                   (int)sVar4 +
                                                                  CONCAT13(cVar66,(int3)sVar8) *
                                                                  iVar102) >> 0xf),
                                                    (short)((uint)(CONCAT13(cVar57,(int3)sVar17) *
                                                                   (int)sVar16 +
                                                                  CONCAT13(cVar66,(int3)sVar8) *
                                                                  (int)(short)uVar76) >> 0xf))));
                    puVar26[1] = CONCAT26((short)((uint)(CONCAT13(cVar57,(int3)sVar17) * iVar93 -
                                                        CONCAT13(cVar66,(int3)sVar8) *
                                                        (int)psVar22[7]) >> 0xf),
                                          CONCAT24((short)((uint)(CONCAT13(cVar57,(int3)sVar17) *
                                                                  iVar86 - CONCAT13(cVar66,(int3)
                                                  sVar8) * (int)psVar22[6]) >> 0xf),
                                                  CONCAT22((short)((uint)(CONCAT13(cVar57,(int3)
                                                  sVar17) * iVar81 -
                                                  CONCAT13(cVar66,(int3)sVar8) * (int)psVar22[5]) >>
                                                  0xf),(short)((uint)(CONCAT13(cVar57,(int3)sVar17)
                                                                      * (int)(short)uVar88 -
                                                                     CONCAT13(cVar66,(int3)sVar8) *
                                                                     (int)sVar14) >> 0xf))));
                    *puVar26 = CONCAT26((short)((uint)(CONCAT13(cVar57,(int3)sVar17) * iVar106 -
                                                      CONCAT13(cVar66,(int3)sVar8) * (int)sVar13) >>
                                               0xf),
                                        CONCAT24((short)((uint)(CONCAT13(cVar57,(int3)sVar17) *
                                                                iVar104 -
                                                               CONCAT13(cVar66,(int3)sVar8) *
                                                               (int)sVar12) >> 0xf),
                                                 CONCAT22((short)((uint)(CONCAT13(cVar57,(int3)
                                                  sVar17) * iVar102 -
                                                  CONCAT13(cVar66,(int3)sVar8) * (int)sVar4) >> 0xf)
                                                  ,(short)((uint)(CONCAT13(cVar57,(int3)sVar17) *
                                                                  (int)(short)uVar76 -
                                                                 CONCAT13(cVar66,(int3)sVar8) *
                                                                 (int)sVar16) >> 0xf))));
                    psVar22 = psVar22 + 8;
                    puVar26 = puVar26 + 2;
                  } while (lVar43 != 0);
                  psVar22 = psVar45 + lVar42;
                  iVar81 = iVar7;
                  if (uVar25 == 0) goto LAB_001123a0;
                }
                iVar81 = iVar81 + 1;
                psVar23 = psVar22 + uVar54;
                do {
                  sVar16 = *psVar22;
                  sVar4 = *psVar23;
                  iVar81 = iVar81 + -1;
                  *psVar23 = (short)((uint)(sVar16 * iVar9 + sVar4 * iVar51) >> 0xf);
                  *psVar22 = (short)((uint)(sVar16 * iVar51 - sVar4 * iVar9) >> 0xf);
                  psVar23 = psVar23 + 1;
                  psVar22 = psVar22 + 1;
                } while (0 < iVar81);
              }
LAB_001123a0:
              if (-1 < iVar50) {
                psVar22 = psVar24;
                psVar45 = psVar45 + iVar50;
                iVar81 = iVar18 + iVar46;
                do {
                  sVar16 = *psVar45;
                  sVar4 = *psVar22;
                  iVar81 = iVar81 + -1;
                  *psVar22 = (short)((uint)(sVar16 * iVar9 + sVar4 * iVar51) >> 0xf);
                  *psVar45 = (short)((uint)(sVar16 * iVar51 - sVar4 * iVar9) >> 0xf);
                  psVar22 = psVar22 + -1;
                  psVar45 = psVar45 + -1;
                } while (0 < iVar81);
              }
              lVar53 = lVar53 + 1;
              puVar30 = (undefined8 *)((long)puVar30 + lVar40 * -2);
              psVar29 = psVar29 + -lVar40;
              psVar24 = psVar24 + -lVar40;
            } while (0 < lVar37);
          }
        }
        else if (iVar94 < 0) {
          lVar53 = 0;
          puVar30 = (undefined8 *)(param_1 + lVar28);
          psVar29 = puVar33 + lVar28;
          if (iVar6 < 0) {
            iVar6 = -1;
          }
          psVar24 = psVar29 + (iVar18 + iVar81);
          psVar45 = (short *)((long)puVar30 + 2);
          do {
            lVar37 = lVar37 + -1;
            lVar43 = lVar53 * lVar41;
            puVar38 = param_1 + lVar37 * lVar40;
            uVar19 = (uint)*puVar38;
            psVar22 = psVar45;
            iVar81 = iVar18 + -1;
            do {
              sVar16 = *psVar22;
              sVar4 = (short)uVar19;
              iVar81 = iVar81 + -1;
              uVar19 = (uint)(sVar4 * iVar103 + sVar16 * iVar105) >> 0xf;
              *psVar22 = (short)uVar19;
              psVar22[-1] = (short)((uint)(sVar4 * iVar105 - sVar16 * iVar103) >> 0xf);
              psVar22 = psVar22 + 1;
            } while (0 < iVar81);
            if (-1 < iVar52) {
              puVar27 = puVar38;
              iVar81 = iVar52;
              if ((7 < uVar32) &&
                 ((param_1 + lVar48 + lVar43 <= param_1 + lVar34 + lVar43 ||
                  (param_1 + lVar47 + lVar43 <= param_1 + lVar28 + lVar43)))) {
                lVar43 = ((ulong)(uint)(iVar18 + iVar6 + iVar20) + 1) -
                         ((ulong)(uint)(iVar18 + iVar6 + iVar36) & 7);
                psVar22 = psVar29;
                puVar26 = puVar30;
                do {
                  sVar16 = *psVar22;
                  sVar4 = psVar22[1];
                  sVar12 = psVar22[2];
                  sVar13 = psVar22[3];
                  sVar14 = psVar22[4];
                  uVar88 = puVar26[1];
                  uVar76 = *puVar26;
                  lVar43 = lVar43 + -8;
                  iVar86 = (int)(short)((ulong)uVar76 >> 0x10);
                  iVar93 = (int)(short)((ulong)uVar76 >> 0x20);
                  iVar102 = (int)(short)((ulong)uVar76 >> 0x30);
                  iVar81 = (int)(short)((ulong)uVar88 >> 0x10);
                  iVar87 = (int)(short)((ulong)uVar88 >> 0x20);
                  iVar94 = (int)(short)((ulong)uVar88 >> 0x30);
                  *(ulong *)(psVar22 + 4) =
                       CONCAT26((short)((uint)(CONCAT13(cVar57,(int3)sVar17) * (int)psVar22[7] +
                                              CONCAT13(cVar66,(int3)sVar8) * iVar94) >> 0xf),
                                CONCAT24((short)((uint)(CONCAT13(cVar57,(int3)sVar17) *
                                                        (int)psVar22[6] +
                                                       CONCAT13(cVar66,(int3)sVar8) * iVar87) >> 0xf
                                                ),CONCAT22((short)((uint)(CONCAT13(cVar57,(int3)
                                                  sVar17) * (int)psVar22[5] +
                                                  CONCAT13(cVar66,(int3)sVar8) * iVar81) >> 0xf),
                                                  (short)((uint)(CONCAT13(cVar57,(int3)sVar17) *
                                                                 (int)sVar14 +
                                                                CONCAT13(cVar66,(int3)sVar8) *
                                                                (int)(short)uVar88) >> 0xf))));
                  *(ulong *)psVar22 =
                       CONCAT26((short)((uint)(CONCAT13(cVar57,(int3)sVar17) * (int)sVar13 +
                                              CONCAT13(cVar66,(int3)sVar8) * iVar102) >> 0xf),
                                CONCAT24((short)((uint)(CONCAT13(cVar57,(int3)sVar17) * (int)sVar12
                                                       + CONCAT13(cVar66,(int3)sVar8) * iVar93) >>
                                                0xf),
                                         CONCAT22((short)((uint)(CONCAT13(cVar57,(int3)sVar17) *
                                                                 (int)sVar4 +
                                                                CONCAT13(cVar66,(int3)sVar8) *
                                                                iVar86) >> 0xf),
                                                  (short)((uint)(CONCAT13(cVar57,(int3)sVar17) *
                                                                 (int)sVar16 +
                                                                CONCAT13(cVar66,(int3)sVar8) *
                                                                (int)(short)uVar76) >> 0xf))));
                  puVar26[1] = CONCAT26((short)((uint)(CONCAT13(cVar57,(int3)sVar17) * iVar94 -
                                                      CONCAT13(cVar66,(int3)sVar8) * (int)psVar22[7]
                                                      ) >> 0xf),
                                        CONCAT24((short)((uint)(CONCAT13(cVar57,(int3)sVar17) *
                                                                iVar87 - CONCAT13(cVar66,(int3)sVar8
                                                                                 ) * (int)psVar22[6]
                                                               ) >> 0xf),
                                                 CONCAT22((short)((uint)(CONCAT13(cVar57,(int3)
                                                  sVar17) * iVar81 -
                                                  CONCAT13(cVar66,(int3)sVar8) * (int)psVar22[5]) >>
                                                  0xf),(short)((uint)(CONCAT13(cVar57,(int3)sVar17)
                                                                      * (int)(short)uVar88 -
                                                                     CONCAT13(cVar66,(int3)sVar8) *
                                                                     (int)sVar14) >> 0xf))));
                  *puVar26 = CONCAT26((short)((uint)(CONCAT13(cVar57,(int3)sVar17) * iVar102 -
                                                    CONCAT13(cVar66,(int3)sVar8) * (int)sVar13) >>
                                             0xf),
                                      CONCAT24((short)((uint)(CONCAT13(cVar57,(int3)sVar17) * iVar93
                                                             - CONCAT13(cVar66,(int3)sVar8) *
                                                               (int)sVar12) >> 0xf),
                                               CONCAT22((short)((uint)(CONCAT13(cVar57,(int3)sVar17)
                                                                       * iVar86 -
                                                                      CONCAT13(cVar66,(int3)sVar8) *
                                                                      (int)sVar4) >> 0xf),
                                                        (short)((uint)(CONCAT13(cVar57,(int3)sVar17)
                                                                       * (int)(short)uVar76 -
                                                                      CONCAT13(cVar66,(int3)sVar8) *
                                                                      (int)sVar16) >> 0xf))));
                  psVar22 = psVar22 + 8;
                  puVar26 = puVar26 + 2;
                } while (lVar43 != 0);
                puVar27 = puVar38 + lVar42;
                iVar81 = iVar7;
                if (uVar25 == 0) goto LAB_00112644;
              }
              iVar81 = iVar81 + 1;
              puVar21 = puVar27 + uVar54;
              do {
                uVar2 = *puVar27;
                uVar3 = *puVar21;
                iVar81 = iVar81 + -1;
                *puVar21 = (ushort)((uint)((short)uVar2 * iVar9 + (short)uVar3 * iVar51) >> 0xf);
                *puVar27 = (ushort)((uint)((short)uVar2 * iVar51 - (short)uVar3 * iVar9) >> 0xf);
                puVar21 = puVar21 + 1;
                puVar27 = puVar27 + 1;
              } while (0 < iVar81);
            }
LAB_00112644:
            if (-1 < iVar50) {
              psVar22 = psVar24;
              puVar38 = puVar38 + iVar50;
              iVar81 = iVar18 + iVar46;
              do {
                uVar2 = *puVar38;
                sVar16 = *psVar22;
                iVar81 = iVar81 + -1;
                *psVar22 = (short)((uint)((short)uVar2 * iVar9 + sVar16 * iVar51) >> 0xf);
                *puVar38 = (ushort)((uint)((short)uVar2 * iVar51 - sVar16 * iVar9) >> 0xf);
                psVar22 = psVar22 + -1;
                puVar38 = puVar38 + -1;
              } while (0 < iVar81);
            }
            lVar53 = lVar53 + 1;
            psVar45 = psVar45 + -lVar40;
            puVar30 = (undefined8 *)((long)puVar30 + lVar40 * -2);
            psVar29 = psVar29 + -lVar40;
            psVar24 = psVar24 + -lVar40;
          } while (0 < lVar37);
        }
        else {
          lVar53 = 0;
          puVar30 = (undefined8 *)(param_1 + lVar28);
          psVar29 = puVar33 + lVar28;
          if (iVar6 < 0) {
            iVar6 = -1;
          }
          psVar24 = psVar29 + (iVar18 + iVar81);
          psVar45 = (short *)((long)puVar30 + 2);
          do {
            lVar37 = lVar37 + -1;
            lVar43 = lVar53 * lVar41;
            puVar38 = param_1 + lVar37 * lVar40;
            uVar19 = (uint)*puVar38;
            psVar22 = psVar45;
            iVar81 = iVar18 + -1;
            do {
              sVar16 = *psVar22;
              sVar4 = (short)uVar19;
              iVar81 = iVar81 + -1;
              uVar19 = (uint)(sVar4 * iVar103 + sVar16 * iVar105) >> 0xf;
              *psVar22 = (short)uVar19;
              psVar22[-1] = (short)((uint)(sVar4 * iVar105 - sVar16 * iVar103) >> 0xf);
              psVar22 = psVar22 + 1;
            } while (0 < iVar81);
            puVar27 = puVar38 + iVar94;
            iVar81 = iVar87;
            do {
              uVar2 = puVar27[1];
              iVar81 = iVar81 + -1;
              puVar27[1] = (ushort)((uint)((short)*puVar27 * iVar103 + (short)uVar2 * iVar105) >>
                                   0xf);
              *puVar27 = (ushort)((uint)((short)*puVar27 * iVar105 - (short)uVar2 * iVar103) >> 0xf)
              ;
              puVar27 = puVar27 + -1;
            } while (0 < iVar81);
            if (-1 < iVar52) {
              puVar27 = puVar38;
              iVar81 = iVar52;
              if ((7 < uVar32) &&
                 ((param_1 + lVar48 + lVar43 <= param_1 + lVar34 + lVar43 ||
                  (param_1 + lVar47 + lVar43 <= param_1 + lVar28 + lVar43)))) {
                lVar43 = ((ulong)(uint)(iVar18 + iVar6 + iVar20) + 1) -
                         ((ulong)(uint)(iVar18 + iVar6 + iVar36) & 7);
                psVar22 = psVar29;
                puVar26 = puVar30;
                do {
                  sVar16 = *psVar22;
                  sVar4 = psVar22[1];
                  sVar12 = psVar22[2];
                  sVar13 = psVar22[3];
                  sVar14 = psVar22[4];
                  uVar88 = puVar26[1];
                  uVar76 = *puVar26;
                  lVar43 = lVar43 + -8;
                  iVar102 = (int)(short)((ulong)uVar76 >> 0x10);
                  iVar104 = (int)(short)((ulong)uVar76 >> 0x20);
                  iVar106 = (int)(short)((ulong)uVar76 >> 0x30);
                  iVar81 = (int)(short)((ulong)uVar88 >> 0x10);
                  iVar86 = (int)(short)((ulong)uVar88 >> 0x20);
                  iVar93 = (int)(short)((ulong)uVar88 >> 0x30);
                  *(ulong *)(psVar22 + 4) =
                       CONCAT26((short)((uint)(CONCAT13(cVar57,(int3)sVar17) * (int)psVar22[7] +
                                              CONCAT13(cVar66,(int3)sVar8) * iVar93) >> 0xf),
                                CONCAT24((short)((uint)(CONCAT13(cVar57,(int3)sVar17) *
                                                        (int)psVar22[6] +
                                                       CONCAT13(cVar66,(int3)sVar8) * iVar86) >> 0xf
                                                ),CONCAT22((short)((uint)(CONCAT13(cVar57,(int3)
                                                  sVar17) * (int)psVar22[5] +
                                                  CONCAT13(cVar66,(int3)sVar8) * iVar81) >> 0xf),
                                                  (short)((uint)(CONCAT13(cVar57,(int3)sVar17) *
                                                                 (int)sVar14 +
                                                                CONCAT13(cVar66,(int3)sVar8) *
                                                                (int)(short)uVar88) >> 0xf))));
                  *(ulong *)psVar22 =
                       CONCAT26((short)((uint)(CONCAT13(cVar57,(int3)sVar17) * (int)sVar13 +
                                              CONCAT13(cVar66,(int3)sVar8) * iVar106) >> 0xf),
                                CONCAT24((short)((uint)(CONCAT13(cVar57,(int3)sVar17) * (int)sVar12
                                                       + CONCAT13(cVar66,(int3)sVar8) * iVar104) >>
                                                0xf),
                                         CONCAT22((short)((uint)(CONCAT13(cVar57,(int3)sVar17) *
                                                                 (int)sVar4 +
                                                                CONCAT13(cVar66,(int3)sVar8) *
                                                                iVar102) >> 0xf),
                                                  (short)((uint)(CONCAT13(cVar57,(int3)sVar17) *
                                                                 (int)sVar16 +
                                                                CONCAT13(cVar66,(int3)sVar8) *
                                                                (int)(short)uVar76) >> 0xf))));
                  puVar26[1] = CONCAT26((short)((uint)(CONCAT13(cVar57,(int3)sVar17) * iVar93 -
                                                      CONCAT13(cVar66,(int3)sVar8) * (int)psVar22[7]
                                                      ) >> 0xf),
                                        CONCAT24((short)((uint)(CONCAT13(cVar57,(int3)sVar17) *
                                                                iVar86 - CONCAT13(cVar66,(int3)sVar8
                                                                                 ) * (int)psVar22[6]
                                                               ) >> 0xf),
                                                 CONCAT22((short)((uint)(CONCAT13(cVar57,(int3)
                                                  sVar17) * iVar81 -
                                                  CONCAT13(cVar66,(int3)sVar8) * (int)psVar22[5]) >>
                                                  0xf),(short)((uint)(CONCAT13(cVar57,(int3)sVar17)
                                                                      * (int)(short)uVar88 -
                                                                     CONCAT13(cVar66,(int3)sVar8) *
                                                                     (int)sVar14) >> 0xf))));
                  *puVar26 = CONCAT26((short)((uint)(CONCAT13(cVar57,(int3)sVar17) * iVar106 -
                                                    CONCAT13(cVar66,(int3)sVar8) * (int)sVar13) >>
                                             0xf),
                                      CONCAT24((short)((uint)(CONCAT13(cVar57,(int3)sVar17) *
                                                              iVar104 -
                                                             CONCAT13(cVar66,(int3)sVar8) *
                                                             (int)sVar12) >> 0xf),
                                               CONCAT22((short)((uint)(CONCAT13(cVar57,(int3)sVar17)
                                                                       * iVar102 -
                                                                      CONCAT13(cVar66,(int3)sVar8) *
                                                                      (int)sVar4) >> 0xf),
                                                        (short)((uint)(CONCAT13(cVar57,(int3)sVar17)
                                                                       * (int)(short)uVar76 -
                                                                      CONCAT13(cVar66,(int3)sVar8) *
                                                                      (int)sVar16) >> 0xf))));
                  psVar22 = psVar22 + 8;
                  puVar26 = puVar26 + 2;
                } while (lVar43 != 0);
                puVar27 = puVar38 + lVar42;
                iVar81 = iVar7;
                if (uVar25 == 0) goto LAB_00112108;
              }
              iVar81 = iVar81 + 1;
              puVar21 = puVar27 + uVar54;
              do {
                uVar2 = *puVar27;
                uVar3 = *puVar21;
                iVar81 = iVar81 + -1;
                *puVar21 = (ushort)((uint)((short)uVar2 * iVar9 + (short)uVar3 * iVar51) >> 0xf);
                *puVar27 = (ushort)((uint)((short)uVar2 * iVar51 - (short)uVar3 * iVar9) >> 0xf);
                puVar21 = puVar21 + 1;
                puVar27 = puVar27 + 1;
              } while (0 < iVar81);
            }
LAB_00112108:
            if (-1 < iVar50) {
              psVar22 = psVar24;
              puVar38 = puVar38 + iVar50;
              iVar81 = iVar18 + iVar46;
              do {
                uVar2 = *puVar38;
                sVar16 = *psVar22;
                iVar81 = iVar81 + -1;
                *psVar22 = (short)((uint)((short)uVar2 * iVar9 + sVar16 * iVar51) >> 0xf);
                *puVar38 = (ushort)((uint)((short)uVar2 * iVar51 - sVar16 * iVar9) >> 0xf);
                psVar22 = psVar22 + -1;
                puVar38 = puVar38 + -1;
              } while (0 < iVar81);
            }
            lVar53 = lVar53 + 1;
            psVar45 = psVar45 + -lVar40;
            puVar30 = (undefined8 *)((long)puVar30 + lVar40 * -2);
            psVar29 = psVar29 + -lVar40;
            psVar24 = psVar24 + -lVar40;
          } while (0 < lVar37);
        }
      }
    }
  }
  uVar54 = (ulong)(int)(param_2 - 1);
  puVar33 = (undefined2 *)(&DAT_0012c0b0 + (long)(int)(param_2 - 1) * 2);
  uVar32 = uVar54;
  do {
    if ((short)param_1[uVar32] < 1) {
      puVar33[0x120] = 0xffff;
      param_1[uVar32] = -param_1[uVar32];
    }
    else {
      puVar33[0x120] = 1;
    }
    *puVar33 = 0;
    *(undefined4 *)(&DAT_0012be70 + uVar32 * 4) = 0;
    bVar15 = 0 < (long)uVar32;
    puVar33 = puVar33 + -1;
    uVar32 = uVar32 - 1;
  } while (bVar15);
  iVar18 = param_3;
  if ((int)param_2 >> 1 < param_3) {
    uVar32 = ~(uVar54 & (long)uVar54 >> 0x3f) + uVar54 + 2;
    if (uVar32 < 4) {
      iVar51 = 0;
      uVar31 = uVar54;
LAB_001129a4:
      do {
        iVar51 = iVar51 + (short)param_1[uVar31];
        bVar15 = 0 < (long)uVar31;
        uVar31 = uVar31 - 1;
      } while (bVar15);
    }
    else {
      uVar35 = uVar32 & 0xfffffffffffffffc;
      uVar55 = 0;
      uVar56 = 0;
      uVar58 = 0;
      uVar59 = 0;
      uVar60 = 0;
      uVar61 = 0;
      uVar62 = 0;
      uVar63 = 0;
      uVar31 = uVar54 - uVar35;
      puVar38 = param_1 + (uVar54 - 1);
      uVar64 = 0;
      uVar65 = 0;
      uVar67 = 0;
      uVar68 = 0;
      uVar69 = 0;
      uVar70 = 0;
      uVar71 = 0;
      uVar72 = 0;
      uVar44 = uVar35;
      do {
        uVar76 = NEON_rev64((ulong)CONCAT24(puVar38[1],(uint)*puVar38),4);
        uVar88 = NEON_rev64((ulong)CONCAT24(puVar38[-1],(uint)puVar38[-2]),4);
        uVar44 = uVar44 - 4;
        iVar51 = CONCAT13(uVar59,CONCAT12(uVar58,CONCAT11(uVar56,uVar55))) + (int)(short)uVar76;
        uVar55 = (undefined1)iVar51;
        uVar56 = (undefined1)((uint)iVar51 >> 8);
        uVar58 = (undefined1)((uint)iVar51 >> 0x10);
        uVar59 = (undefined1)((uint)iVar51 >> 0x18);
        iVar50 = CONCAT13(uVar63,CONCAT12(uVar62,CONCAT11(uVar61,uVar60))) +
                 (int)(short)((ulong)uVar76 >> 0x20);
        uVar60 = (undefined1)iVar50;
        uVar61 = (undefined1)((uint)iVar50 >> 8);
        uVar62 = (undefined1)((uint)iVar50 >> 0x10);
        uVar63 = (undefined1)((uint)iVar50 >> 0x18);
        iVar52 = CONCAT13(uVar68,CONCAT12(uVar67,CONCAT11(uVar65,uVar64))) + (int)(short)uVar88;
        uVar64 = (undefined1)iVar52;
        uVar65 = (undefined1)((uint)iVar52 >> 8);
        uVar67 = (undefined1)((uint)iVar52 >> 0x10);
        uVar68 = (undefined1)((uint)iVar52 >> 0x18);
        iVar36 = CONCAT13(uVar72,CONCAT12(uVar71,CONCAT11(uVar70,uVar69))) +
                 (int)(short)((ulong)uVar88 >> 0x20);
        uVar69 = (undefined1)iVar36;
        uVar70 = (undefined1)((uint)iVar36 >> 8);
        uVar71 = (undefined1)((uint)iVar36 >> 0x10);
        uVar72 = (undefined1)((uint)iVar36 >> 0x18);
        puVar38 = puVar38 + -4;
      } while (uVar44 != 0);
      iVar51 = iVar52 + iVar51 + iVar36 + iVar50;
      if (uVar32 != uVar35) goto LAB_001129a4;
    }
    if (iVar51 <= param_3) {
      iVar51 = 0x4000;
      *param_1 = 0x4000;
      memset(param_1 + (uVar54 - (param_2 - 2)),0,(ulong)(param_2 - 2) * 2 + 2);
    }
    uVar25 = ssc_rcp(iVar51);
    uVar19 = ssc_rcp(iVar51);
    iVar51 = 0;
    iVar50 = 0;
    uVar32 = uVar54;
    do {
      iVar36 = ((int)((uVar25 & 0xffff0000 | uVar19 & 0xffff) *
                     (param_3 * 0x10000 + -0x10000 >> 0x10)) >> 0x10) * (int)(short)param_1[uVar32];
      iVar52 = iVar36 >> 0xf;
      *(int *)(&DAT_0012be70 + uVar32 * 4) = iVar52;
      *(short *)(&DAT_0012c0b0 + uVar32 * 2) = (short)iVar52;
      iVar36 = iVar36 * 2 >> 0x10;
      iVar51 = iVar36 * iVar36 + (int)(short)iVar51;
      iVar50 = iVar50 + iVar36 * (short)param_1[uVar32];
      iVar18 = iVar18 - iVar52;
      *(short *)(&DAT_0012c0b0 + uVar32 * 2) = (short)(iVar52 << 1);
      bVar15 = 0 < (long)uVar32;
      uVar32 = uVar32 - 1;
    } while (bVar15);
    if (iVar18 <= (int)(param_2 + 3)) {
LAB_00112a88:
      if (0 < iVar18) {
        iVar52 = 0;
        do {
          iVar52 = iVar52 + 1;
          iVar20 = ec_ilog((iVar52 + param_3) - iVar18);
          lVar37 = 0;
          uVar32 = 0;
          uVar25 = 0xffff8001;
          iVar36 = 0;
          do {
            iVar46 = (int)(short)(iVar50 + (short)param_1[lVar37] >>
                                 ((iVar20 * 0x10000 + -0x10000 >> 0x10) + 1U & 0x1f));
            iVar81 = (uint)*(ushort *)(&DAT_0012c0b0 + lVar37 * 2) + iVar51 + 1;
            uVar5 = (uint)(iVar46 * iVar46) >> 7;
            lVar34 = (long)(short)iVar81 * (long)(int)uVar25;
            lVar40 = (ulong)uVar5 * (long)(short)iVar36;
            bVar15 = lVar40 - lVar34 == 0;
            uVar19 = (uint)lVar37;
            if (bVar15 || lVar40 < lVar34) {
              uVar19 = (uint)uVar32;
            }
            uVar32 = (ulong)uVar19;
            lVar37 = lVar37 + 1;
            if (bVar15 || lVar40 < lVar34) {
              iVar81 = iVar36;
              uVar5 = uVar25;
            }
            uVar25 = uVar5;
            iVar36 = iVar81;
          } while (lVar37 < (int)param_2);
          uVar32 = -(ulong)(uVar19 >> 0x1f) & 0xfffffffe00000000 | uVar32 << 1;
          uVar2 = *(ushort *)(&DAT_0012c0b0 + uVar32);
          sVar16 = *(short *)((long)param_1 + uVar32);
          *(ushort *)(&DAT_0012c0b0 + uVar32) = uVar2 + 2;
          iVar50 = iVar50 + sVar16;
          iVar51 = (uint)uVar2 + iVar51 + 1;
          *(int *)(&DAT_0012be70 + (long)(int)uVar19 * 4) =
               *(int *)(&DAT_0012be70 + (long)(int)uVar19 * 4) + 1;
        } while (iVar52 != iVar18);
      }
      goto LAB_00112b60;
    }
  }
  else {
    iVar51 = 0;
    iVar50 = 0;
    if (param_3 <= (int)(param_2 + 3)) goto LAB_00112a88;
  }
  _DAT_0012be70 = _DAT_0012be70 + iVar18;
LAB_00112b60:
  do {
    param_1[uVar54] = param_1[uVar54] * *(short *)(&DAT_0012c2f0 + uVar54 * 2);
    *(int *)(&DAT_0012be70 + uVar54 * 4) =
         *(int *)(&DAT_0012be70 + uVar54 * 4) * (int)*(short *)(&DAT_0012c2f0 + uVar54 * 2);
    bVar15 = 0 < (long)uVar54;
    uVar54 = uVar54 - 1;
  } while (bVar15);
  encode_pulses(&DAT_0012be70,param_2,param_3,param_6);
  if (param_5 < 2) {
    uVar54 = 1;
  }
  else {
    iVar18 = 0;
    if (param_5 != 0) {
      iVar18 = (int)param_2 / param_5;
    }
    lVar34 = (long)iVar18;
    lVar40 = (long)param_5;
    pauVar39 = (undefined1 (*) [16])((long)iVar18 * (long)param_5 * 4 + 0x12be60);
    lVar37 = -1;
    if (-1 < -lVar34) {
      lVar37 = -lVar34;
    }
    uVar32 = lVar37 + lVar34 + 1;
    lVar37 = (lVar40 + -1) * lVar34 * 4 + 0x12b0ec;
    uVar44 = uVar32 & 0xfffffffffffffff8;
    uVar54 = 0;
    do {
      lVar40 = lVar40 + -1;
      uVar25 = (uint)lVar40;
      lVar47 = lVar34;
      if (uVar32 < 8) {
LAB_00112cb0:
        do {
          lVar48 = lVar47 + -1;
          uVar54 = (ulong)((uint)(*(int *)(lVar37 + lVar47 * 4 + 0xd80) != 0) <<
                           (ulong)(uVar25 & 0x1f) | (uint)uVar54);
          lVar47 = lVar48;
        } while (0 < lVar48);
      }
      else {
        uVar55 = (undefined1)lVar40;
        uVar56 = (undefined1)((ulong)lVar40 >> 8);
        uVar58 = (undefined1)((ulong)lVar40 >> 0x10);
        uVar59 = (undefined1)((ulong)lVar40 >> 0x18);
        auVar74._8_8_ = 0;
        auVar74._0_8_ = uVar54;
        uVar76 = 0;
        uVar88 = 0;
        uVar54 = uVar44;
        pauVar49 = pauVar39;
        do {
          pauVar1 = pauVar49 + -1;
          auVar98 = *pauVar49;
          uVar54 = uVar54 - 8;
          pauVar49 = pauVar49 + -2;
          auVar98 = NEON_rev64(auVar98,4);
          auVar100 = NEON_rev64(*pauVar1,4);
          auVar98 = NEON_ext(auVar98,auVar98,8,1);
          auVar100 = NEON_ext(auVar100,auVar100,8,1);
          auVar99._0_5_ =
               CONCAT14(~-(auVar98._4_4_ == 0),(uint)(~-(auVar98._0_4_ == 0) & 1)) & 0x1ffffffff;
          auVar99._5_3_ = 0;
          auVar99[8] = ~-(auVar98._8_4_ == 0) & 1;
          auVar99._9_3_ = 0;
          auVar99[0xc] = ~-(auVar98._12_4_ == 0) & 1;
          auVar99._13_3_ = 0;
          auVar101._0_5_ =
               CONCAT14(~-(auVar100._4_4_ == 0),(uint)(~-(auVar100._0_4_ == 0) & 1)) & 0x1ffffffff;
          auVar101._5_3_ = 0;
          auVar101[8] = ~-(auVar100._8_4_ == 0) & 1;
          auVar101._9_3_ = 0;
          auVar101[0xc] = ~-(auVar100._12_4_ == 0) & 1;
          auVar101._13_3_ = 0;
          auVar98[4] = uVar55;
          auVar98._0_4_ = uVar25;
          auVar98[5] = uVar56;
          auVar98[6] = uVar58;
          auVar98[7] = uVar59;
          auVar98[8] = uVar55;
          auVar98[9] = uVar56;
          auVar98[10] = uVar58;
          auVar98[0xb] = uVar59;
          auVar98[0xc] = uVar55;
          auVar98[0xd] = uVar56;
          auVar98[0xe] = uVar58;
          auVar98[0xf] = uVar59;
          auVar98 = NEON_ushl(auVar99,auVar98,4);
          auVar100[4] = uVar55;
          auVar100._0_4_ = uVar25;
          auVar100[5] = uVar56;
          auVar100[6] = uVar58;
          auVar100[7] = uVar59;
          auVar100[8] = uVar55;
          auVar100[9] = uVar56;
          auVar100[10] = uVar58;
          auVar100[0xb] = uVar59;
          auVar100[0xc] = uVar55;
          auVar100[0xd] = uVar56;
          auVar100[0xe] = uVar58;
          auVar100[0xf] = uVar59;
          auVar100 = NEON_ushl(auVar101,auVar100,4);
          auVar73[0] = auVar98[0] | auVar74[0];
          auVar73[1] = auVar98[1] | auVar74[1];
          auVar73[2] = auVar98[2] | auVar74[2];
          auVar73[3] = auVar98[3] | auVar74[3];
          auVar73[4] = auVar98[4] | auVar74[4];
          auVar73[5] = auVar98[5] | auVar74[5];
          auVar73[6] = auVar98[6] | auVar74[6];
          auVar73[7] = auVar98[7] | auVar74[7];
          auVar73[8] = auVar98[8] | auVar74[8];
          auVar73[9] = auVar98[9] | auVar74[9];
          auVar73[10] = auVar98[10] | auVar74[10];
          auVar73[0xb] = auVar98[0xb] | auVar74[0xb];
          auVar73[0xc] = auVar98[0xc] | auVar74[0xc];
          auVar73[0xd] = auVar98[0xd] | auVar74[0xd];
          auVar73[0xe] = auVar98[0xe] | auVar74[0xe];
          auVar73[0xf] = auVar98[0xf] | auVar74[0xf];
          bVar75 = auVar100[0] | (byte)uVar76;
          bVar77 = auVar100[1] | (byte)((ulong)uVar76 >> 8);
          bVar78 = auVar100[2] | (byte)((ulong)uVar76 >> 0x10);
          bVar79 = auVar100[3] | (byte)((ulong)uVar76 >> 0x18);
          bVar80 = auVar100[4] | (byte)((ulong)uVar76 >> 0x20);
          bVar82 = auVar100[5] | (byte)((ulong)uVar76 >> 0x28);
          bVar83 = auVar100[6] | (byte)((ulong)uVar76 >> 0x30);
          bVar84 = auVar100[7] | (byte)((ulong)uVar76 >> 0x38);
          uVar76 = CONCAT17(bVar84,CONCAT16(bVar83,CONCAT15(bVar82,CONCAT14(bVar80,CONCAT13(bVar79,
                                                  CONCAT12(bVar78,CONCAT11(bVar77,bVar75)))))));
          bVar85 = auVar100[8] | (byte)uVar88;
          bVar89 = auVar100[9] | (byte)((ulong)uVar88 >> 8);
          bVar90 = auVar100[10] | (byte)((ulong)uVar88 >> 0x10);
          bVar91 = auVar100[0xb] | (byte)((ulong)uVar88 >> 0x18);
          bVar92 = auVar100[0xc] | (byte)((ulong)uVar88 >> 0x20);
          bVar95 = auVar100[0xd] | (byte)((ulong)uVar88 >> 0x28);
          bVar96 = auVar100[0xe] | (byte)((ulong)uVar88 >> 0x30);
          bVar97 = auVar100[0xf] | (byte)((ulong)uVar88 >> 0x38);
          uVar88 = CONCAT17(bVar97,CONCAT16(bVar96,CONCAT15(bVar95,CONCAT14(bVar92,CONCAT13(bVar91,
                                                  CONCAT12(bVar90,CONCAT11(bVar89,bVar85)))))));
          auVar74 = auVar73;
        } while (uVar54 != 0);
        bVar75 = bVar75 | auVar73[0];
        bVar77 = bVar77 | auVar73[1];
        bVar78 = bVar78 | auVar73[2];
        bVar79 = bVar79 | auVar73[3];
        bVar80 = bVar80 | auVar73[4];
        bVar82 = bVar82 | auVar73[5];
        bVar83 = bVar83 | auVar73[6];
        bVar84 = bVar84 | auVar73[7];
        auVar10[8] = 1;
        auVar10._0_8_ = 0x100000001;
        auVar10._9_3_ = 0;
        auVar10[0xc] = 1;
        auVar10._13_3_ = 0;
        auVar11[1] = bVar77;
        auVar11[0] = bVar75;
        auVar11[2] = bVar78;
        auVar11[3] = bVar79;
        auVar11[4] = bVar80;
        auVar11[5] = bVar82;
        auVar11[6] = bVar83;
        auVar11[7] = bVar84;
        auVar11[8] = bVar85 | auVar73[8];
        auVar11[9] = bVar89 | auVar73[9];
        auVar11[10] = bVar90 | auVar73[10];
        auVar11[0xb] = bVar91 | auVar73[0xb];
        auVar11[0xc] = bVar92 | auVar73[0xc];
        auVar11[0xd] = bVar95 | auVar73[0xd];
        auVar11[0xe] = bVar96 | auVar73[0xe];
        auVar11[0xf] = bVar97 | auVar73[0xf];
        auVar74 = NEON_ext(auVar11,auVar10,8,1);
        uVar54 = (ulong)CONCAT13(bVar79 | auVar74[3] | bVar84 | auVar74[7],
                                 CONCAT12(bVar78 | auVar74[2] | bVar83 | auVar74[6],
                                          CONCAT11(bVar77 | auVar74[1] | bVar82 | auVar74[5],
                                                   bVar75 | auVar74[0] | bVar80 | auVar74[4])));
        lVar47 = lVar34 - uVar44;
        if (uVar32 != uVar44) goto LAB_00112cb0;
      }
      pauVar39 = (undefined1 (*) [16])((long)pauVar39 + (long)iVar18 * -4);
      lVar37 = lVar37 + (long)iVar18 * -4;
    } while (0 < lVar40);
  }
  return uVar54;
}


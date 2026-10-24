/* ssc_alg_quant @ 0011571c size 3640 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulong ssc_alg_quant(undefined1 param_1 [16],undefined1 param_2 [16],undefined1 param_3 [16],
                   short *param_4,uint param_5,int param_6,int param_7,uint param_8,
                   undefined8 param_9)

{
  bool bVar1;
  undefined1 (*pauVar2) [16];
  short *psVar3;
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  int iVar8;
  undefined4 uVar9;
  short extraout_var;
  uint uVar10;
  short *psVar11;
  ulong uVar12;
  undefined1 (*pauVar13) [16];
  ulong uVar14;
  ulong uVar15;
  short *psVar16;
  short *psVar17;
  short *psVar18;
  long lVar19;
  ulong uVar20;
  long lVar21;
  ulong uVar22;
  ulong uVar23;
  short *psVar24;
  ulong uVar25;
  short *psVar26;
  long lVar27;
  undefined8 *puVar28;
  long lVar29;
  undefined2 *puVar30;
  undefined8 *puVar31;
  undefined1 (*pauVar32) [16];
  short *psVar33;
  ulong uVar34;
  ulong uVar35;
  long lVar36;
  uint uVar37;
  long lVar38;
  ulong uVar39;
  short *psVar40;
  long lVar41;
  long lVar42;
  long lVar43;
  short sVar44;
  short sVar45;
  short sVar46;
  short sVar47;
  short sVar48;
  short sVar49;
  uint uVar50;
  uint uVar51;
  uint uVar52;
  uint uVar53;
  undefined8 uVar54;
  int iVar56;
  undefined8 uVar55;
  int iVar57;
  undefined8 uVar58;
  int iVar59;
  int iVar60;
  undefined1 uVar61;
  byte bVar62;
  undefined1 uVar63;
  byte bVar64;
  char cVar65;
  undefined1 uVar66;
  byte bVar67;
  undefined1 uVar68;
  byte bVar69;
  undefined1 uVar70;
  byte bVar71;
  undefined1 uVar72;
  byte bVar73;
  char cVar74;
  undefined1 uVar75;
  byte bVar76;
  undefined1 uVar77;
  byte bVar78;
  undefined1 uVar79;
  byte bVar80;
  undefined1 uVar81;
  byte bVar82;
  undefined1 uVar83;
  byte bVar84;
  undefined1 uVar85;
  byte bVar86;
  undefined1 uVar87;
  byte bVar88;
  undefined1 uVar89;
  byte bVar90;
  undefined1 uVar91;
  byte bVar92;
  undefined1 uVar93;
  byte bVar94;
  byte bVar95;
  int iVar96;
  byte bVar98;
  byte bVar99;
  byte bVar101;
  int iVar102;
  byte bVar103;
  byte bVar104;
  byte bVar106;
  int iVar107;
  byte bVar108;
  byte bVar109;
  byte bVar111;
  byte bVar113;
  byte bVar114;
  byte bVar100;
  byte bVar105;
  byte bVar110;
  int iVar112;
  byte bVar115;
  undefined1 auVar97 [16];
  short sVar116;
  undefined2 uVar117;
  int iVar118;
  undefined8 uVar119;
  short sVar122;
  undefined1 auVar120 [16];
  undefined1 auVar121 [16];
  uint uVar125;
  uint uVar126;
  uint uVar127;
  undefined1 auVar123 [16];
  undefined1 auVar124 [16];
  int iVar128;
  int iVar129;
  int iVar130;
  int iVar131;
  
  if ((param_6 * 2 < (int)param_5) && (param_7 != 0)) {
    iVar8 = ssc_rcp(param_5 + *(int *)("enc->nbits_total = %d\n" + (long)param_7 * 4 + 0x14) *
                              param_6);
    iVar8 = (int)((ulong)((long)iVar8 *
                         (long)(int)((-(param_5 >> 0xf & 1) & 0x80000000 | (param_5 & 0xffff) << 0xf
                                     ) - (int)(short)param_5)) >> 0xf) >> 0x10;
    uVar37 = (uint)(iVar8 * iVar8) >> 0x10;
    uVar9 = ssc_cos_norm(uVar37);
    iVar8 = ssc_cos_norm(uVar37 ^ 0x7fff);
    if ((int)param_5 < (int)(param_8 * 8)) {
      iVar56 = 0;
      if (param_8 != 0) {
        iVar56 = (int)param_5 / (int)param_8;
      }
      iVar57 = param_8 - 1;
      if (iVar57 != 0) {
        psVar18 = param_4 + (long)iVar56 * (long)iVar57;
        do {
          FUN_001167d0(psVar18,iVar56,uVar9,-iVar8);
          iVar57 = iVar57 + -1;
          psVar18 = psVar18 + -(long)iVar56;
        } while (iVar57 != 0);
      }
      FUN_001167d0(param_4,iVar56,uVar9,-iVar8);
    }
    else {
      uVar34 = 1;
      psVar18 = param_4;
      iVar56 = -3;
      iVar57 = -2;
      psVar26 = param_4;
      do {
        iVar96 = iVar57;
        iVar60 = iVar56;
        psVar33 = psVar18;
        uVar12 = uVar34;
        psVar26 = psVar26 + 1;
        uVar37 = (uint)uVar12;
        psVar18 = psVar33 + 1;
        uVar34 = uVar12 + 1;
        iVar56 = iVar60 + -2;
        iVar57 = iVar96 + -1;
      } while ((int)(((int)param_8 >> 2) + (uVar37 + uVar37 * uVar37) * param_8) < (int)param_5);
      uVar10 = 0;
      if (param_8 != 0) {
        uVar10 = (int)param_5 / (int)param_8;
      }
      uVar20 = (ulong)uVar10;
      iVar57 = (int)(short)iVar8;
      sVar116 = -(short)uVar9;
      iVar102 = (int)sVar116;
      uVar125 = uVar10 + ~uVar37;
      uVar39 = (ulong)uVar125;
      uVar34 = uVar12 & 0xffffffff;
      uVar37 = (uVar37 << 1 ^ 0xffffffff) + uVar10;
      uVar35 = (ulong)uVar37;
      iVar56 = param_8 - 1;
      if (iVar56 != 0) {
        lVar42 = (long)iVar56;
        lVar27 = 0;
        lVar38 = (long)(int)uVar10 * (long)iVar56;
        lVar21 = uVar34 + (long)(int)uVar10 * (long)iVar56;
        lVar43 = lVar38 * 2;
        lVar36 = uVar35 + (long)(int)uVar10 * (long)iVar56;
        psVar40 = param_4 + lVar38;
        uVar22 = uVar39 + 1 & 0x1fffffff8;
        uVar14 = uVar35 + 1 & 0x1fffffffe;
        uVar15 = -(ulong)(uVar10 >> 0x1f) & 0xfffffffe00000000 | uVar20 << 1;
        uVar23 = (ulong)(uVar10 + iVar60);
        lVar19 = -uVar15;
        psVar11 = psVar40 + (uVar23 - 1);
        do {
          lVar41 = lVar27 * (int)uVar10;
          psVar17 = param_4 + lVar42 * (int)uVar10;
          FUN_001167d0(psVar17,uVar20,uVar9,-iVar8);
          if (-1 < (int)uVar125) {
            psVar16 = psVar17;
            uVar126 = uVar125;
            if ((6 < uVar125) &&
               ((param_4 + ((uVar39 + (long)(int)uVar10 * (long)iVar56 + 1) - lVar41) <=
                 param_4 + (lVar21 - lVar41) ||
                (param_4 + ((lVar21 + uVar39 + 1) - lVar41) <= param_4 + (lVar38 - lVar41))))) {
              uVar25 = (ulong)(uVar10 + iVar96) + 1 & 0x1fffffff8;
              lVar29 = lVar43;
              psVar16 = psVar40;
              do {
                uVar58 = ((undefined8 *)((long)psVar18 + lVar29))[1];
                uVar54 = *(undefined8 *)((long)psVar18 + lVar29);
                uVar25 = uVar25 - 8;
                uVar55 = *(undefined8 *)(psVar16 + 4);
                uVar119 = *(undefined8 *)psVar16;
                iVar128 = (int)(short)((ulong)uVar54 >> 0x10);
                iVar129 = (int)(short)((ulong)uVar54 >> 0x20);
                iVar130 = (int)(short)((ulong)uVar54 >> 0x30);
                sVar47 = (short)((ulong)uVar119 >> 0x10);
                iVar131 = (int)(short)((ulong)uVar119 >> 0x20);
                iVar118 = (int)(short)((ulong)uVar119 >> 0x30);
                iVar107 = (int)(short)((ulong)uVar58 >> 0x10);
                iVar112 = (int)(short)((ulong)uVar58 >> 0x20);
                iVar59 = (int)(short)((ulong)uVar58 >> 0x30);
                sVar44 = (short)uVar55;
                sVar45 = (short)((ulong)uVar55 >> 0x10);
                sVar48 = (short)((ulong)uVar55 >> 0x20);
                sVar46 = (short)((ulong)uVar55 >> 0x30);
                param_3._0_4_ =
                     iVar102 * CONCAT13(sVar44 >> 0xf,(int3)sVar44) + iVar57 * (short)uVar58;
                param_3._4_4_ = iVar102 * CONCAT13(sVar45 >> 0xf,(int3)sVar45) + iVar57 * iVar107;
                param_3._8_4_ = iVar102 * CONCAT13(sVar48 >> 0xf,(int3)sVar48) + iVar57 * iVar112;
                param_3._12_4_ = iVar102 * CONCAT13(sVar46 >> 0xf,(int3)sVar46) + iVar57 * iVar59;
                uVar126 = (uint)(iVar57 * sVar47 - iVar102 * iVar128) >> 0xf;
                uVar50 = (uint)(iVar57 * iVar131 - iVar102 * iVar129) >> 0xf;
                uVar52 = (uint)(iVar57 * iVar118 - iVar102 * iVar130) >> 0xf;
                uVar127 = (uint)(iVar57 * CONCAT13(sVar45 >> 0xf,(int3)sVar45) - iVar102 * iVar107)
                          >> 0xf;
                uVar51 = (uint)(iVar57 * CONCAT13(sVar48 >> 0xf,(int3)sVar48) - iVar102 * iVar112)
                         >> 0xf;
                uVar53 = (uint)(iVar57 * CONCAT13(sVar46 >> 0xf,(int3)sVar46) - iVar102 * iVar59) >>
                         0xf;
                ((undefined8 *)((long)psVar18 + lVar29))[1] =
                     CONCAT26((short)(param_3._12_4_ >> 0xf),
                              CONCAT24((short)(param_3._8_4_ >> 0xf),
                                       CONCAT22((short)(param_3._4_4_ >> 0xf),
                                                (short)(param_3._0_4_ >> 0xf))));
                *(undefined8 *)((long)psVar18 + lVar29) =
                     CONCAT26((short)((uint)(iVar102 * iVar118 + iVar57 * iVar130) >> 0xf),
                              CONCAT24((short)((uint)(iVar102 * iVar131 + iVar57 * iVar129) >> 0xf),
                                       CONCAT22((short)((uint)(iVar102 * sVar47 + iVar57 * iVar128)
                                                       >> 0xf),
                                                (short)((uint)(iVar102 * (short)uVar119 +
                                                              iVar57 * (short)uVar54) >> 0xf))));
                lVar29 = lVar29 + 0x10;
                *(ulong *)(psVar16 + 4) =
                     CONCAT17((char)(uVar53 >> 8),
                              CONCAT16((char)uVar53,
                                       CONCAT15((char)(uVar51 >> 8),
                                                CONCAT14((char)uVar51,
                                                         CONCAT13((char)(uVar127 >> 8),
                                                                  CONCAT12((char)uVar127,
                                                                           (short)((uint)(iVar57 * 
                                                  CONCAT13(sVar44 >> 0xf,(int3)sVar44) -
                                                  iVar102 * (short)uVar58) >> 0xf)))))));
                *(ulong *)psVar16 =
                     CONCAT17((char)(uVar52 >> 8),
                              CONCAT16((char)uVar52,
                                       CONCAT15((char)(uVar50 >> 8),
                                                CONCAT14((char)uVar50,
                                                         CONCAT13((char)(uVar126 >> 8),
                                                                  CONCAT12((char)uVar126,
                                                                           (short)((uint)(iVar57 * (
                                                  short)uVar119 - iVar102 * (short)uVar54) >> 0xf)))
                                                  ))));
                psVar16 = psVar16 + 8;
              } while (uVar25 != 0);
              psVar16 = psVar17 + uVar22;
              uVar126 = uVar125 - (int)uVar22;
              if (uVar39 + 1 == uVar22) goto LAB_00115b44;
            }
            iVar107 = uVar126 + 1;
            psVar24 = psVar16 + uVar12;
            do {
              sVar44 = *psVar16;
              iVar107 = iVar107 + -1;
              sVar47 = *psVar24;
              *psVar24 = (short)((uint)(sVar44 * iVar102 + sVar47 * iVar57) >> 0xf);
              *psVar16 = (short)((uint)(sVar44 * iVar57 - sVar47 * iVar102) >> 0xf);
              psVar16 = psVar16 + 1;
              psVar24 = psVar24 + 1;
            } while (iVar107 != 0);
          }
LAB_00115b44:
          if (-1 < (int)uVar37) {
            psVar17 = psVar17 + uVar35;
            uVar126 = uVar37;
            if ((((uVar37 != 0) &&
                 (param_4 + ((lVar21 + uVar35) - lVar41) + -uVar35 <=
                  param_4 + ((lVar21 + uVar35) - lVar41))) &&
                (param_4 + (lVar36 - lVar41) + -uVar35 <= param_4 + (lVar36 - lVar41))) &&
               ((param_4 + ((lVar36 + 1) - lVar41) <= param_4 + (lVar21 - lVar41) ||
                (param_4 + ((lVar21 + uVar35 + 1) - lVar41) <= param_4 + (lVar38 - lVar41))))) {
              psVar17 = psVar17 + -uVar14;
              uVar25 = uVar23 + 1 & 0x1fffffffe;
              psVar16 = psVar33 + uVar23;
              psVar24 = psVar11;
              do {
                psVar3 = (short *)((long)psVar16 + lVar43);
                psVar16 = psVar16 + -2;
                uVar25 = uVar25 - 2;
                sVar44 = psVar24[1];
                sVar47 = *psVar24;
                cVar65 = (char)(sVar44 >> 0xf);
                cVar74 = (char)(sVar47 >> 0xf);
                uVar127 = iVar102 * CONCAT13(cVar65,CONCAT12(cVar65,sVar44)) + iVar57 * psVar3[1];
                uVar50 = iVar102 * CONCAT13(cVar74,CONCAT12(cVar74,sVar47)) + iVar57 * *psVar3;
                param_3._0_4_ =
                     iVar57 * CONCAT13(cVar65,CONCAT12(cVar65,sVar44)) - iVar102 * psVar3[1];
                param_3._4_4_ =
                     iVar57 * CONCAT13(cVar74,CONCAT12(cVar74,sVar47)) - iVar102 * *psVar3;
                param_3._8_8_ = 0;
                uVar126 = uVar50 >> 0xf;
                uVar119 = NEON_rev64((ulong)CONCAT16((byte)(uVar50 >> 0x1f),
                                                     CONCAT15((char)(uVar126 >> 8),
                                                              CONCAT14((char)uVar126,
                                                                       (uint)CONCAT12((byte)(uVar127
                                                                                            >> 0x1f)
                                                                                      ,(short)(
                                                  uVar127 >> 0xf))))),4);
                uVar55 = NEON_rev64(CONCAT44(param_3._4_4_ >> 0xf,param_3._0_4_ >> 0xf),4);
                *psVar24 = (short)uVar55;
                psVar24[1] = (short)((ulong)uVar55 >> 0x20);
                psVar24 = psVar24 + -2;
                psVar3[1] = (short)((ulong)uVar119 >> 0x20);
                *psVar3 = (short)uVar119;
              } while (uVar25 != 0);
              uVar126 = uVar37 - (int)uVar14;
              if (uVar35 + 1 == uVar14) goto LAB_001159d0;
            }
            iVar107 = uVar126 + 1;
            psVar16 = psVar17 + uVar12;
            do {
              sVar44 = *psVar17;
              iVar107 = iVar107 + -1;
              sVar47 = *psVar16;
              *psVar16 = (short)((uint)(sVar44 * iVar102 + sVar47 * iVar57) >> 0xf);
              *psVar17 = (short)((uint)(sVar44 * iVar57 - sVar47 * iVar102) >> 0xf);
              psVar17 = psVar17 + -1;
              psVar16 = psVar16 + -1;
            } while (iVar107 != 0);
          }
LAB_001159d0:
          lVar42 = lVar42 + -1;
          lVar27 = lVar27 + 1;
          psVar40 = (short *)((long)psVar40 + lVar19);
          psVar11 = (short *)((long)psVar11 + lVar19);
          lVar43 = lVar43 - uVar15;
        } while ((int)lVar42 != 0);
      }
      FUN_001167d0(param_4,uVar20,uVar9,-iVar8);
      cVar65 = (char)(sVar116 >> 0xf);
      if (-1 < (int)uVar125) {
        psVar18 = param_4;
        if ((6 < uVar125) &&
           ((param_4 + uVar39 + 1 <= param_4 + uVar34 || (param_4 + uVar34 + uVar39 + 1 <= param_4))
           )) {
          uVar14 = uVar39 + 1 & 0x1fffffff8;
          uVar125 = uVar125 - (int)uVar14;
          uVar20 = (ulong)(uVar10 + iVar96) + 1 & 0x1fffffff8;
          do {
            sVar44 = *psVar26;
            sVar47 = psVar26[1];
            sVar45 = psVar26[2];
            sVar48 = psVar26[3];
            uVar20 = uVar20 - 8;
            uVar54 = *(undefined8 *)(psVar18 + 4);
            uVar55 = *(undefined8 *)psVar18;
            iVar96 = (int)(short)((ulong)uVar55 >> 0x10);
            iVar107 = (int)(short)((ulong)uVar55 >> 0x20);
            iVar112 = (int)(short)((ulong)uVar55 >> 0x30);
            sVar46 = (short)((ulong)uVar54 >> 0x10);
            iVar8 = (int)(short)((ulong)uVar54 >> 0x20);
            iVar56 = (int)(short)((ulong)uVar54 >> 0x30);
            param_3._0_8_ =
                 CONCAT26((short)((uint)(CONCAT13(cVar65,(int3)sVar116) * iVar112 + iVar57 * sVar48)
                                 >> 0xf),
                          CONCAT24((short)((uint)(CONCAT13(cVar65,(int3)sVar116) * iVar107 +
                                                 iVar57 * sVar45) >> 0xf),
                                   CONCAT22((short)((uint)(CONCAT13(cVar65,(int3)sVar116) * iVar96 +
                                                          iVar57 * sVar47) >> 0xf),
                                            (short)((uint)(CONCAT13(cVar65,(int3)sVar116) *
                                                           (int)(short)uVar55 + iVar57 * sVar44) >>
                                                   0xf))));
            uVar119 = CONCAT26((short)((uint)(CONCAT13(cVar65,(int3)sVar116) * iVar56 +
                                             iVar57 * psVar26[7]) >> 0xf),
                               CONCAT24((short)((uint)(CONCAT13(cVar65,(int3)sVar116) * iVar8 +
                                                      iVar57 * psVar26[6]) >> 0xf),
                                        CONCAT22((short)((uint)(CONCAT13(cVar65,(int3)sVar116) *
                                                                (int)sVar46 + iVar57 * psVar26[5])
                                                        >> 0xf),
                                                 (short)((uint)(CONCAT13(cVar65,(int3)sVar116) *
                                                                (int)(short)uVar54 +
                                                               iVar57 * psVar26[4]) >> 0xf))));
            param_3._8_8_ = uVar119;
            uVar9 = CONCAT22((short)((uint)(iVar57 * sVar46 -
                                           CONCAT13(cVar65,(int3)sVar116) * (int)psVar26[5]) >> 0xf)
                             ,(short)((uint)(iVar57 * (short)uVar54 -
                                            CONCAT13(cVar65,(int3)sVar116) * (int)psVar26[4]) >> 0xf
                                     ));
            *(undefined8 *)(psVar26 + 4) = uVar119;
            *(ulong *)psVar26 = param_3._0_8_;
            *(ulong *)(psVar18 + 4) =
                 CONCAT44((int)(CONCAT26((short)((uint)(iVar57 * iVar56 -
                                                       CONCAT13(cVar65,(int3)sVar116) *
                                                       (int)psVar26[7]) >> 0xf),
                                         CONCAT24((short)((uint)(iVar57 * iVar8 -
                                                                CONCAT13(cVar65,(int3)sVar116) *
                                                                (int)psVar26[6]) >> 0xf),uVar9)) >>
                               0x20),uVar9);
            *(ulong *)psVar18 =
                 CONCAT26((short)((uint)(iVar57 * iVar112 -
                                        CONCAT13(cVar65,(int3)sVar116) * (int)sVar48) >> 0xf),
                          CONCAT24((short)((uint)(iVar57 * iVar107 -
                                                 CONCAT13(cVar65,(int3)sVar116) * (int)sVar45) >>
                                          0xf),
                                   CONCAT22((short)((uint)(iVar57 * iVar96 -
                                                          CONCAT13(cVar65,(int3)sVar116) *
                                                          (int)sVar47) >> 0xf),
                                            (short)((uint)(iVar57 * (short)uVar55 -
                                                          CONCAT13(cVar65,(int3)sVar116) *
                                                          (int)sVar44) >> 0xf))));
            psVar18 = psVar18 + 8;
            psVar26 = psVar26 + 8;
          } while (uVar20 != 0);
          psVar18 = param_4 + uVar14;
          if (uVar39 + 1 == uVar14) goto LAB_00115de4;
        }
        iVar8 = uVar125 + 1;
        psVar26 = psVar18 + uVar12;
        do {
          sVar44 = *psVar18;
          iVar8 = iVar8 + -1;
          sVar47 = *psVar26;
          *psVar26 = (short)((uint)(sVar44 * iVar102 + sVar47 * iVar57) >> 0xf);
          *psVar18 = (short)((uint)(sVar44 * iVar57 - sVar47 * iVar102) >> 0xf);
          psVar18 = psVar18 + 1;
          psVar26 = psVar26 + 1;
        } while (iVar8 != 0);
      }
LAB_00115de4:
      if (-1 < (int)uVar37) {
        psVar18 = param_4 + uVar35;
        if ((((uVar37 != 0) && (param_4 + uVar34 + uVar35 + -uVar35 <= param_4 + uVar34 + uVar35))
            && (psVar26 = psVar18 + -uVar35, psVar26 <= psVar18)) &&
           ((param_4 + uVar35 + 1 <= param_4 + uVar34 || (param_4 + uVar34 + uVar35 + 1 <= param_4))
           )) {
          uVar34 = (ulong)(uVar10 + iVar60);
          uVar20 = uVar35 + 1 & 0x1fffffffe;
          uVar37 = uVar37 - (int)uVar20;
          psVar18 = psVar18 + -uVar20;
          psVar26 = psVar26 + (uVar34 - 1);
          psVar33 = psVar33 + uVar34;
          uVar34 = uVar34 + 1 & 0x1fffffffe;
          do {
            uVar34 = uVar34 - 2;
            uVar10 = iVar57 * psVar26[1] - CONCAT13(cVar65,(int3)sVar116) * (int)psVar33[1];
            uVar125 = iVar57 * *psVar26 - CONCAT13(cVar65,(int3)sVar116) * (int)*psVar33;
            param_3._0_8_ =
                 NEON_rev64(CONCAT44((uint)(CONCAT13(cVar65,(int3)sVar116) * (int)*psVar26 +
                                           iVar57 * *psVar33) >> 0xf,
                                     (uint)(CONCAT13(cVar65,(int3)sVar116) * (int)psVar26[1] +
                                           iVar57 * psVar33[1]) >> 0xf),4);
            param_3._8_8_ = 0;
            uVar119 = NEON_rev64(CONCAT26((ushort)(uVar125 >> 0x1f),
                                          CONCAT24((short)(uVar125 >> 0xf),
                                                   CONCAT22((ushort)(uVar10 >> 0x1f),
                                                            (short)(uVar10 >> 0xf)))),4);
            *psVar33 = (short)param_3._0_8_;
            psVar33[1] = (short)(param_3._0_8_ >> 0x20);
            psVar33 = psVar33 + -2;
            *psVar26 = (short)uVar119;
            psVar26[1] = (short)((ulong)uVar119 >> 0x20);
            psVar26 = psVar26 + -2;
          } while (uVar34 != 0);
          if (uVar35 + 1 == uVar20) goto LAB_00115f4c;
        }
        iVar8 = uVar37 + 1;
        psVar26 = psVar18 + uVar12;
        do {
          sVar116 = *psVar18;
          iVar8 = iVar8 + -1;
          sVar44 = *psVar26;
          *psVar26 = (short)((uint)(sVar116 * iVar102 + sVar44 * iVar57) >> 0xf);
          *psVar18 = (short)((uint)(sVar116 * iVar57 - sVar44 * iVar102) >> 0xf);
          psVar18 = psVar18 + -1;
          psVar26 = psVar26 + -1;
        } while (iVar8 != 0);
      }
    }
  }
LAB_00115f4c:
  lVar19 = (long)(int)(param_5 - 1);
  puVar30 = (undefined2 *)(&DAT_00124fec + (long)(int)(param_5 - 1) * 2);
  lVar27 = lVar19;
  do {
    if (param_4[lVar27] < 1) {
      puVar30[0x120] = 0xffff;
      param_4[lVar27] = -param_4[lVar27];
    }
    else {
      puVar30[0x120] = 1;
    }
    *puVar30 = 0;
    *(undefined4 *)(&DAT_00124dac + lVar27 * 4) = 0;
    bVar1 = 0 < lVar27;
    puVar30 = puVar30 + -1;
    lVar27 = lVar27 + -1;
  } while (bVar1);
  if ((int)param_5 >> 1 < param_6) {
    uVar34 = lVar19 + 1;
    if (uVar34 < 4) {
      iVar8 = 0;
      lVar27 = lVar19;
LAB_00116050:
      do {
        psVar18 = param_4 + lVar27;
        lVar27 = lVar27 + -1;
        iVar8 = iVar8 + *psVar18;
      } while (lVar27 != -1);
    }
    else {
      uVar20 = uVar34 & 0xfffffffffffffffc;
      iVar8 = 0;
      iVar56 = 0;
      lVar27 = lVar19 - uVar20;
      uVar61 = 0;
      uVar63 = 0;
      uVar66 = 0;
      uVar68 = 0;
      uVar70 = 0;
      uVar72 = 0;
      uVar75 = 0;
      uVar77 = 0;
      psVar18 = param_4 + lVar19 + -1;
      uVar12 = uVar20;
      do {
        psVar33 = psVar18 + -1;
        uVar12 = uVar12 - 4;
        auVar120._2_14_ = param_3._2_14_;
        auVar120._0_2_ = psVar18[1];
        psVar26 = psVar18 + -2;
        auVar123._6_10_ = param_3._6_10_;
        auVar123._0_4_ = auVar120._0_4_;
        auVar123._4_2_ = *psVar18;
        psVar18 = psVar18 + -4;
        param_3._0_4_ = auVar123._0_4_ << 0x10;
        param_3._4_4_ = auVar123._4_4_ << 0x10;
        param_3._8_8_ = 0;
        iVar8 = iVar8 + ((int)param_3._0_4_ >> 0x10);
        iVar56 = iVar56 + ((int)param_3._4_4_ >> 0x10);
        iVar57 = CONCAT13(uVar68,CONCAT12(uVar66,CONCAT11(uVar63,uVar61))) + (int)*psVar33;
        uVar61 = (undefined1)iVar57;
        uVar63 = (undefined1)((uint)iVar57 >> 8);
        uVar66 = (undefined1)((uint)iVar57 >> 0x10);
        uVar68 = (undefined1)((uint)iVar57 >> 0x18);
        iVar60 = CONCAT13(uVar77,CONCAT12(uVar75,CONCAT11(uVar72,uVar70))) + (int)*psVar26;
        uVar70 = (undefined1)iVar60;
        uVar72 = (undefined1)((uint)iVar60 >> 8);
        uVar75 = (undefined1)((uint)iVar60 >> 0x10);
        uVar77 = (undefined1)((uint)iVar60 >> 0x18);
      } while (uVar12 != 0);
      iVar8 = iVar57 + iVar8 + iVar60 + iVar56;
      if (uVar34 != uVar20) goto LAB_00116050;
    }
    if (iVar8 <= param_6) {
      iVar8 = 0x4000;
      *param_4 = 0x4000;
      memset(param_4 + (lVar19 - (ulong)(param_5 - 2)),0,(ulong)(param_5 - 2) * 2 + 2);
    }
    sVar116 = (short)param_6 + -1;
    ssc_rcp(iVar8);
    uVar10 = ssc_rcp(iVar8);
    uVar37 = param_5 + 3;
    if (-1 < (int)param_5) {
      uVar37 = param_5;
    }
    sVar116 = extraout_var * sVar116 + (short)((uVar10 & 0xffff) * (int)sVar116 >> 0x10);
    if ((int)(uVar37 & 0xfffffffc) < 1) {
      uVar61 = 0;
      uVar63 = 0;
      uVar66 = 0;
      uVar68 = 0;
      uVar70 = 0;
      uVar72 = 0;
      uVar75 = 0;
      uVar77 = 0;
      uVar79 = 0;
      uVar81 = 0;
      uVar83 = 0;
      uVar85 = 0;
      uVar87 = 0;
      uVar89 = 0;
      uVar91 = 0;
      uVar93 = 0;
      uVar34 = 0;
      iVar96 = 0;
      iVar102 = 0;
      iVar107 = 0;
      iVar112 = 0;
      iVar8 = 0;
      iVar56 = 0;
      iVar57 = 0;
      iVar60 = 0;
    }
    else {
      iVar8 = 0;
      iVar56 = 0;
      iVar57 = 0;
      iVar60 = 0;
      uVar34 = 0;
      iVar96 = 0;
      iVar102 = 0;
      iVar107 = 0;
      iVar112 = 0;
      uVar61 = 0;
      uVar63 = 0;
      uVar66 = 0;
      uVar68 = 0;
      uVar70 = 0;
      uVar72 = 0;
      uVar75 = 0;
      uVar77 = 0;
      uVar79 = 0;
      uVar81 = 0;
      uVar83 = 0;
      uVar85 = 0;
      uVar87 = 0;
      uVar89 = 0;
      uVar91 = 0;
      uVar93 = 0;
      puVar28 = (undefined8 *)&DAT_00124fec;
      puVar31 = (undefined8 *)&DAT_00124dac;
      psVar18 = param_4;
      do {
        uVar119 = *(undefined8 *)psVar18;
        uVar34 = uVar34 + 4;
        sVar46 = (short)((ulong)uVar119 >> 0x10);
        sVar49 = (short)((ulong)uVar119 >> 0x20);
        sVar122 = (short)((ulong)uVar119 >> 0x30);
        iVar59 = (int)sVar116;
        uVar10 = (short)uVar119 * iVar59;
        uVar125 = sVar46 * iVar59;
        uVar126 = sVar49 * iVar59;
        uVar127 = sVar122 * iVar59;
        sVar44 = (short)(uVar10 >> 0xf);
        sVar47 = (short)(uVar125 >> 0xf);
        sVar45 = (short)(uVar126 >> 0xf);
        sVar48 = (short)(uVar127 >> 0xf);
        iVar128 = (int)uVar10 >> 0xf;
        iVar129 = (int)uVar125 >> 0xf;
        iVar130 = (int)uVar126 >> 0xf;
        iVar131 = (int)uVar127 >> 0xf;
        iVar59 = CONCAT13(uVar68,CONCAT12(uVar66,CONCAT11(uVar63,uVar61))) + iVar128;
        uVar61 = (undefined1)iVar59;
        uVar63 = (undefined1)((uint)iVar59 >> 8);
        uVar66 = (undefined1)((uint)iVar59 >> 0x10);
        uVar68 = (undefined1)((uint)iVar59 >> 0x18);
        iVar59 = CONCAT13(uVar77,CONCAT12(uVar75,CONCAT11(uVar72,uVar70))) + iVar129;
        uVar70 = (undefined1)iVar59;
        uVar72 = (undefined1)((uint)iVar59 >> 8);
        uVar75 = (undefined1)((uint)iVar59 >> 0x10);
        uVar77 = (undefined1)((uint)iVar59 >> 0x18);
        iVar59 = CONCAT13(uVar85,CONCAT12(uVar83,CONCAT11(uVar81,uVar79))) + iVar130;
        uVar79 = (undefined1)iVar59;
        uVar81 = (undefined1)((uint)iVar59 >> 8);
        uVar83 = (undefined1)((uint)iVar59 >> 0x10);
        uVar85 = (undefined1)((uint)iVar59 >> 0x18);
        iVar59 = CONCAT13(uVar93,CONCAT12(uVar91,CONCAT11(uVar89,uVar87))) + iVar131;
        uVar87 = (undefined1)iVar59;
        uVar89 = (undefined1)((uint)iVar59 >> 8);
        uVar91 = (undefined1)((uint)iVar59 >> 0x10);
        uVar93 = (undefined1)((uint)iVar59 >> 0x18);
        iVar8 = iVar8 + (int)sVar44 * (int)sVar44;
        iVar56 = iVar56 + (int)sVar47 * (int)sVar47;
        iVar57 = iVar57 + (int)sVar45 * (int)sVar45;
        iVar60 = iVar60 + (int)sVar48 * (int)sVar48;
        iVar96 = iVar96 + (int)(short)uVar119 * (int)sVar44;
        iVar102 = iVar102 + (int)sVar46 * (int)sVar47;
        iVar107 = iVar107 + (int)sVar49 * (int)sVar45;
        iVar112 = iVar112 + (int)sVar122 * (int)sVar48;
        puVar31[1] = CONCAT44(iVar131,iVar130);
        *puVar31 = CONCAT44(iVar129,iVar128);
        *puVar28 = CONCAT26(sVar48 << 1,CONCAT24(sVar45 << 1,CONCAT22(sVar47 << 1,sVar44 << 1)));
        puVar28 = puVar28 + 1;
        puVar31 = puVar31 + 2;
        psVar18 = psVar18 + 4;
      } while (uVar34 < (uVar37 & 0xfffffffc));
    }
    iVar8 = iVar8 + iVar56 + iVar57 + iVar60;
    iVar56 = iVar96 + iVar102 + iVar107 + iVar112;
    iVar57 = param_6 - (CONCAT13(uVar68,CONCAT12(uVar66,CONCAT11(uVar63,uVar61))) +
                        CONCAT13(uVar77,CONCAT12(uVar75,CONCAT11(uVar72,uVar70))) +
                       CONCAT13(uVar85,CONCAT12(uVar83,CONCAT11(uVar81,uVar79))) +
                       CONCAT13(uVar93,CONCAT12(uVar91,CONCAT11(uVar89,uVar87))));
    if ((int)uVar34 < (int)param_5) {
      uVar34 = uVar34 & 0xffffffff;
      do {
        iVar96 = (int)sVar116 * (int)param_4[uVar34];
        iVar60 = iVar96 >> 0xf;
        iVar96 = iVar96 * 2 >> 0x10;
        iVar57 = iVar57 - iVar60;
        *(int *)(&DAT_00124dac + uVar34 * 4) = iVar60;
        *(short *)(&DAT_00124fec + uVar34 * 2) = (short)iVar60;
        uVar12 = uVar34 + 1;
        iVar8 = iVar96 * iVar96 + (int)(short)iVar8;
        iVar56 = iVar56 + iVar96 * param_4[uVar34];
        *(short *)(&DAT_00124fec + uVar34 * 2) = (short)(iVar60 << 1);
        uVar34 = uVar12;
      } while (param_5 != uVar12);
    }
  }
  else {
    iVar8 = 0;
    iVar56 = 0;
    iVar57 = param_6;
  }
  if ((int)(param_5 + 3) < iVar57) {
    _DAT_00124dac = _DAT_00124dac + iVar57;
  }
  else if (0 < iVar57) {
    iVar60 = 0;
    uVar37 = param_5;
    if ((int)param_5 < 2) {
      uVar37 = 1;
    }
    do {
      iVar60 = iVar60 + 1;
      uVar34 = 0;
      iVar96 = 0;
      uVar12 = 0;
      uVar10 = 0xffff8001;
      do {
        iVar102 = (uint)*(ushort *)(&DAT_00124fec + uVar34 * 2) + iVar8 + 1;
        iVar107 = (int)(short)(iVar56 + param_4[uVar34] >>
                              (0x20U - (int)LZCOUNT((iVar60 + param_6) - iVar57) & 0x1f));
        lVar27 = (long)(short)iVar102 * (long)(int)uVar10;
        uVar126 = (uint)(iVar107 * iVar107) >> 7;
        lVar19 = (ulong)uVar126 * (long)(short)iVar96;
        uVar125 = (uint)uVar34;
        if (lVar19 - lVar27 == 0 || lVar19 < lVar27) {
          uVar125 = (uint)uVar12;
          uVar126 = uVar10;
          iVar102 = iVar96;
        }
        iVar96 = iVar102;
        uVar10 = uVar126;
        uVar12 = (ulong)uVar125;
        uVar34 = uVar34 + 1;
      } while (uVar37 != uVar34);
      uVar34 = -(ulong)(uVar125 >> 0x1f) & 0xfffffffe00000000 | uVar12 << 1;
      iVar96 = *(int *)(&DAT_00124dac + (long)(int)uVar125 * 4);
      iVar56 = iVar56 + *(short *)((long)param_4 + uVar34);
      iVar8 = (uint)*(ushort *)(&DAT_00124fec + uVar34) + iVar8 + 1;
      *(ushort *)(&DAT_00124fec + uVar34) = *(ushort *)(&DAT_00124fec + uVar34) + 2;
      *(int *)(&DAT_00124dac + (long)(int)uVar125 * 4) = iVar96 + 1;
    } while (iVar60 != iVar57);
  }
  uVar37 = param_5 + 3;
  if (-1 < (int)param_5) {
    uVar37 = param_5;
  }
  if ((int)(uVar37 & 0xfffffffc) < 1) {
    uVar34 = 0;
    if ((int)param_5 < 1) goto LAB_0011639c;
  }
  else {
    uVar34 = 0;
    puVar28 = (undefined8 *)&DAT_0012522c;
    puVar31 = (undefined8 *)&DAT_00124dac;
    psVar18 = param_4;
    do {
      uVar55 = *puVar28;
      uVar119 = *(undefined8 *)psVar18;
      uVar34 = uVar34 + 4;
      sVar45 = (short)((ulong)uVar55 >> 0x10);
      sVar116 = (short)((ulong)uVar119 >> 0x10) * sVar45;
      sVar48 = (short)((ulong)uVar55 >> 0x20);
      sVar44 = (short)((ulong)uVar119 >> 0x20) * sVar48;
      sVar46 = (short)((ulong)uVar55 >> 0x30);
      sVar47 = (short)((ulong)uVar119 >> 0x30) * sVar46;
      *(ulong *)psVar18 =
           CONCAT17((char)((ushort)sVar47 >> 8),
                    CONCAT16((char)sVar47,
                             CONCAT15((char)((ushort)sVar44 >> 8),
                                      CONCAT14((char)sVar44,
                                               CONCAT13((char)((ushort)sVar116 >> 8),
                                                        CONCAT12((char)sVar116,
                                                                 (short)uVar119 * (short)uVar55)))))
                   );
      puVar31[1] = CONCAT44((int)((ulong)puVar31[1] >> 0x20) * (int)sVar46,
                            (int)puVar31[1] * (int)sVar48);
      *puVar31 = CONCAT44((int)((ulong)*puVar31 >> 0x20) * (int)sVar45,
                          (int)*puVar31 * (int)(short)uVar55);
      puVar28 = puVar28 + 1;
      puVar31 = puVar31 + 2;
      psVar18 = psVar18 + 4;
    } while (uVar34 < (uVar37 & 0xfffffffc));
    if ((int)param_5 <= (int)uVar34) goto LAB_0011639c;
  }
  uVar34 = uVar34 & 0xffffffff;
  uVar20 = (ulong)param_5;
  uVar35 = uVar20 - uVar34;
  uVar12 = uVar34;
  if (7 < uVar35) {
    if (((undefined1 (*) [16])(&DAT_0012522c + uVar20 * 2) <=
         (undefined1 (*) [16])(param_4 + uVar34)) ||
       (param_4 + uVar20 <= &DAT_0012522c + uVar34 * 2)) {
      uVar39 = uVar35 & 0xfffffffffffffff8;
      uVar12 = uVar39 + uVar34;
      pauVar32 = (undefined1 (*) [16])(param_4 + uVar34);
      puVar28 = (undefined8 *)(&DAT_0012522c + uVar34 * 2);
      pauVar13 = (undefined1 (*) [16])(&DAT_00124dac + uVar34 * 4);
      uVar34 = uVar39;
      do {
        uVar58 = puVar28[1];
        uVar54 = *puVar28;
        auVar120 = *pauVar13;
        uVar55 = *(undefined8 *)(pauVar13[1] + 8);
        uVar119 = *(undefined8 *)pauVar13[1];
        uVar34 = uVar34 - 8;
        sVar116 = (short)uVar58;
        sVar44 = (short)((ulong)uVar58 >> 0x10);
        sVar45 = (short)((ulong)uVar58 >> 0x20);
        sVar46 = (short)((ulong)uVar58 >> 0x30);
        sVar47 = (short)((ulong)uVar54 >> 0x10);
        sVar48 = (short)((ulong)uVar54 >> 0x20);
        sVar49 = (short)((ulong)uVar54 >> 0x30);
        auVar123 = *pauVar32;
        iVar8 = (int)((ulong)uVar119 >> 0x20) * CONCAT13(sVar44 >> 0xf,(int3)sVar44);
        iVar56 = (int)((ulong)uVar55 >> 0x20) * CONCAT13(sVar46 >> 0xf,(int3)sVar46);
        auVar97._0_8_ = CONCAT44(auVar120._4_4_ * (int)sVar47,auVar120._0_4_ * (int)(short)uVar54);
        auVar97._8_4_ = auVar120._8_4_ * (int)sVar48;
        auVar97._12_4_ = auVar120._12_4_ * (int)sVar49;
        *(long *)(*pauVar13 + 8) = auVar97._8_8_;
        *(undefined8 *)*pauVar13 = auVar97._0_8_;
        *(ulong *)(pauVar13[1] + 8) =
             CONCAT17((char)((uint)iVar56 >> 0x18),
                      CONCAT16((char)((uint)iVar56 >> 0x10),
                               CONCAT15((char)((uint)iVar56 >> 8),
                                        CONCAT14((char)iVar56,
                                                 (int)uVar55 * CONCAT13(sVar45 >> 0xf,(int3)sVar45))
                                       )));
        *(ulong *)pauVar13[1] =
             CONCAT17((char)((uint)iVar8 >> 0x18),
                      CONCAT16((char)((uint)iVar8 >> 0x10),
                               CONCAT15((char)((uint)iVar8 >> 8),
                                        CONCAT14((char)iVar8,
                                                 (int)uVar119 *
                                                 CONCAT13(sVar116 >> 0xf,(int3)sVar116)))));
        *(ulong *)((long)*pauVar32 + 8) =
             CONCAT26(auVar123._14_2_ * sVar46,
                      CONCAT24(auVar123._12_2_ * sVar45,
                               CONCAT22(auVar123._10_2_ * sVar44,auVar123._8_2_ * sVar116)));
        *(ulong *)*pauVar32 =
             CONCAT26(auVar123._6_2_ * sVar49,
                      CONCAT24(auVar123._4_2_ * sVar48,
                               CONCAT22(auVar123._2_2_ * sVar47,auVar123._0_2_ * (short)uVar54)));
        pauVar32 = pauVar32 + 1;
        puVar28 = puVar28 + 2;
        pauVar13 = pauVar13 + 2;
      } while (uVar34 != 0);
      if (uVar35 == uVar39) goto LAB_0011639c;
    }
  }
  do {
    uVar34 = uVar12 + 1;
    param_4[uVar12] = param_4[uVar12] * *(short *)(&DAT_0012522c + uVar12 * 2);
    *(int *)(&DAT_00124dac + uVar12 * 4) =
         *(int *)(&DAT_00124dac + uVar12 * 4) * (int)*(short *)(&DAT_0012522c + uVar12 * 2);
    uVar12 = uVar34;
  } while (uVar20 != uVar34);
LAB_0011639c:
  ssc_encode_pulses(&DAT_00124dac,param_5,param_6,param_9);
  if ((int)param_8 < 2) {
    uVar12 = 1;
  }
  else {
    iVar8 = 0;
    if (param_8 != 0) {
      iVar8 = (int)param_5 / (int)param_8;
    }
    uVar34 = (ulong)param_8;
    uVar12 = 0;
    lVar19 = (long)iVar8;
    lVar27 = lVar19;
    if (0 < lVar19) {
      lVar27 = 1;
    }
    uVar20 = (lVar19 - lVar27) + 1;
    uVar35 = uVar20 & 0xfffffffffffffff8;
    pauVar32 = (undefined1 (*) [16])(lVar19 * uVar34 * 4 + 0x124d9c);
    lVar27 = (uVar34 - 1) * lVar19 * 4 + 0x124da8;
    do {
      uVar39 = uVar34 - 1;
      uVar37 = (uint)uVar39;
      lVar21 = lVar19;
      if (uVar20 < 8) {
LAB_001164d8:
        do {
          lVar36 = lVar21 + -1;
          uVar12 = (ulong)((uint)(*(int *)(lVar27 + lVar21 * 4) != 0) << (ulong)(uVar37 & 0x1f) |
                          (uint)uVar12);
          bVar1 = 0 < lVar21;
          lVar21 = lVar36;
        } while (lVar36 != 0 && bVar1);
      }
      else {
        bVar71 = 0;
        bVar73 = 0;
        bVar76 = 0;
        bVar78 = 0;
        bVar80 = 0;
        bVar82 = 0;
        bVar84 = 0;
        bVar86 = 0;
        bVar88 = 0;
        bVar90 = 0;
        bVar92 = 0;
        bVar94 = 0;
        bVar95 = 0;
        bVar98 = 0;
        bVar99 = 0;
        bVar100 = 0;
        bVar101 = 0;
        bVar103 = 0;
        bVar104 = 0;
        bVar105 = 0;
        bVar106 = 0;
        bVar108 = 0;
        bVar109 = 0;
        bVar110 = 0;
        bVar111 = 0;
        bVar113 = 0;
        bVar114 = 0;
        bVar115 = 0;
        uVar117 = (undefined2)(uVar39 >> 0x10);
        bVar62 = (byte)uVar12;
        bVar64 = (byte)(uVar12 >> 8);
        bVar67 = (byte)(uVar12 >> 0x10);
        bVar69 = (byte)(uVar12 >> 0x18);
        pauVar13 = pauVar32;
        uVar12 = uVar35;
        do {
          pauVar2 = pauVar13 + -1;
          auVar120 = *pauVar13;
          pauVar13 = pauVar13 + -2;
          uVar12 = uVar12 - 8;
          auVar123 = NEON_rev64(*pauVar2,4);
          auVar120 = NEON_rev64(auVar120,4);
          auVar123 = NEON_ext(auVar123,auVar123,8,1);
          auVar120 = NEON_ext(auVar120,auVar120,8,1);
          auVar124._0_5_ =
               CONCAT14(~-(auVar123._4_4_ == 0),(uint)(~-(auVar123._0_4_ == 0) & 1)) & 0x1ffffffff;
          auVar124._5_3_ = 0;
          auVar124[8] = ~-(auVar123._8_4_ == 0) & 1;
          auVar124._9_3_ = 0;
          auVar124[0xc] = ~-(auVar123._12_4_ == 0) & 1;
          auVar124._13_3_ = 0;
          auVar121._0_5_ =
               CONCAT14(~-(auVar120._4_4_ == 0),(uint)(~-(auVar120._0_4_ == 0) & 1)) & 0x1ffffffff;
          auVar121._5_3_ = 0;
          auVar121[8] = ~-(auVar120._8_4_ == 0) & 1;
          auVar121._9_3_ = 0;
          auVar121[0xc] = ~-(auVar120._12_4_ == 0) & 1;
          auVar121._13_3_ = 0;
          auVar6._4_2_ = (short)uVar39;
          auVar6._0_4_ = uVar37;
          auVar6._6_2_ = uVar117;
          auVar6._8_4_ = uVar37;
          auVar6._12_4_ = uVar37;
          auVar123 = NEON_ushl(auVar124,auVar6,4);
          auVar7._4_2_ = (short)uVar39;
          auVar7._0_4_ = uVar37;
          auVar7._6_2_ = uVar117;
          auVar7._8_4_ = uVar37;
          auVar7._12_4_ = uVar37;
          auVar120 = NEON_ushl(auVar121,auVar7,4);
          bVar95 = auVar123[0] | bVar95;
          bVar98 = auVar123[1] | bVar98;
          bVar99 = auVar123[2] | bVar99;
          bVar100 = auVar123[3] | bVar100;
          bVar101 = auVar123[4] | bVar101;
          bVar103 = auVar123[5] | bVar103;
          bVar104 = auVar123[6] | bVar104;
          bVar105 = auVar123[7] | bVar105;
          bVar106 = auVar123[8] | bVar106;
          bVar108 = auVar123[9] | bVar108;
          bVar109 = auVar123[10] | bVar109;
          bVar110 = auVar123[0xb] | bVar110;
          bVar111 = auVar123[0xc] | bVar111;
          bVar113 = auVar123[0xd] | bVar113;
          bVar114 = auVar123[0xe] | bVar114;
          bVar115 = auVar123[0xf] | bVar115;
          bVar62 = auVar120[0] | bVar62;
          bVar64 = auVar120[1] | bVar64;
          bVar67 = auVar120[2] | bVar67;
          bVar69 = auVar120[3] | bVar69;
          bVar71 = auVar120[4] | bVar71;
          bVar73 = auVar120[5] | bVar73;
          bVar76 = auVar120[6] | bVar76;
          bVar78 = auVar120[7] | bVar78;
          bVar80 = auVar120[8] | bVar80;
          bVar82 = auVar120[9] | bVar82;
          bVar84 = auVar120[10] | bVar84;
          bVar86 = auVar120[0xb] | bVar86;
          bVar88 = auVar120[0xc] | bVar88;
          bVar90 = auVar120[0xd] | bVar90;
          bVar92 = auVar120[0xe] | bVar92;
          bVar94 = auVar120[0xf] | bVar94;
        } while (uVar12 != 0);
        bVar95 = bVar95 | bVar62;
        bVar98 = bVar98 | bVar64;
        bVar99 = bVar99 | bVar67;
        bVar100 = bVar100 | bVar69;
        bVar101 = bVar101 | bVar71;
        bVar103 = bVar103 | bVar73;
        bVar104 = bVar104 | bVar76;
        bVar105 = bVar105 | bVar78;
        auVar4[1] = bVar98;
        auVar4[0] = bVar95;
        auVar4[2] = bVar99;
        auVar4[3] = bVar100;
        auVar4[4] = bVar101;
        auVar4[5] = bVar103;
        auVar4[6] = bVar104;
        auVar4[7] = bVar105;
        auVar4[8] = bVar106 | bVar80;
        auVar4[9] = bVar108 | bVar82;
        auVar4[10] = bVar109 | bVar84;
        auVar4[0xb] = bVar110 | bVar86;
        auVar4[0xc] = bVar111 | bVar88;
        auVar4[0xd] = bVar113 | bVar90;
        auVar4[0xe] = bVar114 | bVar92;
        auVar4[0xf] = bVar115 | bVar94;
        auVar5[1] = bVar98;
        auVar5[0] = bVar95;
        auVar5[2] = bVar99;
        auVar5[3] = bVar100;
        auVar5[4] = bVar101;
        auVar5[5] = bVar103;
        auVar5[6] = bVar104;
        auVar5[7] = bVar105;
        auVar5[8] = bVar106 | bVar80;
        auVar5[9] = bVar108 | bVar82;
        auVar5[10] = bVar109 | bVar84;
        auVar5[0xb] = bVar110 | bVar86;
        auVar5[0xc] = bVar111 | bVar88;
        auVar5[0xd] = bVar113 | bVar90;
        auVar5[0xe] = bVar114 | bVar92;
        auVar5[0xf] = bVar115 | bVar94;
        auVar120 = NEON_ext(auVar4,auVar5,8,1);
        uVar12 = (ulong)(CONCAT13(bVar100 | auVar120[3],
                                  CONCAT12(bVar99 | auVar120[2],
                                           CONCAT11(bVar98 | auVar120[1],bVar95 | auVar120[0]))) |
                        CONCAT13(bVar105 | auVar120[7],
                                 CONCAT12(bVar104 | auVar120[6],
                                          CONCAT11(bVar103 | auVar120[5],bVar101 | auVar120[4]))));
        lVar21 = lVar19 - uVar35;
        if (uVar20 != uVar35) goto LAB_001164d8;
      }
      pauVar32 = (undefined1 (*) [16])((long)pauVar32 + (long)iVar8 * -4);
      lVar27 = lVar27 + (long)iVar8 * -4;
      bVar1 = 1 < (long)uVar34;
      uVar34 = uVar39;
    } while (bVar1);
  }
  return uVar12;
}


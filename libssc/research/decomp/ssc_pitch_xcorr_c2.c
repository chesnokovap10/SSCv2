/* ssc_pitch_xcorr_c2 @ 00113468 size 188 */

undefined4 ssc_pitch_xcorr_c2(short *param_1,short *param_2,uint *param_3)

{
  bool bVar1;
  long lVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  uint uVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  undefined6 uVar23;
  undefined6 uVar24;
  undefined6 uVar25;
  undefined6 uVar26;
  undefined6 uVar27;
  undefined6 uVar28;
  undefined6 uVar29;
  undefined6 uVar30;
  short *psVar31;
  long lVar32;
  long lVar33;
  short *psVar34;
  short *psVar35;
  undefined1 uVar36;
  undefined1 uVar37;
  undefined1 uVar38;
  undefined1 uVar39;
  undefined1 uVar40;
  undefined1 uVar41;
  undefined1 uVar42;
  undefined1 uVar43;
  undefined1 uVar44;
  undefined1 uVar45;
  undefined1 uVar46;
  undefined1 uVar47;
  undefined1 uVar48;
  undefined1 uVar49;
  undefined1 uVar50;
  undefined1 uVar51;
  undefined1 uVar52;
  undefined1 uVar53;
  undefined1 uVar54;
  undefined1 uVar55;
  undefined1 uVar56;
  undefined1 uVar57;
  undefined1 uVar58;
  undefined1 uVar59;
  undefined1 uVar60;
  undefined1 uVar61;
  undefined1 uVar62;
  undefined1 uVar63;
  undefined1 uVar64;
  undefined1 uVar65;
  undefined1 uVar66;
  undefined1 uVar67;
  undefined1 uVar68;
  undefined1 uVar69;
  undefined1 uVar70;
  undefined1 uVar71;
  undefined1 uVar72;
  undefined1 uVar73;
  undefined1 uVar74;
  undefined1 uVar75;
  undefined1 uVar76;
  undefined1 uVar77;
  undefined1 uVar78;
  undefined1 uVar79;
  undefined1 uVar80;
  undefined1 uVar81;
  undefined1 uVar82;
  undefined1 uVar83;
  undefined1 uVar84;
  undefined1 uVar85;
  undefined1 uVar86;
  undefined1 uVar87;
  undefined1 uVar88;
  undefined1 uVar89;
  undefined1 uVar90;
  undefined1 uVar91;
  undefined1 uVar92;
  undefined1 uVar93;
  undefined1 uVar94;
  undefined1 uVar95;
  undefined1 uVar96;
  undefined1 uVar97;
  undefined1 uVar98;
  undefined1 uVar99;
  short sVar100;
  short sVar101;
  short sVar102;
  short sVar103;
  short sVar104;
  undefined1 auVar105 [16];
  
  auVar105._8_4_ = 1;
  auVar105._0_8_ = 0x100000001;
  auVar105._12_4_ = 1;
  lVar33 = 0x3d;
  do {
    uVar36 = 0;
    uVar37 = 0;
    uVar38 = 0;
    uVar39 = 0;
    uVar40 = 0;
    uVar41 = 0;
    uVar42 = 0;
    uVar43 = 0;
    uVar44 = 0;
    uVar45 = 0;
    uVar46 = 0;
    uVar47 = 0;
    uVar48 = 0;
    uVar49 = 0;
    uVar50 = 0;
    uVar51 = 0;
    uVar52 = 0;
    uVar53 = 0;
    uVar54 = 0;
    uVar55 = 0;
    uVar56 = 0;
    uVar57 = 0;
    uVar58 = 0;
    uVar59 = 0;
    uVar60 = 0;
    uVar61 = 0;
    uVar62 = 0;
    uVar63 = 0;
    uVar64 = 0;
    uVar65 = 0;
    uVar66 = 0;
    uVar67 = 0;
    uVar68 = 0;
    uVar69 = 0;
    uVar70 = 0;
    uVar71 = 0;
    uVar72 = 0;
    uVar73 = 0;
    uVar74 = 0;
    uVar75 = 0;
    uVar76 = 0;
    uVar77 = 0;
    uVar78 = 0;
    uVar79 = 0;
    uVar80 = 0;
    uVar81 = 0;
    uVar82 = 0;
    uVar83 = 0;
    uVar84 = 0;
    uVar85 = 0;
    uVar86 = 0;
    uVar87 = 0;
    uVar88 = 0;
    uVar89 = 0;
    uVar90 = 0;
    uVar91 = 0;
    uVar92 = 0;
    uVar93 = 0;
    uVar94 = 0;
    uVar95 = 0;
    uVar96 = 0;
    uVar97 = 0;
    uVar98 = 0;
    uVar99 = 0;
    lVar32 = 0x1b;
    psVar34 = param_1;
    psVar35 = param_2;
    do {
      sVar100 = *psVar34;
      sVar101 = psVar34[1];
      sVar102 = psVar34[2];
      sVar103 = psVar34[3];
      psVar31 = psVar34 + 4;
      uVar30 = *(undefined6 *)psVar31;
      uVar28 = *(undefined6 *)psVar31;
      uVar26 = *(undefined6 *)psVar31;
      uVar24 = *(undefined6 *)psVar31;
      sVar104 = psVar34[7];
      psVar34 = psVar34 + 8;
      uVar23 = *(undefined6 *)(psVar35 + 4);
      uVar25 = *(undefined6 *)(psVar35 + 5);
      uVar27 = *(undefined6 *)(psVar35 + 6);
      uVar29 = *(undefined6 *)(psVar35 + 7);
      iVar3 = CONCAT13(uVar39,CONCAT12(uVar38,CONCAT11(uVar37,uVar36))) +
              (int)*psVar35 * (int)sVar100 + (int)(short)uVar23 * (int)(short)uVar24;
      uVar36 = (undefined1)iVar3;
      uVar37 = (undefined1)((uint)iVar3 >> 8);
      uVar38 = (undefined1)((uint)iVar3 >> 0x10);
      uVar39 = (undefined1)((uint)iVar3 >> 0x18);
      iVar5 = CONCAT13(uVar43,CONCAT12(uVar42,CONCAT11(uVar41,uVar40))) +
              (int)psVar35[1] * (int)sVar101 +
              (int)(short)((uint6)uVar23 >> 0x10) * (int)(short)((uint6)uVar24 >> 0x10);
      uVar40 = (undefined1)iVar5;
      uVar41 = (undefined1)((uint)iVar5 >> 8);
      uVar42 = (undefined1)((uint)iVar5 >> 0x10);
      uVar43 = (undefined1)((uint)iVar5 >> 0x18);
      iVar6 = CONCAT13(uVar47,CONCAT12(uVar46,CONCAT11(uVar45,uVar44))) +
              (int)psVar35[2] * (int)sVar102 +
              (int)(short)((uint6)uVar23 >> 0x20) * (int)(short)((uint6)uVar24 >> 0x20);
      uVar44 = (undefined1)iVar6;
      uVar45 = (undefined1)((uint)iVar6 >> 8);
      uVar46 = (undefined1)((uint)iVar6 >> 0x10);
      uVar47 = (undefined1)((uint)iVar6 >> 0x18);
      iVar7 = CONCAT13(uVar51,CONCAT12(uVar50,CONCAT11(uVar49,uVar48))) +
              (int)psVar35[3] * (int)sVar103 + (int)psVar35[7] * (int)sVar104;
      uVar48 = (undefined1)iVar7;
      uVar49 = (undefined1)((uint)iVar7 >> 8);
      uVar50 = (undefined1)((uint)iVar7 >> 0x10);
      uVar51 = (undefined1)((uint)iVar7 >> 0x18);
      iVar8 = CONCAT13(uVar55,CONCAT12(uVar54,CONCAT11(uVar53,uVar52))) +
              (int)psVar35[1] * (int)sVar100 + (int)(short)uVar25 * (int)(short)uVar26;
      uVar52 = (undefined1)iVar8;
      uVar53 = (undefined1)((uint)iVar8 >> 8);
      uVar54 = (undefined1)((uint)iVar8 >> 0x10);
      uVar55 = (undefined1)((uint)iVar8 >> 0x18);
      iVar10 = CONCAT13(uVar59,CONCAT12(uVar58,CONCAT11(uVar57,uVar56))) +
               (int)psVar35[2] * (int)sVar101 +
               (int)(short)((uint6)uVar25 >> 0x10) * (int)(short)((uint6)uVar26 >> 0x10);
      uVar56 = (undefined1)iVar10;
      uVar57 = (undefined1)((uint)iVar10 >> 8);
      uVar58 = (undefined1)((uint)iVar10 >> 0x10);
      uVar59 = (undefined1)((uint)iVar10 >> 0x18);
      iVar11 = CONCAT13(uVar63,CONCAT12(uVar62,CONCAT11(uVar61,uVar60))) +
               (int)psVar35[3] * (int)sVar102 +
               (int)(short)((uint6)uVar25 >> 0x20) * (int)(short)((uint6)uVar26 >> 0x20);
      uVar60 = (undefined1)iVar11;
      uVar61 = (undefined1)((uint)iVar11 >> 8);
      uVar62 = (undefined1)((uint)iVar11 >> 0x10);
      uVar63 = (undefined1)((uint)iVar11 >> 0x18);
      iVar12 = CONCAT13(uVar67,CONCAT12(uVar66,CONCAT11(uVar65,uVar64))) +
               (int)psVar35[4] * (int)sVar103 + (int)psVar35[8] * (int)sVar104;
      uVar64 = (undefined1)iVar12;
      uVar65 = (undefined1)((uint)iVar12 >> 8);
      uVar66 = (undefined1)((uint)iVar12 >> 0x10);
      uVar67 = (undefined1)((uint)iVar12 >> 0x18);
      iVar13 = CONCAT13(uVar71,CONCAT12(uVar70,CONCAT11(uVar69,uVar68))) +
               (int)psVar35[2] * (int)sVar100 + (int)(short)uVar27 * (int)(short)uVar28;
      uVar68 = (undefined1)iVar13;
      uVar69 = (undefined1)((uint)iVar13 >> 8);
      uVar70 = (undefined1)((uint)iVar13 >> 0x10);
      uVar71 = (undefined1)((uint)iVar13 >> 0x18);
      iVar15 = CONCAT13(uVar75,CONCAT12(uVar74,CONCAT11(uVar73,uVar72))) +
               (int)psVar35[3] * (int)sVar101 +
               (int)(short)((uint6)uVar27 >> 0x10) * (int)(short)((uint6)uVar28 >> 0x10);
      uVar72 = (undefined1)iVar15;
      uVar73 = (undefined1)((uint)iVar15 >> 8);
      uVar74 = (undefined1)((uint)iVar15 >> 0x10);
      uVar75 = (undefined1)((uint)iVar15 >> 0x18);
      iVar16 = CONCAT13(uVar79,CONCAT12(uVar78,CONCAT11(uVar77,uVar76))) +
               (int)psVar35[4] * (int)sVar102 +
               (int)(short)((uint6)uVar27 >> 0x20) * (int)(short)((uint6)uVar28 >> 0x20);
      uVar76 = (undefined1)iVar16;
      uVar77 = (undefined1)((uint)iVar16 >> 8);
      uVar78 = (undefined1)((uint)iVar16 >> 0x10);
      uVar79 = (undefined1)((uint)iVar16 >> 0x18);
      iVar17 = CONCAT13(uVar83,CONCAT12(uVar82,CONCAT11(uVar81,uVar80))) +
               (int)psVar35[5] * (int)sVar103 + (int)psVar35[9] * (int)sVar104;
      uVar80 = (undefined1)iVar17;
      uVar81 = (undefined1)((uint)iVar17 >> 8);
      uVar82 = (undefined1)((uint)iVar17 >> 0x10);
      uVar83 = (undefined1)((uint)iVar17 >> 0x18);
      iVar18 = CONCAT13(uVar87,CONCAT12(uVar86,CONCAT11(uVar85,uVar84))) +
               (int)psVar35[3] * (int)sVar100 + (int)(short)uVar29 * (int)(short)uVar30;
      uVar84 = (undefined1)iVar18;
      uVar85 = (undefined1)((uint)iVar18 >> 8);
      uVar86 = (undefined1)((uint)iVar18 >> 0x10);
      uVar87 = (undefined1)((uint)iVar18 >> 0x18);
      iVar20 = CONCAT13(uVar91,CONCAT12(uVar90,CONCAT11(uVar89,uVar88))) +
               (int)psVar35[4] * (int)sVar101 +
               (int)(short)((uint6)uVar29 >> 0x10) * (int)(short)((uint6)uVar30 >> 0x10);
      uVar88 = (undefined1)iVar20;
      uVar89 = (undefined1)((uint)iVar20 >> 8);
      uVar90 = (undefined1)((uint)iVar20 >> 0x10);
      uVar91 = (undefined1)((uint)iVar20 >> 0x18);
      iVar21 = CONCAT13(uVar95,CONCAT12(uVar94,CONCAT11(uVar93,uVar92))) +
               (int)psVar35[5] * (int)sVar102 +
               (int)(short)((uint6)uVar29 >> 0x20) * (int)(short)((uint6)uVar30 >> 0x20);
      uVar92 = (undefined1)iVar21;
      uVar93 = (undefined1)((uint)iVar21 >> 8);
      uVar94 = (undefined1)((uint)iVar21 >> 0x10);
      uVar95 = (undefined1)((uint)iVar21 >> 0x18);
      iVar22 = CONCAT13(uVar99,CONCAT12(uVar98,CONCAT11(uVar97,uVar96))) +
               (int)psVar35[6] * (int)sVar103 + (int)psVar35[10] * (int)sVar104;
      uVar96 = (undefined1)iVar22;
      uVar97 = (undefined1)((uint)iVar22 >> 8);
      uVar98 = (undefined1)((uint)iVar22 >> 0x10);
      uVar99 = (undefined1)((uint)iVar22 >> 0x18);
      psVar35 = psVar35 + 8;
      lVar2 = lVar32 + -1;
      bVar1 = 0 < lVar32;
      lVar32 = lVar2;
    } while (lVar2 != 0 && bVar1);
    uVar4 = iVar3 + iVar5 + iVar6 + iVar7;
    uVar9 = iVar8 + iVar10 + iVar11 + iVar12;
    uVar14 = iVar13 + iVar15 + iVar16 + iVar17;
    uVar19 = iVar18 + iVar20 + iVar21 + iVar22;
    *param_3 = uVar4;
    param_3[1] = uVar9;
    param_3[2] = uVar14;
    param_3[3] = uVar19;
    param_3 = param_3 + 4;
    auVar105 = NEON_smax(auVar105,ZEXT416(uVar4),4);
    auVar105 = NEON_smax(auVar105,ZEXT416(uVar9),4);
    auVar105 = NEON_smax(auVar105,ZEXT416(uVar14),4);
    auVar105 = NEON_smax(auVar105,ZEXT416(uVar19),4);
    param_2 = param_2 + 4;
    lVar32 = lVar33 + -1;
    bVar1 = 0 < lVar33;
    lVar33 = lVar32;
  } while (lVar32 != 0 && bVar1);
  return auVar105._0_4_;
}


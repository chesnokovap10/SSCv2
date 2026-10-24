/* ssc_pitch_xcorr_c1 @ 001133a0 size 200 */

short * ssc_pitch_xcorr_c1(short *param_1,short *param_2,int *param_3)

{
  bool bVar1;
  int iVar2;
  undefined6 uVar3;
  undefined6 uVar4;
  undefined6 uVar5;
  undefined6 uVar6;
  undefined6 uVar7;
  undefined6 uVar8;
  undefined6 uVar9;
  undefined6 uVar10;
  undefined6 uVar11;
  undefined6 uVar12;
  short *psVar13;
  short *psVar14;
  short *psVar15;
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
  int iVar28;
  int iVar29;
  int iVar30;
  int iVar31;
  int iVar32;
  int iVar33;
  int iVar34;
  int iVar35;
  int iVar36;
  short sVar37;
  short sVar38;
  short sVar39;
  short sVar40;
  short sVar41;
  short sVar42;
  short sVar43;
  short sVar44;
  short sVar45;
  short sVar46;
  short sVar47;
  short sVar48;
  short sVar49;
  short sVar50;
  short sVar51;
  short sVar52;
  short sVar53;
  short sVar54;
  short sVar55;
  short sVar56;
  
  iVar17 = 0;
  iVar18 = 0;
  iVar19 = 0;
  iVar20 = 0;
  iVar21 = 0;
  iVar22 = 0;
  iVar23 = 0;
  iVar24 = 0;
  iVar25 = 0;
  iVar26 = 0;
  iVar27 = 0;
  iVar28 = 0;
  iVar29 = 0;
  iVar30 = 0;
  iVar31 = 0;
  iVar32 = 0;
  iVar33 = 0;
  iVar34 = 0;
  iVar35 = 0;
  iVar36 = 0;
  iVar16 = 0x75;
  do {
    psVar15 = param_2;
    psVar14 = param_1;
    sVar48 = *psVar14;
    sVar50 = psVar14[1];
    sVar52 = psVar14[2];
    sVar54 = psVar14[3];
    psVar13 = psVar14 + 4;
    uVar12 = *(undefined6 *)psVar13;
    uVar10 = *(undefined6 *)psVar13;
    uVar8 = *(undefined6 *)psVar13;
    uVar6 = *(undefined6 *)psVar13;
    uVar4 = *(undefined6 *)psVar13;
    sVar56 = psVar14[7];
    uVar3 = *(undefined6 *)(psVar15 + 4);
    uVar5 = *(undefined6 *)(psVar15 + 5);
    uVar7 = *(undefined6 *)(psVar15 + 6);
    uVar9 = *(undefined6 *)(psVar15 + 7);
    uVar11 = *(undefined6 *)(psVar15 + 8);
    iVar17 = iVar17 + (int)*psVar15 * (int)sVar48 + (int)(short)uVar3 * (int)(short)uVar4;
    iVar18 = iVar18 + (int)psVar15[1] * (int)sVar50 +
             (int)(short)((uint6)uVar3 >> 0x10) * (int)(short)((uint6)uVar4 >> 0x10);
    iVar19 = iVar19 + (int)psVar15[2] * (int)sVar52 +
             (int)(short)((uint6)uVar3 >> 0x20) * (int)(short)((uint6)uVar4 >> 0x20);
    iVar20 = iVar20 + (int)psVar15[3] * (int)sVar54 + (int)psVar15[7] * (int)sVar56;
    iVar21 = iVar21 + (int)psVar15[1] * (int)sVar48 + (int)(short)uVar5 * (int)(short)uVar6;
    iVar22 = iVar22 + (int)psVar15[2] * (int)sVar50 +
             (int)(short)((uint6)uVar5 >> 0x10) * (int)(short)((uint6)uVar6 >> 0x10);
    iVar23 = iVar23 + (int)psVar15[3] * (int)sVar52 +
             (int)(short)((uint6)uVar5 >> 0x20) * (int)(short)((uint6)uVar6 >> 0x20);
    iVar24 = iVar24 + (int)psVar15[4] * (int)sVar54 + (int)psVar15[8] * (int)sVar56;
    iVar25 = iVar25 + (int)psVar15[2] * (int)sVar48 + (int)(short)uVar7 * (int)(short)uVar8;
    iVar26 = iVar26 + (int)psVar15[3] * (int)sVar50 +
             (int)(short)((uint6)uVar7 >> 0x10) * (int)(short)((uint6)uVar8 >> 0x10);
    iVar27 = iVar27 + (int)psVar15[4] * (int)sVar52 +
             (int)(short)((uint6)uVar7 >> 0x20) * (int)(short)((uint6)uVar8 >> 0x20);
    iVar28 = iVar28 + (int)psVar15[5] * (int)sVar54 + (int)psVar15[9] * (int)sVar56;
    iVar29 = iVar29 + (int)psVar15[3] * (int)sVar48 + (int)(short)uVar9 * (int)(short)uVar10;
    iVar30 = iVar30 + (int)psVar15[4] * (int)sVar50 +
             (int)(short)((uint6)uVar9 >> 0x10) * (int)(short)((uint6)uVar10 >> 0x10);
    iVar31 = iVar31 + (int)psVar15[5] * (int)sVar52 +
             (int)(short)((uint6)uVar9 >> 0x20) * (int)(short)((uint6)uVar10 >> 0x20);
    iVar32 = iVar32 + (int)psVar15[6] * (int)sVar54 + (int)psVar15[10] * (int)sVar56;
    iVar33 = iVar33 + (int)psVar15[4] * (int)sVar48 + (int)(short)uVar11 * (int)(short)uVar12;
    iVar34 = iVar34 + (int)psVar15[5] * (int)sVar50 +
             (int)(short)((uint6)uVar11 >> 0x10) * (int)(short)((uint6)uVar12 >> 0x10);
    iVar35 = iVar35 + (int)psVar15[6] * (int)sVar52 +
             (int)(short)((uint6)uVar11 >> 0x20) * (int)(short)((uint6)uVar12 >> 0x20);
    iVar36 = iVar36 + (int)psVar15[7] * (int)sVar54 + (int)psVar15[0xb] * (int)sVar56;
    iVar2 = iVar16 + -1;
    bVar1 = 0 < iVar16;
    param_1 = psVar14 + 8;
    param_2 = psVar15 + 8;
    iVar16 = iVar2;
  } while (iVar2 != 0 && bVar1);
  sVar49 = psVar14[8];
  sVar51 = psVar14[9];
  sVar53 = psVar14[10];
  sVar55 = psVar14[0xb];
  sVar48 = psVar15[9];
  sVar50 = psVar15[10];
  sVar52 = psVar15[0xb];
  sVar54 = psVar15[0xc];
  sVar56 = psVar15[10];
  sVar37 = psVar15[0xb];
  sVar38 = psVar15[0xc];
  sVar39 = psVar15[0xd];
  sVar40 = psVar15[0xb];
  sVar41 = psVar15[0xc];
  sVar42 = psVar15[0xd];
  sVar43 = psVar15[0xe];
  sVar44 = psVar15[0xc];
  sVar45 = psVar15[0xd];
  sVar46 = psVar15[0xe];
  sVar47 = psVar15[0xf];
  *param_3 = iVar17 + (int)psVar15[8] * (int)sVar49 + iVar18 + (int)psVar15[9] * (int)sVar51 +
             iVar19 + (int)psVar15[10] * (int)sVar53 + iVar20 + (int)psVar15[0xb] * (int)sVar55;
  param_3[1] = iVar21 + (int)sVar48 * (int)sVar49 + iVar22 + (int)sVar50 * (int)sVar51 +
               iVar23 + (int)sVar52 * (int)sVar53 + iVar24 + (int)sVar54 * (int)sVar55;
  param_3[2] = iVar25 + (int)sVar56 * (int)sVar49 + iVar26 + (int)sVar37 * (int)sVar51 +
               iVar27 + (int)sVar38 * (int)sVar53 + iVar28 + (int)sVar39 * (int)sVar55;
  param_3[3] = iVar29 + (int)sVar40 * (int)sVar49 + iVar30 + (int)sVar41 * (int)sVar51 +
               iVar31 + (int)sVar42 * (int)sVar53 + iVar32 + (int)sVar43 * (int)sVar55;
  param_3[4] = iVar33 + (int)sVar44 * (int)sVar49 + iVar34 + (int)sVar45 * (int)sVar51 +
               iVar35 + (int)sVar46 * (int)sVar53 + iVar36 + (int)sVar47 * (int)sVar55;
  return psVar14 + 0xc;
}


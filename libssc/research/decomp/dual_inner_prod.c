/* dual_inner_prod @ 00113300 size 160 */

undefined4 *
dual_inner_prod(undefined4 *param_1,short *param_2,short *param_3,undefined8 param_4,int *param_5,
               int *param_6)

{
  bool bVar1;
  int iVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined6 uVar5;
  undefined6 uVar6;
  undefined6 uVar7;
  undefined6 uVar8;
  undefined6 uVar9;
  undefined6 uVar10;
  undefined6 uVar11;
  undefined6 uVar12;
  undefined6 uVar13;
  undefined6 uVar14;
  undefined6 uVar15;
  undefined6 uVar16;
  undefined4 uVar17;
  undefined4 *puVar18;
  short *psVar19;
  short *psVar20;
  int iVar21;
  short sVar22;
  short sVar23;
  short sVar24;
  short sVar25;
  short sVar26;
  short sVar27;
  short sVar28;
  short sVar29;
  short sVar30;
  short sVar31;
  short sVar32;
  short sVar33;
  short sVar34;
  short sVar35;
  short sVar36;
  short sVar37;
  short sVar38;
  short sVar39;
  short sVar40;
  short sVar41;
  short sVar42;
  short sVar43;
  short sVar44;
  short sVar45;
  int iVar46;
  int iVar47;
  int iVar48;
  int iVar49;
  int iVar50;
  int iVar51;
  int iVar52;
  int iVar53;
  
  iVar46 = 0;
  iVar47 = 0;
  iVar48 = 0;
  iVar49 = 0;
  iVar50 = 0;
  iVar51 = 0;
  iVar52 = 0;
  iVar53 = 0;
  iVar21 = 0xd;
  do {
    psVar20 = param_3;
    psVar19 = param_2;
    puVar18 = param_1;
    uVar3 = *(undefined8 *)(puVar18 + 2);
    uVar4 = *(undefined8 *)(puVar18 + 6);
    uVar11 = *(undefined6 *)(puVar18 + 10);
    uVar9 = *(undefined6 *)(puVar18 + 10);
    uVar15 = *(undefined6 *)(puVar18 + 0xe);
    uVar13 = *(undefined6 *)(puVar18 + 0xe);
    uVar5 = *(undefined6 *)(psVar19 + 4);
    uVar7 = *(undefined6 *)(psVar19 + 0xc);
    uVar10 = *(undefined6 *)(psVar19 + 0x14);
    uVar14 = *(undefined6 *)(psVar19 + 0x1c);
    uVar6 = *(undefined6 *)(psVar20 + 4);
    uVar8 = *(undefined6 *)(psVar20 + 0xc);
    uVar12 = *(undefined6 *)(psVar20 + 0x14);
    uVar16 = *(undefined6 *)(psVar20 + 0x1c);
    sVar28 = (short)*puVar18;
    sVar29 = (short)((uint)*puVar18 >> 0x10);
    sVar30 = (short)puVar18[1];
    sVar31 = (short)((uint)puVar18[1] >> 0x10);
    sVar22 = (short)((ulong)uVar3 >> 0x10);
    sVar24 = (short)((ulong)uVar3 >> 0x20);
    sVar26 = (short)((ulong)uVar3 >> 0x30);
    sVar32 = (short)puVar18[4];
    sVar33 = (short)((uint)puVar18[4] >> 0x10);
    sVar34 = (short)puVar18[5];
    sVar35 = (short)((uint)puVar18[5] >> 0x10);
    sVar23 = (short)((ulong)uVar4 >> 0x10);
    sVar25 = (short)((ulong)uVar4 >> 0x20);
    sVar27 = (short)((ulong)uVar4 >> 0x30);
    iVar46 = iVar46 + (int)sVar28 * (int)*psVar19 + (int)(short)uVar3 * (int)(short)uVar5 +
             (int)sVar32 * (int)psVar19[8] + (int)(short)uVar4 * (int)(short)uVar7 +
             (int)*(short *)(puVar18 + 8) * (int)psVar19[0x10] +
             (int)(short)uVar9 * (int)(short)uVar10 +
             (int)*(short *)(puVar18 + 0xc) * (int)psVar19[0x18] +
             (int)(short)uVar13 * (int)(short)uVar14;
    iVar47 = iVar47 + (int)sVar29 * (int)psVar19[1] +
             (int)sVar22 * (int)(short)((uint6)uVar5 >> 0x10) + (int)sVar33 * (int)psVar19[9] +
             (int)sVar23 * (int)(short)((uint6)uVar7 >> 0x10) +
             (int)*(short *)((long)puVar18 + 0x22) * (int)psVar19[0x11] +
             (int)(short)((uint6)uVar9 >> 0x10) * (int)(short)((uint6)uVar10 >> 0x10) +
             (int)*(short *)((long)puVar18 + 0x32) * (int)psVar19[0x19] +
             (int)(short)((uint6)uVar13 >> 0x10) * (int)(short)((uint6)uVar14 >> 0x10);
    iVar48 = iVar48 + (int)sVar30 * (int)psVar19[2] +
             (int)sVar24 * (int)(short)((uint6)uVar5 >> 0x20) + (int)sVar34 * (int)psVar19[10] +
             (int)sVar25 * (int)(short)((uint6)uVar7 >> 0x20) +
             (int)*(short *)(puVar18 + 9) * (int)psVar19[0x12] +
             (int)(short)((uint6)uVar9 >> 0x20) * (int)(short)((uint6)uVar10 >> 0x20) +
             (int)*(short *)(puVar18 + 0xd) * (int)psVar19[0x1a] +
             (int)(short)((uint6)uVar13 >> 0x20) * (int)(short)((uint6)uVar14 >> 0x20);
    iVar49 = iVar49 + (int)sVar31 * (int)psVar19[3] + (int)sVar26 * (int)psVar19[7] +
             (int)sVar35 * (int)psVar19[0xb] + (int)sVar27 * (int)psVar19[0xf] +
             (int)*(short *)((long)puVar18 + 0x26) * (int)psVar19[0x13] +
             (int)*(short *)((long)puVar18 + 0x2e) * (int)psVar19[0x17] +
             (int)*(short *)((long)puVar18 + 0x36) * (int)psVar19[0x1b] +
             (int)*(short *)((long)puVar18 + 0x3e) * (int)psVar19[0x1f];
    iVar50 = iVar50 + (int)sVar28 * (int)*psVar20 + (int)(short)uVar3 * (int)(short)uVar6 +
             (int)sVar32 * (int)psVar20[8] + (int)(short)uVar4 * (int)(short)uVar8 +
             (int)*(short *)(puVar18 + 8) * (int)psVar20[0x10] +
             (int)(short)uVar11 * (int)(short)uVar12 +
             (int)*(short *)(puVar18 + 0xc) * (int)psVar20[0x18] +
             (int)(short)uVar15 * (int)(short)uVar16;
    iVar51 = iVar51 + (int)sVar29 * (int)psVar20[1] +
             (int)sVar22 * (int)(short)((uint6)uVar6 >> 0x10) + (int)sVar33 * (int)psVar20[9] +
             (int)sVar23 * (int)(short)((uint6)uVar8 >> 0x10) +
             (int)*(short *)((long)puVar18 + 0x22) * (int)psVar20[0x11] +
             (int)(short)((uint6)uVar11 >> 0x10) * (int)(short)((uint6)uVar12 >> 0x10) +
             (int)*(short *)((long)puVar18 + 0x32) * (int)psVar20[0x19] +
             (int)(short)((uint6)uVar15 >> 0x10) * (int)(short)((uint6)uVar16 >> 0x10);
    iVar52 = iVar52 + (int)sVar30 * (int)psVar20[2] +
             (int)sVar24 * (int)(short)((uint6)uVar6 >> 0x20) + (int)sVar34 * (int)psVar20[10] +
             (int)sVar25 * (int)(short)((uint6)uVar8 >> 0x20) +
             (int)*(short *)(puVar18 + 9) * (int)psVar20[0x12] +
             (int)(short)((uint6)uVar11 >> 0x20) * (int)(short)((uint6)uVar12 >> 0x20) +
             (int)*(short *)(puVar18 + 0xd) * (int)psVar20[0x1a] +
             (int)(short)((uint6)uVar15 >> 0x20) * (int)(short)((uint6)uVar16 >> 0x20);
    iVar53 = iVar53 + (int)sVar31 * (int)psVar20[3] + (int)sVar26 * (int)psVar20[7] +
             (int)sVar35 * (int)psVar20[0xb] + (int)sVar27 * (int)psVar20[0xf] +
             (int)*(short *)((long)puVar18 + 0x26) * (int)psVar20[0x13] +
             (int)*(short *)((long)puVar18 + 0x2e) * (int)psVar20[0x17] +
             (int)*(short *)((long)puVar18 + 0x36) * (int)psVar20[0x1b] +
             (int)*(short *)((long)puVar18 + 0x3e) * (int)psVar20[0x1f];
    iVar2 = iVar21 + -1;
    bVar1 = 0 < iVar21;
    param_1 = puVar18 + 0x10;
    param_2 = psVar19 + 0x20;
    param_3 = psVar20 + 0x20;
    iVar21 = iVar2;
  } while (iVar2 != 0 && bVar1);
  uVar17 = puVar18[0x10];
  uVar3 = *(undefined8 *)(puVar18 + 0x12);
  uVar4 = *(undefined8 *)(puVar18 + 0x16);
  uVar5 = *(undefined6 *)(psVar19 + 0x24);
  uVar7 = *(undefined6 *)(psVar19 + 0x2c);
  sVar36 = psVar20[0x20];
  sVar37 = psVar20[0x21];
  sVar38 = psVar20[0x22];
  sVar39 = psVar20[0x23];
  uVar6 = *(undefined6 *)(psVar20 + 0x24);
  sVar40 = psVar20[0x27];
  sVar41 = psVar20[0x28];
  sVar42 = psVar20[0x29];
  sVar43 = psVar20[0x2a];
  sVar44 = psVar20[0x2b];
  uVar8 = *(undefined6 *)(psVar20 + 0x2c);
  sVar45 = psVar20[0x2f];
  sVar28 = (short)uVar17;
  sVar29 = (short)((uint)uVar17 >> 0x10);
  sVar30 = (short)puVar18[0x11];
  sVar31 = (short)((uint)puVar18[0x11] >> 0x10);
  sVar22 = (short)((ulong)uVar3 >> 0x10);
  sVar24 = (short)((ulong)uVar3 >> 0x20);
  sVar26 = (short)((ulong)uVar3 >> 0x30);
  sVar32 = (short)puVar18[0x14];
  sVar33 = (short)((uint)puVar18[0x14] >> 0x10);
  sVar34 = (short)puVar18[0x15];
  sVar35 = (short)((uint)puVar18[0x15] >> 0x10);
  sVar23 = (short)((ulong)uVar4 >> 0x10);
  sVar25 = (short)((ulong)uVar4 >> 0x20);
  sVar27 = (short)((ulong)uVar4 >> 0x30);
  *param_5 = iVar46 + (int)sVar28 * (int)psVar19[0x20] + (int)(short)uVar3 * (int)(short)uVar5 +
             (int)sVar32 * (int)psVar19[0x28] + (int)(short)uVar4 * (int)(short)uVar7 +
             iVar47 + (int)sVar29 * (int)psVar19[0x21] +
             (int)sVar22 * (int)(short)((uint6)uVar5 >> 0x10) + (int)sVar33 * (int)psVar19[0x29] +
             (int)sVar23 * (int)(short)((uint6)uVar7 >> 0x10) +
             iVar48 + (int)sVar30 * (int)psVar19[0x22] +
             (int)sVar24 * (int)(short)((uint6)uVar5 >> 0x20) + (int)sVar34 * (int)psVar19[0x2a] +
             (int)sVar25 * (int)(short)((uint6)uVar7 >> 0x20) +
             iVar49 + (int)sVar31 * (int)psVar19[0x23] + (int)sVar26 * (int)psVar19[0x27] +
             (int)sVar35 * (int)psVar19[0x2b] + (int)sVar27 * (int)psVar19[0x2f];
  *param_6 = iVar50 + (int)sVar28 * (int)sVar36 + (int)(short)uVar3 * (int)(short)uVar6 +
             (int)sVar32 * (int)sVar41 + (int)(short)uVar4 * (int)(short)uVar8 +
             iVar51 + (int)sVar29 * (int)sVar37 + (int)sVar22 * (int)(short)((uint6)uVar6 >> 0x10) +
             (int)sVar33 * (int)sVar42 + (int)sVar23 * (int)(short)((uint6)uVar8 >> 0x10) +
             iVar52 + (int)sVar30 * (int)sVar38 + (int)sVar24 * (int)(short)((uint6)uVar6 >> 0x20) +
             (int)sVar34 * (int)sVar43 + (int)sVar25 * (int)(short)((uint6)uVar8 >> 0x20) +
             iVar53 + (int)sVar31 * (int)sVar39 + (int)sVar26 * (int)sVar40 +
             (int)sVar35 * (int)sVar44 + (int)sVar27 * (int)sVar45;
  return puVar18 + 0x18;
}


/* Biquad_Narrow_int2int_stereo @ 00106d8c size 276 */

void Biquad_Narrow_int2int_stereo
               (undefined8 *param_1,undefined8 *param_2,int *param_3,long *param_4,int param_5)

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  long lVar3;
  ulong uVar4;
  long lVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined1 uVar10;
  undefined1 uVar11;
  undefined1 uVar12;
  undefined1 uVar13;
  undefined1 uVar14;
  undefined1 uVar15;
  undefined1 uVar16;
  undefined1 uVar17;
  undefined1 uVar18;
  undefined1 uVar19;
  undefined1 uVar20;
  undefined1 uVar21;
  undefined1 uVar22;
  undefined1 uVar23;
  undefined1 uVar24;
  undefined1 uVar25;
  int iVar26;
  int iVar27;
  int iVar28;
  int iVar29;
  int iVar30;
  undefined1 auVar31 [16];
  undefined8 uVar32;
  int iVar33;
  int iVar34;
  int iVar35;
  int iVar36;
  int iVar37;
  int iVar38;
  int iVar39;
  int iVar40;
  int iVar41;
  undefined1 auVar42 [16];
  
  lVar3 = param_4[9];
  uVar10 = (undefined1)lVar3;
  uVar11 = (undefined1)((ulong)lVar3 >> 8);
  uVar12 = (undefined1)((ulong)lVar3 >> 0x10);
  uVar13 = (undefined1)((ulong)lVar3 >> 0x18);
  uVar14 = (undefined1)((ulong)lVar3 >> 0x20);
  uVar15 = (undefined1)((ulong)lVar3 >> 0x28);
  uVar16 = (undefined1)((ulong)lVar3 >> 0x30);
  uVar17 = (undefined1)((ulong)lVar3 >> 0x38);
  iVar26 = (int)param_4[7];
  lVar3 = param_4[4];
  uVar18 = (undefined1)lVar3;
  uVar19 = (undefined1)((ulong)lVar3 >> 8);
  uVar20 = (undefined1)((ulong)lVar3 >> 0x10);
  uVar21 = (undefined1)((ulong)lVar3 >> 0x18);
  uVar22 = (undefined1)((ulong)lVar3 >> 0x20);
  uVar23 = (undefined1)((ulong)lVar3 >> 0x28);
  uVar24 = (undefined1)((ulong)lVar3 >> 0x30);
  uVar25 = (undefined1)((ulong)lVar3 >> 0x38);
  iVar28 = (int)param_4[8];
  uVar32 = CONCAT44((int)*param_4,(int)param_4[5]);
  iVar27 = (int)param_4[2];
  param_5 = param_5 + 2;
  iVar29 = (int)param_4[3];
  iVar30 = *param_3;
  iVar34 = param_3[1];
  iVar35 = param_3[2];
  iVar36 = param_3[3];
  iVar37 = param_3[4];
  iVar7 = (int)param_4[6];
  iVar9 = (int)param_4[1];
  do {
    param_5 = param_5 + -2;
    iVar38 = (int)*param_2 << 7;
    iVar39 = (int)((ulong)*param_2 >> 0x20) << 7;
    iVar40 = (int)param_2[1] << 7;
    iVar41 = (int)((ulong)param_2[1] >> 0x20) << 7;
    iVar33 = (int)((ulong)uVar32 >> 0x20);
    lVar3 = CONCAT17(uVar17,CONCAT16(uVar16,CONCAT15(uVar15,CONCAT14(uVar14,CONCAT13(uVar13,CONCAT12
                                                  (uVar12,CONCAT11(uVar11,uVar10))))))) +
            (long)iVar38 * (long)iVar30 + (long)(int)uVar32 * (long)iVar34 +
            (long)iVar7 * (long)iVar35 + (long)iVar26 * (long)iVar36;
    lVar5 = CONCAT17(uVar25,CONCAT16(uVar24,CONCAT15(uVar23,CONCAT14(uVar22,CONCAT13(uVar21,CONCAT12
                                                  (uVar20,CONCAT11(uVar19,uVar18))))))) +
            (long)iVar39 * (long)iVar30 + (long)iVar33 * (long)iVar34 + (long)iVar9 * (long)iVar35 +
            (long)iVar27 * (long)iVar36;
    iVar6 = (int)((ulong)(lVar3 + (long)iVar28 * (long)iVar37) >> 0x20);
    iVar8 = (int)((ulong)(lVar5 + (long)iVar29 * (long)iVar37) >> 0x20);
    iVar7 = iVar28 * iVar37;
    iVar9 = iVar29 * iVar37;
    iVar28 = iVar6 << 3;
    iVar29 = iVar8 << 3;
    lVar3 = (ulong)(uint)((int)lVar3 + iVar7) + (long)iVar40 * (long)iVar30 +
            (long)iVar38 * (long)iVar34 + (long)(int)uVar32 * (long)iVar35 +
            (long)iVar28 * (long)iVar36;
    lVar5 = (ulong)(uint)((int)lVar5 + iVar9) + (long)iVar41 * (long)iVar30 +
            (long)iVar39 * (long)iVar34 + (long)iVar33 * (long)iVar35 + (long)iVar29 * (long)iVar36;
    iVar7 = (int)((ulong)(lVar3 + (long)iVar26 * (long)iVar37) >> 0x20);
    iVar9 = (int)((ulong)(lVar5 + (long)iVar27 * (long)iVar37) >> 0x20);
    uVar4 = lVar3 + (long)iVar26 * (long)iVar37;
    uVar10 = (undefined1)uVar4;
    uVar11 = (undefined1)(uVar4 >> 8);
    uVar12 = (undefined1)(uVar4 >> 0x10);
    uVar13 = (undefined1)(uVar4 >> 0x18);
    lVar5 = lVar5 + (long)iVar27 * (long)iVar37;
    uVar18 = (undefined1)lVar5;
    uVar19 = (undefined1)((ulong)lVar5 >> 8);
    uVar20 = (undefined1)((ulong)lVar5 >> 0x10);
    uVar21 = (undefined1)((ulong)lVar5 >> 0x18);
    uVar14 = 0;
    uVar15 = 0;
    uVar16 = 0;
    uVar17 = 0;
    uVar22 = 0;
    uVar23 = 0;
    uVar24 = 0;
    uVar25 = 0;
    auVar42._4_4_ = iVar39;
    auVar42._0_4_ = iVar38;
    auVar42._8_4_ = iVar40;
    auVar42._12_4_ = iVar41;
    auVar31._4_4_ = iVar39;
    auVar31._0_4_ = iVar38;
    auVar31._8_4_ = iVar40;
    auVar31._12_4_ = iVar41;
    auVar42 = NEON_ext(auVar42,auVar31,8,1);
    iVar26 = iVar7 << 3;
    iVar27 = iVar9 << 3;
    uVar32 = auVar42._0_8_;
    param_1[1] = CONCAT44(iVar9 + 8 >> 4,iVar7 + 8 >> 4);
    *param_1 = CONCAT44(iVar8 + 8 >> 4,iVar6 + 8 >> 4);
    param_1 = param_1 + 2;
    param_2 = param_2 + 2;
    iVar7 = iVar38;
    iVar9 = iVar39;
  } while (2 < param_5);
  auVar1[8] = uVar18;
  auVar1._0_8_ = uVar4 & 0xffffffff;
  auVar1[9] = uVar19;
  auVar1[10] = uVar20;
  auVar1[0xb] = uVar21;
  auVar1._12_4_ = 0;
  auVar2[8] = uVar18;
  auVar2._0_8_ = uVar4 & 0xffffffff;
  auVar2[9] = uVar19;
  auVar2[10] = uVar20;
  auVar2[0xb] = uVar21;
  auVar2._12_4_ = 0;
  auVar31 = NEON_ext(auVar1,auVar2,8,1);
  param_4[6] = (long)iVar38;
  param_4[1] = (long)iVar39;
  *param_4 = (long)auVar42._4_4_;
  param_4[3] = (long)iVar29;
  param_4[2] = (long)iVar27;
  param_4[8] = (long)iVar28;
  param_4[7] = (long)iVar26;
  param_4[5] = (long)auVar42._0_4_;
  param_4[4] = (long)auVar31._0_4_;
  param_4[9] = (long)(int)uVar4;
  return;
}


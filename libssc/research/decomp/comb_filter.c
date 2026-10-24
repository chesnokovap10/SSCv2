/* comb_filter @ 0010a83c size 2404 */

void comb_filter(int *param_1,int *param_2,uint param_3,uint param_4,int param_5,short param_6,
                short param_7,ulong param_8)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  short sVar9;
  short sVar10;
  int iVar11;
  undefined1 (*pauVar12) [12];
  undefined8 uVar13;
  undefined1 auVar14 [16];
  undefined8 uVar15;
  undefined8 uVar16;
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  ushort uVar21;
  uint6 uVar22;
  ushort uVar23;
  int *piVar24;
  int *piVar25;
  long lVar26;
  long lVar27;
  int *piVar28;
  long lVar29;
  ulong uVar30;
  uint *puVar31;
  int iVar32;
  long lVar33;
  ulong uVar34;
  int iVar35;
  long lVar36;
  long lVar37;
  int iVar38;
  ulong uVar39;
  int iVar42;
  uint uVar43;
  undefined1 auVar40 [14];
  int iVar44;
  undefined1 auVar41 [16];
  undefined4 uVar45;
  undefined8 uVar46;
  undefined8 uVar47;
  int iVar48;
  int iVar49;
  int iVar50;
  int iVar51;
  int iVar52;
  int iVar53;
  int iVar54;
  int iVar55;
  int iVar56;
  int iVar57;
  int iVar58;
  undefined1 auVar59 [16];
  undefined8 uVar60;
  undefined8 uVar61;
  undefined1 auVar62 [16];
  int iVar63;
  int iVar64;
  int iVar65;
  int iVar66;
  undefined1 auVar67 [16];
  
  iVar35 = (int)param_8;
  if (param_7 == 0 && param_6 == 0) {
    if (param_2 == param_1) {
      return;
    }
    goto LAB_0010b180;
  }
  iVar4 = param_2[(int)-param_4];
  iVar42 = param_2[(int)~param_4];
  iVar44 = param_2[(int)(1 - param_4)];
  iVar48 = param_2[(int)(-2 - param_4)];
  iVar11 = (int)param_7;
  uVar43 = iVar11 * 0x2740;
  uVar5 = uVar43 >> 0xf;
  iVar2 = iVar11 * 0x1bc8 >> 0xf;
  iVar11 = iVar11 * 0x1098 >> 0xf;
  sVar9 = (short)uVar5;
  if (param_6 == 0) {
    lVar26 = ((ulong)(iVar35 - 1) & 0xffff) + 1;
    lVar33 = 0;
    piVar28 = param_1 + lVar26;
    param_8 = param_8 & 0xffffffff;
    do {
      iVar38 = iVar42;
      iVar42 = iVar4;
      iVar4 = (int)*(uint *)((long)&win_square + lVar33) >> 0x10;
      uVar6 = *(uint *)((long)&win_square + lVar33) & 0xffff;
      iVar32 = *(int *)((long)param_2 + lVar33 + (long)(int)(2 - param_4) * 4);
      uVar7 = (int)param_8 - 1;
      param_8 = (ulong)uVar7;
      *(int *)((long)param_1 + lVar33) =
           *(int *)((long)param_2 + lVar33) +
           (int)((long)(iVar2 * 2 * iVar4 + ((int)(uVar6 * iVar2) >> 0xf)) * (long)(iVar38 + iVar44)
                 + (long)(int)((-(uVar43 >> 0x1e & 1) & 0xfffe0000 | (uVar5 & 0xffff) << 1) * iVar4
                              + ((int)(uVar6 * (int)sVar9) >> 0xf)) * (long)iVar42 +
                 (long)(iVar11 * 2 * iVar4 + ((int)(uVar6 * iVar11) >> 0xf)) *
                 (long)(iVar32 + iVar48) + 0x40000000U >> 0x1f);
      lVar33 = lVar33 + 4;
      iVar4 = iVar44;
      iVar44 = iVar32;
      iVar48 = iVar38;
    } while ((uVar7 & 0xffff) != 0);
    piVar25 = param_2 + lVar26;
    if (param_7 == 0) {
      if (param_2 == param_1) {
        return;
      }
      param_5 = param_5 - iVar35;
      param_1 = piVar28;
      param_2 = piVar25;
      goto LAB_0010b180;
    }
LAB_0010ad68:
    if (0 < param_5 - iVar35) {
      uVar34 = (ulong)(uint)(param_5 - iVar35);
      iVar35 = 2 - param_4;
      piVar24 = piVar25;
      iVar4 = piVar25[(int)(1 - param_4)];
      iVar42 = piVar25[(int)-param_4];
      iVar44 = piVar25[(int)~param_4];
      iVar48 = piVar25[(int)(-2 - param_4)];
      do {
        iVar32 = iVar44;
        iVar44 = iVar42;
        iVar42 = iVar4;
        iVar4 = piVar25[iVar35];
        uVar34 = uVar34 - 1;
        *piVar28 = *piVar24 +
                   (int)((long)(short)iVar2 * (long)(iVar32 + iVar42) + (long)sVar9 * (long)iVar44 +
                         (long)(short)iVar11 * (long)(iVar4 + iVar48) + 0x4000U >> 0xf);
        iVar35 = iVar35 + 1;
        piVar24 = piVar24 + 1;
        piVar28 = piVar28 + 1;
        iVar48 = iVar32;
      } while (uVar34 != 0);
    }
    return;
  }
  iVar38 = (int)param_6;
  uVar7 = iVar38 * 0x2740;
  uVar6 = uVar7 >> 0xf;
  iVar32 = iVar38 * 0x1bc8 >> 0xf;
  iVar38 = iVar38 * 0x1098 >> 0xf;
  sVar10 = (short)uVar6;
  if (param_7 != 0) {
    uVar6 = -(uVar7 >> 0x1e & 1) & 0xfffe0000 | (uVar6 & 0xffff) << 1;
    if (param_3 == param_4) {
      param_8 = param_8 & 0xffffffff;
      piVar28 = param_1;
      puVar31 = &win_square;
      piVar25 = param_2;
      do {
        iVar51 = iVar42;
        iVar42 = iVar4;
        iVar50 = piVar25[(int)(2 - param_4)];
        uVar3 = *puVar31;
        iVar4 = (int)uVar3 >> 0x10;
        uVar7 = uVar3 & 0xffff;
        iVar49 = (int)(0x7fffffff - uVar3) >> 0x10;
        uVar3 = 0x7fffffff - uVar3 & 0xffff;
        uVar8 = (int)param_8 - 1;
        param_8 = (ulong)uVar8;
        *piVar28 = *piVar25 +
                   (int)(((long)(iVar32 * 2 * iVar49 + ((int)(uVar3 * iVar32) >> 0xf)) +
                         (long)(iVar2 * 2 * iVar4 + ((int)(uVar7 * iVar2) >> 0xf))) *
                         (long)(iVar51 + iVar44) +
                         ((long)(iVar38 * 2 * iVar49 + ((int)(uVar3 * iVar38) >> 0xf)) +
                         (long)(iVar11 * 2 * iVar4 + ((int)(uVar7 * iVar11) >> 0xf))) *
                         (long)(iVar50 + iVar48) +
                         ((long)(int)(uVar6 * iVar49 + ((int)(uVar3 * (int)sVar10) >> 0xf)) +
                         (long)(int)((-(uVar43 >> 0x1e & 1) & 0xfffe0000 | (uVar5 & 0xffff) << 1) *
                                     iVar4 + ((int)(uVar7 * (int)sVar9) >> 0xf))) * (long)iVar42 +
                         0x40000000U >> 0x1f);
        piVar28 = piVar28 + 1;
        puVar31 = puVar31 + 1;
        piVar25 = piVar25 + 1;
        iVar4 = iVar44;
        iVar44 = iVar50;
        iVar48 = iVar51;
      } while ((uVar8 & 0xffff) != 0);
    }
    else {
      param_8 = param_8 & 0xffffffff;
      piVar28 = param_1;
      piVar25 = param_2;
      puVar31 = &win_square;
      do {
        iVar51 = iVar42;
        iVar42 = iVar4;
        iVar50 = piVar25[(int)(2 - param_4)];
        uVar3 = *puVar31;
        iVar4 = (int)uVar3 >> 0x10;
        uVar7 = uVar3 & 0xffff;
        iVar49 = (int)(0x7fffffff - uVar3) >> 0x10;
        uVar3 = 0x7fffffff - uVar3 & 0xffff;
        uVar8 = (int)param_8 - 1;
        param_8 = (ulong)uVar8;
        *piVar28 = *piVar25 +
                   (int)((long)(int)((-(uVar43 >> 0x1e & 1) & 0xfffe0000 | (uVar5 & 0xffff) << 1) *
                                     iVar4 + ((int)(uVar7 * (int)sVar9) >> 0xf)) * (long)iVar42 +
                         (long)(iVar2 * 2 * iVar4 + ((int)(uVar7 * iVar2) >> 0xf)) *
                         (long)(iVar51 + iVar44) +
                         (long)(iVar11 * 2 * iVar4 + ((int)(uVar7 * iVar11) >> 0xf)) *
                         (long)(iVar50 + iVar48) +
                         (long)(iVar32 * 2 * iVar49 + ((int)(uVar3 * iVar32) >> 0xf)) *
                         ((long)piVar25[(int)~param_3] + (long)piVar25[(int)(1 - param_3)]) +
                         (long)(int)(uVar6 * iVar49 + ((int)(uVar3 * (int)sVar10) >> 0xf)) *
                         (long)piVar25[-(long)(int)param_3] +
                         ((long)piVar25[(int)(-2 - param_3)] + (long)piVar25[(int)(2 - param_3)]) *
                         (long)(iVar38 * 2 * iVar49 + ((int)(uVar3 * iVar38) >> 0xf)) + 0x40000000U
                        >> 0x1f);
        piVar28 = piVar28 + 1;
        piVar25 = piVar25 + 1;
        puVar31 = puVar31 + 1;
        iVar4 = iVar44;
        iVar44 = iVar50;
        iVar48 = iVar51;
      } while ((uVar8 & 0xffff) != 0);
    }
    lVar26 = ((ulong)(iVar35 - 1) & 0xffff) + 1;
    piVar28 = param_1 + lVar26;
    piVar25 = param_2 + lVar26;
    goto LAB_0010ad68;
  }
  lVar37 = (long)(int)(2 - param_3);
  lVar26 = (long)(int)(-2 - param_3);
  piVar28 = &win_square;
  uVar30 = (ulong)(iVar35 - 1) & 0xffff;
  uVar34 = uVar30 + 1;
  iVar4 = (int)sVar10;
  uVar5 = -(uVar7 >> 0x1e & 1) & 0xfffe0000 | (uVar6 & 0xffff) << 1;
  iVar2 = iVar32 * 2;
  iVar11 = iVar38 * 2;
  lVar33 = (long)(int)~param_3;
  lVar36 = (long)(int)(1 - param_3);
  piVar25 = param_2;
  piVar24 = param_1;
  if (uVar34 < 4) {
    uVar39 = param_8 & 0xffffffff;
LAB_0010b0d4:
    do {
      uVar6 = (int)uVar39 - 1;
      uVar39 = (ulong)uVar6;
      iVar42 = (int)(0x7fffffffU - *piVar28) >> 0x10;
      uVar43 = 0x7fffffffU - *piVar28 & 0xffff;
      *piVar24 = *piVar25 +
                 (int)((long)(int)(uVar5 * iVar42 + ((int)(uVar43 * iVar4) >> 0xf)) *
                       (long)piVar25[-(long)(int)param_3] +
                       (long)(iVar2 * iVar42 + ((int)(uVar43 * iVar32) >> 0xf)) *
                       ((long)piVar25[lVar33] + (long)piVar25[lVar36]) +
                       ((long)piVar25[lVar26] + (long)piVar25[lVar37]) *
                       (long)(iVar11 * iVar42 + ((int)(uVar43 * iVar38) >> 0xf)) + 0x40000000U >>
                      0x1f);
      piVar28 = piVar28 + 1;
      piVar25 = piVar25 + 1;
      piVar24 = piVar24 + 1;
    } while ((uVar6 & 0xffff) != 0);
  }
  else {
    uVar39 = (ulong)(iVar35 - 1) & 0xffff;
    lVar27 = uVar39 + 1;
    piVar1 = param_1 + lVar27;
    if ((((param_1 < &win_square + lVar27 && &win_square < piVar1) ||
         (param_1 < param_2 + lVar27 && param_2 < piVar1)) ||
        (param_1 < param_2 + lVar26 + uVar39 + 1 && param_2 + lVar26 < piVar1)) ||
       ((param_1 < param_2 + lVar37 + uVar39 + 1 && param_2 + lVar37 < piVar1 ||
        (param_1 < param_2 + lVar33 + uVar39 + 1 && param_2 + lVar33 < piVar1)))) {
      uVar39 = param_8 & 0xffffffff;
      goto LAB_0010b0d4;
    }
    if (param_1 < param_2 + lVar36 + uVar39 + 1 && param_2 + lVar36 < piVar1) {
      uVar39 = param_8 & 0xffffffff;
      goto LAB_0010b0d4;
    }
    uVar39 = param_8 & 0xffffffff;
    if (param_1 < param_2 + (lVar27 - (int)param_3) && param_2 + (int)-param_3 < piVar1)
    goto LAB_0010b0d4;
    lVar29 = uVar34 - (param_8 & 3);
    lVar27 = (uVar30 + 1) - (param_8 & 3);
    uVar39 = (ulong)(uint)(iVar35 - (int)lVar29);
    do {
      uVar47 = *(undefined8 *)(piVar25 + lVar36 + 2);
      uVar46 = *(undefined8 *)(piVar25 + lVar36);
      uVar16 = *(undefined8 *)(piVar25 + lVar33 + 2);
      uVar15 = *(undefined8 *)(piVar25 + lVar33);
      uVar61 = *(undefined8 *)(piVar25 + lVar37 + 2);
      uVar60 = *(undefined8 *)(piVar25 + lVar37);
      piVar1 = piVar25 + lVar26;
      iVar42 = 0x7fffffff - piVar28[1];
      uVar43 = 0x7fffffff - piVar28[2];
      iVar44 = 0x7fffffff - piVar28[3];
      pauVar12 = (undefined1 (*) [12])(piVar25 + -(long)(int)param_3);
      uVar45 = (undefined4)((ulong)*(undefined8 *)((long)*pauVar12 + 8) >> 0x20);
      uVar13 = *(undefined8 *)*pauVar12;
      iVar48 = *piVar1 + (int)uVar60;
      iVar49 = piVar1[1] + (int)((ulong)uVar60 >> 0x20);
      iVar50 = piVar1[2] + (int)uVar61;
      iVar51 = piVar1[3] + (int)((ulong)uVar61 >> 0x20);
      iVar52 = 0x7fffffff - *piVar28 >> 0x10;
      iVar53 = iVar42 >> 0x10;
      iVar55 = (int)uVar43 >> 0x10;
      iVar57 = iVar44 >> 0x10;
      uVar22 = CONCAT15((char)((uint)iVar42 >> 8),CONCAT14((char)iVar42,0x7fffffff - *piVar28)) &
               0xffff0000ffff;
      auVar40._0_12_ = ZEXT212((ushort)uVar43) << 0x40;
      auVar40[0xc] = (undefined1)iVar44;
      auVar40[0xd] = (undefined1)((uint)iVar44 >> 8);
      iVar42 = (int)uVar22;
      uVar23 = (ushort)(uVar22 >> 0x20);
      uVar21 = auVar40._12_2_;
      iVar63 = uVar5 * iVar52 + (iVar42 * iVar4 >> 0xf);
      iVar64 = uVar5 * iVar53 + ((int)((uint)uVar23 * iVar4) >> 0xf);
      iVar65 = uVar5 * iVar55 + ((int)((uVar43 & 0xffff) * iVar4) >> 0xf);
      iVar66 = uVar5 * iVar57 + ((int)((uint)uVar21 * iVar4) >> 0xf);
      auVar41._12_4_ = uVar45;
      auVar41._0_12_ = *pauVar12;
      auVar59._12_4_ = uVar45;
      auVar59._0_12_ = *pauVar12;
      auVar62 = NEON_ext(auVar41,auVar59,8,1);
      iVar44 = iVar11 * iVar52 + (iVar42 * iVar38 >> 0xf);
      iVar54 = iVar11 * iVar53 + ((int)((uint)uVar23 * iVar38) >> 0xf);
      iVar56 = iVar11 * iVar55 + ((int)((uVar43 & 0xffff) * iVar38) >> 0xf);
      iVar58 = iVar11 * iVar57 + ((int)((uint)uVar21 * iVar38) >> 0xf);
      auVar19._4_4_ = iVar64;
      auVar19._0_4_ = iVar63;
      auVar19._8_4_ = iVar65;
      auVar19._12_4_ = iVar66;
      auVar20._4_4_ = iVar64;
      auVar20._0_4_ = iVar63;
      auVar20._8_4_ = iVar65;
      auVar20._12_4_ = iVar66;
      auVar41 = NEON_ext(auVar19,auVar20,8,1);
      uVar61 = *(undefined8 *)(piVar25 + 2);
      uVar60 = *(undefined8 *)piVar25;
      auVar67._4_4_ = iVar49;
      auVar67._0_4_ = iVar48;
      auVar67._8_4_ = iVar50;
      auVar67._12_4_ = iVar51;
      auVar14._4_4_ = iVar49;
      auVar14._0_4_ = iVar48;
      auVar14._8_4_ = iVar50;
      auVar14._12_4_ = iVar51;
      auVar59 = NEON_ext(auVar67,auVar14,8,1);
      auVar17._4_4_ = iVar54;
      auVar17._0_4_ = iVar44;
      auVar17._8_4_ = iVar56;
      auVar17._12_4_ = iVar58;
      auVar18._4_4_ = iVar54;
      auVar18._0_4_ = iVar44;
      auVar18._8_4_ = iVar56;
      auVar18._12_4_ = iVar58;
      auVar67 = NEON_ext(auVar17,auVar18,8,1);
      lVar27 = lVar27 + -4;
      piVar24[2] = (int)uVar61 +
                   (int)((long)(iVar2 * iVar55 + ((int)((uVar43 & 0xffff) * iVar32) >> 0xf)) *
                         (long)((int)uVar16 + (int)uVar47) +
                         (long)auVar41._0_4_ * (long)auVar62._0_4_ +
                         (long)auVar59._0_4_ * (long)auVar67._0_4_ + 0x40000000U >> 0x1f);
      piVar24[3] = (int)((ulong)uVar61 >> 0x20) +
                   (int)((long)(iVar2 * iVar57 + ((int)((uint)uVar21 * iVar32) >> 0xf)) *
                         (long)((int)((ulong)uVar16 >> 0x20) + (int)((ulong)uVar47 >> 0x20)) +
                         (long)auVar41._4_4_ * (long)auVar62._4_4_ +
                         (long)auVar59._4_4_ * (long)auVar67._4_4_ + 0x40000000U >> 0x1f);
      *piVar24 = (int)uVar60 +
                 (int)((long)(iVar2 * iVar52 + (iVar42 * iVar32 >> 0xf)) *
                       (long)((int)uVar15 + (int)uVar46) + (long)iVar63 * (long)(int)uVar13 +
                       (long)iVar48 * (long)iVar44 + 0x40000000U >> 0x1f);
      piVar24[1] = (int)((ulong)uVar60 >> 0x20) +
                   (int)((long)(iVar2 * iVar53 + ((int)((uint)uVar23 * iVar32) >> 0xf)) *
                         (long)((int)((ulong)uVar15 >> 0x20) + (int)((ulong)uVar46 >> 0x20)) +
                         (long)iVar64 * (long)(int)((ulong)uVar13 >> 0x20) +
                         (long)iVar49 * (long)iVar54 + 0x40000000U >> 0x1f);
      piVar28 = piVar28 + 4;
      piVar25 = piVar25 + 4;
      piVar24 = piVar24 + 4;
    } while (lVar27 != 0);
    piVar28 = &win_square + lVar29;
    piVar25 = param_2 + lVar29;
    piVar24 = param_1 + lVar29;
    if ((param_8 & 3) != 0) goto LAB_0010b0d4;
  }
  if (param_2 == param_1) {
    return;
  }
  param_5 = param_5 - iVar35;
  param_1 = param_1 + uVar34;
  param_2 = param_2 + uVar34;
LAB_0010b180:
  SSC_COPY32(param_1,param_2,param_5);
  return;
}


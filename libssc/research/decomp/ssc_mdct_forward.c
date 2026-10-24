/* ssc_mdct_forward @ 00106dec size 1000 */

void ssc_mdct_forward(int *param_1,long param_2,undefined4 *param_3,int *param_4,uint param_5,
                     uint param_6,uint param_7)

{
  int *piVar1;
  uint uVar2;
  ulong uVar3;
  ulong uVar4;
  int iVar5;
  uint uVar6;
  long lVar7;
  int *piVar8;
  int iVar9;
  int *piVar10;
  long lVar11;
  int *piVar12;
  int iVar13;
  uint uVar14;
  ulong uVar15;
  int *piVar16;
  undefined4 *puVar17;
  long lVar18;
  long lVar19;
  int *piVar20;
  long lVar21;
  int iVar22;
  int *piVar23;
  
  uVar2 = *param_1 >> (param_6 & 0x1f);
  piVar23 = &_pre_shared;
  uVar14 = 0x7fffff22;
  if (param_6 != 0) {
    uVar14 = 0x7fffc88c;
  }
  uVar3 = (ulong)uVar14;
  lVar7 = param_2 + (long)((int)uVar2 >> 1) * 4;
  uVar14 = 0xee4bb;
  if (param_6 != 0) {
    uVar14 = 0x7725c6;
  }
  uVar4 = (ulong)uVar14;
  iVar13 = (int)(param_5 + 3) >> 2;
  iVar22 = (int)uVar2 >> 2;
  lVar11 = lVar7 + -4;
  uVar14 = 0;
  if ((int)param_5 < 1) {
    uVar15 = -(ulong)((uint)((int)param_5 >> 1) >> 0x1f) & 0xfffffffc00000000 |
             (ulong)(uint)((int)param_5 >> 1) << 2;
    piVar12 = (int *)(param_2 + uVar15);
    piVar10 = (int *)(lVar11 + uVar15);
    uVar6 = iVar22 - iVar13;
    lVar7 = (long)((ulong)uVar2 << 0x20) >> 0x21;
    if ((int)uVar6 < 1) goto joined_r0x00106f70;
  }
  else {
    lVar21 = (long)((ulong)param_5 << 0x20) >> 0x21;
    piVar16 = param_4 + -1;
    lVar18 = param_2 + -4;
    lVar19 = lVar21 * 4;
    piVar12 = param_4;
    piVar10 = &_pre_shared;
    do {
      uVar14 = uVar14 + 1;
      piVar23 = piVar10 + 2;
      *piVar10 = (int)((long)piVar12[lVar21] * (long)*(int *)(lVar11 + lVar19) +
                       (long)piVar16[lVar21] * (long)*(int *)(lVar7 + lVar19) + 0x40000000U >> 0x1f)
      ;
      piVar8 = piVar12 + lVar21;
      piVar20 = (int *)(lVar18 + lVar19);
      lVar11 = lVar11 + -8;
      lVar7 = lVar7 + 8;
      piVar1 = piVar16 + lVar21;
      piVar16 = piVar16 + -2;
      piVar12 = piVar12 + 2;
      lVar18 = lVar18 + -8;
      piVar10[1] = (int)((ulong)(((long)*piVar8 * (long)*(int *)(param_2 + lVar19) + 0x40000000) -
                                (long)*piVar1 * (long)*piVar20) >> 0x1f);
      param_2 = param_2 + 8;
      piVar10 = piVar23;
    } while ((int)uVar14 < iVar13);
    piVar10 = (int *)(lVar11 + lVar19);
    piVar12 = (int *)(param_2 + lVar19);
    uVar6 = iVar22 - iVar13;
    lVar7 = (long)((ulong)uVar2 << 0x20) >> 0x21;
    if ((int)uVar6 <= (int)uVar14) goto joined_r0x00106f70;
  }
  uVar15 = (ulong)((iVar22 + ~uVar14) - iVar13);
  lVar11 = uVar15 * 2 + 2;
  piVar16 = piVar23 + lVar11;
  iVar13 = (iVar22 - uVar14) - iVar13;
  piVar8 = piVar12;
  piVar20 = piVar10;
  do {
    iVar13 = iVar13 + -1;
    *piVar23 = *piVar20;
    piVar23[1] = *piVar8;
    piVar23 = piVar23 + 2;
    piVar8 = piVar8 + 2;
    piVar20 = piVar20 + -2;
  } while (iVar13 != 0);
  piVar12 = piVar12 + lVar11;
  piVar10 = piVar10 + uVar15 * -2 + -2;
  piVar23 = piVar16;
  uVar14 = uVar6;
joined_r0x00106f70:
  if ((int)uVar14 < iVar22) {
    iVar13 = iVar22 - uVar14;
    piVar16 = param_4 + (long)(int)param_5 + -1;
    do {
      iVar13 = iVar13 + -1;
      *piVar23 = (int)((ulong)(((long)*piVar16 * (long)*piVar10 + 0x40000000) -
                              (long)*param_4 * (long)piVar12[-lVar7]) >> 0x1f);
      iVar9 = *piVar12;
      piVar8 = piVar10 + lVar7;
      piVar12 = piVar12 + 2;
      piVar10 = piVar10 + -2;
      piVar23[1] = (int)((long)*param_4 * (long)*piVar8 + (long)*piVar16 * (long)iVar9 + 0x40000000U
                        >> 0x1f);
      piVar23 = piVar23 + 2;
      param_4 = param_4 + 2;
      piVar16 = piVar16 + -2;
    } while (iVar13 != 0);
  }
  iVar13 = iVar22 << (ulong)(param_6 & 0x1f);
  if ((int)uVar2 < 4) {
    uVar2 = 1 << (ulong)(param_6 & 0x1f);
  }
  else {
    piVar12 = *(int **)(param_1 + 6);
    uVar2 = 1 << (ulong)(param_6 & 0x1f);
    uVar15 = -(ulong)(uVar2 >> 0x1f) & 0xfffffffc00000000 | (ulong)uVar2 << 2;
    iVar9 = 0;
    piVar23 = piVar12 + iVar13;
    piVar10 = &_pre_shared;
    do {
      iVar5 = *piVar12;
      iVar9 = iVar9 + 1;
      piVar12 = (int *)((long)piVar12 + uVar15);
      lVar21 = (long)-(((long)*piVar23 * (long)piVar10[1] + (long)iVar5 * (long)*piVar10) * 2 +
                       0x80000000U & 0xffffffff00000000) >> 0x20;
      lVar11 = ((long)*piVar23 * (long)*piVar10 - (long)iVar5 * (long)piVar10[1]) * 2 + 0x80000000
               >> 0x20;
      piVar23 = (int *)((long)piVar23 - uVar15);
      *piVar10 = (int)(lVar21 * uVar3 + lVar11 * uVar4 + 0x40000000 >> 0x1f);
      piVar10[1] = (int)((lVar11 * uVar3 + 0x40000000) - lVar21 * uVar4 >> 0x1f);
      piVar10 = piVar10 + 2;
    } while (iVar9 < iVar22);
  }
  ssc_fft(*(undefined8 *)(param_1 + (long)((int)param_6 >> 1) * 2 + 2),&_pre_shared,&DAT_0012dcd0);
  piVar10 = *(int **)(param_1 + 6);
  uVar15 = -(ulong)((param_7 & 0x7fffffff) >> 0x1e) & 0xfffffffc00000000 |
           (ulong)(param_7 << 1) << 2;
  piVar23 = &DAT_0012dcd4;
  puVar17 = param_3 + (int)(((int)lVar7 + -1) * param_7);
  piVar12 = piVar10 + iVar13;
  do {
    iVar13 = *piVar12;
    iVar22 = iVar22 + -1;
    piVar12 = piVar12 + -(long)(int)uVar2;
    lVar11 = ((long)iVar13 * (long)*piVar23 + (long)*piVar10 * (long)piVar23[-1]) * 2 + 0x80000000
             >> 0x20;
    lVar7 = ((long)piVar23[-1] * (long)iVar13 - (long)*piVar10 * (long)*piVar23) * 2 + 0x80000000 >>
            0x20;
    piVar10 = piVar10 + (int)uVar2;
    piVar23 = piVar23 + 2;
    *param_3 = (int)((lVar11 * uVar3 + 0x40000000) - lVar7 * uVar4 >> 0x1f);
    param_3 = (undefined4 *)((long)param_3 + uVar15);
    *puVar17 = (int)(lVar7 * uVar3 + lVar11 * uVar4 + 0x40000000 >> 0x1f);
    puVar17 = (undefined4 *)((long)puVar17 - uVar15);
  } while (iVar22 != 0);
  return;
}


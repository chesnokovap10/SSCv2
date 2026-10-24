/* powercalc @ 0010b2fc size 228 */

void powercalc(int *param_1,uint param_2,undefined4 *param_3)

{
  uint uVar1;
  int *piVar2;
  int *piVar5;
  ulong uVar8;
  int *piVar9;
  long lVar10;
  int *piVar11;
  long lVar12;
  long lVar13;
  long lVar14;
  long lVar15;
  int iVar16;
  int *piVar3;
  int *piVar4;
  int *piVar6;
  int *piVar7;
  
  if (param_2 == 0) {
    *param_3 = 0;
    return;
  }
  uVar8 = (ulong)(param_2 - 1) + 1;
  if (uVar8 < 4) {
    uVar8 = 0;
  }
  else {
    uVar1 = param_2 & 3;
    lVar10 = uVar8 - uVar1;
    piVar9 = param_1 + 4;
    lVar12 = 0;
    lVar13 = 0;
    param_1 = param_1 + lVar10 * 2;
    param_2 = param_2 - (int)lVar10;
    lVar14 = 0;
    lVar15 = 0;
    do {
      piVar11 = piVar9 + -4;
      iVar16 = *piVar9;
      piVar2 = piVar9 + 1;
      piVar3 = piVar9 + 2;
      piVar4 = piVar9 + 3;
      piVar5 = piVar9 + -3;
      piVar6 = piVar9 + -2;
      piVar7 = piVar9 + -1;
      lVar10 = lVar10 + -4;
      piVar9 = piVar9 + 8;
      lVar14 = lVar14 + ((int)((ulong)((long)iVar16 * (long)iVar16) >> 0x10) >> 1) +
               (long)((int)((ulong)((long)*piVar2 * (long)*piVar2) >> 0x10) >> 1);
      lVar15 = lVar15 + ((int)((ulong)((long)*piVar3 * (long)*piVar3) >> 0x10) >> 1) +
               (long)((int)((ulong)((long)*piVar4 * (long)*piVar4) >> 0x10) >> 1);
      lVar12 = lVar12 + ((int)((ulong)((long)*piVar11 * (long)*piVar11) >> 0x10) >> 1) +
               (long)((int)((ulong)((long)*piVar5 * (long)*piVar5) >> 0x10) >> 1);
      lVar13 = lVar13 + ((int)((ulong)((long)*piVar6 * (long)*piVar6) >> 0x10) >> 1) +
               (long)((int)((ulong)((long)*piVar7 * (long)*piVar7) >> 0x10) >> 1);
    } while (lVar10 != 0);
    uVar8 = lVar14 + lVar12 + lVar15 + lVar13;
    if (uVar1 == 0) goto LAB_0010b3d4;
  }
  do {
    param_2 = param_2 - 1;
    uVar8 = uVar8 + (long)((int)((ulong)((long)*param_1 * (long)*param_1) >> 0x10) >> 1) +
            (long)((int)((ulong)((long)param_1[1] * (long)param_1[1]) >> 0x10) >> 1);
    param_1 = param_1 + 2;
  } while (param_2 != 0);
LAB_0010b3d4:
  *param_3 = (int)(uVar8 >> 9);
  return;
}


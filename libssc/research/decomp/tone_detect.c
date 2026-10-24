/* tone_detect @ 00112088 size 428 */

undefined8 tone_detect(long param_1,uint *param_2,int param_3,int param_4)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  ulong uVar7;
  int iVar8;
  uint uVar9;
  long lVar10;
  long lVar11;
  
  uVar9 = *param_2;
  iVar8 = (int)((ulong)((long)param_3 * 0x7730) >> 0xf);
  if ((*(int *)(param_1 + (long)(int)uVar9 * 4) < iVar8) ||
     (uVar6 = param_2[1], *(int *)(param_1 + (long)(int)uVar6 * 4) < iVar8)) {
    return 0;
  }
  uVar2 = uVar6;
  if ((int)uVar9 <= (int)uVar6) {
    uVar2 = uVar9;
    uVar9 = uVar6;
  }
  uVar6 = -uVar2;
  lVar11 = param_1 + (long)(int)uVar9 * 4;
  if (*(int *)(lVar11 + 4) <= *(int *)(lVar11 + -4)) {
    uVar6 = ~uVar2;
  }
  uVar6 = uVar6 + uVar9;
  if (4 < (int)uVar6) {
    lVar10 = (ulong)uVar2 << 0x20;
    lVar11 = lVar10 + 0x300000000;
    uVar7 = 2;
    do {
      lVar10 = lVar10 + 0x100000000;
      iVar5 = *(int *)(param_1 + (long)(int)uVar2 * 4 + uVar7 * 4);
      if (iVar8 < iVar5) {
        iVar3 = *(int *)(param_1 + (lVar11 >> 0x1e));
        uVar6 = (uint)uVar7;
        if (iVar3 < iVar5) {
          uVar6 = uVar6 - (iVar3 < *(int *)(param_1 + (lVar10 >> 0x1e)));
        }
        if ((int)uVar6 < 5) {
          return 0;
        }
        if (param_4 >> 1 < (int)uVar6) {
          return 0;
        }
        break;
      }
      uVar7 = uVar7 + 1;
      lVar11 = lVar11 + 0x100000000;
    } while (uVar6 != uVar7);
    if (param_4 >> 1 < (int)uVar6) {
      return 0;
    }
    uVar2 = uVar6;
    for (iVar5 = uVar6 + uVar9; iVar5 < param_4 + -1; iVar5 = uVar2 + iVar5) {
      piVar1 = (int *)(param_1 + (long)iVar5 * 4);
      iVar3 = *piVar1;
      iVar4 = piVar1[1];
      uVar2 = uVar6;
      if (iVar3 <= iVar4) {
        uVar2 = uVar6 + 1;
        iVar3 = iVar4;
      }
      if (iVar3 < iVar8) {
        return 0;
      }
    }
    uVar2 = iVar5 - uVar2;
    uVar9 = uVar9 - uVar6;
    do {
      if ((int)uVar9 < 1) {
        uVar6 = uVar2 - uVar6;
        if ((int)uVar6 < 1) {
          return 0;
        }
        if (param_4 <= (int)uVar2) {
          return 0;
        }
        if (*(int *)(param_1 + (ulong)uVar6 * 4) <= *(int *)(param_1 + (ulong)(uVar6 - 1) * 4)) {
          uVar6 = uVar6 - 1;
        }
        *param_2 = uVar2;
        param_2[1] = uVar6;
        return 1;
      }
      iVar3 = *(int *)(param_1 + (ulong)uVar9 * 4);
      iVar4 = *(int *)(param_1 + (ulong)(uVar9 - 1) * 4);
      iVar5 = iVar3;
      if (iVar3 <= iVar4) {
        iVar5 = iVar4;
      }
      uVar9 = (uVar9 - uVar6) - (uint)(iVar3 <= iVar4);
    } while (iVar8 <= iVar5);
  }
  return 0;
}


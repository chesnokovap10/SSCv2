/* tone_detect @ 001076b0 size 480 */

undefined4 tone_detect(long param_1,uint *param_2,int param_3,int param_4)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  long lVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  long lVar12;
  long lVar13;
  
  uVar6 = *param_2;
  iVar8 = (int)((ulong)((long)param_3 * 0x7730) >> 0xf);
  if (*(int *)(param_1 + (long)(int)uVar6 * 4) < iVar8) {
    return 0;
  }
  uVar9 = param_2[1];
  if (*(int *)(param_1 + (long)(int)uVar9 * 4) < iVar8) {
    return 0;
  }
  uVar3 = uVar6;
  if ((int)uVar6 <= (int)uVar9) {
    uVar3 = uVar9;
  }
  lVar7 = param_1 + (long)(int)uVar3 * 4;
  if ((int)uVar6 <= (int)uVar9) {
    uVar9 = uVar6;
  }
  iVar10 = (uVar3 - uVar9) - (uint)(*(int *)(lVar7 + 4) <= *(int *)(lVar7 + -4));
  if (iVar10 < 5) {
    return 0;
  }
  lVar12 = (ulong)uVar9 << 0x20;
  lVar13 = lVar12 + 0x300000000;
  lVar7 = 2;
  do {
    lVar12 = lVar12 + 0x100000000;
    iVar11 = *(int *)(param_1 + (long)(int)uVar9 * 4 + lVar7 * 4);
    if (iVar8 < iVar11) {
      iVar2 = *(int *)(param_1 + (lVar13 >> 0x1e));
      iVar10 = (int)lVar7;
      if (iVar2 < iVar11) {
        iVar10 = iVar10 - (uint)(iVar2 < *(int *)(param_1 + (lVar12 >> 0x1e)));
      }
      if (iVar10 < 5) {
        return 0;
      }
      if (param_4 >> 1 < iVar10) {
        return 0;
      }
      break;
    }
    lVar7 = lVar7 + 1;
    lVar13 = lVar13 + 0x100000000;
  } while (lVar7 < iVar10);
  if (param_4 >> 1 < iVar10) {
    return 0;
  }
  iVar11 = iVar10 + uVar3;
  iVar2 = iVar10;
  while( true ) {
    if (param_4 + -1 <= iVar11) {
      uVar6 = iVar11 - iVar2;
      iVar11 = uVar3 - iVar10;
      do {
        if (iVar11 < 1) {
          uVar9 = uVar6 - iVar10;
          if (*(int *)(param_1 + (long)(int)uVar9 * 4) <=
              *(int *)(param_1 + ((long)(int)uVar9 + -1) * 4)) {
            uVar9 = (uint)((long)(int)uVar9 + -1);
          }
          if (param_4 <= (int)uVar6) {
            return 0;
          }
          if ((int)uVar9 < 0) {
            return 0;
          }
          *param_2 = uVar6;
          param_2[1] = uVar9;
          return 1;
        }
        piVar1 = (int *)(param_1 + (long)iVar11 * 4);
        iVar4 = piVar1[-1];
        iVar5 = *piVar1;
        iVar2 = iVar10;
        if (iVar5 <= iVar4) {
          iVar2 = iVar10 + 1;
          iVar5 = iVar4;
        }
        iVar4 = 0;
        if (iVar8 <= iVar5) {
          iVar4 = iVar2;
        }
        iVar11 = iVar11 - iVar4;
      } while (iVar8 <= iVar5);
      return 0;
    }
    piVar1 = (int *)(param_1 + (long)iVar11 * 4);
    iVar4 = *piVar1;
    iVar5 = piVar1[1];
    iVar2 = iVar10;
    if (iVar4 <= iVar5) {
      iVar2 = iVar10 + 1;
      iVar4 = iVar5;
    }
    if (iVar4 < iVar8) break;
    iVar11 = iVar2 + iVar11;
  }
  return 0;
}


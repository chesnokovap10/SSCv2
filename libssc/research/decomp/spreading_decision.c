/* spreading_decision @ 001036a0 size 808 */

undefined1
spreading_decision(long param_1,long param_2,int *param_3,int param_4,int *param_5,uint *param_6,
                  int param_7,uint param_8)

{
  ulong uVar1;
  ulong uVar2;
  uint uVar3;
  ushort uVar4;
  int iVar5;
  ulong uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  long lVar12;
  uint uVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  long lVar17;
  int iVar18;
  
  if ((int)param_8 < 9) {
    iVar7 = 0;
    iVar8 = 0;
  }
  else {
    lVar12 = *(long *)(param_1 + 0x10);
    iVar7 = 0;
    iVar8 = 0;
    iVar9 = 0;
    uVar13 = (uint)*(ushort *)(lVar12 + 0x10);
    uVar6 = 8;
    uVar11 = uVar13;
    do {
      uVar1 = uVar6 + 1;
      uVar4 = *(ushort *)(lVar12 + uVar1 * 2);
      iVar5 = (int)(short)uVar4 - (int)(short)uVar11;
      if (1 < iVar5) {
        iVar5 = iVar5 * 8;
        lVar17 = 0;
        iVar16 = 0;
        iVar10 = 0;
        iVar14 = 0;
LAB_0010371c:
        do {
          iVar18 = (int)*(short *)(param_2 + (long)(int)(-(uVar11 >> 0xf) & 0xfff80000 | uVar11 << 3
                                                        ) * 2 + lVar17 * 2);
          iVar18 = ((uint)(iVar18 * iVar18) >> 0xf) * iVar5;
          if (iVar18 < 0x80) {
            iVar10 = iVar10 + 2;
          }
          else if (0x1ff < iVar18) {
            iVar15 = iVar14 + 2;
            if (0x7ff < iVar18) {
              iVar15 = iVar14;
            }
            lVar17 = lVar17 + 1;
            iVar14 = iVar15;
            if (iVar5 <= lVar17) break;
            goto LAB_0010371c;
          }
          lVar17 = lVar17 + 1;
          iVar16 = iVar16 + 2;
          iVar15 = iVar14 + 2;
          iVar14 = iVar15;
        } while (lVar17 < iVar5);
        if ((long)*(int *)(param_1 + 8) + -4 < (long)uVar6) {
          iVar14 = 0;
          if (iVar5 != 0) {
            iVar14 = ((iVar15 + iVar16) * 0x20) / iVar5;
          }
          iVar9 = iVar14 + iVar9;
        }
        uVar11 = 2;
        if (iVar10 < iVar5) {
          uVar11 = 1;
        }
        uVar3 = (uint)(iVar5 <= iVar10);
        if (iVar5 <= iVar16) {
          uVar3 = uVar11;
        }
        if (iVar5 <= iVar15) {
          uVar3 = uVar3 + 1;
        }
        iVar7 = iVar7 + uVar3 * 0x100;
        iVar8 = iVar8 + 1;
      }
      uVar11 = (uint)uVar4;
      uVar6 = uVar1;
    } while (uVar1 != param_8);
    uVar6 = 8;
    do {
      uVar2 = uVar6 + 1;
      uVar4 = *(ushort *)(lVar12 + uVar2 * 2);
      iVar5 = (int)(short)uVar4 - (int)(short)uVar13;
      if (1 < iVar5) {
        iVar5 = iVar5 * 8;
        lVar17 = 0;
        iVar16 = 0;
        iVar10 = 0;
        iVar14 = 0;
LAB_00103824:
        do {
          iVar18 = (int)*(short *)(param_2 + 0x6c0 +
                                   (long)(int)(-(uVar13 >> 0xf) & 0xfff80000 | uVar13 << 3) * 2 +
                                  lVar17 * 2);
          iVar18 = ((uint)(iVar18 * iVar18) >> 0xf) * iVar5;
          if (iVar18 < 0x80) {
            iVar10 = iVar10 + 2;
          }
          else if (0x1ff < iVar18) {
            iVar15 = iVar14 + 2;
            if (0x7ff < iVar18) {
              iVar15 = iVar14;
            }
            lVar17 = lVar17 + 1;
            iVar14 = iVar15;
            if (iVar5 <= lVar17) break;
            goto LAB_00103824;
          }
          lVar17 = lVar17 + 1;
          iVar16 = iVar16 + 2;
          iVar15 = iVar14 + 2;
          iVar14 = iVar15;
        } while (lVar17 < iVar5);
        if ((long)*(int *)(param_1 + 8) + -4 < (long)uVar6) {
          iVar14 = 0;
          if (iVar5 != 0) {
            iVar14 = ((iVar15 + iVar16) * 0x20) / iVar5;
          }
          iVar9 = iVar14 + iVar9;
        }
        uVar11 = 2;
        if (iVar10 < iVar5) {
          uVar11 = 1;
        }
        uVar13 = (uint)(iVar5 <= iVar10);
        if (iVar5 <= iVar16) {
          uVar13 = uVar11;
        }
        if (iVar5 <= iVar15) {
          uVar13 = uVar13 + 1;
        }
        iVar7 = iVar7 + uVar13 * 0x100;
        iVar8 = iVar8 + 1;
      }
      uVar13 = (uint)uVar4;
      uVar6 = uVar2;
    } while (uVar2 != uVar1);
    if (iVar9 != 0) {
      iVar5 = ((param_8 + 4) - *(int *)(param_1 + 8)) * 2;
      iVar10 = 0;
      if (iVar5 != 0) {
        iVar10 = iVar9 / iVar5;
      }
      goto joined_r0x00103924;
    }
  }
  iVar10 = 0;
joined_r0x00103924:
  if (param_7 != 0) {
    iVar9 = *param_5 + iVar10 >> 1;
    *param_5 = iVar9;
    if (*param_6 == 0) {
      iVar9 = iVar9 + -4;
    }
    else if (*param_6 == 2) {
      iVar9 = iVar9 + 4;
    }
    uVar11 = 2;
    if (iVar9 < 0x17) {
      uVar11 = (uint)(0x12 < iVar9);
    }
    *param_6 = uVar11;
  }
  iVar9 = 0;
  if (iVar8 != 0) {
    iVar9 = iVar7 / iVar8;
  }
  iVar7 = *param_3 + iVar9 >> 1;
  iVar8 = (param_4 * -0x80 + 0x180U | 0x42) + (*param_3 + iVar9 & 0xfffffffeU) + iVar7;
  *param_3 = iVar7;
  if (iVar8 < 0x140) {
    return 3;
  }
  if (iVar8 < 0x400) {
    return 2;
  }
  return iVar8 < 0x600;
}


/* ssc_spreading_decision @ 001085ac size 592 */

undefined1 ssc_spreading_decision(long *param_1,long param_2,int param_3,uint param_4)

{
  ulong uVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  ushort uVar6;
  undefined1 uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  uint uVar15;
  long lVar16;
  ulong uVar17;
  int iVar18;
  int iVar19;
  short *psVar20;
  ulong uVar21;
  
  if ((int)param_4 < 9) {
    iVar13 = 0;
    iVar14 = 0;
    iVar12 = 0;
  }
  else {
    iVar12 = 0;
    iVar14 = 0;
    iVar13 = 0;
    lVar16 = *(long *)(*param_1 + 0x10);
    uVar17 = 8;
    uVar6 = *(ushort *)(lVar16 + 0x10);
    do {
      uVar1 = uVar17 + 1;
      uVar2 = *(ushort *)(lVar16 + uVar1 * 2);
      iVar18 = (int)(short)uVar2 - (int)(short)uVar6;
      if (1 < iVar18) {
        uVar3 = iVar18 * 8;
        iVar18 = 0;
        iVar8 = 0;
        iVar9 = 0;
        iVar10 = 0;
        iVar19 = 0;
        iVar11 = 0;
        psVar20 = (short *)(param_2 +
                           (long)(int)(-(uint)(uVar6 >> 0xf) & 0xfff80000 | (uint)uVar6 << 3) * 2);
        uVar15 = uVar3;
        if ((int)uVar3 < 2) {
          uVar15 = 1;
        }
        uVar21 = (ulong)uVar15;
        do {
          uVar15 = ((uint)((int)*psVar20 * (int)*psVar20) >> 0xf) * uVar3;
          if ((int)uVar15 < 0x80) {
            iVar19 = iVar19 + 2;
            iVar10 = iVar10 + 2;
            iVar4 = iVar11 + 2;
          }
          else if (uVar15 < 0x200) {
            iVar19 = iVar19 + 2;
            iVar4 = iVar11 + 2;
          }
          else {
            iVar4 = iVar11 + 2;
            if (0x7ff < uVar15) {
              iVar4 = iVar11;
            }
          }
          iVar11 = iVar4;
          uVar15 = ((uint)((int)psVar20[0x360] * (int)psVar20[0x360]) >> 0xf) * uVar3;
          if ((int)uVar15 < 0x80) {
            iVar8 = iVar8 + 2;
            iVar18 = iVar18 + 2;
            iVar4 = iVar9 + 2;
          }
          else if (uVar15 < 0x200) {
            iVar8 = iVar8 + 2;
            iVar4 = iVar9 + 2;
          }
          else {
            iVar4 = iVar9 + 2;
            if (0x7ff < uVar15) {
              iVar4 = iVar9;
            }
          }
          iVar9 = iVar4;
          psVar20 = psVar20 + 1;
          uVar21 = uVar21 - 1;
        } while (uVar21 != 0);
        if ((long)*(int *)(*param_1 + 8) + -4 < (long)uVar17) {
          iVar4 = 0;
          if (uVar3 != 0) {
            iVar4 = ((iVar19 + iVar11) * 0x20) / (int)uVar3;
          }
          iVar5 = 0;
          if (uVar3 != 0) {
            iVar5 = ((iVar8 + iVar9) * 0x20) / (int)uVar3;
          }
          iVar13 = iVar4 + iVar13 + iVar5;
        }
        iVar14 = iVar14 + 2;
        uVar15 = (uint)((int)uVar3 <= iVar19);
        if ((int)uVar3 <= iVar11) {
          uVar15 = uVar15 + 1;
        }
        if ((int)uVar3 <= iVar10) {
          uVar15 = uVar15 + 1;
        }
        if ((int)uVar3 <= iVar9) {
          uVar15 = uVar15 + 1;
        }
        if ((int)uVar3 <= iVar8) {
          uVar15 = uVar15 + 1;
        }
        if ((int)uVar3 <= iVar18) {
          uVar15 = uVar15 + 1;
        }
        iVar12 = iVar12 + uVar15 * 0x100;
      }
      uVar17 = uVar1;
      uVar6 = uVar2;
    } while (uVar1 != param_4);
  }
  if (param_3 != 0) {
    iVar13 = (int)param_1[6] + (iVar13 >> 3) >> 1;
    *(int *)(param_1 + 6) = iVar13;
    if (*(int *)((long)param_1 + 0x34) == 0) {
      iVar13 = iVar13 + -4;
    }
    else if (*(int *)((long)param_1 + 0x34) == 2) {
      iVar13 = iVar13 + 4;
    }
    uVar15 = 2;
    if (iVar13 < 0x17) {
      uVar15 = (uint)(0x12 < iVar13);
    }
    *(uint *)((long)param_1 + 0x34) = uVar15;
  }
  iVar13 = iVar12;
  if ((1 < iVar14) && (iVar13 = 0, iVar14 != 0)) {
    iVar13 = iVar12 / iVar14;
  }
  uVar15 = (int)param_1[5] + iVar13;
  iVar14 = (int)uVar15 >> 1;
  uVar15 = (uVar15 & 0xfffffffe) + iVar14 + (int)param_1[4] * -0x80 + 0x1c0;
  *(int *)(param_1 + 5) = iVar14;
  if ((int)uVar15 < 0x13e) {
    uVar7 = 3;
  }
  else if (uVar15 < 0x3fe) {
    uVar7 = 2;
  }
  else {
    uVar7 = uVar15 < 0x5fe;
  }
  return uVar7;
}


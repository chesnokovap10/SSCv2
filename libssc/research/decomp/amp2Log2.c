/* amp2Log2 @ 001096a0 size 664 */

void amp2Log2(long param_1,uint param_2,int param_3,long param_4,long param_5,int param_6)

{
  char *pcVar1;
  int iVar2;
  uint uVar3;
  short sVar4;
  long lVar5;
  int iVar6;
  ulong uVar7;
  ulong uVar8;
  undefined8 *puVar9;
  undefined2 *puVar10;
  long lVar11;
  long lVar12;
  int iVar13;
  ulong uVar14;
  int iVar15;
  
  lVar5 = (long)(int)param_2;
  if ((int)param_2 < 1) {
    uVar7 = param_3 - lVar5;
    uVar8 = uVar7 & 0xfffffffffffffff0;
    iVar15 = 0;
    do {
      if ((int)param_2 < param_3) {
        iVar6 = *(int *)(param_1 + 8);
        lVar11 = lVar5;
        if (0xf < uVar7) {
          puVar9 = (undefined8 *)(param_5 + 0x10 + (lVar5 + iVar6 * iVar15) * 2);
          uVar14 = uVar8;
          do {
            puVar9[-1] = 0xc800c800c800c800;
            puVar9[-2] = 0xc800c800c800c800;
            puVar9[1] = 0xc800c800c800c800;
            *puVar9 = 0xc800c800c800c800;
            uVar14 = uVar14 - 0x10;
            puVar9 = puVar9 + 4;
          } while (uVar14 != 0);
          lVar11 = uVar8 + lVar5;
          if (uVar7 == uVar8) goto LAB_00109908;
        }
        lVar12 = param_3 - lVar11;
        puVar10 = (undefined2 *)(param_5 + (lVar11 + iVar6 * iVar15) * 2);
        do {
          lVar12 = lVar12 + -1;
          *puVar10 = 0xc800;
          puVar10 = puVar10 + 1;
        } while (lVar12 != 0);
      }
LAB_00109908:
      iVar15 = iVar15 + 1;
    } while (iVar15 < param_6);
  }
  else {
    iVar6 = *(int *)(param_1 + 8);
    uVar7 = param_3 - lVar5;
    uVar8 = uVar7 & 0xfffffffffffffff0;
    iVar15 = 0;
    do {
      uVar14 = 0;
      do {
        iVar13 = (int)uVar14;
        iVar2 = *(int *)(param_4 + (long)(iVar13 + iVar15 * iVar6) * 4) << 2;
        if (iVar2 == 0) {
          sVar4 = -0x7fff;
        }
        else {
          sVar4 = ec_ilog(iVar2);
          sVar4 = sVar4 + -1;
          uVar3 = (int)sVar4 - 0xf;
          iVar6 = iVar2 >> (uVar3 & 0x1f);
          if ((int)uVar3 < 1) {
            iVar6 = iVar2 << (ulong)(0xfU - (int)sVar4 & 0x1f);
          }
          iVar2 = iVar6 * 0x10000 + 0x40000000 >> 0x10;
          iVar6 = *(int *)(param_1 + 8);
          sVar4 = sVar4 * 0x400 +
                  (short)((int)((((int)((((int)((((iVar2 * -0x579 >> 0xf) + 0x9f1) * iVar2 * 2 &
                                                0xffff0000U) + 0xeb9f0000) >> 0x10) * iVar2 * 2 &
                                        0xffff0000U) + 0x3d820000) >> 0x10) * iVar2 * 2 &
                                0xffff0000U) + 0xe5770000) >> 0x14) + -0x3400;
        }
        pcVar1 = (char *)((long)&eMeans + uVar14);
        uVar14 = uVar14 + 1;
        *(short *)(param_5 + (long)(iVar13 + iVar15 * iVar6) * 2) = sVar4 + *pcVar1 * -0x40;
      } while (param_2 != uVar14);
      if ((int)param_2 < param_3) {
        lVar11 = lVar5;
        if (0xf < uVar7) {
          puVar9 = (undefined8 *)(param_5 + 0x10 + (lVar5 + iVar15 * iVar6) * 2);
          uVar14 = uVar8;
          do {
            puVar9[-1] = 0xc800c800c800c800;
            puVar9[-2] = 0xc800c800c800c800;
            puVar9[1] = 0xc800c800c800c800;
            *puVar9 = 0xc800c800c800c800;
            uVar14 = uVar14 - 0x10;
            puVar9 = puVar9 + 4;
          } while (uVar14 != 0);
          lVar11 = uVar8 + lVar5;
          if (uVar7 == uVar8) goto LAB_00109874;
        }
        lVar12 = param_3 - lVar11;
        puVar10 = (undefined2 *)(param_5 + (lVar11 + iVar15 * iVar6) * 2);
        do {
          lVar12 = lVar12 + -1;
          *puVar10 = 0xc800;
          puVar10 = puVar10 + 1;
        } while (lVar12 != 0);
      }
LAB_00109874:
      iVar15 = iVar15 + 1;
    } while (iVar15 < param_6);
  }
  return;
}


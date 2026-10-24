/* FUN_00106180 @ 00106180 size 716 */

void FUN_00106180(int *param_1,long param_2,uint param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  long lVar9;
  int iVar10;
  long lVar11;
  long lVar12;
  long lVar13;
  int iVar14;
  long lVar15;
  int iVar16;
  int iVar17;
  ulong uVar18;
  ulong uVar19;
  ulong uVar20;
  ulong uVar21;
  
  lVar9 = *(long *)(param_2 + 0x10);
  param_3 = ~param_3;
  do {
    uVar18 = (long)(int)*(undefined8 *)(param_1 + 8) * 0x2aaaaaab + 0x40000000;
    uVar19 = (long)(int)((ulong)*(undefined8 *)(param_1 + 8) >> 0x20) * 0x2aaaaaab + 0x40000000;
    uVar20 = (long)(int)*(undefined8 *)(param_1 + 0xe) * 0x2aaaaaab + 0x40000000;
    uVar21 = (long)(int)((ulong)*(undefined8 *)(param_1 + 0xe) >> 0x20) * 0x2aaaaaab + 0x40000000;
    *(ulong *)(param_1 + 8) = CONCAT44((int)(uVar19 >> 0x1f),(int)(uVar18 >> 0x1f));
    *(ulong *)(param_1 + 0xe) = CONCAT44((int)(uVar21 >> 0x1f),(int)(uVar20 >> 0x1f));
    iVar10 = (int)((long)(int)*(undefined8 *)(param_1 + 2) * 0x2aaaaaab + 0x40000000U >> 0x1f);
    iVar17 = (int)((long)(int)((ulong)*(undefined8 *)(param_1 + 2) >> 0x20) * 0x2aaaaaab +
                   0x40000000U >> 0x1f);
    iVar5 = (int)((long)param_1[6] * 0x2aaaaaab + 0x40000000U >> 0x1f);
    iVar7 = (int)((long)param_1[0xc] * 0x2aaaaaab + 0x40000000U >> 0x1f);
    iVar4 = iVar7 + iVar5;
    iVar8 = (int)((long)param_1[0xd] * 0x2aaaaaab + 0x40000000U >> 0x1f);
    iVar6 = (int)((long)param_1[7] * 0x2aaaaaab + 0x40000000U >> 0x1f);
    iVar14 = iVar6 + iVar8;
    iVar16 = (int)((long)*param_1 * 0x2aaaaaab + 0x40000000U >> 0x1f);
    iVar1 = iVar16 - (iVar4 >> 1);
    iVar3 = (int)((long)param_1[1] * 0x2aaaaaab + 0x40000000U >> 0x1f);
    iVar2 = iVar3 - (iVar14 >> 1);
    *param_1 = iVar4 + iVar16;
    param_1[1] = iVar14 + iVar3;
    iVar4 = (int)((long)(iVar6 - iVar8) * -0x6ed9eba1 + 0x40000000U >> 0x1f);
    iVar14 = (int)((long)(iVar5 - iVar7) * -0x6ed9eba1 + 0x40000000U >> 0x1f);
    *(ulong *)(param_1 + 2) = CONCAT44(iVar17,iVar10);
    param_1[0xc] = iVar1 + iVar4;
    param_1[0xd] = iVar2 - iVar14;
    param_1[6] = iVar1 - iVar4;
    param_1[7] = iVar2 + iVar14;
    lVar15 = (long)(int)(uVar18 >> 0x1f);
    lVar13 = (long)(int)(uVar19 >> 0x1f);
    lVar12 = (long)(int)(uVar20 >> 0x1f);
    lVar11 = (long)(int)(uVar21 >> 0x1f);
    iVar5 = (int)((ulong)((lVar15 * *(int *)(lVar9 + 0x180) + 0x40000000) -
                         lVar13 * *(int *)(lVar9 + 0x184)) >> 0x1f);
    iVar8 = (int)((ulong)((lVar12 * *(int *)(lVar9 + 0x300) + 0x40000000) -
                         lVar11 * *(int *)(lVar9 + 0x304)) >> 0x1f);
    iVar4 = iVar8 + iVar5;
    iVar7 = (int)(lVar15 * *(int *)(lVar9 + 0x184) + lVar13 * *(int *)(lVar9 + 0x180) + 0x40000000U
                 >> 0x1f);
    iVar6 = (int)(lVar12 * *(int *)(lVar9 + 0x304) + lVar11 * *(int *)(lVar9 + 0x300) + 0x40000000U
                 >> 0x1f);
    iVar14 = iVar6 + iVar7;
    uVar20 = (long)(int)*(undefined8 *)(param_1 + 10) * 0x2aaaaaab + 0x40000000;
    uVar21 = (long)(int)((ulong)*(undefined8 *)(param_1 + 10) >> 0x20) * 0x2aaaaaab + 0x40000000;
    uVar18 = (long)(int)*(undefined8 *)(param_1 + 0x10) * 0x2aaaaaab + 0x40000000;
    uVar19 = (long)(int)((ulong)*(undefined8 *)(param_1 + 0x10) >> 0x20) * 0x2aaaaaab + 0x40000000;
    iVar1 = iVar10 - (iVar4 >> 1);
    iVar2 = iVar17 - (iVar14 >> 1);
    iVar3 = (int)((long)(int)*(undefined8 *)(param_1 + 4) * 0x2aaaaaab + 0x40000000U >> 0x1f);
    iVar16 = (int)((long)(int)((ulong)*(undefined8 *)(param_1 + 4) >> 0x20) * 0x2aaaaaab +
                   0x40000000U >> 0x1f);
    param_1[2] = iVar4 + iVar10;
    param_1[3] = iVar14 + iVar17;
    iVar14 = (int)((long)(iVar5 - iVar8) * -0x6ed9eba1 + 0x40000000U >> 0x1f);
    iVar4 = (int)((long)(iVar7 - iVar6) * -0x6ed9eba1 + 0x40000000U >> 0x1f);
    *(ulong *)(param_1 + 4) = CONCAT44(iVar16,iVar3);
    *(ulong *)(param_1 + 10) = CONCAT44((int)(uVar21 >> 0x1f),(int)(uVar20 >> 0x1f));
    *(ulong *)(param_1 + 0x10) = CONCAT44((int)(uVar19 >> 0x1f),(int)(uVar18 >> 0x1f));
    param_1[0xe] = iVar1 + iVar4;
    param_1[0xf] = iVar2 - iVar14;
    param_1[8] = iVar1 - iVar4;
    param_1[9] = iVar2 + iVar14;
    lVar11 = (long)(int)(uVar20 >> 0x1f);
    lVar13 = (long)(int)(uVar21 >> 0x1f);
    lVar12 = (long)(int)(uVar18 >> 0x1f);
    lVar15 = (long)(int)(uVar19 >> 0x1f);
    iVar6 = (int)((ulong)((lVar11 * *(int *)(lVar9 + 0x300) + 0x40000000) -
                         lVar13 * *(int *)(lVar9 + 0x304)) >> 0x1f);
    iVar7 = (int)((ulong)((lVar12 * *(int *)(lVar9 + 0x600) + 0x40000000) -
                         lVar15 * *(int *)(lVar9 + 0x604)) >> 0x1f);
    iVar4 = iVar7 + iVar6;
    iVar10 = (int)(lVar11 * *(int *)(lVar9 + 0x304) + lVar13 * *(int *)(lVar9 + 0x300) + 0x40000000U
                  >> 0x1f);
    iVar5 = (int)(lVar12 * *(int *)(lVar9 + 0x604) + lVar15 * *(int *)(lVar9 + 0x600) + 0x40000000U
                 >> 0x1f);
    iVar14 = iVar5 + iVar10;
    iVar1 = iVar3 - (iVar4 >> 1);
    iVar2 = iVar16 - (iVar14 >> 1);
    param_1[4] = iVar4 + iVar3;
    param_1[5] = iVar14 + iVar16;
    iVar14 = (int)((long)(iVar6 - iVar7) * -0x6ed9eba1 + 0x40000000U >> 0x1f);
    iVar4 = (int)((long)(iVar10 - iVar5) * -0x6ed9eba1 + 0x40000000U >> 0x1f);
    param_3 = param_3 + 1;
    param_1[0x10] = iVar1 + iVar4;
    param_1[0x11] = iVar2 - iVar14;
    param_1[10] = iVar1 - iVar4;
    param_1[0xb] = iVar2 + iVar14;
    param_1 = param_1 + 0x12;
  } while (param_3 != 0);
  return;
}


/* FUN_0010644c @ 0010644c size 512 */

void FUN_0010644c(int *param_1,long param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  long lVar6;
  long lVar7;
  int iVar8;
  long lVar9;
  int iVar10;
  int iVar11;
  long lVar12;
  int iVar13;
  int iVar14;
  long lVar15;
  long lVar16;
  int *piVar17;
  int *piVar18;
  int iVar19;
  ulong uVar20;
  ulong uVar21;
  ulong uVar22;
  ulong uVar23;
  undefined8 uVar24;
  undefined8 uVar25;
  undefined8 uVar26;
  
  if (0 < param_3) {
    lVar15 = *(long *)(param_2 + 0x10);
    iVar14 = 0;
    do {
      iVar19 = (int)((long)param_1[0x12] * 0x2aaaaaab + 0x40000000U >> 0x1f);
      iVar4 = (int)((long)param_1[0x24] * 0x2aaaaaab + 0x40000000U >> 0x1f);
      iVar5 = iVar4 + iVar19;
      iVar8 = (int)((long)param_1[0x25] * 0x2aaaaaab + 0x40000000U >> 0x1f);
      iVar3 = (int)((long)param_1[0x13] * 0x2aaaaaab + 0x40000000U >> 0x1f);
      iVar11 = iVar3 + iVar8;
      iVar10 = (int)((long)*param_1 * 0x2aaaaaab + 0x40000000U >> 0x1f);
      iVar1 = iVar10 - (iVar5 >> 1);
      iVar13 = (int)((long)param_1[1] * 0x2aaaaaab + 0x40000000U >> 0x1f);
      iVar2 = iVar13 - (iVar11 >> 1);
      *param_1 = iVar5 + iVar10;
      param_1[1] = iVar11 + iVar13;
      iVar11 = (int)((long)(iVar3 - iVar8) * -0x6ed9eba1 + 0x40000000U >> 0x1f);
      iVar5 = (int)((long)(iVar19 - iVar4) * -0x6ed9eba1 + 0x40000000U >> 0x1f);
      param_1[0x12] = iVar1 - iVar11;
      param_1[0x13] = iVar2 + iVar5;
      param_1[0x24] = iVar1 + iVar11;
      param_1[0x25] = iVar2 - iVar5;
      lVar16 = 0;
      piVar17 = (int *)(lVar15 + 0x84);
      piVar18 = (int *)(lVar15 + 0x104);
      do {
        uVar24 = *(undefined8 *)((long)param_1 + lVar16 + 8);
        uVar26 = *(undefined8 *)((long)param_1 + lVar16 + 0x50);
        uVar25 = *(undefined8 *)((long)param_1 + lVar16 + 0x98);
        uVar22 = (long)(int)uVar26 * 0x2aaaaaab + 0x40000000;
        uVar23 = (long)(int)((ulong)uVar26 >> 0x20) * 0x2aaaaaab + 0x40000000;
        iVar3 = (int)((long)(int)uVar24 * 0x2aaaaaab + 0x40000000U >> 0x1f);
        iVar19 = (int)((long)(int)((ulong)uVar24 >> 0x20) * 0x2aaaaaab + 0x40000000U >> 0x1f);
        uVar20 = (long)(int)uVar25 * 0x2aaaaaab + 0x40000000;
        uVar21 = (long)(int)((ulong)uVar25 >> 0x20) * 0x2aaaaaab + 0x40000000;
        *(ulong *)((long)param_1 + lVar16 + 0x50) =
             CONCAT44((int)(uVar23 >> 0x1f),(int)(uVar22 >> 0x1f));
        *(ulong *)((long)param_1 + lVar16 + 8) = CONCAT44(iVar19,iVar3);
        *(ulong *)((long)param_1 + lVar16 + 0x98) =
             CONCAT44((int)(uVar21 >> 0x1f),(int)(uVar20 >> 0x1f));
        lVar7 = (long)(int)(uVar22 >> 0x1f);
        lVar6 = (long)(int)(uVar23 >> 0x1f);
        lVar12 = (long)(int)(uVar20 >> 0x1f);
        lVar9 = (long)(int)(uVar21 >> 0x1f);
        iVar10 = (int)((ulong)((lVar7 * piVar17[-1] + 0x40000000) - lVar6 * *piVar17) >> 0x1f);
        iVar13 = (int)((ulong)((lVar12 * piVar18[-1] + 0x40000000) - lVar9 * *piVar18) >> 0x1f);
        iVar5 = iVar13 + iVar10;
        iVar4 = (int)(lVar7 * *piVar17 + lVar6 * piVar17[-1] + 0x40000000U >> 0x1f);
        iVar8 = (int)(lVar12 * *piVar18 + lVar9 * piVar18[-1] + 0x40000000U >> 0x1f);
        iVar11 = iVar8 + iVar4;
        lVar6 = lVar16 + 8;
        iVar1 = iVar3 - (iVar5 >> 1);
        iVar2 = iVar19 - (iVar11 >> 1);
        piVar18 = piVar18 + 0x40;
        *(int *)((long)param_1 + lVar16 + 8) = iVar5 + iVar3;
        *(int *)((long)param_1 + lVar16 + 0xc) = iVar11 + iVar19;
        iVar11 = (int)((long)(iVar10 - iVar13) * -0x6ed9eba1 + 0x40000000U >> 0x1f);
        iVar5 = (int)((long)(iVar4 - iVar8) * -0x6ed9eba1 + 0x40000000U >> 0x1f);
        piVar17 = piVar17 + 0x20;
        *(int *)((long)param_1 + lVar16 + 0x98) = iVar1 + iVar5;
        *(int *)((long)param_1 + lVar16 + 0x9c) = iVar2 - iVar11;
        *(int *)((long)param_1 + lVar16 + 0x50) = iVar1 - iVar5;
        *(int *)((long)param_1 + lVar16 + 0x54) = iVar2 + iVar11;
        lVar16 = lVar6;
      } while ((int)lVar6 != 0x40);
      iVar14 = iVar14 + 1;
      param_1 = param_1 + 0x36;
    } while (iVar14 != param_3);
  }
  return;
}


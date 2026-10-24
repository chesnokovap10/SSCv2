/* FUN_0010664c @ 0010664c size 468 */

void FUN_0010664c(long param_1,uint param_2,long param_3,ulong param_4,int param_5)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  int *piVar11;
  int *piVar12;
  int iVar13;
  ulong uVar14;
  int *piVar15;
  int *piVar16;
  ulong uVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  long lVar24;
  long lVar25;
  
  iVar10 = (int)param_4;
  if (1 < iVar10) {
    uVar9 = iVar10 * 3;
    uVar14 = -(param_4 >> 0x1f & 1) & 0xfffffffc00000000 | (param_4 & 0xffffffff) << 2;
    piVar11 = (int *)(param_3 + 4);
    iVar13 = 0;
    uVar17 = -(ulong)(iVar10 + 1U >> 0x1f) & 0xfffffffc00000000 | (ulong)(iVar10 + 1U) << 2;
    piVar12 = piVar11;
    piVar15 = piVar11;
    piVar16 = (int *)(param_1 + (long)param_5 * 4 + 4);
    do {
      iVar22 = piVar15[-1];
      iVar4 = *piVar15;
      lVar24 = (long)*(int *)((long)piVar16 + (uVar14 - 4));
      lVar25 = (long)*(int *)((long)piVar16 + (uVar17 - 4));
      piVar1 = piVar16 + (uint)(iVar10 * 2);
      iVar3 = piVar12[-1];
      iVar5 = *piVar12;
      iVar6 = piVar16[(ulong)uVar9 - 1];
      iVar7 = piVar16[(ulong)(uVar9 + 1) - 1];
      iVar2 = piVar16[-1] + 2 >> 2;
      iVar18 = *piVar16 + 2 >> 2;
      iVar21 = (int)(((long)piVar11[-1] * (long)piVar1[-1] + 0x100000000) -
                     (long)*piVar11 * (long)*piVar1 >> 0x21);
      iVar8 = iVar2 - iVar21;
      iVar2 = iVar2 + iVar21;
      iVar19 = (int)((iVar22 * lVar24 + 0x100000000) - iVar4 * lVar25 >> 0x21);
      iVar23 = (int)(((long)iVar3 * (long)iVar6 + 0x100000000) - (long)iVar5 * (long)iVar7 >> 0x21);
      iVar21 = iVar23 + iVar19;
      iVar19 = iVar19 - iVar23;
      iVar20 = (int)((long)*piVar11 * (long)piVar1[-1] + (long)*piVar1 * (long)piVar11[-1] +
                     0x100000000 >> 0x21);
      iVar23 = iVar18 - iVar20;
      piVar16[-1] = iVar2;
      *piVar16 = iVar18 + iVar20;
      piVar1[-1] = iVar2 - iVar21;
      iVar18 = (int)(iVar4 * lVar24 + lVar25 * iVar22 + 0x100000000 >> 0x21);
      iVar22 = (int)((long)iVar5 * (long)iVar6 + (long)iVar7 * (long)iVar3 + 0x100000000 >> 0x21);
      iVar2 = iVar22 + iVar18;
      *piVar1 = *piVar16 - iVar2;
      iVar13 = iVar13 + 1;
      iVar18 = iVar18 - iVar22;
      piVar12 = piVar12 + param_2 * 3;
      piVar11 = piVar11 + param_2 * 2;
      piVar16[-1] = piVar16[-1] + iVar21;
      *piVar16 = *piVar16 + iVar2;
      piVar15 = piVar15 + param_2;
      *(int *)((long)piVar16 + (uVar14 - 4)) = iVar18 + iVar8;
      *(int *)((long)piVar16 + (uVar17 - 4)) = iVar23 - iVar19;
      piVar16[(ulong)uVar9 - 1] = iVar8 - iVar18;
      piVar16[(ulong)(uVar9 + 1) - 1] = iVar23 + iVar19;
      piVar16 = piVar16 + 2;
    } while (iVar13 < iVar10 >> 1);
  }
  return;
}


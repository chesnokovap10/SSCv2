/* FUN_001167d0 @ 001167d0 size 596 */

void FUN_001167d0(ushort *param_1,int param_2,short param_3,short param_4)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  short sVar6;
  int iVar7;
  int iVar8;
  ushort *puVar9;
  ushort *puVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  
  uVar5 = param_2 - 1;
  iVar7 = (int)param_4;
  uVar13 = param_2 + 2;
  if (-1 < (int)uVar5) {
    uVar13 = uVar5;
  }
  iVar8 = (int)param_3;
  if ((int)(uVar13 & 0xfffffffc) < 1) {
    uVar12 = 0;
    puVar10 = param_1;
    if ((int)uVar5 < 1) goto LAB_0011690c;
  }
  else {
    uVar12 = 0;
    uVar14 = (uint)*param_1;
    puVar9 = param_1;
    do {
      uVar12 = uVar12 + 4;
      iVar11 = ((short)uVar14 * iVar7 + (short)puVar9[1] * iVar8) * 2 >> 0x10;
      puVar10 = puVar9 + 4;
      iVar2 = ((short)puVar9[2] * iVar8 + iVar11 * iVar7) * 2 >> 0x10;
      iVar3 = ((short)puVar9[3] * iVar8 + iVar2 * iVar7) * 2 >> 0x10;
      *puVar9 = (ushort)((uint)((short)uVar14 * iVar8 - (short)puVar9[1] * iVar7) >> 0xf);
      puVar9[1] = (ushort)((uint)(iVar11 * iVar8 - (short)puVar9[2] * iVar7) >> 0xf);
      puVar9[2] = (ushort)((uint)(iVar2 * iVar8 - (short)puVar9[3] * iVar7) >> 0xf);
      uVar14 = (uint)((short)*puVar10 * iVar8 + iVar3 * iVar7) >> 0xf;
      puVar9[3] = (ushort)((uint)(iVar3 * iVar8 - (short)*puVar10 * iVar7) >> 0xf);
      *puVar10 = (ushort)uVar14;
      puVar9 = puVar10;
    } while ((int)uVar12 < (int)(uVar13 & 0xfffffffc));
    if ((int)uVar5 <= (int)uVar12) goto LAB_0011690c;
  }
  uVar13 = (uint)*puVar10;
  iVar11 = ~uVar12 + param_2;
  do {
    puVar9 = puVar10 + 1;
    uVar1 = *puVar9;
    sVar6 = (short)uVar13;
    iVar11 = iVar11 + -1;
    uVar13 = (uint)(sVar6 * iVar7 + (short)uVar1 * iVar8) >> 0xf;
    *puVar9 = (ushort)uVar13;
    *puVar10 = (ushort)((uint)(sVar6 * iVar8 - (short)uVar1 * iVar7) >> 0xf);
    puVar10 = puVar9;
  } while (iVar11 != 0);
LAB_0011690c:
  uVar5 = param_2 - 2;
  uVar13 = uVar5;
  if ((int)uVar5 < 0) {
    uVar13 = param_2 + 1;
  }
  param_1 = param_1 + (param_2 + -3);
  if ((int)(uVar13 & 0xfffffffc) < 1) {
    iVar11 = 0;
    if ((int)uVar5 < 1) {
      return;
    }
  }
  else {
    iVar11 = 0;
    do {
      iVar11 = iVar11 + 4;
      iVar2 = ((short)*param_1 * iVar8 - (short)param_1[1] * iVar7) * 2 >> 0x10;
      iVar3 = ((short)param_1[-1] * iVar8 - iVar2 * iVar7) * 2 >> 0x10;
      param_1[1] = (ushort)((uint)((short)*param_1 * iVar7 + (short)param_1[1] * iVar8) >> 0xf);
      iVar4 = ((short)param_1[-2] * iVar8 - iVar3 * iVar7) * 2 >> 0x10;
      *param_1 = (ushort)((uint)((short)param_1[-1] * iVar7 + iVar2 * iVar8) >> 0xf);
      param_1[-1] = (ushort)((uint)((short)param_1[-2] * iVar7 + iVar3 * iVar8) >> 0xf);
      param_1[-2] = (ushort)((uint)((short)param_1[-3] * iVar7 + iVar4 * iVar8) >> 0xf);
      param_1[-3] = (ushort)((uint)((short)param_1[-3] * iVar8 - iVar4 * iVar7) >> 0xf);
      param_1 = param_1 + -4;
    } while (iVar11 < (int)(uVar13 & 0xfffffffc));
    if ((int)uVar5 <= iVar11) {
      return;
    }
  }
  iVar11 = (param_2 - iVar11) + -2;
  do {
    iVar11 = iVar11 + -1;
    uVar1 = param_1[1];
    param_1[1] = (ushort)((uint)((short)*param_1 * iVar7 + (short)uVar1 * iVar8) >> 0xf);
    *param_1 = (ushort)((uint)((short)*param_1 * iVar8 - (short)uVar1 * iVar7) >> 0xf);
    param_1 = param_1 + -1;
  } while (iVar11 != 0);
  return;
}


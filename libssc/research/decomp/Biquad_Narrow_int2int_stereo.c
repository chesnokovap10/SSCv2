/* Biquad_Narrow_int2int_stereo @ 0010b200 size 252 */

void Biquad_Narrow_int2int_stereo
               (undefined8 *param_1,undefined8 *param_2,int *param_3,long *param_4,int param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  ulong uVar10;
  long lVar11;
  ulong uVar12;
  long lVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  
  uVar10 = param_4[4];
  uVar12 = param_4[9];
  iVar1 = *param_3;
  iVar2 = param_3[2];
  iVar3 = param_3[3];
  iVar4 = param_3[4];
  iVar5 = param_3[1];
  iVar18 = (int)param_4[3];
  iVar19 = (int)param_4[8];
  iVar21 = (int)param_4[2];
  iVar23 = (int)param_4[7];
  iVar15 = (int)*param_4;
  iVar17 = (int)param_4[5];
  iVar8 = (int)param_4[1];
  iVar9 = (int)param_4[6];
  do {
    iVar16 = iVar17;
    iVar14 = iVar15;
    iVar22 = iVar23;
    iVar20 = iVar21;
    iVar15 = (int)*param_2 << 7;
    iVar17 = (int)((ulong)*param_2 >> 0x20) << 7;
    lVar11 = uVar10 + (long)iVar15 * (long)iVar1 + (long)iVar14 * (long)iVar5 +
             (long)iVar8 * (long)iVar2 + (long)iVar20 * (long)iVar3;
    lVar13 = uVar12 + (long)iVar17 * (long)iVar1 + (long)iVar16 * (long)iVar5 +
             (long)iVar9 * (long)iVar2 + (long)iVar22 * (long)iVar3;
    iVar8 = (int)((ulong)(lVar11 + (long)iVar18 * (long)iVar4) >> 0x20);
    iVar9 = (int)((ulong)(lVar13 + (long)iVar19 * (long)iVar4) >> 0x20);
    param_5 = param_5 + -1;
    uVar6 = (int)lVar11 + iVar18 * iVar4;
    uVar7 = (int)lVar13 + iVar19 * iVar4;
    iVar21 = iVar8 << 3;
    iVar23 = iVar9 << 3;
    uVar10 = (ulong)uVar6;
    uVar12 = (ulong)uVar7;
    *param_1 = CONCAT44(iVar9 >> 4,iVar8 >> 4);
    param_1 = param_1 + 1;
    param_2 = param_2 + 1;
    iVar18 = iVar20;
    iVar19 = iVar22;
    iVar8 = iVar14;
    iVar9 = iVar16;
  } while (0 < param_5);
  *param_4 = (long)iVar15;
  param_4[1] = (long)iVar14;
  param_4[2] = (long)iVar21;
  param_4[3] = (long)iVar20;
  param_4[4] = (long)(int)uVar6;
  param_4[6] = (long)iVar16;
  param_4[5] = (long)iVar17;
  param_4[8] = (long)iVar22;
  param_4[7] = (long)iVar23;
  param_4[9] = (long)(int)uVar7;
  return;
}


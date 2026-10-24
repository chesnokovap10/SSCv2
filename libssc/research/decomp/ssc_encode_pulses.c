/* ssc_encode_pulses @ 00109e38 size 212 */

void ssc_encode_pulses(long param_1,ulong param_2,int param_3,undefined8 param_4)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  long lVar6;
  int *piVar7;
  int *piVar8;
  uint uVar9;
  ulong uVar10;
  uint uVar11;
  
  iVar4 = (int)param_2;
  if (param_3 < iVar4) {
    uVar10 = -(param_2 >> 0x1f & 1) & 0xfffffffc00000000 | (param_2 & 0xffffffff) << 2;
    piVar7 = (int *)((&PTR_DAT_0011b948)[param_3] + uVar10);
    piVar8 = (int *)((&PTR_DAT_0011b950)[param_3] + uVar10);
  }
  else {
    piVar7 = (int *)((&PTR_DAT_0011b948)[iVar4] + (long)param_3 * 4);
    piVar8 = piVar7 + 1;
  }
  lVar6 = (long)iVar4;
  uVar10 = 2;
  uVar3 = *(uint *)(param_1 + (long)iVar4 * 4 + -4);
  uVar5 = uVar3 >> 0x1f;
  uVar9 = -uVar3;
  if (-1 < (int)uVar3) {
    uVar9 = uVar3;
  }
  do {
    iVar4 = *(int *)(param_1 + -8 + lVar6 * 4);
    uVar11 = (uint)uVar10;
    uVar3 = uVar11;
    if (uVar9 <= uVar10) {
      uVar3 = uVar9;
    }
    uVar2 = uVar11;
    if (uVar10 <= uVar9) {
      uVar2 = uVar9;
    }
    iVar1 = -iVar4;
    if (-1 < iVar4) {
      iVar1 = iVar4;
    }
    uVar9 = iVar1 + uVar9;
    uVar5 = *(int *)((&PTR_DAT_0011b948)[(int)uVar3] + (ulong)uVar2 * 4) + uVar5;
    if (iVar4 < 0) {
      uVar3 = uVar11;
      if (uVar9 < uVar10) {
        uVar3 = uVar9 + 1;
      }
      if (uVar10 <= uVar9 + 1) {
        uVar11 = uVar9 + 1;
      }
      uVar5 = *(int *)((&PTR_DAT_0011b948)[(int)uVar3] + (ulong)uVar11 * 4) + uVar5;
    }
    lVar6 = lVar6 + -1;
    uVar10 = uVar10 + 1;
  } while ((int)lVar6 != 1);
  ssc_ec_enc_uint(param_4,uVar5,*piVar8 + *piVar7);
  return;
}


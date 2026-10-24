/* encode_pulses @ 001050dc size 240 */

void encode_pulses(long param_1,int param_2,int param_3,undefined8 param_4)

{
  uint *puVar1;
  long lVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  long lVar11;
  uint *puVar12;
  uint uVar13;
  uint uVar14;
  
  puVar1 = (uint *)(param_1 + (long)(param_2 + -1) * 4);
  puVar12 = puVar1 + -1;
  uVar9 = *puVar1;
  lVar11 = 0;
  uVar10 = uVar9 >> 0x1f;
  uVar13 = -uVar9;
  if (-1 < (int)uVar9) {
    uVar13 = uVar9;
  }
  do {
    while( true ) {
      lVar2 = (((long)param_2 + 1) - (long)(param_2 + -1)) + lVar11;
      uVar14 = (int)lVar11 + 2;
      uVar9 = uVar14;
      if ((long)(ulong)uVar13 <= lVar2) {
        uVar9 = uVar13;
      }
      uVar8 = *puVar12;
      uVar4 = uVar14;
      if (lVar2 <= (long)(ulong)uVar13) {
        uVar4 = uVar13;
      }
      uVar3 = -uVar8;
      if (-1 < (int)uVar8) {
        uVar3 = uVar8;
      }
      uVar13 = uVar3 + uVar13;
      uVar10 = *(int *)((&PTR_DAT_001289a0)[(int)uVar9] + (ulong)uVar4 * 4) + uVar10;
      if ((int)uVar8 < 0) break;
      lVar11 = lVar11 + 1;
      puVar12 = puVar12 + -1;
      if (param_2 + -1 == (int)lVar11) goto LAB_0010518c;
    }
    uVar9 = uVar14;
    if ((long)(ulong)uVar13 < lVar2) {
      uVar9 = uVar13 + 1;
    }
    if (lVar2 <= (long)(ulong)(uVar13 + 1)) {
      uVar14 = uVar13 + 1;
    }
    uVar10 = *(int *)((&PTR_DAT_001289a0)[(int)uVar9] + (ulong)uVar14 * 4) + uVar10;
    lVar11 = lVar11 + 1;
    puVar12 = puVar12 + -1;
  } while (param_2 + -1 != (int)lVar11);
LAB_0010518c:
  iVar5 = param_2;
  if (param_3 <= param_2) {
    iVar5 = param_3;
  }
  iVar6 = param_2;
  if (param_2 <= param_3) {
    iVar6 = param_3;
  }
  iVar7 = param_2;
  if (param_3 + 1 <= param_2) {
    iVar7 = param_3 + 1;
  }
  if (param_2 <= param_3 + 1) {
    param_2 = param_3 + 1;
  }
  ec_enc_uint(param_4,uVar10,
              *(int *)((&PTR_DAT_001289a0)[iVar7] + (long)param_2 * 4) +
              *(int *)((&PTR_DAT_001289a0)[iVar5] + (long)iVar6 * 4));
  return;
}


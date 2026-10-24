/* ssc_preemphasis @ 0010d03c size 220 */

void ssc_preemphasis(long param_1,long param_2,uint param_3,int *param_4,int param_5)

{
  long lVar1;
  int iVar2;
  uint uVar3;
  ulong uVar4;
  long lVar5;
  ulong uVar6;
  uint *puVar7;
  uint uVar8;
  int iVar9;
  ulong uVar10;
  
  uVar3 = 0xc;
  if (param_5 != 0) {
    uVar3 = 4;
  }
  if ((int)param_3 < 1) {
    *param_4 = *param_4;
    return;
  }
  uVar4 = (ulong)param_3;
  uVar6 = 0;
  if (param_3 != 1) {
    uVar8 = (uint)(uVar4 - 1);
    if (((-1 < (int)(uVar8 * 2)) && (uVar4 - 1 >> 0x20 == 0)) && (!CARRY4(uVar8,uVar8))) {
      uVar6 = uVar4 & 0xfffffffe;
      puVar7 = (uint *)(param_2 + 4);
      iVar9 = 2;
      uVar10 = uVar6;
      do {
        iVar2 = iVar9 + -2;
        lVar5 = (long)iVar9;
        uVar10 = uVar10 - 2;
        iVar9 = iVar9 + 4;
        uVar8 = *(int *)(param_1 + lVar5 * 4) << (ulong)uVar3;
        puVar7[-1] = *(int *)(param_1 + (long)iVar2 * 4) << (ulong)uVar3;
        *puVar7 = uVar8;
        puVar7 = puVar7 + 2;
      } while (uVar10 != 0);
      if (uVar6 == uVar4) goto LAB_0010d0e4;
    }
  }
  iVar9 = (int)uVar6 << 1;
  lVar5 = uVar4 - uVar6;
  puVar7 = (uint *)(param_2 + uVar6 * 4);
  do {
    lVar1 = (long)iVar9;
    lVar5 = lVar5 + -1;
    iVar9 = iVar9 + 2;
    uVar8 = *(int *)(param_1 + lVar1 * 4) << (ulong)uVar3;
    *puVar7 = uVar8;
    puVar7 = puVar7 + 1;
  } while (lVar5 != 0);
LAB_0010d0e4:
  *param_4 = -(((int)uVar8 >> 0x10) * 0xd99a + ((uVar8 & 0xfff0) * 0x6ccd >> 0xf));
  return;
}


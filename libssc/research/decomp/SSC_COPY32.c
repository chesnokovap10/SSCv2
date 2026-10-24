/* SSC_COPY32 @ 00115460 size 140 */

void SSC_COPY32(ulong param_1,ulong param_2,uint param_3)

{
  undefined8 *puVar1;
  ulong uVar2;
  long lVar3;
  ulong uVar4;
  undefined4 *puVar5;
  undefined8 *puVar6;
  undefined4 *puVar7;
  undefined8 *puVar8;
  ulong uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  
  if (0 < (int)param_3) {
    uVar2 = (ulong)param_3;
    if ((param_3 < 8) || ((param_1 < param_2 + uVar2 * 4 && (param_2 < param_1 + uVar2 * 4)))) {
      uVar4 = 0;
    }
    else {
      uVar4 = uVar2 & 0xfffffff8;
      puVar6 = (undefined8 *)(param_2 + 0x10);
      puVar8 = (undefined8 *)(param_1 + 0x10);
      uVar9 = uVar4;
      do {
        puVar1 = puVar6 + -1;
        uVar10 = puVar6[-2];
        uVar12 = puVar6[1];
        uVar11 = *puVar6;
        puVar6 = puVar6 + 4;
        uVar9 = uVar9 - 8;
        puVar8[-1] = *puVar1;
        puVar8[-2] = uVar10;
        puVar8[1] = uVar12;
        *puVar8 = uVar11;
        puVar8 = puVar8 + 4;
      } while (uVar9 != 0);
      if (uVar4 == uVar2) {
        return;
      }
    }
    lVar3 = uVar2 - uVar4;
    puVar5 = (undefined4 *)(param_1 + uVar4 * 4);
    puVar7 = (undefined4 *)(param_2 + uVar4 * 4);
    do {
      lVar3 = lVar3 + -1;
      *puVar5 = *puVar7;
      puVar5 = puVar5 + 1;
      puVar7 = puVar7 + 1;
    } while (lVar3 != 0);
  }
  return;
}


/* SSC_COPY8 @ 00115578 size 200 */

void SSC_COPY8(ulong param_1,ulong param_2,uint param_3)

{
  undefined8 *puVar1;
  ulong uVar2;
  long lVar3;
  ulong uVar4;
  ulong uVar5;
  undefined1 *puVar6;
  undefined8 *puVar7;
  undefined1 *puVar8;
  undefined8 *puVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  
  if ((int)param_3 < 1) {
    return;
  }
  uVar2 = (ulong)param_3;
  if ((param_3 < 8) || ((param_1 < param_2 + uVar2 && (param_2 < param_1 + uVar2)))) {
    uVar4 = 0;
  }
  else {
    if (param_3 < 0x20) {
      uVar5 = 0;
    }
    else {
      uVar4 = uVar2 & 0xffffffe0;
      puVar7 = (undefined8 *)(param_2 + 0x10);
      puVar9 = (undefined8 *)(param_1 + 0x10);
      uVar5 = uVar4;
      do {
        puVar1 = puVar7 + -1;
        uVar10 = puVar7[-2];
        uVar12 = puVar7[1];
        uVar11 = *puVar7;
        puVar7 = puVar7 + 4;
        uVar5 = uVar5 - 0x20;
        puVar9[-1] = *puVar1;
        puVar9[-2] = uVar10;
        puVar9[1] = uVar12;
        *puVar9 = uVar11;
        puVar9 = puVar9 + 4;
      } while (uVar5 != 0);
      if (uVar4 == uVar2) {
        return;
      }
      uVar5 = uVar4;
      if ((param_3 & 0x18) == 0) goto LAB_001155a8;
    }
    uVar4 = uVar2 & 0xfffffff8;
    lVar3 = uVar5 - uVar4;
    puVar7 = (undefined8 *)(param_2 + uVar5);
    puVar9 = (undefined8 *)(param_1 + uVar5);
    do {
      lVar3 = lVar3 + 8;
      *puVar9 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar9 = puVar9 + 1;
    } while (lVar3 != 0);
    if (uVar4 == uVar2) {
      return;
    }
  }
LAB_001155a8:
  lVar3 = uVar2 - uVar4;
  puVar6 = (undefined1 *)(param_1 + uVar4);
  puVar8 = (undefined1 *)(param_2 + uVar4);
  do {
    lVar3 = lVar3 + -1;
    *puVar6 = *puVar8;
    puVar6 = puVar6 + 1;
    puVar8 = puVar8 + 1;
  } while (lVar3 != 0);
  return;
}


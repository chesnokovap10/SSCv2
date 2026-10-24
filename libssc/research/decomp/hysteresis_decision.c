/* hysteresis_decision @ 00102868 size 136 */

uint hysteresis_decision(short param_1,long param_2,long param_3,int param_4,uint param_5)

{
  uint uVar1;
  uint uVar2;
  long lVar3;
  ulong uVar4;
  
  if (param_4 < 1) {
    uVar1 = 0;
    uVar2 = uVar1;
    if (param_5 < 0x80000000) goto LAB_001028b0;
  }
  else {
    lVar3 = 0;
    do {
      if (param_1 < *(short *)(param_2 + lVar3 * 2)) break;
      lVar3 = lVar3 + 1;
    } while (lVar3 < param_4);
    uVar1 = (uint)lVar3;
    uVar2 = uVar1;
    if ((int)uVar1 <= (int)param_5) goto LAB_001028b0;
  }
  uVar4 = -(ulong)(param_5 >> 0x1f) & 0xfffffffe00000000 | (ulong)param_5 << 1;
  uVar2 = param_5;
  if ((int)*(short *)(param_3 + uVar4) + (int)*(short *)(param_2 + uVar4) <= (int)param_1) {
    uVar2 = uVar1;
  }
LAB_001028b0:
  if ((int)param_5 <= (int)uVar2) {
    return uVar2;
  }
  lVar3 = (-(ulong)(param_5 >> 0x1f) & 0xfffffffe00000000 | (ulong)param_5 << 1) - 2;
  if ((int)param_1 <= (int)*(short *)(param_2 + lVar3) - (int)*(short *)(param_3 + lVar3)) {
    param_5 = uVar2;
  }
  return param_5;
}


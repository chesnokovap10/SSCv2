/* ssc_preemphasis @ 0010ade4 size 180 */

void ssc_preemphasis(int *param_1,int *param_2,int param_3,undefined8 param_4,int param_5)

{
  ulong uVar1;
  ulong uVar2;
  uint uVar3;
  undefined1 auVar4 [16];
  int *piVar5;
  uint uVar6;
  long lVar7;
  int *piVar8;
  int *piVar9;
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  
  uVar6 = 0xc;
  if (param_5 != 0) {
    uVar6 = 4;
  }
  uVar3 = param_3 - 1;
  piVar5 = param_1;
  if ((7 < uVar3) &&
     ((param_1 + (ulong)uVar3 * 2 + 1 <= param_2 || (param_2 + (ulong)uVar3 + 1 <= param_1)))) {
    uVar1 = (ulong)uVar3 + 1;
    uVar2 = 8;
    if ((uVar1 & 7) != 0) {
      uVar2 = uVar1 & 7;
    }
    lVar7 = uVar1 - uVar2;
    piVar9 = param_2 + 4;
    param_3 = param_3 - (int)lVar7;
    param_2 = param_2 + lVar7;
    piVar5 = param_1 + lVar7 * 2;
    piVar8 = param_1 + 8;
    do {
      auVar10._0_4_ = *piVar8;
      auVar10._4_4_ = piVar8[2];
      auVar10._8_4_ = piVar8[4];
      auVar10._12_4_ = piVar8[6];
      lVar7 = lVar7 + -8;
      auVar11._4_4_ = uVar6;
      auVar11._0_4_ = uVar6;
      auVar11._8_4_ = uVar6;
      auVar11._12_4_ = uVar6;
      auVar11 = NEON_ushl(auVar10,auVar11,4);
      auVar12._4_4_ = uVar6;
      auVar12._0_4_ = uVar6;
      auVar12._8_4_ = uVar6;
      auVar12._12_4_ = uVar6;
      auVar4._4_4_ = piVar8[-6];
      auVar4._0_4_ = piVar8[-8];
      auVar4._8_4_ = piVar8[-4];
      auVar4._12_4_ = piVar8[-2];
      auVar12 = NEON_ushl(auVar4,auVar12,4);
      *(long *)(piVar9 + -2) = auVar12._8_8_;
      *(long *)(piVar9 + -4) = auVar12._0_8_;
      *(long *)(piVar9 + 2) = auVar11._8_8_;
      *(long *)piVar9 = auVar11._0_8_;
      piVar9 = piVar9 + 8;
      piVar8 = piVar8 + 0x10;
    } while (lVar7 != 0);
  }
  do {
    param_3 = param_3 + -1;
    *param_2 = *piVar5 << (ulong)uVar6;
    piVar5 = piVar5 + 2;
    param_2 = param_2 + 1;
  } while (param_3 != 0);
  return;
}


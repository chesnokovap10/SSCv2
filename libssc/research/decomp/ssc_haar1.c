/* ssc_haar1 @ 001087fc size 156 */

void ssc_haar1(short *param_1,int param_2,uint param_3)

{
  uint uVar1;
  short sVar2;
  short sVar3;
  ulong uVar4;
  short *psVar5;
  ulong uVar6;
  short *psVar7;
  short *psVar8;
  
  if (0 < (int)param_3) {
    uVar1 = param_2 >> 1;
    uVar4 = 0;
    if ((int)uVar1 < 2) {
      uVar1 = 1;
    }
    psVar5 = param_1 + param_3;
    do {
      uVar6 = (ulong)uVar1;
      psVar7 = psVar5;
      psVar8 = param_1;
      if (1 < param_2) {
        do {
          uVar6 = uVar6 - 1;
          sVar2 = (short)((uint)(*psVar7 * 0xb504) >> 0x10);
          sVar3 = (short)((uint)(*psVar8 * 0xb504) >> 0x10);
          *psVar8 = sVar2 + sVar3;
          *psVar7 = sVar3 - sVar2;
          psVar7 = psVar7 + (ulong)param_3 * 2;
          psVar8 = (short *)((long)psVar8 +
                            (-(ulong)((param_3 & 0x7fffffff) >> 0x1e) & 0xfffffffe00000000 |
                            (ulong)(param_3 << 1) << 1));
        } while (uVar6 != 0);
      }
      uVar4 = uVar4 + 1;
      param_1 = param_1 + 1;
      psVar5 = psVar5 + 1;
    } while (uVar4 != param_3);
  }
  return;
}


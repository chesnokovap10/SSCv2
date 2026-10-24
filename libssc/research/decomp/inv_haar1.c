/* inv_haar1 @ 00103a58 size 144 */

void inv_haar1(short *param_1,uint param_2,ulong param_3)

{
  short sVar1;
  short sVar2;
  uint uVar3;
  ulong uVar4;
  short *psVar5;
  long lVar6;
  short *psVar7;
  short *psVar8;
  
  uVar3 = (uint)param_3;
  if ((0 < (int)uVar3) && (1 < (int)param_2)) {
    uVar4 = 0;
    psVar5 = param_1 + (int)uVar3;
    do {
      lVar6 = 0;
      psVar7 = psVar5;
      psVar8 = param_1;
      do {
        lVar6 = lVar6 + 1;
        sVar1 = (short)((uint)(*psVar7 * 0xb504) >> 0x10);
        sVar2 = (short)((uint)(*psVar8 * 0xb504) >> 0x10);
        *psVar8 = sVar1 + sVar2;
        *psVar7 = sVar2 - sVar1;
        psVar8 = (short *)((long)psVar8 +
                          (-(ulong)((uVar3 & 0x7fffffff) >> 0x1e) & 0xfffffffe00000000 |
                          (ulong)(uVar3 << 1) << 1));
        psVar7 = (short *)((long)psVar7 +
                          (-(param_3 >> 0x1f & 1) & 0xfffffffc00000000 | (param_3 & 0xffffffff) << 2
                          ));
      } while (lVar6 < (long)((ulong)param_2 << 0x20) >> 0x21);
      uVar4 = uVar4 + 1;
      param_1 = param_1 + 1;
      psVar5 = psVar5 + 1;
    } while (uVar4 != (param_3 & 0xffffffff));
  }
  return;
}


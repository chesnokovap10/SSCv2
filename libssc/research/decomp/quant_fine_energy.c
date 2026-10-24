/* quant_fine_energy @ 001093d0 size 296 */

void quant_fine_energy(long param_1,uint param_2,long param_3,long param_4,long param_5,
                      undefined8 param_6,int param_7)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  short sVar5;
  int iVar6;
  ulong uVar7;
  ulong uVar8;
  int iVar9;
  
  if (0 < (int)param_2) {
    uVar8 = 0;
    do {
      uVar3 = *(uint *)(param_5 + uVar8 * 4);
      if (0 < (int)uVar3) {
        iVar6 = *(int *)(param_1 + 8);
        iVar2 = (0x10000 << (ulong)(uVar3 & 0x1f)) >> 0x10;
        iVar9 = 0;
        do {
          uVar1 = *(short *)(param_4 + (long)((int)uVar8 + iVar6 * iVar9) * 2) + 0x200 >>
                  (10 - uVar3 & 0x1f);
          if (iVar2 <= (int)uVar1) {
            uVar1 = iVar2 - 1;
          }
          uVar1 = uVar1 & ((int)uVar1 >> 0x1f ^ 0xffffffffU);
          ec_enc_bits(param_6,uVar1);
          iVar6 = *(int *)(param_1 + 8);
          uVar3 = *(uint *)(param_5 + uVar8 * 4);
          uVar4 = (int)uVar8 + iVar6 * iVar9;
          uVar7 = -(ulong)(uVar4 >> 0x1f) & 0xfffffffe00000000 | (ulong)uVar4 << 1;
          sVar5 = (short)(((uVar1 << 10 | 0x200) >> (ulong)(uVar3 & 0x1f)) * 0x10000 + -0x2000000 >>
                         0x10);
          *(short *)(param_3 + uVar7) = *(short *)(param_3 + uVar7) + sVar5;
          iVar9 = iVar9 + 1;
          *(short *)(param_4 + uVar7) = *(short *)(param_4 + uVar7) - sVar5;
        } while (iVar9 < param_7);
      }
      uVar8 = uVar8 + 1;
    } while (uVar8 != param_2);
  }
  return;
}


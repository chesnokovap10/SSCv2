/* ssc_quant_fine_energy @ 00113c9c size 376 */

void ssc_quant_fine_energy
               (long param_1,uint param_2,long param_3,long param_4,long param_5,undefined8 param_6)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  short sVar5;
  ulong uVar6;
  long lVar7;
  
  if (0 < (int)param_2) {
    uVar6 = 0;
    do {
      uVar2 = *(uint *)(param_5 + uVar6 * 4);
      if (0 < (int)uVar2) {
        lVar7 = uVar6 * 2;
        iVar1 = (0x10000 << (ulong)(uVar2 & 0x1f)) >> 0x10;
        uVar2 = *(short *)(param_4 + lVar7) + 0x200 >> (10 - uVar2 & 0x1f);
        if (iVar1 <= (int)uVar2) {
          uVar2 = iVar1 - 1U;
        }
        uVar2 = uVar2 & ((int)uVar2 >> 0x1f ^ 0xffffffffU);
        ssc_ec_enc_bits(param_6,uVar2);
        uVar3 = *(uint *)(param_5 + uVar6 * 4);
        iVar4 = *(int *)(param_1 + 8);
        sVar5 = (short)((uVar2 << 10 | 0x200) >> (ulong)(uVar3 & 0x1f)) + -0x200;
        *(short *)(param_3 + lVar7) = sVar5 + *(short *)(param_3 + lVar7);
        *(short *)(param_4 + lVar7) = *(short *)(param_4 + lVar7) - sVar5;
        uVar2 = *(short *)(param_4 + (uVar6 + (long)iVar4) * 2) + 0x200 >> (10 - uVar3 & 0x1f);
        if (iVar1 <= (int)uVar2) {
          uVar2 = iVar1 - 1U;
        }
        uVar2 = uVar2 & ((int)uVar2 >> 0x1f ^ 0xffffffffU);
        ssc_ec_enc_bits(param_6,uVar2);
        lVar7 = (uVar6 + (long)*(int *)(param_1 + 8)) * 2;
        sVar5 = (short)((uVar2 << 10 | 0x200) >> (ulong)(*(uint *)(param_5 + uVar6 * 4) & 0x1f)) +
                -0x200;
        *(short *)(param_3 + lVar7) = sVar5 + *(short *)(param_3 + lVar7);
        *(short *)(param_4 + lVar7) = *(short *)(param_4 + lVar7) - sVar5;
      }
      uVar6 = uVar6 + 1;
    } while (param_2 != uVar6);
  }
  return;
}


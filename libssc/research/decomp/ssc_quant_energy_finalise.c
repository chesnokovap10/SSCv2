/* ssc_quant_energy_finalise @ 00113e14 size 556 */

void ssc_quant_energy_finalise
               (long param_1,int param_2,long param_3,long param_4,long param_5,long param_6,
               int param_7,undefined8 param_8)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  long lVar4;
  
  if ((0 < param_2) && (1 < param_7)) {
    lVar4 = 0;
    do {
      if ((*(int *)(param_5 + lVar4 * 4) < 8) && (*(int *)(param_6 + lVar4 * 4) == 0)) {
        lVar3 = lVar4 * 2;
        uVar2 = ~(uint)*(ushort *)(param_4 + lVar3) >> 0xf & 1;
        ssc_ec_enc_bits(param_8,uVar2,1);
        iVar1 = *(int *)(param_1 + 8);
        *(short *)(param_3 + lVar3) =
             *(short *)(param_3 + lVar3) +
             (short)((int)(uVar2 * 0x400 + -0x200) >> (*(int *)(param_5 + lVar4 * 4) + 1U & 0x1f));
        uVar2 = ~(uint)*(ushort *)(param_4 + (lVar4 + iVar1) * 2) >> 0xf & 1;
        ssc_ec_enc_bits(param_8,uVar2,1);
        param_7 = param_7 + -2;
        lVar3 = (lVar4 + *(int *)(param_1 + 8)) * 2;
        *(short *)(param_3 + lVar3) =
             *(short *)(param_3 + lVar3) +
             (short)((int)(uVar2 * 0x400 + -0x200) >> (*(int *)(param_5 + lVar4 * 4) + 1U & 0x1f));
      }
      lVar4 = lVar4 + 1;
    } while ((lVar4 < param_2) && (1 < param_7));
  }
  if ((0 < param_2) && (1 < param_7)) {
    lVar4 = 0;
    do {
      if ((*(int *)(param_5 + lVar4 * 4) < 8) && (*(int *)(param_6 + lVar4 * 4) == 1)) {
        lVar3 = lVar4 * 2;
        uVar2 = ~(uint)*(ushort *)(param_4 + lVar3) >> 0xf & 1;
        ssc_ec_enc_bits(param_8,uVar2,1);
        iVar1 = *(int *)(param_1 + 8);
        *(short *)(param_3 + lVar3) =
             *(short *)(param_3 + lVar3) +
             (short)((int)(uVar2 * 0x400 + -0x200) >> (*(int *)(param_5 + lVar4 * 4) + 1U & 0x1f));
        uVar2 = ~(uint)*(ushort *)(param_4 + (lVar4 + iVar1) * 2) >> 0xf & 1;
        ssc_ec_enc_bits(param_8,uVar2,1);
        param_7 = param_7 + -2;
        lVar3 = (lVar4 + *(int *)(param_1 + 8)) * 2;
        *(short *)(param_3 + lVar3) =
             *(short *)(param_3 + lVar3) +
             (short)((int)(uVar2 * 0x400 + -0x200) >> (*(int *)(param_5 + lVar4 * 4) + 1U & 0x1f));
      }
      lVar4 = lVar4 + 1;
    } while ((lVar4 < param_2) && (1 < param_7));
  }
  return;
}


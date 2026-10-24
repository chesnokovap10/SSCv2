/* quant_energy_finalise @ 001094f8 size 424 */

void quant_energy_finalise
               (long param_1,int param_2,long param_3,long param_4,long param_5,long param_6,
               int param_7,undefined8 param_8,int param_9)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  ulong uVar4;
  long lVar5;
  int iVar6;
  
  if (0 < param_2) {
    if (param_9 <= param_7) {
      lVar5 = 0;
      do {
        if ((*(int *)(param_5 + lVar5 * 4) < 8) && (*(int *)(param_6 + lVar5 * 4) == 0)) {
          iVar3 = *(int *)(param_1 + 8);
          iVar6 = 0;
          do {
            uVar1 = *(ushort *)(param_4 + (long)((int)lVar5 + iVar3 * iVar6) * 2) >> 0xf ^ 1;
            ec_enc_bits(param_8,uVar1,1);
            iVar3 = *(int *)(param_1 + 8);
            uVar2 = (int)lVar5 + iVar3 * iVar6;
            uVar4 = -(ulong)(uVar2 >> 0x1f) & 0xfffffffe00000000 | (ulong)uVar2 << 1;
            iVar6 = iVar6 + 1;
            *(short *)(param_3 + uVar4) =
                 *(short *)(param_3 + uVar4) +
                 (short)((int)(uVar1 * 0x400 + -0x200) >>
                        (*(int *)(param_5 + lVar5 * 4) + 1U & 0x1f));
          } while (iVar6 < param_9);
          param_7 = param_7 - iVar6;
        }
        lVar5 = lVar5 + 1;
      } while ((lVar5 < param_2) && (param_9 <= param_7));
    }
    if (param_9 <= param_7) {
      lVar5 = 0;
      do {
        if ((*(int *)(param_5 + lVar5 * 4) < 8) && (*(int *)(param_6 + lVar5 * 4) == 1)) {
          iVar3 = *(int *)(param_1 + 8);
          iVar6 = 0;
          do {
            uVar1 = *(ushort *)(param_4 + (long)((int)lVar5 + iVar3 * iVar6) * 2) >> 0xf ^ 1;
            ec_enc_bits(param_8,uVar1,1);
            iVar3 = *(int *)(param_1 + 8);
            uVar2 = (int)lVar5 + iVar3 * iVar6;
            uVar4 = -(ulong)(uVar2 >> 0x1f) & 0xfffffffe00000000 | (ulong)uVar2 << 1;
            iVar6 = iVar6 + 1;
            *(short *)(param_3 + uVar4) =
                 *(short *)(param_3 + uVar4) +
                 (short)((int)(uVar1 * 0x400 + -0x200) >>
                        (*(int *)(param_5 + lVar5 * 4) + 1U & 0x1f));
          } while (iVar6 < param_9);
          param_7 = param_7 - iVar6;
        }
        lVar5 = lVar5 + 1;
      } while ((lVar5 < param_2) && (param_9 <= param_7));
    }
  }
  return;
}


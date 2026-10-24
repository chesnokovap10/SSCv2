/* init_caps @ 0010b1a0 size 96 */

void init_caps(long param_1,long param_2,uint param_3,int param_4)

{
  short sVar1;
  short sVar2;
  short *psVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  
  if (0 < *(int *)(param_1 + 8)) {
    psVar3 = *(short **)(param_1 + 0x10);
    lVar4 = *(long *)(param_1 + 0x80);
    lVar5 = 0;
    sVar2 = *psVar3;
    do {
      lVar6 = lVar5 * 4;
      sVar1 = psVar3[lVar5 + 1];
      lVar5 = lVar5 + 1;
      *(int *)(param_2 + lVar6) =
           (*(int *)(lVar4 + lVar6) + 0x40) * param_4 *
           ((int)sVar1 - (int)sVar2 << (ulong)(param_3 & 0x1f)) >> 2;
      sVar2 = sVar1;
    } while (lVar5 < *(int *)(param_1 + 8));
  }
  return;
}


/* ec_enc_icdf @ 001056c4 size 336 */

void ec_enc_icdf(long *param_1,int param_2,long param_3,uint param_4)

{
  byte *pbVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  
  uVar3 = *(uint *)(param_1 + 4);
  uVar4 = uVar3 >> (ulong)(param_4 & 0x1f);
  if (param_2 < 1) {
    uVar4 = uVar3 - uVar4 * *(byte *)(param_3 + param_2);
    *(uint *)(param_1 + 4) = uVar4;
  }
  else {
    pbVar1 = (byte *)(param_3 + param_2);
    *(uint *)((long)param_1 + 0x24) = (*(int *)((long)param_1 + 0x24) + uVar3) - uVar4 * pbVar1[-1];
    uVar4 = ((uint)pbVar1[-1] - (uint)*pbVar1) * uVar4;
    *(uint *)(param_1 + 4) = uVar4;
  }
  if (uVar4 < 0x8001) {
    uVar3 = *(uint *)((long)param_1 + 0x24);
    do {
      if (uVar3 >> 0xf == 0xff) {
        *(int *)(param_1 + 5) = (int)param_1[5] + 1;
      }
      else {
        cVar2 = (char)(uVar3 >> 0x17);
        if (-1 < *(int *)((long)param_1 + 0x2c)) {
          uVar4 = *(uint *)((long)param_1 + 0x1c);
          if (*(int *)((long)param_1 + 0xc) + uVar4 < *(uint *)(param_1 + 1)) {
            uVar5 = 0;
            *(uint *)((long)param_1 + 0x1c) = uVar4 + 1;
            *(char *)(*param_1 + (ulong)uVar4) = (char)*(int *)((long)param_1 + 0x2c) + cVar2;
          }
          else {
            uVar5 = 0xffffffff;
          }
          *(uint *)(param_1 + 6) = *(uint *)(param_1 + 6) | uVar5;
        }
        iVar6 = (int)param_1[5];
        if (iVar6 != 0) {
          do {
            uVar4 = *(uint *)((long)param_1 + 0x1c);
            if (*(int *)((long)param_1 + 0xc) + uVar4 < *(uint *)(param_1 + 1)) {
              *(uint *)((long)param_1 + 0x1c) = uVar4 + 1;
              *(char *)(*param_1 + (ulong)uVar4) = cVar2 + -1;
              iVar6 = (int)param_1[5];
              uVar4 = 0;
            }
            else {
              uVar4 = 0xffffffff;
            }
            iVar6 = iVar6 + -1;
            *(int *)(param_1 + 5) = iVar6;
            *(uint *)(param_1 + 6) = *(uint *)(param_1 + 6) | uVar4;
          } while (iVar6 != 0);
        }
        uVar5 = uVar3 >> 0xf;
        uVar4 = *(uint *)(param_1 + 4);
        uVar3 = *(uint *)((long)param_1 + 0x24);
        *(uint *)((long)param_1 + 0x2c) = uVar5 & 0xff;
      }
      uVar4 = uVar4 << 8;
      uVar3 = (uVar3 & 0x7fff) << 8;
      *(uint *)(param_1 + 4) = uVar4;
      *(uint *)((long)param_1 + 0x24) = uVar3;
      *(int *)(param_1 + 3) = (int)param_1[3] + 8;
    } while (uVar4 < 0x8001);
  }
  return;
}


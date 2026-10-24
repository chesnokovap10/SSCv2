/* ec_encode @ 00105318 size 320 */

void ec_encode(long *param_1,int param_2,int param_3,uint param_4)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  uVar2 = *(uint *)(param_1 + 4);
  uVar3 = 0;
  if (param_4 != 0) {
    uVar3 = uVar2 / param_4;
  }
  if (param_2 == 0) {
    uVar3 = uVar2 - uVar3 * (param_4 - param_3);
    *(uint *)(param_1 + 4) = uVar3;
  }
  else {
    *(uint *)((long)param_1 + 0x24) =
         (uVar2 - uVar3 * (param_4 - param_2)) + *(int *)((long)param_1 + 0x24);
    uVar3 = uVar3 * (param_3 - param_2);
    *(uint *)(param_1 + 4) = uVar3;
  }
  if (uVar3 < 0x8001) {
    uVar2 = *(uint *)((long)param_1 + 0x24);
    do {
      if (uVar2 >> 0xf == 0xff) {
        *(int *)(param_1 + 5) = (int)param_1[5] + 1;
      }
      else {
        cVar1 = (char)(uVar2 >> 0x17);
        if (-1 < *(int *)((long)param_1 + 0x2c)) {
          uVar3 = *(uint *)((long)param_1 + 0x1c);
          if (*(int *)((long)param_1 + 0xc) + uVar3 < *(uint *)(param_1 + 1)) {
            uVar4 = 0;
            *(uint *)((long)param_1 + 0x1c) = uVar3 + 1;
            *(char *)(*param_1 + (ulong)uVar3) = (char)*(int *)((long)param_1 + 0x2c) + cVar1;
          }
          else {
            uVar4 = 0xffffffff;
          }
          *(uint *)(param_1 + 6) = *(uint *)(param_1 + 6) | uVar4;
        }
        iVar5 = (int)param_1[5];
        if (iVar5 != 0) {
          do {
            uVar3 = *(uint *)((long)param_1 + 0x1c);
            if (*(int *)((long)param_1 + 0xc) + uVar3 < *(uint *)(param_1 + 1)) {
              *(uint *)((long)param_1 + 0x1c) = uVar3 + 1;
              *(char *)(*param_1 + (ulong)uVar3) = cVar1 + -1;
              iVar5 = (int)param_1[5];
              uVar3 = 0;
            }
            else {
              uVar3 = 0xffffffff;
            }
            iVar5 = iVar5 + -1;
            *(int *)(param_1 + 5) = iVar5;
            *(uint *)(param_1 + 6) = *(uint *)(param_1 + 6) | uVar3;
          } while (iVar5 != 0);
        }
        uVar4 = uVar2 >> 0xf;
        uVar3 = *(uint *)(param_1 + 4);
        uVar2 = *(uint *)((long)param_1 + 0x24);
        *(uint *)((long)param_1 + 0x2c) = uVar4 & 0xff;
      }
      uVar3 = uVar3 << 8;
      uVar2 = (uVar2 & 0x7fff) << 8;
      *(uint *)(param_1 + 4) = uVar3;
      *(uint *)((long)param_1 + 0x24) = uVar2;
      *(int *)(param_1 + 3) = (int)param_1[3] + 8;
    } while (uVar3 < 0x8001);
  }
  return;
}


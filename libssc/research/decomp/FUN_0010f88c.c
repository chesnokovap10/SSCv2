/* FUN_0010f88c @ 0010f88c size 264 */

void FUN_0010f88c(long *param_1)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  uVar3 = *(uint *)(param_1 + 4);
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
            uVar5 = 0;
            *(uint *)((long)param_1 + 0x1c) = uVar3 + 1;
            *(char *)(*param_1 + (ulong)uVar3) = (char)*(int *)((long)param_1 + 0x2c) + cVar1;
          }
          else {
            uVar5 = 0xffffffff;
          }
          *(uint *)(param_1 + 6) = *(uint *)(param_1 + 6) | uVar5;
        }
        iVar4 = (int)param_1[5];
        if (iVar4 != 0) {
          do {
            uVar3 = *(uint *)((long)param_1 + 0x1c);
            if (*(int *)((long)param_1 + 0xc) + uVar3 < *(uint *)(param_1 + 1)) {
              uVar5 = 0;
              *(uint *)((long)param_1 + 0x1c) = uVar3 + 1;
              *(char *)(*param_1 + (ulong)uVar3) = cVar1 + -1;
              iVar4 = (int)param_1[5];
            }
            else {
              uVar5 = 0xffffffff;
            }
            iVar4 = iVar4 + -1;
            *(int *)(param_1 + 5) = iVar4;
            *(uint *)(param_1 + 6) = *(uint *)(param_1 + 6) | uVar5;
          } while (iVar4 != 0);
        }
        uVar5 = uVar2 >> 0xf;
        uVar3 = *(uint *)(param_1 + 4);
        uVar2 = *(uint *)((long)param_1 + 0x24);
        *(uint *)((long)param_1 + 0x2c) = uVar5 & 0xff;
      }
      uVar2 = (uVar2 & 0x7fff) << 8;
      uVar3 = uVar3 << 8;
      *(uint *)(param_1 + 4) = uVar3;
      *(uint *)((long)param_1 + 0x24) = uVar2;
      *(int *)(param_1 + 3) = (int)param_1[3] + 8;
    } while (uVar3 < 0x8001);
  }
  return;
}


/* powercalc @ 00106ea0 size 108 */

void powercalc(undefined8 *param_1,int param_2,undefined4 *param_3)

{
  long lVar1;
  long lVar2;
  int iVar3;
  undefined8 uVar4;
  int iVar5;
  
  if (param_2 == 0) {
    lVar1 = 0;
    lVar2 = 0;
  }
  else {
    lVar1 = 0;
    lVar2 = 0;
    do {
      uVar4 = *param_1;
      param_1 = param_1 + 0x20;
      param_2 = param_2 + -0x20;
      iVar3 = (int)uVar4;
      iVar5 = (int)((ulong)uVar4 >> 0x20);
      lVar1 = lVar1 + ((ulong)((long)iVar3 * (long)iVar3) >> 0x10 & 0xfffffffffffe) * 0x10;
      lVar2 = lVar2 + ((ulong)((long)iVar5 * (long)iVar5) >> 0x10 & 0xfffffffffffe) * 0x10;
    } while (param_2 != 0);
  }
  *param_3 = (int)((ulong)(lVar1 + lVar2) >> 9);
  return;
}


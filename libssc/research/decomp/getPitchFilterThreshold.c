/* getPitchFilterThreshold @ 0010af64 size 112 */

uint getPitchFilterThreshold(long param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = param_2 - *(int *)(param_1 + 0x38);
  iVar1 = -iVar4;
  if (-1 < iVar4) {
    iVar1 = iVar4;
  }
  uVar3 = 0x3334;
  if (iVar1 * 10 <= param_2) {
    uVar3 = 0x199a;
  }
  uVar2 = uVar3 + 0xccd;
  if (0x22 < param_3) {
    uVar2 = uVar3;
  }
  uVar3 = uVar3 + 0x199a;
  if (0x18 < param_3) {
    uVar3 = uVar2;
  }
  uVar2 = uVar3 - 0xccd;
  if (*(short *)(param_1 + 0x3c) < 0x3334) {
    uVar2 = uVar3;
  }
  uVar3 = uVar3 - 0x199a;
  if (*(short *)(param_1 + 0x3c) < 0x4667) {
    uVar3 = uVar2;
  }
  if ((uVar3 & 0xffff) < 0x199b) {
    uVar3 = 0x199a;
  }
  return uVar3;
}


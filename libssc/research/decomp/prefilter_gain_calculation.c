/* prefilter_gain_calculation @ 0010afd4 size 136 */

undefined8 prefilter_gain_calculation(short param_1,short param_2,int *param_3,short *param_4)

{
  int iVar1;
  short sVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  sVar2 = *param_4;
  if (param_2 <= sVar2) {
    uVar4 = (int)sVar2 - (int)param_1;
    uVar3 = -uVar4;
    if (-1 < (int)uVar4) {
      uVar3 = uVar4;
    }
    iVar5 = (int)param_1;
    if (0xccc < uVar3) {
      iVar5 = (int)sVar2;
      param_1 = sVar2;
    }
    uVar3 = (iVar5 + 0x600 >> 10) * 0x56;
    iVar5 = (int)(char)(((byte)(uVar3 >> 0xf) & 1) + (char)(uVar3 >> 8) + -1);
    if (6 < iVar5) {
      iVar5 = 7;
    }
    iVar1 = 0;
    if (0x5ff < param_1) {
      iVar1 = iVar5;
    }
    *param_3 = iVar1;
    *param_4 = (short)iVar1 * 0xc00 + 0xc00;
    return 1;
  }
  *param_3 = 0;
  *param_4 = 0;
  return 0;
}


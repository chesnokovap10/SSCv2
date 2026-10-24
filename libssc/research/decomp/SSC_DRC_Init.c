/* SSC_DRC_Init @ 001073b4 size 92 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void SSC_DRC_Init(uint param_1,int param_2)

{
  if ((int)param_1 < 0x1f41) {
    param_1 = 8000;
  }
  if (0x176 < param_1 >> 9) {
    param_1 = 0x2ee00;
  }
  DRC_ChNum = 1;
  if (param_2 == 2) {
    DRC_ChNum = 2;
  }
  Soundbooster_DRC_Fs = param_1;
  _DAT_00120510 = 0x2000000000400000;
  return;
}


/* SoundBooster_DRC_Init @ 0010b8fc size 88 */

void SoundBooster_DRC_Init(int param_1,int param_2)

{
  if (param_1 < 0x1f41) {
    param_1 = 8000;
  }
  if (0x2edff < param_1) {
    param_1 = 0x2ee00;
  }
  Soundbooster_DRC_Fs = param_1;
  DRC_ChNum = 1;
  if (param_2 == 2) {
    DRC_ChNum = 2;
  }
  DAT_001295e0 = 0x2000000000400000;
  return;
}


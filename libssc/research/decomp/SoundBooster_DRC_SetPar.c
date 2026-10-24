/* SoundBooster_DRC_SetPar @ 0010b8a4 size 88 */

void SoundBooster_DRC_SetPar(int param_1,undefined4 param_2)

{
  DRC_ModeFlag = (uint)(param_1 == 1);
  DAT_001295d8 = 0x3e6f79;
  if (Soundbooster_DRC_Fs != 96000) {
    DAT_001295d8 = 0x3ca4a1;
  }
  drc_struct = param_2;
  DAT_001295d4 = 0;
  DAT_001295dc = 0x400000;
  return;
}


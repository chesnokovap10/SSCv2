/* getPitchIndexGain @ 0010ae98 size 204 */

uint getPitchIndexGain(long param_1,long param_2,int *param_3,int param_4,int param_5)

{
  undefined2 uVar1;
  short sVar2;
  uint uVar3;
  
  if (param_5 == 0) {
    uVar3 = 0;
    *param_3 = 0xf;
  }
  else {
    ssc_pitch_downsample(&_pre_shared,&_pre_shared + (long)param_4 + 0x400,param_2);
    ssc_pitch_search(param_2 + 0x400,param_2,param_4,0x3d3,param_3);
    uVar1 = *(undefined2 *)(param_1 + 0x3c);
    *param_3 = 0x400 - *param_3;
    sVar2 = ssc_remove_doubling(param_2,0x400,0xf,param_4,param_3,*(undefined4 *)(param_1 + 0x38),
                                uVar1);
    if (0x3fe < *param_3) {
      *param_3 = 0x3fe;
    }
    uVar3 = (uint)(sVar2 * 0x599a) >> 0xf;
  }
  return uVar3;
}


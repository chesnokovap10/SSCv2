/* set_limit_gain_from_bitrate @ 0010b240 size 336 */

void set_limit_gain_from_bitrate(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar2 = 0x79f800;
  if (249999 < param_1) {
    if (param_1 < 0x6be90) {
      if (param_1 == 250000) goto LAB_0010b384;
      if ((param_1 == 0x470b8) || (param_1 == 0x4b320)) goto LAB_0010b364;
    }
    else if (((param_1 == 0x6be90) || (param_1 == 0x8e940)) || (param_1 == 0xd84f0)) {
LAB_0010b364:
      set_DRC_limit_gain(0x7b4c00);
      return;
    }
    return;
  }
  if (param_1 < 0x251c0) {
    if ((param_1 == 88000) || (param_1 == 96000)) {
      uVar1 = 0x76f2;
      uVar2 = 0x76f200;
    }
    else {
      if (param_1 != 0x1f400) {
        return;
      }
      uVar1 = 0x78b4;
      uVar2 = 0x78b400;
    }
  }
  else {
    if (param_1 == 0x251c0) goto LAB_0010b384;
    if ((param_1 != 0x2ee00) && (param_1 != 0x37e88)) {
      return;
    }
    uVar1 = 0x7a94;
    uVar2 = 0x7a9400;
  }
  if (param_2 != 0x18) {
    uVar2 = uVar1;
  }
LAB_0010b384:
  set_DRC_limit_gain(uVar2);
  return;
}


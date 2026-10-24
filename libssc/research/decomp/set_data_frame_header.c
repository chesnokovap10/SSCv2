/* set_data_frame_header @ 0010b504 size 456 */

void set_data_frame_header
               (undefined2 *param_1,int param_2,undefined8 param_3,uint param_4,byte param_5,
               int param_6)

{
  undefined1 uVar1;
  
  *param_1 = 0xeeff;
  *(byte *)(param_1 + 1) = param_5 & 3 | (byte)(param_4 << 4);
  if (param_2 < 0x3e800) {
    if (param_2 < 0x251c0) {
      if (param_2 == 88000) {
        uVar1 = 0xf0;
        goto LAB_0010b6b0;
      }
      if (param_2 == 96000) {
        uVar1 = 0xf1;
        goto LAB_0010b6b0;
      }
      if (param_2 == 0x1f400) {
        uVar1 = 0xf2;
        goto LAB_0010b6b0;
      }
    }
    else if (param_2 < 0x37e88) {
      if (param_2 == 0x251c0) {
        uVar1 = 0xe6;
        goto LAB_0010b6b0;
      }
    }
    else {
      if (param_2 == 0x37e88) {
        uVar1 = 0xf4;
        goto LAB_0010b6b0;
      }
      if (param_2 == 250000) {
        uVar1 = 0xe5;
        goto LAB_0010b6b0;
      }
    }
  }
  else if (param_2 < 0x50140) {
    if (param_2 == 0x3e800) {
      uVar1 = 0xf6;
      goto LAB_0010b6b0;
    }
    if (param_2 == 0x470b8) {
      uVar1 = 0xe0;
      goto LAB_0010b6b0;
    }
    if (param_2 == 0x4b320) {
      uVar1 = 0xe1;
      goto LAB_0010b6b0;
    }
  }
  else if (param_2 < 0x8e940) {
    if (param_2 == 0x50140) {
      uVar1 = 0xf5;
      goto LAB_0010b6b0;
    }
    if (param_2 == 0x6be90) {
      uVar1 = 0xe2;
      goto LAB_0010b6b0;
    }
  }
  else {
    if (param_2 == 0x8e940) {
      uVar1 = 0xe3;
      goto LAB_0010b6b0;
    }
    if (param_2 == 0xd84f0) {
      uVar1 = 0xe4;
      goto LAB_0010b6b0;
    }
  }
  uVar1 = 0xf3;
LAB_0010b6b0:
  *(undefined1 *)((long)param_1 + 3) = uVar1;
  if (param_6 == 1) {
    *(byte *)((long)param_1 + 1) = (byte)(param_4 >> 4) & 0xf | 0xe0;
  }
  return;
}


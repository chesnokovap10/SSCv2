/* get_uhq_info_from_bitrate @ 0010b390 size 344 */

void get_uhq_info_from_bitrate(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  
  uVar1 = 0;
  if (param_1 < 0x3e800) {
    if (param_1 < 0x251c0) {
      if (((param_1 == 88000) || (param_1 == 96000)) || (param_1 == 0x1f400)) {
LAB_0010b3e4:
        *param_3 = 0;
        return;
      }
    }
    else {
      if (0x37e87 < param_1) {
        if (param_1 == 0x37e88) goto LAB_0010b3e4;
        iVar2 = 250000;
        goto LAB_0010b4c0;
      }
      if (param_1 == 0x251c0) goto LAB_0010b4c8;
      if (param_1 == 0x2ee00) goto LAB_0010b3e4;
    }
LAB_0010b4dc:
    uVar3 = 0;
    uVar1 = 0;
  }
  else {
    uVar3 = 1;
    if (param_1 < 0x50140) {
      if (param_1 == 0x3e800) goto LAB_0010b4d0;
      if (param_1 == 0x470b8) goto LAB_0010b4c8;
      iVar2 = 0x4b320;
LAB_0010b4c0:
      if (param_1 != iVar2) goto LAB_0010b4dc;
    }
    else {
      if (param_1 < 0x8e940) {
        if (param_1 == 0x50140) goto LAB_0010b4d0;
        iVar2 = 0x6be90;
        goto LAB_0010b4c0;
      }
      if (param_1 != 0xd84f0) {
        iVar2 = 0x8e940;
        goto LAB_0010b4c0;
      }
    }
LAB_0010b4c8:
    uVar3 = 1;
    uVar1 = 1;
  }
LAB_0010b4d0:
  *param_2 = uVar3;
  *param_3 = uVar1;
  return;
}


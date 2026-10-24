/* get_header_from_bitrate @ 0010b0a4 size 412 */

undefined8 get_header_from_bitrate(int param_1)

{
  if (param_1 < 0x3e800) {
    if (param_1 < 0x251c0) {
      if (param_1 == 88000) {
        return 0xf0;
      }
      if (param_1 == 96000) {
        return 0xf1;
      }
      if (param_1 == 0x1f400) {
        return 0xf2;
      }
    }
    else if (param_1 < 0x37e88) {
      if (param_1 == 0x251c0) {
        return 0xe6;
      }
    }
    else {
      if (param_1 == 0x37e88) {
        return 0xf4;
      }
      if (param_1 == 250000) {
        return 0xe5;
      }
    }
  }
  else if (param_1 < 0x50140) {
    if (param_1 == 0x3e800) {
      return 0xf6;
    }
    if (param_1 == 0x470b8) {
      return 0xe0;
    }
    if (param_1 == 0x4b320) {
      return 0xe1;
    }
  }
  else if (param_1 < 0x8e940) {
    if (param_1 == 0x50140) {
      return 0xf5;
    }
    if (param_1 == 0x6be90) {
      return 0xe2;
    }
  }
  else {
    if (param_1 == 0x8e940) {
      return 0xe3;
    }
    if (param_1 == 0xd84f0) {
      return 0xe4;
    }
  }
  return 0xf3;
}


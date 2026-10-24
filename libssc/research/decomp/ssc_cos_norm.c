/* ssc_cos_norm @ 00106cd4 size 280 */

uint ssc_cos_norm(uint param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  param_1 = param_1 & 0x1ffff;
  uVar3 = 0x20000 - param_1;
  if (param_1 < 0x10001) {
    uVar3 = param_1;
  }
  if ((uVar3 & 0x7fff) != 0) {
    if (uVar3 >> 0xf == 0) {
      iVar1 = ((int)(uVar3 * 0x10000) >> 0xf) * ((int)(uVar3 * 0x10000) >> 0x10) + 0x8000 >> 0x10;
      uVar3 = 0x7fff;
      iVar1 = (0x7fff - iVar1) +
              (((int)((((iVar1 * -0x272 + 0x4000 >> 0xf) + 0x2055) * iVar1 * 2 + 0x8000U &
                      0xffff0000) + 0xe21d0000) >> 0x10) * iVar1 + 0x4000 >> 0xf);
      if (iVar1 < 0x7fff) {
        uVar3 = iVar1 + 1;
      }
      return uVar3;
    }
    iVar1 = ((int)(uVar3 * -0x10000) >> 0xf) * ((int)(uVar3 * -0x10000) >> 0x10) + 0x8000 >> 0x10;
    uVar3 = (0x7fff - iVar1) +
            (((int)((((iVar1 * -0x272 + 0x4000 >> 0xf) + 0x2055) * iVar1 * 2 + 0x8000U & 0xffff0000)
                   + 0xe21d0000) >> 0x10) * iVar1 + 0x4000 >> 0xf);
    uVar2 = 0xffff8001;
    if ((int)uVar3 < 0x7fff) {
      uVar2 = ~uVar3;
    }
    return uVar2;
  }
  if ((uVar3 & 0xffff) != 0) {
    return 0;
  }
  uVar2 = 0xffff8001;
  if ((uVar3 & 0x1ffff) == 0) {
    uVar2 = 0x7fff;
  }
  return uVar2;
}


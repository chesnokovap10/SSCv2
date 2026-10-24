/* ssc_cos_norm @ 00111670 size 252 */

uint ssc_cos_norm(uint param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  param_1 = param_1 & 0x1ffff;
  uVar3 = 0x20000 - param_1;
  if (param_1 < 0x10001) {
    uVar3 = param_1;
  }
  if ((uVar3 & 0x7fff) != 0) {
    if (uVar3 >> 0xf == 0) {
      uVar3 = uVar3 * uVar3 * 2 + 0x8000 >> 0x10;
      iVar1 = (uVar3 ^ 0x7fff) +
              ((int)(((int)(uVar3 * (((int)(uVar3 * -0x272 + 0x4000) >> 0xf) + 0x2055) * 2 +
                           -0x1de28000) >> 0x10) * uVar3 + 0x4000) >> 0xf);
      uVar3 = 0x7fff;
      if (iVar1 < 0x7fff) {
        uVar3 = iVar1 + 1;
      }
      return uVar3;
    }
    iVar1 = ((int)(uVar3 * -0x10000) >> 0xf) * ((int)(uVar3 * -0x10000) >> 0x10) + 0x8000 >> 0x10;
    uVar3 = (((iVar1 * ((iVar1 * -0x272 + 0x4000 >> 0xf) + 0x2055) * 2 + -0x1de28000 >> 0x10) *
              iVar1 + 0x4000 >> 0xf) - iVar1) + 0x7fff;
    uVar4 = 0xffff8001;
    if ((int)uVar3 < 0x7fff) {
      uVar4 = ~uVar3;
    }
    return uVar4;
  }
  uVar4 = 0xffff8001;
  if ((uVar3 & 0x1ffff) == 0) {
    uVar4 = 0x7fff;
  }
  uVar2 = 0;
  if ((uVar3 & 0xffff) == 0) {
    uVar2 = uVar4;
  }
  return uVar2;
}


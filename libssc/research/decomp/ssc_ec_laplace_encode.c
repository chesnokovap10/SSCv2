/* ssc_ec_laplace_encode @ 00110d50 size 224 */

void ssc_ec_laplace_encode(undefined8 param_1,uint *param_2,uint param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  
  uVar3 = *param_2;
  iVar5 = 0;
  if (uVar3 != 0) {
    uVar8 = (0x4000 - param_4) * (0x7fe0 - param_3);
    uVar1 = -uVar3;
    if (-1 < (int)uVar3) {
      uVar1 = uVar3;
    }
    iVar6 = 1;
    uVar7 = uVar8 >> 0xf;
    uVar4 = param_3;
    if ((0x7fff < uVar8) && (1 < (int)uVar1)) {
      iVar6 = 1;
      do {
        iVar6 = iVar6 + 1;
        uVar8 = uVar7 * 2 * param_4;
        uVar4 = uVar4 + uVar7 * 2 + 2;
        uVar7 = uVar8 >> 0xf;
        if (uVar8 < 0x8000) break;
      } while (iVar6 < (int)uVar1);
    }
    if (uVar8 >> 0xf == 0) {
      uVar8 = (int)uVar3 >> 0x1f;
      iVar5 = ((int)((uVar3 >> 0x1f | 0x8000) - uVar4) >> 1) + -1;
      iVar2 = uVar1 - iVar6;
      if (iVar5 <= (int)(uVar1 - iVar6)) {
        iVar2 = iVar5;
      }
      iVar5 = uVar4 + uVar8 + iVar2 * 2 + 1;
      param_3 = (uint)(iVar5 != 0x8000);
      *param_2 = iVar6 + uVar8 + iVar2 ^ uVar8;
    }
    else {
      param_3 = uVar7 + 1;
      iVar5 = 0;
      if (-1 < (int)uVar3) {
        iVar5 = uVar7 + 1;
      }
      iVar5 = iVar5 + uVar4;
    }
  }
  ssc_ec_encode_bin(param_1,iVar5,param_3 + iVar5,0xf);
  return;
}


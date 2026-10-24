/* ec_laplace_encode @ 00106820 size 240 */

void ec_laplace_encode(undefined8 param_1,uint *param_2,uint param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  bool bVar6;
  int iVar7;
  uint uVar8;
  
  uVar4 = *param_2;
  iVar5 = 0;
  if (uVar4 != 0) {
    uVar1 = (int)uVar4 >> 0x1f;
    uVar3 = uVar1 + uVar4 ^ uVar1;
    uVar8 = (0x4000 - param_4) * (0x7fe0 - param_3) >> 0xf;
    bVar6 = uVar8 == 0;
    iVar7 = 1;
    if ((1 < (int)uVar3) && (uVar8 != 0)) {
      iVar7 = 1;
      do {
        iVar5 = uVar8 * 2;
        uVar8 = (uint)(iVar5 * param_4) >> 0xf;
        iVar7 = iVar7 + 1;
        bVar6 = uVar8 == 0;
        param_3 = param_3 + iVar5 + 2;
        if ((int)uVar3 <= iVar7) break;
      } while (uVar8 != 0);
    }
    if (!bVar6) {
      iVar5 = (uVar8 + 1 & (uVar1 ^ 0xffffffff)) + param_3;
      ec_encode_bin(param_1,iVar5,uVar8 + 1 + iVar5,0xf);
      return;
    }
    iVar5 = ((int)((uVar4 >> 0x1f | 0x8000) - param_3) >> 1) + -1;
    iVar2 = uVar3 - iVar7;
    if (iVar5 <= (int)(uVar3 - iVar7)) {
      iVar2 = iVar5;
    }
    iVar5 = param_3 + uVar1 + (iVar2 << 1 | 1U);
    param_3 = (uint)(iVar5 != 0x8000);
    *param_2 = iVar7 + uVar1 + iVar2 ^ uVar1;
  }
  ec_encode_bin(param_1,iVar5,param_3 + iVar5,0xf);
  return;
}


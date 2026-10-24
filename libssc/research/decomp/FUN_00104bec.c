/* FUN_00104bec @ 00104bec size 784 */

void FUN_00104bec(long param_1,int param_2,undefined8 param_3,undefined4 *param_4,undefined8 param_5
                 ,undefined8 param_6,int param_7,int *param_8,uint param_9,int param_10,int param_11
                 ,uint *param_12)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  
  iVar5 = param_7 * 2 + -1;
  iVar4 = (int)*(short *)(param_1 + (long)param_2 * 2) + param_11 * 8;
  uVar11 = (*param_8 - iVar4) - 0x20;
  uVar3 = 0;
  if (iVar5 != 0) {
    uVar3 = (*param_8 + ((iVar4 >> 1) + -4) * iVar5) / iVar5;
  }
  if ((int)uVar3 <= (int)uVar11) {
    uVar11 = uVar3;
  }
  if (0x3f < (int)uVar11) {
    uVar11 = 0x40;
  }
  if ((int)uVar11 < 4) {
    uVar11 = 1;
  }
  else {
    uVar11 = ((int)(short)(&DAT_00113540)[uVar11 & 7] >> (0xe - (uVar11 >> 3) & 0x1f)) + 1U &
             0xfffffffe;
  }
  uVar3 = stereo_itheta(param_5,param_6,0,param_7);
  iVar4 = ec_tell_frac(param_3);
  if (uVar11 != 1) {
    uVar1 = uVar3 * uVar11 + 0x2000;
    iVar5 = (int)uVar1 >> 0xe;
    if (param_10 < 2) {
      iVar9 = ((int)uVar11 >> 1) + 1;
      iVar10 = (uVar11 + 1) - iVar5;
      if ((int)uVar11 >> 1 < iVar5) {
        iVar5 = iVar9 * iVar9 - ((int)(iVar10 * ((uVar11 + 2) - iVar5)) >> 1);
      }
      else {
        iVar10 = iVar5 + 1;
        iVar5 = (iVar5 + 1) * iVar5 >> 1;
      }
      ec_encode(param_3,iVar5,iVar5 + iVar10);
    }
    else {
      ec_enc_uint(param_3,iVar5,uVar11 + 1);
    }
    uVar3 = 0;
    if (uVar11 != 0) {
      uVar3 = (int)(uVar1 & 0xffffc000) / (int)uVar11;
    }
  }
  iVar5 = ec_tell_frac(param_3);
  *param_8 = *param_8 - (iVar5 - iVar4);
  if (uVar3 == 0x4000) {
    iVar9 = 0;
    iVar8 = 0x4000;
    *param_12 = *param_12 & ~(-1 << (ulong)(param_9 & 0x1f)) << (ulong)(param_9 & 0x1f);
    iVar10 = 0x7fff;
  }
  else if (uVar3 == 0) {
    iVar10 = 0;
    iVar8 = -0x4000;
    *param_12 = *param_12 & (-1 << (ulong)(param_9 & 0x1f) ^ 0xffffffffU);
    iVar9 = 0x7fff;
  }
  else {
    iVar10 = uVar3 * -0x10000 + 0x40000000;
    iVar9 = (int)((-(uVar3 >> 0xf & 1) & 0xfff80000 | (uVar3 & 0xffff) << 3) * (int)(short)uVar3 +
                 0x8000) >> 0x10;
    iVar10 = (iVar10 >> 0xd) * (iVar10 >> 0x10) + 0x8000 >> 0x10;
    iVar9 = (int)(((0x7fff - iVar9) +
                  (((int)((((iVar9 * -0x272 + 0x4000 >> 0xf) + 0x2055) * iVar9 * 2 + 0x8000U &
                          0xffff0000) + 0xe21d0000) >> 0x10) * iVar9 + 0x4000U >> 0xf)) * 0x10000 +
                 0x10000) >> 0x10;
    iVar10 = (int)(((0x7fff - iVar10) +
                   (((int)((((iVar10 * -0x272 + 0x4000 >> 0xf) + 0x2055) * iVar10 * 2 + 0x8000U &
                           0xffff0000) + 0xe21d0000) >> 0x10) * iVar10 + 0x4000U >> 0xf)) * 0x10000
                  + 0x10000) >> 0x10;
    iVar6 = ec_ilog(iVar9);
    iVar7 = ec_ilog(iVar10);
    iVar8 = (int)(short)(iVar10 << (ulong)(0xfU - iVar7 & 0x1f));
    iVar2 = (int)(short)(iVar9 << (ulong)(0xfU - iVar6 & 0x1f));
    iVar8 = (int)(short)((((short)iVar7 - (short)iVar6) * 0x800 -
                         (short)(((iVar2 * -0xa25 + 0x4000 >> 0xf) + 0x1efc) * iVar2 + 0x4000U >>
                                0xf)) +
                        (short)(((iVar8 * -0xa25 + 0x4000 >> 0xf) + 0x1efc) * iVar8 + 0x4000U >> 0xf
                               )) * (int)(short)((short)param_7 * 0x80 + -0x80) + 0x4000 >> 0xf;
  }
  *param_4 = 0;
  param_4[1] = iVar9;
  param_4[2] = iVar10;
  param_4[3] = iVar8;
  param_4[4] = uVar3;
  param_4[5] = iVar5 - iVar4;
  return;
}


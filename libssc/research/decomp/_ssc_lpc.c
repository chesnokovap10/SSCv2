/* _ssc_lpc @ 00110e30 size 532 */

void _ssc_lpc(undefined2 *param_1,int *param_2)

{
  int iVar1;
  long lVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined2 uVar6;
  int iVar7;
  int iVar8;
  
  iVar5 = *param_2;
  if (iVar5 == 0) {
    iVar8 = 0;
LAB_00110efc:
    iVar7 = 0;
    iVar3 = 0;
  }
  else {
    iVar3 = ssc_frac_div32(param_2[1] & 0xfffffff8,iVar5);
    iVar3 = -iVar3;
    iVar1 = iVar5 >> 10;
    iVar8 = iVar3 >> 3;
    iVar5 = iVar5 - (int)(((ulong)((long)iVar3 * (long)iVar3) >> 0x1f) * (long)iVar5 >> 0x1f);
    if (iVar5 < iVar1) goto LAB_00110efc;
    iVar3 = ssc_frac_div32(((uint)((ulong)((long)param_2[1] * (long)iVar8) >> 0x1c) & 0xfffffff8) +
                           param_2[2] & 0xfffffff8,iVar5);
    iVar3 = -iVar3;
    iVar7 = iVar3 >> 3;
    iVar8 = iVar8 + (int)((ulong)((long)iVar3 * (long)iVar8) >> 0x1f);
    iVar5 = iVar5 - (int)(((ulong)((long)iVar3 * (long)iVar3) >> 0x1f) * (long)iVar5 >> 0x1f);
    if (iVar5 < iVar1) {
      iVar3 = 0;
      uVar6 = 0;
      goto LAB_00110f08;
    }
    iVar4 = ssc_frac_div32(param_2[3] +
                           ((int)((ulong)((long)param_2[1] * (long)iVar7) >> 0x1f) +
                           (int)((ulong)((long)param_2[2] * (long)iVar8) >> 0x1f)) * 8 & 0xfffffff8,
                           iVar5);
    iVar4 = -iVar4;
    iVar3 = iVar4 >> 3;
    lVar2 = (long)iVar8;
    iVar8 = iVar8 + (int)((ulong)((long)iVar4 * (long)iVar7) >> 0x1f);
    iVar7 = iVar7 + (int)((ulong)(iVar4 * lVar2) >> 0x1f);
    if (iVar1 <= iVar5 - (int)(((ulong)((long)iVar4 * (long)iVar4) >> 0x1f) * (long)iVar5 >> 0x1f))
    {
      iVar5 = ssc_frac_div32(param_2[4] +
                             ((int)((ulong)((long)param_2[2] * (long)iVar7) >> 0x1f) +
                              (int)((ulong)((long)param_2[3] * (long)iVar8) >> 0x1f) +
                             (int)((ulong)((long)param_2[1] * (long)iVar3) >> 0x1f)) * 8 &
                             0xfffffff8);
      iVar5 = -iVar5;
      lVar2 = (long)iVar8;
      iVar8 = iVar8 + (int)((ulong)((long)iVar5 * (long)iVar3) >> 0x1f);
      iVar3 = iVar3 + (int)((ulong)(iVar5 * lVar2) >> 0x1f);
      iVar7 = iVar7 + (int)((ulong)((long)iVar5 * (long)iVar7) >> 0x1f);
      uVar6 = (undefined2)((uint)((iVar5 >> 3) + 0x8000) >> 0x10);
      goto LAB_00110f08;
    }
  }
  uVar6 = 0;
LAB_00110f08:
  param_1[3] = uVar6;
  *param_1 = (short)((uint)(iVar8 + 0x8000) >> 0x10);
  param_1[1] = (short)((uint)(iVar7 + 0x8000) >> 0x10);
  param_1[2] = (short)((uint)(iVar3 + 0x8000) >> 0x10);
  return;
}


/* ssc_comb_filter @ 00107410 size 396 */

void ssc_comb_filter(long param_1,long param_2,undefined8 param_3,int param_4,int param_5,
                    uint param_6,uint param_7,uint param_8)

{
  int iVar1;
  ulong uVar2;
  
  if (((param_7 | param_6) & 0xffff) == 0) {
    if (param_2 == param_1) {
      return;
    }
LAB_00107500:
    SSC_COPY32(param_1,param_2,param_5);
    return;
  }
  uVar2 = (ulong)param_8;
  if ((param_6 & 0xffff) == 0) {
    ssc_comb_filter_function1_asm(param_1,param_2,param_4,param_7,uVar2,win_square);
  }
  else {
    if ((param_7 & 0xffff) == 0) {
      ssc_comb_filter_function2_asm(param_1,param_2,param_3,param_6,uVar2,win_square);
      if (param_2 == param_1) {
        return;
      }
      param_5 = param_5 - param_8;
      param_1 = param_1 + (long)(int)param_8 * 4;
      param_2 = param_2 + (long)(int)param_8 * 4;
      goto LAB_00107500;
    }
    if ((int)param_3 == param_4) {
      ssc_comb_filter_function3_asm(param_1,param_2,param_3,param_6,param_7,uVar2,win_square);
    }
    else {
      ssc_comb_filter_function4_asm
                (param_1,param_2,param_3,param_4,param_6,param_7,uVar2,win_square);
    }
  }
  uVar2 = -(ulong)(param_8 >> 0x1f) & 0xfffffffc00000000 | uVar2 << 2;
  iVar1 = (int)(short)param_7;
  ssc_comb_filter_const_asm
            (param_1 + uVar2,param_2 + uVar2,param_4,param_5 - param_8,iVar1 * 0x4e80 >> 0x10,
             iVar1 * 0x1bc8 >> 0xf,iVar1 * 0x1098 >> 0xf);
  return;
}


/* last_band_info_calc @ 0010b05c size 72 */

ulong last_band_info_calc(int param_1,uint param_2,long param_3)

{
  ulong uVar1;
  int iVar2;
  
  if ((int)param_2 < 1) {
    return 0;
  }
  uVar1 = (ulong)param_2;
  iVar2 = param_2 << 1;
  do {
    if (param_1 < *(int *)(param_3 + (long)(iVar2 + -1) * 4) +
                  *(int *)(param_3 + (long)((int)uVar1 + -1) * 4) >> 1) {
      return uVar1;
    }
    uVar1 = uVar1 - 1;
    iVar2 = iVar2 + -1;
  } while (uVar1 != 0);
  return 0;
}


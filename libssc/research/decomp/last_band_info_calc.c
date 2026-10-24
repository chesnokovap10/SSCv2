/* last_band_info_calc @ 0010d118 size 80 */

int last_band_info_calc(int param_1,int param_2,long param_3)

{
  int iVar1;
  long lVar2;
  int iVar3;
  
  if (0 < param_2) {
    iVar3 = param_2 * 2;
    lVar2 = 0;
    iVar1 = param_2;
    do {
      iVar3 = iVar3 + -1;
      if (param_1 < *(int *)(param_3 + (long)iVar3 * 4) + *(int *)(param_3 + (long)(iVar1 + -1) * 4)
                    >> 1) {
        return iVar1;
      }
      lVar2 = lVar2 + 1;
      iVar1 = iVar1 + -1;
    } while (lVar2 < param_2);
  }
  return 0;
}


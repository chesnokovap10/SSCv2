/* SSC_COPY32 @ 00111b94 size 40 */

void SSC_COPY32(long param_1,long param_2,int param_3)

{
  long lVar1;
  long lVar2;
  
  if (param_3 != 0) {
    lVar1 = (long)param_3 + -1;
    do {
      lVar2 = lVar1 * 4;
      lVar1 = lVar1 + -1;
      *(undefined4 *)(param_1 + lVar2) = *(undefined4 *)(param_2 + lVar2);
    } while (lVar1 != -1);
  }
  return;
}


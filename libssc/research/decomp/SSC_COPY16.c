/* SSC_COPY16 @ 00111bbc size 40 */

void SSC_COPY16(long param_1,long param_2,int param_3)

{
  long lVar1;
  long lVar2;
  
  if (param_3 != 0) {
    lVar1 = (long)param_3 + -1;
    do {
      lVar2 = lVar1 * 2;
      lVar1 = lVar1 + -1;
      *(undefined2 *)(param_1 + lVar2) = *(undefined2 *)(param_2 + lVar2);
    } while (lVar1 != -1);
  }
  return;
}


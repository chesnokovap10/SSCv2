/* SSC_COPY8 @ 00111be4 size 36 */

void SSC_COPY8(long param_1,long param_2,int param_3)

{
  long lVar1;
  long lVar2;
  long lVar3;
  
  if (param_3 != 0) {
    lVar3 = (long)param_3;
    do {
      lVar1 = param_2 + lVar3;
      lVar2 = param_1 + lVar3;
      lVar3 = lVar3 + -1;
      *(undefined1 *)(lVar2 + -1) = *(undefined1 *)(lVar1 + -1);
    } while (lVar3 != 0);
  }
  return;
}


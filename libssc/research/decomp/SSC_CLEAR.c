/* SSC_CLEAR @ 00111c08 size 48 */

void SSC_CLEAR(long param_1,uint param_2)

{
  if (param_2 != 0) {
    memset((void *)(param_1 + ~(ulong)(param_2 - 1) + (long)(int)param_2),0,(ulong)param_2);
  }
  return;
}


/* SSC_CLEAR @ 00115640 size 36 */

void SSC_CLEAR(void *param_1,uint param_2)

{
  if (0 < (int)param_2) {
    memset(param_1,0,(ulong)param_2);
  }
  return;
}


/* headroom_process @ 0010d030 size 12 */

void headroom_process(void)

{
  int in_w4;
  
  if (in_w4 != 0) {
    uhq_headroom();
    return;
  }
  normal_headroom();
  return;
}


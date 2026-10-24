/* headroom_process @ 0010add8 size 12 */

void headroom_process(void)

{
  int in_w5;
  
  if (in_w5 != 0) {
    uhq_headroom();
    return;
  }
  normal_headroom();
  return;
}


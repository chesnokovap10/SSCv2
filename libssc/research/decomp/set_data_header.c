/* set_data_header @ 0010b4e8 size 28 */

void set_data_header(long param_1,undefined1 param_2,uint param_3,int param_4)

{
  *(undefined1 *)(param_1 + 3) = param_2;
  if (param_4 == 1) {
    *(byte *)(param_1 + 1) = (byte)(param_3 >> 4) & 0xf | 0xe0;
  }
  return;
}


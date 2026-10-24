/* ssc_encoder_get_size @ 0010b960 size 76 */

int ssc_encoder_get_size(int param_1,undefined4 param_2)

{
  long lVar1;
  
  lVar1 = ssc_custom_mode_create(param_2,0x360,0);
  return (*(int *)(lVar1 + 8) * 6 + *(int *)(lVar1 + 4) * 4 + 0x1000) * param_1 + 300;
}


/* ssc_ec_enc_init @ 0010f824 size 44 */

void ssc_ec_enc_init(undefined8 *param_1,undefined8 param_2,undefined4 param_3)

{
  *param_1 = param_2;
  *(undefined4 *)(param_1 + 1) = param_3;
  *(undefined8 *)((long)param_1 + 0x2c) = 0xffffffff;
  *(undefined8 *)((long)param_1 + 0x14) = 0x1900000000;
  *(undefined8 *)((long)param_1 + 0xc) = 0;
  *(undefined8 *)((long)param_1 + 0x24) = 0;
  *(undefined8 *)((long)param_1 + 0x1c) = 0x80000000000000;
  return;
}


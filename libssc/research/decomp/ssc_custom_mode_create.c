/* ssc_custom_mode_create @ 00111ac8 size 100 */

undefined * ssc_custom_mode_create(int param_1,undefined8 param_2,undefined4 *param_3)

{
  undefined *puVar1;
  
  if (param_3 != (undefined4 *)0x0) {
    *param_3 = 0;
  }
  puVar1 = &DAT_0011b9c0;
  if ((param_1 != 0xac44) && (param_1 != 48000)) {
    if (param_1 == 96000) {
      return &DAT_0011ba40;
    }
    if (param_3 == (undefined4 *)0x0) {
      return (undefined *)0x0;
    }
    puVar1 = (undefined *)0x0;
    *param_3 = 0xffffffff;
  }
  return puVar1;
}


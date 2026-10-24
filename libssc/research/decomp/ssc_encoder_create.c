/* ssc_encoder_create @ 0010a0b8 size 180 */

void * ssc_encoder_create(ulong param_1,int param_2,undefined4 param_3,int *param_4)

{
  int iVar1;
  long lVar2;
  void *__ptr;
  
  lVar2 = ssc_custom_mode_create(param_1,0x360,0);
  __ptr = malloc((long)((*(int *)(lVar2 + 8) * 6 + *(int *)(lVar2 + 4) * 4 + 0x1000) * param_2 +
                       0xdc));
  if (__ptr == (void *)0x0) {
    if (param_4 != (int *)0x0) {
      *param_4 = -7;
      return (void *)0x0;
    }
  }
  else {
    iVar1 = ssc_encoder_init(__ptr,param_1 & 0xffffffff,param_2,param_3);
    if (param_4 != (int *)0x0) {
      *param_4 = iVar1;
    }
    if (iVar1 == 0) {
      return __ptr;
    }
    free(__ptr);
  }
  return (void *)0x0;
}


/* ssc_encoder_init @ 00109f54 size 356 */

undefined8 ssc_encoder_init(long *param_1,int param_2,uint param_3,undefined4 param_4)

{
  undefined4 uVar1;
  long lVar2;
  undefined8 uVar3;
  
  lVar2 = ssc_custom_mode_create(param_2,0x360,0);
  SSC_CLEAR(param_1,(*(int *)(lVar2 + 8) * 6 + *(int *)(lVar2 + 4) * 4 + 0x1000) * param_3 + 0xdc);
  lVar2 = ssc_custom_mode_create(param_2,0x360,0);
  if (param_3 < 3) {
    uVar3 = 0xfffffff9;
    if ((param_1 != (long *)0x0) && (lVar2 != 0)) {
      SSC_CLEAR(param_1,(*(int *)(lVar2 + 8) * 6 + *(int *)(lVar2 + 4) * 4 + 0x1000) * param_3 +
                        0xdc);
      uVar1 = *(undefined4 *)(lVar2 + 4);
      *param_1 = lVar2;
      *(undefined4 *)(param_1 + 1) = uVar1;
      *(uint *)((long)param_1 + 0xc) = param_3;
      uVar1 = *(undefined4 *)(lVar2 + 0xc);
      *(undefined4 *)(param_1 + 5) = 0x100;
      param_1[4] = 0x100000002;
      *(undefined4 *)((long)param_1 + 0x14) = uVar1;
      *(undefined4 *)(param_1 + 3) = 0xffffffff;
      param_1[6] = 0;
      *(undefined4 *)(param_1 + 0x10) = 0;
      *(undefined8 *)((long)param_1 + 0x84) = 0;
      *(uint *)((long)param_1 + 0xc) = param_3;
      *(undefined4 *)(param_1 + 2) = 0;
      *(int *)(param_1 + 0xc) = param_2;
      *(int *)((long)param_1 + 100) = param_2;
      *(undefined4 *)((long)param_1 + 0x6c) = param_4;
      param_1[0x19] = 0;
      param_1[0x18] = 0;
      param_1[0x1b] = 0;
      param_1[0x1a] = 0;
      param_1[0x15] = 0;
      param_1[0x14] = 0;
      param_1[0x17] = 0;
      param_1[0x16] = 0;
      param_1[0x13] = 0;
      param_1[0x12] = 0;
      *(undefined4 *)((long)param_1 + 0x8c) = 0x10000;
      if (param_2 == 48000) {
        *(undefined4 *)(param_1 + 0xc) = 0xac44;
      }
      previous_uhq_index = 0;
      SSC_DRC_Init(param_2,param_3);
      SSC_DRC_SetPar(1,0x7b8e,0,50000,0);
      uVar3 = 0;
    }
  }
  else {
    uVar3 = 0xffffffff;
  }
  return uVar3;
}


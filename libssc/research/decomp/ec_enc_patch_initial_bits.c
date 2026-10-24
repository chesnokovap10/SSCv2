/* ec_enc_patch_initial_bits @ 001059e8 size 148 */

void ec_enc_patch_initial_bits(undefined8 *param_1,int param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = -param_3 + 8;
  uVar1 = ~(-1 << (ulong)(param_3 & 0x1f)) << (ulong)(uVar2 & 0x1f);
  if (*(int *)((long)param_1 + 0x1c) != 0) {
    *(byte *)*param_1 =
         *(byte *)*param_1 & ((byte)uVar1 ^ 0xff) | (byte)(param_2 << (ulong)(uVar2 & 0x1f));
    return;
  }
  if (-1 < (int)*(uint *)((long)param_1 + 0x2c)) {
    *(uint *)((long)param_1 + 0x2c) =
         *(uint *)((long)param_1 + 0x2c) & (uVar1 ^ 0xffffffff) | param_2 << (ulong)(uVar2 & 0x1f);
    return;
  }
  if (0x800000U >> (ulong)(param_3 & 0x1f) < *(uint *)(param_1 + 4)) {
    *(undefined4 *)(param_1 + 6) = 0xffffffff;
    return;
  }
  *(uint *)((long)param_1 + 0x24) =
       *(uint *)((long)param_1 + 0x24) & (uVar1 << 0xf ^ 0xffffffff) |
       param_2 << (ulong)(-param_3 + 0x17 & 0x1f);
  return;
}


/* print_enc_fields @ 00115664 size 184 */

int print_enc_fields(long param_1)

{
  int iVar1;
  
  printf("enc->end_offs = %d\n",(ulong)*(uint *)(param_1 + 0xc));
  printf("enc->end_window = %d\n",(ulong)*(uint *)(param_1 + 0x10));
  printf("enc->nend_bits = %d\n",(ulong)*(uint *)(param_1 + 0x14));
  printf("enc->nbits_total = %d\n",(ulong)*(uint *)(param_1 + 0x18));
  printf("enc->offs = %d\n",(ulong)*(uint *)(param_1 + 0x1c));
  printf("enc->rng = %d\n",(ulong)*(uint *)(param_1 + 0x20));
  printf("enc->val = %d\n",(ulong)*(uint *)(param_1 + 0x24));
  printf("enc->ext = %d\n",(ulong)*(uint *)(param_1 + 0x28));
  printf("enc->rem = %d\n",(ulong)*(uint *)(param_1 + 0x2c));
  iVar1 = printf("enc->error = %d\n",(ulong)*(uint *)(param_1 + 0x30));
  return iVar1;
}


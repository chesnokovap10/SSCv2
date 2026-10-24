/* ec_enc_shrink @ 00105a7c size 64 */

void ec_enc_shrink(long *param_1,uint param_2)

{
  SSC_COPY8((*param_1 + (ulong)param_2) - (ulong)*(uint *)((long)param_1 + 0xc),
            (*param_1 + (ulong)*(uint *)(param_1 + 1)) - (ulong)*(uint *)((long)param_1 + 0xc));
  *(uint *)(param_1 + 1) = param_2;
  return;
}


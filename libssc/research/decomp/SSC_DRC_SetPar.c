/* SSC_DRC_SetPar @ 0010737c size 56 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void SSC_DRC_SetPar(int param_1,undefined4 param_2)

{
  DRC_ModeFlag = (uint)(param_1 == 1);
  drc_struct = param_2;
  _DAT_00120504 = 0x3ca4a100000000;
  DAT_0012050c = 0x400000;
  return;
}


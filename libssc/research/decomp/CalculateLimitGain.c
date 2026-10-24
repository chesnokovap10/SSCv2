/* CalculateLimitGain @ 00106f0c size 424 */

int CalculateLimitGain(int param_1,int param_2,uint param_3,int param_4)

{
  int iVar1;
  int iVar2;
  long lVar3;
  
  if ((int)param_3 < 0x17701) {
    iVar2 = -0x50;
    iVar1 = 0x76c0;
  }
  else {
    if (0x1f400 < param_3) {
      if (param_4 == 96000) {
        lVar3 = (long)param_2;
        iVar2 = (int)((ulong)((long)param_2 * 0xf0a4) >> 0x10);
        if (param_3 < 270000) {
          if (iVar2 <= param_1) {
            return 0x7b4c;
          }
          if ((int)((ulong)(lVar3 * 0xeb85) >> 0x10) <= param_1) {
            return 0x7a52;
          }
          if ((int)((ulong)(lVar3 * 0xe666) >> 0x10) <= param_1) {
            return 0x796c;
          }
          if ((int)((ulong)(lVar3 * 0xcccc) >> 0x10) <= param_1) {
            return 0x7890;
          }
        }
        else {
          if (iVar2 <= param_1) {
            return 0x7b4c;
          }
          if ((int)((ulong)(lVar3 * 0xeb85) >> 0x10) <= param_1) {
            return 0x7a01;
          }
          if ((int)((ulong)(lVar3 * 0xe666) >> 0x10) <= param_1) {
            return 0x78f4;
          }
          if ((int)((ulong)(lVar3 * 0xcccc) >> 0x10) <= param_1) {
            return 0x785e;
          }
        }
        return 0x75d4;
      }
      if ((int)((ulong)((long)param_2 * 0xe666) >> 0x10) <= param_1) {
        return 0x7a94;
      }
      if ((int)((ulong)((long)param_2 * 0xcccc) >> 0x10) <= param_1) {
        return 0x76b3;
      }
      iVar2 = 0x741d;
      goto LAB_00106f5c;
    }
    iVar2 = -0x2f8;
    iVar1 = 0x78b4;
  }
  if ((int)((ulong)((long)param_2 * 0xe666) >> 0x10) <= param_1) {
    return iVar1;
  }
  iVar2 = iVar2 + iVar1;
LAB_00106f5c:
  iVar1 = 0x8000;
  if (param_2 >> 2 <= param_1) {
    iVar1 = iVar2;
  }
  return iVar1;
}


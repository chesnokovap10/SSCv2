/* CalculateLimitGain @ 0010b3e0 size 492 */

int CalculateLimitGain(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  long lVar4;
  
  if (param_3 < 0x17701) {
    iVar3 = 0x76c0;
    iVar2 = 0x50;
  }
  else {
    if (0x1f400 < param_3) {
      if (param_4 != 96000) {
        if ((int)((ulong)((long)param_2 * 0xe666) >> 0x10) <= param_1) {
          return 0x7a94;
        }
        iVar3 = (int)((ulong)((long)param_2 * 0xcccc) >> 0x10);
        if (param_1 < iVar3) {
          iVar2 = 0x8000;
          if (param_1 <= iVar3 && param_2 >> 2 <= param_1) {
            iVar2 = 0x741d;
          }
          return iVar2;
        }
        return 0x76b3;
      }
      lVar4 = (long)param_2;
      iVar3 = (int)((ulong)((long)param_2 * 0xf0a4) >> 0x10);
      if (param_3 < 270000) {
        if (iVar3 <= param_1) {
          return 0x7b4c;
        }
        if ((int)((ulong)(lVar4 * 0xeb85) >> 0x10) <= param_1) {
          return 0x7a52;
        }
        if ((int)((ulong)(lVar4 * 0xe666) >> 0x10) <= param_1) {
          return 0x796c;
        }
        if ((int)((ulong)(lVar4 * 0xcccc) >> 0x10) <= param_1) {
          return 0x7890;
        }
      }
      else {
        if (iVar3 <= param_1) {
          return 0x7b4c;
        }
        if ((int)((ulong)(lVar4 * 0xeb85) >> 0x10) <= param_1) {
          return 0x7a01;
        }
        if ((int)((ulong)(lVar4 * 0xe666) >> 0x10) <= param_1) {
          return 0x78f4;
        }
        if ((int)((ulong)(lVar4 * 0xcccc) >> 0x10) <= param_1) {
          return 0x785e;
        }
      }
      return 0x75d4;
    }
    iVar3 = 0x78b4;
    iVar2 = 0x2f8;
  }
  if ((int)((ulong)((long)param_2 * 0xe666) >> 0x10) <= param_1) {
    return iVar3;
  }
  iVar1 = 0x8000;
  if (param_2 >> 2 <= param_1) {
    iVar1 = iVar3 - iVar2;
  }
  return iVar1;
}


/* ec_ilog @ 001051cc size 108 */

byte ec_ilog(uint param_1)

{
  byte bVar1;
  uint uVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  
  bVar3 = param_1 >> 0x10 != 0;
  uVar2 = param_1 >> ((ulong)bVar3 << 4);
  bVar4 = (uVar2 & 0xff00) != 0;
  uVar2 = uVar2 >> ((ulong)bVar4 << 3);
  bVar5 = (uVar2 & 0xf0) != 0;
  uVar2 = uVar2 >> ((ulong)bVar5 << 2);
  bVar6 = (uVar2 & 0xc) != 0;
  bVar1 = bVar3 << 4 | bVar4 << 3 | bVar5 << 2 | param_1 != 0 | bVar6 << 1;
  if ((2 << ((ulong)bVar6 << 1) & uVar2) != 0) {
    bVar1 = bVar1 + 1;
  }
  return bVar1;
}


/* ec_tell_frac @ 00105238 size 180 */

int ec_tell_frac(long param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  bool bVar8;
  
  uVar2 = *(uint *)(param_1 + 0x20);
  bVar5 = uVar2 >> 0x10 != 0;
  uVar3 = uVar2 >> ((ulong)bVar5 << 4);
  bVar6 = (uVar3 & 0xff00) != 0;
  uVar3 = uVar3 >> ((ulong)bVar6 << 3);
  bVar7 = (uVar3 & 0xf0) != 0;
  uVar3 = uVar3 >> ((ulong)bVar7 << 2);
  bVar8 = (uVar3 & 0xc) != 0;
  uVar1 = (uint)bVar5 << 4 | (uint)bVar6 << 3 | (uint)bVar7 << 2 |
          (uint)(uVar2 != 0) | (uint)bVar8 << 1;
  if ((2 << ((ulong)bVar8 << 1) & uVar3) != 0) {
    uVar1 = uVar1 + 1;
  }
  uVar2 = uVar2 >> (ulong)(uVar1 - 0x10 & 0x1f);
  uVar2 = uVar2 * uVar2;
  uVar3 = (uVar2 >> 0xf) >> (ulong)(uVar2 >> 0x1f);
  uVar3 = uVar3 * uVar3;
  uVar4 = (uVar3 >> 0xf) >> (ulong)(uVar3 >> 0x1f);
  return *(int *)(param_1 + 0x18) * 8 -
         (int)(((((CONCAT44(uVar1,uVar2) >> 0x1f) << 0x20 | (ulong)uVar3) >> 0x1f) << 0x20 |
               (ulong)(uVar4 * uVar4)) >> 0x1f);
}


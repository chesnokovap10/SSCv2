/* _ssc_lpc @ 001117a8 size 372 */

void _ssc_lpc(undefined8 *param_1,int *param_2)

{
  int iVar1;
  ulong uVar2;
  long lVar3;
  ulong uVar4;
  int iVar5;
  long lVar6;
  ulong uVar7;
  int *piVar8;
  int *piVar9;
  int iVar10;
  ulong uVar11;
  int *piVar12;
  ulong uVar13;
  undefined8 uVar14;
  int local_84;
  int local_80 [6];
  long local_68;
  
  lVar3 = tpidr_el0;
  local_68 = *(long *)(lVar3 + 0x28);
  iVar10 = *param_2;
  local_80[0] = 0;
  local_80[1] = 0;
  local_80[2] = 0;
  local_80[3] = 0;
  if (iVar10 == 0) {
    uVar14 = 0;
  }
  else {
    uVar11 = 0;
    piVar12 = &local_84;
    uVar13 = 1;
    uVar7 = 0;
    do {
      if (3 < uVar7) break;
      iVar5 = 0;
      uVar2 = uVar11;
      piVar8 = local_80;
      uVar4 = uVar7;
      while (uVar4 != 0) {
        iVar5 = iVar5 + (int)((ulong)((long)*(int *)((long)param_2 + uVar2) * (long)*piVar8) >> 0x1f
                             );
        uVar2 = uVar2 - 4;
        piVar8 = piVar8 + 1;
        uVar4 = uVar2;
      }
      uVar2 = uVar7 + 1;
      iVar5 = frac_div32(param_2[uVar2] + iVar5 * 8 & 0xfffffff8,iVar10);
      lVar6 = (long)-iVar5;
      local_80[uVar7] = -iVar5 >> 3;
      if ((uVar2 & 0xfffffffe) != 0) {
        uVar7 = uVar13 >> 1;
        piVar8 = local_80;
        piVar9 = piVar12;
        do {
          iVar5 = *piVar9;
          iVar1 = *piVar8;
          uVar7 = uVar7 - 1;
          *piVar8 = iVar1 + (int)((ulong)(iVar5 * lVar6) >> 0x1f);
          *piVar9 = iVar5 + (int)((ulong)(iVar1 * lVar6) >> 0x1f);
          piVar8 = piVar8 + 1;
          piVar9 = piVar9 + -1;
        } while (uVar7 != 0);
      }
      iVar10 = iVar10 - (int)(((ulong)(lVar6 * lVar6) >> 0x1f) * (long)iVar10 >> 0x1f);
      uVar11 = uVar11 + 4;
      piVar12 = piVar12 + 1;
      uVar13 = uVar13 + 1;
      uVar7 = uVar2;
    } while (*param_2 >> 10 <= iVar10);
    uVar14 = CONCAT26((short)((uint)(SUB84(local_80._8_8_,4) + 0x8000) >> 0x10),
                      CONCAT24((short)((uint)((int)local_80._8_8_ + 0x8000) >> 0x10),
                               CONCAT22((short)((uint)(SUB84(local_80._0_8_,4) + 0x8000) >> 0x10),
                                        (short)((uint)((int)local_80._0_8_ + 0x8000) >> 0x10))));
  }
  *param_1 = uVar14;
  if (*(long *)(lVar3 + 0x28) == local_68) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


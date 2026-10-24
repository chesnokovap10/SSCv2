/* FUN_00109ca4 @ 00109ca4 size 404 */

void FUN_00109ca4(long param_1,undefined8 *param_2,undefined8 *param_3,long param_4,int param_5,
                 uint param_6)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  short sVar5;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  short sVar10;
  ulong uVar11;
  long lVar12;
  ulong uVar13;
  short *psVar14;
  ulong uVar15;
  short *psVar16;
  undefined8 *puVar17;
  undefined8 *puVar18;
  undefined8 uVar19;
  undefined8 uVar20;
  
  iVar3 = *(int *)(param_4 + (long)param_5 * 4);
  iVar4 = *(int *)(param_4 + (long)(*(int *)(param_1 + 8) + param_5) * 4);
  iVar7 = iVar3;
  if (iVar3 <= iVar4) {
    iVar7 = iVar4;
  }
  iVar6 = 0x1f - (int)LZCOUNT(iVar7);
  if (iVar7 < 1) {
    iVar6 = 0;
  }
  uVar1 = iVar4 << (ulong)(0xdU - iVar6 & 0x1f);
  if (0xd < iVar6) {
    uVar1 = iVar4 >> (iVar6 - 0xdU & 0x1f);
  }
  uVar2 = iVar3 << (ulong)(0xdU - iVar6 & 0x1f);
  if (0xd < iVar6) {
    uVar2 = iVar3 >> (iVar6 - 0xdU & 0x1f);
  }
  sVar10 = ssc_sqrt((int)(short)uVar1 * (int)(short)uVar1 + (int)(short)uVar2 * (int)(short)uVar2 +
                    1);
  if (0 < (int)param_6) {
    iVar7 = (int)(short)(sVar10 + 1);
    sVar10 = 0;
    if (iVar7 != 0) {
      sVar10 = (short)((int)(-(uVar2 >> 0xf & 1) & 0xc0000000 | (uVar2 & 0xffff) << 0xe) / iVar7);
    }
    sVar5 = 0;
    if (iVar7 != 0) {
      sVar5 = (short)((int)(-(uVar1 >> 0xf & 1) & 0xc0000000 | (uVar1 & 0xffff) << 0xe) / iVar7);
    }
    iVar7 = (int)sVar10;
    iVar3 = (int)sVar5;
    uVar11 = (ulong)param_6;
    if ((param_6 < 8) ||
       ((param_2 < (undefined8 *)((long)param_3 + uVar11 * 2) &&
        (param_3 < (undefined8 *)((long)param_2 + uVar11 * 2))))) {
      uVar13 = 0;
    }
    else {
      uVar13 = uVar11 & 0xfffffff8;
      uVar15 = uVar13;
      puVar17 = param_3;
      puVar18 = param_2;
      do {
        uVar9 = puVar17[1];
        uVar8 = *puVar17;
        uVar20 = puVar18[1];
        uVar19 = *puVar18;
        uVar15 = uVar15 - 8;
        puVar18[1] = CONCAT26((short)((uint)(iVar3 * (short)((ulong)uVar9 >> 0x30)) >> 0xe) +
                              (short)((uint)(iVar7 * (short)((ulong)uVar20 >> 0x30)) >> 0xe),
                              CONCAT24((short)((uint)(iVar3 * (short)((ulong)uVar9 >> 0x20)) >> 0xe)
                                       + (short)((uint)(iVar7 * (short)((ulong)uVar20 >> 0x20)) >>
                                                0xe),
                                       CONCAT22((short)((uint)(iVar3 * (short)((ulong)uVar9 >> 0x10)
                                                              ) >> 0xe) +
                                                (short)((uint)(iVar7 * (short)((ulong)uVar20 >> 0x10
                                                                              )) >> 0xe),
                                                (short)((uint)(iVar3 * (short)uVar9) >> 0xe) +
                                                (short)((uint)(iVar7 * (short)uVar20) >> 0xe))));
        *puVar18 = CONCAT26((short)(((uint)(iVar3 * (short)((ulong)uVar8 >> 0x30)) >> 0xe & 0xffff)
                                   + ((uint)(iVar7 * (short)((ulong)uVar19 >> 0x30)) >> 0xe)),
                            CONCAT24((short)(((uint)(iVar3 * (short)((ulong)uVar8 >> 0x20)) >> 0xe &
                                             0xffff) +
                                            ((uint)(iVar7 * (short)((ulong)uVar19 >> 0x20)) >> 0xe))
                                     ,CONCAT22((short)(((uint)(iVar3 * (short)((ulong)uVar8 >> 0x10)
                                                              ) >> 0xe & 0xffff) +
                                                      ((uint)(iVar7 * (short)((ulong)uVar19 >> 0x10)
                                                             ) >> 0xe)),
                                               (short)((uint)(iVar3 * (short)uVar8) >> 0xe) +
                                               (short)((uint)(iVar7 * (short)uVar19) >> 0xe))));
        puVar17 = puVar17 + 2;
        puVar18 = puVar18 + 2;
      } while (uVar15 != 0);
      if (uVar13 == uVar11) {
        return;
      }
    }
    lVar12 = uVar11 - uVar13;
    psVar14 = (short *)((long)param_3 + uVar13 * 2);
    psVar16 = (short *)((long)param_2 + uVar13 * 2);
    do {
      lVar12 = lVar12 + -1;
      *psVar16 = (short)((uint)(iVar3 * *psVar14) >> 0xe) + (short)((uint)(iVar7 * *psVar16) >> 0xe)
      ;
      psVar14 = psVar14 + 1;
      psVar16 = psVar16 + 1;
    } while (lVar12 != 0);
  }
  return;
}


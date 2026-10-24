/* FUN_00104efc @ 00104efc size 480 */

void FUN_00104efc(long param_1,undefined8 *param_2,undefined8 *param_3,long param_4,int param_5,
                 uint param_6)

{
  int iVar1;
  short sVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  ulong uVar8;
  long lVar9;
  ulong uVar10;
  short *psVar11;
  ulong uVar12;
  short *psVar13;
  undefined8 *puVar14;
  undefined8 *puVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  
  iVar6 = *(int *)(param_4 + (long)param_5 * 4);
  piVar7 = (int *)(param_4 + (long)(*(int *)(param_1 + 8) + param_5) * 4);
  iVar5 = iVar6;
  if (iVar6 <= *piVar7) {
    iVar5 = *piVar7;
  }
  if (iVar5 < 1) {
    iVar5 = 0;
  }
  else {
    iVar5 = ec_ilog();
    iVar6 = *(int *)(param_4 + (long)param_5 * 4);
    iVar5 = iVar5 * 0x10000 + -0x10000 >> 0x10;
    piVar7 = (int *)(param_4 + (long)(*(int *)(param_1 + 8) + param_5) * 4);
  }
  uVar4 = iVar5 - 0xd;
  iVar1 = iVar6 >> (uVar4 & 0x1f);
  if ((int)uVar4 < 1) {
    iVar1 = iVar6 << (ulong)(0xdU - iVar5 & 0x1f);
  }
  iVar6 = *piVar7 >> (uVar4 & 0x1f);
  if ((int)uVar4 < 1) {
    iVar6 = *piVar7 << (ulong)(0xdU - iVar5 & 0x1f);
  }
  iVar5 = ssc_sqrt((int)(short)iVar6 * (int)(short)iVar6 + (int)(short)iVar1 * (int)(short)iVar1 + 1
                  );
  if (0 < (int)param_6) {
    iVar5 = iVar5 * 0x10000 + 0x10000 >> 0x10;
    sVar2 = 0;
    if (iVar5 != 0) {
      sVar2 = (short)(((iVar6 << 0x10) >> 2) / iVar5);
    }
    sVar3 = 0;
    if (iVar5 != 0) {
      sVar3 = (short)(((iVar1 << 0x10) >> 2) / iVar5);
    }
    iVar5 = (int)sVar3;
    iVar6 = (int)sVar2;
    uVar8 = (ulong)param_6;
    if ((param_6 < 8) ||
       ((param_2 < (undefined8 *)((long)param_3 + uVar8 * 2) &&
        (param_3 < (undefined8 *)((long)param_2 + uVar8 * 2))))) {
      uVar10 = 0;
    }
    else {
      uVar10 = uVar8 & 0xfffffff8;
      uVar12 = uVar10;
      puVar14 = param_3;
      puVar15 = param_2;
      do {
        uVar17 = puVar15[1];
        uVar16 = *puVar15;
        uVar19 = puVar14[1];
        uVar18 = *puVar14;
        uVar12 = uVar12 - 8;
        puVar15[1] = CONCAT26((short)((uint)(iVar6 * (short)((ulong)uVar19 >> 0x30)) >> 0xe) +
                              (short)((uint)(iVar5 * (short)((ulong)uVar17 >> 0x30)) >> 0xe),
                              CONCAT24((short)((uint)(iVar6 * (short)((ulong)uVar19 >> 0x20)) >> 0xe
                                              ) +
                                       (short)((uint)(iVar5 * (short)((ulong)uVar17 >> 0x20)) >> 0xe
                                              ),CONCAT22((short)((uint)(iVar6 * (short)((ulong)
                                                  uVar19 >> 0x10)) >> 0xe) +
                                                  (short)((uint)(iVar5 * (short)((ulong)uVar17 >>
                                                                                0x10)) >> 0xe),
                                                  (short)((uint)(iVar6 * (short)uVar19) >> 0xe) +
                                                  (short)((uint)(iVar5 * (short)uVar17) >> 0xe))));
        *puVar15 = CONCAT26((short)((uint)(iVar6 * (short)((ulong)uVar18 >> 0x30)) >> 0xe) +
                            (short)((uint)(iVar5 * (short)((ulong)uVar16 >> 0x30)) >> 0xe),
                            CONCAT24((short)((uint)(iVar6 * (short)((ulong)uVar18 >> 0x20)) >> 0xe)
                                     + (short)((uint)(iVar5 * (short)((ulong)uVar16 >> 0x20)) >> 0xe
                                              ),
                                     CONCAT22((short)((uint)(iVar6 * (short)((ulong)uVar18 >> 0x10))
                                                     >> 0xe) +
                                              (short)((uint)(iVar5 * (short)((ulong)uVar16 >> 0x10))
                                                     >> 0xe),
                                              (short)((uint)(iVar6 * (short)uVar18) >> 0xe) +
                                              (short)((uint)(iVar5 * (short)uVar16) >> 0xe))));
        puVar14 = puVar14 + 2;
        puVar15 = puVar15 + 2;
      } while (uVar12 != 0);
      if (uVar10 == uVar8) {
        return;
      }
    }
    lVar9 = uVar8 - uVar10;
    psVar11 = (short *)((long)param_3 + uVar10 * 2);
    psVar13 = (short *)((long)param_2 + uVar10 * 2);
    do {
      lVar9 = lVar9 + -1;
      *psVar13 = (short)((uint)(iVar6 * *psVar11) >> 0xe) + (short)((uint)(iVar5 * *psVar13) >> 0xe)
      ;
      psVar11 = psVar11 + 1;
      psVar13 = psVar13 + 1;
    } while (lVar9 != 0);
  }
  return;
}


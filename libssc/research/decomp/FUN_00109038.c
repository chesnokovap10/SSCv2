/* FUN_00109038 @ 00109038 size 1064 */

void FUN_00109038(long param_1,short *param_2,int param_3,undefined4 param_4,int param_5,
                 undefined4 param_6,undefined8 param_7,ulong param_8)

{
  bool bVar1;
  undefined2 *puVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  short sVar6;
  short sVar7;
  int iVar8;
  long lVar9;
  short *psVar10;
  long lVar11;
  short *psVar12;
  long lVar13;
  ulong uVar14;
  short *psVar15;
  undefined2 *puVar16;
  uint uVar17;
  uint uVar18;
  ulong uVar19;
  uint uVar20;
  uint uVar21;
  ulong uVar22;
  long lVar23;
  ulong uVar24;
  ulong uVar25;
  short *psVar26;
  uint uVar27;
  undefined2 auStack_190 [144];
  long local_70;
  
  lVar9 = tpidr_el0;
  iVar8 = 0;
  if (param_5 != 0) {
    iVar8 = param_3 / param_5;
  }
  local_70 = *(long *)(lVar9 + 0x28);
  param_8 = param_8 & 0xffffffff;
  uVar17 = *(uint *)(param_1 + 0x1c);
  uVar4 = uVar17 & ((int)uVar17 >> 0x1f ^ 0xffffffffU);
  if (0 < (int)uVar17) {
    uVar20 = 0;
    do {
      if (uVar20 != 0x1f) {
        iVar3 = param_3 >> (uVar20 & 0x1f);
        uVar21 = 1 << (ulong)(uVar20 & 0x1f);
        uVar18 = iVar3 >> 1;
        uVar25 = 0;
        psVar10 = param_2 + uVar21;
        if ((int)uVar18 < 2) {
          uVar18 = 1;
        }
        psVar26 = param_2;
        do {
          psVar12 = psVar26;
          psVar15 = psVar10;
          uVar19 = (ulong)uVar18;
          if (1 < iVar3) {
            do {
              uVar19 = uVar19 - 1;
              sVar6 = (short)((uint)(*psVar15 * 0xb504) >> 0x10);
              sVar7 = (short)((uint)(*psVar12 * 0xb504) >> 0x10);
              *psVar12 = sVar6 + sVar7;
              *psVar15 = sVar7 - sVar6;
              psVar12 = (short *)((long)psVar12 +
                                 (-(ulong)((uVar21 & 0x7fffffff) >> 0x1e) & 0xfffffffe00000000 |
                                 (ulong)(uVar21 << 1) << 1));
              psVar15 = psVar15 + (ulong)uVar21 * 2;
            } while (uVar19 != 0);
          }
          uVar25 = uVar25 + 1;
          psVar10 = psVar10 + 1;
          psVar26 = psVar26 + 1;
        } while (uVar25 != uVar21);
      }
      uVar20 = uVar20 + 1;
      param_8 = (ulong)((uint)(byte)(&DAT_001027c0)[param_8 & 0xf] |
                       (uint)(byte)(&DAT_001027c0)[(int)param_8 >> 4] << 2);
    } while (uVar20 != uVar4);
  }
  uVar21 = iVar8 << (ulong)(uVar4 & 0x1f);
  uVar20 = param_5 >> (uVar4 & 0x1f);
  uVar18 = uVar21;
  uVar27 = uVar20;
  if (((uVar21 & 1) == 0) && ((int)uVar17 < 0)) {
    do {
      uVar27 = uVar20 << 1;
      uVar18 = (int)uVar21 >> 1;
      if (0 < (int)uVar20) {
        uVar25 = 0;
        uVar5 = uVar18;
        if ((int)uVar18 < 2) {
          uVar5 = 1;
        }
        psVar10 = param_2 + uVar20;
        psVar26 = param_2;
        do {
          psVar12 = psVar26;
          psVar15 = psVar10;
          uVar19 = (ulong)uVar5;
          if (1 < (int)uVar21) {
            do {
              uVar19 = uVar19 - 1;
              sVar6 = (short)((uint)(*psVar15 * 0xb504) >> 0x10);
              sVar7 = (short)((uint)(*psVar12 * 0xb504) >> 0x10);
              *psVar12 = sVar6 + sVar7;
              *psVar15 = sVar7 - sVar6;
              psVar12 = (short *)((long)psVar12 +
                                 (-(ulong)((uVar20 & 0x7fffffff) >> 0x1e) & 0xfffffffe00000000 |
                                 (ulong)uVar27 << 1));
              psVar15 = psVar15 + (ulong)uVar20 * 2;
            } while (uVar19 != 0);
          }
          uVar25 = uVar25 + 1;
          psVar10 = psVar10 + 1;
          psVar26 = psVar26 + 1;
        } while (uVar25 != uVar20);
      }
      param_8 = (ulong)((uint)param_8 << (ulong)(uVar20 & 0x1f) | (uint)param_8);
    } while (((uVar21 >> 1 & 1) == 0) &&
            (bVar1 = (int)uVar17 < -1, uVar17 = uVar17 + 1, uVar21 = uVar18, uVar20 = uVar27, bVar1)
            );
  }
  if (1 < (int)uVar27) {
    uVar18 = (int)uVar18 >> (uVar4 & 0x1f);
    uVar25 = (ulong)uVar18;
    uVar4 = uVar27 << (ulong)(uVar4 & 0x1f);
    uVar19 = (ulong)uVar4;
    if (param_5 == 1) {
      if (0 < (int)uVar4) {
        lVar23 = (long)(int)uVar4;
        uVar22 = 0;
        uVar24 = uVar25 & 0xfffffffe;
        psVar10 = param_2;
        do {
          if (0 < (int)uVar18) {
            iVar8 = *(int *)(&DAT_00102878 + uVar22 * 4 + (long)(int)uVar4 * 4);
            if (uVar18 == 1) {
              uVar14 = 0;
            }
            else {
              psVar12 = (short *)(((ulong)auStack_190 | 2) + (long)iVar8 * (long)(int)uVar18 * 2);
              uVar14 = uVar24;
              psVar26 = psVar10;
              do {
                sVar7 = psVar26[lVar23];
                uVar14 = uVar14 - 2;
                sVar6 = *psVar26;
                psVar26 = psVar26 + lVar23 * 2;
                psVar12[-1] = sVar6;
                *psVar12 = sVar7;
                psVar12 = psVar12 + 2;
              } while (uVar14 != 0);
              uVar14 = uVar24;
              if (uVar24 == uVar25) goto LAB_001092a4;
            }
            lVar11 = lVar23 * 2 * uVar14;
            lVar13 = uVar25 - uVar14;
            puVar16 = auStack_190 + uVar14 + (long)iVar8 * (long)(int)uVar18;
            do {
              puVar2 = (undefined2 *)((long)psVar10 + lVar11);
              lVar13 = lVar13 + -1;
              lVar11 = lVar11 + lVar23 * 2;
              *puVar16 = *puVar2;
              puVar16 = puVar16 + 1;
            } while (lVar13 != 0);
          }
LAB_001092a4:
          uVar22 = uVar22 + 1;
          psVar10 = psVar10 + 1;
        } while (uVar22 != uVar19);
      }
    }
    else if (0 < (int)uVar4) {
      lVar23 = 0;
      uVar22 = 0;
      uVar24 = uVar25 & 0xfffffffe;
      psVar26 = (short *)((ulong)auStack_190 | 2);
      psVar10 = param_2;
      do {
        if (0 < (int)uVar18) {
          psVar12 = psVar26;
          uVar14 = uVar24;
          psVar15 = psVar10;
          if (uVar18 == 1) {
            uVar14 = 0;
          }
          else {
            do {
              sVar6 = psVar15[uVar19];
              uVar14 = uVar14 - 2;
              psVar12[-1] = *psVar15;
              *psVar12 = sVar6;
              psVar12 = psVar12 + 2;
              psVar15 = psVar15 + uVar19 * 2;
            } while (uVar14 != 0);
            uVar14 = uVar24;
            if (uVar24 == uVar25) goto LAB_00109368;
          }
          lVar11 = uVar19 * 2 * uVar14;
          lVar13 = uVar25 - uVar14;
          puVar16 = auStack_190 + uVar14 + lVar23;
          do {
            puVar2 = (undefined2 *)((long)psVar10 + lVar11);
            lVar13 = lVar13 + -1;
            lVar11 = lVar11 + uVar19 * 2;
            *puVar16 = *puVar2;
            puVar16 = puVar16 + 1;
          } while (lVar13 != 0);
        }
LAB_00109368:
        uVar22 = uVar22 + 1;
        psVar10 = psVar10 + 1;
        psVar26 = (short *)((long)psVar26 +
                           (-(ulong)(uVar18 >> 0x1f) & 0xfffffffe00000000 | (ulong)uVar18 << 1));
        lVar23 = lVar23 + (int)uVar18;
      } while (uVar22 != uVar19);
    }
    if (0 < (int)(uVar4 * uVar18)) {
      memcpy(param_2,auStack_190,(ulong)(uVar4 * uVar18) << 1);
    }
  }
  FUN_00109460(param_1,param_2,param_3,param_4,uVar27,3,param_6,param_8);
  if (*(long *)(lVar9 + 0x28) != local_70) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}


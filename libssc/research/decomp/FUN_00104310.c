/* FUN_00104310 @ 00104310 size 1072 */

void FUN_00104310(long param_1,short *param_2,int param_3,undefined4 param_4,int param_5,
                 undefined4 param_6,ulong param_7)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  short sVar4;
  short sVar5;
  undefined2 uVar6;
  uint uVar7;
  int iVar8;
  long lVar9;
  short *psVar10;
  short *psVar11;
  ulong uVar12;
  undefined2 *puVar13;
  short *psVar14;
  short *psVar15;
  ulong uVar16;
  undefined2 *puVar17;
  long lVar18;
  ulong uVar19;
  uint uVar20;
  long lVar21;
  uint uVar22;
  ulong uVar23;
  ulong uVar24;
  short asStack_190 [144];
  long local_70;
  
  lVar9 = tpidr_el0;
  local_70 = *(long *)(lVar9 + 0x28);
  param_7 = param_7 & 0xffffffff;
  uVar3 = *(uint *)(param_1 + 0x1c);
  iVar8 = 0;
  if (param_5 != 0) {
    iVar8 = param_3 / param_5;
  }
  uVar1 = uVar3 & ((int)uVar3 >> 0x1f ^ 0xffffffffU);
  if (0 < (int)uVar3) {
    uVar20 = 0;
    do {
      if ((uVar20 != 0x1f) && (uVar22 = param_3 >> (uVar20 & 0x1f), 1 < (int)uVar22)) {
        uVar7 = 1 << (ulong)(uVar20 & 0x1f);
        uVar24 = 0;
        psVar10 = param_2 + (int)uVar7;
        psVar11 = param_2;
        do {
          uVar16 = 0;
          psVar14 = psVar10;
          psVar15 = psVar11;
          do {
            uVar16 = uVar16 + 1;
            sVar4 = (short)((uint)(*psVar14 * 0xb504) >> 0x10);
            sVar5 = (short)((uint)(*psVar15 * 0xb504) >> 0x10);
            *psVar15 = sVar4 + sVar5;
            *psVar14 = sVar5 - sVar4;
            psVar15 = (short *)((long)psVar15 +
                               (-(ulong)((uVar7 & 0x7fffffff) >> 0x1e) & 0xfffffffe00000000 |
                               (ulong)(uVar7 << 1) << 1));
            psVar14 = (short *)((long)psVar14 +
                               (-(ulong)(uVar7 >> 0x1f) & 0xfffffffc00000000 | (ulong)uVar7 << 2));
          } while (uVar16 < uVar22 >> 1);
          uVar24 = uVar24 + 1;
          psVar11 = psVar11 + 1;
          psVar10 = psVar10 + 1;
        } while (uVar24 != uVar7);
      }
      uVar20 = uVar20 + 1;
      param_7 = (ulong)((uint)(byte)(&DAT_00113530)[param_7 & 0xf] |
                       (uint)(byte)(&DAT_00113530)[(int)param_7 >> 4] << 2);
    } while (uVar20 < uVar1);
  }
  uVar22 = iVar8 << (ulong)(uVar1 & 0x1f);
  uVar20 = param_5 >> (uVar1 & 0x1f);
  uVar24 = (ulong)uVar20;
  if ((uVar22 & 1) == 0) {
    for (; (int)uVar3 < 0; uVar3 = uVar3 + 1) {
      uVar20 = (uint)uVar24;
      uVar7 = (int)uVar22 >> 1;
      if (((int)uVar22 < 2) || ((int)uVar20 < 1)) {
        uVar16 = (ulong)(uVar20 << 1);
      }
      else {
        uVar16 = (ulong)(uVar20 << 1);
        uVar23 = 0;
        psVar10 = param_2 + (int)uVar20;
        psVar11 = param_2;
        do {
          uVar12 = 0;
          psVar14 = psVar10;
          psVar15 = psVar11;
          do {
            uVar12 = uVar12 + 1;
            sVar4 = (short)((uint)(*psVar14 * 0xb504) >> 0x10);
            sVar5 = (short)((uint)(*psVar15 * 0xb504) >> 0x10);
            *psVar15 = sVar4 + sVar5;
            *psVar14 = sVar5 - sVar4;
            psVar15 = (short *)((long)psVar15 +
                               (-(ulong)((uVar20 & 0x7fffffff) >> 0x1e) & 0xfffffffe00000000 |
                               uVar16 << 1));
            psVar14 = (short *)((long)psVar14 +
                               (-(uVar24 >> 0x1f) & 0xfffffffc00000000 | uVar24 << 2));
          } while (uVar12 < uVar22 >> 1);
          uVar23 = uVar23 + 1;
          psVar11 = psVar11 + 1;
          psVar10 = psVar10 + 1;
        } while (uVar23 != uVar24);
      }
      uVar2 = uVar22 >> 1;
      param_7 = (ulong)((uint)param_7 << (ulong)(uVar20 & 0x1f) | (uint)param_7);
      uVar20 = uVar20 << 1;
      uVar22 = uVar7;
      if ((uVar2 & 1) != 0) break;
      uVar20 = (uint)uVar16;
      uVar24 = uVar16;
    }
  }
  if (1 < (int)uVar20) {
    uVar22 = (int)uVar22 >> (uVar1 & 0x1f);
    uVar24 = (ulong)uVar22;
    uVar3 = uVar20 << (ulong)(uVar1 & 0x1f);
    if (param_5 == 1) {
      if ((0 < (int)uVar22) && (0 < (int)uVar3)) {
        lVar21 = (long)(int)uVar3;
        uVar16 = (ulong)uVar22;
        uVar24 = 0;
        uVar23 = uVar16 & 0xfffffffe;
        psVar10 = param_2;
        do {
          iVar8 = *(int *)(&DAT_00113548 + uVar24 * 4 + (long)(int)uVar3 * 4);
          if (uVar22 < 2) {
            uVar12 = 0;
LAB_001045c8:
            psVar11 = param_2 + uVar24 + lVar21 * uVar12;
            lVar18 = uVar16 - uVar12;
            psVar15 = asStack_190 + uVar12 + (long)iVar8 * (long)(int)uVar22;
            do {
              sVar4 = *psVar11;
              lVar18 = lVar18 + -1;
              psVar11 = psVar11 + lVar21;
              *psVar15 = sVar4;
              psVar15 = psVar15 + 1;
            } while (lVar18 != 0);
          }
          else {
            psVar15 = (short *)(((ulong)asStack_190 | 2) + (long)iVar8 * (long)(int)uVar22 * 2);
            uVar12 = uVar23;
            psVar11 = psVar10;
            do {
              sVar4 = *psVar11;
              sVar5 = psVar11[lVar21];
              psVar11 = psVar11 + lVar21 * 2;
              uVar12 = uVar12 - 2;
              psVar15[-1] = sVar4;
              *psVar15 = sVar5;
              psVar15 = psVar15 + 2;
            } while (uVar12 != 0);
            uVar12 = uVar23;
            if (uVar23 != uVar16) goto LAB_001045c8;
          }
          uVar24 = uVar24 + 1;
          psVar10 = psVar10 + 1;
        } while (uVar24 != uVar3);
      }
    }
    else if ((0 < (int)uVar22) && (0 < (int)uVar3)) {
      lVar21 = 0;
      uVar16 = 0;
      uVar12 = -(ulong)(uVar3 >> 0x1f) & 0xfffffffe00000000 | (ulong)uVar3 << 1;
      uVar23 = uVar24 & 0xfffffffe;
      puVar13 = (undefined2 *)((ulong)asStack_190 | 2);
      psVar10 = param_2;
      do {
        puVar17 = puVar13;
        uVar19 = uVar23;
        psVar11 = psVar10;
        if (uVar22 < 2) {
          uVar19 = 0;
LAB_0010468c:
          psVar11 = param_2 + uVar16 + (long)(int)uVar3 * uVar19;
          lVar18 = uVar24 - uVar19;
          psVar15 = asStack_190 + uVar19 + lVar21;
          do {
            sVar4 = *psVar11;
            lVar18 = lVar18 + -1;
            psVar11 = (short *)((long)psVar11 + uVar12);
            *psVar15 = sVar4;
            psVar15 = psVar15 + 1;
          } while (lVar18 != 0);
        }
        else {
          do {
            uVar6 = *(undefined2 *)((long)psVar11 + uVar12);
            uVar19 = uVar19 - 2;
            puVar17[-1] = *psVar11;
            *puVar17 = uVar6;
            puVar17 = puVar17 + 2;
            psVar11 = (short *)((long)psVar11 +
                               (-(ulong)(uVar3 >> 0x1f) & 0xfffffffc00000000 | (ulong)uVar3 << 2));
          } while (uVar19 != 0);
          uVar19 = uVar23;
          if (uVar23 != uVar24) goto LAB_0010468c;
        }
        uVar16 = uVar16 + 1;
        psVar10 = psVar10 + 1;
        puVar13 = (undefined2 *)
                  ((long)puVar13 + (-(ulong)(uVar22 >> 0x1f) & 0xfffffffe00000000 | uVar24 << 1));
        lVar21 = lVar21 + (int)uVar22;
      } while (uVar16 != uVar3);
    }
    if (0 < (int)(uVar3 * uVar22)) {
      memcpy(param_2,asStack_190,(ulong)(uVar3 * uVar22) << 1);
    }
  }
  FUN_00104740(param_1,param_2,param_3,param_4,uVar20,3,param_6,param_7);
  if (*(long *)(lVar9 + 0x28) == local_70) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


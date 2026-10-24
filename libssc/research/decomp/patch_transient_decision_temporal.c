/* patch_transient_decision_temporal @ 0010be68 size 1468 */

void patch_transient_decision_temporal(long param_1,long param_2,long param_3)

{
  uint *puVar1;
  float *pfVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  long lVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  float *pfVar13;
  int iVar14;
  long lVar15;
  long lVar16;
  long lVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  long lVar21;
  int *piVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  float fVar35;
  float fVar36;
  float fVar37;
  float fVar38;
  float fVar39;
  undefined8 local_b0;
  undefined8 uStack_a8;
  undefined8 local_a0;
  undefined8 local_98;
  uint local_90 [2];
  long local_88;
  
  lVar6 = tpidr_el0;
  local_88 = *(long *)(lVar6 + 0x28);
  iVar5 = *(int *)(param_1 + 0x1c);
  iVar7 = iVar5 * 2;
  iVar8 = iVar5 * 4;
  uVar3 = *(int *)(param_1 + 4) + iVar5 * 8;
  iVar9 = iVar5 * 3;
  lVar15 = 0;
  iVar14 = 0;
  iVar10 = iVar5 * 5;
  iVar18 = iVar5 * 7;
  iVar19 = iVar5 * 6;
  lVar21 = param_3;
  iVar20 = iVar5;
  do {
    if (iVar5 < 1) {
      fVar33 = 0.0;
      fVar32 = 0.0;
      fVar31 = 0.0;
      fVar28 = 0.0;
      fVar26 = 0.0;
      fVar25 = 0.0;
      fVar24 = 0.0;
      fVar23 = 0.0;
      uStack_a8 = 0;
      local_b0 = 0;
      local_98 = 0;
      local_a0 = 0;
    }
    else {
      lVar17 = param_2 + lVar15 * 8;
      pfVar13 = (float *)(lVar17 + 0xc4);
      pfVar2 = (float *)(lVar17 + 200);
      fVar29 = *pfVar13;
      fVar27 = *pfVar2;
      lVar17 = 0;
      fVar23 = 0.0;
      do {
        lVar16 = lVar17 * 4;
        fVar24 = fVar29 * 0.7548;
        lVar17 = lVar17 + 1;
        fVar29 = (float)*(int *)(lVar21 + lVar16);
        fVar27 = (fVar29 * 0.7548 - fVar24) + fVar27 * 0.5095;
        fVar23 = fVar23 + fVar27 * fVar27;
      } while (iVar5 != (int)lVar17);
      lVar17 = 0;
      fVar24 = 0.0;
      *pfVar13 = fVar29;
      *pfVar2 = fVar27;
      do {
        lVar16 = lVar17 * 4;
        fVar25 = fVar29 * 0.7548;
        lVar17 = lVar17 + 1;
        fVar29 = (float)*(int *)(param_3 + (long)iVar20 * 4 + lVar16);
        fVar27 = (fVar29 * 0.7548 - fVar25) + fVar27 * 0.5095;
        fVar24 = fVar24 + fVar27 * fVar27;
      } while (iVar5 != (int)lVar17);
      lVar17 = 0;
      fVar25 = 0.0;
      *pfVar13 = fVar29;
      *pfVar2 = fVar27;
      local_b0 = CONCAT44(fVar24,fVar23);
      do {
        lVar16 = lVar17 * 4;
        fVar26 = fVar29 * 0.7548;
        lVar17 = lVar17 + 1;
        fVar29 = (float)*(int *)(param_3 + (long)iVar7 * 4 + lVar16);
        fVar27 = (fVar29 * 0.7548 - fVar26) + fVar27 * 0.5095;
        fVar25 = fVar25 + fVar27 * fVar27;
      } while (iVar5 != (int)lVar17);
      lVar17 = 0;
      fVar26 = 0.0;
      *pfVar13 = fVar29;
      *pfVar2 = fVar27;
      do {
        lVar16 = lVar17 * 4;
        fVar28 = fVar29 * 0.7548;
        lVar17 = lVar17 + 1;
        fVar29 = (float)*(int *)(param_3 + (long)iVar9 * 4 + lVar16);
        fVar27 = (fVar29 * 0.7548 - fVar28) + fVar27 * 0.5095;
        fVar26 = fVar26 + fVar27 * fVar27;
      } while (iVar5 != (int)lVar17);
      fVar28 = 0.0;
      *pfVar13 = fVar29;
      *pfVar2 = fVar27;
      uStack_a8 = CONCAT44(fVar26,fVar25);
      piVar22 = (int *)(param_3 + (long)iVar8 * 4);
      iVar11 = iVar5;
      do {
        fVar31 = fVar29 * 0.7548;
        iVar11 = iVar11 + -1;
        fVar29 = (float)*piVar22;
        fVar27 = (fVar29 * 0.7548 - fVar31) + fVar27 * 0.5095;
        fVar28 = fVar28 + fVar27 * fVar27;
        piVar22 = piVar22 + 1;
      } while (iVar11 != 0);
      fVar31 = 0.0;
      *pfVar13 = fVar29;
      *pfVar2 = fVar27;
      piVar22 = (int *)(param_3 + (long)iVar10 * 4);
      iVar11 = iVar5;
      do {
        fVar32 = fVar29 * 0.7548;
        iVar11 = iVar11 + -1;
        fVar29 = (float)*piVar22;
        fVar27 = (fVar29 * 0.7548 - fVar32) + fVar27 * 0.5095;
        fVar31 = fVar31 + fVar27 * fVar27;
        piVar22 = piVar22 + 1;
      } while (iVar11 != 0);
      fVar32 = 0.0;
      *pfVar13 = fVar29;
      *pfVar2 = fVar27;
      local_a0 = CONCAT44(fVar31,fVar28);
      piVar22 = (int *)(param_3 + (long)iVar19 * 4);
      iVar11 = iVar5;
      do {
        fVar33 = fVar29 * 0.7548;
        iVar11 = iVar11 + -1;
        fVar29 = (float)*piVar22;
        fVar27 = (fVar29 * 0.7548 - fVar33) + fVar27 * 0.5095;
        fVar32 = fVar32 + fVar27 * fVar27;
        piVar22 = piVar22 + 1;
      } while (iVar11 != 0);
      fVar33 = 0.0;
      *pfVar13 = fVar29;
      *pfVar2 = fVar27;
      piVar22 = (int *)(param_3 + (long)iVar18 * 4);
      iVar11 = iVar5;
      do {
        fVar34 = fVar29 * 0.7548;
        iVar11 = iVar11 + -1;
        fVar29 = (float)*piVar22;
        fVar27 = (fVar29 * 0.7548 - fVar34) + fVar27 * 0.5095;
        fVar33 = fVar33 + fVar27 * fVar27;
        piVar22 = piVar22 + 1;
      } while (iVar11 != 0);
      *pfVar13 = fVar29;
      *pfVar2 = fVar27;
      local_98 = CONCAT44(fVar33,fVar32);
    }
    pfVar13 = (float *)(param_2 + lVar15 * 4 + 0xbc);
    fVar27 = fVar23;
    if (fVar23 <= 0.0) {
      fVar27 = 0.0;
    }
    fVar29 = *(float *)(param_2 + lVar15 * 0x20 + 0x98) * 3.0 + *pfVar13 * 7.0;
    fVar34 = fVar23 * 3.0 + (fVar29 / 10.0) * 7.0;
    if (fVar27 <= fVar24) {
      fVar27 = fVar24;
    }
    fVar30 = fVar24 * 3.0 + (fVar34 / 10.0) * 7.0;
    fVar35 = fVar25 * 3.0 + (fVar30 / 10.0) * 7.0;
    if (fVar27 <= fVar25) {
      fVar27 = fVar25;
    }
    if (fVar27 <= fVar26) {
      fVar27 = fVar26;
    }
    fVar37 = fVar26 * 3.0 + (fVar35 / 10.0) * 7.0;
    if (fVar27 <= fVar28) {
      fVar27 = fVar28;
    }
    fVar38 = fVar28 * 3.0 + (fVar37 / 10.0) * 7.0;
    fVar39 = fVar31 * 3.0 + (fVar38 / 10.0) * 7.0;
    if (fVar27 <= fVar31) {
      fVar27 = fVar31;
    }
    if (fVar27 <= fVar32) {
      fVar27 = fVar32;
    }
    fVar36 = fVar32 * 3.0 + (fVar39 / 10.0) * 7.0;
    lVar17 = param_2 + lVar15 * 0x20;
    if (((((fVar29 < fVar23) || (fVar34 < fVar24)) || (fVar30 < fVar25)) ||
        ((fVar35 < fVar26 || (fVar37 < fVar28)))) ||
       ((fVar38 < fVar31 || ((fVar39 < fVar32 || (fVar36 < fVar33)))))) {
      uVar12 = 2;
      if (fVar25 <= fVar30) {
        uVar12 = (uint)(fVar34 < fVar24);
      }
      uVar4 = 3;
      if (fVar26 <= fVar35) {
        uVar4 = uVar12;
      }
      uVar12 = 4;
      if (fVar28 <= fVar37) {
        uVar12 = uVar4;
      }
      uVar4 = 5;
      if (fVar31 <= fVar38) {
        uVar4 = uVar12;
      }
      uVar12 = 6;
      if (fVar32 <= fVar39) {
        uVar12 = uVar4;
      }
      uVar4 = 7;
      if (fVar33 <= fVar36) {
        uVar4 = uVar12;
      }
      local_90[lVar15] = uVar4;
    }
    if (fVar27 <= fVar33) {
      fVar27 = fVar33;
    }
    *pfVar13 = fVar36 / 10.0;
    if ((fVar27 < 1e+06) ||
       (fVar33 <= fVar36 &&
        (fVar32 <= fVar39 &&
        (fVar31 <= fVar38 &&
        (fVar28 <= fVar37 &&
        (fVar26 <= fVar35 && (fVar25 <= fVar30 && (fVar24 <= fVar34 && fVar23 <= fVar29)))))))) {
      uVar12 = 0;
      if (*(int *)(param_2 + 0x70) != 0) {
        uVar12 = (uint)(*(int *)(param_2 + lVar15 * 4 + 0x74) == 7);
      }
    }
    else {
      uVar12 = 1;
    }
    lVar16 = lVar15 * 4;
    iVar14 = uVar12 + iVar14;
    puVar1 = local_90 + lVar15;
    lVar15 = lVar15 + 1;
    lVar21 = lVar21 + (-(ulong)(uVar3 >> 0x1f) & 0xfffffffc00000000 | (ulong)uVar3 << 2);
    *(uint *)(param_2 + lVar16 + 0x74) = *puVar1;
    iVar20 = iVar20 + uVar3;
    iVar7 = iVar7 + uVar3;
    iVar9 = iVar9 + uVar3;
    iVar8 = iVar8 + uVar3;
    iVar10 = iVar10 + uVar3;
    iVar19 = iVar19 + uVar3;
    iVar18 = iVar18 + uVar3;
    *(undefined8 *)(lVar17 + 0x84) = uStack_a8;
    *(undefined8 *)(lVar17 + 0x7c) = local_b0;
    *(undefined8 *)(lVar17 + 0x94) = local_98;
    *(undefined8 *)(lVar17 + 0x8c) = local_a0;
  } while (lVar15 != 2);
  *(uint *)(param_2 + 0x70) = (uint)(iVar14 != 0);
  if (*(long *)(lVar6 + 0x28) == local_88) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


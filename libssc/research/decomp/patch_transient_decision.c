/* patch_transient_decision @ 0010bbcc size 668 */

void patch_transient_decision(long param_1,long param_2,int param_3,uint param_4)

{
  undefined8 *puVar1;
  short sVar2;
  uint uVar3;
  long lVar4;
  short sVar5;
  ulong uVar6;
  long lVar7;
  undefined8 *puVar8;
  undefined8 *puVar9;
  short *psVar10;
  undefined2 *puVar11;
  ulong uVar12;
  short *psVar13;
  long lVar14;
  ulong uVar15;
  uint uVar16;
  ulong uVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  int iVar24;
  int iVar25;
  undefined8 uVar26;
  undefined1 auVar27 [16];
  undefined1 auVar28 [16];
  undefined8 uVar29;
  undefined1 auVar30 [16];
  undefined1 auVar31 [16];
  undefined8 uVar32;
  undefined8 uVar33;
  short asStack_4c [13];
  short local_32;
  undefined2 auStack_30 [3];
  undefined8 auStack_2a [2];
  long local_18;
  
  lVar4 = tpidr_el0;
  local_18 = *(long *)(lVar4 + 0x28);
  sVar2 = *(short *)(param_2 + (long)(param_3 + 0xd) * 2);
  local_32 = *(short *)(param_2 + 0x1a);
  if (*(short *)(param_2 + 0x1a) <= sVar2) {
    local_32 = sVar2;
  }
  iVar18 = (int)local_32;
  if (0xe < (int)param_4) {
    psVar10 = (short *)(param_2 + 0x1c);
    lVar14 = (ulong)param_4 - 0xe;
    puVar11 = auStack_30;
    do {
      sVar2 = (short)iVar18;
      sVar5 = *psVar10;
      if (*psVar10 <= psVar10[param_3]) {
        sVar5 = psVar10[param_3];
      }
      iVar18 = iVar18 + -0x400;
      if (sVar2 + -0x400 <= (int)sVar5) {
        iVar18 = (int)sVar5;
      }
      lVar14 = lVar14 + -1;
      *puVar11 = (short)iVar18;
      psVar10 = psVar10 + 1;
      puVar11 = puVar11 + 1;
    } while (lVar14 != 0);
  }
  if (0xc < (int)(param_4 - 2)) {
    lVar14 = (long)(int)(param_4 - 2);
    do {
      psVar10 = asStack_4c + lVar14;
      lVar7 = lVar14 + 1;
      sVar2 = *psVar10;
      lVar14 = lVar14 + -1;
      iVar18 = (int)sVar2;
      if ((int)sVar2 <= asStack_4c[lVar7] + -0x400) {
        iVar18 = asStack_4c[lVar7] + -0x400;
      }
      *psVar10 = (short)iVar18;
    } while (0xc < lVar14);
    uVar3 = param_4 - 1;
    if (0xd < (int)uVar3) {
      uVar6 = (ulong)uVar3 - 0xd;
      if (uVar6 < 8) {
        iVar18 = 0;
        uVar6 = 0xd;
LAB_0010bd64:
        do {
          lVar14 = uVar6 * 2;
          psVar10 = asStack_4c + uVar6;
          uVar6 = uVar6 + 1;
          uVar16 = (uint)*(short *)(param_1 + lVar14);
          uVar16 = (uVar16 & (uVar16 >> 0xf ^ 0xffffffff) & 0xffff) -
                   ((int)*psVar10 & ((uint)(int)*psVar10 >> 0xf ^ 0xffffffff) & 0xffff);
          iVar18 = (uVar16 & ((int)uVar16 >> 0x1f ^ 0xffffffffU)) + iVar18;
        } while (uVar3 != uVar6);
      }
      else {
        uVar16 = param_4 + 2 & 7;
        lVar14 = uVar6 - uVar16;
        puVar8 = (undefined8 *)(param_1 + 0x22);
        iVar18 = 0;
        iVar19 = 0;
        iVar20 = 0;
        iVar21 = 0;
        puVar9 = auStack_2a;
        uVar6 = lVar14 + 0xd;
        iVar22 = 0;
        iVar23 = 0;
        iVar24 = 0;
        iVar25 = 0;
        do {
          puVar1 = puVar8 + -1;
          uVar29 = *puVar8;
          puVar8 = puVar8 + 2;
          lVar14 = lVar14 + -8;
          uVar26 = NEON_smax(*puVar1,0,2);
          uVar29 = NEON_smax(uVar29,0,2);
          uVar32 = NEON_smax(puVar9[-1],0,2);
          uVar33 = NEON_smax(*puVar9,0,2);
          auVar28._0_4_ = (uint)(ushort)uVar26 - (uint)(ushort)uVar32;
          auVar28._4_4_ =
               (uint)(ushort)((ulong)uVar26 >> 0x10) - (uint)(ushort)((ulong)uVar32 >> 0x10);
          auVar28._8_4_ =
               (uint)(ushort)((ulong)uVar26 >> 0x20) - (uint)(ushort)((ulong)uVar32 >> 0x20);
          auVar28._12_4_ =
               (uint)(ushort)((ulong)uVar26 >> 0x30) - (uint)(ushort)((ulong)uVar32 >> 0x30);
          auVar31._0_4_ = (uint)(ushort)uVar29 - (uint)(ushort)uVar33;
          auVar31._4_4_ =
               (uint)(ushort)((ulong)uVar29 >> 0x10) - (uint)(ushort)((ulong)uVar33 >> 0x10);
          auVar31._8_4_ =
               (uint)(ushort)((ulong)uVar29 >> 0x20) - (uint)(ushort)((ulong)uVar33 >> 0x20);
          auVar31._12_4_ =
               (uint)(ushort)((ulong)uVar29 >> 0x30) - (uint)(ushort)((ulong)uVar33 >> 0x30);
          auVar28 = NEON_smax(auVar28,ZEXT816(0),4);
          auVar31 = NEON_smax(auVar31,ZEXT816(0),4);
          iVar18 = auVar28._0_4_ + iVar18;
          iVar19 = auVar28._4_4_ + iVar19;
          iVar20 = auVar28._8_4_ + iVar20;
          iVar21 = auVar28._12_4_ + iVar21;
          iVar22 = auVar31._0_4_ + iVar22;
          iVar23 = auVar31._4_4_ + iVar23;
          iVar24 = auVar31._8_4_ + iVar24;
          iVar25 = auVar31._12_4_ + iVar25;
          puVar9 = puVar9 + 2;
        } while (lVar14 != 0);
        iVar18 = iVar22 + iVar18 + iVar23 + iVar19 + iVar24 + iVar20 + iVar25 + iVar21;
        if (uVar16 != 0) goto LAB_0010bd64;
      }
      uVar12 = uVar6 - 0xd;
      if (uVar12 < 8) {
        lVar14 = 0xd;
      }
      else {
        uVar15 = uVar12 & 0xfffffffffffffff8;
        iVar20 = 0;
        iVar21 = 0;
        puVar8 = (undefined8 *)(param_1 + 0x22);
        lVar14 = uVar15 + 0xd;
        iVar19 = 0;
        puVar9 = auStack_2a;
        iVar22 = 0;
        iVar23 = 0;
        iVar24 = 0;
        iVar25 = 0;
        uVar17 = uVar15;
        do {
          puVar1 = puVar8 + -1;
          uVar29 = *puVar8;
          puVar8 = puVar8 + 2;
          uVar17 = uVar17 - 8;
          uVar26 = NEON_smax(*puVar1,0,2);
          uVar29 = NEON_smax(uVar29,0,2);
          uVar32 = NEON_smax(puVar9[-1],0,2);
          uVar33 = NEON_smax(*puVar9,0,2);
          auVar27._0_4_ = (uint)(ushort)uVar26 - (uint)(ushort)uVar32;
          auVar27._4_4_ =
               (uint)(ushort)((ulong)uVar26 >> 0x10) - (uint)(ushort)((ulong)uVar32 >> 0x10);
          auVar27._8_4_ =
               (uint)(ushort)((ulong)uVar26 >> 0x20) - (uint)(ushort)((ulong)uVar32 >> 0x20);
          auVar27._12_4_ =
               (uint)(ushort)((ulong)uVar26 >> 0x30) - (uint)(ushort)((ulong)uVar32 >> 0x30);
          auVar30._0_4_ = (uint)(ushort)uVar29 - (uint)(ushort)uVar33;
          auVar30._4_4_ =
               (uint)(ushort)((ulong)uVar29 >> 0x10) - (uint)(ushort)((ulong)uVar33 >> 0x10);
          auVar30._8_4_ =
               (uint)(ushort)((ulong)uVar29 >> 0x20) - (uint)(ushort)((ulong)uVar33 >> 0x20);
          auVar30._12_4_ =
               (uint)(ushort)((ulong)uVar29 >> 0x30) - (uint)(ushort)((ulong)uVar33 >> 0x30);
          auVar28 = NEON_smax(auVar27,ZEXT816(0),4);
          auVar31 = NEON_smax(auVar30,ZEXT816(0),4);
          iVar18 = auVar28._0_4_ + iVar18;
          iVar19 = auVar28._4_4_ + iVar19;
          iVar20 = auVar28._8_4_ + iVar20;
          iVar21 = auVar28._12_4_ + iVar21;
          iVar22 = auVar31._0_4_ + iVar22;
          iVar23 = auVar31._4_4_ + iVar23;
          iVar24 = auVar31._8_4_ + iVar24;
          iVar25 = auVar31._12_4_ + iVar25;
          puVar9 = puVar9 + 2;
        } while (uVar17 != 0);
        iVar18 = iVar22 + iVar18 + iVar23 + iVar19 + iVar24 + iVar20 + iVar25 + iVar21;
        if (uVar12 == uVar15) goto LAB_0010bcb8;
      }
      lVar7 = uVar6 - lVar14;
      psVar10 = asStack_4c + lVar14;
      psVar13 = (short *)(param_1 + lVar14 * 2);
      do {
        lVar7 = lVar7 + -1;
        uVar3 = ((int)*psVar13 & ((uint)(int)*psVar13 >> 0xf ^ 0xffffffff) & 0xffff) -
                ((int)*psVar10 & ((uint)(int)*psVar10 >> 0xf ^ 0xffffffff) & 0xffff);
        iVar18 = (uVar3 & ((int)uVar3 >> 0x1f ^ 0xffffffffU)) + iVar18;
        psVar10 = psVar10 + 1;
        psVar13 = psVar13 + 1;
      } while (lVar7 != 0);
      goto LAB_0010bcb8;
    }
  }
  iVar18 = 0;
LAB_0010bcb8:
  iVar20 = param_4 * 2 + -0x1c;
  iVar19 = 0;
  if (iVar20 != 0) {
    iVar19 = iVar18 / iVar20;
  }
  if (*(long *)(lVar4 + 0x28) == local_18) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(0x400 < iVar19);
}


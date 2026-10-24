/* CalculateBandEnergy @ 00107630 size 316 */

void CalculateBandEnergy(long param_1,long param_2,long param_3,uint param_4,int param_5,int param_6
                        )

{
  undefined1 (*pauVar1) [16];
  ulong uVar2;
  uint uVar3;
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 (*pauVar6) [16];
  undefined1 *puVar7;
  undefined1 *puVar8;
  undefined1 *puVar9;
  undefined1 *puVar10;
  long lVar11;
  long lVar12;
  undefined1 (*pauVar13) [16];
  long lVar14;
  undefined1 (*pauVar15) [16];
  ulong uVar16;
  uint uVar17;
  int iVar18;
  int iVar21;
  int iVar22;
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  int iVar23;
  undefined4 uVar24;
  undefined4 uVar25;
  undefined4 uVar26;
  undefined4 uVar27;
  
  if (0 < (int)param_4) {
    uVar16 = 0;
    do {
      uVar2 = uVar16 + 1;
      auVar20 = ZEXT816(0);
      lVar12 = (long)*(short *)(param_3 + uVar16 * 2);
      lVar11 = lVar12 << 3;
      pauVar13 = (undefined1 (*) [16])(param_2 + (long)param_5 * 4 + 0x10 + lVar12 * 0x20);
      lVar14 = (long)*(short *)(param_3 + uVar2 * 2) * 8;
      pauVar15 = pauVar13;
      lVar12 = lVar11;
      do {
        pauVar1 = pauVar15 + -1;
        pauVar6 = pauVar15 + -1;
        puVar7 = *pauVar15;
        puVar8 = *pauVar15;
        puVar9 = *pauVar15;
        puVar10 = *pauVar15;
        lVar12 = lVar12 + 8;
        pauVar15 = pauVar15 + 2;
        uVar24 = MP_INT_ABS((int)*(undefined8 *)*pauVar1);
        uVar25 = MP_INT_ABS((int)((ulong)*(undefined8 *)*pauVar1 >> 0x20));
        uVar26 = MP_INT_ABS((int)*(undefined8 *)(*pauVar6 + 8));
        uVar27 = MP_INT_ABS((int)((ulong)*(undefined8 *)(*pauVar6 + 8) >> 0x20));
        auVar19._4_4_ = uVar25;
        auVar19._0_4_ = uVar24;
        auVar19._8_4_ = uVar26;
        auVar19._12_4_ = uVar27;
        auVar19 = NEON_smax(auVar20,auVar19,4);
        uVar24 = MP_INT_ABS(*(undefined4 *)puVar7);
        uVar25 = MP_INT_ABS(*(undefined4 *)(puVar8 + 4));
        uVar26 = MP_INT_ABS(*(undefined4 *)(puVar9 + 8));
        uVar27 = MP_INT_ABS(*(undefined4 *)(puVar10 + 0xc));
        auVar20._4_4_ = uVar25;
        auVar20._0_4_ = uVar24;
        auVar20._8_4_ = uVar26;
        auVar20._12_4_ = uVar27;
        auVar20 = NEON_smax(auVar19,auVar20,4);
      } while (lVar12 < lVar14);
      uVar17 = NEON_smaxv(auVar20,4);
      if ((int)uVar17 < 1) {
        iVar18 = 1;
      }
      else {
        uVar3 = (int)LZCOUNT(uVar17) - 0x15;
        iVar18 = 0;
        iVar21 = 0;
        iVar22 = 0;
        iVar23 = 0;
        do {
          pauVar15 = pauVar13 + -1;
          auVar20 = *pauVar13;
          lVar11 = lVar11 + 8;
          pauVar13 = pauVar13 + 2;
          auVar4._4_4_ = uVar3;
          auVar4._0_4_ = uVar3;
          auVar4._8_4_ = uVar3;
          auVar4._12_4_ = uVar3;
          auVar19 = NEON_sshl(*pauVar15,auVar4,4);
          auVar5._4_4_ = uVar3;
          auVar5._0_4_ = uVar3;
          auVar5._8_4_ = uVar3;
          auVar5._12_4_ = uVar3;
          auVar20 = NEON_sshl(auVar20,auVar5,4);
          iVar18 = iVar18 + (int)auVar19._0_2_ * (int)auVar19._0_2_ +
                   (int)auVar20._0_2_ * (int)auVar20._0_2_;
          iVar21 = iVar21 + (int)auVar19._4_2_ * (int)auVar19._4_2_ +
                   (int)auVar20._4_2_ * (int)auVar20._4_2_;
          iVar22 = iVar22 + (int)auVar19._8_2_ * (int)auVar19._8_2_ +
                   (int)auVar20._8_2_ * (int)auVar20._8_2_;
          iVar23 = iVar23 + (int)auVar19._12_2_ * (int)auVar19._12_2_ +
                   (int)auVar20._12_2_ * (int)auVar20._12_2_;
        } while (lVar11 < lVar14);
        iVar18 = iVar18 + iVar21 + iVar22 + iVar23;
        if (uVar17 < 0x400) {
          iVar18 = ssc_sqrt(iVar18);
          iVar18 = iVar18 >> (uVar3 & 0x1f);
        }
        else {
          iVar18 = ssc_sqrt(iVar18);
          iVar18 = iVar18 << (ulong)(0x15U - (int)LZCOUNT(uVar17) & 0x1f);
        }
        iVar18 = iVar18 + 1;
      }
      *(int *)(param_1 + (long)param_6 * 4 + uVar16 * 4) = iVar18;
      uVar16 = uVar2;
    } while (uVar2 != param_4);
  }
  return;
}


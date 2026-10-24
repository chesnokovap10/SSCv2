/* ssc_comb_filter_const_asm @ 00116b00 size 144 */

void ssc_comb_filter_const_asm
               (int *param_1,int *param_2,long param_3,long param_4,int param_5,int param_6,
               int param_7)

{
  bool bVar1;
  undefined1 (*pauVar2) [16];
  long lVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined1 (*pauVar6) [16];
  int iVar7;
  int iVar8;
  int iVar9;
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  int iVar13;
  int iVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  
  pauVar6 = (undefined1 (*) [16])(param_2 + -(param_3 + 2));
  uVar15 = *(undefined8 *)*pauVar6;
  uVar16 = *(undefined8 *)(*pauVar6 + 8);
  do {
    pauVar2 = pauVar6 + 1;
    iVar7 = *(int *)(pauVar6[1] + 4);
    uVar4 = *(undefined8 *)*pauVar2;
    iVar8 = *(int *)(pauVar6[1] + 8);
    iVar9 = *(int *)(pauVar6[1] + 0xc);
    uVar5 = *(undefined8 *)(pauVar6[1] + 8);
    iVar13 = (int)uVar16;
    iVar14 = (int)((ulong)uVar16 >> 0x20);
    auVar10._8_4_ = iVar13;
    auVar10._0_8_ = uVar15;
    auVar10._12_4_ = iVar14;
    auVar10 = NEON_ext(auVar10,*pauVar2,0xc,1);
    auVar11._8_4_ = iVar13;
    auVar11._0_8_ = uVar15;
    auVar11._12_4_ = iVar14;
    auVar11 = NEON_ext(auVar11,*pauVar2,8,1);
    auVar12._8_4_ = iVar13;
    auVar12._0_8_ = uVar15;
    auVar12._12_4_ = iVar14;
    auVar12 = NEON_ext(auVar12,*pauVar2,4,1);
    iVar17 = param_2[1];
    iVar18 = param_2[2];
    iVar19 = param_2[3];
    lVar3 = param_4 + -4;
    *param_1 = (int)((long)param_5 * (long)auVar11._0_4_ +
                     (long)param_6 * (long)(auVar10._0_4_ + auVar12._0_4_) +
                     (long)param_7 * (long)(*(int *)*pauVar2 + (int)uVar15) + 0x4000U >> 0xf) +
               *param_2;
    param_1[1] = (int)((long)param_5 * (long)auVar11._4_4_ +
                       (long)param_6 * (long)(auVar10._4_4_ + auVar12._4_4_) +
                       (long)param_7 * (long)(iVar7 + (int)((ulong)uVar15 >> 0x20)) + 0x4000U >> 0xf
                      ) + iVar17;
    param_1[2] = (int)((long)param_5 * (long)auVar11._8_4_ +
                       (long)param_6 * (long)(auVar10._8_4_ + auVar12._8_4_) +
                       (long)param_7 * (long)(iVar8 + iVar13) + 0x4000U >> 0xf) + iVar18;
    param_1[3] = (int)((long)param_5 * (long)auVar11._12_4_ +
                       (long)param_6 * (long)(auVar10._12_4_ + auVar12._12_4_) +
                       (long)param_7 * (long)(iVar9 + iVar14) + 0x4000U >> 0xf) + iVar19;
    param_2 = param_2 + 4;
    param_1 = param_1 + 4;
    bVar1 = 3 < param_4;
    param_4 = lVar3;
    pauVar6 = pauVar2;
    uVar15 = uVar4;
    uVar16 = uVar5;
  } while (lVar3 != 0 && bVar1);
  return;
}


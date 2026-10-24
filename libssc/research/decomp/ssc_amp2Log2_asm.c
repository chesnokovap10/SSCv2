/* ssc_amp2Log2_asm @ 00117200 size 296 */

void ssc_amp2Log2_asm(long param_1,undefined8 *param_2,short *param_3,char *param_4)

{
  bool bVar1;
  int *piVar2;
  char cVar3;
  char cVar4;
  long lVar5;
  long lVar6;
  int iVar7;
  int iVar10;
  int iVar11;
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  int iVar12;
  
  lVar6 = param_1;
  do {
    piVar2 = (int *)((long)param_2 + param_1 * 4);
    auVar8._0_4_ = (int)*param_2 << 2;
    auVar8._4_4_ = (int)((ulong)*param_2 >> 0x20) << 2;
    auVar8._8_4_ = *piVar2 << 2;
    auVar8._12_4_ = piVar2[1] << 2;
    auVar9._4_4_ = 2 - (0x12 - LZCOUNT(auVar8._4_4_));
    auVar9._0_4_ = 2 - (0x12 - LZCOUNT(auVar8._0_4_));
    auVar9._8_4_ = 2 - (0x12 - LZCOUNT(auVar8._8_4_));
    auVar9._12_4_ = 2 - (0x12 - LZCOUNT(auVar8._12_4_));
    auVar9 = NEON_sshl(auVar8,auVar9,4);
    iVar7 = auVar9._0_4_ + -0xc000;
    iVar10 = auVar9._4_4_ + -0xc000;
    iVar11 = auVar9._8_4_ + -0xc000;
    iVar12 = auVar9._12_4_ + -0xc000;
    cVar3 = *param_4;
    cVar4 = param_4[1];
    *param_3 = (short)(((iVar7 * (((iVar7 * (((iVar7 * (((iVar7 * -0x579 >> 0xf) + 0x9f1) * 0x10000
                                                       >> 0x10) >> 0xf) + -0x1461) * 0x10000 >> 0x10
                                            ) >> 0xf) + 0x3d82) * 0x10000 >> 0x10) >> 0xf) + -0x1a89
                       ) * 0x10000 >> 0x14) + (short)(0x12 - LZCOUNT(auVar8._0_4_)) * 0x400 +
               cVar3 * -0x40;
    param_3[1] = (short)(((iVar10 * (((iVar10 * (((iVar10 * (((iVar10 * -0x579 >> 0xf) + 0x9f1) *
                                                             0x10000 >> 0x10) >> 0xf) + -0x1461) *
                                                 0x10000 >> 0x10) >> 0xf) + 0x3d82) * 0x10000 >>
                                    0x10) >> 0xf) + -0x1a89) * 0x10000 >> 0x14) +
                 (short)(0x12 - LZCOUNT(auVar8._4_4_)) * 0x400 + cVar4 * -0x40;
    param_3[param_1] =
         (short)(((iVar11 * (((iVar11 * (((iVar11 * (((iVar11 * -0x579 >> 0xf) + 0x9f1) * 0x10000 >>
                                                    0x10) >> 0xf) + -0x1461) * 0x10000 >> 0x10) >>
                              0xf) + 0x3d82) * 0x10000 >> 0x10) >> 0xf) + -0x1a89) * 0x10000 >> 0x14
                ) + (short)(0x12 - LZCOUNT(auVar8._8_4_)) * 0x400 + cVar3 * -0x40;
    (param_3 + param_1)[1] =
         (short)(((iVar12 * (((iVar12 * (((iVar12 * (((iVar12 * -0x579 >> 0xf) + 0x9f1) * 0x10000 >>
                                                    0x10) >> 0xf) + -0x1461) * 0x10000 >> 0x10) >>
                              0xf) + 0x3d82) * 0x10000 >> 0x10) >> 0xf) + -0x1a89) * 0x10000 >> 0x14
                ) + (short)(0x12 - LZCOUNT(auVar8._12_4_)) * 0x400 + cVar4 * -0x40;
    param_4 = param_4 + 2;
    param_2 = param_2 + 1;
    param_3 = param_3 + 2;
    lVar5 = lVar6 + -2;
    bVar1 = 1 < lVar6;
    lVar6 = lVar5;
  } while (lVar5 != 0 && bVar1);
  return;
}


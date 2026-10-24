/* ssc_pitch_search @ 00112234 size 1160 */

void ssc_pitch_search(undefined2 *param_1,undefined2 *param_2,int param_3,int param_4,int *param_5)

{
  undefined1 (*pauVar1) [16];
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  long lVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined1 auVar12 [16];
  undefined2 *puVar13;
  undefined4 uVar16;
  undefined1 (*pauVar17) [16];
  short *psVar18;
  ulong uVar19;
  int iVar20;
  uint uVar21;
  ulong uVar22;
  ulong uVar23;
  undefined2 *puVar24;
  long lVar25;
  long lVar26;
  ulong uVar27;
  undefined8 *puVar28;
  long lVar29;
  undefined2 *puVar30;
  undefined2 *puVar31;
  undefined1 (*pauVar32) [16];
  undefined1 (*pauVar33) [16];
  short *psVar34;
  undefined2 uVar35;
  undefined2 uVar37;
  int iVar36;
  undefined2 uVar38;
  undefined2 uVar40;
  int iVar39;
  undefined2 uVar41;
  undefined2 uVar43;
  int iVar42;
  undefined2 uVar44;
  undefined2 uVar46;
  int iVar45;
  int iVar47;
  int iVar48;
  int iVar49;
  int iVar50;
  undefined2 uVar51;
  undefined2 uVar53;
  int iVar52;
  undefined2 uVar54;
  undefined2 uVar56;
  int iVar55;
  int iVar57;
  int iVar58;
  int iVar59;
  int iVar60;
  int iVar61;
  int iVar62;
  undefined1 auVar63 [16];
  undefined1 auVar64 [16];
  undefined1 auVar65 [16];
  undefined1 auVar66 [16];
  undefined8 local_70;
  long local_68;
  undefined2 *puVar14;
  undefined2 *puVar15;
  
  lVar7 = tpidr_el0;
  local_68 = *(long *)(lVar7 + 0x28);
  uVar3 = param_3 >> 2;
  local_70 = 0;
  if (param_3 < 4) {
    uVar21 = 0;
  }
  else {
    uVar21 = uVar3;
    if ((int)uVar3 < 2) {
      uVar21 = 1;
    }
    uVar22 = (ulong)uVar21;
    if (uVar21 < 9) {
      lVar25 = 0;
    }
    else {
      lVar25 = 0;
      if ((param_1 + uVar22 * 2 + -1 < (undefined2 *)0x1247a1 ||
           &DAT_00124950 + uVar22 * 2 <= param_1) &&
         (param_2 + uVar22 * 2 + -1 < (undefined2 *)0x1247a1 ||
          &DAT_00124950 + uVar22 * 2 <= param_2)) {
        uVar23 = 8;
        if ((uVar21 & 7) != 0) {
          uVar23 = uVar22 & 7;
        }
        puVar28 = (undefined8 *)&DAT_001247a0;
        lVar25 = uVar22 - uVar23;
        lVar26 = lVar25;
        puVar24 = param_1;
        puVar30 = param_2;
        do {
          uVar35 = *puVar24;
          uVar37 = puVar24[2];
          uVar38 = puVar24[4];
          uVar40 = puVar24[6];
          puVar31 = puVar24 + 8;
          puVar13 = puVar24 + 10;
          puVar14 = puVar24 + 0xc;
          puVar15 = puVar24 + 0xe;
          puVar24 = puVar24 + 0x10;
          puVar28[1] = CONCAT26(*puVar15,CONCAT24(*puVar14,CONCAT22(*puVar13,*puVar31)));
          *puVar28 = CONCAT26(uVar40,CONCAT24(uVar38,CONCAT22(uVar37,uVar35)));
          lVar26 = lVar26 + -8;
          uVar35 = *puVar30;
          uVar37 = puVar30[2];
          uVar38 = puVar30[4];
          uVar40 = puVar30[6];
          puVar31 = puVar30 + 8;
          puVar13 = puVar30 + 10;
          puVar14 = puVar30 + 0xc;
          puVar15 = puVar30 + 0xe;
          puVar30 = puVar30 + 0x10;
          puVar28[0x37] = CONCAT26(*puVar15,CONCAT24(*puVar14,CONCAT22(*puVar13,*puVar31)));
          puVar28[0x36] = CONCAT26(uVar40,CONCAT24(uVar38,CONCAT22(uVar37,uVar35)));
          puVar28 = puVar28 + 2;
        } while (lVar26 != 0);
      }
    }
    lVar26 = uVar22 - lVar25;
    puVar24 = (undefined2 *)((long)&DAT_001247a0 + lVar25 * 2);
    puVar30 = param_1 + lVar25 * 2;
    puVar31 = param_2 + lVar25 * 2;
    do {
      lVar26 = lVar26 + -1;
      *puVar24 = *puVar30;
      puVar24[0xd8] = *puVar31;
      puVar24 = puVar24 + 1;
      puVar30 = puVar30 + 2;
      puVar31 = puVar31 + 2;
    } while (lVar26 != 0);
  }
  uVar4 = param_4 + param_3 >> 2;
  uVar22 = (ulong)uVar4;
  if ((int)uVar21 < (int)uVar4) {
    uVar23 = (ulong)uVar21;
    uVar27 = uVar22 - uVar23;
    if ((0x10 < uVar27) &&
       ((lVar25 = uVar23 * 2, param_2 + uVar22 * 2 + -1 <= &DAT_00124950 + uVar23 * 2 ||
        (&DAT_00124950 + uVar22 * 2 <= param_2 + lVar25)))) {
      uVar19 = 0x10;
      if ((uVar27 & 0xf) != 0) {
        uVar19 = uVar27 & 0xf;
      }
      lVar26 = uVar23 * 2;
      lVar29 = uVar19 + uVar23;
      uVar23 = (uVar27 - uVar19) + uVar23;
      lVar29 = lVar29 - uVar22;
      puVar28 = (undefined8 *)(&DAT_00124960 + lVar26);
      puVar24 = param_2 + lVar25 + 0x10;
      do {
        uVar35 = *puVar24;
        uVar37 = puVar24[2];
        uVar38 = puVar24[4];
        uVar40 = puVar24[6];
        uVar41 = puVar24[8];
        uVar43 = puVar24[10];
        uVar44 = puVar24[0xc];
        uVar46 = puVar24[0xe];
        lVar29 = lVar29 + 0x10;
        uVar51 = puVar24[-0x10];
        uVar53 = puVar24[-0xe];
        uVar54 = puVar24[-0xc];
        uVar56 = puVar24[-10];
        puVar28[-1] = CONCAT26(puVar24[-2],CONCAT24(puVar24[-4],CONCAT22(puVar24[-6],puVar24[-8])));
        puVar28[-2] = CONCAT26(uVar56,CONCAT24(uVar54,CONCAT22(uVar53,uVar51)));
        puVar28[1] = CONCAT26(uVar46,CONCAT24(uVar44,CONCAT22(uVar43,uVar41)));
        *puVar28 = CONCAT26(uVar40,CONCAT24(uVar38,CONCAT22(uVar37,uVar35)));
        puVar28 = puVar28 + 4;
        puVar24 = puVar24 + 0x20;
      } while (lVar29 != 0);
    }
    lVar25 = uVar22 - uVar23;
    puVar24 = param_2 + uVar23 * 2;
    puVar30 = (undefined2 *)(&DAT_00124950 + uVar23 * 2);
    do {
      lVar25 = lVar25 + -1;
      *puVar30 = *puVar24;
      puVar24 = puVar24 + 2;
      puVar30 = puVar30 + 1;
    } while (lVar25 != 0);
  }
  iVar20 = param_4 >> 2;
  uVar16 = ssc_pitch_xcorr_c2(&DAT_001247a0,&DAT_00124950,&DAT_00124d18,uVar3,iVar20);
  FUN_001126bc(&DAT_00124950,uVar3,iVar20,&local_70,0,uVar16);
  tone_detect(&DAT_00124d18,&local_70,uVar16,iVar20);
  uVar3 = param_4 >> 1;
  uVar21 = param_3 >> 1;
  if (param_4 < 2) {
    iVar20 = 1;
  }
  else {
    uVar22 = 0;
    uVar4 = uVar21;
    if ((int)uVar21 < 2) {
      uVar4 = 1;
    }
    uVar23 = (ulong)uVar4;
    uVar6 = uVar3;
    if ((int)uVar3 < 2) {
      uVar6 = 1;
    }
    uVar27 = uVar23 & 0x7ffffff0;
    pauVar32 = (undefined1 (*) [16])(param_2 + 8);
    iVar20 = 1;
    do {
      uVar2 = (int)local_70 * -2 + (int)uVar22;
      uVar5 = -uVar2;
      if (-1 < (int)uVar2) {
        uVar5 = uVar2;
      }
      (&DAT_00124d18)[uVar22] = 0;
      if (uVar5 < 3) {
LAB_00112514:
        if (param_3 < 2) {
          iVar36 = 0;
          iVar39 = iVar36;
        }
        else {
          if (uVar4 < 0x10) {
            iVar36 = 0;
            uVar19 = 0;
LAB_001125a4:
            lVar25 = uVar23 - uVar19;
            psVar18 = param_1 + uVar19;
            psVar34 = param_2 + uVar19 + uVar22;
            do {
              lVar25 = lVar25 + -1;
              iVar36 = iVar36 + (int)*psVar34 * (int)*psVar18;
              psVar18 = psVar18 + 1;
              psVar34 = psVar34 + 1;
            } while (lVar25 != 0);
          }
          else {
            iVar36 = 0;
            iVar39 = 0;
            iVar42 = 0;
            iVar45 = 0;
            iVar47 = 0;
            iVar48 = 0;
            iVar49 = 0;
            iVar50 = 0;
            iVar52 = 0;
            iVar55 = 0;
            iVar57 = 0;
            iVar58 = 0;
            iVar59 = 0;
            iVar60 = 0;
            iVar61 = 0;
            iVar62 = 0;
            pauVar17 = (undefined1 (*) [16])(param_1 + 8);
            uVar19 = uVar27;
            pauVar33 = pauVar32;
            do {
              pauVar1 = pauVar17 + -1;
              uVar8 = *(undefined8 *)*pauVar1;
              uVar9 = *(undefined8 *)*pauVar17;
              auVar65 = *pauVar17;
              auVar64 = *pauVar17;
              pauVar17 = pauVar17 + 2;
              uVar19 = uVar19 - 0x10;
              auVar63 = NEON_ext(*pauVar1,*pauVar1,8,1);
              pauVar1 = pauVar33 + -1;
              uVar10 = *(undefined8 *)*pauVar1;
              uVar11 = *(undefined8 *)*pauVar33;
              auVar12 = *pauVar33;
              auVar66 = *pauVar33;
              auVar64 = NEON_ext(auVar64,auVar65,8,1);
              pauVar33 = pauVar33 + 2;
              auVar65 = NEON_ext(*pauVar1,*pauVar1,8,1);
              iVar36 = iVar36 + (int)(short)uVar10 * (int)(short)uVar8;
              iVar39 = iVar39 + (int)(short)((ulong)uVar10 >> 0x10) *
                                (int)(short)((ulong)uVar8 >> 0x10);
              iVar42 = iVar42 + (int)(short)((ulong)uVar10 >> 0x20) *
                                (int)(short)((ulong)uVar8 >> 0x20);
              iVar45 = iVar45 + (int)(short)((ulong)uVar10 >> 0x30) *
                                (int)(short)((ulong)uVar8 >> 0x30);
              auVar66 = NEON_ext(auVar66,auVar12,8,1);
              iVar52 = iVar52 + (int)(short)uVar11 * (int)(short)uVar9;
              iVar55 = iVar55 + (int)(short)((ulong)uVar11 >> 0x10) *
                                (int)(short)((ulong)uVar9 >> 0x10);
              iVar57 = iVar57 + (int)(short)((ulong)uVar11 >> 0x20) *
                                (int)(short)((ulong)uVar9 >> 0x20);
              iVar58 = iVar58 + (int)(short)((ulong)uVar11 >> 0x30) *
                                (int)(short)((ulong)uVar9 >> 0x30);
              iVar47 = iVar47 + (int)auVar65._0_2_ * (int)auVar63._0_2_;
              iVar48 = iVar48 + (int)auVar65._2_2_ * (int)auVar63._2_2_;
              iVar49 = iVar49 + (int)auVar65._4_2_ * (int)auVar63._4_2_;
              iVar50 = iVar50 + (int)auVar65._6_2_ * (int)auVar63._6_2_;
              iVar59 = iVar59 + (int)auVar66._0_2_ * (int)auVar64._0_2_;
              iVar60 = iVar60 + (int)auVar66._2_2_ * (int)auVar64._2_2_;
              iVar61 = iVar61 + (int)auVar66._4_2_ * (int)auVar64._4_2_;
              iVar62 = iVar62 + (int)auVar66._6_2_ * (int)auVar64._6_2_;
            } while (uVar19 != 0);
            iVar36 = iVar52 + iVar36 + iVar59 + iVar47 + iVar55 + iVar39 + iVar60 + iVar48 +
                     iVar57 + iVar42 + iVar61 + iVar49 + iVar58 + iVar45 + iVar62 + iVar50;
            uVar19 = uVar27;
            if (uVar27 != uVar23) goto LAB_001125a4;
          }
          iVar39 = iVar36;
          if (iVar36 < 0) {
            iVar39 = -1;
          }
        }
        if (iVar20 <= iVar36) {
          iVar20 = iVar36;
        }
        (&DAT_00124d18)[uVar22] = iVar39;
      }
      else {
        uVar2 = local_70._4_4_ * -2 + (int)uVar22;
        uVar5 = -uVar2;
        if (-1 < (int)uVar2) {
          uVar5 = uVar2;
        }
        if (uVar5 < 3) goto LAB_00112514;
      }
      uVar22 = uVar22 + 1;
      pauVar32 = (undefined1 (*) [16])(*pauVar32 + 2);
    } while (uVar22 != uVar6);
  }
  FUN_001126bc(param_2,uVar21,uVar3,&local_70,1,iVar20);
  uVar21 = 0;
  if ((0 < (int)local_70) && ((int)local_70 < (int)(uVar3 - 1))) {
    iVar36 = (&DAT_00124d18)[(int)local_70 - 1];
    iVar20 = (&DAT_00124d1c)[local_70 & 0xffffffff];
    uVar3 = (&DAT_00124d18)[local_70 & 0xffffffff] - iVar36;
    if ((int)(((int)uVar3 >> 0x10) * 0xb334 + ((uVar3 & 0xffff) * 0x599a >> 0xf)) < iVar20 - iVar36)
    {
      uVar21 = 0xffffffff;
    }
    else {
      uVar3 = (&DAT_00124d18)[local_70 & 0xffffffff] - iVar20;
      uVar21 = (uint)((int)(((int)uVar3 >> 0x10) * 0xb334 + ((uVar3 & 0xffff) * 0x599a >> 0xf)) <
                     iVar36 - iVar20);
    }
  }
  *param_5 = uVar21 + (int)local_70 * 2;
  if (*(long *)(lVar7 + 0x28) != local_68) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}


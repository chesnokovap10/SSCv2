/* pitch_search @ 00107890 size 1356 */

void pitch_search(undefined2 *param_1,undefined2 *param_2,int param_3,int param_4,int *param_5)

{
  ulong uVar1;
  int iVar2;
  uint uVar3;
  long lVar4;
  undefined2 *puVar5;
  undefined4 uVar8;
  undefined8 *puVar9;
  long lVar10;
  undefined8 *puVar11;
  ulong uVar12;
  long lVar13;
  ulong uVar14;
  undefined2 *puVar15;
  undefined8 *puVar16;
  undefined2 *puVar17;
  ulong uVar18;
  undefined2 *puVar19;
  int iVar20;
  ulong uVar21;
  undefined2 uVar22;
  undefined2 uVar24;
  int iVar23;
  undefined2 uVar25;
  undefined2 uVar27;
  int iVar26;
  undefined2 uVar28;
  undefined2 uVar30;
  int iVar29;
  undefined2 uVar31;
  undefined2 uVar33;
  int iVar32;
  int iVar34;
  int iVar35;
  int iVar36;
  int iVar37;
  undefined2 uVar38;
  undefined2 uVar40;
  undefined2 uVar41;
  undefined2 uVar42;
  undefined8 uVar39;
  undefined8 uVar43;
  undefined8 uVar44;
  undefined8 uVar45;
  undefined8 local_70;
  long local_68;
  undefined2 *puVar6;
  undefined2 *puVar7;
  
  lVar4 = tpidr_el0;
  local_68 = *(long *)(lVar4 + 0x28);
  iVar2 = param_3 >> 2;
  local_70 = 0;
  uVar3 = param_4 + param_3 >> 2;
  if (param_3 < 4) {
    uVar14 = 0;
    if (0 < (int)uVar3) goto LAB_001079a4;
  }
  else {
    uVar12 = (ulong)iVar2;
    uVar14 = uVar12;
    if ((long)uVar12 < 2) {
      uVar14 = 1;
    }
    if (uVar14 < 9) {
      uVar14 = 0;
    }
    else {
      uVar21 = 8;
      if ((uVar14 & 7) != 0) {
        uVar21 = uVar14 & 7;
      }
      uVar14 = uVar14 - uVar21;
      puVar16 = (undefined8 *)&DAT_0012b864;
      uVar21 = uVar14;
      puVar15 = param_1;
      puVar17 = param_2;
      do {
        uVar22 = *puVar15;
        uVar24 = puVar15[2];
        uVar25 = puVar15[4];
        uVar27 = puVar15[6];
        puVar19 = puVar15 + 8;
        puVar5 = puVar15 + 10;
        puVar6 = puVar15 + 0xc;
        puVar7 = puVar15 + 0xe;
        puVar15 = puVar15 + 0x10;
        uVar21 = uVar21 - 8;
        puVar16[1] = CONCAT26(*puVar7,CONCAT24(*puVar6,CONCAT22(*puVar5,*puVar19)));
        *puVar16 = CONCAT26(uVar27,CONCAT24(uVar25,CONCAT22(uVar24,uVar22)));
        uVar22 = *puVar17;
        uVar24 = puVar17[2];
        uVar25 = puVar17[4];
        uVar27 = puVar17[6];
        puVar19 = puVar17 + 8;
        puVar5 = puVar17 + 10;
        puVar6 = puVar17 + 0xc;
        puVar7 = puVar17 + 0xe;
        puVar17 = puVar17 + 0x10;
        puVar16[0x37] = CONCAT26(*puVar7,CONCAT24(*puVar6,CONCAT22(*puVar5,*puVar19)));
        puVar16[0x36] = CONCAT26(uVar27,CONCAT24(uVar25,CONCAT22(uVar24,uVar22)));
        puVar16 = puVar16 + 2;
      } while (uVar21 != 0);
    }
    puVar15 = (undefined2 *)((long)&DAT_0012b864 + uVar14 * 2);
    puVar17 = param_1 + uVar14 * 2;
    puVar19 = param_2 + uVar14 * 2;
    do {
      uVar14 = uVar14 + 1;
      *puVar15 = *puVar17;
      puVar15[0xd8] = *puVar19;
      puVar15 = puVar15 + 1;
      puVar17 = puVar17 + 2;
      puVar19 = puVar19 + 2;
    } while ((long)uVar14 < (long)uVar12);
    if ((int)uVar14 < (int)uVar3) {
LAB_001079a4:
      uVar21 = (ulong)uVar3;
      uVar14 = uVar14 & 0xffffffff;
      uVar18 = uVar21 - uVar14;
      uVar12 = uVar14;
      if (0x10 < uVar18) {
        uVar1 = 0x10;
        if ((uVar18 & 0xf) != 0) {
          uVar1 = uVar18 & 0xf;
        }
        puVar15 = param_2 + uVar14 * 2 + 0x10;
        puVar16 = (undefined8 *)(&DAT_0012ba24 + uVar14 * 2);
        uVar12 = (uVar18 - uVar1) + uVar14;
        lVar13 = (uVar21 - uVar1) - uVar14;
        do {
          uVar22 = *puVar15;
          uVar24 = puVar15[2];
          uVar25 = puVar15[4];
          uVar27 = puVar15[6];
          uVar28 = puVar15[8];
          uVar30 = puVar15[10];
          uVar31 = puVar15[0xc];
          uVar33 = puVar15[0xe];
          uVar38 = puVar15[-0x10];
          uVar40 = puVar15[-0xe];
          uVar41 = puVar15[-0xc];
          uVar42 = puVar15[-10];
          puVar17 = puVar15 + -8;
          puVar19 = puVar15 + -6;
          puVar5 = puVar15 + -4;
          puVar6 = puVar15 + -2;
          puVar15 = puVar15 + 0x20;
          lVar13 = lVar13 + -0x10;
          puVar16[-1] = CONCAT26(*puVar6,CONCAT24(*puVar5,CONCAT22(*puVar19,*puVar17)));
          puVar16[-2] = CONCAT26(uVar42,CONCAT24(uVar41,CONCAT22(uVar40,uVar38)));
          puVar16[1] = CONCAT26(uVar33,CONCAT24(uVar31,CONCAT22(uVar30,uVar28)));
          *puVar16 = CONCAT26(uVar27,CONCAT24(uVar25,CONCAT22(uVar24,uVar22)));
          puVar16 = puVar16 + 4;
        } while (lVar13 != 0);
      }
      lVar13 = uVar21 - uVar12;
      puVar15 = param_2 + uVar12 * 2;
      puVar17 = &DAT_0012ba14 + uVar12;
      do {
        lVar13 = lVar13 + -1;
        *puVar17 = *puVar15;
        puVar15 = puVar15 + 2;
        puVar17 = puVar17 + 1;
      } while (lVar13 != 0);
    }
  }
  iVar20 = param_4 >> 2;
  uVar8 = ssc_pitch_xcorr_c2(&DAT_0012b864,&DAT_0012ba14,&DAT_0012bddc,iVar2,iVar20);
  FUN_00107ddc(&DAT_0012ba14,iVar2,iVar20,&local_70,0,uVar8);
  tone_detect(&DAT_0012bddc,&local_70,uVar8,iVar20);
  iVar2 = param_4 >> 1;
  if (1 < param_4) {
    if (1 < param_3) {
      uVar12 = (ulong)(param_3 >> 1);
      uVar14 = uVar12;
      if ((long)uVar12 < 2) {
        uVar14 = 1;
      }
      lVar13 = 0;
      puVar16 = (undefined8 *)(param_2 + 4);
      uVar21 = uVar14 & 0x7ffffffffffffff8;
      iVar20 = 1;
      puVar15 = param_2;
      do {
        iVar26 = (int)lVar13 + (int)local_70 * -2;
        iVar23 = -iVar26;
        if (-1 < iVar26) {
          iVar23 = iVar26;
        }
        (&DAT_0012bddc)[lVar13] = 0;
        if (iVar23 < 3) {
LAB_00107b0c:
          if (uVar14 < 8) {
            iVar23 = 0;
            uVar18 = 0;
LAB_00107b6c:
            do {
              uVar1 = uVar18 + 1;
              iVar23 = iVar23 + (int)(short)puVar15[uVar18] * (int)(short)param_1[uVar18];
              uVar18 = uVar1;
            } while ((long)uVar1 < (long)uVar12);
          }
          else {
            iVar23 = 0;
            iVar26 = 0;
            iVar29 = 0;
            iVar32 = 0;
            iVar34 = 0;
            iVar35 = 0;
            iVar36 = 0;
            iVar37 = 0;
            uVar18 = uVar21;
            puVar9 = puVar16;
            puVar11 = (undefined8 *)(param_1 + 4);
            do {
              uVar39 = puVar11[-1];
              uVar43 = *puVar11;
              uVar44 = puVar9[-1];
              uVar45 = *puVar9;
              puVar11 = puVar11 + 2;
              uVar18 = uVar18 - 8;
              puVar9 = puVar9 + 2;
              iVar23 = iVar23 + (int)(short)uVar44 * (int)(short)uVar39;
              iVar26 = iVar26 + (int)(short)((ulong)uVar44 >> 0x10) *
                                (int)(short)((ulong)uVar39 >> 0x10);
              iVar29 = iVar29 + (int)(short)((ulong)uVar44 >> 0x20) *
                                (int)(short)((ulong)uVar39 >> 0x20);
              iVar32 = iVar32 + (int)(short)((ulong)uVar44 >> 0x30) *
                                (int)(short)((ulong)uVar39 >> 0x30);
              iVar34 = iVar34 + (int)(short)uVar45 * (int)(short)uVar43;
              iVar35 = iVar35 + (int)(short)((ulong)uVar45 >> 0x10) *
                                (int)(short)((ulong)uVar43 >> 0x10);
              iVar36 = iVar36 + (int)(short)((ulong)uVar45 >> 0x20) *
                                (int)(short)((ulong)uVar43 >> 0x20);
              iVar37 = iVar37 + (int)(short)((ulong)uVar45 >> 0x30) *
                                (int)(short)((ulong)uVar43 >> 0x30);
            } while (uVar18 != 0);
            iVar23 = iVar34 + iVar23 + iVar35 + iVar26 + iVar36 + iVar29 + iVar37 + iVar32;
            uVar18 = uVar21;
            if (uVar14 != uVar21) goto LAB_00107b6c;
          }
          iVar26 = iVar23;
          if (iVar23 < 0) {
            iVar26 = -1;
          }
          (&DAT_0012bddc)[lVar13] = iVar26;
          if (iVar20 <= iVar23) {
            iVar20 = iVar23;
          }
        }
        else {
          iVar26 = (int)lVar13 + local_70._4_4_ * -2;
          iVar23 = -iVar26;
          if (-1 < iVar26) {
            iVar23 = iVar26;
          }
          if (iVar23 < 3) goto LAB_00107b0c;
        }
        lVar13 = lVar13 + 1;
        puVar16 = (undefined8 *)((long)puVar16 + 2);
        puVar15 = puVar15 + 1;
      } while (lVar13 < iVar2);
      goto LAB_00107cf0;
    }
    uVar12 = (ulong)iVar2;
    uVar14 = uVar12;
    if ((long)uVar12 < 2) {
      uVar14 = 1;
    }
    if (uVar14 < 2) {
      uVar21 = 0;
    }
    else {
      uVar21 = uVar14 & 0x7ffffffffffffffe;
      iVar20 = (int)local_70 * 2 + -1;
      iVar23 = local_70._4_4_ * 2 + -1;
      lVar13 = 0x33c;
      lVar10 = 0xcec;
      do {
        iVar26 = (int)local_70 * -2 + (int)lVar13;
        *(undefined8 *)((long)&in_shared + lVar10) = 0;
        iVar29 = iVar26 + -0x33c;
        iVar26 = iVar26 + -0x33b;
        if (iVar29 < 0) {
          iVar29 = iVar20 + 1;
        }
        iVar32 = local_70._4_4_ * -2 + (int)lVar13;
        iVar34 = iVar20;
        if (-1 < iVar26) {
          iVar34 = iVar26;
        }
        iVar26 = iVar32 + -0x33c;
        iVar32 = iVar32 + -0x33b;
        if (iVar26 < 0) {
          iVar26 = iVar23 + 1;
        }
        iVar35 = iVar23;
        if (-1 < iVar32) {
          iVar35 = iVar32;
        }
        if ((iVar26 < 3) || (iVar29 < 3)) {
          *(undefined4 *)((long)&in_shared + lVar10) = 0;
        }
        if (iVar35 < 3 || iVar34 < 3) {
          (&in_shared)[lVar13] = 0;
        }
        lVar13 = lVar13 + 2;
        lVar10 = lVar10 + 8;
        iVar20 = iVar20 + -2;
        iVar23 = iVar23 + -2;
      } while (lVar13 - (uVar14 & 0xfffffffffffffffe) != 0x33c);
      if (uVar14 == uVar21) goto LAB_00107cec;
    }
    iVar20 = local_70._4_4_ * 2 - (int)uVar21;
    iVar23 = (int)local_70 * 2 - (int)uVar21;
    do {
      iVar26 = (int)local_70 * -2 + (int)uVar21;
      iVar29 = iVar23;
      if (-1 < iVar26) {
        iVar29 = iVar26;
      }
      (&DAT_0012bddc)[uVar21] = 0;
      if (iVar29 < 3) {
LAB_00107cd4:
        (&DAT_0012bddc)[uVar21] = 0;
      }
      else {
        iVar26 = local_70._4_4_ * -2 + (int)uVar21;
        iVar29 = iVar20;
        if (-1 < iVar26) {
          iVar29 = iVar26;
        }
        if (iVar29 < 3) goto LAB_00107cd4;
      }
      uVar21 = uVar21 + 1;
      iVar20 = iVar20 + -1;
      iVar23 = iVar23 + -1;
    } while ((long)uVar21 < (long)uVar12);
  }
LAB_00107cec:
  iVar20 = 1;
LAB_00107cf0:
  FUN_00107ddc(param_2,param_3 >> 1,iVar2,&local_70,1,iVar20);
  iVar20 = 0;
  if ((0 < (int)local_70) && ((int)local_70 < iVar2 + -1)) {
    iVar2 = (&DAT_0012bddc)[(int)local_70 + -1];
    iVar20 = (&DAT_0012bddc)[(int)local_70 + 1];
    uVar3 = (&DAT_0012bddc)[(int)local_70] - iVar2;
    if ((int)(((int)uVar3 >> 0x10) * 0xb334 + ((uVar3 & 0xffff) * 0x599a >> 0xf)) < iVar20 - iVar2)
    {
      iVar20 = 1;
    }
    else {
      uVar3 = (&DAT_0012bddc)[(int)local_70] - iVar20;
      iVar20 = -(uint)((int)(((int)uVar3 >> 0x10) * 0xb334 + ((uVar3 & 0xffff) * 0x599a >> 0xf)) <
                      iVar2 - iVar20);
    }
  }
  *param_5 = (int)local_70 * 2 - iVar20;
  if (*(long *)(lVar4 + 0x28) != local_68) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}


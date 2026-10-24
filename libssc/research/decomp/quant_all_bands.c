/* quant_all_bands @ 00103ae8 size 2088 */

void quant_all_bands(long param_1,uint param_2,long param_3,long param_4,undefined8 param_5,
                    long param_6,int param_7,undefined4 param_8,int param_9,uint param_10,
                    long param_11,int param_12,int param_13,undefined8 param_14,int param_15,
                    undefined4 *param_16)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  long lVar12;
  short sVar13;
  short sVar14;
  short sVar15;
  short sVar16;
  short sVar17;
  short sVar18;
  short sVar19;
  short sVar20;
  short sVar21;
  short sVar22;
  short sVar23;
  short sVar24;
  short sVar25;
  short sVar26;
  short sVar27;
  short sVar28;
  long lVar29;
  undefined8 uVar30;
  byte bVar31;
  byte bVar32;
  int iVar33;
  int iVar34;
  int iVar35;
  int iVar36;
  int iVar37;
  int iVar38;
  long lVar39;
  ulong uVar40;
  ulong uVar41;
  undefined8 *puVar42;
  short *psVar43;
  long lVar44;
  ulong uVar45;
  long lVar46;
  uint uVar47;
  uint uVar48;
  uint uVar49;
  int iVar50;
  ulong uVar51;
  uint uVar52;
  undefined8 uVar53;
  undefined8 uVar54;
  undefined8 uVar55;
  undefined8 uVar56;
  undefined8 uVar57;
  int local_c8;
  undefined4 local_b0 [2];
  long local_a8;
  int local_a0;
  uint local_9c;
  undefined4 uStack_98;
  undefined4 local_94;
  undefined8 local_90;
  int local_88;
  undefined8 local_80;
  undefined4 local_78;
  long local_70;
  
  lVar12 = tpidr_el0;
  local_70 = *(long *)(lVar12 + 0x28);
  lVar44 = *(long *)(param_1 + 0x10);
  local_90 = param_14;
  local_b0[0] = 1;
  local_9c = param_10;
  local_78 = *param_16;
  uVar47 = 8;
  if (param_7 == 0) {
    uVar47 = 1;
  }
  local_a8 = param_1;
  uStack_98 = param_8;
  local_80 = param_5;
  if (0 < (int)param_2) {
    local_c8 = param_9;
    uVar9 = ~(-1 << (ulong)uVar47);
    uVar51 = 0;
    do {
      iVar50 = (int)uVar51;
      uVar1 = uVar51 + 1;
      lVar39 = (long)*(short *)(lVar44 + uVar51 * 2);
      lVar2 = param_3 + lVar39 * 0x10;
      lVar3 = param_3 + 0x6c0 + lVar39 * 0x10;
      uVar10 = *(short *)(lVar44 + uVar1 * 2) * 8 - (int)(lVar39 * 8);
      uVar40 = (ulong)uVar10;
      local_a0 = iVar50;
      iVar35 = ec_tell_frac(param_14);
      uVar53 = local_80;
      uVar30 = local_90;
      uVar6 = local_9c;
      iVar38 = local_a0;
      lVar29 = local_a8;
      iVar7 = 0;
      if (uVar51 != 0) {
        iVar7 = iVar35;
      }
      uVar52 = param_12 - iVar35;
      uVar48 = 0;
      local_88 = uVar52 - 1;
      if ((long)uVar51 < (long)param_15) {
        iVar11 = param_15 - iVar50;
        if (2 < iVar11) {
          iVar11 = 3;
        }
        iVar36 = 0;
        if (iVar11 != 0) {
          iVar36 = (param_13 - iVar7) / iVar11;
        }
        uVar48 = *(int *)(param_6 + uVar51 * 4) + iVar36;
        if ((int)uVar48 <= (int)uVar52) {
          uVar52 = uVar48;
        }
        if ((int)uVar52 < 0x4000) {
          uVar48 = uVar52 & ((int)uVar52 >> 0x1f ^ 0xffffffffU);
        }
        else {
          uVar48 = 0x3fff;
        }
      }
      local_94 = *(undefined4 *)(param_11 + uVar51 * 4);
      iVar11 = 0;
      if (local_c8 != 0 && uVar51 != param_10) {
        iVar11 = local_c8;
      }
      if (iVar11 == 0) {
        iVar37 = uVar10 * 2 + -1;
        iVar36 = *(short *)(*(long *)(local_a8 + 0x38) + (long)local_a0 * 2) + 0x18;
        uVar52 = (uVar48 - iVar36) - 0x20;
        uVar49 = 0;
        if (iVar37 != 0) {
          uVar49 = (int)(uVar48 + ((iVar36 >> 1) + -4) * iVar37) / iVar37;
        }
        if ((int)uVar49 <= (int)uVar52) {
          uVar52 = uVar49;
        }
        if (0x3f < (int)uVar52) {
          uVar52 = 0x40;
        }
        if ((int)uVar52 < 4) {
          uVar52 = 1;
        }
        else {
          uVar52 = ((int)(short)(&DAT_00113540)[uVar52 & 7] >> (0xe - (uVar52 >> 3) & 0x1f)) + 1U &
                   0xfffffffe;
        }
        iVar36 = stereo_itheta(lVar2,lVar3,1);
        iVar37 = ec_tell_frac(uVar30);
        uVar49 = uVar9;
        if ((iVar38 < (int)uVar6) && (uVar52 != 1)) {
          uVar6 = uVar52;
          if ((int)uVar52 < 0) {
            uVar6 = uVar52 + 1;
          }
          uVar4 = (int)uVar6 >> 1;
          uVar8 = iVar36 * uVar52 + 0x2000;
          iVar5 = (int)uVar8 >> 0xe;
          iVar36 = (uVar6 & 0xfffffffe) + uVar4 + 3;
          if ((int)uVar4 < iVar5) {
            iVar33 = iVar36 + ~uVar4 + iVar5;
          }
          else {
            iVar33 = iVar5 * 3;
          }
          iVar34 = iVar5 * 3 + 3;
          if ((int)uVar4 < iVar5) {
            iVar34 = (iVar36 - uVar4) + iVar5;
          }
          ec_encode(uVar30,iVar33,iVar34,iVar36 + uVar4);
          uVar6 = 0;
          if (uVar52 != 0) {
            uVar6 = (int)(uVar8 & 0xffffc000) / (int)uVar52;
          }
          if (uVar6 == 0) {
            FUN_00104efc(lVar29,lVar2,lVar3,uVar53,iVar38,uVar40);
            goto LAB_00104154;
          }
          if (0 < (int)uVar10) {
            puVar42 = (undefined8 *)(param_3 + lVar39 * 0x10);
            uVar45 = uVar40;
            do {
              uVar54 = puVar42[1];
              uVar53 = *puVar42;
              uVar56 = puVar42[0xd9];
              uVar55 = puVar42[0xd8];
              uVar45 = uVar45 - 8;
              sVar17 = (short)((uint)((short)uVar53 * 0xb504) >> 0x10);
              sVar13 = (short)((uint)((short)uVar55 * 0xb504) >> 0x10);
              sVar18 = (short)((uint)((short)((ulong)uVar53 >> 0x10) * 0xb504) >> 0x10);
              sVar14 = (short)((uint)((short)((ulong)uVar55 >> 0x10) * 0xb504) >> 0x10);
              sVar19 = (short)((uint)((short)((ulong)uVar53 >> 0x20) * 0xb504) >> 0x10);
              sVar15 = (short)((uint)((short)((ulong)uVar55 >> 0x20) * 0xb504) >> 0x10);
              sVar20 = (short)((uint)((short)((ulong)uVar53 >> 0x30) * 0xb504) >> 0x10);
              sVar16 = (short)((uint)((short)((ulong)uVar55 >> 0x30) * 0xb504) >> 0x10);
              sVar25 = (short)((uint)((short)uVar54 * 0xb504) >> 0x10);
              sVar21 = (short)((uint)((short)uVar56 * 0xb504) >> 0x10);
              sVar26 = (short)((uint)((short)((ulong)uVar54 >> 0x10) * 0xb504) >> 0x10);
              sVar22 = (short)((uint)((short)((ulong)uVar56 >> 0x10) * 0xb504) >> 0x10);
              sVar27 = (short)((uint)((short)((ulong)uVar54 >> 0x20) * 0xb504) >> 0x10);
              sVar23 = (short)((uint)((short)((ulong)uVar56 >> 0x20) * 0xb504) >> 0x10);
              sVar28 = (short)((uint)((short)((ulong)uVar54 >> 0x30) * 0xb504) >> 0x10);
              sVar24 = (short)((uint)((short)((ulong)uVar56 >> 0x30) * 0xb504) >> 0x10);
              puVar42[1] = CONCAT26(sVar24 + sVar28,
                                    CONCAT24(sVar23 + sVar27,
                                             CONCAT22(sVar22 + sVar26,sVar21 + sVar25)));
              *puVar42 = CONCAT26(sVar16 + sVar20,
                                  CONCAT24(sVar15 + sVar19,CONCAT22(sVar14 + sVar18,sVar13 + sVar17)
                                          ));
              puVar42[0xd9] =
                   CONCAT26(sVar24 - sVar28,
                            CONCAT24(sVar23 - sVar27,CONCAT22(sVar22 - sVar26,sVar21 - sVar25)));
              puVar42[0xd8] =
                   CONCAT26(sVar16 - sVar20,
                            CONCAT24(sVar15 - sVar19,CONCAT22(sVar14 - sVar18,sVar13 - sVar17)));
              puVar42 = puVar42 + 2;
            } while (uVar45 != 0);
          }
          iVar38 = ec_tell_frac(uVar30);
          iVar38 = iVar38 - iVar37;
          uVar48 = uVar48 - iVar38;
          if (uVar6 == 0) goto LAB_0010416c;
          if (uVar6 == 0x4000) {
            iVar36 = 0x7fff;
            uVar6 = 0x4000;
            iVar37 = 0x4000;
            uVar49 = uVar9 << (ulong)uVar47 & (-1 << (ulong)uVar47 ^ 0xffffffffU);
          }
          else {
            iVar37 = uVar6 * -0x10000 + 0x40000000;
            iVar36 = (int)((-(uVar6 >> 0xf & 1) & 0xfff80000 | (uVar6 & 0xffff) << 3) *
                           (int)(short)uVar6 + 0x8000) >> 0x10;
            iVar37 = (iVar37 >> 0xd) * (iVar37 >> 0x10) + 0x8000 >> 0x10;
            iVar5 = (int)(((0x7fff - iVar36) +
                          (((int)((((iVar36 * -0x272 + 0x4000 >> 0xf) + 0x2055) * iVar36 * 2 +
                                   0x8000U & 0xffff0000) + 0xe21d0000) >> 0x10) * iVar36 + 0x4000U
                          >> 0xf)) * 0x10000 + 0x10000) >> 0x10;
            iVar36 = (int)(((0x7fff - iVar37) +
                           (((int)((((iVar37 * -0x272 + 0x4000 >> 0xf) + 0x2055) * iVar37 * 2 +
                                    0x8000U & 0xffff0000) + 0xe21d0000) >> 0x10) * iVar37 + 0x4000U
                           >> 0xf)) * 0x10000 + 0x10000) >> 0x10;
            iVar33 = ec_ilog(iVar5);
            iVar34 = ec_ilog(iVar36);
            iVar37 = (int)(short)(iVar36 << (ulong)(0xfU - iVar34 & 0x1f));
            iVar5 = (int)(short)(iVar5 << (ulong)(0xfU - iVar33 & 0x1f));
            iVar37 = (int)(short)((((short)iVar34 - (short)iVar33) * 0x800 -
                                  (short)(((iVar5 * -0xa25 + 0x4000 >> 0xf) + 0x1efc) * iVar5 +
                                          0x4000U >> 0xf)) +
                                 (short)(((iVar37 * -0xa25 + 0x4000 >> 0xf) + 0x1efc) * iVar37 +
                                         0x4000U >> 0xf)) *
                     (int)(short)((short)uVar10 * 0x80 + -0x80) + 0x4000 >> 0xf;
          }
        }
        else {
          if ((0 < (int)uVar10) && (0x2000 < iVar36)) {
            if (uVar10 < 0x10) {
              uVar41 = 0;
            }
            else {
              uVar41 = uVar40 & 0xfffffff0;
              puVar42 = (undefined8 *)(param_3 + 0x6d0 + lVar39 * 0x10);
              uVar45 = uVar41;
              do {
                uVar55 = puVar42[-1];
                uVar54 = puVar42[-2];
                uVar57 = puVar42[1];
                uVar56 = *puVar42;
                uVar45 = uVar45 - 0x10;
                puVar42[-1] = CONCAT26(-(short)((ulong)uVar55 >> 0x30),
                                       CONCAT24(-(short)((ulong)uVar55 >> 0x20),
                                                CONCAT22(-(short)((ulong)uVar55 >> 0x10),
                                                         -(short)uVar55)));
                puVar42[-2] = CONCAT26(-(short)((ulong)uVar54 >> 0x30),
                                       CONCAT24(-(short)((ulong)uVar54 >> 0x20),
                                                CONCAT22(-(short)((ulong)uVar54 >> 0x10),
                                                         -(short)uVar54)));
                puVar42[1] = CONCAT26(-(short)((ulong)uVar57 >> 0x30),
                                      CONCAT24(-(short)((ulong)uVar57 >> 0x20),
                                               CONCAT22(-(short)((ulong)uVar57 >> 0x10),
                                                        -(short)uVar57)));
                *puVar42 = CONCAT26(-(short)((ulong)uVar56 >> 0x30),
                                    CONCAT24(-(short)((ulong)uVar56 >> 0x20),
                                             CONCAT22(-(short)((ulong)uVar56 >> 0x10),-(short)uVar56
                                                     )));
                puVar42 = puVar42 + 4;
              } while (uVar45 != 0);
              if (uVar41 == uVar40) goto LAB_0010411c;
            }
            lVar46 = uVar40 - uVar41;
            psVar43 = (short *)(param_3 + 0x6c0 + (uVar41 + lVar39 * 8) * 2);
            do {
              lVar46 = lVar46 + -1;
              *psVar43 = -*psVar43;
              psVar43 = psVar43 + 1;
            } while (lVar46 != 0);
          }
LAB_0010411c:
          FUN_00104efc(lVar29,lVar2,lVar3,uVar53,iVar38);
          if ((0x10 < uVar48) && (0x10 < local_88)) {
            ec_enc_bit_logp(uVar30,0x2000 < iVar36,2);
          }
LAB_00104154:
          iVar38 = ec_tell_frac(uVar30);
          iVar38 = iVar38 - iVar37;
          uVar48 = uVar48 - iVar38;
LAB_0010416c:
          uVar6 = 0;
          iVar36 = 0;
          iVar37 = -0x4000;
        }
        iVar37 = uVar48 - iVar37;
        if (iVar37 < 0) {
          iVar37 = iVar37 + 1;
        }
        uVar10 = uVar48;
        if (iVar37 >> 1 <= (int)uVar48) {
          uVar10 = iVar37 >> 1;
        }
        uVar10 = uVar10 & ((int)uVar10 >> 0x1f ^ 0xffffffffU);
        iVar37 = uVar48 - uVar10;
        iVar38 = local_88 - iVar38;
        local_88 = iVar38;
        if ((int)uVar10 < iVar37) {
          bVar32 = FUN_00104310(local_b0,lVar3,uVar40,iVar37,uVar47,iVar36,(int)uVar49 >> uVar47);
          iVar37 = (local_88 - iVar38) + iVar37;
          iVar38 = iVar37 + -0x18;
          if ((iVar38 == 0 || iVar37 < 0x18) || uVar6 == 0x4000) {
            iVar38 = 0;
          }
          bVar31 = FUN_00104310(local_b0,lVar2,uVar40,iVar38 + uVar10,uVar47,0x7fff,uVar49);
          bVar31 = bVar31 | bVar32;
          bVar32 = bVar31;
        }
        else {
          bVar32 = FUN_00104310(local_b0,lVar2,uVar40,uVar10,uVar47,0x7fff,uVar49);
          iVar38 = (local_88 - iVar38) + uVar10;
          iVar5 = iVar38 + -0x18;
          if ((iVar5 == 0 || iVar38 < 0x18) || uVar6 == 0) {
            iVar5 = 0;
          }
          bVar31 = FUN_00104310(local_b0,lVar3,uVar40,iVar5 + iVar37,uVar47,iVar36,
                                (int)uVar49 >> uVar47);
          bVar31 = bVar31 | bVar32;
          bVar32 = bVar31;
        }
      }
      else {
        uVar10 = uVar48 >> 1 & 0x7fff;
        bVar31 = FUN_00104310(local_b0,lVar2,uVar40,uVar10,uVar47,0x7fff,uVar9);
        bVar32 = FUN_00104310(local_b0,lVar3,uVar40,uVar10,uVar47,0x7fff,uVar9);
      }
      *(byte *)(param_4 + (-(uVar51 >> 0x1e & 1) & 0xffffffff00000000 | (uVar51 & 0x7fffffff) << 1))
           = bVar31;
      *(byte *)(param_4 + ((long)(iVar50 << 1) | 1U)) = bVar32;
      param_13 = (param_13 - iVar7) + iVar35 + *(int *)(param_6 + uVar51 * 4);
      uVar51 = uVar1;
      local_c8 = iVar11;
    } while (uVar1 != param_2);
  }
  *param_16 = local_78;
  if (*(long *)(lVar12 + 0x28) == local_70) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


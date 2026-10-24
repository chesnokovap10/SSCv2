/* ssc_quant_all_bands @ 00108898 size 1952 */

void ssc_quant_all_bands(long param_1,uint param_2,long param_3,long param_4,undefined8 param_5,
                        long param_6,int param_7,undefined4 param_8,int param_9,uint param_10,
                        long param_11,int param_12,int param_13,undefined8 param_14,int param_15,
                        undefined4 *param_16)

{
  long lVar1;
  ulong uVar2;
  undefined8 *puVar3;
  long lVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  short sVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  long lVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  short sVar15;
  short sVar16;
  short sVar17;
  short sVar18;
  short sVar19;
  short sVar20;
  short sVar21;
  short sVar22;
  int iVar23;
  undefined8 uVar24;
  byte bVar25;
  byte bVar26;
  int iVar27;
  int iVar28;
  int iVar29;
  ulong uVar30;
  long lVar31;
  ulong uVar32;
  long lVar33;
  int iVar34;
  long lVar35;
  undefined8 *puVar36;
  short *psVar37;
  uint uVar38;
  long lVar39;
  ulong uVar40;
  uint uVar41;
  uint uVar42;
  uint uVar43;
  ulong uVar44;
  ulong uVar45;
  int iVar46;
  undefined8 uVar47;
  int iVar48;
  int iVar49;
  undefined8 uVar50;
  undefined8 uVar51;
  short sVar52;
  ushort uVar53;
  ushort uVar54;
  ushort uVar55;
  int local_cc;
  long local_c8;
  undefined4 local_b8 [2];
  long local_b0;
  int local_a8;
  uint local_a4;
  undefined4 uStack_a0;
  undefined4 local_9c;
  undefined8 local_98;
  int local_90;
  undefined8 local_88;
  undefined4 local_80;
  int local_78;
  int iStack_74;
  long local_70;
  
  lVar12 = tpidr_el0;
  local_70 = *(long *)(lVar12 + 0x28);
  lVar39 = *(long *)(param_1 + 0x10);
  local_b8[0] = 1;
  local_80 = *param_16;
  local_98 = param_14;
  uVar38 = 8;
  if (param_7 == 0) {
    uVar38 = 1;
  }
  local_a4 = param_10;
  local_b0 = param_1;
  uStack_a0 = param_8;
  local_88 = param_5;
  if (0 < (int)param_2) {
    local_cc = param_9;
    lVar1 = param_3 + 0x6c0;
    uVar10 = ~(-1 << (ulong)uVar38);
    uVar45 = 0;
    local_c8 = lVar1 + (long)*(short *)(lVar39 + (long)*(int *)(param_1 + 8) * 2) * 0x10;
    do {
      uVar2 = uVar45 + 1;
      sVar8 = *(short *)(lVar39 + uVar45 * 2);
      uVar44 = (ulong)sVar8;
      iVar49 = (int)*(short *)(lVar39 + uVar2 * 2);
      iVar46 = iVar49 - sVar8;
      local_a8 = (int)uVar45;
      iVar27 = ssc_ec_tell_frac(param_14);
      uVar13 = local_88;
      uVar24 = local_98;
      uVar5 = local_a4;
      iVar48 = local_a8;
      lVar31 = local_b0;
      iVar6 = 0;
      if (uVar45 != 0) {
        iVar6 = iVar27;
      }
      uVar11 = param_12 - iVar27;
      uVar41 = 0;
      local_90 = uVar11 - 1;
      if ((long)uVar45 < (long)param_15) {
        lVar35 = (long)param_15 - uVar45;
        iVar34 = (int)lVar35;
        if (2 < lVar35) {
          iVar34 = 3;
        }
        iVar28 = 0;
        if (iVar34 != 0) {
          iVar28 = (param_13 - iVar6) / iVar34;
        }
        uVar41 = *(int *)(param_6 + uVar45 * 4) + iVar28;
        if ((int)uVar41 <= (int)uVar11) {
          uVar11 = uVar41;
        }
        if ((int)uVar11 < 0x4000) {
          uVar41 = uVar11 & ((int)uVar11 >> 0x1f ^ 0xffffffffU);
        }
        else {
          uVar41 = 0x3fff;
        }
      }
      lVar35 = 0;
      if (uVar45 != param_2 - 1) {
        lVar35 = local_c8;
      }
      local_9c = *(undefined4 *)(param_11 + uVar45 * 4);
      uVar30 = -(uVar44 >> 0x1f & 1) & 0xfffffff000000000 | (uVar44 & 0xffffffff) << 4;
      puVar3 = (undefined8 *)(param_3 + uVar30);
      lVar4 = lVar1 + uVar30;
      uVar11 = iVar46 * 8;
      uVar30 = (ulong)uVar11;
      iVar34 = 0;
      if (uVar45 != param_10 && local_cc != 0) {
        iVar34 = local_cc;
      }
      if (iVar34 == 0) {
        iVar29 = iVar46 * 0x10 + -1;
        iVar28 = *(short *)(*(long *)(local_b0 + 0x38) + (long)local_a8 * 2) + 0x18;
        uVar43 = (uVar41 - iVar28) - 0x20;
        uVar42 = 0;
        if (iVar29 != 0) {
          uVar42 = (int)(uVar41 + ((iVar28 >> 1) + -4) * iVar29) / iVar29;
        }
        if ((int)uVar42 <= (int)uVar43) {
          uVar43 = uVar42;
        }
        if (0x3f < (int)uVar43) {
          uVar43 = 0x40;
        }
        if ((int)uVar43 < 4) {
          uVar43 = 1;
        }
        else {
          uVar43 = ((int)(short)(&DAT_00102760)[uVar43 & 7] >> (0xe - (uVar43 >> 3) & 0x1f)) + 1U &
                   0xfffffffe;
        }
        uVar40 = (uVar44 & 0xffffffff) << 3;
        uVar44 = -(uVar44 >> 0x1f & 1) & 0xfffffff800000000 | uVar40;
        iVar28 = ssc_stereo_itheta(puVar3,lVar4,uVar30);
        iVar29 = ssc_ec_tell_frac(uVar24);
        uVar42 = uVar10;
        if ((iVar48 < (int)uVar5) && (uVar43 != 1)) {
          uVar9 = iVar28 * uVar43 + 0x2000;
          uVar5 = (int)uVar43 >> 1;
          iVar28 = (int)uVar9 >> 0xe;
          iVar46 = (uVar43 & 0xfffffffe) + uVar5 + 3;
          iVar7 = (iVar46 - uVar5) + iVar28;
          iVar23 = iVar46 + ~uVar5 + iVar28;
          if (iVar28 <= (int)uVar5) {
            iVar7 = iVar28 * 3 + 3;
            iVar23 = iVar28 * 3;
          }
          ssc_ec_encode(uVar24,iVar23,iVar7,iVar46 + uVar5);
          iVar46 = 0;
          if (uVar43 != 0) {
            iVar46 = (int)(uVar9 & 0xffffc000) / (int)uVar43;
          }
          if (iVar46 == 0) {
            FUN_00109ca4(lVar31,puVar3,lVar4,uVar13,iVar48,uVar30);
            goto LAB_00108e0c;
          }
          lVar31 = (ulong)((iVar49 * 8 - (int)uVar40) - 8) + 8;
          puVar36 = puVar3;
          do {
            uVar50 = puVar36[1];
            uVar47 = *puVar36;
            lVar31 = lVar31 + -8;
            uVar14 = puVar36[0xd9];
            uVar13 = puVar36[0xd8];
            iVar48 = (short)((ulong)uVar47 >> 0x10) * 0xb504;
            iVar49 = (short)((ulong)uVar47 >> 0x20) * 0xb504;
            iVar28 = (short)((ulong)uVar47 >> 0x30) * 0xb504;
            sVar52 = (short)((uint)((short)uVar13 * 0xb504) >> 0x10);
            uVar53 = (ushort)((uint)((short)((ulong)uVar13 >> 0x10) * 0xb504) >> 0x10);
            uVar54 = (ushort)((uint)((short)((ulong)uVar13 >> 0x20) * 0xb504) >> 0x10);
            uVar55 = (ushort)((uint)((short)((ulong)uVar13 >> 0x30) * 0xb504) >> 0x10);
            sVar22 = (short)((uint)((short)uVar50 * 0xb504) >> 0x10);
            sVar20 = (short)((uint)((short)uVar14 * 0xb504) >> 0x10);
            sVar19 = (short)((uint)((short)((ulong)uVar50 >> 0x10) * 0xb504) >> 0x10);
            sVar18 = (short)((uint)((short)((ulong)uVar14 >> 0x10) * 0xb504) >> 0x10);
            sVar17 = (short)((uint)((short)((ulong)uVar50 >> 0x20) * 0xb504) >> 0x10);
            sVar16 = (short)((uint)((short)((ulong)uVar14 >> 0x20) * 0xb504) >> 0x10);
            sVar15 = (short)((uint)((short)((ulong)uVar50 >> 0x30) * 0xb504) >> 0x10);
            sVar8 = (short)((uint)((short)((ulong)uVar14 >> 0x30) * 0xb504) >> 0x10);
            sVar21 = (short)((uint)((short)uVar47 * 0xb504) >> 0x10);
            puVar36[1] = CONCAT26(sVar8 + sVar15,
                                  CONCAT24(sVar16 + sVar17,CONCAT22(sVar18 + sVar19,sVar20 + sVar22)
                                          ));
            *puVar36 = CONCAT26((short)((uint)uVar55 + (iVar28 >> 0x10)),
                                CONCAT24((short)((uint)uVar54 + (iVar49 >> 0x10)),
                                         CONCAT22((short)((uint)uVar53 + (iVar48 >> 0x10)),
                                                  sVar52 + sVar21)));
            puVar36[0xd9] =
                 CONCAT26(sVar8 - sVar15,
                          CONCAT24(sVar16 - sVar17,CONCAT22(sVar18 - sVar19,sVar20 - sVar22)));
            puVar36[0xd8] =
                 CONCAT26(uVar55 - (short)((uint)iVar28 >> 0x10),
                          CONCAT24(uVar54 - (short)((uint)iVar49 >> 0x10),
                                   CONCAT22(uVar53 - (short)((uint)iVar48 >> 0x10),sVar52 - sVar21))
                         );
            puVar36 = puVar36 + 2;
          } while (lVar31 != 0);
          iVar48 = ssc_ec_tell_frac(uVar24);
          if (iVar46 == 0) goto LAB_00108e20;
          if (iVar46 == 0x4000) {
            iVar49 = 0x4000;
            uVar42 = uVar10 << (ulong)uVar38 & (-1 << (ulong)uVar38 ^ 0xffffffffU);
            iVar28 = 0x7fff;
          }
          else {
            ssc_bitexact_cos_asm(iVar46,0x4000 - iVar46,&iStack_74,&local_78);
            uVar5 = (int)LZCOUNT(local_78) - 0x11;
            uVar43 = (int)LZCOUNT(iStack_74) - 0x11;
            iVar49 = (int)(short)(local_78 << (ulong)(uVar5 & 0x1f));
            iVar28 = (int)(short)(iStack_74 << (ulong)(uVar43 & 0x1f));
            iVar49 = (int)(short)(((short)(((iVar49 * -0xa25 + 0x4000 >> 0xf) + 0x1efc) * iVar49 +
                                           0x4000U >> 0xf) + ((short)uVar43 - (short)uVar5) * 0x800)
                                 - (short)(((iVar28 * -0xa25 + 0x4000 >> 0xf) + 0x1efc) * iVar28 +
                                           0x4000U >> 0xf)) *
                     (int)(short)((short)uVar11 * 0x80 + -0x80) + 0x4000 >> 0xf;
            iVar28 = local_78;
          }
        }
        else {
          if ((0 < iVar46) && (0x2000 < iVar28)) {
            if (uVar11 < 0x10) {
              uVar32 = 0;
            }
            else {
              uVar32 = uVar30 & 0xfffffff0;
              puVar36 = (undefined8 *)(param_3 + 0x6d0 + uVar44 * 2);
              uVar40 = uVar32;
              do {
                uVar51 = puVar36[-1];
                uVar50 = puVar36[-2];
                uVar47 = puVar36[1];
                uVar14 = *puVar36;
                uVar40 = uVar40 - 0x10;
                puVar36[-1] = CONCAT26(-(short)((ulong)uVar51 >> 0x30),
                                       CONCAT24(-(short)((ulong)uVar51 >> 0x20),
                                                CONCAT22(-(short)((ulong)uVar51 >> 0x10),
                                                         -(short)uVar51)));
                puVar36[-2] = CONCAT26(-(short)((ulong)uVar50 >> 0x30),
                                       CONCAT24(-(short)((ulong)uVar50 >> 0x20),
                                                CONCAT22(-(short)((ulong)uVar50 >> 0x10),
                                                         -(short)uVar50)));
                puVar36[1] = CONCAT26(-(short)((ulong)uVar47 >> 0x30),
                                      CONCAT24(-(short)((ulong)uVar47 >> 0x20),
                                               CONCAT22(-(short)((ulong)uVar47 >> 0x10),
                                                        -(short)uVar47)));
                *puVar36 = CONCAT26(-(short)((ulong)uVar14 >> 0x30),
                                    CONCAT24(-(short)((ulong)uVar14 >> 0x20),
                                             CONCAT22(-(short)((ulong)uVar14 >> 0x10),-(short)uVar14
                                                     )));
                puVar36 = puVar36 + 4;
              } while (uVar40 != 0);
              if (uVar32 == uVar30) goto LAB_00108dd0;
            }
            lVar33 = uVar30 - uVar32;
            psVar37 = (short *)(lVar1 + (uVar32 + uVar44) * 2);
            do {
              lVar33 = lVar33 + -1;
              *psVar37 = -*psVar37;
              psVar37 = psVar37 + 1;
            } while (lVar33 != 0);
          }
LAB_00108dd0:
          FUN_00109ca4(lVar31,puVar3,lVar4,uVar13,iVar48,uVar30);
          if ((0x10 < uVar41) && (0x10 < local_90)) {
            ssc_ec_enc_bit_logp(uVar24,0x2000 < iVar28,2);
          }
LAB_00108e0c:
          iVar48 = ssc_ec_tell_frac(uVar24);
          iVar46 = 0;
LAB_00108e20:
          iVar28 = 0;
          iVar49 = -0x4000;
        }
        uVar41 = uVar41 - (iVar48 - iVar29);
        iVar48 = local_90 - (iVar48 - iVar29);
        iVar49 = uVar41 - iVar49;
        if (iVar49 < 0) {
          iVar49 = iVar49 + 1;
        }
        uVar5 = uVar41;
        if (iVar49 >> 1 <= (int)uVar41) {
          uVar5 = iVar49 >> 1;
        }
        uVar5 = uVar5 & ((int)uVar5 >> 0x1f ^ 0xffffffffU);
        iVar49 = uVar41 - uVar5;
        local_90 = iVar48;
        if ((int)uVar5 < iVar49) {
          bVar26 = FUN_00109038(local_b8,lVar4,uVar30,iVar49,uVar38,iVar28,0,uVar42 >> (ulong)uVar38
                               );
          iVar49 = (local_90 - iVar48) + iVar49;
          iVar48 = iVar49 + -0x18;
          if (iVar46 == 0x4000 || iVar49 < 0x19) {
            iVar48 = 0;
          }
          bVar25 = FUN_00109038(local_b8,puVar3,uVar30,iVar48 + uVar5,uVar38,0x7fff,lVar35,uVar42);
          bVar25 = bVar25 | bVar26;
          bVar26 = bVar25;
        }
        else {
          bVar26 = FUN_00109038(local_b8,puVar3,uVar30,uVar5,uVar38,0x7fff,lVar35,uVar42);
          iVar48 = (local_90 - iVar48) + uVar5;
          iVar29 = iVar48 + -0x18;
          if (iVar46 == 0 || iVar48 < 0x19) {
            iVar29 = 0;
          }
          bVar25 = FUN_00109038(local_b8,lVar4,uVar30,iVar29 + iVar49,uVar38,iVar28,0,
                                uVar42 >> (ulong)uVar38);
          bVar25 = bVar25 | bVar26;
          bVar26 = bVar25;
        }
      }
      else {
        bVar25 = FUN_00109038(local_b8,puVar3,uVar30,uVar41 >> 1,uVar38,0x7fff,lVar35,uVar10);
        bVar26 = FUN_00109038(local_b8,lVar4,uVar30,uVar41 >> 1,uVar38,0x7fff,lVar35,uVar10);
      }
      *(byte *)(param_4 + (-(uVar45 >> 0x1e & 1) & 0xffffffff00000000 | (uVar45 & 0x7fffffff) << 1))
           = bVar25;
      *(byte *)(param_4 + ((int)uVar45 << 1) + 1) = bVar26;
      param_13 = (param_13 - iVar6) + iVar27 + *(int *)(param_6 + uVar45 * 4);
      uVar45 = uVar2;
      local_cc = iVar34;
      local_c8 = lVar35;
    } while (uVar2 != param_2);
  }
  *param_16 = local_80;
  if (*(long *)(lVar12 + 0x28) != local_70) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}


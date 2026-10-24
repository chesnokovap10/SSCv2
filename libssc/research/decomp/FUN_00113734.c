/* FUN_00113734 @ 00113734 size 1384 */

void FUN_00113734(long param_1,uint param_2,long param_3,long param_4,int param_5,int param_6,
                 long param_7,long param_8,long param_9,int param_10,short param_11)

{
  uint uVar1;
  uint uVar2;
  ulong uVar3;
  short sVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  long lVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  long lVar16;
  int iVar17;
  long lVar18;
  ulong uVar19;
  int iVar20;
  int iVar21;
  uint local_6c;
  long local_68;
  
  lVar9 = tpidr_el0;
  local_68 = *(long *)(lVar9 + 0x28);
  if (param_6 + 3 <= param_5) {
    ssc_ec_enc_bit_logp(param_9,param_10,3);
  }
  iVar15 = -0x199a;
  if (param_10 != 0) {
    iVar15 = -0x1333;
  }
  if ((int)param_2 < 1) {
    iVar11 = 0;
  }
  else {
    iVar5 = (uint)(param_10 == 0) * 0x4000;
    uVar19 = 0;
    iVar20 = 0;
    iVar17 = 0;
    iVar11 = 0;
    iVar21 = param_5 + param_2 * -6 + 0x20;
    do {
      lVar18 = uVar19 * 2;
      sVar4 = *(short *)(param_4 + lVar18);
      iVar12 = (int)sVar4;
      if (sVar4 < -0x23ff) {
        iVar12 = -0x2400;
      }
      iVar12 = iVar17 + (iVar5 * iVar12 >> 8);
      iVar13 = (int)*(short *)(param_3 + lVar18);
      iVar6 = iVar13 * 0x80 - iVar12;
      local_6c = iVar6 + 0x10000 >> 0x11;
      if (iVar6 < -0x10000) {
        iVar14 = (int)sVar4 - (int)param_11;
        if (iVar14 < -0x6fff) {
          iVar14 = -0x7000;
        }
        iVar7 = (short)iVar14 - iVar13;
        if (iVar7 != 0 && iVar13 <= (short)iVar14) {
          local_6c = local_6c + (iVar7 >> 10);
          local_6c = local_6c & (int)local_6c >> 0x1f;
        }
      }
      uVar10 = local_6c;
      iVar13 = *(int *)(param_9 + 0x18) + (int)LZCOUNT(*(undefined4 *)(param_9 + 0x20));
      iVar14 = (param_5 + 0x20) - iVar13;
      if (((uVar19 != 0) && (iVar13 = iVar21 - iVar13, iVar13 < 0x1e)) && (iVar13 < 0x18)) {
        if (0 < (int)local_6c) {
          local_6c = 1;
        }
        if ((iVar13 < 0x10) && ((int)local_6c < 0)) {
          local_6c = 0xffffffff;
        }
      }
      if (iVar14 < 0xf) {
        if (iVar14 < 2) {
          if (iVar14 == 1) {
            local_6c = local_6c & (int)local_6c >> 0x1f;
            ssc_ec_enc_bit_logp(param_9,-local_6c,1);
          }
          else {
            local_6c = 0xffffffff;
          }
        }
        else {
          if (0 < (int)local_6c) {
            local_6c = 1;
          }
          if ((int)local_6c < 0) {
            local_6c = 0xffffffff;
          }
          ssc_ec_enc_icdf(param_9,local_6c << 1 ^ (int)local_6c >> 0x1f,&DAT_00105ded,2);
        }
      }
      else {
        uVar3 = uVar19;
        if (0x13 < uVar19) {
          uVar3 = 0x14;
        }
        ssc_ec_laplace_encode
                  (param_9,&local_6c,(ulong)*(byte *)(param_7 + (uVar3 << 1 & 0x1fffffffe)) << 7,
                   (ulong)*(byte *)(param_7 + (uVar3 << 1 & 0xfffffffe) + 1) << 6);
      }
      uVar2 = local_6c;
      if ((int)local_6c < -0x7fffff) {
        uVar2 = 0xff800000;
      }
      if (0x7ffffe < (int)uVar2) {
        uVar2 = 0x7fffff;
      }
      iVar14 = uVar10 - uVar2;
      iVar12 = uVar2 * 0x20000 + iVar12;
      iVar13 = -iVar14;
      if (-1 < iVar14) {
        iVar13 = iVar14;
      }
      lVar16 = (uVar19 + (long)*(int *)(param_1 + 8)) * 2;
      if (iVar12 < -0x37ffff) {
        iVar12 = -0x380000;
      }
      *(short *)(param_8 + lVar18) = (short)(iVar6 + 0x40U >> 7) + (short)local_6c * -0x400;
      *(short *)(param_4 + lVar18) = (short)(iVar12 + 0x40U >> 7);
      sVar4 = *(short *)(param_4 + lVar16);
      iVar12 = (int)sVar4;
      if (sVar4 < -0x23ff) {
        iVar12 = -0x2400;
      }
      iVar14 = (int)*(short *)(param_3 + lVar16);
      iVar12 = iVar20 + (iVar5 * iVar12 >> 8);
      iVar6 = iVar14 * 0x80 - iVar12;
      local_6c = iVar6 + 0x10000 >> 0x11;
      if (iVar6 < -0x10000) {
        iVar7 = (int)sVar4 - (int)param_11;
        if (iVar7 < -0x6fff) {
          iVar7 = -0x7000;
        }
        iVar8 = (short)iVar7 - iVar14;
        if (iVar8 != 0 && iVar14 <= (short)iVar7) {
          local_6c = local_6c + (iVar8 >> 10);
          local_6c = local_6c & (int)local_6c >> 0x1f;
        }
      }
      uVar10 = local_6c;
      iVar14 = *(int *)(param_9 + 0x18) + (int)LZCOUNT(*(undefined4 *)(param_9 + 0x20));
      iVar7 = (param_5 + 0x20) - iVar14;
      if (((uVar19 != 0) && (iVar14 = iVar21 - iVar14, iVar14 < 0x1e)) && (iVar14 < 0x18)) {
        if (0 < (int)local_6c) {
          local_6c = 1;
        }
        if ((iVar14 < 0x10) && ((int)local_6c < 0)) {
          local_6c = 0xffffffff;
        }
      }
      if (iVar7 < 0xf) {
        if (iVar7 < 2) {
          if (iVar7 == 1) {
            local_6c = local_6c & (int)local_6c >> 0x1f;
            ssc_ec_enc_bit_logp(param_9,-local_6c,1);
          }
          else {
            local_6c = 0xffffffff;
          }
        }
        else {
          if (0 < (int)local_6c) {
            local_6c = 1;
          }
          if ((int)local_6c < 0) {
            local_6c = 0xffffffff;
          }
          ssc_ec_enc_icdf(param_9,local_6c << 1 ^ (int)local_6c >> 0x1f,&DAT_00105ded,2);
        }
      }
      else {
        uVar3 = uVar19;
        if (0x13 < uVar19) {
          uVar3 = 0x14;
        }
        ssc_ec_laplace_encode
                  (param_9,&local_6c,(ulong)*(byte *)(param_7 + (uVar3 << 1 & 0x1fffffffe)) << 7,
                   (ulong)*(byte *)(param_7 + (uVar3 << 1 & 0xfffffffe) + 1) << 6);
      }
      uVar1 = local_6c;
      if ((int)local_6c < -0x7fffff) {
        uVar1 = 0xff800000;
      }
      lVar18 = (uVar19 + (long)*(int *)(param_1 + 8)) * 2;
      uVar19 = uVar19 + 1;
      iVar17 = uVar2 * 0x20000 + iVar17 + iVar15 * (short)(uVar2 << 2);
      if (0x7ffffe < (int)uVar1) {
        uVar1 = 0x7fffff;
      }
      *(short *)(param_8 + lVar18) = (short)(iVar6 + 0x40U >> 7) + (short)local_6c * -0x400;
      iVar14 = uVar10 - uVar1;
      iVar6 = -iVar14;
      if (-1 < iVar14) {
        iVar6 = iVar14;
      }
      iVar11 = iVar13 + iVar11 + iVar6;
      iVar12 = uVar1 * 0x20000 + iVar12;
      if (iVar12 < -0x37ffff) {
        iVar12 = -0x380000;
      }
      iVar20 = uVar1 * 0x20000 + iVar20 + iVar15 * (short)(uVar1 << 2);
      iVar21 = iVar21 + 6;
      *(short *)(param_4 + lVar18) = (short)(iVar12 + 0x40U >> 7);
      local_6c = uVar1;
    } while (param_2 != uVar19);
  }
  if (*(long *)(lVar9 + 0x28) != local_68) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(iVar11);
  }
  return;
}


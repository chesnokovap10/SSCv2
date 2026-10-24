/* FUN_00108f10 @ 00108f10 size 1216 */

void FUN_00108f10(long param_1,uint param_2,long param_3,long param_4,int param_5,int param_6,
                 long param_7,long param_8,long param_9,int param_10,short param_11)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  long lVar5;
  long lVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  ulong uVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  long lVar17;
  ulong uVar18;
  int local_74;
  int iStack_70;
  uint local_6c;
  long local_68;
  
  lVar6 = tpidr_el0;
  local_68 = *(long *)(lVar6 + 0x28);
  if (param_6 + 3 <= param_5) {
    ec_enc_bit_logp(param_9,param_10,3);
  }
  iVar13 = 0x199a;
  if (param_10 != 0) {
    iVar13 = 0x1333;
  }
  if ((int)param_2 < 1) {
    iVar9 = 0;
  }
  else {
    iVar2 = (uint)(param_10 == 0) * 0x4000;
    uVar18 = 0;
    iVar9 = 0;
    iVar16 = param_5 + param_2 * -6;
    local_74 = 0;
    iStack_70 = 0;
    do {
      lVar17 = uVar18 * 2;
      uVar12 = uVar18;
      if (0x13 < uVar18) {
        uVar12 = 0x14;
      }
      sVar1 = *(short *)(param_4 + lVar17);
      lVar5 = (uVar12 & 0xffffffff) * 2;
      iVar14 = (int)sVar1;
      if (sVar1 < -0x23ff) {
        iVar14 = -0x2400;
      }
      iVar10 = (int)*(short *)(param_3 + lVar17);
      iVar15 = iVar2 * iVar14 >> 8;
      iVar3 = (iVar10 * 0x80 - iVar15) - local_74;
      iVar14 = iVar3 + 0x10000;
      local_6c = iVar14 >> 0x11;
      if (iVar14 < 0) {
        iVar14 = (int)sVar1 - (int)param_11;
        if (iVar14 < -0x6fff) {
          iVar14 = -0x7000;
        }
        iVar11 = (short)iVar14 - iVar10;
        if (iVar11 != 0 && iVar10 <= (short)iVar14) {
          local_6c = local_6c + (iVar11 >> 10);
          local_6c = local_6c & (int)local_6c >> 0x1f;
        }
      }
      uVar7 = local_6c;
      iVar14 = *(int *)(param_9 + 0x18);
      uVar12 = (ulong)((uint)lVar5 | 1);
      iVar10 = ec_ilog(*(undefined4 *)(param_9 + 0x20));
      iVar10 = iVar10 - iVar14;
      iVar14 = iVar10 + param_5;
      if ((uVar18 != 0) && (iVar10 = iVar16 + iVar10, iVar10 < 0x18)) {
        if (0 < (int)local_6c) {
          local_6c = 1;
        }
        if ((iVar10 < 0x10) && ((int)local_6c < 0)) {
          local_6c = 0xffffffff;
        }
      }
      if (iVar14 < 0xf) {
        if (iVar14 < 2) {
          if (iVar14 == 1) {
            local_6c = local_6c & (int)local_6c >> 0x1f;
            ec_enc_bit_logp(param_9,-local_6c,1);
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
          ec_enc_icdf(param_9,local_6c << 1 ^ (int)local_6c >> 0x1f,&DAT_00116a75,2);
        }
      }
      else {
        ec_laplace_encode(param_9,&local_6c,(ulong)*(byte *)(param_7 + lVar5) << 7,
                          (ulong)*(byte *)(param_7 + uVar12) << 6);
      }
      uVar8 = local_6c;
      iVar10 = uVar7 - local_6c;
      local_74 = local_74 + local_6c * 0x20000;
      *(short *)(param_8 + lVar17) = (short)(iVar3 + 0x40U >> 7) + (short)local_6c * -0x400;
      iVar14 = -iVar10;
      if (-1 < iVar10) {
        iVar14 = iVar10;
      }
      iVar15 = local_74 + iVar15;
      if (iVar15 < -0x37ffff) {
        iVar15 = -0x380000;
      }
      *(short *)(param_4 + lVar17) = (short)(iVar15 + 0x40U >> 7);
      lVar17 = (uVar18 + (long)*(int *)(param_1 + 8)) * 2;
      sVar1 = *(short *)(param_4 + lVar17);
      iVar15 = (int)sVar1;
      if (sVar1 < -0x23ff) {
        iVar15 = -0x2400;
      }
      iVar11 = (int)*(short *)(param_3 + lVar17);
      iVar3 = iVar2 * iVar15 >> 8;
      iVar10 = (iVar11 * 0x80 - iVar3) - iStack_70;
      iVar15 = iVar10 + 0x10000;
      local_6c = iVar15 >> 0x11;
      if (iVar15 < 0) {
        iVar15 = (int)sVar1 - (int)param_11;
        if (iVar15 < -0x6fff) {
          iVar15 = -0x7000;
        }
        iVar4 = (short)iVar15 - iVar11;
        if (iVar4 != 0 && iVar11 <= (short)iVar15) {
          local_6c = local_6c + (iVar4 >> 10);
          local_6c = local_6c & (int)local_6c >> 0x1f;
        }
      }
      uVar7 = local_6c;
      iVar15 = *(int *)(param_9 + 0x18);
      iVar11 = ec_ilog(*(undefined4 *)(param_9 + 0x20));
      iVar11 = iVar11 - iVar15;
      iVar15 = iVar11 + param_5;
      if ((uVar18 != 0) && (iVar11 = iVar16 + iVar11, iVar11 < 0x18)) {
        if (0 < (int)local_6c) {
          local_6c = 1;
        }
        if ((iVar11 < 0x10) && ((int)local_6c < 0)) {
          local_6c = 0xffffffff;
        }
      }
      local_74 = local_74 - (-(uVar8 >> 0xd & 1) & 0xffff0000 | (uVar8 & 0x3fff) << 2) * iVar13;
      if (iVar15 < 0xf) {
        if (iVar15 < 2) {
          if (iVar15 == 1) {
            local_6c = local_6c & (int)local_6c >> 0x1f;
            ec_enc_bit_logp(param_9,-local_6c,1);
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
          ec_enc_icdf(param_9,local_6c << 1 ^ (int)local_6c >> 0x1f,&DAT_00116a75,2);
        }
      }
      else {
        ec_laplace_encode(param_9,&local_6c,(ulong)*(byte *)(param_7 + lVar5) << 7,
                          (ulong)*(byte *)(param_7 + uVar12) << 6);
      }
      iVar11 = uVar7 - local_6c;
      iVar15 = iStack_70 + local_6c * 0x20000;
      lVar17 = (uVar18 + (long)*(int *)(param_1 + 8)) * 2;
      iStack_70 = iVar15 - (-(local_6c >> 0xd & 1) & 0xffff0000 | (local_6c & 0x3fff) << 2) * iVar13
      ;
      iVar15 = iVar15 + iVar3;
      *(short *)(param_8 + lVar17) = (short)(iVar10 + 0x40U >> 7) + (short)local_6c * -0x400;
      iVar3 = -iVar11;
      if (-1 < iVar11) {
        iVar3 = iVar11;
      }
      if (iVar15 < -0x37ffff) {
        iVar15 = -0x380000;
      }
      uVar18 = uVar18 + 1;
      iVar9 = iVar3 + iVar14 + iVar9;
      iVar16 = iVar16 + 6;
      *(short *)(param_4 + lVar17) = (short)(iVar15 + 0x40U >> 7);
    } while (param_2 != uVar18);
  }
  if (*(long *)(lVar6 + 0x28) != local_68) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(iVar9);
  }
  return;
}


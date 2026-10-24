/* ec_enc_done @ 00105abc size 816 */

void ec_enc_done(long *param_1)

{
  uint *puVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  byte bVar10;
  
  iVar3 = ec_ilog((int)param_1[4]);
  iVar7 = *(int *)((long)param_1 + 0x24);
  uVar9 = -iVar3 + 0x18;
  uVar5 = 0x7fffff >> (ulong)(uVar9 & 0x1f);
  uVar4 = uVar5 + iVar7 & -0x800000 >> (uVar9 & 0x1f);
  if ((uint)((int)param_1[4] + iVar7) <= (uVar4 | uVar5)) {
    uVar9 = -iVar3 + 0x19;
    uVar4 = (uVar5 >> 1) + iVar7 & (uVar5 >> 1 ^ 0xffffffff);
  }
  puVar1 = (uint *)((long)param_1 + 0x2c);
  if (0 < (int)uVar9) {
    uVar5 = uVar9;
    do {
      while (uVar4 >> 0xf != 0xff) {
        cVar2 = (char)(uVar4 >> 0x17);
        if (-1 < (int)*puVar1) {
          uVar8 = *(uint *)((long)param_1 + 0x1c);
          if (*(int *)((long)param_1 + 0xc) + uVar8 < *(uint *)(param_1 + 1)) {
            uVar6 = 0;
            *(uint *)((long)param_1 + 0x1c) = uVar8 + 1;
            *(char *)(*param_1 + (ulong)uVar8) = (char)*puVar1 + cVar2;
          }
          else {
            uVar6 = 0xffffffff;
          }
          *(uint *)(param_1 + 6) = *(uint *)(param_1 + 6) | uVar6;
        }
        iVar7 = (int)param_1[5];
        if (iVar7 != 0) {
          do {
            uVar8 = *(uint *)((long)param_1 + 0x1c);
            if (*(int *)((long)param_1 + 0xc) + uVar8 < *(uint *)(param_1 + 1)) {
              *(uint *)((long)param_1 + 0x1c) = uVar8 + 1;
              *(char *)(*param_1 + (ulong)uVar8) = cVar2 + -1;
              iVar7 = (int)param_1[5];
              uVar8 = 0;
            }
            else {
              uVar8 = 0xffffffff;
            }
            iVar7 = iVar7 + -1;
            *(int *)(param_1 + 5) = iVar7;
            *(uint *)(param_1 + 6) = *(uint *)(param_1 + 6) | uVar8;
          } while (iVar7 != 0);
        }
        *puVar1 = uVar4 >> 0xf & 0xff;
        uVar5 = uVar5 - 8;
        uVar4 = (uVar4 & 0x7fff) << 8;
        if ((int)uVar5 < 1) goto LAB_00105c20;
      }
      *(int *)(param_1 + 5) = (int)param_1[5] + 1;
      uVar5 = uVar5 - 8;
      uVar4 = (uVar4 & 0x7fff) << 8;
    } while (0 < (int)uVar5);
LAB_00105c20:
    uVar9 = (uVar9 - 8) - (uVar9 - 1 & 0xfffffff8);
  }
  if ((int)*puVar1 < 0) {
    iVar7 = (int)param_1[5];
    if (iVar7 != 0) goto LAB_00105cf0;
    uVar5 = *(uint *)(param_1 + 2);
    uVar4 = *(uint *)((long)param_1 + 0x14);
  }
  else {
    uVar4 = *(uint *)((long)param_1 + 0x1c);
    if (*(int *)((long)param_1 + 0xc) + uVar4 < *(uint *)(param_1 + 1)) {
      uVar5 = 0;
      *(uint *)((long)param_1 + 0x1c) = uVar4 + 1;
      *(char *)(*param_1 + (ulong)uVar4) = (char)*puVar1;
    }
    else {
      uVar5 = 0xffffffff;
    }
    iVar7 = (int)param_1[5];
    *(uint *)(param_1 + 6) = *(uint *)(param_1 + 6) | uVar5;
    while (iVar7 != 0) {
LAB_00105cf0:
      uVar4 = *(uint *)((long)param_1 + 0x1c);
      if (*(int *)((long)param_1 + 0xc) + uVar4 < *(uint *)(param_1 + 1)) {
        *(uint *)((long)param_1 + 0x1c) = uVar4 + 1;
        *(undefined1 *)(*param_1 + (ulong)uVar4) = 0xff;
        iVar7 = (int)param_1[5];
        uVar4 = 0;
      }
      else {
        uVar4 = 0xffffffff;
      }
      iVar7 = iVar7 + -1;
      *(int *)(param_1 + 5) = iVar7;
      *(uint *)(param_1 + 6) = *(uint *)(param_1 + 6) | uVar4;
    }
    *puVar1 = 0;
    uVar5 = *(uint *)(param_1 + 2);
    uVar4 = *(uint *)((long)param_1 + 0x14);
  }
  if ((int)uVar4 < 8) {
    uVar6 = *(uint *)(param_1 + 6);
  }
  else {
    uVar8 = uVar4;
    do {
      if ((uint)(*(int *)((long)param_1 + 0xc) + *(int *)((long)param_1 + 0x1c)) <
          *(uint *)(param_1 + 1)) {
        iVar7 = *(int *)((long)param_1 + 0xc) + 1;
        uVar6 = 0;
        *(int *)((long)param_1 + 0xc) = iVar7;
        *(char *)(*param_1 + (ulong)(*(uint *)(param_1 + 1) - iVar7)) = (char)uVar5;
      }
      else {
        uVar6 = 0xffffffff;
      }
      uVar8 = uVar8 - 8;
      uVar5 = uVar5 >> 8;
      uVar6 = *(uint *)(param_1 + 6) | uVar6;
      *(uint *)(param_1 + 6) = uVar6;
    } while (7 < (int)uVar8);
    uVar4 = uVar4 & 7;
  }
  if (uVar6 == 0) {
    bVar10 = (byte)uVar5;
    SSC_CLEAR(*param_1 + (ulong)*(uint *)((long)param_1 + 0x1c),
              ((int)param_1[1] - *(uint *)((long)param_1 + 0x1c)) - *(int *)((long)param_1 + 0xc));
    if (0 < (int)uVar4) {
      uVar5 = *(uint *)(param_1 + 1);
      uVar8 = *(uint *)((long)param_1 + 0xc);
      if (uVar8 < uVar5) {
        if (((int)-uVar9 < (int)uVar4) && (uVar5 <= *(int *)((long)param_1 + 0x1c) + uVar8)) {
          bVar10 = bVar10 & ((byte)(-1 << (ulong)(-uVar9 & 0x1f)) ^ 0xff);
          *(undefined4 *)(param_1 + 6) = 0xffffffff;
        }
        *(byte *)(*param_1 + (ulong)(uVar5 + ~uVar8)) =
             *(byte *)(*param_1 + (ulong)(uVar5 + ~uVar8)) | bVar10;
      }
      else {
        *(undefined4 *)(param_1 + 6) = 0xffffffff;
      }
    }
  }
  return;
}


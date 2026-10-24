/* ssc_ec_enc_done @ 0010fd08 size 752 */

void ssc_ec_enc_done(long *param_1)

{
  bool bVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  byte bVar9;
  
  iVar5 = *(int *)((long)param_1 + 0x24);
  iVar4 = (int)LZCOUNT((int)param_1[4]);
  uVar7 = iVar4 - 8;
  uVar8 = 0x7fffff >> (ulong)(uVar7 & 0x1f);
  uVar3 = uVar8 + iVar5 & -0x800000 >> (uVar7 & 0x1f);
  if ((uint)(iVar5 + (int)param_1[4]) <= (uVar3 | uVar8)) {
    uVar7 = iVar4 - 7;
    uVar3 = (uVar8 >> 1) + iVar5 & (uVar8 >> 1 ^ 0xffffffff);
  }
  uVar8 = uVar7;
  if (0 < (int)uVar7) {
    do {
      if (uVar3 >> 0xf == 0xff) {
        *(int *)(param_1 + 5) = (int)param_1[5] + 1;
      }
      else {
        cVar2 = (char)(uVar3 >> 0x17);
        if (-1 < *(int *)((long)param_1 + 0x2c)) {
          uVar7 = *(uint *)((long)param_1 + 0x1c);
          if (*(int *)((long)param_1 + 0xc) + uVar7 < *(uint *)(param_1 + 1)) {
            uVar6 = 0;
            *(uint *)((long)param_1 + 0x1c) = uVar7 + 1;
            *(char *)(*param_1 + (ulong)uVar7) = (char)*(int *)((long)param_1 + 0x2c) + cVar2;
          }
          else {
            uVar6 = 0xffffffff;
          }
          *(uint *)(param_1 + 6) = *(uint *)(param_1 + 6) | uVar6;
        }
        iVar5 = (int)param_1[5];
        if (iVar5 != 0) {
          do {
            uVar7 = *(uint *)((long)param_1 + 0x1c);
            if (*(int *)((long)param_1 + 0xc) + uVar7 < *(uint *)(param_1 + 1)) {
              uVar6 = 0;
              *(uint *)((long)param_1 + 0x1c) = uVar7 + 1;
              *(char *)(*param_1 + (ulong)uVar7) = cVar2 + -1;
              iVar5 = (int)param_1[5];
            }
            else {
              uVar6 = 0xffffffff;
            }
            iVar5 = iVar5 + -1;
            *(int *)(param_1 + 5) = iVar5;
            *(uint *)(param_1 + 6) = *(uint *)(param_1 + 6) | uVar6;
          } while (iVar5 != 0);
        }
        *(uint *)((long)param_1 + 0x2c) = uVar3 >> 0xf & 0xff;
      }
      uVar3 = (uVar3 & 0x7fff) << 8;
      uVar7 = uVar8 - 8;
      bVar1 = 7 < (int)uVar8;
      uVar8 = uVar7;
    } while (uVar7 != 0 && bVar1);
  }
  if (*(int *)((long)param_1 + 0x2c) < 0) {
    iVar5 = (int)param_1[5];
    if (iVar5 != 0) goto LAB_0010fed4;
  }
  else {
    uVar3 = *(uint *)((long)param_1 + 0x1c);
    if (*(int *)((long)param_1 + 0xc) + uVar3 < *(uint *)(param_1 + 1)) {
      uVar8 = 0;
      *(uint *)((long)param_1 + 0x1c) = uVar3 + 1;
      *(char *)(*param_1 + (ulong)uVar3) = (char)*(int *)((long)param_1 + 0x2c);
    }
    else {
      uVar8 = 0xffffffff;
    }
    iVar5 = (int)param_1[5];
    *(uint *)(param_1 + 6) = *(uint *)(param_1 + 6) | uVar8;
    while (iVar5 != 0) {
LAB_0010fed4:
      uVar3 = *(uint *)((long)param_1 + 0x1c);
      if (*(int *)((long)param_1 + 0xc) + uVar3 < *(uint *)(param_1 + 1)) {
        uVar8 = 0;
        *(uint *)((long)param_1 + 0x1c) = uVar3 + 1;
        *(undefined1 *)(*param_1 + (ulong)uVar3) = 0xff;
        iVar5 = (int)param_1[5];
      }
      else {
        uVar8 = 0xffffffff;
      }
      iVar5 = iVar5 + -1;
      *(int *)(param_1 + 5) = iVar5;
      *(uint *)(param_1 + 6) = *(uint *)(param_1 + 6) | uVar8;
    }
    *(undefined4 *)((long)param_1 + 0x2c) = 0;
  }
  uVar3 = *(uint *)(param_1 + 2);
  iVar5 = *(int *)((long)param_1 + 0x14);
  iVar4 = iVar5;
  if (iVar5 < 8) {
    uVar8 = *(uint *)(param_1 + 6);
  }
  else {
    do {
      if ((uint)(*(int *)((long)param_1 + 0xc) + *(int *)((long)param_1 + 0x1c)) <
          *(uint *)(param_1 + 1)) {
        iVar5 = *(int *)((long)param_1 + 0xc) + 1;
        uVar8 = 0;
        *(int *)((long)param_1 + 0xc) = iVar5;
        *(char *)(*param_1 + (ulong)(*(uint *)(param_1 + 1) - iVar5)) = (char)uVar3;
      }
      else {
        uVar8 = 0xffffffff;
      }
      iVar5 = iVar4 + -8;
      uVar3 = uVar3 >> 8;
      uVar8 = *(uint *)(param_1 + 6) | uVar8;
      *(uint *)(param_1 + 6) = uVar8;
      bVar1 = 0xf < iVar4;
      iVar4 = iVar5;
    } while (bVar1);
  }
  if (uVar8 == 0) {
    bVar9 = (byte)uVar3;
    SSC_CLEAR(*param_1 + (ulong)*(uint *)((long)param_1 + 0x1c),
              (int)param_1[1] - (*(uint *)((long)param_1 + 0x1c) + *(int *)((long)param_1 + 0xc)));
    if (0 < iVar5) {
      uVar3 = *(uint *)(param_1 + 1);
      uVar8 = *(uint *)((long)param_1 + 0xc);
      if (uVar8 < uVar3) {
        if ((uVar3 <= *(int *)((long)param_1 + 0x1c) + uVar8) && ((int)-uVar7 < iVar5)) {
          bVar9 = bVar9 & ((byte)(-1 << (ulong)(-uVar7 & 0x1f)) ^ 0xff);
          *(undefined4 *)(param_1 + 6) = 0xffffffff;
        }
        *(byte *)(*param_1 + (ulong)(uVar3 + ~uVar8)) =
             *(byte *)(*param_1 + (ulong)(uVar3 + ~uVar8)) | bVar9;
      }
      else {
        *(undefined4 *)(param_1 + 6) = 0xffffffff;
      }
    }
  }
  return;
}


/* ==== print_raw_with_column @ 004ca4fc size 880 ::       <unknown>must specify at least one of read, write, or append accesscreating or truncating a file requires write or append accessBox<dyn Any>thread caused non-unwinding panic. aborting.
ï¿½failed to write whole bufferLazyLock instance has previously been poisoneduse of std::thread::current() is not possible after the thread's local data has been destroyedfatal runtime error: init_current() was re-entrant, which indicates a bug in the Rust threading implementation, aborting
failed to open /dev/randomfailed to generate random data/dev/random */

/* WARNING: Unknown calling convention: __rustcall */
/* <std[ccd30353ceeaff35]::backtrace_rs::print::BacktraceFrameFmt>::print_raw_with_column */

undefined4 __rustcall
<std[ccd30353ceeaff35]::backtrace_rs::print::BacktraceFrameFmt>::print_raw_with_column
          (long *param_1,undefined8 *****param_2,long *param_3,long *param_4,uint param_5,
          undefined4 param_6,uint param_7,undefined4 param_8)

{
  undefined8 *puVar1;
  long lVar2;
  ulong uVar3;
  undefined *puVar4;
  undefined8 *puVar5;
  undefined4 uVar6;
  undefined8 ****local_c8;
  undefined8 *****local_c0;
  code *pcStack_b8;
  long lStack_b0;
  long local_a8;
  long local_a0;
  long lStack_98;
  long lStack_90;
  long lStack_88;
  long local_80;
  long lStack_78;
  undefined8 *****local_70;
  code *pcStack_68;
  undefined4 local_44;
  
  puVar1 = (undefined8 *)*param_1;
  lVar2 = param_1[1];
  local_c8 = param_2;
  if ((param_2 == (undefined8 *****)0x0) && ((*(byte *)(puVar1 + 4) & 1) == 0)) {
LAB_004ca534:
    if (lVar2 == -1) {
                    /* WARNING: Subroutine does not return */
      core[edc4a680d2d7e122]::panicking::panic_const::panic_const_add_overflow
                (&PTR_s_prebuilts_rust_toolchain_linux_x_00f71848);
    }
    uVar6 = 0;
    param_1[1] = lVar2 + 1;
  }
  else {
    puVar5 = (undefined8 *)*puVar1;
    if (lVar2 == 0) {
      local_c0 = (undefined8 *****)(puVar1 + 3);
      pcStack_b8 = <u64_as_core[edc4a680d2d7e122]::fmt::Display>::fmt;
      uVar3 = core[edc4a680d2d7e122]::fmt::write(*puVar5,puVar5[1],&DAT_0022ecb3,&local_c0);
      if ((uVar3 & 1) == 0) {
        if (*(char *)(puVar1 + 4) == '\x01') {
          local_c0 = &local_c8;
          pcStack_b8 = <*mut_core[edc4a680d2d7e122]::ffi::c_void_as_core[edc4a680d2d7e122]::fmt::Debug>
                       ::fmt;
          lStack_b0 = 0;
          local_a8 = CONCAT62(local_a8._2_6_,0x12);
          uVar3 = core[edc4a680d2d7e122]::fmt::write
                            (*(undefined8 *)*puVar1,((undefined8 *)*puVar1)[1],&DAT_0022ecbe,
                             &local_c0);
          goto joined_r0x004ca640;
        }
        goto LAB_004ca644;
      }
    }
    else {
      uVar3 = (**(code **)(puVar5[1] + 0x18))(*puVar5,&DAT_0022ecd0,6);
      if ((uVar3 & 1) == 0) {
        if (*(char *)(puVar1 + 4) == '\x01') {
          lStack_b0 = 0;
          local_c0 = (undefined8 *****)&DAT_00208db0;
          pcStack_b8 = <&str_as_core[edc4a680d2d7e122]::fmt::Display>::fmt;
          local_a8 = CONCAT62(local_a8._2_6_,0x15);
          uVar3 = core[edc4a680d2d7e122]::fmt::write
                            (*(undefined8 *)*puVar1,((undefined8 *)*puVar1)[1],&DAT_0020b298,
                             &local_c0);
joined_r0x004ca640:
          if ((uVar3 & 1) != 0) goto LAB_004ca6fc;
        }
LAB_004ca644:
        if (*param_3 == 3) {
          uVar3 = (**(code **)(((undefined8 *)*puVar1)[1] + 0x18))
                            (*(undefined8 *)*puVar1,&DAT_0022ecd6,9);
        }
        else {
          if ((*(byte *)(puVar1 + 4) & 1) == 0) {
            lStack_98 = param_3[5];
            local_a0 = param_3[4];
            lStack_88 = param_3[7];
            lStack_90 = param_3[6];
            lStack_78 = param_3[9];
            local_80 = param_3[8];
            puVar4 = &DAT_0022ecca;
          }
          else {
            lStack_98 = param_3[5];
            local_a0 = param_3[4];
            lStack_88 = param_3[7];
            lStack_90 = param_3[6];
            lStack_78 = param_3[9];
            local_80 = param_3[8];
            puVar4 = &DAT_0015f710;
          }
          pcStack_b8 = (code *)param_3[1];
          local_c0 = (undefined8 *****)*param_3;
          local_a8 = param_3[3];
          lStack_b0 = param_3[2];
          local_70 = &local_c0;
          pcStack_68 = <std[ccd30353ceeaff35]::backtrace_rs::symbolize::SymbolName_as_core[edc4a680d2d7e122]::fmt::Display>
                       ::fmt;
          uVar3 = core[edc4a680d2d7e122]::fmt::write
                            (*(undefined8 *)*puVar1,((undefined8 *)*puVar1)[1],puVar4,&local_70);
        }
        if (((uVar3 & 1) == 0) &&
           (uVar3 = (**(code **)(((undefined8 *)*puVar1)[1] + 0x18))
                              (*(undefined8 *)*puVar1,&DAT_0022ecb2,1), (uVar3 & 1) == 0)) {
          if ((*param_4 == 2) || ((param_5 & 1) == 0)) goto LAB_004ca534;
          local_44 = param_6;
          if (*(char *)(puVar1 + 4) == '\x01') {
            lStack_b0 = 0;
            local_c0 = (undefined8 *****)&DAT_00208db0;
            pcStack_b8 = <&str_as_core[edc4a680d2d7e122]::fmt::Display>::fmt;
            local_a8 = CONCAT62(local_a8._2_6_,0x12);
            uVar3 = core[edc4a680d2d7e122]::fmt::write
                              (*(undefined8 *)*puVar1,((undefined8 *)*puVar1)[1],&DAT_0020b298,
                               &local_c0);
            if ((uVar3 & 1) != 0) goto LAB_004ca6fc;
          }
          uVar3 = (**(code **)(((undefined8 *)*puVar1)[1] + 0x18))
                            (*(undefined8 *)*puVar1,&DAT_00208e80,0x10);
          if ((uVar3 & 1) == 0) {
            local_c0 = (undefined8 *****)*puVar1;
            lStack_b0 = param_4[1];
            pcStack_b8 = (code *)*param_4;
            local_a8 = param_4[2];
            uVar3 = (**(code **)(puVar1[2] + 0x20))(puVar1[1],local_c0,&pcStack_b8);
            if ((uVar3 & 1) == 0) {
              local_c0 = (undefined8 *****)&local_44;
              pcStack_b8 = <u32_as_core[edc4a680d2d7e122]::fmt::Display>::fmt;
              uVar3 = core[edc4a680d2d7e122]::fmt::write
                                (*(undefined8 *)*puVar1,((undefined8 *)*puVar1)[1],&DAT_00138566,
                                 &local_c0);
              if ((uVar3 & 1) == 0) {
                if ((param_7 & 1) != 0) {
                  local_70 = (undefined8 *****)CONCAT44(local_70._4_4_,param_8);
                  local_c0 = &local_70;
                  pcStack_b8 = <u32_as_core[edc4a680d2d7e122]::fmt::Display>::fmt;
                  uVar3 = core[edc4a680d2d7e122]::fmt::write
                                    (*(undefined8 *)*puVar1,((undefined8 *)*puVar1)[1],&DAT_00138566
                                     ,&local_c0);
                  if ((uVar3 & 1) != 0) goto LAB_004ca6fc;
                }
                uVar3 = (**(code **)(((undefined8 *)*puVar1)[1] + 0x18))
                                  (*(undefined8 *)*puVar1,&DAT_0022ecb2,1);
                if ((uVar3 & 1) != 0) {
                  return 1;
                }
                goto LAB_004ca534;
              }
            }
          }
        }
      }
    }
LAB_004ca6fc:
    uVar6 = 1;
  }
  return uVar6;
}


/* ==== open_c @ 004cac04 size 472 ::       <unknown>must specify at least one of read, write, or append accesscreating or truncating a file requires write or append accessBox<dyn Any>thread caused non-unwinding panic. aborting.
ï¿½failed to write whole bufferLazyLock instance has previously been poisoneduse of std::thread::current() is not possible after the thread's local data has been destroyedfatal runtime error: init_current() was re-entrant, which indicates a bug in the Rust threading implementation, aborting
failed to open /dev/randomfailed to generate random data/dev/random */

/* WARNING: Unknown calling convention: __rustcall */
/* <std[ccd30353ceeaff35]::sys::fs::unix::File>::open_c */

void __rustcall
<std[ccd30353ceeaff35]::sys::fs::unix::File>::open_c
          (undefined4 *param_1,char *param_2,uint *param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined8 uVar4;
  int *piVar5;
  undefined *puVar6;
  uint uVar7;
  byte bVar8;
  byte bVar9;
  uint uVar10;
  
  bVar8 = *(byte *)((long)param_3 + 10);
  if ((param_3[2] & 1) == 0) {
    if ((*(byte *)((long)param_3 + 9) & 1) == 0) {
      if ((bVar8 & 1) == 0) {
        if ((((param_3[3] & 1) == 0) && ((*(byte *)((long)param_3 + 0xd) & 1) == 0)) &&
           ((*(byte *)((long)param_3 + 0xb) & 1) == 0)) {
          puVar6 = &DAT_0022ecdf;
          uVar4 = 0x3a;
        }
        else {
          puVar6 = &DAT_0022ed19;
          uVar4 = 0x3d;
        }
        uVar4 = <std[ccd30353ceeaff35]::io::error::Error>::new::<&str>(0x14,puVar6,uVar4);
        *(undefined8 *)(param_1 + 2) = uVar4;
        goto LAB_004cadc0;
      }
    }
    else if ((bVar8 & 1) == 0) {
      uVar7 = 1;
      goto LAB_004cac4c;
    }
    uVar10 = 0x401;
    uVar7 = 0x401;
    bVar9 = *(byte *)((long)param_3 + 0xb);
    bVar8 = *(byte *)((long)param_3 + 0xd);
joined_r0x004cac88:
    if ((bVar9 == 1) && (uVar7 = uVar10, (bVar8 & 1) == 0)) {
LAB_004cac90:
      uVar4 = <std[ccd30353ceeaff35]::io::error::Error>::new::<&str>(0x14,&DAT_0022ed19,0x3d);
      *(undefined8 *)(param_1 + 2) = uVar4;
      *param_1 = 1;
      return;
    }
LAB_004cacc4:
    if ((param_3[3] & 1) == 0) {
      uVar10 = 0x200;
      if ((bVar9 & 1) == 0) {
        uVar10 = 0;
      }
    }
    else {
      uVar10 = 0x240;
      if ((bVar9 & 1) == 0) {
        uVar10 = 0x40;
      }
    }
    if ((bVar8 & 1) != 0) {
      uVar10 = 0xc0;
    }
  }
  else {
    if ((*(byte *)((long)param_3 + 9) & 1) != 0) {
      if ((bVar8 & 1) != 0) goto LAB_004cac5c;
      uVar7 = 2;
LAB_004cac4c:
      bVar8 = *(byte *)((long)param_3 + 0xd);
      bVar9 = *(byte *)((long)param_3 + 0xb);
      goto LAB_004cacc4;
    }
    if ((bVar8 & 1) != 0) {
LAB_004cac5c:
      uVar10 = 0x402;
      uVar7 = 0x402;
      bVar9 = *(byte *)((long)param_3 + 0xb);
      bVar8 = *(byte *)((long)param_3 + 0xd);
      goto joined_r0x004cac88;
    }
    if ((((*(byte *)((long)param_3 + 0xb) & 1) != 0) || ((param_3[3] & 1) != 0)) ||
       ((*(byte *)((long)param_3 + 0xd) & 1) != 0)) goto LAB_004cac90;
    uVar7 = 0;
    uVar10 = 0;
  }
  uVar1 = *param_3;
  uVar2 = param_3[1];
  do {
    iVar3 = open(param_2,uVar7 | uVar10 | uVar1 & 0xfffffffc | 0x80000,(ulong)uVar2);
    if (iVar3 != -1) {
      *param_1 = 0;
      param_1[1] = iVar3;
      return;
    }
    piVar5 = (int *)__errno();
  } while (*piVar5 == 4);
  *(ulong *)(param_1 + 2) = (long)*piVar5 << 0x20 | 2;
LAB_004cadc0:
  *param_1 = 1;
  return;
}


/* ==== payload_as_str @ 004cb650 size 224 ::       <unknown>must specify at least one of read, write, or append accesscreating or truncating a file requires write or append accessBox<dyn Any>thread caused non-unwinding panic. aborting.
ï¿½failed to write whole bufferLazyLock instance has previously been poisoneduse of std::thread::current() is not possible after the thread's local data has been destroyedfatal runtime error: init_current() was re-entrant, which indicates a bug in the Rust threading implementation, aborting
failed to open /dev/randomfailed to generate random data/dev/random */

/* WARNING: Unknown calling convention: __rustcall */
/* std[ccd30353ceeaff35]::panicking::payload_as_str */

undefined1  [16] __rustcall
std[ccd30353ceeaff35]::panicking::payload_as_str(undefined8 *param_1,long param_2)

{
  long lVar1;
  undefined8 *puVar2;
  code *pcVar3;
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  long local_30;
  long lStack_28;
  
  pcVar3 = *(code **)(param_2 + 0x18);
  (*pcVar3)(&local_30);
  if (lStack_28 == -0x4674e48ea859be88 && local_30 == 0x63eb502cd6cb5d6d) {
    lVar1 = 8;
    puVar2 = param_1;
  }
  else {
    (*pcVar3)(&local_30,param_1);
    if (lStack_28 != -0x765bbfe123b4fadb || local_30 != 0x481c5eabebfe518d) {
      auVar5._8_8_ = 0xc;
      auVar5._0_8_ = &DAT_0022ed56;
      return auVar5;
    }
    puVar2 = param_1 + 1;
    lVar1 = 0x10;
  }
  auVar4._0_8_ = *puVar2;
  auVar4._8_8_ = *(undefined8 *)((long)param_1 + lVar1);
  return auVar4;
}


/* ==== panic_with_hook @ 004cb730 size 496 ::       <unknown>must specify at least one of read, write, or append accesscreating or truncating a file requires write or append accessBox<dyn Any>thread caused non-unwinding panic. aborting.
ï¿½failed to write whole bufferLazyLock instance has previously been poisoneduse of std::thread::current() is not possible after the thread's local data has been destroyedfatal runtime error: init_current() was re-entrant, which indicates a bug in the Rust threading implementation, aborting
failed to open /dev/randomfailed to generate random data/dev/random */

/* WARNING: Removing unreachable block (ram,0x004cb7b4) */
/* WARNING: Unknown calling convention: __rustcall */
/* std[ccd30353ceeaff35]::panicking::panic_with_hook */

void __rustcall
std[ccd30353ceeaff35]::panicking::panic_with_hook
          (long param_1,long param_2,long *param_3,byte param_4,undefined1 param_5)

{
  char cVar1;
  long lVar2;
  uint uVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  undefined *puVar7;
  undefined1 *puVar8;
  ulong uVar9;
  ulong extraout_x8;
  long *plVar10;
  undefined1 auVar11 [16];
  long local_90;
  long local_88;
  long *plStack_80;
  long local_78;
  undefined8 uStack_70;
  undefined1 local_68 [16];
  long *local_58;
  undefined8 local_50;
  undefined1 uStack_41;
  
  plVar10 = &local_90;
  local_90 = param_1;
  local_88 = param_2;
  plStack_80 = param_3;
  uVar5 = panic_count::increase(1);
  uVar9 = (ulong)(uVar5 & 0xff);
  if ((uVar5 & 0xff) == 2) {
    if (DAT_00fae3d0 < 0x3ffffffe) {
      cVar1 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(&DAT_00fae3d0,0x10);
      if (bVar4) {
        cVar1 = ExclusiveMonitorsStatus();
        DAT_00fae3d0 = DAT_00fae3d0 + 1;
      }
      if (cVar1 != '\0') goto LAB_004cb7b8;
    }
    else {
LAB_004cb7b8:
      <std[ccd30353ceeaff35]::sys::sync::rwlock::futex::RwLock>::read_contended(&DAT_00fae3d0);
    }
    local_58 = param_3;
    if (DAT_00fae3d8 == 0) {
      local_68 = (**(code **)(param_2 + 0x28))(param_1);
      local_50._0_2_ = CONCAT11(param_5,param_4);
      default_hook(local_68);
    }
    else {
      local_68 = (**(code **)(param_2 + 0x28))(param_1);
      local_50._0_2_ = CONCAT11(param_5,param_4);
      (**(code **)(DAT_00fae3e0 + 0x28))(DAT_00fae3d8,local_68);
    }
    do {
      uVar3 = DAT_00fae3d0;
      uVar5 = DAT_00fae3d0 - 1;
      cVar1 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(&DAT_00fae3d0,0x10);
      if (bVar4) {
        cVar1 = ExclusiveMonitorsStatus();
        DAT_00fae3d0 = uVar5;
      }
    } while (cVar1 != '\0');
    if (uVar3 == 0) {
                    /* WARNING: Subroutine does not return */
      core[edc4a680d2d7e122]::panicking::panic_const::panic_const_sub_overflow
                (&PTR_s_prebuilts_rust_toolchain_linux_x_00f71560);
    }
    if ((uVar5 & 0xbfffffff) == 0x80000000) {
      <std[ccd30353ceeaff35]::sys::sync::rwlock::futex::RwLock>::wake_writer_or_readers
                (&DAT_00fae3d0);
    }
    lVar6 = (*(code *)(undefined *)0x0)(&PTR_00fa64c0);
    lVar2 = tpidr_el0;
    *(undefined1 *)(lVar2 + lVar6 + 8) = 0;
    if ((param_4 & 1) == 0) {
      puVar7 = &DAT_0022ed62;
      puVar8 = (undefined1 *)0x5b;
      goto LAB_004cb904;
    }
    __rustc[14c7d0a79fb2d505]::rust_panic(local_90,local_88);
    uVar9 = extraout_x8;
  }
  if ((uVar9 & 1) == 0) {
    local_50 = <&mut_dyn_core[edc4a680d2d7e122]::panic::PanicPayload_as_core[edc4a680d2d7e122]::fmt::Display>
               ::fmt;
    puVar7 = &UNK_001b71c6;
  }
  else {
    auVar11 = (**(code **)(param_2 + 0x30))(param_1);
    local_78 = auVar11._0_8_;
    bVar4 = local_78 == 0;
    if (bVar4) {
      local_78 = 1;
    }
    uStack_70 = 0;
    if (!bVar4) {
      uStack_70 = auVar11._8_8_;
    }
    puVar7 = &DAT_001dfdcb;
    plVar10 = &local_78;
    local_50 = <&str_as_core[edc4a680d2d7e122]::fmt::Display>::fmt;
  }
  local_68._0_8_ = &plStack_80;
  local_68._8_8_ =
       <&core[edc4a680d2d7e122]::panic::location::Location_as_core[edc4a680d2d7e122]::fmt::Display>
       ::fmt;
  puVar8 = local_68;
  local_58 = plVar10;
LAB_004cb904:
  <std[ccd30353ceeaff35]::sys::stdio::unix::Stderr_as_std[ccd30353ceeaff35]::io::Write>::write_fmt
            (&uStack_41,puVar7,puVar8);
  core[edc4a680d2d7e122]::ptr::drop_in_place::
  <core[edc4a680d2d7e122]::result::Result<(),std[ccd30353ceeaff35]::io::error::Error>>();
                    /* WARNING: Subroutine does not return */
  process::abort();
}


/* ==== output_filename @ 004cbc64 size 256 ::       <unknown>must specify at least one of read, write, or append accesscreating or truncating a file requires write or append accessBox<dyn Any>thread caused non-unwinding panic. aborting.
ï¿½failed to write whole bufferLazyLock instance has previously been poisoneduse of std::thread::current() is not possible after the thread's local data has been destroyedfatal runtime error: init_current() was re-entrant, which indicates a bug in the Rust threading implementation, aborting
failed to open /dev/randomfailed to generate random data/dev/random */

/* WARNING: Unknown calling convention: __rustcall */
/* std[ccd30353ceeaff35]::sys::backtrace::output_filename */

void __rustcall
std[ccd30353ceeaff35]::sys::backtrace::output_filename
          (undefined8 *param_1,uint *param_2,uint param_3,long param_4)

{
  long lVar1;
  char *pcVar2;
  long lVar3;
  undefined8 local_60;
  undefined8 local_58;
  char *local_50;
  code *local_48;
  undefined1 *puStack_40;
  code *local_38;
  
  if ((*param_2 & 1) == 0) {
    pcVar2 = *(char **)(param_2 + 2);
    lVar3 = *(long *)(param_2 + 4);
    if (((param_3 & 1) != 0) || (lVar3 == 0)) goto LAB_004cbce0;
  }
  else {
    pcVar2 = &DAT_0022ecd6;
    lVar3 = 9;
    if (param_3 != 0) goto LAB_004cbce0;
  }
  if ((((param_4 != 0) && (*pcVar2 == '/')) &&
      (lVar1 = <std[ccd30353ceeaff35]::path::Path>::_strip_prefix
                         (pcVar2,lVar3,*(undefined8 *)(param_4 + 8),*(undefined8 *)(param_4 + 0x10))
      , lVar1 != 0)) &&
     (core[edc4a680d2d7e122]::str::converts::from_utf8(&local_50), (int)local_50 != 1)) {
    local_60 = local_48;
    local_58 = puStack_40;
    local_50 = "/";
    local_48 = <char_as_core[edc4a680d2d7e122]::fmt::Display>::fmt;
    local_38 = <&str_as_core[edc4a680d2d7e122]::fmt::Display>::fmt;
    puStack_40 = (undefined1 *)&local_60;
    core[edc4a680d2d7e122]::fmt::write(*param_1,param_1[1],&DAT_0011107c,&local_50);
    return;
  }
LAB_004cbce0:
  local_50 = pcVar2;
  local_48 = (code *)lVar3;
  <std[ccd30353ceeaff35]::ffi::os_str::Display_as_core[edc4a680d2d7e122]::fmt::Display>::fmt
            (&local_50,param_1);
  return;
}


/* ==== panic_poisoned @ 004cbdc4 size 36 ::       <unknown>must specify at least one of read, write, or append accesscreating or truncating a file requires write or append accessBox<dyn Any>thread caused non-unwinding panic. aborting.
ï¿½failed to write whole bufferLazyLock instance has previously been poisoneduse of std::thread::current() is not possible after the thread's local data has been destroyedfatal runtime error: init_current() was re-entrant, which indicates a bug in the Rust threading implementation, aborting
failed to open /dev/randomfailed to generate random data/dev/random */

/* WARNING: Unknown calling convention: __rustcall */
/* std[ccd30353ceeaff35]::sync::lazy_lock::panic_poisoned */

void __rustcall std[ccd30353ceeaff35]::sync::lazy_lock::panic_poisoned(void)

{
                    /* WARNING: Subroutine does not return */
  core[edc4a680d2d7e122]::panicking::panic_fmt
            (&DAT_0022edae,0x5d,&PTR_s_prebuilts_rust_toolchain_linux_x_00f71940);
}


/* ==== init_current @ 004cbe1c size 316 ::       <unknown>must specify at least one of read, write, or append accesscreating or truncating a file requires write or append accessBox<dyn Any>thread caused non-unwinding panic. aborting.
ï¿½failed to write whole bufferLazyLock instance has previously been poisoneduse of std::thread::current() is not possible after the thread's local data has been destroyedfatal runtime error: init_current() was re-entrant, which indicates a bug in the Rust threading implementation, aborting
failed to open /dev/randomfailed to generate random data/dev/random */

/* WARNING: Unknown calling convention: __rustcall */
/* std[ccd30353ceeaff35]::thread::current::init_current */

long * __rustcall std[ccd30353ceeaff35]::thread::current::init_current(long param_1)

{
  char cVar1;
  bool bVar2;
  long lVar3;
  long lVar4;
  code *pcVar5;
  long lVar6;
  long lVar7;
  long *plVar8;
  long lVar9;
  long lVar10;
  undefined8 local_48 [3];
  undefined1 uStack_11;
  
  if (param_1 != 0) {
LAB_004cbf18:
    if (param_1 == 1) {
      <std[ccd30353ceeaff35]::sys::stdio::unix::Stderr_as_std[ccd30353ceeaff35]::io::Write>::
      write_fmt(&uStack_11,&DAT_0022ee3a,0xf3);
      core[edc4a680d2d7e122]::ptr::drop_in_place::
      <core[edc4a680d2d7e122]::result::Result<(),std[ccd30353ceeaff35]::io::error::Error>>();
                    /* WARNING: Subroutine does not return */
      process::abort();
    }
                    /* WARNING: Subroutine does not return */
    core[edc4a680d2d7e122]::panicking::panic_fmt
              (&DAT_0022eddc,0xbd,&PTR_s_prebuilts_rust_toolchain_linux_x_00f71958);
  }
  lVar6 = (*(code *)(undefined *)0x0)(&PTR_00fa6340);
  lVar3 = tpidr_el0;
  *(undefined8 *)(lVar3 + lVar6) = 1;
  lVar7 = (*(code *)(undefined *)0x0)(&PTR_00fa6468);
  lVar9 = *(long *)(lVar3 + lVar7);
  lVar10 = DAT_00fae400;
  if (lVar9 == 0) {
    do {
      while( true ) {
        lVar4 = DAT_00fae400;
        if (lVar10 == -1) {
          param_1 = <std[ccd30353ceeaff35]::thread::id::ThreadId>::new::exhausted();
          goto LAB_004cbf18;
        }
        lVar9 = lVar10 + 1;
        if (DAT_00fae400 == lVar10) break;
        ClearExclusiveLocal();
        lVar10 = lVar4;
      }
      cVar1 = '\x01';
      bVar2 = (bool)ExclusiveMonitorPass(0xfae400,0x10);
      if (bVar2) {
        cVar1 = ExclusiveMonitorsStatus();
        DAT_00fae400 = lVar9;
      }
      lVar10 = lVar4;
    } while (cVar1 != '\0');
    *(long *)(lVar3 + lVar7) = lVar9;
  }
  local_48[0] = 0x8000000000000000;
  plVar8 = (long *)<std[ccd30353ceeaff35]::thread::thread::Thread>::new(lVar9,local_48);
  sys::thread_local::guard::key::enable();
  do {
    lVar9 = *plVar8;
    cVar1 = '\x01';
    bVar2 = (bool)ExclusiveMonitorPass(plVar8,0x10);
    if (bVar2) {
      *plVar8 = lVar9 + 1;
      cVar1 = ExclusiveMonitorsStatus();
    }
  } while (cVar1 != '\0');
  if (-1 < lVar9) {
    *(long **)(lVar3 + lVar6) = plVar8 + 2;
    return plVar8;
  }
                    /* WARNING: Does not return */
  pcVar5 = (code *)SoftwareBreakpoint(1,0x4cbf58);
  (*pcVar5)();
}


/* ==== getrandom @ 004cd8e0 size 1200 ::       <unknown>must specify at least one of read, write, or append accesscreating or truncating a file requires write or append accessBox<dyn Any>thread caused non-unwinding panic. aborting.
ï¿½failed to write whole bufferLazyLock instance has previously been poisoneduse of std::thread::current() is not possible after the thread's local data has been destroyedfatal runtime error: init_current() was re-entrant, which indicates a bug in the Rust threading implementation, aborting
failed to open /dev/randomfailed to generate random data/dev/random */

/* WARNING: Removing unreachable block (ram,0x004cda30) */
/* WARNING: Removing unreachable block (ram,0x004cdaf0) */
/* WARNING: Removing unreachable block (ram,0x004cdb0c) */
/* WARNING: Removing unreachable block (ram,0x004cdb14) */
/* WARNING: Removing unreachable block (ram,0x004cdb20) */
/* WARNING: Removing unreachable block (ram,0x004cdb24) */
/* WARNING: Removing unreachable block (ram,0x004cdb34) */
/* WARNING: Removing unreachable block (ram,0x004cda34) */
/* WARNING: Removing unreachable block (ram,0x004cda3c) */
/* WARNING: Removing unreachable block (ram,0x004cda50) */
/* WARNING: Removing unreachable block (ram,0x004cda7c) */
/* WARNING: Removing unreachable block (ram,0x004cda84) */
/* WARNING: Removing unreachable block (ram,0x004cdab4) */
/* WARNING: Removing unreachable block (ram,0x004cdabc) */
/* WARNING: Removing unreachable block (ram,0x004cda90) */
/* WARNING: Removing unreachable block (ram,0x004cda98) */
/* WARNING: Removing unreachable block (ram,0x004cdaa0) */
/* WARNING: Removing unreachable block (ram,0x004cdaa8) */
/* WARNING: Removing unreachable block (ram,0x004cdaac) */
/* WARNING: Removing unreachable block (ram,0x004cdac4) */
/* WARNING: Removing unreachable block (ram,0x004cdad8) */
/* WARNING: Removing unreachable block (ram,0x004cdaec) */
/* WARNING: Removing unreachable block (ram,0x004cda64) */
/* WARNING: Removing unreachable block (ram,0x004cda6c) */
/* WARNING: Removing unreachable block (ram,0x004cda78) */
/* WARNING: Unknown calling convention: __rustcall */
/* std[ccd30353ceeaff35]::sys::random::linux::getrandom */

void __rustcall
std[ccd30353ceeaff35]::sys::random::linux::getrandom(int *param_1,int *param_2,ulong param_3)

{
  undefined4 uVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  undefined **ppuVar6;
  long lVar7;
  long extraout_x8;
  int *__buf;
  undefined8 local_200;
  undefined4 local_1f8;
  undefined2 local_1f4;
  int local_1f0;
  int local_1ec;
  undefined8 local_1e8;
  undefined1 local_1e0 [7];
  undefined4 uStack_1d9;
  undefined1 local_1d5;
  
  __buf = param_1;
  if (DAT_00fa8250 != '\0') {
    if (param_2 == (int *)0x0) {
      return;
    }
    if ((param_3 & 1) != 0) {
      while( true ) {
        bVar2 = DAT_00fa8254 == '\0';
        uVar1 = 4;
        if (bVar2) {
          uVar1 = 1;
        }
        param_1 = (int *)::getrandom(__buf,param_2,uVar1);
        if (param_1 == (int *)0xffffffffffffffff) {
          piVar5 = (int *)__errno();
          param_1 = piVar5;
          do {
            iVar3 = *piVar5;
            if (iVar3 < 0xb) {
              if (iVar3 == 1) goto LAB_004cdb5c;
              if (iVar3 != 4) goto LAB_004cdb44;
            }
            else {
              if (iVar3 == 0xb) {
                if (bVar2) goto LAB_004cdb68;
                goto LAB_004cdb44;
              }
              if (iVar3 == 0x26) goto LAB_004cdb5c;
              if ((iVar3 != 0x16) || (bVar2)) goto LAB_004cdb44;
              DAT_00fa8254 = '\0';
            }
            bVar2 = DAT_00fa8254 == '\0';
            uVar1 = 4;
            if (bVar2) {
              uVar1 = 1;
            }
            param_1 = (int *)::getrandom(__buf,param_2,uVar1);
          } while (param_1 == (int *)0xffffffffffffffff);
        }
        piVar5 = (int *)((long)param_2 - (long)param_1);
        if (param_2 < param_1) break;
        param_2 = piVar5;
        __buf = (int *)((long)__buf + (long)param_1);
        if (piVar5 == (int *)0x0) {
          return;
        }
      }
LAB_004cdcb8:
      piVar5 = (int *)core[edc4a680d2d7e122]::slice::index::slice_index_fail
                                (param_1,param_2,param_2,
                                 &PTR_s_prebuilts_rust_toolchain_linux_x_00f719e8);
LAB_004cdccc:
      param_1 = (int *)core[edc4a680d2d7e122]::slice::index::slice_index_fail
                                 (piVar5,param_2,param_2,
                                  &PTR_s_prebuilts_rust_toolchain_linux_x_00f712a0);
LAB_004cdce0:
      ppuVar6 = (undefined **)
                <std[ccd30353ceeaff35]::sync::once_lock::OnceLock<std[ccd30353ceeaff35]::fs::File>>
                ::initialize::
                <std[ccd30353ceeaff35]::sys::random::linux::getrandom::_closure_0_,std[ccd30353ceeaff35]::io::error::Error>
                          (param_1);
      if (ppuVar6 == (undefined **)0x0) {
LAB_004cdc40:
        iVar3 = DAT_00fa825c;
        if (param_2 == (int *)0x0) {
          return;
        }
        do {
          piVar5 = (int *)::read(iVar3,__buf,(size_t)param_2);
          if (piVar5 == (int *)0xffffffffffffffff) {
            piVar5 = (int *)__errno();
            lVar7 = (long)*piVar5;
            if (*piVar5 != 4) goto LAB_004cdd28;
          }
          else {
            if (piVar5 == (int *)0x0) {
              ppuVar6 = &PTR_DAT_00f712b8;
              break;
            }
            if (param_2 < piVar5) goto LAB_004cdccc;
            __buf = (int *)((long)__buf + (long)piVar5);
            param_2 = (int *)((long)param_2 - (long)piVar5);
          }
          if (param_2 == (int *)0x0) {
            return;
          }
        } while( true );
      }
LAB_004cdd3c:
      local_1e0._0_4_ = SUB84(ppuVar6,0);
      local_1e0._4_2_ = (undefined2)((ulong)ppuVar6 >> 0x20);
      local_1e0[6] = (undefined1)((ulong)ppuVar6 >> 0x30);
      uStack_1d9._0_1_ = (undefined1)((ulong)ppuVar6 >> 0x38);
                    /* WARNING: Subroutine does not return */
      core[edc4a680d2d7e122]::result::unwrap_failed
                (&DAT_0022eecd,0x1e,local_1e0,
                 &PTR_<std[ccd30353ceeaff35]::io::error::Error>_00f716b0,
                 &PTR_s_prebuilts_rust_toolchain_linux_x_00f719b8);
    }
    do {
      while (param_1 = (int *)::getrandom(__buf,param_2,0), param_1 != (int *)0xffffffffffffffff) {
        piVar5 = (int *)((long)param_2 - (long)param_1);
        if (param_2 < param_1) goto LAB_004cdcb8;
        __buf = (int *)((long)__buf + (long)param_1);
        param_2 = piVar5;
        if (piVar5 == (int *)0x0) {
          return;
        }
      }
      param_1 = (int *)__errno();
      iVar3 = *param_1;
      if (iVar3 == 1) goto LAB_004cdb5c;
    } while (iVar3 == 4);
    if (iVar3 != 0x26) {
LAB_004cdb44:
                    /* WARNING: Subroutine does not return */
      core[edc4a680d2d7e122]::panicking::panic_fmt
                (&DAT_0022eecd,0x3d,&PTR_s_prebuilts_rust_toolchain_linux_x_00f719d0);
    }
LAB_004cdb5c:
    DAT_00fa8250 = '\0';
  }
LAB_004cdb68:
  if (((param_3 & 1) != 0) || (DAT_00fae410 != '\0')) {
LAB_004cdc30:
    if (DAT_00fa8258 != 0) goto LAB_004cdce0;
    goto LAB_004cdc40;
  }
  local_1e0._0_4_ = 0x7665642f;
  local_1e0._4_2_ = 0x722f;
  local_1e0[6] = 0x61;
  local_1f4 = 0;
  local_1f8 = 1;
  local_200 = 0x1b600000000;
  uStack_1d9 = 0x6d6f646e;
  local_1d5 = 0;
  <std[ccd30353ceeaff35]::sys::fs::unix::File>::open_c(&local_1f0,local_1e0,&local_200);
  if (local_1f0 == 1) {
    local_1e0._0_4_ = (undefined4)local_1e8;
    local_1e0._4_2_ = (undefined2)((ulong)local_1e8 >> 0x20);
    local_1e0[6] = (undefined1)((ulong)local_1e8 >> 0x30);
    uStack_1d9._0_1_ = (undefined1)((ulong)local_1e8 >> 0x38);
                    /* WARNING: Subroutine does not return */
    core[edc4a680d2d7e122]::result::unwrap_failed
              (&DAT_0022eeb3,0x1a,local_1e0,&PTR_<std[ccd30353ceeaff35]::io::error::Error>_00f716b0,
               &PTR_s_prebuilts_rust_toolchain_linux_x_00f719a0);
  }
  local_1e0._0_4_ = local_1ec;
  local_1e0._4_2_ = 1;
  local_1e0[6] = 0;
  uStack_1d9 = (uint)uStack_1d9._1_3_ << 8;
  do {
    if (DAT_00fae410 != '\0') {
LAB_004cdc28:
      uVar4 = close(local_1ec);
      param_1 = (int *)(ulong)uVar4;
      goto LAB_004cdc30;
    }
    iVar3 = poll((pollfd *)local_1e0,1,-1);
    if (iVar3 != -1) {
      if (iVar3 == 1) {
        if (CONCAT11((undefined1)uStack_1d9,local_1e0[6]) != 1) {
          core[edc4a680d2d7e122]::panicking::assert_failed::<i16,i16>
                    (0,local_1e0 + 6,&DAT_0022eef6,0);
          lVar7 = extraout_x8;
LAB_004cdd28:
          ppuVar6 = (undefined **)(lVar7 << 0x20 | 2);
          goto LAB_004cdd3c;
        }
        DAT_00fae410 = '\x01';
        goto LAB_004cdc28;
      }
      goto LAB_004cdcec;
    }
    piVar5 = (int *)__errno();
    if (*piVar5 != 4) {
LAB_004cdcec:
                    /* WARNING: Subroutine does not return */
      core[edc4a680d2d7e122]::panicking::panic_fmt
                ("poll(\"/dev/random\") failedthe number of hardware threads is not known for the target platform"
                 ,0x35,&PTR_s_prebuilts_rust_toolchain_linux_x_00f71988);
    }
  } while( true );
}


/* ==== fmt @ 004cf9e8 size 288 ::       <unknown>must specify at least one of read, write, or append accesscreating or truncating a file requires write or append accessBox<dyn Any>thread caused non-unwinding panic. aborting.
ï¿½failed to write whole bufferLazyLock instance has previously been poisoneduse of std::thread::current() is not possible after the thread's local data has been destroyedfatal runtime error: init_current() was re-entrant, which indicates a bug in the Rust threading implementation, aborting
failed to open /dev/randomfailed to generate random data/dev/random */

/* WARNING: Unknown calling convention: __rustcall */
/* <std[ccd30353ceeaff35]::backtrace_rs::symbolize::SymbolName as
   core[edc4a680d2d7e122]::fmt::Display>::fmt */

undefined8 __rustcall
<std[ccd30353ceeaff35]::backtrace_rs::symbolize::SymbolName_as_core[edc4a680d2d7e122]::fmt::Display>
::fmt(long *param_1,undefined8 param_2)

{
  ulong uVar1;
  byte bVar2;
  ulong uVar3;
  undefined8 uVar4;
  ulong uVar5;
  long lVar6;
  ulong uVar7;
  int local_68 [2];
  ulong local_60;
  byte local_58;
  byte local_57;
  undefined6 uStack_56;
  
  if (*param_1 != 2) {
    uVar4 = <rustc_demangle[73c884e9013cabc4]::Demangle_as_core[edc4a680d2d7e122]::fmt::Display>::
            fmt(param_1,param_2);
    return uVar4;
  }
  if (param_1[9] != 0) {
    lVar6 = param_1[8];
    uVar5 = param_1[9];
    do {
      core[edc4a680d2d7e122]::str::converts::from_utf8(local_68,lVar6,uVar5);
      bVar2 = local_58;
      uVar1 = local_60;
      if (local_68[0] != 1) {
        uVar4 = <core[edc4a680d2d7e122]::fmt::Formatter>::pad
                          (param_2,local_60,CONCAT62(uStack_56,CONCAT11(local_57,local_58)));
        if ((int)uVar4 != 0) {
          return 1;
        }
        return uVar4;
      }
      uVar7 = (ulong)local_57;
      uVar3 = <core[edc4a680d2d7e122]::fmt::Formatter>::pad(param_2,&DAT_0022ed8f,3);
      if ((uVar3 & 1) != 0) {
        return 1;
      }
      if ((bVar2 & 1) == 0) {
        return 0;
      }
      uVar3 = uVar1 + uVar7;
      if (CARRY8(uVar1,uVar7)) {
LAB_004cfafc:
                    /* WARNING: Subroutine does not return */
        core[edc4a680d2d7e122]::panicking::panic_const::panic_const_add_overflow
                  (&PTR_s_prebuilts_rust_toolchain_linux_x_00f718e0);
      }
      uVar1 = uVar5 - uVar3;
      if (uVar5 < uVar3) {
        core[edc4a680d2d7e122]::slice::index::slice_index_fail
                  (uVar3,uVar5,uVar5,&PTR_s_prebuilts_rust_toolchain_linux_x_00f718f8);
        goto LAB_004cfafc;
      }
      lVar6 = lVar6 + uVar3;
      uVar5 = uVar1;
    } while (uVar1 != 0);
  }
  return 0;
}


/* ==== dbfwPlusScoDumpNative @ 005190fc size 204 :: dbfwPlusScoDumpNative */

/* android::dbfwPlusScoDumpNative(_JNIEnv*, _jobject*, unsigned char) */

void android::dbfwPlusScoDumpNative(_JNIEnv *param_1,_jobject *param_2,uchar param_3)

{
  long lVar1;
  bool bVar2;
  int iVar3;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  undefined8 local_58 [3];
  undefined4 local_40 [2];
  char *local_38;
  char *pcStack_30;
  long local_28;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_28 = *(long *)(lVar1 + 0x28);
  local_40[0] = 0xacf;
  local_38 = 
  "packages/modules/Bluetooth/android/app/jni/com_android_bluetooth_btservice_AdapterService.cpp";
  pcStack_30 = "dbfwPlusScoDumpNative";
  local_58[0] = 0;
  bluetooth::log_internal::vlog(2,"BluetoothServiceJni",local_40,&DAT_0013f82c,0,local_58);
  if (DAT_00faedb8 == 0) {
    bVar2 = false;
  }
  else {
    iVar3 = (*(code *)PTR_dbfw_plus_sco_dump_00faae30)(param_3 != '\0');
    bVar2 = iVar3 == 0;
  }
  if (*(long *)(lVar1 + 0x28) == local_28) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(bVar2);
}


/* ==== dbfwPlusScoDebugInfoNative @ 005191c8 size 220 :: dbfwPlusScoDebugInfoNative */

/* android::dbfwPlusScoDebugInfoNative(_JNIEnv*, _jobject*, unsigned char, int) */

void android::dbfwPlusScoDebugInfoNative
               (_JNIEnv *param_1,_jobject *param_2,uchar param_3,int param_4)

{
  long lVar1;
  bool bVar2;
  int iVar3;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  undefined8 local_68 [3];
  undefined4 local_50 [2];
  char *local_48;
  char *pcStack_40;
  long local_38;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_38 = *(long *)(lVar1 + 0x28);
  local_50[0] = 0xad7;
  local_48 = 
  "packages/modules/Bluetooth/android/app/jni/com_android_bluetooth_btservice_AdapterService.cpp";
  pcStack_40 = "dbfwPlusScoDebugInfoNative";
  local_68[0] = 0;
  bluetooth::log_internal::vlog(2,"BluetoothServiceJni",local_50,&DAT_0013f82c,0,local_68);
  if (DAT_00faedb8 == 0) {
    bVar2 = false;
  }
  else {
    iVar3 = (*(code *)PTR_dbfw_plus_sco_debug_info_00faae38)(param_3 != '\0',param_4);
    bVar2 = iVar3 == 0;
  }
  if (*(long *)(lVar1 + 0x28) == local_38) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(bVar2);
}


/* ==== parseParams @ 00528758 size 1216 :: isScannable */

/* android::parseParams(_JNIEnv*, _jobject*) */

void __thiscall android::parseParams(android *this,_JNIEnv *param_1,_jobject *param_2)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  char cVar4;
  char cVar5;
  char cVar6;
  char cVar7;
  char cVar8;
  char cVar9;
  undefined1 uVar10;
  undefined1 uVar11;
  undefined1 uVar12;
  undefined1 uVar13;
  char cVar14;
  char cVar15;
  undefined1 uVar16;
  char cVar17;
  uint uVar18;
  undefined8 uVar19;
  undefined8 uVar20;
  _jstring *p_Var21;
  ushort uVar22;
  ushort *in_x8;
  long lVar23;
  code *pcVar24;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  
  *in_x18 = unaff_x30;
  lVar23 = *(long *)this;
  in_x8[0] = 0;
  in_x8[1] = 0;
  in_x8[2] = 0;
  in_x8[3] = 0;
  in_x8[4] = 0;
  in_x8[5] = 0;
  in_x8[6] = 0;
  in_x8[7] = 0;
  pcVar24 = *(code **)(lVar23 + 0xf8);
  in_x8[0xc] = 0;
  in_x8[0xd] = 0;
  in_x8[8] = 0;
  in_x8[9] = 0;
  in_x8[10] = 0;
  in_x8[0xb] = 0;
  uVar19 = (*pcVar24)();
  uVar20 = (**(code **)(*(long *)this + 0x108))(this,uVar19,"isConnectable",&DAT_001773c4);
  cVar4 = _JNIEnv::CallBooleanMethod(this,param_1,uVar20);
  uVar20 = (**(code **)(*(long *)this + 0x108))(this,uVar19,"isDiscoverable",&DAT_001773c4);
  cVar5 = _JNIEnv::CallBooleanMethod(this,param_1,uVar20);
  uVar20 = (**(code **)(*(long *)this + 0x108))(this,uVar19,"isScannable",&DAT_001773c4);
  cVar6 = _JNIEnv::CallBooleanMethod(this,param_1,uVar20);
  uVar20 = (**(code **)(*(long *)this + 0x108))(this,uVar19,"isLegacy",&DAT_001773c4);
  cVar7 = _JNIEnv::CallBooleanMethod(this,param_1,uVar20);
  uVar20 = (**(code **)(*(long *)this + 0x108))(this,uVar19,"isAnonymous",&DAT_001773c4);
  cVar8 = _JNIEnv::CallBooleanMethod(this,param_1,uVar20);
  uVar20 = (**(code **)(*(long *)this + 0x108))(this,uVar19,"includeTxPower",&DAT_001773c4);
  cVar9 = _JNIEnv::CallBooleanMethod(this,param_1,uVar20);
  uVar20 = (**(code **)(*(long *)this + 0x108))(this,uVar19,"getPrimaryPhy",&DAT_001bf1e4);
  uVar10 = _JNIEnv::CallIntMethod(this,param_1,uVar20);
  uVar20 = (**(code **)(*(long *)this + 0x108))(this,uVar19,"getSecondaryPhy",&DAT_001bf1e4);
  uVar11 = _JNIEnv::CallIntMethod(this,param_1,uVar20);
  uVar20 = (**(code **)(*(long *)this + 0x108))(this,uVar19,"getInterval",&DAT_001bf1e4);
  uVar18 = _JNIEnv::CallIntMethod(this,param_1,uVar20);
  uVar20 = (**(code **)(*(long *)this + 0x108))(this,uVar19,"getTxPowerLevel",&DAT_001bf1e4);
  uVar12 = _JNIEnv::CallIntMethod(this,param_1,uVar20);
  uVar20 = (**(code **)(*(long *)this + 0x108))(this,uVar19,"getOwnAddressType",&DAT_001bf1e4);
  uVar13 = _JNIEnv::CallIntMethod(this,param_1,uVar20);
  uVar20 = (**(code **)(*(long *)this + 0x108))(this,uVar19,"isDirected",&DAT_001773c4);
  cVar14 = _JNIEnv::CallBooleanMethod(this,param_1,uVar20);
  uVar20 = (**(code **)(*(long *)this + 0x108))(this,uVar19,"isHighDutyCycle",&DAT_001773c4);
  cVar15 = _JNIEnv::CallBooleanMethod(this,param_1,uVar20);
  uVar20 = (**(code **)(*(long *)this + 0x108))(this,uVar19,"getPeerA","()Ljava/lang/String;");
  p_Var21 = (_jstring *)_JNIEnv::CallObjectMethod(this,param_1,uVar20);
  uVar20 = (**(code **)(*(long *)this + 0x108))(this,uVar19,"getPeerAddressType",&DAT_001bf1e4);
  uVar16 = _JNIEnv::CallIntMethod(this,param_1,uVar20);
  uVar19 = (**(code **)(*(long *)this + 0x108))(this,uVar19,"isStrictIntervalEnabled",&DAT_001773c4)
  ;
  cVar17 = _JNIEnv::CallBooleanMethod(this,param_1,uVar19);
  *(undefined1 *)(in_x8 + 8) = 0;
  *(undefined1 *)(in_x8 + 6) = 7;
  *(undefined1 *)((long)in_x8 + 0xd) = uVar12;
  uVar22 = 2;
  if (cVar4 != '\0') {
    uVar22 = 3;
  }
  uVar1 = (ushort)(cVar4 != '\0');
  if (cVar6 != '\0') {
    uVar1 = uVar22;
  }
  if (cVar14 != '\0') {
    uVar1 = uVar1 | 4;
  }
  if (cVar15 != '\0') {
    uVar1 = uVar1 | 8;
  }
  if (cVar7 != '\0') {
    uVar1 = uVar1 | 0x10;
  }
  if (cVar8 != '\0') {
    uVar1 = uVar1 | 0x20;
  }
  *(undefined1 *)(in_x8 + 7) = uVar10;
  *(undefined1 *)((long)in_x8 + 0xf) = uVar11;
  if (cVar9 != '\0') {
    uVar1 = uVar1 | 0x40;
  }
  uVar2 = uVar18;
  if (0xfffffe < uVar18) {
    uVar2 = 0xffffff;
  }
  *in_x8 = uVar1;
  if (0xffffcc < uVar18) {
    uVar18 = 0xffffcd;
  }
  uVar3 = uVar18 + 0x32;
  if (cVar17 != '\0') {
    uVar3 = uVar2;
    uVar18 = uVar2;
  }
  *(uint *)(in_x8 + 2) = uVar18;
  *(uint *)(in_x8 + 4) = uVar3;
  *(undefined1 *)((long)in_x8 + 0x11) = uVar13;
  if (p_Var21 == (_jstring *)0x0) {
    in_x8[0xb] = 0;
    in_x8[9] = 0;
    in_x8[10] = 0;
  }
  else {
    uVar19 = str2addr((_JNIEnv *)this,p_Var21);
    *(int *)(in_x8 + 9) = (int)uVar19;
    in_x8[0xb] = (ushort)((ulong)uVar19 >> 0x20);
  }
  *(undefined1 *)(in_x8 + 0xc) = uVar16;
  *(bool *)((long)in_x8 + 0x19) = cVar5 != '\0';
  return;
}


/* ==== getOwnAddressCb @ 00529020 size 432 :: getOwnAddressCb */

/* android::getOwnAddressCb(unsigned char, unsigned char, RawAddress) */

void android::getOwnAddressCb(undefined1 param_1,undefined1 param_2,ulong param_3)

{
  long lVar1;
  char cVar2;
  int extraout_w1;
  char *pcVar3;
  char *pcVar4;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  _JNIEnv *local_b0;
  long *local_a8;
  undefined8 local_a0;
  long **pplStack_98;
  undefined8 local_90;
  char local_88 [8];
  char *local_80;
  char *pcStack_78;
  long *local_70;
  long local_68;
  undefined8 uStack_60;
  long local_48;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_48 = *(long *)(lVar1 + 0x28);
  std::__shared_mutex_base::lock_shared((__shared_mutex_base *)&DAT_00faf1e8);
  local_b0 = (_JNIEnv *)0x0;
  local_a8 = (long *)0x0;
  CallbackEnv::CallbackEnv((CallbackEnv *)&local_b0,"getOwnAddressCb");
  if (DAT_00faf350 != 0) {
    local_70 = (long *)0x0;
    local_68 = 0;
    addressToJString(&local_70,&local_b0,param_3 & 0xffffffffffff);
    _JNIEnv::CallVoidMethod(local_b0,DAT_00faf350,DAT_00faf310,param_1,param_2,local_68);
    if (local_68 != 0) {
      (**(code **)(*local_70 + 0xb8))();
    }
  }
  cVar2 = (**(code **)(*(long *)local_b0 + 0x720))();
  if (cVar2 != '\0') {
    local_88[0] = '5';
    local_88[1] = '\0';
    local_88[2] = '\0';
    local_88[3] = '\0';
    local_70 = (long *)"(nullptr)";
    if (local_a8 != (long *)0x0) {
      local_70 = local_a8;
    }
    local_80 = "packages/modules/Bluetooth/android/app/jni/com_android_bluetooth.h";
    pcStack_78 = "~CallbackEnv";
    pplStack_98 = &local_70;
    local_a0 = 1;
    pcVar4 = "An exception was thrown by callback \'{}\'.";
    pcVar3 = local_88;
    uStack_60 = 0xc;
    local_68 = 0;
    local_90 = 0xc;
    bluetooth::log_internal::vlog
              (6,"BtGatt.JNI",pcVar3,"An exception was thrown by callback \'{}\'.",0x29,&local_a0);
    ::jniLogException(local_b0,extraout_w1,pcVar3,(_jthrowable *)pcVar4);
    (**(code **)(*(long *)local_b0 + 0x88))();
  }
  (**(code **)(*(long *)local_b0 + 0xa0))(local_b0,0);
  std::__shared_mutex_base::unlock_shared((__shared_mutex_base *)&DAT_00faf1e8);
  if (*(long *)(lVar1 + 0x28) == local_48) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== setIsScoManagedByAudioNative @ 005387ec size 364 :: setIsScoManagedByAudioNative */

/* android::setIsScoManagedByAudioNative(_JNIEnv*, _jobject*, unsigned char) */

bool android::setIsScoManagedByAudioNative(_JNIEnv *param_1,_jobject *param_2,uchar param_3)

{
  long lVar1;
  bool bVar2;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  undefined8 local_90;
  undefined8 uStack_88;
  undefined8 local_80;
  undefined1 **ppuStack_78;
  undefined8 local_70;
  undefined8 local_68;
  char *local_60;
  char *pcStack_58;
  undefined1 *local_50;
  code *local_48;
  char *pcStack_40;
  long local_28;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_28 = *(long *)(lVar1 + 0x28);
  std::shared_timed_mutex::lock_shared((shared_timed_mutex *)&DAT_00faf838);
  if (DAT_00fafa20 == (long *)0x0) {
    local_50 = (undefined1 *)CONCAT44(local_50._4_4_,0x355);
    local_48 = (code *)0x1311a7;
    pcStack_40 = "setIsScoManagedByAudioNative";
    local_68 = 0;
    bluetooth::log_internal::vlog
              (5,"BluetoothHeadsetServiceJni",&local_50,"sBluetoothHfpInterface is null",0x1e,
               &local_68);
    bVar2 = false;
  }
  else {
    local_90 = 0;
    uStack_88 = 0;
    (**(code **)(*DAT_00fafa20 + 200))(&local_90,DAT_00fafa20,param_3 == '\x01');
    if ((short)local_90 == 0) {
      bVar2 = true;
    }
    else {
      local_68 = CONCAT44(local_68._4_4_,0x35a);
      local_60 = "packages/modules/Bluetooth/android/app/jni/com_android_bluetooth_hfp.cpp";
      pcStack_58 = "setIsScoManagedByAudioNative";
      ppuStack_78 = &local_50;
      local_48 = 
      _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I8BtStatusEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
      ;
      pcStack_40 = (char *)0xf;
      local_80 = 1;
      local_70 = 0xf;
      local_50 = (undefined1 *)&local_90;
      bluetooth::log_internal::vlog
                (6,"BluetoothHeadsetServiceJni",&local_68,
                 "Failed HF set is sco managed by audio, status: {}",0x31,&local_80);
      bVar2 = (short)local_90 == 0;
    }
  }
  std::shared_timed_mutex::unlock_shared((shared_timed_mutex *)&DAT_00faf838);
  if (*(long *)(lVar1 + 0x28) == local_28) {
    return bVar2;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== ProcessGattCtpNotification @ 00675a18 size 3476 :: processCommonCtpFailed */

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Unknown calling convention: __rustcall */
/* _GLOBAL__N_1::LeAudioGroupStateMachineImpl::ProcessGattCtpNotification */

void __rustcall
_GLOBAL__N_1::LeAudioGroupStateMachineImpl::ProcessGattCtpNotification
          (long param_1,LeAudioDeviceGroup *param_2,char *param_3,undefined8 param_4,
          undefined4 param_5)

{
  uchar *puVar1;
  undefined4 uVar2;
  LeAudioDeviceGroup LVar3;
  byte bVar4;
  long lVar5;
  bool bVar6;
  uint uVar7;
  byte *pbVar8;
  code *pcVar9;
  ostream *poVar10;
  undefined8 *puVar11;
  undefined8 uVar12;
  LeAudioDevice *pLVar13;
  void *pvVar14;
  AseState *extraout_x1;
  AseState *extraout_x1_00;
  AseState *extraout_x1_01;
  AseState *pAVar15;
  AseState *extraout_x1_02;
  AseState *extraout_x1_03;
  undefined8 uVar16;
  ulong uVar17;
  long *plVar18;
  undefined8 *in_x18;
  byte *pbVar19;
  uint uVar20;
  uchar *puVar21;
  long *plVar22;
  char *pcVar23;
  char *pcVar24;
  undefined8 unaff_x30;
  byte local_3b8;
  undefined7 uStack_3b7;
  ulong local_3b0;
  undefined7 *local_3a8;
  LeAudioDeviceGroup local_3a0 [4];
  LeAudioDeviceGroup local_39c [4];
  byte local_398;
  undefined7 uStack_397;
  ulong local_390;
  char *local_388;
  ulong local_380;
  undefined8 *local_378;
  char *local_370;
  undefined8 local_368;
  char *local_360;
  char *local_358;
  undefined **local_350;
  undefined8 local_348;
  undefined **ppuStack_340;
  undefined **local_338;
  undefined8 uStack_330;
  long local_328;
  undefined8 uStack_320;
  ulong local_318;
  long lStack_310;
  ulong local_308;
  undefined8 uStack_300;
  ulong local_2f8;
  undefined8 uStack_2f0;
  void *local_2e8;
  ulong uStack_2e0;
  undefined8 local_2d8;
  undefined **ppuStack_2d0;
  undefined8 local_2c8;
  undefined8 uStack_2c0;
  undefined8 local_2b8;
  undefined8 uStack_2b0;
  undefined8 local_2a8;
  undefined8 uStack_2a0;
  undefined8 local_298;
  undefined8 uStack_290;
  undefined8 local_288;
  undefined8 uStack_280;
  undefined8 local_278;
  undefined8 uStack_270;
  undefined8 local_268;
  undefined8 uStack_260;
  undefined8 local_258;
  undefined8 uStack_250;
  undefined8 local_248;
  undefined8 uStack_240;
  undefined **local_238;
  char *local_230;
  undefined **ppuStack_228;
  undefined **local_220;
  undefined8 uStack_218;
  long local_210;
  undefined8 uStack_208;
  ulong local_200;
  long lStack_1f8;
  ulong local_1f0;
  undefined8 uStack_1e8;
  ulong local_1e0;
  undefined8 uStack_1d8;
  void *local_1d0;
  ulong uStack_1c8;
  undefined8 local_1c0;
  undefined **ppuStack_1b8;
  undefined8 local_1b0;
  undefined8 uStack_1a8;
  undefined8 local_1a0;
  undefined8 uStack_198;
  undefined8 local_190;
  undefined8 uStack_188;
  undefined8 local_180;
  undefined8 uStack_178;
  undefined8 local_170;
  undefined8 uStack_168;
  undefined8 local_160;
  undefined8 uStack_158;
  undefined8 local_150;
  undefined8 uStack_148;
  undefined8 local_140;
  undefined8 uStack_138;
  undefined8 local_130;
  undefined8 uStack_128;
  undefined8 local_120;
  code *pcStack_118;
  char *local_110;
  code *pcStack_108;
  char *local_100;
  ulong uStack_f8;
  undefined7 *local_f0;
  ulong local_e8;
  ulong local_e0;
  undefined8 uStack_d8;
  ulong local_d0;
  undefined8 local_c8;
  ulong local_c0;
  undefined8 uStack_b8;
  ulong local_b0;
  undefined8 uStack_a8;
  ulong local_a0;
  undefined8 local_98;
  undefined8 uStack_90;
  long local_78;
  
  *in_x18 = unaff_x30;
  lVar5 = tpidr_el0;
  local_78 = *(long *)(lVar5 + 0x28);
  pbVar8 = (byte *)FUN_00f62c00(0x20);
  pbVar8[8] = 0;
  pbVar8[9] = 0;
  pbVar8[10] = 0;
  pbVar8[0xb] = 0;
  pbVar8[0xc] = 0;
  pbVar8[0xd] = 0;
  pbVar8[0xe] = 0;
  pbVar8[0xf] = 0;
  pbVar8[0] = 0;
  pbVar8[1] = 0;
  pbVar8[2] = 0;
  pbVar8[3] = 0;
  pbVar8[4] = 0;
  pbVar8[5] = 0;
  pbVar8[6] = 0;
  pbVar8[7] = 0;
  pbVar8[0x18] = 0;
  pbVar8[0x19] = 0;
  pbVar8[0x1a] = 0;
  pbVar8[0x1b] = 0;
  pbVar8[0x1c] = 0;
  pbVar8[0x1d] = 0;
  pbVar8[0x1e] = 0;
  pbVar8[0x1f] = 0;
  pbVar8[0x10] = 0;
  pbVar8[0x11] = 0;
  pbVar8[0x12] = 0;
  pbVar8[0x13] = 0;
  pbVar8[0x14] = 0;
  pbVar8[0x15] = 0;
  pbVar8[0x16] = 0;
  pbVar8[0x17] = 0;
  uVar7 = bluetooth::le_audio::client_parser::ascs::ParseAseCtpNotification(pbVar8,param_5,param_4);
  if (param_2 == (LeAudioDeviceGroup *)0x0) {
    local_238 = (undefined **)CONCAT44(local_238._4_4_,0x234);
    local_230 = "packages/modules/Bluetooth/system/bta/le_audio/state_machine.cc";
    ppuStack_228 = (undefined **)0x18857d;
    local_350 = (undefined **)0x0;
    bluetooth::log_internal::vlog
              (5,"bluetooth",&local_238,"Notification received to invalid group",0x26,&local_350);
    pvVar14 = *(void **)(pbVar8 + 8);
    goto joined_r0x00675d6c;
  }
  uStack_138 = 0;
  local_140 = 0;
  uStack_148 = 0;
  local_150 = 0;
  uStack_128 = 0;
  local_130 = 0;
  uStack_158 = 0;
  local_160 = 0;
  uStack_168 = 0;
  local_170 = 0;
  uStack_178 = 0;
  local_180 = 0;
  uStack_188 = 0;
  local_190 = 0;
  uStack_198 = 0;
  local_1a0 = 0;
  uStack_1a8 = 0;
  local_1b0 = 0;
  local_1c0 = 0;
  uStack_1c8 = 0;
  local_1d0 = (void *)0x0;
  uStack_1d8 = 0;
  local_1e0 = 0;
  uStack_1e8 = 0;
  local_1f0 = 0;
  lStack_1f8 = 0;
  local_200 = 0;
  uStack_208 = 0;
  local_210 = 0;
  uStack_218 = 0;
  local_220 = (undefined **)0x0;
  ppuStack_1b8 = &PTR__istream_00f68b08;
  local_230 = (char *)0x0;
  local_238 = &PTR__istream_00f68ae0;
  ppuStack_228 = &PTR__stringstream_00f689c8;
  std::ios_base::init((ios_base *)&ppuStack_1b8,&local_220);
  local_130 = 0;
                    /* WARNING: Ignoring partial resolution of indirect */
  uStack_128._0_4_ = 0xffffffff;
  local_238 = &PTR__stringstream_00f689a0;
  ppuStack_228 = &PTR__stringstream_00f689c8;
  local_220 = &PTR__streambuf_00f68750;
  ppuStack_1b8 = &PTR__stringstream_00f689f0;
  std::locale::locale((locale *)&uStack_218);
  uStack_1e8 = 0;
  local_1f0 = 0;
  lStack_1f8 = 0;
  local_200 = 0;
  uStack_208 = 0;
  local_210 = 0;
  uStack_1d8 = 0;
  local_1e0 = 0;
  uStack_1c8 = 0;
  local_1d0 = (void *)0x0;
  local_1c0 = CONCAT44(local_1c0._4_4_,0x18);
  local_220 = &PTR__stringbuf_00f687d0;
  std::stringbuf::__init_buf_ptrs_abi_nn220000_((stringbuf *)&local_220);
  uStack_250 = 0;
  local_258 = 0;
  uStack_240 = 0;
  local_248 = 0;
  uStack_260 = 0;
  local_268 = 0;
  uStack_270 = 0;
  local_278 = 0;
  uStack_280 = 0;
  local_288 = 0;
  uStack_290 = 0;
  local_298 = 0;
  uStack_2a0 = 0;
  local_2a8 = 0;
  uStack_2b0 = 0;
  local_2b8 = 0;
  uStack_2c0 = 0;
  local_2c8 = 0;
  local_2d8 = 0;
  uStack_2e0 = 0;
  local_2e8 = (void *)0x0;
  uStack_2f0 = 0;
  local_2f8 = 0;
  uStack_300 = 0;
  local_308 = 0;
  lStack_310 = 0;
  local_318 = 0;
  uStack_320 = 0;
  local_328 = 0;
  uStack_330 = 0;
  local_338 = (undefined **)0x0;
  ppuStack_2d0 = &PTR__istream_00f68b08;
  local_348 = 0;
  local_350 = &PTR__istream_00f68ae0;
  ppuStack_340 = &PTR__stringstream_00f689c8;
  std::ios_base::init((ios_base *)&ppuStack_2d0,&local_338);
  local_248 = 0;
                    /* WARNING: Ignoring partial resolution of indirect */
  uStack_240._0_4_ = 0xffffffff;
  local_350 = &PTR__stringstream_00f689a0;
  ppuStack_340 = &PTR__stringstream_00f689c8;
  local_338 = &PTR__streambuf_00f68750;
  ppuStack_2d0 = &PTR__stringstream_00f689f0;
  std::locale::locale((locale *)&uStack_330);
  local_2d8 = CONCAT44(local_2d8._4_4_,0x18);
  uStack_300 = 0;
  local_308 = 0;
  lStack_310 = 0;
  local_318 = 0;
  uStack_320 = 0;
  local_328 = 0;
  uStack_2f0 = 0;
  local_2f8 = 0;
  uStack_2e0 = 0;
  local_2e8 = (void *)0x0;
  local_338 = &PTR__stringbuf_00f687d0;
  std::stringbuf::__init_buf_ptrs_abi_nn220000_((stringbuf *)&local_338);
  if ((ulong)*pbVar8 < 9) {
    pcVar23 = (&PTR_s_UnUsed_00f9cd70)[*pbVar8];
    pcVar9 = (code *)strlen(pcVar23);
    if ((code *)0xfffffffffffffff6 < pcVar9) goto LAB_006767a4;
    if (pcVar9 < (code *)0x17) {
      pcVar24 = (char *)((ulong)&local_120 | 1);
      local_120 = (char *)CONCAT71(local_120._1_7_,(char)((int)pcVar9 << 1));
    }
    else {
      uVar17 = 0x1a;
      if (((ulong)pcVar9 | 7) != 0x17) {
        uVar17 = ((ulong)pcVar9 | 7) + 1;
      }
      pcVar24 = (char *)FUN_00f62c00(uVar17);
      local_120 = (char *)(uVar17 | 1);
      pcStack_118 = pcVar9;
      local_110 = pcVar24;
    }
    memmove(pcVar24,pcVar23,(size_t)pcVar9);
    pcVar24[(long)pcVar9] = '\0';
    uVar17 = (ulong)local_120 & 0xff;
  }
  else {
    uVar17 = 0xe;
    local_120 = (char *)0x4e574f4e4b4e550e;
    pcStack_118 = (code *)((ulong)pcStack_118 & 0xffffffffffffff00);
  }
  pcVar9 = pcStack_118;
  pcVar23 = local_110;
  if ((uVar17 & 1) == 0) {
    pcVar9 = (code *)(uVar17 >> 1);
    pcVar23 = (char *)((long)&local_120 + 1);
  }
  poVar10 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                      ((ostream *)&ppuStack_228,pcVar23,(ulong)pcVar9);
  poVar10 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>(poVar10," (",2)
  ;
  loghex<unsigned_char>(*pbVar8);
  pcVar23 = local_360;
  pcVar24 = local_358;
  if ((local_368 & 1) == 0) {
    pcVar23 = (char *)(local_368 >> 1 & 0x7f);
    pcVar24 = (char *)((long)&local_368 + 1);
  }
  poVar10 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                      (poVar10,pcVar24,(ulong)pcVar23);
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>(poVar10,")",1);
  if ((local_368 & 1) != 0) {
    operator_delete(local_358,local_368 & 0xfffffffffffffffe);
  }
  if (((ulong)local_120 & 1) != 0) {
    operator_delete(local_110,(ulong)local_120 & 0xfffffffffffffffe);
  }
  puVar21 = *(uchar **)(pbVar8 + 8);
  puVar1 = *(uchar **)(pbVar8 + 0x10);
  if (puVar21 != puVar1) {
    do {
      loghex<unsigned_char>(*puVar21);
      puVar11 = (undefined8 *)std::string::insert((string *)&local_368,0,"ASE ID ",7);
      pcStack_118 = (code *)puVar11[1];
      local_120 = (char *)*puVar11;
      local_110 = (char *)puVar11[2];
      puVar11[1] = 0;
      puVar11[2] = 0;
      *puVar11 = 0;
      pcVar9 = (code *)((ulong)local_120 >> 1 & 0x7f);
      pcVar23 = (char *)((ulong)&local_120 | 1);
      if (((ulong)local_120 & 1) != 0) {
        pcVar9 = pcStack_118;
        pcVar23 = local_110;
      }
      poVar10 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                          ((ostream *)&ppuStack_340,pcVar23,(ulong)pcVar9);
      poVar10 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                          (poVar10," resp ",6);
      loghex<unsigned_char>(puVar21[1]);
      puVar11 = (undefined8 *)(local_380 >> 1 & 0x7f);
      pcVar23 = (char *)((ulong)&local_380 | 1);
      if ((local_380 & 1) != 0) {
        puVar11 = local_378;
        pcVar23 = local_370;
      }
      poVar10 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                          (poVar10,pcVar23,(ulong)puVar11);
      poVar10 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                          (poVar10," reason ",8);
      loghex<unsigned_char>(puVar21[2]);
      uVar17 = (ulong)(local_398 >> 1);
      pcVar23 = (char *)((ulong)&local_398 | 1);
      if ((local_398 & 1) != 0) {
        uVar17 = local_390;
        pcVar23 = local_388;
      }
      poVar10 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                          (poVar10,pcVar23,uVar17);
      std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>(poVar10,", ",2);
      if ((local_398 & 1) != 0) {
        operator_delete(local_388,CONCAT71(uStack_397,local_398) & 0xfffffffffffffffe);
      }
      if ((local_380 & 1) != 0) {
        operator_delete(local_370,local_380 & 0xfffffffffffffffe);
      }
      if (((ulong)local_120 & 1) != 0) {
        operator_delete(local_110,(ulong)local_120 & 0xfffffffffffffffe);
      }
      if ((local_368 & 1) != 0) {
        operator_delete(local_358,local_368 & 0xfffffffffffffffe);
      }
      puVar21 = puVar21 + 3;
    } while (puVar21 != puVar1);
  }
  plVar22 = *(long **)(param_1 + 0x18);
  uVar2 = *(undefined4 *)param_2;
  if (((uint)local_1c0 >> 4 & 1) == 0) {
    if (((uint)local_1c0 >> 3 & 1) != 0) {
      plVar18 = &local_210;
      uVar17 = local_200;
      goto LAB_006760a0;
    }
    pvVar14 = (void *)0x0;
    pcVar9 = (code *)0x0;
LAB_006760b8:
    pcVar23 = (char *)((ulong)&local_120 | 1);
    local_120 = (char *)CONCAT71(local_120._1_7_,(char)((int)pcVar9 << 1));
  }
  else {
    if (uStack_1c8 < local_1f0) {
      uStack_1c8 = local_1f0;
    }
    plVar18 = &lStack_1f8;
    uVar17 = uStack_1c8;
LAB_006760a0:
    pvVar14 = (void *)*plVar18;
    pcVar9 = (code *)(uVar17 - (long)pvVar14);
    if ((code *)0xfffffffffffffff6 < pcVar9) goto LAB_006767a4;
    if (pcVar9 < (code *)0x17) goto LAB_006760b8;
    uVar17 = 0x1a;
    if (((ulong)pcVar9 | 7) != 0x17) {
      uVar17 = ((ulong)pcVar9 | 7) + 1;
    }
    pcVar23 = (char *)FUN_00f62c00(uVar17);
    local_120 = (char *)(uVar17 | 1);
    pcStack_118 = pcVar9;
    local_110 = pcVar23;
  }
  memmove(pcVar23,pvVar14,(size_t)pcVar9);
  pcVar23[(long)pcVar9] = '\0';
  if (((uint)local_2d8 >> 4 & 1) == 0) {
    if (((uint)local_2d8 >> 3 & 1) != 0) {
      plVar18 = &local_328;
      uVar17 = local_318;
      goto LAB_00676154;
    }
    pvVar14 = (void *)0x0;
    pcVar23 = (char *)0x0;
LAB_0067616c:
    pcVar24 = (char *)((ulong)&local_368 | 1);
    local_368 = CONCAT71(local_368._1_7_,(char)((int)pcVar23 << 1));
  }
  else {
    if (uStack_2e0 < local_308) {
      uStack_2e0 = local_308;
    }
    plVar18 = &lStack_310;
    uVar17 = uStack_2e0;
LAB_00676154:
    pvVar14 = (void *)*plVar18;
    pcVar23 = (char *)(uVar17 - (long)pvVar14);
    if ((char *)0xfffffffffffffff6 < pcVar23) {
LAB_006767a4:
                    /* WARNING: Subroutine does not return */
      std::string::__throw_length_error_abi_nn220000_();
    }
    if (pcVar23 < (char *)0x17) goto LAB_0067616c;
    uVar17 = 0x1a;
    if (((ulong)pcVar23 | 7) != 0x17) {
      uVar17 = ((ulong)pcVar23 | 7) + 1;
    }
    pcVar24 = (char *)FUN_00f62c00(uVar17);
    local_368 = uVar17 | 1;
    local_360 = pcVar23;
    local_358 = pcVar24;
  }
  memmove(pcVar24,pvVar14,(size_t)pcVar23);
  pcVar24[(long)pcVar23] = '\0';
  (**(code **)(*plVar22 + 0x18))(plVar22,&DAT_00faa290,uVar2,&DAT_00291a56,&local_120,&local_368);
  pAVar15 = extraout_x1;
  if ((local_368 & 1) != 0) {
    operator_delete(local_358,local_368 & 0xfffffffffffffffe);
    pAVar15 = extraout_x1_00;
  }
  if (((ulong)local_120 & 1) != 0) {
    operator_delete(local_110,(ulong)local_120 & 0xfffffffffffffffe);
    pAVar15 = extraout_x1_01;
  }
  LVar3 = param_2[0x172];
  local_39c[0] = param_2[0x170];
  local_3a0[0] = param_2[0x171];
  if ((LVar3 == (LeAudioDeviceGroup)0x1) && (local_39c[0] == (LeAudioDeviceGroup)0x4)) {
    if ((uVar7 & 1) != 0) {
      pbVar19 = *(byte **)(pbVar8 + 8);
LAB_00676260:
      if (pbVar19 != *(byte **)(pbVar8 + 0x10)) {
        local_e0 = (ulong)pbVar19[1];
        if (pbVar19[1] == 0) goto LAB_0067625c;
        bVar4 = *pbVar8;
        if (bVar4 - 1 < 7) {
          uVar17 = PrepareAndSendRelease(param_1,param_3);
          uVar7 = bluetooth::le_audio::LeAudioDeviceGroup::GetNumOfActiveDevices(param_2);
          pLVar13 = (LeAudioDevice *)
                    bluetooth::le_audio::LeAudioDeviceGroup::GetFirstActiveDevice(param_2);
          if (pLVar13 == (LeAudioDevice *)0x0) {
            uVar20 = 0;
          }
          else {
            uVar20 = 0;
            do {
              if (pLVar13[0xfa] == (LeAudioDevice)0x8) {
                uVar20 = uVar20 + 1;
              }
              pLVar13 = (LeAudioDevice *)
                        bluetooth::le_audio::LeAudioDeviceGroup::GetNextActiveDevice
                                  (param_2,pLVar13);
            } while (pLVar13 != (LeAudioDevice *)0x0);
          }
          local_368 = CONCAT44(local_368._4_4_,0x215);
          local_360 = "packages/modules/Bluetooth/system/bta/le_audio/state_machine.cc";
          local_358 = "processCommonCtpFailed";
          local_378 = &local_120;
          pcStack_118 = 
          _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
          ;
          local_110 = (char *)(ulong)*pbVar19;
          uStack_f8 = 0;
          pcStack_108 = (code *)0x0;
          local_f0 = (undefined7 *)(ulong)(byte)param_3[0xfa];
          local_a0 = (ulong)uVar20;
          local_e8 = 0;
          local_e0 = (ulong)pbVar19[1];
          uStack_d8 = 0;
          local_d0 = (ulong)pbVar19[2];
          local_380 = 9;
          local_c8 = 0;
          local_c0 = uVar17 & 1;
          uStack_b8 = 0;
          uStack_a8 = 0;
          local_98 = 0;
          uStack_90 = 0x3184c6318cf;
          local_370 = (char *)0x3184c6318cf;
          local_120 = param_3;
          local_100 = (char *)(ulong)bVar4;
          local_b0 = (ulong)uVar7;
          bluetooth::log_internal::vlog
                    (6,"bluetooth",&local_368,
                     "Releasing ASE due to control point error for {}, ase: {}, opcode: {:#x}, last_ase_ctp_command_sent: {:#x}, error: {:#x}, reason: {:#x}. release_sent_to_remote: {}, active_devices: {}, releasing_devices: {}"
                     ,0xcd,&local_380);
          if (uVar20 == 0 && uVar7 == 0) {
            ClearGroup(param_1,param_2,1);
LAB_00676784:
            plVar22 = (long *)bluetooth::le_audio::LeAudioHealthStatus::Get();
            if (plVar22 != (long *)0x0) {
              (**(code **)(*plVar22 + 0x20))(plVar22,param_2,2);
            }
          }
          else if ((uVar7 != 0) && (uVar20 == uVar7)) {
            bluetooth::le_audio::LeAudioDeviceGroup::SetTargetState(param_2,0);
            (**(code **)(**(long **)(param_1 + 8) + 0x10))
                      (*(long **)(param_1 + 8),*(undefined4 *)param_2,2);
            goto LAB_00676784;
          }
          goto LAB_0067646c;
        }
        if (bVar4 != 8) goto LAB_0067625c;
        local_368 = CONCAT44(local_368._4_4_,0x200);
        local_358 = "processReleaseCtpFailed";
        pcVar23 = 
        "Release failed for group_id: {},  {}, ase: {}, last_ase_ctp_command_sent: {:#x}, error: {:#x}, reason: {:#x}, let watchdog to fire"
        ;
        uVar7 = *(uint *)(param_3 + 0x14);
        uVar12 = 5;
        uVar16 = 0x82;
        pcStack_108 = 
        _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
        ;
        local_100 = (char *)(ulong)*pbVar19;
        uStack_d8 = 0;
        uStack_f8 = 0;
        local_f0 = (undefined7 *)(ulong)(byte)param_3[0xfa];
        local_e8 = 0;
        local_d0 = (ulong)pbVar19[2];
        local_c8 = 0;
        local_c0 = 0xc6319e3;
        local_370 = (char *)0xc6319e3;
        local_380 = 6;
        local_110 = param_3;
        goto LAB_00676468;
      }
      bluetooth::common::ToString<bluetooth::le_audio::types::AseState>((common *)local_39c,pAVar15)
      ;
      bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                ((common *)local_3a0,extraout_x1_03);
      local_368 = CONCAT44(local_368._4_4_,0x279);
      uVar7 = *(uint *)param_2;
      local_110 = (char *)0x1;
      pcVar23 = "Ctp result OK for group {} inTransition: {} , targetState: {}, currentState: {}";
      local_100 = local_388;
      if ((local_398 & 1) == 0) {
        local_100 = (char *)&uStack_397;
        local_390 = (ulong)(local_398 >> 1);
      }
      bVar6 = (local_3b8 & 1) == 0;
      uVar12 = 0x4f;
      local_f0 = local_3a8;
      uStack_f8 = local_390;
      if (bVar6) {
        local_f0 = &uStack_3b7;
      }
      goto LAB_006763bc;
    }
    local_368 = CONCAT44(local_368._4_4_,0x25d);
    local_358 = "ProcessGattCtpNotification";
    uVar7 = *(uint *)param_2;
    pcVar23 = "Invalid CTP notification for group {}";
    uVar12 = 6;
    uVar16 = 0x25;
    local_110 = (char *)0x3;
    local_380 = 1;
    local_370 = (char *)0x3;
LAB_00676468:
    local_120 = (char *)(ulong)uVar7;
    local_378 = &local_120;
    pcStack_118 = (code *)0x0;
    local_360 = "packages/modules/Bluetooth/system/bta/le_audio/state_machine.cc";
    bluetooth::log_internal::vlog(uVar12,"bluetooth",&local_368,pcVar23,uVar16,&local_380);
  }
  else {
    bluetooth::common::ToString<bluetooth::le_audio::types::AseState>((common *)local_39c,pAVar15);
    bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
              ((common *)local_3a0,extraout_x1_02);
    local_368 = CONCAT44(local_368._4_4_,0x254);
    uVar7 = *(uint *)param_2;
    pcVar23 = 
    "Not interested in ctp result for group {} inTransition: {} , targetState: {}, currentState: {}"
    ;
    local_100 = local_388;
    if ((local_398 & 1) == 0) {
      local_390 = (ulong)(local_398 >> 1);
      local_100 = (char *)&uStack_397;
    }
    bVar6 = (local_3b8 & 1) == 0;
    uVar12 = 0x5e;
    local_f0 = local_3a8;
    local_110 = (char *)(ulong)(byte)LVar3;
    uStack_f8 = local_390;
    if (bVar6) {
      local_f0 = &uStack_3b7;
    }
LAB_006763bc:
    local_120 = (char *)(ulong)uVar7;
    pcStack_108 = (code *)0x0;
    pcStack_118 = (code *)0x0;
    local_358 = "ProcessGattCtpNotification";
    local_360 = "packages/modules/Bluetooth/system/bta/le_audio/state_machine.cc";
    local_370 = (char *)0x6b423;
    local_e8 = (ulong)(local_3b8 >> 1);
    if (!bVar6) {
      local_e8 = local_3b0;
    }
    local_e0 = 0x6b423;
    local_378 = &local_120;
    local_380 = 4;
    bluetooth::log_internal::vlog(3,"bluetooth",&local_368,pcVar23,uVar12,&local_380);
    if ((local_3b8 & 1) != 0) {
      operator_delete(local_3a8,CONCAT71(uStack_3b7,local_3b8) & 0xfffffffffffffffe);
    }
    if ((local_398 & 1) != 0) {
      operator_delete(local_388,CONCAT71(uStack_397,local_398) & 0xfffffffffffffffe);
    }
  }
LAB_0067646c:
  ppuStack_2d0 = &PTR__stringstream_00f689f0;
  local_350 = &PTR__stringstream_00f689a0;
  ppuStack_340 = &PTR__stringstream_00f689c8;
  if ((local_2f8 & 1) != 0) {
    local_338 = &PTR__stringbuf_00f687d0;
    operator_delete(local_2e8,local_2f8 & 0xfffffffffffffffe);
  }
  local_338 = &PTR__streambuf_00f68750;
  std::locale::~locale((locale *)&uStack_330);
  std::iostream::~iostream((iostream *)&local_350);
  std::ios::~ios((ios *)&ppuStack_2d0);
  ppuStack_1b8 = &PTR__stringstream_00f689f0;
  local_238 = &PTR__stringstream_00f689a0;
  ppuStack_228 = &PTR__stringstream_00f689c8;
  if ((local_1e0 & 1) != 0) {
    local_220 = &PTR__stringbuf_00f687d0;
    operator_delete(local_1d0,local_1e0 & 0xfffffffffffffffe);
  }
  local_220 = &PTR__streambuf_00f68750;
  std::locale::~locale((locale *)&uStack_218);
  std::iostream::~iostream((iostream *)&local_238);
  std::ios::~ios((ios *)&ppuStack_1b8);
  pvVar14 = *(void **)(pbVar8 + 8);
joined_r0x00675d6c:
  if (pvVar14 != (void *)0x0) {
    *(void **)(pbVar8 + 0x10) = pvVar14;
    operator_delete(pvVar14,*(long *)(pbVar8 + 0x18) - (long)pvVar14);
  }
  operator_delete(pbVar8,0x20);
  if (*(long *)(lVar5 + 0x28) != local_78) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
LAB_0067625c:
  pbVar19 = pbVar19 + 3;
  goto LAB_00676260;
}


/* ==== ProcessGattNotifEvent @ 006767ac size 16988 :: AseStateMachineProcessCodecConfigured */

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Unknown calling convention: __rustcall */
/* _GLOBAL__N_1::LeAudioGroupStateMachineImpl::ProcessGattNotifEvent */

void __rustcall
_GLOBAL__N_1::LeAudioGroupStateMachineImpl::ProcessGattNotifEvent
          (long *param_1,long param_2,int param_3,long param_4,LeAudioDevice *param_5,
          LeAudioDeviceGroup *param_6,undefined8 param_7,undefined8 param_8)

{
  ulong uVar1;
  LeAudioDeviceGroup LVar2;
  long lVar3;
  char *pcVar4;
  bool bVar5;
  byte bVar6;
  undefined2 uVar7;
  ushort uVar8;
  ushort uVar9;
  int iVar10;
  undefined4 uVar11;
  ulong *puVar12;
  undefined8 *puVar13;
  ulong uVar14;
  ulong uVar15;
  long lVar16;
  ostream *poVar17;
  LeAudioDevice *pLVar18;
  long lVar19;
  long lVar20;
  undefined1 *puVar21;
  AseState *extraout_x1;
  AseState *extraout_x1_00;
  AseState *extraout_x1_01;
  AseState *extraout_x1_02;
  AseState *extraout_x1_03;
  AseState *extraout_x1_04;
  AseState *extraout_x1_05;
  AseState *extraout_x1_06;
  AseState *extraout_x1_07;
  AseState *extraout_x1_08;
  AseState *extraout_x1_09;
  AseState *extraout_x1_10;
  AseState *extraout_x1_11;
  AseState *extraout_x1_12;
  AseState *extraout_x1_13;
  AseState *extraout_x1_14;
  AseState *extraout_x1_15;
  AseState *extraout_x1_16;
  AseState *extraout_x1_17;
  AseState *extraout_x1_18;
  AseState *extraout_x1_19;
  AseState *extraout_x1_20;
  AseState *extraout_x1_21;
  AseState *extraout_x1_22;
  AseState *extraout_x1_23;
  long lVar22;
  AseState *extraout_x1_24;
  AseState *extraout_x1_25;
  AseState *extraout_x1_26;
  AseState *extraout_x1_27;
  AseState *extraout_x1_28;
  AseState *extraout_x1_29;
  AseState *pAVar23;
  AseState *extraout_x1_30;
  undefined4 *puVar24;
  char *pcVar25;
  undefined8 uVar26;
  uint uVar27;
  code *pcVar28;
  LeAudioDevice **ppLVar29;
  undefined8 *in_x18;
  LeAudioDevice *pLVar30;
  LeAudioDevice *pLVar31;
  byte *pbVar32;
  ulong uVar33;
  size_t __n;
  long *plVar34;
  undefined8 unaff_x30;
  undefined1 auVar35 [16];
  undefined8 uVar36;
  LeAudioDevice *local_498;
  LeAudioDevice *local_470;
  common local_468 [4];
  undefined2 local_464;
  undefined4 local_460 [2];
  char *local_458;
  char *pcStack_450;
  undefined4 local_448 [2];
  char *local_440;
  char *pcStack_438;
  undefined1 uStack_429;
  undefined4 local_428 [2];
  char *local_420;
  char *pcStack_418;
  undefined1 uStack_409;
  undefined4 local_408 [2];
  char *local_400;
  char *pcStack_3f8;
  undefined4 local_3f0 [2];
  char *local_3e8;
  char *pcStack_3e0;
  undefined4 local_3d8 [2];
  char *local_3d0;
  char *pcStack_3c8;
  undefined1 uStack_3b9;
  undefined4 local_3b8 [2];
  char *local_3b0;
  char *pcStack_3a8;
  undefined4 local_3a0 [2];
  char *local_398;
  char *pcStack_390;
  undefined1 uStack_381;
  undefined4 local_380 [2];
  char *local_378;
  char *pcStack_370;
  undefined4 local_368 [2];
  char *local_360;
  char *pcStack_358;
  undefined1 uStack_349;
  undefined4 local_348 [2];
  char *local_340;
  char *pcStack_338;
  undefined1 uStack_329;
  undefined4 local_328 [2];
  char *local_320;
  char *pcStack_318;
  undefined1 uStack_309;
  undefined4 local_308 [2];
  char *local_300;
  char *pcStack_2f8;
  undefined4 local_2f0 [2];
  char *local_2e8;
  char *pcStack_2e0;
  undefined1 uStack_2d1;
  undefined1 local_2d0 [8];
  char *local_2c8;
  char *pcStack_2c0;
  common local_2b4 [4];
  LeAudioDevice *local_2b0;
  LeAudioDeviceGroup *pLStack_2a8;
  ulong local_2a0;
  LeAudioDevice *local_298;
  char *local_290;
  undefined4 local_288;
  undefined4 uStack_284;
  char *local_280;
  char *local_278;
  undefined8 local_270;
  LeAudioDevice *pLStack_268;
  LeAudioDevice *local_260;
  LeAudioDevice *local_258;
  undefined8 local_250;
  LeAudioDevice *pLStack_248;
  LeAudioDevice *local_240;
  undefined8 local_230;
  LeAudioDevice *pLStack_228;
  LeAudioDevice *local_220;
  undefined8 local_210;
  LeAudioDevice *pLStack_208;
  LeAudioDevice *local_200;
  LeAudioDevice *local_1f0;
  __tree_node *p_Stack_1e8;
  LeAudioDevice *local_1e0;
  LeAudioDevice *local_1d8;
  LeAudioDevice *pLStack_1d0;
  LeAudioDevice *local_1c8;
  LeAudioDevice *pLStack_1c0;
  LeAudioDevice *local_1b8;
  LeAudioDevice *pLStack_1b0;
  LeAudioDevice *local_1a8;
  char *pcStack_1a0;
  char *local_198;
  undefined8 uStack_190;
  void *local_188;
  LeAudioDevice *pLStack_180;
  undefined8 local_178;
  undefined **ppuStack_170;
  undefined8 local_168;
  undefined8 uStack_160;
  undefined8 local_158;
  undefined8 uStack_150;
  undefined8 local_148;
  undefined8 uStack_140;
  undefined8 local_138;
  undefined8 uStack_130;
  undefined8 local_128;
  undefined8 uStack_120;
  undefined8 local_118;
  undefined8 uStack_110;
  undefined8 local_108;
  undefined8 uStack_100;
  undefined8 local_f8;
  undefined8 uStack_f0;
  undefined8 local_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 local_c8;
  undefined8 local_c0;
  undefined8 uStack_b8;
  undefined8 local_b0;
  undefined8 uStack_a8;
  LeAudioDevice *local_a0;
  LeAudioDevice *local_98;
  LeAudioDevice *local_90;
  long local_78;
  
  *in_x18 = unaff_x30;
  uVar36 = 0;
  lVar3 = tpidr_el0;
  local_78 = *(long *)(lVar3 + 0x28);
  local_464 = 0;
  bluetooth::le_audio::client_parser::ascs::ParseAseStatusHeader(&local_464,param_3,param_2);
  pbVar32 = (byte *)(param_4 + 4);
  pAVar23 = extraout_x1;
  if (*pbVar32 == 0) {
    local_1f0 = (LeAudioDevice *)(ulong)(byte)local_464;
    local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0x28c);
    uStack_b8 = (code *)0x1d97f3;
    local_b0 = "ProcessGattNotifEvent";
    local_1e0 = (LeAudioDevice *)0x6;
    p_Stack_1e8 = (__tree_node *)0x0;
    local_270 = 1;
    local_260 = (LeAudioDevice *)0x6;
    pLStack_268 = (LeAudioDevice *)&local_1f0;
    bluetooth::log_internal::vlog
              (4,"bluetooth",&local_c0,", discovered ase id: {}",0x17,&local_270,param_7,param_8,
               uVar36);
    *pbVar32 = (byte)local_464;
    pAVar23 = extraout_x1_00;
  }
  local_468[0] = local_464._1_1_;
  bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
            ((common *)(param_4 + 0x310),pAVar23);
  bluetooth::common::ToString<bluetooth::le_audio::types::AseState>(local_468,extraout_x1_01);
  local_1e0 = (LeAudioDevice *)(ulong)*(byte *)(param_4 + 4);
  local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0x292);
  p_Stack_1e8 = (__tree_node *)
                _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
  ;
  local_1c8 = pLStack_208;
  pLStack_1d0 = local_200;
  if (((ulong)local_210 & 1) == 0) {
    pLStack_1d0 = (LeAudioDevice *)((long)&local_210 + 1);
    local_1c8 = (LeAudioDevice *)((ulong)local_210 >> 1 & 0x7f);
  }
  local_1b8 = pLStack_248;
  pLStack_1c0 = local_240;
  if ((local_250 & 1) == 0) {
    local_1b8 = (LeAudioDevice *)(local_250 >> 1 & 0x7f);
    pLStack_1c0 = (LeAudioDevice *)((long)&local_250 + 1);
  }
  uStack_b8 = (code *)0x1d97f3;
  local_b0 = "ProcessGattNotifEvent";
  local_1d8 = (LeAudioDevice *)0x0;
  pLStack_1b0 = (LeAudioDevice *)0x6b4cf;
  local_270 = 4;
  local_260 = (LeAudioDevice *)0x6b4cf;
  pLStack_268 = (LeAudioDevice *)&local_1f0;
  local_1f0 = param_5;
  bluetooth::log_internal::vlog
            (4,"bluetooth",&local_c0,"{} , ASE id: {}, state changed {} -> {}",0x27,&local_270,
             param_7,param_8,uVar36);
  if ((local_250 & 1) != 0) {
    operator_delete(local_240,local_250 & 0xfffffffffffffffe);
  }
  if (((ulong)local_210 & 1) != 0) {
    operator_delete(local_200,(ulong)local_210 & 0xfffffffffffffffe);
  }
  uVar11 = *(undefined4 *)(param_5 + 0x14);
  plVar34 = (long *)param_1[3];
  std::to_string((uint)(byte)local_464);
  puVar12 = (ulong *)std::string::insert((string *)&local_210,0,"ASE_ID ",7);
  pLStack_268 = (LeAudioDevice *)puVar12[1];
  local_270 = *puVar12;
  local_260 = (LeAudioDevice *)puVar12[2];
  puVar12[1] = 0;
  puVar12[2] = 0;
  *puVar12 = 0;
  auVar35 = std::string::append((string *)&local_270,": ");
  puVar12 = auVar35._0_8_;
  uStack_b8 = (code *)puVar12[1];
  local_c0 = (LeAudioDevice *)*puVar12;
  local_b0 = (char *)puVar12[2];
  puVar12[1] = 0;
  puVar12[2] = 0;
  *puVar12 = 0;
  bluetooth::common::ToString<bluetooth::le_audio::types::AseState>(local_468,auVar35._8_8_);
  auVar35 = std::string::append_abi_nn220000_((string *)&local_c0,(string *)&local_250);
  puVar13 = auVar35._0_8_;
  p_Stack_1e8 = (__tree_node *)puVar13[1];
  local_1f0 = (LeAudioDevice *)*puVar13;
  local_1e0 = (LeAudioDevice *)puVar13[2];
  puVar13[1] = 0;
  puVar13[2] = 0;
  *puVar13 = 0;
  bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
            ((common *)(param_4 + 0x310),auVar35._8_8_);
  puVar12 = (ulong *)std::string::insert((string *)&local_288,0,"curr: ",6);
  pLStack_228 = (LeAudioDevice *)puVar12[1];
  local_230 = *puVar12;
  local_220 = (LeAudioDevice *)puVar12[2];
  puVar12[1] = 0;
  puVar12[2] = 0;
  *puVar12 = 0;
  (**(code **)(*plVar34 + 0x18))(plVar34,&DAT_00faa2a8,uVar11,param_5,&local_1f0,&local_230);
  pAVar23 = extraout_x1_02;
  if ((local_230 & 1) != 0) {
    operator_delete(local_220,local_230 & 0xfffffffffffffffe);
    pAVar23 = extraout_x1_04;
  }
  if ((local_288 & 1) != 0) {
    operator_delete(local_278,CONCAT44(uStack_284,local_288) & 0xfffffffffffffffe);
    pAVar23 = extraout_x1_05;
  }
  if (((ulong)local_1f0 & 1) != 0) {
    operator_delete(local_1e0,(ulong)local_1f0 & 0xfffffffffffffffe);
    pAVar23 = extraout_x1_06;
  }
  if ((local_250 & 1) != 0) {
    operator_delete(local_240,local_250 & 0xfffffffffffffffe);
    pAVar23 = extraout_x1_07;
  }
  if (((ulong)local_c0 & 1) != 0) {
    operator_delete(local_b0,(ulong)local_c0 & 0xfffffffffffffffe);
    pAVar23 = extraout_x1_08;
  }
  if ((local_270 & 1) != 0) {
    operator_delete(local_260,local_270 & 0xfffffffffffffffe);
    pAVar23 = extraout_x1_09;
  }
  if (((ulong)local_210 & 1) != 0) {
    operator_delete(local_200,(ulong)local_210 & 0xfffffffffffffffe);
    pAVar23 = extraout_x1_03;
  }
  if ((byte)local_468[0] < 3) {
    if (local_468[0] != (common)0x0) {
      if (local_468[0] != (common)0x1) {
        if (local_468[0] != (common)0x2) goto LAB_00676f6c;
        if (param_6 == (LeAudioDeviceGroup *)0x0) {
          local_1f0 = (LeAudioDevice *)CONCAT44(local_1f0._4_4_,0xb79);
          local_1e0 = (LeAudioDevice *)0x1b8ffe;
          goto LAB_0067748c;
        }
        bVar6 = *(byte *)(param_4 + 0x310);
        if (bVar6 < 3) {
          if (bVar6 == 0) goto LAB_00677f00;
          if (bVar6 != 1) {
            if (bVar6 != 2) goto LAB_006782bc;
            bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                      ((common *)(param_4 + 0x310),pAVar23);
            local_2a0 = CONCAT71(local_2a0._1_7_,2);
            bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                      ((common *)&local_2a0,extraout_x1_14);
            local_2d0[0] = 1;
            bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                      ((common *)local_2d0,extraout_x1_15);
            local_2f0[0] = CONCAT31(local_2f0[0]._1_3_,2);
            bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                      ((common *)local_2f0,extraout_x1_16);
            uStack_b8 = (code *)0x1d97f3;
            local_b0 = "AseStateMachineProcessQosConfigured";
            local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0xb80);
            local_1f0 = local_200;
            p_Stack_1e8 = (__tree_node *)pLStack_208;
            if (((ulong)local_210 & 1) == 0) {
              local_1f0 = (LeAudioDevice *)((long)&local_210 + 1);
              p_Stack_1e8 = (__tree_node *)((ulong)local_210 >> 1 & 0x7f);
            }
            bVar5 = (local_250 & 1) == 0;
            local_1e0 = local_240;
            if (bVar5) {
              local_1e0 = (LeAudioDevice *)((long)&local_250 + 1);
            }
            local_1c8 = (LeAudioDevice *)
                        _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
            ;
            local_1d8 = (LeAudioDevice *)(local_250 >> 1 & 0x7f);
            if (!bVar5) {
              local_1d8 = pLStack_248;
            }
            pLStack_1c0 = (LeAudioDevice *)(ulong)*pbVar32;
            bVar5 = (local_230 & 1) == 0;
            pLStack_1b0 = local_220;
            if (bVar5) {
              pLStack_1b0 = (LeAudioDevice *)((long)&local_230 + 1);
            }
            local_1a8 = (LeAudioDevice *)(local_230 >> 1 & 0x7f);
            if (!bVar5) {
              local_1a8 = pLStack_228;
            }
            local_198 = local_280;
            pcStack_1a0 = local_278;
            if ((local_288 & 1) == 0) {
              local_198 = (char *)(ulong)((byte)local_288._0_1_ >> 1);
              pcStack_1a0 = (char *)((long)&local_288 + 1);
            }
            pLStack_268 = (LeAudioDevice *)&local_1f0;
            local_1b8 = (LeAudioDevice *)0x0;
            uStack_190 = 0x1ad33dad;
            local_270 = 6;
            local_260 = (LeAudioDevice *)0x1ad33dad;
            pLStack_1d0 = param_5;
            bluetooth::log_internal::vlog
                      (4,"bluetooth",&local_c0,
                       "Unexpected state transition from {} to {}, {}, ase_id: {}, fallback to transition from {} to {}"
                       ,0x5f,&local_270);
            if ((local_288 & 1) != 0) {
              operator_delete(local_278,CONCAT44(uStack_284,local_288) & 0xfffffffffffffffe);
            }
            if ((local_230 & 1) != 0) {
              operator_delete(local_220,local_230 & 0xfffffffffffffffe);
            }
            if ((local_250 & 1) != 0) {
              operator_delete(local_240,local_250 & 0xfffffffffffffffe);
            }
            if (((ulong)local_210 & 1) != 0) {
              operator_delete(local_200,(ulong)local_210 & 0xfffffffffffffffe);
            }
            bluetooth::le_audio::LeAudioDeviceGroup::PrintDebugState(param_6);
          }
          SetAseState(param_5,param_4,2);
          LVar2 = param_6[0x170];
          if ((LVar2 == (LeAudioDeviceGroup)0x2) || (LVar2 == (LeAudioDeviceGroup)0x4)) {
            uVar14 = bluetooth::le_audio::LeAudioDevice::HaveAllActiveAsesSameState(param_5,2);
            if ((uVar14 & 1) == 0) goto LAB_006782bc;
            if (param_6[0x171] == (LeAudioDeviceGroup)0x4) {
              uVar11 = (**(code **)(*(long *)param_1[1] + 0x28))
                                 ((long *)param_1[1],*(undefined4 *)param_6);
              PrepareAndSendEnable(param_1,param_5,uVar11,0xffffffff);
              goto LAB_006782bc;
            }
            uVar14 = bluetooth::le_audio::LeAudioDeviceGroup::HaveAllActiveDevicesAsesTheSameState
                               (param_6,2);
            if ((uVar14 & 1) != 0) {
              bluetooth::le_audio::LeAudioDeviceGroup::SetState(param_6,2);
              if (param_6[0x170] != (LeAudioDeviceGroup)0x2) {
                uVar11 = (**(code **)(*(long *)param_1[1] + 0x28))
                                   ((long *)param_1[1],*(undefined4 *)param_6);
                PrepareAndSendEnableToTheGroup(param_1,param_6,uVar11);
                goto LAB_006782bc;
              }
              (**(code **)(*param_1 + 0x98))(param_1,*(undefined4 *)param_6);
              bluetooth::le_audio::LeAudioDeviceGroup::ClearPendingConfiguration(param_6);
              plVar34 = (long *)param_1[1];
              uVar11 = *(undefined4 *)param_6;
              uVar36 = 7;
              goto LAB_0067a2a8;
            }
            local_1f0 = (LeAudioDevice *)CONCAT44(local_1f0._4_4_,0xba5);
            local_1e0 = (LeAudioDevice *)0x1b8ffe;
            pcVar25 = "Waiting for all the devices to be in QoS state";
            uVar36 = 3;
            uVar26 = 0x2e;
            goto LAB_006774b0;
          }
          local_250 = CONCAT71(local_250._1_7_,LVar2);
          bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                    ((common *)&local_250,extraout_x1_17);
          local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0xb8f);
          uStack_b8 = (code *)0x1d97f3;
          local_b0 = "AseStateMachineProcessQosConfigured";
          p_Stack_1e8 = (__tree_node *)
                        _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
          ;
          local_1e0 = (LeAudioDevice *)(ulong)*pbVar32;
          pLStack_1d0 = local_200;
          local_1c8 = pLStack_208;
          if (((ulong)local_210 & 1) == 0) {
            pLStack_1d0 = (LeAudioDevice *)((long)&local_210 + 1);
            local_1c8 = (LeAudioDevice *)((ulong)local_210 >> 1 & 0x7f);
          }
          pLStack_268 = (LeAudioDevice *)&local_1f0;
          local_1d8 = (LeAudioDevice *)0x0;
          pLStack_1c0 = (LeAudioDevice *)0x34cf;
          local_270 = 3;
          local_260 = (LeAudioDevice *)0x34cf;
          local_1f0 = param_5;
          bluetooth::log_internal::vlog
                    (5,"bluetooth",&local_c0,"{}, ase_id: {}, target state: {}",0x20,&local_270);
        }
        else {
          if (bVar6 < 5) {
            if (bVar6 == 3) {
              bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                        ((common *)(param_4 + 0x310),pAVar23);
              local_230 = CONCAT71(local_230._1_7_,2);
              bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                        ((common *)&local_230,extraout_x1_21);
              uStack_b8 = (code *)0x1d97f3;
              local_b0 = "AseStateMachineProcessQosConfigured";
              local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0xc11);
              p_Stack_1e8 = (__tree_node *)pLStack_208;
              local_1f0 = local_200;
              if (((ulong)local_210 & 1) == 0) {
                p_Stack_1e8 = (__tree_node *)((ulong)local_210 >> 1 & 0x7f);
                local_1f0 = (LeAudioDevice *)((long)&local_210 + 1);
              }
              local_1d8 = pLStack_248;
              local_1e0 = local_240;
              if ((local_250 & 1) == 0) {
                local_1d8 = (LeAudioDevice *)(local_250 >> 1 & 0x7f);
                local_1e0 = (LeAudioDevice *)((long)&local_250 + 1);
              }
              pLStack_1c0 = (LeAudioDevice *)(ulong)*pbVar32;
              local_1c8 = (LeAudioDevice *)
                          _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
              ;
              pLStack_268 = (LeAudioDevice *)&local_1f0;
              pLStack_1b0 = (LeAudioDevice *)0x33dad;
              local_1b8 = (LeAudioDevice *)0x0;
              local_270 = 4;
              local_260 = (LeAudioDevice *)0x33dad;
              pLStack_1d0 = param_5;
              bluetooth::log_internal::vlog
                        (6,"bluetooth",&local_c0,
                         "Invalid state transition from {} to {}, {}, ase_id: {}. Stopping the stream."
                         ,0x4c,&local_270);
              pLVar18 = local_210;
              pLVar30 = local_200;
              if ((local_250 & 1) != 0) {
                operator_delete(local_240,local_250 & 0xfffffffffffffffe);
                pLVar18 = local_210;
                pLVar30 = local_200;
              }
joined_r0x00678910:
              if (((ulong)pLVar18 & 1) != 0) {
                operator_delete(pLVar30,(ulong)pLVar18 & 0xfffffffffffffffe);
              }
            }
            else {
              if (bVar6 != 4) goto LAB_006782bc;
              if (*(char *)(param_4 + 6) != '\x02') {
                SetAseState(param_5,param_4,2);
                if (*(char *)(param_4 + 0x311) == '\x05') {
                  SetAseExpectedState(param_5,param_4,2);
                  bVar6 = (**(code **)(*(long *)param_1[1] + 0x28))
                                    ((long *)param_1[1],*(undefined4 *)param_6);
                  if ((bVar6 & *(byte *)(param_4 + 6)) != 0) {
                    local_1f0 = (LeAudioDevice *)CONCAT44(local_1f0._4_4_,0xbc8);
                    p_Stack_1e8 = (__tree_node *)0x1d97f3;
                    local_1e0 = (LeAudioDevice *)0x1b8ffe;
                    bluetooth::log::info<RawAddress&,unsigned_char&>::log
                              (param_5,pbVar32,&local_1f0);
                    goto LAB_006791fc;
                  }
                }
                uVar14 = bluetooth::le_audio::LeAudioDeviceGroup::
                         HaveAllActiveDevicesAsesTheSameState(param_6,2);
                if ((uVar14 & 1) != 0) {
                  bluetooth::le_audio::LeAudioDeviceGroup::SetState(param_6,2);
                }
                if (param_6[0x170] != (LeAudioDeviceGroup)0x2) {
                  ProcessAutonomousDisable(param_1,param_6,param_5,param_4);
                  goto LAB_006782bc;
                }
                goto LAB_00679340;
              }
              pLStack_268 = (LeAudioDevice *)&local_1f0;
              local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0xbb9);
              uStack_b8 = (code *)0x1d97f3;
              local_b0 = "AseStateMachineProcessQosConfigured";
              local_1f0 = (LeAudioDevice *)&DAT_00000004;
              p_Stack_1e8 = (__tree_node *)0x0;
              pLStack_1d0 = (LeAudioDevice *)0x63;
              local_1d8 = (LeAudioDevice *)0x0;
              local_1e0 = (LeAudioDevice *)0x2;
              local_270 = 2;
              local_260 = (LeAudioDevice *)0x63;
              bluetooth::log_internal::vlog
                        (6,"bluetooth",&local_c0,"invalid state transition, from: {}, to: {}",0x2a,
                         &local_270);
            }
            uVar11 = *(undefined4 *)param_6;
            uVar36 = 7;
            goto LAB_00678930;
          }
          if (bVar6 == 5) {
            SetAseState(param_5,param_4,2);
            if ((*(char *)(param_4 + 0x311) == '\x02') &&
               (bVar6 = (**(code **)(*(long *)param_1[1] + 0x28))
                                  ((long *)param_1[1],*(undefined4 *)param_6),
               (bVar6 & *(byte *)(param_4 + 6)) != 0)) {
              local_1e0 = (LeAudioDevice *)(ulong)*(byte *)(param_4 + 4);
              pLStack_268 = (LeAudioDevice *)&local_1f0;
              local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0xbe7);
              uStack_b8 = (code *)0x1d97f3;
              local_b0 = "AseStateMachineProcessQosConfigured";
              p_Stack_1e8 = (__tree_node *)
                            _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
              ;
              pLStack_1d0 = (LeAudioDevice *)0xcf;
              local_1d8 = (LeAudioDevice *)0x0;
              local_270 = 2;
              local_260 = (LeAudioDevice *)0xcf;
              local_1f0 = param_5;
              bluetooth::log_internal::vlog
                        (4,"bluetooth",&local_c0,"Quick disable / enable happened for {}, {}",0x2a,
                         &local_270);
LAB_006791fc:
              PrepareAndSendEnable
                        (param_1,param_5,*(undefined1 *)(param_4 + 6),*(undefined1 *)(param_4 + 4));
              goto LAB_006782bc;
            }
            uVar14 = bluetooth::le_audio::LeAudioDeviceGroup::HaveAllActiveDevicesAsesTheSameState
                               (param_6,2);
            if ((uVar14 & 1) == 0) goto LAB_006782bc;
            bluetooth::le_audio::LeAudioDeviceGroup::SetState(param_6,2);
            auVar35 = bluetooth::le_audio::LeAudioDeviceGroup::HaveAllCisesDisconnected(param_6);
            if ((auVar35._0_8_ & 1) == 0) goto LAB_006782bc;
            if (param_6[0x170] != (LeAudioDeviceGroup)0x2) {
              local_250 = CONCAT71(local_250._1_7_,param_6[0x171]);
              bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                        ((common *)&local_250,auVar35._8_8_);
              local_230 = CONCAT71(local_230._1_7_,param_6[0x170]);
              bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                        ((common *)&local_230,extraout_x1_27);
              local_270 = CONCAT44(local_270._4_4_,0xc00);
              pLStack_268 = (LeAudioDevice *)0x1d97f3;
              local_260 = (LeAudioDevice *)0x1b8ffe;
              bluetooth::log::error<std::string,std::string>::log
                        (&local_210,", invalid state transition, from: {}, to: {}",0x2c,&local_1f0,
                         &local_c0,&local_270);
              pLVar18 = local_1f0;
              pLVar30 = local_1e0;
              if (((ulong)local_c0 & 1) != 0) {
                operator_delete(local_b0,(ulong)local_c0 & 0xfffffffffffffffe);
                pLVar18 = local_1f0;
                pLVar30 = local_1e0;
              }
              goto joined_r0x00678910;
            }
            (**(code **)(*param_1 + 0x98))(param_1,*(undefined4 *)param_6);
            plVar34 = (long *)param_1[1];
            uVar11 = *(undefined4 *)param_6;
            pcVar28 = *(code **)(*plVar34 + 0x10);
            goto LAB_00676fe0;
          }
          if (bVar6 != 6) goto LAB_006782bc;
LAB_00677f00:
          bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                    ((common *)(param_4 + 0x310),pAVar23);
          local_230 = CONCAT71(local_230._1_7_,2);
          bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                    ((common *)&local_230,extraout_x1_19);
          uStack_b8 = (code *)0x1d97f3;
          local_b0 = "AseStateMachineProcessQosConfigured";
          local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0xc0b);
          p_Stack_1e8 = (__tree_node *)pLStack_208;
          local_1f0 = local_200;
          if (((ulong)local_210 & 1) == 0) {
            p_Stack_1e8 = (__tree_node *)((ulong)local_210 >> 1 & 0x7f);
            local_1f0 = (LeAudioDevice *)((long)&local_210 + 1);
          }
          local_1d8 = pLStack_248;
          local_1e0 = local_240;
          if ((local_250 & 1) == 0) {
            local_1d8 = (LeAudioDevice *)(local_250 >> 1 & 0x7f);
            local_1e0 = (LeAudioDevice *)((long)&local_250 + 1);
          }
          pLStack_1c0 = (LeAudioDevice *)(ulong)*pbVar32;
          local_1c8 = (LeAudioDevice *)
                      _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
          ;
          pLStack_268 = (LeAudioDevice *)&local_1f0;
          pLStack_1b0 = (LeAudioDevice *)0x33dad;
          local_1b8 = (LeAudioDevice *)0x0;
          local_270 = 4;
          local_260 = (LeAudioDevice *)0x33dad;
          pLStack_1d0 = param_5;
          bluetooth::log_internal::vlog
                    (6,"bluetooth",&local_c0,
                     "Ignore invalid attempt of state transition from {} to {}, {}, ase_id: {",0x48,
                     &local_270);
          if ((local_250 & 1) != 0) {
            operator_delete(local_240,local_250 & 0xfffffffffffffffe);
          }
        }
        if (((ulong)local_210 & 1) != 0) {
          operator_delete(local_200,(ulong)local_210 & 0xfffffffffffffffe);
        }
        bluetooth::le_audio::LeAudioDeviceGroup::PrintDebugState(param_6);
        goto LAB_006782bc;
      }
      auVar35 = logging::ShouldCreateLogMessage(0);
      pAVar23 = auVar35._8_8_;
      if ((auVar35._0_8_ & 1) != 0) {
        logging::LogMessage::LogMessage
                  ((LogMessage *)&local_1f0,
                   "packages/modules/Bluetooth/system/bta/le_audio/state_machine.cc",0x9dd,0);
        std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                  ((ostream *)&p_Stack_1e8,"AseStateMachineProcessCodecConfigured",0x25);
        logging::LogMessage::~LogMessage((LogMessage *)&local_1f0);
        pAVar23 = extraout_x1_13;
      }
      if (param_6 == (LeAudioDeviceGroup *)0x0) {
        local_1f0 = (LeAudioDevice *)CONCAT44(local_1f0._4_4_,0x9df);
        local_1e0 = (LeAudioDevice *)0x198ab9;
        goto LAB_0067748c;
      }
      bVar6 = *(byte *)(param_4 + 0x310);
      local_2b0 = param_5;
      pLStack_2a8 = param_6;
      if (2 < bVar6) {
        if (1 < bVar6 - 3) {
          if (bVar6 == 5) {
            bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                      ((common *)(param_4 + 0x310),pAVar23);
            local_230 = CONCAT71(local_230._1_7_,1);
            bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                      ((common *)&local_230,extraout_x1_22);
            uStack_b8 = (code *)0x1d97f3;
            local_b0 = "AseStateMachineProcessCodecConfigured";
            local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0xb39);
            p_Stack_1e8 = (__tree_node *)pLStack_208;
            local_1f0 = local_200;
            if (((ulong)local_210 & 1) == 0) {
              p_Stack_1e8 = (__tree_node *)((ulong)local_210 >> 1 & 0x7f);
              local_1f0 = (LeAudioDevice *)((long)&local_210 + 1);
            }
            local_1d8 = pLStack_248;
            local_1e0 = local_240;
            if ((local_250 & 1) == 0) {
              local_1d8 = (LeAudioDevice *)(local_250 >> 1 & 0x7f);
              local_1e0 = (LeAudioDevice *)((long)&local_250 + 1);
            }
            pLStack_1c0 = (LeAudioDevice *)(ulong)*pbVar32;
            local_1c8 = (LeAudioDevice *)
                        _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
            ;
            pLStack_268 = (LeAudioDevice *)&local_1f0;
            pLStack_1b0 = (LeAudioDevice *)0x33dad;
            local_1b8 = (LeAudioDevice *)0x0;
            local_270 = 4;
            local_260 = (LeAudioDevice *)0x33dad;
            pLStack_1d0 = param_5;
            bluetooth::log_internal::vlog
                      (6,"bluetooth",&local_c0,
                       "Ignore invalid attempt of state transition from {} to {}, {}, ase_id: {",
                       0x48,&local_270);
            if ((local_250 & 1) != 0) {
              operator_delete(local_240,local_250 & 0xfffffffffffffffe);
            }
            if (((ulong)local_210 & 1) != 0) {
              operator_delete(local_200,(ulong)local_210 & 0xfffffffffffffffe);
            }
          }
          else {
            if (bVar6 != 6) goto LAB_006782bc;
            SetAseState(param_5,param_4,1);
            *(undefined1 *)(param_4 + 10) = 0;
            uVar14 = bluetooth::le_audio::LeAudioDevice::HaveAllActiveAsesSameState(param_5,1);
            if ((uVar14 & 1) == 0) {
              local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0xb47);
              local_b0 = "AseStateMachineProcessCodecConfigured";
              goto LAB_00679230;
            }
            pLVar18 = (LeAudioDevice *)
                      bluetooth::le_audio::LeAudioDeviceGroup::GetFirstActiveDevice(param_6);
            if (pLVar18 != (LeAudioDevice *)0x0) {
              local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0xb4e);
              local_b0 = "AseStateMachineProcessCodecConfigured";
              local_260 = (LeAudioDevice *)&DAT_0000000f;
              p_Stack_1e8 = (__tree_node *)
                            _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
              ;
              local_270 = 1;
              pcVar25 = "There is at least one active device {}, wait to become inactive";
              uVar36 = 3;
              uVar26 = 0x3f;
              local_1e0 = (LeAudioDevice *)&DAT_0000000f;
              local_1f0 = pLVar18;
              goto LAB_00679274;
            }
            bluetooth::le_audio::LeAudioDeviceGroup::SetState(param_6,1);
            bluetooth::le_audio::LeAudioDeviceGroup::SetTargetState(param_6,param_6[0x171]);
            uVar14 = bluetooth::le_audio::LeAudioDeviceGroup::HaveAllCisesDisconnected(param_6);
            if ((uVar14 & 1) != 0) {
              (**(code **)(*param_1 + 0x98))(param_1,*(undefined4 *)param_6);
              plVar34 = (long *)param_1[1];
              uVar11 = *(undefined4 *)param_6;
              uVar36 = 6;
              goto LAB_0067a2a8;
            }
            local_460[0] = 0xb5d;
            local_458 = "packages/modules/Bluetooth/system/bta/le_audio/state_machine.cc";
            pcStack_450 = "AseStateMachineProcessCodecConfigured";
            bluetooth::log::warn<int_const&>::log
                      ((warn<int_const&> *)
                       "Not all CISes removed before going to IDLE for group {}, waiting...",0x43,
                       param_6,local_460);
          }
          bluetooth::le_audio::LeAudioDeviceGroup::PrintDebugState(param_6);
          goto LAB_006782bc;
        }
        bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                  ((common *)(param_4 + 0x310),pAVar23);
        local_230 = CONCAT71(local_230._1_7_,1);
        bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                  ((common *)&local_230,extraout_x1_20);
        uStack_b8 = (code *)0x1d97f3;
        local_b0 = "AseStateMachineProcessCodecConfigured";
        local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0xb6a);
        p_Stack_1e8 = (__tree_node *)pLStack_208;
        local_1f0 = local_200;
        if (((ulong)local_210 & 1) == 0) {
          p_Stack_1e8 = (__tree_node *)((ulong)local_210 >> 1 & 0x7f);
          local_1f0 = (LeAudioDevice *)((long)&local_210 + 1);
        }
        local_1d8 = pLStack_248;
        local_1e0 = local_240;
        if ((local_250 & 1) == 0) {
          local_1d8 = (LeAudioDevice *)(local_250 >> 1 & 0x7f);
          local_1e0 = (LeAudioDevice *)((long)&local_250 + 1);
        }
        pLStack_1c0 = (LeAudioDevice *)(ulong)*pbVar32;
        local_1c8 = (LeAudioDevice *)
                    _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
        ;
        pLStack_268 = (LeAudioDevice *)&local_1f0;
        pLStack_1b0 = (LeAudioDevice *)0x33dad;
        local_1b8 = (LeAudioDevice *)0x0;
        local_270 = 4;
        local_260 = (LeAudioDevice *)0x33dad;
        pLStack_1d0 = param_5;
        bluetooth::log_internal::vlog
                  (6,"bluetooth",&local_c0,
                   "Invalid state transition from {} to {}, {}, ase_id: {}. Stopping the stream",
                   0x4b,&local_270);
        if ((local_250 & 1) != 0) {
          operator_delete(local_240,local_250 & 0xfffffffffffffffe);
        }
        if (((ulong)local_210 & 1) != 0) {
          operator_delete(local_200,(ulong)local_210 & 0xfffffffffffffffe);
        }
        bluetooth::le_audio::LeAudioDeviceGroup::PrintDebugState(param_6);
        uVar11 = *(undefined4 *)param_6;
        goto LAB_006782a8;
      }
      if (bVar6 == 0) {
        local_90 = (LeAudioDevice *)0x0;
        uStack_a8 = 0;
        local_b0 = (char *)0x0;
        local_98 = (LeAudioDevice *)0x0;
        local_a0 = (LeAudioDevice *)0x0;
        uStack_b8 = (code *)0x0;
        local_c0 = (LeAudioDevice *)0x0;
        uVar14 = bluetooth::le_audio::client_parser::ascs::ParseAseStatusCodecConfiguredStateParams
                           (&local_c0,param_3 + -2,param_2 + 2);
        if ((uVar14 & 1) == 0) goto LAB_006787f0;
        uStack_f0 = 0;
        local_f8 = 0;
        uStack_100 = 0;
        local_108 = 0;
        uStack_e0 = 0;
        local_e8 = 0;
        uStack_110 = 0;
        local_118 = 0;
        uStack_120 = 0;
        local_128 = 0;
        uStack_130 = 0;
        local_138 = 0;
        uStack_140 = 0;
        local_148 = 0;
        uStack_150 = 0;
        local_158 = 0;
        uStack_160 = 0;
        local_168 = 0;
        local_178 = 0;
        pLStack_180 = (LeAudioDevice *)0x0;
        local_188 = (void *)0x0;
        uStack_190 = 0;
        local_198 = (char *)0x0;
        pcStack_1a0 = (char *)0x0;
        local_1a8 = (LeAudioDevice *)0x0;
        pLStack_1b0 = (LeAudioDevice *)0x0;
        local_1b8 = (LeAudioDevice *)0x0;
        pLStack_1c0 = (LeAudioDevice *)0x0;
        local_1c8 = (LeAudioDevice *)0x0;
        pLStack_1d0 = (LeAudioDevice *)0x0;
        local_1d8 = (LeAudioDevice *)0x0;
        local_1f0 = (LeAudioDevice *)&PTR__istream_00f68ae0;
        ppuStack_170 = &PTR__istream_00f68b08;
        p_Stack_1e8 = (__tree_node *)0x0;
        local_2b4[0] = local_464._1_1_;
        local_1e0 = (LeAudioDevice *)&PTR__stringstream_00f689c8;
        std::ios_base::init((ios_base *)&ppuStack_170,&local_1d8);
        local_e8 = 0;
                    /* WARNING: Ignoring partial resolution of indirect */
        uStack_e0._0_4_ = 0xffffffff;
        local_1f0 = (LeAudioDevice *)&PTR__stringstream_00f689a0;
        local_1d8 = (LeAudioDevice *)&PTR__streambuf_00f68750;
        local_1e0 = (LeAudioDevice *)&PTR__stringstream_00f689c8;
        ppuStack_170 = &PTR__stringstream_00f689f0;
        std::locale::locale((locale *)&pLStack_1d0);
        pcStack_1a0 = (char *)0x0;
        local_1a8 = (LeAudioDevice *)0x0;
        pLStack_1b0 = (LeAudioDevice *)0x0;
        local_1b8 = (LeAudioDevice *)0x0;
        pLStack_1c0 = (LeAudioDevice *)0x0;
        local_1c8 = (LeAudioDevice *)0x0;
        local_1d8 = (LeAudioDevice *)&PTR__stringbuf_00f687d0;
        uStack_190 = 0;
        local_198 = (char *)0x0;
        pLStack_180 = (LeAudioDevice *)0x0;
        local_188 = (void *)0x0;
        local_178 = CONCAT44(local_178._4_4_,0x18);
        std::stringbuf::__init_buf_ptrs_abi_nn220000_((stringbuf *)&local_1d8);
        poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                            ((ostream *)&local_1e0,"fr ",3);
        loghex<unsigned_char>((uchar)local_c0._0_1_);
        pLVar18 = pLStack_268;
        pLVar30 = local_260;
        if ((local_270 & 1) == 0) {
          pLVar18 = (LeAudioDevice *)(local_270 >> 1 & 0x7f);
          pLVar30 = (LeAudioDevice *)((long)&local_270 + 1);
        }
        poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                            (poVar17,(char *)pLVar30,(ulong)pLVar18);
        poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                            (poVar17," phy ",5);
        loghex<unsigned_char>(local_c0._1_1_);
        pLVar18 = local_200;
        if (((ulong)local_210 & 1) == 0) {
          pLStack_208 = (LeAudioDevice *)((ulong)local_210 >> 1 & 0x7f);
          pLVar18 = (LeAudioDevice *)((long)&local_210 + 1);
        }
        poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                            (poVar17,(char *)pLVar18,(ulong)pLStack_208);
        poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                            (poVar17," rt ",4);
        poVar17 = (ostream *)std::ostream::operator<<(poVar17,(uint)local_c0._2_1_);
        poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                            (poVar17," lt ",4);
        poVar17 = (ostream *)std::ostream::operator<<(poVar17,(uint)local_c0._4_2_);
        poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                            (poVar17," pd_min ",8);
        poVar17 = (ostream *)std::ostream::operator<<(poVar17,(uint)uStack_b8);
        poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                            (poVar17," pd_max ",8);
        poVar17 = (ostream *)std::ostream::operator<<(poVar17,uStack_b8._4_4_);
        poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                            (poVar17," ppd_min ",9);
        poVar17 = (ostream *)std::ostream::operator<<(poVar17,(uint)local_b0);
        poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                            (poVar17," ppd_max ",9);
        poVar17 = (ostream *)std::ostream::operator<<(poVar17,local_b0._4_4_);
        poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                            (poVar17," cd ",4);
        loghex<unsigned_char>((uchar)uStack_a8);
        pLVar18 = local_240;
        if ((local_250 & 1) == 0) {
          pLStack_248 = (LeAudioDevice *)(local_250 >> 1 & 0x7f);
          pLVar18 = (LeAudioDevice *)((long)&local_250 + 1);
        }
        poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                            (poVar17,(char *)pLVar18,(ulong)pLStack_248);
        poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                            (poVar17," (v ",4);
        loghex<unsigned_short>(uStack_a8._2_2_);
        pLVar18 = pLStack_228;
        pLVar30 = local_220;
        if ((local_230 & 1) == 0) {
          pLVar18 = (LeAudioDevice *)(local_230 >> 1 & 0x7f);
          pLVar30 = (LeAudioDevice *)((long)&local_230 + 1);
        }
        poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                            (poVar17,(char *)pLVar30,(ulong)pLVar18);
        poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                            (poVar17," vc ",4);
        loghex<unsigned_short>(uStack_a8._4_2_);
        pcVar25 = local_280;
        pcVar4 = local_278;
        if ((local_288 & 1) == 0) {
          pcVar25 = (char *)(ulong)((byte)local_288._0_1_ >> 1);
          pcVar4 = (char *)((long)&local_288 + 1);
        }
        poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                            (poVar17,pcVar4,(ulong)pcVar25);
        std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>(poVar17,")",1);
        if ((local_288 & 1) != 0) {
          operator_delete(local_278,CONCAT44(uStack_284,local_288) & 0xfffffffffffffffe);
        }
        if ((local_230 & 1) != 0) {
          operator_delete(local_220,local_230 & 0xfffffffffffffffe);
        }
        if ((local_250 & 1) != 0) {
          operator_delete(local_240,local_250 & 0xfffffffffffffffe);
        }
        if (((ulong)local_210 & 1) != 0) {
          operator_delete(local_200,(ulong)local_210 & 0xfffffffffffffffe);
        }
        if ((local_270 & 1) != 0) {
          operator_delete(local_260,local_270 & 0xfffffffffffffffe);
        }
        uVar11 = *(undefined4 *)(param_5 + 0x14);
        plVar34 = (long *)param_1[3];
        std::to_string((uint)(byte)local_464);
        puVar12 = (ulong *)std::string::insert((string *)&local_230,0,"ASE_ID ",7);
        pLStack_248 = (LeAudioDevice *)puVar12[1];
        local_250 = *puVar12;
        local_240 = (LeAudioDevice *)puVar12[2];
        puVar12[1] = 0;
        puVar12[2] = 0;
        *puVar12 = 0;
        auVar35 = std::string::append((string *)&local_250,": ");
        puVar13 = auVar35._0_8_;
        pLStack_208 = (LeAudioDevice *)puVar13[1];
        local_210 = (LeAudioDevice *)*puVar13;
        local_200 = (LeAudioDevice *)puVar13[2];
        puVar13[1] = 0;
        puVar13[2] = 0;
        *puVar13 = 0;
        bluetooth::common::ToString<bluetooth::le_audio::types::AseState>(local_2b4,auVar35._8_8_);
        puVar12 = (ulong *)std::string::append_abi_nn220000_
                                     ((string *)&local_210,(string *)&local_288);
        pLStack_268 = (LeAudioDevice *)puVar12[1];
        local_270 = *puVar12;
        local_260 = (LeAudioDevice *)puVar12[2];
        puVar12[1] = 0;
        puVar12[2] = 0;
        *puVar12 = 0;
        if (((uint)local_178 >> 4 & 1) == 0) {
          if (((uint)local_178 >> 3 & 1) != 0) {
            ppLVar29 = &local_1c8;
            pLVar18 = local_1b8;
            goto LAB_00679e9c;
          }
          pLVar30 = (LeAudioDevice *)0x0;
          pLVar18 = (LeAudioDevice *)0x0;
LAB_00679eb4:
          pcVar25 = (char *)((ulong)&local_2a0 | 1);
          local_2a0 = CONCAT71(local_2a0._1_7_,(char)((int)pLVar18 << 1));
        }
        else {
          if (pLStack_180 < local_1a8) {
            pLStack_180 = local_1a8;
          }
          ppLVar29 = &pLStack_1b0;
          pLVar18 = pLStack_180;
LAB_00679e9c:
          pLVar30 = *ppLVar29;
          pLVar18 = pLVar18 + -(long)pLVar30;
          if ((LeAudioDevice *)0xfffffffffffffff6 < pLVar18) goto LAB_0067aa04;
          if (pLVar18 < (LeAudioDevice *)0x17) goto LAB_00679eb4;
          uVar14 = 0x1a;
          if (((ulong)pLVar18 | 7) != 0x17) {
            uVar14 = ((ulong)pLVar18 | 7) + 1;
          }
          pcVar25 = (char *)FUN_00f62c00(uVar14);
          local_2a0 = uVar14 | 1;
          local_298 = pLVar18;
          local_290 = pcVar25;
        }
        memmove(pcVar25,pLVar30,(size_t)pLVar18);
        pcVar25[(long)pLVar18] = '\0';
        (**(code **)(*plVar34 + 0x18))(plVar34,&DAT_00faa5c0,uVar11,param_5,&local_270,&local_2a0);
        if ((local_2a0 & 1) != 0) {
          operator_delete(local_290,local_2a0 & 0xfffffffffffffffe);
        }
        if ((local_270 & 1) != 0) {
          operator_delete(local_260,local_270 & 0xfffffffffffffffe);
        }
        if ((local_288 & 1) != 0) {
          operator_delete(local_278,CONCAT44(uStack_284,local_288) & 0xfffffffffffffffe);
        }
        if (((ulong)local_210 & 1) != 0) {
          operator_delete(local_200,(ulong)local_210 & 0xfffffffffffffffe);
        }
        if ((local_250 & 1) != 0) {
          operator_delete(local_240,local_250 & 0xfffffffffffffffe);
        }
        if ((local_230 & 1) != 0) {
          operator_delete(local_220,local_230 & 0xfffffffffffffffe);
        }
        if (param_6[0x171] == (LeAudioDeviceGroup)0x4) {
          uVar8 = bluetooth::le_audio::find_max_transport_latency(param_6,'\x01');
          uVar9 = bluetooth::le_audio::find_max_transport_latency(param_6,'\x02');
          if (((*(char *)(param_4 + 6) != '\x01') || (uVar8 <= local_c0._4_2_)) &&
             ((*(char *)(param_4 + 6) != '\x02' || (uVar9 <= local_c0._4_2_)))) goto LAB_0067a000;
          bluetooth::le_audio::LeAudioDeviceGroup::SetPendingConfiguration(param_6);
          uVar11 = *(undefined4 *)param_6;
          uVar36 = 6;
LAB_00679fec:
          plVar34 = (long *)param_1[1];
LAB_00679ff0:
          (**(code **)(*plVar34 + 0x30))(plVar34,uVar11,uVar36);
          goto LAB_0067a558;
        }
LAB_0067a000:
        ::(anonymous_namespace)::LeAudioGroupStateMachineImpl::
        AseStateMachineProcessCodecConfigured(bluetooth::le_audio::client_parser::ascs::ase_rsp_hdr&,bluetooth::le_audio::types::ase*,unsigned_char*,unsigned_short,bluetooth::le_audio::LeAudioDeviceGroup*,bluetooth::le_audio::LeAudioDevice*)
        ::
        {lambda(bluetooth::le_audio::client_parser::ascs::ase_codec_configured_state_params_const&,bluetooth::le_audio::types::AseQosPreferences&,bluetooth::le_audio::types::AseQosConfiguration&)#1}
        ::operator()((_lambda_bluetooth__le_audio__client_parser__ascs__ase_codec_configured_state_params_const__bluetooth__le_audio__types__AseQosPreferences__bluetooth__le_audio__types__AseQosConfiguration___1_
                      *)&local_2b0,(ase_codec_configured_state_params *)&local_c0,
                     (AseQosPreferences *)(param_4 + 0x1c8),(AseQosConfiguration *)(param_4 + 0x1b8)
                    );
        SetAseState(param_5,param_4,1);
        if (param_6[0x170] == (LeAudioDeviceGroup)0x0) {
          local_2d0._0_4_ = 0xa4e;
          local_2c8 = "packages/modules/Bluetooth/system/bta/le_audio/state_machine.cc";
          pcStack_2c0 = "AseStateMachineProcessCodecConfigured";
          bluetooth::log::debug<RawAddress&,unsigned_char&>::log(param_5,pbVar32,local_2d0);
          uVar14 = bluetooth::le_audio::LeAudioDeviceGroup::HaveAllActiveDevicesAsesTheSameState
                             (param_6,1);
          if ((uVar14 & 1) != 0) {
            bluetooth::le_audio::LeAudioDeviceGroup::SetState(param_6,1);
          }
          goto LAB_0067a558;
        }
        uVar14 = bluetooth::le_audio::LeAudioDevice::HaveAnyUnconfiguredAses(param_5);
        if ((uVar14 & 1) == 0) {
          if (param_6[0x171] == (LeAudioDeviceGroup)0x4) {
            if (param_5[6] != (LeAudioDevice)0x1) {
              pcVar25 = 
              "Device {} initiated configured state but it is not yet ready to be configured";
              local_328[0] = 0xa6e;
              local_320 = "packages/modules/Bluetooth/system/bta/le_audio/state_machine.cc";
              pcStack_318 = "AseStateMachineProcessCodecConfigured";
              puVar21 = &uStack_309;
              puVar24 = local_328;
              uVar36 = 0x4d;
              goto LAB_0067a060;
            }
            uVar14 = PrepareAndSendConfigQos(param_1,param_6,param_5);
            if ((uVar14 & 1) == 0) {
              local_308[0] = 0xa69;
              local_300 = "packages/modules/Bluetooth/system/bta/le_audio/state_machine.cc";
              pcStack_2f8 = "AseStateMachineProcessCodecConfigured";
              bluetooth::log::warn<int_const&,RawAddress&>::log(param_6,param_5,local_308);
            }
          }
          else {
            uVar14 = bluetooth::le_audio::LeAudioDeviceGroup::HaveAnyActiveDeviceInUnconfiguredState
                               (param_6);
            if ((uVar14 & 1) == 0) {
              bluetooth::le_audio::LeAudioDeviceGroup::SetState(param_6,1);
              LVar2 = param_6[0x170];
              if (LVar2 == (LeAudioDeviceGroup)0x1) {
                auVar35 = bluetooth::le_audio::LeAudioDeviceGroup::IsPendingConfiguration(param_6);
                pAVar23 = auVar35._8_8_;
                if ((auVar35._0_8_ & 1) == 0) goto LAB_0067a91c;
                local_270 = CONCAT44(local_270._4_4_,0xa9d);
                pLStack_268 = (LeAudioDevice *)0x1d97f3;
                local_260 = (LeAudioDevice *)0x198ab9;
                local_210 = (LeAudioDevice *)0x0;
                bluetooth::log_internal::vlog
                          (4,"bluetooth",&local_270,"Configured state completed",0x1a,&local_210);
                uVar14 = bluetooth::le_audio::LeAudioDeviceGroup::HaveAllCisesDisconnected(param_6);
                if ((uVar14 & 1) == 0) {
                  local_380[0] = 0xaa2;
                  local_378 = "packages/modules/Bluetooth/system/bta/le_audio/state_machine.cc";
                  pcStack_370 = "AseStateMachineProcessCodecConfigured";
                  bluetooth::log::warn<int_const&>::log
                            ((warn<int_const&> *)
                             "Not all CISes removed before going to CONFIGURED for group {}, waiting..."
                             ,0x49,param_6,local_380);
                  bluetooth::le_audio::LeAudioDeviceGroup::PrintDebugState(param_6);
                }
                else {
                  bluetooth::le_audio::LeAudioDeviceGroup::ClearPendingConfiguration(param_6);
                  (**(code **)(*(long *)param_1[1] + 0x10))
                            ((long *)param_1[1],*(undefined4 *)param_6,7);
                  (**(code **)(*param_1 + 0x98))(param_1,*(undefined4 *)param_6);
                }
              }
              else {
                if ((LVar2 != (LeAudioDeviceGroup)0x4) &&
                   (pAVar23 = extraout_x1_29, LVar2 != (LeAudioDeviceGroup)0x2)) {
LAB_0067a91c:
                  local_250 = CONCAT71(local_250._1_7_,param_6[0x171]);
                  bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                            ((common *)&local_250,pAVar23);
                  local_230 = CONCAT71(local_230._1_7_,param_6[0x170]);
                  bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                            ((common *)&local_230,extraout_x1_30);
                  local_3a0[0] = 0xab1;
                  local_398 = "packages/modules/Bluetooth/system/bta/le_audio/state_machine.cc";
                  pcStack_390 = "AseStateMachineProcessCodecConfigured";
                  bluetooth::log::error<std::string,std::string>::log
                            (&uStack_381,", invalid state transition, from: {} to {}",0x2a,
                             &local_270,&local_210,local_3a0);
                  if (((ulong)local_210 & 1) != 0) {
                    operator_delete(local_200,(ulong)local_210 & 0xfffffffffffffffe);
                  }
                  if ((local_270 & 1) != 0) {
                    operator_delete(local_260,local_270 & 0xfffffffffffffffe);
                  }
                  uVar36 = 7;
                  plVar34 = (long *)param_1[1];
                  uVar11 = *(undefined4 *)param_6;
                  goto LAB_00679ff0;
                }
                if (param_6[0x10] == (LeAudioDeviceGroup)0x2) {
                  uVar14 = PrepareAndSendQoSToTheGroup(param_1,param_6);
                  if ((uVar14 & 1) == 0) {
                    local_348[0] = 0xa8e;
                    local_340 = "packages/modules/Bluetooth/system/bta/le_audio/state_machine.cc";
                    pcStack_338 = "AseStateMachineProcessCodecConfigured";
                    bluetooth::log::error<int>::log
                              (&uStack_329,"Could not trigger QoS configured state for group_id: {}"
                               ,0x37,param_6,local_348);
                  }
                }
                else {
                  uVar14 = CigCreate(param_1,param_6);
                  if ((uVar14 & 1) == 0) {
                    local_368[0] = 0xa94;
                    local_360 = "packages/modules/Bluetooth/system/bta/le_audio/state_machine.cc";
                    pcStack_358 = "AseStateMachineProcessCodecConfigured";
                    bluetooth::log::error<int>::log
                              (&uStack_349,"Could not create CIG. Stop the stream for group {}",0x32
                               ,param_6,local_368);
                    uVar11 = *(undefined4 *)param_6;
                    uVar36 = 1;
                    goto LAB_00679fec;
                  }
                }
              }
            }
            else {
              local_270 = CONCAT44(local_270._4_4_,0xa77);
              pLStack_268 = (LeAudioDevice *)0x1d97f3;
              local_260 = (LeAudioDevice *)0x198ab9;
              local_210 = (LeAudioDevice *)0x0;
              bluetooth::log_internal::vlog
                        (3,"bluetooth",&local_270,"Waiting for all the ASES in the Configured state"
                         ,0x30,&local_210);
            }
          }
        }
        else {
          pcVar25 = "More Ases to be configured for the device {}";
          local_2f0[0] = 0xa5c;
          puVar21 = &uStack_2d1;
          puVar24 = local_2f0;
          uVar36 = 0x2c;
          local_2e8 = "packages/modules/Bluetooth/system/bta/le_audio/state_machine.cc";
          pcStack_2e0 = "AseStateMachineProcessCodecConfigured";
LAB_0067a060:
          bluetooth::log::debug<RawAddress&>::log(puVar21,pcVar25,uVar36,param_5,puVar24);
        }
LAB_0067a558:
LAB_0067a728:
        ppuStack_170 = &PTR__stringstream_00f689f0;
        local_1f0 = (LeAudioDevice *)&PTR__stringstream_00f689a0;
        local_1d8 = (LeAudioDevice *)&PTR__stringbuf_00f687d0;
        local_1e0 = (LeAudioDevice *)&PTR__stringstream_00f689c8;
        if (((byte)local_198 & 1) != 0) {
          operator_delete(local_188,(ulong)local_198 & 0xfffffffffffffffe);
        }
        local_1d8 = (LeAudioDevice *)&PTR__streambuf_00f68750;
        std::locale::~locale((locale *)&pLStack_1d0);
        std::iostream::~iostream((iostream *)&local_1f0);
        std::ios::~ios((ios *)&ppuStack_170);
      }
      else {
        if (bVar6 != 1) {
          if (bVar6 != 2) goto LAB_006782bc;
          local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0xab8);
          uStack_b8 = (code *)0x1d97f3;
          local_b0 = "AseStateMachineProcessCodecConfigured";
          local_1f0 = (LeAudioDevice *)(ulong)*(byte *)(param_4 + 4);
          pLStack_268 = (LeAudioDevice *)&local_1f0;
          local_1e0 = (LeAudioDevice *)(ulong)*(uint *)param_6;
          pLStack_1d0 = (LeAudioDevice *)0x66;
          local_260 = (LeAudioDevice *)0x66;
          p_Stack_1e8 = (__tree_node *)0x0;
          local_1d8 = (LeAudioDevice *)0x0;
          local_270 = 2;
          bluetooth::log_internal::vlog
                    (2,"bluetooth",&local_c0,
                     "Reconfiguring ase {} from QoS to Codec Configured group_id: {}",0x3e,
                     &local_270);
          SetAseState(param_5,param_4,1);
          bluetooth::le_audio::LeAudioDeviceGroup::PrintDebugState(param_6);
        }
        local_90 = (LeAudioDevice *)0x0;
        uStack_a8 = 0;
        local_b0 = (char *)0x0;
        local_98 = (LeAudioDevice *)0x0;
        local_a0 = (LeAudioDevice *)0x0;
        uStack_b8 = (code *)0x0;
        local_c0 = (LeAudioDevice *)0x0;
        uVar14 = bluetooth::le_audio::client_parser::ascs::ParseAseStatusCodecConfiguredStateParams
                           (&local_c0,param_3 + -2,param_2 + 2);
        if ((uVar14 & 1) != 0) {
          uStack_f0 = 0;
          local_f8 = 0;
          uStack_100 = 0;
          local_108 = 0;
          uStack_e0 = 0;
          local_e8 = 0;
          uStack_110 = 0;
          local_118 = 0;
          uStack_120 = 0;
          local_128 = 0;
          uStack_130 = 0;
          local_138 = 0;
          uStack_140 = 0;
          local_148 = 0;
          uStack_150 = 0;
          local_158 = 0;
          uStack_160 = 0;
          local_168 = 0;
          local_178 = 0;
          pLStack_180 = (LeAudioDevice *)0x0;
          local_188 = (void *)0x0;
          uStack_190 = 0;
          local_198 = (char *)0x0;
          pcStack_1a0 = (char *)0x0;
          local_1a8 = (LeAudioDevice *)0x0;
          pLStack_1b0 = (LeAudioDevice *)0x0;
          local_1b8 = (LeAudioDevice *)0x0;
          pLStack_1c0 = (LeAudioDevice *)0x0;
          local_1c8 = (LeAudioDevice *)0x0;
          pLStack_1d0 = (LeAudioDevice *)0x0;
          local_1d8 = (LeAudioDevice *)0x0;
          local_1f0 = (LeAudioDevice *)&PTR__istream_00f68ae0;
          ppuStack_170 = &PTR__istream_00f68b08;
          p_Stack_1e8 = (__tree_node *)0x0;
          local_2b4[0] = local_464._1_1_;
          local_1e0 = (LeAudioDevice *)&PTR__stringstream_00f689c8;
          std::ios_base::init((ios_base *)&ppuStack_170,&local_1d8);
          local_e8 = 0;
                    /* WARNING: Ignoring partial resolution of indirect */
          uStack_e0._0_4_ = 0xffffffff;
          local_1f0 = (LeAudioDevice *)&PTR__stringstream_00f689a0;
          local_1d8 = (LeAudioDevice *)&PTR__streambuf_00f68750;
          local_1e0 = (LeAudioDevice *)&PTR__stringstream_00f689c8;
          ppuStack_170 = &PTR__stringstream_00f689f0;
          std::locale::locale((locale *)&pLStack_1d0);
          pcStack_1a0 = (char *)0x0;
          local_1a8 = (LeAudioDevice *)0x0;
          pLStack_1b0 = (LeAudioDevice *)0x0;
          local_1b8 = (LeAudioDevice *)0x0;
          pLStack_1c0 = (LeAudioDevice *)0x0;
          local_1c8 = (LeAudioDevice *)0x0;
          local_1d8 = (LeAudioDevice *)&PTR__stringbuf_00f687d0;
          uStack_190 = 0;
          local_198 = (char *)0x0;
          pLStack_180 = (LeAudioDevice *)0x0;
          local_188 = (void *)0x0;
          local_178 = CONCAT44(local_178._4_4_,0x18);
          std::stringbuf::__init_buf_ptrs_abi_nn220000_((stringbuf *)&local_1d8);
          poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                              ((ostream *)&local_1e0,"fr ",3);
          loghex<unsigned_char>((uchar)local_c0._0_1_);
          pLVar18 = pLStack_268;
          pLVar30 = local_260;
          if ((local_270 & 1) == 0) {
            pLVar18 = (LeAudioDevice *)(local_270 >> 1 & 0x7f);
            pLVar30 = (LeAudioDevice *)((long)&local_270 + 1);
          }
          poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                              (poVar17,(char *)pLVar30,(ulong)pLVar18);
          poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                              (poVar17," phy ",5);
          loghex<unsigned_char>(local_c0._1_1_);
          pLVar18 = local_200;
          if (((ulong)local_210 & 1) == 0) {
            pLStack_208 = (LeAudioDevice *)((ulong)local_210 >> 1 & 0x7f);
            pLVar18 = (LeAudioDevice *)((long)&local_210 + 1);
          }
          poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                              (poVar17,(char *)pLVar18,(ulong)pLStack_208);
          poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                              (poVar17," rt ",4);
          poVar17 = (ostream *)std::ostream::operator<<(poVar17,(uint)local_c0._2_1_);
          poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                              (poVar17," lt ",4);
          poVar17 = (ostream *)std::ostream::operator<<(poVar17,(uint)local_c0._4_2_);
          poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                              (poVar17," pd_min ",8);
          poVar17 = (ostream *)std::ostream::operator<<(poVar17,(uint)uStack_b8);
          poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                              (poVar17," pd_max ",8);
          poVar17 = (ostream *)std::ostream::operator<<(poVar17,uStack_b8._4_4_);
          poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                              (poVar17," ppd_min ",9);
          poVar17 = (ostream *)std::ostream::operator<<(poVar17,(uint)local_b0);
          poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                              (poVar17," ppd_max ",9);
          poVar17 = (ostream *)std::ostream::operator<<(poVar17,local_b0._4_4_);
          poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                              (poVar17," cd ",4);
          loghex<unsigned_char>((uchar)uStack_a8);
          pLVar18 = local_240;
          if ((local_250 & 1) == 0) {
            pLStack_248 = (LeAudioDevice *)(local_250 >> 1 & 0x7f);
            pLVar18 = (LeAudioDevice *)((long)&local_250 + 1);
          }
          poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                              (poVar17,(char *)pLVar18,(ulong)pLStack_248);
          poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                              (poVar17," (v ",4);
          loghex<unsigned_short>(uStack_a8._2_2_);
          pLVar18 = pLStack_228;
          pLVar30 = local_220;
          if ((local_230 & 1) == 0) {
            pLVar18 = (LeAudioDevice *)(local_230 >> 1 & 0x7f);
            pLVar30 = (LeAudioDevice *)((long)&local_230 + 1);
          }
          poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                              (poVar17,(char *)pLVar30,(ulong)pLVar18);
          poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                              (poVar17," vc ",4);
          loghex<unsigned_short>(uStack_a8._4_2_);
          pcVar25 = local_280;
          pcVar4 = local_278;
          if ((local_288 & 1) == 0) {
            pcVar25 = (char *)(ulong)((byte)local_288._0_1_ >> 1);
            pcVar4 = (char *)((long)&local_288 + 1);
          }
          poVar17 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                              (poVar17,pcVar4,(ulong)pcVar25);
          std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>(poVar17,")",1);
          if ((local_288 & 1) != 0) {
            operator_delete(local_278,CONCAT44(uStack_284,local_288) & 0xfffffffffffffffe);
          }
          if ((local_230 & 1) != 0) {
            operator_delete(local_220,local_230 & 0xfffffffffffffffe);
          }
          if ((local_250 & 1) != 0) {
            operator_delete(local_240,local_250 & 0xfffffffffffffffe);
          }
          if (((ulong)local_210 & 1) != 0) {
            operator_delete(local_200,(ulong)local_210 & 0xfffffffffffffffe);
          }
          if ((local_270 & 1) != 0) {
            operator_delete(local_260,local_270 & 0xfffffffffffffffe);
          }
          uVar11 = *(undefined4 *)(param_5 + 0x14);
          plVar34 = (long *)param_1[3];
          std::to_string((uint)(byte)local_464);
          puVar12 = (ulong *)std::string::insert((string *)&local_230,0,"ASE_ID ",7);
          pLStack_248 = (LeAudioDevice *)puVar12[1];
          local_250 = *puVar12;
          local_240 = (LeAudioDevice *)puVar12[2];
          puVar12[1] = 0;
          puVar12[2] = 0;
          *puVar12 = 0;
          auVar35 = std::string::append((string *)&local_250,": ");
          puVar13 = auVar35._0_8_;
          pLStack_208 = (LeAudioDevice *)puVar13[1];
          local_210 = (LeAudioDevice *)*puVar13;
          local_200 = (LeAudioDevice *)puVar13[2];
          puVar13[1] = 0;
          puVar13[2] = 0;
          *puVar13 = 0;
          bluetooth::common::ToString<bluetooth::le_audio::types::AseState>(local_2b4,auVar35._8_8_)
          ;
          puVar12 = (ulong *)std::string::append_abi_nn220000_
                                       ((string *)&local_210,(string *)&local_288);
          pLStack_268 = (LeAudioDevice *)puVar12[1];
          local_270 = *puVar12;
          local_260 = (LeAudioDevice *)puVar12[2];
          puVar12[1] = 0;
          puVar12[2] = 0;
          *puVar12 = 0;
          if (((uint)local_178 >> 4 & 1) == 0) {
            if (((uint)local_178 >> 3 & 1) != 0) {
              ppLVar29 = &local_1c8;
              pLVar18 = local_1b8;
              goto LAB_0067994c;
            }
            pLVar30 = (LeAudioDevice *)0x0;
            pLVar18 = (LeAudioDevice *)0x0;
LAB_00679968:
            pcVar25 = (char *)((ulong)&local_2a0 | 1);
            local_2a0 = CONCAT71(local_2a0._1_7_,(char)((int)pLVar18 << 1));
          }
          else {
            if (pLStack_180 < local_1a8) {
              pLStack_180 = local_1a8;
            }
            ppLVar29 = &pLStack_1b0;
            pLVar18 = pLStack_180;
LAB_0067994c:
            pLVar30 = *ppLVar29;
            pLVar18 = pLVar18 + -(long)pLVar30;
            if ((LeAudioDevice *)0xfffffffffffffff6 < pLVar18) {
LAB_0067aa04:
                    /* WARNING: Subroutine does not return */
              std::string::__throw_length_error_abi_nn220000_();
            }
            if (pLVar18 < (LeAudioDevice *)0x17) goto LAB_00679968;
            uVar14 = 0x1a;
            if (((ulong)pLVar18 | 7) != 0x17) {
              uVar14 = ((ulong)pLVar18 | 7) + 1;
            }
            pcVar25 = (char *)FUN_00f62c00(uVar14);
            local_2a0 = uVar14 | 1;
            local_298 = pLVar18;
            local_290 = pcVar25;
          }
          memmove(pcVar25,pLVar30,(size_t)pLVar18);
          pcVar25[(long)pLVar18] = '\0';
          (**(code **)(*plVar34 + 0x18))(plVar34,&DAT_00faa5c0,uVar11,param_5,&local_270,&local_2a0)
          ;
          if ((local_2a0 & 1) != 0) {
            operator_delete(local_290,local_2a0 & 0xfffffffffffffffe);
          }
          if ((local_270 & 1) != 0) {
            operator_delete(local_260,local_270 & 0xfffffffffffffffe);
          }
          if ((local_288 & 1) != 0) {
            operator_delete(local_278,CONCAT44(uStack_284,local_288) & 0xfffffffffffffffe);
          }
          if (((ulong)local_210 & 1) != 0) {
            operator_delete(local_200,(ulong)local_210 & 0xfffffffffffffffe);
          }
          if ((local_250 & 1) != 0) {
            operator_delete(local_240,local_250 & 0xfffffffffffffffe);
          }
          if ((local_230 & 1) != 0) {
            operator_delete(local_220,local_230 & 0xfffffffffffffffe);
          }
          *(undefined1 *)(param_4 + 0xb) = 0;
          ::(anonymous_namespace)::LeAudioGroupStateMachineImpl::
          AseStateMachineProcessCodecConfigured(bluetooth::le_audio::client_parser::ascs::ase_rsp_hdr&,bluetooth::le_audio::types::ase*,unsigned_char*,unsigned_short,bluetooth::le_audio::LeAudioDeviceGroup*,bluetooth::le_audio::LeAudioDevice*)
          ::
          {lambda(bluetooth::le_audio::client_parser::ascs::ase_codec_configured_state_params_const&,bluetooth::le_audio::types::AseQosPreferences&,bluetooth::le_audio::types::AseQosConfiguration&)#1}
          ::operator()((_lambda_bluetooth__le_audio__client_parser__ascs__ase_codec_configured_state_params_const__bluetooth__le_audio__types__AseQosPreferences__bluetooth__le_audio__types__AseQosConfiguration___1_
                        *)&local_2b0,(ase_codec_configured_state_params *)&local_c0,
                       (AseQosPreferences *)(param_4 + 0x1c8),
                       (AseQosConfiguration *)(param_4 + 0x1b8));
          uVar14 = bluetooth::le_audio::LeAudioDevice::HaveAnyUnconfiguredAses(param_5);
          if ((uVar14 & 1) == 0) {
            if ((param_6[0x171] == (LeAudioDeviceGroup)0x4) &&
               (param_6[0x170] == (LeAudioDeviceGroup)0x4)) {
              if (param_5[6] == (LeAudioDevice)0x1) {
                uVar14 = PrepareAndSendConfigQos(param_1,param_6,param_5);
                if ((uVar14 & 1) == 0) {
                  puVar24 = local_3b8;
                  local_3b8[0] = 0xaf5;
                  local_3b0 = "packages/modules/Bluetooth/system/bta/le_audio/state_machine.cc";
                  pcStack_3a8 = "AseStateMachineProcessCodecConfigured";
LAB_00679bf8:
                  bluetooth::log::warn<int_const&,RawAddress&>::log(param_6,param_5,puVar24);
                }
              }
              else {
                local_3d8[0] = 0xafa;
                local_3d0 = "packages/modules/Bluetooth/system/bta/le_audio/state_machine.cc";
                pcStack_3c8 = "AseStateMachineProcessCodecConfigured";
                bluetooth::log::debug<RawAddress&>::log
                          (&uStack_3b9,
                           "Device {} initiated configured state but it is not yet ready to be configured"
                           ,0x4d,param_5,local_3d8);
              }
            }
            else {
              uVar14 = bluetooth::le_audio::LeAudioDeviceGroup::
                       HaveAnyActiveDeviceInUnconfiguredState(param_6);
              if ((uVar14 & 1) == 0) {
                bluetooth::le_audio::LeAudioDeviceGroup::SetState(param_6,1);
                LVar2 = param_6[0x170];
                if (LVar2 == (LeAudioDeviceGroup)0x1) {
                  auVar35 = bluetooth::le_audio::LeAudioDeviceGroup::IsPendingConfiguration(param_6)
                  ;
                  pAVar23 = auVar35._8_8_;
                  if ((auVar35._0_8_ & 1) == 0) goto LAB_0067a674;
                  local_270 = CONCAT44(local_270._4_4_,0xb29);
                  pLStack_268 = (LeAudioDevice *)0x1d97f3;
                  local_260 = (LeAudioDevice *)0x198ab9;
                  local_210 = (LeAudioDevice *)0x0;
                  bluetooth::log_internal::vlog
                            (4,"bluetooth",&local_270,"Configured state completed",0x1a,&local_210);
                  bluetooth::le_audio::LeAudioDeviceGroup::ClearPendingConfiguration(param_6);
                  (**(code **)(*(long *)param_1[1] + 0x10))
                            ((long *)param_1[1],*(undefined4 *)param_6,7);
                  (**(code **)(*param_1 + 0x98))(param_1,*(undefined4 *)param_6);
                }
                else if ((LVar2 == (LeAudioDeviceGroup)0x4) ||
                        (pAVar23 = extraout_x1_24, LVar2 == (LeAudioDeviceGroup)0x2)) {
                  if (param_6[0x10] == (LeAudioDeviceGroup)0x2) {
                    uVar14 = PrepareAndSendConfigQos(param_1,param_6,param_5);
                    if ((uVar14 & 1) == 0) {
                      puVar24 = local_408;
                      local_408[0] = 0xb1b;
                      local_400 = "packages/modules/Bluetooth/system/bta/le_audio/state_machine.cc";
                      pcStack_3f8 = "AseStateMachineProcessCodecConfigured";
                      goto LAB_00679bf8;
                    }
                  }
                  else {
                    uVar14 = CigCreate(param_1,param_6);
                    if ((uVar14 & 1) == 0) {
                      local_428[0] = 0xb20;
                      local_420 = "packages/modules/Bluetooth/system/bta/le_audio/state_machine.cc";
                      pcStack_418 = "AseStateMachineProcessCodecConfigured";
                      bluetooth::log::error<int>::log
                                (&uStack_409,"Could not create CIG. Stop the stream for group {}",
                                 0x32,param_6,local_428);
                      (**(code **)(*(long *)param_1[1] + 0x30))
                                ((long *)param_1[1],*(undefined4 *)param_6,1);
                    }
                  }
                }
                else {
LAB_0067a674:
                  local_250 = CONCAT71(local_250._1_7_,param_6[0x171]);
                  bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                            ((common *)&local_250,pAVar23);
                  local_230 = CONCAT71(local_230._1_7_,param_6[0x170]);
                  bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                            ((common *)&local_230,extraout_x1_28);
                  local_448[0] = 0xb33;
                  local_440 = "packages/modules/Bluetooth/system/bta/le_audio/state_machine.cc";
                  pcStack_438 = "AseStateMachineProcessCodecConfigured";
                  bluetooth::log::info<std::string,std::string>::log
                            (&uStack_429,"Autonomous change, from: {} to {}",0x21,&local_270,
                             &local_210,local_448);
                  if (((ulong)local_210 & 1) != 0) {
                    operator_delete(local_200,(ulong)local_210 & 0xfffffffffffffffe);
                  }
                  if ((local_270 & 1) != 0) {
                    operator_delete(local_260,local_270 & 0xfffffffffffffffe);
                  }
                }
              }
              else {
                local_3f0[0] = 0xb02;
                local_3e8 = "packages/modules/Bluetooth/system/bta/le_audio/state_machine.cc";
                pcStack_3e0 = "AseStateMachineProcessCodecConfigured";
                bluetooth::log::debug<int_const&>::log(param_6,local_3f0);
              }
            }
          }
          goto LAB_0067a728;
        }
LAB_006787f0:
        (**(code **)(*(long *)param_1[1] + 0x30))((long *)param_1[1],*(undefined4 *)param_6,6);
      }
      if (local_a0 == (LeAudioDevice *)0x0) goto LAB_006782bc;
      local_98 = local_a0;
      pLVar18 = local_a0;
      pLVar30 = local_90;
LAB_0067a784:
      operator_delete(pLVar18,(long)pLVar30 - (long)pLVar18);
      goto LAB_006782bc;
    }
    uVar27 = (uint)*(byte *)(param_4 + 0x310);
    if (*(byte *)(param_4 + 0x310) < 5) {
      if (uVar27 - 3 < 2) {
        bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                  ((common *)(param_4 + 0x310),pAVar23);
        local_230 = local_230 & 0xffffffffffffff00;
        bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                  ((common *)&local_230,extraout_x1_10);
        uStack_b8 = (code *)0x1d97f3;
        local_b0 = "AseStateMachineProcessIdle";
        local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0x945);
        p_Stack_1e8 = (__tree_node *)pLStack_208;
        local_1f0 = local_200;
        if (((ulong)local_210 & 1) == 0) {
          p_Stack_1e8 = (__tree_node *)((ulong)local_210 >> 1 & 0x7f);
          local_1f0 = (LeAudioDevice *)((long)&local_210 + 1);
        }
        local_1d8 = pLStack_248;
        local_1e0 = local_240;
        if ((local_250 & 1) == 0) {
          local_1d8 = (LeAudioDevice *)(local_250 >> 1 & 0x7f);
          local_1e0 = (LeAudioDevice *)((long)&local_250 + 1);
        }
        pLStack_1c0 = (LeAudioDevice *)(ulong)*pbVar32;
        local_1c8 = (LeAudioDevice *)
                    _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
        ;
        pLStack_268 = (LeAudioDevice *)&local_1f0;
        pLStack_1b0 = (LeAudioDevice *)0x33dad;
        local_1b8 = (LeAudioDevice *)0x0;
        local_270 = 4;
        local_260 = (LeAudioDevice *)0x33dad;
        pLStack_1d0 = param_5;
        bluetooth::log_internal::vlog
                  (6,"bluetooth",&local_c0,
                   "Invalid state transition from {} to {}, {}, ase_id: {}. Stopping the stream.",
                   0x4c,&local_270);
        if ((local_250 & 1) != 0) {
          operator_delete(local_240,local_250 & 0xfffffffffffffffe);
        }
        if (((ulong)local_210 & 1) != 0) {
          operator_delete(local_200,(ulong)local_210 & 0xfffffffffffffffe);
        }
        bluetooth::le_audio::LeAudioDeviceGroup::PrintDebugState(param_6);
        goto LAB_00677ee4;
      }
      if (uVar27 != 2) goto LAB_006782bc;
LAB_00677d80:
      bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                ((common *)(param_4 + 0x310),pAVar23);
      local_230 = local_230 & 0xffffffffffffff00;
      bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                ((common *)&local_230,extraout_x1_18);
      uStack_b8 = (code *)0x1d97f3;
      local_b0 = "AseStateMachineProcessIdle";
      local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0x93e);
      p_Stack_1e8 = (__tree_node *)pLStack_208;
      local_1f0 = local_200;
      if (((ulong)local_210 & 1) == 0) {
        p_Stack_1e8 = (__tree_node *)((ulong)local_210 >> 1 & 0x7f);
        local_1f0 = (LeAudioDevice *)((long)&local_210 + 1);
      }
      local_1d8 = pLStack_248;
      local_1e0 = local_240;
      if ((local_250 & 1) == 0) {
        local_1d8 = (LeAudioDevice *)(local_250 >> 1 & 0x7f);
        local_1e0 = (LeAudioDevice *)((long)&local_250 + 1);
      }
      pLStack_1c0 = (LeAudioDevice *)(ulong)*pbVar32;
      local_1c8 = (LeAudioDevice *)
                  _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
      ;
      pLStack_268 = (LeAudioDevice *)&local_1f0;
      pLStack_1b0 = (LeAudioDevice *)0x33dad;
      local_1b8 = (LeAudioDevice *)0x0;
      local_270 = 4;
      local_260 = (LeAudioDevice *)0x33dad;
      pLStack_1d0 = param_5;
      bluetooth::log_internal::vlog
                (6,"bluetooth",&local_c0,
                 "Ignore invalid attempt of state transition from  {} to {}, {}, ase_id: {}",0x49,
                 &local_270);
      if ((local_250 & 1) != 0) {
        operator_delete(local_240,local_250 & 0xfffffffffffffffe);
      }
      goto LAB_006781dc;
    }
    if (uVar27 == 5) goto LAB_00677d80;
    if (uVar27 != 6) goto LAB_006782bc;
    SetAseState(param_5,param_4,0);
    *(undefined1 *)(param_4 + 10) = 0;
    *(undefined2 *)(param_4 + 0x14) = 0;
    uVar14 = bluetooth::le_audio::LeAudioDevice::HaveAllActiveAsesSameState(param_5,0);
    if ((uVar14 & 1) == 0) {
      local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0x914);
      local_b0 = "AseStateMachineProcessIdle";
LAB_00679230:
      local_260 = (LeAudioDevice *)&DAT_0000000f;
      p_Stack_1e8 = (__tree_node *)
                    _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
      ;
      local_270 = 1;
      pcVar25 = "Wait for more ASE to configure for device {}";
      uVar36 = 3;
      uVar26 = 0x2c;
      local_1e0 = (LeAudioDevice *)&DAT_0000000f;
      local_1f0 = param_5;
LAB_00679274:
      uStack_b8 = (code *)0x1d97f3;
      pLStack_268 = (LeAudioDevice *)&local_1f0;
      bluetooth::log_internal::vlog(uVar36,"bluetooth",&local_c0,pcVar25,uVar26,&local_270);
      goto LAB_006782bc;
    }
    uVar14 = bluetooth::le_audio::LeAudioDeviceGroup::HaveAllActiveDevicesAsesTheSameState
                       (param_6,0);
    if ((uVar14 & 1) == 0) {
      local_1f0 = (LeAudioDevice *)CONCAT44(local_1f0._4_4_,0x919);
      local_1e0 = (LeAudioDevice *)0x112abb;
      pcVar25 = "Waiting for more devices to get into idle state";
      uVar26 = 0x2f;
LAB_0067917c:
      uVar36 = 3;
      goto LAB_006774b0;
    }
    bluetooth::le_audio::LeAudioDeviceGroup::SetState(param_6,0);
    bluetooth::le_audio::LeAudioDeviceGroup::PrintDebugState(param_6);
    uVar14 = bluetooth::le_audio::LeAudioDeviceGroup::HaveAllCisesDisconnected(param_6);
    if (((uVar14 & 1) != 0) && (lVar16 = getDeviceTryingToAttachTheStream(param_6), lVar16 == 0)) {
      (**(code **)(*param_1 + 0x98))(param_1,*(undefined4 *)param_6);
      pLVar18 = (LeAudioDevice *)
                bluetooth::le_audio::LeAudioDeviceGroup::GetFirstActiveDevice(param_6);
      if (pLVar18 != (LeAudioDevice *)0x0) {
        do {
          uVar7 = BTM_GetHCIConnHandle(pLVar18,2);
          local_210 = (LeAudioDevice *)CONCAT44(local_210._4_4_,0x1000026);
          uVar36 = local_210;
          local_210._0_2_ = CONCAT11((char)uVar7,0x26);
          local_210._3_5_ = SUB85(uVar36,3);
          local_210._0_3_ = CONCAT12((char)((ushort)uVar7 >> 8),(undefined2)local_210);
          local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0xffd);
          uStack_b8 = (code *)0x1d97f3;
          local_b0 = "QbceQleSetConnEventDuration";
          local_1e0 = (LeAudioDevice *)0x3;
          p_Stack_1e8 = (__tree_node *)0x0;
          local_1f0 = (LeAudioDevice *)0x1;
          local_270 = 1;
          local_260 = (LeAudioDevice *)0x3;
          pLStack_268 = (LeAudioDevice *)&local_1f0;
          bluetooth::log_internal::vlog
                    (4,"bluetooth",&local_c0,"HCI_VSC_QBCE_QLE_ENABLE_CONN_EVENT_DURATION : {}",0x30
                     ,&local_270);
          BTM_VendorSpecificCommand
                    (0xfc51,'\x04',(uchar *)&local_210,(_func_void_tBTM_VSC_CMPL_ptr *)0x0);
          pLVar18 = (LeAudioDevice *)
                    bluetooth::le_audio::LeAudioDeviceGroup::GetNextActiveDevice(param_6,pLVar18);
        } while (pLVar18 != (LeAudioDevice *)0x0);
      }
      ReleaseCisIds(param_6);
      uVar11 = *(undefined4 *)param_6;
      uVar36 = 0;
      plVar34 = (long *)param_1[1];
      goto LAB_0067a2a8;
    }
    local_1f0 = (LeAudioDevice *)(ulong)*(uint *)param_6;
    pLStack_268 = (LeAudioDevice *)&local_1f0;
    local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0x925);
    uStack_b8 = (code *)0x1d97f3;
    local_b0 = "AseStateMachineProcessIdle";
    local_1e0 = (LeAudioDevice *)0x3;
    p_Stack_1e8 = (__tree_node *)0x0;
    local_270 = 1;
    local_260 = (LeAudioDevice *)0x3;
    bluetooth::log_internal::vlog
              (5,"bluetooth",&local_c0,
               "Not all CISes removed before going to IDLE for group {}, waiting...",0x43,&local_270
              );
  }
  else {
    if (4 < (byte)local_468[0]) {
      if (local_468[0] == (common)0x5) {
        if (param_6 == (LeAudioDeviceGroup *)0x0) {
          local_1f0 = (LeAudioDevice *)CONCAT44(local_1f0._4_4_,0xedd);
          local_1e0 = (LeAudioDevice *)0x132996;
          goto LAB_0067748c;
        }
        if (*(char *)(param_4 + 6) == '\x01') {
          local_230 = CONCAT71(local_230._1_7_,param_6[0x171]);
          bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                    ((common *)&local_230,pAVar23);
          local_288 = CONCAT31(local_288._1_3_,param_6[0x170]);
          bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                    ((common *)&local_288,extraout_x1_12);
          uStack_b8 = (code *)0x1d97f3;
          local_b0 = "AseStateMachineProcessDisabling";
          local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0xee4);
          p_Stack_1e8 = (__tree_node *)pLStack_208;
          local_1f0 = local_200;
          if (((ulong)local_210 & 1) == 0) {
            p_Stack_1e8 = (__tree_node *)((ulong)local_210 >> 1 & 0x7f);
            local_1f0 = (LeAudioDevice *)((long)&local_210 + 1);
          }
          local_1d8 = pLStack_248;
          local_1e0 = local_240;
          if ((local_250 & 1) == 0) {
            local_1e0 = (LeAudioDevice *)((long)&local_250 + 1);
            local_1d8 = (LeAudioDevice *)(local_250 >> 1 & 0x7f);
          }
          pLStack_268 = (LeAudioDevice *)&local_1f0;
          pLStack_1d0 = (LeAudioDevice *)0x1ad;
          local_270 = 2;
          local_260 = (LeAudioDevice *)0x1ad;
          bluetooth::log_internal::vlog
                    (6,"bluetooth",&local_c0,", invalid state transition, from: {} , to: {}",0x2d,
                     &local_270);
          if ((local_250 & 1) != 0) {
            operator_delete(local_240,local_250 & 0xfffffffffffffffe);
          }
          if (((ulong)local_210 & 1) != 0) {
            operator_delete(local_200,(ulong)local_210 & 0xfffffffffffffffe);
          }
        }
        else {
          bVar6 = *(byte *)(param_4 + 0x310);
          if (bVar6 == 3) goto LAB_006782bc;
          if (bVar6 == 4) {
            SetAseState(param_5,param_4,5);
            if (param_6[0x170] == (LeAudioDeviceGroup)0x2) {
              uVar14 = bluetooth::le_audio::LeAudioDevice::IsReadyToSuspendStream(param_5);
              if ((uVar14 & 1) == 0) goto LAB_006782bc;
LAB_00679340:
              ProcessGroupDisable(param_1,param_6);
              goto LAB_006782bc;
            }
            if (*(char *)(param_4 + 0x311) == '\x05') {
              PrepareAndSendReceiverStopReady(param_1,param_5,param_4);
              goto LAB_006782bc;
            }
            local_1e0 = (LeAudioDevice *)(ulong)*pbVar32;
            pLStack_268 = (LeAudioDevice *)&local_1f0;
            local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0x108f);
            uStack_b8 = (code *)0x1d97f3;
            local_b0 = "ProcessAutonomousDisable";
            p_Stack_1e8 = (__tree_node *)
                          _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
            ;
            pLStack_1d0 = (LeAudioDevice *)0xcf;
            local_1d8 = (LeAudioDevice *)0x0;
            local_270 = 2;
            local_260 = (LeAudioDevice *)0xcf;
            local_1f0 = param_5;
            bluetooth::log_internal::vlog(4,"bluetooth",&local_c0,"{}, ase {}",10,&local_270);
            uVar14 = bluetooth::le_audio::LeAudioDeviceGroup::HaveAnyActiveDeviceInStreamingState
                               (param_6);
            if (((uVar14 & 1) != 0) &&
               (uVar14 = bluetooth::le_audio::LeAudioDeviceGroup::HaveAllCisesDisconnected(param_6),
               (uVar14 & 1) == 0)) goto LAB_006782bc;
            uVar11 = *(undefined4 *)param_6;
            uVar36 = 0;
LAB_00678930:
            plVar34 = (long *)param_1[1];
            pcVar28 = *(code **)(*plVar34 + 0x30);
            goto LAB_006782b8;
          }
          local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0xf06);
          uStack_b8 = (code *)0x1d97f3;
          local_b0 = "AseStateMachineProcessDisabling";
          pLStack_268 = (LeAudioDevice *)&local_1f0;
          local_1e0 = (LeAudioDevice *)&DAT_00000005;
          p_Stack_1e8 = (__tree_node *)0x0;
          pLStack_1d0 = (LeAudioDevice *)0x63;
          local_1d8 = (LeAudioDevice *)0x0;
          local_270 = 2;
          local_260 = (LeAudioDevice *)0x63;
          local_1f0 = (LeAudioDevice *)(ulong)bVar6;
          bluetooth::log_internal::vlog
                    (6,"bluetooth",&local_c0,"invalid state transition, from: {}, to: {}",0x2a,
                     &local_270);
        }
        uVar11 = *(undefined4 *)param_6;
LAB_006782a8:
        plVar34 = (long *)param_1[1];
        pcVar28 = *(code **)(*plVar34 + 0x30);
        uVar36 = 7;
LAB_006782b8:
        (*pcVar28)(plVar34,uVar11,uVar36);
        goto LAB_006782bc;
      }
      if (local_468[0] != (common)0x6) goto LAB_00676f6c;
      if (param_6 == (LeAudioDeviceGroup *)0x0) {
        local_1f0 = (LeAudioDevice *)CONCAT44(local_1f0._4_4_,0xf44);
        local_1e0 = (LeAudioDevice *)0x1613da;
        goto LAB_0067748c;
      }
      bVar6 = *(byte *)(param_4 + 0x310);
      uVar27 = (uint)bVar6;
      if (bVar6 < 4) {
        if (uVar27 - 1 < 2) goto LAB_00677c8c;
        if (uVar27 != 3) {
LAB_006782f8:
          local_260 = (LeAudioDevice *)0x63;
          local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0xf9b);
          local_b0 = "AseStateMachineProcessReleasing";
          local_1e0 = (LeAudioDevice *)&DAT_00000006;
          local_270 = 2;
          pcVar25 = "invalid state transition, from: {}, to: {}";
          uVar36 = 6;
          uVar26 = 0x2a;
          p_Stack_1e8 = (__tree_node *)0x0;
          pLStack_1d0 = (LeAudioDevice *)0x63;
          local_1d8 = (LeAudioDevice *)0x0;
          local_1f0 = (LeAudioDevice *)(ulong)bVar6;
          goto LAB_00679274;
        }
        SetAseState(param_5,param_4,6);
        iVar10 = DisconnectCisIfNeeded(param_1,param_6,param_5,param_4);
        uVar14 = bluetooth::le_audio::LeAudioDeviceGroup::HaveAllActiveDevicesAsesTheSameState
                           (param_6,6);
        if ((uVar14 & 1) == 0) goto LAB_006782bc;
        bluetooth::le_audio::LeAudioDeviceGroup::SetState(param_6,6);
        local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0x172);
        uStack_b8 = (code *)0x17f5f4;
        local_b0 = "ClearStreamingMetadataContexts";
        local_1f0 = (LeAudioDevice *)(ulong)*(uint *)param_6;
        pLStack_268 = (LeAudioDevice *)&local_1f0;
        local_1e0 = (LeAudioDevice *)0x3;
        p_Stack_1e8 = (__tree_node *)0x0;
        local_270 = 1;
        local_260 = (LeAudioDevice *)0x3;
        bluetooth::log_internal::vlog(3,"bluetooth",&local_c0,"group_id: {}",0xc,&local_270);
        *(undefined4 *)(param_6 + 0x126) = 0;
        if (iVar10 != 0) goto LAB_006782bc;
      }
      else {
        if (uVar27 == 4) {
          SetAseState(param_5,param_4,6);
          if (*(uint *)(param_4 + 0xc) == 4) goto LAB_006782bc;
          uVar27 = *(uint *)(param_4 + 0x10);
          if (uVar27 == 2) {
            RemoveDataPathByCisHandle(param_5,*(undefined2 *)(param_4 + 8));
          }
          else if (((*(uint *)(param_4 + 0xc) & 0xfffffffe) == 2) && (uVar27 == 0)) {
            btif_dm_log_collector_cback
                      ("LEASESM-Send CIS Disc Req, cis_hdl : %d by Releasing",
                       (ulong)*(ushort *)(param_4 + 8));
            DisconnectCisIfNeeded(param_1,param_6,param_5,param_4);
          }
          else {
            local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0xf88);
            uStack_b8 = (code *)0x1d97f3;
            local_b0 = "AseStateMachineProcessReleasing";
            pLStack_268 = (LeAudioDevice *)&local_1f0;
            local_1e0 = (LeAudioDevice *)0x3;
            p_Stack_1e8 = (__tree_node *)0x0;
            local_270 = 1;
            local_260 = (LeAudioDevice *)0x3;
            local_1f0 = (LeAudioDevice *)(ulong)uVar27;
            bluetooth::log_internal::vlog
                      (3,"bluetooth",&local_c0,"Nothing to do ase data path state: {}",0x25,
                       &local_270);
          }
          uVar14 = bluetooth::le_audio::LeAudioDeviceGroup::HaveAllActiveDevicesAsesTheSameState
                             (param_6,6);
          if ((uVar14 & 1) == 0) goto LAB_006782bc;
          bluetooth::le_audio::LeAudioDeviceGroup::SetState(param_6,6);
          local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0x172);
          uStack_b8 = (code *)0x17f5f4;
          local_b0 = "ClearStreamingMetadataContexts";
          local_1f0 = (LeAudioDevice *)(ulong)*(uint *)param_6;
          pLStack_268 = (LeAudioDevice *)&local_1f0;
          local_1e0 = (LeAudioDevice *)0x3;
          p_Stack_1e8 = (__tree_node *)0x0;
          local_270 = 1;
          local_260 = (LeAudioDevice *)0x3;
          bluetooth::log_internal::vlog(3,"bluetooth",&local_c0,"group_id: {}",0xc,&local_270);
          *(undefined4 *)(param_6 + 0x126) = 0;
          if (param_6[0x170] != (LeAudioDeviceGroup)0x4) goto LAB_006782bc;
          local_1f0 = (LeAudioDevice *)CONCAT44(local_1f0._4_4_,0xf91);
          p_Stack_1e8 = (__tree_node *)0x1d97f3;
          local_1e0 = (LeAudioDevice *)0x1613da;
          bluetooth::log::info<int_const&>::log(param_6,&local_1f0);
          SetTargetState(param_1,param_6,0);
          plVar34 = (long *)param_1[1];
          uVar11 = *(undefined4 *)param_6;
          uVar36 = 3;
LAB_0067a2a8:
          pcVar28 = *(code **)(*plVar34 + 0x10);
          goto LAB_006782b8;
        }
        if (uVar27 != 5) goto LAB_006782f8;
LAB_00677c8c:
        SetAseState(param_5,param_4,6);
        uVar14 = bluetooth::le_audio::LeAudioDeviceGroup::HaveAllActiveDevicesAsesTheSameState
                           (param_6,6);
        if ((uVar14 & 1) != 0) {
          bluetooth::le_audio::LeAudioDeviceGroup::SetState(param_6,6);
          local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0x172);
          uStack_b8 = (code *)0x17f5f4;
          local_b0 = "ClearStreamingMetadataContexts";
          local_1f0 = (LeAudioDevice *)(ulong)*(uint *)param_6;
          pLStack_268 = (LeAudioDevice *)&local_1f0;
          local_1e0 = (LeAudioDevice *)0x3;
          p_Stack_1e8 = (__tree_node *)0x0;
          local_270 = 1;
          local_260 = (LeAudioDevice *)0x3;
          bluetooth::log_internal::vlog(3,"bluetooth",&local_c0,"group_id: {}",0xc,&local_270);
          *(undefined4 *)(param_6 + 0x126) = 0;
        }
        iVar10 = DisconnectCisIfNeeded(param_1,param_6,param_5,param_4);
        if ((((iVar10 != 0) || (param_6[0x10] != (LeAudioDeviceGroup)0x2)) ||
            (uVar14 = bluetooth::le_audio::LeAudioDeviceGroup::HaveAllCisesDisconnected(param_6),
            (uVar14 & 1) == 0)) || (lVar16 = getDeviceTryingToAttachTheStream(param_6), lVar16 != 0)
           ) goto LAB_006782bc;
      }
      RemoveCigForGroup(param_1,param_6,3);
      goto LAB_006782bc;
    }
    if (local_468[0] != (common)0x3) {
      if (local_468[0] != (common)0x4) {
LAB_00676f6c:
        local_1f0 = (LeAudioDevice *)(ulong)(byte)local_464._1_1_;
        pLStack_268 = (LeAudioDevice *)&local_1f0;
        local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0x2b7);
        uStack_b8 = (code *)0x1d97f3;
        local_b0 = "ProcessGattNotifEvent";
        local_1e0 = (LeAudioDevice *)0x3;
        p_Stack_1e8 = (__tree_node *)0x0;
        local_270 = 1;
        local_260 = (LeAudioDevice *)0x3;
        bluetooth::log_internal::vlog(6,"bluetooth",&local_c0,"Wrong AES state: {}",0x13,&local_270)
        ;
        plVar34 = (long *)param_1[1];
        uVar11 = *(undefined4 *)param_6;
        pcVar28 = *(code **)(*plVar34 + 0x30);
LAB_00676fe0:
        uVar36 = 5;
        goto LAB_006782b8;
      }
      if (param_6 == (LeAudioDeviceGroup *)0x0) {
        local_1f0 = (LeAudioDevice *)CONCAT44(local_1f0._4_4_,0xe69);
        local_1e0 = (LeAudioDevice *)0x11b754;
        goto LAB_0067748c;
      }
      pLStack_268 = (LeAudioDevice *)0x0;
      local_270 = 0;
      local_258 = (LeAudioDevice *)0x0;
      local_260 = (LeAudioDevice *)0x0;
      uVar14 = bluetooth::le_audio::client_parser::ascs::ParseAseStatusTransientStateParams
                         (&local_270,param_3 + -2,param_2 + 2);
      local_1f0 = (LeAudioDevice *)&p_Stack_1e8;
      local_2d0._0_4_ = 0;
      local_c8 = 0;
      uStack_e0 = 0;
      local_e8 = 0;
      uStack_d0 = 0;
      uStack_d8 = 0;
      uStack_f0 = 0;
      local_f8 = 0;
      uStack_100 = 0;
      local_108 = 0;
      uStack_110 = 0;
      local_118 = 0;
      uStack_120 = 0;
      local_128 = 0;
      uStack_130 = 0;
      local_138 = 0;
      uStack_140 = 0;
      local_148 = 0;
      uStack_150 = 0;
      local_158 = 0;
      uStack_160 = 0;
      local_168 = 0;
      ppuStack_170 = (undefined **)0x0;
      local_178 = 0;
      pLStack_180 = (LeAudioDevice *)0x0;
      local_188 = (void *)0x0;
      uStack_190 = 0;
      local_198 = (char *)0x0;
      pcStack_1a0 = (char *)0x0;
      local_1a8 = (LeAudioDevice *)0x0;
      pLStack_1b0 = (LeAudioDevice *)0x0;
      local_1b8 = (LeAudioDevice *)0x0;
      pLStack_1c0 = (LeAudioDevice *)0x0;
      local_1c8 = (LeAudioDevice *)0x0;
      pLStack_1d0 = (LeAudioDevice *)0x0;
      local_1d8 = (LeAudioDevice *)0x0;
      local_1e0 = (LeAudioDevice *)0x0;
      p_Stack_1e8 = (__tree_node *)0x0;
      if ((((uVar14 & 1) != 0) && (pLStack_268 != local_260)) &&
         (uVar15 = bluetooth::le_audio::types::LeAudioLtvMap::Parse
                             (&local_1f0,pLStack_268,(int)local_260 - (int)pLStack_268),
         (uVar15 & 1) != 0)) {
        lVar16 = bluetooth::le_audio::types::LeAudioLtvMap::GetAsLeAudioMetadata
                           ((LeAudioLtvMap *)&local_1f0);
        if (local_2d0[2] == *(char *)(lVar16 + 6)) {
          if (local_2d0[2] == '\0') {
LAB_00679094:
            bluetooth::common::ToHexString(&local_230,(ulong)&local_270 | 8);
            local_210 = (LeAudioDevice *)CONCAT44(local_210._4_4_,0xe78);
            local_200 = (LeAudioDevice *)0x11b754;
            uStack_b8 = 
            _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
            ;
            local_b0 = (char *)(ulong)*pbVar32;
            uStack_a8 = 0;
            local_a0 = local_220;
            local_98 = pLStack_228;
            if ((local_230 & 1) == 0) {
              local_a0 = (LeAudioDevice *)((long)&local_230 + 1);
              local_98 = (LeAudioDevice *)(local_230 >> 1 & 0x7f);
            }
            local_90 = (LeAudioDevice *)0x34cf;
            pLStack_248 = (LeAudioDevice *)&local_c0;
            pLStack_208 = (LeAudioDevice *)0x1d97f3;
            local_250 = 3;
            local_240 = (LeAudioDevice *)0x34cf;
            local_c0 = param_5;
            bluetooth::log_internal::vlog
                      (6,"bluetooth",&local_210,
                       "{}, ase_id: {}, Did not found streaming metadata while parsing metadata: {}"
                       ,0x4b,&local_250);
            if ((local_230 & 1) != 0) {
              operator_delete(local_220,local_230 & 0xfffffffffffffffe);
            }
            goto LAB_00679488;
          }
          uVar7 = *(undefined2 *)(lVar16 + 4);
        }
        else {
          if (local_2d0[2] != '\0') {
            local_2d0[2] = 0;
            goto LAB_00679094;
          }
          uVar7 = *(undefined2 *)(lVar16 + 4);
          local_2d0._0_3_ = 0x10000;
        }
        local_2d0._0_2_ = uVar7;
      }
LAB_00679488:
      bVar6 = *(byte *)(param_4 + 0x310);
      if (bVar6 == 4) {
        if ((uVar14 & 1) != 0) {
          if (local_2d0[2] == '\x01') {
            bluetooth::le_audio::LeAudioDeviceGroup::SetStreamingMetadataContexts
                      (param_6,local_2d0,*(undefined1 *)(param_4 + 6));
          }
          goto LAB_006796a8;
        }
        uVar36 = 6;
        plVar34 = (long *)param_1[1];
        uVar11 = *(undefined4 *)param_6;
LAB_0067969c:
        pcVar28 = *(code **)(*plVar34 + 0x30);
LAB_006796a4:
        (*pcVar28)(plVar34,uVar11,uVar36);
      }
      else {
        if (bVar6 != 3) {
          if (bVar6 == 2) {
            local_b0 = (char *)(ulong)*pbVar32;
            pLStack_208 = (LeAudioDevice *)0x1d97f3;
            local_210 = (LeAudioDevice *)CONCAT44(local_210._4_4_,0xe7f);
            local_200 = (LeAudioDevice *)0x11b754;
            uStack_b8 = 
            _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
            ;
            pLStack_248 = (LeAudioDevice *)&local_c0;
            uStack_a8 = 0;
            local_a0 = (LeAudioDevice *)0xcf;
            local_250 = 2;
            local_240 = (LeAudioDevice *)0xcf;
            local_c0 = param_5;
            bluetooth::log_internal::vlog
                      (6,"bluetooth",&local_210,
                       "{}, ase_id: {}, moving from QoS Configured to Streaming is impossible.",0x46
                       ,&local_250);
            bluetooth::le_audio::LeAudioDeviceGroup::PrintDebugState(param_6);
          }
          else {
            pLStack_208 = (LeAudioDevice *)0x1d97f3;
            pLStack_248 = (LeAudioDevice *)&local_c0;
            local_210 = (LeAudioDevice *)CONCAT44(local_210._4_4_,0xed1);
            local_200 = (LeAudioDevice *)0x11b754;
            uStack_b8 = (code *)0x0;
            local_b0 = &DAT_00000004;
            uStack_a8 = 0;
            local_a0 = (LeAudioDevice *)0x63;
            local_250 = 2;
            local_240 = (LeAudioDevice *)0x63;
            local_c0 = (LeAudioDevice *)(ulong)bVar6;
            bluetooth::log_internal::vlog
                      (6,"bluetooth",&local_210,"invalid state transition, from: {}, to: {}",0x2a,
                       &local_250);
          }
LAB_0067968c:
          uVar11 = *(undefined4 *)param_6;
          uVar36 = 7;
          plVar34 = (long *)param_1[1];
          goto LAB_0067969c;
        }
        SetAseState(param_5,param_4,4);
        if (local_2d0[2] == '\x01') {
          bluetooth::le_audio::LeAudioDeviceGroup::SetStreamingMetadataContexts
                    (param_6,local_2d0,*(undefined1 *)(param_4 + 6));
        }
        uVar14 = bluetooth::le_audio::LeAudioDeviceGroup::HasAllRequiredStreamingAses(param_6);
        if ((uVar14 & 1) != 0) {
          auVar35 = bluetooth::le_audio::LeAudioDeviceGroup::IsGroupStreamReady(param_6);
          if ((auVar35._0_8_ & 1) == 0) {
            local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0xe96);
            uStack_b8 = (code *)0x1d97f3;
            local_b0 = "AseStateMachineProcessStreaming";
            local_210 = (LeAudioDevice *)0x0;
            bluetooth::log_internal::vlog
                      (4,"bluetooth",&local_c0,"CISes are not yet ready, wait for it.",0x25,
                       &local_210);
            param_6[0xe0] = (LeAudioDeviceGroup)0x1;
            goto LAB_006796a8;
          }
          if (param_6[0x171] != (LeAudioDeviceGroup)0x4) {
            auVar35 = bluetooth::le_audio::LeAudioDeviceGroup::GetFirstActiveDevice(param_6);
            pAVar23 = auVar35._8_8_;
            pLVar18 = auVar35._0_8_;
            if (pLVar18 != (LeAudioDevice *)0x0) {
              do {
                uVar7 = BTM_GetHCIConnHandle(pLVar18,2);
                local_230 = CONCAT44(local_230._4_4_,0x1000026);
                uVar36 = local_230;
                local_230._3_5_ = SUB85(uVar36,3);
                local_230._0_3_ = CONCAT12((char)((ushort)uVar7 >> 8),CONCAT11((char)uVar7,0x26));
                local_210 = (LeAudioDevice *)CONCAT44(local_210._4_4_,0xffd);
                pLStack_208 = (LeAudioDevice *)0x1d97f3;
                local_200 = (LeAudioDevice *)0x159044;
                uStack_b8 = (code *)0x0;
                local_b0 = (char *)0x3;
                local_c0 = (LeAudioDevice *)0x1;
                local_250 = 1;
                local_240 = (LeAudioDevice *)0x3;
                pLStack_248 = (LeAudioDevice *)&local_c0;
                bluetooth::log_internal::vlog
                          (4,"bluetooth",&local_210,
                           "HCI_VSC_QBCE_QLE_ENABLE_CONN_EVENT_DURATION : {}",0x30,&local_250);
                BTM_VendorSpecificCommand
                          (0xfc51,'\x04',(uchar *)&local_230,(_func_void_tBTM_VSC_CMPL_ptr *)0x0);
                auVar35 = bluetooth::le_audio::LeAudioDeviceGroup::GetNextActiveDevice
                                    (param_6,pLVar18);
                pAVar23 = auVar35._8_8_;
                pLVar18 = auVar35._0_8_;
              } while (pLVar18 != (LeAudioDevice *)0x0);
            }
            if (param_6[0x170] != (LeAudioDeviceGroup)0x4) {
              local_250 = CONCAT71(local_250._1_7_,param_6[0x171]);
              bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                        ((common *)&local_250,pAVar23);
              local_230 = CONCAT71(local_230._1_7_,param_6[0x170]);
              bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                        ((common *)&local_230,extraout_x1_26);
              local_2a0 = CONCAT44(local_2a0._4_4_,0xebb);
              local_298 = (LeAudioDevice *)0x1d97f3;
              local_290 = "AseStateMachineProcessStreaming";
              bluetooth::log::error<std::string,std::string>::log
                        (local_2f0,", invalid state transition, from: {}, to: {}",0x2c,&local_c0,
                         &local_210,&local_2a0);
              if (((ulong)local_210 & 1) != 0) {
                operator_delete(local_200,(ulong)local_210 & 0xfffffffffffffffe);
              }
              if (((ulong)local_c0 & 1) != 0) {
                operator_delete(local_b0,(ulong)local_c0 & 0xfffffffffffffffe);
              }
              goto LAB_0067968c;
            }
            (**(code **)(*param_1 + 0x98))(param_1,*(undefined4 *)param_6);
            bluetooth::le_audio::LeAudioDeviceGroup::SetState(param_6,4);
            (**(code **)(*(long *)param_1[1] + 0x10))((long *)param_1[1],*(undefined4 *)param_6,1);
            goto LAB_006796a8;
          }
          bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                    ((common *)(param_4 + 0x310),auVar35._8_8_);
          local_288 = 0xe9d;
          local_280 = "packages/modules/Bluetooth/system/bta/le_audio/state_machine.cc";
          local_278 = "AseStateMachineProcessStreaming";
          bluetooth::log::info<RawAddress&,unsigned_char&,std::string>::log
                    (param_5,pbVar32,&local_c0,&local_288);
          if (((ulong)local_c0 & 1) != 0) {
            operator_delete(local_b0,(ulong)local_c0 & 0xfffffffffffffffe);
          }
          (**(code **)(*param_1 + 0x98))(param_1,*(undefined4 *)param_6);
          plVar34 = (long *)param_1[1];
          uVar11 = *(undefined4 *)param_6;
          uVar36 = 1;
          pcVar28 = *(code **)(*plVar34 + 0x10);
          goto LAB_006796a4;
        }
        local_c0 = (LeAudioDevice *)(ulong)*(uint *)param_6;
        pLStack_248 = (LeAudioDevice *)&local_c0;
        local_210 = (LeAudioDevice *)CONCAT44(local_210._4_4_,0xe8f);
        local_200 = (LeAudioDevice *)0x11b754;
        pLStack_208 = (LeAudioDevice *)0x1d97f3;
        uStack_b8 = (code *)0x0;
        local_b0 = (char *)0x3;
        local_250 = 1;
        local_240 = (LeAudioDevice *)0x3;
        bluetooth::log_internal::vlog
                  (4,"bluetooth",&local_210,"More Ases to get in streaming state for group_id: {}",
                   0x34,&local_250);
      }
LAB_006796a8:
      if ((char)local_c8 == '\x01') {
        bluetooth::le_audio::types::LeAudioMetadata::~LeAudioMetadata
                  ((LeAudioMetadata *)&pcStack_1a0);
      }
      std::
      __tree<std::__value_type<unsigned_char,std::vector<unsigned_char,std::allocator<unsigned_char>>>,std::__map_value_compare<unsigned_char,std::pair<unsigned_char_const,std::vector<unsigned_char,std::allocator<unsigned_char>>>,std::less<unsigned_char>,true>,std::allocator<std::pair<unsigned_char_const,std::vector<unsigned_char,std::allocator<unsigned_char>>>>>
      ::destroy((__tree<std::__value_type<unsigned_char,std::vector<unsigned_char,std::allocator<unsigned_char>>>,std::__map_value_compare<unsigned_char,std::pair<unsigned_char_const,std::vector<unsigned_char,std::allocator<unsigned_char>>>,std::less<unsigned_char>,true>,std::allocator<std::pair<unsigned_char_const,std::vector<unsigned_char,std::allocator<unsigned_char>>>>>
                 *)&local_1f0,p_Stack_1e8);
      if (pLStack_268 == (LeAudioDevice *)0x0) goto LAB_006782bc;
      local_260 = pLStack_268;
      pLVar18 = pLStack_268;
      pLVar30 = local_258;
      goto LAB_0067a784;
    }
    if (param_6 == (LeAudioDeviceGroup *)0x0) {
      local_1f0 = (LeAudioDevice *)CONCAT44(local_1f0._4_4_,0xe1d);
      local_1e0 = (LeAudioDevice *)0x1e9c17;
LAB_0067748c:
      pcVar25 = "leAudioDevice doesn\'t belong to any group";
      uVar36 = 6;
      uVar26 = 0x29;
LAB_006774b0:
      p_Stack_1e8 = (__tree_node *)0x1d97f3;
      local_c0 = (LeAudioDevice *)0x0;
      bluetooth::log_internal::vlog(uVar36,"bluetooth",&local_1f0,pcVar25,uVar26,&local_c0);
      goto LAB_006782bc;
    }
    bVar6 = *(byte *)(param_4 + 0x310);
    if (bVar6 == 3) goto LAB_006782bc;
    if (bVar6 != 2) {
      local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0xe5d);
      uStack_b8 = (code *)0x1d97f3;
      local_b0 = "AseStateMachineProcessEnabling";
      pLStack_268 = (LeAudioDevice *)&local_1f0;
      local_1e0 = (LeAudioDevice *)0x3;
      p_Stack_1e8 = (__tree_node *)0x0;
      pLStack_1d0 = (LeAudioDevice *)0x63;
      local_1d8 = (LeAudioDevice *)0x0;
      local_270 = 2;
      local_260 = (LeAudioDevice *)0x63;
      local_1f0 = (LeAudioDevice *)(ulong)bVar6;
      bluetooth::log_internal::vlog
                (6,"bluetooth",&local_c0,"invalid state transition, from: {}, to: {}",0x2a,
                 &local_270);
LAB_00677ee4:
      uVar11 = *(undefined4 *)param_6;
      goto LAB_006782a8;
    }
    SetAseState(param_5,param_4,3);
    if (param_6[0x170] == (LeAudioDeviceGroup)0x4) {
      if (*(char *)(param_4 + 6) == '\x01') {
        SetAseExpectedState(param_5,param_4,4);
      }
      if (param_6[0x171] == (LeAudioDeviceGroup)0x4) {
        if ((1 < *(int *)(param_4 + 0xc)) ||
           (uVar14 = CisCreateForDevice(param_6,param_5), (uVar14 & 1) != 0)) {
          uVar14 = bluetooth::le_audio::LeAudioDevice::HaveAllActiveAsesCisEst(param_5);
          if (((uVar14 & 1) != 0) &&
             (uVar14 = bluetooth::le_audio::LeAudioDevice::IsReadyToCreateStream(param_5),
             (uVar14 & 1) != 0)) {
            lVar16 = bluetooth::le_audio::LeAudioDevice::GetFirstActiveAse(param_5);
            RawAddress::ToString();
            local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0xe4c);
            uStack_b8 = (code *)0x1d97f3;
            local_b0 = "AseStateMachineProcessEnabling";
            bluetooth::log::assert_that<std::string>::assert_that
                      (&local_270,lVar16 != 0,
                       "shouldn\'t be called without an active ASE, device {}",0x34,&local_1f0,
                       &local_c0);
            if (((ulong)local_1f0 & 1) != 0) {
              operator_delete(local_1e0,(ulong)local_1f0 & 0xfffffffffffffffe);
            }
            PrepareAndSendReceiverStartReady(param_1,param_5,lVar16);
          }
          goto LAB_006782bc;
        }
LAB_0067a48c:
        uVar11 = *(undefined4 *)param_6;
        uVar36 = 2;
        goto LAB_00678930;
      }
      uVar14 = bluetooth::le_audio::LeAudioDevice::IsReadyToCreateStream(param_5);
      if ((uVar14 & 1) == 0) goto LAB_006782bc;
      if (param_6[0x171] != (LeAudioDeviceGroup)0x3) {
        uVar14 = bluetooth::le_audio::LeAudioDeviceGroup::IsGroupReadyToCreateStream(param_6);
        if ((uVar14 & 1) == 0) {
          local_1f0 = (LeAudioDevice *)CONCAT44(local_1f0._4_4_,0xfa5);
          local_1e0 = (LeAudioDevice *)0x151412;
          pcVar25 = "Waiting for more ASEs to be in enabling or directly in streaming state";
          uVar26 = 0x46;
          goto LAB_0067917c;
        }
        bluetooth::le_audio::LeAudioDeviceGroup::SetState(param_6,3);
      }
      auVar35 = bluetooth::le_audio::LeAudioDeviceGroup::HaveAllActiveDevicesAsesTheSameState
                          (param_6,4);
      pAVar23 = auVar35._8_8_;
      if ((auVar35._0_8_ & 1) != 0) {
        pLVar18 = (LeAudioDevice *)
                  bluetooth::le_audio::LeAudioDeviceGroup::GetFirstActiveDevice(param_6);
        if (pLVar18 != (LeAudioDevice *)0x0) {
          do {
            uVar7 = BTM_GetHCIConnHandle(pLVar18,2);
            local_210 = (LeAudioDevice *)CONCAT44(local_210._4_4_,0x1000026);
            uVar36 = local_210;
            local_210._0_2_ = CONCAT11((char)uVar7,0x26);
            local_210._3_5_ = SUB85(uVar36,3);
            local_210._0_3_ = CONCAT12((char)((ushort)uVar7 >> 8),(undefined2)local_210);
            local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0xffd);
            uStack_b8 = (code *)0x1d97f3;
            local_b0 = "QbceQleSetConnEventDuration";
            local_1e0 = (LeAudioDevice *)0x3;
            p_Stack_1e8 = (__tree_node *)0x0;
            local_1f0 = (LeAudioDevice *)0x1;
            local_270 = 1;
            local_260 = (LeAudioDevice *)0x3;
            pLStack_268 = (LeAudioDevice *)&local_1f0;
            bluetooth::log_internal::vlog
                      (4,"bluetooth",&local_c0,"HCI_VSC_QBCE_QLE_ENABLE_CONN_EVENT_DURATION : {}",
                       0x30,&local_270);
            BTM_VendorSpecificCommand
                      (0xfc51,'\x04',(uchar *)&local_210,(_func_void_tBTM_VSC_CMPL_ptr *)0x0);
            pLVar18 = (LeAudioDevice *)
                      bluetooth::le_audio::LeAudioDeviceGroup::GetNextActiveDevice(param_6,pLVar18);
          } while (pLVar18 != (LeAudioDevice *)0x0);
        }
        bluetooth::le_audio::LeAudioDeviceGroup::SetState(param_6,4);
        pAVar23 = extraout_x1_23;
      }
      if (param_6[0x170] != (LeAudioDeviceGroup)0x4) {
        local_230 = CONCAT71(local_230._1_7_,param_6[0x171]);
        bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                  ((common *)&local_230,pAVar23);
        local_288 = CONCAT31(local_288._1_3_,param_6[0x170]);
        bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
                  ((common *)&local_288,extraout_x1_25);
        uStack_b8 = (code *)0x1d97f3;
        local_b0 = "ProcessGroupEnable";
        local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0xfc3);
        p_Stack_1e8 = (__tree_node *)pLStack_208;
        local_1f0 = local_200;
        if (((ulong)local_210 & 1) == 0) {
          p_Stack_1e8 = (__tree_node *)((ulong)local_210 >> 1 & 0x7f);
          local_1f0 = (LeAudioDevice *)((long)&local_210 + 1);
        }
        local_1d8 = pLStack_248;
        local_1e0 = local_240;
        if ((local_250 & 1) == 0) {
          local_1e0 = (LeAudioDevice *)((long)&local_250 + 1);
          local_1d8 = (LeAudioDevice *)(local_250 >> 1 & 0x7f);
        }
        pLStack_268 = (LeAudioDevice *)&local_1f0;
        pLStack_1d0 = (LeAudioDevice *)0x1ad;
        local_270 = 2;
        local_260 = (LeAudioDevice *)0x1ad;
        bluetooth::log_internal::vlog
                  (6,"bluetooth",&local_c0,", invalid state transition, from: {} , to: {}",0x2d,
                   &local_270);
        if ((local_250 & 1) != 0) {
          operator_delete(local_240,local_250 & 0xfffffffffffffffe);
        }
        if (((ulong)local_210 & 1) != 0) {
          operator_delete(local_200,(ulong)local_210 & 0xfffffffffffffffe);
        }
        goto LAB_00677ee4;
      }
      pLVar18 = (LeAudioDevice *)
                bluetooth::le_audio::LeAudioDeviceGroup::GetFirstActiveDevice(param_6);
      if (pLVar18 == (LeAudioDevice *)0x0) {
        local_1f0 = (LeAudioDevice *)CONCAT44(local_1f0._4_4_,0x871);
        p_Stack_1e8 = (__tree_node *)0x1d97f3;
        local_1e0 = (LeAudioDevice *)0x13a1ad;
        local_c0 = (LeAudioDevice *)0x0;
        bluetooth::log_internal::vlog
                  (7,"bluetooth",&local_1f0,"Shouldn\'t be called without an active device.",0x2d,
                   &local_c0);
      }
      if (param_6[0x10] != (LeAudioDeviceGroup)0x2) {
        local_1f0 = (LeAudioDevice *)(ulong)*(uint *)param_6;
        pLStack_268 = (LeAudioDevice *)&local_1f0;
        local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0x875);
        uStack_b8 = (code *)0x1d97f3;
        local_b0 = "CisCreate";
        local_1e0 = (LeAudioDevice *)0x3;
        p_Stack_1e8 = (__tree_node *)0x0;
        local_270 = 1;
        local_260 = (LeAudioDevice *)0x3;
        bluetooth::log_internal::vlog
                  (6,"bluetooth",&local_c0,"CIG is not created for group_id {}",0x22,&local_270);
        bluetooth::le_audio::LeAudioDeviceGroup::PrintDebugState(param_6);
        goto LAB_0067a48c;
      }
      pLVar30 = (LeAudioDevice *)0x0;
      local_470 = (LeAudioDevice *)0x0;
      local_498 = (LeAudioDevice *)0x0;
      do {
        lVar16 = bluetooth::le_audio::LeAudioDevice::GetFirstActiveAse(pLVar18);
        if (lVar16 == 0) {
          local_1f0 = (LeAudioDevice *)CONCAT44(local_1f0._4_4_,0x87c);
          p_Stack_1e8 = (__tree_node *)0x1d97f3;
          local_1e0 = (LeAudioDevice *)0x13a1ad;
          local_c0 = (LeAudioDevice *)0x0;
          bluetooth::log_internal::vlog
                    (7,"bluetooth",&local_1f0,"shouldn\'t be called without an active ASE",0x29,
                     &local_c0);
        }
        *(undefined4 *)(pLVar18 + 0x30) = 0;
        do {
          auVar35 = bluetooth::le_audio::LeAudioDevice::GetAsesByCisConnHdl
                              (pLVar18,*(undefined2 *)(lVar16 + 8));
          lVar22 = auVar35._8_8_;
          lVar19 = auVar35._0_8_;
          if (*(int *)(lVar16 + 0xc) != 2) {
            if (lVar19 != 0) {
              *(undefined4 *)(lVar19 + 0xc) = 2;
            }
            if (lVar22 != 0) {
              *(undefined4 *)(lVar22 + 0xc) = 2;
            }
            uVar14 = (*(code *)PTR_BTM_GetHCIConnHandle_00fabd38)(pLVar18,2);
            uVar8 = *(ushort *)(lVar16 + 8);
            uVar27 = (uint)uVar14;
            if (pLVar30 < local_470) {
              *(uint *)pLVar30 = (uint)uVar8 | uVar27 << 0x10;
              pLVar31 = local_498;
            }
            else {
              __n = (long)pLVar30 - (long)local_498;
              uVar15 = ((long)__n >> 2) + 1;
              if (uVar15 >> 0x3e != 0) {
                    /* WARNING: Subroutine does not return */
                std::vector<signed_char,std::allocator<signed_char>>::
                __throw_length_error_abi_nn220000_();
              }
              uVar33 = (long)local_470 - (long)local_498;
              uVar1 = (long)uVar33 >> 1;
              if ((ulong)((long)uVar33 >> 1) <= uVar15) {
                uVar1 = uVar15;
              }
              if (0x7ffffffffffffffb < uVar33) {
                uVar1 = 0x3fffffffffffffff;
              }
              if (uVar1 >> 0x3e != 0) {
                    /* WARNING: Subroutine does not return */
                std::__throw_bad_array_new_length_abi_nn220000_();
              }
              lVar20 = FUN_00f62c00(uVar1 * 4);
              pLVar30 = (LeAudioDevice *)(lVar20 + __n);
              local_470 = (LeAudioDevice *)(lVar20 + uVar1 * 4);
              pLVar31 = pLVar30 + ((long)__n >> 2) * -4;
              *(uint *)pLVar30 = (uint)uVar8 | uVar27 << 0x10;
              memcpy(pLVar31,local_498,__n);
              if (local_498 != (LeAudioDevice *)0x0) {
                operator_delete(local_498,uVar33);
              }
            }
            local_498 = pLVar31;
            pLStack_268 = (LeAudioDevice *)&local_1f0;
            pLVar30 = pLVar30 + 4;
            uStack_b8 = (code *)0x1d97f3;
            local_b0 = "CisCreate";
            local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0x891);
            local_1f0 = (LeAudioDevice *)(ulong)*(ushort *)(lVar16 + 8);
            local_1e0 = (LeAudioDevice *)(uVar14 & 0xffff);
            p_Stack_1e8 = (__tree_node *)0x0;
            pLStack_1d0 = (LeAudioDevice *)0xc6;
            local_1d8 = (LeAudioDevice *)0x0;
            local_270 = 2;
            local_260 = (LeAudioDevice *)0xc6;
            bluetooth::log_internal::vlog
                      (3,"bluetooth",&local_c0,"cis handle: {} acl handle : 0x{:x}",0x22,&local_270)
            ;
            *(int *)(pLVar18 + 0x30) = *(int *)(pLVar18 + 0x30) + 1;
            RawAddress::ToRedactedStringForLogging();
            pLVar31 = (LeAudioDevice *)((ulong)&local_1f0 | 1);
            if (((ulong)local_1f0 & 1) != 0) {
              pLVar31 = local_1e0;
            }
            btif_dm_log_collector_cback
                      ("LEASESM-Send CIS Con Req, %s cig_id 0x%x cis_hld 0x%x (%d) from 0x%x",
                       pLVar31,(ulong)*(uint *)param_6,(ulong)*(ushort *)(lVar16 + 8),
                       (ulong)*(uint *)(pLVar18 + 0x30),(ulong)(uVar27 & 0xffff));
            if (((ulong)local_1f0 & 1) != 0) {
              operator_delete(local_1e0,(ulong)local_1f0 & 0xfffffffffffffffe);
            }
            WriteCisInfoInSnoop(1,param_6,uVar14 & 0xffffffff,lVar19,lVar22);
          }
          lVar16 = bluetooth::le_audio::LeAudioDevice::GetNextActiveAse(pLVar18,lVar16);
        } while (lVar16 != 0);
        pLVar18 = (LeAudioDevice *)
                  bluetooth::le_audio::LeAudioDeviceGroup::GetNextActiveDevice(param_6,pLVar18);
      } while (pLVar18 != (LeAudioDevice *)0x0);
      plVar34 = (long *)bluetooth::hci::IsoManager::GetInstance();
      local_210 = local_498;
      local_200 = local_470;
      pLStack_208 = pLVar30;
      (**(code **)(*plVar34 + 0x38))(plVar34,&local_210);
      if (local_210 == (LeAudioDevice *)0x0) goto LAB_006782bc;
      pLStack_208 = local_210;
      pLVar18 = local_210;
      pLVar30 = local_200;
      goto LAB_0067a784;
    }
    local_250 = CONCAT71(local_250._1_7_,param_6[0x170]);
    bluetooth::common::ToString<bluetooth::le_audio::types::AseState>
              ((common *)&local_250,extraout_x1_11);
    local_c0 = (LeAudioDevice *)CONCAT44(local_c0._4_4_,0xe27);
    uStack_b8 = (code *)0x1d97f3;
    local_b0 = "AseStateMachineProcessEnabling";
    p_Stack_1e8 = (__tree_node *)
                  _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
    ;
    local_1e0 = (LeAudioDevice *)(ulong)*pbVar32;
    pLStack_1d0 = local_200;
    local_1c8 = pLStack_208;
    if (((ulong)local_210 & 1) == 0) {
      pLStack_1d0 = (LeAudioDevice *)((long)&local_210 + 1);
      local_1c8 = (LeAudioDevice *)((ulong)local_210 >> 1 & 0x7f);
    }
    pLStack_268 = (LeAudioDevice *)&local_1f0;
    local_1d8 = (LeAudioDevice *)0x0;
    pLStack_1c0 = (LeAudioDevice *)0x34cf;
    local_270 = 3;
    local_260 = (LeAudioDevice *)0x34cf;
    local_1f0 = param_5;
    bluetooth::log_internal::vlog
              (5,"bluetooth",&local_c0,"{}, ase_id: {}, target state: {}",0x20,&local_270);
LAB_006781dc:
    if (((ulong)local_210 & 1) != 0) {
      operator_delete(local_200,(ulong)local_210 & 0xfffffffffffffffe);
    }
  }
  bluetooth::le_audio::LeAudioDeviceGroup::PrintDebugState(param_6);
LAB_006782bc:
  if (*(long *)(lVar3 + 0x28) != local_78) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}


/* ==== GattWriteCallback @ 006f0db8 size 1412 :: All vendor specific reply write complete, size {} successCounter {} */

/* WARNING: Unknown calling convention: __rustcall */
/* _GLOBAL__N_1::RasClientImpl::GattWriteCallback */

void __rustcall
_GLOBAL__N_1::RasClientImpl::GattWriteCallback
          (uint param_1,char param_2,uint param_3,undefined8 param_4,undefined8 param_5,int *param_6
          )

{
  long lVar1;
  long lVar2;
  long lVar3;
  byte bVar4;
  undefined8 *in_x18;
  __shared_weak_count *this;
  ulong uVar5;
  ulong uVar6;
  long lVar7;
  ushort *puVar8;
  undefined8 unaff_x30;
  byte local_100;
  undefined7 uStack_ff;
  ulong local_f8;
  char *local_f0;
  char local_e4 [4];
  undefined8 local_e0;
  ulong *puStack_d8;
  undefined8 local_d0;
  undefined8 local_c8;
  char *local_c0;
  char *pcStack_b8;
  ulong local_b0;
  char *local_a8;
  char *local_a0;
  ulong local_98;
  ulong local_90;
  undefined8 local_88;
  undefined8 uStack_80;
  long local_68;
  
  *in_x18 = unaff_x30;
  lVar3 = DAT_01011810;
  lVar1 = tpidr_el0;
  local_68 = *(long *)(lVar1 + 0x28);
  if (DAT_01011810 == 0) goto LAB_006f1300;
  uVar5 = (ulong)(param_3 & 0xffff);
  param_1 = param_1 & 0xffff;
  uVar6 = (ulong)param_1;
  local_e4[0] = param_2;
  if ((param_6 == (int *)0x0) || (*param_6 != 0)) {
    if (param_2 != '\0') {
      gatt_status_text(local_e4);
      local_c8 = CONCAT44(local_c8._4_4_,0x32c);
      local_a0 = local_f0;
      if ((local_100 & 1) == 0) {
        local_f8 = (ulong)(local_100 >> 1);
        local_a0 = (char *)&uStack_ff;
      }
      puStack_d8 = &local_b0;
      local_c0 = "packages/modules/Bluetooth/system/bta/ras/ras_client.cc";
      pcStack_b8 = "GattWriteCallback";
      local_a8 = (char *)0x0;
      local_88 = 0;
      uStack_80 = 0x19a6;
      local_e0 = 3;
      local_d0 = 0x19a6;
      local_b0 = uVar6;
      local_98 = local_f8;
      local_90 = uVar5;
      bluetooth::log_internal::vlog
                (6,"bluetooth",&local_c8,"Fail to write conn_id {}, status {}, handle {}",0x2e,
                 &local_e0);
      if ((local_100 & 1) != 0) {
        operator_delete(local_f0,CONCAT71(uStack_ff,local_100) & 0xfffffffffffffffe);
      }
      for (lVar7 = *(long *)(lVar3 + 0x18); lVar7 != lVar3 + 0x10; lVar7 = *(long *)(lVar7 + 8)) {
        puVar8 = *(ushort **)(lVar7 + 0x10);
        this = *(__shared_weak_count **)(lVar7 + 0x18);
        if (this == (__shared_weak_count *)0x0) {
          if (*puVar8 == param_1) goto LAB_006f1044;
        }
        else {
          __aarch64_ldadd8_relax(1,this + 8);
          if (*puVar8 == param_1) {
LAB_006f1044:
            lVar3 = *(long *)(puVar8 + 0x20);
            if (lVar3 != *(long *)(puVar8 + 0x24)) goto LAB_006f1050;
            local_b0 = CONCAT44(local_b0._4_4_,0xa4);
            local_a8 = "packages/modules/Bluetooth/system/bta/ras/ras_client.cc";
            local_a0 = "FindCharacteristicByHandle";
            local_c8 = 0;
            bluetooth::log_internal::vlog
                      (5,"bluetooth",&local_b0,"No characteristics available",0x1c,&local_c8);
            goto LAB_006f10b4;
          }
          lVar2 = __aarch64_ldadd8_acq_rel(0xffffffffffffffff,this + 8);
          if (lVar2 == 0) {
            (**(code **)(*(long *)this + 0x10))(this);
            std::__shared_weak_count::__release_weak(this);
          }
        }
      }
      puStack_d8 = &local_b0;
      local_c8 = CONCAT44(local_c8._4_4_,0x330);
      local_c0 = "packages/modules/Bluetooth/system/bta/ras/ras_client.cc";
      pcStack_b8 = "GattWriteCallback";
      local_a8 = (char *)0x0;
      local_a0 = &DAT_00000006;
      local_e0 = 1;
      local_d0 = 6;
      local_b0 = uVar6;
      bluetooth::log_internal::vlog
                (5,"bluetooth",&local_c8,"Can\'t find tracker for conn_id:{}",0x21,&local_e0);
    }
    goto LAB_006f1300;
  }
  local_b0 = CONCAT44(local_b0._4_4_,0x30c);
  local_a8 = "packages/modules/Bluetooth/system/bta/ras/ras_client.cc";
  local_a0 = "GattWriteCallbackForVendorSpecificData";
  local_c8 = 0;
  bluetooth::log_internal::vlog
            (4,"bluetooth",&local_b0,"Write vendor specific reply complete",0x24,&local_c8);
  lVar7 = *(long *)(lVar3 + 0x18);
  if (lVar7 == lVar3 + 0x10) {
    this = (__shared_weak_count *)0x0;
    puVar8 = (ushort *)0x0;
  }
  else {
    do {
      puVar8 = *(ushort **)(lVar7 + 0x10);
      this = *(__shared_weak_count **)(lVar7 + 0x18);
      if (this == (__shared_weak_count *)0x0) {
        if (*puVar8 == param_1) {
          this = (__shared_weak_count *)0x0;
          param_2 = local_e4[0];
          goto LAB_006f1174;
        }
      }
      else {
        __aarch64_ldadd8_relax(1,this + 8);
        param_2 = local_e4[0];
        if (*puVar8 == param_1) goto LAB_006f1174;
        lVar2 = __aarch64_ldadd8_acq_rel(0xffffffffffffffff,this + 8);
        if (lVar2 == 0) {
          (**(code **)(*(long *)this + 0x10))(this);
          std::__shared_weak_count::__release_weak(this);
        }
      }
      lVar7 = *(long *)(lVar7 + 8);
    } while (lVar7 != lVar3 + 0x10);
    this = (__shared_weak_count *)0x0;
    puVar8 = (ushort *)0x0;
    param_2 = local_e4[0];
  }
LAB_006f1174:
  bVar4 = (char)puVar8[0x40] + 1;
  *(byte *)(puVar8 + 0x40) = bVar4;
  if (param_2 == '\0') {
    *(char *)((long)puVar8 + 0x81) = *(char *)((long)puVar8 + 0x81) + '\x01';
  }
  else {
    gatt_status_text(local_e4);
    local_c8 = CONCAT44(local_c8._4_4_,0x312);
    local_a0 = local_f0;
    if ((local_100 & 1) == 0) {
      local_f8 = (ulong)(local_100 >> 1);
      local_a0 = (char *)&uStack_ff;
    }
    puStack_d8 = &local_b0;
    local_c0 = "packages/modules/Bluetooth/system/bta/ras/ras_client.cc";
    pcStack_b8 = "GattWriteCallbackForVendorSpecificData";
    local_a8 = (char *)0x0;
    local_88 = 0;
    uStack_80 = 0x19a6;
    local_e0 = 3;
    local_d0 = 0x19a6;
    local_b0 = uVar6;
    local_98 = local_f8;
    local_90 = uVar5;
    bluetooth::log_internal::vlog
              (6,"bluetooth",&local_c8,
               "Fail to write vendor specific reply conn_id {}, status {}, handle {}",0x44,&local_e0
              );
    if ((local_100 & 1) != 0) {
      operator_delete(local_f0,CONCAT71(uStack_ff,local_100) & 0xfffffffffffffffe);
    }
    bVar4 = (byte)puVar8[0x40];
  }
  if (*(long *)(puVar8 + 0x38) - *(long *)(puVar8 + 0x34) >> 6 == (ulong)bVar4) {
    local_b0 = (ulong)bVar4;
    puStack_d8 = &local_b0;
    local_c8 = CONCAT44(local_c8._4_4_,0x319);
    local_a0 = (char *)(ulong)*(byte *)((long)puVar8 + 0x81);
    local_a8 = (char *)0x0;
    local_c0 = "packages/modules/Bluetooth/system/bta/ras/ras_client.cc";
    pcStack_b8 = "GattWriteCallbackForVendorSpecificData";
    local_98 = 0;
    local_90 = 199;
    local_e0 = 2;
    local_d0 = 199;
    bluetooth::log_internal::vlog
              (4,"bluetooth",&local_c8,
               "All vendor specific reply write complete, size {} successCounter {}",0x43,&local_e0)
    ;
    puVar8[0x40] = 0;
    (**(code **)(**(long **)(lVar3 + 0x28) + 0x28))
              (*(long **)(lVar3 + 0x28),puVar8 + 4,
               (ulong)*(byte *)((long)puVar8 + 0x81) ==
               *(long *)(puVar8 + 0x38) - *(long *)(puVar8 + 0x34) >> 6);
  }
  goto LAB_006f12d4;
  while (lVar3 = lVar3 + 0x30, lVar3 != *(long *)(puVar8 + 0x24)) {
LAB_006f1050:
    if ((uint)*(ushort *)(lVar3 + 0x12) == (param_3 & 0xffff)) {
      if (*(long *)(lVar3 + 2) == 0x100000172c0000 && *(long *)(lVar3 + 10) == -0x4cb64a07fffff80) {
        local_b0 = CONCAT44(local_b0._4_4_,0x33a);
        local_a8 = "packages/modules/Bluetooth/system/bta/ras/ras_client.cc";
        local_a0 = "GattWriteCallback";
        local_c8 = 0;
        bluetooth::log_internal::vlog
                  (6,"bluetooth",&local_b0,"Write RAS-CP command fail",0x19,&local_c8);
        *(undefined1 *)(puVar8 + 0x2f) = 0;
      }
      goto LAB_006f12d4;
    }
  }
LAB_006f10b4:
  puStack_d8 = &local_b0;
  local_c8 = CONCAT44(local_c8._4_4_,0x335);
  local_c0 = "packages/modules/Bluetooth/system/bta/ras/ras_client.cc";
  pcStack_b8 = "GattWriteCallback";
  local_a8 = (char *)0x0;
  local_a0 = &DAT_00000006;
  local_e0 = 1;
  local_d0 = 6;
  local_b0 = uVar5;
  bluetooth::log_internal::vlog
            (5,"bluetooth",&local_c8,"Can\'t find characteristic for handle:{}",0x27,&local_e0);
LAB_006f12d4:
  if ((this != (__shared_weak_count *)0x0) &&
     (lVar3 = __aarch64_ldadd8_acq_rel(0xffffffffffffffff,this + 8), lVar3 == 0)) {
    (**(code **)(*(long *)this + 0x10))(this);
    std::__shared_weak_count::__release_weak(this);
  }
LAB_006f1300:
  if (*(long *)(lVar1 + 0x28) != local_68) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}


/* ==== GattcCallback @ 0072e090 size 13152 :: ProcessCtpNotificationQueue */

/* WARNING: Unknown calling convention: __rustcall */
/* _GLOBAL__N_1::HasClientImpl::GattcCallback */

void __rustcall
_GLOBAL__N_1::HasClientImpl::GattcCallback(long param_1,byte param_2,HasDevice *param_3)

{
  HasDevice *pHVar1;
  RawAddress *pRVar2;
  __tree_node_base *p_Var3;
  code *pcVar4;
  undefined2 *puVar5;
  HasDevice *__n;
  HasDevice *pHVar6;
  size_t sVar7;
  undefined4 uVar8;
  long lVar9;
  char cVar10;
  __tree_node_base _Var11;
  PresetInfo PVar12;
  byte bVar13;
  short sVar14;
  size_t sVar15;
  long lVar16;
  uint6 uVar17;
  void *pvVar18;
  undefined2 *puVar19;
  bool bVar20;
  undefined1 uVar21;
  uchar uVar22;
  ushort uVar23;
  int iVar24;
  long *plVar25;
  long *plVar26;
  PresetInfo *pPVar27;
  ulong uVar28;
  code *pcVar29;
  void *pvVar30;
  undefined8 *puVar31;
  char *pcVar32;
  undefined2 uVar33;
  uint uVar34;
  uint uVar35;
  undefined8 *puVar36;
  undefined8 uVar37;
  short *psVar38;
  string *this;
  __tree_node_base *p_Var39;
  long *plVar40;
  uint uVar41;
  long lVar42;
  __tree_node_base *p_Var43;
  __tree_node_base *p_Var44;
  __tree_node_base *p_Var45;
  __tree_node_base *p_Var46;
  undefined8 *in_x18;
  long lVar47;
  long *plVar48;
  PresetInfo *pPVar49;
  PresetInfo *pPVar50;
  string *this_00;
  long lVar51;
  long lVar52;
  long *plVar53;
  undefined8 unaff_x30;
  undefined8 uVar54;
  undefined8 local_280;
  void *local_260;
  void *local_258;
  long local_250;
  undefined2 *local_248;
  undefined2 *local_240;
  undefined2 *local_238;
  void *local_230;
  void *local_228;
  void *local_220;
  PresetInfo *local_218;
  PresetInfo *local_210;
  PresetInfo *local_208;
  undefined8 local_200;
  ulong uStack_1f8;
  void *local_1f0;
  char *pcStack_1e8;
  undefined8 local_1e0;
  undefined8 local_1d8;
  undefined8 local_1d0;
  char *pcStack_1c8;
  char *local_1c0;
  char *pcStack_1b8;
  undefined8 local_1b0;
  undefined8 local_1a8;
  ulong local_1a0;
  undefined8 local_190;
  code *pcStack_188;
  HasDevice *local_180;
  void *pvStack_178;
  undefined8 local_170;
  undefined8 local_168;
  undefined8 local_160;
  PresetInfo *pPStack_158;
  PresetInfo *local_150;
  char *local_148;
  ulong local_140;
  undefined8 local_130;
  code *pcStack_128;
  undefined8 local_120;
  code *local_118;
  HasDevice *pHStack_110;
  code *local_108;
  void *local_100;
  ulong local_f8;
  HasDevice *local_f0;
  code *local_e8;
  timespec atStack_e0 [2];
  undefined8 local_c0;
  PresetInfo *local_b8;
  PresetInfo *pPStack_b0;
  char *local_a8;
  undefined8 local_a0;
  undefined8 uStack_98;
  HasDevice *local_90;
  code *pcStack_88;
  undefined8 local_80;
  ulong local_78;
  long local_70;
  
  *in_x18 = unaff_x30;
  lVar16 = tpidr_el0;
  local_70 = *(long *)(lVar16 + 0x28);
  uStack_98 = (char *)&local_130;
  local_1d0._0_4_ = 0x779;
  local_130 = (HasDevice *)(ulong)param_2;
  pcStack_1c8 = "packages/modules/Bluetooth/system/bta/has/has_client.cc";
  local_1c0 = "GattcCallback";
  pcStack_128 = (code *)0x0;
  local_120 = (char *)0x3;
  local_a0 = (code *)0x1;
  local_90 = (HasDevice *)0x3;
  bluetooth::log_internal::vlog(3,"bluetooth",&local_1d0,"event = {}",10,&local_a0);
  if (param_2 < 8) {
    if (param_2 == 2) {
      pHVar1 = param_3 + 5;
      bt_transport_text(param_3 + 0xb);
      gatt_status_text(param_3);
      local_120 = (char *)(ulong)*(ushort *)(param_3 + 2);
      local_1d0._0_4_ = 0x7a0;
      local_118 = (code *)0x0;
      pcStack_1c8 = "packages/modules/Bluetooth/system/bta/has/has_client.cc";
      local_1c0 = "OnGattConnected";
      pHStack_110 = local_180;
      local_108 = pcStack_188;
      if (((ulong)local_190 & 1) == 0) {
        pHStack_110 = (HasDevice *)((long)&local_190 + 1);
        local_108 = (code *)((ulong)local_190 >> 1 & 0x7f);
      }
      uStack_98 = (char *)&local_130;
      local_f8 = uStack_1f8;
      local_100 = local_1f0;
      if ((local_200 & 1) == 0) {
        local_f8 = local_200 >> 1 & 0x7f;
        local_100 = (void *)((long)&local_200 + 1);
      }
      local_e8 = 
      _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IK10GattStatusEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESH_SI_SK_
      ;
      atStack_e0[0].tv_sec = (__time_t)&DAT_00f6b4cf;
      pcStack_128 = 
      _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IK10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESH_SI_SK_
      ;
      local_a0 = (code *)&DAT_00000005;
      local_90 = (HasDevice *)&DAT_00f6b4cf;
      local_130 = pHVar1;
      local_f0 = param_3;
      bluetooth::log_internal::vlog
                (4,"bluetooth",&local_1d0,"{}, conn_id=0x{:04x}, transport={}, status={}(0x{:02x})",
                 0x37,&local_a0);
      if ((local_200 & 1) != 0) {
        operator_delete(local_1f0,local_200 & 0xfffffffffffffffe);
      }
      if (((ulong)local_190 & 1) != 0) {
        operator_delete(local_180,(ulong)local_190 & 0xfffffffffffffffe);
      }
      if (param_3[0xb] == (HasDevice)0x2) {
        plVar26 = *(long **)(param_1 + 0x20);
        plVar25 = (long *)(param_1 + 0x18);
        uVar8 = CONCAT22(local_130._6_2_,*(short *)(param_3 + 9));
        local_130 = (HasDevice *)CONCAT44(uVar8,*(int *)pHVar1);
        if (plVar26 == plVar25) {
LAB_0072ea20:
          if (plVar26 != plVar25) {
            if (*param_3 == (HasDevice)0x0) {
              pHVar1 = (HasDevice *)(plVar26 + 2);
              *(undefined2 *)((long)plVar26 + 0x16) = *(undefined2 *)(param_3 + 2);
              BtaGattQueue::Clean();
              uVar28 = (**(code **)(PTR_PTR_00fabec8 + 0x98))(&PTR_PTR_00fabec8,pHVar1);
              if ((uVar28 & 1) == 0) {
                uVar28 = (**(code **)(PTR_PTR_00fabec8 + 0x90))(&PTR_PTR_00fabec8,pHVar1,2);
                if ((uVar28 & 1) == 0) {
                  uVar21 = (**(code **)(PTR_PTR_00fabec8 + 0x88))(&PTR_PTR_00fabec8,pHVar1,2,0,0,1);
                  local_120 = (char *)&local_190;
                  local_190 = (code *)CONCAT71(local_190._1_7_,uVar21);
                  local_1d0._0_4_ = 0x7d1;
                  pcStack_128 = 
                  _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
                  ;
                  uStack_98 = (char *)&local_130;
                  pcStack_1c8 = "packages/modules/Bluetooth/system/bta/has/has_client.cc";
                  local_1c0 = "OnGattConnected";
                  local_118 = 
                  _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I11tBTM_STATUSEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
                  ;
                  pHStack_110 = (HasDevice *)0x1ef;
                  local_a0 = (code *)0x2;
                  local_90 = (HasDevice *)0x1ef;
                  local_130 = pHVar1;
                  bluetooth::log_internal::vlog
                            (4,"bluetooth",&local_1d0,
                             "Encryption required for {}. Request result: 0x{:02x}",0x34,&local_a0);
                  if (local_190._0_1_ == (HasDevice)0x16) {
                    local_130 = (HasDevice *)CONCAT44(local_130._4_4_,0x7d4);
                    pcStack_128 = (code *)0x123e5b;
                    local_120 = "OnGattConnected";
                    bluetooth::log::error<RawAddress&>::log
                              (&local_1d0,"Link key unknown for {}, disconnect profile",0x2b,pHVar1,
                               &local_130);
                    BTA_GATTC_Close(*(ushort *)((long)plVar26 + 0x16));
                  }
                }
                else {
                  OnEncrypted(param_1,pHVar1);
                }
              }
            }
            else if (*(char *)((long)plVar26 + 0x1a) == '\x01') {
              local_130 = (HasDevice *)CONCAT44(uVar8,0x7b8);
              pcStack_128 = (code *)0x123e5b;
              local_120 = "OnGattConnected";
              local_1d0._0_4_ = 0;
              local_1d0._4_4_ = 0;
              bluetooth::log_internal::vlog
                        (5,"bluetooth",&local_130,"Failed to connect to server device",0x22,
                         &local_1d0);
              plVar25 = (long *)plVar26[1];
              *(long **)(*plVar26 + 8) = plVar25;
              *plVar25 = *plVar26;
              *(long *)(param_1 + 0x28) = *(long *)(param_1 + 0x28) + -1;
              bluetooth::le_audio::has::HasDevice::~HasDevice((HasDevice *)(plVar26 + 2));
              operator_delete(plVar26,0x80);
              (**(code **)(**(long **)(param_1 + 0x10) + 0x10))(*(long **)(param_1 + 0x10),0,pHVar1)
              ;
            }
            goto LAB_00730fcc;
          }
        }
        else {
          do {
            if (*(int *)pHVar1 == (int)plVar26[2] &&
                *(short *)(param_3 + 9) == *(short *)((long)plVar26 + 0x14)) goto LAB_0072ea20;
            plVar26 = (long *)plVar26[1];
          } while (plVar26 != plVar25);
        }
        uStack_98 = (char *)&local_130;
        local_1d0._0_4_ = 0x7ad;
        pcStack_1c8 = "packages/modules/Bluetooth/system/bta/has/has_client.cc";
        local_1c0 = "OnGattConnected";
        pcStack_128 = 
        _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IK10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESH_SI_SK_
        ;
        local_120 = &DAT_0000000f;
        local_a0 = (code *)0x1;
        local_90 = (HasDevice *)&DAT_0000000f;
        local_130 = pHVar1;
        bluetooth::log_internal::vlog
                  (5,"bluetooth",&local_1d0,"Skipping unknown device, address={}",0x23,&local_a0);
      }
      else {
        bt_transport_text(param_3 + 0xb);
        local_1d0._0_4_ = 0x7a5;
        pcStack_128 = pcStack_188;
        local_130 = local_180;
        if (((ulong)local_190 & 1) == 0) {
          pcStack_128 = (code *)((ulong)local_190 >> 1 & 0x7f);
          local_130 = (HasDevice *)((long)&local_190 + 1);
        }
        local_120 = &DAT_0000000d;
        uStack_98 = (char *)&local_130;
        pcStack_1c8 = "packages/modules/Bluetooth/system/bta/has/has_client.cc";
        local_1c0 = "OnGattConnected";
        local_a0 = (code *)0x1;
        local_90 = (HasDevice *)&DAT_0000000d;
        bluetooth::log_internal::vlog
                  (5,"bluetooth",&local_1d0,"Only LE connection is allowed (transport {})",0x2c,
                   &local_a0);
        if (((ulong)local_190 & 1) != 0) {
          operator_delete(local_180,(ulong)local_190 & 0xfffffffffffffffe);
        }
      }
      BTA_GATTC_Close(*(ushort *)(param_3 + 2));
      goto LAB_00730fcc;
    }
    if (param_2 != 5) {
      if (param_2 != 6) goto LAB_00730fcc;
      lVar42 = *(long *)(param_1 + 0x20);
      param_1 = param_1 + 0x18;
      uVar23 = *(ushort *)param_3;
      if (lVar42 == param_1) {
LAB_0072e6c0:
        pRVar2 = (RawAddress *)(lVar42 + 0x10);
        if (lVar42 != param_1) {
          local_130 = (HasDevice *)CONCAT44(local_130._4_4_,0x7fa);
          pcStack_128 = (code *)0x123e5b;
          local_120 = "OnGattServiceSearchComplete";
          local_1d0._0_4_ = 0;
          local_1d0._4_4_ = 0;
          bluetooth::log_internal::vlog(3,"bluetooth",&local_130,&DAT_0013f82c,0,&local_1d0);
          uVar28 = (**(code **)(PTR_PTR_00fabec8 + 0x90))(&PTR_PTR_00fabec8,pRVar2,2);
          if ((uVar28 & 1) == 0) {
            local_130 = (HasDevice *)CONCAT44(local_130._4_4_,0x7fe);
            pcStack_128 = (code *)0x123e5b;
            local_120 = "OnGattServiceSearchComplete";
            local_1d0._0_4_ = 0;
            local_1d0._4_4_ = 0;
            bluetooth::log_internal::vlog
                      (5,"bluetooth",&local_130,"Device not yet bonded - waiting for encryption",
                       0x2e,&local_1d0);
            goto LAB_00730fcc;
          }
          if (*(char *)(lVar42 + 0x1b) == '\0') goto LAB_00730fcc;
          if (param_3[2] != (HasDevice)0x0) {
            pcVar32 = "Service discovery failed";
            puVar31 = &local_130;
            puVar36 = &local_1d0;
            uVar37 = 0x18;
            local_130 = (HasDevice *)CONCAT44(local_130._4_4_,0x807);
            pcStack_128 = (code *)0x123e5b;
            local_120 = "OnGattServiceSearchComplete";
            local_1d0._0_4_ = 0;
            local_1d0._4_4_ = 0;
            goto LAB_0072ebdc;
          }
          lVar51 = bta_gattc_get_services(*(ushort *)(lVar42 + 0x16));
          lVar52 = DAT_01014288;
          lVar47 = *(long *)(lVar51 + 8);
          if (lVar47 == lVar51) {
LAB_0072ed84:
            if (lVar47 != lVar51) {
              local_130 = (HasDevice *)CONCAT44(local_130._4_4_,0x765);
              pcStack_128 = (code *)0x123e5b;
              local_120 = "OnHasServiceFound";
              local_1d0 = 0;
              bluetooth::log_internal::vlog(3,"bluetooth",&local_130,&DAT_0013f82c,0,&local_1d0);
              local_1d0 = CONCAT44(local_1d0._4_4_,0x6c1);
              pcStack_1c8 = "packages/modules/Bluetooth/system/bta/has/has_client.cc";
              local_1c0 = "CacheAttributeHandles";
              pcStack_128 = 
              _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
              ;
              local_120 = (char *)0xf;
              local_a0 = (code *)0x1;
              local_90 = (HasDevice *)&DAT_0000000f;
              local_130 = (HasDevice *)pRVar2;
              uStack_98 = (char *)&local_130;
              bluetooth::log_internal::vlog(3,"bluetooth",&local_1d0,"device={}",9,&local_a0);
              lVar9 = *(long *)(lVar47 + 0x48);
              for (lVar51 = *(long *)(lVar47 + 0x40); lVar51 != lVar9; lVar51 = lVar51 + 0x30) {
                if (*(long *)(lVar51 + 2) == 0x100000dc2b0000 &&
                    *(long *)(lVar51 + 10) == -0x4cb64a07fffff80) {
                  uVar23 = *(ushort *)(lVar51 + 0x12);
                  lVar47 = bta_gattc_get_characteristic(*(ushort *)(lVar42 + 0x16),uVar23);
                  if (lVar47 == 0) {
                    uStack_98 = (char *)&local_130;
                    local_1d0 = CONCAT44(local_1d0._4_4_,0x877);
                    pcStack_1c8 = "packages/modules/Bluetooth/system/bta/has/has_client.cc";
                    local_1c0 = "FindCccHandle";
                    pcStack_128 = (code *)0x0;
                    local_120 = (char *)0x6;
                    local_a0 = (code *)0x1;
                    local_90 = (HasDevice *)&DAT_00000006;
                    local_130 = (HasDevice *)(ulong)uVar23;
                    bluetooth::log_internal::vlog
                              (5,"bluetooth",&local_1d0,"No such characteristic: {}",0x1a,&local_a0)
                    ;
                  }
                  else {
                    psVar38 = *(short **)(lVar47 + 0x18);
                    if (psVar38 != *(short **)(lVar47 + 0x20)) {
                      while( true ) {
                        pcStack_128 = (code *)0xfb349b5f80000080;
                        local_130 = (HasDevice *)0x10000002290000;
                        if (*(long *)(psVar38 + 1) == 0x10000002290000 &&
                            *(long *)(psVar38 + 5) == -0x4cb64a07fffff80) break;
                        psVar38 = psVar38 + 10;
                        if (psVar38 == *(short **)(lVar47 + 0x20)) goto LAB_0073129c;
                      }
                      if (*psVar38 != -1) {
                        *(short *)(lVar42 + 0x22) = *psVar38;
                        *(undefined2 *)(lVar42 + 0x20) = *(undefined2 *)(lVar51 + 0x12);
                        goto LAB_0072f058;
                      }
                    }
                  }
LAB_0073129c:
                  local_130 = (HasDevice *)CONCAT44(local_130._4_4_,0x6c8);
                  pcVar32 = "no HAS Active Preset CCC descriptor found!";
LAB_00731344:
                  local_120 = "CacheAttributeHandles";
                  pcStack_128 = (code *)0x123e5b;
                  local_1d0 = 0;
                  puVar36 = &local_130;
                  puVar31 = &local_1d0;
                  uVar37 = 0x2a;
                  goto LAB_00731354;
                }
                if (*(long *)(lVar51 + 2) == 0x100000db2b0000 &&
                    *(long *)(lVar51 + 10) == -0x4cb64a07fffff80) {
                  uVar23 = *(ushort *)(lVar51 + 0x12);
                  lVar47 = bta_gattc_get_characteristic(*(ushort *)(lVar42 + 0x16),uVar23);
                  if (lVar47 == 0) {
                    uStack_98 = (char *)&local_130;
                    local_1d0 = CONCAT44(local_1d0._4_4_,0x877);
                    pcStack_1c8 = "packages/modules/Bluetooth/system/bta/has/has_client.cc";
                    local_1c0 = "FindCccHandle";
                    pcStack_128 = (code *)0x0;
                    local_120 = (char *)0x6;
                    local_a0 = (code *)0x1;
                    local_90 = (HasDevice *)&DAT_00000006;
                    local_130 = (HasDevice *)(ulong)uVar23;
                    bluetooth::log_internal::vlog
                              (5,"bluetooth",&local_1d0,"No such characteristic: {}",0x1a,&local_a0)
                    ;
                  }
                  else {
                    psVar38 = *(short **)(lVar47 + 0x18);
                    if (psVar38 != *(short **)(lVar47 + 0x20)) {
                      while( true ) {
                        pcStack_128 = (code *)0xfb349b5f80000080;
                        local_130 = (HasDevice *)0x10000002290000;
                        if (*(long *)(psVar38 + 1) == 0x10000002290000 &&
                            *(long *)(psVar38 + 5) == -0x4cb64a07fffff80) break;
                        psVar38 = psVar38 + 10;
                        if (psVar38 == *(short **)(lVar47 + 0x20)) goto LAB_0073131c;
                      }
                      if (*psVar38 != -1) {
                        bVar13 = *(byte *)(lVar51 + 0x14) >> 4 & 3;
                        if (bVar13 != 0) {
                          *(short *)(lVar42 + 0x26) = *psVar38;
                          uVar33 = *(undefined2 *)(lVar51 + 0x12);
                          *(byte *)(lVar42 + 0x28) = bVar13;
                          *(undefined2 *)(lVar42 + 0x24) = uVar33;
                          goto LAB_0072f058;
                        }
                        local_1d0 = CONCAT44(local_1d0._4_4_,0x6df);
                        pcStack_1c8 = "packages/modules/Bluetooth/system/bta/has/has_client.cc";
                        local_1c0 = "CacheAttributeHandles";
                        uStack_98 = (char *)&local_130;
                        pcVar32 = "Invalid properties for the control point 0x{:02x}";
                        puVar36 = &local_1d0;
                        puVar31 = &local_a0;
                        uVar37 = 0x31;
                        pcStack_128 = (code *)0x0;
                        local_120 = &DAT_00000006;
                        local_a0 = (code *)0x1;
                        local_90 = (HasDevice *)&DAT_00000006;
                        local_130 = (HasDevice *)(ulong)*(byte *)(lVar51 + 0x14);
                        goto LAB_00731354;
                      }
                    }
                  }
LAB_0073131c:
                  local_130 = (HasDevice *)CONCAT44(local_130._4_4_,0x6d2);
                  pcVar32 = "no HAS Control Point CCC descriptor found!";
                  goto LAB_00731344;
                }
                if (*(long *)(lVar51 + 2) == 0x100000da2b0000 &&
                    *(long *)(lVar51 + 10) == -0x4cb64a07fffff80) {
                  uVar23 = *(ushort *)(lVar51 + 0x12);
                  lVar47 = bta_gattc_get_characteristic(*(ushort *)(lVar42 + 0x16),uVar23);
                  if (lVar47 == 0) {
                    local_1d0 = CONCAT44(local_1d0._4_4_,0x877);
                    pcStack_1c8 = "packages/modules/Bluetooth/system/bta/has/has_client.cc";
                    local_1c0 = "FindCccHandle";
                    local_a0 = (code *)0x1;
                    uStack_98 = (char *)&local_130;
                    pcStack_128 = (code *)0x0;
                    local_120 = (char *)0x6;
                    local_90 = (HasDevice *)&DAT_00000006;
                    local_130 = (HasDevice *)(ulong)uVar23;
                    bluetooth::log_internal::vlog
                              (5,"bluetooth",&local_1d0,"No such characteristic: {}",0x1a,&local_a0)
                    ;
                  }
                  else {
                    for (puVar5 = *(undefined2 **)(lVar47 + 0x18);
                        puVar5 != *(undefined2 **)(lVar47 + 0x20); puVar5 = puVar5 + 10) {
                      pcStack_128 = (code *)0xfb349b5f80000080;
                      local_130 = (HasDevice *)0x10000002290000;
                      if (*(long *)(puVar5 + 1) == 0x10000002290000 &&
                          *(long *)(puVar5 + 5) == -0x4cb64a07fffff80) {
                        uVar33 = *puVar5;
                        goto LAB_0072f044;
                      }
                    }
                  }
                  uVar33 = 0xffff;
LAB_0072f044:
                  *(undefined2 *)(lVar42 + 0x2c) = uVar33;
                  *(undefined2 *)(lVar42 + 0x2a) = *(undefined2 *)(lVar51 + 0x12);
                }
LAB_0072f058:
              }
              local_1d0._4_4_ = (undefined4)((ulong)local_1d0 >> 0x20);
              local_1d0._0_4_ = 0x6f1;
              pcStack_128 = 
              _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
              ;
              local_120 = &DAT_0000000f;
              local_a0 = (code *)0x1;
              uStack_98 = (char *)&local_130;
              pcStack_1c8 = "packages/modules/Bluetooth/system/bta/has/has_client.cc";
              local_1c0 = "LoadHasDetailsFromStorage";
              local_90 = (HasDevice *)0xf;
              local_130 = (HasDevice *)pRVar2;
              bluetooth::log_internal::vlog(3,"bluetooth",&local_1d0,"device={}",9,&local_a0);
              local_a0 = (code *)0x0;
              uStack_98 = (char *)0x0;
              local_90 = (HasDevice *)0x0;
              local_200 = local_200 & 0xffffffffffffff00;
              uVar28 = btif_storage_get_leaudio_has_presets
                                 (pRVar2,(vector *)&local_a0,(uchar *)&local_200);
              if (((uVar28 & 1) == 0) ||
                 (uVar28 = bluetooth::le_audio::has::HasDevice::DeserializePresets
                                     (local_a0,(long)uStack_98 - (long)local_a0,pRVar2),
                 (uVar28 & 1) == 0)) {
                bVar20 = false;
              }
              else {
                local_130 = (HasDevice *)CONCAT44(local_130._4_4_,0x6fe);
                pcStack_128 = (code *)0x123e5b;
                local_120 = "LoadHasDetailsFromStorage";
                local_1d0._0_4_ = 0;
                local_1d0._4_4_ = 0;
                bluetooth::log_internal::vlog
                          (2,"bluetooth",&local_130,"Loading HAS service details from storage.",0x29
                           ,&local_1d0);
                local_160 = (PresetInfo *)((ulong)local_160 & 0xffffffffffffff00);
                *(HasDevice *)(lVar42 + 0x48) = local_200._0_1_;
                uVar28 = btif_storage_get_leaudio_has_features(pRVar2,(uchar *)&local_160);
                if ((uVar28 & 1) != 0) {
                  *(HasPreset *)(lVar42 + 0x1c) = local_160._0_1_;
                  uVar23 = 0;
                  if (*(short *)(lVar42 + 0x20) != -1 && *(short *)(lVar42 + 0x24) != -1) {
                    uVar23 = 0xe2;
                  }
                  if (((ulong)local_160 & 4) != 0) {
                    uVar23 = 0x7e2;
                  }
                  *(ushort *)(lVar42 + 0x1e) = uVar23 | (byte)local_160._0_1_ >> 1 & 0x10;
                }
                *(undefined2 *)(lVar42 + 0x1a) = 0;
                NotifyHasDeviceValid(lVar52,pRVar2);
                uVar17 = *(uint6 *)(lVar42 + 0x10);
                plVar25 = *(long **)(lVar52 + 0x10);
                bluetooth::le_audio::has::HasDevice::GetAllPresetInfo();
                (**(code **)(*plVar25 + 0x40))(plVar25,(ulong)uVar17,0,0,&local_190);
                pcVar29 = local_190;
                if (local_190 != (code *)0x0) {
                  for (; pcVar29 != pcStack_188; pcStack_188 = pcStack_188 + -0x20) {
                    if (((byte)pcStack_188[-0x18] & 1) != 0) {
                      operator_delete(*(void **)(pcStack_188 + -8),
                                      *(ulong *)(pcStack_188 + -0x18) & 0xfffffffffffffffe);
                    }
                  }
                  pcStack_188 = pcVar29;
                  operator_delete(local_190,(long)local_180 - (long)local_190);
                }
                (**(code **)(**(long **)(lVar52 + 0x10) + 0x28))
                          (*(long **)(lVar52 + 0x10),pRVar2,*(undefined1 *)(lVar42 + 0x48));
                if (*(short *)(lVar42 + 0x16) != -1) {
                  local_130 = (HasDevice *)CONCAT44(local_130._4_4_,0x715);
                  pcStack_128 = (code *)0x123e5b;
                  local_120 = "LoadHasDetailsFromStorage";
                  local_1d0._0_4_ = 0;
                  local_1d0._4_4_ = 0;
                  bluetooth::log_internal::vlog
                            (4,"bluetooth",&local_130,"Subscribing for notification/indications",
                             0x28,&local_1d0);
                  WriteAllNeededCcc(lVar52,pRVar2);
                }
                bVar20 = true;
              }
              if (local_a0 != (code *)0x0) {
                uStack_98 = (char *)local_a0;
                operator_delete(local_a0,(long)local_90 - (long)local_a0);
              }
              if (bVar20) goto LAB_00730fcc;
              if (*(short *)(lVar42 + 0x2a) != -1) {
                if (*(short *)(lVar42 + 0x24) == -1) {
                  bVar20 = *(short *)(lVar42 + 0x20) != -1;
                }
                else {
                  if ((*(short *)(lVar42 + 0x20) == -1) || (*(short *)(lVar42 + 0x22) == -1))
                  goto LAB_00731358;
                  bVar20 = true;
                }
                uVar21 = 3;
                if (!(bool)(*(short *)(lVar42 + 0x24) != -1 & bVar20)) {
                  uVar21 = 1;
                }
                *(undefined1 *)(lVar42 + 0x1b) = uVar21;
                BtaGattQueue::ReadCharacteristic
                          (*(undefined2 *)(lVar42 + 0x16),*(short *)(lVar42 + 0x2a),
                           ::(anonymous_namespace)::HasClientImpl::
                           StartInitialHasDetailsReadAndValidation(gatt::Service_const&,bluetooth::le_audio::has::HasDevice*)
                           ::
                           {lambda(unsigned_short,GattStatus,unsigned_short,unsigned_short,unsigned_char*,void*)#1}
                           ::__invoke,0);
                if (*(short *)(lVar42 + 0x2c) == -1) {
                  local_1d0._0_4_ = 0x740;
                  pcStack_1c8 = "packages/modules/Bluetooth/system/bta/has/has_client.cc";
                  local_1c0 = "StartInitialHasDetailsReadAndValidation";
                  local_a0 = (code *)0x0;
                  bluetooth::log_internal::vlog
                            (5,"bluetooth",&local_1d0,
                             "server does not support features notification",0x2d,&local_a0);
                }
                else {
                  SubscribeForNotifications
                            (lVar52,*(undefined2 *)(lVar42 + 0x16),pRVar2,
                             *(undefined2 *)(lVar42 + 0x2a),*(short *)(lVar42 + 0x2c),1);
                }
                if ((*(short *)(lVar42 + 0x20) == -1) || (*(short *)(lVar42 + 0x24) == -1)) {
                  local_1d0._0_4_ = 0x75e;
                  pcStack_1c8 = "packages/modules/Bluetooth/system/bta/has/has_client.cc";
                  local_1c0 = "StartInitialHasDetailsReadAndValidation";
                  local_a0 = (code *)0x0;
                  bluetooth::log_internal::vlog
                            (5,"bluetooth",&local_1d0,
                             "server can only report HAS features, other functionality is disabled",
                             0x44,&local_a0);
                }
                else {
                  SubscribeForNotifications
                            (lVar52,*(undefined2 *)(lVar42 + 0x16),pRVar2,*(short *)(lVar42 + 0x20),
                             *(undefined2 *)(lVar42 + 0x22),1);
                  SubscribeForNotifications
                            (lVar52,*(undefined2 *)(lVar42 + 0x16),pRVar2,
                             *(undefined2 *)(lVar42 + 0x24),*(undefined2 *)(lVar42 + 0x26),
                             *(undefined1 *)(lVar42 + 0x28));
                  pcStack_128 = (code *)CONCAT17(pcStack_128._7_1_,0xff010100000000);
                  local_130 = (HasDevice *)(ulong)*(uint6 *)(lVar42 + 0x10);
                  local_120 = (char *)((ulong)local_120 & 0xffffffffffffff00);
                  uVar23 = DAT_01014290 + 1;
                  local_108 = (code *)((ulong)local_108 & 0xffffffffffffff00);
                  DAT_01014290 = DAT_01014290 + 1;
                  if ((uVar23 & 0xfffe) == 0) {
                    DAT_01014290 = 1;
                  }
                  local_100 = (void *)CONCAT62(local_100._2_6_,DAT_01014290);
                  CpReadAllPresetsOperation(lVar52,&local_130);
                  if (((char)local_108 == '\x01') && (((ulong)local_120 & 1) != 0)) {
                    operator_delete(pHStack_110,(ulong)local_120 & 0xfffffffffffffffe);
                  }
                  BtaGattQueue::ReadCharacteristic
                            (*(undefined2 *)(lVar42 + 0x16),*(undefined2 *)(lVar42 + 0x20),
                             ::(anonymous_namespace)::HasClientImpl::
                             StartInitialHasDetailsReadAndValidation(gatt::Service_const&,bluetooth::le_audio::has::HasDevice*)
                             ::
                             {lambda(unsigned_short,GattStatus,unsigned_short,unsigned_short,unsigned_char*,void*)#2}
                             ::__invoke,0);
                }
                goto LAB_00730fcc;
              }
              local_a0 = (code *)0x0;
              local_1d0 = CONCAT44(local_1d0._4_4_,0x720);
              pcVar32 = "Service has broken structure";
              pcStack_1c8 = "packages/modules/Bluetooth/system/bta/has/has_client.cc";
              local_1c0 = "StartInitialHasDetailsReadAndValidation";
              puVar36 = &local_1d0;
              puVar31 = &local_a0;
              uVar37 = 0x1c;
LAB_00731354:
              bluetooth::log_internal::vlog(6,"bluetooth",puVar36,pcVar32,uVar37,puVar31);
LAB_00731358:
              pcStack_128 = (code *)0x123e5b;
              local_120 = "OnGattServiceSearchComplete";
              local_130 = (HasDevice *)CONCAT44(local_130._4_4_,0x819);
              pcVar32 = "Not a valid service!";
              local_1d0._0_4_ = 0;
              local_1d0._4_4_ = 0;
              puVar31 = &local_130;
              puVar36 = &local_1d0;
              uVar37 = 0x14;
              goto LAB_0072ebdc;
            }
          }
          else {
            do {
              if (*(long *)(lVar47 + 0x12) == 0x10000054180000 &&
                  *(long *)(lVar47 + 0x1a) == -0x4cb64a07fffff80) goto LAB_0072ed84;
              lVar47 = *(long *)(lVar47 + 8);
            } while (lVar47 != lVar51);
          }
          pcStack_128 = (code *)0x123e5b;
          local_120 = "OnGattServiceSearchComplete";
          local_130 = (HasDevice *)CONCAT44(local_130._4_4_,0x812);
          pcVar32 = "No service found";
          local_1d0._0_4_ = 0;
          local_1d0._4_4_ = 0;
          puVar31 = &local_130;
          puVar36 = &local_1d0;
          uVar37 = 0x10;
          goto LAB_0072ebdc;
        }
      }
      else {
        do {
          if (*(ushort *)(lVar42 + 0x16) == uVar23) goto LAB_0072e6c0;
          lVar42 = *(long *)(lVar42 + 8);
        } while (lVar42 != param_1);
      }
      local_1c0 = "OnGattServiceSearchComplete";
      local_1d0._0_4_ = 0x7f6;
      goto LAB_0072e8f0;
    }
    lVar52 = *(long *)(param_1 + 0x20);
    lVar42 = param_1 + 0x18;
    if (lVar52 == lVar42) {
LAB_0072e768:
      if (lVar52 != lVar42) {
        pcStack_1c8 = "packages/modules/Bluetooth/system/bta/has/has_client.cc";
        local_1c0 = "OnGattDisconnected";
        local_120 = (char *)(ulong)*(ushort *)(param_3 + 0xc);
        local_1d0._0_4_ = 0x7e0;
        pcStack_128 = 
        _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
        ;
        uStack_98 = (char *)&local_130;
        local_118 = (code *)0x0;
        pHStack_110 = (HasDevice *)0x6f;
        local_a0 = (code *)0x2;
        local_90 = (HasDevice *)0x6f;
        local_130 = (HasDevice *)(lVar52 + 0x10);
        bluetooth::log_internal::vlog
                  (3,"bluetooth",&local_1d0,"device={}: reason=0x{:x}",0x18,&local_a0);
        if (((*(byte *)(lVar52 + 0x1a) & 1) != 0) || (*(char *)(lVar52 + 0x1b) == '\0')) {
          (**(code **)(**(long **)(param_1 + 0x10) + 0x10))
                    (*(long **)(param_1 + 0x10),0,param_3 + 4);
        }
        DoDisconnectCleanUp(param_1,(HasDevice *)(lVar52 + 0x10),
                            *(short *)(param_3 + 0xc) != 8 && *(short *)(param_3 + 0xc) != 0x13);
        goto LAB_00730fcc;
      }
    }
    else {
      do {
        if (*(int *)(param_3 + 4) == *(int *)(lVar52 + 0x10) &&
            *(short *)(param_3 + 8) == *(short *)(lVar52 + 0x14)) goto LAB_0072e768;
        lVar52 = *(long *)(lVar52 + 8);
      } while (lVar52 != lVar42);
    }
    local_130 = (HasDevice *)(ulong)*(ushort *)param_3;
    local_1d0._0_4_ = 0x7dd;
    local_1c0 = "OnGattDisconnected";
    local_90 = (HasDevice *)&DAT_00000006;
    pcVar32 = "Skipping unknown device disconnect, conn_id=0x{:x}";
    uVar37 = 0x32;
    pcStack_128 = (code *)0x0;
    local_120 = &DAT_00000006;
  }
  else {
    if (param_2 < 0xf) {
      if (param_2 != 8) {
        if (param_2 != 10) goto LAB_00730fcc;
        if (0x200 < *(ushort *)(param_3 + 10)) {
          local_1d0._0_4_ = 0x823;
          pcStack_1c8 = "packages/modules/Bluetooth/system/bta/has/has_client.cc";
          local_1c0 = "OnGattNotification";
          local_130 = (HasDevice *)(ulong)(byte)param_3[0x20c];
          uStack_98 = (char *)&local_130;
          pcStack_128 = (code *)0x0;
          local_118 = (code *)0x0;
          pHStack_110 = (HasDevice *)0x61;
          local_a0 = (code *)0x2;
          local_90 = (HasDevice *)0x61;
          local_120 = (char *)(ulong)*(ushort *)(param_3 + 10);
          bluetooth::log_internal::vlog
                    (6,"bluetooth",&local_1d0,"rejected BTA_GATTC_NOTIF_EVT. is_notify = {}, len={}"
                     ,0x34,&local_a0);
        }
        if (((byte)param_3[0x20c] & 1) == 0) {
          BTA_GATTC_SendIndConfirm(*(ushort *)param_3,*(ushort *)(param_3 + 0x20e));
        }
        lVar52 = *(long *)(param_1 + 0x20);
        uVar23 = *(ushort *)param_3;
        lVar42 = param_1 + 0x18;
        sVar14 = *(short *)(param_3 + 8);
        uVar33 = *(undefined2 *)(param_3 + 10);
        if (lVar52 == lVar42) {
LAB_0072e66c:
          if (lVar52 != lVar42) {
            pHVar1 = (HasDevice *)(lVar52 + 0x10);
            if (sVar14 == *(short *)(lVar52 + 0x2a)) {
              OnHasFeaturesValue(param_1,pHVar1,1,0,sVar14,uVar33,param_3 + 0xc);
            }
            else if (sVar14 == *(short *)(lVar52 + 0x24)) {
              local_1a0 = 0;
              pcStack_1b8 = (char *)0x0;
              local_1c0 = (char *)0x0;
              local_1a8 = 0;
              local_1b0 = 0;
              pcStack_1c8 = (char *)0x0;
              local_1d0._0_4_ = 0;
              local_1d0._4_4_ = 0;
              bluetooth::le_audio::has::HasCtpNtf::FromCharacteristicValue
                        (&local_1d0,uVar33,param_3 + 0xc);
              if ((local_1a0 & 1) == 0) {
                local_a0 = (code *)CONCAT44(local_a0._4_4_,0x61b);
                uVar33 = *(undefined2 *)(lVar52 + 0x16);
                uStack_98 = "packages/modules/Bluetooth/system/bta/has/has_client.cc";
                local_90 = (HasDevice *)0x10bddc;
                pcStack_188 = (code *)&local_130;
                pcStack_128 = 
                _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IN9bluetooth8le_audio3has9HasDeviceEEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESJ_SK_SM_
                ;
                local_120 = &DAT_0000000f;
                local_190 = (code *)0x1;
                local_180 = (HasDevice *)&DAT_0000000f;
                local_130 = pHVar1;
                bluetooth::log_internal::vlog
                          (6,"bluetooth",&local_a0,"Unhandled notification for device: {}",0x25,
                           &local_190);
                CleanAndDisconnectByConnId(param_1,uVar33);
              }
              else {
                this_00 = (string *)((ulong)&local_200 | 8);
                pcStack_1e8 = (char *)0x0;
                local_1f0 = (void *)0x0;
                local_1d8 = 0;
                local_1e0 = 0;
                uStack_1f8 = 0;
                local_200 = (ulong)(uint)local_1d0;
                if ((char)local_1a8 == '\x01') {
                  if (((ulong)pcStack_1c8 & 1) == 0) {
                    puVar36 = (undefined8 *)((ulong)&local_1d0 | 8);
                    uVar54 = *puVar36;
                    uVar37 = puVar36[2];
                    *(undefined8 *)(this_00 + 8) = puVar36[1];
                    *(undefined8 *)this_00 = uVar54;
                    *(undefined8 *)(this_00 + 0x10) = uVar37;
                  }
                  else {
                    std::string::__init_copy_ctor_external(this_00,pcStack_1b8,(ulong)local_1c0);
                  }
                  local_1d8 = CONCAT71(local_1d8._1_7_,1);
                  local_1e0 = CONCAT62(local_1e0._2_6_,(undefined2)local_1b0);
                }
                local_a0 = (code *)CONCAT44(local_a0._4_4_,0x621);
                uStack_98 = "packages/modules/Bluetooth/system/bta/has/has_client.cc";
                local_90 = (HasDevice *)0x10bddc;
                pcStack_188 = (code *)&local_130;
                pcStack_128 = 
                _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IN9bluetooth8le_audio3has9HasCtpNtfEEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESJ_SK_SM_
                ;
                local_120 = &DAT_0000000f;
                local_190 = (code *)0x1;
                local_180 = (HasDevice *)&DAT_0000000f;
                local_130 = (HasDevice *)&local_200;
                bluetooth::log_internal::vlog(3,"bluetooth",&local_a0,&DAT_0012915b,2,&local_190);
                plVar25 = (long *)FUN_00f62c00(0x40);
                *plVar25 = 0;
                plVar25[1] = 0;
                *(uint *)(plVar25 + 2) = (uint)local_200;
                uVar41 = (uint)local_200 >> 0x10 & 1;
                this = (string *)(plVar25 + 3);
                *this = (string)0x0;
                *(undefined1 *)(plVar25 + 7) = 0;
                if ((char)local_1d8 == '\x01') {
                  if ((uStack_1f8 & 1) == 0) {
                    uVar37 = *(undefined8 *)this_00;
                    lVar42 = *(long *)(this_00 + 0x10);
                    plVar25[4] = *(long *)(this_00 + 8);
                    *(undefined8 *)this = uVar37;
                    plVar25[5] = lVar42;
                  }
                  else {
                    std::string::__init_copy_ctor_external(this,pcStack_1e8,(ulong)local_1f0);
                    uVar41 = (uint)local_200._2_1_;
                  }
                  *(undefined1 *)(plVar25 + 7) = 1;
                  *(undefined2 *)(plVar25 + 6) = (undefined2)local_1e0;
                }
                plVar25[1] = lVar52 + 0x50;
                lVar42 = *(long *)(lVar52 + 0x50);
                *plVar25 = lVar42;
                *(long **)(lVar42 + 8) = plVar25;
                *(long **)(lVar52 + 0x50) = plVar25;
                lVar42 = *(long *)(lVar52 + 0x60) + 1;
                *(long *)(lVar52 + 0x60) = lVar42;
                if (((uVar41 & 1) != 0) && (lVar42 != 0)) {
                  p_Var3 = (__tree_node_base *)(lVar52 + 0x38);
                  do {
                    lVar42 = *(long *)(lVar52 + 0x58);
                    pvStack_178 = (void *)0x0;
                    local_180 = (HasDevice *)0x0;
                    local_170 = 0;
                    pcStack_188 = (code *)0x0;
                    local_168 = 0;
                    local_190 = (code *)(ulong)*(uint *)(lVar42 + 0x10);
                    if (*(char *)(lVar42 + 0x38) == '\x01') {
                      if ((*(byte *)(lVar42 + 0x18) & 1) == 0) {
                        local_180 = *(HasDevice **)(lVar42 + 0x20);
                        pcStack_188 = *(code **)(lVar42 + 0x18);
                        pvStack_178 = *(void **)(lVar42 + 0x28);
                      }
                      else {
                        std::string::__init_copy_ctor_external
                                  ((string *)&pcStack_188,*(char **)(lVar42 + 0x28),
                                   *(ulong *)(lVar42 + 0x20));
                      }
                      local_170 = CONCAT62(local_170._2_6_,*(undefined2 *)(lVar42 + 0x30));
                      local_168 = CONCAT71(local_168._1_7_,1);
                    }
                    local_a0 = (code *)CONCAT44(local_a0._4_4_,0x5f8);
                    uStack_98 = "packages/modules/Bluetooth/system/bta/has/has_client.cc";
                    local_90 = (HasDevice *)0x1e2854;
                    pcStack_128 = 
                    _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IN9bluetooth8le_audio3has9HasCtpNtfEEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESJ_SK_SM_
                    ;
                    local_120 = &DAT_0000000f;
                    local_160 = (PresetInfo *)0x1;
                    local_150 = (PresetInfo *)&DAT_0000000f;
                    pPStack_158 = (PresetInfo *)&local_130;
                    local_130 = (HasDevice *)&local_190;
                    bluetooth::log_internal::vlog(3,"bluetooth",&local_a0,"ntf: {}",7,&local_160);
                    uVar22 = (uchar)pHVar1;
                    if (local_190._0_1_ == (HasDevice)0x2) {
                      local_a0 = (code *)CONCAT44(local_a0._4_4_,0x4e4);
                      uStack_98 = "packages/modules/Bluetooth/system/bta/has/has_client.cc";
                      local_90 = (HasDevice *)0x1f236f;
                      local_160 = (PresetInfo *)0x0;
                      bluetooth::log_internal::vlog
                                (3,"bluetooth",&local_a0,&DAT_0013f82c,0,&local_160);
                      lVar42 = *(long *)(lVar52 + 0x60);
                      while (lVar42 != 0) {
                        lVar42 = *(long *)(lVar52 + 0x58);
                        pcStack_88 = (code *)0x0;
                        local_90 = (HasDevice *)0x0;
                        local_80 = 0;
                        uVar35 = *(uint *)(lVar42 + 0x10);
                        uStack_98 = (char *)0x0;
                        local_78 = 0;
                        uVar41 = uVar35 & 0xff;
                        local_a0 = (code *)(ulong)uVar35;
                        if (*(char *)(lVar42 + 0x38) == '\x01') {
                          if ((*(byte *)(lVar42 + 0x18) & 1) == 0) {
                            local_90 = *(HasDevice **)(lVar42 + 0x20);
                            uStack_98 = *(char **)(lVar42 + 0x18);
                            pcStack_88 = *(code **)(lVar42 + 0x28);
                          }
                          else {
                            std::string::__init_copy_ctor_external
                                      ((string *)&uStack_98,*(char **)(lVar42 + 0x28),
                                       *(ulong *)(lVar42 + 0x20));
                            uVar41 = (uint)(byte)local_a0;
                          }
                          local_78 = CONCAT71(local_78._1_7_,1);
                          local_80 = CONCAT62(local_80._2_6_,*(undefined2 *)(lVar42 + 0x30));
                          if (uVar41 == 2) {
                            local_160 = (PresetInfo *)0x0;
                            pPStack_158 = (PresetInfo *)0x0;
                            local_150 = (PresetInfo *)0x0;
                            local_148 = (char *)(CONCAT62((int6)((ulong)local_148 >> 0x10),
                                                          *(undefined2 *)(lVar42 + 0x30)) &
                                                0xffffffffffffff00);
                            std::
                            __tree<bluetooth::le_audio::has::HasPreset,bluetooth::le_audio::has::HasPreset::ComparatorDesc,std::allocator<bluetooth::le_audio::has::HasPreset>>
                            ::__erase_unique<bluetooth::le_audio::has::HasPreset>
                                      ((__tree<bluetooth::le_audio::has::HasPreset,bluetooth::le_audio::has::HasPreset::ComparatorDesc,std::allocator<bluetooth::le_audio::has::HasPreset>>
                                        *)(lVar52 + 0x30),(HasPreset *)&local_160);
                            if (((ulong)local_160 & 1) != 0) {
                              operator_delete(local_150,(ulong)local_160 & 0xfffffffffffffffe);
                            }
                            if ((local_78 & 1) == 0) {
LAB_007313e4:
                    /* WARNING: Subroutine does not return */
                              std::__throw_bad_optional_access_abi_nn220000_();
                            }
                            std::
                            __tree<bluetooth::le_audio::has::HasPreset,bluetooth::le_audio::has::HasPreset::ComparatorDesc,std::allocator<bluetooth::le_audio::has::HasPreset>>
                            ::
                            __emplace_unique_key_args<bluetooth::le_audio::has::HasPreset,bluetooth::le_audio::has::HasPreset_const&>
                                      ((__tree<bluetooth::le_audio::has::HasPreset,bluetooth::le_audio::has::HasPreset::ComparatorDesc,std::allocator<bluetooth::le_audio::has::HasPreset>>
                                        *)(lVar52 + 0x30),(HasPreset *)&uStack_98,
                                       (HasPreset *)&uStack_98);
                            if (*(char *)(lVar52 + 0x1b) == '\0') {
                              local_140 = 0;
                              pPStack_158 = (PresetInfo *)0x0;
                              local_160 = (PresetInfo *)0x0;
                              local_148 = (char *)0x0;
                              local_150 = (PresetInfo *)0x0;
                              if ((local_78 & 1) == 0) goto LAB_007313e4;
                              bluetooth::le_audio::has::HasDevice::GetPresetInfo(uVar22);
                              pPVar27 = pPStack_158;
                              if ((local_140 & 1) != 0) {
                                plVar25 = *(long **)(param_1 + 0x10);
                                uVar17 = *(uint6 *)pHVar1;
                                local_c0._0_3_ = SUB83(local_160,0);
                                if (((ulong)pPStack_158 & 1) == 0) {
                                  pPStack_b0 = local_150;
                                  local_b8 = pPStack_158;
                                  local_a8 = local_148;
                                }
                                else {
                                  std::string::__init_copy_ctor_external
                                            ((string *)&local_b8,local_148,(ulong)local_150);
                                }
                                local_218 = (PresetInfo *)FUN_00f62c00(0x20);
                                pPVar49 = local_218 + 0x20;
                                *(undefined2 *)local_218 = (undefined2)local_c0;
                                local_218[2] = local_c0._2_1_;
                                local_208 = pPVar49;
                                if (((ulong)local_b8 & 1) == 0) {
                                  *(PresetInfo **)(local_218 + 0x10) = pPStack_b0;
                                  *(PresetInfo **)(local_218 + 8) = local_b8;
                                  *(char **)(local_218 + 0x18) = local_a8;
                                }
                                else {
                                  local_210 = local_218;
                                  std::string::__init_copy_ctor_external
                                            ((string *)(local_218 + 8),local_a8,(ulong)pPStack_b0);
                                }
                                local_280 = (long *)((ulong)local_280 & 0xffffffff00000000);
                                local_210 = pPVar49;
                                (**(code **)(*plVar25 + 0x40))
                                          (plVar25,(ulong)uVar17,local_280,4,&local_218);
                                pPVar50 = local_218;
                                pPVar49 = local_210;
                                if (local_218 != (PresetInfo *)0x0) {
                                  for (; pPVar50 != pPVar49; pPVar49 = pPVar49 + -0x20) {
                                    if (((byte)pPVar49[-0x18] & 1) != 0) {
                                      operator_delete(*(void **)(pPVar49 + -8),
                                                      *(ulong *)(pPVar49 + -0x18) &
                                                      0xfffffffffffffffe);
                                    }
                                  }
                                  local_210 = pPVar50;
                                  operator_delete(local_218,(long)local_208 - (long)local_218);
                                }
                                if (((ulong)local_b8 & 1) != 0) {
                                  operator_delete(local_a8,(ulong)local_b8 & 0xfffffffffffffffe);
                                }
                                if (((ulong)pPVar27 & 1) != 0) {
                                  operator_delete(local_148,(ulong)pPStack_158 & 0xfffffffffffffffe)
                                  ;
                                }
                              }
                              local_118 = (code *)((ulong)local_118 & 0xffffffffffffff00);
                              local_f8 = local_f8 & 0xffffffffffffff00;
                              local_120 = (char *)CONCAT44(local_120._4_4_,(undefined4)local_a0);
                              if ((local_78 & 1) != 0) goto LAB_0072f714;
                            }
                            else {
                              local_118 = (code *)((ulong)local_118 & 0xffffffffffffff00);
                              local_f8 = local_f8 & 0xffffffffffffff00;
                              local_120 = (char *)CONCAT44(local_120._4_4_,(undefined4)local_a0);
                              if ((char)local_78 != '\0') {
LAB_0072f714:
                                if (((ulong)uStack_98 & 1) == 0) {
                                  pHStack_110 = local_90;
                                  local_118 = (code *)uStack_98;
                                  local_108 = pcStack_88;
                                }
                                else {
                                  std::string::__init_copy_ctor_external
                                            ((string *)&local_118,(char *)pcStack_88,(ulong)local_90
                                            );
                                }
                                local_100 = (void *)CONCAT62(local_100._2_6_,(undefined2)local_80);
                                uVar21 = 1;
                                goto LAB_0072f748;
                              }
                            }
                            goto LAB_0072f74c;
                          }
                          if (((ulong)uStack_98 & 1) == 0) break;
                          bVar20 = false;
LAB_0072f444:
                          operator_delete(pcStack_88,(ulong)uStack_98 & 0xfffffffffffffffe);
                          if (!bVar20) break;
                        }
                        else {
                          if (uVar41 != 2) break;
                          if (*(char *)(lVar52 + 0x1b) == '\0') goto LAB_007313e4;
                          uVar21 = 0;
                          local_120._4_4_ = (undefined4)((ulong)local_120 >> 0x20);
                          local_120 = (char *)CONCAT44(local_120._4_4_,uVar35);
                          local_118 = (code *)((ulong)local_118 & 0xffffffffffffff00);
LAB_0072f748:
                          local_f8 = CONCAT71(local_f8._1_7_,uVar21);
LAB_0072f74c:
                          local_e8 = (code *)CONCAT44(local_e8._4_4_,1);
                          clock_gettime(0,atStack_e0);
                          local_130 = (HasDevice *)((ulong)local_130 & 0xfffffffffffffff0 | 2);
                          bluetooth::le_audio::has::
                          CacheList<bluetooth::le_audio::has::HasJournalRecord,20ul>::Append
                                    ((CacheList<bluetooth::le_audio::has::HasJournalRecord,20ul> *)
                                     (lVar52 + 0x68),&local_130);
                          if ((int)local_e8 != -1) {
                            (*(code *)(&
                                      PTR___dispatch_abi_nn220000_<std::__variant_detail::__dtor<std::__variant_detail::__traits<bluetooth::le_audio::has::HasCtpOp,bluetooth::le_audio::has::HasCtpNtf,unsigned_char>,(std::__variant_detail::_Trait)1>::__destroy[abi:nn220000]()::_lambda(auto:1&)_1_&&,std::__variant_detail::__base<(std::__variant_detail::_Trait)1,bluetooth::le_audio::has::HasCtpOp,bluetooth::le_audio::has::HasCtpNtf,unsigned_char>&>_00f9d270
                                      )[(ulong)local_e8 & 0xffffffff])(&local_160,&local_120);
                          }
                          plVar26 = *(long **)(lVar52 + 0x58);
                          local_e8 = (code *)CONCAT44(local_e8._4_4_,0xffffffff);
                          plVar25 = (long *)plVar26[1];
                          *(long **)(*plVar26 + 8) = plVar25;
                          *plVar25 = *plVar26;
                          *(long *)(lVar52 + 0x60) = *(long *)(lVar52 + 0x60) + -1;
                          if (((char)plVar26[7] == '\x01') && ((*(byte *)(plVar26 + 3) & 1) != 0)) {
                            operator_delete((void *)plVar26[5],plVar26[3] & 0xfffffffffffffffe);
                          }
                          operator_delete(plVar26,0x40);
                          if (((char)local_78 == '\x01') && (((ulong)uStack_98 & 1) != 0)) {
                            bVar20 = true;
                            goto LAB_0072f444;
                          }
                        }
                        lVar42 = *(long *)(lVar52 + 0x60);
                      }
                      cVar10 = *(char *)(lVar52 + 0x1b);
                      MarkDeviceValidIfInInitialDiscovery(param_1,pHVar1);
                      if (cVar10 != '\0') {
                        uVar17 = *(uint6 *)pHVar1;
                        plVar25 = *(long **)(param_1 + 0x10);
                        bluetooth::le_audio::has::HasDevice::GetAllPresetInfo();
                        (**(code **)(*plVar25 + 0x40))(plVar25,(ulong)uVar17,0,0,&local_a0);
                        pcVar4 = local_a0;
                        pcVar29 = (code *)uStack_98;
                        if (local_a0 != (code *)0x0) {
                          for (; pcVar4 != pcVar29; pcVar29 = pcVar29 + -0x20) {
                            if (((byte)pcVar29[-0x18] & 1) != 0) {
                              operator_delete(*(void **)(pcVar29 + -8),
                                              *(ulong *)(pcVar29 + -0x18) & 0xfffffffffffffffe);
                            }
                          }
                          uStack_98 = (char *)pcVar4;
                          operator_delete(local_a0,(long)local_90 - (long)local_a0);
                        }
                        if (*(char *)(lVar52 + 0x1b) == '\0') {
                          (**(code **)(**(long **)(param_1 + 0x10) + 0x28))
                                    (*(long **)(param_1 + 0x10),pHVar1,
                                     *(undefined1 *)(lVar52 + 0x48));
                        }
                      }
                    }
                    else if (local_190._0_1_ == (HasDevice)0x3) {
                      if (local_190._1_1_ < 2) {
                        if (local_190._1_1_ == 0) {
                          local_a0 = (code *)CONCAT44(local_a0._4_4_,0x517);
                          uStack_98 = "packages/modules/Bluetooth/system/bta/has/has_client.cc";
                          local_90 = (HasDevice *)0x13aae1;
                          local_160 = (PresetInfo *)0x0;
                          bluetooth::log_internal::vlog
                                    (2,"bluetooth",&local_a0,&DAT_0013f82c,0,&local_160);
                          local_c0 = (PresetInfo *)0x0;
                          local_b8 = (PresetInfo *)0x0;
                          pPStack_b0 = (PresetInfo *)0x0;
                          local_218 = (PresetInfo *)0x0;
                          local_210 = (PresetInfo *)0x0;
                          local_208 = (PresetInfo *)0x0;
                          if (*(long *)(lVar52 + 0x60) != 0) {
                            do {
                              lVar42 = *(long *)(lVar52 + 0x58);
                              pcStack_88 = (code *)0x0;
                              local_90 = (HasDevice *)0x0;
                              local_80 = 0;
                              uVar41 = *(uint *)(lVar42 + 0x10);
                              uStack_98 = (char *)0x0;
                              local_78 = 0;
                              uVar35 = uVar41 >> 8 & 0xff;
                              local_a0 = (code *)(ulong)uVar41;
                              uVar41 = uVar41 & 0xff;
                              if (*(char *)(lVar42 + 0x38) == '\x01') {
                                if ((*(byte *)(lVar42 + 0x18) & 1) == 0) {
                                  local_90 = *(HasDevice **)(lVar42 + 0x20);
                                  uStack_98 = *(char **)(lVar42 + 0x18);
                                  pcStack_88 = *(code **)(lVar42 + 0x28);
                                }
                                else {
                                  std::string::__init_copy_ctor_external
                                            ((string *)&uStack_98,*(char **)(lVar42 + 0x28),
                                             *(ulong *)(lVar42 + 0x20));
                                  uVar41 = (uint)(byte)local_a0;
                                  uVar35 = (uint)local_a0._1_1_;
                                }
                                bVar20 = true;
                                local_78 = CONCAT71(local_78._1_7_,1);
                                local_80 = CONCAT62(local_80._2_6_,*(ushort *)(lVar42 + 0x30));
                                if ((uVar41 == 3) && (uVar35 == 0)) {
                                  p_Var39 = *(__tree_node_base **)(lVar52 + 0x30);
                                  if (*(__tree_node_base **)(lVar52 + 0x30) == p_Var3) {
                                    uVar23 = *(ushort *)(lVar42 + 0x30) >> 8;
                                  }
                                  else {
                                    do {
                                      if (((byte)local_a0._3_1_ < (byte)p_Var39[0x39]) &&
                                         ((byte)p_Var39[0x39] < (byte)local_80._1_1_)) {
                                        local_140 = 0;
                                        pPStack_158 = (PresetInfo *)0x0;
                                        local_160 = (PresetInfo *)0x0;
                                        local_148 = (char *)0x0;
                                        local_150 = (PresetInfo *)0x0;
                                        bluetooth::le_audio::has::HasDevice::GetPresetInfo(uVar22);
                                        pPVar27 = local_210;
                                        if ((local_140 & 1) != 0) {
                                          if (local_210 < local_208) {
                                            *(undefined2 *)local_210 = (undefined2)local_160;
                                            local_210[2] = local_160._2_1_;
                                            if (((ulong)pPStack_158 & 1) == 0) {
                                              *(PresetInfo **)(local_210 + 0x10) = local_150;
                                              *(PresetInfo **)(local_210 + 8) = pPStack_158;
                                              *(char **)(local_210 + 0x18) = local_148;
                                              local_210 = local_210 + 0x20;
                                            }
                                            else {
                                              std::string::__init_copy_ctor_external
                                                        ((string *)(local_210 + 8),local_148,
                                                         (ulong)local_150);
                                              local_210 = pPVar27 + 0x20;
                                            }
                                          }
                                          else {
                                            local_210 = std::
                                                  vector<bluetooth::has::PresetInfo,std::allocator<bluetooth::has::PresetInfo>>
                                                  ::
                                                  __emplace_back_slow_path<bluetooth::has::PresetInfo_const&>
                                                            ((
                                                  vector<bluetooth::has::PresetInfo,std::allocator<bluetooth::has::PresetInfo>>
                                                  *)&local_218,(PresetInfo *)&local_160);
                                          }
                                        }
                                        p_Var44 = *(__tree_node_base **)(p_Var39 + 8);
                                        p_Var45 = p_Var39;
                                        if (*(__tree_node_base **)(p_Var39 + 8) ==
                                            (__tree_node_base *)0x0) {
                                          do {
                                            p_Var43 = *(__tree_node_base **)(p_Var45 + 0x10);
                                            bVar20 = p_Var45 != *(__tree_node_base **)p_Var43;
                                            p_Var45 = p_Var43;
                                          } while (bVar20);
                                        }
                                        else {
                                          do {
                                            p_Var43 = p_Var44;
                                            p_Var44 = *(__tree_node_base **)p_Var43;
                                          } while (*(__tree_node_base **)p_Var43 !=
                                                   (__tree_node_base *)0x0);
                                        }
                                        if (*(__tree_node_base **)(lVar52 + 0x30) == p_Var39) {
                                          *(__tree_node_base **)(lVar52 + 0x30) = p_Var43;
                                        }
                                        *(long *)(lVar52 + 0x40) = *(long *)(lVar52 + 0x40) + -1;
                                        std::
                                        __tree_remove_abi_nn220000_<std::__tree_node_base<void*>*>
                                                  (*(__tree_node_base **)(lVar52 + 0x38),p_Var39);
                                        if (((byte)p_Var39[0x20] & 1) != 0) {
                                          operator_delete(*(void **)(p_Var39 + 0x30),
                                                          *(ulong *)(p_Var39 + 0x20) &
                                                          0xfffffffffffffffe);
                                        }
                                        operator_delete(p_Var39,0x40);
                                        if (((local_140 & 1) != 0) &&
                                           (((ulong)pPStack_158 & 1) != 0)) {
                                          operator_delete(local_148,
                                                          (ulong)pPStack_158 & 0xfffffffffffffffe);
                                        }
                                      }
                                      else {
                                        p_Var44 = *(__tree_node_base **)(p_Var39 + 8);
                                        if (*(__tree_node_base **)(p_Var39 + 8) ==
                                            (__tree_node_base *)0x0) {
                                          do {
                                            p_Var43 = *(__tree_node_base **)(p_Var39 + 0x10);
                                            bVar20 = p_Var39 != *(__tree_node_base **)p_Var43;
                                            p_Var39 = p_Var43;
                                          } while (bVar20);
                                        }
                                        else {
                                          do {
                                            p_Var43 = p_Var44;
                                            p_Var44 = *(__tree_node_base **)p_Var43;
                                          } while (*(__tree_node_base **)p_Var43 !=
                                                   (__tree_node_base *)0x0);
                                        }
                                      }
                                      p_Var39 = p_Var43;
                                    } while (p_Var43 != p_Var3);
                                    uVar23 = (ushort)(byte)local_80._1_1_;
                                  }
                                  p_Var43 = *(__tree_node_base **)p_Var3;
                                  p_Var39 = p_Var3;
                                  p_Var44 = p_Var43;
joined_r0x0072ffb0:
                                  if (p_Var44 == (__tree_node_base *)0x0) goto LAB_0073011c;
                                  if (uVar23 < (byte)p_Var44[0x39]) {
                                    p_Var39 = p_Var44;
                                    p_Var44 = *(__tree_node_base **)p_Var44;
                                    goto joined_r0x0072ffb0;
                                  }
                                  if ((byte)p_Var44[0x39] < uVar23) {
                                    p_Var44 = *(__tree_node_base **)(p_Var44 + 8);
                                    goto joined_r0x0072ffb0;
                                  }
                                  p_Var45 = p_Var44;
                                  for (p_Var46 = *(__tree_node_base **)p_Var44;
                                      p_Var46 != (__tree_node_base *)0x0;
                                      p_Var46 = *(__tree_node_base **)(p_Var46 + lVar42)) {
                                    lVar42 = 8;
                                    if (uVar23 <= (byte)p_Var46[0x39]) {
                                      lVar42 = 0;
                                      p_Var45 = p_Var46;
                                    }
                                  }
                                  for (p_Var44 = *(__tree_node_base **)(p_Var44 + 8);
                                      p_Var44 != (__tree_node_base *)0x0;
                                      p_Var44 = *(__tree_node_base **)(p_Var44 + lVar42)) {
                                    lVar42 = 0;
                                    p_Var46 = p_Var44;
                                    if ((byte)p_Var44[0x39] <= uVar23) {
                                      lVar42 = 8;
                                      p_Var46 = p_Var39;
                                    }
                                    p_Var39 = p_Var46;
                                  }
                                  p_Var44 = p_Var3;
                                  if (p_Var45 == p_Var39) {
LAB_0073011c:
                                    std::
                                    __tree<bluetooth::le_audio::has::HasPreset,bluetooth::le_audio::has::HasPreset::ComparatorDesc,std::allocator<bluetooth::le_audio::has::HasPreset>>
                                    ::
                                    __emplace_unique_key_args<bluetooth::le_audio::has::HasPreset,bluetooth::le_audio::has::HasPreset_const&>
                                              ((__tree<bluetooth::le_audio::has::HasPreset,bluetooth::le_audio::has::HasPreset::ComparatorDesc,std::allocator<bluetooth::le_audio::has::HasPreset>>
                                                *)(lVar52 + 0x30),(HasPreset *)&uStack_98,
                                               (HasPreset *)&uStack_98);
                                    bluetooth::le_audio::has::HasDevice::GetPresetInfo(uVar22);
                                    if (local_b8 < pPStack_b0) {
                                      pPVar27 = local_b8 + 0x20;
                                      *(undefined2 *)local_b8 = (undefined2)local_160;
                                      local_b8[2] = local_160._2_1_;
                                      *(PresetInfo **)(local_b8 + 0x10) = local_150;
                                      *(PresetInfo **)(local_b8 + 8) = pPStack_158;
                                      *(char **)(local_b8 + 0x18) = local_148;
                                      pPStack_158 = (PresetInfo *)0x0;
                                      local_150 = (PresetInfo *)0x0;
                                      local_148 = (char *)0x0;
                                    }
                                    else {
                                      pPVar27 = std::
                                                vector<bluetooth::has::PresetInfo,std::allocator<bluetooth::has::PresetInfo>>
                                                ::
                                                __emplace_back_slow_path<bluetooth::has::PresetInfo>
                                                          ((
                                                  vector<bluetooth::has::PresetInfo,std::allocator<bluetooth::has::PresetInfo>>
                                                  *)&local_c0,(PresetInfo *)&local_160);
                                    }
                                    local_b8 = pPVar27;
                                    if (((char)local_140 == '\x01') &&
                                       (((ulong)pPStack_158 & 1) != 0)) {
                                      operator_delete(local_148,
                                                      (ulong)pPStack_158 & 0xfffffffffffffffe);
                                    }
                                    goto LAB_007301b0;
                                  }
                                  do {
                                    lVar42 = 8;
                                    if (uVar23 <= (byte)p_Var43[0x39]) {
                                      lVar42 = 0;
                                      p_Var44 = p_Var43;
                                    }
                                    p_Var43 = *(__tree_node_base **)(p_Var43 + lVar42);
                                  } while (p_Var43 != (__tree_node_base *)0x0);
                                  p_Var39 = p_Var3;
                                  if ((p_Var44 != p_Var3) && ((byte)p_Var44[0x39] <= uVar23)) {
                                    p_Var39 = p_Var44;
                                  }
                                  if (((byte)p_Var39[0x39] != uVar23) ||
                                     (p_Var39[0x38] != local_80._0_1_)) {
LAB_007300e8:
                                    local_160 = (PresetInfo *)0x0;
                                    pPStack_158 = (PresetInfo *)0x0;
                                    local_150 = (PresetInfo *)0x0;
                                    local_148 = (char *)((ulong)CONCAT61((int6)((ulong)local_148 >>
                                                                               0x10),(char)uVar23)
                                                        << 8);
                                    std::
                                    __tree<bluetooth::le_audio::has::HasPreset,bluetooth::le_audio::has::HasPreset::ComparatorDesc,std::allocator<bluetooth::le_audio::has::HasPreset>>
                                    ::__erase_unique<bluetooth::le_audio::has::HasPreset>
                                              ((__tree<bluetooth::le_audio::has::HasPreset,bluetooth::le_audio::has::HasPreset::ComparatorDesc,std::allocator<bluetooth::le_audio::has::HasPreset>>
                                                *)(lVar52 + 0x30),(HasPreset *)&local_160);
                                    if (((ulong)local_160 & 1) != 0) {
                                      operator_delete(local_150,
                                                      (ulong)local_160 & 0xfffffffffffffffe);
                                    }
                                    goto LAB_0073011c;
                                  }
                                  _Var11 = p_Var39[0x20];
                                  __n = (HasDevice *)(ulong)((byte)_Var11 >> 1);
                                  if (((byte)_Var11 & 1) != 0) {
                                    __n = *(HasDevice **)(p_Var39 + 0x28);
                                  }
                                  pHVar6 = (HasDevice *)((ulong)uStack_98 >> 1 & 0x7f);
                                  if (((ulong)uStack_98 & 1) != 0) {
                                    pHVar6 = local_90;
                                  }
                                  if (__n != pHVar6) goto LAB_007300e8;
                                  p_Var44 = p_Var39 + 0x21;
                                  if (((byte)_Var11 & 1) != 0) {
                                    p_Var44 = *(__tree_node_base **)(p_Var39 + 0x30);
                                  }
                                  pcVar29 = (code *)((long)&uStack_98 + 1);
                                  if (((ulong)uStack_98 & 1) != 0) {
                                    pcVar29 = pcStack_88;
                                  }
                                  iVar24 = memcmp(p_Var44,pcVar29,(size_t)__n);
                                  if (iVar24 != 0) goto LAB_007300e8;
                                  goto LAB_007301b0;
                                }
LAB_007302cc:
                                if (((ulong)uStack_98 & 1) != 0) {
                                  operator_delete(pcStack_88,(ulong)uStack_98 & 0xfffffffffffffffe);
                                }
                              }
                              else {
                                if (uVar41 != 3 || uVar35 != 0) break;
LAB_007301b0:
                                local_118 = (code *)((ulong)local_118 & 0xffffffffffffff00);
                                local_120 = (char *)CONCAT44(local_120._4_4_,(undefined4)local_a0);
                                local_f8 = local_f8 & 0xffffffffffffff00;
                                if ((char)local_78 == '\x01') {
                                  if (((ulong)uStack_98 & 1) == 0) {
                                    pHStack_110 = local_90;
                                    local_118 = (code *)uStack_98;
                                    local_108 = pcStack_88;
                                  }
                                  else {
                                    std::string::__init_copy_ctor_external
                                              ((string *)&local_118,(char *)pcStack_88,
                                               (ulong)local_90);
                                  }
                                  local_100 = (void *)CONCAT62(local_100._2_6_,(undefined2)local_80)
                                  ;
                                  local_f8 = CONCAT71(local_f8._1_7_,1);
                                }
                                local_e8 = (code *)CONCAT44(local_e8._4_4_,1);
                                clock_gettime(0,atStack_e0);
                                local_130 = (HasDevice *)((ulong)local_130 & 0xfffffffffffffff0 | 2)
                                ;
                                bluetooth::le_audio::has::
                                CacheList<bluetooth::le_audio::has::HasJournalRecord,20ul>::Append
                                          ((CacheList<bluetooth::le_audio::has::HasJournalRecord,20ul>
                                            *)(lVar52 + 0x68),&local_130);
                                if ((int)local_e8 != -1) {
                                  (*(code *)(&
                                            PTR___dispatch_abi_nn220000_<std::__variant_detail::__dtor<std::__variant_detail::__traits<bluetooth::le_audio::has::HasCtpOp,bluetooth::le_audio::has::HasCtpNtf,unsigned_char>,(std::__variant_detail::_Trait)1>::__destroy[abi:nn220000]()::_lambda(auto:1&)_1_&&,std::__variant_detail::__base<(std::__variant_detail::_Trait)1,bluetooth::le_audio::has::HasCtpOp,bluetooth::le_audio::has::HasCtpNtf,unsigned_char>&>_00f9d270
                                            )[(ulong)local_e8 & 0xffffffff])(&local_160,&local_120);
                                }
                                plVar26 = *(long **)(lVar52 + 0x58);
                                local_e8 = (code *)CONCAT44(local_e8._4_4_,0xffffffff);
                                plVar25 = (long *)plVar26[1];
                                *(long **)(*plVar26 + 8) = plVar25;
                                *plVar25 = *plVar26;
                                *(long *)(lVar52 + 0x60) = *(long *)(lVar52 + 0x60) + -1;
                                if (((char)plVar26[7] == '\x01') &&
                                   ((*(byte *)(plVar26 + 3) & 1) != 0)) {
                                  operator_delete((void *)plVar26[5],plVar26[3] & 0xfffffffffffffffe
                                                 );
                                }
                                operator_delete(plVar26,0x40);
                                bVar20 = false;
                                if ((char)local_78 == '\x01') goto LAB_007302cc;
                              }
                              if ((bVar20) || (*(long *)(lVar52 + 0x60) == 0)) break;
                            } while( true );
                          }
                          if (*(char *)(lVar52 + 0x1b) == '\0') {
                            local_160 = (PresetInfo *)0x0;
                            pPStack_158 = (PresetInfo *)0x0;
                            local_150 = (PresetInfo *)0x0;
                            uVar28 = bluetooth::le_audio::has::HasDevice::SerializePresets
                                               (pHVar1,(vector *)&local_160);
                            pPVar27 = local_160;
                            if ((uVar28 & 1) != 0) {
                              local_230 = (void *)0x0;
                              local_228 = (void *)0x0;
                              local_220 = (void *)0x0;
                              sVar15 = (long)pPStack_158 - (long)local_160;
                              if (sVar15 != 0) {
                                if ((long)sVar15 < 0) {
LAB_007313ec:
                    /* WARNING: Subroutine does not return */
                                  std::vector<signed_char,std::allocator<signed_char>>::
                                  __throw_length_error_abi_nn220000_();
                                }
                                local_230 = (void *)FUN_00f62c00(sVar15);
                                pvVar30 = (void *)((long)local_230 + sVar15);
                                local_228 = local_230;
                                local_220 = pvVar30;
                                memcpy(local_230,pPVar27,sVar15);
                                local_228 = pvVar30;
                              }
                              btif_storage_set_leaudio_has_presets(pHVar1,&local_230);
                              if (local_230 != (void *)0x0) {
                                local_228 = local_230;
                                operator_delete(local_230,(long)local_220 - (long)local_230);
                              }
                            }
                            plVar25 = (long *)(param_1 + 0x50);
                            pPVar27 = local_b8;
                            if ((long *)(param_1 + 0x50) != *(long **)(param_1 + 0x48)) {
LAB_00730574:
                              pPVar49 = local_b8;
                              plVar48 = (long *)*plVar25;
                              plVar26 = plVar25;
                              plVar40 = plVar48;
                              if (plVar48 == (long *)0x0) {
                                do {
                                  plVar53 = (long *)plVar26[2];
                                  bVar20 = plVar26 == (long *)*plVar53;
                                  plVar26 = plVar53;
                                } while (bVar20);
                              }
                              else {
                                do {
                                  plVar53 = plVar40;
                                  plVar40 = (long *)plVar53[1];
                                } while ((long *)plVar53[1] != (long *)0x0);
                              }
                              if ((*(char *)((long)plVar53 + 0x4c) != '\x04') ||
                                 ((char)plVar53[0xd] != '\x01')) goto LAB_007306a0;
                              pPVar27 = local_c0;
                              if (local_c0 != local_b8) {
                                bVar13 = *(byte *)(plVar53 + 10);
                                sVar15 = (ulong)(bVar13 >> 1);
                                if ((bVar13 & 1) != 0) {
                                  sVar15 = plVar53[0xb];
                                }
                                do {
                                  PVar12 = pPVar27[8];
                                  sVar7 = (ulong)((byte)PVar12 >> 1);
                                  if (((byte)PVar12 & 1) != 0) {
                                    sVar7 = *(size_t *)(pPVar27 + 0x10);
                                  }
                                  if (sVar15 == sVar7) {
                                    pvVar30 = (void *)((long)plVar53 + 0x51);
                                    if ((bVar13 & 1) != 0) {
                                      pvVar30 = (void *)plVar53[0xc];
                                    }
                                    pPVar50 = pPVar27 + 9;
                                    if (((byte)PVar12 & 1) != 0) {
                                      pPVar50 = *(PresetInfo **)(pPVar27 + 0x18);
                                    }
                                    iVar24 = memcmp(pvVar30,pPVar50,sVar15);
                                    if (iVar24 == 0) goto LAB_00730644;
                                  }
                                  pPVar27 = pPVar27 + 0x20;
                                } while (pPVar27 != pPVar49);
                                goto LAB_007306a0;
                              }
LAB_00730644:
                              if (pPVar27 == pPVar49) goto LAB_007306a0;
                              plVar26 = (long *)((ulong)local_280 & 0xffff000000000000 |
                                                (ulong)*(uint6 *)pHVar1);
                              uVar28 = bluetooth::le_audio::has::HasCtpGroupOpCoordinator::
                                       SetCompleted(plVar53 + 5,plVar26);
                              if ((uVar28 & 1) == 0) {
                                plVar48 = (long *)*plVar25;
                                local_280 = plVar26;
                                goto LAB_007306a0;
                              }
                              plVar26 = (long *)FUN_00f62c00(0x30);
                              *plVar26 = 0;
                              plVar26[1] = 0;
                              PVar12 = pPVar27[2];
                              *(undefined2 *)(plVar26 + 2) = *(undefined2 *)pPVar27;
                              *(PresetInfo *)((long)plVar26 + 0x12) = PVar12;
                              pPVar49 = pPVar27 + 8;
                              if (((byte)*pPVar49 & 1) == 0) {
                                lVar51 = *(long *)(pPVar27 + 0x10);
                                lVar42 = *(long *)pPVar49;
                                plVar26[5] = *(long *)(pPVar27 + 0x18);
                                plVar26[4] = lVar51;
                                plVar26[3] = lVar42;
                              }
                              else {
                                std::string::__init_copy_ctor_external
                                          ((string *)(plVar26 + 3),*(char **)(pPVar27 + 0x18),
                                           *(ulong *)(pPVar27 + 0x10));
                              }
                              plVar26[1] = (long)(plVar53 + 0xf);
                              lVar42 = DAT_01014280;
                              lVar51 = plVar53[0xf];
                              *plVar26 = lVar51;
                              *(long **)(lVar51 + 8) = plVar26;
                              plVar53[0xf] = (long)plVar26;
                              plVar53[0x11] = plVar53[0x11] + 1;
                              if (lVar42 == 0) {
                                uVar8 = (undefined4)plVar53[8];
                                plVar26 = *(long **)(param_1 + 0x10);
                                if ((int)plVar53[9] != 1) {
                                  uVar8 = 0xffffffff;
                                }
                                local_a0 = (code *)CONCAT62(CONCAT51(local_a0._3_5_,pPVar27[2]),
                                                            *(undefined2 *)pPVar27);
                                if (((byte)pPVar27[8] & 1) == 0) {
                                  pcStack_88 = *(code **)(pPVar27 + 0x18);
                                  local_90 = *(HasDevice **)(pPVar27 + 0x10);
                                  uStack_98 = *(char **)pPVar49;
                                }
                                else {
                                  std::string::__init_copy_ctor_external
                                            ((string *)&uStack_98,*(char **)(pPVar27 + 0x18),
                                             *(ulong *)(pPVar27 + 0x10));
                                }
                                local_248 = (undefined2 *)FUN_00f62c00(0x20);
                                puVar5 = local_248 + 0x10;
                                *local_248 = (undefined2)local_a0;
                                *(undefined1 *)(local_248 + 1) = local_a0._2_1_;
                                local_238 = puVar5;
                                if (((ulong)uStack_98 & 1) == 0) {
                                  *(HasDevice **)(local_248 + 8) = local_90;
                                  *(char **)(local_248 + 4) = uStack_98;
                                  *(code **)(local_248 + 0xc) = pcStack_88;
                                }
                                else {
                                  local_240 = local_248;
                                  std::string::__init_copy_ctor_external
                                            ((string *)(local_248 + 4),(char *)pcStack_88,
                                             (ulong)local_90);
                                }
                                local_240 = puVar5;
                                (**(code **)(*plVar26 + 0x40))(plVar26,uVar8,1,1,&local_248);
                                puVar19 = local_248;
                                puVar5 = local_240;
                                if (local_248 != (undefined2 *)0x0) {
                                  for (; puVar19 != puVar5; puVar5 = puVar5 + -0x10) {
                                    if ((*(byte *)(puVar5 + -0xc) & 1) != 0) {
                                      operator_delete(*(void **)(puVar5 + -4),
                                                      *(ulong *)(puVar5 + -0xc) & 0xfffffffffffffffe
                                                     );
                                    }
                                  }
                                  local_240 = puVar19;
                                  operator_delete(local_248,(long)local_238 - (long)local_248);
                                }
                                if (((ulong)uStack_98 & 1) != 0) {
                                  operator_delete(pcStack_88,(ulong)uStack_98 & 0xfffffffffffffffe);
                                }
                                plVar26 = (long *)*plVar25;
                                if ((long *)*plVar25 == (long *)0x0) {
                                  do {
                                    plVar40 = (long *)plVar25[2];
                                    bVar20 = plVar25 == (long *)*plVar40;
                                    plVar25 = plVar40;
                                  } while (bVar20);
                                }
                                else {
                                  do {
                                    plVar40 = plVar26;
                                    plVar26 = (long *)plVar40[1];
                                  } while ((long *)plVar40[1] != (long *)0x0);
                                }
                                std::
                                __tree<std::__value_type<unsigned_short,bluetooth::le_audio::has::HasCtpGroupOpCoordinator>,std::__map_value_compare<unsigned_short,std::pair<unsigned_short_const,bluetooth::le_audio::has::HasCtpGroupOpCoordinator>,std::less<unsigned_short>,true>,std::allocator<std::pair<unsigned_short_const,bluetooth::le_audio::has::HasCtpGroupOpCoordinator>>>
                                ::__erase_unique<unsigned_short>
                                          ((__tree<std::__value_type<unsigned_short,bluetooth::le_audio::has::HasCtpGroupOpCoordinator>,std::__map_value_compare<unsigned_short,std::pair<unsigned_short_const,bluetooth::le_audio::has::HasCtpGroupOpCoordinator>,std::less<unsigned_short>,true>,std::allocator<std::pair<unsigned_short_const,bluetooth::le_audio::has::HasCtpGroupOpCoordinator>>>
                                            *)(param_1 + 0x48),(ushort *)(plVar40 + 4));
                              }
                              pPVar50 = local_b8;
                              pPVar49 = pPVar27 + 0x20;
                              while (pPVar49 != pPVar50) {
                                *(undefined2 *)pPVar27 = *(undefined2 *)(pPVar27 + 0x20);
                                pPVar27[2] = pPVar27[0x22];
                                if (((byte)pPVar27[8] & 1) != 0) {
                                  operator_delete(*(void **)(pPVar27 + 0x18),
                                                  *(ulong *)(pPVar27 + 8) & 0xfffffffffffffffe);
                                }
                                uVar37 = *(undefined8 *)(pPVar27 + 0x28);
                                *(undefined2 *)(pPVar27 + 0x28) = 0;
                                *(undefined8 *)(pPVar27 + 0x10) = *(undefined8 *)(pPVar27 + 0x30);
                                *(undefined8 *)(pPVar27 + 8) = uVar37;
                                *(undefined8 *)(pPVar27 + 0x18) = *(undefined8 *)(pPVar27 + 0x38);
                                pPVar49 = pPVar27 + 0x40;
                                pPVar27 = pPVar27 + 0x20;
                              }
                              for (; pPVar27 != pPVar50; pPVar50 = pPVar50 + -0x20) {
                                if (((byte)pPVar50[-0x18] & 1) != 0) {
                                  operator_delete(*(void **)(pPVar50 + -8),
                                                  *(ulong *)(pPVar50 + -0x18) & 0xfffffffffffffffe);
                                }
                              }
                            }
LAB_00730950:
                            local_b8 = pPVar27;
                            pPVar49 = local_b8;
                            pPVar27 = local_c0;
                            if (local_c0 != local_b8) {
                              plVar25 = *(long **)(param_1 + 0x10);
                              lVar42 = (long)local_b8 - (long)local_c0;
                              local_a0 = (code *)0x0;
                              uStack_98 = (char *)0x0;
                              local_90 = (HasDevice *)0x0;
                              if (lVar42 < 0) goto LAB_007313e8;
                              local_280 = (long *)(ulong)*(uint6 *)pHVar1;
                              pcVar29 = (code *)FUN_00f62c00(lVar42);
                              lVar51 = 0;
                              local_90 = (HasDevice *)(pcVar29 + lVar42);
                              local_a0 = pcVar29;
                              uStack_98 = (char *)pcVar29;
                              do {
                                pPVar50 = pPVar27 + lVar51;
                                pcVar4 = pcVar29 + lVar51;
                                PVar12 = pPVar50[2];
                                *(undefined2 *)pcVar4 = *(undefined2 *)pPVar50;
                                *(PresetInfo *)(pcVar4 + 2) = PVar12;
                                if (((byte)pPVar50[8] & 1) == 0) {
                                  uVar54 = *(undefined8 *)(pPVar50 + 0x10);
                                  uVar37 = *(undefined8 *)(pPVar50 + 8);
                                  *(undefined8 *)(pcVar4 + 0x18) = *(undefined8 *)(pPVar50 + 0x18);
                                  *(undefined8 *)(pcVar4 + 0x10) = uVar54;
                                  *(undefined8 *)(pcVar4 + 8) = uVar37;
                                }
                                else {
                                  std::string::__init_copy_ctor_external
                                            ((string *)(pcVar4 + 8),*(char **)(pPVar50 + 0x18),
                                             *(ulong *)(pPVar50 + 0x10));
                                }
                                lVar51 = lVar51 + 0x20;
                              } while (pPVar27 + lVar51 != pPVar49);
                              uStack_98 = (char *)(pcVar29 + lVar51);
                              (**(code **)(*plVar25 + 0x40))(plVar25,local_280,0,1,&local_a0);
                              pcVar4 = local_a0;
                              pcVar29 = (code *)uStack_98;
                              if (local_a0 != (code *)0x0) {
                                for (; pcVar4 != pcVar29; pcVar29 = pcVar29 + -0x20) {
                                  if (((byte)pcVar29[-0x18] & 1) != 0) {
                                    operator_delete(*(void **)(pcVar29 + -8),
                                                    *(ulong *)(pcVar29 + -0x18) & 0xfffffffffffffffe
                                                   );
                                  }
                                }
                                uStack_98 = (char *)pcVar4;
                                operator_delete(local_a0,(long)local_90 - (long)local_a0);
                              }
                            }
                            pPVar49 = local_210;
                            pPVar27 = local_218;
                            if (local_218 != local_210) {
                              plVar25 = *(long **)(param_1 + 0x10);
                              lVar42 = (long)local_210 - (long)local_218;
                              local_258 = (void *)0x0;
                              if (lVar42 < 0) {
LAB_007313e8:
                    /* WARNING: Subroutine does not return */
                                std::vector<signed_char,std::allocator<signed_char>>::
                                __throw_length_error_abi_nn220000_();
                              }
                              local_280 = (long *)(ulong)*(uint6 *)pHVar1;
                              pvVar30 = (void *)FUN_00f62c00(lVar42);
                              lVar51 = 0;
                              local_250 = (long)pvVar30 + lVar42;
                              local_260 = pvVar30;
                              do {
                                pPVar50 = pPVar27 + lVar51;
                                puVar5 = (undefined2 *)((long)pvVar30 + lVar51);
                                PVar12 = pPVar50[2];
                                *puVar5 = *(undefined2 *)pPVar50;
                                *(PresetInfo *)(puVar5 + 1) = PVar12;
                                if (((byte)pPVar50[8] & 1) == 0) {
                                  uVar54 = *(undefined8 *)(pPVar50 + 0x10);
                                  uVar37 = *(undefined8 *)(pPVar50 + 8);
                                  *(undefined8 *)(puVar5 + 0xc) = *(undefined8 *)(pPVar50 + 0x18);
                                  *(undefined8 *)(puVar5 + 8) = uVar54;
                                  *(undefined8 *)(puVar5 + 4) = uVar37;
                                }
                                else {
                                  std::string::__init_copy_ctor_external
                                            ((string *)(puVar5 + 4),*(char **)(pPVar50 + 0x18),
                                             *(ulong *)(pPVar50 + 0x10));
                                }
                                lVar51 = lVar51 + 0x20;
                              } while (pPVar27 + lVar51 != pPVar49);
                              local_258 = (void *)((long)pvVar30 + lVar51);
                              (**(code **)(*plVar25 + 0x40))(plVar25,local_280,0,2,&local_260);
                              pvVar18 = local_260;
                              pvVar30 = local_258;
                              if (local_260 != (void *)0x0) {
                                for (; pvVar18 != pvVar30; pvVar30 = (void *)((long)pvVar30 + -0x20)
                                    ) {
                                  if ((*(byte *)((long)pvVar30 + -0x18) & 1) != 0) {
                                    operator_delete(*(void **)((long)pvVar30 + -8),
                                                    *(ulong *)((long)pvVar30 + -0x18) &
                                                    0xfffffffffffffffe);
                                  }
                                }
                                local_258 = pvVar18;
                                operator_delete(local_260,local_250 - (long)local_260);
                              }
                            }
                            if (local_160 != (PresetInfo *)0x0) {
                              pPStack_158 = local_160;
                              operator_delete(local_160,(long)local_150 - (long)local_160);
                            }
                          }
                          pPVar49 = local_218;
                          pPVar27 = local_210;
                          if (local_218 != (PresetInfo *)0x0) {
                            for (; pPVar49 != pPVar27; pPVar27 = pPVar27 + -0x20) {
                              if (((byte)pPVar27[-0x18] & 1) != 0) {
                                operator_delete(*(void **)(pPVar27 + -8),
                                                *(ulong *)(pPVar27 + -0x18) & 0xfffffffffffffffe);
                              }
                            }
                            local_210 = pPVar49;
                            operator_delete(pPVar49,(long)local_208 - (long)pPVar49);
                          }
                          pPVar50 = local_c0;
                          pPVar27 = local_b8;
                          pPVar49 = pPStack_b0;
                          if (local_c0 != (PresetInfo *)0x0) {
                            for (; pPStack_b0 = pPVar49, pPVar50 != pPVar27;
                                pPVar27 = pPVar27 + -0x20) {
                              if (((byte)pPVar27[-0x18] & 1) != 0) {
                                operator_delete(*(void **)(pPVar27 + -8),
                                                *(ulong *)(pPVar27 + -0x18) & 0xfffffffffffffffe);
                              }
                              pPVar49 = pPStack_b0;
                            }
                            local_b8 = pPVar50;
LAB_00730c9c:
                            operator_delete(pPVar50,(long)pPVar49 - (long)pPVar50);
                          }
                        }
                        else {
                          if (local_190._1_1_ != 1) goto LAB_0072fcdc;
                          local_a0 = (code *)CONCAT44(local_a0._4_4_,0x5c5);
                          uStack_98 = "packages/modules/Bluetooth/system/bta/has/has_client.cc";
                          local_90 = (HasDevice *)0x113962;
                          local_160 = (PresetInfo *)0x0;
                          bluetooth::log_internal::vlog
                                    (3,"bluetooth",&local_a0,&DAT_0013f82c,0,&local_160);
                          local_218 = (PresetInfo *)0x0;
                          local_210 = (PresetInfo *)0x0;
                          local_208 = (PresetInfo *)0x0;
                          if (*(long *)(lVar52 + 0x60) == 0) {
                            local_280 = (long *)((ulong)local_280._4_4_ << 0x20);
                          }
                          else {
                            local_280 = (long *)((ulong)local_280._4_4_ << 0x20);
                            do {
                              lVar42 = *(long *)(lVar52 + 0x58);
                              pcStack_88 = (code *)0x0;
                              local_90 = (HasDevice *)0x0;
                              local_80 = 0;
                              uVar35 = *(uint *)(lVar42 + 0x10);
                              uStack_98 = (char *)0x0;
                              local_78 = 0;
                              uVar34 = uVar35 >> 8 & 0xff;
                              uVar41 = uVar35 & 0xff;
                              local_a0 = (code *)(ulong)uVar35;
                              if (*(char *)(lVar42 + 0x38) == '\x01') {
                                if ((*(byte *)(lVar42 + 0x18) & 1) == 0) {
                                  local_90 = *(HasDevice **)(lVar42 + 0x20);
                                  uStack_98 = *(char **)(lVar42 + 0x18);
                                  pcStack_88 = *(code **)(lVar42 + 0x28);
                                }
                                else {
                                  std::string::__init_copy_ctor_external
                                            ((string *)&uStack_98,*(char **)(lVar42 + 0x28),
                                             *(ulong *)(lVar42 + 0x20));
                                  uVar41 = (uint)(byte)local_a0;
                                  uVar34 = (uint)local_a0._1_1_;
                                }
                                local_78 = CONCAT71(local_78._1_7_,1);
                                local_80 = CONCAT62(local_80._2_6_,*(undefined2 *)(lVar42 + 0x30));
                                if ((uVar41 == 3) && (uVar34 == 1)) goto LAB_0072f9f0;
                                if (((ulong)uStack_98 & 1) == 0) break;
                                bVar20 = false;
LAB_0072f938:
                                operator_delete(pcStack_88,(ulong)uStack_98 & 0xfffffffffffffffe);
                                if (!bVar20) break;
                              }
                              else {
                                if ((uVar41 != 3) || (uVar34 != 1)) break;
LAB_0072f9f0:
                                local_140 = 0;
                                pPStack_158 = (PresetInfo *)0x0;
                                local_160 = (PresetInfo *)0x0;
                                local_148 = (char *)0x0;
                                local_150 = (PresetInfo *)0x0;
                                bluetooth::le_audio::has::HasDevice::GetPresetInfo(uVar22);
                                pPVar27 = local_210;
                                if ((local_140 & 1) != 0) {
                                  if (local_210 < local_208) {
                                    *(undefined2 *)local_210 = (undefined2)local_160;
                                    local_210[2] = local_160._2_1_;
                                    if (((ulong)pPStack_158 & 1) == 0) {
                                      *(PresetInfo **)(local_210 + 0x10) = local_150;
                                      *(PresetInfo **)(local_210 + 8) = pPStack_158;
                                      *(char **)(local_210 + 0x18) = local_148;
                                      local_210 = local_210 + 0x20;
                                    }
                                    else {
                                      std::string::__init_copy_ctor_external
                                                ((string *)(local_210 + 8),local_148,
                                                 (ulong)local_150);
                                      local_210 = pPVar27 + 0x20;
                                    }
                                  }
                                  else {
                                    local_210 = std::
                                                vector<bluetooth::has::PresetInfo,std::allocator<bluetooth::has::PresetInfo>>
                                                ::
                                                __emplace_back_slow_path<bluetooth::has::PresetInfo_const&>
                                                          ((
                                                  vector<bluetooth::has::PresetInfo,std::allocator<bluetooth::has::PresetInfo>>
                                                  *)&local_218,(PresetInfo *)&local_160);
                                  }
                                }
                                if (*(__tree_node_base **)p_Var3 != (__tree_node_base *)0x0) {
                                  p_Var39 = p_Var3;
                                  p_Var44 = *(__tree_node_base **)p_Var3;
LAB_0072fa9c:
                                  do {
                                    if ((byte)local_a0._3_1_ < (byte)p_Var44[0x39])
                                    goto LAB_0072fa90;
                                    if ((byte)local_a0._3_1_ <= (byte)p_Var44[0x39]) {
                                      p_Var43 = p_Var44;
                                      for (p_Var45 = *(__tree_node_base **)p_Var44;
                                          p_Var45 != (__tree_node_base *)0x0;
                                          p_Var45 = *(__tree_node_base **)(p_Var45 + lVar42)) {
                                        lVar42 = 8;
                                        if ((byte)local_a0._3_1_ <= (byte)p_Var45[0x39]) {
                                          lVar42 = 0;
                                          p_Var43 = p_Var45;
                                        }
                                      }
                                      for (p_Var44 = *(__tree_node_base **)(p_Var44 + 8);
                                          p_Var44 != (__tree_node_base *)0x0;
                                          p_Var44 = *(__tree_node_base **)(p_Var44 + lVar42)) {
                                        lVar42 = 0;
                                        p_Var45 = p_Var44;
                                        if ((byte)p_Var44[0x39] <= (byte)local_a0._3_1_) {
                                          lVar42 = 8;
                                          p_Var45 = p_Var39;
                                        }
                                        p_Var39 = p_Var45;
                                      }
                                      if (p_Var43 != p_Var39) {
                                        local_c0 = (PresetInfo *)0x0;
                                        local_b8 = (PresetInfo *)0x0;
                                        pPStack_b0 = (PresetInfo *)0x0;
                                        local_a8 = (char *)((ulong)CONCAT61((int6)((ulong)local_a8
                                                                                  >> 0x10),
                                                                            local_a0._3_1_) << 8);
                                        std::
                                        __tree<bluetooth::le_audio::has::HasPreset,bluetooth::le_audio::has::HasPreset::ComparatorDesc,std::allocator<bluetooth::le_audio::has::HasPreset>>
                                        ::__erase_unique<bluetooth::le_audio::has::HasPreset>
                                                  ((
                                                  __tree<bluetooth::le_audio::has::HasPreset,bluetooth::le_audio::has::HasPreset::ComparatorDesc,std::allocator<bluetooth::le_audio::has::HasPreset>>
                                                  *)(lVar52 + 0x30),(HasPreset *)&local_c0);
                                        if (((ulong)local_c0 & 1) != 0) {
                                          operator_delete(pPStack_b0,
                                                          (ulong)local_c0 & 0xfffffffffffffffe);
                                        }
                                        local_280 = (long *)CONCAT44(local_280._4_4_,1);
                                      }
                                      break;
                                    }
                                    p_Var43 = p_Var44 + 8;
                                    p_Var44 = *(__tree_node_base **)p_Var43;
                                  } while (*(__tree_node_base **)p_Var43 != (__tree_node_base *)0x0)
                                  ;
                                }
LAB_0072fb48:
                                local_118 = (code *)((ulong)local_118 & 0xffffffffffffff00);
                                local_f8 = local_f8 & 0xffffffffffffff00;
                                local_120 = (char *)CONCAT44(local_120._4_4_,(undefined4)local_a0);
                                if ((char)local_78 == '\x01') {
                                  if (((ulong)uStack_98 & 1) == 0) {
                                    pHStack_110 = local_90;
                                    local_118 = (code *)uStack_98;
                                    local_108 = pcStack_88;
                                  }
                                  else {
                                    std::string::__init_copy_ctor_external
                                              ((string *)&local_118,(char *)pcStack_88,
                                               (ulong)local_90);
                                  }
                                  local_100 = (void *)CONCAT62(local_100._2_6_,(undefined2)local_80)
                                  ;
                                  local_f8 = CONCAT71(local_f8._1_7_,1);
                                }
                                local_e8 = (code *)CONCAT44(local_e8._4_4_,1);
                                clock_gettime(0,atStack_e0);
                                local_130 = (HasDevice *)((ulong)local_130 & 0xfffffffffffffff0 | 2)
                                ;
                                bluetooth::le_audio::has::
                                CacheList<bluetooth::le_audio::has::HasJournalRecord,20ul>::Append
                                          ((CacheList<bluetooth::le_audio::has::HasJournalRecord,20ul>
                                            *)(lVar52 + 0x68),&local_130);
                                if ((int)local_e8 != -1) {
                                  (*(code *)(&
                                            PTR___dispatch_abi_nn220000_<std::__variant_detail::__dtor<std::__variant_detail::__traits<bluetooth::le_audio::has::HasCtpOp,bluetooth::le_audio::has::HasCtpNtf,unsigned_char>,(std::__variant_detail::_Trait)1>::__destroy[abi:nn220000]()::_lambda(auto:1&)_1_&&,std::__variant_detail::__base<(std::__variant_detail::_Trait)1,bluetooth::le_audio::has::HasCtpOp,bluetooth::le_audio::has::HasCtpNtf,unsigned_char>&>_00f9d270
                                            )[(ulong)local_e8 & 0xffffffff])(&local_c0,&local_120);
                                }
                                plVar26 = *(long **)(lVar52 + 0x58);
                                local_e8 = (code *)CONCAT44(local_e8._4_4_,0xffffffff);
                                plVar25 = (long *)plVar26[1];
                                *(long **)(*plVar26 + 8) = plVar25;
                                *plVar25 = *plVar26;
                                *(long *)(lVar52 + 0x60) = *(long *)(lVar52 + 0x60) + -1;
                                if (((char)plVar26[7] == '\x01') &&
                                   ((*(byte *)(plVar26 + 3) & 1) != 0)) {
                                  operator_delete((void *)plVar26[5],plVar26[3] & 0xfffffffffffffffe
                                                 );
                                }
                                operator_delete(plVar26,0x40);
                                if (((local_140 & 1) != 0) && (((ulong)pPStack_158 & 1) != 0)) {
                                  operator_delete(local_148,(ulong)pPStack_158 & 0xfffffffffffffffe)
                                  ;
                                }
                                if (((char)local_78 == '\x01') && (((ulong)uStack_98 & 1) != 0)) {
                                  bVar20 = true;
                                  goto LAB_0072f938;
                                }
                              }
                            } while (*(long *)(lVar52 + 0x60) != 0);
                          }
                          if (*(char *)(lVar52 + 0x1b) == '\0') {
                            local_a0 = (code *)0x0;
                            uStack_98 = (char *)0x0;
                            local_90 = (HasDevice *)0x0;
                            uVar28 = bluetooth::le_audio::has::HasDevice::SerializePresets
                                               (pHVar1,(vector *)&local_a0);
                            pcVar29 = local_a0;
                            if ((uVar28 & 1) != 0) {
                              local_160 = (PresetInfo *)0x0;
                              pPStack_158 = (PresetInfo *)0x0;
                              local_150 = (PresetInfo *)0x0;
                              sVar15 = (long)uStack_98 - (long)local_a0;
                              if (sVar15 != 0) {
                                if ((long)sVar15 < 0) goto LAB_007313ec;
                                local_160 = (PresetInfo *)FUN_00f62c00(sVar15);
                                pPVar27 = local_160 + sVar15;
                                local_150 = pPVar27;
                                memcpy(local_160,pcVar29,sVar15);
                                pPStack_158 = pPVar27;
                              }
                              btif_storage_set_leaudio_has_presets(pHVar1,&local_160);
                              if (local_160 != (PresetInfo *)0x0) {
                                pPStack_158 = local_160;
                                operator_delete(local_160,(long)local_150 - (long)local_160);
                              }
                            }
                            if (local_a0 != (code *)0x0) {
                              uStack_98 = (char *)local_a0;
                              operator_delete(local_a0,(long)local_90 - (long)local_a0);
                            }
                          }
                          pPVar49 = local_210;
                          pPVar27 = local_218;
                          if (((ulong)local_280 & 1) != 0) {
                            plVar25 = *(long **)(param_1 + 0x10);
                            uVar17 = *(uint6 *)pHVar1;
                            local_a0 = (code *)0x0;
                            uStack_98 = (char *)0x0;
                            lVar42 = (long)local_210 - (long)local_218;
                            local_90 = (HasDevice *)0x0;
                            if (lVar42 != 0) {
                              if (lVar42 < 0) goto LAB_007313e8;
                              pcVar29 = (code *)FUN_00f62c00(lVar42);
                              lVar51 = 0;
                              local_90 = (HasDevice *)(pcVar29 + lVar42);
                              local_a0 = pcVar29;
                              do {
                                pPVar50 = pPVar27 + lVar51;
                                pcVar4 = pcVar29 + lVar51;
                                PVar12 = pPVar50[2];
                                *(undefined2 *)pcVar4 = *(undefined2 *)pPVar50;
                                *(PresetInfo *)(pcVar4 + 2) = PVar12;
                                if (((byte)pPVar50[8] & 1) == 0) {
                                  uVar54 = *(undefined8 *)(pPVar50 + 0x10);
                                  uVar37 = *(undefined8 *)(pPVar50 + 8);
                                  *(undefined8 *)(pcVar4 + 0x18) = *(undefined8 *)(pPVar50 + 0x18);
                                  *(undefined8 *)(pcVar4 + 0x10) = uVar54;
                                  *(undefined8 *)(pcVar4 + 8) = uVar37;
                                }
                                else {
                                  std::string::__init_copy_ctor_external
                                            ((string *)(pcVar4 + 8),*(char **)(pPVar50 + 0x18),
                                             *(ulong *)(pPVar50 + 0x10));
                                }
                                lVar51 = lVar51 + 0x20;
                              } while (pPVar27 + lVar51 != pPVar49);
                              uStack_98 = (char *)(pcVar29 + lVar51);
                              local_280 = plVar25;
                            }
                            (**(code **)(*plVar25 + 0x40))(plVar25,(ulong)uVar17,0,2,&local_a0);
                            pcVar4 = local_a0;
                            pcVar29 = (code *)uStack_98;
                            if (local_a0 != (code *)0x0) {
                              for (; pcVar4 != pcVar29; pcVar29 = pcVar29 + -0x20) {
                                if (((byte)pcVar29[-0x18] & 1) != 0) {
                                  operator_delete(*(void **)(pcVar29 + -8),
                                                  *(ulong *)(pcVar29 + -0x18) & 0xfffffffffffffffe);
                                }
                              }
                              uStack_98 = (char *)pcVar4;
                              operator_delete(local_a0,(long)local_90 - (long)local_a0);
                            }
                          }
                          pPVar50 = local_218;
                          pPVar27 = local_210;
                          pPVar49 = local_208;
                          if (local_218 != (PresetInfo *)0x0) {
                            for (; local_208 = pPVar49, pPVar50 != pPVar27;
                                pPVar27 = pPVar27 + -0x20) {
                              if (((byte)pPVar27[-0x18] & 1) != 0) {
                                operator_delete(*(void **)(pPVar27 + -8),
                                                *(ulong *)(pPVar27 + -0x18) & 0xfffffffffffffffe);
                              }
                              pPVar49 = local_208;
                            }
                            local_210 = pPVar50;
                            goto LAB_00730c9c;
                          }
                        }
                      }
                      else {
                        if ((local_190._1_1_ != 2) && (local_190._1_1_ != 3)) {
LAB_0072fcdc:
                          local_a0 = (code *)CONCAT44(local_a0._4_4_,0x609);
                          pcVar32 = "Invalid notification: {}";
                          uVar37 = 0x18;
                          goto LAB_0072f868;
                        }
                        OnHasPresetAvailabilityChanged(param_1,pHVar1);
                      }
                    }
                    else {
                      local_a0 = (code *)CONCAT44(local_a0._4_4_,0x611);
                      pcVar32 = "Unsupported preset notification: {}";
                      uVar37 = 0x23;
LAB_0072f868:
                      local_90 = (HasDevice *)0x1e2854;
                      uStack_98 = "packages/modules/Bluetooth/system/bta/has/has_client.cc";
                      local_120 = &DAT_0000000f;
                      pcStack_128 = 
                      _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IN9bluetooth8le_audio3has9HasCtpNtfEEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESJ_SK_SM_
                      ;
                      local_150 = (PresetInfo *)&DAT_0000000f;
                      local_160 = (PresetInfo *)0x1;
                      pPStack_158 = (PresetInfo *)&local_130;
                      local_130 = (HasDevice *)&local_190;
                      bluetooth::log_internal::vlog
                                (6,"bluetooth",&local_a0,pcVar32,uVar37,&local_160);
                    }
                    if (((char)local_168 == '\x01') && (((ulong)pcStack_188 & 1) != 0)) {
                      operator_delete(pvStack_178,(ulong)pcStack_188 & 0xfffffffffffffffe);
                    }
                  } while (*(long *)(lVar52 + 0x60) != 0);
                }
                if (((char)local_1d8 == '\x01') && ((uStack_1f8 & 1) != 0)) {
                  operator_delete(pcStack_1e8,uStack_1f8 & 0xfffffffffffffffe);
                }
              }
              if ((((local_1a0 & 1) != 0) && ((char)local_1a8 == '\x01')) &&
                 (((ulong)pcStack_1c8 & 1) != 0)) {
                operator_delete(pcStack_1b8,(ulong)pcStack_1c8 & 0xfffffffffffffffe);
              }
            }
            else if (sVar14 == *(short *)(lVar52 + 0x20)) {
              OnHasActivePresetValue(param_1,pHVar1,1,0,sVar14,uVar33,param_3 + 0xc);
            }
            goto LAB_00730fcc;
          }
        }
        else {
          do {
            if (*(ushort *)(lVar52 + 0x16) == uVar23) goto LAB_0072e66c;
            lVar52 = *(long *)(lVar52 + 8);
          } while (lVar52 != lVar42);
        }
        local_1d0._0_4_ = 0x471;
        local_1c0 = "OnHasNotification";
LAB_0072e8f0:
        pcStack_1c8 = "packages/modules/Bluetooth/system/bta/has/has_client.cc";
        local_130 = (HasDevice *)(ulong)uVar23;
        uStack_98 = (char *)&local_130;
        pcStack_128 = (code *)0x0;
        local_120 = &DAT_00000006;
        local_a0 = (code *)0x1;
        local_90 = (HasDevice *)&DAT_00000006;
        bluetooth::log_internal::vlog
                  (5,"bluetooth",&local_1d0,"Skipping unknown device, conn_id=0x{:x}",0x27,&local_a0
                  );
        goto LAB_00730fcc;
      }
      lVar42 = *(long *)(param_1 + 0x20);
      param_1 = param_1 + 0x18;
      if (lVar42 == param_1) {
LAB_0072e580:
        if (lVar42 != param_1) {
          local_1d0._0_4_ = 0x86d;
          pcStack_1c8 = "packages/modules/Bluetooth/system/bta/has/has_client.cc";
          local_1c0 = "OnGattServiceDiscoveryDoneEvent";
          uStack_98 = (char *)&local_130;
          pcStack_128 = 
          _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IK10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESH_SI_SK_
          ;
          local_120 = &DAT_0000000f;
          local_a0 = (code *)0x1;
          local_90 = (HasDevice *)&DAT_0000000f;
          local_130 = param_3;
          bluetooth::log_internal::vlog(3,"bluetooth",&local_1d0,"address={}",10,&local_a0);
          if (*(char *)(lVar42 + 0x1b) == '\0') goto LAB_00730fcc;
          uVar23 = *(ushort *)(lVar42 + 0x16);
LAB_0072e6b8:
          BTA_GATTC_ServiceSearchRequest(uVar23);
          goto LAB_00730fcc;
        }
      }
      else {
        do {
          if (*(int *)param_3 == *(int *)(lVar42 + 0x10) &&
              *(short *)(param_3 + 4) == *(short *)(lVar42 + 0x14)) goto LAB_0072e580;
          lVar42 = *(long *)(lVar42 + 8);
        } while (lVar42 != param_1);
      }
      local_1d0._0_4_ = 0x869;
      local_1c0 = "OnGattServiceDiscoveryDoneEvent";
    }
    else {
      if (param_2 != 0xf) {
        if (param_2 != 0x11) goto LAB_00730fcc;
        pHVar1 = param_3 + 1;
        uVar28 = (**(code **)(PTR_PTR_00fabec8 + 0x90))(&PTR_PTR_00fabec8,pHVar1,2);
        local_1d0._0_4_ = 0x82e;
        uStack_98 = (char *)&local_130;
        pcStack_1c8 = "packages/modules/Bluetooth/system/bta/has/has_client.cc";
        local_1c0 = "OnLeEncryptionComplete";
        pcStack_128 = 
        _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IK10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESH_SI_SK_
        ;
        local_120 = &DAT_0000000f;
        local_a0 = (code *)0x1;
        local_90 = (HasDevice *)&DAT_0000000f;
        local_130 = pHVar1;
        bluetooth::log_internal::vlog(3,"bluetooth",&local_1d0,&DAT_0012915b,2,&local_a0);
        lVar42 = *(long *)(param_1 + 0x20);
        param_1 = param_1 + 0x18;
        local_130 = (HasDevice *)
                    CONCAT44(CONCAT22(local_130._6_2_,*(short *)(param_3 + 5)),*(int *)(param_3 + 1)
                            );
        if (lVar42 == param_1) {
LAB_0072e6a0:
          if (lVar42 != param_1) {
            if ((uVar28 & 1) != 0) {
              if (*(char *)(lVar42 + 0x1b) == '\0') {
                OnEncrypted(DAT_01014288,lVar42 + 0x10);
                goto LAB_00730fcc;
              }
              uVar23 = *(ushort *)(lVar42 + 0x16);
              goto LAB_0072e6b8;
            }
            uStack_98 = (char *)&local_130;
            local_1d0._0_4_ = 0x837;
            pcStack_1c8 = "packages/modules/Bluetooth/system/bta/has/has_client.cc";
            local_1c0 = "OnLeEncryptionComplete";
            pcVar32 = "Encryption failed for device {}";
            pcStack_128 = 
            _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IK10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESH_SI_SK_
            ;
            local_120 = &DAT_0000000f;
            puVar31 = &local_1d0;
            puVar36 = &local_a0;
            local_a0 = (code *)0x1;
            uVar37 = 0x1f;
            local_90 = (HasDevice *)&DAT_0000000f;
            local_130 = pHVar1;
LAB_0072ebdc:
            bluetooth::log_internal::vlog(6,"bluetooth",puVar31,pcVar32,uVar37,puVar36);
            BTA_GATTC_Close(*(ushort *)(lVar42 + 0x16));
            goto LAB_00730fcc;
          }
        }
        else {
          do {
            if (*(int *)(param_3 + 1) == *(int *)(lVar42 + 0x10) &&
                *(short *)(param_3 + 5) == *(short *)(lVar42 + 0x14)) goto LAB_0072e6a0;
            lVar42 = *(long *)(lVar42 + 8);
          } while (lVar42 != param_1);
        }
        local_1d0._0_4_ = 0x832;
        local_90 = (HasDevice *)&DAT_0000000f;
        pcVar32 = "Skipping unknown device{}";
        uVar37 = 0x19;
        local_1c0 = "OnLeEncryptionComplete";
        pcStack_128 = 
        _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IK10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESH_SI_SK_
        ;
        local_120 = &DAT_0000000f;
        local_130 = pHVar1;
        goto LAB_0072e980;
      }
      lVar52 = *(long *)(param_1 + 0x20);
      lVar42 = param_1 + 0x18;
      if (lVar52 == lVar42) {
LAB_0072e5f4:
        if (lVar52 != lVar42) {
          local_1d0._0_4_ = 0x862;
          pcStack_1c8 = "packages/modules/Bluetooth/system/bta/has/has_client.cc";
          local_1c0 = "OnGattServiceChangeEvent";
          uStack_98 = (char *)&local_130;
          pcStack_128 = 
          _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IK10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESH_SI_SK_
          ;
          local_120 = &DAT_0000000f;
          local_a0 = (code *)0x1;
          local_90 = (HasDevice *)&DAT_0000000f;
          local_130 = param_3;
          bluetooth::log_internal::vlog(4,"bluetooth",&local_1d0,&DAT_0012915b,2,&local_a0);
          ClearDeviceInformationAndStartSearch(param_1,lVar52 + 0x10,0);
          goto LAB_00730fcc;
        }
      }
      else {
        do {
          if (*(int *)param_3 == *(int *)(lVar52 + 0x10) &&
              *(short *)(param_3 + 4) == *(short *)(lVar52 + 0x14)) goto LAB_0072e5f4;
          lVar52 = *(long *)(lVar52 + 8);
        } while (lVar52 != lVar42);
      }
      local_1d0._0_4_ = 0x85f;
      local_1c0 = "OnGattServiceChangeEvent";
    }
    local_90 = (HasDevice *)&DAT_0000000f;
    pcStack_128 = 
    _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IK10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESH_SI_SK_
    ;
    local_120 = &DAT_0000000f;
    pcVar32 = "Skipping unknown device: {}";
    uVar37 = 0x1b;
    local_130 = param_3;
  }
LAB_0072e980:
  pcStack_1c8 = "packages/modules/Bluetooth/system/bta/has/has_client.cc";
  uStack_98 = (char *)&local_130;
  local_a0 = (code *)0x1;
  bluetooth::log_internal::vlog(5,"bluetooth",&local_1d0,pcVar32,uVar37,&local_a0);
LAB_00730fcc:
  if (*(long *)(lVar16 + 0x28) != local_70) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
LAB_007306a0:
  if (plVar48 == (long *)0x0) {
    do {
      plVar26 = (long *)plVar25[2];
      bVar20 = plVar25 == (long *)*plVar26;
      plVar25 = plVar26;
    } while (bVar20);
  }
  else {
    do {
      plVar26 = plVar48;
      plVar48 = (long *)plVar26[1];
    } while ((long *)plVar26[1] != (long *)0x0);
  }
  plVar25 = plVar26;
  pPVar27 = local_b8;
  if (plVar26 == *(long **)(param_1 + 0x48)) goto LAB_00730950;
  goto LAB_00730574;
LAB_0072fa90:
  p_Var43 = *(__tree_node_base **)p_Var44;
  p_Var39 = p_Var44;
  p_Var44 = p_Var43;
  if (p_Var43 == (__tree_node_base *)0x0) goto LAB_0072fb48;
  goto LAB_0072fa9c;
}


/* ==== bta_av_co_audio_close @ 00751738 size 584 :: ProcessClose */

/* bta_av_co_audio_close(unsigned char, RawAddress const&) */

void bta_av_co_audio_close(uchar param_1,RawAddress *param_2)

{
  ushort uVar1;
  long lVar2;
  recursive_mutex *this;
  RawAddress *pRVar3;
  RawAddress *pRVar4;
  long lVar5;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  undefined8 local_d0;
  RawAddress **ppRStack_c8;
  undefined8 local_c0;
  undefined4 local_b8;
  undefined4 uStack_b4;
  char *local_b0;
  char *pcStack_a8;
  RawAddress *local_a0;
  code *local_98;
  RawAddress *local_90;
  code *local_88;
  undefined8 uStack_80;
  long local_68;
  
  pRVar3 = (RawAddress *)(ulong)param_1;
  *in_x18 = unaff_x30;
  lVar2 = tpidr_el0;
  local_68 = *(long *)(lVar2 + 0x28);
  local_b8 = 0x27e;
  local_98 = 
  _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IK10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESH_SI_SK_
  ;
  local_b0 = "packages/modules/Bluetooth/system/btif/co/bta_av_co.cc";
  pcStack_a8 = "ProcessClose";
  local_88 = (code *)0x0;
  uStack_80 = 0xcf;
  local_d0 = 2;
  local_c0 = 0xcf;
  ppRStack_c8 = &local_a0;
  local_a0 = param_2;
  local_90 = pRVar3;
  bluetooth::log_internal::vlog
            (4,"bluetooth-a2dp",&local_b8,"peer {} bta_av_handle: 0x{:x}",0x1d,&local_d0);
  this = DAT_01014368;
  std::recursive_mutex::lock(DAT_01014368);
  pRVar4 = (RawAddress *)BtaAvCoPeerCache::FindPeerAndUpdate(DAT_01014368,pRVar3,param_2);
  if (pRVar4 == (RawAddress *)0x0) {
    local_b8 = 0x285;
    local_98 = (code *)0x0;
    local_b0 = "packages/modules/Bluetooth/system/btif/co/bta_av_co.cc";
    pcStack_a8 = "ProcessClose";
    local_88 = 
    _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IK10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESH_SI_SK_
    ;
    uStack_80 = 0x1e6;
    local_d0 = 2;
    local_c0 = 0x1e6;
    ppRStack_c8 = &local_a0;
    local_a0 = pRVar3;
    local_90 = param_2;
    bluetooth::log_internal::vlog
              (6,"bluetooth-a2dp",&local_b8,
               "could not find peer entry for bta_av_handle 0x{:x} peer {}",0x3a,&local_d0);
    goto LAB_0075193c;
  }
  uVar1 = *(ushort *)(pRVar4 + 0x41a);
  if (uVar1 == 0x110b) {
LAB_00751910:
    lVar5 = 0x18;
  }
  else {
    if (uVar1 != 0x110a) {
      _local_b8 = CONCAT44(uStack_b4,0x5de);
      local_b0 = "packages/modules/Bluetooth/system/btif/co/bta_av_co.cc";
      pcStack_a8 = "getStateFromPeer";
      ppRStack_c8 = &local_a0;
      local_98 = 
      _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IK10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESH_SI_SK_
      ;
      local_88 = (code *)0x0;
      uStack_80 = 0xcf;
      local_d0 = 2;
      local_c0 = 0xcf;
      local_a0 = pRVar4;
      local_90 = (RawAddress *)(ulong)uVar1;
      bluetooth::log_internal::vlog
                (5,"bluetooth-a2dp",&local_b8,
                 "Invalid bta av state for peer_address : {} with uuid as :{}",0x3b,&local_d0);
      local_a0 = (RawAddress *)CONCAT44(local_a0._4_4_,0x290);
      local_98 = (code *)0x1423d9;
      local_90 = (RawAddress *)0x12ba08;
      local_b8 = 0;
      uStack_b4 = 0;
      bluetooth::log_internal::vlog
                (5,"bluetooth-a2dp",&local_a0,"Invalid bta av state : Set bta_av_source_state_",0x2f
                 ,&local_b8);
      goto LAB_00751910;
    }
    lVar5 = 0x40;
  }
  if (*(RawAddress **)((long)&DAT_01014368 + lVar5) == pRVar4) {
    *(undefined8 *)((long)&DAT_01014368 + lVar5) = 0;
  }
  BtaAvCoPeer::Init(pRVar4,DAT_01014368 + 0x28);
LAB_0075193c:
  std::recursive_mutex::unlock(this);
  if (*(long *)(lVar2 + 0x28) == local_68) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== ContentProtectIsScmst @ 00755618 size 248 :: ContentProtectIsScmst */

/* ContentProtectIsScmst(unsigned char const*) */

void ContentProtectIsScmst(uchar *param_1)

{
  long lVar1;
  undefined8 uVar2;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  undefined8 local_68 [3];
  undefined4 local_50 [2];
  char *local_48;
  char *pcStack_40;
  long local_38;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_38 = *(long *)(lVar1 + 0x28);
  local_50[0] = 0x106;
  local_48 = "packages/modules/Bluetooth/system/btif/co/bta_av_co_peer.cc";
  pcStack_40 = "ContentProtectIsScmst";
  local_68[0] = 0;
  bluetooth::log_internal::vlog(3,"bluetooth-a2dp",local_50,&DAT_0013f82c,0,local_68);
  if ((*param_1 < 2) || (*(short *)(param_1 + 1) != 2)) {
    uVar2 = 0;
  }
  else {
    local_50[0] = 0x10d;
    local_48 = "packages/modules/Bluetooth/system/btif/co/bta_av_co_peer.cc";
    pcStack_40 = "ContentProtectIsScmst";
    local_68[0] = 0;
    bluetooth::log_internal::vlog(3,"bluetooth-a2dp",local_50,"SCMS-T found",0xc,local_68);
    uVar2 = 1;
  }
  if (*(long *)(lVar1 + 0x28) == local_38) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar2);
}


/* ==== AudioProtectHasScmst @ 00755710 size 428 :: AudioProtectHasScmst | ContentProtectIsScmst */

/* AudioProtectHasScmst(unsigned char, unsigned char const*) */

void AudioProtectHasScmst(uchar param_1,uchar *param_2)

{
  long lVar1;
  undefined8 uVar2;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  undefined8 local_98 [3];
  undefined4 local_80 [2];
  char *local_78;
  char *pcStack_70;
  long local_68;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_68 = *(long *)(lVar1 + 0x28);
  local_80[0] = 0x115;
  local_78 = "packages/modules/Bluetooth/system/btif/co/bta_av_co_peer.cc";
  pcStack_70 = "AudioProtectHasScmst";
  local_98[0] = 0;
  bluetooth::log_internal::vlog(3,"bluetooth-a2dp",local_80,&DAT_0013f82c,0,local_98);
  do {
    if (param_1 == '\0') {
      local_80[0] = 0x11d;
      local_78 = "packages/modules/Bluetooth/system/btif/co/bta_av_co_peer.cc";
      pcStack_70 = "AudioProtectHasScmst";
      local_98[0] = 0;
      bluetooth::log_internal::vlog(3,"bluetooth-a2dp",local_80,"SCMS-T not found",0x10,local_98);
      uVar2 = 0;
LAB_00755880:
      if (*(long *)(lVar1 + 0x28) == local_68) {
        return;
      }
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(uVar2);
    }
    local_80[0] = 0x106;
    local_78 = "packages/modules/Bluetooth/system/btif/co/bta_av_co_peer.cc";
    pcStack_70 = "ContentProtectIsScmst";
    local_98[0] = 0;
    bluetooth::log_internal::vlog(3,"bluetooth-a2dp",local_80,&DAT_0013f82c,0,local_98);
    if ((1 < (ulong)*param_2) && (*(short *)(param_2 + 1) == 2)) {
      local_80[0] = 0x10d;
      local_78 = "packages/modules/Bluetooth/system/btif/co/bta_av_co_peer.cc";
      pcStack_70 = "ContentProtectIsScmst";
      local_98[0] = 0;
      bluetooth::log_internal::vlog(3,"bluetooth-a2dp",local_80,"SCMS-T found",0xc,local_98);
      uVar2 = 1;
      goto LAB_00755880;
    }
    param_1 = param_1 + 0xff;
    param_2 = param_2 + (ulong)*param_2 + 1;
  } while( true );
}


/* ==== btif_av_need_dual_play_for_ssc @ 0079f704 size 368 :: btif_av_need_dual_play_for_ssc */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* btif_av_need_dual_play_for_ssc() */

void btif_av_need_dual_play_for_ssc(void)

{
  long lVar1;
  undefined8 *puVar2;
  bool bVar3;
  int iVar4;
  RawAddress *pRVar5;
  undefined8 uVar6;
  undefined8 *puVar7;
  undefined8 *in_x18;
  char cVar8;
  char cVar9;
  undefined8 *puVar10;
  undefined8 unaff_x30;
  undefined8 local_78 [3];
  undefined4 local_60 [2];
  char *local_58;
  char *pcStack_50;
  long local_48;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_48 = *(long *)(lVar1 + 0x28);
  if (DAT_0101f6a0 != &DAT_0101f6a8) {
    cVar9 = '\0';
    cVar8 = '\0';
    puVar10 = DAT_0101f6a0;
    do {
      pRVar5 = (RawAddress *)puVar10[5];
      if (((pRVar5 == (RawAddress *)0x0) || (*(long *)(pRVar5 + 0x20) == 0)) ||
         ((*(uint *)(*(long *)(pRVar5 + 0x20) + 0x10) & 0xfffffffe) != 2)) {
LAB_0079f79c:
        puVar2 = (undefined8 *)puVar10[1];
        if ((undefined8 *)puVar10[1] != (undefined8 *)0x0) goto LAB_0079f7a4;
LAB_0079f7c0:
        do {
          puVar7 = (undefined8 *)puVar10[2];
          bVar3 = puVar10 != (undefined8 *)*puVar7;
          puVar10 = puVar7;
        } while (bVar3);
      }
      else {
        iVar4 = bta_av_co_get_current_codec(pRVar5);
        if (iVar4 != 0x100) {
          if (iVar4 == 0x80) {
            cVar9 = cVar9 + '\x01';
          }
          goto LAB_0079f79c;
        }
        cVar8 = cVar8 + '\x01';
        puVar2 = (undefined8 *)puVar10[1];
        if ((undefined8 *)puVar10[1] == (undefined8 *)0x0) goto LAB_0079f7c0;
LAB_0079f7a4:
        do {
          puVar7 = puVar2;
          puVar2 = (undefined8 *)*puVar7;
        } while ((undefined8 *)*puVar7 != (undefined8 *)0x0);
      }
      puVar10 = puVar7;
    } while (puVar7 != &DAT_0101f6a8);
    if ((cVar9 == '\x02') || (cVar8 == '\x02')) {
      local_60[0] = 0x16e2;
      local_58 = "packages/modules/Bluetooth/system/btif/src/btif_av.cc";
      pcStack_50 = "btif_av_need_dual_play_for_ssc";
      local_78[0] = 0;
      bluetooth::log_internal::vlog(4,"bluetooth-a2dp",local_60,&DAT_0013f82c,0,local_78);
      uVar6 = 1;
      goto LAB_0079f840;
    }
  }
  uVar6 = 0;
LAB_0079f840:
  if (*(long *)(lVar1 + 0x28) != local_48) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(uVar6);
  }
  return;
}


/* ==== bta_av_sink_co_audio_close @ 007b5f88 size 396 :: ProcessClose */

/* bta_av_sink_co_audio_close(unsigned char, RawAddress const&) */

void bta_av_sink_co_audio_close(uchar param_1,RawAddress *param_2)

{
  long lVar1;
  RawAddress *pRVar2;
  long lVar3;
  A2dpCodecs *this;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  undefined8 local_c0;
  RawAddress **ppRStack_b8;
  undefined8 local_b0;
  undefined4 local_a8 [2];
  char *local_a0;
  char *pcStack_98;
  RawAddress *local_90;
  code *pcStack_88;
  RawAddress *local_80;
  code *local_78;
  undefined8 uStack_70;
  long local_58;
  
  pRVar2 = (RawAddress *)(ulong)param_1;
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_58 = *(long *)(lVar1 + 0x28);
  local_a8[0] = 0x461;
  pcStack_88 = 
  _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IK10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESH_SI_SK_
  ;
  local_a0 = "packages/modules/Bluetooth/system/btif/co/bta_av_sink_co_ss.cc";
  pcStack_98 = "ProcessClose";
  local_78 = (code *)0x0;
  uStack_70 = 0xcf;
  local_c0 = 2;
  local_b0 = 0xcf;
  ppRStack_b8 = &local_90;
  local_90 = param_2;
  local_80 = pRVar2;
  bluetooth::log_internal::vlog
            (3,"bluetooth",local_a8,"peer {} bta_av_sink_handle: 0x{:x}",0x22,&local_c0);
  lVar3 = BtaAvSinkCo::FindPeerAndUpdate(pRVar2,param_2);
  if (lVar3 == 0) {
    local_a8[0] = 0x466;
    pcStack_88 = (code *)0x0;
    local_a0 = "packages/modules/Bluetooth/system/btif/co/bta_av_sink_co_ss.cc";
    pcStack_98 = "ProcessClose";
    local_78 = 
    _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IK10RawAddressEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESH_SI_SK_
    ;
    uStack_70 = 0x1e6;
    local_c0 = 2;
    local_b0 = 0x1e6;
    ppRStack_b8 = &local_90;
    local_90 = pRVar2;
    local_80 = param_2;
    bluetooth::log_internal::vlog
              (6,"bluetooth",local_a8,
               "could not find peer entry for bta_av_sink_handle 0x{:x} peer {}",0x3f,&local_c0);
  }
  else {
    if (DAT_0101fea0 == lVar3) {
      DAT_0101fea0 = 0;
    }
    BtaAvSinkCoPeer::Reset(lVar3,*(undefined1 *)(lVar3 + 0x450));
    this = (A2dpCodecs *)FUN_00f62c00(0xd8);
    A2dpCodecs::A2dpCodecs(this,(vector *)&DAT_0101fa20);
    *(A2dpCodecs **)(lVar3 + 0x458) = this;
    A2dpCodecs::initSink(this);
    A2DP_InitDefaultCodecSbc((uchar *)(lVar3 + 0x430));
  }
  if (*(long *)(lVar1 + 0x28) == local_58) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== SetIsScoManagedByAudio @ 0080f600 size 288 :: SetIsScoManagedByAudio */

/* WARNING: Unknown calling convention: __rustcall */
/* bluetooth::headset::HeadsetInterface::SetIsScoManagedByAudio */

void __rustcall
bluetooth::headset::HeadsetInterface::SetIsScoManagedByAudio
          (undefined2 *param_1,undefined8 param_2,byte param_3)

{
  long lVar1;
  undefined2 uVar2;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  undefined8 local_68 [3];
  undefined4 local_50 [2];
  char *local_48;
  char *pcStack_40;
  long local_38;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_38 = *(long *)(lVar1 + 0x28);
  if (DAT_01020f10 == 0) {
    local_50[0] = 0x95b;
    local_48 = "packages/modules/Bluetooth/system/btif/src/btif_hf.cc";
    pcStack_40 = "SetIsScoManagedByAudio";
    local_68[0] = 0;
    log_internal::vlog(5,"bt_btif_hf",local_50,"BTHF not initialized",0x14,local_68);
    uVar2 = 2;
  }
  else {
    local_50[0] = 0x95b;
    local_48 = "packages/modules/Bluetooth/system/btif/src/btif_hf.cc";
    pcStack_40 = "SetIsScoManagedByAudio";
    local_68[0] = 0;
    log_internal::vlog(2,"bt_btif_hf",local_50,"BTHF ok",7,local_68);
    BTA_AgSetIsScoManagedByAudio((bool)(param_3 & 1));
    uVar2 = 0;
  }
  *param_1 = uVar2;
  param_1[1] = 0x80;
  *(code **)(param_1 + 4) = ::btif_status_text;
  if (*(long *)(lVar1 + 0x28) == local_38) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== setup_codec @ 00900d74 size 3408 :: No ssc_data_parcel | SscVendorGetTrackBitrateLimitation */

/* WARNING: Unknown calling convention: __rustcall */
/* bluetooth::audio::aidl::a2dp::setup_codec */

uint __rustcall bluetooth::audio::aidl::a2dp::setup_codec(ushort *param_1)

{
  int iVar1;
  long lVar2;
  char *pcVar3;
  char *__s2;
  char cVar4;
  byte bVar5;
  size_t __n;
  long lVar6;
  undefined *__src;
  uint uVar7;
  undefined4 uVar8;
  int iVar9;
  ulong uVar10;
  long lVar11;
  ulong uVar12;
  undefined8 uVar13;
  undefined8 *in_x18;
  __shared_weak_count *p_Var14;
  undefined8 *puVar15;
  uint uVar16;
  ushort *puVar17;
  char *pcVar18;
  ulong uVar19;
  void **ppvVar20;
  void *pvVar21;
  uint uVar22;
  undefined8 unaff_x30;
  undefined1 auVar23 [16];
  undefined8 local_200;
  undefined4 local_1f8;
  undefined8 local_1f0;
  undefined8 uStack_1e8;
  undefined8 local_1e0;
  undefined8 *puStack_1d8;
  undefined8 local_1d0;
  undefined8 local_1c8;
  char *local_1c0;
  char *local_1b8;
  undefined1 local_1b0 [4];
  char cStack_1ac;
  char cStack_1ab;
  undefined8 local_1a8;
  void **local_1a0;
  undefined4 local_198;
  undefined2 local_194;
  uint local_190;
  uint uStack_18c;
  uint uStack_188;
  uint uStack_184;
  undefined8 local_180;
  undefined8 local_178;
  undefined8 local_170;
  long lStack_168;
  undefined8 uStack_160;
  undefined8 uStack_158;
  undefined8 local_150;
  undefined8 uStack_148;
  undefined8 uStack_140;
  ulong local_138;
  undefined8 local_130;
  char *pcStack_128;
  char *pcStack_120;
  undefined8 local_118;
  void *local_110;
  long lStack_108;
  long local_100;
  undefined8 uStack_f8;
  undefined8 local_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 local_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 local_b8;
  undefined8 local_b0;
  char *local_a8;
  char *local_a0;
  undefined8 local_98;
  ulong local_90;
  undefined8 local_88;
  undefined8 uStack_80;
  long local_70;
  
  *in_x18 = unaff_x30;
  lVar6 = tpidr_el0;
  local_70 = *(long *)(lVar6 + 0x28);
  if (DAT_01033a00 == 0) {
    local_130 = CONCAT44(local_130._4_4_,0xfa);
    pcStack_128 = 
    "packages/modules/Bluetooth/system/audio_hal_interface/aidl/a2dp/a2dp_encoding_aidl.cc";
    pcStack_120 = "setup_codec";
    local_190 = 0;
    uStack_18c = 0;
    log_internal::vlog(6,"bluetooth-a2dp-aidl",&local_130,"BluetoothAudio HAL is not enabled",0x21,
                       &local_190);
    uVar7 = 0;
    goto LAB_00901a08;
  }
  if (DAT_010339f8 != (ProviderInfo *)0x0) {
    uVar10 = ProviderInfo::SupportsCodec(DAT_010339f8,*(undefined4 *)(param_1 + 0x10));
    if ((uVar10 & 1) != 0) {
      uStack_188 = 0;
      uStack_184 = 0;
      uStack_18c = 0;
      local_178 = (void *)0x0;
      local_180 = 0;
      lStack_168 = 0;
      local_170 = (void *)0x0;
      local_190 = (uint)*param_1;
      auVar23 = ProviderInfo::GetCodec(DAT_010339f8,*(undefined4 *)(param_1 + 0x10));
      if ((auVar23._8_8_ & 1) == 0) {
                    /* WARNING: Subroutine does not return */
        std::__throw_bad_optional_access_abi_nn220000_();
      }
      puVar17 = param_1 + 6;
      uVar13 = *auVar23._0_8_;
      lVar11 = (ulong)(byte)*puVar17 + 1;
      local_180 = CONCAT44(local_180._4_4_,*(undefined4 *)(auVar23._0_8_ + 1));
      lVar2 = 3;
      if (1 < *(uint *)(param_1 + 0x10)) {
        lVar2 = 9;
      }
      uStack_188 = (uint)uVar13;
      uStack_184 = (uint)((ulong)uVar13 >> 0x20);
      std::vector<unsigned_char,std::allocator<unsigned_char>>::
      __insert_with_size_abi_nn220000_<unsigned_char_const*,unsigned_char_const*>
                ((vector<unsigned_char,std::allocator<unsigned_char>> *)&local_178,0,
                 (byte *)((long)puVar17 + lVar2),(byte *)((long)puVar17 + lVar11),lVar11 - lVar2);
      if (DAT_01033a00 == 0) {
LAB_00900e90:
        local_130 = CONCAT44(local_130._4_4_,0x11e);
        pcStack_128 = 
        "packages/modules/Bluetooth/system/audio_hal_interface/aidl/a2dp/a2dp_encoding_aidl.cc";
        pcStack_120 = "setup_codec";
        local_b0 = (void **)0x0;
        log_internal::vlog(5,"bluetooth-a2dp-aidl",&local_130,
                           "Switching BluetoothAudio HAL to Hardware",0x28,&local_b0);
        end_session();
        DAT_01033a00 = DAT_01033a10;
      }
      else {
        p_Var14 = *(__shared_weak_count **)(DAT_01033a00 + 0x3c78);
        pcVar18 = *(char **)(DAT_01033a00 + 0x3c70);
        if (p_Var14 == (__shared_weak_count *)0x0) {
          cVar4 = *pcVar18;
        }
        else {
          __aarch64_ldadd8_relax(1,p_Var14 + 8);
          cVar4 = *pcVar18;
          lVar11 = __aarch64_ldadd8_acq_rel(0xffffffffffffffff,p_Var14 + 8);
          if (lVar11 == 0) {
            (**(code **)(*(long *)p_Var14 + 0x10))(p_Var14);
            std::__shared_weak_count::__release_weak(p_Var14);
          }
        }
        if (cVar4 != '\x02') goto LAB_00900e90;
      }
      pvVar21 = local_178;
      lVar11 = DAT_01033a00;
      pcStack_120 = (char *)CONCAT44(uStack_184,uStack_188);
      pcStack_128 = (char *)CONCAT44(uStack_18c,local_190);
      lStack_108 = 0;
      local_100 = 0;
      __n = (long)local_170 - (long)local_178;
      local_118 = CONCAT44(local_118._4_4_,(undefined4)local_180);
      local_110 = (void *)0x0;
      if (__n != 0) {
        if ((long)__n < 0) {
                    /* WARNING: Subroutine does not return */
          std::vector<signed_char,std::allocator<signed_char>>::__throw_length_error_abi_nn220000_()
          ;
        }
        local_110 = (void *)FUN_00f62c00(__n);
        lVar2 = (long)local_110 + __n;
        local_100 = lVar2;
        memcpy(local_110,pvVar21,__n);
        lStack_108 = lVar2;
      }
      local_b8 = CONCAT44(local_b8._4_4_,5);
      uVar7 = BluetoothAudioClientInterface::UpdateAudioConfig(lVar11,&local_130);
      if ((int)local_b8 != -1) {
        (*(code *)(&
                  PTR___dispatch_abi_nn220000_<std::__variant_detail::__dtor<std::__variant_detail::__traits<aidl::android::hardware::bluetooth::audio::PcmConfiguration,aidl::android::hardware::bluetooth::audio::CodecConfiguration,aidl::android::hardware::bluetooth::audio::LeAudioConfiguration,aidl::android::hardware::bluetooth::audio::LeAudioBroadcastConfiguration,aidl::android::hardware::bluetooth::audio::HfpConfiguration,aidl::android::hardware::bluetooth::audio::A2dpStreamConfiguration>,(std::__variant_detail::_Trait)1>::__destroy[abi:nn220000]()::_lambda(auto:1&)_1_&&,std::__variant_detail::__base<(std::__variant_detail::_Trait)1,aidl::android::hardware::bluetooth::audio::PcmConfiguration,aidl::android::hardware::bluetooth::audio::CodecConfiguration,aidl::android::hardware::bluetooth::audio::LeAudioConfiguration,aidl::android::hardware::bluetooth::audio::LeAudioBroadcastConfiguration,aidl::android::hardware::bluetooth::audio::HfpConfiguration,aidl::android::hardware::bluetooth::audio::A2dpStreamConfiguration>&>_00f9e488
                  )[local_b8 & 0xffffffff])(&local_b0,&pcStack_128);
      }
      if (local_178 != (void *)0x0) {
        local_170 = local_178;
        operator_delete(local_178,lStack_168 - (long)local_178);
      }
      goto LAB_00901a08;
    }
  }
  local_1f8 = 0;
  puVar15 = (undefined8 *)((ulong)&local_130 | 8);
  local_200 = 0;
  pcStack_128 = (char *)0x0;
  local_130 = 0;
  local_118 = 0;
  pcStack_120 = (char *)0x0;
  lStack_108 = 0;
  local_110 = (void *)0x0;
  uStack_f8 = 0;
  local_100 = 0;
  uStack_e8 = 0;
  local_f0 = 0;
  uStack_d8 = 0;
  uStack_e0 = 0;
  uStack_c8 = 0;
  local_d0 = 0;
  local_b8 = 0;
  uStack_c0 = 0;
  uStack_188 = 0;
  uStack_184 = 0;
  local_190 = 0;
  uStack_18c = 0;
  local_178 = (void *)0x0;
  local_180 = 0;
  lStack_168 = 0;
  local_170 = (void *)0x0;
  uStack_158 = 0;
  uStack_160 = 0;
  uStack_148 = 0;
  local_150 = 0;
  local_138 = 0;
  uStack_140 = 0;
  codec::HalConfigToA2dpConfig(param_1,&DAT_01033a20);
  uVar10 = codec::getHalCodecConfiguration(param_1,&local_190);
  if ((uVar10 & 1) == 0) {
    uVar10 = codec::getHalPcmConfiguration(param_1,&local_200);
    if ((uVar10 & 1) != 0) {
      if (DAT_01033a00 != 0) {
        p_Var14 = *(__shared_weak_count **)(DAT_01033a00 + 0x3c78);
        pcVar18 = *(char **)(DAT_01033a00 + 0x3c70);
        if (p_Var14 == (__shared_weak_count *)0x0) {
          cVar4 = *pcVar18;
        }
        else {
          __aarch64_ldadd8_relax(1,p_Var14 + 8);
          cVar4 = *pcVar18;
          lVar11 = __aarch64_ldadd8_acq_rel(0xffffffffffffffff,p_Var14 + 8);
          if (lVar11 == 0) {
            (**(code **)(*(long *)p_Var14 + 0x10))(p_Var14);
            std::__shared_weak_count::__release_weak(p_Var14);
          }
        }
        if (cVar4 == '\x02') {
          local_b0._4_4_ = (undefined4)((ulong)local_b0 >> 0x20);
          local_b0 = (void **)CONCAT44(local_b0._4_4_,0x140);
          local_a8 = 
          "packages/modules/Bluetooth/system/audio_hal_interface/aidl/a2dp/a2dp_encoding_aidl.cc";
          local_a0 = "setup_codec";
          local_1c8 = 0;
          log_internal::vlog(4,"bluetooth-a2dp-aidl",&local_b0,
                             "Switching BluetoothAudio HAL to Software",0x28,&local_1c8);
          DAT_01033a00 = DAT_01033a08;
        }
      }
      if ((int)local_b8 != -1) {
        (*(code *)(&
                  PTR___dispatch_abi_nn220000_<std::__variant_detail::__dtor<std::__variant_detail::__traits<aidl::android::hardware::bluetooth::audio::PcmConfiguration,aidl::android::hardware::bluetooth::audio::CodecConfiguration,aidl::android::hardware::bluetooth::audio::LeAudioConfiguration,aidl::android::hardware::bluetooth::audio::LeAudioBroadcastConfiguration,aidl::android::hardware::bluetooth::audio::HfpConfiguration,aidl::android::hardware::bluetooth::audio::A2dpStreamConfiguration>,(std::__variant_detail::_Trait)1>::__destroy[abi:nn220000]()::_lambda(auto:1&)_1_&&,std::__variant_detail::__base<(std::__variant_detail::_Trait)1,aidl::android::hardware::bluetooth::audio::PcmConfiguration,aidl::android::hardware::bluetooth::audio::CodecConfiguration,aidl::android::hardware::bluetooth::audio::LeAudioConfiguration,aidl::android::hardware::bluetooth::audio::LeAudioBroadcastConfiguration,aidl::android::hardware::bluetooth::audio::HfpConfiguration,aidl::android::hardware::bluetooth::audio::A2dpStreamConfiguration>&>_00f9e488
                  )[local_b8 & 0xffffffff])(&local_b0,puVar15);
      }
      lVar11 = DAT_01033a00;
      local_b8 = local_b8 & 0xffffffff00000000;
      *puVar15 = local_200;
      *(undefined4 *)(puVar15 + 1) = local_1f8;
      goto LAB_009019b4;
    }
    audio::a2dp::ahal_codec_configuration::ToString();
    local_1c8 = CONCAT44(local_1c8._4_4_,0x148);
    local_1c0 = 
    "packages/modules/Bluetooth/system/audio_hal_interface/aidl/a2dp/a2dp_encoding_aidl.cc";
    local_1b8 = "setup_codec";
    local_a8 = local_1a8;
    local_b0 = local_1a0;
    if ((_local_1b0 & 1) == 0) {
      local_a8 = (char *)(_local_1b0 >> 1 & 0x7f);
      local_b0 = (void **)(local_1b0 + 1);
    }
    local_a0 = (char *)0xd;
    puStack_1d8 = &local_b0;
    local_1e0 = 1;
    local_1d0 = 0xd;
    log_internal::vlog(6,"bluetooth-a2dp-aidl",&local_1c8,
                       "The codec configuration cannot be set for either software or hardware sessions:\n{}"
                       ,0x52,&local_1e0);
    if ((_local_1b0 & 1) != 0) {
      operator_delete(local_1a0,_local_1b0 & 0xfffffffffffffffe);
    }
    uVar7 = 0;
  }
  else {
    if (DAT_01033a00 == 0) {
LAB_00901038:
      local_b0 = (void **)CONCAT44(local_b0._4_4_,0x131);
      local_a8 = 
      "packages/modules/Bluetooth/system/audio_hal_interface/aidl/a2dp/a2dp_encoding_aidl.cc";
      local_a0 = "setup_codec";
      local_1c8 = 0;
      log_internal::vlog(4,"bluetooth-a2dp-aidl",&local_b0,
                         "Switching BluetoothAudio HAL to Hardware",0x28,&local_1c8);
      DAT_01033a00 = DAT_01033a10;
    }
    else {
      p_Var14 = *(__shared_weak_count **)(DAT_01033a00 + 0x3c78);
      pcVar18 = *(char **)(DAT_01033a00 + 0x3c70);
      if (p_Var14 == (__shared_weak_count *)0x0) {
        cVar4 = *pcVar18;
      }
      else {
        __aarch64_ldadd8_relax(1,p_Var14 + 8);
        cVar4 = *pcVar18;
        lVar11 = __aarch64_ldadd8_acq_rel(0xffffffffffffffff,p_Var14 + 8);
        if (lVar11 == 0) {
          (**(code **)(*(long *)p_Var14 + 0x10))(p_Var14);
          std::__shared_weak_count::__release_weak(p_Var14);
        }
      }
      if (cVar4 != '\x02') goto LAB_00901038;
    }
    local_194 = DAT_0101f6d4;
    local_198 = DAT_0101f6d0;
    if (*(int *)(param_1 + 0x10) == 8) {
      local_1c8 = CONCAT44(local_1c8._4_4_,0x35c);
      local_1c0 = 
      "packages/modules/Bluetooth/system/audio_hal_interface/aidl/a2dp/a2dp_encoding_aidl.cc";
      local_1b8 = "SscVendorGetTrackBitrateLimitation";
      local_b0 = (void **)(ulong)*(byte *)((long)param_1 + 0x15);
      puStack_1d8 = &local_b0;
      local_a8 = (char *)0x0;
      local_a0 = (char *)0x6;
      local_1e0 = 1;
      local_1d0 = 6;
      log_internal::vlog(4,"bluetooth-a2dp-aidl",&local_1c8,"0x{:x}",6,&local_1e0);
      bVar5 = *(byte *)((long)param_1 + 0x15);
      uStack_184 = CONCAT31(uStack_184._1_3_,(char)((bVar5 & 8) >> 3)) ^ 1;
      uVar13 = bta_av_co_get_current_codec((RawAddress *)&local_198);
      uStack_18c = codec::SscBitrateByBusyLevel(uVar13,DAT_01033a1c,(bVar5 & 8) == 0);
    }
    else if (*(int *)(param_1 + 0x10) == 0) {
      uStack_18c = codec::SbcBitrateByBusyLevel(&local_190,DAT_01033a1c);
    }
    local_1f0 = 0;
    uStack_1e8 = 0;
    BtaAvCo::GetPeerEncoderParameters(&DAT_01014360,&local_198,&local_1f0);
    uVar7 = BtaAvCo::GetSourceEncoderEffectiveFrameSize(&DAT_01014360,&local_198);
    uStack_188 = uVar7;
    if (local_1f0._6_2_ <= uVar7) {
      uStack_188 = (uint)local_1f0._6_2_;
    }
    if ((int)uVar7 < 1) {
      uStack_188 = (uint)local_1f0._6_2_;
    }
    if (*(int *)(param_1 + 0x10) == 0) {
      if ((int)local_138 == 0) {
        if (0x23 < (int)lStack_168) goto LAB_009013a0;
        uStack_188 = 0x297;
        goto LAB_009013b0;
      }
      goto LAB_00901a50;
    }
LAB_009013a0:
    if (0x3ed < uStack_188) {
      uStack_188 = 0x3ed;
    }
LAB_009013b0:
    ::aidl::android::hardware::bluetooth::audio::CodecConfiguration::toString();
    local_1c8 = CONCAT44(local_1c8._4_4_,0x38a);
    local_1c0 = 
    "packages/modules/Bluetooth/system/audio_hal_interface/aidl/a2dp/a2dp_encoding_aidl.cc";
    local_1b8 = "updateCodecConfigurationSS";
    local_a8 = local_1a8;
    local_b0 = local_1a0;
    if ((_local_1b0 & 1) == 0) {
      local_a8 = (char *)(_local_1b0 >> 1 & 0x7f);
      local_b0 = (void **)(local_1b0 + 1);
    }
    local_a0 = (char *)0xd;
    puStack_1d8 = &local_b0;
    local_1e0 = 1;
    local_1d0 = 0xd;
    log_internal::vlog(4,"bluetooth-a2dp-aidl",&local_1c8,"CodecConfiguration={}",0x15,&local_1e0);
    if ((_local_1b0 & 1) != 0) {
      operator_delete(local_1a0,_local_1b0 & 0xfffffffffffffffe);
    }
    iVar1 = DAT_010338a0;
    if (DAT_0101f898 == '\x01') {
      iVar9 = *(int *)(param_1 + 0x10);
      uVar19 = 0;
      uVar10 = 0x4000;
      if (iVar9 < 2) {
        if (iVar9 == 0) {
          if ((int)local_138 != 0) {
LAB_00901a50:
            pcVar18 = 
            "auto &aidl::android::hardware::bluetooth::audio::CodecConfiguration::CodecSpecific::get() [_tag = aidl::android::hardware::bluetooth::audio::CodecConfiguration::CodecSpecific::Tag::sbcConfig]"
            ;
LAB_00901a60:
                    /* WARNING: Subroutine does not return */
            __assert2("out/soong/.intermediates/hardware/interfaces/bluetooth/audio/aidl/android.hardware.bluetooth.audio-V6-ndk-source/gen/include/aidl/android/hardware/bluetooth/audio/CodecConfiguration.h"
                      ,0xa8,pcVar18,"bad access: a wrong tag");
          }
          ppvVar20 = (void **)((ulong)local_178 & 0xffffffff);
          pcVar18 = (char *)(long)(char)local_170;
          uVar19 = (ulong)local_178._4_1_;
          uVar7 = (uint)local_170._4_1_;
          uVar22 = (uint)(byte)lStack_168;
          uVar10 = btif_av_is_carkit_on_active_device();
          if (((uVar10 & 1) == 0) && (0x297 < (int)uStack_188)) {
            if ((int)local_138 != 0) goto LAB_00901a50;
            if ((0x23 < (int)lStack_168) && ((param_1[0x30] & 1) == 0)) {
              uVar12 = 0;
              uVar10 = 0;
              uVar16 = 1;
              goto LAB_009018f4;
            }
          }
          uVar16 = 0;
          uVar12 = 0;
          uVar10 = 0;
        }
        else {
          pcVar18 = (char *)0x0;
          ppvVar20 = (void **)0x0;
          uVar16 = 0;
          uVar22 = 0;
          uVar7 = 0;
          uVar12 = 0;
          if (iVar9 == 1) {
            if ((int)local_138 != 1) {
              pcVar18 = 
              "auto &aidl::android::hardware::bluetooth::audio::CodecConfiguration::CodecSpecific::get() [_tag = aidl::android::hardware::bluetooth::audio::CodecConfiguration::CodecSpecific::Tag::aacConfig]"
              ;
              goto LAB_00901a60;
            }
            ppvVar20 = (void **)((ulong)local_178 >> 0x20);
            pcVar18 = (char *)(long)local_170._2_1_;
            uVar22 = 0;
            uVar19 = (ulong)(char)local_170;
            uVar7 = 0;
            uVar12 = 0;
            uVar10 = 2;
            uVar16 = 1;
          }
        }
      }
      else if (iVar9 == 2) {
        if ((int)local_138 != 3) {
          pcVar18 = 
          "auto &aidl::android::hardware::bluetooth::audio::CodecConfiguration::CodecSpecific::get() [_tag = aidl::android::hardware::bluetooth::audio::CodecConfiguration::CodecSpecific::Tag::aptxConfig]"
          ;
          goto LAB_00901a60;
        }
        ppvVar20 = (void **)((ulong)local_178 & 0xffffffff);
        pcVar18 = (char *)(long)(char)local_178._5_1_;
        uVar16 = 0;
        uVar19 = (ulong)local_178._4_1_;
        uVar22 = 0;
        uVar7 = 0;
        uVar12 = 0;
        uVar10 = 8;
      }
      else if (iVar9 == 4) {
        if ((int)local_138 != 2) {
          pcVar18 = 
          "auto &aidl::android::hardware::bluetooth::audio::CodecConfiguration::CodecSpecific::get() [_tag = aidl::android::hardware::bluetooth::audio::CodecConfiguration::CodecSpecific::Tag::ldacConfig]"
          ;
          goto LAB_00901a60;
        }
        ppvVar20 = (void **)((ulong)local_178 & 0xffffffff);
        uVar19 = (ulong)local_178._4_1_;
        pcVar18 = (char *)0x0;
        uVar12 = (ulong)local_178._5_1_;
        uVar22 = 0;
        uVar7 = 0;
        uVar10 = 0x40;
        uVar16 = 1;
      }
      else {
        pcVar18 = (char *)0x0;
        ppvVar20 = (void **)0x0;
        uVar16 = 0;
        uVar22 = 0;
        uVar7 = 0;
        uVar12 = 0;
        if (iVar9 == 8) {
          if ((int)local_138 != 6) {
            pcVar18 = 
            "auto &aidl::android::hardware::bluetooth::audio::CodecConfiguration::CodecSpecific::get() [_tag = aidl::android::hardware::bluetooth::audio::CodecConfiguration::CodecSpecific::Tag::vendorConfig]"
            ;
            goto LAB_00901a60;
          }
          uVar19 = (ulong)local_178 & 0xffffffff;
          uVar10 = (ulong)local_178 >> 0x20;
          uVar13 = AParcel_create();
          lVar11 = lStack_168;
          uVar8 = AParcel_getDataSize(lStack_168);
          AParcel_appendFrom(lVar11,uVar13,0,uVar8);
          local_1c8 = CONCAT44(local_1c8._4_4_,0x3b9);
          puStack_1d8 = &local_b0;
          local_1c0 = 
          "packages/modules/Bluetooth/system/audio_hal_interface/aidl/a2dp/a2dp_encoding_aidl.cc";
          local_1b8 = "updateCodecConfigurationSS";
          local_a8 = (char *)0x0;
          local_98 = 0;
          local_90 = 99;
          local_1e0 = 2;
          local_1d0 = 99;
          local_b0 = (void **)uVar19;
          local_a0 = (char *)(uVar10 & 0xffff);
          log_internal::vlog(5,"bluetooth-a2dp-aidl",&local_1c8,"vid {} cid {}",0xd,&local_1e0);
          __src = PTR_s_android_hardware_bluetooth_audio_00fab9a8;
          _local_1b0 = 0;
          local_1a8 = (char *)0x0;
          pcVar18 = (char *)strlen(PTR_s_android_hardware_bluetooth_audio_00fab9a8);
          if ((char *)0xfffffffffffffff6 < pcVar18) {
                    /* WARNING: Subroutine does not return */
            std::string::__throw_length_error_abi_nn220000_();
          }
          local_b0 = (void **)0x0;
          local_a8 = (char *)0x0;
          local_a0 = (void *)0x0;
          if (pcVar18 < (char *)0x17) {
            pvVar21 = (void *)((ulong)&local_b0 | 1);
            local_b0 = (void **)(ulong)(byte)((int)pcVar18 << 1);
          }
          else {
            uVar10 = 0x1a;
            if (((ulong)pcVar18 | 7) != 0x17) {
              uVar10 = ((ulong)pcVar18 | 7) + 1;
            }
            pvVar21 = (void *)FUN_00f62c00(uVar10);
            local_b0 = (void **)(uVar10 | 1);
            local_a8 = pcVar18;
            local_a0 = pvVar21;
          }
          memmove(pvVar21,__src,(size_t)pcVar18);
          *(char *)((long)pvVar21 + (long)pcVar18) = '\0';
          AParcel_setDataPosition(uVar13,0);
          iVar9 = AParcel_getDataSize(uVar13);
          if (iVar9 != 0) {
            local_1c8 = 0;
            local_1c0 = (char *)0x0;
            local_1b8 = (char *)0x0;
            iVar9 = AParcel_readString(uVar13,&local_1c8,ndk::AParcel_stdStringAllocator);
            if (iVar9 == 0) {
              pcVar18 = (char *)((ulong)local_b0 >> 1 & 0x7f);
              if (((ulong)local_b0 & 1) != 0) {
                pcVar18 = local_a8;
              }
              pcVar3 = (char *)(local_1c8 >> 1 & 0x7f);
              if ((local_1c8 & 1) != 0) {
                pcVar3 = local_1c0;
              }
              if (pcVar18 == pcVar3) {
                pcVar3 = local_a0;
                if (((ulong)local_b0 & 1) == 0) {
                  pcVar3 = (char *)((long)&local_b0 + 1);
                }
                __s2 = local_1b8;
                if ((local_1c8 & 1) == 0) {
                  __s2 = (char *)((long)&local_1c8 + 1);
                }
                iVar9 = memcmp(pcVar3,__s2,(size_t)pcVar18);
                if (iVar9 == 0) {
                  _local_1b0 = 0;
                  local_1a8 = (char *)CONCAT35((int3)((ulong)local_1a8 >> 0x28),0x100000000);
                  iVar9 = ::aidl::android::hardware::bluetooth::audio::PcmConfiguration::
                          readFromParcel(local_1b0,uVar13);
                  if ((iVar9 != 0) && (((ulong)local_1a8 & 0x100000000) != 0)) {
                    local_1a8._0_5_ = (uint5)(uint)local_1a8;
                  }
                }
              }
            }
            if ((local_1c8 & 1) != 0) {
              operator_delete(local_1b8,local_1c8 & 0xfffffffffffffffe);
            }
          }
          if (((ulong)local_b0 & 1) != 0) {
            operator_delete(local_a0,(ulong)local_b0 & 0xfffffffffffffffe);
          }
          if (local_1a8._4_1_ == '\x01') {
            ppvVar20 = (void **)(_local_1b0 & 0xffffffff);
            pcVar18 = (char *)(long)cStack_1ab;
            uVar19 = (ulong)cStack_1ac;
            local_1c8 = CONCAT44(local_1c8._4_4_,0x3c2);
            puStack_1d8 = &local_b0;
            local_1c0 = 
            "packages/modules/Bluetooth/system/audio_hal_interface/aidl/a2dp/a2dp_encoding_aidl.cc";
            local_1b8 = "updateCodecConfigurationSS";
            local_a8 = (char *)0x0;
            local_98 = 0;
            local_88 = 0;
            uStack_80 = 0x18c6;
            local_1e0 = 3;
            local_1d0 = 0x18c6;
            local_b0 = ppvVar20;
            local_a0 = pcVar18;
            local_90 = uVar19;
            log_internal::vlog(5,"bluetooth-a2dp-aidl",&local_1c8,
                               "sampleRate {} bitsPerSample {} channelMode {}",0x2d,&local_1e0);
          }
          else {
            local_b0 = (void **)CONCAT44(local_b0._4_4_,0x3c4);
            local_a8 = 
            "packages/modules/Bluetooth/system/audio_hal_interface/aidl/a2dp/a2dp_encoding_aidl.cc";
            local_a0 = "updateCodecConfigurationSS";
            local_1c8 = 0;
            log_internal::vlog(6,"bluetooth-a2dp-aidl",&local_b0,"No ssc_data_parcel",0x12,
                               &local_1c8);
            uVar19 = 0;
            pcVar18 = (char *)0x0;
            ppvVar20 = (void **)0x0;
          }
          uVar7 = bta_av_co_get_current_codec((RawAddress *)&local_198);
          uVar10 = (ulong)uVar7;
          uVar16 = (uint)(uVar7 != 0x200);
          AParcel_delete(uVar13);
          uVar22 = 0;
          uVar7 = 0;
          uVar12 = 0;
        }
      }
LAB_009018f4:
      if (iVar1 != 2) {
        iVar1 = 0;
      }
      btif_av_big_data_report
                ("{\"OMCC\":\"01%08x%08x%08x%08x%08x%08x%02x%02x%02x%02x%02x%02x\"}",uVar10,ppvVar20
                 ,(ulong)pcVar18 & 0xffffffff,uVar19 & 0xffffffff,(ulong)uStack_18c,
                 (ulong)uStack_188,uVar12,uVar7,uVar22,0,iVar1,uVar16);
    }
    if ((int)local_b8 != -1) {
      (*(code *)(&
                PTR___dispatch_abi_nn220000_<std::__variant_detail::__dtor<std::__variant_detail::__traits<aidl::android::hardware::bluetooth::audio::PcmConfiguration,aidl::android::hardware::bluetooth::audio::CodecConfiguration,aidl::android::hardware::bluetooth::audio::LeAudioConfiguration,aidl::android::hardware::bluetooth::audio::LeAudioBroadcastConfiguration,aidl::android::hardware::bluetooth::audio::HfpConfiguration,aidl::android::hardware::bluetooth::audio::A2dpStreamConfiguration>,(std::__variant_detail::_Trait)1>::__destroy[abi:nn220000]()::_lambda(auto:1&)_1_&&,std::__variant_detail::__base<(std::__variant_detail::_Trait)1,aidl::android::hardware::bluetooth::audio::PcmConfiguration,aidl::android::hardware::bluetooth::audio::CodecConfiguration,aidl::android::hardware::bluetooth::audio::LeAudioConfiguration,aidl::android::hardware::bluetooth::audio::LeAudioBroadcastConfiguration,aidl::android::hardware::bluetooth::audio::HfpConfiguration,aidl::android::hardware::bluetooth::audio::A2dpStreamConfiguration>&>_00f9e488
                )[local_b8 & 0xffffffff])(&local_b0,puVar15);
    }
    iVar1 = (int)local_138;
    local_110 = (void *)((ulong)local_110 & 0xffffffffffffff00);
    *puVar15 = CONCAT44(uStack_18c,local_190);
    *(ulong *)((long)puVar15 + 5) =
         CONCAT17((undefined1)uStack_184,CONCAT43(uStack_188,uStack_18c._1_3_));
    local_b8._0_4_ = 0xffffffff;
    local_d0 = CONCAT44(local_d0._4_4_,0xffffffff);
    if ((int)local_138 != -1) {
      local_b0 = &local_110;
      (*(code *)(&
                PTR___dispatch_abi_nn220000_<std::__variant_detail::__ctor<std::__variant_detail::__traits<aidl::android::hardware::bluetooth::audio::SbcConfiguration,aidl::android::hardware::bluetooth::audio::AacConfiguration,aidl::android::hardware::bluetooth::audio::LdacConfiguration,aidl::android::hardware::bluetooth::audio::AptxConfiguration,aidl::android::hardware::bluetooth::audio::AptxAdaptiveConfiguration,aidl::android::hardware::bluetooth::audio::Lc3Configuration,aidl::android::hardware::bluetooth::audio::CodecConfiguration::VendorConfiguration,std::optional<aidl::android::hardware::bluetooth::audio::OpusConfiguration>>>::__generic_construct[abi:nn220000]<std::__variant_detail::__copy_constructor<std::__variant_detail::__traits<aidl::android::hardware::bluetooth::audio::SbcConfiguration,aidl::android::hardware::bluetooth::audio::AacConfiguration,aidl::android::hardware::bluetooth::audio::LdacConfiguration,aidl::android::hardware::bluetooth::audio::AptxConfiguration,aidl::android::hardware::bluet___dorConfiguration,std::optional<aidl::android::hardware::bluetooth::audio::OpusConfiguration>>const&>_00f9e550
                )[local_138 & 0xffffffff])(&local_b0,&local_178);
      local_d0 = CONCAT44(local_d0._4_4_,iVar1);
    }
    local_b8 = CONCAT44(local_b8._4_4_,1);
    lVar11 = DAT_01033a00;
LAB_009019b4:
    uVar7 = BluetoothAudioClientInterface::UpdateAudioConfig(lVar11,&local_130);
  }
  if ((int)local_138 != -1) {
    (*(code *)(&
              PTR___dispatch_abi_nn220000_<std::__variant_detail::__dtor<std::__variant_detail::__traits<aidl::android::hardware::bluetooth::audio::SbcConfiguration,aidl::android::hardware::bluetooth::audio::AacConfiguration,aidl::android::hardware::bluetooth::audio::LdacConfiguration,aidl::android::hardware::bluetooth::audio::AptxConfiguration,aidl::android::hardware::bluetooth::audio::AptxAdaptiveConfiguration,aidl::android::hardware::bluetooth::audio::Lc3Configuration,aidl::android::hardware::bluetooth::audio::CodecConfiguration::VendorConfiguration,std::optional<aidl::android::hardware::bluetooth::audio::OpusConfiguration>>,(std::__variant_detail::_Trait)1>::__destroy[abi:nn220000]()::_lambda(auto:1&)_1_&&,std::__variant_detail::__base<(std::__variant_detail::_Trait)1,aidl::android::hardware::bluetooth::audio::SbcConfiguration,aidl::android::hardware::bluetooth::audio::AacConfiguration,aidl::android::hardware::bluetooth::audio::LdacConfiguration,aidl::android::hardware::bluetooth::audio::AptxConfiguration,aidl::android::hardware::bluetooth::audio::AptxAdaptiveConfiguration,aidl::android::hardware::bluetooth::audio::Lc3Configuration,aidl::android::hardware::bluetooth::audio::CodecConfiguration::VendorConfiguration,std::optional<aidl::android::hardware::bluetooth::audio::OpusConfiguration>>&>_00f9e4f0
              )[local_138 & 0xffffffff])(&local_b0,&local_178);
  }
  if ((int)local_b8 != -1) {
    (*(code *)(&
              PTR___dispatch_abi_nn220000_<std::__variant_detail::__dtor<std::__variant_detail::__traits<aidl::android::hardware::bluetooth::audio::PcmConfiguration,aidl::android::hardware::bluetooth::audio::CodecConfiguration,aidl::android::hardware::bluetooth::audio::LeAudioConfiguration,aidl::android::hardware::bluetooth::audio::LeAudioBroadcastConfiguration,aidl::android::hardware::bluetooth::audio::HfpConfiguration,aidl::android::hardware::bluetooth::audio::A2dpStreamConfiguration>,(std::__variant_detail::_Trait)1>::__destroy[abi:nn220000]()::_lambda(auto:1&)_1_&&,std::__variant_detail::__base<(std::__variant_detail::_Trait)1,aidl::android::hardware::bluetooth::audio::PcmConfiguration,aidl::android::hardware::bluetooth::audio::CodecConfiguration,aidl::android::hardware::bluetooth::audio::LeAudioConfiguration,aidl::android::hardware::bluetooth::audio::LeAudioBroadcastConfiguration,aidl::android::hardware::bluetooth::audio::HfpConfiguration,aidl::android::hardware::bluetooth::audio::A2dpStreamConfiguration>&>_00f9e488
              )[local_b8 & 0xffffffff])(&local_190,puVar15);
  }
LAB_00901a08:
  if (*(long *)(lVar6 + 0x28) == local_70) {
    return uVar7 & 1;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== toString @ 00904844 size 1176 :: , isScmstEnabled:  */

/* aidl::android::hardware::bluetooth::audio::CodecConfiguration::toString() const */

void aidl::android::hardware::bluetooth::audio::CodecConfiguration::toString(void)

{
  char *pcVar1;
  long lVar2;
  bool bVar3;
  internal *in_x0;
  ostream *poVar4;
  CodecType *extraout_x1;
  void *__src;
  ulong *in_x8;
  ulong uVar5;
  long *plVar6;
  undefined8 *in_x18;
  undefined1 *__dest;
  size_t sVar7;
  undefined8 unaff_x30;
  byte local_190;
  undefined7 uStack_18f;
  ulong local_188;
  char *local_180;
  undefined **local_178;
  undefined **local_170;
  undefined8 uStack_168;
  long local_160 [8];
  void *local_120;
  ulong local_118;
  undefined8 local_110;
  undefined **ppuStack_108;
  undefined8 local_100;
  undefined8 uStack_f8;
  undefined8 local_f0;
  undefined8 uStack_e8;
  undefined8 local_e0;
  undefined8 uStack_d8;
  undefined8 local_d0;
  undefined8 uStack_c8;
  undefined8 local_c0;
  undefined8 uStack_b8;
  undefined8 local_b0;
  undefined8 uStack_a8;
  undefined8 local_a0;
  undefined8 uStack_98;
  undefined8 local_90;
  undefined8 uStack_88;
  undefined8 local_80;
  undefined8 uStack_78;
  long local_70;
  
  *in_x18 = unaff_x30;
  lVar2 = tpidr_el0;
  local_70 = *(long *)(lVar2 + 0x28);
  local_110 = 0;
  uStack_78 = 0;
  local_80 = 0;
  uStack_88 = 0;
  local_90 = 0;
  uStack_98 = 0;
  local_a0 = 0;
  uStack_a8 = 0;
  local_b0 = 0;
  uStack_b8 = 0;
  local_c0 = 0;
  uStack_c8 = 0;
  local_d0 = 0;
  uStack_d8 = 0;
  local_e0 = 0;
  uStack_e8 = 0;
  local_f0 = 0;
  uStack_f8 = 0;
  local_100 = 0;
  local_160[7] = 0;
  local_160[6] = 0;
  local_118 = 0;
  local_120 = (void *)0x0;
  local_160[5] = 0;
  local_160[4] = 0;
  local_160[1] = 0;
  local_160[0] = 0;
  local_160[3] = 0;
  local_160[2] = 0;
  uStack_168 = 0;
  local_170 = (undefined **)0x0;
  local_178 = &PTR__ostream_00f68c08;
  ppuStack_108 = &PTR__ostream_00f68c30;
  std::ios_base::init((ios_base *)&ppuStack_108,&local_170);
  local_80 = 0;
                    /* WARNING: Ignoring partial resolution of indirect */
  uStack_78._0_4_ = 0xffffffff;
  local_178 = &PTR__ostringstream_00f68b98;
  local_170 = &PTR__streambuf_00f68750;
  ppuStack_108 = &PTR__ostringstream_00f68bc0;
  std::locale::locale((locale *)&uStack_168);
  local_160[5] = 0;
  local_160[4] = 0;
  local_160[1] = 0;
  local_160[0] = 0;
  local_160[3] = 0;
  local_160[2] = 0;
  local_160[7] = 0;
  local_160[6] = 0;
  local_118 = 0;
  local_120 = (void *)0x0;
  local_170 = &PTR__stringbuf_00f687d0;
  local_110 = CONCAT44(local_110._4_4_,0x10);
  std::stringbuf::__init_buf_ptrs_abi_nn220000_((stringbuf *)&local_170);
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
            ((ostream *)&local_178,"CodecConfiguration{",0x13);
  poVar4 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                     ((ostream *)&local_178,"codecType: ",0xb);
  ::android::internal::ToString<aidl::android::hardware::bluetooth::audio::CodecType>
            (in_x0,extraout_x1);
  uVar5 = local_188;
  pcVar1 = local_180;
  if ((local_190 & 1) == 0) {
    uVar5 = (ulong)(local_190 >> 1);
    pcVar1 = (char *)&uStack_18f;
  }
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>(poVar4,pcVar1,uVar5);
  if ((local_190 & 1) != 0) {
    operator_delete(local_180,CONCAT71(uStack_18f,local_190) & 0xfffffffffffffffe);
  }
  poVar4 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                     ((ostream *)&local_178,", encodedAudioBitrate: ",0x17);
  std::to_string(*(int *)(in_x0 + 4));
  uVar5 = local_188;
  pcVar1 = local_180;
  if ((local_190 & 1) == 0) {
    uVar5 = (ulong)(local_190 >> 1);
    pcVar1 = (char *)&uStack_18f;
  }
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>(poVar4,pcVar1,uVar5);
  if ((local_190 & 1) != 0) {
    operator_delete(local_180,CONCAT71(uStack_18f,local_190) & 0xfffffffffffffffe);
  }
  poVar4 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                     ((ostream *)&local_178,", peerMtu: ",0xb);
  std::to_string(*(int *)(in_x0 + 8));
  uVar5 = local_188;
  pcVar1 = local_180;
  if ((local_190 & 1) == 0) {
    uVar5 = (ulong)(local_190 >> 1);
    pcVar1 = (char *)&uStack_18f;
  }
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>(poVar4,pcVar1,uVar5);
  if ((local_190 & 1) != 0) {
    operator_delete(local_180,CONCAT71(uStack_18f,local_190) & 0xfffffffffffffffe);
  }
  poVar4 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                     ((ostream *)&local_178,", isScmstEnabled: ",0x12);
  bVar3 = in_x0[0xc] == (internal)0x0;
  sVar7 = 4;
  if (bVar3) {
    sVar7 = 5;
  }
  local_190 = (byte)((int)sVar7 << 1);
  pcVar1 = "true";
  if (bVar3) {
    pcVar1 = "f";
  }
  uVar5 = 5;
  if (bVar3) {
    uVar5 = 6;
  }
  memcpy((void *)((ulong)&local_190 | 1),pcVar1,sVar7);
  *(undefined1 *)((ulong)&local_190 | uVar5) = 0;
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
            (poVar4,(char *)((ulong)&local_190 | 1),sVar7);
  if ((local_190 & 1) != 0) {
    operator_delete(local_180,CONCAT71(uStack_18f,local_190) & 0xfffffffffffffffe);
  }
  poVar4 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                     ((ostream *)&local_178,", config: ",10);
  CodecSpecific::toString();
  pcVar1 = local_180;
  if ((local_190 & 1) == 0) {
    local_188 = (ulong)(local_190 >> 1);
    pcVar1 = (char *)&uStack_18f;
  }
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>(poVar4,pcVar1,local_188);
  if ((local_190 & 1) != 0) {
    operator_delete(local_180,CONCAT71(uStack_18f,local_190) & 0xfffffffffffffffe);
  }
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
            ((ostream *)&local_178,"}",1);
  if (((uint)local_110 >> 4 & 1) == 0) {
    if (((uint)local_110 >> 3 & 1) != 0) {
      plVar6 = local_160;
      uVar5 = local_160[2];
      goto LAB_00904bd4;
    }
    __src = (void *)0x0;
    sVar7 = 0;
  }
  else {
    if (local_118 < (ulong)local_160[4]) {
      local_118 = local_160[4];
    }
    plVar6 = local_160 + 3;
    uVar5 = local_118;
LAB_00904bd4:
    __src = (void *)*plVar6;
    sVar7 = uVar5 - (long)__src;
    if (0xfffffffffffffff6 < sVar7) {
                    /* WARNING: Subroutine does not return */
      std::string::__throw_length_error_abi_nn220000_();
    }
    if (0x16 < sVar7) {
      uVar5 = 0x1a;
      if ((sVar7 | 7) != 0x17) {
        uVar5 = (sVar7 | 7) + 1;
      }
      __dest = (undefined1 *)FUN_00f62c00(uVar5);
      in_x8[1] = sVar7;
      in_x8[2] = (ulong)__dest;
      *in_x8 = uVar5 | 1;
      goto LAB_00904c28;
    }
  }
  __dest = (undefined1 *)((long)in_x8 + 1);
  *(char *)in_x8 = (char)((int)sVar7 << 1);
LAB_00904c28:
  memmove(__dest,__src,sVar7);
  local_178 = &PTR__ostringstream_00f68b98;
  __dest[sVar7] = 0;
  ppuStack_108 = &PTR__ostringstream_00f68bc0;
  local_170 = &PTR__stringbuf_00f687d0;
  if ((local_160[6] & 1U) != 0) {
    operator_delete(local_120,local_160[6] & 0xfffffffffffffffe);
  }
  local_170 = &PTR__streambuf_00f68750;
  std::locale::~locale((locale *)&uStack_168);
  std::ostream::~ostream((ostream *)&local_178);
  std::ios::~ios((ios *)&ppuStack_108);
  if (*(long *)(lVar2 + 0x28) == local_70) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== getHalCodecConfiguration @ 009499c4 size 4964 :: A2dpSscToHalConfig */

/* WARNING: Unknown calling convention: __rustcall */
/* bluetooth::audio::aidl::a2dp::codec::getHalCodecConfiguration */

uint __rustcall
bluetooth::audio::aidl::a2dp::codec::getHalCodecConfiguration(ushort *param_1,undefined4 *param_2)

{
  int iVar1;
  byte bVar2;
  byte bVar3;
  uint uVar4;
  uint uVar5;
  long lVar6;
  ushort uVar7;
  undefined *puVar8;
  undefined4 uVar9;
  uint uVar10;
  AParcel *pAVar11;
  size_t sVar12;
  char *pcVar13;
  undefined8 uVar14;
  ulong uVar15;
  undefined1 uVar16;
  undefined4 uVar17;
  undefined8 *in_x18;
  ulong uVar18;
  ulong uVar19;
  uint uVar20;
  ulong uVar21;
  uint uVar22;
  uint uVar23;
  undefined8 unaff_x30;
  undefined1 local_118;
  undefined4 local_108;
  undefined1 uStack_104;
  undefined1 uStack_103;
  ushort uStack_102;
  undefined4 uStack_100;
  undefined4 uStack_fc;
  undefined8 local_f8;
  uint **ppuStack_f0;
  undefined8 local_e8;
  undefined4 local_e0 [2];
  char *local_d8;
  char *pcStack_d0;
  undefined4 local_c8;
  undefined2 local_c4;
  uint *local_c0;
  code *local_b8;
  ulong local_b0;
  undefined8 local_a8;
  ulong local_a0;
  undefined8 uStack_98;
  ulong local_90;
  undefined8 local_88;
  undefined8 uStack_80;
  long local_70;
  
  *in_x18 = unaff_x30;
  lVar6 = tpidr_el0;
  local_70 = *(long *)(lVar6 + 0x28);
  if (param_2 != (undefined4 *)0x0) {
    param_2[1] = *(undefined4 *)(param_1 + 4);
    param_2[2] = (uint)*param_1;
    uVar10 = 0;
    iVar1 = *(int *)(param_1 + 0x10);
    if (iVar1 < 6) {
      if (iVar1 < 2) {
        if (iVar1 == 0) goto LAB_00949b3c;
        if (iVar1 != 1) goto LAB_0094ac98;
LAB_00949ae4:
        *param_2 = 2;
        bVar2 = *(byte *)((long)param_1 + 0xf);
        uVar10 = bVar2 - 0x10 >> 4;
        uVar23 = uVar10 | (uint)bVar2 << 0x1c;
        if ((7 < uVar23) || ((0x8bU >> (ulong)(uVar10 & 0x1f) & 1) == 0)) {
          local_e0[0] = 0x1bd;
          local_e8 = 6;
          pcVar13 = "Unknown AAC object_type={}";
          local_b8 = (code *)0x0;
          local_b0 = 6;
          local_c0 = (uint *)(ulong)bVar2;
LAB_00949c00:
          pcStack_d0 = "A2dpAacToHalConfig";
LAB_00949c04:
          uVar14 = 0x1a;
          goto LAB_0094ac90;
        }
        uVar10 = *(uint *)(param_1 + 0x14);
        if ((int)uVar10 < 0x10) {
          if ((int)uVar10 < 4) {
            if (uVar10 == 1) {
              uVar9 = 0xac44;
            }
            else {
              if (uVar10 != 2) {
LAB_0094a7ec:
                local_e0[0] = 0x1c2;
                local_e8 = 0xf;
                local_b8 = 
                _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IK29btav_a2dp_codec_sample_rate_tEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESH_SI_SK_
                ;
                local_b0 = 0xf;
                pcVar13 = "Unknown AAC sample_rate={}";
                local_c0 = (uint *)(param_1 + 0x14);
                goto LAB_00949c00;
              }
              uVar9 = 48000;
            }
          }
          else if (uVar10 == 4) {
            uVar9 = 0x15888;
          }
          else {
            if (uVar10 != 8) goto LAB_0094a7ec;
            uVar9 = 96000;
          }
        }
        else if ((int)uVar10 < 0x40) {
          if (uVar10 == 0x10) {
            uVar9 = 0x2b110;
          }
          else {
            if (uVar10 != 0x20) goto LAB_0094a7ec;
            uVar9 = 0x2ee00;
          }
        }
        else if (uVar10 == 0x40) {
          uVar9 = 16000;
        }
        else {
          if (uVar10 != 0x80) goto LAB_0094a7ec;
          uVar9 = 24000;
        }
        uVar22 = *(uint *)(param_1 + 0x18);
        uVar10 = uVar22;
        if (uVar22 != 2) {
          uVar10 = 0;
        }
        if (uVar22 == 1) {
          uVar10 = 1;
        }
        if (uVar10 == 0) {
          local_e0[0] = 0x1c7;
          pcStack_d0 = "A2dpAacToHalConfig";
          local_b8 = 
          _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IK30btav_a2dp_codec_channel_mode_tEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESH_SI_SK_
          ;
          pcVar13 = "Unknown AAC channel_mode={}";
          local_c0 = (uint *)(param_1 + 0x18);
          goto LAB_0094a57c;
        }
        uVar22 = *(int *)(param_1 + 0x16) - 1;
        if ((7 < uVar22) || ((0x8bU >> (ulong)(uVar22 & 0x1f) & 1) == 0)) {
          local_e0[0] = 0x1d9;
          pcStack_d0 = "A2dpAacToHalConfig";
          pcVar13 = "Unknown AAC bits_per_sample={}";
          goto LAB_0094ab04;
        }
        uVar7 = param_1[9];
        if (param_2[0x16] != 0xffffffff) {
          (*(code *)(&
                    PTR___dispatch_abi_nn220000_<std::__variant_detail::__dtor<std::__variant_detail::__traits<aidl::android::hardware::bluetooth::audio::SbcConfiguration,aidl::android::hardware::bluetooth::audio::AacConfiguration,aidl::android::hardware::bluetooth::audio::LdacConfiguration,aidl::android::hardware::bluetooth::audio::AptxConfiguration,aidl::android::hardware::bluetooth::audio::AptxAdaptiveConfiguration,aidl::android::hardware::bluetooth::audio::Lc3Configuration,aidl::android::hardware::bluetooth::audio::CodecConfiguration::VendorConfiguration,std::optional<aidl::android::hardware::bluetooth::audio::OpusConfiguration>>,(std::__variant_detail::_Trait)1>::__destroy[abi:nn220000]()::_lambda(auto:1&)_1_&&,std::__variant_detail::__base<(std::__variant_detail::_Trait)1,aidl::android::hardware::bluetooth::audio::SbcConfiguration,aidl::android::hardware::bluetooth::audio::AacConfiguration,aidl::android::hardware::bluetooth::audio::LdacConfiguration,aidl::android::hardware::bluetooth::audio::AptxConfiguration,aidl::android::hardware::bluetooth::audio::AptxAdaptiveConfiguration,aidl::android::hardware::bluetooth::audio::Lc3Configuration,aidl::android::hardware::bluetooth::audio::CodecConfiguration::VendorConfiguration,std::optional<aidl::android::hardware::bluetooth::audio::OpusConfiguration>>&>_00f9e4f0
                    )[(uint)param_2[0x16]])(&local_c0,param_2 + 6);
        }
        uVar17 = 1;
        *(char *)(param_2 + 6) = (char)(0x1000203 >> ((ulong)(uVar23 << 3) & 0x3f));
        *(undefined2 *)((long)param_2 + 0x19) = 0;
        *(undefined1 *)((long)param_2 + 0x1b) = 0;
        param_2[7] = uVar9;
        *(char *)(param_2 + 8) = (char)uVar10;
        *(byte *)((long)param_2 + 0x21) = (byte)uVar7 >> 7;
        *(char *)((long)param_2 + 0x22) = (char)(0x2200000020001810 >> ((ulong)(uVar22 * 8) & 0x3f))
        ;
        *(undefined1 *)((long)param_2 + 0x23) = 0;
LAB_0094ac1c:
        param_2[0x16] = uVar17;
      }
      else {
        if (iVar1 - 2U < 2) {
          uVar9 = 3;
          if (iVar1 != 2) {
            uVar9 = 4;
          }
          *param_2 = uVar9;
          uVar10 = *(uint *)(param_1 + 0x14);
          if ((int)uVar10 < 0x10) {
            if ((int)uVar10 < 4) {
              if (uVar10 == 1) {
                uVar18 = 0xac44;
              }
              else {
                if (uVar10 != 2) {
LAB_0094a160:
                  local_e0[0] = 0x1ed;
                  pcStack_d0 = "A2dpAptxToHalConfig";
                  local_b8 = 
                  _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IK29btav_a2dp_codec_sample_rate_tEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESH_SI_SK_
                  ;
                  local_b0 = 0xf;
                  pcVar13 = "Unknown aptX sample_rate={}";
                  local_e8 = 0xf;
                  local_c0 = (uint *)(param_1 + 0x14);
                  goto LAB_0094a580;
                }
                uVar18 = 48000;
              }
            }
            else if (uVar10 == 4) {
              uVar18 = 0x15888;
            }
            else {
              if (uVar10 != 8) goto LAB_0094a160;
              uVar18 = 96000;
            }
          }
          else if ((int)uVar10 < 0x40) {
            if (uVar10 == 0x10) {
              uVar18 = 0x2b110;
            }
            else {
              if (uVar10 != 0x20) goto LAB_0094a160;
              uVar18 = 0x2ee00;
            }
          }
          else if (uVar10 == 0x40) {
            uVar18 = 16000;
          }
          else {
            if (uVar10 != 0x80) goto LAB_0094a160;
            uVar18 = 24000;
          }
          uVar23 = *(uint *)(param_1 + 0x18);
          uVar10 = uVar23;
          if (uVar23 != 2) {
            uVar10 = 0;
          }
          if (uVar23 == 1) {
            uVar10 = 1;
          }
          if (uVar10 == 0) {
            local_e0[0] = 0x1f2;
            pcStack_d0 = "A2dpAptxToHalConfig";
            local_b8 = 
            _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IK30btav_a2dp_codec_channel_mode_tEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESH_SI_SK_
            ;
            local_b0 = 0xf;
            pcVar13 = "Unknown aptX channel_mode={}";
            local_e8 = 0xf;
            local_c0 = (uint *)(param_1 + 0x18);
            goto LAB_0094ac80;
          }
          uVar23 = *(int *)(param_1 + 0x16) - 1;
          if ((7 < uVar23) || ((0x8bU >> (ulong)(uVar23 & 0x1f) & 1) == 0)) {
            local_e0[0] = 0x1f7;
            pcStack_d0 = "A2dpAptxToHalConfig";
            pcVar13 = "Unknown aptX bits_per_sample={}";
            goto LAB_0094a734;
          }
          uVar21 = *(ulong *)(&DAT_00252840 + (ulong)uVar23 * 8);
          if (param_2[0x16] != 0xffffffff) {
            (*(code *)(&
                      PTR___dispatch_abi_nn220000_<std::__variant_detail::__dtor<std::__variant_detail::__traits<aidl::android::hardware::bluetooth::audio::SbcConfiguration,aidl::android::hardware::bluetooth::audio::AacConfiguration,aidl::android::hardware::bluetooth::audio::LdacConfiguration,aidl::android::hardware::bluetooth::audio::AptxConfiguration,aidl::android::hardware::bluetooth::audio::AptxAdaptiveConfiguration,aidl::android::hardware::bluetooth::audio::Lc3Configuration,aidl::android::hardware::bluetooth::audio::CodecConfiguration::VendorConfiguration,std::optional<aidl::android::hardware::bluetooth::audio::OpusConfiguration>>,(std::__variant_detail::_Trait)1>::__destroy[abi:nn220000]()::_lambda(auto:1&)_1_&&,std::__variant_detail::__base<(std::__variant_detail::_Trait)1,aidl::android::hardware::bluetooth::audio::SbcConfiguration,aidl::android::hardware::bluetooth::audio::AacConfiguration,aidl::android::hardware::bluetooth::audio::LdacConfiguration,aidl::android::hardware::bluetooth::audio::AptxConfiguration,aidl::android::hardware::bluetooth::audio::AptxAdaptiveConfiguration,aidl::android::hardware::bluetooth::audio::Lc3Configuration,aidl::android::hardware::bluetooth::audio::CodecConfiguration::VendorConfiguration,std::optional<aidl::android::hardware::bluetooth::audio::OpusConfiguration>>&>_00f9e4f0
                      )[(uint)param_2[0x16]])(&local_c0,param_2 + 6);
          }
          uVar9 = 3;
          uVar18 = uVar21 | (ulong)(uVar10 & 0xff) << 0x20 | uVar18;
        }
        else {
          if (iVar1 != 4) goto LAB_0094ac98;
          *param_2 = 5;
          uVar10 = *(uint *)(param_1 + 0x14);
          if ((int)uVar10 < 0x10) {
            if ((int)uVar10 < 4) {
              if (uVar10 == 1) {
                uVar21 = 0xac44;
              }
              else {
                if (uVar10 != 2) {
LAB_0094a83c:
                  local_e0[0] = 0x206;
                  pcStack_d0 = "A2dpLdacToHalConfig";
                  local_b8 = 
                  _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IK29btav_a2dp_codec_sample_rate_tEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESH_SI_SK_
                  ;
                  local_b0 = 0xf;
                  pcVar13 = "Unknown LDAC sample_rate={}";
                  local_e8 = 0xf;
                  local_c0 = (uint *)(param_1 + 0x14);
                  goto LAB_0094a580;
                }
                uVar21 = 48000;
              }
            }
            else if (uVar10 == 4) {
              uVar21 = 0x15888;
            }
            else {
              if (uVar10 != 8) goto LAB_0094a83c;
              uVar21 = 96000;
            }
          }
          else if ((int)uVar10 < 0x40) {
            if (uVar10 == 0x10) {
              uVar21 = 0x2b110;
            }
            else {
              if (uVar10 != 0x20) goto LAB_0094a83c;
              uVar21 = 0x2ee00;
            }
          }
          else if (uVar10 == 0x40) {
            uVar21 = 16000;
          }
          else {
            if (uVar10 != 0x80) goto LAB_0094a83c;
            uVar21 = 24000;
          }
          bVar2 = (byte)param_1[0xb];
          if (bVar2 == 1) {
            uVar19 = 0x100000000;
          }
          else if (bVar2 == 4) {
            uVar19 = 0x300000000;
          }
          else {
            if (bVar2 != 2) {
              local_e0[0] = 0x215;
              pcStack_d0 = "A2dpLdacToHalConfig";
              pcVar13 = "Unknown LDAC channel_mode={}";
              local_b8 = (code *)0x0;
              local_b0 = 3;
              local_e8 = 3;
              local_c0 = (uint *)(ulong)bVar2;
              goto LAB_0094ac80;
            }
            uVar19 = 0x200000000;
          }
          if (*(long *)(param_1 + 0x1c) == 0) {
            uVar15 = 0x30000000000;
          }
          else {
            uVar15 = *(long *)(param_1 + 0x1c) % 10;
            if (2 < uVar15) {
              uVar15 = 3;
            }
            uVar15 = uVar15 << 0x28;
          }
          uVar10 = *(int *)(param_1 + 0x16) - 1;
          if ((7 < uVar10) || ((0x8bU >> (ulong)(uVar10 & 0x1f) & 1) == 0)) {
            local_e0[0] = 0x23d;
            pcStack_d0 = "A2dpLdacToHalConfig";
            pcVar13 = "Unknown LDAC bits_per_sample={}";
            goto LAB_0094a734;
          }
          uVar18 = *(ulong *)(&DAT_00252880 + (ulong)uVar10 * 8);
          if (param_2[0x16] != 0xffffffff) {
            (*(code *)(&
                      PTR___dispatch_abi_nn220000_<std::__variant_detail::__dtor<std::__variant_detail::__traits<aidl::android::hardware::bluetooth::audio::SbcConfiguration,aidl::android::hardware::bluetooth::audio::AacConfiguration,aidl::android::hardware::bluetooth::audio::LdacConfiguration,aidl::android::hardware::bluetooth::audio::AptxConfiguration,aidl::android::hardware::bluetooth::audio::AptxAdaptiveConfiguration,aidl::android::hardware::bluetooth::audio::Lc3Configuration,aidl::android::hardware::bluetooth::audio::CodecConfiguration::VendorConfiguration,std::optional<aidl::android::hardware::bluetooth::audio::OpusConfiguration>>,(std::__variant_detail::_Trait)1>::__destroy[abi:nn220000]()::_lambda(auto:1&)_1_&&,std::__variant_detail::__base<(std::__variant_detail::_Trait)1,aidl::android::hardware::bluetooth::audio::SbcConfiguration,aidl::android::hardware::bluetooth::audio::AacConfiguration,aidl::android::hardware::bluetooth::audio::LdacConfiguration,aidl::android::hardware::bluetooth::audio::AptxConfiguration,aidl::android::hardware::bluetooth::audio::AptxAdaptiveConfiguration,aidl::android::hardware::bluetooth::audio::Lc3Configuration,aidl::android::hardware::bluetooth::audio::CodecConfiguration::VendorConfiguration,std::optional<aidl::android::hardware::bluetooth::audio::OpusConfiguration>>&>_00f9e4f0
                      )[(uint)param_2[0x16]])(&local_c0,param_2 + 6);
          }
          uVar9 = 2;
          uVar18 = uVar19 | uVar21 | uVar15 | uVar18;
        }
        *(ulong *)(param_2 + 6) = uVar18;
        param_2[0x16] = uVar9;
      }
LAB_0094ac24:
      uVar10 = _GLOBAL__N_1::IsCodecOffloadingEnabled(param_2);
      goto LAB_0094ac98;
    }
    if (iVar1 < 0xd) {
      if (iVar1 == 6) {
        *param_2 = 9;
        uVar10 = *(int *)(param_1 + 0x16) - 1;
        if ((uVar10 < 8) && ((0x8bU >> (ulong)(uVar10 & 0x1f) & 1) != 0)) {
          uVar23 = *(uint *)(param_1 + 0x14);
          if ((int)uVar23 < 0x10) {
            if ((int)uVar23 < 4) {
              if (uVar23 == 1) {
                uVar9 = 0xac44;
              }
              else {
                if (uVar23 != 2) {
LAB_0094acd4:
                  local_e0[0] = 0x253;
                  pcStack_d0 = "A2dpOpusToHalConfig";
                  local_b8 = 
                  _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IK29btav_a2dp_codec_sample_rate_tEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESH_SI_SK_
                  ;
                  pcVar13 = "Unknown Opus sample_rate={}";
                  local_c0 = (uint *)(param_1 + 0x14);
                  goto LAB_0094a57c;
                }
                uVar9 = 48000;
              }
            }
            else if (uVar23 == 4) {
              uVar9 = 0x15888;
            }
            else {
              if (uVar23 != 8) goto LAB_0094acd4;
              uVar9 = 96000;
            }
          }
          else if ((int)uVar23 < 0x40) {
            if (uVar23 == 0x10) {
              uVar9 = 0x2b110;
            }
            else {
              if (uVar23 != 0x20) goto LAB_0094acd4;
              uVar9 = 0x2ee00;
            }
          }
          else if (uVar23 == 0x40) {
            uVar9 = 16000;
          }
          else {
            if (uVar23 != 0x80) goto LAB_0094acd4;
            uVar9 = 24000;
          }
          uVar22 = *(uint *)(param_1 + 0x18);
          uVar23 = uVar22;
          if (uVar22 != 2) {
            uVar23 = 0;
          }
          if (uVar22 == 1) {
            uVar23 = 1;
          }
          if (uVar23 != 0) {
            uVar17 = 0x280;
            if (uVar22 != 2) {
              uVar17 = 0x140;
            }
            if (param_2[0x16] != 0xffffffff) {
              (*(code *)(&
                        PTR___dispatch_abi_nn220000_<std::__variant_detail::__dtor<std::__variant_detail::__traits<aidl::android::hardware::bluetooth::audio::SbcConfiguration,aidl::android::hardware::bluetooth::audio::AacConfiguration,aidl::android::hardware::bluetooth::audio::LdacConfiguration,aidl::android::hardware::bluetooth::audio::AptxConfiguration,aidl::android::hardware::bluetooth::audio::AptxAdaptiveConfiguration,aidl::android::hardware::bluetooth::audio::Lc3Configuration,aidl::android::hardware::bluetooth::audio::CodecConfiguration::VendorConfiguration,std::optional<aidl::android::hardware::bluetooth::audio::OpusConfiguration>>,(std::__variant_detail::_Trait)1>::__destroy[abi:nn220000]()::_lambda(auto:1&)_1_&&,std::__variant_detail::__base<(std::__variant_detail::_Trait)1,aidl::android::hardware::bluetooth::audio::SbcConfiguration,aidl::android::hardware::bluetooth::audio::AacConfiguration,aidl::android::hardware::bluetooth::audio::LdacConfiguration,aidl::android::hardware::bluetooth::audio::AptxConfiguration,aidl::android::hardware::bluetooth::audio::AptxAdaptiveConfiguration,aidl::android::hardware::bluetooth::audio::Lc3Configuration,aidl::android::hardware::bluetooth::audio::CodecConfiguration::VendorConfiguration,std::optional<aidl::android::hardware::bluetooth::audio::OpusConfiguration>>&>_00f9e4f0
                        )[(uint)param_2[0x16]])(&local_c0,param_2 + 6);
            }
            *(char *)(param_2 + 6) = (char)(0x2200000020001810 >> ((ulong)(uVar10 * 8) & 0x3f));
            param_2[7] = uVar9;
            param_2[8] = 20000;
            *(undefined2 *)((long)param_2 + 0x19) = 0;
            *(undefined1 *)((long)param_2 + 0x1b) = 0;
            param_2[9] = uVar17;
            *(undefined1 *)(param_2 + 10) = 0;
            *(char *)((long)param_2 + 0x29) = (char)uVar23;
            *(undefined2 *)((long)param_2 + 0x2a) = 0;
            *(undefined1 *)(param_2 + 0xb) = 1;
            uVar17 = 7;
            goto LAB_0094ac1c;
          }
          local_e0[0] = 600;
          pcStack_d0 = "A2dpOpusToHalConfig";
          local_b8 = 
          _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IK30btav_a2dp_codec_channel_mode_tEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESH_SI_SK_
          ;
          local_b0 = 0xf;
          pcVar13 = "Unknown Opus channel_mode={}";
          local_e8 = 0xf;
          local_c0 = (uint *)(param_1 + 0x18);
LAB_0094ac80:
          uVar14 = 0x1c;
        }
        else {
          local_e0[0] = 0x24e;
          pcStack_d0 = "A2dpOpusToHalConfig";
          pcVar13 = "Unknown Opus bits_per_sample={}";
LAB_0094a734:
          local_c0 = (uint *)(param_1 + 0x16);
          local_b0 = 0xf;
          local_b8 = 
          _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IK33btav_a2dp_codec_bits_per_sample_tEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESH_SI_SK_
          ;
          local_e8 = 0xf;
          uVar14 = 0x1f;
        }
      }
      else {
        if (iVar1 != 8) goto LAB_0094ac98;
        uStack_104 = 0;
        uStack_103 = 0;
        uStack_102 = 0;
        uStack_100 = 0;
        *param_2 = 7;
        uVar10 = *(uint *)(param_1 + 0x14);
        if ((int)uVar10 < 0x10) {
          if ((int)uVar10 < 4) {
            if (uVar10 == 1) {
              local_108 = 0xac44;
            }
            else {
              if (uVar10 != 2) {
LAB_0094a798:
                local_e0[0] = 0x272;
                pcStack_d0 = "A2dpSscToHalConfig";
                local_b8 = 
                _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IK29btav_a2dp_codec_sample_rate_tEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESH_SI_SK_
                ;
                local_b0 = 0xf;
                pcVar13 = "Unknown ssc sample_rate={}";
                local_e8 = 0xf;
                local_c0 = (uint *)(param_1 + 0x14);
                goto LAB_00949c04;
              }
              local_108 = 48000;
            }
          }
          else if (uVar10 == 4) {
            local_108 = 0x15888;
          }
          else {
            if (uVar10 != 8) goto LAB_0094a798;
            local_108 = 96000;
          }
        }
        else if ((int)uVar10 < 0x40) {
          if (uVar10 == 0x10) {
            local_108 = 0x2b110;
          }
          else {
            if (uVar10 != 0x20) goto LAB_0094a798;
            local_108 = 0x2ee00;
          }
        }
        else if (uVar10 == 0x40) {
          local_108 = 16000;
        }
        else {
          if (uVar10 != 0x80) goto LAB_0094a798;
          local_108 = 24000;
        }
        uVar23 = *(uint *)(param_1 + 0x18);
        uVar10 = uVar23;
        if (uVar23 != 2) {
          uVar10 = 0;
        }
        if (uVar23 == 1) {
          uVar10 = 1;
        }
        uStack_104 = (undefined1)uVar10;
        if (uVar10 == 0) {
          local_e0[0] = 0x277;
          pcStack_d0 = "A2dpSscToHalConfig";
          local_b8 = 
          _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IK30btav_a2dp_codec_channel_mode_tEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESH_SI_SK_
          ;
          pcVar13 = "Unknown ssc channel_mode={}";
          local_c0 = (uint *)(param_1 + 0x18);
LAB_0094a57c:
          local_b0 = 0xf;
          local_e8 = 0xf;
          goto LAB_0094a580;
        }
        uVar10 = *(int *)(param_1 + 0x16) - 1;
        if ((uVar10 < 8) && ((0x8bU >> (ulong)(uVar10 & 0x1f) & 1) != 0)) {
          uStack_103 = (undefined1)(0x2200000020001810 >> ((ulong)(uVar10 * 8) & 0x3f));
          pAVar11 = (AParcel *)AParcel_create();
          AParcel_reset();
          puVar8 = PTR_s_android_hardware_bluetooth_audio_00fab9a8;
          sVar12 = strlen(PTR_s_android_hardware_bluetooth_audio_00fab9a8);
          AParcel_writeString(pAVar11,puVar8,sVar12);
          ::aidl::android::hardware::bluetooth::audio::PcmConfiguration::writeToParcel
                    ((PcmConfiguration *)&local_108,pAVar11);
          if (param_2[0x16] != 0xffffffff) {
            (*(code *)(&
                      PTR___dispatch_abi_nn220000_<std::__variant_detail::__dtor<std::__variant_detail::__traits<aidl::android::hardware::bluetooth::audio::SbcConfiguration,aidl::android::hardware::bluetooth::audio::AacConfiguration,aidl::android::hardware::bluetooth::audio::LdacConfiguration,aidl::android::hardware::bluetooth::audio::AptxConfiguration,aidl::android::hardware::bluetooth::audio::AptxAdaptiveConfiguration,aidl::android::hardware::bluetooth::audio::Lc3Configuration,aidl::android::hardware::bluetooth::audio::CodecConfiguration::VendorConfiguration,std::optional<aidl::android::hardware::bluetooth::audio::OpusConfiguration>>,(std::__variant_detail::_Trait)1>::__destroy[abi:nn220000]()::_lambda(auto:1&)_1_&&,std::__variant_detail::__base<(std::__variant_detail::_Trait)1,aidl::android::hardware::bluetooth::audio::SbcConfiguration,aidl::android::hardware::bluetooth::audio::AacConfiguration,aidl::android::hardware::bluetooth::audio::LdacConfiguration,aidl::android::hardware::bluetooth::audio::AptxConfiguration,aidl::android::hardware::bluetooth::audio::AptxAdaptiveConfiguration,aidl::android::hardware::bluetooth::audio::Lc3Configuration,aidl::android::hardware::bluetooth::audio::CodecConfiguration::VendorConfiguration,std::optional<aidl::android::hardware::bluetooth::audio::OpusConfiguration>>&>_00f9e4f0
                      )[(uint)param_2[0x16]])(&local_c0,param_2 + 6);
          }
          param_2[0x16] = 0xffffffff;
          param_2[6] = 0x75;
          *(undefined2 *)(param_2 + 7) = 1;
          *(undefined ***)(param_2 + 8) = &PTR__AParcelableHolder_00f81998;
          uVar14 = AParcel_create();
          *(undefined8 *)(param_2 + 10) = uVar14;
          param_2[0xc] = 1;
          uVar9 = AParcel_getDataSize(pAVar11);
          AParcel_appendFrom(pAVar11,uVar14,0,uVar9);
          param_2[0x16] = 6;
          AParcel_delete(pAVar11);
          goto LAB_0094ac24;
        }
        local_e0[0] = 0x27c;
        pcStack_d0 = "A2dpSscToHalConfig";
        pcVar13 = "Unknown ssc bits_per_sample={}";
LAB_0094ab04:
        local_c0 = (uint *)(param_1 + 0x16);
        local_b0 = 0xf;
        local_b8 = 
        _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IK33btav_a2dp_codec_bits_per_sample_tEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESH_SI_SK_
        ;
        local_e8 = 0xf;
        uVar14 = 0x1e;
      }
    }
    else {
      if (iVar1 == 0xe) goto LAB_00949ae4;
      if (iVar1 != 0xd) goto LAB_0094ac98;
LAB_00949b3c:
      *param_2 = 1;
      uVar10 = *(uint *)(param_1 + 0x14);
      if ((int)uVar10 < 0x10) {
        if (3 < (int)uVar10) {
          if (uVar10 == 4) {
            uVar9 = 0x15888;
          }
          else {
            if (uVar10 != 8) goto LAB_0094a10c;
            uVar9 = 96000;
          }
          goto LAB_00949ec0;
        }
        if (uVar10 == 1) {
          uVar9 = 0xac44;
          goto LAB_00949ec0;
        }
        if (uVar10 != 2) {
LAB_0094a10c:
          local_e0[0] = 0x13e;
          pcStack_d0 = "A2dpSbcToHalConfig";
          local_b8 = 
          _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IK29btav_a2dp_codec_sample_rate_tEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESH_SI_SK_
          ;
          local_b0 = 0xf;
          pcVar13 = "Unknown SBC sample_rate={}";
          local_e8 = 0xf;
          local_c0 = (uint *)(param_1 + 0x14);
          goto LAB_00949c04;
        }
        uVar9 = 48000;
        uVar10 = 0x21;
        uVar23 = 0x33;
      }
      else {
        if ((int)uVar10 < 0x40) {
          if (uVar10 == 0x10) {
            uVar9 = 0x2b110;
          }
          else {
            if (uVar10 != 0x20) goto LAB_0094a10c;
            uVar9 = 0x2ee00;
          }
        }
        else if (uVar10 == 0x40) {
          uVar9 = 16000;
        }
        else {
          if (uVar10 != 0x80) goto LAB_0094a10c;
          uVar9 = 24000;
        }
LAB_00949ec0:
        uVar10 = 0x23;
        uVar23 = 0x35;
      }
      uVar22 = *(byte *)((long)param_1 + 0xf) & 0xf;
      uVar4 = uVar22 - 1;
      if ((uVar4 < 8) && ((0x8bU >> (ulong)(uVar4 & 0x1f) & 1) != 0)) {
        bVar2 = (byte)param_1[8];
        uVar5 = bVar2 - 0x10;
        if ((0x7f < uVar5) || (uVar5 = uVar5 >> 4, (0x8bU >> (ulong)(uVar5 & 0x1f) & 1) == 0)) {
          local_e0[0] = 0x165;
          local_c0 = (uint *)((ulong)bVar2 & 0xf0);
          pcStack_d0 = "A2dpSbcToHalConfig";
          local_b8 = (code *)0x0;
          local_b0 = 6;
          pcVar13 = "Unknown SBC block_length={}";
          local_e8 = 6;
          goto LAB_0094a580;
        }
        uVar22 = bVar2 & 0xc;
        if (uVar22 == 8) {
          uVar16 = 4;
        }
        else {
          if (uVar22 != 4) {
            local_e0[0] = 0x172;
            pcStack_d0 = "A2dpSbcToHalConfig";
            local_b8 = (code *)0x0;
            local_b0 = 6;
            pcVar13 = "Unknown SBC Subbands={}";
            local_e8 = 6;
            uVar14 = 0x17;
            local_c0 = (uint *)(ulong)uVar22;
            goto LAB_0094ac90;
          }
          uVar16 = 8;
        }
        uVar22 = bVar2 & 3;
        if (uVar22 == 2) {
          local_118 = 0;
        }
        else {
          if (uVar22 != 1) {
            local_e0[0] = 0x17f;
            pcVar13 = "Unknown SBC alloc_method={}";
            goto LAB_00949f64;
          }
          local_118 = 1;
        }
        bVar2 = *(byte *)((long)param_1 + 0x11);
        uVar20 = (uint)bVar2;
        bVar3 = (byte)param_1[9];
        uVar22 = (uint)bVar3;
        uVar21 = btif_av_is_carkit_on_active_device();
        local_c4 = DAT_0101f6d4;
        local_c8 = DAT_0101f6d0;
        local_108 = 0;
        uStack_104 = 0;
        uStack_103 = 0;
        uStack_102 = 0;
        uStack_100 = 0;
        uStack_fc = 0;
        BtaAvCo::GetPeerEncoderParameters(&DAT_01014360,&local_c8,&local_108);
        if ((char)param_1[0x30] == '\x01') {
          uVar22 = (uint)bVar3;
          if (uVar10 <= bVar3) {
            uVar22 = uVar10;
          }
          local_c0 = (uint *)(ulong)uVar22;
          local_e0[0] = 0x191;
          local_d8 = 
          "packages/modules/Bluetooth/system/audio_hal_interface/aidl/a2dp/codec_status_aidl.cc";
          pcStack_d0 = "A2dpSbcToHalConfig";
          uVar20 = (uint)bVar2;
          if (uVar22 <= bVar2) {
            uVar20 = uVar22;
          }
          local_b0 = (ulong)uVar20;
          ppuStack_f0 = &local_c0;
          local_b8 = (code *)0x0;
          local_a8 = 0;
          local_a0 = 99;
          local_f8 = 2;
          local_e8 = 99;
          log_internal::vlog(6,"bluetooth-a2dp-aidl",local_e0,
                             "avoid scalable with low quality, max bitpool={}, min bitpool={}",0x3f,
                             &local_f8);
        }
        else if ((uVar21 & 1) != 0 || uStack_102 < 0x298) {
          local_e0[0] = 0x199;
          local_d8 = 
          "packages/modules/Bluetooth/system/audio_hal_interface/aidl/a2dp/codec_status_aidl.cc";
          pcStack_d0 = "A2dpSbcToHalConfig";
          local_c0 = (uint *)(uVar21 & 1);
          local_a8 = 0;
          uVar20 = (uint)bVar3;
          if (uVar23 <= bVar3) {
            uVar20 = uVar23;
          }
          local_a0 = (ulong)uVar20;
          local_b8 = (code *)0x0;
          ppuStack_f0 = &local_c0;
          uStack_98 = 0;
          local_88 = 0;
          uStack_80 = 0x18cc1;
          local_f8 = 4;
          local_e8 = 0x18cc1;
          local_b0 = (ulong)uStack_102;
          local_90 = local_a0;
          log_internal::vlog(6,"bluetooth-a2dp-aidl",local_e0,
                             "avoid scalable with high quality, is carkit={}, mtu={}, max bitpool={}, min bitpool={}"
                             ,0x56,&local_f8);
          uVar22 = uVar20;
        }
        uVar10 = *(int *)(param_1 + 0x16) - 1;
        if ((7 < uVar10) || ((0x8bU >> (ulong)(uVar10 & 0x1f) & 1) == 0)) {
          local_e0[0] = 0x1a0;
          pcStack_d0 = "A2dpSbcToHalConfig";
          pcVar13 = "Unknown SBC bits_per_sample={}";
          goto LAB_0094ab04;
        }
        if (param_2[0x16] != 0xffffffff) {
          (*(code *)(&
                    PTR___dispatch_abi_nn220000_<std::__variant_detail::__dtor<std::__variant_detail::__traits<aidl::android::hardware::bluetooth::audio::SbcConfiguration,aidl::android::hardware::bluetooth::audio::AacConfiguration,aidl::android::hardware::bluetooth::audio::LdacConfiguration,aidl::android::hardware::bluetooth::audio::AptxConfiguration,aidl::android::hardware::bluetooth::audio::AptxAdaptiveConfiguration,aidl::android::hardware::bluetooth::audio::Lc3Configuration,aidl::android::hardware::bluetooth::audio::CodecConfiguration::VendorConfiguration,std::optional<aidl::android::hardware::bluetooth::audio::OpusConfiguration>>,(std::__variant_detail::_Trait)1>::__destroy[abi:nn220000]()::_lambda(auto:1&)_1_&&,std::__variant_detail::__base<(std::__variant_detail::_Trait)1,aidl::android::hardware::bluetooth::audio::SbcConfiguration,aidl::android::hardware::bluetooth::audio::AacConfiguration,aidl::android::hardware::bluetooth::audio::LdacConfiguration,aidl::android::hardware::bluetooth::audio::AptxConfiguration,aidl::android::hardware::bluetooth::audio::AptxAdaptiveConfiguration,aidl::android::hardware::bluetooth::audio::Lc3Configuration,aidl::android::hardware::bluetooth::audio::CodecConfiguration::VendorConfiguration,std::optional<aidl::android::hardware::bluetooth::audio::OpusConfiguration>>&>_00f9e4f0
                    )[(uint)param_2[0x16]])(&local_c0,param_2 + 6);
        }
        param_2[6] = uVar9;
        *(char *)(param_2 + 7) = (char)(0x400000003000201 >> (((ulong)uVar4 & 7) << 3));
        *(char *)((long)param_2 + 0x1d) = (char)(0x400000008000c10 >> ((ulong)(uVar5 << 3) & 0x3f));
        *(undefined1 *)((long)param_2 + 0x1e) = uVar16;
        *(undefined1 *)((long)param_2 + 0x1f) = local_118;
        *(char *)(param_2 + 8) = (char)(0x2200000020001810 >> ((ulong)(uVar10 * 8) & 0x3f));
        *(undefined2 *)((long)param_2 + 0x21) = 0;
        *(undefined1 *)((long)param_2 + 0x23) = 0;
        param_2[9] = uVar20;
        param_2[10] = uVar22;
        param_2[0x16] = 0;
        goto LAB_0094ac24;
      }
      local_e0[0] = 0x151;
      pcVar13 = "Unknown SBC channel_mode={}";
LAB_00949f64:
      local_c0 = (uint *)(ulong)uVar22;
      local_b0 = 6;
      local_b8 = (code *)0x0;
      pcStack_d0 = "A2dpSbcToHalConfig";
      local_e8 = 6;
LAB_0094a580:
      uVar14 = 0x1b;
    }
LAB_0094ac90:
    ppuStack_f0 = &local_c0;
    local_d8 = 
    "packages/modules/Bluetooth/system/audio_hal_interface/aidl/a2dp/codec_status_aidl.cc";
    local_f8 = 1;
    log_internal::vlog(6,"bluetooth-a2dp-aidl",local_e0,pcVar13,uVar14,&local_f8);
  }
  uVar10 = 0;
LAB_0094ac98:
  if (*(long *)(lVar6 + 0x28) != local_70) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar10 & 1;
}


/* ==== SscBitrateByBusyLevel @ 0094b63c size 284 :: SscBitrateByBusyLevel */

/* WARNING: Unknown calling convention: __rustcall */
/* bluetooth::audio::aidl::a2dp::codec::SscBitrateByBusyLevel */

void __rustcall
bluetooth::audio::aidl::a2dp::codec::SscBitrateByBusyLevel(uint param_1,uint param_2,ulong param_3)

{
  long lVar1;
  undefined *puVar2;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  undefined8 local_b0;
  ulong *puStack_a8;
  undefined8 local_a0;
  undefined4 local_98 [2];
  char *local_90;
  char *pcStack_88;
  ulong local_80 [3];
  undefined8 uStack_68;
  ulong local_60;
  undefined8 local_58;
  undefined8 uStack_50;
  long local_38;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_38 = *(long *)(lVar1 + 0x28);
  local_98[0] = 900;
  local_90 = "packages/modules/Bluetooth/system/audio_hal_interface/aidl/a2dp/codec_status_aidl.cc";
  pcStack_88 = "SscBitrateByBusyLevel";
  param_2 = param_2 & 0xffff;
  local_80[0] = (ulong)param_1;
  local_80[1] = 0;
  local_60 = param_3 & 1;
  if (2 < param_2) {
    param_2 = 3;
  }
  puStack_a8 = local_80;
  uStack_68 = 0;
  local_58 = 0;
  uStack_50 = 0x4c6;
  local_b0 = 3;
  local_a0 = 0x4c6;
  local_80[2] = (ulong)param_2;
  log_internal::vlog(4,"bluetooth-a2dp-aidl",local_98,
                     "codec_type {} busy_level {} is_bitrate_limit {}",0x2f,&local_b0);
  if (param_1 == 0x200) {
    puVar2 = &UNK_0020a320;
  }
  else if (param_1 == 0x400) {
    puVar2 = &DAT_00207800;
  }
  else {
    puVar2 = &UNK_00209770;
    if ((param_3 & 1) == 0) {
      puVar2 = &DAT_00207650;
    }
  }
  if (*(long *)(lVar1 + 0x28) != local_38) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(*(undefined4 *)(puVar2 + (ulong)param_2 * 4));
  }
  return;
}


/* ==== setup_codec @ 0095637c size 2652 :: SscVendorGetTrackBitrateLimitation | auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::get() [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::Tag::sscConfig] */

/* WARNING: Unknown calling convention: __rustcall */
/* bluetooth::audio::seh_aidl::a2dp::setup_codec */

uint __rustcall bluetooth::audio::seh_aidl::a2dp::setup_codec(void)

{
  long lVar1;
  bool bVar2;
  byte bVar3;
  char cVar4;
  char cVar5;
  uint uVar6;
  int iVar7;
  long *plVar8;
  ulong uVar9;
  undefined8 uVar10;
  ostream *poVar11;
  long lVar12;
  ulong uVar13;
  ulong *puVar14;
  ulong uVar15;
  char *pcVar16;
  ulong uVar17;
  ulong uVar18;
  undefined8 uVar19;
  int **ppiVar20;
  ulong uVar21;
  uint uVar22;
  undefined4 uVar23;
  undefined8 *in_x18;
  uint uVar24;
  undefined8 unaff_x30;
  undefined8 local_2b0;
  undefined8 uStack_2a8;
  undefined8 local_2a0;
  code *local_298;
  int *local_290;
  int *local_288;
  int **local_280;
  char *local_278;
  undefined8 local_270;
  uint uStack_268;
  uint uStack_264;
  char *local_260;
  undefined8 uStack_258;
  undefined8 local_250;
  undefined8 uStack_248;
  undefined8 local_240;
  undefined8 uStack_238;
  undefined8 uStack_230;
  undefined8 uStack_228;
  undefined8 local_220;
  undefined8 uStack_218;
  undefined8 uStack_210;
  ulong local_208;
  undefined4 local_148;
  undefined2 local_144;
  int local_140;
  uint uStack_13c;
  uint uStack_138;
  uint uStack_134;
  undefined8 uStack_130;
  undefined8 local_128;
  undefined8 local_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined8 local_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  ulong local_e8;
  ulong local_e0;
  char *local_d8;
  char *pcStack_d0;
  int *local_c0;
  code *pcStack_b8;
  char *local_b0;
  undefined8 uStack_a8;
  undefined8 local_a0;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  long local_78;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_78 = *(long *)(lVar1 + 0x28);
  if (DAT_01033b50 == 0) {
    local_270._0_4_ = 0x2a5;
    uStack_268 = 0x163cf7;
    uStack_264 = 0;
    local_260 = "setup_codec";
    local_140 = 0;
    uStack_13c = 0;
    log_internal::vlog(6,"BTAudioA2dpSehAIDL",&local_270,"BluetoothAudio HAL is not enabled",0x21,
                       &local_140);
    uVar6 = 0;
    goto LAB_00956540;
  }
  uStack_138 = 0;
  uStack_134 = 0;
  local_140 = 0;
  uStack_13c = 0;
  local_128 = 0;
  uStack_130 = 0;
  uStack_118 = 0;
  local_120 = 0;
  uStack_108 = 0;
  uStack_110 = 0;
  uStack_f8 = 0;
  local_100 = 0;
  local_e8 = 0;
  uStack_f0 = 0;
  plVar8 = (long *)BtaAvCo::GetActivePeerCurrentCodec(&DAT_01014360);
  if (plVar8 == (long *)0x0) {
    local_270._0_4_ = 0x144;
    uStack_268 = 0x163cf7;
    uStack_264 = 0;
    local_260 = "a2dp_get_selected_hal_codec_config";
    local_c0 = (int *)0x0;
    pcVar16 = "failure to get A2DP codec config";
    puVar14 = &local_270;
    ppiVar20 = &local_c0;
    uVar10 = 5;
    uVar19 = 0x20;
LAB_009564d0:
    log_internal::vlog(uVar10,"BTAudioA2dpSehAIDL",puVar14,pcVar16,uVar19,ppiVar20);
LAB_009564d4:
    local_270._0_4_ = 0x2aa;
    uStack_268 = 0x163cf7;
    uStack_264 = 0;
    local_260 = "setup_codec";
    local_c0 = (int *)0x0;
    log_internal::vlog(6,"BTAudioA2dpSehAIDL",&local_270,"Failed to get SehCodecConfiguration",0x23,
                       &local_c0);
    uVar6 = 0;
  }
  else {
    local_148 = DAT_0101f6d0;
    local_144 = DAT_0101f6d4;
    uStack_268 = 0;
    uStack_264 = 0;
    local_270._0_4_ = 0;
    local_270._4_1_ = '\0';
    local_270._5_1_ = '\0';
    local_270._6_2_ = 0;
    uStack_258 = 0;
    local_260 = (char *)0x0;
    uStack_248 = 0;
    local_250 = 0;
    uStack_238 = 0;
    local_240 = 0;
    A2dpCodecConfig::getCodecConfig(&local_270);
    if (5 < (int)local_270) {
      if ((int)local_270 < 0xd) {
        if ((int)local_270 == 6) {
          uVar9 = codec::A2dpOpusToHalConfig(&local_140,plVar8);
joined_r0x009566cc:
          if ((uVar9 & 1) == 0) goto LAB_009564d4;
          goto LAB_009566d0;
        }
        if ((int)local_270 == 8) {
          uVar9 = codec::A2dpSscToHalConfig(&local_140,plVar8);
          if ((uVar9 & 1) == 0) goto LAB_009564d4;
          uStack_8c = 0;
          uStack_88 = 0;
          uStack_90 = 0;
          uStack_a8 = 0;
          local_b0 = (char *)0x0;
          uStack_98 = 0;
          uStack_94 = 0;
          local_a0 = 0;
          pcStack_b8 = (code *)0x0;
          local_c0 = (int *)0x0;
          A2dpCodecConfig::getCodecSpecificConfig(plVar8,&local_c0);
          local_288 = (int *)CONCAT44(local_288._4_4_,0x13c);
          local_280 = (int **)0x163cf7;
          local_278 = "SscVendorGetTrackBitrateLimitation";
          local_e0 = uStack_a8 >> 0x10 & 0xff;
          local_298 = (code *)&local_e0;
          local_d8 = (char *)0x0;
          pcStack_d0 = (char *)0x6;
          local_2a0 = 1;
          local_290 = (int *)&DAT_00000006;
          log_internal::vlog(4,"BTAudioA2dpSehAIDL",&local_288,"0x{:x}",6,&local_2a0);
          bVar2 = uStack_a8._2_1_ != '\0';
          uStack_134 = CONCAT31(uStack_134._1_3_,bVar2);
          uVar10 = bta_av_co_get_current_codec((RawAddress *)&local_148);
          uStack_13c = codec::SscBitrateByBusyLevel(uVar10,DAT_01033b6c,bVar2);
          goto LAB_009566e0;
        }
      }
      else {
        if ((int)local_270 == 0xe) {
LAB_0095666c:
          uVar9 = codec::A2dpAacToHalConfig(&local_140,plVar8);
          goto joined_r0x009566cc;
        }
        if ((int)local_270 == 0xd) goto LAB_00956680;
      }
LAB_00956898:
      local_e0 = CONCAT44(local_e0._4_4_,0x184);
      local_d8 = 
      "packages/modules/Bluetooth/system/audio_hal_interface/seh_aidl/a2dp/a2dp_encoding_aidl.cc";
      pcStack_d0 = "a2dp_get_selected_hal_codec_config";
      local_c0 = (int *)&local_270;
      pcStack_b8 = 
      _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I23btav_a2dp_codec_index_tEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
      ;
      local_b0 = (char *)0xf;
      local_280 = &local_c0;
      pcVar16 = "Unknown codec_type={}";
      puVar14 = &local_e0;
      ppiVar20 = &local_288;
      uVar10 = 6;
      uVar19 = 0x15;
      local_288 = (int *)0x1;
      local_278 = (char *)0xf;
      goto LAB_009564d0;
    }
    if (1 < (int)local_270) {
      if ((int)local_270 - 2U < 2) {
        uVar9 = codec::A2dpAptxToHalConfig(&local_140,plVar8);
      }
      else {
        if ((int)local_270 != 4) goto LAB_00956898;
        uVar9 = codec::A2dpLdacToHalConfig(&local_140,plVar8);
      }
      if ((uVar9 & 1) != 0) {
LAB_009566d0:
        uStack_13c = (**(code **)(*plVar8 + 0x10))(plVar8);
        goto LAB_009566e0;
      }
      goto LAB_009564d4;
    }
    if ((int)local_270 != 0) {
      if ((int)local_270 == 1) goto LAB_0095666c;
      goto LAB_00956898;
    }
LAB_00956680:
    uVar9 = codec::A2dpSbcToHalConfig(&local_140,plVar8);
    if ((uVar9 & 1) == 0) goto LAB_009564d4;
    uStack_13c = codec::SbcBitrateByBusyLevel(&local_140,DAT_01033b6c);
LAB_009566e0:
    local_2b0 = 0;
    uStack_2a8 = 0;
    BtaAvCo::GetPeerEncoderParameters(&DAT_01014360,&local_148,&local_2b0);
    uVar6 = BtaAvCo::GetSourceEncoderEffectiveFrameSize(&DAT_01014360,&local_148);
    uStack_138 = uVar6;
    if (local_2b0._6_2_ <= uVar6) {
      uStack_138 = (uint)local_2b0._6_2_;
    }
    if ((int)uVar6 < 1) {
      uStack_138 = (uint)local_2b0._6_2_;
    }
    if ((int)local_270 == 0) {
      if ((int)local_e8 == 0) {
        if (0x23 < (int)uStack_118) goto LAB_00956748;
        uStack_138 = 0x297;
        goto LAB_00956758;
      }
      goto LAB_00956d68;
    }
LAB_00956748:
    if (0x3ed < uStack_138) {
      uStack_138 = 0x3ed;
    }
LAB_00956758:
    ::aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::toString();
    local_e0 = CONCAT44(local_e0._4_4_,0x19a);
    local_d8 = 
    "packages/modules/Bluetooth/system/audio_hal_interface/seh_aidl/a2dp/a2dp_encoding_aidl.cc";
    pcStack_d0 = "a2dp_get_selected_hal_codec_config";
    pcStack_b8 = local_298;
    local_c0 = local_290;
    if ((local_2a0 & 1) == 0) {
      pcStack_b8 = (code *)(local_2a0 >> 1 & 0x7f);
      local_c0 = (int *)((long)&local_2a0 + 1);
    }
    local_b0 = (char *)0xd;
    local_280 = &local_c0;
    local_288 = (int *)0x1;
    local_278 = (char *)0xd;
    log_internal::vlog(4,"BTAudioA2dpSehAIDL",&local_e0,"SehCodecConfiguration={}",0x18,&local_288);
    if ((local_2a0 & 1) != 0) {
      operator_delete(local_290,local_2a0 & 0xfffffffffffffffe);
    }
    uVar9 = local_128;
    iVar7 = DAT_010338a0;
    if (DAT_0101f898 == '\x01') {
      uVar15 = 0;
      uVar13 = 0x4000;
      if ((int)local_270 < 2) {
        if ((int)local_270 == 0) {
          if ((int)local_e8 != 0) {
LAB_00956d68:
            pcVar16 = 
            "auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::get() [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::Tag::sbcConfig]"
            ;
LAB_00956d78:
                    /* WARNING: Subroutine does not return */
            __assert2("out/soong/.intermediates/vendor/samsung/interfaces/bluetooth/audio/aidl/vendor.samsung.hardware.bluetooth.audio-V2-ndk-source/gen/include/aidl/vendor/samsung/hardware/bluetooth/audio/SehCodecConfiguration.h"
                      ,0xad,pcVar16,"bad access: a wrong tag");
          }
          uVar17 = local_120 & 0xff;
          uVar18 = (ulong)local_128._4_1_;
          uVar24 = (uint)local_120._4_1_;
          uVar6 = (uint)(byte)uStack_118;
          uVar15 = btif_av_is_carkit_on_active_device();
          if (((uVar15 & 1) == 0) && (0x297 < (int)uStack_138)) {
            if ((int)local_e8 != 0) goto LAB_00956d68;
            if (((int)uStack_118 < 0x24) ||
               (uVar15 = a2dp_sbc_is_avoid_scalable(), (uVar15 & 1) != 0)) goto LAB_00956a00;
            uVar22 = 1;
          }
          else {
LAB_00956a00:
            uVar22 = 0;
          }
          uVar21 = 0;
          uVar13 = 0;
          uVar15 = uVar9 & 0xffffffff;
        }
        else {
          uVar17 = 0;
          uVar18 = 0;
          uVar21 = 0;
          uVar24 = 0;
          uVar22 = 0;
          uVar6 = uVar24;
          if ((int)local_270 == 1) {
            if ((int)local_e8 != 1) {
              pcVar16 = 
              "auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::get() [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::Tag::aacConfig]"
              ;
              goto LAB_00956d78;
            }
            uVar15 = local_128 >> 0x20;
            uVar17 = local_120 >> 0x10 & 0xff;
            uVar21 = 0;
            uVar18 = local_120 & 0xff;
            uVar24 = 0;
            uVar6 = 0;
            uVar13 = 2;
            uVar22 = 1;
          }
        }
      }
      else if ((int)local_270 == 2) {
        if ((int)local_e8 != 3) {
          pcVar16 = 
          "auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::get() [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::Tag::aptxConfig]"
          ;
          goto LAB_00956d78;
        }
        uVar15 = local_128 & 0xffffffff;
        uVar17 = (ulong)local_128._5_1_;
        uVar21 = 0;
        uVar18 = (ulong)local_128._4_1_;
        uVar24 = 0;
        uVar22 = 0;
        uVar13 = 8;
        uVar6 = 0;
      }
      else if ((int)local_270 == 4) {
        if ((int)local_e8 != 2) {
          pcVar16 = 
          "auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::get() [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::Tag::ldacConfig]"
          ;
          goto LAB_00956d78;
        }
        uVar15 = local_128 & 0xffffffff;
        uVar18 = (ulong)local_128._4_1_;
        uVar17 = 0;
        uVar21 = (ulong)local_128._5_1_;
        uVar24 = 0;
        uVar22 = 1;
        uVar13 = 0x40;
        uVar6 = 0;
      }
      else {
        uVar17 = 0;
        uVar18 = 0;
        uVar21 = 0;
        uVar24 = 0;
        uVar22 = 0;
        uVar6 = 0;
        if ((int)local_270 == 8) {
          if ((int)local_e8 != 6) {
            pcVar16 = 
            "auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::get() [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::Tag::sscConfig]"
            ;
            goto LAB_00956d78;
          }
          uVar17 = (ulong)local_128._5_1_;
          uVar18 = (ulong)local_128._4_1_;
          uVar6 = bta_av_co_get_current_codec((RawAddress *)&local_148);
          uVar15 = uVar9 & 0xffffffff;
          uVar13 = (ulong)uVar6;
          uVar21 = 0;
          uVar24 = 0;
          uVar22 = (uint)(uVar6 != 0x200);
          uVar6 = 0;
        }
      }
      if (iVar7 != 2) {
        iVar7 = 0;
      }
      btif_av_big_data_report
                ("{\"OMCC\":\"01%08x%08x%08x%08x%08x%08x%02x%02x%02x%02x%02x%02x\"}",uVar13,uVar15,
                 uVar17,uVar18,(ulong)uStack_13c,(ulong)uStack_138,uVar21,uVar24,uVar6,0,iVar7,
                 uVar22);
    }
    bVar3 = codec::IsCodecOffloadingEnabled(&local_140);
    iVar7 = DAT_010338a0;
    uVar9 = logging::ShouldCreateLogMessage(0);
    if ((uVar9 & 1) != 0) {
      logging::LogMessage::LogMessage
                ((LogMessage *)&local_270,
                 "packages/modules/Bluetooth/system/audio_hal_interface/seh_aidl/a2dp/a2dp_encoding_aidl.cc"
                 ,0x2b5,0);
      poVar11 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                          ((ostream *)&uStack_268,"setup_codec",0xb);
      poVar11 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                          (poVar11,": offload mode - ",0x11);
      poVar11 = (ostream *)std::ostream::operator<<(poVar11,iVar7 == 2);
      poVar11 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                          (poVar11," should_codec_offloading = ",0x1b);
      std::ostream::operator<<(poVar11,(bool)(bVar3 & 1));
      logging::LogMessage::~LogMessage((LogMessage *)&local_270);
    }
    if (iVar7 == 2 && ((bVar3 ^ 0xff) & 1) == 0) {
      local_270._0_4_ = 0x2b7;
      uStack_268 = 0x163cf7;
      uStack_264 = 0;
      local_260 = "setup_codec";
      local_c0 = (int *)0x0;
      log_internal::vlog(5,"BTAudioA2dpSehAIDL",&local_270,
                         "Switching BluetoothAudio HAL to Hardware",0x28,&local_c0);
      plVar8 = &DAT_01033b60;
    }
    else {
      local_270._0_4_ = 699;
      uStack_268 = 0x163cf7;
      uStack_264 = 0;
      local_260 = "setup_codec";
      local_c0 = (int *)0x0;
      log_internal::vlog(5,"BTAudioA2dpSehAIDL",&local_270,
                         "Switching BluetoothAudio HAL to Software",0x28,&local_c0);
      plVar8 = &DAT_01033b58;
    }
    DAT_01033b50 = *plVar8;
    uStack_258 = 0;
    local_260 = (char *)0x0;
    uStack_248 = 0;
    local_250 = 0;
    uStack_238 = 0;
    local_240 = 0;
    uStack_228 = 0;
    uStack_230 = 0;
    uStack_218 = 0;
    local_220 = 0;
    local_208 = 0;
    uStack_210 = 0;
    uStack_268 = 0;
    uStack_264 = 0;
    local_270._0_4_ = 0;
    local_270._4_1_ = '\0';
    local_270._5_1_ = '\0';
    local_270._6_2_ = 0;
    if (*(char *)(*(long *)(DAT_01033b50 + 0x68) + 8) == '\x02') {
      iVar7 = (int)local_e8;
      uStack_258 = 0;
      local_270._0_4_ = local_140;
      local_270._4_1_ = (char)uStack_13c;
      local_270._5_1_ = (char)(uStack_13c >> 8);
      local_270._6_2_ = (undefined2)(uStack_13c >> 0x10);
      uStack_268 = uStack_138;
      uStack_264 = uStack_134 & 0xff;
      local_208 = 0xffffffff;
      uStack_218 = 0xffffffff;
      if ((int)local_e8 != -1) {
        local_c0 = (int *)&uStack_258;
        (*(code *)(&
                  PTR___dispatch_abi_nn220000_<std::__variant_detail::__ctor<std::__variant_detail::__traits<aidl::vendor::samsung::hardware::bluetooth::audio::SehSbcConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehAacConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehLdacConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehAptxConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehAptxAdaptiveConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehLc3Configuration,aidl::vendor::samsung::hardware::bluetooth::audio::SehSscConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::VendorConfiguration,std::optional<aidl::vendor::samsung::hardware::bluetooth::audio::SehOpusConfiguration>>>::__generic_construct[abi:nn220000]<std::__variant_detail::__copy_constructor<std::__variant_detail::__traits<aidl::vendor::samsung::hardware::bluetooth::audio::SehSbcConfiguration,aidl::vendor::samsung::hardware::bluetooth___ation,std::optional<aidl::vendor::samsung::hardware::bluetooth::audio::SehOpusConfiguration>>const&>_00f9e910
                  )[local_e8 & 0xffffffff])(&local_c0,&local_128);
        uStack_218 = CONCAT44(uStack_218._4_4_,iVar7);
      }
      uVar23 = 1;
LAB_00956bf0:
      local_208 = CONCAT44(local_208._4_4_,uVar23);
      uVar6 = BluetoothAudioClientInterface::UpdateAudioConfig(DAT_01033b50,&local_270);
    }
    else {
      lVar12 = BtaAvCo::GetActivePeerCurrentCodec(&DAT_01014360);
      if (lVar12 == 0) {
        local_c0 = (int *)CONCAT44(local_c0._4_4_,0x1e1);
        pcStack_b8 = (code *)0x163cf7;
        local_b0 = "a2dp_get_selected_hal_pcm_config";
        local_e0 = 0;
        log_internal::vlog(5,"BTAudioA2dpSehAIDL",&local_c0,"failure to get A2DP codec config",0x20,
                           &local_e0);
      }
      else {
        pcStack_b8 = (code *)0x0;
        local_c0 = (int *)0x0;
        uStack_a8 = 0;
        local_b0 = (char *)0x0;
        uStack_98 = 0;
        uStack_94 = 0;
        local_a0 = 0;
        uStack_88 = 0;
        uStack_84 = 0;
        uStack_90 = 0;
        uStack_8c = 0;
        A2dpCodecConfig::getCodecConfig(&local_c0);
        iVar7 = codec::A2dpCodecToHalSampleRate(&local_c0);
        cVar4 = codec::A2dpCodecToHalBitsPerSample(&local_c0);
        cVar5 = codec::A2dpCodecToHalChannelMode(&local_c0);
        if (((0 < iVar7) && ('\0' < cVar4)) && (cVar5 != '\0')) {
          if ((int)local_208 != -1) {
            (*(code *)(&
                      PTR___dispatch_abi_nn220000_<std::__variant_detail::__dtor<std::__variant_detail::__traits<aidl::vendor::samsung::hardware::bluetooth::audio::SehPcmConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehLeAudioConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehLeAudioBroadcastConfiguration>,(std::__variant_detail::_Trait)1>::__destroy[abi:nn220000]()::_lambda(auto:1&)_1_&&,std::__variant_detail::__base<(std::__variant_detail::_Trait)1,aidl::vendor::samsung::hardware::bluetooth::audio::SehPcmConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehLeAudioConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehLeAudioBroadcastConfiguration>&>_00f9e890
                      )[local_208 & 0xffffffff])(&local_c0,&local_270);
          }
          uVar23 = 0;
          local_270._6_2_ = 0;
          uStack_268 = 0;
          local_270._0_4_ = iVar7;
          local_270._4_1_ = cVar5;
          local_270._5_1_ = cVar4;
          goto LAB_00956bf0;
        }
      }
      local_c0 = (int *)CONCAT44(local_c0._4_4_,0x2c7);
      pcStack_b8 = (code *)0x163cf7;
      local_b0 = "setup_codec";
      local_e0 = 0;
      log_internal::vlog(6,"BTAudioA2dpSehAIDL",&local_c0,"Failed to get SehPcmConfiguration",0x21,
                         &local_e0);
      uVar6 = 0;
    }
    if ((int)local_208 != -1) {
      (*(code *)(&
                PTR___dispatch_abi_nn220000_<std::__variant_detail::__dtor<std::__variant_detail::__traits<aidl::vendor::samsung::hardware::bluetooth::audio::SehPcmConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehLeAudioConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehLeAudioBroadcastConfiguration>,(std::__variant_detail::_Trait)1>::__destroy[abi:nn220000]()::_lambda(auto:1&)_1_&&,std::__variant_detail::__base<(std::__variant_detail::_Trait)1,aidl::vendor::samsung::hardware::bluetooth::audio::SehPcmConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehLeAudioConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehLeAudioBroadcastConfiguration>&>_00f9e890
                )[local_208 & 0xffffffff])(&local_c0,&local_270);
    }
  }
  if ((int)local_e8 != -1) {
    (*(code *)(&
              PTR___dispatch_abi_nn220000_<std::__variant_detail::__dtor<std::__variant_detail::__traits<aidl::vendor::samsung::hardware::bluetooth::audio::SehSbcConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehAacConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehLdacConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehAptxConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehAptxAdaptiveConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehLc3Configuration,aidl::vendor::samsung::hardware::bluetooth::audio::SehSscConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::VendorConfiguration,std::optional<aidl::vendor::samsung::hardware::bluetooth::audio::SehOpusConfiguration>>,(std::__variant_detail::_Trait)1>::__destroy[abi:nn220000]()::_lambda(auto:1&)_1_&&,std::__variant_detail::__base<(std::__variant_detail::_Trait)1,aidl::vendor::samsung::hardware::bluetooth::audio::SehSbcConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehAacConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehLdacConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehAptxConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehAptxAdaptiveConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehLc3Configuration,aidl::vendor::samsung::hardware::bluetooth::audio::SehSscConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::VendorConfiguration,std::optional<aidl::vendor::samsung::hardware::bluetooth::audio::SehOpusConfiguration>>&>_00f9e8c8
              )[local_e8 & 0xffffffff])(&local_270,&local_128);
  }
LAB_00956540:
  if (*(long *)(lVar1 + 0x28) != local_78) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar6 & 1;
}


/* ==== toString @ 0095915c size 1176 :: , isScmstEnabled:  */

/* aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::toString() const */

void aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::toString(void)

{
  char *pcVar1;
  long lVar2;
  bool bVar3;
  internal *in_x0;
  ostream *poVar4;
  SehCodecType *extraout_x1;
  void *__src;
  ulong *in_x8;
  ulong uVar5;
  long *plVar6;
  undefined8 *in_x18;
  undefined1 *__dest;
  size_t sVar7;
  undefined8 unaff_x30;
  byte local_190;
  undefined7 uStack_18f;
  ulong local_188;
  char *local_180;
  undefined **local_178;
  undefined **local_170;
  undefined8 uStack_168;
  long local_160 [8];
  void *local_120;
  ulong local_118;
  undefined8 local_110;
  undefined **ppuStack_108;
  undefined8 local_100;
  undefined8 uStack_f8;
  undefined8 local_f0;
  undefined8 uStack_e8;
  undefined8 local_e0;
  undefined8 uStack_d8;
  undefined8 local_d0;
  undefined8 uStack_c8;
  undefined8 local_c0;
  undefined8 uStack_b8;
  undefined8 local_b0;
  undefined8 uStack_a8;
  undefined8 local_a0;
  undefined8 uStack_98;
  undefined8 local_90;
  undefined8 uStack_88;
  undefined8 local_80;
  undefined8 uStack_78;
  long local_70;
  
  *in_x18 = unaff_x30;
  lVar2 = tpidr_el0;
  local_70 = *(long *)(lVar2 + 0x28);
  local_110 = 0;
  uStack_78 = 0;
  local_80 = 0;
  uStack_88 = 0;
  local_90 = 0;
  uStack_98 = 0;
  local_a0 = 0;
  uStack_a8 = 0;
  local_b0 = 0;
  uStack_b8 = 0;
  local_c0 = 0;
  uStack_c8 = 0;
  local_d0 = 0;
  uStack_d8 = 0;
  local_e0 = 0;
  uStack_e8 = 0;
  local_f0 = 0;
  uStack_f8 = 0;
  local_100 = 0;
  local_160[7] = 0;
  local_160[6] = 0;
  local_118 = 0;
  local_120 = (void *)0x0;
  local_160[5] = 0;
  local_160[4] = 0;
  local_160[1] = 0;
  local_160[0] = 0;
  local_160[3] = 0;
  local_160[2] = 0;
  uStack_168 = 0;
  local_170 = (undefined **)0x0;
  local_178 = &PTR__ostream_00f68c08;
  ppuStack_108 = &PTR__ostream_00f68c30;
  std::ios_base::init((ios_base *)&ppuStack_108,&local_170);
  local_80 = 0;
                    /* WARNING: Ignoring partial resolution of indirect */
  uStack_78._0_4_ = 0xffffffff;
  local_178 = &PTR__ostringstream_00f68b98;
  local_170 = &PTR__streambuf_00f68750;
  ppuStack_108 = &PTR__ostringstream_00f68bc0;
  std::locale::locale((locale *)&uStack_168);
  local_160[5] = 0;
  local_160[4] = 0;
  local_160[1] = 0;
  local_160[0] = 0;
  local_160[3] = 0;
  local_160[2] = 0;
  local_160[7] = 0;
  local_160[6] = 0;
  local_118 = 0;
  local_120 = (void *)0x0;
  local_170 = &PTR__stringbuf_00f687d0;
  local_110 = CONCAT44(local_110._4_4_,0x10);
  std::stringbuf::__init_buf_ptrs_abi_nn220000_((stringbuf *)&local_170);
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
            ((ostream *)&local_178,"SehCodecConfiguration{",0x16);
  poVar4 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                     ((ostream *)&local_178,"codecType: ",0xb);
  ::android::internal::ToString<aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecType>
            (in_x0,extraout_x1);
  uVar5 = local_188;
  pcVar1 = local_180;
  if ((local_190 & 1) == 0) {
    uVar5 = (ulong)(local_190 >> 1);
    pcVar1 = (char *)&uStack_18f;
  }
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>(poVar4,pcVar1,uVar5);
  if ((local_190 & 1) != 0) {
    operator_delete(local_180,CONCAT71(uStack_18f,local_190) & 0xfffffffffffffffe);
  }
  poVar4 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                     ((ostream *)&local_178,", encodedAudioBitrate: ",0x17);
  std::to_string(*(int *)(in_x0 + 4));
  uVar5 = local_188;
  pcVar1 = local_180;
  if ((local_190 & 1) == 0) {
    uVar5 = (ulong)(local_190 >> 1);
    pcVar1 = (char *)&uStack_18f;
  }
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>(poVar4,pcVar1,uVar5);
  if ((local_190 & 1) != 0) {
    operator_delete(local_180,CONCAT71(uStack_18f,local_190) & 0xfffffffffffffffe);
  }
  poVar4 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                     ((ostream *)&local_178,", peerMtu: ",0xb);
  std::to_string(*(int *)(in_x0 + 8));
  uVar5 = local_188;
  pcVar1 = local_180;
  if ((local_190 & 1) == 0) {
    uVar5 = (ulong)(local_190 >> 1);
    pcVar1 = (char *)&uStack_18f;
  }
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>(poVar4,pcVar1,uVar5);
  if ((local_190 & 1) != 0) {
    operator_delete(local_180,CONCAT71(uStack_18f,local_190) & 0xfffffffffffffffe);
  }
  poVar4 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                     ((ostream *)&local_178,", isScmstEnabled: ",0x12);
  bVar3 = in_x0[0xc] == (internal)0x0;
  sVar7 = 4;
  if (bVar3) {
    sVar7 = 5;
  }
  local_190 = (byte)((int)sVar7 << 1);
  pcVar1 = "true";
  if (bVar3) {
    pcVar1 = "f";
  }
  uVar5 = 5;
  if (bVar3) {
    uVar5 = 6;
  }
  memcpy((void *)((ulong)&local_190 | 1),pcVar1,sVar7);
  *(undefined1 *)((ulong)&local_190 | uVar5) = 0;
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
            (poVar4,(char *)((ulong)&local_190 | 1),sVar7);
  if ((local_190 & 1) != 0) {
    operator_delete(local_180,CONCAT71(uStack_18f,local_190) & 0xfffffffffffffffe);
  }
  poVar4 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                     ((ostream *)&local_178,", config: ",10);
  CodecSpecific::toString();
  pcVar1 = local_180;
  if ((local_190 & 1) == 0) {
    local_188 = (ulong)(local_190 >> 1);
    pcVar1 = (char *)&uStack_18f;
  }
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>(poVar4,pcVar1,local_188);
  if ((local_190 & 1) != 0) {
    operator_delete(local_180,CONCAT71(uStack_18f,local_190) & 0xfffffffffffffffe);
  }
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
            ((ostream *)&local_178,"}",1);
  if (((uint)local_110 >> 4 & 1) == 0) {
    if (((uint)local_110 >> 3 & 1) != 0) {
      plVar6 = local_160;
      uVar5 = local_160[2];
      goto LAB_009594ec;
    }
    __src = (void *)0x0;
    sVar7 = 0;
  }
  else {
    if (local_118 < (ulong)local_160[4]) {
      local_118 = local_160[4];
    }
    plVar6 = local_160 + 3;
    uVar5 = local_118;
LAB_009594ec:
    __src = (void *)*plVar6;
    sVar7 = uVar5 - (long)__src;
    if (0xfffffffffffffff6 < sVar7) {
                    /* WARNING: Subroutine does not return */
      std::string::__throw_length_error_abi_nn220000_();
    }
    if (0x16 < sVar7) {
      uVar5 = 0x1a;
      if ((sVar7 | 7) != 0x17) {
        uVar5 = (sVar7 | 7) + 1;
      }
      __dest = (undefined1 *)FUN_00f62c00(uVar5);
      in_x8[1] = sVar7;
      in_x8[2] = (ulong)__dest;
      *in_x8 = uVar5 | 1;
      goto LAB_00959540;
    }
  }
  __dest = (undefined1 *)((long)in_x8 + 1);
  *(char *)in_x8 = (char)((int)sVar7 << 1);
LAB_00959540:
  memmove(__dest,__src,sVar7);
  local_178 = &PTR__ostringstream_00f68b98;
  __dest[sVar7] = 0;
  ppuStack_108 = &PTR__ostringstream_00f68bc0;
  local_170 = &PTR__stringbuf_00f687d0;
  if ((local_160[6] & 1U) != 0) {
    operator_delete(local_120,local_160[6] & 0xfffffffffffffffe);
  }
  local_170 = &PTR__streambuf_00f68750;
  std::locale::~locale((locale *)&uStack_168);
  std::ostream::~ostream((ostream *)&local_178);
  std::ios::~ios((ios *)&ppuStack_108);
  if (*(long *)(lVar2 + 0x28) == local_70) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== toString @ 0095979c size 1500 :: const auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::get() const [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::Tag::sscConfig] | sscConfig:  */

/* aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::toString()
   const */

void aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::
     toString(void)

{
  int iVar1;
  long lVar2;
  long in_x0;
  ostream *poVar3;
  optional *extraout_x1;
  void *__src;
  char *pcVar4;
  ulong *in_x8;
  ulong uVar5;
  long *plVar6;
  undefined8 *in_x18;
  undefined1 *__dest;
  size_t __n;
  undefined8 unaff_x30;
  byte local_188;
  undefined7 uStack_187;
  ulong local_180;
  char *local_178;
  undefined **local_170;
  undefined **local_168;
  undefined8 uStack_160;
  long local_158 [8];
  void *local_118;
  ulong uStack_110;
  undefined8 local_108;
  undefined **ppuStack_100;
  undefined8 local_f8;
  undefined8 uStack_f0;
  undefined8 local_e8;
  undefined8 uStack_e0;
  undefined8 local_d8;
  undefined8 uStack_d0;
  undefined8 local_c8;
  undefined8 uStack_c0;
  undefined8 local_b8;
  undefined8 uStack_b0;
  undefined8 local_a8;
  undefined8 uStack_a0;
  undefined8 local_98;
  undefined8 uStack_90;
  undefined8 local_88;
  undefined8 uStack_80;
  undefined8 local_78;
  undefined8 uStack_70;
  long local_68;
  
  *in_x18 = unaff_x30;
  lVar2 = tpidr_el0;
  local_68 = *(long *)(lVar2 + 0x28);
  local_108 = 0;
  uStack_70 = 0;
  local_78 = 0;
  uStack_80 = 0;
  local_88 = 0;
  uStack_90 = 0;
  local_98 = 0;
  uStack_a0 = 0;
  local_a8 = 0;
  uStack_b0 = 0;
  local_b8 = 0;
  uStack_c0 = 0;
  local_c8 = 0;
  uStack_d0 = 0;
  local_d8 = 0;
  uStack_e0 = 0;
  local_e8 = 0;
  uStack_f0 = 0;
  local_f8 = 0;
  uStack_110 = 0;
  local_118 = (void *)0x0;
  local_158[7] = 0;
  local_158[6] = 0;
  local_158[5] = 0;
  local_158[4] = 0;
  local_158[3] = 0;
  local_158[2] = 0;
  local_158[1] = 0;
  local_158[0] = 0;
  local_170 = &PTR__ostream_00f68c08;
  uStack_160 = 0;
  local_168 = (undefined **)0x0;
  ppuStack_100 = &PTR__ostream_00f68c30;
  std::ios_base::init((ios_base *)&ppuStack_100,&local_168);
  local_78 = 0;
                    /* WARNING: Ignoring partial resolution of indirect */
  uStack_70._0_4_ = 0xffffffff;
  local_170 = &PTR__ostringstream_00f68b98;
  local_168 = &PTR__streambuf_00f68750;
  ppuStack_100 = &PTR__ostringstream_00f68bc0;
  std::locale::locale((locale *)&uStack_160);
  local_158[5] = 0;
  local_158[4] = 0;
  local_158[3] = 0;
  local_158[2] = 0;
  local_158[1] = 0;
  local_158[0] = 0;
  local_168 = &PTR__stringbuf_00f687d0;
  local_158[7] = 0;
  local_158[6] = 0;
  uStack_110 = 0;
  local_118 = (void *)0x0;
  local_108 = CONCAT44(local_108._4_4_,0x10);
  std::stringbuf::__init_buf_ptrs_abi_nn220000_((stringbuf *)&local_168);
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
            ((ostream *)&local_170,"CodecSpecific{",0xe);
  iVar1 = *(int *)(in_x0 + 0x48);
  if (iVar1 < 4) {
    if (1 < iVar1) {
      if (iVar1 == 2) {
        poVar3 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                           ((ostream *)&local_170,"ldacConfig: ",0xc);
        if (*(int *)(in_x0 + 0x48) != 2) {
          pcVar4 = 
          "const auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::get() const [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::Tag::ldacConfig]"
          ;
          goto LAB_00959d68;
        }
        SehLdacConfiguration::toString();
      }
      else {
        if (iVar1 != 3) goto LAB_00959b60;
        poVar3 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                           ((ostream *)&local_170,"aptxConfig: ",0xc);
        if (*(int *)(in_x0 + 0x48) != 3) {
          pcVar4 = 
          "const auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::get() const [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::Tag::aptxConfig]"
          ;
          goto LAB_00959d68;
        }
        SehAptxConfiguration::toString();
      }
      goto LAB_00959b28;
    }
    if (iVar1 == 0) {
      poVar3 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                         ((ostream *)&local_170,"sbcConfig: ",0xb);
      if (*(int *)(in_x0 + 0x48) != 0) {
        pcVar4 = 
        "const auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::get() const [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::Tag::sbcConfig]"
        ;
        goto LAB_00959d68;
      }
      SehSbcConfiguration::toString();
      goto LAB_00959b28;
    }
    if (iVar1 == 1) {
      poVar3 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                         ((ostream *)&local_170,"aacConfig: ",0xb);
      if (*(int *)(in_x0 + 0x48) != 1) {
        pcVar4 = 
        "const auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::get() const [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::Tag::aacConfig]"
        ;
        goto LAB_00959d68;
      }
      SehAacConfiguration::toString();
      goto LAB_00959b28;
    }
  }
  else {
    if (iVar1 < 6) {
      if (iVar1 == 4) {
        poVar3 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                           ((ostream *)&local_170,"aptxAdaptiveConfig: ",0x14);
        if (*(int *)(in_x0 + 0x48) != 4) {
          pcVar4 = 
          "const auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::get() const [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::Tag::aptxAdaptiveConfig]"
          ;
          goto LAB_00959d68;
        }
        SehAptxAdaptiveConfiguration::toString();
      }
      else {
        if (iVar1 != 5) goto LAB_00959b60;
        poVar3 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                           ((ostream *)&local_170,"lc3Config: ",0xb);
        if (*(int *)(in_x0 + 0x48) != 5) {
          pcVar4 = 
          "const auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::get() const [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::Tag::lc3Config]"
          ;
          goto LAB_00959d68;
        }
        SehLc3Configuration::toString();
      }
    }
    else if (iVar1 == 6) {
      poVar3 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                         ((ostream *)&local_170,"sscConfig: ",0xb);
      if (*(int *)(in_x0 + 0x48) != 6) {
        pcVar4 = 
        "const auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::get() const [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::Tag::sscConfig]"
        ;
LAB_00959d68:
                    /* WARNING: Subroutine does not return */
        __assert2("out/soong/.intermediates/vendor/samsung/interfaces/bluetooth/audio/aidl/vendor.samsung.hardware.bluetooth.audio-V2-ndk-source/gen/include/aidl/vendor/samsung/hardware/bluetooth/audio/SehCodecConfiguration.h"
                  ,0xa7,pcVar4,"bad access: a wrong tag");
      }
      SehSscConfiguration::toString();
    }
    else if (iVar1 == 7) {
      poVar3 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                         ((ostream *)&local_170,"vendorConfig: ",0xe);
      if (*(int *)(in_x0 + 0x48) != 7) {
        pcVar4 = 
        "const auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::get() const [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::Tag::vendorConfig]"
        ;
        goto LAB_00959d68;
      }
      android::hardware::bluetooth::audio::CodecConfiguration::VendorConfiguration::toString();
    }
    else {
      if (iVar1 != 8) goto LAB_00959b60;
      poVar3 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                         ((ostream *)&local_170,"opusConfig: ",0xc);
      if (*(int *)(in_x0 + 0x48) != 8) {
        pcVar4 = 
        "const auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::get() const [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::Tag::opusConfig]"
        ;
        goto LAB_00959d68;
      }
      ::android::internal::
      ToString<std::optional<aidl::vendor::samsung::hardware::bluetooth::audio::SehOpusConfiguration>>
                ((internal *)(in_x0 + 8),extraout_x1);
    }
LAB_00959b28:
    pcVar4 = local_178;
    if ((local_188 & 1) == 0) {
      local_180 = (ulong)(local_188 >> 1);
      pcVar4 = (char *)&uStack_187;
    }
    std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
              (poVar3,pcVar4,local_180);
    if ((local_188 & 1) != 0) {
      operator_delete(local_178,CONCAT71(uStack_187,local_188) & 0xfffffffffffffffe);
    }
  }
LAB_00959b60:
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
            ((ostream *)&local_170,"}",1);
  if (((uint)local_108 >> 4 & 1) == 0) {
    if (((uint)local_108 >> 3 & 1) != 0) {
      plVar6 = local_158;
      uVar5 = local_158[2];
      goto LAB_00959bb8;
    }
    __src = (void *)0x0;
    __n = 0;
  }
  else {
    if (uStack_110 < (ulong)local_158[4]) {
      uStack_110 = local_158[4];
    }
    plVar6 = local_158 + 3;
    uVar5 = uStack_110;
LAB_00959bb8:
    __src = (void *)*plVar6;
    __n = uVar5 - (long)__src;
    if (0xfffffffffffffff6 < __n) {
                    /* WARNING: Subroutine does not return */
      std::string::__throw_length_error_abi_nn220000_();
    }
    if (0x16 < __n) {
      uVar5 = 0x1a;
      if ((__n | 7) != 0x17) {
        uVar5 = (__n | 7) + 1;
      }
      __dest = (undefined1 *)FUN_00f62c00(uVar5);
      in_x8[1] = __n;
      in_x8[2] = (ulong)__dest;
      *in_x8 = uVar5 | 1;
      goto LAB_00959c0c;
    }
  }
  __dest = (undefined1 *)((long)in_x8 + 1);
  *(char *)in_x8 = (char)((int)__n << 1);
LAB_00959c0c:
  memmove(__dest,__src,__n);
  local_170 = &PTR__ostringstream_00f68b98;
  __dest[__n] = 0;
  ppuStack_100 = &PTR__ostringstream_00f68bc0;
  local_168 = &PTR__stringbuf_00f687d0;
  if ((local_158[6] & 1U) != 0) {
    operator_delete(local_118,local_158[6] & 0xfffffffffffffffe);
  }
  local_168 = &PTR__streambuf_00f68750;
  std::locale::~locale((locale *)&uStack_160);
  std::ostream::~ostream((ostream *)&local_170);
  std::ios::~ios((ios *)&ppuStack_100);
  if (*(long *)(lVar2 + 0x28) == local_68) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== toString @ 0095cf04 size 1140 :: SehSscConfiguration{ */

/* aidl::vendor::samsung::hardware::bluetooth::audio::SehSscConfiguration::toString() const */

void aidl::vendor::samsung::hardware::bluetooth::audio::SehSscConfiguration::toString(void)

{
  ulong uVar1;
  byte bVar2;
  long lVar3;
  int *in_x0;
  ostream *poVar4;
  void *__src;
  ulong *in_x8;
  ulong uVar5;
  char *pcVar6;
  long *plVar7;
  undefined8 *in_x18;
  undefined1 *__dest;
  size_t __n;
  undefined8 unaff_x30;
  undefined4 local_188;
  undefined1 uStack_184;
  undefined1 uStack_183;
  undefined1 uStack_182;
  undefined1 uStack_181;
  undefined1 local_180;
  undefined1 uStack_17f;
  undefined6 uStack_17e;
  char *local_178;
  undefined **local_170;
  undefined **local_168;
  undefined8 uStack_160;
  long local_158 [8];
  void *local_118;
  ulong uStack_110;
  undefined8 local_108;
  undefined **ppuStack_100;
  undefined8 local_f8;
  undefined8 uStack_f0;
  undefined8 local_e8;
  undefined8 uStack_e0;
  undefined8 local_d8;
  undefined8 uStack_d0;
  undefined8 local_c8;
  undefined8 uStack_c0;
  undefined8 local_b8;
  undefined8 uStack_b0;
  undefined8 local_a8;
  undefined8 uStack_a0;
  undefined8 local_98;
  undefined8 uStack_90;
  undefined8 local_88;
  undefined8 uStack_80;
  undefined8 local_78;
  undefined8 uStack_70;
  long local_68;
  
  *in_x18 = unaff_x30;
  lVar3 = tpidr_el0;
  local_68 = *(long *)(lVar3 + 0x28);
  local_108 = 0;
  uStack_70 = 0;
  local_78 = 0;
  uStack_80 = 0;
  local_88 = 0;
  uStack_90 = 0;
  local_98 = 0;
  uStack_a0 = 0;
  local_a8 = 0;
  uStack_b0 = 0;
  local_b8 = 0;
  uStack_c0 = 0;
  local_c8 = 0;
  uStack_d0 = 0;
  local_d8 = 0;
  uStack_e0 = 0;
  local_e8 = 0;
  uStack_f0 = 0;
  local_f8 = 0;
  uStack_110 = 0;
  local_118 = (void *)0x0;
  local_158[7] = 0;
  local_158[6] = 0;
  local_158[5] = 0;
  local_158[4] = 0;
  local_158[3] = 0;
  local_158[2] = 0;
  local_158[1] = 0;
  local_158[0] = 0;
  local_170 = &PTR__ostream_00f68c08;
  uStack_160 = 0;
  local_168 = (undefined **)0x0;
  ppuStack_100 = &PTR__ostream_00f68c30;
  std::ios_base::init((ios_base *)&ppuStack_100,&local_168);
  local_78 = 0;
                    /* WARNING: Ignoring partial resolution of indirect */
  uStack_70._0_4_ = 0xffffffff;
  local_170 = &PTR__ostringstream_00f68b98;
  local_168 = &PTR__streambuf_00f68750;
  ppuStack_100 = &PTR__ostringstream_00f68bc0;
  std::locale::locale((locale *)&uStack_160);
  local_158[5] = 0;
  local_158[4] = 0;
  local_158[3] = 0;
  local_158[2] = 0;
  local_158[1] = 0;
  local_158[0] = 0;
  local_168 = &PTR__stringbuf_00f687d0;
  local_158[7] = 0;
  local_158[6] = 0;
  uStack_110 = 0;
  local_118 = (void *)0x0;
  local_108 = CONCAT44(local_108._4_4_,0x10);
  std::stringbuf::__init_buf_ptrs_abi_nn220000_((stringbuf *)&local_168);
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
            ((ostream *)&local_170,"SehSscConfiguration{",0x14);
  poVar4 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                     ((ostream *)&local_170,"sampleRateHz: ",0xe);
  std::to_string(*in_x0);
  uVar5 = CONCAT62(uStack_17e,CONCAT11(uStack_17f,local_180));
  pcVar6 = local_178;
  if ((local_188 & 1) == 0) {
    uVar5 = (ulong)((byte)local_188 >> 1);
    pcVar6 = (char *)((long)&local_188 + 1);
  }
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>(poVar4,pcVar6,uVar5);
  if ((local_188 & 1) != 0) {
    operator_delete(local_178,
                    CONCAT17(uStack_181,
                             CONCAT16(uStack_182,CONCAT15(uStack_183,CONCAT14(uStack_184,local_188))
                                     )) & 0xfffffffffffffffe);
  }
  poVar4 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                     ((ostream *)&local_170,", channelMode: ",0xf);
  bVar2 = *(byte *)(in_x0 + 1);
  if (bVar2 < 2) {
    if (bVar2 == 0) {
      uVar5 = 0xe;
      pcVar6 = (char *)0x4e4b4e55;
      local_188 = 0x4b4e550e;
      uStack_184 = 0x4e;
      uStack_183 = 0x4f;
      uStack_182 = 0x57;
      uStack_181 = 0x4e;
      local_180 = 0;
    }
    else if (bVar2 == 1) {
      uVar5 = 8;
      uStack_183 = 0;
      local_188 = 0x4e4f4d08;
      uStack_184 = 0x4f;
      pcVar6 = (char *)0x4f4e4f4d;
    }
    else {
LAB_0095d120:
      std::to_string((int)(char)bVar2);
      uVar5 = (ulong)(byte)local_188;
      pcVar6 = local_178;
    }
  }
  else if (bVar2 == 2) {
    uVar5 = 0xc;
    pcVar6 = (char *)0x52455453;
    local_188 = 0x4554530c;
    uStack_184 = 0x52;
    uStack_183 = 0x45;
    uStack_182 = 0x4f;
    uStack_181 = 0;
  }
  else {
    if (bVar2 != 3) goto LAB_0095d120;
    uVar5 = 0x10;
    uStack_17f = 0;
    pcVar6 = (char *)0x4f4e4f4d4c415544;
    local_188 = 0x41554410;
    uStack_184 = 0x4c;
    uStack_183 = 0x4d;
    uStack_182 = 0x4f;
    uStack_181 = 0x4e;
    local_180 = 0x4f;
  }
  uVar1 = CONCAT62(uStack_17e,CONCAT11(uStack_17f,local_180));
  if ((uVar5 & 1) == 0) {
    pcVar6 = (char *)((long)&local_188 + 1);
    uVar1 = uVar5 >> 1;
  }
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>(poVar4,pcVar6,uVar1);
  if ((local_188 & 1) != 0) {
    operator_delete(local_178,
                    CONCAT17(uStack_181,
                             CONCAT16(uStack_182,CONCAT15(uStack_183,CONCAT14(uStack_184,local_188))
                                     )) & 0xfffffffffffffffe);
  }
  poVar4 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                     ((ostream *)&local_170,", bitsPerSample: ",0x11);
  std::to_string((int)*(char *)((long)in_x0 + 5));
  uVar5 = CONCAT62(uStack_17e,CONCAT11(uStack_17f,local_180));
  pcVar6 = local_178;
  if ((local_188 & 1) == 0) {
    uVar5 = (ulong)((byte)local_188 >> 1);
    pcVar6 = (char *)((long)&local_188 + 1);
  }
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>(poVar4,pcVar6,uVar5);
  if ((local_188 & 1) != 0) {
    operator_delete(local_178,
                    CONCAT17(uStack_181,
                             CONCAT16(uStack_182,CONCAT15(uStack_183,CONCAT14(uStack_184,local_188))
                                     )) & 0xfffffffffffffffe);
  }
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
            ((ostream *)&local_170,"}",1);
  if (((uint)local_108 >> 4 & 1) == 0) {
    if (((uint)local_108 >> 3 & 1) != 0) {
      plVar7 = local_158;
      uVar5 = local_158[2];
      goto LAB_0095d278;
    }
    __src = (void *)0x0;
    __n = 0;
  }
  else {
    if (uStack_110 < (ulong)local_158[4]) {
      uStack_110 = local_158[4];
    }
    plVar7 = local_158 + 3;
    uVar5 = uStack_110;
LAB_0095d278:
    __src = (void *)*plVar7;
    __n = uVar5 - (long)__src;
    if (0xfffffffffffffff6 < __n) {
                    /* WARNING: Subroutine does not return */
      std::string::__throw_length_error_abi_nn220000_();
    }
    if (0x16 < __n) {
      uVar5 = 0x1a;
      if ((__n | 7) != 0x17) {
        uVar5 = (__n | 7) + 1;
      }
      __dest = (undefined1 *)FUN_00f62c00(uVar5);
      in_x8[1] = __n;
      in_x8[2] = (ulong)__dest;
      *in_x8 = uVar5 | 1;
      goto LAB_0095d2cc;
    }
  }
  __dest = (undefined1 *)((long)in_x8 + 1);
  *(char *)in_x8 = (char)((int)__n << 1);
LAB_0095d2cc:
  memmove(__dest,__src,__n);
  local_170 = &PTR__ostringstream_00f68b98;
  __dest[__n] = 0;
  ppuStack_100 = &PTR__ostringstream_00f68bc0;
  local_168 = &PTR__stringbuf_00f687d0;
  if ((local_158[6] & 1U) != 0) {
    operator_delete(local_118,local_158[6] & 0xfffffffffffffffe);
  }
  local_168 = &PTR__streambuf_00f68750;
  std::locale::~locale((locale *)&uStack_160);
  std::ostream::~ostream((ostream *)&local_170);
  std::ios::~ios((ios *)&ppuStack_100);
  if (*(long *)(lVar3 + 0x28) == local_68) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== SscBitrateByBusyLevel @ 00975920 size 284 :: SscBitrateByBusyLevel */

/* WARNING: Unknown calling convention: __rustcall */
/* bluetooth::audio::seh_aidl::a2dp::codec::SscBitrateByBusyLevel */

void __rustcall
bluetooth::audio::seh_aidl::a2dp::codec::SscBitrateByBusyLevel
          (uint param_1,uint param_2,ulong param_3)

{
  long lVar1;
  undefined *puVar2;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  undefined8 local_b0;
  ulong *puStack_a8;
  undefined8 local_a0;
  undefined4 local_98 [2];
  char *local_90;
  char *pcStack_88;
  ulong local_80 [3];
  undefined8 uStack_68;
  ulong local_60;
  undefined8 local_58;
  undefined8 uStack_50;
  long local_38;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_38 = *(long *)(lVar1 + 0x28);
  local_98[0] = 0x2ef;
  local_90 = 
  "packages/modules/Bluetooth/system/audio_hal_interface/seh_aidl/a2dp/codec_status_aidl.cc";
  pcStack_88 = "SscBitrateByBusyLevel";
  param_2 = param_2 & 0xffff;
  local_80[0] = (ulong)param_1;
  local_80[1] = 0;
  local_60 = param_3 & 1;
  if (2 < param_2) {
    param_2 = 3;
  }
  puStack_a8 = local_80;
  uStack_68 = 0;
  local_58 = 0;
  uStack_50 = 0x4c6;
  local_b0 = 3;
  local_a0 = 0x4c6;
  local_80[2] = (ulong)param_2;
  log_internal::vlog(4,"BTAudioCodecStatusSehAIDL",local_98,
                     "codec_type {} busy_level {} is_bitrate_limit {}",0x2f,&local_b0);
  if (param_1 == 0x200) {
    puVar2 = &UNK_0020a320;
  }
  else if (param_1 == 0x400) {
    puVar2 = &DAT_00207800;
  }
  else {
    puVar2 = &UNK_00209770;
    if ((param_3 & 1) == 0) {
      puVar2 = &DAT_00207650;
    }
  }
  if (*(long *)(lVar1 + 0x28) != local_38) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(*(undefined4 *)(puVar2 + (ulong)param_2 * 4));
  }
  return;
}


/* ==== HalConfigToA2dpConfig @ 00975a3c size 2392 :: const auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::get() const [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::Tag::sscConfig] */

/* WARNING: Unknown calling convention: __rustcall */
/* bluetooth::audio::seh_aidl::a2dp::codec::HalConfigToA2dpConfig */

void __rustcall
bluetooth::audio::seh_aidl::a2dp::codec::HalConfigToA2dpConfig(long param_1,int *param_2)

{
  byte bVar1;
  uint uVar2;
  long lVar3;
  bool bVar4;
  undefined8 uVar5;
  char *pcVar6;
  uint uVar7;
  ulong uVar8;
  int iVar9;
  undefined4 uVar10;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  undefined4 local_98;
  undefined1 uStack_94;
  undefined1 uStack_93;
  undefined1 uStack_92;
  undefined1 uStack_91;
  undefined1 uStack_90;
  undefined5 uStack_8f;
  undefined1 uStack_8a;
  undefined1 uStack_89;
  undefined1 uStack_88;
  undefined1 uStack_87;
  undefined1 uStack_86;
  undefined5 uStack_85;
  undefined8 local_80;
  ulong *puStack_78;
  undefined8 local_70;
  undefined4 local_68 [2];
  char *local_60;
  char *pcStack_58;
  ulong local_50;
  ulong local_48;
  undefined8 uStack_40;
  long local_28;
  
  *in_x18 = unaff_x30;
  lVar3 = tpidr_el0;
  local_28 = *(long *)(lVar3 + 0x28);
  iVar9 = *param_2;
  if (iVar9 < 5) {
    if (iVar9 - 3U < 2) {
      if (param_2[0x16] != 3) {
        pcVar6 = 
        "const auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::get() const [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::Tag::aptxConfig]"
        ;
LAB_00976384:
                    /* WARNING: Subroutine does not return */
        __assert2("out/soong/.intermediates/vendor/samsung/interfaces/bluetooth/audio/aidl/vendor.samsung.hardware.bluetooth.audio-V2-ndk-source/gen/include/aidl/vendor/samsung/hardware/bluetooth/audio/SehCodecConfiguration.h"
                  ,0xa7,pcVar6,"bad access: a wrong tag");
      }
LAB_00975c50:
      uVar5 = *(undefined8 *)(param_2 + 6);
      uVar2 = (uint)((ulong)uVar5 >> 0x20) & 0xff;
      iVar9 = (int)uVar5;
      if (iVar9 < 0x15888) {
        if (iVar9 < 0xac44) {
          if (iVar9 == 16000) {
            uVar10 = 0x40;
          }
          else if (iVar9 == 24000) {
            uVar10 = 0x80;
          }
          else {
LAB_00975eb0:
            uVar10 = 0;
          }
        }
        else if (iVar9 == 0xac44) {
          uVar10 = 1;
        }
        else {
          if (iVar9 != 48000) goto LAB_00975eb0;
          uVar10 = 2;
        }
      }
      else if (iVar9 < 0x2b110) {
        if (iVar9 == 0x15888) {
          uVar10 = 4;
        }
        else {
          if (iVar9 != 96000) goto LAB_00975eb0;
          uVar10 = 8;
        }
      }
      else if (iVar9 == 0x2b110) {
        uVar10 = 0x10;
      }
      else {
        if (iVar9 != 0x2ee00) goto LAB_00975eb0;
        uVar10 = 0x20;
      }
      *(undefined4 *)(param_1 + 8) = uVar10;
      iVar9 = (int)((ulong)uVar5 >> 0x10) >> 0x18;
      uVar7 = iVar9 - 0x10U >> 1 | iVar9 << 0x1f;
      if (uVar7 < 10) {
        uVar10 = *(undefined4 *)(&DAT_002527d4 + (ulong)uVar7 * 4);
      }
      else {
        uVar10 = 0;
      }
      uVar7 = uVar2;
      if (uVar2 != 2) {
        uVar7 = 0;
      }
      bVar4 = uVar2 == 1;
    }
    else {
      if (iVar9 == 1) {
        if (param_2[0x16] != 0) {
          pcVar6 = 
          "const auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::get() const [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::Tag::sbcConfig]"
          ;
          goto LAB_00976384;
        }
        iVar9 = param_2[6];
        if (iVar9 < 0x15888) {
          if (iVar9 < 0xac44) {
            if (iVar9 == 16000) {
              uVar10 = 0x40;
            }
            else if (iVar9 == 24000) {
              uVar10 = 0x80;
            }
            else {
LAB_00976240:
              uVar10 = 0;
            }
          }
          else if (iVar9 == 0xac44) {
            uVar10 = 1;
          }
          else {
            if (iVar9 != 48000) goto LAB_00976240;
            uVar10 = 2;
          }
        }
        else if (iVar9 < 0x2b110) {
          if (iVar9 == 0x15888) {
            uVar10 = 4;
          }
          else {
            if (iVar9 != 96000) goto LAB_00976240;
            uVar10 = 8;
          }
        }
        else if (iVar9 == 0x2b110) {
          uVar10 = 0x10;
        }
        else {
          if (iVar9 != 0x2ee00) goto LAB_00976240;
          uVar10 = 0x20;
        }
        uVar2 = (int)(char)param_2[8] - 0x10U >> 1 | (int)(char)param_2[8] << 0x1f;
        bVar1 = *(byte *)(param_2 + 7);
        uVar7 = (uint)bVar1;
        *(undefined4 *)(param_1 + 8) = uVar10;
        if (uVar2 < 10) {
          uVar10 = *(undefined4 *)(&DAT_002527d4 + (ulong)uVar2 * 4);
        }
        else {
          uVar10 = 0;
        }
        *(undefined4 *)(param_1 + 0xc) = uVar10;
        if (bVar1 != 2) {
          if (bVar1 == 4) goto LAB_0097621c;
LAB_00976284:
          *(undefined4 *)(param_1 + 0x10) = 0;
          goto LAB_009762f4;
        }
        goto LAB_009762f0;
      }
      if (iVar9 != 2) {
LAB_00975bb8:
        if (iVar9 < 9) {
          if (iVar9 == 0) {
            uVar8 = 0xe;
            local_98 = 0x4b4e550e;
            uStack_94 = 0x4e;
            uStack_93 = 0x4f;
            uStack_92 = 0x57;
            uStack_91 = 0x4e;
            uStack_90 = 0;
          }
          else if (iVar9 == 7) {
            uVar8 = 6;
            local_98 = 0x33434c06;
            uStack_94 = 0;
          }
          else if (iVar9 == 8) {
            uVar8 = 0xc;
            local_98 = 0x4e45560c;
            uStack_94 = 0x44;
            uStack_93 = 0x4f;
            uStack_92 = 0x52;
            uStack_91 = 0;
          }
          else {
LAB_00976054:
            std::to_string(iVar9);
            uVar8 = (ulong)(byte)local_98;
          }
        }
        else if (iVar9 == 9) {
          uVar8 = 0x1a;
          uStack_8a = 0;
          local_98 = 0x5450411a;
          uStack_94 = 0x58;
          uStack_93 = 0x5f;
          uStack_92 = 0x41;
          uStack_91 = 0x44;
          uStack_90 = 0x41;
          uStack_8f = 0x4556495450;
        }
        else {
          if (iVar9 == 0xb) {
            uVar8 = 0x20;
            local_98._0_1_ = 0x20;
            uStack_87 = 0;
          }
          else {
            if (iVar9 != 0xc) goto LAB_00976054;
            uVar8 = 0x22;
            local_98._0_1_ = 0x22;
            uStack_87 = 0x58;
            uStack_86 = 0;
          }
          uStack_8f = 0x4556495450;
          uStack_8a = 0x5f;
          uStack_89 = 0x4c;
          uStack_88 = 0x45;
          local_98 = CONCAT31(0x545041,(byte)local_98);
          uStack_94 = 0x58;
          uStack_93 = 0x5f;
          uStack_92 = 0x41;
          uStack_91 = 0x44;
          uStack_90 = 0x41;
        }
        local_68[0] = 0x345;
        local_60 = 
        "packages/modules/Bluetooth/system/audio_hal_interface/seh_aidl/a2dp/codec_status_aidl.cc";
        pcStack_58 = "HalConfigToA2dpConfig";
        local_48 = CONCAT17(uStack_89,CONCAT16(uStack_8a,CONCAT51(uStack_8f,uStack_90)));
        local_50 = CONCAT53(uStack_85,CONCAT12(uStack_86,CONCAT11(uStack_87,uStack_88)));
        if ((uVar8 & 1) == 0) {
          local_50 = (long)&local_98 + 1;
          local_48 = uVar8 >> 1;
        }
        uStack_40 = 0xd;
        puStack_78 = &local_50;
        local_80 = 1;
        local_70 = 0xd;
        log_internal::vlog(6,"BTAudioCodecStatusSehAIDL",local_68,"Unknown codecType={}",0x14,
                           &local_80);
        if ((local_98 & 1) != 0) {
          operator_delete((void *)CONCAT53(uStack_85,
                                           CONCAT12(uStack_86,CONCAT11(uStack_87,uStack_88))),
                          CONCAT17(uStack_91,
                                   CONCAT16(uStack_92,
                                            CONCAT15(uStack_93,CONCAT14(uStack_94,local_98)))) &
                          0xfffffffffffffffe);
        }
        uVar5 = 0;
        goto LAB_009762f8;
      }
      if (param_2[0x16] != 1) {
        pcVar6 = 
        "const auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::get() const [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::Tag::aacConfig]"
        ;
        goto LAB_00976384;
      }
      iVar9 = param_2[7];
      if (iVar9 < 0x15888) {
        if (iVar9 < 0xac44) {
          if (iVar9 == 16000) {
            uVar10 = 0x40;
          }
          else if (iVar9 == 24000) {
            uVar10 = 0x80;
          }
          else {
LAB_0097622c:
            uVar10 = 0;
          }
        }
        else if (iVar9 == 0xac44) {
          uVar10 = 1;
        }
        else {
          if (iVar9 != 48000) goto LAB_0097622c;
          uVar10 = 2;
        }
      }
      else if (iVar9 < 0x2b110) {
        if (iVar9 == 0x15888) {
          uVar10 = 4;
        }
        else {
          if (iVar9 != 96000) goto LAB_0097622c;
          uVar10 = 8;
        }
      }
      else if (iVar9 == 0x2b110) {
        uVar10 = 0x10;
      }
      else {
        if (iVar9 != 0x2ee00) goto LAB_0097622c;
        uVar10 = 0x20;
      }
      uVar7 = (int)*(char *)((long)param_2 + 0x22) - 0x10U >> 1 |
              (int)*(char *)((long)param_2 + 0x22) << 0x1f;
      bVar1 = *(byte *)(param_2 + 8);
LAB_009762bc:
      *(undefined4 *)(param_1 + 8) = uVar10;
      if (uVar7 < 10) {
        uVar10 = *(undefined4 *)(&DAT_002527d4 + (ulong)uVar7 * 4);
      }
      else {
        uVar10 = 0;
      }
      uVar7 = (uint)bVar1;
      if (uVar7 != 2) {
        uVar7 = 0;
      }
      bVar4 = bVar1 == 1;
    }
    if (bVar4) {
      uVar7 = 1;
    }
    *(undefined4 *)(param_1 + 0xc) = uVar10;
LAB_009762f0:
    *(uint *)(param_1 + 0x10) = uVar7;
  }
  else {
    if (iVar9 == 5) {
      if (param_2[0x16] != 2) {
        pcVar6 = 
        "const auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::get() const [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::Tag::ldacConfig]"
        ;
        goto LAB_00976384;
      }
      iVar9 = param_2[6];
      if (iVar9 < 0x15888) {
        if (iVar9 < 0xac44) {
          if (iVar9 == 16000) {
            uVar10 = 0x40;
          }
          else if (iVar9 == 24000) {
            uVar10 = 0x80;
          }
          else {
LAB_009761d8:
            uVar10 = 0;
          }
        }
        else if (iVar9 == 0xac44) {
          uVar10 = 1;
        }
        else {
          if (iVar9 != 48000) goto LAB_009761d8;
          uVar10 = 2;
        }
      }
      else if (iVar9 < 0x2b110) {
        if (iVar9 == 0x15888) {
          uVar10 = 4;
        }
        else {
          if (iVar9 != 96000) goto LAB_009761d8;
          uVar10 = 8;
        }
      }
      else if (iVar9 == 0x2b110) {
        uVar10 = 0x10;
      }
      else {
        if (iVar9 != 0x2ee00) goto LAB_009761d8;
        uVar10 = 0x20;
      }
      uVar7 = (int)*(char *)((long)param_2 + 0x1e) - 0x10U >> 1 |
              (int)*(char *)((long)param_2 + 0x1e) << 0x1f;
      iVar9 = param_2[7];
      *(undefined4 *)(param_1 + 8) = uVar10;
      if (uVar7 < 10) {
        uVar10 = *(undefined4 *)(&DAT_002527d4 + (ulong)uVar7 * 4);
      }
      else {
        uVar10 = 0;
      }
      *(undefined4 *)(param_1 + 0xc) = uVar10;
      if ((char)iVar9 == '\x01') {
        uVar7 = 2;
      }
      else {
        if ((char)iVar9 != '\x03') goto LAB_00976284;
LAB_0097621c:
        uVar7 = 1;
      }
      goto LAB_009762f0;
    }
    if (iVar9 == 6) {
      if (param_2[0x16] != 6) {
        pcVar6 = 
        "const auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::get() const [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::Tag::sscConfig]"
        ;
        goto LAB_00976384;
      }
      goto LAB_00975c50;
    }
    if (iVar9 != 10) goto LAB_00975bb8;
    if (param_2[0x16] != 8) {
      pcVar6 = 
      "const auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::get() const [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::CodecSpecific::Tag::opusConfig]"
      ;
      goto LAB_00976384;
    }
    if ((*(byte *)(param_2 + 0xb) & 1) != 0) {
      iVar9 = param_2[7];
      if (iVar9 < 0x15888) {
        if (iVar9 < 0xac44) {
          if (iVar9 == 16000) {
            uVar10 = 0x40;
          }
          else if (iVar9 == 24000) {
            uVar10 = 0x80;
          }
          else {
LAB_009762ac:
            uVar10 = 0;
          }
        }
        else if (iVar9 == 0xac44) {
          uVar10 = 1;
        }
        else {
          if (iVar9 != 48000) goto LAB_009762ac;
          uVar10 = 2;
        }
      }
      else if (iVar9 < 0x2b110) {
        if (iVar9 == 0x15888) {
          uVar10 = 4;
        }
        else {
          if (iVar9 != 96000) goto LAB_009762ac;
          uVar10 = 8;
        }
      }
      else if (iVar9 == 0x2b110) {
        uVar10 = 0x10;
      }
      else {
        if (iVar9 != 0x2ee00) goto LAB_009762ac;
        uVar10 = 0x20;
      }
      uVar7 = (int)(char)param_2[6] - 0x10U >> 1 | (int)(char)param_2[6] << 0x1f;
      bVar1 = *(byte *)((long)param_2 + 0x29);
      goto LAB_009762bc;
    }
    local_98 = 0x55504f08;
    uStack_94 = 0x53;
    local_68[0] = 0x33d;
    local_60 = 
    "packages/modules/Bluetooth/system/audio_hal_interface/seh_aidl/a2dp/codec_status_aidl.cc";
    pcStack_58 = "HalConfigToA2dpConfig";
    local_50 = (ulong)&local_98 | 1;
    local_48 = 4;
    uStack_40 = 0xd;
    puStack_78 = &local_50;
    uStack_93 = 0;
    local_80 = 1;
    local_70 = 0xd;
    log_internal::vlog(6,"BTAudioCodecStatusSehAIDL",local_68,"No configs included codecType={}",
                       0x20,&local_80);
    if ((local_98 & 1) != 0) {
      operator_delete((void *)CONCAT53(uStack_85,CONCAT12(uStack_86,CONCAT11(uStack_87,uStack_88))),
                      CONCAT17(uStack_91,
                               CONCAT16(uStack_92,CONCAT15(uStack_93,CONCAT14(uStack_94,local_98))))
                      & 0xfffffffffffffffe);
    }
  }
LAB_009762f4:
  uVar5 = 1;
LAB_009762f8:
  if (*(long *)(lVar3 + 0x28) == local_28) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar5);
}


/* ==== A2dpSscToHalConfig @ 009764c8 size 812 :: A2dpSscToHalConfig | Unknown ssc bits_per_sample={} | Unknown ssc channel_mode={} | Unknown ssc sample_rate={} */

/* WARNING: Unknown calling convention: __rustcall */
/* bluetooth::audio::seh_aidl::a2dp::codec::A2dpSscToHalConfig */

void __rustcall
bluetooth::audio::seh_aidl::a2dp::codec::A2dpSscToHalConfig(undefined4 *param_1,undefined8 param_2)

{
  uint uVar1;
  uint uVar2;
  long lVar3;
  undefined8 uVar4;
  char *pcVar5;
  undefined8 *in_x18;
  ulong uVar6;
  ulong uVar7;
  undefined8 unaff_x30;
  undefined8 local_120;
  undefined8 uStack_118;
  undefined8 local_110;
  undefined8 uStack_108;
  undefined8 local_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 local_e0;
  undefined8 **ppuStack_d8;
  undefined8 local_d0;
  undefined4 local_c8 [2];
  char *local_c0;
  char *pcStack_b8;
  undefined8 local_b0;
  undefined8 uStack_a8;
  undefined8 local_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined4 uStack_88;
  undefined4 local_84;
  undefined4 uStack_80;
  undefined8 uStack_7c;
  undefined8 *local_70;
  code *local_68;
  undefined8 uStack_60;
  long local_48;
  
  *in_x18 = unaff_x30;
  lVar3 = tpidr_el0;
  local_48 = *(long *)(lVar3 + 0x28);
  uStack_118 = 0;
  local_120 = 0;
  uStack_108 = 0;
  local_110 = 0;
  uStack_f8 = 0;
  local_100 = 0;
  uStack_e8 = 0;
  uStack_f0 = 0;
  A2dpCodecConfig::getCodecConfig(&local_120,param_2);
  if ((int)local_120 == 8) {
    uStack_7c = 0;
    uStack_80 = 0;
    uStack_98 = 0;
    local_a0 = 0;
    uStack_88 = 0;
    local_84 = 0;
    uStack_90 = 0;
    uStack_a8 = 0;
    local_b0 = 0;
    A2dpCodecConfig::getCodecSpecificConfig(param_2,&local_b0);
    if ((int)local_120 == 8) {
      *param_1 = 6;
    }
    if ((int)uStack_118 < 0x10) {
      if (3 < (int)uStack_118) {
        if ((int)uStack_118 == 4) {
          uVar6 = 0x15888;
        }
        else {
          if ((int)uStack_118 != 8) goto LAB_00976750;
          uVar6 = 96000;
        }
        goto LAB_009765f8;
      }
      if ((int)uStack_118 == 1) {
        uVar6 = 0xac44;
        goto LAB_009765f8;
      }
      if ((int)uStack_118 == 2) {
        uVar6 = 48000;
        goto LAB_009765f8;
      }
LAB_00976750:
      local_c8[0] = 0x38d;
      local_70 = (undefined8 *)((ulong)&local_120 | 8);
      local_68 = 
      _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I29btav_a2dp_codec_sample_rate_tEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
      ;
      pcVar5 = "Unknown ssc sample_rate={}";
      uVar4 = 0x1a;
    }
    else {
      if ((int)uStack_118 < 0x40) {
        if ((int)uStack_118 == 0x10) {
          uVar6 = 0x2b110;
        }
        else {
          if ((int)uStack_118 != 0x20) goto LAB_00976750;
          uVar6 = 0x2ee00;
        }
      }
      else if ((int)uStack_118 == 0x40) {
        uVar6 = 16000;
      }
      else {
        if ((int)uStack_118 != 0x80) goto LAB_00976750;
        uVar6 = 24000;
      }
LAB_009765f8:
      uVar1 = (uint)local_110;
      if ((uint)local_110 != 2) {
        uVar1 = 0;
      }
      if ((uint)local_110 == 1) {
        uVar1 = 1;
      }
      if (uVar1 == 0) {
        local_c8[0] = 0x392;
        local_70 = &local_110;
        local_68 = 
        _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I30btav_a2dp_codec_channel_mode_tEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
        ;
        pcVar5 = "Unknown ssc channel_mode={}";
        uVar4 = 0x1b;
      }
      else {
        uVar2 = uStack_118._4_4_ - 1;
        if ((uVar2 < 8) && ((0x8bU >> (ulong)(uVar2 & 0x1f) & 1) != 0)) {
          uVar7 = *(ulong *)(&DAT_00252840 + (ulong)uVar2 * 8);
          if (param_1[0x16] != 0xffffffff) {
            (*(code *)(&
                      PTR___dispatch_abi_nn220000_<std::__variant_detail::__dtor<std::__variant_detail::__traits<aidl::vendor::samsung::hardware::bluetooth::audio::SehSbcConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehAacConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehLdacConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehAptxConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehAptxAdaptiveConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehLc3Configuration,aidl::vendor::samsung::hardware::bluetooth::audio::SehSscConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::VendorConfiguration,std::optional<aidl::vendor::samsung::hardware::bluetooth::audio::SehOpusConfiguration>>,(std::__variant_detail::_Trait)1>::__destroy[abi:nn220000]()::_lambda(auto:1&)_1_&&,std::__variant_detail::__base<(std::__variant_detail::_Trait)1,aidl::vendor::samsung::hardware::bluetooth::audio::SehSbcConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehAacConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehLdacConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehAptxConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehAptxAdaptiveConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehLc3Configuration,aidl::vendor::samsung::hardware::bluetooth::audio::SehSscConfiguration,aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecConfiguration::VendorConfiguration,std::optional<aidl::vendor::samsung::hardware::bluetooth::audio::SehOpusConfiguration>>&>_00f9e8c8
                      )[(uint)param_1[0x16]])(&local_70,param_1 + 6);
          }
          uVar4 = 1;
          param_1[0x16] = 6;
          *(ulong *)(param_1 + 6) = uVar7 | (ulong)(uVar1 & 0xff) << 0x20 | uVar6;
          goto LAB_009767c0;
        }
        local_c8[0] = 0x397;
        local_70 = (undefined8 *)((ulong)&local_120 | 0xc);
        local_68 = 
        _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I33btav_a2dp_codec_bits_per_sample_tEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
        ;
        pcVar5 = "Unknown ssc bits_per_sample={}";
        uVar4 = 0x1e;
      }
    }
    ppuStack_d8 = &local_70;
    uStack_60 = 0xf;
    pcStack_b8 = "A2dpSscToHalConfig";
    local_c0 = 
    "packages/modules/Bluetooth/system/audio_hal_interface/seh_aidl/a2dp/codec_status_aidl.cc";
    local_d0 = 0xf;
    local_e0 = 1;
    log_internal::vlog(6,"BTAudioCodecStatusSehAIDL",local_c8,pcVar5,uVar4,&local_e0);
  }
  uVar4 = 0;
LAB_009767c0:
  if (*(long *)(lVar3 + 0x28) == local_48) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar4);
}


/* ==== toString @ 00976f50 size 1500 :: const auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecCapabilities::Capabilities::get() const [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecCapabilities::Capabilities::Tag::sscCapabilities] | sscCapabilities:  */

/* aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecCapabilities::Capabilities::toString()
   const */

void aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecCapabilities::Capabilities::toString
               (void)

{
  int iVar1;
  long lVar2;
  long in_x0;
  ostream *poVar3;
  optional *extraout_x1;
  void *__src;
  char *pcVar4;
  ulong *in_x8;
  ulong uVar5;
  long *plVar6;
  undefined8 *in_x18;
  undefined1 *__dest;
  size_t __n;
  undefined8 unaff_x30;
  byte local_188;
  undefined7 uStack_187;
  ulong local_180;
  char *local_178;
  undefined **local_170;
  undefined **local_168;
  undefined8 uStack_160;
  long local_158 [8];
  void *local_118;
  ulong uStack_110;
  undefined8 local_108;
  undefined **ppuStack_100;
  undefined8 local_f8;
  undefined8 uStack_f0;
  undefined8 local_e8;
  undefined8 uStack_e0;
  undefined8 local_d8;
  undefined8 uStack_d0;
  undefined8 local_c8;
  undefined8 uStack_c0;
  undefined8 local_b8;
  undefined8 uStack_b0;
  undefined8 local_a8;
  undefined8 uStack_a0;
  undefined8 local_98;
  undefined8 uStack_90;
  undefined8 local_88;
  undefined8 uStack_80;
  undefined8 local_78;
  undefined8 uStack_70;
  long local_68;
  
  *in_x18 = unaff_x30;
  lVar2 = tpidr_el0;
  local_68 = *(long *)(lVar2 + 0x28);
  local_108 = 0;
  uStack_70 = 0;
  local_78 = 0;
  uStack_80 = 0;
  local_88 = 0;
  uStack_90 = 0;
  local_98 = 0;
  uStack_a0 = 0;
  local_a8 = 0;
  uStack_b0 = 0;
  local_b8 = 0;
  uStack_c0 = 0;
  local_c8 = 0;
  uStack_d0 = 0;
  local_d8 = 0;
  uStack_e0 = 0;
  local_e8 = 0;
  uStack_f0 = 0;
  local_f8 = 0;
  uStack_110 = 0;
  local_118 = (void *)0x0;
  local_158[7] = 0;
  local_158[6] = 0;
  local_158[5] = 0;
  local_158[4] = 0;
  local_158[3] = 0;
  local_158[2] = 0;
  local_158[1] = 0;
  local_158[0] = 0;
  local_170 = &PTR__ostream_00f68c08;
  uStack_160 = 0;
  local_168 = (undefined **)0x0;
  ppuStack_100 = &PTR__ostream_00f68c30;
  std::ios_base::init((ios_base *)&ppuStack_100,&local_168);
  local_78 = 0;
                    /* WARNING: Ignoring partial resolution of indirect */
  uStack_70._0_4_ = 0xffffffff;
  local_170 = &PTR__ostringstream_00f68b98;
  local_168 = &PTR__streambuf_00f68750;
  ppuStack_100 = &PTR__ostringstream_00f68bc0;
  std::locale::locale((locale *)&uStack_160);
  local_158[5] = 0;
  local_158[4] = 0;
  local_158[3] = 0;
  local_158[2] = 0;
  local_158[1] = 0;
  local_158[0] = 0;
  local_168 = &PTR__stringbuf_00f687d0;
  local_158[7] = 0;
  local_158[6] = 0;
  uStack_110 = 0;
  local_118 = (void *)0x0;
  local_108 = CONCAT44(local_108._4_4_,0x10);
  std::stringbuf::__init_buf_ptrs_abi_nn220000_((stringbuf *)&local_168);
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
            ((ostream *)&local_170,"Capabilities{",0xd);
  iVar1 = *(int *)(in_x0 + 0xa0);
  if (iVar1 < 4) {
    if (1 < iVar1) {
      if (iVar1 == 2) {
        poVar3 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                           ((ostream *)&local_170,"ldacCapabilities: ",0x12);
        if (*(int *)(in_x0 + 0xa0) != 2) {
          pcVar4 = 
          "const auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecCapabilities::Capabilities::get() const [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecCapabilities::Capabilities::Tag::ldacCapabilities]"
          ;
          goto LAB_0097751c;
        }
        SehLdacCapabilities::toString();
      }
      else {
        if (iVar1 != 3) goto LAB_00977314;
        poVar3 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                           ((ostream *)&local_170,"aptxCapabilities: ",0x12);
        if (*(int *)(in_x0 + 0xa0) != 3) {
          pcVar4 = 
          "const auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecCapabilities::Capabilities::get() const [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecCapabilities::Capabilities::Tag::aptxCapabilities]"
          ;
          goto LAB_0097751c;
        }
        SehAptxCapabilities::toString();
      }
      goto LAB_009772dc;
    }
    if (iVar1 == 0) {
      poVar3 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                         ((ostream *)&local_170,"sbcCapabilities: ",0x11);
      if (*(int *)(in_x0 + 0xa0) != 0) {
        pcVar4 = 
        "const auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecCapabilities::Capabilities::get() const [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecCapabilities::Capabilities::Tag::sbcCapabilities]"
        ;
        goto LAB_0097751c;
      }
      SehSbcCapabilities::toString();
      goto LAB_009772dc;
    }
    if (iVar1 == 1) {
      poVar3 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                         ((ostream *)&local_170,"aacCapabilities: ",0x11);
      if (*(int *)(in_x0 + 0xa0) != 1) {
        pcVar4 = 
        "const auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecCapabilities::Capabilities::get() const [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecCapabilities::Capabilities::Tag::aacCapabilities]"
        ;
        goto LAB_0097751c;
      }
      SehAacCapabilities::toString();
      goto LAB_009772dc;
    }
  }
  else {
    if (iVar1 < 6) {
      if (iVar1 == 4) {
        poVar3 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                           ((ostream *)&local_170,"aptxAdaptiveCapabilities: ",0x1a);
        if (*(int *)(in_x0 + 0xa0) != 4) {
          pcVar4 = 
          "const auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecCapabilities::Capabilities::get() const [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecCapabilities::Capabilities::Tag::aptxAdaptiveCapabilities]"
          ;
          goto LAB_0097751c;
        }
        SehAptxAdaptiveCapabilities::toString();
      }
      else {
        if (iVar1 != 5) goto LAB_00977314;
        poVar3 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                           ((ostream *)&local_170,"lc3Capabilities: ",0x11);
        if (*(int *)(in_x0 + 0xa0) != 5) {
          pcVar4 = 
          "const auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecCapabilities::Capabilities::get() const [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecCapabilities::Capabilities::Tag::lc3Capabilities]"
          ;
          goto LAB_0097751c;
        }
        SehLc3Capabilities::toString();
      }
    }
    else if (iVar1 == 6) {
      poVar3 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                         ((ostream *)&local_170,"sscCapabilities: ",0x11);
      if (*(int *)(in_x0 + 0xa0) != 6) {
        pcVar4 = 
        "const auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecCapabilities::Capabilities::get() const [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecCapabilities::Capabilities::Tag::sscCapabilities]"
        ;
LAB_0097751c:
                    /* WARNING: Subroutine does not return */
        __assert2("out/soong/.intermediates/vendor/samsung/interfaces/bluetooth/audio/aidl/vendor.samsung.hardware.bluetooth.audio-V2-ndk-source/gen/include/aidl/vendor/samsung/hardware/bluetooth/audio/SehCodecCapabilities.h"
                  ,0xa3,pcVar4,"bad access: a wrong tag");
      }
      SehSscCapabilities::toString();
    }
    else if (iVar1 == 7) {
      poVar3 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                         ((ostream *)&local_170,"vendorCapabilities: ",0x14);
      if (*(int *)(in_x0 + 0xa0) != 7) {
        pcVar4 = 
        "const auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecCapabilities::Capabilities::get() const [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecCapabilities::Capabilities::Tag::vendorCapabilities]"
        ;
        goto LAB_0097751c;
      }
      android::hardware::bluetooth::audio::CodecCapabilities::VendorCapabilities::toString
                ((VendorCapabilities *)(in_x0 + 8));
    }
    else {
      if (iVar1 != 8) goto LAB_00977314;
      poVar3 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                         ((ostream *)&local_170,"opusCapabilities: ",0x12);
      if (*(int *)(in_x0 + 0xa0) != 8) {
        pcVar4 = 
        "const auto &aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecCapabilities::Capabilities::get() const [_tag = aidl::vendor::samsung::hardware::bluetooth::audio::SehCodecCapabilities::Capabilities::Tag::opusCapabilities]"
        ;
        goto LAB_0097751c;
      }
      ::android::internal::
      ToString<std::optional<aidl::vendor::samsung::hardware::bluetooth::audio::SehOpusCapabilities>>
                ((internal *)(in_x0 + 8),extraout_x1);
    }
LAB_009772dc:
    pcVar4 = local_178;
    if ((local_188 & 1) == 0) {
      local_180 = (ulong)(local_188 >> 1);
      pcVar4 = (char *)&uStack_187;
    }
    std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
              (poVar3,pcVar4,local_180);
    if ((local_188 & 1) != 0) {
      operator_delete(local_178,CONCAT71(uStack_187,local_188) & 0xfffffffffffffffe);
    }
  }
LAB_00977314:
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
            ((ostream *)&local_170,"}",1);
  if (((uint)local_108 >> 4 & 1) == 0) {
    if (((uint)local_108 >> 3 & 1) != 0) {
      plVar6 = local_158;
      uVar5 = local_158[2];
      goto LAB_0097736c;
    }
    __src = (void *)0x0;
    __n = 0;
  }
  else {
    if (uStack_110 < (ulong)local_158[4]) {
      uStack_110 = local_158[4];
    }
    plVar6 = local_158 + 3;
    uVar5 = uStack_110;
LAB_0097736c:
    __src = (void *)*plVar6;
    __n = uVar5 - (long)__src;
    if (0xfffffffffffffff6 < __n) {
                    /* WARNING: Subroutine does not return */
      std::string::__throw_length_error_abi_nn220000_();
    }
    if (0x16 < __n) {
      uVar5 = 0x1a;
      if ((__n | 7) != 0x17) {
        uVar5 = (__n | 7) + 1;
      }
      __dest = (undefined1 *)FUN_00f62c00(uVar5);
      in_x8[1] = __n;
      in_x8[2] = (ulong)__dest;
      *in_x8 = uVar5 | 1;
      goto LAB_009773c0;
    }
  }
  __dest = (undefined1 *)((long)in_x8 + 1);
  *(char *)in_x8 = (char)((int)__n << 1);
LAB_009773c0:
  memmove(__dest,__src,__n);
  local_170 = &PTR__ostringstream_00f68b98;
  __dest[__n] = 0;
  ppuStack_100 = &PTR__ostringstream_00f68bc0;
  local_168 = &PTR__stringbuf_00f687d0;
  if ((local_158[6] & 1U) != 0) {
    operator_delete(local_118,local_158[6] & 0xfffffffffffffffe);
  }
  local_168 = &PTR__streambuf_00f68750;
  std::locale::~locale((locale *)&uStack_160);
  std::ostream::~ostream((ostream *)&local_170);
  std::ios::~ios((ios *)&ppuStack_100);
  if (*(long *)(lVar2 + 0x28) == local_68) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== toString @ 009795b4 size 944 :: SehSscCapabilities{ */

/* aidl::vendor::samsung::hardware::bluetooth::audio::SehSscCapabilities::toString() const */

void aidl::vendor::samsung::hardware::bluetooth::audio::SehSscCapabilities::toString(void)

{
  long lVar1;
  char *pcVar2;
  internal *in_x0;
  ostream *poVar3;
  vector *extraout_x1;
  vector *extraout_x1_00;
  vector *extraout_x1_01;
  void *__src;
  ulong *in_x8;
  ulong uVar4;
  long *plVar5;
  undefined8 *in_x18;
  undefined1 *__dest;
  size_t __n;
  undefined8 unaff_x30;
  byte local_188;
  undefined7 uStack_187;
  ulong local_180;
  char *local_178;
  undefined **local_170;
  undefined **local_168;
  undefined8 uStack_160;
  long local_158 [8];
  void *local_118;
  ulong uStack_110;
  undefined8 local_108;
  undefined **ppuStack_100;
  undefined8 local_f8;
  undefined8 uStack_f0;
  undefined8 local_e8;
  undefined8 uStack_e0;
  undefined8 local_d8;
  undefined8 uStack_d0;
  undefined8 local_c8;
  undefined8 uStack_c0;
  undefined8 local_b8;
  undefined8 uStack_b0;
  undefined8 local_a8;
  undefined8 uStack_a0;
  undefined8 local_98;
  undefined8 uStack_90;
  undefined8 local_88;
  undefined8 uStack_80;
  undefined8 local_78;
  undefined8 uStack_70;
  long local_68;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_68 = *(long *)(lVar1 + 0x28);
  local_108 = 0;
  uStack_70 = 0;
  local_78 = 0;
  uStack_80 = 0;
  local_88 = 0;
  uStack_90 = 0;
  local_98 = 0;
  uStack_a0 = 0;
  local_a8 = 0;
  uStack_b0 = 0;
  local_b8 = 0;
  uStack_c0 = 0;
  local_c8 = 0;
  uStack_d0 = 0;
  local_d8 = 0;
  uStack_e0 = 0;
  local_e8 = 0;
  uStack_f0 = 0;
  local_f8 = 0;
  uStack_110 = 0;
  local_118 = (void *)0x0;
  local_158[7] = 0;
  local_158[6] = 0;
  local_158[5] = 0;
  local_158[4] = 0;
  local_158[3] = 0;
  local_158[2] = 0;
  local_158[1] = 0;
  local_158[0] = 0;
  local_170 = &PTR__ostream_00f68c08;
  uStack_160 = 0;
  local_168 = (undefined **)0x0;
  ppuStack_100 = &PTR__ostream_00f68c30;
  std::ios_base::init((ios_base *)&ppuStack_100,&local_168);
  local_78 = 0;
                    /* WARNING: Ignoring partial resolution of indirect */
  uStack_70._0_4_ = 0xffffffff;
  local_170 = &PTR__ostringstream_00f68b98;
  local_168 = &PTR__streambuf_00f68750;
  ppuStack_100 = &PTR__ostringstream_00f68bc0;
  std::locale::locale((locale *)&uStack_160);
  local_158[5] = 0;
  local_158[4] = 0;
  local_158[3] = 0;
  local_158[2] = 0;
  local_158[1] = 0;
  local_158[0] = 0;
  local_168 = &PTR__stringbuf_00f687d0;
  local_158[7] = 0;
  local_158[6] = 0;
  uStack_110 = 0;
  local_118 = (void *)0x0;
  local_108 = CONCAT44(local_108._4_4_,0x10);
  std::stringbuf::__init_buf_ptrs_abi_nn220000_((stringbuf *)&local_168);
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
            ((ostream *)&local_170,"SehSscCapabilities{",0x13);
  poVar3 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                     ((ostream *)&local_170,"sampleRateHz: ",0xe);
  ::android::internal::ToString<std::vector<int,std::allocator<int>>>(in_x0,extraout_x1);
  uVar4 = local_180;
  pcVar2 = local_178;
  if ((local_188 & 1) == 0) {
    uVar4 = (ulong)(local_188 >> 1);
    pcVar2 = (char *)&uStack_187;
  }
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>(poVar3,pcVar2,uVar4);
  if ((local_188 & 1) != 0) {
    operator_delete(local_178,CONCAT71(uStack_187,local_188) & 0xfffffffffffffffe);
  }
  poVar3 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                     ((ostream *)&local_170,", channelMode: ",0xf);
  ::android::internal::
  ToString<std::vector<aidl::android::hardware::bluetooth::audio::ChannelMode,std::allocator<aidl::android::hardware::bluetooth::audio::ChannelMode>>>
            (in_x0 + 0x18,extraout_x1_00);
  uVar4 = local_180;
  pcVar2 = local_178;
  if ((local_188 & 1) == 0) {
    uVar4 = (ulong)(local_188 >> 1);
    pcVar2 = (char *)&uStack_187;
  }
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>(poVar3,pcVar2,uVar4);
  if ((local_188 & 1) != 0) {
    operator_delete(local_178,CONCAT71(uStack_187,local_188) & 0xfffffffffffffffe);
  }
  poVar3 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                     ((ostream *)&local_170,", bitsPerSample: ",0x11);
  ::android::internal::ToString<std::vector<unsigned_char,std::allocator<unsigned_char>>>
            (in_x0 + 0x30,extraout_x1_01);
  pcVar2 = local_178;
  if ((local_188 & 1) == 0) {
    local_180 = (ulong)(local_188 >> 1);
    pcVar2 = (char *)&uStack_187;
  }
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>(poVar3,pcVar2,local_180);
  if ((local_188 & 1) != 0) {
    operator_delete(local_178,CONCAT71(uStack_187,local_188) & 0xfffffffffffffffe);
  }
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
            ((ostream *)&local_170,"}",1);
  if (((uint)local_108 >> 4 & 1) == 0) {
    if (((uint)local_108 >> 3 & 1) != 0) {
      plVar5 = local_158;
      uVar4 = local_158[2];
      goto LAB_00979864;
    }
    __src = (void *)0x0;
    __n = 0;
  }
  else {
    if (uStack_110 < (ulong)local_158[4]) {
      uStack_110 = local_158[4];
    }
    plVar5 = local_158 + 3;
    uVar4 = uStack_110;
LAB_00979864:
    __src = (void *)*plVar5;
    __n = uVar4 - (long)__src;
    if (0xfffffffffffffff6 < __n) {
                    /* WARNING: Subroutine does not return */
      std::string::__throw_length_error_abi_nn220000_();
    }
    if (0x16 < __n) {
      uVar4 = 0x1a;
      if ((__n | 7) != 0x17) {
        uVar4 = (__n | 7) + 1;
      }
      __dest = (undefined1 *)FUN_00f62c00(uVar4);
      in_x8[1] = __n;
      in_x8[2] = (ulong)__dest;
      *in_x8 = uVar4 | 1;
      goto LAB_009798b8;
    }
  }
  __dest = (undefined1 *)((long)in_x8 + 1);
  *(char *)in_x8 = (char)((int)__n << 1);
LAB_009798b8:
  memmove(__dest,__src,__n);
  local_170 = &PTR__ostringstream_00f68b98;
  __dest[__n] = 0;
  ppuStack_100 = &PTR__ostringstream_00f68bc0;
  local_168 = &PTR__stringbuf_00f687d0;
  if ((local_158[6] & 1U) != 0) {
    operator_delete(local_118,local_158[6] & 0xfffffffffffffffe);
  }
  local_168 = &PTR__streambuf_00f68750;
  std::locale::~locale((locale *)&uStack_160);
  std::ostream::~ostream((ostream *)&local_170);
  std::ios::~ios((ios *)&ppuStack_100);
  if (*(long *)(lVar1 + 0x28) == local_68) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== toString @ 009b8128 size 2860 :: .sscCapabilities =  */

/* WARNING: Type propagation algorithm not settling */
/* vendor::samsung::hardware::bluetooth::audio::V2_0::toString(vendor::samsung::hardware::bluetooth::audio::V2_0::SehAudioCapabilities
   const&) */

void vendor::samsung::hardware::bluetooth::audio::V2_0::toString(SehAudioCapabilities *param_1)

{
  void *pvVar1;
  SehAudioCapabilities SVar2;
  byte bVar3;
  long lVar4;
  ulong uVar5;
  undefined4 *puVar6;
  SehSscParameters *pSVar7;
  byte *pbVar8;
  undefined8 *puVar9;
  ulong *puVar10;
  SehAacParameters *pSVar11;
  SehLdacParameters *pSVar12;
  SehSbcParameters *pSVar13;
  undefined1 in_w2;
  undefined4 uVar14;
  string *in_x8;
  undefined8 uVar15;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  undefined8 uVar16;
  undefined8 uVar17;
  ulong local_b8;
  undefined8 local_b0;
  void *local_a8;
  ulong local_a0;
  undefined8 local_98;
  void *local_90;
  ulong local_88;
  undefined8 local_80;
  void *local_78;
  uint local_70;
  undefined1 uStack_6c;
  undefined1 uStack_6b;
  undefined1 uStack_6a;
  undefined1 uStack_69;
  undefined1 uStack_68;
  undefined2 uStack_67;
  undefined2 uStack_65;
  undefined1 uStack_63;
  undefined2 uStack_62;
  undefined1 local_60;
  undefined1 uStack_5f;
  undefined6 uStack_5e;
  undefined8 local_50;
  ulong uStack_48;
  void *local_40;
  long local_38;
  
  *in_x18 = unaff_x30;
  lVar4 = tpidr_el0;
  local_38 = *(long *)(lVar4 + 0x28);
  *(undefined8 *)in_x8 = 0;
  *(undefined8 *)(in_x8 + 8) = 0;
  *(undefined8 *)(in_x8 + 0x10) = 0;
  std::string::append(in_x8,"{");
  SVar2 = *param_1;
  if (SVar2 == (SehAudioCapabilities)0x2) {
    std::string::append(in_x8,".leAudioCapabilities = ");
    pbVar8 = (byte *)SehCodecCapabilities::Capabilities::ldacCapabilities(param_1);
    local_98 = 0;
    local_90 = (void *)0x0;
    local_a0 = 0;
    std::string::append((string *)&local_a0,"{");
    std::string::append((string *)&local_a0,".supportedChannelCounts = ");
    std::to_string((uint)*pbVar8);
    std::string::append_abi_nn220000_((string *)&local_a0,(string *)&local_50);
    if ((local_50 & 1) != 0) {
      operator_delete(local_40,local_50 & 0xfffffffffffffffe);
    }
    std::string::append((string *)&local_a0,", .lc3Capabilities = ");
    local_88 = 0;
    local_80 = 0;
    local_78 = (void *)0x0;
    std::string::append((string *)&local_88,"{");
    std::string::append((string *)&local_88,".pcmBitDepth = ");
    bVar3 = pbVar8[4];
    if (bVar3 < 2) {
      if (bVar3 == 0) {
        uStack_67 = 0x4f4e;
        uStack_65 = 0x4e57;
        local_70 = 0x54494218;
        uStack_6c = 0x53;
        uStack_6b = 0x5f;
        uStack_6a = 0x55;
        uStack_69 = 0x4e;
        uStack_68 = 0x4b;
        uStack_63 = 0;
      }
      else {
        if (bVar3 == 1) {
          uVar14 = 0x36315f53;
          goto LAB_009b8784;
        }
LAB_009b88c4:
        local_70 = 0;
        uStack_6c = 0;
        uStack_6b = 0;
        uStack_6a = 0;
        uStack_69 = 0;
        uStack_68 = 0;
        uStack_67 = 0;
        uStack_65 = 0;
        uStack_63 = 0;
        uStack_62 = 0;
        local_60 = 0;
        uStack_5f = 0;
        uStack_5e = 0;
        android::hardware::details::toHexString<int,int>((details *)(ulong)bVar3,1,(bool)in_w2);
        std::string::append_abi_nn220000_((string *)&local_70,(string *)&local_50);
        if ((local_50 & 1) != 0) {
          operator_delete(local_40,local_50 & 0xfffffffffffffffe);
        }
      }
    }
    else {
      if (bVar3 == 2) {
        uVar14 = 0x34325f53;
      }
      else {
        if (bVar3 != 4) {
          if (bVar3 != 8) goto LAB_009b88c4;
          uStack_67 = 0x38;
          local_70 = 0x54494212;
          uStack_6c = 0x53;
          uStack_6b = 0x5f;
          uStack_6a = 0x33;
          uStack_69 = 0x32;
          uStack_68 = 0x5f;
          goto LAB_009b88fc;
        }
        uVar14 = 0x32335f53;
      }
LAB_009b8784:
      local_70 = 0x5449420e;
      uStack_6c = (undefined1)uVar14;
      uStack_6b = (undefined1)((uint)uVar14 >> 8);
      uStack_6a = (undefined1)((uint)uVar14 >> 0x10);
      uStack_69 = (undefined1)((uint)uVar14 >> 0x18);
      uStack_68 = 0;
    }
LAB_009b88fc:
    std::string::append_abi_nn220000_((string *)&local_88,(string *)&local_70);
    if ((local_70 & 1) != 0) {
      operator_delete((void *)CONCAT62(uStack_5e,CONCAT11(uStack_5f,local_60)),
                      CONCAT17(uStack_69,
                               CONCAT16(uStack_6a,CONCAT15(uStack_6b,CONCAT14(uStack_6c,local_70))))
                      & 0xfffffffffffffffe);
    }
    std::string::append((string *)&local_88,", .samplingFrequency = ");
    toString(&local_50,*(undefined4 *)(pbVar8 + 8));
    std::string::append_abi_nn220000_((string *)&local_88,(string *)&local_50);
    if ((local_50 & 1) != 0) {
      operator_delete(local_40,local_50 & 0xfffffffffffffffe);
    }
    std::string::append((string *)&local_88,", .frameDuration = ");
    bVar3 = pbVar8[0xc];
    if (bVar3 == 1) {
      local_60 = 0;
      local_70 = 0x5255441e;
      uStack_6c = 0x41;
      uStack_6b = 0x54;
      uStack_6a = 0x49;
      uStack_69 = 0x4f;
      uStack_68 = 0x4e;
      uStack_67 = 0x375f;
      uStack_65 = 0x3035;
      uStack_63 = 0x30;
      uStack_62 = 0x5355;
    }
    else if (bVar3 == 0) {
      uStack_5f = 0;
      uStack_67 = 0x315f;
      uStack_65 = 0x3030;
      uStack_63 = 0x30;
      uStack_62 = 0x5530;
      local_60 = 0x53;
      local_70 = 0x52554420;
      uStack_6c = 0x41;
      uStack_6b = 0x54;
      uStack_6a = 0x49;
      uStack_69 = 0x4f;
      uStack_68 = 0x4e;
    }
    else {
      local_70 = 0;
      uStack_6c = 0;
      uStack_6b = 0;
      uStack_6a = 0;
      uStack_69 = 0;
      uStack_68 = 0;
      uStack_67 = 0;
      uStack_65 = 0;
      uStack_63 = 0;
      uStack_62 = 0;
      local_60 = 0;
      uStack_5f = 0;
      uStack_5e = 0;
      android::hardware::details::toHexString<int,int>((details *)(ulong)bVar3,1,(bool)in_w2);
      std::string::append_abi_nn220000_((string *)&local_70,(string *)&local_50);
      if ((local_50 & 1) != 0) {
        operator_delete(local_40,local_50 & 0xfffffffffffffffe);
      }
    }
    std::string::append_abi_nn220000_((string *)&local_88,(string *)&local_70);
    if ((local_70 & 1) != 0) {
      operator_delete((void *)CONCAT62(uStack_5e,CONCAT11(uStack_5f,local_60)),
                      CONCAT17(uStack_69,
                               CONCAT16(uStack_6a,CONCAT15(uStack_6b,CONCAT14(uStack_6c,local_70))))
                      & 0xfffffffffffffffe);
    }
    std::string::append((string *)&local_88,", .octetsPerFrame = ");
    std::to_string(*(uint *)(pbVar8 + 0x10));
    std::string::append_abi_nn220000_((string *)&local_88,(string *)&local_50);
    if ((local_50 & 1) != 0) {
      operator_delete(local_40,local_50 & 0xfffffffffffffffe);
    }
    std::string::append((string *)&local_88,", .blocksPerSdu = ");
    std::to_string((uint)pbVar8[0x14]);
    std::string::append_abi_nn220000_((string *)&local_88,(string *)&local_50);
    if ((local_50 & 1) != 0) {
      operator_delete(local_40,local_50 & 0xfffffffffffffffe);
    }
    std::string::append((string *)&local_88,"}");
    std::string::append_abi_nn220000_((string *)&local_a0,(string *)&local_88);
    if ((local_88 & 1) != 0) {
      operator_delete(local_78,local_88 & 0xfffffffffffffffe);
    }
    std::string::append((string *)&local_a0,"}");
    std::string::append_abi_nn220000_(in_x8,(string *)&local_a0);
    uVar5 = local_a0;
    pvVar1 = local_90;
    goto joined_r0x009b84b0;
  }
  if (SVar2 != (SehAudioCapabilities)0x1) {
    if ((byte)SVar2 != 0) {
      std::to_string((uint)(byte)SVar2);
      puVar9 = (undefined8 *)
               std::string::insert((string *)&local_88,0,"Unknown union discriminator (value: ",0x24
                                  );
      uVar17 = puVar9[1];
      uVar16 = *puVar9;
      uVar15 = puVar9[2];
      uStack_68 = (undefined1)uVar17;
      uStack_67 = (undefined2)((ulong)uVar17 >> 8);
      uStack_65 = (undefined2)((ulong)uVar17 >> 0x18);
      uStack_63 = (undefined1)((ulong)uVar17 >> 0x28);
      uStack_62 = (undefined2)((ulong)uVar17 >> 0x30);
      local_70 = (uint)uVar16;
      uStack_6c = (undefined1)((ulong)uVar16 >> 0x20);
      uStack_6b = (undefined1)((ulong)uVar16 >> 0x28);
      uStack_6a = (undefined1)((ulong)uVar16 >> 0x30);
      uStack_69 = (undefined1)((ulong)uVar16 >> 0x38);
      local_60 = (undefined1)uVar15;
      uStack_5f = (undefined1)((ulong)uVar15 >> 8);
      uStack_5e = (undefined6)((ulong)uVar15 >> 0x10);
      puVar9[1] = 0;
      puVar9[2] = 0;
      *puVar9 = 0;
      puVar10 = (ulong *)std::string::append((string *)&local_70,").");
      uStack_48 = puVar10[1];
      local_50 = *puVar10;
      local_40 = (void *)puVar10[2];
      puVar10[1] = 0;
      puVar10[2] = 0;
      *puVar10 = 0;
      pvVar1 = local_40;
      if ((local_50 & 1) == 0) {
        pvVar1 = (void *)((long)&local_50 + 1);
      }
      android::hardware::details::logAlwaysFatal(pvVar1);
      if ((local_50 & 1) != 0) {
        operator_delete(local_40,local_50 & 0xfffffffffffffffe);
      }
      uVar5 = local_88;
      pvVar1 = local_78;
      if ((local_70 & 1) != 0) {
        operator_delete((void *)CONCAT62(uStack_5e,CONCAT11(uStack_5f,local_60)),
                        CONCAT17(uStack_69,
                                 CONCAT16(uStack_6a,CONCAT15(uStack_6b,CONCAT14(uStack_6c,local_70))
                                         )) & 0xfffffffffffffffe);
        uVar5 = local_88;
        pvVar1 = local_78;
      }
      goto joined_r0x009b84b0;
    }
    std::string::append(in_x8,".pcmCapabilities = ");
    puVar6 = (undefined4 *)SehCodecCapabilities::Capabilities::sbcCapabilities(param_1);
    local_80 = 0;
    local_78 = (void *)0x0;
    local_88 = 0;
    std::string::append((string *)&local_88,"{");
    std::string::append((string *)&local_88,".sampleRate = ");
    toString(&local_50,*puVar6);
    std::string::append_abi_nn220000_((string *)&local_88,(string *)&local_50);
    if ((local_50 & 1) != 0) {
      operator_delete(local_40,local_50 & 0xfffffffffffffffe);
    }
    std::string::append((string *)&local_88,", .channelMode = ");
    bVar3 = *(byte *)(puVar6 + 1);
    if (bVar3 == 2) {
      uStack_69 = 0;
      local_70 = 0x4554530c;
      uStack_6c = 0x52;
      uStack_6b = 0x45;
      uStack_6a = 0x4f;
    }
    else if (bVar3 == 1) {
      uStack_6b = 0;
      local_70 = 0x4e4f4d08;
      uStack_6c = 0x4f;
    }
    else if (bVar3 == 0) {
      uStack_68 = 0;
      local_70 = 0x4b4e550e;
      uStack_6c = 0x4e;
      uStack_6b = 0x4f;
      uStack_6a = 0x57;
      uStack_69 = 0x4e;
    }
    else {
      local_70 = 0;
      uStack_6c = 0;
      uStack_6b = 0;
      uStack_6a = 0;
      uStack_69 = 0;
      uStack_68 = 0;
      uStack_67 = 0;
      uStack_65 = 0;
      uStack_63 = 0;
      uStack_62 = 0;
      local_60 = 0;
      uStack_5f = 0;
      uStack_5e = 0;
      android::hardware::details::toHexString<int,int>((details *)(ulong)bVar3,1,(bool)in_w2);
      std::string::append_abi_nn220000_((string *)&local_70,(string *)&local_50);
      if ((local_50 & 1) != 0) {
        operator_delete(local_40,local_50 & 0xfffffffffffffffe);
      }
    }
    std::string::append_abi_nn220000_((string *)&local_88,(string *)&local_70);
    if ((local_70 & 1) != 0) {
      operator_delete((void *)CONCAT62(uStack_5e,CONCAT11(uStack_5f,local_60)),
                      CONCAT17(uStack_69,
                               CONCAT16(uStack_6a,CONCAT15(uStack_6b,CONCAT14(uStack_6c,local_70))))
                      & 0xfffffffffffffffe);
    }
    std::string::append((string *)&local_88,", .bitsPerSample = ");
    bVar3 = *(byte *)((long)puVar6 + 5);
    if (bVar3 < 2) {
      if (bVar3 == 0) {
        uStack_67 = 0x4f4e;
        uStack_65 = 0x4e57;
        local_70 = 0x54494218;
        uStack_6c = 0x53;
        uStack_6b = 0x5f;
        uStack_6a = 0x55;
        uStack_69 = 0x4e;
        uStack_68 = 0x4b;
        uStack_63 = 0;
      }
      else {
        if (bVar3 == 1) {
          uVar14 = 0x36315f53;
          goto LAB_009b87c8;
        }
LAB_009b8b08:
        local_70 = 0;
        uStack_6c = 0;
        uStack_6b = 0;
        uStack_6a = 0;
        uStack_69 = 0;
        uStack_68 = 0;
        uStack_67 = 0;
        uStack_65 = 0;
        uStack_63 = 0;
        uStack_62 = 0;
        local_60 = 0;
        uStack_5f = 0;
        uStack_5e = 0;
        android::hardware::details::toHexString<int,int>((details *)(ulong)bVar3,1,(bool)in_w2);
        std::string::append_abi_nn220000_((string *)&local_70,(string *)&local_50);
        if ((local_50 & 1) != 0) {
          operator_delete(local_40,local_50 & 0xfffffffffffffffe);
        }
      }
    }
    else {
      if (bVar3 == 2) {
        uVar14 = 0x34325f53;
      }
      else {
        if (bVar3 != 4) {
          if (bVar3 != 8) goto LAB_009b8b08;
          uStack_67 = 0x38;
          local_70 = 0x54494212;
          uStack_6c = 0x53;
          uStack_6b = 0x5f;
          uStack_6a = 0x33;
          uStack_69 = 0x32;
          uStack_68 = 0x5f;
          goto LAB_009b8b40;
        }
        uVar14 = 0x32335f53;
      }
LAB_009b87c8:
      local_70 = 0x5449420e;
      uStack_6c = (undefined1)uVar14;
      uStack_6b = (undefined1)((uint)uVar14 >> 8);
      uStack_6a = (undefined1)((uint)uVar14 >> 0x10);
      uStack_69 = (undefined1)((uint)uVar14 >> 0x18);
      uStack_68 = 0;
    }
LAB_009b8b40:
    std::string::append_abi_nn220000_((string *)&local_88,(string *)&local_70);
    if ((local_70 & 1) != 0) {
      operator_delete((void *)CONCAT62(uStack_5e,CONCAT11(uStack_5f,local_60)),
                      CONCAT17(uStack_69,
                               CONCAT16(uStack_6a,CONCAT15(uStack_6b,CONCAT14(uStack_6c,local_70))))
                      & 0xfffffffffffffffe);
    }
    std::string::append((string *)&local_88,", .dataIntervalUs = ");
    std::to_string(puVar6[2]);
    std::string::append_abi_nn220000_((string *)&local_88,(string *)&local_50);
    if ((local_50 & 1) != 0) {
      operator_delete(local_40,local_50 & 0xfffffffffffffffe);
    }
    std::string::append((string *)&local_88,"}");
    std::string::append_abi_nn220000_(in_x8,(string *)&local_88);
    uVar5 = local_88;
    pvVar1 = local_78;
    goto joined_r0x009b84b0;
  }
  std::string::append(in_x8,".codecCapabilities = ");
  puVar6 = (undefined4 *)SehAudioCapabilities::codecCapabilities(param_1);
  local_b0 = 0;
  local_a8 = (void *)0x0;
  local_b8 = 0;
  std::string::append((string *)&local_b8,"{");
  std::string::append((string *)&local_b8,".codecType = ");
  toString(&local_50,*puVar6);
  std::string::append_abi_nn220000_((string *)&local_b8,(string *)&local_50);
  if ((local_50 & 1) != 0) {
    operator_delete(local_40,local_50 & 0xfffffffffffffffe);
  }
  std::string::append((string *)&local_b8,", .capabilities = ");
  local_a0 = 0;
  local_98 = 0;
  local_90 = (void *)0x0;
  std::string::append((string *)&local_a0,"{");
  pbVar8 = (byte *)(puVar6 + 1);
  bVar3 = *pbVar8;
  if (bVar3 < 2) {
    if (bVar3 == 0) {
      std::string::append((string *)&local_a0,".sbcCapabilities = ");
      pSVar13 = (SehSbcParameters *)SehCodecCapabilities::Capabilities::sbcCapabilities(pbVar8);
      toString(pSVar13);
      goto LAB_009b86c8;
    }
    if (bVar3 == 1) {
      std::string::append((string *)&local_a0,".aacCapabilities = ");
      pSVar11 = (SehAacParameters *)SehAudioCapabilities::codecCapabilities(pbVar8);
      toString(pSVar11);
      goto LAB_009b86c8;
    }
LAB_009b8830:
    std::to_string((uint)bVar3);
    puVar9 = (undefined8 *)
             std::string::insert((string *)&local_88,0,"Unknown union discriminator (value: ",0x24);
    uVar17 = puVar9[1];
    uVar16 = *puVar9;
    uVar15 = puVar9[2];
    uStack_68 = (undefined1)uVar17;
    uStack_67 = (undefined2)((ulong)uVar17 >> 8);
    uStack_65 = (undefined2)((ulong)uVar17 >> 0x18);
    uStack_63 = (undefined1)((ulong)uVar17 >> 0x28);
    uStack_62 = (undefined2)((ulong)uVar17 >> 0x30);
    local_70 = (uint)uVar16;
    uStack_6c = (undefined1)((ulong)uVar16 >> 0x20);
    uStack_6b = (undefined1)((ulong)uVar16 >> 0x28);
    uStack_6a = (undefined1)((ulong)uVar16 >> 0x30);
    uStack_69 = (undefined1)((ulong)uVar16 >> 0x38);
    local_60 = (undefined1)uVar15;
    uStack_5f = (undefined1)((ulong)uVar15 >> 8);
    uStack_5e = (undefined6)((ulong)uVar15 >> 0x10);
    puVar9[1] = 0;
    puVar9[2] = 0;
    *puVar9 = 0;
    puVar10 = (ulong *)std::string::append((string *)&local_70,").");
    uStack_48 = puVar10[1];
    local_50 = *puVar10;
    local_40 = (void *)puVar10[2];
    puVar10[1] = 0;
    puVar10[2] = 0;
    *puVar10 = 0;
    pvVar1 = local_40;
    if ((local_50 & 1) == 0) {
      pvVar1 = (void *)((long)&local_50 + 1);
    }
    android::hardware::details::logAlwaysFatal(pvVar1);
    if ((local_50 & 1) != 0) {
      operator_delete(local_40,local_50 & 0xfffffffffffffffe);
    }
    uVar5 = local_88;
    pvVar1 = local_78;
    if ((local_70 & 1) != 0) {
      operator_delete((void *)CONCAT62(uStack_5e,CONCAT11(uStack_5f,local_60)),
                      CONCAT17(uStack_69,
                               CONCAT16(uStack_6a,CONCAT15(uStack_6b,CONCAT14(uStack_6c,local_70))))
                      & 0xfffffffffffffffe);
      uVar5 = local_88;
      pvVar1 = local_78;
    }
  }
  else {
    if (bVar3 == 2) {
      std::string::append((string *)&local_a0,".ldacCapabilities = ");
      pSVar12 = (SehLdacParameters *)SehCodecCapabilities::Capabilities::ldacCapabilities(pbVar8);
      toString(pSVar12);
    }
    else if (bVar3 == 3) {
      std::string::append((string *)&local_a0,".aptxCapabilities = ");
      pSVar7 = (SehSscParameters *)SehCodecCapabilities::Capabilities::aptxCapabilities(pbVar8);
      toString(pSVar7);
    }
    else {
      if (bVar3 != 4) goto LAB_009b8830;
      std::string::append((string *)&local_a0,".sscCapabilities = ");
      pSVar7 = (SehSscParameters *)SehCodecCapabilities::Capabilities::sscCapabilities(pbVar8);
      toString(pSVar7);
    }
LAB_009b86c8:
    std::string::append_abi_nn220000_((string *)&local_a0,(string *)&local_50);
    uVar5 = local_50;
    pvVar1 = local_40;
  }
  if ((uVar5 & 1) != 0) {
    operator_delete(pvVar1,uVar5 & 0xfffffffffffffffe);
  }
  std::string::append((string *)&local_a0,"}");
  std::string::append_abi_nn220000_((string *)&local_b8,(string *)&local_a0);
  if ((local_a0 & 1) != 0) {
    operator_delete(local_90,local_a0 & 0xfffffffffffffffe);
  }
  std::string::append((string *)&local_b8,"}");
  std::string::append_abi_nn220000_(in_x8,(string *)&local_b8);
  uVar5 = local_b8;
  pvVar1 = local_a8;
joined_r0x009b84b0:
  if ((uVar5 & 1) != 0) {
    operator_delete(pvVar1,uVar5 & 0xfffffffffffffffe);
  }
  std::string::append(in_x8,"}");
  if (*(long *)(lVar4 + 0x28) == local_38) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== IsCodecOffloadingEnabled @ 009b9900 size 3040 :: , .isScmstEnabled =  | .sscConfig =  | ssc_offloading_capability_match */

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Unknown calling convention: __rustcall */
/* bluetooth::audio::hidl::codec::_GLOBAL__N_1::IsCodecOffloadingEnabled */

void __rustcall bluetooth::audio::hidl::codec::_GLOBAL__N_1::IsCodecOffloadingEnabled(int *param_1)

{
  byte bVar1;
  long lVar2;
  char *pcVar3;
  SehAudioCapabilities *pSVar4;
  void *pvVar5;
  SehAudioCapabilities *pSVar6;
  bool bVar7;
  bool bVar8;
  bool bVar9;
  int iVar10;
  int *piVar11;
  undefined4 *puVar12;
  SehSscParameters *pSVar13;
  ostream *poVar14;
  SehAacParameters *pSVar15;
  SehLdacParameters *pSVar16;
  SehSbcParameters *pSVar17;
  ulong *puVar18;
  undefined8 *puVar19;
  undefined8 uVar20;
  char *pcVar21;
  undefined8 uVar22;
  undefined4 uVar23;
  undefined8 *in_x18;
  byte *pbVar24;
  bool bVar25;
  ulong uVar26;
  undefined8 unaff_x30;
  undefined8 local_268;
  undefined4 local_260;
  undefined8 local_258;
  undefined4 local_250;
  undefined8 local_248;
  undefined8 uStack_240;
  undefined4 local_238;
  ulong local_230;
  char *pcStack_228;
  char *local_220;
  undefined4 local_218;
  ulong local_208;
  char *local_200;
  char *pcStack_1f8;
  byte local_1f0;
  undefined7 uStack_1ef;
  ulong local_1e8;
  char *local_1e0;
  undefined8 local_1d8;
  ulong local_1d0;
  void *local_1c8;
  undefined8 local_1c0;
  undefined8 *local_1b8;
  char *local_1b0;
  undefined8 local_1a8;
  char *local_1a0;
  char *local_198;
  undefined8 local_190;
  ulong uStack_188;
  char *local_180;
  ulong local_178;
  undefined8 uStack_170;
  long local_68;
  
  *in_x18 = unaff_x30;
  iVar10 = DAT_010338a0;
  lVar2 = tpidr_el0;
  local_68 = *(long *)(lVar2 + 0x28);
  local_230 = CONCAT44(local_230._4_4_,0xcb);
  local_1a0 = (char *)&local_190;
  local_1a8 = (void *)0x1;
  local_190 = (void *)(ulong)(DAT_010338a0 == 2);
  pcStack_228 = "packages/modules/Bluetooth/system/audio_hal_interface/hidl/codec_status_hidl.cc";
  local_220 = "IsCodecOffloadingEnabled";
  uStack_188 = 0;
  local_180 = (char *)0x1;
  local_198 = (char *)0x1;
  log_internal::vlog(5,"BTAudioCodecStatusHIDL",&local_230,"offload mode - {}",0x11,&local_1a8);
  pSVar6 = DAT_01033ee0;
  pSVar4 = DAT_01033ed8;
  if (iVar10 != 2) goto LAB_009b9f38;
  for (; pSVar4 != pSVar6; pSVar4 = pSVar4 + 0x1c) {
    local_230 = 0;
    pcStack_228 = (char *)0x0;
    local_218 = 0;
    local_220 = (char *)0x0;
    vendor::samsung::hardware::bluetooth::audio::V2_0::SehAudioCapabilities::SehAudioCapabilities
              ((SehAudioCapabilities *)&local_230,pSVar4);
    iVar10 = *param_1;
    piVar11 = (int *)vendor::samsung::hardware::bluetooth::audio::V2_0::SehAudioCapabilities::
                     codecCapabilities(&local_230);
    if (iVar10 == *piVar11) {
      local_248 = 0;
      uStack_240 = 0;
      local_238 = 0;
      puVar12 = (undefined4 *)
                vendor::samsung::hardware::bluetooth::audio::V2_0::SehAudioCapabilities::
                codecCapabilities(&local_230);
      local_248 = CONCAT44(local_248._4_4_,*puVar12);
      vendor::samsung::hardware::bluetooth::audio::V2_0::SehCodecCapabilities::Capabilities::
      Capabilities((Capabilities *)((long)&local_248 + 4),(Capabilities *)(puVar12 + 1));
      if ((int)local_248 != 2) {
        if ((int)local_248 < 8) {
          if ((int)local_248 == 1) {
            puVar18 = (ulong *)vendor::samsung::hardware::bluetooth::audio::V2_0::
                               SehCodecCapabilities::Capabilities::sbcCapabilities
                                         ((long)&local_248 + 4);
            local_258 = *puVar18;
            local_250 = (undefined4)puVar18[1];
            puVar19 = (undefined8 *)
                      vendor::samsung::hardware::bluetooth::audio::V2_0::SehCodecCapabilities::
                      Capabilities::sbcCapabilities(param_1 + 3);
            uVar20 = *puVar19;
            uVar23 = *(undefined4 *)(puVar19 + 1);
            local_268 = uVar20;
            local_260 = uVar23;
            if (((uint)uVar20 & (uint)local_258) != 0) {
              local_268._4_1_ = (byte)((ulong)uVar20 >> 0x20);
              if ((local_268._4_1_ & local_258._4_1_) != 0) {
                local_268._5_1_ = (byte)((ulong)uVar20 >> 0x28);
                if ((local_268._5_1_ & local_258._5_1_) != 0) {
                  local_268._6_1_ = (byte)((ulong)uVar20 >> 0x30);
                  if ((local_268._6_1_ & local_258._6_1_) != 0) {
                    local_268._7_1_ = (byte)((ulong)uVar20 >> 0x38);
                    if ((local_268._7_1_ & local_258._7_1_) != 0) {
                      local_260._0_1_ = (byte)uVar23;
                      if (((byte)local_260 & (byte)local_250) != 0) {
                        local_260._1_1_ = (byte)((uint)uVar23 >> 8);
                        if (((local_250._1_1_ <= local_260._1_1_) &&
                            (local_260._2_1_ = (byte)((uint)uVar23 >> 0x10),
                            local_260._1_1_ <= local_260._2_1_)) &&
                           (local_260._2_1_ <= local_250._2_1_)) {
                          vendor::samsung::hardware::bluetooth::audio::V2_0::toString
                                    ((SehSbcParameters *)&local_268);
                          vendor::samsung::hardware::bluetooth::audio::V2_0::toString
                                    ((SehSbcParameters *)&local_258);
                          local_208 = CONCAT44(local_208._4_4_,0x71);
                          local_200 = 
                          "packages/modules/Bluetooth/system/audio_hal_interface/hidl/codec_status_hidl.cc"
                          ;
                          pcStack_1f8 = "sbc_offloading_capability_match";
                          bluetooth::log::verbose<std::string,std::string>::log
                                    (&local_190,&local_1a8,&local_208);
                          if (((ulong)local_1a8 & 1) != 0) {
                            operator_delete(local_198,(ulong)local_1a8 & 0xfffffffffffffffe);
                          }
                          if (((ulong)local_190 & 1) != 0) {
                            operator_delete(local_180,(ulong)local_190 & 0xfffffffffffffffe);
                          }
                          bVar25 = true;
                          goto LAB_009ba404;
                        }
                      }
                    }
                  }
                }
              }
            }
            vendor::samsung::hardware::bluetooth::audio::V2_0::toString
                      ((SehSbcParameters *)&local_268);
            vendor::samsung::hardware::bluetooth::audio::V2_0::toString
                      ((SehSbcParameters *)&local_258);
            local_1a0 = 
            "packages/modules/Bluetooth/system/audio_hal_interface/hidl/codec_status_hidl.cc";
            local_198 = "sbc_offloading_capability_match";
            local_1a8 = (void *)CONCAT44(local_1a8._4_4_,0x6e);
            uStack_188 = local_1d0;
            local_190 = local_1c8;
            if ((local_1d8 & 1) == 0) {
              uStack_188 = local_1d8 >> 1 & 0x7f;
              local_190 = (void *)((long)&local_1d8 + 1);
            }
            local_180 = local_1e0;
            if ((local_1f0 & 1) == 0) {
              local_1e8 = (ulong)(local_1f0 >> 1);
              local_180 = (char *)&uStack_1ef;
            }
            uStack_170 = 0x1ad;
            local_1b8 = &local_190;
            local_1c0 = 2;
            local_1b0 = (char *)0x1ad;
            local_178 = local_1e8;
            log_internal::vlog(5,"BTAudioCodecStatusHIDL",&local_1a8,
                               "software codec={} capability={}",0x1f,&local_1c0);
            if ((local_1f0 & 1) != 0) {
              operator_delete(local_1e0,CONCAT71(uStack_1ef,local_1f0) & 0xfffffffffffffffe);
            }
          }
          else {
            if ((int)local_248 == 4) goto LAB_009b9d74;
LAB_009ba230:
            vendor::samsung::hardware::bluetooth::audio::V2_0::toString(&local_1d8);
            local_1a8 = (void *)CONCAT44(local_1a8._4_4_,0xfa);
            uStack_188 = local_1d0;
            local_190 = local_1c8;
            if ((local_1d8 & 1) == 0) {
              uStack_188 = local_1d8 >> 1 & 0x7f;
              local_190 = (void *)((long)&local_1d8 + 1);
            }
            local_180 = &DAT_0000000d;
            local_1b8 = &local_190;
            local_1a0 = 
            "packages/modules/Bluetooth/system/audio_hal_interface/hidl/codec_status_hidl.cc";
            local_198 = "IsCodecOffloadingEnabled";
            local_1c0 = 1;
            local_1b0 = &DAT_0000000d;
            log_internal::vlog(6,"BTAudioCodecStatusHIDL",&local_1a8,"Unknown codecType={}",0x14,
                               &local_1c0);
          }
          if ((local_1d8 & 1) != 0) {
            operator_delete(local_1c8,local_1d8 & 0xfffffffffffffffe);
          }
          bVar25 = false;
        }
        else {
          if ((int)local_248 == 8) {
LAB_009b9d74:
            puVar18 = (ulong *)vendor::samsung::hardware::bluetooth::audio::V2_0::
                               SehCodecCapabilities::Capabilities::aptxCapabilities
                                         ((long)&local_248 + 4);
            uVar26 = *puVar18;
            local_208 = uVar26;
            puVar18 = (ulong *)vendor::samsung::hardware::bluetooth::audio::V2_0::
                               SehCodecCapabilities::Capabilities::aptxCapabilities(param_1 + 3);
            local_258 = *puVar18;
            uVar26 = local_258 & uVar26;
            bVar7 = (uVar26 & 0xff0000000000) != 0;
            bVar8 = (uVar26 & 0xff00000000) != 0;
            bVar9 = (int)uVar26 != 0;
            bVar25 = (bVar8 && bVar9) && bVar7;
            if ((!bVar8 || !bVar9) || !bVar7) {
              vendor::samsung::hardware::bluetooth::audio::V2_0::toString
                        ((SehSscParameters *)&local_258);
              vendor::samsung::hardware::bluetooth::audio::V2_0::toString
                        ((SehSscParameters *)&local_208);
              uVar26 = local_1d8 & 0xff;
              local_198 = "aptx_offloading_capability_match";
              uVar23 = 0x93;
              goto LAB_009ba35c;
            }
            vendor::samsung::hardware::bluetooth::audio::V2_0::toString
                      ((SehSscParameters *)&local_258);
            vendor::samsung::hardware::bluetooth::audio::V2_0::toString
                      ((SehSscParameters *)&local_208);
            local_198 = "aptx_offloading_capability_match";
            uVar23 = 0x96;
LAB_009ba048:
            local_1a8 = (void *)CONCAT44(local_1a8._4_4_,uVar23);
            uStack_188 = local_1d0;
            local_190 = local_1c8;
            if (((byte)local_1d8._0_1_ & 1) == 0) {
              uStack_188 = (ulong)((byte)local_1d8._0_1_ >> 1);
              local_190 = (void *)((long)&local_1d8 + 1);
            }
            pcVar21 = "offloading codec={} capability={}";
            uVar20 = 2;
            uVar22 = 0x21;
          }
          else {
            if ((int)local_248 != 0x10) {
              if ((int)local_248 != 0x20) goto LAB_009ba230;
              puVar18 = (ulong *)vendor::samsung::hardware::bluetooth::audio::V2_0::
                                 SehCodecCapabilities::Capabilities::sscCapabilities
                                           ((long)&local_248 + 4);
              uVar26 = *puVar18;
              local_208 = uVar26;
              puVar18 = (ulong *)vendor::samsung::hardware::bluetooth::audio::V2_0::
                                 SehCodecCapabilities::Capabilities::sscCapabilities(param_1 + 3);
              local_258 = *puVar18;
              uVar26 = local_258 & uVar26;
              bVar7 = (uVar26 & 0xff0000000000) != 0;
              bVar8 = (uVar26 & 0xff00000000) != 0;
              bVar9 = (int)uVar26 != 0;
              bVar25 = (bVar8 && bVar9) && bVar7;
              if ((!bVar8 || !bVar9) || !bVar7) {
                vendor::samsung::hardware::bluetooth::audio::V2_0::toString
                          ((SehSscParameters *)&local_258);
                vendor::samsung::hardware::bluetooth::audio::V2_0::toString
                          ((SehSscParameters *)&local_208);
                uVar26 = local_1d8 & 0xff;
                local_198 = "ssc_offloading_capability_match";
                uVar23 = 0xb7;
                goto LAB_009ba35c;
              }
              iVar10 = A2dpCodecConfigExt::init
                                 ("packages/modules/Bluetooth/system/audio_hal_interface/hidl/codec_status_hidl.cc"
                                  ,0x50);
              if (0 < iVar10) {
                logging::LogMessage::LogMessage
                          ((LogMessage *)&local_190,
                           "packages/modules/Bluetooth/system/audio_hal_interface/hidl/codec_status_hidl.cc"
                           ,0xbb,-1);
                poVar14 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                                    ((ostream *)&uStack_188,"ssc_offloading_capability_match",0x1f);
                poVar14 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                                    (poVar14,": offloading codec=",0x13);
                vendor::samsung::hardware::bluetooth::audio::V2_0::toString
                          ((SehSscParameters *)&local_258);
                pcVar21 = local_1a0;
                pcVar3 = local_198;
                if (((ulong)local_1a8 & 1) == 0) {
                  pcVar21 = (char *)((ulong)local_1a8 >> 1 & 0x7f);
                  pcVar3 = (char *)((long)&local_1a8 + 1);
                }
                poVar14 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                                    (poVar14,pcVar3,(ulong)pcVar21);
                poVar14 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                                    (poVar14," capability=",0xc);
                vendor::samsung::hardware::bluetooth::audio::V2_0::toString
                          ((SehSscParameters *)&local_208);
                puVar19 = local_1b8;
                pcVar21 = local_1b0;
                if ((local_1c0 & 1) == 0) {
                  puVar19 = (undefined8 *)(local_1c0 >> 1 & 0x7f);
                  pcVar21 = (char *)((long)&local_1c0 + 1);
                }
                std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                          (poVar14,pcVar21,(ulong)puVar19);
                if ((local_1c0 & 1) != 0) {
                  operator_delete(local_1b0,local_1c0 & 0xfffffffffffffffe);
                }
                if (((ulong)local_1a8 & 1) != 0) {
                  operator_delete(local_198,(ulong)local_1a8 & 0xfffffffffffffffe);
                }
                logging::LogMessage::~LogMessage((LogMessage *)&local_190);
              }
              goto LAB_009ba404;
            }
            puVar18 = (ulong *)vendor::samsung::hardware::bluetooth::audio::V2_0::
                               SehCodecCapabilities::Capabilities::ldacCapabilities
                                         ((long)&local_248 + 4);
            uVar26 = *puVar18;
            local_208 = uVar26;
            puVar18 = (ulong *)vendor::samsung::hardware::bluetooth::audio::V2_0::
                               SehCodecCapabilities::Capabilities::ldacCapabilities(param_1 + 3);
            local_258 = *puVar18;
            uVar26 = local_258 & uVar26;
            bVar7 = (uVar26 & 0xff000000000000) != 0;
            bVar8 = (uVar26 & 0xff00000000) != 0;
            bVar9 = (int)uVar26 != 0;
            bVar25 = (bVar8 && bVar9) && bVar7;
            if ((bVar8 && bVar9) && bVar7) {
              vendor::samsung::hardware::bluetooth::audio::V2_0::toString
                        ((SehLdacParameters *)&local_258);
              vendor::samsung::hardware::bluetooth::audio::V2_0::toString
                        ((SehLdacParameters *)&local_208);
              local_198 = "ldac_offloading_capability_match";
              uVar23 = 0xa6;
              goto LAB_009ba048;
            }
            vendor::samsung::hardware::bluetooth::audio::V2_0::toString
                      ((SehLdacParameters *)&local_258);
            vendor::samsung::hardware::bluetooth::audio::V2_0::toString
                      ((SehLdacParameters *)&local_208);
            uVar26 = local_1d8 & 0xff;
            local_198 = "ldac_offloading_capability_match";
            uVar23 = 0xa3;
LAB_009ba35c:
            local_1a8 = (void *)CONCAT44(local_1a8._4_4_,uVar23);
            uStack_188 = local_1d0;
            local_190 = local_1c8;
            if ((uVar26 & 1) == 0) {
              uStack_188 = uVar26 >> 1;
              local_190 = (void *)((long)&local_1d8 + 1);
            }
            pcVar21 = "software codec={} capability={}";
            uVar20 = 5;
            uVar22 = 0x1f;
          }
          local_1a0 = 
          "packages/modules/Bluetooth/system/audio_hal_interface/hidl/codec_status_hidl.cc";
          local_1b0 = (char *)0x1ad;
          local_180 = local_1e0;
          if ((local_1f0 & 1) == 0) {
            local_1e8 = (ulong)(local_1f0 >> 1);
            local_180 = (char *)&uStack_1ef;
          }
          uStack_170 = 0x1ad;
          local_1b8 = &local_190;
          local_1c0 = 2;
          local_178 = local_1e8;
          log_internal::vlog(uVar20,"BTAudioCodecStatusHIDL",&local_1a8,pcVar21,uVar22,&local_1c0);
          if ((local_1f0 & 1) != 0) {
            operator_delete(local_1e0,CONCAT71(uStack_1ef,local_1f0) & 0xfffffffffffffffe);
          }
          if ((local_1d8 & 1) != 0) {
            operator_delete(local_1c8,local_1d8 & 0xfffffffffffffffe);
          }
        }
LAB_009ba404:
        vendor::samsung::hardware::bluetooth::audio::V2_0::SehCodecCapabilities::Capabilities::
        hidl_destructUnion((long)&local_248 + 4);
        vendor::samsung::hardware::bluetooth::audio::V2_0::SehAudioCapabilities::hidl_destructUnion
                  (&local_230);
        goto LAB_009ba418;
      }
      vendor::samsung::hardware::bluetooth::audio::V2_0::SehCodecCapabilities::Capabilities::
      hidl_destructUnion((long)&local_248 + 4);
    }
    vendor::samsung::hardware::bluetooth::audio::V2_0::SehAudioCapabilities::hidl_destructUnion
              (&local_230);
  }
  local_1d8 = 0;
  local_1d0 = 0;
  local_1c8 = (void *)0x0;
  std::string::append((string *)&local_1d8,"{");
  std::string::append((string *)&local_1d8,".codecType = ");
  vendor::samsung::hardware::bluetooth::audio::V2_0::toString(&local_190,*param_1);
  std::string::append_abi_nn220000_((string *)&local_1d8,(string *)&local_190);
  if (((ulong)local_190 & 1) != 0) {
    operator_delete(local_180,(ulong)local_190 & 0xfffffffffffffffe);
  }
  std::string::append((string *)&local_1d8,", .encodedAudioBitrate = ");
  std::to_string(param_1[1]);
  std::string::append_abi_nn220000_((string *)&local_1d8,(string *)&local_190);
  if (((ulong)local_190 & 1) != 0) {
    operator_delete(local_180,(ulong)local_190 & 0xfffffffffffffffe);
  }
  std::string::append((string *)&local_1d8,", .peerMtu = ");
  std::to_string((uint)*(ushort *)(param_1 + 2));
  std::string::append_abi_nn220000_((string *)&local_1d8,(string *)&local_190);
  if (((ulong)local_190 & 1) != 0) {
    operator_delete(local_180,(ulong)local_190 & 0xfffffffffffffffe);
  }
  std::string::append((string *)&local_1d8,", .isScmstEnabled = ");
  std::to_string((uint)*(byte *)((long)param_1 + 10));
  std::string::append_abi_nn220000_((string *)&local_1d8,(string *)&local_190);
  if (((ulong)local_190 & 1) != 0) {
    operator_delete(local_180,(ulong)local_190 & 0xfffffffffffffffe);
  }
  std::string::append((string *)&local_1d8,", .config = ");
  local_1c0 = 0;
  local_1b8 = (undefined8 *)0x0;
  local_1b0 = (char *)0x0;
  std::string::append((string *)&local_1c0,"{");
  pbVar24 = (byte *)(param_1 + 3);
  bVar1 = *pbVar24;
  if (bVar1 < 2) {
    if (bVar1 == 0) {
      std::string::append((string *)&local_1c0,".sbcConfig = ");
      pSVar17 = (SehSbcParameters *)
                vendor::samsung::hardware::bluetooth::audio::V2_0::SehCodecCapabilities::
                Capabilities::sbcCapabilities(pbVar24);
      vendor::samsung::hardware::bluetooth::audio::V2_0::toString(pSVar17);
      goto LAB_009b9e54;
    }
    if (bVar1 == 1) {
      std::string::append((string *)&local_1c0,".aacConfig = ");
      pSVar15 = (SehAacParameters *)
                vendor::samsung::hardware::bluetooth::audio::V2_0::SehAudioCapabilities::
                codecCapabilities(pbVar24);
      vendor::samsung::hardware::bluetooth::audio::V2_0::toString(pSVar15);
      goto LAB_009b9e54;
    }
LAB_009b9f40:
    std::to_string((uint)bVar1);
    puVar18 = (ulong *)std::string::insert((string *)&local_1a8,0,
                                           "Unknown union discriminator (value: ",0x24);
    pcStack_228 = (char *)puVar18[1];
    local_230 = *puVar18;
    local_220 = (char *)puVar18[2];
    puVar18[1] = 0;
    puVar18[2] = 0;
    *puVar18 = 0;
    puVar18 = (ulong *)std::string::append((string *)&local_230,").");
    uStack_188 = puVar18[1];
    local_190 = (void *)*puVar18;
    local_180 = (char *)puVar18[2];
    puVar18[1] = 0;
    puVar18[2] = 0;
    *puVar18 = 0;
    pcVar21 = local_180;
    if (((ulong)local_190 & 1) == 0) {
      pcVar21 = (char *)((long)&local_190 + 1);
    }
    android::hardware::details::logAlwaysFatal(pcVar21);
    if (((ulong)local_190 & 1) != 0) {
      operator_delete(local_180,(ulong)local_190 & 0xfffffffffffffffe);
    }
    pvVar5 = local_1a8;
    pcVar21 = local_198;
    if ((local_230 & 1) != 0) {
      operator_delete(local_220,local_230 & 0xfffffffffffffffe);
      pvVar5 = local_1a8;
      pcVar21 = local_198;
    }
  }
  else {
    if (bVar1 == 2) {
      std::string::append((string *)&local_1c0,".ldacConfig = ");
      pSVar16 = (SehLdacParameters *)
                vendor::samsung::hardware::bluetooth::audio::V2_0::SehCodecCapabilities::
                Capabilities::ldacCapabilities(pbVar24);
      vendor::samsung::hardware::bluetooth::audio::V2_0::toString(pSVar16);
    }
    else if (bVar1 == 3) {
      std::string::append((string *)&local_1c0,".aptxConfig = ");
      pSVar13 = (SehSscParameters *)
                vendor::samsung::hardware::bluetooth::audio::V2_0::SehCodecCapabilities::
                Capabilities::aptxCapabilities(pbVar24);
      vendor::samsung::hardware::bluetooth::audio::V2_0::toString(pSVar13);
    }
    else {
      if (bVar1 != 4) goto LAB_009b9f40;
      std::string::append((string *)&local_1c0,".sscConfig = ");
      pSVar13 = (SehSscParameters *)
                vendor::samsung::hardware::bluetooth::audio::V2_0::SehCodecCapabilities::
                Capabilities::sscCapabilities(pbVar24);
      vendor::samsung::hardware::bluetooth::audio::V2_0::toString(pSVar13);
    }
LAB_009b9e54:
    std::string::append_abi_nn220000_((string *)&local_1c0,(string *)&local_190);
    pvVar5 = local_190;
    pcVar21 = local_180;
  }
  if (((ulong)pvVar5 & 1) != 0) {
    operator_delete(pcVar21,(ulong)pvVar5 & 0xfffffffffffffffe);
  }
  std::string::append((string *)&local_1c0,"}");
  std::string::append_abi_nn220000_((string *)&local_1d8,(string *)&local_1c0);
  if ((local_1c0 & 1) != 0) {
    operator_delete(local_1b0,local_1c0 & 0xfffffffffffffffe);
  }
  std::string::append((string *)&local_1d8,"}");
  local_230 = CONCAT44(local_230._4_4_,0xfe);
  uStack_188 = local_1d0;
  local_190 = local_1c8;
  if ((local_1d8 & 1) == 0) {
    uStack_188 = local_1d8 >> 1 & 0x7f;
    local_190 = (void *)((long)&local_1d8 + 1);
  }
  local_198 = &DAT_0000000d;
  local_180 = &DAT_0000000d;
  local_1a0 = (char *)&local_190;
  pcStack_228 = "packages/modules/Bluetooth/system/audio_hal_interface/hidl/codec_status_hidl.cc";
  local_220 = "IsCodecOffloadingEnabled";
  local_1a8 = (void *)0x1;
  log_internal::vlog(4,"BTAudioCodecStatusHIDL",&local_230,"software codec={}",0x11,&local_1a8);
  if ((local_1d8 & 1) != 0) {
    operator_delete(local_1c8,local_1d8 & 0xfffffffffffffffe);
  }
LAB_009b9f38:
  bVar25 = false;
LAB_009ba418:
  if (*(long *)(lVar2 + 0x28) == local_68) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(bVar25);
}


/* ==== A2DP_IsVendorSourceCodecValidSsc @ 00a90788 size 240 :: A2DP_IsVendorSourceCodecValidSsc | a2dp_vendor_ssc | packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc */

/* A2DP_IsVendorSourceCodecValidSsc(unsigned char const*) */

bool A2DP_IsVendorSourceCodecValidSsc(uchar *param_1)

{
  long lVar1;
  bool bVar2;
  char cVar3;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  undefined8 local_90;
  ulong *puStack_88;
  undefined8 local_80;
  undefined4 local_78 [2];
  char *local_70;
  char *pcStack_68;
  ulong local_60 [5];
  long local_38;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_38 = *(long *)(lVar1 + 0x28);
  bVar2 = true;
  local_78[0] = 0xca;
  local_70 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
  pcStack_68 = "A2DP_IsVendorSourceCodecValidSsc";
  local_60[0] = (ulong)param_1[9];
  puStack_88 = local_60;
  local_60[1] = 0;
  local_60[2] = 6;
  local_90 = 1;
  local_80 = 6;
  bluetooth::log_internal::vlog(4,"a2dp_vendor_ssc",local_78,&DAT_00150033,8,&local_90);
  cVar3 = A2DP_ParseInfoSsc((tA2DP_SSC_CIE *)local_60,param_1,false);
  if (cVar3 != '\0') {
    cVar3 = A2DP_ParseInfoSsc((tA2DP_SSC_CIE *)local_60,param_1,true);
    bVar2 = cVar3 == '\0';
  }
  if (*(long *)(lVar1 + 0x28) == local_38) {
    return bVar2;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== A2DP_ParseInfoSsc @ 00a90878 size 460 :: A2DP_ParseInfoSsc | a2dp_vendor_ssc | packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc */

/* A2DP_ParseInfoSsc(tA2DP_SSC_CIE*, unsigned char const*, bool) */

undefined8 A2DP_ParseInfoSsc(tA2DP_SSC_CIE *param_1,uchar *param_2,bool param_3)

{
  int iVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  short sVar5;
  long lVar6;
  char cVar7;
  undefined8 uVar8;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  undefined8 local_100;
  ulong *puStack_f8;
  undefined8 local_f0;
  undefined4 local_e8 [2];
  char *local_e0;
  char *pcStack_d8;
  ulong local_d0 [3];
  undefined8 uStack_b8;
  ulong local_b0;
  undefined8 uStack_a8;
  ulong local_a0;
  undefined8 uStack_98;
  ulong local_90;
  undefined8 uStack_88;
  ulong local_80;
  undefined8 uStack_78;
  ulong local_70;
  undefined8 uStack_68;
  ulong local_60;
  undefined8 local_58;
  undefined8 uStack_50;
  long local_38;
  
  *in_x18 = unaff_x30;
  lVar6 = tpidr_el0;
  local_38 = *(long *)(lVar6 + 0x28);
  if ((param_2 == (uchar *)0x0) || (*param_2 != '\t')) {
    uVar8 = 0x29;
  }
  else {
    uVar8 = 0x29;
    if ((param_2[1] < 0x10) && (param_2[2] == 0xff)) {
      local_e8[0] = 0x9d;
      local_e0 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
      pcStack_d8 = "A2DP_ParseInfoSsc";
      local_d0[0] = (ulong)param_2[6];
      puStack_f8 = local_d0;
      local_d0[1] = 0;
      local_d0[2] = (ulong)param_2[5];
      uStack_b8 = 0;
      local_b0 = (ulong)param_2[4];
      uStack_a8 = 0;
      local_a0 = (ulong)param_2[3];
      uStack_98 = 0;
      local_90 = (ulong)param_2[8];
      uStack_88 = 0;
      local_80 = (ulong)param_2[7];
      uStack_78 = 0;
      local_70 = (ulong)(param_2[9] & 0xf0);
      local_60 = (ulong)(param_2[9] & 0xf);
      uStack_68 = 0;
      local_100 = 8;
      local_58 = 0;
      uStack_50 = 0x18cc6318c6;
      local_f0 = 0x18cc6318c6;
      bluetooth::log_internal::vlog
                (2,"a2dp_vendor_ssc",local_e8,
                 "codec info[{:02x}{:02x}{:02x}{:02x}] codecid[{:02x}{:02x}] samplerate[{:x}] limitation[{:x}]"
                 ,0x5c,&local_100);
      iVar1 = *(int *)(param_2 + 3);
      *(int *)param_1 = iVar1;
      uVar8 = 0x29;
      sVar5 = *(short *)(param_2 + 7);
      *(short *)(param_1 + 4) = sVar5;
      if ((iVar1 == 0x75) && (sVar5 == 0x103)) {
        bVar2 = param_2[9];
        param_1[6] = SUB81((ulong)bVar2 & 0xf0,0);
        param_1[7] = (tA2DP_SSC_CIE)(param_2[9] & 8);
        bVar3 = param_2[9];
        param_1[8] = (tA2DP_SSC_CIE)(bVar3 & 4);
        bVar4 = param_2[9];
        param_1[9] = (tA2DP_SSC_CIE)(bVar4 & 2);
        param_1[10] = (tA2DP_SSC_CIE)(param_2[9] & 1);
        if (((param_3) || ((bVar3 & 4) != 0 || (bVar4 & 2) != 0)) ||
           (cVar7 = A2DP_BitsSet((ulong)bVar2 & 0xf0), cVar7 == '\x01')) {
          uVar8 = 0;
        }
        else {
          uVar8 = 0xc3;
        }
      }
    }
  }
  if (*(long *)(lVar6 + 0x28) == local_38) {
    return uVar8;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== A2DP_IsVendorPeerSinkCodecValidSsc @ 00a90a44 size 208 :: A2DP_IsVendorPeerSinkCodecValidSsc | a2dp_vendor_ssc | packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc */

/* A2DP_IsVendorPeerSinkCodecValidSsc(unsigned char const*) */

void A2DP_IsVendorPeerSinkCodecValidSsc(uchar *param_1)

{
  long lVar1;
  bool bVar2;
  char cVar3;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  undefined8 local_58 [3];
  undefined4 local_40 [2];
  char *local_38;
  char *pcStack_30;
  long local_28;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_28 = *(long *)(lVar1 + 0x28);
  local_40[0] = 0xd4;
  local_38 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
  pcStack_30 = "A2DP_IsVendorPeerSinkCodecValidSsc";
  local_58[0] = 0;
  bluetooth::log_internal::vlog(3,"a2dp_vendor_ssc",local_40,&DAT_0013f82c,0,local_58);
  cVar3 = A2DP_ParseInfoSsc((tA2DP_SSC_CIE *)local_40,param_1,false);
  if (cVar3 == '\0') {
    bVar2 = true;
  }
  else {
    cVar3 = A2DP_ParseInfoSsc((tA2DP_SSC_CIE *)local_40,param_1,true);
    bVar2 = cVar3 == '\0';
  }
  if (*(long *)(lVar1 + 0x28) == local_28) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(bVar2);
}


/* ==== A2DP_VendorUsesRtpHeaderSsc @ 00a90b14 size 152 :: A2DP_VendorUsesRtpHeaderSsc | a2dp_vendor_ssc | packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc */

/* A2DP_VendorUsesRtpHeaderSsc(bool, unsigned char const*) */

undefined8 A2DP_VendorUsesRtpHeaderSsc(bool param_1,uchar *param_2)

{
  long lVar1;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  undefined8 local_58 [3];
  undefined4 local_40 [2];
  char *local_38;
  char *pcStack_30;
  long local_28;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_28 = *(long *)(lVar1 + 0x28);
  local_40[0] = 0x101;
  local_38 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
  pcStack_30 = "A2DP_VendorUsesRtpHeaderSsc";
  local_58[0] = 0;
  bluetooth::log_internal::vlog(2,"a2dp_vendor_ssc",local_40,&DAT_0013f82c,0,local_58);
  if (*(long *)(lVar1 + 0x28) == local_28) {
    return 1;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== A2DP_VendorCodecTypeEqualsSsc @ 00a90bac size 1080 :: A2DP_VendorCodecTypeEqualsSsc | a2dp_vendor_ssc | packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc */

/* A2DP_VendorCodecTypeEqualsSsc(unsigned char const*, unsigned char const*) */

void A2DP_VendorCodecTypeEqualsSsc(uchar *param_1,uchar *param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  byte bVar9;
  byte bVar10;
  byte bVar11;
  byte bVar12;
  byte bVar13;
  byte bVar14;
  byte bVar15;
  byte bVar16;
  byte bVar17;
  byte bVar18;
  byte bVar19;
  byte bVar20;
  long lVar21;
  undefined8 uVar22;
  char *pcVar23;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  byte local_330 [4];
  tA2DP_SSC_CIE atStack_32c [12];
  undefined8 local_320;
  undefined4 local_318;
  undefined8 local_310;
  undefined1 **ppuStack_308;
  undefined8 local_300;
  undefined8 local_2f8;
  char *local_2f0;
  char *pcStack_2e8;
  undefined1 *local_2e0;
  code *local_2d8;
  char *local_2d0;
  ulong local_2c0;
  undefined8 uStack_2b8;
  undefined1 local_2b0;
  ulong local_2a0;
  undefined8 uStack_298;
  undefined1 local_290;
  ulong local_280;
  undefined8 uStack_278;
  undefined1 local_270;
  ulong local_260;
  undefined8 uStack_258;
  undefined1 local_250;
  ulong local_240;
  undefined8 uStack_238;
  undefined1 local_230;
  ulong local_220;
  undefined8 uStack_218;
  undefined1 local_210;
  ulong local_200;
  undefined8 uStack_1f8;
  undefined1 local_1f0;
  ulong local_1e0;
  undefined8 uStack_1d8;
  undefined1 local_1d0;
  ulong local_1c0;
  undefined8 uStack_1b8;
  undefined1 local_1b0;
  ulong local_1a0;
  undefined8 uStack_198;
  undefined1 local_190;
  ulong local_180;
  undefined8 uStack_178;
  undefined1 local_170;
  ulong local_160;
  undefined8 uStack_158;
  undefined1 local_150;
  ulong local_140;
  undefined8 uStack_138;
  undefined1 local_130;
  ulong local_120;
  undefined8 local_118;
  undefined1 local_110;
  ulong local_100;
  undefined8 local_f8;
  undefined1 local_f0;
  ulong local_e0;
  undefined8 local_d8;
  undefined1 local_d0;
  ulong local_c0;
  undefined8 local_b8;
  undefined1 local_b0;
  ulong local_a0;
  undefined8 local_98;
  undefined1 local_90;
  ulong local_80;
  undefined8 local_78;
  undefined1 local_70;
  long local_58;
  
  *in_x18 = unaff_x30;
  lVar21 = tpidr_el0;
  local_58 = *(long *)(lVar21 + 0x28);
  local_318 = 0;
  local_320 = 0;
  local_330[0] = A2DP_ParseInfoSsc((tA2DP_SSC_CIE *)&local_320,param_1,true);
  if (local_330[0] == 0) {
    local_330[0] = A2DP_ParseInfoSsc(atStack_32c,param_2,true);
    if (local_330[0] == 0) {
      local_2e0 = (undefined1 *)CONCAT44(local_2e0._4_4_,0x125);
      local_2d8 = (code *)0x1e4d6a;
      local_2d0 = "A2DP_VendorCodecTypeEqualsSsc";
      local_2f8 = 0;
      bluetooth::log_internal::vlog(3,"a2dp_vendor_ssc",&local_2e0,&DAT_0013f82c,0,&local_2f8);
      uVar22 = 1;
      goto LAB_00a90f60;
    }
    local_2f8._0_4_ = 0x11c;
    ppuStack_308 = &local_2e0;
    local_2f0 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
    pcStack_2e8 = "A2DP_VendorCodecTypeEqualsSsc";
    local_2d8 = 
    _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I12tA2DP_STATUSEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
    ;
    local_2d0 = (char *)0xf;
    local_310 = 1;
    local_300 = 0xf;
    local_2e0 = local_330;
    bluetooth::log_internal::vlog
              (6,"a2dp_vendor_ssc",&local_2f8,"cannot decode codec information: {}",0x23,&local_310)
    ;
    pcVar23 = 
    "p_codec_info_b {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x}"
    ;
    local_2f8 = CONCAT44(local_2f8._4_4_,0x11d);
    bVar1 = *param_2;
    bVar2 = param_2[1];
    bVar3 = param_2[2];
    bVar4 = param_2[3];
    bVar5 = param_2[4];
    bVar6 = param_2[5];
    bVar7 = param_2[6];
    bVar8 = param_2[7];
    bVar9 = param_2[8];
    bVar10 = param_2[9];
    bVar11 = param_2[10];
    bVar12 = param_2[0xb];
    bVar13 = param_2[0xc];
    bVar14 = param_2[0xd];
    bVar15 = param_2[0xe];
    bVar16 = param_2[0xf];
    bVar17 = param_2[0x10];
    bVar18 = param_2[0x11];
    bVar19 = param_2[0x12];
    bVar20 = param_2[0x13];
  }
  else {
    local_2f8._0_4_ = 0x112;
    ppuStack_308 = &local_2e0;
    local_2f0 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
    pcStack_2e8 = "A2DP_VendorCodecTypeEqualsSsc";
    local_2d8 = 
    _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I12tA2DP_STATUSEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
    ;
    local_2d0 = (char *)0xf;
    local_310 = 1;
    local_300 = 0xf;
    local_2e0 = local_330;
    bluetooth::log_internal::vlog
              (6,"a2dp_vendor_ssc",&local_2f8,"cannot decode codec information: {}",0x23,&local_310)
    ;
    pcVar23 = 
    "p_codec_info_a {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x}"
    ;
    local_2f8 = CONCAT44(local_2f8._4_4_,0x113);
    bVar1 = *param_1;
    bVar2 = param_1[1];
    bVar3 = param_1[2];
    bVar4 = param_1[3];
    bVar5 = param_1[4];
    bVar6 = param_1[5];
    bVar7 = param_1[6];
    bVar8 = param_1[7];
    bVar9 = param_1[8];
    bVar10 = param_1[9];
    bVar11 = param_1[10];
    bVar12 = param_1[0xb];
    bVar13 = param_1[0xc];
    bVar14 = param_1[0xd];
    bVar15 = param_1[0xe];
    bVar16 = param_1[0xf];
    bVar17 = param_1[0x10];
    bVar18 = param_1[0x11];
    bVar19 = param_1[0x12];
    bVar20 = param_1[0x13];
  }
  local_80 = (ulong)bVar20;
  local_a0 = (ulong)bVar19;
  local_c0 = (ulong)bVar18;
  local_e0 = (ulong)bVar17;
  local_100 = (ulong)bVar16;
  local_120 = (ulong)bVar15;
  local_140 = (ulong)bVar14;
  local_160 = (ulong)bVar13;
  local_180 = (ulong)bVar12;
  local_1a0 = (ulong)bVar11;
  local_1c0 = (ulong)bVar10;
  local_1e0 = (ulong)bVar9;
  local_200 = (ulong)bVar8;
  local_220 = (ulong)bVar7;
  local_240 = (ulong)bVar6;
  local_260 = (ulong)bVar5;
  local_280 = (ulong)bVar4;
  local_2a0 = (ulong)bVar3;
  local_2c0 = (ulong)bVar2;
  local_2e0 = (undefined1 *)(ulong)bVar1;
  local_d0 = 6;
  local_d8 = 0;
  local_f0 = 6;
  local_f8 = 0;
  local_110 = 6;
  local_118 = 0;
  local_130 = 6;
  uStack_138 = 0;
  local_150 = 6;
  uStack_158 = 0;
  local_170 = 6;
  uStack_178 = 0;
  local_190 = 6;
  uStack_198 = 0;
  local_1b0 = 6;
  uStack_1b8 = 0;
  local_1d0 = 6;
  uStack_1d8 = 0;
  local_1f0 = 6;
  uStack_1f8 = 0;
  local_210 = 6;
  uStack_218 = 0;
  local_230 = 6;
  uStack_238 = 0;
  local_250 = 6;
  uStack_258 = 0;
  local_270 = 6;
  uStack_278 = 0;
  local_290 = 6;
  uStack_298 = 0;
  local_2b0 = 6;
  uStack_2b8 = 0;
  local_2d0 = (char *)CONCAT71(local_2d0._1_7_,6);
  local_2d8 = (code *)0x0;
  pcStack_2e8 = "A2DP_VendorCodecTypeEqualsSsc";
  local_2f0 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
  ppuStack_308 = &local_2e0;
  local_b8 = 0;
  local_b0 = 6;
  local_98 = 0;
  local_90 = 6;
  local_78 = 0;
  local_70 = 6;
  local_310 = 0x14;
  bluetooth::log_internal::vlog(3,"a2dp_vendor_ssc",&local_2f8,pcVar23,0x9a,&local_310);
  uVar22 = 0;
LAB_00a90f60:
  if (*(long *)(lVar21 + 0x28) == local_58) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar22);
}


/* ==== A2DP_VendorCodecEqualsSsc @ 00a90fe4 size 1152 :: A2DP_VendorCodecEqualsSsc | a2dp_vendor_ssc | packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc */

/* A2DP_VendorCodecEqualsSsc(unsigned char const*, unsigned char const*) */

void A2DP_VendorCodecEqualsSsc(uchar *param_1,uchar *param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  byte bVar9;
  byte bVar10;
  byte bVar11;
  byte bVar12;
  byte bVar13;
  byte bVar14;
  byte bVar15;
  byte bVar16;
  byte bVar17;
  byte bVar18;
  byte bVar19;
  byte bVar20;
  long lVar21;
  bool bVar22;
  char *pcVar23;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  byte local_344 [4];
  undefined8 local_340;
  undefined4 local_338;
  undefined8 local_330;
  undefined4 local_328;
  undefined8 local_320;
  undefined1 **ppuStack_318;
  undefined8 local_310;
  undefined8 local_308;
  char *local_300;
  char *pcStack_2f8;
  byte *local_2f0;
  code *local_2e8;
  char *local_2e0;
  ulong local_2d0;
  undefined8 uStack_2c8;
  undefined1 local_2c0;
  ulong local_2b0;
  undefined8 uStack_2a8;
  undefined1 local_2a0;
  ulong local_290;
  undefined8 uStack_288;
  undefined1 local_280;
  ulong local_270;
  undefined8 uStack_268;
  undefined1 local_260;
  ulong local_250;
  undefined8 uStack_248;
  undefined1 local_240;
  ulong local_230;
  undefined8 uStack_228;
  undefined1 local_220;
  ulong local_210;
  undefined8 uStack_208;
  undefined1 local_200;
  ulong local_1f0;
  undefined8 uStack_1e8;
  undefined1 local_1e0;
  ulong local_1d0;
  undefined8 uStack_1c8;
  undefined1 local_1c0;
  ulong local_1b0;
  undefined8 uStack_1a8;
  undefined1 local_1a0;
  ulong local_190;
  undefined8 uStack_188;
  undefined1 local_180;
  ulong local_170;
  undefined8 uStack_168;
  undefined1 local_160;
  ulong local_150;
  undefined8 uStack_148;
  undefined1 local_140;
  ulong local_130;
  undefined8 uStack_128;
  undefined1 local_120;
  ulong local_110;
  undefined8 uStack_108;
  undefined1 local_100;
  ulong local_f0;
  undefined8 local_e8;
  undefined1 local_e0;
  ulong local_d0;
  undefined8 local_c8;
  undefined1 local_c0;
  ulong local_b0;
  undefined8 local_a8;
  undefined1 local_a0;
  ulong local_90;
  undefined8 local_88;
  undefined1 local_80;
  long local_68;
  
  *in_x18 = unaff_x30;
  lVar21 = tpidr_el0;
  local_68 = *(long *)(lVar21 + 0x28);
  local_328 = 0;
  local_330 = 0;
  local_344[0] = A2DP_ParseInfoSsc((tA2DP_SSC_CIE *)&local_330,param_1,true);
  if (local_344[0] == 0) {
    local_338 = 0;
    local_340 = 0;
    local_344[0] = A2DP_ParseInfoSsc((tA2DP_SSC_CIE *)&local_340,param_2,true);
    if (local_344[0] != 0) {
      local_2f0 = local_344;
      local_308._0_4_ = 0x13c;
      ppuStack_318 = &local_2f0;
      local_300 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
      pcStack_2f8 = "A2DP_VendorCodecEqualsSsc";
      local_2e8 = 
      _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I12tA2DP_STATUSEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
      ;
      local_2e0 = (char *)0xf;
      local_320 = 1;
      local_310 = 0xf;
      bluetooth::log_internal::vlog
                (6,"a2dp_vendor_ssc",&local_308,"cannot decode b codec information: {}",0x25,
                 &local_320);
      pcVar23 = 
      "p_codec_info_b {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x}"
      ;
      local_308 = CONCAT44(local_308._4_4_,0x13d);
      bVar1 = *param_2;
      bVar2 = param_2[1];
      bVar3 = param_2[2];
      bVar4 = param_2[3];
      bVar5 = param_2[4];
      bVar6 = param_2[5];
      bVar7 = param_2[6];
      bVar8 = param_2[7];
      bVar9 = param_2[8];
      bVar10 = param_2[9];
      bVar11 = param_2[10];
      bVar12 = param_2[0xb];
      bVar13 = param_2[0xc];
      bVar14 = param_2[0xd];
      bVar15 = param_2[0xe];
      bVar16 = param_2[0xf];
      bVar17 = param_2[0x10];
      bVar18 = param_2[0x11];
      bVar19 = param_2[0x12];
      bVar20 = param_2[0x13];
      goto LAB_00a913a4;
    }
    local_2f0 = (byte *)CONCAT44(local_2f0._4_4_,0x145);
    local_2e8 = (code *)0x1e4d6a;
    local_2e0 = "A2DP_VendorCodecEqualsSsc";
    local_308 = 0;
    bluetooth::log_internal::vlog(3,"a2dp_vendor_ssc",&local_2f0,&DAT_0013f82c,0,&local_308);
    if ((local_330._6_1_ == local_340._6_1_) && ((local_328 & 0xff) == (local_338 & 0xff))) {
      bVar22 = local_328._1_1_ == local_338._1_1_;
      goto LAB_00a913b0;
    }
  }
  else {
    local_2f0 = local_344;
    local_308._0_4_ = 0x132;
    local_300 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
    pcStack_2f8 = "A2DP_VendorCodecEqualsSsc";
    local_2e8 = 
    _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I12tA2DP_STATUSEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
    ;
    local_2e0 = (char *)0xf;
    local_320 = 1;
    local_310 = 0xf;
    ppuStack_318 = &local_2f0;
    bluetooth::log_internal::vlog
              (6,"a2dp_vendor_ssc",&local_308,"cannot decode a codec information: {}",0x25,
               &local_320);
    pcVar23 = 
    "p_codec_info_a {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x}"
    ;
    local_308 = CONCAT44(local_308._4_4_,0x133);
    bVar1 = *param_1;
    bVar2 = param_1[1];
    bVar3 = param_1[2];
    bVar4 = param_1[3];
    bVar5 = param_1[4];
    bVar6 = param_1[5];
    bVar7 = param_1[6];
    bVar8 = param_1[7];
    bVar9 = param_1[8];
    bVar10 = param_1[9];
    bVar11 = param_1[10];
    bVar12 = param_1[0xb];
    bVar13 = param_1[0xc];
    bVar14 = param_1[0xd];
    bVar15 = param_1[0xe];
    bVar16 = param_1[0xf];
    bVar17 = param_1[0x10];
    bVar18 = param_1[0x11];
    bVar19 = param_1[0x12];
    bVar20 = param_1[0x13];
LAB_00a913a4:
    local_90 = (ulong)bVar20;
    local_b0 = (ulong)bVar19;
    local_d0 = (ulong)bVar18;
    local_f0 = (ulong)bVar17;
    local_110 = (ulong)bVar16;
    local_130 = (ulong)bVar15;
    local_150 = (ulong)bVar14;
    local_170 = (ulong)bVar13;
    local_190 = (ulong)bVar12;
    local_1b0 = (ulong)bVar11;
    local_1d0 = (ulong)bVar10;
    local_1f0 = (ulong)bVar9;
    local_210 = (ulong)bVar8;
    local_230 = (ulong)bVar7;
    local_250 = (ulong)bVar6;
    local_270 = (ulong)bVar5;
    local_290 = (ulong)bVar4;
    local_2b0 = (ulong)bVar3;
    local_2d0 = (ulong)bVar2;
    local_2f0 = (byte *)(ulong)bVar1;
    ppuStack_318 = &local_2f0;
    local_80 = 6;
    local_88 = 0;
    local_a0 = 6;
    local_a8 = 0;
    local_c0 = 6;
    local_c8 = 0;
    local_e0 = 6;
    local_e8 = 0;
    local_100 = 6;
    uStack_108 = 0;
    local_120 = 6;
    uStack_128 = 0;
    local_140 = 6;
    uStack_148 = 0;
    local_160 = 6;
    uStack_168 = 0;
    local_180 = 6;
    uStack_188 = 0;
    local_1a0 = 6;
    uStack_1a8 = 0;
    local_1c0 = 6;
    uStack_1c8 = 0;
    local_1e0 = 6;
    uStack_1e8 = 0;
    local_200 = 6;
    uStack_208 = 0;
    local_220 = 6;
    uStack_228 = 0;
    local_240 = 6;
    uStack_248 = 0;
    local_260 = 6;
    uStack_268 = 0;
    local_280 = 6;
    uStack_288 = 0;
    local_2a0 = 6;
    uStack_2a8 = 0;
    local_2c0 = 6;
    uStack_2c8 = 0;
    local_2e0 = (char *)CONCAT71(local_2e0._1_7_,6);
    local_2e8 = (code *)0x0;
    pcStack_2f8 = "A2DP_VendorCodecEqualsSsc";
    local_300 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
    local_320 = 0x14;
    bluetooth::log_internal::vlog(3,"a2dp_vendor_ssc",&local_308,pcVar23,0x9a,&local_320);
  }
  bVar22 = false;
LAB_00a913b0:
  if (*(long *)(lVar21 + 0x28) == local_68) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(bVar22);
}


/* ==== A2DP_VendorGetTrackSampleRateSsc @ 00a91464 size 444 :: A2DP_VendorGetTrackSampleRateSsc | a2dp_vendor_ssc | packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc */

/* A2DP_VendorGetTrackSampleRateSsc(unsigned char const*) */

void A2DP_VendorGetTrackSampleRateSsc(uchar *param_1)

{
  long lVar1;
  undefined8 uVar2;
  undefined8 *in_x18;
  ulong uVar3;
  undefined8 unaff_x30;
  byte local_a4 [4];
  undefined8 local_a0;
  undefined4 local_98;
  undefined8 local_90;
  undefined1 **ppuStack_88;
  undefined8 local_80;
  undefined4 local_78 [2];
  char *local_70;
  char *pcStack_68;
  byte *local_60;
  code *local_58;
  ulong local_50;
  undefined8 local_48;
  undefined8 uStack_40;
  long local_28;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_28 = *(long *)(lVar1 + 0x28);
  local_98 = 0;
  local_a0 = 0;
  local_a4[0] = A2DP_ParseInfoSsc((tA2DP_SSC_CIE *)&local_a0,param_1,false);
  if (local_a4[0] != 0) {
    local_78[0] = 0x15a;
    local_70 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
    pcStack_68 = "A2DP_VendorGetTrackSampleRateSsc";
    local_60 = local_a4;
    local_58 = 
    _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I12tA2DP_STATUSEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
    ;
    local_50 = 0xf;
    ppuStack_88 = &local_60;
    local_90 = 1;
    local_80 = 0xf;
    bluetooth::log_internal::vlog
              (6,"a2dp_vendor_ssc",local_78,"cannot decode codec information: {}",0x23,&local_90);
    uVar2 = 0xffffffff;
    goto LAB_00a915a8;
  }
  local_78[0] = 0x15e;
  local_70 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
  pcStack_68 = "A2DP_VendorGetTrackSampleRateSsc";
  uVar3 = (ulong)local_98._1_1_;
  local_60 = &DAT_00000020;
  local_58 = (code *)0x0;
  ppuStack_88 = &local_60;
  local_48 = 0;
  uStack_40 = 0xc6;
  local_90 = 2;
  local_80 = 0xc6;
  local_50 = uVar3;
  bluetooth::log_internal::vlog
            (4,"a2dp_vendor_ssc",local_78,"0x{:x}, uhq ver2 : 0x{:x}",0x19,&local_90);
  if (uVar3 == 2) {
    uVar2 = 96000;
    goto LAB_00a915a8;
  }
  if ((char)local_98 == '\x04') {
LAB_00a915a4:
    uVar2 = 48000;
  }
  else {
    if (local_a0._6_1_ < 0x40) {
      if (local_a0._6_1_ == 0x10) goto LAB_00a915a4;
      if (local_a0._6_1_ == 0x20) {
        uVar2 = 0xac44;
        goto LAB_00a915a8;
      }
    }
    else {
      if (local_a0._6_1_ == 0x40) {
        uVar2 = 32000;
        goto LAB_00a915a8;
      }
      uVar2 = 96000;
      if (local_a0._6_1_ == 0x80) goto LAB_00a915a8;
    }
    uVar2 = 0xffffffff;
  }
LAB_00a915a8:
  if (*(long *)(lVar1 + 0x28) == local_28) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar2);
}


/* ==== A2DP_VendorGetTrackBitsPerSampleSsc @ 00a91620 size 276 :: A2DP_VendorGetTrackBitsPerSampleSsc | a2dp_vendor_ssc | packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc */

/* A2DP_VendorGetTrackBitsPerSampleSsc(unsigned char const*) */

void A2DP_VendorGetTrackBitsPerSampleSsc(uchar *param_1)

{
  long lVar1;
  undefined4 uVar2;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  byte local_94 [4];
  undefined8 local_90;
  undefined4 local_88;
  undefined8 local_80;
  undefined1 **ppuStack_78;
  undefined8 local_70;
  undefined4 local_68 [2];
  char *local_60;
  char *pcStack_58;
  byte *local_50;
  code *local_48;
  undefined8 uStack_40;
  long local_28;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_28 = *(long *)(lVar1 + 0x28);
  local_88 = 0;
  local_90 = 0;
  local_94[0] = A2DP_ParseInfoSsc((tA2DP_SSC_CIE *)&local_90,param_1,false);
  if (local_94[0] == 0) {
    uVar2 = 0x22;
    if ((local_88._1_1_ != '\x02') && (local_90._6_1_ != -0x80)) {
      uVar2 = 0x18;
      if ((char)local_88 != '\x04') {
        uVar2 = 0x10;
      }
    }
  }
  else {
    local_68[0] = 0x170;
    local_60 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
    pcStack_58 = "A2DP_VendorGetTrackBitsPerSampleSsc";
    local_50 = local_94;
    local_48 = 
    _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I12tA2DP_STATUSEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
    ;
    uStack_40 = 0xf;
    ppuStack_78 = &local_50;
    local_80 = 1;
    local_70 = 0xf;
    bluetooth::log_internal::vlog
              (6,"a2dp_vendor_ssc",local_68,"cannot decode codec information: {}",0x23,&local_80);
    uVar2 = 0xffffffff;
  }
  if (*(long *)(lVar1 + 0x28) != local_28) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(uVar2);
  }
  return;
}


/* ==== A2DP_VendorGetTrackBitrateLimitationSsc @ 00a91734 size 196 :: A2DP_VendorGetTrackBitrateLimitationSsc | a2dp_vendor_ssc | packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc */

/* A2DP_VendorGetTrackBitrateLimitationSsc(unsigned char const*) */

void A2DP_VendorGetTrackBitrateLimitationSsc(uchar *param_1)

{
  long lVar1;
  bool bVar2;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  undefined8 local_80;
  ulong *puStack_78;
  undefined8 local_70;
  undefined4 local_68 [2];
  char *local_60;
  char *pcStack_58;
  ulong local_50 [5];
  long local_28;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_28 = *(long *)(lVar1 + 0x28);
  bVar2 = false;
  if (param_1 != (uchar *)0x0) {
    local_68[0] = 0x182;
    local_60 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
    pcStack_58 = "A2DP_VendorGetTrackBitrateLimitationSsc";
    local_50[0] = (ulong)param_1[9];
    puStack_78 = local_50;
    local_50[1] = 0;
    local_50[2] = 6;
    local_80 = 1;
    local_70 = 6;
    bluetooth::log_internal::vlog(3,"a2dp_vendor_ssc",local_68,"0x{:x}",6,&local_80);
    bVar2 = (param_1[9] & 8) == 0;
  }
  if (*(long *)(lVar1 + 0x28) == local_28) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(bVar2);
}


/* ==== A2DP_VendorGetSscType @ 00a917f8 size 288 :: A2DP_VendorGetSscType | a2dp_vendor_ssc | packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc */

/* A2DP_VendorGetSscType(unsigned char const*) */

void A2DP_VendorGetSscType(uchar *param_1)

{
  long lVar1;
  undefined4 uVar2;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  byte local_94 [4];
  undefined8 local_90;
  undefined4 local_88;
  undefined8 local_80;
  undefined1 **ppuStack_78;
  undefined8 local_70;
  undefined4 local_68 [2];
  char *local_60;
  char *pcStack_58;
  byte *local_50;
  code *local_48;
  undefined8 uStack_40;
  long local_28;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_28 = *(long *)(lVar1 + 0x28);
  local_88 = 0;
  local_90 = 0;
  local_94[0] = A2DP_ParseInfoSsc((tA2DP_SSC_CIE *)&local_90,param_1,false);
  if (local_94[0] == 0) {
    if (local_88._1_1_ == '\x02') {
      uVar2 = 0x400;
    }
    else if (local_90._6_1_ == -0x80) {
      uVar2 = 0x200;
    }
    else {
      uVar2 = 0x100;
      if ((char)local_88 != '\x04') {
        uVar2 = 0x80;
      }
    }
  }
  else {
    local_68[0] = 400;
    local_60 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
    pcStack_58 = "A2DP_VendorGetSscType";
    local_50 = local_94;
    local_48 = 
    _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I12tA2DP_STATUSEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
    ;
    uStack_40 = 0xf;
    ppuStack_78 = &local_50;
    local_80 = 1;
    local_70 = 0xf;
    bluetooth::log_internal::vlog
              (6,"a2dp_vendor_ssc",local_68,"cannot decode codec information: {}",0x23,&local_80);
    uVar2 = 0x80;
  }
  if (*(long *)(lVar1 + 0x28) != local_28) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(uVar2);
  }
  return;
}


/* ==== A2DP_VendorGetPacketTimestampSsc @ 00a91918 size 176 :: A2DP_VendorGetPacketTimestampSsc | a2dp_vendor_ssc | packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc */

/* A2DP_VendorGetPacketTimestampSsc(unsigned char const*, unsigned char const*, unsigned int*) */

undefined8 A2DP_VendorGetPacketTimestampSsc(uchar *param_1,uchar *param_2,uint *param_3)

{
  long lVar1;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  undefined8 local_68 [3];
  undefined4 local_50 [2];
  char *local_48;
  char *pcStack_40;
  long local_38;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_38 = *(long *)(lVar1 + 0x28);
  local_50[0] = 0x19e;
  local_48 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
  pcStack_40 = "A2DP_VendorGetPacketTimestampSsc";
  local_68[0] = 0;
  bluetooth::log_internal::vlog(2,"a2dp_vendor_ssc",local_50,&DAT_0013f82c,0,local_68);
  *param_3 = *(uint *)param_2;
  if (*(long *)(lVar1 + 0x28) == local_38) {
    return 1;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== A2DP_VendorCodecInfoStringSsc @ 00a919c8 size 1316 :: 	name: SSC
 | A2DP_ParseInfoSsc fail:  */

/* A2DP_VendorCodecInfoStringSsc(unsigned char const*) */

void A2DP_VendorCodecInfoStringSsc(uchar *param_1)

{
  long lVar1;
  char *pcVar2;
  uchar uVar3;
  ostream *poVar4;
  void *__src;
  ulong *in_x8;
  ulong uVar5;
  undefined8 *in_x18;
  undefined1 *__dest;
  size_t __n;
  uint uVar6;
  long *plVar7;
  undefined8 unaff_x30;
  string local_1c8;
  undefined4 uStack_1c7;
  undefined1 uStack_1c3;
  undefined1 uStack_1c2;
  undefined1 uStack_1c1;
  ulong local_1c0;
  char *local_1b8;
  undefined8 local_1b0;
  undefined4 local_1a8;
  undefined8 local_1a0;
  ulong local_198;
  char *local_190;
  undefined **local_188;
  undefined8 local_180;
  undefined **local_178;
  undefined **local_170;
  undefined8 uStack_168;
  long local_160 [8];
  void *local_120;
  ulong uStack_118;
  undefined8 local_110;
  undefined **ppuStack_108;
  undefined8 local_100;
  undefined8 uStack_f8;
  undefined8 local_f0;
  undefined8 uStack_e8;
  undefined8 local_e0;
  undefined8 uStack_d8;
  undefined8 local_d0;
  undefined8 uStack_c8;
  undefined8 local_c0;
  undefined8 uStack_b8;
  undefined8 local_b0;
  undefined8 uStack_a8;
  undefined8 local_a0;
  undefined8 uStack_98;
  undefined8 local_90;
  undefined8 uStack_88;
  undefined8 local_80;
  undefined8 uStack_78;
  long local_70;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_70 = *(long *)(lVar1 + 0x28);
  uStack_78 = 0;
  local_80 = 0;
  local_110 = 0;
  uStack_88 = 0;
  local_90 = 0;
  uStack_98 = 0;
  local_a0 = 0;
  uStack_a8 = 0;
  local_b0 = 0;
  uStack_b8 = 0;
  local_c0 = 0;
  uStack_c8 = 0;
  local_d0 = 0;
  uStack_d8 = 0;
  local_e0 = 0;
  uStack_e8 = 0;
  local_f0 = 0;
  uStack_f8 = 0;
  local_100 = 0;
  uStack_118 = 0;
  local_120 = (void *)0x0;
  local_160[7] = 0;
  local_160[6] = 0;
  local_160[5] = 0;
  local_160[4] = 0;
  local_160[3] = 0;
  local_160[2] = 0;
  local_160[1] = 0;
  local_160[0] = 0;
  uStack_168 = 0;
  local_170 = (undefined **)0x0;
  local_188 = &PTR__istream_00f68ae0;
  ppuStack_108 = &PTR__istream_00f68b08;
  local_180 = 0;
  local_178 = &PTR__stringstream_00f689c8;
  std::ios_base::init((ios_base *)&ppuStack_108,(stringbuf *)&local_170);
  local_80 = 0;
                    /* WARNING: Ignoring partial resolution of indirect */
  uStack_78._0_4_ = 0xffffffff;
  local_188 = &PTR__stringstream_00f689a0;
  local_170 = &PTR__streambuf_00f68750;
  local_178 = &PTR__stringstream_00f689c8;
  ppuStack_108 = &PTR__stringstream_00f689f0;
  std::locale::locale((locale *)&uStack_168);
  plVar7 = local_160;
  local_160[5] = 0;
  local_160[4] = 0;
  local_160[1] = 0;
  local_160[0] = 0;
  local_160[3] = 0;
  local_160[2] = 0;
  local_160[7] = 0;
  local_160[6] = 0;
  local_170 = &PTR__stringbuf_00f687d0;
  uStack_118 = 0;
  local_120 = (void *)0x0;
  local_110 = CONCAT44(local_110._4_4_,0x18);
  std::stringbuf::__init_buf_ptrs_abi_nn220000_((stringbuf *)&local_170);
  local_1a0 = 0;
  local_198 = 0;
  local_190 = (char *)0x0;
  local_1a8 = 0;
  local_1b0 = 0;
  uVar3 = A2DP_ParseInfoSsc((tA2DP_SSC_CIE *)&local_1b0,param_1,true);
  if (uVar3 == '\0') {
    std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
              ((ostream *)&local_178,"\tname: SSC\n",0xb);
    if ((local_1a0 & 1) == 0) {
      local_1a0 = local_1a0 & 0xffffffffffff0000;
    }
    else {
      *local_190 = '\0';
      local_198 = 0;
    }
    uVar3 = local_1b0._6_1_;
    local_1c8 = (string)0x8;
    uStack_1c7 = 0x454e4f4e;
    uStack_1c3 = 0;
    uVar6 = (uint)(char)local_1b0._6_1_;
    if (local_1b0._6_1_ == '\0') {
LAB_00a91cb0:
      uVar5 = local_1a0 >> 1 & 0x7f;
      if ((local_1a0 & 1) != 0) {
        uVar5 = local_198;
      }
      if (uVar5 != 0) {
        std::string::append((string *)&local_1a0,"|");
      }
      std::string::append_abi_nn220000_((string *)&local_1a0,&local_1c8);
      if (((byte)local_1c8 & 1) != 0) {
        operator_delete(local_1b8,
                        CONCAT17(uStack_1c1,
                                 CONCAT16(uStack_1c2,
                                          CONCAT15(uStack_1c3,CONCAT41(uStack_1c7,local_1c8)))) &
                        0xfffffffffffffffe);
      }
    }
    else {
      local_1c8 = (string)0xa;
      uStack_1c7 = 0x30303639;
      uStack_1c3 = 0x30;
      uStack_1c2 = 0;
      if ((char)local_1b0._6_1_ < '\0') {
        uVar5 = local_1a0 >> 1 & 0x7f;
        if ((local_1a0 & 1) != 0) {
          uVar5 = local_198;
        }
        if (uVar5 != 0) {
          std::string::append((string *)&local_1a0,"|");
        }
        std::string::append_abi_nn220000_((string *)&local_1a0,&local_1c8);
        if (((byte)local_1c8 & 1) != 0) {
          operator_delete(local_1b8,
                          CONCAT17(uStack_1c1,
                                   CONCAT16(uStack_1c2,
                                            CONCAT15(uStack_1c3,CONCAT41(uStack_1c7,local_1c8)))) &
                          0xfffffffffffffffe);
        }
      }
      uStack_1c3 = 0x30;
      uStack_1c2 = 0;
      local_1c8 = (string)0xa;
      uStack_1c7 = 0x30313434;
      if ((uVar6 >> 5 & 1) != 0) goto LAB_00a91cb0;
    }
    poVar4 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                       ((ostream *)&local_178,"\tsamp_freq: ",0xc);
    uVar5 = local_198;
    pcVar2 = local_190;
    if ((local_1a0 & 1) == 0) {
      uVar5 = local_1a0 >> 1 & 0x7f;
      pcVar2 = (char *)((long)&local_1a0 + 1);
    }
    poVar4 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                       (poVar4,pcVar2,uVar5);
    poVar4 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>(poVar4," (",2)
    ;
    loghex<unsigned_char>(uVar3);
    pcVar2 = local_1b8;
    if (((byte)local_1c8 & 1) == 0) {
      local_1c0 = (ulong)((byte)local_1c8 >> 1);
      pcVar2 = (char *)&uStack_1c7;
    }
    poVar4 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                       (poVar4,pcVar2,local_1c0);
    std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>(poVar4,")\n",2);
    if (((byte)local_1c8 & 1) != 0) {
      operator_delete(local_1b8,
                      CONCAT17(uStack_1c1,
                               CONCAT16(uStack_1c2,
                                        CONCAT15(uStack_1c3,CONCAT41(uStack_1c7,local_1c8)))) &
                      0xfffffffffffffffe);
    }
    if (((uint)local_110 >> 4 & 1) != 0) goto LAB_00a91db0;
    uVar5 = local_160[2];
    if (((uint)local_110 >> 3 & 1) != 0) goto LAB_00a91dd0;
LAB_00a91bc8:
    __src = (void *)0x0;
    __n = 0;
  }
  else {
    poVar4 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                       ((ostream *)&local_178,"A2DP_ParseInfoSsc fail: ",0x18);
    loghex<unsigned_char>(uVar3);
    pcVar2 = local_1b8;
    if (((byte)local_1c8 & 1) == 0) {
      local_1c0 = (ulong)((byte)local_1c8 >> 1);
      pcVar2 = (char *)&uStack_1c7;
    }
    std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
              (poVar4,pcVar2,local_1c0);
    if (((byte)local_1c8 & 1) != 0) {
      operator_delete(local_1b8,
                      CONCAT17(uStack_1c1,
                               CONCAT16(uStack_1c2,
                                        CONCAT15(uStack_1c3,CONCAT41(uStack_1c7,local_1c8)))) &
                      0xfffffffffffffffe);
    }
    if (((uint)local_110 >> 4 & 1) == 0) {
      uVar5 = local_160[2];
      if (((uint)local_110 >> 3 & 1) == 0) goto LAB_00a91bc8;
    }
    else {
LAB_00a91db0:
      if (uStack_118 < (ulong)local_160[4]) {
        uStack_118 = local_160[4];
      }
      plVar7 = local_160 + 3;
      uVar5 = uStack_118;
    }
LAB_00a91dd0:
    __src = (void *)*plVar7;
    __n = uVar5 - (long)__src;
    if (0xfffffffffffffff6 < __n) {
                    /* WARNING: Subroutine does not return */
      std::string::__throw_length_error_abi_nn220000_();
    }
    if (0x16 < __n) {
      uVar5 = 0x1a;
      if ((__n | 7) != 0x17) {
        uVar5 = (__n | 7) + 1;
      }
      __dest = (undefined1 *)FUN_00f62c00(uVar5);
      in_x8[1] = __n;
      in_x8[2] = (ulong)__dest;
      *in_x8 = uVar5 | 1;
      goto LAB_00a91e24;
    }
  }
  __dest = (undefined1 *)((long)in_x8 + 1);
  *(char *)in_x8 = (char)((int)__n << 1);
LAB_00a91e24:
  memmove(__dest,__src,__n);
  __dest[__n] = 0;
  if ((local_1a0 & 1) != 0) {
    operator_delete(local_190,local_1a0 & 0xfffffffffffffffe);
  }
  local_188 = &PTR__stringstream_00f689a0;
  local_178 = &PTR__stringstream_00f689c8;
  ppuStack_108 = &PTR__stringstream_00f689f0;
  local_170 = &PTR__stringbuf_00f687d0;
  if ((local_160[6] & 1U) != 0) {
    operator_delete(local_120,local_160[6] & 0xfffffffffffffffe);
  }
  local_170 = &PTR__streambuf_00f68750;
  std::locale::~locale((locale *)&uStack_168);
  std::iostream::~iostream((iostream *)&local_188);
  std::ios::~ios((ios *)&ppuStack_108);
  if (*(long *)(lVar1 + 0x28) == local_70) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== A2DP_VendorGetEncoderInterfaceSsc @ 00a91eec size 312 :: A2DP_IsVendorSourceCodecValidSsc | A2DP_VendorGetEncoderInterfaceSsc | a2dp_vendor_ssc | packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc */

/* A2DP_VendorGetEncoderInterfaceSsc(unsigned char const*) */

void A2DP_VendorGetEncoderInterfaceSsc(uchar *param_1)

{
  long lVar1;
  char cVar2;
  undefined **ppuVar3;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  tA2DP_SSC_CIE atStack_9c [12];
  undefined8 local_90;
  ulong *puStack_88;
  undefined8 local_80;
  undefined8 local_78;
  char *local_70;
  char *pcStack_68;
  ulong local_60;
  char *local_58;
  char *pcStack_50;
  long local_38;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_38 = *(long *)(lVar1 + 0x28);
  local_78 = CONCAT44(local_78._4_4_,0xca);
  local_60 = (ulong)param_1[9];
  local_70 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
  pcStack_68 = "A2DP_IsVendorSourceCodecValidSsc";
  puStack_88 = &local_60;
  local_58 = (char *)0x0;
  pcStack_50 = (char *)0x6;
  local_90 = 1;
  local_80 = 6;
  bluetooth::log_internal::vlog(4,"a2dp_vendor_ssc",&local_78,&DAT_00150033,8,&local_90);
  cVar2 = A2DP_ParseInfoSsc(atStack_9c,param_1,false);
  if ((cVar2 == '\0') || (cVar2 = A2DP_ParseInfoSsc(atStack_9c,param_1,true), cVar2 == '\0')) {
    local_60 = CONCAT44(local_60._4_4_,0x1ca);
    local_58 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
    pcStack_50 = "A2DP_VendorGetEncoderInterfaceSsc";
    local_78 = 0;
    bluetooth::log_internal::vlog(3,"a2dp_vendor_ssc",&local_60,&DAT_0013f82c,0,&local_78);
    ppuVar3 = &PTR_a2dp_vendor_ssc_encoder_init_00fa0808;
  }
  else {
    ppuVar3 = (undefined **)0x0;
  }
  if (*(long *)(lVar1 + 0x28) == local_38) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(ppuVar3);
}


/* ==== A2DP_VendorAdjustCodecSsc @ 00a92024 size 184 :: A2DP_VendorAdjustCodecSsc | a2dp_vendor_ssc | packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc */

/* A2DP_VendorAdjustCodecSsc(unsigned char*) */

void A2DP_VendorAdjustCodecSsc(uchar *param_1)

{
  long lVar1;
  char cVar2;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  tA2DP_SSC_CIE atStack_64 [12];
  undefined8 local_58 [3];
  undefined4 local_40 [2];
  char *local_38;
  char *pcStack_30;
  long local_28;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_28 = *(long *)(lVar1 + 0x28);
  cVar2 = A2DP_ParseInfoSsc(atStack_64,param_1,true);
  if (cVar2 == '\0') {
    local_40[0] = 0x1d5;
    local_38 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
    pcStack_30 = "A2DP_VendorAdjustCodecSsc";
    local_58[0] = 0;
    bluetooth::log_internal::vlog(3,"a2dp_vendor_ssc",local_40,&DAT_0013f82c,0,local_58);
  }
  if (*(long *)(lVar1 + 0x28) == local_28) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(cVar2 == '\0');
}


/* ==== A2DP_VendorInitCodecConfigSsc @ 00a920dc size 352 :: A2DPSM-SSC HiFi 1st is disabled | A2DP_BuildInfoSsc | A2DP_VendorInitCodecConfigSsc | SSC_HIFI_DISABLED_1 | a2dp_vendor_ssc | packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc */

/* A2DP_VendorInitCodecConfigSsc(AvdtpSepConfig*) */

void A2DP_VendorInitCodecConfigSsc(AvdtpSepConfig *param_1)

{
  long lVar1;
  byte bVar2;
  ulong uVar3;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  undefined8 local_90 [3];
  undefined4 local_78 [2];
  char *local_70;
  char *pcStack_68;
  char local_60 [24];
  long local_48;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_48 = *(long *)(lVar1 + 0x28);
  builtin_strncpy(local_60,"SSC_HIFI_DISABLED_1",0x14);
  uVar3 = iop_exception_with_string(10,local_60);
  if ((uVar3 & 1) == 0) {
    DAT_00fabbe8 = 4;
  }
  else {
    btif_dm_log_collector_cback("A2DPSM-SSC HiFi 1st is disabled");
    DAT_00fabbe8 = 0;
  }
  if (param_1 != (AvdtpSepConfig *)0x0) {
    local_78[0] = 0x6a;
    local_70 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
    pcStack_68 = "A2DP_BuildInfoSsc";
    local_90[0] = 0;
    bluetooth::log_internal::vlog(3,"a2dp_vendor_ssc",local_78,&DAT_0013f82c,0,local_90);
    bVar2 = DAT_00fabbe8;
    param_1[8] = (AvdtpSepConfig)0x1;
    local_78[0] = 0x202;
    param_1[9] = (AvdtpSepConfig)(bVar2 | 0x28);
    *(undefined8 *)param_1 = 0x300000075ff0009;
    local_70 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
    pcStack_68 = "A2DP_VendorInitCodecConfigSsc";
    local_90[0] = 0;
    bluetooth::log_internal::vlog(3,"a2dp_vendor_ssc",local_78,&DAT_0013f82c,0,local_90);
  }
  if (*(long *)(lVar1 + 0x28) == local_48) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(param_1 != (AvdtpSepConfig *)0x0);
}


/* ==== A2dpCodecConfigSsc @ 00a9223c size 288 :: A2dpCodecConfigSsc | a2dp_vendor_ssc | packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc */

/* A2dpCodecConfigSsc::A2dpCodecConfigSsc(btav_a2dp_codec_priority_t) */

void __thiscall A2dpCodecConfigSsc::A2dpCodecConfigSsc(A2dpCodecConfigSsc *this,undefined4 param_2)

{
  long lVar1;
  byte bVar2;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  undefined8 local_58 [3];
  uint local_40;
  uint uStack_3c;
  char *local_38;
  char *local_30;
  long local_28;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_28 = *(long *)(lVar1 + 0x28);
  local_40 = 0x43535306;
  uStack_3c = uStack_3c & 0xffffff00;
  A2dpCodecConfig::A2dpCodecConfig((A2dpCodecConfig *)this,8,0x1030075ff,&local_40,param_2);
  if ((local_40 & 1) != 0) {
    operator_delete(local_30,CONCAT44(uStack_3c,local_40) & 0xfffffffffffffffe);
  }
  bVar2 = DAT_00fabbe8;
  *(undefined ***)this = &PTR__A2dpCodecConfigSsc_00f82220;
  *(uint *)(this + 0xa8) = *(uint *)(this + 0xa8) | 1;
  if ((bVar2 >> 2 & 1) != 0) {
    *(uint *)(this + 0xa8) = *(uint *)(this + 0xa8) | 2;
  }
  local_40 = 0x214;
  *(undefined4 *)(this + 0xac) = 3;
  *(uint *)(this + 0xb0) = *(uint *)(this + 0xb0) | 2;
  local_38 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
  local_30 = "A2dpCodecConfigSsc";
  local_58[0] = 0;
  bluetooth::log_internal::vlog(3,"a2dp_vendor_ssc",&local_40,&DAT_0013f82c,0,local_58);
  if (*(long *)(lVar1 + 0x28) == local_28) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== init @ 00a9235c size 164 :: a2dp_vendor_ssc | packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc */

/* WARNING: Unknown calling convention: __rustcall */
/* A2dpCodecConfigSsc::init */

uint __rustcall A2dpCodecConfigSsc::init(void)

{
  long lVar1;
  uint uVar2;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  undefined8 local_58 [3];
  undefined4 local_40 [2];
  char *local_38;
  undefined *puStack_30;
  long local_28;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_28 = *(long *)(lVar1 + 0x28);
  uVar2 = A2DP_VendorLoadEncoderSsc();
  if ((uVar2 & 1) == 0) {
    local_40[0] = 0x21c;
    local_38 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
    puStack_30 = &DAT_0018f4a0;
    local_58[0] = 0;
    bluetooth::log_internal::vlog
              (6,"a2dp_vendor_ssc",local_40,"cannot load the encoder",0x17,local_58);
  }
  if (*(long *)(lVar1 + 0x28) == local_28) {
    return uVar2 & 1;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== setCodecConfig @ 00a92400 size 3108 :: A2DP_BuildInfoSsc | a2dp_vendor_ssc | packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc */

/* WARNING: Removing unreachable block (ram,0x00a929b8) */
/* WARNING: Removing unreachable block (ram,0x00a929cc) */
/* WARNING: Removing unreachable block (ram,0x00a929a0) */
/* WARNING: Unknown calling convention: __rustcall */
/* A2dpCodecConfigSsc::setCodecConfig */

byte __rustcall
A2dpCodecConfigSsc::setCodecConfig(long param_1,uchar *param_2,bool param_3,undefined2 *param_4)

{
  int *piVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  uint uVar5;
  long lVar6;
  bool bVar7;
  char *pcVar8;
  undefined8 uVar9;
  byte bVar10;
  int iVar11;
  byte bVar12;
  undefined8 *in_x18;
  undefined4 uVar13;
  uint uVar14;
  byte *pbVar15;
  byte *pbVar16;
  undefined8 unaff_x30;
  byte local_298;
  uint local_294;
  uint local_278;
  byte local_264 [4];
  undefined8 local_260;
  undefined8 uStack_258;
  undefined8 uStack_250;
  undefined8 uStack_248;
  undefined8 local_240;
  undefined8 uStack_238;
  undefined8 uStack_230;
  undefined8 uStack_228;
  undefined8 local_220;
  undefined8 uStack_218;
  undefined8 uStack_210;
  undefined8 uStack_208;
  undefined8 local_200;
  undefined8 uStack_1f8;
  undefined8 uStack_1f0;
  undefined8 uStack_1e8;
  undefined8 local_1e0;
  undefined8 uStack_1d8;
  undefined8 uStack_1d0;
  undefined8 uStack_1c8;
  undefined8 local_1c0;
  undefined8 uStack_1b8;
  undefined8 uStack_1b0;
  undefined8 uStack_1a8;
  undefined8 local_1a0;
  undefined8 uStack_198;
  undefined8 uStack_190;
  undefined8 uStack_188;
  undefined8 local_180;
  undefined8 uStack_178;
  undefined8 uStack_170;
  undefined8 uStack_168;
  undefined8 local_160;
  undefined4 local_158;
  undefined8 local_150;
  byte **ppbStack_148;
  undefined8 local_140;
  undefined8 local_138;
  char *local_130;
  char *pcStack_128;
  undefined8 local_120;
  undefined8 uStack_118;
  undefined4 local_110;
  undefined8 local_100;
  undefined8 uStack_f8;
  undefined4 local_f0;
  undefined8 local_e0;
  undefined8 uStack_d8;
  undefined4 local_d0;
  byte *local_c0;
  code *local_b8;
  byte *local_b0;
  code *local_a8;
  int *local_a0;
  code *local_98;
  undefined8 uStack_90;
  long local_78;
  
  *in_x18 = unaff_x30;
  lVar6 = tpidr_el0;
  local_78 = *(long *)(lVar6 + 0x28);
  local_c0 = (byte *)CONCAT44(local_c0._4_4_,0x2a8);
  local_b8 = (code *)0x1e4d6a;
  local_b0 = (byte *)0x164228;
  local_1a0 = 0;
  bluetooth::log_internal::vlog(3,"a2dp_vendor_ssc",&local_c0,&DAT_0013f82c,0,&local_1a0);
  std::recursive_mutex::lock((recursive_mutex *)(param_1 + 8));
  uStack_198 = *(undefined8 *)(param_1 + 0x68);
  local_1a0 = *(undefined8 *)(param_1 + 0x60);
  uStack_188 = *(undefined8 *)(param_1 + 0x78);
  uStack_190 = *(undefined8 *)(param_1 + 0x70);
  local_d0 = *(undefined4 *)(param_1 + 0x1b0);
  local_158 = 0;
  uStack_178 = *(undefined8 *)(param_1 + 0x88);
  local_180 = *(undefined8 *)(param_1 + 0x80);
  uStack_168 = *(undefined8 *)(param_1 + 0x98);
  uStack_170 = *(undefined8 *)(param_1 + 0x90);
  local_f0 = *(undefined4 *)(param_1 + 0x1c4);
  local_160 = 0;
  uStack_1d8 = *(undefined8 *)(param_1 + 0xe8);
  local_1e0 = *(undefined8 *)(param_1 + 0xe0);
  uStack_1c8 = *(undefined8 *)(param_1 + 0xf8);
  uStack_1d0 = *(undefined8 *)(param_1 + 0xf0);
  local_110 = *(undefined4 *)(param_1 + 0x1d8);
  uStack_1b8 = *(undefined8 *)(param_1 + 0x108);
  local_1c0 = *(undefined8 *)(param_1 + 0x100);
  uStack_1a8 = *(undefined8 *)(param_1 + 0x118);
  uStack_1b0 = *(undefined8 *)(param_1 + 0x110);
  uStack_218 = *(undefined8 *)(param_1 + 0x128);
  local_220 = *(undefined8 *)(param_1 + 0x120);
  uStack_208 = *(undefined8 *)(param_1 + 0x138);
  uStack_210 = *(undefined8 *)(param_1 + 0x130);
  uStack_1f8 = *(undefined8 *)(param_1 + 0x148);
  local_200 = *(undefined8 *)(param_1 + 0x140);
  uStack_1e8 = *(undefined8 *)(param_1 + 0x158);
  uStack_1f0 = *(undefined8 *)(param_1 + 0x150);
  uStack_258 = *(undefined8 *)(param_1 + 0x168);
  local_260 = *(undefined8 *)(param_1 + 0x160);
  uStack_248 = *(undefined8 *)(param_1 + 0x178);
  uStack_250 = *(undefined8 *)(param_1 + 0x170);
  uStack_238 = *(undefined8 *)(param_1 + 0x188);
  local_240 = *(undefined8 *)(param_1 + 0x180);
  uStack_228 = *(undefined8 *)(param_1 + 0x198);
  uStack_230 = *(undefined8 *)(param_1 + 400);
  uStack_d8 = *(undefined8 *)(param_1 + 0x1a8);
  local_e0 = *(undefined8 *)(param_1 + 0x1a0);
  uStack_f8 = *(undefined8 *)(param_1 + 0x1bc);
  local_100 = *(undefined8 *)(param_1 + 0x1b4);
  uStack_118 = *(undefined8 *)(param_1 + 0x1d0);
  local_120 = *(undefined8 *)(param_1 + 0x1c8);
  local_264[0] = A2DP_ParseInfoSsc((tA2DP_SSC_CIE *)&local_160,param_2,param_3);
  if (local_264[0] == 0) {
    bVar4 = local_160._6_1_;
    pbVar15 = (byte *)(ulong)local_160._6_1_;
    local_298 = (byte)local_158;
    if (local_160._6_1_ == 0xffffff80) {
      local_294 = 8;
LAB_00a92660:
      pbVar16 = pbVar15;
      if ((local_158 & 0xff) == 4) goto LAB_00a926a4;
      local_278 = 0;
    }
    else {
      local_294 = 1;
      if ((((local_160._6_1_ != 0 & (param_3 ^ 0xffU)) != 0) || ((local_158 & 0xff) != 4)) ||
         (DAT_00fabbe8 != '\x04')) goto LAB_00a92660;
      local_294 = 2;
      *(undefined4 *)(param_1 + 0xe8) = 2;
      pbVar16 = (byte *)0x10;
LAB_00a926a4:
      if (*(int *)(param_1 + 0x128) == 1) {
        *(undefined8 *)(param_1 + 0x128) = 0x200000002;
      }
      local_298 = 4;
      local_278 = 1;
    }
    local_b0 = (byte *)(param_1 + 0x128);
    piVar1 = (int *)(param_1 + 0xe8);
    local_138._0_4_ = 0x2df;
    ppbStack_148 = &local_c0;
    local_b8 = (code *)0x0;
    local_a8 = 
    _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I29btav_a2dp_codec_sample_rate_tEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
    ;
    local_98 = 
    _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I29btav_a2dp_codec_sample_rate_tEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
    ;
    uStack_90 = 0x3de6;
    local_130 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
    pcStack_128 = "setCodecConfig";
    local_150 = 3;
    local_140 = 0x3de6;
    local_c0 = pbVar16;
    local_a0 = piVar1;
    bluetooth::log_internal::vlog
              (5,"a2dp_vendor_ssc",&local_138,
               "peer sampleRates = 0x{:x}, user.sample_rate = 0x{:x}, selectable = 0x{:x}",0x49,
               &local_150);
    iVar11 = *(int *)(param_1 + 0x128);
    *(undefined4 *)(param_1 + 0x68) = 0;
    uVar14 = (uint)pbVar16;
    if (iVar11 == 8) {
      if ((local_158._1_1_ != '\x02') || (local_158._2_1_ == '\x01')) goto LAB_00a927e0;
      bVar7 = false;
      bVar12 = 0;
      *(undefined4 *)(param_1 + 0x68) = 8;
      *(undefined4 *)(param_1 + 0xe8) = 8;
LAB_00a929f0:
      local_138._0_4_ = 0x337;
      local_130 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
      pcStack_128 = "setCodecConfig";
      local_b8 = 
      _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I33btav_a2dp_codec_bits_per_sample_tEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
      ;
      local_b0 = (byte *)0xf;
      ppbStack_148 = &local_c0;
      *(undefined4 *)(param_1 + 0x6c) = 0;
      local_150 = 1;
      local_140 = 0xf;
      local_c0 = (byte *)(param_1 + 300);
      bluetooth::log_internal::vlog
                (5,"a2dp_vendor_ssc",&local_138,"bits per sample: user preference = 0x{:x}",0x29,
                 &local_150);
      uVar14 = *(uint *)(param_1 + 300);
      if (uVar14 < 9) {
        if ((1 << (ulong)(uVar14 & 0x1f) & 0x106U) == 0) {
          if ((1 << (ulong)(uVar14 & 0x1f) & 0x11U) == 0) goto LAB_00a92dac;
          *(undefined4 *)(param_1 + 0x6c) = 0;
          *(undefined4 *)(param_1 + 0xec) = 0;
          goto LAB_00a92a94;
        }
        *(uint *)(param_1 + 0x6c) = uVar14;
        *(uint *)(param_1 + 0xec) = uVar14;
      }
      else {
LAB_00a92dac:
        if (*(int *)(param_1 + 0xec) == 0) {
LAB_00a92a94:
          uVar14 = local_294;
          if ((local_294 & 8) != 0) {
            uVar14 = 8;
          }
          if (local_294 != 0) {
            *(uint *)(param_1 + 0xec) = local_294;
          }
          iVar11 = *(int *)(param_1 + 0x6c);
        }
        else {
          iVar11 = *(int *)(param_1 + 0x6c);
          uVar14 = local_294;
        }
        if (iVar11 == 0) {
          local_c0 = (byte *)(param_1 + 0x16c);
          local_138._0_4_ = 0x290;
          local_130 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
          pcStack_128 = "select_audio_bits_per_sample";
          ppbStack_148 = &local_c0;
          local_b8 = 
          _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IK33btav_a2dp_codec_bits_per_sample_tEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESH_SI_SK_
          ;
          local_b0 = (byte *)0xf;
          local_150 = 1;
          local_140 = 0xf;
          bluetooth::log_internal::vlog(3,"a2dp_vendor_ssc",&local_138,"0x{:x}",6,&local_150);
          uVar5 = *(uint *)(param_1 + 0x16c);
          if ((uVar5 < 9) && ((1 << (ulong)(uVar5 & 0x1f) & 0x106U) != 0)) {
            *(uint *)(param_1 + 0x6c) = uVar5;
          }
          else {
            local_c0 = (byte *)(ulong)uVar14;
            uVar13 = 1;
            local_138._0_4_ = 0x276;
            local_130 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
            pcStack_128 = "select_best_bits_per_sample";
            ppbStack_148 = &local_c0;
            local_b8 = (code *)0x0;
            local_b0 = (byte *)0x6;
            local_150 = 1;
            local_140 = 6;
            bluetooth::log_internal::vlog(3,"a2dp_vendor_ssc",&local_138,"0x{:x}",6,&local_150);
            if ((uVar14 & 1) == 0) {
              if ((uVar14 >> 1 & 1) == 0) {
                if (uVar14 >> 3 != 0) {
                  uVar13 = 8;
                  goto LAB_00a93018;
                }
                if (*(int *)(param_1 + 0x6c) == 0) {
                  local_138 = CONCAT44(local_138._4_4_,0x366);
                  local_b8 = 
                  _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I33btav_a2dp_codec_bits_per_sample_tEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
                  ;
                  local_b0 = (byte *)0xf;
                  pcVar8 = "cannot match bits per sample: user preference = 0x{:x}";
                  local_150 = 1;
                  local_140 = 0xf;
                  uVar9 = 0x36;
                  local_c0 = (byte *)(param_1 + 300);
                  goto LAB_00a93000;
                }
              }
              else {
                *(undefined4 *)(param_1 + 0x6c) = 2;
              }
            }
            else {
LAB_00a93018:
              *(undefined4 *)(param_1 + 0x6c) = uVar13;
            }
          }
        }
      }
      local_c0 = (byte *)(param_1 + 0x130);
      local_138 = CONCAT44(local_138._4_4_,0x36e);
      local_b8 = 
      _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I30btav_a2dp_codec_channel_mode_tEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
      ;
      local_b0 = (byte *)0xf;
      ppbStack_148 = &local_c0;
      local_130 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
      pcStack_128 = "setCodecConfig";
      local_150 = 1;
      local_140 = 0xf;
      bluetooth::log_internal::vlog(3,"a2dp_vendor_ssc",&local_138,&DAT_001830fe,4,&local_150);
      *(uint *)(param_1 + 0x70) = *(uint *)(param_1 + 0x70) | 2;
      *(uint *)(param_1 + 0xf0) = *(uint *)(param_1 + 0xf0) | 2;
      if (param_4 != (undefined2 *)0x0) {
        bVar10 = local_160._7_1_;
        local_c0._0_4_ = 0x6a;
        local_b8 = (code *)0x1e4d6a;
        local_b0 = (byte *)0x10e2af;
        uVar14 = local_278 & (uVar14 & 2) >> 1;
        bVar2 = local_160._7_1_ & 8;
        local_138 = 0;
        bluetooth::log_internal::vlog(3,"a2dp_vendor_ssc",&local_c0,&DAT_0013f82c,0,&local_138);
        *(undefined1 *)(param_4 + 1) = 0xff;
        *param_4 = 9;
        if (bVar12 == 0x80) {
          bVar7 = true;
        }
        *(undefined4 *)((long)param_4 + 3) = 0x75;
        bVar3 = 4;
        if (uVar14 == 0) {
          bVar3 = bVar12;
        }
        if (!bVar7) {
          bVar3 = 2;
        }
        *(undefined2 *)((long)param_4 + 7) = 0x103;
        *(byte *)((long)param_4 + 9) = bVar2 | bVar3;
        if (*(long *)(param_1 + 0x138) != 0) {
          *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x138);
        }
        if (*(long *)(param_1 + 0x140) != 0) {
          *(long *)(param_1 + 0x80) = *(long *)(param_1 + 0x140);
        }
        if (*(long *)(param_1 + 0x148) != 0) {
          *(long *)(param_1 + 0x88) = *(long *)(param_1 + 0x148);
        }
        if (*(long *)(param_1 + 0x150) != 0) {
          *(long *)(param_1 + 0x90) = *(long *)(param_1 + 0x150);
        }
        if ((param_3 & 1U) == 0) {
          local_c0 = (byte *)CONCAT44(local_c0._4_4_,0x6a);
          local_b8 = (code *)0x1e4d6a;
          local_b0 = (byte *)0x10e2af;
          local_138 = 0;
          bluetooth::log_internal::vlog(3,"a2dp_vendor_ssc",&local_c0,&DAT_0013f82c,0,&local_138);
          *(undefined2 *)(param_1 + 0x1c8) = 9;
          *(undefined1 *)(param_1 + 0x1ca) = 0xff;
          *(undefined4 *)(param_1 + 0x1cb) = (undefined4)local_160;
          *(undefined2 *)(param_1 + 0x1cf) = local_160._4_2_;
          if (((bVar4 == 0xffffff80) || (local_158._1_1_ != '\x02')) || (local_158._2_1_ == '\x01'))
          {
            if (local_278 == 0) {
              bVar10 = local_298 | bVar4 | bVar10;
            }
            else {
              bVar10 = bVar10 | 4;
            }
          }
          else {
            bVar10 = bVar10 | 2;
          }
          *(byte *)(param_1 + 0x1d1) = bVar10;
        }
        else {
          local_c0 = (byte *)CONCAT44(local_c0._4_4_,0x6a);
          local_b8 = (code *)0x1e4d6a;
          local_b0 = (byte *)0x10e2af;
          local_138 = 0;
          bluetooth::log_internal::vlog(3,"a2dp_vendor_ssc",&local_c0,&DAT_0013f82c,0,&local_138);
          *(undefined2 *)(param_1 + 0x1b4) = 9;
          *(undefined1 *)(param_1 + 0x1b6) = 0xff;
          *(undefined4 *)(param_1 + 0x1b7) = (undefined4)local_160;
          *(undefined2 *)(param_1 + 0x1bb) = local_160._4_2_;
          if (((bVar4 == 0xffffff80) || (local_158._1_1_ != '\x02')) || (local_158._2_1_ == '\x01'))
          {
            if (local_278 == 0) {
              *(byte *)(param_1 + 0x1bd) = local_298 | bVar4 | bVar10;
            }
            else {
              *(byte *)(param_1 + 0x1bd) = bVar10 | 4;
            }
          }
          else {
            *(byte *)(param_1 + 0x1bd) = bVar10 | 2;
          }
        }
        local_c0 = (byte *)CONCAT44(local_c0._4_4_,0x6a);
        local_b8 = (code *)0x1e4d6a;
        local_b0 = (byte *)0x10e2af;
        local_138 = 0;
        bluetooth::log_internal::vlog(3,"a2dp_vendor_ssc",&local_c0,&DAT_0013f82c,0,&local_138);
        *(undefined2 *)(param_1 + 0x1a0) = 9;
        *(undefined1 *)(param_1 + 0x1a2) = 0xff;
        *(undefined4 *)(param_1 + 0x1a3) = 0x75;
        bVar10 = 0;
        bVar4 = 4;
        if (uVar14 == 0) {
          bVar4 = bVar12;
        }
        if (!bVar7) {
          bVar4 = 2;
        }
        *(undefined2 *)(param_1 + 0x1a7) = 0x103;
        *(byte *)(param_1 + 0x1a9) = bVar2 | bVar4;
        goto LAB_00a92e98;
      }
    }
    else {
      if (iVar11 == 2) {
        if ((uVar14 >> 4 & 1) == 0) goto LAB_00a927e0;
        *(undefined4 *)(param_1 + 0x68) = 2;
        *(undefined4 *)(param_1 + 0xe8) = 2;
        bVar12 = 0x10;
        goto LAB_00a929ec;
      }
      if ((iVar11 == 1) && ((uVar14 >> 5 & 1) != 0)) {
        bVar7 = true;
        *(undefined4 *)(param_1 + 0x68) = 1;
        *(undefined4 *)(param_1 + 0xe8) = 1;
        bVar12 = 0x20;
        goto LAB_00a929f0;
      }
LAB_00a927e0:
      if (*piVar1 == 0) {
        if ((uVar14 >> 5 & 1) == 0) {
          if ((uVar14 >> 4 & 1) == 0) goto LAB_00a92804;
          iVar11 = 2;
        }
        else {
          iVar11 = 1;
        }
        *piVar1 = iVar11;
      }
LAB_00a92804:
      local_c0 = (byte *)(param_1 + 0x168);
      local_138._0_4_ = 0x24c;
      local_130 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
      pcStack_128 = "select_audio_sample_rate";
      local_b8 = 
      _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000IK29btav_a2dp_codec_sample_rate_tEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESH_SI_SK_
      ;
      local_b0 = (byte *)0xf;
      ppbStack_148 = &local_c0;
      local_150 = 1;
      local_140 = 0xf;
      bluetooth::log_internal::vlog
                (3,"a2dp_vendor_ssc",&local_138,"sample_rate : 0x{:x}",0x14,&local_150);
      iVar11 = *(int *)(param_1 + 0x168);
      if (iVar11 != 8) {
        if (iVar11 == 2) {
          if ((uVar14 >> 4 & 1) != 0) {
            bVar12 = 0x10;
            goto LAB_00a929bc;
          }
        }
        else if ((iVar11 == 1) && ((uVar14 >> 5 & 1) != 0)) {
          bVar12 = 0x20;
LAB_00a929bc:
          *(int *)(param_1 + 0x68) = iVar11;
          goto LAB_00a929ec;
        }
      }
      local_c0 = (byte *)((ulong)pbVar16 & 0x20);
      local_138._0_4_ = 0x22e;
      local_130 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
      pcStack_128 = "select_best_sample_rate";
      local_b8 = (code *)0x0;
      local_b0 = (byte *)0x6;
      local_150 = 1;
      local_140 = 6;
      ppbStack_148 = &local_c0;
      bluetooth::log_internal::vlog
                (3,"a2dp_vendor_ssc",&local_138,"sample_rate : 0x{:x}",0x14,&local_150);
      if ((uVar14 >> 5 & 1) != 0) {
        *(undefined4 *)(param_1 + 0x68) = 1;
        bVar7 = true;
        bVar12 = 0x20;
        goto LAB_00a929f0;
      }
      local_138._0_4_ = 0x22e;
      local_130 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
      pcStack_128 = "select_best_sample_rate";
      local_b8 = (code *)0x0;
      local_b0 = (byte *)0x6;
      local_150 = 1;
      local_140 = 6;
      ppbStack_148 = &local_c0;
      local_c0 = pbVar16;
      bluetooth::log_internal::vlog
                (3,"a2dp_vendor_ssc",&local_138,"sample_rate : 0x{:x}",0x14,&local_150);
      if ((uVar14 >> 4 & 1) != 0) {
        bVar12 = 0x10;
        *(undefined4 *)(param_1 + 0x68) = 2;
LAB_00a929ec:
        bVar7 = true;
        goto LAB_00a929f0;
      }
      if (*(int *)(param_1 + 0x68) != 0) {
        bVar12 = 0;
        goto LAB_00a929ec;
      }
      local_138 = CONCAT44(local_138._4_4_,0x32b);
      local_c0 = &DAT_00000020;
      local_b8 = (code *)0x0;
      pcVar8 = "cannot match sample frequency: source caps = 0x{:x} sink info = 0x{:x}";
      uVar9 = 0x46;
      local_a8 = (code *)0x0;
      local_a0 = (int *)0xc6;
      local_150 = 2;
      local_140 = 0xc6;
      local_b0 = pbVar15;
LAB_00a93000:
      ppbStack_148 = &local_c0;
      pcStack_128 = "setCodecConfig";
      local_130 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
      bluetooth::log_internal::vlog(6,"a2dp_vendor_ssc",&local_138,pcVar8,uVar9,&local_150);
    }
  }
  else {
    local_c0 = local_264;
    local_138 = CONCAT44(local_138._4_4_,0x2bd);
    local_130 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
    pcStack_128 = "setCodecConfig";
    local_b8 = 
    _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I12tA2DP_STATUSEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
    ;
    local_b0 = (byte *)0xf;
    local_150 = 1;
    local_140 = 0xf;
    ppbStack_148 = &local_c0;
    bluetooth::log_internal::vlog
              (6,"a2dp_vendor_ssc",&local_138,"can\'t parse peer\'s Sink capabilities: error = {}",
               0x30,&local_150);
  }
  local_c0 = (byte *)CONCAT44(local_c0._4_4_,0x3a1);
  local_b8 = (code *)0x1e4d6a;
  local_b0 = (byte *)0x164228;
  local_138 = 0;
  bluetooth::log_internal::vlog(5,"a2dp_vendor_ssc",&local_c0,&DAT_00134072,4,&local_138);
  *(undefined8 *)(param_1 + 0x68) = uStack_198;
  *(undefined8 *)(param_1 + 0x60) = local_1a0;
  *(undefined8 *)(param_1 + 0x78) = uStack_188;
  *(undefined8 *)(param_1 + 0x70) = uStack_190;
  *(undefined4 *)(param_1 + 0x1b0) = local_d0;
  *(undefined8 *)(param_1 + 0x88) = uStack_178;
  *(undefined8 *)(param_1 + 0x80) = local_180;
  *(undefined8 *)(param_1 + 0x98) = uStack_168;
  *(undefined8 *)(param_1 + 0x90) = uStack_170;
  *(undefined4 *)(param_1 + 0x1c4) = local_f0;
  *(undefined8 *)(param_1 + 0xe8) = uStack_1d8;
  *(undefined8 *)(param_1 + 0xe0) = local_1e0;
  *(undefined8 *)(param_1 + 0xf8) = uStack_1c8;
  *(undefined8 *)(param_1 + 0xf0) = uStack_1d0;
  *(undefined4 *)(param_1 + 0x1d8) = local_110;
  *(undefined8 *)(param_1 + 0x108) = uStack_1b8;
  *(undefined8 *)(param_1 + 0x100) = local_1c0;
  *(undefined8 *)(param_1 + 0x118) = uStack_1a8;
  *(undefined8 *)(param_1 + 0x110) = uStack_1b0;
  *(undefined8 *)(param_1 + 0x148) = uStack_1f8;
  *(undefined8 *)(param_1 + 0x140) = local_200;
  *(undefined8 *)(param_1 + 0x158) = uStack_1e8;
  *(undefined8 *)(param_1 + 0x150) = uStack_1f0;
  *(undefined8 *)(param_1 + 0x128) = uStack_218;
  *(undefined8 *)(param_1 + 0x120) = local_220;
  *(undefined8 *)(param_1 + 0x138) = uStack_208;
  *(undefined8 *)(param_1 + 0x130) = uStack_210;
  *(undefined8 *)(param_1 + 0x188) = uStack_238;
  *(undefined8 *)(param_1 + 0x180) = local_240;
  *(undefined8 *)(param_1 + 0x198) = uStack_228;
  *(undefined8 *)(param_1 + 400) = uStack_230;
  *(undefined8 *)(param_1 + 0x168) = uStack_258;
  *(undefined8 *)(param_1 + 0x160) = local_260;
  *(undefined8 *)(param_1 + 0x178) = uStack_248;
  *(undefined8 *)(param_1 + 0x170) = uStack_250;
  *(undefined8 *)(param_1 + 0x1a8) = uStack_d8;
  *(undefined8 *)(param_1 + 0x1a0) = local_e0;
  *(undefined8 *)(param_1 + 0x1bc) = uStack_f8;
  *(undefined8 *)(param_1 + 0x1b4) = local_100;
  *(undefined8 *)(param_1 + 0x1d0) = uStack_118;
  *(undefined8 *)(param_1 + 0x1c8) = local_120;
  bVar10 = local_264[0];
LAB_00a92e98:
  std::recursive_mutex::unlock((recursive_mutex *)(param_1 + 8));
  if (*(long *)(lVar6 + 0x28) == local_78) {
    return bVar10;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== setPeerCodecCapabilities @ 00a93024 size 732 :: A2DP_BuildInfoSsc | a2dp_vendor_ssc | packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc */

/* WARNING: Unknown calling convention: __rustcall */
/* A2dpCodecConfigSsc::setPeerCodecCapabilities */

bool __rustcall A2dpCodecConfigSsc::setPeerCodecCapabilities(long param_1,uchar *param_2)

{
  long lVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  byte local_134 [4];
  undefined8 local_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 local_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 local_f0;
  undefined4 local_e8;
  undefined8 local_e0;
  undefined1 **ppuStack_d8;
  undefined8 local_d0;
  undefined8 local_c8;
  char *local_c0;
  char *pcStack_b8;
  undefined8 local_b0;
  undefined8 uStack_a8;
  undefined4 local_a0;
  byte *local_90;
  code *local_88;
  int *local_80;
  code *local_78;
  undefined8 uStack_70;
  long local_58;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_58 = *(long *)(lVar1 + 0x28);
  std::recursive_mutex::lock((recursive_mutex *)(param_1 + 8));
  uStack_128 = *(undefined8 *)(param_1 + 0xe8);
  local_130 = *(undefined8 *)(param_1 + 0xe0);
  uStack_118 = *(undefined8 *)(param_1 + 0xf8);
  uStack_120 = *(undefined8 *)(param_1 + 0xf0);
  local_a0 = *(undefined4 *)(param_1 + 0x1c4);
  local_e8 = 0;
  uStack_108 = *(undefined8 *)(param_1 + 0x108);
  local_110 = *(undefined8 *)(param_1 + 0x100);
  uStack_f8 = *(undefined8 *)(param_1 + 0x118);
  uStack_100 = *(undefined8 *)(param_1 + 0x110);
  local_f0 = 0;
  uStack_a8 = *(undefined8 *)(param_1 + 0x1bc);
  local_b0 = *(undefined8 *)(param_1 + 0x1b4);
  bVar2 = A2DP_ParseInfoSsc((tA2DP_SSC_CIE *)&local_f0,param_2,true);
  local_134[0] = bVar2;
  if (bVar2 == 0) {
    local_c8 = CONCAT44(local_c8._4_4_,0x3bd);
    local_c0 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
    pcStack_b8 = "setPeerCodecCapabilities";
    local_90 = (byte *)(param_1 + 0x68);
    ppuStack_d8 = &local_90;
    local_88 = 
    _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I29btav_a2dp_codec_sample_rate_tEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
    ;
    local_78 = 
    _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I33btav_a2dp_codec_bits_per_sample_tEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
    ;
    uStack_70 = 0x1ef;
    local_e0 = 2;
    local_d0 = 0x1ef;
    local_80 = (int *)(param_1 + 0x6c);
    bluetooth::log_internal::vlog
              (3,"a2dp_vendor_ssc",&local_c8,
               "peer sampleRates = 0x{:x}, peer bits_per_sample = 0x{:x}",0x38,&local_e0);
    iVar4 = *(int *)(param_1 + 0x68);
    if ((iVar4 == 8) || (iVar4 = *(int *)(param_1 + 0x6c), iVar4 == 2)) {
      *(int *)(param_1 + 0xe8) = iVar4;
    }
    else {
      if ((local_f0._6_1_ >> 5 & 1) != 0) {
        *(uint *)(param_1 + 0xe8) = *(uint *)(param_1 + 0xe8) | 1;
      }
      iVar4 = 1;
    }
    *(int *)(param_1 + 0xec) = iVar4;
    *(uint *)(param_1 + 0xf0) = *(uint *)(param_1 + 0xf0) | 2;
    local_90 = (byte *)CONCAT44(local_90._4_4_,0x6a);
    local_88 = (code *)0x1e4d6a;
    local_80 = (int *)0x10e2af;
    local_c8 = 0;
    bluetooth::log_internal::vlog(3,"a2dp_vendor_ssc",&local_90,&DAT_0013f82c,0,&local_c8);
    *(undefined2 *)(param_1 + 0x1b4) = 9;
    *(undefined1 *)(param_1 + 0x1b6) = 0xff;
    *(undefined4 *)(param_1 + 0x1b7) = (undefined4)local_f0;
    *(undefined2 *)(param_1 + 0x1bb) = local_f0._4_2_;
    if (((local_e8._1_1_ == '\x02') && (local_f0._6_1_ != 0x80)) && (local_e8._2_1_ != '\x01')) {
      bVar3 = local_f0._7_1_ | 2;
    }
    else if ((byte)local_e8 == 4) {
      bVar3 = local_f0._7_1_ | 4;
    }
    else {
      bVar3 = (byte)local_e8 | local_f0._6_1_ | local_f0._7_1_;
    }
    *(byte *)(param_1 + 0x1bd) = bVar3;
  }
  else {
    local_c8 = CONCAT44(local_c8._4_4_,0x3b9);
    local_c0 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc.cc";
    pcStack_b8 = "setPeerCodecCapabilities";
    local_90 = local_134;
    local_88 = 
    _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I12tA2DP_STATUSEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
    ;
    local_80 = (int *)0xf;
    ppuStack_d8 = &local_90;
    local_e0 = 1;
    local_d0 = 0xf;
    bluetooth::log_internal::vlog
              (6,"a2dp_vendor_ssc",&local_c8,"can\'t parse peer\'s capabilities: error = {}",0x2b,
               &local_e0);
    *(undefined4 *)(param_1 + 0x1c4) = local_a0;
    *(undefined8 *)(param_1 + 0xe8) = uStack_128;
    *(undefined8 *)(param_1 + 0xe0) = local_130;
    *(undefined8 *)(param_1 + 0xf8) = uStack_118;
    *(undefined8 *)(param_1 + 0xf0) = uStack_120;
    *(undefined8 *)(param_1 + 0x108) = uStack_108;
    *(undefined8 *)(param_1 + 0x100) = local_110;
    *(undefined8 *)(param_1 + 0x118) = uStack_f8;
    *(undefined8 *)(param_1 + 0x110) = uStack_100;
    *(undefined8 *)(param_1 + 0x1bc) = uStack_a8;
    *(undefined8 *)(param_1 + 0x1b4) = local_b0;
  }
  std::recursive_mutex::unlock((recursive_mutex *)(param_1 + 8));
  if (*(long *)(lVar1 + 0x28) == local_58) {
    return bVar2 == 0;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== A2DP_VendorLoadEncoderSsc @ 00a93300 size 1436 :: A2DP_VendorLoadEncoderSsc | A2DP_VendorUnloadEncoderSsc | a2dp_vendor_ssc_encoder | packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc | ssc_encode | ssc_encoder_create | ssc_encoder_create_func ({}) | ssc_encoder_create_func for 2nd ({}) | ssc_encoder_destroy */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* A2DP_VendorLoadEncoderSsc() */

void A2DP_VendorLoadEncoderSsc(void)

{
  char *pcVar1;
  long lVar2;
  undefined8 uVar3;
  char *pcVar4;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  undefined4 local_100 [2];
  char *local_f8;
  char *pcStack_f0;
  undefined1 uStack_e1;
  undefined4 local_e0 [2];
  char *local_d8;
  char *pcStack_d0;
  undefined1 uStack_c5;
  uint local_c4;
  undefined8 local_c0;
  uint *puStack_b8;
  undefined8 local_b0;
  undefined8 local_a8;
  char *local_a0;
  char *pcStack_98;
  uint local_90;
  undefined4 uStack_8c;
  undefined1 uStack_88;
  undefined7 uStack_87;
  undefined1 uStack_80;
  undefined1 uStack_7f;
  undefined6 uStack_7e;
  undefined8 local_78;
  undefined8 uStack_70;
  long local_58;
  
  *in_x18 = unaff_x30;
  lVar2 = tpidr_el0;
  local_58 = *(long *)(lVar2 + 0x28);
  if (DAT_01043e30 != 0) {
LAB_00a9333c:
    uVar3 = 1;
    goto LAB_00a93340;
  }
  uStack_87 = 0x65646f636e6520;
  uStack_80 = 0x72;
  local_90 = 0x61637320;
  uStack_8c = 0x6c62616c;
  uStack_88 = 0x65;
  uStack_7f = 0;
  DAT_01043e30 = A2DP_VendorCodecLoadExternalLib
                           ((string *)",libScalable_Encoder.so",(string *)&local_90);
  if ((local_90 & 1) != 0) {
    operator_delete((void *)CONCAT62(uStack_7e,CONCAT11(uStack_7f,uStack_80)),
                    CONCAT44(uStack_8c,local_90) & 0xfffffffffffffffe);
  }
  uVar3 = 0;
  if (DAT_01043e30 == 0) goto LAB_00a93340;
  DAT_01043e38 = (code *)dlsym(DAT_01043e30,"ssc_encoder_create");
  if (DAT_01043e38 == (code *)0x0) {
    pcVar4 = (char *)dlerror();
    local_a8 = CONCAT44(local_a8._4_4_,0x105);
    local_a0 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
    pcStack_98 = "A2DP_VendorLoadEncoderSsc";
    local_90 = 0x1160d0;
    uStack_8c = 0;
    uStack_88 = 0;
    uStack_87 = 0;
    pcVar1 = "(nullptr)";
    if (pcVar4 != (char *)0x0) {
      pcVar1 = pcVar4;
    }
    puStack_b8 = &local_90;
    uStack_80 = SUB81(pcVar1,0);
    uStack_7f = (undefined1)((ulong)pcVar1 >> 8);
    uStack_7e = (undefined6)((ulong)pcVar1 >> 0x10);
    local_c0 = 2;
    uStack_70 = 0x18c;
    local_78 = 0;
    local_b0 = 0x18c;
    bluetooth::log_internal::vlog
              (6,"a2dp_vendor_ssc_encoder",&local_a8,
               "cannot find function \'{}\' in the encoder library: {}",0x34,&local_c0);
    local_90 = 0x134;
    uStack_88 = 0x69;
    uStack_87 = 0x1263;
    uStack_80 = 0xe4;
    uStack_7f = 0xc4;
    uStack_7e = 0x15;
    local_a8 = 0;
    bluetooth::log_internal::vlog(3,"a2dp_vendor_ssc_encoder",&local_90,&DAT_0013f82c,0,&local_a8);
    if (DAT_0104ab30 != 0) {
      (*DAT_01043e40)();
      DAT_0104ab30 = 0;
    }
    if (DAT_0104ab38 != 0) {
      (*DAT_01043e40)();
      DAT_0104ab38 = 0;
    }
LAB_00a936d0:
    DAT_01043e40 = (code *)0x0;
    DAT_01043e38 = (code *)0x0;
    DAT_01043e48 = 0;
    uVar3 = 0;
    if (DAT_01043e30 == 0) goto LAB_00a93340;
  }
  else {
    DAT_01043e40 = (code *)dlsym(DAT_01043e30,"ssc_encoder_destroy");
    if (DAT_01043e40 == (code *)0x0) {
      pcVar4 = (char *)dlerror();
      local_a8 = CONCAT44(local_a8._4_4_,0x10e);
      local_a0 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
      pcStack_98 = "A2DP_VendorLoadEncoderSsc";
      local_90 = 0x12da8f;
      uStack_8c = 0;
      uStack_88 = 0;
      uStack_87 = 0;
      pcVar1 = "(nullptr)";
      if (pcVar4 != (char *)0x0) {
        pcVar1 = pcVar4;
      }
      puStack_b8 = &local_90;
      uStack_80 = SUB81(pcVar1,0);
      uStack_7f = (undefined1)((ulong)pcVar1 >> 8);
      uStack_7e = (undefined6)((ulong)pcVar1 >> 0x10);
      local_c0 = 2;
      uStack_70 = 0x18c;
      local_78 = 0;
      local_b0 = 0x18c;
      bluetooth::log_internal::vlog
                (6,"a2dp_vendor_ssc_encoder",&local_a8,
                 "cannot find function \'{}\' in the encoder library: {}",0x34,&local_c0);
      local_90 = 0x134;
      uStack_88 = 0x69;
      uStack_87 = 0x1263;
      uStack_80 = 0xe4;
      uStack_7f = 0xc4;
      uStack_7e = 0x15;
      local_a8 = 0;
      bluetooth::log_internal::vlog(3,"a2dp_vendor_ssc_encoder",&local_90,&DAT_0013f82c,0,&local_a8)
      ;
      if (DAT_0104ab30 != 0) {
        (*DAT_01043e40)();
        DAT_0104ab30 = 0;
      }
      if (DAT_0104ab38 != 0) {
        (*DAT_01043e40)();
        DAT_0104ab38 = 0;
      }
      goto LAB_00a936d0;
    }
    DAT_01043e48 = dlsym(DAT_01043e30,"ssc_encode");
    if (DAT_01043e48 != 0) {
      local_c4 = 0;
      DAT_01043e7c = DAT_0104ab14;
      if (DAT_0104ab14 != 96000) {
        DAT_01043e7c = 0xac44;
      }
      DAT_0104ab30 = (*DAT_01043e38)(DAT_01043e7c,2,DAT_0104ab18,&local_c4);
      if (local_c4 != 0) {
        local_a8 = CONCAT44(local_a8._4_4_,0x126);
        local_a0 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
        pcStack_98 = "A2DP_VendorLoadEncoderSsc";
        puStack_b8 = &local_90;
        local_90 = local_c4;
        uStack_8c = 0;
        uStack_88 = 0;
        uStack_87 = 0;
        uStack_80 = 3;
        uStack_7f = 0;
        uStack_7e = 0;
        local_c0 = 1;
        local_b0 = 3;
        bluetooth::log_internal::vlog
                  (6,"a2dp_vendor_ssc_encoder",&local_a8,"ssc_encoder_create_func ({})",0x1c,
                   &local_c0);
        uVar3 = 0;
        goto LAB_00a93340;
      }
      DAT_0104ab38 = (*DAT_01043e38)(DAT_01043e7c,2,DAT_0104ab18,&local_c4);
      if (local_c4 != 0) {
        local_e0[0] = 300;
        local_d8 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
        pcStack_d0 = "A2DP_VendorLoadEncoderSsc";
        bluetooth::log::error<int&>::log
                  (&uStack_c5,"ssc_encoder_create_func for 2nd ({})",0x24,&local_c4,local_e0);
        uVar3 = 0;
        goto LAB_00a93340;
      }
      local_100[0] = 0x12f;
      local_f8 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
      pcStack_f0 = "A2DP_VendorLoadEncoderSsc";
      bluetooth::log::debug<unsigned_int&>::log
                (&uStack_e1,"sample_rate {}",0xe,&DAT_01043e7c,local_100);
      goto LAB_00a9333c;
    }
    pcVar4 = (char *)dlerror();
    local_a8 = CONCAT44(local_a8._4_4_,0x117);
    local_a0 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
    pcStack_98 = "A2DP_VendorLoadEncoderSsc";
    local_90 = 0x1b3e6a;
    uStack_8c = 0;
    uStack_88 = 0;
    uStack_87 = 0;
    pcVar1 = "(nullptr)";
    if (pcVar4 != (char *)0x0) {
      pcVar1 = pcVar4;
    }
    puStack_b8 = &local_90;
    uStack_80 = SUB81(pcVar1,0);
    uStack_7f = (undefined1)((ulong)pcVar1 >> 8);
    uStack_7e = (undefined6)((ulong)pcVar1 >> 0x10);
    local_c0 = 2;
    uStack_70 = 0x18c;
    local_78 = 0;
    local_b0 = 0x18c;
    bluetooth::log_internal::vlog
              (6,"a2dp_vendor_ssc_encoder",&local_a8,
               "cannot find function \'{}\' in the encoder library: {}",0x34,&local_c0);
    local_90 = 0x134;
    uStack_88 = 0x69;
    uStack_87 = 0x1263;
    uStack_80 = 0xe4;
    uStack_7f = 0xc4;
    uStack_7e = 0x15;
    local_a8 = 0;
    bluetooth::log_internal::vlog(3,"a2dp_vendor_ssc_encoder",&local_90,&DAT_0013f82c,0,&local_a8);
    if (DAT_0104ab30 != 0) {
      (*DAT_01043e40)();
      DAT_0104ab30 = 0;
    }
    if (DAT_0104ab38 != 0) {
      (*DAT_01043e40)();
      DAT_0104ab38 = 0;
    }
    DAT_01043e38 = (code *)0x0;
    DAT_01043e40 = (code *)0x0;
    DAT_01043e48 = 0;
    if (DAT_01043e30 == 0) {
      uVar3 = 0;
      goto LAB_00a93340;
    }
  }
  DAT_01043e48 = 0;
  DAT_01043e40 = (code *)0x0;
  DAT_01043e38 = (code *)0x0;
  dlclose();
  uVar3 = 0;
  DAT_01043e30 = 0;
LAB_00a93340:
  if (*(long *)(lVar2 + 0x28) != local_58) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(uVar3);
  }
  return;
}


/* ==== log @ 00a9389c size 168 :: a2dp_vendor_ssc_encoder */

/* bluetooth::log::debug<unsigned int&>::log(std::basic_format_string<char, unsigned int&>, unsigned
   int&, bluetooth::log_internal::source_location) */

void bluetooth::log::debug<unsigned_int&>::log
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,uint *param_4,
               undefined8 *param_5)

{
  long lVar1;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  undefined8 local_88;
  ulong *puStack_80;
  undefined8 local_78;
  undefined8 local_70;
  undefined8 uStack_68;
  undefined8 local_60;
  ulong local_50 [5];
  long local_28;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_28 = *(long *)(lVar1 + 0x28);
  local_60 = param_5[2];
  local_50[0] = (ulong)*param_4;
  uStack_68 = param_5[1];
  local_70 = *param_5;
  local_50[1] = 0;
  local_50[2] = 6;
  puStack_80 = local_50;
  local_88 = 1;
  local_78 = 6;
  log_internal::vlog(3,"a2dp_vendor_ssc_encoder",&local_70,param_2,param_3,&local_88);
  if (*(long *)(lVar1 + 0x28) == local_28) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== a2dp_vendor_ssc_encoder_init @ 00a93944 size 1148 :: A2DP_VendorUnloadEncoderSsc | a2dp_vendor_ssc_encoder | a2dp_vendor_ssc_encoder_init | a2dp_vendor_ssc_encoder_update | a2dp_vendor_ssc_reset_encoder | packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* a2dp_vendor_ssc_encoder_init(tA2DP_ENCODER_INIT_PEER_PARAMS const*, A2dpCodecConfig*, unsigned
   int (*)(unsigned char*, unsigned int), bool (*)(BT_HDR*, unsigned long, unsigned int), unsigned
   int (*)(tA2DP_CODEC_INFO_CB_CMD, btav_a2dp_codec_index_t), A2dpCurrentEncodeInfo*) */

void a2dp_vendor_ssc_encoder_init
               (tA2DP_ENCODER_INIT_PEER_PARAMS *param_1,A2dpCodecConfig *param_2,
               _func_uint_uchar_ptr_uint *param_3,_func_bool_BT_HDR_ptr_ulong_uint *param_4,
               _func_uint_tA2DP_CODEC_INFO_CB_CMD_btav_a2dp_codec_index_t *param_5,
               A2dpCurrentEncodeInfo *param_6)

{
  A2dpCodecConfig *pAVar1;
  long lVar2;
  A2dpCurrentEncodeInfo AVar3;
  byte bVar4;
  int iVar5;
  ulong uVar6;
  undefined8 uVar7;
  char *pcVar8;
  undefined8 uVar9;
  uint uVar10;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  undefined8 local_118;
  A2dpCodecConfig **ppAStack_110;
  char *local_108;
  undefined8 local_100;
  char *local_f8;
  char *pcStack_f0;
  uchar local_e8 [8];
  ulong uStack_e0;
  undefined4 local_d8;
  A2dpCodecConfig *local_d0;
  char *local_c8;
  char *pcStack_c0;
  undefined8 local_b8;
  ulong local_b0;
  undefined8 uStack_a8;
  ulong local_a0;
  undefined8 local_98;
  ulong local_90;
  undefined8 local_88;
  char *pcStack_80;
  long local_70;
  
  *in_x18 = unaff_x30;
  lVar2 = tpidr_el0;
  local_70 = *(long *)(lVar2 + 0x28);
  local_d0 = (A2dpCodecConfig *)CONCAT44(local_d0._4_4_,0x152);
  local_c8 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
  pcStack_c0 = "a2dp_vendor_ssc_encoder_init";
  local_100 = 0;
  bluetooth::log_internal::vlog(3,"a2dp_vendor_ssc_encoder",&local_d0,&DAT_0013f82c,0,&local_100);
  memset(&DAT_01043e50,0,0x6ce0);
  DAT_01043ea8 = bluetooth::common::time_get_os_boottime_us();
  uRam0000000001043e74 = *(undefined8 *)(param_1 + 8);
  _DAT_01043e6c = *(undefined8 *)param_1;
  DAT_0104ab00 = 0x5dc;
  DAT_01043e64 = 0;
  DAT_01043e68 = 0;
  DAT_01043e60 = 0;
  DAT_0104aaf0 = 0;
  DAT_01043e50 = param_3;
  DAT_01043e58 = param_4;
  DAT_0104ab08 = param_5;
  memset(&DAT_0104ab40,0,0x54678);
  DAT_0109f1b4 = DAT_0101f684 != 0;
  DAT_0104ab28 = 0x14;
  if (!(bool)DAT_0109f1b4) {
    DAT_0104ab28 = 10;
  }
  a2dp_vendor_ssc_set_current_encoder_info(param_6);
  local_100 = CONCAT44(local_100._4_4_,0x375);
  pcStack_c0 = (char *)(ulong)DAT_0104ab14;
  local_f8 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
  pcStack_f0 = "a2dp_vendor_ssc_reset_encoder";
  local_d0 = (A2dpCodecConfig *)(ulong)DAT_01043e7c;
  local_c8 = (char *)0x0;
  local_b8 = 0;
  local_b0 = 0xc6;
  local_118 = 2;
  local_108 = (char *)0xc6;
  ppAStack_110 = &local_d0;
  bluetooth::log_internal::vlog(3,"a2dp_vendor_ssc_encoder",&local_100,"{} {}",5,&local_118);
  if (DAT_01043e7c != DAT_0104ab14) {
    local_d0 = (A2dpCodecConfig *)CONCAT44(local_d0._4_4_,0x134);
    local_c8 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
    pcStack_c0 = "A2DP_VendorUnloadEncoderSsc";
    local_100 = 0;
    bluetooth::log_internal::vlog(3,"a2dp_vendor_ssc_encoder",&local_d0,&DAT_0013f82c,0,&local_100);
    if (DAT_0104ab30 != 0) {
      (*DAT_01043e40)();
      DAT_0104ab30 = 0;
    }
    if (DAT_0104ab38 != 0) {
      (*DAT_01043e40)();
      DAT_0104ab38 = 0;
    }
    DAT_01043e40 = (code *)0x0;
    DAT_01043e38 = 0;
    DAT_01043e48 = 0;
    if (DAT_01043e30 != 0) {
      dlclose();
      DAT_01043e30 = 0;
    }
    A2DP_VendorLoadEncoderSsc();
  }
  local_e8[0] = '\0';
  local_e8[1] = '\0';
  local_e8[2] = '\0';
  local_e8[3] = '\0';
  local_e8[4] = '\0';
  local_e8[5] = '\0';
  local_e8[6] = '\0';
  local_e8[7] = '\0';
  uStack_e0 = 0;
  local_d8 = 0;
  uVar6 = A2dpCodecConfig::copyOutOtaCodecConfig(param_2,local_e8);
  if ((uVar6 & 1) == 0) {
    pAVar1 = param_2 + 0x41;
    if (((byte)param_2[0x40] & 1) != 0) {
      pAVar1 = *(A2dpCodecConfig **)(param_2 + 0x50);
    }
    local_d0 = (A2dpCodecConfig *)"(nullptr)";
    if (pAVar1 != (A2dpCodecConfig *)0x0) {
      local_d0 = pAVar1;
    }
    pcVar8 = "Cannot update the codec encoder for {}: invalid codec config";
    local_118 = 1;
    local_100 = CONCAT44(local_100._4_4_,400);
    pcStack_c0 = (char *)0xc;
    uVar7 = 6;
    uVar9 = 0x3c;
    local_108 = (char *)0xc;
  }
  else {
    local_d0 = (A2dpCodecConfig *)(uStack_e0 >> 8 & 0xff);
    local_100._0_4_ = 0x197;
    ppAStack_110 = &local_d0;
    local_f8 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
    pcStack_f0 = "a2dp_vendor_ssc_encoder_update";
    local_c8 = (char *)0x0;
    pcStack_c0 = (char *)0x6;
    local_118 = 1;
    local_108 = (char *)0x6;
    bluetooth::log_internal::vlog(3,"a2dp_vendor_ssc_encoder",&local_100,&DAT_00150033,8,&local_118)
    ;
    DAT_01043e7c = A2DP_VendorGetTrackSampleRateSsc(local_e8);
    DAT_01043e80 = A2DP_VendorGetTrackBitsPerSampleSsc(local_e8);
    DAT_01043e81 = 2;
    bVar4 = A2DP_VendorGetTrackBitrateLimitationSsc(local_e8);
    DAT_01043e82 = bVar4 & 1;
    iVar5 = A2DP_VendorGetSscType(local_e8);
    AVar3 = (A2dpCurrentEncodeInfo)(iVar5 == 0x400);
    DAT_01043e83 = AVar3;
    param_6[0x2e] = AVar3;
    if ((bool)AVar3) {
      uVar10 = 10;
      DAT_0104ab28 = 10;
    }
    else {
      uVar10 = (uint)DAT_0104ab28;
    }
    local_d0 = (A2dpCodecConfig *)(ulong)DAT_01043e7c;
    pcStack_c0 = (char *)(ulong)DAT_01043e80;
    local_a0 = (ulong)DAT_01043e82;
    local_100 = CONCAT44(local_100._4_4_,0x1b2);
    local_b0 = (ulong)DAT_01043e81;
    pcVar8 = "sample_rate={} bits_per_sample={} channel_count={}, bitrate_limitation={}, is_uhq2={}"
    ;
    uVar7 = 4;
    uVar9 = 0x55;
    local_b8 = 0;
    local_98 = 0;
    local_90 = (ulong)(byte)DAT_01043e83;
    local_88 = 0;
    pcStack_80 = "ddress";
    local_118 = 5;
    uStack_a8 = 0;
    DAT_01043e98 = (DAT_01043e7c * uVar10 * (uint)(DAT_01043e80 >> 3) * (uint)DAT_01043e81) / 1000;
    local_108 = "ddress";
  }
  ppAStack_110 = &local_d0;
  local_c8 = (char *)0x0;
  pcStack_f0 = "a2dp_vendor_ssc_encoder_update";
  local_f8 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
  bluetooth::log_internal::vlog(uVar7,"a2dp_vendor_ssc_encoder",&local_100,pcVar8,uVar9,&local_118);
  if (*(long *)(lVar2 + 0x28) == local_70) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== a2dp_vendor_ssc_set_current_encoder_info @ 00a93dc0 size 396 :: a2dp_vendor_ssc_encoder | a2dp_vendor_ssc_set_current_encoder_info | packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc */

/* a2dp_vendor_ssc_set_current_encoder_info(A2dpCurrentEncodeInfo*) */

void a2dp_vendor_ssc_set_current_encoder_info(A2dpCurrentEncodeInfo *param_1)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  undefined8 local_a0;
  A2dpCurrentEncodeInfo **ppAStack_98;
  undefined8 local_90;
  undefined4 local_88 [2];
  char *local_80;
  char *pcStack_78;
  A2dpCurrentEncodeInfo *local_70;
  code *pcStack_68;
  A2dpCurrentEncodeInfo *local_60;
  code *local_58;
  undefined8 uStack_50;
  long local_38;
  
  *in_x18 = unaff_x30;
  lVar3 = tpidr_el0;
  local_38 = *(long *)(lVar3 + 0x28);
  ppAStack_98 = &local_70;
  local_88[0] = 0x37e;
  local_80 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
  pcStack_78 = "a2dp_vendor_ssc_set_current_encoder_info";
  local_70 = param_1 + 0x14;
  pcStack_68 = 
  _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I29btav_a2dp_codec_sample_rate_tEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
  ;
  local_58 = 
  _ZZNSt3__124__basic_format_arg_valueINS_20basic_format_contextINS_20back_insert_iteratorINS_8__format15__output_bufferIcEEEEcEEE8__handleC1B8nn220000I33btav_a2dp_codec_bits_per_sample_tEERT_ENUlRNS_26basic_format_parse_contextIcEERS7_PKvE_8__invokeESG_SH_SJ_
  ;
  uStack_50 = 0x1ef;
  local_a0 = 2;
  local_90 = 0x1ef;
  local_60 = param_1 + 0x18;
  bluetooth::log_internal::vlog
            (3,"a2dp_vendor_ssc_encoder",local_88,"set_current_encoder_info 0x{:x} 0x{:x}",0x26,
             &local_a0);
  DAT_0104ab04 = param_1[0x38];
  iVar1 = *(int *)(param_1 + 0x14);
  if (iVar1 < 8) {
    if (iVar1 == 2) {
      DAT_0104ab14 = 48000;
      goto LAB_00a93ee0;
    }
    if (iVar1 == 4) {
      DAT_0104ab14 = 0x15888;
      goto LAB_00a93ee0;
    }
  }
  else {
    if (iVar1 == 8) {
      DAT_0104ab14 = 96000;
      goto LAB_00a93ee0;
    }
    if (iVar1 == 0x10) {
      DAT_0104ab14 = 0x2b110;
      goto LAB_00a93ee0;
    }
    if (iVar1 == 0x20) {
      DAT_0104ab14 = 0x2ee00;
      goto LAB_00a93ee0;
    }
  }
  DAT_0104ab14 = 0xac44;
LAB_00a93ee0:
  uVar2 = *(uint *)(param_1 + 0x18);
  if ((uVar2 >> 3 & 1) == 0) {
    if ((uVar2 >> 2 & 1) == 0) {
      DAT_0104ab18 = 0x10;
      if ((uVar2 & 2) != 0) {
        DAT_0104ab18 = 0x18;
      }
    }
    else {
      DAT_0104ab18 = 0x20;
    }
  }
  else {
    DAT_0104ab18 = 0x22;
  }
  if (*(long *)(lVar3 + 0x28) != local_38) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}


/* ==== a2dp_vendor_ssc_encoder_cleanup @ 00a93f4c size 168 :: a2dp_vendor_ssc_encoder | a2dp_vendor_ssc_encoder_cleanup | packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* a2dp_vendor_ssc_encoder_cleanup() */

void a2dp_vendor_ssc_encoder_cleanup(void)

{
  long lVar1;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  undefined8 local_58 [3];
  undefined4 local_40 [2];
  char *local_38;
  char *pcStack_30;
  long local_28;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_28 = *(long *)(lVar1 + 0x28);
  local_40[0] = 0x1b9;
  local_38 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
  pcStack_30 = "a2dp_vendor_ssc_encoder_cleanup";
  local_58[0] = 0;
  bluetooth::log_internal::vlog(3,"a2dp_vendor_ssc_encoder",local_40,&DAT_0013f82c,0,local_58);
  memset(&DAT_01043e50,0,0x6ce0);
  if (*(long *)(lVar1 + 0x28) == local_28) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== a2dp_vendor_ssc_feeding_reset @ 00a93ff4 size 324 :: a2dp_vendor_ssc_encoder | a2dp_vendor_ssc_feeding_reset | packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* a2dp_vendor_ssc_feeding_reset() */

void a2dp_vendor_ssc_feeding_reset(void)

{
  uint uVar1;
  long lVar2;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  undefined8 local_c0;
  ulong *puStack_b8;
  undefined8 local_b0;
  undefined8 local_a8;
  char *local_a0;
  char *pcStack_98;
  ulong local_90;
  char *local_88;
  char *local_80;
  undefined8 uStack_78;
  ulong local_70;
  undefined8 local_68;
  undefined8 uStack_60;
  long local_48;
  
  *in_x18 = unaff_x30;
  lVar2 = tpidr_el0;
  local_48 = *(long *)(lVar2 + 0x28);
  local_90 = CONCAT44(local_90._4_4_,0x1bf);
  local_88 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
  local_80 = "a2dp_vendor_ssc_feeding_reset";
  local_a8 = 0;
  bluetooth::log_internal::vlog(3,"a2dp_vendor_ssc_encoder",&local_90,&DAT_0013f82c,0,&local_a8);
  local_80 = (char *)(ulong)DAT_01043e7c;
  local_70 = (ulong)DAT_01043e81;
  local_a0 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
  pcStack_98 = "a2dp_vendor_ssc_feeding_reset";
  local_c0 = 3;
  local_a8 = CONCAT44(local_a8._4_4_,0x1cc);
  local_68 = 0;
  uStack_60 = 0x18c6;
  uStack_78 = 0;
  uVar1 = DAT_01043e7c * (DAT_01043e80 >> 3) * (uint)DAT_01043e81 * (uint)DAT_0104ab28;
  DAT_01043ea0 = 0;
  uRam0000000001043e90 = 0;
  _DAT_01043e88 = 0;
  local_b0 = 0x18c6;
  local_90 = (ulong)uVar1 / 1000;
  _DAT_01043e98 = (ulong)(uVar1 / 1000);
  local_88 = (char *)0x0;
  puStack_b8 = &local_90;
  bluetooth::log_internal::vlog
            (3,"a2dp_vendor_ssc_encoder",&local_a8,
             "PCM bytes per tick {} sample rate {} channel count {}",0x35,&local_c0);
  if (*(long *)(lVar2 + 0x28) == local_48) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== a2dp_vendor_ssc_feeding_flush @ 00a94138 size 148 :: a2dp_vendor_ssc_encoder | a2dp_vendor_ssc_feeding_flush | packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* a2dp_vendor_ssc_feeding_flush() */

void a2dp_vendor_ssc_feeding_flush(void)

{
  long lVar1;
  undefined8 *in_x18;
  undefined8 unaff_x30;
  undefined8 local_58 [3];
  undefined4 local_40 [2];
  char *local_38;
  char *pcStack_30;
  long local_28;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_28 = *(long *)(lVar1 + 0x28);
  local_40[0] = 0x1d3;
  local_38 = "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
  pcStack_30 = "a2dp_vendor_ssc_feeding_flush";
  local_58[0] = 0;
  bluetooth::log_internal::vlog(3,"a2dp_vendor_ssc_encoder",local_40,&DAT_0013f82c,0,local_58);
  if (*(long *)(lVar1 + 0x28) == local_28) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== a2dp_vendor_ssc_send_frames @ 00a94210 size 9244 :: SSC output_pos :  [ {} ]!!! | SSC output_pos_2nd : [ {} ]!!! | a2dp_ssc_encode_frames | a2dp_ssc_encode_frames, under flow! | a2dp_ssc_encode_frames_on_dual_play | a2dp_ssc_get_num_frame | a2dp_vendor_ssc_encoder | a2dp_vendor_ssc_send_frames | packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* a2dp_vendor_ssc_send_frames(unsigned long, A2dpCurrentEncodeInfo*) */

void a2dp_vendor_ssc_send_frames(ulong param_1,A2dpCurrentEncodeInfo *param_2)

{
  undefined1 (*pauVar1) [12];
  unkbyte9 *pVar2;
  undefined4 *puVar3;
  long lVar4;
  short *psVar5;
  undefined4 uVar6;
  char cVar7;
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  undefined1 auVar21 [16];
  undefined1 auVar22 [16];
  undefined1 auVar23 [16];
  undefined1 auVar24 [12];
  undefined1 auVar25 [12];
  unkbyte9 Var26;
  unkbyte9 Var27;
  undefined1 auVar28 [12];
  unkbyte9 Var29;
  unkbyte9 Var30;
  unkbyte9 Var31;
  unkbyte9 Var32;
  undefined1 *puVar33;
  bool bVar34;
  undefined1 *puVar35;
  byte *pbVar36;
  int iVar37;
  uint uVar38;
  int iVar39;
  int iVar40;
  long lVar41;
  void *__ptr;
  void *__ptr_00;
  int extraout_w1;
  int extraout_w1_00;
  undefined1 *puVar42;
  undefined8 uVar43;
  char *pcVar44;
  undefined8 uVar45;
  uint uVar46;
  undefined *puVar47;
  undefined4 uVar48;
  uint uVar49;
  byte *pbVar50;
  undefined8 *in_x18;
  ulong uVar51;
  long lVar52;
  ulong uVar53;
  ulong uVar54;
  undefined8 unaff_x30;
  short sVar55;
  short sVar56;
  short sVar57;
  short sVar58;
  float fVar59;
  undefined1 auVar61 [12];
  undefined1 auVar63 [12];
  undefined1 auVar64 [16];
  undefined1 auVar65 [16];
  undefined1 auVar66 [16];
  float fVar60;
  undefined1 auVar67 [16];
  undefined1 auVar68 [16];
  undefined1 auVar69 [16];
  undefined1 auVar62 [12];
  undefined1 auVar70 [16];
  undefined1 auVar71 [16];
  undefined1 auVar72 [16];
  undefined1 auVar73 [16];
  undefined1 auVar74 [16];
  byte bVar75;
  float fVar76;
  undefined1 auVar77 [12];
  undefined1 auVar79 [12];
  byte bVar88;
  byte bVar89;
  byte bVar90;
  byte bVar91;
  byte bVar92;
  byte bVar93;
  byte bVar94;
  byte bVar95;
  byte bVar96;
  byte bVar97;
  byte bVar98;
  byte bVar99;
  undefined1 auVar80 [16];
  undefined1 auVar81 [16];
  undefined1 auVar82 [16];
  undefined1 auVar83 [16];
  undefined1 auVar78 [12];
  undefined1 auVar84 [16];
  undefined1 auVar85 [16];
  undefined1 auVar86 [16];
  undefined1 auVar87 [16];
  byte bVar100;
  float fVar101;
  undefined1 auVar102 [16];
  undefined1 auVar103 [16];
  undefined1 auVar104 [16];
  undefined1 auVar105 [16];
  undefined1 auVar106 [16];
  undefined1 auVar107 [16];
  undefined1 auVar108 [16];
  undefined1 auVar109 [16];
  undefined1 auVar110 [12];
  undefined1 auVar111 [16];
  undefined1 auVar112 [16];
  undefined1 auVar113 [16];
  undefined1 auVar114 [16];
  undefined1 auVar115 [16];
  undefined1 auVar117 [16];
  undefined1 auVar118 [16];
  undefined1 auVar119 [12];
  undefined1 auVar121 [16];
  undefined1 auVar123 [16];
  undefined1 auVar124 [16];
  undefined1 auVar125 [16];
  undefined1 auVar120 [12];
  undefined1 auVar127 [16];
  undefined1 auVar128 [16];
  undefined1 auVar129 [16];
  undefined1 auVar130 [16];
  undefined1 auVar131 [16];
  uint uVar132;
  undefined1 auVar133 [12];
  uint uVar139;
  undefined1 auVar134 [16];
  undefined1 auVar135 [16];
  uint uVar140;
  uint uVar141;
  undefined1 auVar136 [16];
  undefined1 auVar137 [16];
  undefined1 auVar138 [16];
  short sVar142;
  uint uVar143;
  short sVar150;
  uint uVar151;
  short sVar152;
  uint uVar153;
  short sVar154;
  undefined1 auVar144 [16];
  undefined1 auVar145 [16];
  uint uVar155;
  undefined1 auVar146 [16];
  undefined1 auVar147 [16];
  undefined1 auVar148 [16];
  undefined1 auVar149 [16];
  uint uVar156;
  undefined1 auVar157 [12];
  uint uVar163;
  undefined1 auVar159 [16];
  uint uVar164;
  uint uVar165;
  undefined1 auVar160 [16];
  undefined1 auVar158 [12];
  undefined1 auVar161 [16];
  undefined1 auVar162 [16];
  undefined1 auVar166 [16];
  undefined1 auVar167 [16];
  undefined1 auVar168 [16];
  undefined1 auVar169 [16];
  undefined1 auVar170 [16];
  undefined1 auVar171 [16];
  int iVar178;
  int iVar179;
  undefined1 auVar172 [16];
  undefined1 auVar173 [16];
  int iVar180;
  undefined1 auVar174 [16];
  undefined1 auVar175 [16];
  undefined1 auVar176 [16];
  undefined1 auVar177 [16];
  uint uVar181;
  uint uVar188;
  uint uVar189;
  undefined1 auVar182 [16];
  undefined1 auVar183 [16];
  uint uVar190;
  undefined1 auVar184 [16];
  undefined1 auVar185 [16];
  undefined1 auVar186 [16];
  undefined1 auVar187 [16];
  undefined1 auVar191 [16];
  undefined1 auVar192 [16];
  undefined1 auVar193 [16];
  undefined1 auVar194 [16];
  undefined1 auVar195 [16];
  undefined1 auVar196 [16];
  int iVar200;
  int iVar201;
  undefined1 auVar197 [16];
  int iVar202;
  undefined1 auVar198 [16];
  undefined1 auVar199 [16];
  undefined1 auVar203 [16];
  undefined1 auVar204 [16];
  undefined1 auVar205 [16];
  int iVar208;
  int iVar209;
  undefined1 auVar206 [16];
  int iVar210;
  undefined1 auVar207 [16];
  undefined1 uVar211;
  undefined1 uVar212;
  undefined1 uVar213;
  undefined1 uVar214;
  undefined1 uVar215;
  undefined1 uVar216;
  undefined1 uVar217;
  undefined1 uVar218;
  undefined1 uVar219;
  undefined1 uVar220;
  undefined1 uVar221;
  undefined1 uVar222;
  undefined1 uVar223;
  undefined1 uVar224;
  undefined1 auStack_a070 [26992];
  short asStack_3700 [6912];
  undefined1 auStack_100 [120];
  long local_88;
  undefined1 auVar116 [16];
  undefined1 auVar122 [16];
  undefined1 auVar126 [16];
  
  *in_x18 = unaff_x30;
  puVar42 = &stack0xffffffffffffff90;
  do {
    puVar33 = puVar42;
    *(undefined8 *)(puVar33 + -0x1000) = 0;
    puVar42 = puVar33 + -0x1000;
  } while (puVar33 + -0x1000 != auStack_a070);
  *(A2dpCurrentEncodeInfo **)(puVar33 + -0x12c8) = param_2;
  lVar52 = tpidr_el0;
  *(long *)(puVar33 + -0x1340) = lVar52;
  local_88 = *(long *)(lVar52 + 0x28);
  puVar3 = (undefined4 *)(puVar33 + 0x5970);
  *(char **)(puVar33 + 0x5978) =
       "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
  uVar51 = (ulong)DAT_01043e7c;
  *puVar3 = 0x310;
  *(char **)(puVar33 + 0x5980) = "a2dp_vendor_ssc_send_frames";
  *(ulong *)(puVar33 + -0x1280) = (ulong)DAT_0104aae0;
  *(ulong *)(puVar33 + -0x1290) = uVar51;
  *(undefined8 *)(puVar33 + -0x1288) = 0;
  *(undefined8 *)(puVar33 + -0x1278) = 0;
  *(undefined8 *)(puVar33 + -0x1270) = 0xc6;
  *(undefined8 *)(puVar33 + 0x8f70) = 2;
  *(undefined1 **)(puVar33 + 0x8f78) = puVar33 + -0x1290;
  *(undefined8 *)(puVar33 + 0x8f80) = 0xc6;
  bluetooth::log_internal::vlog
            (2,"a2dp_vendor_ssc_encoder",puVar33 + 0x5970,"sample rate : {}, nb_byte_read = {}",0x23
             ,auStack_100);
  *(ulong *)(puVar33 + -0x1328) = uVar51;
  if ((DAT_01043ea0 == 0) || (param_1 <= DAT_01043ea0)) {
    *puVar3 = 499;
    *(ulong *)(puVar33 + -0x1280) = DAT_01043ea0;
    *(char **)(puVar33 + 0x5978) =
         "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
    *(char **)(puVar33 + 0x5980) = "a2dp_ssc_get_num_frame";
    *(ulong *)(puVar33 + -0x1290) = param_1;
    *(undefined8 *)(puVar33 + -0x1288) = 0;
    *(undefined8 *)(puVar33 + -0x1278) = 0;
    *(undefined8 *)(puVar33 + -0x1270) = 0xe7;
    *(undefined8 *)(puVar33 + 0x8f70) = 2;
    *(undefined1 **)(puVar33 + 0x8f78) = puVar33 + -0x1290;
    *(undefined8 *)(puVar33 + 0x8f80) = 0xe7;
    bluetooth::log_internal::vlog
              (6,"a2dp_vendor_ssc_encoder",puVar33 + 0x5970,"now_us {} less than {}",0x16,
               auStack_100);
    iVar39 = (uint)DAT_0104ab28 * 1000;
  }
  else {
    iVar39 = (int)param_1 - (int)DAT_01043ea0;
  }
  *puVar3 = 0x1fa;
  *(ulong *)(puVar33 + -0x1290) = (ulong)DAT_01043e7c;
  *(undefined8 *)(puVar33 + -0x1288) = 0;
  *(char **)(puVar33 + 0x5978) =
       "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
  *(char **)(puVar33 + 0x5980) = "a2dp_ssc_get_num_frame";
  *(undefined8 *)(puVar33 + -0x1278) = 0;
  *(undefined8 *)(puVar33 + -0x1270) = 0xc6;
  *(ulong *)(puVar33 + -0x1280) = (ulong)DAT_01043e81;
  *(undefined8 *)(puVar33 + 0x8f70) = 2;
  *(undefined1 **)(puVar33 + 0x8f78) = puVar33 + -0x1290;
  *(undefined8 *)(puVar33 + 0x8f80) = 0xc6;
  DAT_01043ea0 = param_1;
  bluetooth::log_internal::vlog
            (2,"a2dp_vendor_ssc_encoder",puVar33 + 0x5970,"s={}, num ch={}",0xf,auStack_100);
  *(undefined8 *)(puVar33 + -0x1288) = 0;
  *(ulong *)(puVar33 + -0x1280) = (ulong)DAT_01043e98;
  *(char **)(puVar33 + 0x5978) =
       "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
  uVar38 = 0;
  if ((uint)DAT_0104ab28 * 1000 != 0) {
    uVar38 = (DAT_01043e98 * iVar39) / ((uint)DAT_0104ab28 * 1000);
  }
  *(char **)(puVar33 + 0x5980) = "a2dp_ssc_get_num_frame";
  *(undefined8 *)(puVar33 + -0x1278) = 0;
  *(undefined8 *)(puVar33 + -0x1270) = 0xc6;
  *(undefined8 *)(puVar33 + 0x8f70) = 2;
  *(undefined1 **)(puVar33 + 0x8f78) = puVar33 + -0x1290;
  *(undefined4 *)(puVar33 + 0x5970) = 0x203;
  *(undefined8 *)(puVar33 + 0x8f80) = 0xc6;
  DAT_01043e94 = DAT_01043e94 + uVar38;
  *(ulong *)(puVar33 + -0x1290) = (ulong)DAT_01043e94;
  bluetooth::log_internal::vlog
            (2,"a2dp_vendor_ssc_encoder",puVar33 + 0x5970,"counter {} (bytes per tick {})",0x1e,
             auStack_100);
  uVar38 = (uint)DAT_0104ab28 * 1000;
  uVar46 = 0;
  if (uVar38 != 0) {
    uVar46 = (DAT_01043e98 * iVar39) / uVar38;
  }
  if ((uint)DAT_0104ab28 * 500 <= DAT_01043e98 * iVar39 - uVar46 * uVar38) {
    DAT_01043e94 = DAT_01043e94 + 1;
  }
  pbVar50 = *(byte **)(puVar33 + -0x12c8);
  iVar39 = (int)*(undefined8 *)(puVar33 + -0x1328);
  if (iVar39 == 96000) {
    uVar38 = 0x3600;
    if ((DAT_01043e83 == '\x01') && (uVar38 = 0x3600, *pbVar50 < 2)) {
      uVar38 = 0x1b00;
    }
  }
  else {
    uVar38 = 0x1440;
    if (DAT_01043e80 != '\x18') {
      uVar38 = 0xd80;
    }
  }
  if (uVar38 <= DAT_01043e94) {
    uVar51 = 0;
    do {
      DAT_01043e94 = DAT_01043e94 - uVar38;
      *(ulong *)(puVar33 + -0x1290) = (ulong)DAT_01043e94;
      *(undefined4 *)(puVar33 + 0x5970) = 0x223;
      uVar46 = (int)uVar51 + 1;
      uVar51 = (ulong)uVar46;
      *(char **)(puVar33 + 0x5978) =
           "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
      *(char **)(puVar33 + 0x5980) = "a2dp_ssc_get_num_frame";
      *(undefined8 *)(puVar33 + -0x1288) = 0;
      *(undefined8 *)(puVar33 + -0x1280) = 6;
      *(undefined8 *)(puVar33 + 0x8f70) = 1;
      *(undefined1 **)(puVar33 + 0x8f78) = puVar33 + -0x1290;
      *(undefined8 *)(puVar33 + 0x8f80) = 6;
      bluetooth::log_internal::vlog
                (2,"a2dp_vendor_ssc_encoder",puVar33 + 0x5970,"SCHED FRAME TX ({})",0x13,auStack_100
                );
    } while (uVar38 <= DAT_01043e94);
    uVar54 = *(ulong *)(puVar33 + -0x1328);
    iVar39 = (int)uVar54;
    pbVar50 = *(byte **)(puVar33 + -0x12c8);
    if ((uVar46 & 0xff) != 0) {
      if (DAT_010338a0 == 0) {
        if (((DAT_0104ab04 & 1) == 0) && (*(int *)(pbVar50 + 0x3c) == 0)) {
          memset(puVar33 + 0x5970,0,0x3600);
          memset(puVar33 + -0x1290,0,0x6c00);
          if (DAT_0104ab00 < 0x5dc) {
            DAT_0104ab00 = DAT_0104ab00 + 1;
          }
          else {
            DAT_0104ab00 = 0;
            *(undefined4 *)(puVar33 + -0x12a8) = 0x23b;
            *(ulong *)(puVar33 + 0x8f70) = uVar51 & 0xff;
            *(ulong *)(puVar33 + 0x8f80) = uVar54 & 0xffffffff;
            *(ulong *)(puVar33 + 0x8f90) = (ulong)**(byte **)(puVar33 + -0x12c8);
            *(char **)(puVar33 + -0x12a0) =
                 "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
            *(char **)(puVar33 + -0x1298) = "a2dp_ssc_encode_frames";
            *(ulong *)(puVar33 + 0x8fa0) = (ulong)DAT_01043e82;
            bVar75 = (*(byte **)(puVar33 + -0x12c8))[8];
            *(ulong *)(puVar33 + 0x8fc0) = (ulong)DAT_01043e60;
            *(ulong *)(puVar33 + 0x8fb0) = (ulong)bVar75;
            *(undefined8 *)(puVar33 + 0x8f78) = 0;
            *(undefined8 *)(puVar33 + 0x8f88) = 0;
            *(undefined8 *)(puVar33 + 0x8f98) = 0;
            *(undefined8 *)(puVar33 + 0x8fa8) = 0;
            *(undefined8 *)(puVar33 + 0x8fb8) = 0;
            *(undefined8 *)(puVar33 + 0x8fd0) = 0x21098c6;
            *(undefined8 *)(puVar33 + 0x8fc8) = 0;
            *(undefined8 *)(puVar33 + -0x12c0) = 6;
            *(undefined1 **)(puVar33 + -0x12b8) = auStack_100;
            *(undefined8 *)(puVar33 + -0x12b0) = 0x21098c6;
            bluetooth::log_internal::vlog
                      (4,"a2dp_vendor_ssc_encoder",puVar33 + -0x12a8,
                       "nb_frame {} sample {} level {} limit {} monitor {} scmst {}",0x3b,
                       puVar33 + -0x12c0);
          }
          if (iVar39 == 96000) {
            pbVar50 = *(byte **)(puVar33 + -0x12c8);
            pbVar50[0x20] = 0;
            pbVar50[0x21] = 0x77;
            pbVar50[0x22] = 1;
            pbVar50[0x23] = 0;
            uVar38 = (uint)*pbVar50;
            if (2 < uVar38) {
              uVar38 = 3;
            }
            if (DAT_01043e83 == '\x01') {
              DAT_0104aaf8 = *(uint *)(&DAT_00207800 + (ulong)uVar38 * 4);
            }
            else {
              DAT_0104aaf8 = 0x50140;
            }
            *(undefined4 *)(puVar33 + -0x12cc) = 0x1b00;
          }
          else {
            bVar34 = DAT_01043e80 != '\x18';
            uVar48 = 48000;
            if (bVar34) {
              uVar48 = 0xac44;
            }
            pbVar50 = *(byte **)(puVar33 + -0x12c8);
            *(undefined4 *)(pbVar50 + 0x20) = uVar48;
            bVar75 = *pbVar50;
            uVar48 = 0x1440;
            if (bVar34) {
              uVar48 = 0xd80;
            }
            *(undefined4 *)(puVar33 + -0x12cc) = uVar48;
            uVar38 = (uint)bVar75;
            if (2 < uVar38) {
              uVar38 = 3;
            }
            if ((DAT_01043e82 & 1) == 0) {
              puVar47 = &DAT_00207650;
            }
            else {
              puVar47 = &UNK_00209770;
            }
            DAT_0104aaf8 = *(uint *)(puVar47 + (ulong)uVar38 * 4);
          }
          if (DAT_0104aaf8 != DAT_0104aafc) {
            *(ulong *)(puVar33 + 0x8f80) = (ulong)DAT_0104aafc;
            *(undefined4 *)(puVar33 + -0x12a8) = 0x262;
            *(ulong *)(puVar33 + 0x8f70) = (ulong)DAT_0104aaf8;
            *(char **)(puVar33 + -0x12a0) =
                 "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
            *(char **)(puVar33 + -0x1298) = "a2dp_ssc_encode_frames";
            *(undefined8 *)(puVar33 + 0x8f78) = 0;
            *(undefined8 *)(puVar33 + 0x8f90) = 99;
            *(undefined8 *)(puVar33 + 0x8f88) = 0;
            *(undefined8 *)(puVar33 + -0x12c0) = 2;
            *(undefined1 **)(puVar33 + -0x12b8) = auStack_100;
            *(undefined8 *)(puVar33 + -0x12b0) = 99;
            bluetooth::log_internal::vlog
                      (6,"a2dp_vendor_ssc_encoder",puVar33 + -0x12a8,
                       "new bitrate {}, previous bitrate {}",0x23,puVar33 + -0x12c0);
            *(uint *)(*(long *)(puVar33 + -0x12c8) + 0x28) = DAT_0104aaf8;
            (*DAT_0104ab08)(0,8);
          }
          *(undefined4 *)(puVar33 + -0x12a8) = 0x268;
          *(ulong *)(puVar33 + 0x8f70) = (ulong)uVar38;
          *(ulong *)(puVar33 + 0x8f80) = (ulong)DAT_0104aaf8;
          *(ulong *)(puVar33 + 0x8f90) = (ulong)DAT_0104aae0;
          *(char **)(puVar33 + -0x12a0) =
               "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
          *(char **)(puVar33 + -0x1298) = "a2dp_ssc_encode_frames";
          *(undefined8 *)(puVar33 + 0x8f78) = 0;
          *(undefined8 *)(puVar33 + 0x8f88) = 0;
          *(undefined8 *)(puVar33 + 0x8fa0) = 0x1863;
          *(undefined8 *)(puVar33 + 0x8f98) = 0;
          *(undefined8 *)(puVar33 + -0x12c0) = 3;
          *(undefined1 **)(puVar33 + -0x12b8) = auStack_100;
          *(undefined8 *)(puVar33 + -0x12b0) = 0x1863;
          DAT_0104aafc = DAT_0104aaf8;
          bluetooth::log_internal::vlog
                    (2,"a2dp_vendor_ssc_encoder",puVar33 + -0x12a8,
                     "bitrate_idx {} bit_rate {} nb_byte_read {}",0x2a,puVar33 + -0x12c0);
          *(ulong *)(puVar33 + -0x12e0) = (ulong)(*(uint *)(puVar33 + -0x12cc) >> 1);
          *(ulong *)(puVar33 + -0x12d8) = (ulong)*(uint *)(puVar33 + -0x12cc);
          *(undefined8 *)(puVar33 + -0x12e8) = 0xffffff0fffffff0e;
          *(undefined8 *)(puVar33 + -0x12f0) = 0xffffff0dffffff0c;
          *(undefined8 *)(puVar33 + -0x12f8) = 0xffffff0bffffff0a;
          *(undefined8 *)(puVar33 + -0x1300) = 0xffffff09ffffff08;
          *(undefined8 *)(puVar33 + -0x1308) = 0xffffff07ffffff06;
          *(undefined8 *)(puVar33 + -0x1310) = 0xffffff05ffffff04;
          *(undefined8 *)(puVar33 + -0x1318) = 0xffffff03ffffff02;
          *(undefined8 *)(puVar33 + -0x1320) = 0xffffff01ffffff00;
          do {
            lVar52 = osi_malloc(0x1010);
            *(undefined2 *)(lVar52 + 6) = 0;
            *(undefined4 *)(lVar52 + 2) = 0x170000;
            *(long *)(puVar33 + -0x1330) = lVar52;
            uVar38 = DAT_0104aae0;
            if (0 < (int)DAT_0104aaf0) {
              iVar39 = 0x1f5;
              do {
                iVar39 = iVar39 + -1;
                if (iVar39 == 0) {
                  *(undefined4 *)(puVar33 + 0x8f70) = 0x279;
                  *(char **)(puVar33 + 0x8f78) =
                       "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
                  *(char **)(puVar33 + 0x8f80) = "a2dp_ssc_encode_frames";
                  *(undefined8 *)(puVar33 + -0x12a8) = 0;
                  bluetooth::log_internal::vlog
                            (6,"a2dp_vendor_ssc_encoder",auStack_100,
                             "Cannot read PCM at all, break!!",0x1f,puVar33 + -0x12a8);
                  uVar38 = DAT_0104aae0;
                  break;
                }
                iVar37 = (*DAT_01043e50)(&DAT_0104aae4);
                DAT_0104aaf0 = DAT_0104aaf0 - iVar37;
                uVar38 = DAT_0104aae0;
              } while (0 < (int)DAT_0104aaf0);
            }
            if ((int)uVar54 == 96000) {
                    /* WARNING: Read-only address (ram,0x00207670) is written */
                    /* WARNING: Read-only address (ram,0x00207be0) is written */
                    /* WARNING: Read-only address (ram,0x00208900) is written */
                    /* WARNING: Read-only address (ram,0x0020a230) is written */
              if (DAT_01043e83 == '\x01') {
                uVar46 = 0x3600;
                if (**(byte **)(puVar33 + -0x12c8) < 2) {
                  uVar46 = 0x1b00;
                }
              }
              else {
                uVar46 = 0x3600;
              }
            }
            else {
                    /* WARNING: Read-only address (ram,0x00207670) is written */
                    /* WARNING: Read-only address (ram,0x00207be0) is written */
                    /* WARNING: Read-only address (ram,0x00208900) is written */
                    /* WARNING: Read-only address (ram,0x0020a230) is written */
              uVar46 = 0x1440;
              if (DAT_01043e80 != '\x18') {
                uVar46 = 0xd80;
              }
            }
            *(ulong *)(puVar33 + -0x1338) = uVar51;
            DAT_0104aae0 = uVar38;
            if (DAT_0109f1b4 != 1) {
              uVar49 = uVar38;
              if (uVar46 <= uVar38) {
                uVar49 = 0;
              }
              if ((uVar46 - uVar49) + uVar38 < 0x3601) {
                iVar39 = (*DAT_01043e50)(&DAT_01043ee0 + uVar38);
                uVar54 = (ulong)(iVar39 + uVar38);
              }
              else {
                uVar54 = (*DAT_01043e50)(&DAT_01043ee0,uVar46);
                uVar54 = uVar54 & 0xffffffff;
              }
              DAT_0104aae0 = 0;
              uVar38 = (uint)uVar54;
              if (uVar38 != 0) {
                iVar39 = uVar46 - uVar38;
                if (uVar38 <= uVar46 && iVar39 != 0) {
                  iVar37 = (*DAT_01043e50)(&DAT_01043ee0 + uVar54,iVar39);
                  uVar54 = (ulong)(iVar37 + uVar38);
                  if (0 < iVar39 - iVar37) {
                    iVar39 = (*DAT_01043e50)(&DAT_01043ee0 + uVar54);
                    uVar54 = (ulong)(iVar39 + iVar37 + uVar38);
                  }
                  goto LAB_00a96198;
                }
LAB_00a9619c:
                *(ulong *)(puVar33 + -0x1348) = uVar54;
                if ((int)uVar54 < *(int *)(puVar33 + -0x12cc)) {
                  iVar39 = 0;
                }
                else {
                  lVar52 = *(long *)(puVar33 + -0x1330);
                  uVar53 = 0;
                  iVar39 = 0;
                  do {
                    uVar45 = *(undefined8 *)(puVar33 + -0x12d8);
                    *(undefined4 *)(puVar33 + -0x12a8) = 0x2ce;
                    *(char **)(puVar33 + -0x12a0) =
                         "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
                    *(char **)(puVar33 + -0x1298) = "a2dp_ssc_encode_frames";
                    *(ulong *)(puVar33 + 0x8f80) = uVar54;
                    *(ulong *)(puVar33 + 0x8fa0) = uVar53 & 0xffffffe0;
                    *(ulong *)(puVar33 + 0x8fb0) = (ulong)DAT_0104aaf8;
                    *(undefined8 *)(puVar33 + -0x12c0) = 5;
                    *(undefined8 *)(puVar33 + 0x8f78) = 0;
                    *(ulong *)(puVar33 + 0x8f70) = uVar51 & 0xff;
                    *(undefined8 *)(puVar33 + 0x8f88) = 0;
                    *(undefined8 *)(puVar33 + 0x8f98) = 0;
                    *(undefined8 *)(puVar33 + 0x8f90) = uVar45;
                    *(undefined8 *)(puVar33 + 0x8fa8) = 0;
                    *(undefined8 *)(puVar33 + 0x8fc0) = 0x318c66;
                    *(undefined8 *)(puVar33 + 0x8fb8) = 0;
                    *(undefined1 **)(puVar33 + -0x12b8) = auStack_100;
                    *(undefined8 *)(puVar33 + -0x12b0) = 0x318c66;
                    bluetooth::log_internal::vlog
                              (2,"a2dp_vendor_ssc_encoder",puVar33 + -0x12a8,
                               "nb_frame {} left {}, input {} pos {} bit rate {}",0x30,
                               puVar33 + -0x12c0);
                    puVar42 = puVar33 + 0x5970;
                    __memcpy_chk(puVar33 + 0x5970,&DAT_01043ee0 + ((int)uVar53 << 1),uVar45,0x3600);
                    if (DAT_01043e7c != 96000) {
                      if (DAT_01043e80 == '\x18') {
                        pauVar1 = (undefined1 (*) [12])(puVar33 + -0x1300);
                        uVar48 = (undefined4)((ulong)*(undefined8 *)(puVar33 + -0x12f8) >> 0x20);
                        auVar28 = *pauVar1;
                        auVar25 = *pauVar1;
                        auVar24 = *pauVar1;
                        auVar69 = *(undefined1 (*) [16])(puVar33 + -0x12f0);
                        pVar2 = (unkbyte9 *)(puVar33 + -0x1320);
                        uVar45 = *(undefined8 *)(puVar33 + -0x1318);
                        uVar218 = (undefined1)((ulong)uVar45 >> 8);
                        uVar219 = (undefined1)((ulong)uVar45 >> 0x10);
                        uVar220 = (undefined1)((ulong)uVar45 >> 0x18);
                        uVar221 = (undefined1)((ulong)uVar45 >> 0x20);
                        uVar222 = (undefined1)((ulong)uVar45 >> 0x28);
                        uVar223 = (undefined1)((ulong)uVar45 >> 0x30);
                        uVar224 = (undefined1)((ulong)uVar45 >> 0x38);
                        Var32 = *pVar2;
                        Var30 = *pVar2;
                        Var29 = *pVar2;
                        pVar2 = (unkbyte9 *)(puVar33 + -0x1310);
                        uVar45 = *(undefined8 *)(puVar33 + -0x1308);
                        uVar211 = (undefined1)((ulong)uVar45 >> 8);
                        uVar212 = (undefined1)((ulong)uVar45 >> 0x10);
                        uVar213 = (undefined1)((ulong)uVar45 >> 0x18);
                        uVar214 = (undefined1)((ulong)uVar45 >> 0x20);
                        uVar215 = (undefined1)((ulong)uVar45 >> 0x28);
                        uVar216 = (undefined1)((ulong)uVar45 >> 0x30);
                        uVar217 = (undefined1)((ulong)uVar45 >> 0x38);
                        Var31 = *pVar2;
                        Var27 = *pVar2;
                        Var26 = *pVar2;
                        puVar35 = puVar33 + 0x5970;
                        lVar41 = -0x1b00;
                        do {
                          auVar73[0] = *puVar35;
                          auVar86[0] = puVar35[1];
                          auVar108[0] = puVar35[2];
                          auVar73[1] = puVar35[3];
                          auVar86[1] = puVar35[4];
                          auVar108[1] = puVar35[5];
                          auVar73[2] = puVar35[6];
                          auVar86[2] = puVar35[7];
                          auVar108[2] = puVar35[8];
                          auVar73[3] = puVar35[9];
                          auVar86[3] = puVar35[10];
                          auVar108[3] = puVar35[0xb];
                          auVar73[4] = puVar35[0xc];
                          auVar86[4] = puVar35[0xd];
                          auVar108[4] = puVar35[0xe];
                          auVar73[5] = puVar35[0xf];
                          auVar86[5] = puVar35[0x10];
                          auVar108[5] = puVar35[0x11];
                          auVar73[6] = puVar35[0x12];
                          auVar86[6] = puVar35[0x13];
                          auVar108[6] = puVar35[0x14];
                          auVar73[7] = puVar35[0x15];
                          auVar86[7] = puVar35[0x16];
                          auVar108[7] = puVar35[0x17];
                          auVar73[8] = puVar35[0x18];
                          auVar86[8] = puVar35[0x19];
                          auVar108[8] = puVar35[0x1a];
                          auVar73[9] = puVar35[0x1b];
                          auVar86[9] = puVar35[0x1c];
                          auVar108[9] = puVar35[0x1d];
                          auVar73[10] = puVar35[0x1e];
                          auVar86[10] = puVar35[0x1f];
                          auVar108[10] = puVar35[0x20];
                          auVar73[0xb] = puVar35[0x21];
                          auVar86[0xb] = puVar35[0x22];
                          auVar108[0xb] = puVar35[0x23];
                          auVar73[0xc] = puVar35[0x24];
                          auVar86[0xc] = puVar35[0x25];
                          auVar108[0xc] = puVar35[0x26];
                          auVar73[0xd] = puVar35[0x27];
                          auVar86[0xd] = puVar35[0x28];
                          auVar108[0xd] = puVar35[0x29];
                          auVar73[0xe] = puVar35[0x2a];
                          auVar86[0xe] = puVar35[0x2b];
                          auVar108[0xe] = puVar35[0x2c];
                          auVar73[0xf] = puVar35[0x2d];
                          auVar86[0xf] = puVar35[0x2e];
                          auVar108[0xf] = puVar35[0x2f];
                          puVar35 = puVar35 + 0x30;
                          puVar42 = puVar33 + -0x1290;
                          lVar4 = lVar41 + 0x40;
                          auVar115 = a64_TBL(ZEXT816(0),auVar108,auVar69);
                          auVar129 = a64_TBL(ZEXT816(0),auVar86,auVar69);
                          auVar74._12_4_ = uVar48;
                          auVar74._0_12_ = auVar24;
                          auVar138 = a64_TBL(ZEXT816(0),auVar108,auVar74);
                          auVar130._12_4_ = uVar48;
                          auVar130._0_12_ = auVar25;
                          auVar148 = a64_TBL(ZEXT816(0),auVar86,auVar130);
                          auVar161[9] = uVar211;
                          auVar161._0_9_ = Var26;
                          auVar161[10] = uVar212;
                          auVar161[0xb] = uVar213;
                          auVar161[0xc] = uVar214;
                          auVar161[0xd] = uVar215;
                          auVar161[0xe] = uVar216;
                          auVar161[0xf] = uVar217;
                          auVar161 = a64_TBL(ZEXT816(0),auVar108,auVar161);
                          auVar170[9] = uVar211;
                          auVar170._0_9_ = Var27;
                          auVar170[10] = uVar212;
                          auVar170[0xb] = uVar213;
                          auVar170[0xc] = uVar214;
                          auVar170[0xd] = uVar215;
                          auVar170[0xe] = uVar216;
                          auVar170[0xf] = uVar217;
                          auVar170 = a64_TBL(ZEXT816(0),auVar86,auVar170);
                          auVar176[9] = uVar218;
                          auVar176._0_9_ = Var29;
                          auVar176[10] = uVar219;
                          auVar176[0xb] = uVar220;
                          auVar176[0xc] = uVar221;
                          auVar176[0xd] = uVar222;
                          auVar176[0xe] = uVar223;
                          auVar176[0xf] = uVar224;
                          auVar176 = a64_TBL(ZEXT816(0),auVar108,auVar176);
                          auVar186[9] = uVar218;
                          auVar186._0_9_ = Var30;
                          auVar186[10] = uVar219;
                          auVar186[0xb] = uVar220;
                          auVar186[0xc] = uVar221;
                          auVar186[0xd] = uVar222;
                          auVar186[0xe] = uVar223;
                          auVar186[0xf] = uVar224;
                          auVar186 = a64_TBL(ZEXT816(0),auVar86,auVar186);
                          auVar195 = a64_TBL(ZEXT816(0),auVar73,auVar69);
                          auVar199._12_4_ = uVar48;
                          auVar199._0_12_ = auVar28;
                          auVar199 = a64_TBL(ZEXT816(0),auVar73,auVar199);
                          auVar205[9] = uVar211;
                          auVar205._0_9_ = Var31;
                          auVar205[10] = uVar212;
                          auVar205[0xb] = uVar213;
                          auVar205[0xc] = uVar214;
                          auVar205[0xd] = uVar215;
                          auVar205[0xe] = uVar216;
                          auVar205[0xf] = uVar217;
                          auVar130 = a64_TBL(ZEXT816(0),auVar73,auVar205);
                          auVar23[9] = uVar218;
                          auVar23._0_9_ = Var32;
                          auVar23[10] = uVar219;
                          auVar23[0xb] = uVar220;
                          auVar23[0xc] = uVar221;
                          auVar23[0xd] = uVar222;
                          auVar23[0xe] = uVar223;
                          auVar23[0xf] = uVar224;
                          auVar74 = a64_TBL(ZEXT816(0),auVar73,auVar23);
                          auVar110._0_8_ =
                               CONCAT17(auVar129[6] | auVar115[5] | auVar195[7],
                                        CONCAT16(auVar129[5] | auVar115[4] | auVar195[6],
                                                 CONCAT15(auVar129[4] | auVar195[5],
                                                          CONCAT14(auVar195[4],
                                                                   CONCAT13(auVar129[2] |
                                                                            auVar115[1] |
                                                                            auVar195[3],
                                                                            CONCAT12(auVar129[1] |
                                                                                     auVar115[0] |
                                                                                     auVar195[2],
                                                                                     CONCAT11(
                                                  auVar129[0] | auVar195[1],auVar195[0])))))));
                          auVar110[8] = auVar195[8];
                          auVar110[9] = auVar129[8] | auVar195[9];
                          auVar110[10] = auVar129[9] | auVar115[8] | auVar195[10];
                          auVar110[0xb] = auVar129[10] | auVar115[9] | auVar195[0xb];
                          auVar116[0xc] = auVar195[0xc];
                          auVar116._0_12_ = auVar110;
                          auVar116[0xd] = auVar129[0xc] | auVar195[0xd];
                          auVar116[0xe] = auVar129[0xd] | auVar115[0xc] | auVar195[0xe];
                          auVar116[0xf] = auVar129[0xe] | auVar115[0xd] | auVar195[0xf];
                          auVar133._0_8_ =
                               CONCAT17(auVar148[6] | auVar138[5] | auVar199[7],
                                        CONCAT16(auVar148[5] | auVar138[4] | auVar199[6],
                                                 CONCAT15(auVar148[4] | auVar199[5],
                                                          CONCAT14(auVar199[4],
                                                                   CONCAT13(auVar148[2] |
                                                                            auVar138[1] |
                                                                            auVar199[3],
                                                                            CONCAT12(auVar148[1] |
                                                                                     auVar138[0] |
                                                                                     auVar199[2],
                                                                                     CONCAT11(
                                                  auVar148[0] | auVar199[1],auVar199[0])))))));
                          auVar133[8] = auVar199[8];
                          auVar133[9] = auVar148[8] | auVar199[9];
                          auVar133[10] = auVar148[9] | auVar138[8] | auVar199[10];
                          auVar133[0xb] = auVar148[10] | auVar138[9] | auVar199[0xb];
                          auVar118[0xc] = auVar199[0xc];
                          auVar118._0_12_ = auVar133;
                          auVar118[0xd] = auVar148[0xc] | auVar199[0xd];
                          auVar118[0xe] = auVar148[0xd] | auVar138[0xc] | auVar199[0xe];
                          auVar118[0xf] = auVar148[0xe] | auVar138[0xd] | auVar199[0xf];
                          auVar79._0_8_ =
                               CONCAT17(auVar170[6] | auVar161[5] | auVar130[7],
                                        CONCAT16(auVar170[5] | auVar161[4] | auVar130[6],
                                                 CONCAT15(auVar170[4] | auVar130[5],
                                                          CONCAT14(auVar130[4],
                                                                   CONCAT13(auVar170[2] |
                                                                            auVar161[1] |
                                                                            auVar130[3],
                                                                            CONCAT12(auVar170[1] |
                                                                                     auVar161[0] |
                                                                                     auVar130[2],
                                                                                     CONCAT11(
                                                  auVar170[0] | auVar130[1],auVar130[0])))))));
                          auVar79[8] = auVar130[8];
                          auVar79[9] = auVar170[8] | auVar130[9];
                          auVar79[10] = auVar170[9] | auVar161[8] | auVar130[10];
                          auVar79[0xb] = auVar170[10] | auVar161[9] | auVar130[0xb];
                          auVar87[0xc] = auVar130[0xc];
                          auVar87._0_12_ = auVar79;
                          auVar87[0xd] = auVar170[0xc] | auVar130[0xd];
                          auVar87[0xe] = auVar170[0xd] | auVar161[0xc] | auVar130[0xe];
                          auVar87[0xf] = auVar170[0xe] | auVar161[0xd] | auVar130[0xf];
                          auVar63._0_8_ =
                               CONCAT17(auVar186[6] | auVar176[5] | auVar74[7],
                                        CONCAT16(auVar186[5] | auVar176[4] | auVar74[6],
                                                 CONCAT15(auVar186[4] | auVar74[5],
                                                          CONCAT14(auVar74[4],
                                                                   CONCAT13(auVar186[2] |
                                                                            auVar176[1] | auVar74[3]
                                                                            ,CONCAT12(auVar186[1] |
                                                                                      auVar176[0] |
                                                                                      auVar74[2],
                                                                                      CONCAT11(
                                                  auVar186[0] | auVar74[1],auVar74[0])))))));
                          auVar63[8] = auVar74[8];
                          auVar63[9] = auVar186[8] | auVar74[9];
                          auVar63[10] = auVar186[9] | auVar176[8] | auVar74[10];
                          auVar63[0xb] = auVar186[10] | auVar176[9] | auVar74[0xb];
                          auVar195[0xc] = auVar74[0xc];
                          auVar195._0_12_ = auVar63;
                          auVar195[0xd] = auVar186[0xc] | auVar74[0xd];
                          auVar195[0xe] = auVar186[0xd] | auVar176[0xc] | auVar74[0xe];
                          auVar195[0xf] = auVar186[0xe] | auVar176[0xd] | auVar74[0xf];
                          auVar162._0_4_ = (int)(short)-(auVar108[0xc] < '\0');
                          auVar162._4_4_ = (int)(short)-(auVar108[0xd] < '\0');
                          auVar162._8_4_ = (int)(short)-(auVar108[0xe] < '\0');
                          auVar162._12_4_ = (int)(short)-(auVar108[0xf] < '\0');
                          auVar149._0_8_ =
                               CONCAT44((int)(short)-(auVar108[9] < '\0'),
                                        (int)(short)-(auVar108[8] < '\0'));
                          auVar149._8_4_ = (int)(short)-(auVar108[10] < '\0');
                          auVar149._12_4_ = (int)(short)-(auVar108[0xb] < '\0');
                          auVar187._0_4_ = (int)(short)-(auVar108[4] < '\0');
                          auVar187._4_4_ = (int)(short)-(auVar108[5] < '\0');
                          auVar187._8_4_ = (int)(short)-(auVar108[6] < '\0');
                          auVar187._12_4_ = (int)(short)-(auVar108[7] < '\0');
                          auVar131._0_4_ = (int)(short)-(auVar108[0] < '\0');
                          auVar131._4_4_ = (int)(short)-(auVar108[1] < '\0');
                          auVar131._8_4_ = (int)(short)-(auVar108[2] < '\0');
                          auVar131._12_4_ = (int)(short)-(auVar108[3] < '\0');
                          auVar109._0_8_ = auVar110._0_8_ | 0xff000000ff000000;
                          auVar109._8_4_ = auVar110._8_4_ | 0xff000000;
                          auVar109._12_4_ = auVar116._12_4_ | 0xff000000;
                          auVar171._0_8_ = auVar133._0_8_ | 0xff000000ff000000;
                          auVar171._8_4_ = auVar133._8_4_ | 0xff000000;
                          auVar171._12_4_ = auVar118._12_4_ | 0xff000000;
                          auVar177._0_8_ = auVar79._0_8_ | 0xff000000ff000000;
                          auVar177._8_4_ = auVar79._8_4_ | 0xff000000;
                          auVar177._12_4_ = auVar87._12_4_ | 0xff000000;
                          auVar196._0_8_ = auVar63._0_8_ | 0xff000000ff000000;
                          auVar196._8_4_ = auVar63._8_4_ | 0xff000000;
                          auVar196._12_4_ = auVar195._12_4_ | 0xff000000;
                          auVar109 = auVar109 ^ (auVar109 ^ auVar116) & ~auVar162;
                          auVar117._8_8_ = auVar149._8_8_;
                          auVar117._0_8_ = auVar149._0_8_;
                          auVar87 = auVar87 ^ (auVar87 ^ auVar177) & auVar187;
                          auVar195 = auVar195 ^ (auVar195 ^ auVar196) & auVar131;
                          auVar118 = auVar118 ^ (auVar118 ^ auVar171) & auVar117;
                          *(long *)(puVar42 + lVar41 + 0x1b38) = auVar109._8_8_;
                          *(long *)(puVar42 + lVar41 + 0x1b30) = auVar109._0_8_;
                          *(long *)(puVar42 + lVar41 + 0x1b18) = auVar87._8_8_;
                          *(long *)(puVar42 + lVar41 + 0x1b10) = auVar87._0_8_;
                          *(long *)(puVar42 + lVar41 + 0x1b08) = auVar195._8_8_;
                          *(long *)(puVar42 + lVar41 + 0x1b00) = auVar195._0_8_;
                          *(long *)(puVar42 + lVar41 + 0x1b28) = auVar118._8_8_;
                          *(long *)(puVar42 + lVar41 + 0x1b20) = auVar118._0_8_;
                          lVar41 = lVar4;
                        } while (lVar4 != 0);
                      }
                      else {
                        auVar74 = *(undefined1 (*) [16])(puVar33 + -0x1300);
                        auVar69 = *(undefined1 (*) [16])(puVar33 + -0x12f0);
                        auVar199 = *(undefined1 (*) [16])(puVar33 + -0x1320);
                        auVar130 = *(undefined1 (*) [16])(puVar33 + -0x1310);
                        puVar35 = puVar33 + 0x5970;
                        lVar41 = -0x1b00;
                        do {
                          auVar115[0] = *puVar35;
                          bVar75 = puVar35[1];
                          auVar115[1] = puVar35[2];
                          bVar88 = puVar35[3];
                          auVar115[2] = puVar35[4];
                          bVar89 = puVar35[5];
                          auVar115[3] = puVar35[6];
                          bVar90 = puVar35[7];
                          auVar115[4] = puVar35[8];
                          bVar91 = puVar35[9];
                          auVar115[5] = puVar35[10];
                          bVar92 = puVar35[0xb];
                          auVar115[6] = puVar35[0xc];
                          bVar93 = puVar35[0xd];
                          auVar115[7] = puVar35[0xe];
                          pbVar50 = puVar35 + 0xf;
                          auVar115[8] = puVar35[0x10];
                          bVar94 = puVar35[0x11];
                          auVar115[9] = puVar35[0x12];
                          bVar95 = puVar35[0x13];
                          auVar115[10] = puVar35[0x14];
                          bVar96 = puVar35[0x15];
                          auVar115[0xb] = puVar35[0x16];
                          pbVar36 = puVar35 + 0x17;
                          auVar115[0xc] = puVar35[0x18];
                          bVar97 = puVar35[0x19];
                          auVar115[0xd] = puVar35[0x1a];
                          bVar98 = puVar35[0x1b];
                          auVar115[0xe] = puVar35[0x1c];
                          bVar99 = puVar35[0x1d];
                          auVar115[0xf] = puVar35[0x1e];
                          bVar100 = puVar35[0x1f];
                          puVar35 = puVar35 + 0x20;
                          puVar42 = puVar33 + -0x1290;
                          lVar4 = lVar41 + 0x40;
                          auVar161 = a64_TBL(ZEXT816(0),auVar115,auVar69);
                          auVar129 = a64_TBL(ZEXT816(0),auVar115,auVar74);
                          auVar170 = a64_TBL(ZEXT816(0),auVar115,auVar130);
                          auVar115 = a64_TBL(ZEXT816(0),auVar115,auVar199);
                          auVar148._0_8_ =
                               CONCAT17((byte)((short)(char)bVar95 >> 0xf) | auVar129[7],
                                        CONCAT16((char)bVar95 >> 7 | auVar129[6],
                                                 CONCAT15(bVar95 | auVar129[5],
                                                          CONCAT14(auVar129[4],
                                                                   CONCAT13((byte)((short)(char)
                                                  bVar94 >> 0xf) | auVar129[3],
                                                  CONCAT12((char)bVar94 >> 7 | auVar129[2],
                                                           CONCAT11(bVar94 | auVar129[1],auVar129[0]
                                                                   )))))));
                          auVar148[8] = auVar129[8];
                          auVar148[9] = bVar96 | auVar129[9];
                          auVar148[10] = (char)bVar96 >> 7 | auVar129[10];
                          auVar148[0xb] = (byte)((short)(char)bVar96 >> 0xf) | auVar129[0xb];
                          auVar148[0xc] = auVar129[0xc];
                          auVar148[0xd] = *pbVar36 | auVar129[0xd];
                          bVar94 = (char)*pbVar36 >> 7;
                          auVar148[0xe] = bVar94 | auVar129[0xe];
                          auVar148[0xf] = bVar94 | auVar129[0xf];
                          auVar138._0_8_ =
                               CONCAT17((byte)((short)(char)bVar92 >> 0xf) | auVar170[7],
                                        CONCAT16((char)bVar92 >> 7 | auVar170[6],
                                                 CONCAT15(bVar92 | auVar170[5],
                                                          CONCAT14(auVar170[4],
                                                                   CONCAT13((byte)((short)(char)
                                                  bVar91 >> 0xf) | auVar170[3],
                                                  CONCAT12((char)bVar91 >> 7 | auVar170[2],
                                                           CONCAT11(bVar91 | auVar170[1],auVar170[0]
                                                                   )))))));
                          auVar138[8] = auVar170[8];
                          auVar138[9] = bVar93 | auVar170[9];
                          auVar138[10] = (char)bVar93 >> 7 | auVar170[10];
                          auVar138[0xb] = (byte)((short)(char)bVar93 >> 0xf) | auVar170[0xb];
                          auVar138[0xc] = auVar170[0xc];
                          auVar138[0xd] = *pbVar50 | auVar170[0xd];
                          bVar91 = (char)*pbVar50 >> 7;
                          auVar138[0xe] = bVar91 | auVar170[0xe];
                          auVar138[0xf] = bVar91 | auVar170[0xf];
                          auVar129._0_8_ =
                               CONCAT17((byte)((short)(char)bVar88 >> 0xf) | auVar115[7],
                                        CONCAT16((char)bVar88 >> 7 | auVar115[6],
                                                 CONCAT15(bVar88 | auVar115[5],
                                                          CONCAT14(auVar115[4],
                                                                   CONCAT13((byte)((short)(char)
                                                  bVar75 >> 0xf) | auVar115[3],
                                                  CONCAT12((char)bVar75 >> 7 | auVar115[2],
                                                           CONCAT11(bVar75 | auVar115[1],auVar115[0]
                                                                   )))))));
                          auVar129[8] = auVar115[8];
                          auVar129[9] = bVar89 | auVar115[9];
                          auVar129[10] = (char)bVar89 >> 7 | auVar115[10];
                          auVar129[0xb] = (byte)((short)(char)bVar89 >> 0xf) | auVar115[0xb];
                          auVar129[0xc] = auVar115[0xc];
                          auVar129[0xd] = bVar90 | auVar115[0xd];
                          auVar129[0xe] = (char)bVar90 >> 7 | auVar115[0xe];
                          auVar129[0xf] = (byte)((short)(char)bVar90 >> 0xf) | auVar115[0xf];
                          puVar42[lVar41 + 0x1b38] = auVar161[8];
                          puVar42[lVar41 + 0x1b39] = bVar99 | auVar161[9];
                          puVar42[lVar41 + 0x1b3a] = (char)bVar99 >> 7 | auVar161[10];
                          puVar42[lVar41 + 0x1b3b] =
                               (byte)((short)(char)bVar99 >> 0xf) | auVar161[0xb];
                          puVar42[lVar41 + 0x1b3c] = auVar161[0xc];
                          puVar42[lVar41 + 0x1b3d] = bVar100 | auVar161[0xd];
                          puVar42[lVar41 + 0x1b3e] = (char)bVar100 >> 7 | auVar161[0xe];
                          puVar42[lVar41 + 0x1b3f] =
                               (byte)((short)(char)bVar100 >> 0xf) | auVar161[0xf];
                          puVar42[lVar41 + 0x1b30] = auVar161[0];
                          puVar42[lVar41 + 0x1b31] = bVar97 | auVar161[1];
                          puVar42[lVar41 + 0x1b32] = (char)bVar97 >> 7 | auVar161[2];
                          puVar42[lVar41 + 0x1b33] =
                               (byte)((short)(char)bVar97 >> 0xf) | auVar161[3];
                          puVar42[lVar41 + 0x1b34] = auVar161[4];
                          puVar42[lVar41 + 0x1b35] = bVar98 | auVar161[5];
                          puVar42[lVar41 + 0x1b36] = (char)bVar98 >> 7 | auVar161[6];
                          puVar42[lVar41 + 0x1b37] =
                               (byte)((short)(char)bVar98 >> 0xf) | auVar161[7];
                          *(long *)(puVar42 + lVar41 + 0x1b28) = auVar148._8_8_;
                          *(undefined8 *)(puVar42 + lVar41 + 0x1b20) = auVar148._0_8_;
                          *(long *)(puVar42 + lVar41 + 0x1b18) = auVar138._8_8_;
                          *(undefined8 *)(puVar42 + lVar41 + 0x1b10) = auVar138._0_8_;
                          *(long *)(puVar42 + lVar41 + 0x1b08) = auVar129._8_8_;
                          *(undefined8 *)(puVar42 + lVar41 + 0x1b00) = auVar129._0_8_;
                          lVar41 = lVar4;
                        } while (lVar4 != 0);
                      }
                    }
                    iVar37 = (*DAT_01043e48)(DAT_0104ab30,puVar42,0x360,lVar52 + 0x1f + (long)iVar39
                                             ,DAT_0104aaf8);
                    iVar39 = iVar37 + iVar39;
                    uVar38 = (int)uVar54 - *(int *)(puVar33 + -0x12cc);
                    uVar54 = (ulong)uVar38;
                    uVar53 = uVar53 + *(long *)(puVar33 + -0x12e0);
                  } while (*(int *)(puVar33 + -0x12cc) <= (int)uVar38);
                }
                iVar37 = (int)uVar54;
                if (((0 < iVar37) && (DAT_01043e80 == '\x18')) &&
                   (iVar40 = iVar37 + (int)(uVar54 / 6) * -6, iVar40 != 0)) {
                  uVar38 = 6 - iVar40;
                  iVar40 = (*DAT_01043e50)(&DAT_0104aae4,(ulong)uVar38);
                  *(undefined4 *)(puVar33 + -0x12a8) = 0x2eb;
                  DAT_0104aaf0 = uVar38 - iVar40;
                  *(char **)(puVar33 + -0x12a0) =
                       "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
                  *(char **)(puVar33 + -0x1298) = "a2dp_ssc_encode_frames";
                  *(ulong *)(puVar33 + 0x8f90) = (ulong)DAT_0104aaf0;
                  *(ulong *)(puVar33 + 0x8f70) = (ulong)(uint)(iVar40 + iVar37);
                  *(undefined8 *)(puVar33 + -0x12c0) = 3;
                  *(undefined8 *)(puVar33 + 0x8f78) = 0;
                  *(undefined8 *)(puVar33 + 0x8f88) = 0;
                  *(ulong *)(puVar33 + 0x8f80) = (ulong)uVar38;
                  *(undefined8 *)(puVar33 + 0x8fa0) = 0xc63;
                  *(undefined8 *)(puVar33 + 0x8f98) = 0;
                  *(undefined1 **)(puVar33 + -0x12b8) = auStack_100;
                  *(undefined8 *)(puVar33 + -0x12b0) = 0xc63;
                  bluetooth::log_internal::vlog
                            (6,"a2dp_vendor_ssc_encoder",puVar33 + -0x12a8,
                             "Couldn\'t read PCM, discarded {}, read_more before {}, read_more after {}"
                             ,0x48,puVar33 + -0x12c0);
                }
                uVar54 = *(ulong *)(puVar33 + -0x1328);
                uVar45 = *(undefined8 *)(puVar33 + -0x1338);
                if (0 < iVar39) {
                  lVar52 = *(long *)(puVar33 + -0x1330);
                  uVar43 = *(undefined8 *)(puVar33 + -0x1348);
                  *(short *)(lVar52 + 2) = (short)iVar39;
                  DAT_01043e64 = DAT_01043e64 + 1;
                  *(int *)(lVar52 + 8) = DAT_01043e64;
                  uVar51 = (*DAT_01043e58)(lVar52,1,uVar43);
                  if ((uVar51 & 1) != 0) {
                    uVar51 = (ulong)((int)uVar45 - 1);
                    sVar55 = *(short *)(*(long *)(puVar33 + -0x12c8) + 10);
                    if (sVar55 != 0) {
                      *(short *)(*(long *)(puVar33 + -0x12c8) + 10) = sVar55 + -1;
                    }
                    goto LAB_00a95b68;
                  }
                  break;
                }
                *(char **)(puVar33 + 0x8f78) =
                     "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
                *(undefined4 *)(puVar33 + 0x8f70) = 0x2fd;
                *(char **)(puVar33 + 0x8f80) = "a2dp_ssc_encode_frames";
                *(undefined8 *)(puVar33 + -0x12a8) = 0;
                bluetooth::log_internal::vlog
                          (6,"a2dp_vendor_ssc_encoder",auStack_100,"output_pos 0",0xc,
                           puVar33 + -0x12a8);
              }
LAB_00a965dc:
              __ptr_00 = *(void **)(puVar33 + -0x1330);
              goto LAB_00a965e0;
            }
            uVar38 = (*DAT_01043e50)(&DAT_01043ee0,uVar46);
            if (uVar38 < uVar46) {
              *(undefined4 *)(puVar33 + 0x8f70) = 0x293;
              *(char **)(puVar33 + 0x8f78) =
                   "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
              *(char **)(puVar33 + 0x8f80) = "a2dp_ssc_encode_frames";
              *(undefined8 *)(puVar33 + -0x12a8) = 0;
              bluetooth::log_internal::vlog
                        (5,"a2dp_vendor_ssc_encoder",auStack_100,
                         "a2dp_ssc_encode_frames, under flow!",0x23,puVar33 + -0x12a8);
              uVar54 = *(ulong *)(puVar33 + -0x1328);
              if ((DAT_01043e80 == '\x18') &&
                 (iVar39 = uVar38 + (int)((ulong)uVar38 * 0x2aaaaaab >> 0x20) * -6, iVar39 != 0)) {
                uVar46 = 6 - iVar39;
                iVar39 = (*DAT_01043e50)(&DAT_0104aae4,(ulong)uVar46);
                *(undefined4 *)(puVar33 + -0x12a8) = 0x29a;
                DAT_0104aaf0 = uVar46 - iVar39;
                *(char **)(puVar33 + -0x12a0) =
                     "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
                *(char **)(puVar33 + -0x1298) = "a2dp_ssc_encode_frames";
                *(ulong *)(puVar33 + 0x8f90) = (ulong)DAT_0104aaf0;
                *(ulong *)(puVar33 + 0x8f70) = (ulong)(iVar39 + uVar38);
                *(ulong *)(puVar33 + 0x8f80) = (ulong)uVar46;
                *(undefined8 *)(puVar33 + -0x12c0) = 3;
                *(undefined8 *)(puVar33 + 0x8f78) = 0;
                *(undefined8 *)(puVar33 + 0x8f88) = 0;
                *(undefined8 *)(puVar33 + 0x8fa0) = 0xc66;
                *(undefined8 *)(puVar33 + 0x8f98) = 0;
                *(undefined1 **)(puVar33 + -0x12b8) = auStack_100;
                *(undefined8 *)(puVar33 + -0x12b0) = 0xc66;
                bluetooth::log_internal::vlog
                          (6,"a2dp_vendor_ssc_encoder",puVar33 + -0x12a8,
                           "(Audio Share): Couldn\'t read PCM, discarded {}, read_more before {}, read_more after {}"
                           ,0x57,puVar33 + -0x12c0);
              }
            }
            else {
              std::recursive_mutex::lock((recursive_mutex *)&DAT_01043e08);
              uVar54 = *(ulong *)(puVar33 + -0x1328);
              if ((int)(DAT_0104ab40 + 1) % 0x19 == DAT_0104ab44) {
                *(undefined4 *)(puVar33 + 0x8f70) = 0xc3;
                *(char **)(puVar33 + 0x8f78) =
                     "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
                pcVar44 = "queueEnqueue: queue is full";
                uVar45 = 0x1b;
                *(char **)(puVar33 + 0x8f80) = "queueEnqueue";
                *(undefined8 *)(puVar33 + -0x12a8) = 0;
LAB_00a95ff8:
                bluetooth::log_internal::vlog
                          (6,"a2dp_vendor_ssc_encoder",auStack_100,pcVar44,uVar45,puVar33 + -0x12a8)
                ;
              }
              else {
                if (0x3600 < (int)uVar38) {
                  *(undefined8 *)(puVar33 + -0x12a8) = 0;
                  *(undefined4 *)(puVar33 + 0x8f70) = 0xcb;
                  *(char **)(puVar33 + 0x8f78) =
                       "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
                  *(char **)(puVar33 + 0x8f80) = "queueEnqueue";
                  pcVar44 = "queueEnqueue: wrong size";
                  uVar45 = 0x18;
                  goto LAB_00a95ff8;
                }
                *(ulong *)(puVar33 + 0x8f80) = (ulong)DAT_0104ab40;
                *(undefined4 *)(puVar33 + -0x12a8) = 199;
                *(undefined8 *)(puVar33 + -0x12c0) = 2;
                *(char **)(puVar33 + -0x12a0) =
                     "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
                *(char **)(puVar33 + -0x1298) = "queueEnqueue";
                *(ulong *)(puVar33 + 0x8f70) = (ulong)uVar38;
                *(undefined8 *)(puVar33 + 0x8f78) = 0;
                *(undefined8 *)(puVar33 + 0x8f90) = 99;
                *(undefined8 *)(puVar33 + 0x8f88) = 0;
                *(undefined1 **)(puVar33 + -0x12b8) = auStack_100;
                *(undefined8 *)(puVar33 + -0x12b0) = 99;
                bluetooth::log_internal::vlog
                          (3,"a2dp_vendor_ssc_encoder",puVar33 + -0x12a8,
                           "queueEnqueue: size = {}, queue front = {}",0x29,puVar33 + -0x12c0);
                uVar51 = (long)(int)DAT_0104ab40 * 0x3600 | 0x10;
                lVar52 = 0;
                if (uVar51 < 0x54679) {
                  lVar52 = 0x54678 - uVar51;
                }
                __memcpy_chk((long)(int)DAT_0104ab40 * 0x3600 + 0x104ab50,&DAT_01043ee0,
                             (long)(int)uVar38,lVar52);
                *(uint *)(&DAT_0109f150 + (long)(int)DAT_0104ab40 * 4) = uVar38;
                if (DAT_0104ab40 == 0xf) {
                  DAT_0104ab48 = 1;
                  DAT_0104ab40 = DAT_0104ab40 + 1;
                }
                else {
                  bVar34 = DAT_0104ab40 == 0x18;
                  DAT_0104ab40 = DAT_0104ab40 + 1;
                  if (bVar34) {
                    DAT_0104ab40 = 0;
                  }
                }
              }
              std::recursive_mutex::unlock((recursive_mutex *)&DAT_01043e08);
            }
            if (DAT_0104ab48 != 0) {
              std::recursive_mutex::lock((recursive_mutex *)&DAT_01043e08);
              if (DAT_0104ab40 == DAT_0104ab44) {
                *(undefined8 *)(puVar33 + -0x12a8) = 0;
                DAT_0104ab48 = 0;
                *(undefined4 *)(puVar33 + 0x8f70) = 0xdc;
                *(char **)(puVar33 + 0x8f78) =
                     "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
                *(char **)(puVar33 + 0x8f80) = "queueDequeue";
                pcVar44 = "queueDequeue: queue is empty";
                uVar45 = 0x1c;
LAB_00a96180:
                bluetooth::log_internal::vlog
                          (6,"a2dp_vendor_ssc_encoder",auStack_100,pcVar44,uVar45,puVar33 + -0x12a8)
                ;
                uVar54 = 0;
              }
              else {
                *(undefined4 *)(puVar33 + -0x12a8) = 0xe0;
                *(ulong *)(puVar33 + 0x8f80) = (ulong)DAT_0104ab44;
                uVar38 = *(uint *)(&DAT_0109f150 + (long)(int)DAT_0104ab44 * 4);
                uVar54 = (ulong)uVar38;
                *(undefined8 *)(puVar33 + -0x12c0) = 2;
                *(char **)(puVar33 + -0x12a0) =
                     "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
                *(char **)(puVar33 + -0x1298) = "queueDequeue";
                *(undefined8 *)(puVar33 + 0x8f78) = 0;
                *(ulong *)(puVar33 + 0x8f70) = uVar54;
                *(undefined8 *)(puVar33 + 0x8f90) = 99;
                *(undefined8 *)(puVar33 + 0x8f88) = 0;
                *(undefined1 **)(puVar33 + -0x12b8) = auStack_100;
                *(undefined8 *)(puVar33 + -0x12b0) = 99;
                bluetooth::log_internal::vlog
                          (3,"a2dp_vendor_ssc_encoder",puVar33 + -0x12a8,
                           "queueDequeue: valid_buffer_size = {}, queue rear = {}",0x35,
                           puVar33 + -0x12c0);
                uVar46 = DAT_0104ab44;
                if (0x3600 < (int)uVar38) {
                  pcVar44 = "queueDequeue: wrong size";
                  uVar45 = 0x18;
                  *(undefined4 *)(puVar33 + 0x8f70) = 0xe4;
                  *(char **)(puVar33 + 0x8f78) =
                       "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
                  *(char **)(puVar33 + 0x8f80) = "queueDequeue";
                  *(undefined8 *)(puVar33 + -0x12a8) = 0;
                  goto LAB_00a96180;
                }
                __memcpy_chk(&DAT_01043ee0,(long)(int)DAT_0104ab44 * 0x3600 + 0x104ab50,
                             (long)(int)uVar38,0x6c50);
                DAT_0104ab44 = 0;
                if (uVar46 != 0x18) {
                  DAT_0104ab44 = uVar46 + 1;
                }
              }
              uVar51 = *(ulong *)(puVar33 + -0x1338);
              std::recursive_mutex::unlock((recursive_mutex *)&DAT_01043e08);
LAB_00a96198:
              if ((int)uVar54 != 0) goto LAB_00a9619c;
              goto LAB_00a965dc;
            }
            free(*(void **)(puVar33 + -0x1330));
            uVar51 = (ulong)((int)*(undefined8 *)(puVar33 + -0x1338) - 1U);
            if (((int)*(undefined8 *)(puVar33 + -0x1338) - 1U & 0xff) == 0) break;
LAB_00a95b68:
          } while ((uVar51 & 0xff) != 0);
        }
        else {
          memset(puVar33 + 0x5970,0,0x3600);
          memset(puVar33 + -0x1290,0,0x6c00);
          if (DAT_0104ab00 < 0x5dc) {
            DAT_0104ab00 = DAT_0104ab00 + 1;
            if (iVar39 != 96000) goto LAB_00a94920;
LAB_00a94988:
            pbVar50 = *(byte **)(puVar33 + -0x12c8);
            pbVar50[0x20] = 0;
            pbVar50[0x21] = 0x77;
            pbVar50[0x22] = 1;
            pbVar50[0x23] = 0;
            uVar38 = (uint)*pbVar50;
            if (2 < uVar38) {
              uVar38 = 3;
            }
            if (DAT_01043e83 == '\x01') {
              DAT_0104aaf8 = *(uint *)(&DAT_00207800 + (ulong)uVar38 * 4);
            }
            else {
              DAT_0104aaf8 = 0x50140;
            }
            *(undefined4 *)(puVar33 + -0x12cc) = 0x1b00;
          }
          else {
            DAT_0104ab00 = 0;
            *(undefined4 *)(puVar33 + -0x12a8) = 0x408;
            *(ulong *)(puVar33 + 0x8f70) = uVar51 & 0xff;
            *(ulong *)(puVar33 + 0x8f80) = uVar54 & 0xffffffff;
            *(ulong *)(puVar33 + 0x8f90) = (ulong)**(byte **)(puVar33 + -0x12c8);
            *(char **)(puVar33 + -0x12a0) =
                 "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
            *(char **)(puVar33 + -0x1298) = "a2dp_ssc_encode_frames_on_dual_play";
            *(ulong *)(puVar33 + 0x8fa0) = (ulong)DAT_01043e82;
            bVar75 = (*(byte **)(puVar33 + -0x12c8))[8];
            *(ulong *)(puVar33 + 0x8fc0) = (ulong)DAT_01043e60;
            *(ulong *)(puVar33 + 0x8fb0) = (ulong)bVar75;
            *(undefined8 *)(puVar33 + 0x8f78) = 0;
            *(undefined8 *)(puVar33 + 0x8f88) = 0;
            *(undefined8 *)(puVar33 + 0x8f98) = 0;
            *(undefined8 *)(puVar33 + 0x8fa8) = 0;
            *(undefined8 *)(puVar33 + 0x8fb8) = 0;
            *(undefined8 *)(puVar33 + 0x8fd0) = 0x21098c6;
            *(undefined8 *)(puVar33 + 0x8fc8) = 0;
            *(undefined8 *)(puVar33 + -0x12c0) = 6;
            *(undefined1 **)(puVar33 + -0x12b8) = auStack_100;
            *(undefined8 *)(puVar33 + -0x12b0) = 0x21098c6;
            bluetooth::log_internal::vlog
                      (4,"a2dp_vendor_ssc_encoder",puVar33 + -0x12a8,
                       "nb_frame {} sample {} level {} limit {} monitor {} scmst {}",0x3b,
                       puVar33 + -0x12c0);
            if (iVar39 == 96000) goto LAB_00a94988;
LAB_00a94920:
            pbVar50 = *(byte **)(puVar33 + -0x12c8);
            bVar34 = DAT_01043e80 != '\x18';
            uVar48 = 48000;
            if (bVar34) {
              uVar48 = 0xac44;
            }
            *(undefined4 *)(pbVar50 + 0x20) = uVar48;
            bVar75 = *pbVar50;
            uVar48 = 0x1440;
            if (bVar34) {
              uVar48 = 0xd80;
            }
            *(undefined4 *)(puVar33 + -0x12cc) = uVar48;
            uVar38 = (uint)bVar75;
            if (2 < uVar38) {
              uVar38 = 3;
            }
            if ((DAT_01043e82 & 1) == 0) {
              puVar47 = &DAT_00207650;
            }
            else {
              puVar47 = &UNK_00209770;
            }
            DAT_0104aaf8 = *(uint *)(puVar47 + (ulong)uVar38 * 4);
          }
          *(ulong *)(puVar33 + -0x1350) = uVar51;
          if (DAT_0104aaf8 != DAT_0104aafc) {
            *(uint *)(pbVar50 + 0x28) = DAT_0104aaf8;
            (*DAT_0104ab08)(0,8);
          }
          *(undefined4 *)(puVar33 + -0x12a8) = 0x434;
          *(ulong *)(puVar33 + 0x8f70) = (ulong)uVar38;
          *(ulong *)(puVar33 + 0x8f80) = (ulong)DAT_0104aaf8;
          *(ulong *)(puVar33 + 0x8f90) = (ulong)DAT_0104aae0;
          *(char **)(puVar33 + -0x12a0) =
               "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
          *(char **)(puVar33 + -0x1298) = "a2dp_ssc_encode_frames_on_dual_play";
          *(undefined8 *)(puVar33 + 0x8f78) = 0;
          *(undefined8 *)(puVar33 + 0x8f88) = 0;
          *(undefined8 *)(puVar33 + 0x8fa0) = 0x1863;
          *(undefined8 *)(puVar33 + 0x8f98) = 0;
          *(undefined8 *)(puVar33 + -0x12c0) = 3;
          *(undefined1 **)(puVar33 + -0x12b8) = auStack_100;
          *(undefined8 *)(puVar33 + -0x12b0) = 0x1863;
          DAT_0104aafc = DAT_0104aaf8;
          bluetooth::log_internal::vlog
                    (2,"a2dp_vendor_ssc_encoder",puVar33 + -0x12a8,
                     "bitrate_idx {} bit_rate {} nb_byte_read {}",0x2a,puVar33 + -0x12c0);
          uVar51 = (ulong)*(uint *)(puVar33 + -0x12cc);
          *(undefined8 *)(puVar33 + -0x12e0) = 0;
          *(ulong *)(puVar33 + -0x12d8) = (ulong)(*(uint *)(puVar33 + -0x12cc) >> 1);
          *(undefined8 *)(puVar33 + -0x12f0) = 0;
          *(undefined8 *)(puVar33 + -0x1308) = 0xffffff0fffffff0e;
          *(undefined8 *)(puVar33 + -0x1310) = 0xffffff0dffffff0c;
          *(undefined8 *)(puVar33 + -0x1318) = 0xffffff0bffffff0a;
          *(undefined8 *)(puVar33 + -0x1320) = 0xffffff09ffffff08;
          lVar52 = *(long *)(puVar33 + -0x12c8);
          *(undefined8 *)(puVar33 + -0x1358) = 0x700000006;
          *(undefined8 *)(puVar33 + -0x1360) = 0x500000004;
          *(long *)(puVar33 + -0x1368) = DAT_00207be0._8_8_;
          *(long *)(puVar33 + -0x1370) = (long)DAT_00207be0;
          do {
            if (*(char *)(lVar52 + 0x50) == '\x01') {
              lVar41 = osi_malloc(0x1010);
              lVar52 = *(long *)(puVar33 + -0x12c8);
            }
            else {
              lVar41 = 0;
            }
            cVar7 = *(char *)(lVar52 + 0x60);
            *(long *)(puVar33 + -0x1338) = lVar41;
            if (cVar7 == '\x01') {
              lVar52 = osi_malloc(0x1010);
              lVar41 = *(long *)(puVar33 + -0x1338);
            }
            else {
              lVar52 = 0;
            }
            if (lVar41 != 0) {
              *(undefined2 *)(lVar41 + 4) = 0x17;
            }
            if (lVar52 != 0) {
              *(undefined2 *)(lVar52 + 4) = 0x17;
            }
            if (lVar41 != 0) {
              *(undefined2 *)(lVar41 + 2) = 0;
              *(undefined2 *)(lVar41 + 6) = 0;
              *(ulong *)(puVar33 + -0x12e0) = lVar41 + (ulong)*(ushort *)(lVar41 + 4) + 8;
            }
            if (lVar52 != 0) {
              *(undefined2 *)(lVar52 + 2) = 0;
              *(undefined2 *)(lVar52 + 6) = 0;
              *(ulong *)(puVar33 + -0x12f0) = lVar52 + (ulong)*(ushort *)(lVar52 + 4) + 8;
            }
            *(long *)(puVar33 + -0x1330) = lVar52;
            if (0 < (int)DAT_0104aaf0) {
              iVar39 = 0x1f5;
              do {
                iVar39 = iVar39 + -1;
                if (iVar39 == 0) {
                  *(undefined4 *)(puVar33 + 0x8f70) = 0x45c;
                  *(char **)(puVar33 + 0x8f78) =
                       "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
                  *(char **)(puVar33 + 0x8f80) = "a2dp_ssc_encode_frames_on_dual_play";
                  *(undefined8 *)(puVar33 + -0x12a8) = 0;
                  bluetooth::log_internal::vlog
                            (6,"a2dp_vendor_ssc_encoder",auStack_100,
                             "Cannot read PCM at all, break!!",0x1f,puVar33 + -0x12a8);
                  break;
                }
                iVar37 = (*DAT_01043e50)(&DAT_0104aae4);
                DAT_0104aaf0 = DAT_0104aaf0 - iVar37;
              } while (0 < (int)DAT_0104aaf0);
            }
            uVar38 = DAT_0104aae0;
            if ((int)*(undefined8 *)(puVar33 + -0x1328) == 96000) {
              if (DAT_01043e83 == '\x01') {
                uVar46 = 0x3600;
                if (**(byte **)(puVar33 + -0x12c8) < 2) {
                  uVar46 = 0x1b00;
                }
              }
              else {
                uVar46 = 0x3600;
              }
            }
            else {
              uVar46 = 0x1440;
              if (DAT_01043e80 != '\x18') {
                uVar46 = 0xd80;
              }
            }
            uVar49 = DAT_0104aae0;
            if (uVar46 <= DAT_0104aae0) {
              uVar49 = 0;
            }
            if ((uVar46 - uVar49) + DAT_0104aae0 < 0x3601) {
              iVar39 = (*DAT_01043e50)(&DAT_01043ee0 + DAT_0104aae0);
              uVar38 = iVar39 + uVar38;
            }
            else {
              uVar38 = (*DAT_01043e50)(&DAT_01043ee0,uVar46);
            }
            __ptr_00 = *(void **)(puVar33 + -0x1330);
            DAT_0104aae0 = 0;
            if ((uVar38 != 0) && (iVar39 = uVar46 - uVar38, uVar38 <= uVar46 && iVar39 != 0)) {
              iVar37 = (*DAT_01043e50)(&DAT_01043ee0 + uVar38,iVar39);
              uVar38 = iVar37 + uVar38;
              if (0 < iVar39 - iVar37) {
                iVar39 = (*DAT_01043e50)(&DAT_01043ee0 + uVar38);
                uVar38 = iVar39 + uVar38;
              }
            }
            if (__ptr_00 != (void *)0x0) {
              __memcpy_chk(&DAT_010474e0,&DAT_01043ee0,uVar38,0x3650);
            }
            if (uVar38 == 0) {
              __ptr = *(void **)(puVar33 + -0x1338);
joined_r0x00a95964:
              if (__ptr != (void *)0x0) {
                free(__ptr);
              }
              if (__ptr_00 != (void *)0x0) {
LAB_00a965e0:
                free(__ptr_00);
              }
              break;
            }
            *(uint *)(puVar33 + -0x1348) = uVar38;
            uVar46 = uVar38;
            if (*(long *)(puVar33 + -0x1338) == 0) {
              uVar49 = 0;
              lVar52 = 0;
            }
            else {
              if ((int)uVar38 < *(int *)(puVar33 + -0x12cc)) {
                uVar132 = 0;
              }
              else {
                uVar54 = 0;
                uVar132 = 0;
                *(ulong *)(puVar33 + -0x1300) = *(ulong *)(puVar33 + -0x1350) & 0xff;
                do {
                  *(undefined4 *)(puVar33 + -0x12a8) = 0x49b;
                  *(char **)(puVar33 + -0x12a0) =
                       "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
                  *(char **)(puVar33 + -0x1298) = "a2dp_ssc_encode_frames_on_dual_play";
                  *(undefined8 *)(puVar33 + 0x8f70) = *(undefined8 *)(puVar33 + -0x1300);
                  *(ulong *)(puVar33 + 0x8f80) = (ulong)uVar46;
                  *(ulong *)(puVar33 + 0x8fa0) = uVar54 & 0xffffffe0;
                  *(undefined8 *)(puVar33 + 0x8f78) = 0;
                  *(ulong *)(puVar33 + 0x8fb0) = (ulong)DAT_0104aaf8;
                  *(undefined8 *)(puVar33 + -0x12c0) = 5;
                  *(undefined8 *)(puVar33 + 0x8f88) = 0;
                  *(undefined8 *)(puVar33 + 0x8f98) = 0;
                  *(ulong *)(puVar33 + 0x8f90) = uVar51;
                  *(undefined8 *)(puVar33 + 0x8fa8) = 0;
                  *(undefined8 *)(puVar33 + 0x8fc0) = 0x318c66;
                  *(undefined8 *)(puVar33 + 0x8fb8) = 0;
                  *(undefined1 **)(puVar33 + -0x12b8) = auStack_100;
                  *(undefined8 *)(puVar33 + -0x12b0) = 0x318c66;
                  bluetooth::log_internal::vlog
                            (2,"a2dp_vendor_ssc_encoder",puVar33 + -0x12a8,
                             "nb_frame {} left {}, input {} pos {} bit rate {}",0x30,
                             puVar33 + -0x12c0);
                  __memcpy_chk(puVar33 + 0x5970,&DAT_01043ee0 + ((int)uVar54 << 1),uVar51,0x3600);
                  lVar52 = *(long *)(puVar33 + -0x12c8);
                  fVar59 = *(float *)(lVar52 + 0x48);
                  fVar76 = *(float *)(lVar52 + 0x4c);
                  if ((fVar59 != 1.0) || (fVar101 = 1.0, fVar76 != 1.0)) {
                    if (DAT_01043e80 == '\x18') {
                      volumeStereo24(puVar33 + 0x5970,extraout_w1,fVar59,fVar76);
                      lVar52 = *(long *)(puVar33 + -0x12c8);
                      fVar101 = *(float *)(lVar52 + 0x4c);
                    }
                    else {
                      fVar60 = (float)((int)(fVar76 * 4096.0) - (int)(fVar59 * 4096.0)) / 864.0;
                      fVar59 = (float)(int)(fVar59 * 4096.0);
                      lVar41 = 0;
                      auVar69 = _DAT_00207670;
                      auVar74 = _DAT_00207be0;
                      do {
                        auVar130 = NEON_ucvtf(auVar69,4);
                        auVar199 = NEON_ucvtf(auVar74,4);
                        psVar5 = (short *)(puVar33 + lVar41 + 0x5970);
                        auVar121._0_4_ = auVar74._0_4_ + 8;
                        auVar121._4_4_ = auVar74._4_4_ + 8;
                        auVar121._8_4_ = auVar74._8_4_ + 8;
                        auVar121._12_4_ = auVar74._12_4_ + 8;
                        auVar111._0_4_ = auVar69._0_4_ + 8;
                        auVar111._4_4_ = auVar69._4_4_ + 8;
                        auVar111._8_4_ = auVar69._8_4_ + 8;
                        auVar111._12_4_ = auVar69._12_4_ + 8;
                        lVar41 = lVar41 + 0x20;
                        sVar55 = (short)(int)(auVar130._0_4_ * fVar60 + fVar59);
                        sVar56 = (short)(int)(auVar130._4_4_ * fVar60 + fVar59);
                        sVar57 = (short)(int)(auVar130._8_4_ * fVar60 + fVar59);
                        sVar58 = (short)(int)(auVar130._12_4_ * fVar60 + fVar59);
                        sVar142 = (short)(int)(auVar199._0_4_ * fVar60 + fVar59);
                        sVar150 = (short)(int)(auVar199._4_4_ * fVar60 + fVar59);
                        sVar152 = (short)(int)(auVar199._8_4_ * fVar60 + fVar59);
                        sVar154 = (short)(int)(auVar199._12_4_ * fVar60 + fVar59);
                        uVar155 = (int)sVar55 * (int)psVar5[8];
                        uVar156 = (int)sVar56 * (int)psVar5[10];
                        uVar163 = (int)sVar57 * (int)psVar5[0xc];
                        uVar164 = (int)sVar58 * (int)psVar5[0xe];
                        uVar165 = (int)sVar142 * (int)*psVar5;
                        uVar181 = (int)sVar150 * (int)psVar5[2];
                        uVar188 = (int)sVar152 * (int)psVar5[4];
                        uVar189 = (int)sVar154 * (int)psVar5[6];
                        uVar38 = (int)sVar55 * (int)psVar5[9];
                        uVar49 = (int)sVar56 * (int)psVar5[0xb];
                        uVar139 = (int)sVar57 * (int)psVar5[0xd];
                        uVar140 = (int)sVar58 * (int)psVar5[0xf];
                        uVar141 = (int)sVar142 * (int)psVar5[1];
                        uVar143 = (int)sVar150 * (int)psVar5[3];
                        uVar151 = (int)sVar152 * (int)psVar5[5];
                        uVar153 = (int)sVar154 * (int)psVar5[7];
                        iVar178 = -(uint)((int)uVar156 < 0);
                        iVar179 = -(uint)((int)uVar163 < 0);
                        iVar180 = -(uint)((int)uVar164 < 0);
                        iVar200 = -(uint)((int)uVar181 < 0);
                        iVar201 = -(uint)((int)uVar188 < 0);
                        iVar202 = -(uint)((int)uVar189 < 0);
                        iVar208 = -(uint)((int)uVar49 < 0);
                        iVar209 = -(uint)((int)uVar139 < 0);
                        iVar210 = -(uint)((int)uVar140 < 0);
                        iVar39 = -(uint)((int)uVar143 < 0);
                        iVar37 = -(uint)((int)uVar151 < 0);
                        iVar40 = -(uint)((int)uVar153 < 0);
                        auVar159._0_4_ = uVar155 >> 0xc;
                        auVar159._4_4_ = uVar156 >> 0xc;
                        auVar159._8_4_ = uVar163 >> 0xc;
                        auVar159._12_4_ = uVar164 >> 0xc;
                        auVar182._0_4_ = uVar165 >> 0xc;
                        auVar182._4_4_ = uVar181 >> 0xc;
                        auVar182._8_4_ = uVar188 >> 0xc;
                        auVar182._12_4_ = uVar189 >> 0xc;
                        auVar166._0_4_ = -(uint)((int)uVar155 >> 0x1b == -(uint)((int)uVar155 < 0));
                        auVar166._4_4_ = -(uint)((int)uVar156 >> 0x1b == iVar178);
                        auVar166._8_4_ = -(uint)((int)uVar163 >> 0x1b == iVar179);
                        auVar166._12_4_ = -(uint)((int)uVar164 >> 0x1b == iVar180);
                        auVar172._0_6_ =
                             CONCAT15((char)((uint)iVar178 >> 8),
                                      CONCAT14((char)iVar178,
                                               (uint)(ushort)((ushort)-(uint)((int)uVar155 < 0) ^
                                                             0x7fff))) ^ 0x7fff00000000;
                        auVar172[6] = 0;
                        auVar172[7] = (undefined1)((uint)iVar178 >> 0x18);
                        auVar172[8] = (byte)iVar179 ^ 0xff;
                        auVar172[9] = (byte)((uint)iVar179 >> 8) ^ 0x7f;
                        auVar172[10] = (undefined1)((uint)iVar179 >> 0x10);
                        auVar172[0xb] = (undefined1)((uint)iVar179 >> 0x18);
                        auVar172[0xc] = (byte)iVar180 ^ 0xff;
                        auVar172[0xd] = (byte)((uint)iVar180 >> 8) ^ 0x7f;
                        auVar172[0xe] = (undefined1)((uint)iVar180 >> 0x10);
                        auVar172[0xf] = (undefined1)((uint)iVar180 >> 0x18);
                        auVar191._0_4_ = -(uint)((int)uVar165 >> 0x1b == -(uint)((int)uVar165 < 0));
                        auVar191._4_4_ = -(uint)((int)uVar181 >> 0x1b == iVar200);
                        auVar191._8_4_ = -(uint)((int)uVar188 >> 0x1b == iVar201);
                        auVar191._12_4_ = -(uint)((int)uVar189 >> 0x1b == iVar202);
                        auVar197._0_6_ =
                             CONCAT15((char)((uint)iVar200 >> 8),
                                      CONCAT14((char)iVar200,
                                               (uint)(ushort)((ushort)-(uint)((int)uVar165 < 0) ^
                                                             0x7fff))) ^ 0x7fff00000000;
                        auVar197[6] = 0;
                        auVar197[7] = (undefined1)((uint)iVar200 >> 0x18);
                        auVar197[8] = (byte)iVar201 ^ 0xff;
                        auVar197[9] = (byte)((uint)iVar201 >> 8) ^ 0x7f;
                        auVar197[10] = (undefined1)((uint)iVar201 >> 0x10);
                        auVar197[0xb] = (undefined1)((uint)iVar201 >> 0x18);
                        auVar197[0xc] = (byte)iVar202 ^ 0xff;
                        auVar197[0xd] = (byte)((uint)iVar202 >> 8) ^ 0x7f;
                        auVar197[0xe] = (undefined1)((uint)iVar202 >> 0x10);
                        auVar197[0xf] = (undefined1)((uint)iVar202 >> 0x18);
                        auVar134._0_4_ = uVar38 >> 0xc;
                        auVar134._4_4_ = uVar49 >> 0xc;
                        auVar134._8_4_ = uVar139 >> 0xc;
                        auVar134._12_4_ = uVar140 >> 0xc;
                        auVar144._0_4_ = uVar141 >> 0xc;
                        auVar144._4_4_ = uVar143 >> 0xc;
                        auVar144._8_4_ = uVar151 >> 0xc;
                        auVar144._12_4_ = uVar153 >> 0xc;
                        auVar203._0_4_ = -(uint)((int)uVar38 >> 0x1b == -(uint)((int)uVar38 < 0));
                        auVar203._4_4_ = -(uint)((int)uVar49 >> 0x1b == iVar208);
                        auVar203._8_4_ = -(uint)((int)uVar139 >> 0x1b == iVar209);
                        auVar203._12_4_ = -(uint)((int)uVar140 >> 0x1b == iVar210);
                        auVar206._0_6_ =
                             CONCAT15((char)((uint)iVar208 >> 8),
                                      CONCAT14((char)iVar208,
                                               (uint)(ushort)((ushort)-(uint)((int)uVar38 < 0) ^
                                                             0x7fff))) ^ 0x7fff00000000;
                        auVar206[6] = 0;
                        auVar206[7] = (undefined1)((uint)iVar208 >> 0x18);
                        auVar206[8] = (byte)iVar209 ^ 0xff;
                        auVar206[9] = (byte)((uint)iVar209 >> 8) ^ 0x7f;
                        auVar206[10] = (undefined1)((uint)iVar209 >> 0x10);
                        auVar206[0xb] = (undefined1)((uint)iVar209 >> 0x18);
                        auVar206[0xc] = (byte)iVar210 ^ 0xff;
                        auVar206[0xd] = (byte)((uint)iVar210 >> 8) ^ 0x7f;
                        auVar206[0xe] = (undefined1)((uint)iVar210 >> 0x10);
                        auVar206[0xf] = (undefined1)((uint)iVar210 >> 0x18);
                        auVar159 = auVar159 ^ (auVar159 ^ auVar172) & ~auVar166;
                        auVar182 = auVar182 ^ (auVar182 ^ auVar197) & ~auVar191;
                        auVar22[6] = 0;
                        auVar22._0_6_ =
                             CONCAT15((char)((uint)iVar39 >> 8),
                                      CONCAT14((char)iVar39,
                                               (uint)(ushort)((ushort)-(uint)((int)uVar141 < 0) ^
                                                             0x7fff))) ^ 0x7fff00000000;
                        auVar22[7] = (char)((uint)iVar39 >> 0x18);
                        auVar22[8] = (byte)iVar37 ^ 0xff;
                        auVar22[9] = (byte)((uint)iVar37 >> 8) ^ 0x7f;
                        auVar22[10] = (char)((uint)iVar37 >> 0x10);
                        auVar22[0xb] = (char)((uint)iVar37 >> 0x18);
                        auVar22[0xc] = (byte)iVar40 ^ 0xff;
                        auVar22[0xd] = (byte)((uint)iVar40 >> 8) ^ 0x7f;
                        auVar22[0xe] = (char)((uint)iVar40 >> 0x10);
                        auVar22[0xf] = (char)((uint)iVar40 >> 0x18);
                        auVar69._4_4_ = -(uint)((int)uVar143 >> 0x1b == iVar39);
                        auVar69._0_4_ = -(uint)((int)uVar141 >> 0x1b == -(uint)((int)uVar141 < 0));
                        auVar69._8_4_ = -(uint)((int)uVar151 >> 0x1b == iVar37);
                        auVar69._12_4_ = -(uint)((int)uVar153 >> 0x1b == iVar40);
                        auVar144 = auVar144 ^ (auVar144 ^ auVar22) & ~auVar69;
                        auVar134 = auVar134 ^ (auVar134 ^ auVar206) & ~auVar203;
                        *psVar5 = auVar182._0_2_;
                        psVar5[1] = auVar144._0_2_;
                        psVar5[2] = auVar182._4_2_;
                        psVar5[3] = auVar144._4_2_;
                        psVar5[4] = auVar182._8_2_;
                        psVar5[5] = auVar144._8_2_;
                        psVar5[6] = auVar182._12_2_;
                        psVar5[7] = auVar144._12_2_;
                        psVar5[8] = auVar159._0_2_;
                        psVar5[9] = auVar134._0_2_;
                        psVar5[10] = auVar159._4_2_;
                        psVar5[0xb] = auVar134._4_2_;
                        psVar5[0xc] = auVar159._8_2_;
                        psVar5[0xd] = auVar134._8_2_;
                        psVar5[0xe] = auVar159._12_2_;
                        psVar5[0xf] = auVar134._12_2_;
                        auVar69 = auVar111;
                        auVar74 = auVar121;
                        fVar101 = fVar76;
                      } while (lVar41 != 0xd80);
                    }
                  }
                  *(float *)(lVar52 + 0x48) = fVar101;
                  if (DAT_01043e7c == 96000) {
                    puVar42 = puVar33 + 0x5970;
                  }
                  else if (DAT_01043e80 == '\x18') {
                    pVar2 = (unkbyte9 *)(puVar33 + -0x1320);
                    uVar45 = *(undefined8 *)(puVar33 + -0x1318);
                    uVar211 = (undefined1)((ulong)uVar45 >> 8);
                    uVar212 = (undefined1)((ulong)uVar45 >> 0x10);
                    uVar213 = (undefined1)((ulong)uVar45 >> 0x18);
                    uVar214 = (undefined1)((ulong)uVar45 >> 0x20);
                    uVar215 = (undefined1)((ulong)uVar45 >> 0x28);
                    uVar216 = (undefined1)((ulong)uVar45 >> 0x30);
                    uVar217 = (undefined1)((ulong)uVar45 >> 0x38);
                    Var29 = *pVar2;
                    Var27 = *pVar2;
                    Var26 = *pVar2;
                    pauVar1 = (undefined1 (*) [12])(puVar33 + -0x1310);
                    uVar48 = (undefined4)((ulong)*(undefined8 *)(puVar33 + -0x1308) >> 0x20);
                    auVar28 = *pauVar1;
                    auVar25 = *pauVar1;
                    auVar24 = *pauVar1;
                    puVar35 = puVar33 + 0x5970;
                    lVar52 = -0x1b00;
                    do {
                      auVar64[0] = *puVar35;
                      auVar80[0] = puVar35[1];
                      auVar102[0] = puVar35[2];
                      auVar64[1] = puVar35[3];
                      auVar80[1] = puVar35[4];
                      auVar102[1] = puVar35[5];
                      auVar64[2] = puVar35[6];
                      auVar80[2] = puVar35[7];
                      auVar102[2] = puVar35[8];
                      auVar64[3] = puVar35[9];
                      auVar80[3] = puVar35[10];
                      auVar102[3] = puVar35[0xb];
                      auVar64[4] = puVar35[0xc];
                      auVar80[4] = puVar35[0xd];
                      auVar102[4] = puVar35[0xe];
                      auVar64[5] = puVar35[0xf];
                      auVar80[5] = puVar35[0x10];
                      auVar102[5] = puVar35[0x11];
                      auVar64[6] = puVar35[0x12];
                      auVar80[6] = puVar35[0x13];
                      auVar102[6] = puVar35[0x14];
                      auVar64[7] = puVar35[0x15];
                      auVar80[7] = puVar35[0x16];
                      auVar102[7] = puVar35[0x17];
                      auVar64[8] = puVar35[0x18];
                      auVar80[8] = puVar35[0x19];
                      auVar102[8] = puVar35[0x1a];
                      auVar64[9] = puVar35[0x1b];
                      auVar80[9] = puVar35[0x1c];
                      auVar102[9] = puVar35[0x1d];
                      auVar64[10] = puVar35[0x1e];
                      auVar80[10] = puVar35[0x1f];
                      auVar102[10] = puVar35[0x20];
                      auVar64[0xb] = puVar35[0x21];
                      auVar80[0xb] = puVar35[0x22];
                      auVar102[0xb] = puVar35[0x23];
                      auVar64[0xc] = puVar35[0x24];
                      auVar80[0xc] = puVar35[0x25];
                      auVar102[0xc] = puVar35[0x26];
                      auVar64[0xd] = puVar35[0x27];
                      auVar80[0xd] = puVar35[0x28];
                      auVar102[0xd] = puVar35[0x29];
                      auVar64[0xe] = puVar35[0x2a];
                      auVar80[0xe] = puVar35[0x2b];
                      auVar102[0xe] = puVar35[0x2c];
                      auVar64[0xf] = puVar35[0x2d];
                      auVar80[0xf] = puVar35[0x2e];
                      auVar102[0xf] = puVar35[0x2f];
                      puVar35 = puVar35 + 0x30;
                      puVar42 = puVar33 + -0x1290;
                      lVar41 = lVar52 + 0x40;
                      auVar12._12_4_ = uVar48;
                      auVar12._0_12_ = auVar24;
                      auVar130 = a64_TBL(ZEXT816(0),auVar102,auVar12);
                      auVar13._12_4_ = uVar48;
                      auVar13._0_12_ = auVar25;
                      auVar199 = a64_TBL(ZEXT816(0),auVar80,auVar13);
                      auVar19[9] = uVar211;
                      auVar19._0_9_ = Var26;
                      auVar19[10] = uVar212;
                      auVar19[0xb] = uVar213;
                      auVar19[0xc] = uVar214;
                      auVar19[0xd] = uVar215;
                      auVar19[0xe] = uVar216;
                      auVar19[0xf] = uVar217;
                      auVar115 = a64_TBL(ZEXT816(0),auVar102,auVar19);
                      auVar20[9] = uVar211;
                      auVar20._0_9_ = Var27;
                      auVar20[10] = uVar212;
                      auVar20[0xb] = uVar213;
                      auVar20[0xc] = uVar214;
                      auVar20[0xd] = uVar215;
                      auVar20[0xe] = uVar216;
                      auVar20[0xf] = uVar217;
                      auVar129 = a64_TBL(ZEXT816(0),auVar80,auVar20);
                      auVar138 = a64_TBL(ZEXT816(0),auVar102,_DAT_0020a230);
                      auVar148 = a64_TBL(ZEXT816(0),auVar80,_DAT_0020a230);
                      auVar161 = a64_TBL(ZEXT816(0),auVar102,_DAT_00208900);
                      auVar170 = a64_TBL(ZEXT816(0),auVar80,_DAT_00208900);
                      auVar14._12_4_ = uVar48;
                      auVar14._0_12_ = auVar28;
                      auVar205 = a64_TBL(ZEXT816(0),auVar64,auVar14);
                      auVar21[9] = uVar211;
                      auVar21._0_9_ = Var29;
                      auVar21[10] = uVar212;
                      auVar21[0xb] = uVar213;
                      auVar21[0xc] = uVar214;
                      auVar21[0xd] = uVar215;
                      auVar21[0xe] = uVar216;
                      auVar21[0xf] = uVar217;
                      auVar176 = a64_TBL(ZEXT816(0),auVar64,auVar21);
                      auVar74 = a64_TBL(ZEXT816(0),auVar64,_DAT_0020a230);
                      auVar69 = a64_TBL(ZEXT816(0),auVar64,_DAT_00208900);
                      auVar119._0_8_ =
                           CONCAT17(auVar199[6] | auVar130[5] | auVar205[7],
                                    CONCAT16(auVar199[5] | auVar130[4] | auVar205[6],
                                             CONCAT15(auVar199[4] | auVar205[5],
                                                      CONCAT14(auVar205[4],
                                                               CONCAT13(auVar199[2] | auVar130[1] |
                                                                        auVar205[3],
                                                                        CONCAT12(auVar199[1] |
                                                                                 auVar130[0] |
                                                                                 auVar205[2],
                                                                                 CONCAT11(auVar199[0
                                                  ] | auVar205[1],auVar205[0])))))));
                      auVar119[8] = auVar205[8];
                      auVar119[9] = auVar199[8] | auVar205[9];
                      auVar119[10] = auVar199[9] | auVar130[8] | auVar205[10];
                      auVar119[0xb] = auVar199[10] | auVar130[9] | auVar205[0xb];
                      auVar122[0xc] = auVar205[0xc];
                      auVar122._0_12_ = auVar119;
                      auVar122[0xd] = auVar199[0xc] | auVar205[0xd];
                      auVar122[0xe] = auVar199[0xd] | auVar130[0xc] | auVar205[0xe];
                      auVar122[0xf] = auVar199[0xe] | auVar130[0xd] | auVar205[0xf];
                      auVar157._0_8_ =
                           CONCAT17(auVar129[6] | auVar115[5] | auVar176[7],
                                    CONCAT16(auVar129[5] | auVar115[4] | auVar176[6],
                                             CONCAT15(auVar129[4] | auVar176[5],
                                                      CONCAT14(auVar176[4],
                                                               CONCAT13(auVar129[2] | auVar115[1] |
                                                                        auVar176[3],
                                                                        CONCAT12(auVar129[1] |
                                                                                 auVar115[0] |
                                                                                 auVar176[2],
                                                                                 CONCAT11(auVar129[0
                                                  ] | auVar176[1],auVar176[0])))))));
                      auVar157[8] = auVar176[8];
                      auVar157[9] = auVar129[8] | auVar176[9];
                      auVar157[10] = auVar129[9] | auVar115[8] | auVar176[10];
                      auVar157[0xb] = auVar129[10] | auVar115[9] | auVar176[0xb];
                      auVar124[0xc] = auVar176[0xc];
                      auVar124._0_12_ = auVar157;
                      auVar124[0xd] = auVar129[0xc] | auVar176[0xd];
                      auVar124[0xe] = auVar129[0xd] | auVar115[0xc] | auVar176[0xe];
                      auVar124[0xf] = auVar129[0xe] | auVar115[0xd] | auVar176[0xf];
                      auVar77._0_8_ =
                           CONCAT17(auVar148[6] | auVar138[5] | auVar74[7],
                                    CONCAT16(auVar148[5] | auVar138[4] | auVar74[6],
                                             CONCAT15(auVar148[4] | auVar74[5],
                                                      CONCAT14(auVar74[4],
                                                               CONCAT13(auVar148[2] | auVar138[1] |
                                                                        auVar74[3],
                                                                        CONCAT12(auVar148[1] |
                                                                                 auVar138[0] |
                                                                                 auVar74[2],
                                                                                 CONCAT11(auVar148[0
                                                  ] | auVar74[1],auVar74[0])))))));
                      auVar77[8] = auVar74[8];
                      auVar77[9] = auVar148[8] | auVar74[9];
                      auVar77[10] = auVar148[9] | auVar138[8] | auVar74[10];
                      auVar77[0xb] = auVar148[10] | auVar138[9] | auVar74[0xb];
                      auVar81[0xc] = auVar74[0xc];
                      auVar81._0_12_ = auVar77;
                      auVar81[0xd] = auVar148[0xc] | auVar74[0xd];
                      auVar81[0xe] = auVar148[0xd] | auVar138[0xc] | auVar74[0xe];
                      auVar81[0xf] = auVar148[0xe] | auVar138[0xd] | auVar74[0xf];
                      auVar61._0_8_ =
                           CONCAT17(auVar170[6] | auVar161[5] | auVar69[7],
                                    CONCAT16(auVar170[5] | auVar161[4] | auVar69[6],
                                             CONCAT15(auVar170[4] | auVar69[5],
                                                      CONCAT14(auVar69[4],
                                                               CONCAT13(auVar170[2] | auVar161[1] |
                                                                        auVar69[3],
                                                                        CONCAT12(auVar170[1] |
                                                                                 auVar161[0] |
                                                                                 auVar69[2],
                                                                                 CONCAT11(auVar170[0
                                                  ] | auVar69[1],auVar69[0])))))));
                      auVar61[8] = auVar69[8];
                      auVar61[9] = auVar170[8] | auVar69[9];
                      auVar61[10] = auVar170[9] | auVar161[8] | auVar69[10];
                      auVar61[0xb] = auVar170[10] | auVar161[9] | auVar69[0xb];
                      auVar65[0xc] = auVar69[0xc];
                      auVar65._0_12_ = auVar61;
                      auVar65[0xd] = auVar170[0xc] | auVar69[0xd];
                      auVar65[0xe] = auVar170[0xd] | auVar161[0xc] | auVar69[0xe];
                      auVar65[0xf] = auVar170[0xe] | auVar161[0xd] | auVar69[0xf];
                      auVar135._0_4_ = (int)(short)-(auVar102[0xc] < '\0');
                      auVar135._4_4_ = (int)(short)-(auVar102[0xd] < '\0');
                      auVar135._8_4_ = (int)(short)-(auVar102[0xe] < '\0');
                      auVar135._12_4_ = (int)(short)-(auVar102[0xf] < '\0');
                      auVar145._0_8_ =
                           CONCAT44((int)(short)-(auVar102[9] < '\0'),
                                    (int)(short)-(auVar102[8] < '\0'));
                      auVar145._8_4_ = (int)(short)-(auVar102[10] < '\0');
                      auVar145._12_4_ = (int)(short)-(auVar102[0xb] < '\0');
                      auVar183._0_4_ = (int)(short)-(auVar102[4] < '\0');
                      auVar183._4_4_ = (int)(short)-(auVar102[5] < '\0');
                      auVar183._8_4_ = (int)(short)-(auVar102[6] < '\0');
                      auVar183._12_4_ = (int)(short)-(auVar102[7] < '\0');
                      auVar112._0_4_ = (int)(short)-(auVar102[0] < '\0');
                      auVar112._4_4_ = (int)(short)-(auVar102[1] < '\0');
                      auVar112._8_4_ = (int)(short)-(auVar102[2] < '\0');
                      auVar112._12_4_ = (int)(short)-(auVar102[3] < '\0');
                      auVar103._0_8_ = auVar119._0_8_ | 0xff000000ff000000;
                      auVar103._8_4_ = auVar119._8_4_ | 0xff000000;
                      auVar103._12_4_ = auVar122._12_4_ | 0xff000000;
                      auVar167._0_8_ = auVar157._0_8_ | 0xff000000ff000000;
                      auVar167._8_4_ = auVar157._8_4_ | 0xff000000;
                      auVar167._12_4_ = auVar124._12_4_ | 0xff000000;
                      auVar173._0_8_ = auVar77._0_8_ | 0xff000000ff000000;
                      auVar173._8_4_ = auVar77._8_4_ | 0xff000000;
                      auVar173._12_4_ = auVar81._12_4_ | 0xff000000;
                      auVar192._0_8_ = auVar61._0_8_ | 0xff000000ff000000;
                      auVar192._8_4_ = auVar61._8_4_ | 0xff000000;
                      auVar192._12_4_ = auVar65._12_4_ | 0xff000000;
                      auVar103 = auVar103 ^ (auVar103 ^ auVar122) & ~auVar135;
                      auVar123._8_8_ = auVar145._8_8_;
                      auVar123._0_8_ = auVar145._0_8_;
                      auVar81 = auVar81 ^ (auVar81 ^ auVar173) & auVar183;
                      auVar65 = auVar65 ^ (auVar65 ^ auVar192) & auVar112;
                      auVar124 = auVar124 ^ (auVar124 ^ auVar167) & auVar123;
                      *(long *)(puVar42 + lVar52 + 0x1b38) = auVar103._8_8_;
                      *(long *)(puVar42 + lVar52 + 0x1b30) = auVar103._0_8_;
                      *(long *)(puVar42 + lVar52 + 0x1b18) = auVar81._8_8_;
                      *(long *)(puVar42 + lVar52 + 0x1b10) = auVar81._0_8_;
                      *(long *)(puVar42 + lVar52 + 0x1b08) = auVar65._8_8_;
                      *(long *)(puVar42 + lVar52 + 0x1b00) = auVar65._0_8_;
                      *(long *)(puVar42 + lVar52 + 0x1b28) = auVar124._8_8_;
                      *(long *)(puVar42 + lVar52 + 0x1b20) = auVar124._0_8_;
                      lVar52 = lVar41;
                    } while (lVar41 != 0);
                  }
                  else {
                    auVar74 = *(undefined1 (*) [16])(puVar33 + -0x1320);
                    auVar69 = *(undefined1 (*) [16])(puVar33 + -0x1310);
                    puVar35 = puVar33 + 0x5970;
                    lVar52 = -0x1b00;
                    do {
                      auVar66[0] = *puVar35;
                      bVar75 = puVar35[1];
                      auVar66[1] = puVar35[2];
                      bVar88 = puVar35[3];
                      auVar66[2] = puVar35[4];
                      bVar89 = puVar35[5];
                      auVar66[3] = puVar35[6];
                      bVar90 = puVar35[7];
                      auVar66[4] = puVar35[8];
                      bVar91 = puVar35[9];
                      auVar66[5] = puVar35[10];
                      bVar92 = puVar35[0xb];
                      auVar66[6] = puVar35[0xc];
                      bVar93 = puVar35[0xd];
                      auVar66[7] = puVar35[0xe];
                      pbVar50 = puVar35 + 0xf;
                      auVar66[8] = puVar35[0x10];
                      bVar94 = puVar35[0x11];
                      auVar66[9] = puVar35[0x12];
                      bVar95 = puVar35[0x13];
                      auVar66[10] = puVar35[0x14];
                      bVar96 = puVar35[0x15];
                      auVar66[0xb] = puVar35[0x16];
                      pbVar36 = puVar35 + 0x17;
                      auVar66[0xc] = puVar35[0x18];
                      bVar97 = puVar35[0x19];
                      auVar66[0xd] = puVar35[0x1a];
                      bVar98 = puVar35[0x1b];
                      auVar66[0xe] = puVar35[0x1c];
                      bVar99 = puVar35[0x1d];
                      auVar66[0xf] = puVar35[0x1e];
                      bVar100 = puVar35[0x1f];
                      puVar35 = puVar35 + 0x20;
                      puVar42 = puVar33 + -0x1290;
                      lVar41 = lVar52 + 0x40;
                      auVar115 = a64_TBL(ZEXT816(0),auVar66,auVar69);
                      auVar129 = a64_TBL(ZEXT816(0),auVar66,auVar74);
                      auVar199 = a64_TBL(ZEXT816(0),auVar66,_DAT_0020a230);
                      auVar130 = a64_TBL(ZEXT816(0),auVar66,_DAT_00208900);
                      auVar104._0_8_ =
                           CONCAT17((byte)((short)(char)bVar95 >> 0xf) | auVar129[7],
                                    CONCAT16((char)bVar95 >> 7 | auVar129[6],
                                             CONCAT15(bVar95 | auVar129[5],
                                                      CONCAT14(auVar129[4],
                                                               CONCAT13((byte)((short)(char)bVar94
                                                                              >> 0xf) | auVar129[3],
                                                                        CONCAT12((char)bVar94 >> 7 |
                                                                                 auVar129[2],
                                                                                 CONCAT11(bVar94 | 
                                                  auVar129[1],auVar129[0])))))));
                      auVar104[8] = auVar129[8];
                      auVar104[9] = bVar96 | auVar129[9];
                      auVar104[10] = (char)bVar96 >> 7 | auVar129[10];
                      auVar104[0xb] = (byte)((short)(char)bVar96 >> 0xf) | auVar129[0xb];
                      auVar104[0xc] = auVar129[0xc];
                      auVar104[0xd] = *pbVar36 | auVar129[0xd];
                      bVar94 = (char)*pbVar36 >> 7;
                      auVar104[0xe] = bVar94 | auVar129[0xe];
                      auVar104[0xf] = bVar94 | auVar129[0xf];
                      auVar82._0_8_ =
                           CONCAT17((byte)((short)(char)bVar92 >> 0xf) | auVar199[7],
                                    CONCAT16((char)bVar92 >> 7 | auVar199[6],
                                             CONCAT15(bVar92 | auVar199[5],
                                                      CONCAT14(auVar199[4],
                                                               CONCAT13((byte)((short)(char)bVar91
                                                                              >> 0xf) | auVar199[3],
                                                                        CONCAT12((char)bVar91 >> 7 |
                                                                                 auVar199[2],
                                                                                 CONCAT11(bVar91 | 
                                                  auVar199[1],auVar199[0])))))));
                      auVar82[8] = auVar199[8];
                      auVar82[9] = bVar93 | auVar199[9];
                      auVar82[10] = (char)bVar93 >> 7 | auVar199[10];
                      auVar82[0xb] = (byte)((short)(char)bVar93 >> 0xf) | auVar199[0xb];
                      auVar82[0xc] = auVar199[0xc];
                      auVar82[0xd] = *pbVar50 | auVar199[0xd];
                      bVar91 = (char)*pbVar50 >> 7;
                      auVar82[0xe] = bVar91 | auVar199[0xe];
                      auVar82[0xf] = bVar91 | auVar199[0xf];
                      auVar67._0_8_ =
                           CONCAT17((byte)((short)(char)bVar88 >> 0xf) | auVar130[7],
                                    CONCAT16((char)bVar88 >> 7 | auVar130[6],
                                             CONCAT15(bVar88 | auVar130[5],
                                                      CONCAT14(auVar130[4],
                                                               CONCAT13((byte)((short)(char)bVar75
                                                                              >> 0xf) | auVar130[3],
                                                                        CONCAT12((char)bVar75 >> 7 |
                                                                                 auVar130[2],
                                                                                 CONCAT11(bVar75 | 
                                                  auVar130[1],auVar130[0])))))));
                      auVar67[8] = auVar130[8];
                      auVar67[9] = bVar89 | auVar130[9];
                      auVar67[10] = (char)bVar89 >> 7 | auVar130[10];
                      auVar67[0xb] = (byte)((short)(char)bVar89 >> 0xf) | auVar130[0xb];
                      auVar67[0xc] = auVar130[0xc];
                      auVar67[0xd] = bVar90 | auVar130[0xd];
                      auVar67[0xe] = (char)bVar90 >> 7 | auVar130[0xe];
                      auVar67[0xf] = (byte)((short)(char)bVar90 >> 0xf) | auVar130[0xf];
                      puVar42[lVar52 + 0x1b38] = auVar115[8];
                      puVar42[lVar52 + 0x1b39] = bVar99 | auVar115[9];
                      puVar42[lVar52 + 0x1b3a] = (char)bVar99 >> 7 | auVar115[10];
                      puVar42[lVar52 + 0x1b3b] = (byte)((short)(char)bVar99 >> 0xf) | auVar115[0xb];
                      puVar42[lVar52 + 0x1b3c] = auVar115[0xc];
                      puVar42[lVar52 + 0x1b3d] = bVar100 | auVar115[0xd];
                      puVar42[lVar52 + 0x1b3e] = (char)bVar100 >> 7 | auVar115[0xe];
                      puVar42[lVar52 + 0x1b3f] = (byte)((short)(char)bVar100 >> 0xf) | auVar115[0xf]
                      ;
                      puVar42[lVar52 + 0x1b30] = auVar115[0];
                      puVar42[lVar52 + 0x1b31] = bVar97 | auVar115[1];
                      puVar42[lVar52 + 0x1b32] = (char)bVar97 >> 7 | auVar115[2];
                      puVar42[lVar52 + 0x1b33] = (byte)((short)(char)bVar97 >> 0xf) | auVar115[3];
                      puVar42[lVar52 + 0x1b34] = auVar115[4];
                      puVar42[lVar52 + 0x1b35] = bVar98 | auVar115[5];
                      puVar42[lVar52 + 0x1b36] = (char)bVar98 >> 7 | auVar115[6];
                      puVar42[lVar52 + 0x1b37] = (byte)((short)(char)bVar98 >> 0xf) | auVar115[7];
                      *(long *)(puVar42 + lVar52 + 0x1b28) = auVar104._8_8_;
                      *(undefined8 *)(puVar42 + lVar52 + 0x1b20) = auVar104._0_8_;
                      *(long *)(puVar42 + lVar52 + 0x1b18) = auVar82._8_8_;
                      *(undefined8 *)(puVar42 + lVar52 + 0x1b10) = auVar82._0_8_;
                      *(long *)(puVar42 + lVar52 + 0x1b08) = auVar67._8_8_;
                      *(undefined8 *)(puVar42 + lVar52 + 0x1b00) = auVar67._0_8_;
                      lVar52 = lVar41;
                    } while (lVar41 != 0);
                  }
                  iVar39 = (*DAT_01043e48)(DAT_0104ab30,puVar42,0x360,
                                           *(long *)(puVar33 + -0x12e0) + (long)(int)uVar132,
                                           DAT_0104aaf8);
                  uVar132 = iVar39 + uVar132;
                  uVar46 = uVar46 - *(int *)(puVar33 + -0x12cc);
                  uVar54 = uVar54 + *(long *)(puVar33 + -0x12d8);
                } while (*(int *)(puVar33 + -0x12cc) <= (int)uVar46);
              }
              *(undefined4 *)(puVar33 + -0x12a8) = 0x4bc;
              *(char **)(puVar33 + -0x12a0) =
                   "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
              *(char **)(puVar33 + -0x1298) = "a2dp_ssc_encode_frames_on_dual_play";
              *(ulong *)(puVar33 + 0x8f70) = (ulong)uVar132;
              *(undefined8 *)(puVar33 + -0x12c0) = 1;
              *(undefined8 *)(puVar33 + 0x8f80) = 3;
              *(undefined8 *)(puVar33 + 0x8f78) = 0;
              *(undefined1 **)(puVar33 + -0x12b8) = auStack_100;
              *(undefined8 *)(puVar33 + -0x12b0) = 3;
              bluetooth::log_internal::vlog
                        (2,"a2dp_vendor_ssc_encoder",puVar33 + -0x12a8,"SSC output_pos :  [ {} ]!!!"
                         ,0x1b,puVar33 + -0x12c0);
              lVar52 = *(long *)(puVar33 + -0x1338);
              uVar38 = *(uint *)(puVar33 + -0x1348);
              uVar49 = (uint)(0 < (int)uVar132);
              *(short *)(lVar52 + 2) = (short)uVar132;
              DAT_01043e64 = DAT_01043e64 + 1;
              *(int *)(lVar52 + 8) = DAT_01043e64;
            }
            *(uint *)(puVar33 + -0x1374) = uVar49;
            if (*(long *)(puVar33 + -0x1330) == 0) {
              bVar34 = false;
            }
            else {
              if ((int)uVar38 < *(int *)(puVar33 + -0x12cc)) {
                uVar49 = 0;
              }
              else {
                uVar54 = 0;
                uVar49 = 0;
                *(ulong *)(puVar33 + -0x1300) = *(ulong *)(puVar33 + -0x1350) & 0xff;
                do {
                  *(undefined4 *)(puVar33 + -0x12a8) = 0x4c5;
                  *(char **)(puVar33 + -0x12a0) =
                       "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
                  *(char **)(puVar33 + -0x1298) = "a2dp_ssc_encode_frames_on_dual_play";
                  *(undefined8 *)(puVar33 + 0x8f70) = *(undefined8 *)(puVar33 + -0x1300);
                  *(ulong *)(puVar33 + 0x8f80) = (ulong)uVar38;
                  *(ulong *)(puVar33 + 0x8fa0) = uVar54 & 0xffffffe0;
                  *(undefined8 *)(puVar33 + 0x8f78) = 0;
                  *(ulong *)(puVar33 + 0x8fb0) = (ulong)DAT_0104aaf8;
                  *(undefined8 *)(puVar33 + -0x12c0) = 5;
                  *(undefined8 *)(puVar33 + 0x8f88) = 0;
                  *(undefined8 *)(puVar33 + 0x8f98) = 0;
                  *(ulong *)(puVar33 + 0x8f90) = uVar51;
                  *(undefined8 *)(puVar33 + 0x8fa8) = 0;
                  *(undefined8 *)(puVar33 + 0x8fc0) = 0x318c66;
                  *(undefined8 *)(puVar33 + 0x8fb8) = 0;
                  *(undefined1 **)(puVar33 + -0x12b8) = auStack_100;
                  *(undefined8 *)(puVar33 + -0x12b0) = 0x318c66;
                  bluetooth::log_internal::vlog
                            (2,"a2dp_vendor_ssc_encoder",puVar33 + -0x12a8,
                             "nb_frame {} left_2nd {}, input {} pos_2nd {} bit rate {}",0x38,
                             puVar33 + -0x12c0);
                  __memcpy_chk(puVar33 + 0x5970,&DAT_010474e0 + ((int)uVar54 << 1),uVar51,0x3600);
                  lVar52 = *(long *)(puVar33 + -0x12c8);
                  fVar59 = *(float *)(lVar52 + 0x58);
                  fVar76 = *(float *)(lVar52 + 0x5c);
                  if ((fVar59 != 1.0) || (fVar101 = 1.0, fVar76 != 1.0)) {
                    if (DAT_01043e80 == '\x18') {
                      volumeStereo24(puVar33 + 0x5970,extraout_w1_00,fVar59,fVar76);
                      lVar52 = *(long *)(puVar33 + -0x12c8);
                      fVar101 = *(float *)(lVar52 + 0x5c);
                    }
                    else {
                      lVar41 = 0;
                      fVar60 = (float)((int)(fVar76 * 4096.0) - (int)(fVar59 * 4096.0)) / 864.0;
                      fVar59 = (float)(int)(fVar59 * 4096.0);
                      auVar69 = *(undefined1 (*) [16])(puVar33 + -0x1370);
                      auVar74 = *(undefined1 (*) [16])(puVar33 + -0x1360);
                      do {
                        auVar130 = NEON_ucvtf(auVar74,4);
                        auVar199 = NEON_ucvtf(auVar69,4);
                        psVar5 = (short *)(puVar33 + lVar41 + 0x5970);
                        auVar113._0_4_ = auVar69._0_4_ + 8;
                        auVar113._4_4_ = auVar69._4_4_ + 8;
                        auVar113._8_4_ = auVar69._8_4_ + 8;
                        auVar113._12_4_ = auVar69._12_4_ + 8;
                        auVar125._0_4_ = auVar74._0_4_ + 8;
                        auVar125._4_4_ = auVar74._4_4_ + 8;
                        auVar125._8_4_ = auVar74._8_4_ + 8;
                        auVar125._12_4_ = auVar74._12_4_ + 8;
                        lVar41 = lVar41 + 0x20;
                        sVar55 = (short)(int)(auVar130._0_4_ * fVar60 + fVar59);
                        sVar56 = (short)(int)(auVar130._4_4_ * fVar60 + fVar59);
                        sVar57 = (short)(int)(auVar130._8_4_ * fVar60 + fVar59);
                        sVar58 = (short)(int)(auVar130._12_4_ * fVar60 + fVar59);
                        sVar142 = (short)(int)(auVar199._0_4_ * fVar60 + fVar59);
                        sVar150 = (short)(int)(auVar199._4_4_ * fVar60 + fVar59);
                        sVar152 = (short)(int)(auVar199._8_4_ * fVar60 + fVar59);
                        sVar154 = (short)(int)(auVar199._12_4_ * fVar60 + fVar59);
                        uVar156 = (int)sVar55 * (int)psVar5[8];
                        uVar163 = (int)sVar56 * (int)psVar5[10];
                        uVar164 = (int)sVar57 * (int)psVar5[0xc];
                        uVar165 = (int)sVar58 * (int)psVar5[0xe];
                        uVar181 = (int)sVar142 * (int)*psVar5;
                        uVar188 = (int)sVar150 * (int)psVar5[2];
                        uVar189 = (int)sVar152 * (int)psVar5[4];
                        uVar190 = (int)sVar154 * (int)psVar5[6];
                        uVar132 = (int)sVar55 * (int)psVar5[9];
                        uVar139 = (int)sVar56 * (int)psVar5[0xb];
                        uVar140 = (int)sVar57 * (int)psVar5[0xd];
                        uVar141 = (int)sVar58 * (int)psVar5[0xf];
                        uVar143 = (int)sVar142 * (int)psVar5[1];
                        uVar151 = (int)sVar150 * (int)psVar5[3];
                        uVar153 = (int)sVar152 * (int)psVar5[5];
                        uVar155 = (int)sVar154 * (int)psVar5[7];
                        iVar178 = -(uint)((int)uVar163 < 0);
                        iVar179 = -(uint)((int)uVar164 < 0);
                        iVar180 = -(uint)((int)uVar165 < 0);
                        iVar200 = -(uint)((int)uVar188 < 0);
                        iVar201 = -(uint)((int)uVar189 < 0);
                        iVar202 = -(uint)((int)uVar190 < 0);
                        iVar208 = -(uint)((int)uVar139 < 0);
                        iVar209 = -(uint)((int)uVar140 < 0);
                        iVar210 = -(uint)((int)uVar141 < 0);
                        iVar39 = -(uint)((int)uVar151 < 0);
                        iVar37 = -(uint)((int)uVar153 < 0);
                        iVar40 = -(uint)((int)uVar155 < 0);
                        auVar160._0_4_ = uVar156 >> 0xc;
                        auVar160._4_4_ = uVar163 >> 0xc;
                        auVar160._8_4_ = uVar164 >> 0xc;
                        auVar160._12_4_ = uVar165 >> 0xc;
                        auVar184._0_4_ = uVar181 >> 0xc;
                        auVar184._4_4_ = uVar188 >> 0xc;
                        auVar184._8_4_ = uVar189 >> 0xc;
                        auVar184._12_4_ = uVar190 >> 0xc;
                        auVar168._0_4_ = -(uint)((int)uVar156 >> 0x1b == -(uint)((int)uVar156 < 0));
                        auVar168._4_4_ = -(uint)((int)uVar163 >> 0x1b == iVar178);
                        auVar168._8_4_ = -(uint)((int)uVar164 >> 0x1b == iVar179);
                        auVar168._12_4_ = -(uint)((int)uVar165 >> 0x1b == iVar180);
                        auVar174._0_6_ =
                             CONCAT15((char)((uint)iVar178 >> 8),
                                      CONCAT14((char)iVar178,
                                               (uint)(ushort)((ushort)-(uint)((int)uVar156 < 0) ^
                                                             0x7fff))) ^ 0x7fff00000000;
                        auVar174[6] = 0;
                        auVar174[7] = (undefined1)((uint)iVar178 >> 0x18);
                        auVar174[8] = (byte)iVar179 ^ 0xff;
                        auVar174[9] = (byte)((uint)iVar179 >> 8) ^ 0x7f;
                        auVar174[10] = (undefined1)((uint)iVar179 >> 0x10);
                        auVar174[0xb] = (undefined1)((uint)iVar179 >> 0x18);
                        auVar174[0xc] = (byte)iVar180 ^ 0xff;
                        auVar174[0xd] = (byte)((uint)iVar180 >> 8) ^ 0x7f;
                        auVar174[0xe] = (undefined1)((uint)iVar180 >> 0x10);
                        auVar174[0xf] = (undefined1)((uint)iVar180 >> 0x18);
                        auVar193._0_4_ = -(uint)((int)uVar181 >> 0x1b == -(uint)((int)uVar181 < 0));
                        auVar193._4_4_ = -(uint)((int)uVar188 >> 0x1b == iVar200);
                        auVar193._8_4_ = -(uint)((int)uVar189 >> 0x1b == iVar201);
                        auVar193._12_4_ = -(uint)((int)uVar190 >> 0x1b == iVar202);
                        auVar198._0_6_ =
                             CONCAT15((char)((uint)iVar200 >> 8),
                                      CONCAT14((char)iVar200,
                                               (uint)(ushort)((ushort)-(uint)((int)uVar181 < 0) ^
                                                             0x7fff))) ^ 0x7fff00000000;
                        auVar198[6] = 0;
                        auVar198[7] = (undefined1)((uint)iVar200 >> 0x18);
                        auVar198[8] = (byte)iVar201 ^ 0xff;
                        auVar198[9] = (byte)((uint)iVar201 >> 8) ^ 0x7f;
                        auVar198[10] = (undefined1)((uint)iVar201 >> 0x10);
                        auVar198[0xb] = (undefined1)((uint)iVar201 >> 0x18);
                        auVar198[0xc] = (byte)iVar202 ^ 0xff;
                        auVar198[0xd] = (byte)((uint)iVar202 >> 8) ^ 0x7f;
                        auVar198[0xe] = (undefined1)((uint)iVar202 >> 0x10);
                        auVar198[0xf] = (undefined1)((uint)iVar202 >> 0x18);
                        auVar136._0_4_ = uVar132 >> 0xc;
                        auVar136._4_4_ = uVar139 >> 0xc;
                        auVar136._8_4_ = uVar140 >> 0xc;
                        auVar136._12_4_ = uVar141 >> 0xc;
                        auVar146._0_4_ = uVar143 >> 0xc;
                        auVar146._4_4_ = uVar151 >> 0xc;
                        auVar146._8_4_ = uVar153 >> 0xc;
                        auVar146._12_4_ = uVar155 >> 0xc;
                        auVar204._0_4_ = -(uint)((int)uVar132 >> 0x1b == -(uint)((int)uVar132 < 0));
                        auVar204._4_4_ = -(uint)((int)uVar139 >> 0x1b == iVar208);
                        auVar204._8_4_ = -(uint)((int)uVar140 >> 0x1b == iVar209);
                        auVar204._12_4_ = -(uint)((int)uVar141 >> 0x1b == iVar210);
                        auVar207._0_6_ =
                             CONCAT15((char)((uint)iVar208 >> 8),
                                      CONCAT14((char)iVar208,
                                               (uint)(ushort)((ushort)-(uint)((int)uVar132 < 0) ^
                                                             0x7fff))) ^ 0x7fff00000000;
                        auVar207[6] = 0;
                        auVar207[7] = (undefined1)((uint)iVar208 >> 0x18);
                        auVar207[8] = (byte)iVar209 ^ 0xff;
                        auVar207[9] = (byte)((uint)iVar209 >> 8) ^ 0x7f;
                        auVar207[10] = (undefined1)((uint)iVar209 >> 0x10);
                        auVar207[0xb] = (undefined1)((uint)iVar209 >> 0x18);
                        auVar207[0xc] = (byte)iVar210 ^ 0xff;
                        auVar207[0xd] = (byte)((uint)iVar210 >> 8) ^ 0x7f;
                        auVar207[0xe] = (undefined1)((uint)iVar210 >> 0x10);
                        auVar207[0xf] = (undefined1)((uint)iVar210 >> 0x18);
                        auVar160 = auVar160 ^ (auVar160 ^ auVar174) & ~auVar168;
                        auVar184 = auVar184 ^ (auVar184 ^ auVar198) & ~auVar193;
                        auVar18[6] = 0;
                        auVar18._0_6_ =
                             CONCAT15((char)((uint)iVar39 >> 8),
                                      CONCAT14((char)iVar39,
                                               (uint)(ushort)((ushort)-(uint)((int)uVar143 < 0) ^
                                                             0x7fff))) ^ 0x7fff00000000;
                        auVar18[7] = (char)((uint)iVar39 >> 0x18);
                        auVar18[8] = (byte)iVar37 ^ 0xff;
                        auVar18[9] = (byte)((uint)iVar37 >> 8) ^ 0x7f;
                        auVar18[10] = (char)((uint)iVar37 >> 0x10);
                        auVar18[0xb] = (char)((uint)iVar37 >> 0x18);
                        auVar18[0xc] = (byte)iVar40 ^ 0xff;
                        auVar18[0xd] = (byte)((uint)iVar40 >> 8) ^ 0x7f;
                        auVar18[0xe] = (char)((uint)iVar40 >> 0x10);
                        auVar18[0xf] = (char)((uint)iVar40 >> 0x18);
                        auVar11._4_4_ = -(uint)((int)uVar151 >> 0x1b == iVar39);
                        auVar11._0_4_ = -(uint)((int)uVar143 >> 0x1b == -(uint)((int)uVar143 < 0));
                        auVar11._8_4_ = -(uint)((int)uVar153 >> 0x1b == iVar37);
                        auVar11._12_4_ = -(uint)((int)uVar155 >> 0x1b == iVar40);
                        auVar146 = auVar146 ^ (auVar146 ^ auVar18) & ~auVar11;
                        auVar136 = auVar136 ^ (auVar136 ^ auVar207) & ~auVar204;
                        *psVar5 = auVar184._0_2_;
                        psVar5[1] = auVar146._0_2_;
                        psVar5[2] = auVar184._4_2_;
                        psVar5[3] = auVar146._4_2_;
                        psVar5[4] = auVar184._8_2_;
                        psVar5[5] = auVar146._8_2_;
                        psVar5[6] = auVar184._12_2_;
                        psVar5[7] = auVar146._12_2_;
                        psVar5[8] = auVar160._0_2_;
                        psVar5[9] = auVar136._0_2_;
                        psVar5[10] = auVar160._4_2_;
                        psVar5[0xb] = auVar136._4_2_;
                        psVar5[0xc] = auVar160._8_2_;
                        psVar5[0xd] = auVar136._8_2_;
                        psVar5[0xe] = auVar160._12_2_;
                        psVar5[0xf] = auVar136._12_2_;
                        auVar69 = auVar113;
                        auVar74 = auVar125;
                        fVar101 = fVar76;
                      } while (lVar41 != 0xd80);
                    }
                  }
                  *(float *)(lVar52 + 0x58) = fVar101;
                  if (DAT_01043e7c == 96000) {
                    puVar42 = puVar33 + 0x5970;
                  }
                  else if (DAT_01043e80 == '\x18') {
                    pVar2 = (unkbyte9 *)(puVar33 + -0x1320);
                    uVar45 = *(undefined8 *)(puVar33 + -0x1318);
                    uVar211 = (undefined1)((ulong)uVar45 >> 8);
                    uVar212 = (undefined1)((ulong)uVar45 >> 0x10);
                    uVar213 = (undefined1)((ulong)uVar45 >> 0x18);
                    uVar214 = (undefined1)((ulong)uVar45 >> 0x20);
                    uVar215 = (undefined1)((ulong)uVar45 >> 0x28);
                    uVar216 = (undefined1)((ulong)uVar45 >> 0x30);
                    uVar217 = (undefined1)((ulong)uVar45 >> 0x38);
                    Var29 = *pVar2;
                    Var27 = *pVar2;
                    Var26 = *pVar2;
                    pauVar1 = (undefined1 (*) [12])(puVar33 + -0x1310);
                    uVar48 = (undefined4)((ulong)*(undefined8 *)(puVar33 + -0x1308) >> 0x20);
                    auVar28 = *pauVar1;
                    auVar25 = *pauVar1;
                    auVar24 = *pauVar1;
                    puVar35 = puVar33 + 0x5970;
                    lVar52 = -0x1b00;
                    do {
                      auVar68[0] = *puVar35;
                      auVar83[0] = puVar35[1];
                      auVar105[0] = puVar35[2];
                      auVar68[1] = puVar35[3];
                      auVar83[1] = puVar35[4];
                      auVar105[1] = puVar35[5];
                      auVar68[2] = puVar35[6];
                      auVar83[2] = puVar35[7];
                      auVar105[2] = puVar35[8];
                      auVar68[3] = puVar35[9];
                      auVar83[3] = puVar35[10];
                      auVar105[3] = puVar35[0xb];
                      auVar68[4] = puVar35[0xc];
                      auVar83[4] = puVar35[0xd];
                      auVar105[4] = puVar35[0xe];
                      auVar68[5] = puVar35[0xf];
                      auVar83[5] = puVar35[0x10];
                      auVar105[5] = puVar35[0x11];
                      auVar68[6] = puVar35[0x12];
                      auVar83[6] = puVar35[0x13];
                      auVar105[6] = puVar35[0x14];
                      auVar68[7] = puVar35[0x15];
                      auVar83[7] = puVar35[0x16];
                      auVar105[7] = puVar35[0x17];
                      auVar68[8] = puVar35[0x18];
                      auVar83[8] = puVar35[0x19];
                      auVar105[8] = puVar35[0x1a];
                      auVar68[9] = puVar35[0x1b];
                      auVar83[9] = puVar35[0x1c];
                      auVar105[9] = puVar35[0x1d];
                      auVar68[10] = puVar35[0x1e];
                      auVar83[10] = puVar35[0x1f];
                      auVar105[10] = puVar35[0x20];
                      auVar68[0xb] = puVar35[0x21];
                      auVar83[0xb] = puVar35[0x22];
                      auVar105[0xb] = puVar35[0x23];
                      auVar68[0xc] = puVar35[0x24];
                      auVar83[0xc] = puVar35[0x25];
                      auVar105[0xc] = puVar35[0x26];
                      auVar68[0xd] = puVar35[0x27];
                      auVar83[0xd] = puVar35[0x28];
                      auVar105[0xd] = puVar35[0x29];
                      auVar68[0xe] = puVar35[0x2a];
                      auVar83[0xe] = puVar35[0x2b];
                      auVar105[0xe] = puVar35[0x2c];
                      auVar68[0xf] = puVar35[0x2d];
                      auVar83[0xf] = puVar35[0x2e];
                      auVar105[0xf] = puVar35[0x2f];
                      puVar35 = puVar35 + 0x30;
                      puVar42 = puVar33 + -0x1290;
                      lVar41 = lVar52 + 0x40;
                      auVar8._12_4_ = uVar48;
                      auVar8._0_12_ = auVar24;
                      auVar130 = a64_TBL(ZEXT816(0),auVar105,auVar8);
                      auVar9._12_4_ = uVar48;
                      auVar9._0_12_ = auVar25;
                      auVar199 = a64_TBL(ZEXT816(0),auVar83,auVar9);
                      auVar15[9] = uVar211;
                      auVar15._0_9_ = Var26;
                      auVar15[10] = uVar212;
                      auVar15[0xb] = uVar213;
                      auVar15[0xc] = uVar214;
                      auVar15[0xd] = uVar215;
                      auVar15[0xe] = uVar216;
                      auVar15[0xf] = uVar217;
                      auVar115 = a64_TBL(ZEXT816(0),auVar105,auVar15);
                      auVar16[9] = uVar211;
                      auVar16._0_9_ = Var27;
                      auVar16[10] = uVar212;
                      auVar16[0xb] = uVar213;
                      auVar16[0xc] = uVar214;
                      auVar16[0xd] = uVar215;
                      auVar16[0xe] = uVar216;
                      auVar16[0xf] = uVar217;
                      auVar129 = a64_TBL(ZEXT816(0),auVar83,auVar16);
                      auVar138 = a64_TBL(ZEXT816(0),auVar105,_DAT_0020a230);
                      auVar148 = a64_TBL(ZEXT816(0),auVar83,_DAT_0020a230);
                      auVar161 = a64_TBL(ZEXT816(0),auVar105,_DAT_00208900);
                      auVar170 = a64_TBL(ZEXT816(0),auVar83,_DAT_00208900);
                      auVar10._12_4_ = uVar48;
                      auVar10._0_12_ = auVar28;
                      auVar205 = a64_TBL(ZEXT816(0),auVar68,auVar10);
                      auVar17[9] = uVar211;
                      auVar17._0_9_ = Var29;
                      auVar17[10] = uVar212;
                      auVar17[0xb] = uVar213;
                      auVar17[0xc] = uVar214;
                      auVar17[0xd] = uVar215;
                      auVar17[0xe] = uVar216;
                      auVar17[0xf] = uVar217;
                      auVar176 = a64_TBL(ZEXT816(0),auVar68,auVar17);
                      auVar74 = a64_TBL(ZEXT816(0),auVar68,_DAT_0020a230);
                      auVar69 = a64_TBL(ZEXT816(0),auVar68,_DAT_00208900);
                      auVar120._0_8_ =
                           CONCAT17(auVar199[6] | auVar130[5] | auVar205[7],
                                    CONCAT16(auVar199[5] | auVar130[4] | auVar205[6],
                                             CONCAT15(auVar199[4] | auVar205[5],
                                                      CONCAT14(auVar205[4],
                                                               CONCAT13(auVar199[2] | auVar130[1] |
                                                                        auVar205[3],
                                                                        CONCAT12(auVar199[1] |
                                                                                 auVar130[0] |
                                                                                 auVar205[2],
                                                                                 CONCAT11(auVar199[0
                                                  ] | auVar205[1],auVar205[0])))))));
                      auVar120[8] = auVar205[8];
                      auVar120[9] = auVar199[8] | auVar205[9];
                      auVar120[10] = auVar199[9] | auVar130[8] | auVar205[10];
                      auVar120[0xb] = auVar199[10] | auVar130[9] | auVar205[0xb];
                      auVar126[0xc] = auVar205[0xc];
                      auVar126._0_12_ = auVar120;
                      auVar126[0xd] = auVar199[0xc] | auVar205[0xd];
                      auVar126[0xe] = auVar199[0xd] | auVar130[0xc] | auVar205[0xe];
                      auVar126[0xf] = auVar199[0xe] | auVar130[0xd] | auVar205[0xf];
                      auVar158._0_8_ =
                           CONCAT17(auVar129[6] | auVar115[5] | auVar176[7],
                                    CONCAT16(auVar129[5] | auVar115[4] | auVar176[6],
                                             CONCAT15(auVar129[4] | auVar176[5],
                                                      CONCAT14(auVar176[4],
                                                               CONCAT13(auVar129[2] | auVar115[1] |
                                                                        auVar176[3],
                                                                        CONCAT12(auVar129[1] |
                                                                                 auVar115[0] |
                                                                                 auVar176[2],
                                                                                 CONCAT11(auVar129[0
                                                  ] | auVar176[1],auVar176[0])))))));
                      auVar158[8] = auVar176[8];
                      auVar158[9] = auVar129[8] | auVar176[9];
                      auVar158[10] = auVar129[9] | auVar115[8] | auVar176[10];
                      auVar158[0xb] = auVar129[10] | auVar115[9] | auVar176[0xb];
                      auVar128[0xc] = auVar176[0xc];
                      auVar128._0_12_ = auVar158;
                      auVar128[0xd] = auVar129[0xc] | auVar176[0xd];
                      auVar128[0xe] = auVar129[0xd] | auVar115[0xc] | auVar176[0xe];
                      auVar128[0xf] = auVar129[0xe] | auVar115[0xd] | auVar176[0xf];
                      auVar78._0_8_ =
                           CONCAT17(auVar148[6] | auVar138[5] | auVar74[7],
                                    CONCAT16(auVar148[5] | auVar138[4] | auVar74[6],
                                             CONCAT15(auVar148[4] | auVar74[5],
                                                      CONCAT14(auVar74[4],
                                                               CONCAT13(auVar148[2] | auVar138[1] |
                                                                        auVar74[3],
                                                                        CONCAT12(auVar148[1] |
                                                                                 auVar138[0] |
                                                                                 auVar74[2],
                                                                                 CONCAT11(auVar148[0
                                                  ] | auVar74[1],auVar74[0])))))));
                      auVar78[8] = auVar74[8];
                      auVar78[9] = auVar148[8] | auVar74[9];
                      auVar78[10] = auVar148[9] | auVar138[8] | auVar74[10];
                      auVar78[0xb] = auVar148[10] | auVar138[9] | auVar74[0xb];
                      auVar84[0xc] = auVar74[0xc];
                      auVar84._0_12_ = auVar78;
                      auVar84[0xd] = auVar148[0xc] | auVar74[0xd];
                      auVar84[0xe] = auVar148[0xd] | auVar138[0xc] | auVar74[0xe];
                      auVar84[0xf] = auVar148[0xe] | auVar138[0xd] | auVar74[0xf];
                      auVar62._0_8_ =
                           CONCAT17(auVar170[6] | auVar161[5] | auVar69[7],
                                    CONCAT16(auVar170[5] | auVar161[4] | auVar69[6],
                                             CONCAT15(auVar170[4] | auVar69[5],
                                                      CONCAT14(auVar69[4],
                                                               CONCAT13(auVar170[2] | auVar161[1] |
                                                                        auVar69[3],
                                                                        CONCAT12(auVar170[1] |
                                                                                 auVar161[0] |
                                                                                 auVar69[2],
                                                                                 CONCAT11(auVar170[0
                                                  ] | auVar69[1],auVar69[0])))))));
                      auVar62[8] = auVar69[8];
                      auVar62[9] = auVar170[8] | auVar69[9];
                      auVar62[10] = auVar170[9] | auVar161[8] | auVar69[10];
                      auVar62[0xb] = auVar170[10] | auVar161[9] | auVar69[0xb];
                      auVar70[0xc] = auVar69[0xc];
                      auVar70._0_12_ = auVar62;
                      auVar70[0xd] = auVar170[0xc] | auVar69[0xd];
                      auVar70[0xe] = auVar170[0xd] | auVar161[0xc] | auVar69[0xe];
                      auVar70[0xf] = auVar170[0xe] | auVar161[0xd] | auVar69[0xf];
                      auVar137._0_4_ = (int)(short)-(auVar105[0xc] < '\0');
                      auVar137._4_4_ = (int)(short)-(auVar105[0xd] < '\0');
                      auVar137._8_4_ = (int)(short)-(auVar105[0xe] < '\0');
                      auVar137._12_4_ = (int)(short)-(auVar105[0xf] < '\0');
                      auVar147._0_8_ =
                           CONCAT44((int)(short)-(auVar105[9] < '\0'),
                                    (int)(short)-(auVar105[8] < '\0'));
                      auVar147._8_4_ = (int)(short)-(auVar105[10] < '\0');
                      auVar147._12_4_ = (int)(short)-(auVar105[0xb] < '\0');
                      auVar185._0_4_ = (int)(short)-(auVar105[4] < '\0');
                      auVar185._4_4_ = (int)(short)-(auVar105[5] < '\0');
                      auVar185._8_4_ = (int)(short)-(auVar105[6] < '\0');
                      auVar185._12_4_ = (int)(short)-(auVar105[7] < '\0');
                      auVar114._0_4_ = (int)(short)-(auVar105[0] < '\0');
                      auVar114._4_4_ = (int)(short)-(auVar105[1] < '\0');
                      auVar114._8_4_ = (int)(short)-(auVar105[2] < '\0');
                      auVar114._12_4_ = (int)(short)-(auVar105[3] < '\0');
                      auVar106._0_8_ = auVar120._0_8_ | 0xff000000ff000000;
                      auVar106._8_4_ = auVar120._8_4_ | 0xff000000;
                      auVar106._12_4_ = auVar126._12_4_ | 0xff000000;
                      auVar169._0_8_ = auVar158._0_8_ | 0xff000000ff000000;
                      auVar169._8_4_ = auVar158._8_4_ | 0xff000000;
                      auVar169._12_4_ = auVar128._12_4_ | 0xff000000;
                      auVar175._0_8_ = auVar78._0_8_ | 0xff000000ff000000;
                      auVar175._8_4_ = auVar78._8_4_ | 0xff000000;
                      auVar175._12_4_ = auVar84._12_4_ | 0xff000000;
                      auVar194._0_8_ = auVar62._0_8_ | 0xff000000ff000000;
                      auVar194._8_4_ = auVar62._8_4_ | 0xff000000;
                      auVar194._12_4_ = auVar70._12_4_ | 0xff000000;
                      auVar106 = auVar106 ^ (auVar106 ^ auVar126) & ~auVar137;
                      auVar127._8_8_ = auVar147._8_8_;
                      auVar127._0_8_ = auVar147._0_8_;
                      auVar84 = auVar84 ^ (auVar84 ^ auVar175) & auVar185;
                      auVar70 = auVar70 ^ (auVar70 ^ auVar194) & auVar114;
                      auVar128 = auVar128 ^ (auVar128 ^ auVar169) & auVar127;
                      *(long *)(puVar42 + lVar52 + 0x1b38) = auVar106._8_8_;
                      *(long *)(puVar42 + lVar52 + 0x1b30) = auVar106._0_8_;
                      *(long *)(puVar42 + lVar52 + 0x1b18) = auVar84._8_8_;
                      *(long *)(puVar42 + lVar52 + 0x1b10) = auVar84._0_8_;
                      *(long *)(puVar42 + lVar52 + 0x1b08) = auVar70._8_8_;
                      *(long *)(puVar42 + lVar52 + 0x1b00) = auVar70._0_8_;
                      *(long *)(puVar42 + lVar52 + 0x1b28) = auVar128._8_8_;
                      *(long *)(puVar42 + lVar52 + 0x1b20) = auVar128._0_8_;
                      lVar52 = lVar41;
                    } while (lVar41 != 0);
                  }
                  else {
                    auVar74 = *(undefined1 (*) [16])(puVar33 + -0x1320);
                    auVar69 = *(undefined1 (*) [16])(puVar33 + -0x1310);
                    puVar35 = puVar33 + 0x5970;
                    lVar52 = -0x1b00;
                    do {
                      auVar71[0] = *puVar35;
                      bVar75 = puVar35[1];
                      auVar71[1] = puVar35[2];
                      bVar88 = puVar35[3];
                      auVar71[2] = puVar35[4];
                      bVar89 = puVar35[5];
                      auVar71[3] = puVar35[6];
                      bVar90 = puVar35[7];
                      auVar71[4] = puVar35[8];
                      bVar91 = puVar35[9];
                      auVar71[5] = puVar35[10];
                      bVar92 = puVar35[0xb];
                      auVar71[6] = puVar35[0xc];
                      bVar93 = puVar35[0xd];
                      auVar71[7] = puVar35[0xe];
                      pbVar50 = puVar35 + 0xf;
                      auVar71[8] = puVar35[0x10];
                      bVar94 = puVar35[0x11];
                      auVar71[9] = puVar35[0x12];
                      bVar95 = puVar35[0x13];
                      auVar71[10] = puVar35[0x14];
                      bVar96 = puVar35[0x15];
                      auVar71[0xb] = puVar35[0x16];
                      pbVar36 = puVar35 + 0x17;
                      auVar71[0xc] = puVar35[0x18];
                      bVar97 = puVar35[0x19];
                      auVar71[0xd] = puVar35[0x1a];
                      bVar98 = puVar35[0x1b];
                      auVar71[0xe] = puVar35[0x1c];
                      bVar99 = puVar35[0x1d];
                      auVar71[0xf] = puVar35[0x1e];
                      bVar100 = puVar35[0x1f];
                      puVar35 = puVar35 + 0x20;
                      puVar42 = puVar33 + -0x1290;
                      lVar41 = lVar52 + 0x40;
                      auVar115 = a64_TBL(ZEXT816(0),auVar71,auVar69);
                      auVar129 = a64_TBL(ZEXT816(0),auVar71,auVar74);
                      auVar199 = a64_TBL(ZEXT816(0),auVar71,_DAT_0020a230);
                      auVar130 = a64_TBL(ZEXT816(0),auVar71,_DAT_00208900);
                      auVar107._0_8_ =
                           CONCAT17((byte)((short)(char)bVar95 >> 0xf) | auVar129[7],
                                    CONCAT16((char)bVar95 >> 7 | auVar129[6],
                                             CONCAT15(bVar95 | auVar129[5],
                                                      CONCAT14(auVar129[4],
                                                               CONCAT13((byte)((short)(char)bVar94
                                                                              >> 0xf) | auVar129[3],
                                                                        CONCAT12((char)bVar94 >> 7 |
                                                                                 auVar129[2],
                                                                                 CONCAT11(bVar94 | 
                                                  auVar129[1],auVar129[0])))))));
                      auVar107[8] = auVar129[8];
                      auVar107[9] = bVar96 | auVar129[9];
                      auVar107[10] = (char)bVar96 >> 7 | auVar129[10];
                      auVar107[0xb] = (byte)((short)(char)bVar96 >> 0xf) | auVar129[0xb];
                      auVar107[0xc] = auVar129[0xc];
                      auVar107[0xd] = *pbVar36 | auVar129[0xd];
                      bVar94 = (char)*pbVar36 >> 7;
                      auVar107[0xe] = bVar94 | auVar129[0xe];
                      auVar107[0xf] = bVar94 | auVar129[0xf];
                      auVar85._0_8_ =
                           CONCAT17((byte)((short)(char)bVar92 >> 0xf) | auVar199[7],
                                    CONCAT16((char)bVar92 >> 7 | auVar199[6],
                                             CONCAT15(bVar92 | auVar199[5],
                                                      CONCAT14(auVar199[4],
                                                               CONCAT13((byte)((short)(char)bVar91
                                                                              >> 0xf) | auVar199[3],
                                                                        CONCAT12((char)bVar91 >> 7 |
                                                                                 auVar199[2],
                                                                                 CONCAT11(bVar91 | 
                                                  auVar199[1],auVar199[0])))))));
                      auVar85[8] = auVar199[8];
                      auVar85[9] = bVar93 | auVar199[9];
                      auVar85[10] = (char)bVar93 >> 7 | auVar199[10];
                      auVar85[0xb] = (byte)((short)(char)bVar93 >> 0xf) | auVar199[0xb];
                      auVar85[0xc] = auVar199[0xc];
                      auVar85[0xd] = *pbVar50 | auVar199[0xd];
                      bVar91 = (char)*pbVar50 >> 7;
                      auVar85[0xe] = bVar91 | auVar199[0xe];
                      auVar85[0xf] = bVar91 | auVar199[0xf];
                      auVar72._0_8_ =
                           CONCAT17((byte)((short)(char)bVar88 >> 0xf) | auVar130[7],
                                    CONCAT16((char)bVar88 >> 7 | auVar130[6],
                                             CONCAT15(bVar88 | auVar130[5],
                                                      CONCAT14(auVar130[4],
                                                               CONCAT13((byte)((short)(char)bVar75
                                                                              >> 0xf) | auVar130[3],
                                                                        CONCAT12((char)bVar75 >> 7 |
                                                                                 auVar130[2],
                                                                                 CONCAT11(bVar75 | 
                                                  auVar130[1],auVar130[0])))))));
                      auVar72[8] = auVar130[8];
                      auVar72[9] = bVar89 | auVar130[9];
                      auVar72[10] = (char)bVar89 >> 7 | auVar130[10];
                      auVar72[0xb] = (byte)((short)(char)bVar89 >> 0xf) | auVar130[0xb];
                      auVar72[0xc] = auVar130[0xc];
                      auVar72[0xd] = bVar90 | auVar130[0xd];
                      auVar72[0xe] = (char)bVar90 >> 7 | auVar130[0xe];
                      auVar72[0xf] = (byte)((short)(char)bVar90 >> 0xf) | auVar130[0xf];
                      puVar42[lVar52 + 0x1b38] = auVar115[8];
                      puVar42[lVar52 + 0x1b39] = bVar99 | auVar115[9];
                      puVar42[lVar52 + 0x1b3a] = (char)bVar99 >> 7 | auVar115[10];
                      puVar42[lVar52 + 0x1b3b] = (byte)((short)(char)bVar99 >> 0xf) | auVar115[0xb];
                      puVar42[lVar52 + 0x1b3c] = auVar115[0xc];
                      puVar42[lVar52 + 0x1b3d] = bVar100 | auVar115[0xd];
                      puVar42[lVar52 + 0x1b3e] = (char)bVar100 >> 7 | auVar115[0xe];
                      puVar42[lVar52 + 0x1b3f] = (byte)((short)(char)bVar100 >> 0xf) | auVar115[0xf]
                      ;
                      puVar42[lVar52 + 0x1b30] = auVar115[0];
                      puVar42[lVar52 + 0x1b31] = bVar97 | auVar115[1];
                      puVar42[lVar52 + 0x1b32] = (char)bVar97 >> 7 | auVar115[2];
                      puVar42[lVar52 + 0x1b33] = (byte)((short)(char)bVar97 >> 0xf) | auVar115[3];
                      puVar42[lVar52 + 0x1b34] = auVar115[4];
                      puVar42[lVar52 + 0x1b35] = bVar98 | auVar115[5];
                      puVar42[lVar52 + 0x1b36] = (char)bVar98 >> 7 | auVar115[6];
                      puVar42[lVar52 + 0x1b37] = (byte)((short)(char)bVar98 >> 0xf) | auVar115[7];
                      *(long *)(puVar42 + lVar52 + 0x1b28) = auVar107._8_8_;
                      *(undefined8 *)(puVar42 + lVar52 + 0x1b20) = auVar107._0_8_;
                      *(long *)(puVar42 + lVar52 + 0x1b18) = auVar85._8_8_;
                      *(undefined8 *)(puVar42 + lVar52 + 0x1b10) = auVar85._0_8_;
                      *(long *)(puVar42 + lVar52 + 0x1b08) = auVar72._8_8_;
                      *(undefined8 *)(puVar42 + lVar52 + 0x1b00) = auVar72._0_8_;
                      lVar52 = lVar41;
                    } while (lVar41 != 0);
                  }
                  iVar39 = (*DAT_01043e48)(DAT_0104ab38,puVar42,0x360,
                                           *(long *)(puVar33 + -0x12f0) + (long)(int)uVar49,
                                           DAT_0104aaf8);
                  uVar49 = iVar39 + uVar49;
                  uVar38 = uVar38 - *(int *)(puVar33 + -0x12cc);
                  uVar54 = uVar54 + *(long *)(puVar33 + -0x12d8);
                } while (*(int *)(puVar33 + -0x12cc) <= (int)uVar38);
              }
              *(undefined4 *)(puVar33 + -0x12a8) = 0x4e6;
              *(char **)(puVar33 + -0x12a0) =
                   "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
              *(char **)(puVar33 + -0x1298) = "a2dp_ssc_encode_frames_on_dual_play";
              *(ulong *)(puVar33 + 0x8f70) = (ulong)uVar49;
              *(undefined8 *)(puVar33 + -0x12c0) = 1;
              *(undefined8 *)(puVar33 + 0x8f80) = 3;
              *(undefined8 *)(puVar33 + 0x8f78) = 0;
              *(undefined1 **)(puVar33 + -0x12b8) = auStack_100;
              *(undefined8 *)(puVar33 + -0x12b0) = 3;
              bluetooth::log_internal::vlog
                        (2,"a2dp_vendor_ssc_encoder",puVar33 + -0x12a8,
                         "SSC output_pos_2nd : [ {} ]!!!",0x1e,puVar33 + -0x12c0);
              lVar52 = *(long *)(puVar33 + -0x1338);
              lVar41 = *(long *)(puVar33 + -0x1330);
              bVar34 = 0 < (int)uVar49;
              *(short *)(lVar41 + 2) = (short)uVar49;
              DAT_01043e68 = DAT_01043e68 + 1;
              *(int *)(lVar41 + 8) = DAT_01043e68;
              *(ushort *)(lVar41 + 6) = *(ushort *)(lVar41 + 6) | 0x100;
              uVar49 = *(uint *)(puVar33 + -0x1374);
            }
            if (((0 < (int)uVar46) && (DAT_01043e80 == '\x18')) && (uVar46 % 6 != 0)) {
              uVar38 = 6 - uVar46 % 6;
              iVar39 = (*DAT_01043e50)(&DAT_0104aae4,(ulong)uVar38);
              *(undefined4 *)(puVar33 + -0x12a8) = 0x4f3;
              DAT_0104aaf0 = uVar38 - iVar39;
              *(char **)(puVar33 + -0x12a0) =
                   "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
              *(char **)(puVar33 + -0x1298) = "a2dp_ssc_encode_frames_on_dual_play";
              *(ulong *)(puVar33 + 0x8f90) = (ulong)DAT_0104aaf0;
              *(ulong *)(puVar33 + 0x8f70) = (ulong)(iVar39 + uVar46);
              *(undefined8 *)(puVar33 + -0x12c0) = 3;
              *(undefined8 *)(puVar33 + 0x8f78) = 0;
              *(undefined8 *)(puVar33 + 0x8f88) = 0;
              *(ulong *)(puVar33 + 0x8f80) = (ulong)uVar38;
              *(undefined8 *)(puVar33 + 0x8fa0) = 0xc63;
              *(undefined8 *)(puVar33 + 0x8f98) = 0;
              *(undefined1 **)(puVar33 + -0x12b8) = auStack_100;
              *(undefined8 *)(puVar33 + -0x12b0) = 0xc63;
              bluetooth::log_internal::vlog
                        (6,"a2dp_vendor_ssc_encoder",puVar33 + -0x12a8,
                         "Couldn\'t read PCM, discarded {}, read_more before {}, read_more after {}"
                         ,0x48,puVar33 + -0x12c0);
              uVar49 = *(uint *)(puVar33 + -0x1374);
              lVar52 = *(long *)(puVar33 + -0x1338);
            }
            if ((uVar49 & 1) == 0 && !bVar34) {
              *(undefined4 *)(puVar33 + 0x8f70) = 0x50c;
              *(char **)(puVar33 + 0x8f78) =
                   "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
              *(char **)(puVar33 + 0x8f80) = "a2dp_ssc_encode_frames_on_dual_play";
              *(undefined8 *)(puVar33 + -0x12a8) = 0;
              bluetooth::log_internal::vlog
                        (6,"a2dp_vendor_ssc_encoder",auStack_100,"output_pos 0",0xc,
                         puVar33 + -0x12a8);
              __ptr = *(void **)(puVar33 + -0x1338);
              __ptr_00 = *(void **)(puVar33 + -0x1330);
              goto joined_r0x00a95964;
            }
            lVar41 = *(long *)(puVar33 + -0x1330);
            if ((lVar52 != 0) &&
               (uVar54 = (*DAT_01043e58)(lVar52,1,*(undefined4 *)(puVar33 + -0x1348)),
               (uVar54 & 1) == 0)) {
              *(undefined4 *)(puVar33 + 0x8f70) = 0x4fd;
              *(char **)(puVar33 + 0x8f78) =
                   "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
              *(char **)(puVar33 + 0x8f80) = "a2dp_ssc_encode_frames_on_dual_play";
              *(undefined8 *)(puVar33 + -0x12a8) = 0;
              bluetooth::log_internal::vlog
                        (6,"a2dp_vendor_ssc_encoder",auStack_100,"enqueue failed",0xe,
                         puVar33 + -0x12a8);
            }
            if ((lVar41 != 0) &&
               (uVar54 = (*DAT_01043e58)(lVar41,1,*(undefined4 *)(puVar33 + -0x1348)),
               (uVar54 & 1) == 0)) {
              *(undefined4 *)(puVar33 + 0x8f70) = 0x503;
              *(char **)(puVar33 + 0x8f78) =
                   "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
              *(char **)(puVar33 + 0x8f80) = "a2dp_ssc_encode_frames_on_dual_play";
              *(undefined8 *)(puVar33 + -0x12a8) = 0;
              bluetooth::log_internal::vlog
                        (6,"a2dp_vendor_ssc_encoder",auStack_100,"enqueue for 2nd failed",0x16,
                         puVar33 + -0x12a8);
            }
            lVar52 = *(long *)(puVar33 + -0x12c8);
            if (*(short *)(lVar52 + 10) != 0) {
              *(short *)(lVar52 + 10) = *(short *)(lVar52 + 10) + -1;
            }
            uVar45 = *(undefined8 *)(puVar33 + -0x1350);
            *(ulong *)(puVar33 + -0x1350) = (ulong)((int)uVar45 - 1U);
          } while (((int)uVar45 - 1U & 0xff) != 0);
        }
      }
      else {
        *(undefined4 *)(puVar33 + -0x1290) = 0x334;
        *(char **)(puVar33 + -0x1288) =
             "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
        *(char **)(puVar33 + -0x1280) = "a2dp_vendor_ssc_send_frames";
        *(undefined8 *)(puVar33 + 0x5970) = 0;
        bluetooth::log_internal::vlog
                  (5,"a2dp_vendor_ssc_encoder",puVar33 + -0x1290,
                   "### offload is enabled, discarded frame ###",0x2b,puVar33 + 0x5970);
      }
      lVar52 = *(long *)(puVar33 + -0x1340);
      goto LAB_00a965e8;
    }
  }
  lVar52 = *(long *)(puVar33 + -0x1340);
  if ((((DAT_0109f1b4 & 1) == 0) && (DAT_0104aae0 == 0)) && ((pbVar50[0x2e] != 1 || (1 < *pbVar50)))
     ) {
    uVar48 = 0xb40;
    if (DAT_01043e80 != '\x18') {
      uVar48 = 0x6e4;
    }
    uVar6 = 0x1e00;
    if (iVar39 != 96000) {
      uVar6 = uVar48;
    }
    if (0 < (int)DAT_0104aaf0) {
      iVar39 = 0x1f5;
      do {
        iVar39 = iVar39 + -1;
        if (iVar39 == 0) {
          *(undefined4 *)(puVar33 + -0x1290) = 0x327;
          *(char **)(puVar33 + -0x1288) =
               "packages/modules/Bluetooth/system/stack/a2dp/a2dp_vendor_ssc_encoder.cc";
          *(char **)(puVar33 + -0x1280) = "a2dp_vendor_ssc_send_frames";
          *(undefined8 *)(puVar33 + 0x5970) = 0;
          bluetooth::log_internal::vlog
                    (6,"a2dp_vendor_ssc_encoder",puVar33 + -0x1290,"Cannot read PCM at all, break!!"
                     ,0x1f,puVar33 + 0x5970);
          break;
        }
        iVar37 = (*DAT_01043e50)(&DAT_0104aae4);
        DAT_0104aaf0 = DAT_0104aaf0 - iVar37;
      } while (0 < (int)DAT_0104aaf0);
    }
    DAT_0104aae0 = (*DAT_01043e50)(&DAT_01043ee0,uVar6);
  }
LAB_00a965e8:
  if (*(long *)(lVar52 + 0x28) != local_88) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}


/* ==== btm_brcm_enable_dbfwplus_linkloss_cmpl @ 00a977d4 size 412 :: [BTCORE][DBFW+]btm_brcm_enable_dbfwpluslinklosscmpl status = 0x{:02x} | [BTCORE][DBFW+]btm_brcm_enable_dbfwpluslinklosscmpl: p_params->opcode:0x{:04x}, param_len:0x{:04x} */

/* btm_brcm_enable_dbfwplus_linkloss_cmpl(tBTM_VSC_CMPL*) */

void btm_brcm_enable_dbfwplus_linkloss_cmpl(tBTM_VSC_CMPL *param_1)

{
  byte bVar1;
  long lVar2;
  char *pcVar3;
  undefined8 uVar4;
  undefined8 *in_x18;
  byte *pbVar5;
  undefined8 unaff_x30;
  undefined8 local_c0;
  ulong *puStack_b8;
  undefined8 local_b0;
  undefined8 local_a8;
  char *local_a0;
  char *pcStack_98;
  ulong local_90;
  char *local_88;
  char *local_80;
  undefined8 local_78;
  undefined8 uStack_70;
  long local_58;
  
  *in_x18 = unaff_x30;
  lVar2 = tpidr_el0;
  local_58 = *(long *)(lVar2 + 0x28);
  local_a8._0_4_ = 0x1a3;
  local_90 = (ulong)*(ushort *)param_1;
  local_80 = (char *)(ulong)*(ushort *)(param_1 + 2);
  pbVar5 = *(byte **)(param_1 + 8);
  local_88 = (char *)0x0;
  local_a0 = "packages/modules/Bluetooth/system/stack/acl/btm_acl.cc";
  pcStack_98 = "btm_brcm_enable_dbfwplus_linkloss_cmpl";
  local_78 = 0;
  uStack_70 = 0xc6;
  local_c0 = 2;
  local_b0 = 0xc6;
  puStack_b8 = &local_90;
  bluetooth::log_internal::vlog
            (6,"btm_acl",&local_a8,
             "[BTCORE][DBFW+]btm_brcm_enable_dbfwpluslinklosscmpl: p_params->opcode:0x{:04x}, param_len:0x{:04x}"
             ,0x62,&local_c0);
  bVar1 = *pbVar5;
  local_90 = (ulong)bVar1;
  local_a8 = CONCAT44(local_a8._4_4_,0x1a6);
  local_a0 = "packages/modules/Bluetooth/system/stack/acl/btm_acl.cc";
  pcStack_98 = "btm_brcm_enable_dbfwplus_linkloss_cmpl";
  local_88 = (char *)0x0;
  local_80 = (char *)0x6;
  local_c0 = 1;
  local_b0 = 6;
  puStack_b8 = &local_90;
  bluetooth::log_internal::vlog
            (6,"btm_acl",&local_a8,
             "[BTCORE][DBFW+]btm_brcm_enable_dbfwpluslinklosscmpl status = 0x{:02x}",0x45,&local_c0)
  ;
  if (*(short *)param_1 == -0x20f) {
    if (bVar1 == 0) {
      local_90 = CONCAT44(local_90._4_4_,0x1aa);
      pcVar3 = "[BTCORE][DBFW+]success: enable dbfwpluslinkloss callback";
      uVar4 = 0x38;
    }
    else {
      pcVar3 = "[BTCORE][DBFW+]failed: enable dbfwpluslinkloss callback";
      uVar4 = 0x37;
      local_90 = CONCAT44(local_90._4_4_,0x1ac);
    }
    local_80 = "btm_brcm_enable_dbfwplus_linkloss_cmpl";
    local_88 = "packages/modules/Bluetooth/system/stack/acl/btm_acl.cc";
    local_a8 = 0;
    bluetooth::log_internal::vlog(6,"btm_acl",&local_90,pcVar3,uVar4,&local_a8);
  }
  if (*(long *)(lVar2 + 0x28) == local_58) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== ToString @ 00add4e8 size 1020 :: LeReadPeerResolvableAddressComplete {  */

/* bluetooth::hci::LeReadPeerResolvableAddressCompleteView::ToString() const */

void bluetooth::hci::LeReadPeerResolvableAddressCompleteView::ToString(void)

{
  long lVar1;
  char *pcVar2;
  LeReadPeerResolvableAddressCompleteView *in_x0;
  ostream *poVar3;
  undefined8 uVar4;
  void *__src;
  ulong *in_x8;
  ulong uVar5;
  long *plVar6;
  undefined8 *in_x18;
  undefined1 *__dest;
  size_t __n;
  undefined8 unaff_x30;
  byte local_1c8;
  undefined7 uStack_1c7;
  ulong local_1c0;
  char *local_1b8;
  undefined1 local_1ac [4];
  byte local_1a8;
  undefined7 uStack_1a7;
  ulong local_1a0;
  char *local_198;
  undefined4 local_190;
  undefined2 local_18c;
  undefined **local_188;
  undefined8 local_180;
  undefined **local_178;
  undefined **local_170;
  undefined8 uStack_168;
  long local_160 [8];
  void *local_120;
  ulong uStack_118;
  undefined8 local_110;
  undefined **ppuStack_108;
  undefined8 local_100;
  undefined8 uStack_f8;
  undefined8 local_f0;
  undefined8 uStack_e8;
  undefined8 local_e0;
  undefined8 uStack_d8;
  undefined8 local_d0;
  undefined8 uStack_c8;
  undefined8 local_c0;
  undefined8 uStack_b8;
  undefined8 local_b0;
  undefined8 uStack_a8;
  undefined8 local_a0;
  undefined8 uStack_98;
  undefined8 local_90;
  undefined8 uStack_88;
  undefined8 local_80;
  undefined8 uStack_78;
  long local_70;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_70 = *(long *)(lVar1 + 0x28);
  uStack_78 = 0;
  local_80 = 0;
  local_110 = 0;
  uStack_88 = 0;
  local_90 = 0;
  uStack_98 = 0;
  local_a0 = 0;
  uStack_a8 = 0;
  local_b0 = 0;
  uStack_b8 = 0;
  local_c0 = 0;
  uStack_c8 = 0;
  local_d0 = 0;
  uStack_d8 = 0;
  local_e0 = 0;
  uStack_e8 = 0;
  local_f0 = 0;
  uStack_f8 = 0;
  local_100 = 0;
  uStack_118 = 0;
  local_120 = (void *)0x0;
  local_160[7] = 0;
  local_160[6] = 0;
  local_160[5] = 0;
  local_160[4] = 0;
  local_160[3] = 0;
  local_160[2] = 0;
  local_160[1] = 0;
  local_160[0] = 0;
  uStack_168 = 0;
  local_170 = (undefined **)0x0;
  local_188 = &PTR__istream_00f68ae0;
  ppuStack_108 = &PTR__istream_00f68b08;
  local_180 = 0;
  local_178 = &PTR__stringstream_00f689c8;
  std::ios_base::init((ios_base *)&ppuStack_108,(stringbuf *)&local_170);
  local_80 = 0;
                    /* WARNING: Ignoring partial resolution of indirect */
  uStack_78._0_4_ = 0xffffffff;
  local_188 = &PTR__stringstream_00f689a0;
  local_170 = &PTR__streambuf_00f68750;
  local_178 = &PTR__stringstream_00f689c8;
  ppuStack_108 = &PTR__stringstream_00f689f0;
  std::locale::locale((locale *)&uStack_168);
  local_160[5] = 0;
  local_160[4] = 0;
  local_160[1] = 0;
  local_160[0] = 0;
  local_160[3] = 0;
  local_160[2] = 0;
  local_160[7] = 0;
  local_160[6] = 0;
  local_170 = &PTR__stringbuf_00f687d0;
  uStack_118 = 0;
  local_120 = (void *)0x0;
  local_110 = CONCAT44(local_110._4_4_,0x18);
  std::stringbuf::__init_buf_ptrs_abi_nn220000_((stringbuf *)&local_170);
  *(uint *)((long)&local_170 + (long)local_178[-3]) =
       *(uint *)((long)&local_170 + (long)local_178[-3]) | 0x200;
  *(uint *)((long)&local_170 + (long)local_178[-3]) =
       *(uint *)((long)&local_170 + (long)local_178[-3]) & 0xffffffb5 | 8;
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
            ((ostream *)&local_178,"LeReadPeerResolvableAddressComplete { ",0x26);
  poVar3 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                     ((ostream *)&local_178,"",0);
  poVar3 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                     (poVar3,"status = ",9);
  local_1ac[0] = GetStatus(in_x0);
  ErrorCodeText(&local_1a8,local_1ac);
  pcVar2 = local_198;
  if ((local_1a8 & 1) == 0) {
    local_1a0 = (ulong)(local_1a8 >> 1);
    pcVar2 = (char *)&uStack_1a7;
  }
  poVar3 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                     (poVar3,pcVar2,local_1a0);
  poVar3 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                     (poVar3,", peer_resolvable_address = ",0x1c);
  uVar4 = GetPeerResolvableAddress(in_x0);
  local_190 = (undefined4)uVar4;
  local_18c = (undefined2)((ulong)uVar4 >> 0x20);
  Address::_ToMaskedColonSepHexString((int)&local_190);
  pcVar2 = local_1b8;
  if ((local_1c8 & 1) == 0) {
    local_1c0 = (ulong)(local_1c8 >> 1);
    pcVar2 = (char *)&uStack_1c7;
  }
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>(poVar3,pcVar2,local_1c0);
  if ((local_1c8 & 1) != 0) {
    operator_delete(local_1b8,CONCAT71(uStack_1c7,local_1c8) & 0xfffffffffffffffe);
  }
  if ((local_1a8 & 1) != 0) {
    operator_delete(local_198,CONCAT71(uStack_1a7,local_1a8) & 0xfffffffffffffffe);
  }
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
            ((ostream *)&local_178," }",2);
  if (((uint)local_110 >> 4 & 1) == 0) {
    if (((uint)local_110 >> 3 & 1) != 0) {
      plVar6 = local_160;
      uVar5 = local_160[2];
      goto LAB_00add7e0;
    }
    __src = (void *)0x0;
    __n = 0;
  }
  else {
    if (uStack_118 < (ulong)local_160[4]) {
      uStack_118 = local_160[4];
    }
    plVar6 = local_160 + 3;
    uVar5 = uStack_118;
LAB_00add7e0:
    __src = (void *)*plVar6;
    __n = uVar5 - (long)__src;
    if (0xfffffffffffffff6 < __n) {
                    /* WARNING: Subroutine does not return */
      std::string::__throw_length_error_abi_nn220000_();
    }
    if (0x16 < __n) {
      uVar5 = 0x1a;
      if ((__n | 7) != 0x17) {
        uVar5 = (__n | 7) + 1;
      }
      __dest = (undefined1 *)FUN_00f62c00(uVar5);
      in_x8[1] = __n;
      in_x8[2] = (ulong)__dest;
      *in_x8 = uVar5 | 1;
      goto LAB_00add834;
    }
  }
  __dest = (undefined1 *)((long)in_x8 + 1);
  *(char *)in_x8 = (char)((int)__n << 1);
LAB_00add834:
  memmove(__dest,__src,__n);
  local_188 = &PTR__stringstream_00f689a0;
  __dest[__n] = 0;
  local_178 = &PTR__stringstream_00f689c8;
  ppuStack_108 = &PTR__stringstream_00f689f0;
  local_170 = &PTR__stringbuf_00f687d0;
  if ((local_160[6] & 1U) != 0) {
    operator_delete(local_120,local_160[6] & 0xfffffffffffffffe);
  }
  local_170 = &PTR__streambuf_00f68750;
  std::locale::~locale((locale *)&uStack_168);
  std::iostream::~iostream((iostream *)&local_188);
  std::ios::~ios((ios *)&ppuStack_108);
  if (*(long *)(lVar1 + 0x28) == local_70) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== ToString @ 00d4acc8 size 900 :: LeSetRandomAddressComplete {  */

/* bluetooth::hci::LeSetRandomAddressCompleteView::ToString() const */

void bluetooth::hci::LeSetRandomAddressCompleteView::ToString(void)

{
  long lVar1;
  char *pcVar2;
  LeSetRandomAddressCompleteView *in_x0;
  ostream *poVar3;
  void *__src;
  ulong *in_x8;
  ulong uVar4;
  long *plVar5;
  undefined8 *in_x18;
  undefined1 *__dest;
  size_t __n;
  undefined8 unaff_x30;
  undefined1 local_1a4 [4];
  byte local_1a0;
  undefined7 uStack_19f;
  ulong local_198;
  char *local_190;
  undefined **local_188;
  undefined8 local_180;
  undefined **local_178;
  undefined **local_170;
  undefined8 uStack_168;
  long local_160 [8];
  void *local_120;
  ulong uStack_118;
  undefined8 local_110;
  undefined **ppuStack_108;
  undefined8 local_100;
  undefined8 uStack_f8;
  undefined8 local_f0;
  undefined8 uStack_e8;
  undefined8 local_e0;
  undefined8 uStack_d8;
  undefined8 local_d0;
  undefined8 uStack_c8;
  undefined8 local_c0;
  undefined8 uStack_b8;
  undefined8 local_b0;
  undefined8 uStack_a8;
  undefined8 local_a0;
  undefined8 uStack_98;
  undefined8 local_90;
  undefined8 uStack_88;
  undefined8 local_80;
  undefined8 uStack_78;
  long local_70;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_70 = *(long *)(lVar1 + 0x28);
  uStack_78 = 0;
  local_80 = 0;
  local_110 = 0;
  uStack_88 = 0;
  local_90 = 0;
  uStack_98 = 0;
  local_a0 = 0;
  uStack_a8 = 0;
  local_b0 = 0;
  uStack_b8 = 0;
  local_c0 = 0;
  uStack_c8 = 0;
  local_d0 = 0;
  uStack_d8 = 0;
  local_e0 = 0;
  uStack_e8 = 0;
  local_f0 = 0;
  uStack_f8 = 0;
  local_100 = 0;
  uStack_118 = 0;
  local_120 = (void *)0x0;
  local_160[5] = 0;
  local_160[4] = 0;
  local_160[7] = 0;
  local_160[6] = 0;
  local_160[3] = 0;
  local_160[2] = 0;
  local_160[1] = 0;
  local_160[0] = 0;
  uStack_168 = 0;
  local_170 = (undefined **)0x0;
  local_188 = &PTR__istream_00f68ae0;
  ppuStack_108 = &PTR__istream_00f68b08;
  local_180 = 0;
  local_178 = &PTR__stringstream_00f689c8;
  std::ios_base::init((ios_base *)&ppuStack_108,(stringbuf *)&local_170);
  local_80 = 0;
                    /* WARNING: Ignoring partial resolution of indirect */
  uStack_78._0_4_ = 0xffffffff;
  local_188 = &PTR__stringstream_00f689a0;
  local_170 = &PTR__streambuf_00f68750;
  local_178 = &PTR__stringstream_00f689c8;
  ppuStack_108 = &PTR__stringstream_00f689f0;
  std::locale::locale((locale *)&uStack_168);
  local_160[5] = 0;
  local_160[4] = 0;
  local_160[1] = 0;
  local_160[0] = 0;
  local_160[3] = 0;
  local_160[2] = 0;
  local_160[7] = 0;
  local_160[6] = 0;
  local_170 = &PTR__stringbuf_00f687d0;
  uStack_118 = 0;
  local_120 = (void *)0x0;
  local_110 = CONCAT44(local_110._4_4_,0x18);
  std::stringbuf::__init_buf_ptrs_abi_nn220000_((stringbuf *)&local_170);
  *(uint *)((long)&local_170 + (long)local_178[-3]) =
       *(uint *)((long)&local_170 + (long)local_178[-3]) | 0x200;
  *(uint *)((long)&local_170 + (long)local_178[-3]) =
       *(uint *)((long)&local_170 + (long)local_178[-3]) & 0xffffffb5 | 8;
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
            ((ostream *)&local_178,"LeSetRandomAddressComplete { ",0x1d);
  poVar3 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                     ((ostream *)&local_178,"",0);
  poVar3 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                     (poVar3,"status = ",9);
  local_1a4[0] = GetStatus(in_x0);
  ErrorCodeText(&local_1a0,local_1a4);
  pcVar2 = local_190;
  if ((local_1a0 & 1) == 0) {
    local_198 = (ulong)(local_1a0 >> 1);
    pcVar2 = (char *)&uStack_19f;
  }
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>(poVar3,pcVar2,local_198);
  if ((local_1a0 & 1) != 0) {
    operator_delete(local_190,CONCAT71(uStack_19f,local_1a0) & 0xfffffffffffffffe);
  }
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
            ((ostream *)&local_178," }",2);
  if (((uint)local_110 >> 4 & 1) == 0) {
    if (((uint)local_110 >> 3 & 1) != 0) {
      plVar5 = local_160;
      uVar4 = local_160[2];
      goto LAB_00d4af48;
    }
    __src = (void *)0x0;
    __n = 0;
  }
  else {
    if (uStack_118 < (ulong)local_160[4]) {
      uStack_118 = local_160[4];
    }
    plVar5 = local_160 + 3;
    uVar4 = uStack_118;
LAB_00d4af48:
    __src = (void *)*plVar5;
    __n = uVar4 - (long)__src;
    if (0xfffffffffffffff6 < __n) {
                    /* WARNING: Subroutine does not return */
      std::string::__throw_length_error_abi_nn220000_();
    }
    if (0x16 < __n) {
      uVar4 = 0x1a;
      if ((__n | 7) != 0x17) {
        uVar4 = (__n | 7) + 1;
      }
      __dest = (undefined1 *)FUN_00f62c00(uVar4);
      in_x8[1] = __n;
      in_x8[2] = (ulong)__dest;
      *in_x8 = uVar4 | 1;
      goto LAB_00d4af9c;
    }
  }
  __dest = (undefined1 *)((long)in_x8 + 1);
  *(char *)in_x8 = (char)((int)__n << 1);
LAB_00d4af9c:
  memmove(__dest,__src,__n);
  local_188 = &PTR__stringstream_00f689a0;
  __dest[__n] = 0;
  local_178 = &PTR__stringstream_00f689c8;
  ppuStack_108 = &PTR__stringstream_00f689f0;
  local_170 = &PTR__stringbuf_00f687d0;
  if ((local_160[6] & 1U) != 0) {
    operator_delete(local_120,local_160[6] & 0xfffffffffffffffe);
  }
  local_170 = &PTR__streambuf_00f68750;
  std::locale::~locale((locale *)&uStack_168);
  std::iostream::~iostream((iostream *)&local_188);
  std::ios::~ios((ios *)&ppuStack_108);
  if (*(long *)(lVar1 + 0x28) == local_70) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== ToString @ 00d5c6c8 size 900 :: LeSetAdvertisingSetRandomAddressComplete {  */

/* bluetooth::hci::LeSetAdvertisingSetRandomAddressCompleteView::ToString() const */

void bluetooth::hci::LeSetAdvertisingSetRandomAddressCompleteView::ToString(void)

{
  long lVar1;
  char *pcVar2;
  LeSetAdvertisingSetRandomAddressCompleteView *in_x0;
  ostream *poVar3;
  void *__src;
  ulong *in_x8;
  ulong uVar4;
  long *plVar5;
  undefined8 *in_x18;
  undefined1 *__dest;
  size_t __n;
  undefined8 unaff_x30;
  undefined1 local_1a4 [4];
  byte local_1a0;
  undefined7 uStack_19f;
  ulong local_198;
  char *local_190;
  undefined **local_188;
  undefined8 local_180;
  undefined **local_178;
  undefined **local_170;
  undefined8 uStack_168;
  long local_160 [8];
  void *local_120;
  ulong uStack_118;
  undefined8 local_110;
  undefined **ppuStack_108;
  undefined8 local_100;
  undefined8 uStack_f8;
  undefined8 local_f0;
  undefined8 uStack_e8;
  undefined8 local_e0;
  undefined8 uStack_d8;
  undefined8 local_d0;
  undefined8 uStack_c8;
  undefined8 local_c0;
  undefined8 uStack_b8;
  undefined8 local_b0;
  undefined8 uStack_a8;
  undefined8 local_a0;
  undefined8 uStack_98;
  undefined8 local_90;
  undefined8 uStack_88;
  undefined8 local_80;
  undefined8 uStack_78;
  long local_70;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_70 = *(long *)(lVar1 + 0x28);
  uStack_78 = 0;
  local_80 = 0;
  local_110 = 0;
  uStack_88 = 0;
  local_90 = 0;
  uStack_98 = 0;
  local_a0 = 0;
  uStack_a8 = 0;
  local_b0 = 0;
  uStack_b8 = 0;
  local_c0 = 0;
  uStack_c8 = 0;
  local_d0 = 0;
  uStack_d8 = 0;
  local_e0 = 0;
  uStack_e8 = 0;
  local_f0 = 0;
  uStack_f8 = 0;
  local_100 = 0;
  uStack_118 = 0;
  local_120 = (void *)0x0;
  local_160[5] = 0;
  local_160[4] = 0;
  local_160[7] = 0;
  local_160[6] = 0;
  local_160[3] = 0;
  local_160[2] = 0;
  local_160[1] = 0;
  local_160[0] = 0;
  uStack_168 = 0;
  local_170 = (undefined **)0x0;
  local_188 = &PTR__istream_00f68ae0;
  ppuStack_108 = &PTR__istream_00f68b08;
  local_180 = 0;
  local_178 = &PTR__stringstream_00f689c8;
  std::ios_base::init((ios_base *)&ppuStack_108,(stringbuf *)&local_170);
  local_80 = 0;
                    /* WARNING: Ignoring partial resolution of indirect */
  uStack_78._0_4_ = 0xffffffff;
  local_188 = &PTR__stringstream_00f689a0;
  local_170 = &PTR__streambuf_00f68750;
  local_178 = &PTR__stringstream_00f689c8;
  ppuStack_108 = &PTR__stringstream_00f689f0;
  std::locale::locale((locale *)&uStack_168);
  local_160[5] = 0;
  local_160[4] = 0;
  local_160[1] = 0;
  local_160[0] = 0;
  local_160[3] = 0;
  local_160[2] = 0;
  local_160[7] = 0;
  local_160[6] = 0;
  local_170 = &PTR__stringbuf_00f687d0;
  uStack_118 = 0;
  local_120 = (void *)0x0;
  local_110 = CONCAT44(local_110._4_4_,0x18);
  std::stringbuf::__init_buf_ptrs_abi_nn220000_((stringbuf *)&local_170);
  *(uint *)((long)&local_170 + (long)local_178[-3]) =
       *(uint *)((long)&local_170 + (long)local_178[-3]) | 0x200;
  *(uint *)((long)&local_170 + (long)local_178[-3]) =
       *(uint *)((long)&local_170 + (long)local_178[-3]) & 0xffffffb5 | 8;
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
            ((ostream *)&local_178,"LeSetAdvertisingSetRandomAddressComplete { ",0x2b);
  poVar3 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                     ((ostream *)&local_178,"",0);
  poVar3 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                     (poVar3,"status = ",9);
  local_1a4[0] = GetStatus(in_x0);
  ErrorCodeText(&local_1a0,local_1a4);
  pcVar2 = local_190;
  if ((local_1a0 & 1) == 0) {
    local_198 = (ulong)(local_1a0 >> 1);
    pcVar2 = (char *)&uStack_19f;
  }
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>(poVar3,pcVar2,local_198);
  if ((local_1a0 & 1) != 0) {
    operator_delete(local_190,CONCAT71(uStack_19f,local_1a0) & 0xfffffffffffffffe);
  }
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
            ((ostream *)&local_178," }",2);
  if (((uint)local_110 >> 4 & 1) == 0) {
    if (((uint)local_110 >> 3 & 1) != 0) {
      plVar5 = local_160;
      uVar4 = local_160[2];
      goto LAB_00d5c948;
    }
    __src = (void *)0x0;
    __n = 0;
  }
  else {
    if (uStack_118 < (ulong)local_160[4]) {
      uStack_118 = local_160[4];
    }
    plVar5 = local_160 + 3;
    uVar4 = uStack_118;
LAB_00d5c948:
    __src = (void *)*plVar5;
    __n = uVar4 - (long)__src;
    if (0xfffffffffffffff6 < __n) {
                    /* WARNING: Subroutine does not return */
      std::string::__throw_length_error_abi_nn220000_();
    }
    if (0x16 < __n) {
      uVar4 = 0x1a;
      if ((__n | 7) != 0x17) {
        uVar4 = (__n | 7) + 1;
      }
      __dest = (undefined1 *)FUN_00f62c00(uVar4);
      in_x8[1] = __n;
      in_x8[2] = (ulong)__dest;
      *in_x8 = uVar4 | 1;
      goto LAB_00d5c99c;
    }
  }
  __dest = (undefined1 *)((long)in_x8 + 1);
  *(char *)in_x8 = (char)((int)__n << 1);
LAB_00d5c99c:
  memmove(__dest,__src,__n);
  local_188 = &PTR__stringstream_00f689a0;
  __dest[__n] = 0;
  local_178 = &PTR__stringstream_00f689c8;
  ppuStack_108 = &PTR__stringstream_00f689f0;
  local_170 = &PTR__stringbuf_00f687d0;
  if ((local_160[6] & 1U) != 0) {
    operator_delete(local_120,local_160[6] & 0xfffffffffffffffe);
  }
  local_170 = &PTR__streambuf_00f68750;
  std::locale::~locale((locale *)&uStack_168);
  std::iostream::~iostream((iostream *)&local_188);
  std::ios::~ios((ios *)&ppuStack_108);
  if (*(long *)(lVar1 + 0x28) == local_70) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


/* ==== ToString @ 00d88e38 size 940 :: LeAdvFilterBroadcasterAddressComplete {  */

/* bluetooth::hci::LeAdvFilterBroadcasterAddressCompleteView::ToString() const */

void bluetooth::hci::LeAdvFilterBroadcasterAddressCompleteView::ToString(void)

{
  long lVar1;
  char *pcVar2;
  uint uVar3;
  LeAdvFilterBroadcasterAddressCompleteView *in_x0;
  ostream *poVar4;
  void *__src;
  ulong *in_x8;
  ulong uVar5;
  long *plVar6;
  undefined8 *in_x18;
  undefined1 *__dest;
  size_t __n;
  undefined8 unaff_x30;
  undefined1 local_1a4 [4];
  byte local_1a0;
  undefined7 uStack_19f;
  ulong local_198;
  char *local_190;
  undefined **local_188;
  undefined8 local_180;
  undefined **local_178;
  undefined **local_170;
  undefined8 uStack_168;
  long local_160 [8];
  void *local_120;
  ulong uStack_118;
  undefined8 local_110;
  undefined **ppuStack_108;
  undefined8 local_100;
  undefined8 uStack_f8;
  undefined8 local_f0;
  undefined8 uStack_e8;
  undefined8 local_e0;
  undefined8 uStack_d8;
  undefined8 local_d0;
  undefined8 uStack_c8;
  undefined8 local_c0;
  undefined8 uStack_b8;
  undefined8 local_b0;
  undefined8 uStack_a8;
  undefined8 local_a0;
  undefined8 uStack_98;
  undefined8 local_90;
  undefined8 uStack_88;
  undefined8 local_80;
  undefined8 uStack_78;
  long local_70;
  
  *in_x18 = unaff_x30;
  lVar1 = tpidr_el0;
  local_70 = *(long *)(lVar1 + 0x28);
  uStack_78 = 0;
  local_80 = 0;
  local_110 = 0;
  uStack_88 = 0;
  local_90 = 0;
  uStack_98 = 0;
  local_a0 = 0;
  uStack_a8 = 0;
  local_b0 = 0;
  uStack_b8 = 0;
  local_c0 = 0;
  uStack_c8 = 0;
  local_d0 = 0;
  uStack_d8 = 0;
  local_e0 = 0;
  uStack_e8 = 0;
  local_f0 = 0;
  uStack_f8 = 0;
  local_100 = 0;
  uStack_118 = 0;
  local_120 = (void *)0x0;
  local_160[5] = 0;
  local_160[4] = 0;
  local_160[7] = 0;
  local_160[6] = 0;
  local_160[3] = 0;
  local_160[2] = 0;
  local_160[1] = 0;
  local_160[0] = 0;
  uStack_168 = 0;
  local_170 = (undefined **)0x0;
  local_188 = &PTR__istream_00f68ae0;
  ppuStack_108 = &PTR__istream_00f68b08;
  local_180 = 0;
  local_178 = &PTR__stringstream_00f689c8;
  std::ios_base::init((ios_base *)&ppuStack_108,(stringbuf *)&local_170);
  local_80 = 0;
                    /* WARNING: Ignoring partial resolution of indirect */
  uStack_78._0_4_ = 0xffffffff;
  local_188 = &PTR__stringstream_00f689a0;
  local_170 = &PTR__streambuf_00f68750;
  local_178 = &PTR__stringstream_00f689c8;
  ppuStack_108 = &PTR__stringstream_00f689f0;
  std::locale::locale((locale *)&uStack_168);
  local_160[5] = 0;
  local_160[4] = 0;
  local_160[1] = 0;
  local_160[0] = 0;
  local_160[3] = 0;
  local_160[2] = 0;
  local_160[7] = 0;
  local_160[6] = 0;
  local_170 = &PTR__stringbuf_00f687d0;
  uStack_118 = 0;
  local_120 = (void *)0x0;
  local_110 = CONCAT44(local_110._4_4_,0x18);
  std::stringbuf::__init_buf_ptrs_abi_nn220000_((stringbuf *)&local_170);
  *(uint *)((long)&local_170 + (long)local_178[-3]) =
       *(uint *)((long)&local_170 + (long)local_178[-3]) | 0x200;
  *(uint *)((long)&local_170 + (long)local_178[-3]) =
       *(uint *)((long)&local_170 + (long)local_178[-3]) & 0xffffffb5 | 8;
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
            ((ostream *)&local_178,"LeAdvFilterBroadcasterAddressComplete { ",0x28);
  poVar4 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                     ((ostream *)&local_178,"",0);
  poVar4 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                     (poVar4,"apcf_action = ",0xe);
  local_1a4[0] = GetApcfAction(in_x0);
  ApcfActionText(&local_1a0,local_1a4);
  pcVar2 = local_190;
  if ((local_1a0 & 1) == 0) {
    local_198 = (ulong)(local_1a0 >> 1);
    pcVar2 = (char *)&uStack_19f;
  }
  poVar4 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                     (poVar4,pcVar2,local_198);
  poVar4 = std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
                     (poVar4,", apcf_available_spaces = ",0x1a);
  uVar3 = GetApcfAvailableSpaces(in_x0);
  std::ostream::operator<<(poVar4,uVar3 & 0xff);
  if ((local_1a0 & 1) != 0) {
    operator_delete(local_190,CONCAT71(uStack_19f,local_1a0) & 0xfffffffffffffffe);
  }
  std::__put_character_sequence_abi_nn220000_<char,std::char_traits<char>>
            ((ostream *)&local_178," }",2);
  if (((uint)local_110 >> 4 & 1) == 0) {
    if (((uint)local_110 >> 3 & 1) != 0) {
      plVar6 = local_160;
      uVar5 = local_160[2];
      goto LAB_00d890e0;
    }
    __src = (void *)0x0;
    __n = 0;
  }
  else {
    if (uStack_118 < (ulong)local_160[4]) {
      uStack_118 = local_160[4];
    }
    plVar6 = local_160 + 3;
    uVar5 = uStack_118;
LAB_00d890e0:
    __src = (void *)*plVar6;
    __n = uVar5 - (long)__src;
    if (0xfffffffffffffff6 < __n) {
                    /* WARNING: Subroutine does not return */
      std::string::__throw_length_error_abi_nn220000_();
    }
    if (0x16 < __n) {
      uVar5 = 0x1a;
      if ((__n | 7) != 0x17) {
        uVar5 = (__n | 7) + 1;
      }
      __dest = (undefined1 *)FUN_00f62c00(uVar5);
      in_x8[1] = __n;
      in_x8[2] = (ulong)__dest;
      *in_x8 = uVar5 | 1;
      goto LAB_00d89134;
    }
  }
  __dest = (undefined1 *)((long)in_x8 + 1);
  *(char *)in_x8 = (char)((int)__n << 1);
LAB_00d89134:
  memmove(__dest,__src,__n);
  local_188 = &PTR__stringstream_00f689a0;
  __dest[__n] = 0;
  local_178 = &PTR__stringstream_00f689c8;
  ppuStack_108 = &PTR__stringstream_00f689f0;
  local_170 = &PTR__stringbuf_00f687d0;
  if ((local_160[6] & 1U) != 0) {
    operator_delete(local_120,local_160[6] & 0xfffffffffffffffe);
  }
  local_170 = &PTR__streambuf_00f68750;
  std::locale::~locale((locale *)&uStack_168);
  std::iostream::~iostream((iostream *)&local_188);
  std::ios::~ios((ios *)&ppuStack_108);
  if (*(long *)(lVar1 + 0x28) == local_70) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



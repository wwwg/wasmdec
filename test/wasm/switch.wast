(module
 (type $FUNCSIG$vii (func (param i32 i32)))
 (type $FUNCSIG$vi (func (param i32)))
 (type $FUNCSIG$iii (func (param i32 i32) (result i32)))
 (import "env" "memory" (memory $0 256))
 (import "env" "table" (table 0 anyfunc))
 (import "env" "memoryBase" (global $memoryBase i32))
 (import "env" "tableBase" (global $tableBase i32))
 (import "env" "DYNAMICTOP_PTR" (global $DYNAMICTOP_PTR$asm2wasm$import i32))
 (import "env" "tempDoublePtr" (global $tempDoublePtr$asm2wasm$import i32))
 (import "env" "ABORT" (global $ABORT$asm2wasm$import i32))
 (import "global" "NaN" (global $nan$asm2wasm$import f64))
 (import "global" "Infinity" (global $inf$asm2wasm$import f64))
 (import "env" "abortStackOverflow" (func $abortStackOverflow (param i32)))
 (import "env" "_printf" (func $_printf (param i32 i32) (result i32)))
 (global $DYNAMICTOP_PTR (mut i32) (get_global $DYNAMICTOP_PTR$asm2wasm$import))
 (global $tempDoublePtr (mut i32) (get_global $tempDoublePtr$asm2wasm$import))
 (global $ABORT (mut i32) (get_global $ABORT$asm2wasm$import))
 (global $STACKTOP (mut i32) (i32.const 0))
 (global $STACK_MAX (mut i32) (i32.const 0))
 (global $__THREW__ (mut i32) (i32.const 0))
 (global $threwValue (mut i32) (i32.const 0))
 (global $setjmpId (mut i32) (i32.const 0))
 (global $undef (mut i32) (i32.const 0))
 (global $nan (mut f64) (get_global $nan$asm2wasm$import))
 (global $inf (mut f64) (get_global $inf$asm2wasm$import))
 (global $tempInt (mut i32) (i32.const 0))
 (global $tempBigInt (mut i32) (i32.const 0))
 (global $tempBigIntS (mut i32) (i32.const 0))
 (global $tempValue (mut i32) (i32.const 0))
 (global $tempDouble (mut f64) (f64.const 0))
 (global $tempRet0 (mut i32) (i32.const 0))
 (global $tempFloat (mut f32) (f32.const 0))
 (global $f0 (mut f32) (f32.const 0))
 (data (get_global $memoryBase) "one\n\00two\n\00forty two!\n\00default\n")
 (export "__post_instantiate" (func $__post_instantiate))
 (export "_main" (func $_main))
 (export "runPostSets" (func $runPostSets))
 (func $stackAlloc (; 2 ;) (param $size i32) (result i32)
  (local $ret i32)
  (set_local $ret
   (get_global $STACKTOP)
  )
  (set_global $STACKTOP
   (i32.add
    (get_global $STACKTOP)
    (get_local $size)
   )
  )
  (set_global $STACKTOP
   (i32.and
    (i32.add
     (get_global $STACKTOP)
     (i32.const 15)
    )
    (i32.const -16)
   )
  )
  (if
   (i32.ge_s
    (get_global $STACKTOP)
    (get_global $STACK_MAX)
   )
   (call $abortStackOverflow
    (get_local $size)
   )
  )
  (return
   (get_local $ret)
  )
 )
 (func $stackSave (; 3 ;) (result i32)
  (return
   (get_global $STACKTOP)
  )
 )
 (func $stackRestore (; 4 ;) (param $top i32)
  (set_global $STACKTOP
   (get_local $top)
  )
 )
 (func $establishStackSpace (; 5 ;) (param $stackBase i32) (param $stackMax i32)
  (set_global $STACKTOP
   (get_local $stackBase)
  )
  (set_global $STACK_MAX
   (get_local $stackMax)
  )
 )
 (func $setThrew (; 6 ;) (param $threw i32) (param $value i32)
  (if
   (i32.eq
    (get_global $__THREW__)
    (i32.const 0)
   )
   (block
    (set_global $__THREW__
     (get_local $threw)
    )
    (set_global $threwValue
     (get_local $value)
    )
   )
  )
 )
 (func $_main (; 7 ;) (param $$0 i32) (param $$1 i32) (result i32)
  (local $$2 i32)
  (local $$3 i32)
  (local $$4 i32)
  (local $$5 i32)
  (local $$6 i32)
  (local $$vararg_buffer i32)
  (local $$vararg_buffer1 i32)
  (local $$vararg_buffer3 i32)
  (local $$vararg_buffer5 i32)
  (local $label i32)
  (local $sp i32)
  (set_local $sp
   (get_global $STACKTOP)
  )
  (set_global $STACKTOP
   (i32.add
    (get_global $STACKTOP)
    (i32.const 48)
   )
  )
  (if
   (i32.ge_s
    (get_global $STACKTOP)
    (get_global $STACK_MAX)
   )
   (call $abortStackOverflow
    (i32.const 48)
   )
  )
  (set_local $$vararg_buffer5
   (i32.add
    (get_local $sp)
    (i32.const 24)
   )
  )
  (set_local $$vararg_buffer3
   (i32.add
    (get_local $sp)
    (i32.const 16)
   )
  )
  (set_local $$vararg_buffer1
   (i32.add
    (get_local $sp)
    (i32.const 8)
   )
  )
  (set_local $$vararg_buffer
   (get_local $sp)
  )
  (set_local $$2
   (i32.const 0)
  )
  (set_local $$3
   (get_local $$0)
  )
  (set_local $$4
   (get_local $$1)
  )
  ;;@ switch.c:9:0
  (set_local $$5
   (i32.const 42)
  )
  ;;@ switch.c:10:0
  (set_local $$6
   (get_local $$5)
  )
  (block $switch
   (block $switch-default
    (block $switch-case1
     (block $switch-case0
      (block $switch-case
       (br_table $switch-case $switch-case0 $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-default $switch-case1 $switch-default
        (i32.sub
         (get_local $$6)
         (i32.const 1)
        )
       )
      )
      (block
       ;;@ switch.c:12:0
       (drop
        (call $_printf
         (i32.add
          (get_global $memoryBase)
          (i32.const 0)
         )
         (get_local $$vararg_buffer)
        )
       )
       (br $switch)
      )
     )
     (block
      ;;@ switch.c:15:0
      (drop
       (call $_printf
        (i32.add
         (get_global $memoryBase)
         (i32.const 5)
        )
        (get_local $$vararg_buffer1)
       )
      )
      (br $switch)
     )
    )
    (block
     ;;@ switch.c:18:0
     (drop
      (call $_printf
       (i32.add
        (get_global $memoryBase)
        (i32.const 10)
       )
       (get_local $$vararg_buffer3)
      )
     )
     (br $switch)
    )
   )
   ;;@ switch.c:21:0
   (drop
    (call $_printf
     (i32.add
      (get_global $memoryBase)
      (i32.const 22)
     )
     (get_local $$vararg_buffer5)
    )
   )
  )
  (set_global $STACKTOP
   (get_local $sp)
  )
  ;;@ switch.c:24:0
  (return
   (i32.const 0)
  )
 )
 (func $runPostSets (; 8 ;)
  (local $temp i32)
  (nop)
 )
 (func $__post_instantiate (; 9 ;)
  (set_global $STACKTOP
   (i32.add
    (get_global $memoryBase)
    (i32.const 32)
   )
  )
  (set_global $STACK_MAX
   (i32.add
    (get_global $STACKTOP)
    (i32.const 5242880)
   )
  )
  (call $runPostSets)
 )
)

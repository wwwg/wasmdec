(module
 (type $FUNCSIG$vii (func (param i32 i32)))
 (type $FUNCSIG$vi (func (param i32)))
 (type $FUNCSIG$iii (func (param i32 i32) (result i32)))
 (import "env" "memory" (memory $0 256))
 (import "env" "table" (table 4 anyfunc))
 (import "env" "memoryBase" (global $memoryBase i32))
 (import "env" "tableBase" (global $tableBase i32))
 (import "env" "DYNAMICTOP_PTR" (global $DYNAMICTOP_PTR$asm2wasm$import i32))
 (import "env" "tempDoublePtr" (global $tempDoublePtr$asm2wasm$import i32))
 (import "global" "NaN" (global $nan$asm2wasm$import f64))
 (import "global" "Infinity" (global $inf$asm2wasm$import f64))
 (import "env" "abortStackOverflow" (func $abortStackOverflow (param i32)))
 (import "env" "nullFunc_X" (func $nullFunc_X (param i32)))
 (import "env" "_printf" (func $_printf (param i32 i32) (result i32)))
 (global $DYNAMICTOP_PTR (mut i32) (get_global $DYNAMICTOP_PTR$asm2wasm$import))
 (global $tempDoublePtr (mut i32) (get_global $tempDoublePtr$asm2wasm$import))
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
 (elem (get_global $tableBase) $b0 $_doubleValue $_main $b0)
 (data (get_global $memoryBase) "%s\n\00Hello, wasmdec!\00secondVal: %d\n")
 (export "__post_instantiate" (func $__post_instantiate))
 (export "_doubleValue" (func $_doubleValue))
 (export "_main" (func $_main))
 (export "runPostSets" (func $runPostSets))
 (func $stackAlloc (; 3 ;) (param $size i32) (result i32)
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
 (func $stackSave (; 4 ;) (result i32)
  (return
   (get_global $STACKTOP)
  )
 )
 (func $stackRestore (; 5 ;) (param $top i32)
  (set_global $STACKTOP
   (get_local $top)
  )
 )
 (func $establishStackSpace (; 6 ;) (param $stackBase i32) (param $stackMax i32)
  (set_global $STACKTOP
   (get_local $stackBase)
  )
  (set_global $STACK_MAX
   (get_local $stackMax)
  )
 )
 (func $setThrew (; 7 ;) (param $threw i32) (param $value i32)
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
 (func $_doubleValue (; 8 ;) (param $$0 i32) (result i32)
  (local $$1 i32)
  (local $$2 i32)
  (local $$3 i32)
  (local $label i32)
  (local $sp i32)
  (set_local $sp
   (get_global $STACKTOP)
  )
  (set_global $STACKTOP
   (i32.add
    (get_global $STACKTOP)
    (i32.const 16)
   )
  )
  (if
   (i32.ge_s
    (get_global $STACKTOP)
    (get_global $STACK_MAX)
   )
   (call $abortStackOverflow
    (i32.const 16)
   )
  )
  (set_local $$1
   (get_local $$0)
  )
  ;;@ main.c:4:0
  (set_local $$2
   (get_local $$1)
  )
  (set_local $$3
   (i32.shl
    (get_local $$2)
    (i32.const 1)
   )
  )
  (set_global $STACKTOP
   (get_local $sp)
  )
  (return
   (get_local $$3)
  )
 )
 (func $_main (; 9 ;) (result i32)
  (local $$0 i32)
  (local $$1 i32)
  (local $$2 i32)
  (local $$3 i32)
  (local $$4 i32)
  (local $$5 i32)
  (local $$6 i32)
  (local $$7 i32)
  (local $$8 i32)
  (local $$9 i32)
  (local $$vararg_buffer i32)
  (local $$vararg_buffer1 i32)
  (local $label i32)
  (local $sp i32)
  (set_local $sp
   (get_global $STACKTOP)
  )
  (set_global $STACKTOP
   (i32.add
    (get_global $STACKTOP)
    (i32.const 32)
   )
  )
  (if
   (i32.ge_s
    (get_global $STACKTOP)
    (get_global $STACK_MAX)
   )
   (call $abortStackOverflow
    (i32.const 32)
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
  (set_local $$0
   (i32.const 0)
  )
  (loop $while-in
   (block $while-out
    ;;@ main.c:10:0
    (set_local $$3
     (get_local $$1)
    )
    (set_local $$4
     (i32.add
      (get_local $$3)
      (i32.const 1)
     )
    )
    (set_local $$1
     (get_local $$4)
    )
    ;;@ main.c:11:0
    (set_local $$5
     (get_local $$1)
    )
    (set_local $$6
     (i32.lt_s
      (get_local $$5)
      (i32.const 10)
     )
    )
    (if
     (get_local $$6)
     (br $while-out)
    )
    (br $while-in)
   )
  )
  ;;@ main.c:15:0
  (i32.store
   (get_local $$vararg_buffer)
   (i32.add
    (get_global $memoryBase)
    (i32.const 4)
   )
  )
  (drop
   (call $_printf
    (i32.add
     (get_global $memoryBase)
     (i32.const 0)
    )
    (get_local $$vararg_buffer)
   )
  )
  ;;@ main.c:17:0
  (set_local $$1
   (i32.const 6)
  )
  ;;@ main.c:19:0
  (set_local $$7
   (get_local $$1)
  )
  (set_local $$8
   (call $_doubleValue
    (get_local $$7)
   )
  )
  (set_local $$2
   (get_local $$8)
  )
  ;;@ main.c:20:0
  (set_local $$9
   (get_local $$2)
  )
  (i32.store
   (get_local $$vararg_buffer1)
   (get_local $$9)
  )
  (drop
   (call $_printf
    (i32.add
     (get_global $memoryBase)
     (i32.const 20)
    )
    (get_local $$vararg_buffer1)
   )
  )
  (set_global $STACKTOP
   (get_local $sp)
  )
  ;;@ main.c:21:0
  (return
   (i32.const 0)
  )
 )
 (func $runPostSets (; 10 ;)
  (local $temp i32)
  (nop)
 )
 (func $__post_instantiate (; 11 ;)
  (set_global $STACKTOP
   (i32.add
    (get_global $memoryBase)
    (i32.const 48)
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
 (func $b0 (; 12 ;) (result f64)
  (call $nullFunc_X
   (i32.const 0)
  )
  (return
   (f64.const 0)
  )
 )
)

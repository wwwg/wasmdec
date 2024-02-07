(module
  (func (export "i32.load") (result i32)
    (i32.load align=1 (i32.const 0)))
  (func (export "i64.load") (result i64)
    (i64.load align=1 (i32.const 0)))
  (func (export "f32.load") (result f32)
    (f32.load align=1 (i32.const 0)))
  (func (export "f64.load") (result f64)
    (f64.load align=1 (i32.const 0)))

  (func (export "i32.store")
    (i32.store align=1 (i32.const 0) (i32.const 0)))
  (func (export "i64.store")
    (i64.store align=1 (i32.const 0) (i64.const 0)))
  (func (export "f32.store")
    (f32.store align=1 (i32.const 0) (f32.const 0)))
  (func (export "f64.store")
    (f64.store align=1 (i32.const 0) (f64.const 0)))
)

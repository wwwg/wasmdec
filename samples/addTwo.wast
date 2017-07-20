(module
	(import "env" "DYNAMICTOP_PTR" (global $import$0 i32))
	(import "env" "abort" (func $import$7 (param i32)))
	(func $addTwo (param i32 i32) (result i32)
	(return
		(i32.add
			(get_local 0)
			(get_local 1))))
	(export "addTwo" $addTwo))
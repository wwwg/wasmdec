(module
	(type $varg_i32 (func (result i32)))
	(func $addTwo (param i32 i32) (result i32)
		(return
			(i32.add
				(get_local 0)
				(get_local 1)
			)
		)
	)
	(func $getOne (type $varg_i32)
		(return
			(i32.const 1)
		)
	)
	(export "addTwo" $addTwo)
)
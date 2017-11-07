# wasmdec
wasmdec is a program that converts WebAssembly binaries to pseudo-C code.

# Example
wasmdec will translate this WebAssembly binary:
```wasm
(module
	(func $addTwo (param i32 i32) (result i32)
		(return
			(i32.add (get_local 0) (get_local 1))
		)
	)
	(export "addTwo" $addTwo)
)
```
To the following pseudo-C code:
```c
int fn_addTwo(int arg0, int arg1) {
	return arg0 + arg1;
}
```
# Building
To build wasmdec and install all of it's dependencies, run `sudo make all`.

# WebAssembly Feature Support
wasmdec supports almost every single WASM expression, with the exception of atomics. No support for atomics are planned.
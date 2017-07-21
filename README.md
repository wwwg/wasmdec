# wdis
wdis is a program that converts WebAssembly binaries to pseudo-C code.

# Building
To build, run `make binaryen && make`.
If the executable fails to locate `libbinaryen.so`, move / copy `src/binaryen/lib/libbinaryen.so` to `/usr/lib64`.

# Example
wdis will translate this WebAssembly binary:
```
(module
	(func $addTwo (param i32 i32) (result i32)
	(return
		(i32.add
			(get_local 0)
			(get_local 1))))
	(export "addTwo" $addTwo))
```
To the following pseudo-C code:
```c
#include <stdint.h>
typedef float float32_t;
typedef double float64_t;

int32_t fn_addTwo(int32_t arg0, int32_t arg1) {
	return arg0 + arg1;
}
```

# Support
wdis is currently limited, and only supports a few WebAssembly expressions:
- Blocks
- Binary operations
- Constants
- Conditional branching (Experimental)
- get_local
- Imports
- return<br>
More are planned.
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
# Usage
```bash
wasmdec -i (input file) -o (output file) (options)
```
Where options is one of:
- `-e` or `--extra` : Writes extra information about the binary to output files
- `-m` or `--memdump` : Dumps the binary's memory to disk. Please note that if memdump ONLY dumps memory and doesn't perform any translation.
- `-d` or `--debug` : Print extra debug information to stdout

# WebAssembly Feature Support
wasmdec supports almost every single WASM expression, with the exception of atomics. No support for atomics are planned.
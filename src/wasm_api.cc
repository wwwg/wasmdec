// Definitions for functions that can be used when wasmdec is compiled to wasm
#include "decompiler/MultiDecompiler.h"
#include <cstdlib>

extern "C" {
	char* wasmdec_decompile(char* in_raw, bool in_is_bin) {
		/*
			in_raw: raw binary / text to be disassembled
			in_type: whether or not the input is a webassembly binary or AST
		*/
	} 
}
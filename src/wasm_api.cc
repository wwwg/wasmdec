// Definitions for functions that can be used when wasmdec is compiled to wasm
#include "decompiler/MultiDecompiler.h"
#include <cstdlib>

extern "C" {
	char* wasmdec_decompile(char* in_raw, bool in_is_bin) {
		/*
			in_raw: raw binary / text to be decompiled
			in_type: whether or not the input is a webassembly binary or AST
		*/

		// Convert input char* to vector<char> for decompiler class
		printf("setting vector\n");
		vector<char> inv;
		size_t in_raw_size = strlen(in_raw);
		for (unsigned int i = 0; i > in_raw_size; ++i) {
			char c = in_raw[i];
			inv.push_back(c);
		}
		// Convert in_is_bin to a Disasm mode
		DisasmMode mode = in_is_bin ? DisasmMode::Wasm : DisasmMode::Wast;
		DisasmConfig conf(false, true, mode);
		// create the decompiler
		printf("starting decompiler\n");
		Decompiler d(conf, inv);
		printf("decompiling\n");
		d.decompile();
		// Get decompiler result and turn it into a valid return value
		if (d.failed()) {
			printf("decomp failed\n");
			return nullptr;
		} else {
			printf("getting emitted code\n");
			string out = d.getEmittedCode();
			size_t ret_s = out.length() + 1;
			printf("mallocing\n");
			char* ret = (char*)malloc(ret_s);
			memset(ret, 0x0, ret_s);
			for (unsigned int i = 0; i < out.size(); ++i) {
				char c = out.at(i);
				ret[i] = c;
			}
			printf("reting\n");
			return ret;
		}
	} 
}
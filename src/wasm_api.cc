// Definitions for functions that can be used when wasmdec is compiled to wasm
#include "decompiler/MultiDecompiler.h"
#include <cstdlib>

extern "C" {
	/*
		Creates a wasmdec decompiler

		debug: log debug information
		extra: output extra binary information in the decompilation
		mode: "wasm" or "wast", whether or not the input is an ast or binary
		input: the input binary / webassembly text

		return value: a pointer to the configured decompiler (for use in other wasmdec api functions)
	*/
	Decompiler* wasmdec_create_decompiler(bool debug, bool extra,
																			char* mode, char* input) {
		// convert mode to a DisasmMode
		string smode = string(mode);
		DisasmMode dmode = DisasmMode::None;
		if (smode == "wasm") {
			dmode = DisasmMode::Wasm;
		} else if (smode == "wast") {
			dmode = DisasmMode::Wast;
		} else {
			printf("WARN: wasmdec: invalid input mode");
			return nullptr;
		}
		// Create the config
		DisasmConfig conf(debug, extra, dmode);

		// Convert input char* to vector<char> for decompiler class
		vector<char> inv;
		size_t input_size = strlen(input);
		for (unsigned int i = 0; i < input_size; ++i) {
			char c = input[i];
			inv.push_back(c);
		}
		// Create decompiler
		Decompiler* ret = new Decompiler(conf, inv);
		return ret;
	}
	char* wasmdec_decompile(char* in_raw, bool in_is_bin) {
		/*
			in_raw: raw binary / text to be decompiled
			in_type: whether or not the input is a webassembly binary or AST
		*/

		// Convert input char* to vector<char> for decompiler class
		vector<char> inv;
		size_t in_raw_size = strlen(in_raw);
		for (unsigned int i = 0; i < in_raw_size; ++i) {
			char c = in_raw[i];
			inv.push_back(c);
		}
		// Convert in_is_bin to a Disasm mode
		DisasmMode mode = in_is_bin ? DisasmMode::Wasm : DisasmMode::Wast;
		DisasmConfig conf(true, true, mode);
		// create the decompiler
		Decompiler d(conf, inv);
		d.decompile();
		// Get decompiler result and turn it into a valid return value
		if (d.failed()) {
			printf("WARN: wasmdec decomp failed\n");
			return nullptr;
		} else {
			string out = d.getEmittedCode();
			size_t ret_s = out.length() + 1;
			char* ret = (char*)malloc(ret_s);
			memset(ret, 0x0, ret_s);
			for (unsigned int i = 0; i < out.size(); ++i) {
				char c = out.at(i);
				ret[i] = c;
			}
			return ret;
		}
	} 
}
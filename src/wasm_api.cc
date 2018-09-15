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
	/*
		Decompiles the input binary / ast

		decomp: the decompiler generated in wasmdec_create_decompiler()

		return value: whether or not the decompiler succeeded
	*/
	bool wasmdec_decompile(Decompiler* decomp) {
		if (decomp == nullptr)
			return false;
		decomp->decompile();
		if (decomp.failed()) {
			return false;
		}
		return true;
	}
	/*
		Gets the decompiler's output

		decomp: the decompiler generated in wasmdec_create_decompiler()

		return value: resulting decompiled C code
	*/
	char* wasmdec_get_decompiled_code(Decompiler* decomp) {
		if (decomp.failed())
			return nullptr;
		string emitted = decomp->getEmittedCode();
		size_t ret_size = emitted.size() + 1;
		char* ret = malloc(ret_size);
		memset(ret, 0x0, ret_size);
		for (int i = 0 ; i < emitted.size(); ++i) {
			ret[i] = emitted.at(i);
		}
		return ret;
	}
}
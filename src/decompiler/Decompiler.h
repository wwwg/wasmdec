#ifndef _CODEGEN_H
#define _CODEGEN_H

#include "wasm-s-parser.h"
// #include "asm2wasm.h"

#include "../convert/Conversion.h"
#include "../Emitter.h"

#include "DisasmConfig.h"
#include "DecompilerCtx.h"

using namespace wasmdec;
using namespace std;

namespace wasmdec {
	class Decompiler {
	public:
		wasm::Module module;
		vector<char> binary;
		Emitter emit;
		Decompiler(DisasmConfig, vector<char>*);
		void decompile();
		string getEmittedCode();
		bool failed();
		vector<char> dumpMemory();
		vector<char> dumpTable();
		DisasmMode mode;
		DecompilerCtx* dctx;
	protected:
		void debug(string);
		void debugf(string);
		bool parserFailed;
		bool isDebug;
		bool emitExtraData;
		vector<char> rawTable;
		vector<char> rawMemory;
	};
} // namespace wasmdec

#endif // _CODEGEN_H
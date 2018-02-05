#ifndef _CODEGEN_H
#define _CODEGEN_H

#include "convert/Conversion.h"
#include "Emitter.h"
#include "DisasmConfig.h"
#include "wasm-s-parser.h"

using namespace std;

namespace wasmdec {
	class Disassembler {
	public:
		wasm::Module module;
		vector<char> binary;
		Emitter emit;
		Disassembler(DisasmConfig, vector<char>*);
		void gen();
		string getEmittedCode();
		bool failed();
		vector<char>* dumpMemory();
		vector<char>* dumpTable();
		DisasmMode mode;
		
		// Allocated as needed
		wasm::WasmBinaryBuilder* parser;
		wasm::SExpressionParser* sparser;
		wasm::SExpressionWasmBuilder* sbuilder;
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
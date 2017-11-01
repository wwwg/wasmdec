#ifndef _CODEGEN_H
#define _CODEGEN_H

#include "convert/Conversion.h"
#include "Emitter.h"

using namespace std;

namespace wasmdec {
	class CodeGenerator {
	public:
		wasm::Module module;
		vector<char> binary;
		wasm::WasmBinaryBuilder parser;
		bool isDebug;
		bool emitExtraData;
		Emitter emit;
		CodeGenerator(vector<char>*, bool, bool);
		void gen();
		string getEmittedCode();
		bool failed();
	protected:
		void debug(string);
		void debugf(string);
		bool parserFailed;
	};
} // namespace wasmdec

#endif // _CODEGEN_H
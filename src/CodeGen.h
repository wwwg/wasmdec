#ifndef _CODEGEN_H
#define _CODEGEN_H

#include "convert/Conversion.h"
#include "Emitter.h"

using namespace std;

namespace wdis {
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
	protected:
		void debug(string);
		void debugf(string);
	};
} // namespace wdis

#endif // _CODEGEN_H
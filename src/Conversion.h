#ifndef _CONVER_H
#define _CONVER_H

#include "wasm.h"
#include "wasm-binary.h"
#include "wasm-printing.h"
#include "wasm-s-parser.h"
#include "WasmUtils.h"
#pragma once

using namespace std;

namespace wdis {
	class Convert {
	public:
		// Declared in Conversion.cc
		static string getFName(wasm::Name);
		static string getVName(wasm::Name);
		static string getLocal(wasm::Index);
		static string voidCall(wasm::Function*);
		static string getBinOperator(wasm::BinaryOp);
		static string resolveType(wasm::WasmType);
		static string getDecl(wasm::FunctionType*, string);
		static string getDecl(wasm::FunctionType*, wasm::Name);
		static string getDecl(wasm::Function*);
		static string getDecl(wasm::Module* m, unique_ptr<wasm::Import>& i);
		// Declared in BlockConverter.cc
		static string parseExpr(wasm::Module*, wasm::Expression*);
		static string getBlockBody(wasm::Module*, wasm::Block*);
		static string getFuncBody(wasm::Module*, wasm::Function*);
	};
} // namespace wdis

#endif // _CONVER_H
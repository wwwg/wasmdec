#ifndef _CONVER_H
#define _CONVER_H

#include "wasm.h"
#include "wasm-binary.h"
#include "wasm-printing.h"
#include "wasm-s-parser.h"
#include "../WasmUtils.h"
#include "../WasmContext.h"
using namespace std;

namespace wasmdec {
	class Convert {
	public:
		static string getFName(wasm::Name);
		static string getLocal(wasm::Index);
		static string voidCall(wasm::Function*);
		static string getBinOperator(string, wasm::BinaryOp, string);
		static string getUnary(string);
		static string resolveType(wasm::WasmType);
		static string getDecl(wasm::FunctionType*, string);
		static string getDecl(wasm::FunctionType*, wasm::Name);
		static string getDecl(wasm::Function*);
		static string getDecl(wasm::Module* m, unique_ptr<wasm::Import>& i);

		static string parseExpr(Context*, wasm::Expression*, int);
		static string getBlockBody(Context*, wasm::Block*, int);
		static string getFuncBody(Context, bool);
		static string parseOperandList(Context*, wasm::ExpressionList*, int);
	};
} // namespace wasmdec

#endif // _CONVER_H
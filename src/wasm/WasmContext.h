#ifndef _WASM_CONTEXT_H
#define _WASM_CONTEXT_H

#include "wasm.h"
using namespace wasm;

#include "../decompiler/DecompilerCtx.h"

namespace wasmdec {
	// Context is a union between WASM functions and modules
	class Context {
	public:
		bool isGlobal = false;
		bool isIfCondition = false;
		Function* fn = nullptr;
		Module* mod = nullptr;
		Context(Function*, Module*, DecompilerCtx*);
		Context(Module*);
		int depth = 0;

		int lastSetLocal = 0;

		bool hasDecompilerCtx = false;
		DecompilerCtx* dctx = nullptr;
		Expression* lastExpr = nullptr;
		// Whether or not the expression is exactly one layer below a function
		bool functionLevelExpression = false;
	};
} // namespace wasmdec

#endif // _WASM_CONTEXT_H
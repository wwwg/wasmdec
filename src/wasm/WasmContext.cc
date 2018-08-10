#include "WasmContext.h"
using namespace wasmdec;

Context::Context(Function* _fn, Module* _md, DecompilerCtx* _dctx) {
	isGlobal = false;
	fn = _fn;
	mod = _md;
	depth = 0;
	if (_dctx) {
		hasDecompilerCtx = true;
		dctx = _dctx;
	} else {
		hasDecompilerCtx = false;
		dctx = nullptr;
	}
}
Context::Context(Module* _md) {
	isGlobal = true;
	fn = nullptr; // No function context in global
	mod = _md;
}
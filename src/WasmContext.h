#ifndef _WASM_CONTEXT_H
#define _WASM_CONTEXT_H

#include "convert/Conversion.h"
using namespace wasm;

namespace wdis {
	// Context is a union between WASM functions and modules
	class Context {
	public:
		bool isGlobal;
		Function* fn;
		Module* mod;
		Context(Function* _fn, Module* _md) {
			isGlobal = false;
			fn = _fn;
			mod = _md;
		}
		Context(Module* _md) {
			isGlobal = true;
			fn = nullptr; // No function context in global
			mod = _md;
		}
	};
} // namespace wdis

#endif // _WASM_CONTEXT_H
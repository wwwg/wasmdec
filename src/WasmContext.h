#ifndef _WASM_CONTEXT_H
#define _WASM_CONTEXT_H

#include "convert/Conversion.h"
using namespace wasm;

namespace wdis {
	// Context is a union between WASM functions and modules
	class Context {
	public:
		Function* fn;
		Module* mod;
		Context(Function* _fn, Module* _md) {
			fn = _fn;
			mod = _md;
		}
	};
} // namespace wdis

#endif // _WASM_CONTEXT_H
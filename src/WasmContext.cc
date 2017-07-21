#include "WasmContext.h"
using namespace wdis;

Context::Context(Function* _fn, Module* _md) {
	isGlobal = false;
	fn = _fn;
	mod = _md;
}
Context::Context(Module* _md) {
	isGlobal = true;
	fn = nullptr; // No function context in global
	mod = _md;
}
#ifndef _INTER_LOCAL_H
#define _INTER_LOCAL_H

// Hack to prevent compiler issues
#ifndef _CONVER_H
#include "Conversion.h"
#else
class Convert;
#endif

namespace wdis {
	class InterLocal {
	public:
		wasm::Function* fn;
		int index;
		string CLocal;
		wasm::WasmType wasmLocal;
		InterLocal(wasm::Function* _fn, int _index) {
			fn = _fn;
			index = _fn->params.size() + _index;
			wasmLocal = _fn->vars[index];
			CLocal = Convert::resolveType(wasmLocal);
		}
		string getCDecloration(void) {
			string ret = CLocal;
			ret += " " + Convert::getLocal(index);
			return ret;
		}
	};
} // namespace wdis

#endif // _INTER_LOCAL_H
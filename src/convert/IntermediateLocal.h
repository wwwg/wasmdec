#ifndef _INTER_LOCAL_H
#define _INTER_LOCAL_H

// Hack to prevent compiler issues
#ifndef _CONVER_H
#include "Conversion.h"
#else
class Convert;
#endif

namespace wasmdec {
	class InterLocal {
	public:
		wasm::Function* fn;
		int index;
		string CLocal;
		wasm::Type wasmLocal;
		InterLocal(wasm::Function* _fn, int _index) {
			fn = _fn;
			wasmLocal = _fn->vars[_index];
			index = _fn->params.size() + _index;
			CLocal = Convert::resolveType(wasmLocal);
		}
		string getCDecloration(void) {
			string ret = CLocal;
			ret += " " + Convert::getLocal(index);
			return ret;
		}
	};
} // namespace wasmdec

#endif // _INTER_LOCAL_H
#ifndef _WASM_UTILS
#define _WASM_UTILS
#include "convert/Conversion.h"

using namespace wasm;
using namespace std;

namespace wdis {
	class util {
	public:
		static FunctionType* resolveFType(Module*, Name);
		static string tab(int);
		static string getLiteralValue(Literal*);
		static int getLocalIndex(Function*, int);
	};
}; // namespace wdis

#endif // _WASM_UTILS
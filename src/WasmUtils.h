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
		static string getAddrStr(Address*);
		static string boolStr(bool);
		template<typename T>
		static string getHex(T val);
	};
}; // namespace wdis

template<typename T>
string wdis::util::getHex(T val) {
  stringstream stream;
  stream << "0x" 
         << setfill ('0') << setw(sizeof(T) * 2) 
         << hex << val;
  return stream.str();
}

#endif // _WASM_UTILS
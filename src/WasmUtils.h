#ifndef _WASM_UTILS
#define _WASM_UTILS

using namespace wasm;
using namespace std;

namespace wdis {
	class util {
	public:
		static FunctionType* resolveFType(Module* m, Name nm) {
			for (int i = 0; i < m->functionTypes.size(); ++i) {
				if (m->functionTypes[i]->name == nm) {
					return m->functionTypes[i].get();
				}
			}
			return nullptr;
		}
		static string tab(int tabTimes) {
			// Util for generating nicer looking C
			string ret;
			for (int i = 0; i < tabTimes; ++i) {
				ret += "\t";
			}
			return ret;
		}
	};
}; // namespace wdis

#endif // _WASM_UTILS
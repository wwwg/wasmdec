#include "WasmUtils.h"
using namespace wasmdec;

FunctionType* util::resolveFType(Module* m, Name nm) {
	for (int i = 0; i < m->functionTypes.size(); ++i) {
		if (m->functionTypes[i]->name == nm) {
			return m->functionTypes[i].get();
		}
	}
	return nullptr;
}
string util::tab(int tabTimes) {
	// Util for generating nicer looking C
	string ret;
	if (tabTimes < 1) {
		tabTimes = 1;
	}
	for (int i = 0; i < tabTimes; ++i) {
		ret += "\t";
	}
	return ret;
}
string util::getLiteralValue(Literal* val) {
	int32_t conv_i32;
	int64_t conv_i64;
	float conv_f32;
	double conv_f64;
	switch (val->type) {
		// Convert constant literal type to string
		case WasmType::none:
		case WasmType::unreachable:
			return "0";
			break;
		case WasmType::i32:
			conv_i32 = val->geti32();
			return to_string(conv_i32);
			break;
		case WasmType::i64:
			conv_i64 = val->geti64();
			return to_string(conv_i64);
			break;
		case WasmType::f32:
			conv_f32 = val->getf32();
			return to_string(conv_f32);
			break;
		case WasmType::f64:
			conv_f64 = val->getf64();
			return to_string(conv_f64);
			break;
	}
}
int util::getLocalIndex(Function* fn, int index) {
	return (&fn->params)->size() + index;
}
string util::getAddrStr(Address* addr) {
	stringstream stream;
	stream << "0x" 
		 << setfill('0') << setw(sizeof(uint32_t) * 2) 
		 << hex << addr->addr;
	return stream.str();
}
string util::boolStr(bool b) {
	if (b) return "true";
	else return "false";
}
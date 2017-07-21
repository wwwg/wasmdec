#ifndef _CONVER_H
#include "Conversion.h"
#endif
using namespace std;
using namespace wasm;

string wdis::Convert::getBlockBody(Module* mod, Block* blck, int depth) {
	// Stream all block expressions and components into a string
	stringstream s;
	depth++;
	for (auto& expr : blck->list) {
		s << parseExpr(mod, expr, depth);
	}
	depth--;
	return s.str();
}
string wdis::Convert::getFuncBody(Module* mod, Function* fn, bool addExtraInfo) {
	string fnBody;
	fnBody += " {\n";
	// Function bodies are block expressions
	fnBody += parseExpr(mod, fn->body, -1);
	fnBody += "}";
	return fnBody;
}
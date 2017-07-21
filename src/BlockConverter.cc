#ifndef _CONVER_H
#include "Conversion.h"
#endif
#include "IntermediateLocal.h"
using namespace std;
using namespace wasm;

string wdis::Convert::getBlockBody(Module* mod, Block* blck, int depth) {
	// Stream all block expressions and components into a string
	stringstream s;
	depth++;
	for (auto& expr : blck->list) {
		s << Convert::parseExpr(mod, expr, depth);
	}
	depth--;
	return s.str();
}
string wdis::Convert::getFuncBody(Module* mod, Function* fn, bool addExtraInfo) {
	string fnBody;
	fnBody += " {\n";
	if (addExtraInfo) {
		fnBody += "\t// Function locals:\n";
	}
	// TODO : Parse local variables
	if (addExtraInfo) fnBody += "\n";
	// Function bodies are block expressions
	fnBody += Convert::parseExpr(mod, fn->body, -1);
	fnBody += "}";
	return fnBody;
}
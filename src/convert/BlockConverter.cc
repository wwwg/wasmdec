#ifndef _CONVER_H
#include "Conversion.h"
#endif
#include "IntermediateLocal.h"
using namespace std;
using namespace wasm;

string wdis::Convert::getBlockBody(Context* ctx, Block* blck, int depth) {
	// Stream all block expressions and components into a string
	stringstream s;
	depth++;
	for (auto& expr : blck->list) {
		s << Convert::parseExpr(ctx, expr, depth);
	}
	depth--;
	return s.str();
}
string wdis::Convert::getFuncBody(Context ctx, bool addExtraInfo) {
	string fnBody;
	fnBody += " {\n";
	// Convert function locals to intermediate locals
	vector<WasmType>* vars = &(ctx.fn->vars);
	if (vars->size()) {
		vector<InterLocal> locals;
		for (int i = 0; i < vars->size(); ++i) {
			// Fill locals vector
			InterLocal il(ctx.fn, i);
			locals.push_back(il);
		}
		fnBody += "\t// Parsed WASM function locals:\n";
		// Convert intermediates to C declorations
		for (auto& ilocal : locals) {
			string cdecl = ilocal.getCDecloration();
			fnBody += "\t";
			fnBody += cdecl;
			if (addExtraInfo) {
				// Initialize locals to 0 with extra info enabled
				fnBody += " = 0";
			}
			fnBody += "; ";
			if (addExtraInfo) {
				// Local info
				fnBody += "// Local with index '" + to_string(ilocal.index) + "'";
			}
			fnBody += "\n";
		}
		if (addExtraInfo) fnBody += "\n";
	} else {
		if (addExtraInfo) {
			fnBody += "\t// Function contains no non-parameter locals\n";
		}
	}
	// Function bodies are block expressions
	fnBody += Convert::parseExpr(&ctx, ctx.fn->body, -1);
	fnBody += "}";
	return fnBody;
}
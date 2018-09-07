#ifndef _CONVER_H
#include "Conversion.h"
#endif
#include "IntermediateLocal.h"
using namespace std;
using namespace wasm;

string wasmdec::Convert::getBlockBody(Context* ctx, Block* blck) {
	// Stream all block expressions and components into a string
	stringstream s;
	const char* bname = blck->name.str;
	if (bname != nullptr && strlen(bname)) {
		s << util::tab(ctx->depth);
		s << blck->name.str << ":\n";
	}
	for (auto& expr : blck->list) {
		ctx->lastExpr = blck;
		s << Convert::parseExpr(ctx, expr);
	}
	return s.str();
}
string wasmdec::Convert::getFuncBody(Context ctx, bool addExtraInfo) {
	string fnBody;
	fnBody += " {\n";
	// Convert function locals to intermediate locals
	vector<Type>* vars = &(ctx.fn->vars);
	if (vars->size()) {
		vector<InterLocal> locals;
		for (unsigned int i = 0; i < vars->size(); ++i) {
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
	ctx.depth = -1;
	fnBody += Convert::parseExpr(&ctx, ctx.fn->body);
	fnBody += "}";
	return fnBody;
}
#include "parser.h"
using namespace wasmdec;

string wasmdec::parsers::_return(Context* ctx, Expression* ex) {
	string ret;
	Return* spex = ex->cast<Return>();
	if (ctx->depth < 1) {
		ret += util::tab(1);
	} else {
		ret += util::tab(ctx->depth);
	}
	if (spex->value) {
		// Insert expression as function return value
		ret += "return ";
		ctx->lastExpr = ex;
		ctx->functionLevelExpression = false;
		ret += parseExpr(ctx, spex->value) + ";\n";
	} else {
		ret += "return;\n"; // For void functions
	}
	return ret;
}
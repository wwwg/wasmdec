#include "parser.h"
using namespace wasmdec;

string wasmdec::parsers::call_indirect(Context* ctx, Expression* ex) {
	string ret;
	
    CallIndirect* ci = ex->cast<CallIndirect>();
    ctx->lastExpr = ex;
    ctx->functionLevelExpression = false;
    string _icall = parseExpr(ctx, ci->target);
    ret += "// Indirect call:\n";
    ret += "(" + _icall + ")";
    ret += parseOperandList(ctx, &(ci->operands));
    ret += "; \n";

	return ret;
}
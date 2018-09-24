#include "parser.h"
using namespace wasmdec;

string wasmdec::parsers::binary(Context* ctx, Expression* ex) {
	string ret;
	// Select is the WASM equivalent of C's ternary operator.
    Select* slex = ex->cast<Select>();
    ctx->lastExpr = ex;
    ctx->functionLevelExpression = false;
    string cond = Convert::parseExpr(ctx, slex->condition);
    ctx->lastExpr = ex;
    ctx->functionLevelExpression = false;
    string ifTrue = Convert::parseExpr(ctx, slex->ifTrue);
    ctx->lastExpr = ex;
    ctx->functionLevelExpression = false;
    string ifFalse = Convert::parseExpr(ctx, slex->ifFalse);
    ret += "(" + cond + ") ? (" + ifTrue + ") : (" + ifFalse + ");\n";
	return ret;
}
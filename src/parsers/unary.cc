#include "parser.h"
using namespace wasmdec;

string wasmdec::parsers::unary(Context* ctx, Expression* ex) {
	string ret;
	Unary* uex = ex->cast<Unary>();
    ctx->lastExpr = ex;
    ctx->functionLevelExpression = false;
    string unaryEx = Convert::parseExpr(ctx, uex->value);
    ret += Convert::getUnary(unaryEx, uex->op);
	return ret;
}
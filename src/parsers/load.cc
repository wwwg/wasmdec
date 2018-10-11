#include "parser.h"
using namespace wasmdec;

string wasmdec::parsers::load(Context* ctx, Expression* ex) {
	string ret;
	// Memory loading
    Load* lxp = ex->cast<Load>();
    ctx->lastExpr = ex;
    ctx->functionLevelExpression = false;
    string var = Convert::parseExpr(ctx, lxp->ptr);
    ret += util::tab(ctx->depth);
    ret += "*(void*)(";
    ret += var;
    ret += ")";
	return ret;
}
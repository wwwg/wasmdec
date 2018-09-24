#include "parser.h"
using namespace wasmdec;

string wasmdec::parsers::drop(Context* ctx, Expression* ex) {
	string ret;
	
    Drop* dex = ex->cast<Drop>();
    ret += util::tab(1);
    ret += "/* Drop routine */\n";
    ctx->functionLevelExpression = false;
    ctx->lastExpr = ex;
    ret += Convert::parseExpr(ctx, dex->value);
    ret += util::tab(1);
    ret += "/* End of drop routine */\n";

	return ret;
}
#include "parser.h"
using namespace wasmdec;

string wasmdec::parsers::call(Context* ctx, Expression* ex) {
	string ret;
	Call* fnCall = ex->cast<Call>();
    if (ctx->depth < 1) {
        ret += util::tab(1);
    } else {
        ret += util::tab(ctx->depth);
    }
    ret += Convert::getFName(fnCall->target) + Convert::parseOperandList(ctx, &(fnCall->operands));
    ret += ";\n";
	return ret;
}
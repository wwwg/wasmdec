#include "parser.h"
using namespace wasmdec;

string wasmdec::parsers::_break(Context* ctx, Expression* ex) {
	string ret;
	Break* br = ex->cast<Break>();
    ret += util::tab(ctx->depth);
    if (br->condition) {
        // Conditional breaking
        ctx->lastExpr = ex;
        ctx->functionLevelExpression = false;
        ret += "if (" + Convert::parseExpr(ctx, br->condition) + ") break;";
    } else {
        // Literal breaking
        ret += "break;";
    }
    if (br->value) {
        ctx->lastExpr = ex;
        ctx->functionLevelExpression = false;
        string val = Convert::parseExpr(ctx, br->value);
        // TODO : parse break values
        // cout << "Break val: " << val << endl;
    }
    return ret;
}
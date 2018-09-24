#include "parser.h"
using namespace wasmdec;

string wasmdec::parsers::loop(Context* ctx, Expression* ex) {
    string ret;
	Loop* lex = ex->cast<Loop>();
    ret += util::tab(ctx->depth);
    ret += "while (1) {";
    if (lex->name.str) {
            ret += " // Loop name: '";
            ret += lex->name.str;
            ret += "'";
    }
    ret += "\n";
    ctx->depth -= 1;
    ctx->lastExpr = ex;
    ctx->functionLevelExpression = false;
    ret += Convert::parseExpr(ctx, lex->body);
    ret += "\n";
    if (ctx->depth < 1) {
        ret += util::tab(1);
    } else {
        ret += util::tab(ctx->depth);
    }
    ret += "} " ;
    if (lex->name.str) {
            ret += "// End of loop '";
            ret += lex->name.str;
            ret += "'";
    }
    ret += "\n";
    return ret;
}
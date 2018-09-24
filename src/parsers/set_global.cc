#include "parser.h"
using namespace wasmdec;

string wasmdec::parsers::set_global(Context* ctx, Expression* ex) {
    string ret;
    // Set global variable
    SetGlobal* gex = ex->cast<SetGlobal>();
    bool isInline = false;
    bool isInPolyAssignment = false;
    if (ctx->lastExpr && !ctx->functionLevelExpression) {
        if (ctx->isIfCondition) {
            isInline = true;
        }
        if (ctx->lastExpr != nullptr) {
            isInPolyAssignment = (ctx->lastExpr->is<Store>()
                                || ctx->lastExpr->is<SetLocal>()
                                || ctx->lastExpr->is<SetGlobal>());
        }
    }

    ret += util::tab(ctx->depth) + gex->name.str + " = ";
    // The value is an expression
    ctx->functionLevelExpression = false;
    ctx->lastExpr = ex;
    ret += Convert::parseExpr(ctx, gex->value);
    if (!isInline && !isInPolyAssignment && !ctx->isIfCondition) {
        ret += ";\n";
    }
    return ret;
}
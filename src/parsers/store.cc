#include "parser.h"
using namespace wasmdec;

string wasmdec::parsers::store(Context* ctx, Expression* ex) {
	string ret;
	Store* sxp = ex->cast<Store>();
    ctx->lastExpr = ex;
    ctx->functionLevelExpression = false;
    string _offset = Convert::parseExpr(ctx, sxp->ptr);
    ctx->lastExpr = ex;
    ctx->functionLevelExpression = false;
    string val = Convert::parseExpr(ctx, sxp->value);

    bool valueIsAssignment = (sxp->value->is<SetLocal>()
                            || sxp->value->is<SetGlobal>()
                            || sxp->value->is<Store>());
    
    bool isInline = false;
    bool isInPolyAssignment = false;
    if (ctx->lastExpr && !ctx->functionLevelExpression) {
        if (ctx->isIfCondition) {
            isInline = true;
        }
        isInPolyAssignment = ((ctx->lastExpr != nullptr)
            && (ctx->lastExpr->is<SetLocal>()
            || ctx->lastExpr->is<SetGlobal>()
            || ctx->lastExpr->is<Store>()));
    }
    
    if (!isInline) {
        if (!isInPolyAssignment) {
            ret += util::tab(ctx->depth);
        }
    }
    ret += "*("
    ret += _offset;
    ret += ") = ";
    ret += val;
    if (!isInline) {
        if (!valueIsAssignment) {
            ret += "; \n";;
        }
    }
	return ret;
}
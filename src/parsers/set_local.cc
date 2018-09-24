#include "parser.h"
using namespace wasmdec;

string wasmdec::parsers::set_local(Context* ctx, Expression* ex) {
	string ret;
	
    // Resolve variable's C name
    SetLocal* sl = ex->cast<SetLocal>();
    bool isInline = false;
    bool isInPolyAssignment = false;
    if (ctx->lastExpr && !ctx->functionLevelExpression) {
        if (ctx->isIfCondition) {
            isInline = true;
            isInPolyAssignment = ((ctx->lastExpr != nullptr)
                            && (ctx->lastExpr->is<SetLocal>()
                            || ctx->lastExpr->is<SetGlobal>()
                            || ctx->lastExpr->is<Store>()));
        }
    }

    /*
    int idx = util::getLocalIndex(ctx->fn, sl->index);
    */
    int idx = sl->index;
    ctx->lastSetLocal = idx;
    if (!isInline) {
        if (!isInPolyAssignment) {
            ret += util::tab(ctx->depth);
        }
    }
    ret += Convert::getLocal((Index)idx);
    ret += " = ";
    // Resolve the value to be set
    bool valueIsAssignment = (sl->value->is<SetLocal>()
                            || sl->value->is<SetGlobal>()
                            || sl->value->is<Store>());
    ctx->lastExpr = ex;
    ctx->functionLevelExpression = false;
    ret += Convert::parseExpr(ctx, sl->value);
    if (!isInline && !valueIsAssignment) {
        ret += ";\n";
    }

	return ret;
}
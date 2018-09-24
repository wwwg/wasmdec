#include "parser.h"
using namespace wasmdec;

string wasmdec::parsers::call_import(Context* ctx, Expression* ex) {
    string ret;
	// Imported function call
    CallImport* imCall = ex->cast<CallImport>();
    // ret += "/* Import call */ ";
    if (ctx->depth < 1) {
        ret += util::tab(1);
    } else {
        ret += util::tab(ctx->depth);
    }
    ret += imCall->target.str + Convert::parseOperandList(ctx, &(imCall->operands));
    ret += ";\n";
    return ret;
}
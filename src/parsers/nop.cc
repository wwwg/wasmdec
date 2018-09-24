#include "parser.h"
using namespace wasmdec;

string wasmdec::parsers::nop(Context* ctx, Expression* ex) {
	return util::tab(ctx->depth) + "// <Nop expression>\n"; // Nop expressions do nothing
}
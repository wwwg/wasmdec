#include "parser.h"
using namespace wasmdec;

string wasmdec::parsers::block(Context*, Expression*) {
	Block* blck = ex->cast<Block>();
	ctx->depth++;
	string ret = getBlockBody(ctx, blck);
	ctx->depth--;
	return ret;
}
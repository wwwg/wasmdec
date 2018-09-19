#include "parser.h"
using namespace wasmdec;

string wasmdec::parsers::block(Context* ctx, Expression* ex) {
	string ret;
	Block* blck = ex->cast<Block>();
	ctx->depth++;
	ret += Convert::getBlockBody(ctx, blck);
	ctx->depth--;
	return ret;
}
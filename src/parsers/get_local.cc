#include "parser.h"
using namespace wasmdec;

string wasmdec::parsers::get_local(Context* ctx, Expression* ex) {
	GetLocal* spex = ex->cast<GetLocal>();
	return Convert::getLocal(spex->index);
}
#include "parser.h"
using namespace wasmdec;

string wasmdec::parsers::unreachable(Context* ctx, Expression* ex) {
	return "/* Unreachable */";
}
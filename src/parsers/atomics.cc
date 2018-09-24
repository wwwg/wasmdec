#include "parser.h"
using namespace wasmdec;

string wasmdec::parsers::atomics(Context* ctx, Expression* ex) {
	return "/* Atomic operation unsupported */\n";
}
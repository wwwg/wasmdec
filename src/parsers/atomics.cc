#include "parser.h"
using namespace wasmdec;

string wasmdec::parsers::atmoics(Context* ctx, Expression* ex) {
	return "/* Atomic operation unsupported */\n";
}
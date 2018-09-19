#include "parser.h"
using namespace wasmdec;

string wasmdec::parsers::_const(Context* ctx, Expression* ex) {
	// Resolve constant's literal value to a syntactically valid C literal
	Literal* val = &(ex->cast<Const>()->value);
	return util::getLiteralValue(val);
}
#include "parser.h"
using namespace wasmdec;

string wasmdec::parsers::get_global(Context* ctx, Expression* ex) {
    string ret;
	// Global variable lookup
    ret += ex->cast<GetGlobal>()->name.str;
    // ret += "\n";
    return ret;
}
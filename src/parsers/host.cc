#include "parser.h"
using namespace wasmdec;

string wasmdec::parsers::host(Context* ctx, Expression* ex) {
	string ret;
	Host* hexp = ex->cast<Host>();
    string hoperands = Convert::parseOperandList(ctx, &(hexp->operands));
    string hfunc = Convert::getHostFunc(hexp->op);
    ret += "/* Host call */\n" + hfunc + hoperands;
	return ret;
}
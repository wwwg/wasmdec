#include "parser.h"
using namespace wasmdec;

string wasmdec::parsers::_switch(Context* ctx, Expression* ex) {
	string ret;
    /*
        how wasm switches work:

        switch (<topmost stack variable>) {
            case <index of body expression>:
                goto <body expression>
            default:
                <default value>
        }
    */
    // cout << "switch!\n" << endl;
    Switch* sw = ex->cast<Switch>();
    // start of switch routine
    ret += util::tab(ctx->depth);
    ret += "switch (";
    ret += Convert::getLocal(ctx->lastSetLocal);
    ret += ") {\n";
    ctx->depth++;
    
    // routine body
    for (unsigned int i = 0; i < sw->targets.size(); ++i) {
        string sname = string(sw->targets[i].str);
        ret += util::tab(ctx->depth);
        ret += "case ";
        ret += to_string(i + 1);
        ret += ":\n";
        ctx->depth++;
        ret += util::tab(ctx->depth);
        ret += "goto ";
        ret += sname;
        ret += ";";
        ctx->depth--;
        ret += "\n";
    }
    // default
    const char* defaultName = sw->default_.str;
    if (defaultName != nullptr && strlen(defaultName)) {
        ret += util::tab(ctx->depth);
        ret += "default:\n";
        ctx->depth++;
        ret += util::tab(ctx->depth);
        ret += "goto ";
        ret += defaultName;
        ret += ";\n";
        ctx->depth--;
    }
    
    // end of switch routine
    ctx->depth--;
    ret += util::tab(ctx->depth);
    ret += "}\n";
    return ret;
}
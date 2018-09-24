#ifndef _WASMDEC_PARSER_H
#define _WASMDEC_PARSER_H

#include "../convert/Conversion.h"

namespace wasmdec {
    namespace parsers {
        string block(Context*, Expression*);
        string binary(Context*, Expression*);
        string get_local(Context*, Expression*);
        string _return(Context*, Expression*);
        string _if(Context*, Expression*);
        string _const(Context*, Expression*);
        string nop(Context*, Expression*);
        string get_global(Context*, Expression*);
        string set_global(Context*, Expression*);
        string _break(Context*, Expression*);
        string call(Context*, Expression*);
        string call_import(Context*, Expression*);
        string loop(Context*, Expression*);
        string _switch(Context*, Expression*);
        string call_indirect(Context*, Expression*);
        string set_local(Context*, Expression*);
        string load(Context*, Expression*);
        string store(Context*, Expression*);
        string unary(Context*, Expression*);
        string select(Context*, Expression*);
        string drop(Context*, Expression*);
        string host(Context*, Expression*);
        string unreachable(Context*, Expression*);
        string atmoics(Context*, Expression*);
        string expression(Context*, Expression*);
    }
}

#endif
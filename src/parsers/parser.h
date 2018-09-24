#ifndef _WASMDEC_PARSER_H
#define _WASMDEC_PARSER_H

#include "../convert/Conversion.h"
using namespace std;

namespace wasmdec {
    namespace parsers {
        std::string block(Context*, Expression*);
        std::string binary(Context*, Expression*);
        std::string get_local(Context*, Expression*);
        std::string _return(Context*, Expression*);
        std::string _if(Context*, Expression*);
        std::string _const(Context*, Expression*);
        std::string nop(Context*, Expression*);
        std::string get_global(Context*, Expression*);
        std::string set_global(Context*, Expression*);
        std::string _break(Context*, Expression*);
        std::string call(Context*, Expression*);
        std::string call_import(Context*, Expression*);
        std::string loop(Context*, Expression*);
        std::string _switch(Context*, Expression*);
        std::string call_indirect(Context*, Expression*);
        std::string set_local(Context*, Expression*);
        std::string load(Context*, Expression*);
        std::string store(Context*, Expression*);
        std::string unary(Context*, Expression*);
        std::string select(Context*, Expression*);
        std::string drop(Context*, Expression*);
        std::string host(Context*, Expression*);
        std::string unreachable(Context*, Expression*);
        std::string atomics(Context*, Expression*);
        std::string expression(Context*, Expression*);
    }
}

#endif
#ifndef _WASMDEC_PARSER_H
#define _WASMDEC_PARSER_H

#include "../convert/Conversion.h"

namespace wasmdec {
    typedef string (*WasmParser) (Context*, Expression*);
    namespace parsers {
        WasmParser block;
        WasmParser binary;
        WasmParser get_local;
        WasmParser _return;
        WasmParser _if;
        WasmParser _const;
        WasmParser nop;
        WasmParser get_global;
        WasmParser set_global;
        WasmParser _break;
        WasmParser call;
        WasmParser call_import;
        WasmParser loop;
        WasmParser _switch;
        WasmParser call_indirect;
        WasmParser set_local;
        WasmParser load;
        WasmParser store;
        WasmParser unary;
        WasmParser select;
        WasmParser drop;
        WasmParser host;
        WasmParser unreachable;
    }
}
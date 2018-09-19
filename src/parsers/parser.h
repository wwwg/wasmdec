#ifndef _WASMDEC_PARSER_H
#define _WASMDEC_PARSER_H

#include "../convert/Conversion.h"

namespace wasmdec {
    typedef string (*WasmParser) (Context*, Expression*);
    namespace parsers {
        WasmParser block;
    };
};

#endif
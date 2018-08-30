#ifndef _DISASM_CONFIG_H
#define _DISASM_CONFIG_H

enum DisasmMode {
	Wasm,
	AsmJs,
	Wast,
	None = 0
};

class DisasmConfig {
public:
    bool debug;
    bool extra;
    bool includePreamble;
    string fnPreface;
    DisasmMode mode;
    inline DisasmConfig(bool _debug, bool _extra, DisasmMode _mode) {
        debug = _debug;
        extra = extra;
        mode = _mode;
        includePreamble = true;
        fnPreface = "";
    }
};

#endif
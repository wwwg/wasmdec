#include "wasm.h"
#include "wasm-binary.h"
#include "wasm-printing.h"
#include "wasm-s-parser.h"

#include "Emitter.h"
#include "Conversion.h"
#pragma once

#include <string>

using namespace std;

namespace wdis {
	class CodeGenerator {
	public:
		wasm::Module module;
		vector<char> binary;
		wasm::WasmBinaryBuilder parser;
		bool isDebug;
		Emitter emit;
		CodeGenerator(vector<char>* inbin, bool useDebug) : binary((*inbin)), parser(module, binary, useDebug), emit(useDebug) {
			isDebug = useDebug;
			debug("Parsing wasm binary...\n");
			try {
				parser.read();
			} catch (wasm::ParseException& err) {
				err.dump(cerr);
				cout << "Failed to parse wasm binary." << endl;
				return;
			}
			debug("Parsed bin successfully.\n");
		}
		void gen() {
			debug("Starting code generation...\n");
			// Process imports
			if (module.imports.size()) {
				emit.comment("WASM imports:");
				for (auto& i : module.imports) {
					// cout << "Got import: " << i->name << endl;
					string decl = Convert::getDecl(&module, i);
					emit << decl << endl;
				}
			} else {
				emit.comment("No WASM imports");
				emit.ln();
			}
			// Process functions
			emit.comment("WASM functions:");
			emit.ln();
			for (const auto &func : parser.functions) {
				emit << Convert::getDecl(func) << Convert::getFuncBody(&module, func) << endl;
			}
			debug("Code generation complete.\n");
		}
		string getEmittedCode() {
			return emit.getCode();
		}
	protected:
		void debug(string msg) {
			if (isDebug) {
				cerr << "wdis CodeGen: " << msg;
			}
		}
		void debugf(string msg) {
			if (isDebug) {
				cerr << msg;
			}
		}
	};
} // namespace wdis
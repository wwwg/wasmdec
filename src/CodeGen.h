#ifndef _CODEGEN_H
#define _EMITTER_H

#include "wasm.h"
#include "wasm-binary.h"
#include "wasm-printing.h"
#include "wasm-s-parser.h"
#include "Emitter.h"
#include "Conversion.h"

using namespace std;

namespace wdis {
	class CodeGenerator {
	public:
		wasm::Module module;
		vector<char> binary;
		wasm::WasmBinaryBuilder parser;
		bool isDebug;
		bool emitExtraData;
		Emitter emit;
		CodeGenerator(vector<char>* inbin, bool useDebug, bool _emitExtraData) : binary((*inbin)), parser(module, binary, useDebug) {
			isDebug = useDebug;
			emitExtraData = _emitExtraData;
			debug("Parsing wasm binary...\n");
			// Attempt to parse binary via Binaryen's AST parser
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
				// No imports, so just leave a comment
				emit.comment("No WASM imports.");
				emit.ln();
			}
			// Process functions
			if (parser.functions.size()) {
				emit.comment("WASM functions:");
				emit.ln();
				for (const auto &func : parser.functions) {
					if (emitExtraData) {
						// Emit information about the function as a comment
						wasm::Block* fnBody = func->body->cast<wasm::Block>();
						emit << "/*" << endl
						<< "\tFunction '" << func->name << "'" << endl
						<< "\tLocal variables: " << func->vars.size() << endl
						<< "\tParameters: " << func->params.size() << endl
						<< "\tImmediate block expressions: " << fnBody->list.size() << endl
						<< "*/" << endl;
					}
					emit << Convert::getDecl(func) << Convert::getFuncBody(&module, func, emitExtraData) << endl;
				}
			} else {
				emit.comment("No WASM functions.");
				emit.ln();
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

#endif // _EMITTER_H
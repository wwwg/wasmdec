#include "Decompiler.h"

#ifdef ASM_JS_DECOMP

#ifndef wasm_asm2wasm_h
#include "asm2wasm.h"
#endif

#endif

Decompiler::Decompiler(DisasmConfig conf, vector<char>* inbin)
: binary((*inbin)) {
	if (conf.includePreamble) {
		emit.preamble();
	}
	functionPreface = conf.fnPreface;
	rawMemory = vector<char>();
	rawTable = vector<char>();
	isDebug = conf.debug;
	emitExtraData = conf.extra;
	mode = conf.mode;

	if (mode == DisasmMode::Wasm) {
		debug("Creating WasmBinaryBuilder\n");
		// Create parser
		wasm::WasmBinaryBuilder parser(module, binary, conf.debug);
		debug("Parsing wasm binary...\n");
		// Attempt to parse binary via Binaryen's AST parser
		try {
			parser.read();
			parserFailed = false;
		} catch (exception& err) {
			cerr << "wasmdec: FAILED to parse wasm binary: " << endl;
			cerr << err.what() << endl;
			cerr << endl;
			fail();
			return;
		}
	} else if (mode == DisasmMode::Wast) {
		try {
			debug("Starting SExpressionParser\n");
			string binary_s(binary.begin(), binary.end());
			SExpressionParser parser(const_cast<char*>(binary_s.c_str()));
			Element& _root = *(parser.root);
			debug("Starting SExpressionWasmBuilder\n");
			SExpressionWasmBuilder sbuilder(module, *_root[0]);
			parserFailed = false;
		} catch (wasm::ParseException& err) {
			cerr << "wasmdec: FAILED to parse wast: " << endl;
			err.dump(cerr);
			cerr << endl;
			fail();
			return;
		}
	}
	
	#ifdef ASM_JS_DECOMP

	else if (mode == DisasmMode::AsmJs) {
		// preprocess
		debug("Preprocessing asm.js\n");
		Asm2WasmPreProcessor a2wp;
		string binary_s(binary.begin(), binary.end());
		char* begin = a2wp.process(const_cast<char*>(binary_s.c_str()));

		// parse
		debug("Initializing parser\n");
		cashew::Parser<Ref, DotZeroValueBuilder> parser_builder;
		Ref js = parser_builder.parseToplevel(begin);

		// compile to wasm
		debug("Compiling to wasm\n");
		PassOptions popts;
		popts.debug = isDebug;
		Asm2WasmBuilder a2w(module,
							a2wp,
							isDebug,
							TrapMode::JS,
							popts,
							true, true, false);
		a2w.processAsm(js);
		debug("Compilation finished");
	}

	#endif

	debug("Parsed bin successfully.\n");
	dctx = new DecompilerCtx();
}
void Decompiler::fail() {
	debug("Decompiler::fail() called!\n");
	parserFailed = true;
}
Decompiler::Decompiler(DisasmConfig conf, vector<char> inbin)
: binary(inbin) {
	if (conf.includePreamble) {
		emit.preamble();
	}
	functionPreface = conf.fnPreface;
	rawMemory = vector<char>();
	rawTable = vector<char>();
	isDebug = conf.debug;
	emitExtraData = conf.extra;
	mode = conf.mode;
	if (mode == DisasmMode::Wasm) {
		debug("Creating WasmBinaryBuilder\n");
		// Create parser
		wasm::WasmBinaryBuilder parser(module, binary, conf.debug);
		debug("Parsing wasm binary...\n");
		// Attempt to parse binary via Binaryen's AST parser
		try {
			parser.read();
			parserFailed = false;
		} catch (exception& err) {
			cerr << "wasmdec: FAILED to parse wasm binary: " << endl;
			cerr << err.what() << endl;
			cerr << endl;
			fail();
			return;
		}
	} else if (mode == DisasmMode::Wast) {
		try {
			debug("Starting SExpressionParser\n");
			string binary_s(binary.begin(), binary.end());
			SExpressionParser parser(const_cast<char*>(binary_s.c_str()));
			Element& _root = *(parser.root);
			debug("Starting SExpressionWasmBuilder\n");
			SExpressionWasmBuilder sbuilder(module, *_root[0]);
			parserFailed = false;
		} catch (wasm::ParseException& err) {
			cerr << "wasmdec: FAILED to parse wast: " << endl;
			err.dump(cerr);
			cerr << endl;
			fail();
			return;
		}
	}
	
	#ifdef ASM_JS_DECOMP

	else if (mode == DisasmMode::AsmJs) {
		// preprocess
		debug("Preprocessing asm.js\n");
		Asm2WasmPreProcessor a2wp;
		string binary_s(binary.begin(), binary.end());
		char* begin = a2wp.process(const_cast<char*>(binary_s.c_str()));

		// parse
		debug("Initializing parser\n");
		cashew::Parser<Ref, DotZeroValueBuilder> parser_builder;
		Ref js = parser_builder.parseToplevel(begin);

		// compile to wasm
		debug("Compiling to wasm\n");
		PassOptions popts;
		popts.debug = isDebug;
		Asm2WasmBuilder a2w(module,
							a2wp,
							isDebug,
							TrapMode::JS,
							popts,
							true, true, false);
		a2w.processAsm(js);
		debug("Compilation finished");
	}

	#endif

	debug("Parsed bin successfully.\n");
	dctx = new DecompilerCtx();
}
void Decompiler::decompile() {
	if (parserFailed) {
		return;
	}
	debug("Starting code generation...\n");
	// Process imports
	if (module.imports.size()) {
		debug("Processing imports...\n");
		emit.comment("WASM imports:");
		for (auto& i : module.imports) {
			// cout << "Got import: " << i->name << endl;
			emit << "/*" << endl
			<< "\tImport '" << i->name.str << "':" << endl
			<< "\tModule: '" << i->module.str << "'" << endl
			<< "\tBase: '" << i->base.str << "'" << endl
			<< "*/" << endl;
			string decl = Convert::getDecl(&module, i);
			emit << decl << endl;
		}
		debug("Processed imports\n");
	} else {
		debug("No wasm imports detected\n");
		// No imports, so just leave a comment
		emit.comment("No WASM imports.");
		emit.ln();
	}
	// Process globals
	if (module.globals.size()) {
		debug("Processing globals...\n");
		Context gctx = Context(&module); // Initialize a global context to parse expressions with
		gctx.isGlobal = true;
		emit.comment("WASM globals:");
		for (auto& glb : module.globals) {
			string globalType = Convert::resolveType(glb->type);
			string globalInitializer = Convert::parseExpr(&gctx, glb->init);
			if (!glb->mutable_) { // Non-mutable global is represented by const
				emit << "const ";
			}
			emit << globalType << " " << glb->name.str << " = " << globalInitializer << ";" << endl;
		}
		debug("Processed globals.\n");
	} else {
		debug("No wasm globals.\n");
		// No globals, so just leave a comment
		emit.comment("No WASM globals.");
	}
	emit.ln();
	// Process functions
	if (module.functions.size()) {
		debug("Processing wasm functions...\n");
		emit.comment("WASM functions:");
		emit.ln();
		int funcNumber = 0;
		for (const auto &func : module.functions) {
			Function* fn = func.get();
			debug("Processing function #" + to_string(funcNumber) + "\n");
			debug(" (name: '" + string(fn->name.str) + "')\n");
			funcNumber++;
			if (emitExtraData) {
				// Emit information about the function as a comment
				emit << "/*" << endl
				<< "\tFunction '" << fn->name << "'" << endl
				<< "\tLocal variables: " << fn->vars.size() << endl
				<< "\tParameters: " << fn->params.size() << endl
				<< "*/" << endl;
			}
			Context ctx = Context(fn, &module, dctx);
			ctx.functionLevelExpression = true;
			emit << Convert::getDecl(fn, functionPreface) << Convert::getFuncBody(ctx, emitExtraData) << endl;
		}
	} else {
		emit.comment("No WASM functions.");
		emit.ln();
	}
	// Process exports
	if (module.exports.size()) {
		debug("Processing wasm exports...\n");
		emit << "\n/*" << endl
		<< "\tExported WASM functions:" << endl;
		for (const auto& expt : module.exports) {
			// Stringify export to comment
			emit << "\tFunction '" << Convert::getFName(expt->value) << "':" << endl
				<< "\t\tWASM name: '" << expt->value.str << "'" << endl
				<< "\t\tExport name: '" << expt->name.str << "'" << endl << endl;
		}
		emit << "*/" << endl;
		debug("Processed wasm exports.\n");
	} else {
		emit.comment("No WASM exports.");
		emit.ln();
	}
	debug("Code generation complete.\n");
	vector<char>().swap(binary);
}
string Decompiler::getEmittedCode() {
	debug("Exporting emitted code.\n");
	return emit.getCode();
}
// Debug functions
void Decompiler::debug(string msg) {
	if (isDebug) {
		cerr << "wasmdec CodeGen: " << msg;
	}
}
void Decompiler::debugf(string msg) {
	if (isDebug) {
		cerr << msg;
	}
}
bool Decompiler::failed() {
	// TODO : Develop this function to support other code generation failures
	return parserFailed;
}
vector<char> Decompiler::dumpMemory() {
	if (module.memory.exists && module.memory.imported) {
		for (const auto &seg : module.memory.segments) {
			// Push each raw byte from each segment into raw memory vector
			for (const char byte : seg.data) {
				rawMemory.push_back(byte);
			}
		}
		return rawMemory;
	} else {
		return vector<char>();
	}
}
vector<char> Decompiler::dumpTable() {
	if (module.table.exists && module.table.imported) {
		for (const auto &seg : module.table.segments) {
			for (const auto &name : seg.data) {
				const char* _data = name.c_str();
				char* i = (char*)_data;
				while (i[0] != '\0') {
					rawTable.push_back((char)i[0]);
					++i;
				}
			}
		}
		return rawTable;
	} else {
		return vector<char>();
	}
}
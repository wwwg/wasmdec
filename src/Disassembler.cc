#include "Disassembler.h"
using namespace wasmdec;
using namespace std;

Disassembler::Disassembler(DisasmConfig conf, vector<char>* inbin)
: binary((*inbin)) {
	isDebug = conf.debug;
	emitExtraData = conf.extra;
	mode = conf.mode;
	if (mode == DisasmMode::Wasm) {
		// Create parser
		parser = new wasm::WasmBinaryBuilder(module, binary, conf.debug);
		debug("Parsing wasm binary...\n");
		// Attempt to parse binary via Binaryen's AST parser
		try {
			parser->read();
			parserFailed = false;
		} catch (wasm::ParseException& err) {
			cerr << "wasmdec: FAILED to parse wasm binary: " << endl;
			err.dump(cerr);
			cerr << endl;
			parserFailed = true;
			return;
		}
	} else if (mode == DisasmMode::Wast) {
		try {
			char* data = reinterpret_cast<char*>(binary.data());
			debug("Starting SExpressionParser\n");
			sparser = new SExpressionParser(const_cast<char*>(data));
			Element& _root = *sparser->root;
			debug("Starting SExpressionWasmBuilder\n");
			sbuilder = new SExpressionWasmBuilder(module, *_root[0]);
			parserFailed = false;
		} catch (wasm::ParseException& err) {
			cerr << "wasmdec: FAILED to parse wast: " << endl;
			err.dump(cerr);
			cerr << endl;
			parserFailed = true;
			return;
		}
	}
	debug("Parsed bin successfully.\n");
}
void Disassembler::gen() {
	if (parserFailed) {
		return;
	}
	debug("Starting code generation...\n");
	// Process imports
	if (module.imports.size()) {
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
	} else {
		// No imports, so just leave a comment
		emit.comment("No WASM imports.");
		emit.ln();
	}
	// Process globals
	if (module.globals.size()) {
		Context gctx = Context(&module); // Initialize a global context to parse expressions with
		gctx.isGlobal = true;
		emit.comment("WASM globals:");
		for (auto& glb : module.globals) {
			string globalType = Convert::resolveType(glb->type);
			string globalInitializer = Convert::parseExpr(&gctx, glb->init, 0);
			if (!glb->mutable_) { // Non-mutable global is represented by const
				emit << "const ";
			}
			emit << globalType << " " << glb->name.str << " = " << globalInitializer << ";" << endl;
		}
	} else {
		// No globals, so just leave a comment
		emit.comment("No WASM globals.");
	}
	emit.ln();
	// Process functions
	if (module.functions.size()) {
		emit.comment("WASM functions:");
		emit.ln();
		for (const auto &func : module.functions) {
			Function* fn = func.get();
			if (emitExtraData) {
				// Emit information about the function as a comment
				emit << "/*" << endl
				<< "\tFunction '" << fn->name << "'" << endl
				<< "\tLocal variables: " << fn->vars.size() << endl
				<< "\tParameters: " << fn->params.size() << endl
				<< "*/" << endl;
			}
			Context ctx = Context(fn, &module);
			emit << Convert::getDecl(fn) << Convert::getFuncBody(ctx, emitExtraData) << endl;
		}
	} else {
		emit.comment("No WASM functions.");
		emit.ln();
	}
	// Process exports
	if (module.exports.size()) {
		emit << "\n/*" << endl
		<< "\tExported WASM functions:" << endl;
		for (const auto& expt : module.exports) {
			// Stringify export to comment
			emit << "\tFunction '" << Convert::getFName(expt->value) << "':" << endl
				<< "\t\tWASM name: '" << expt->value.str << "'" << endl
				<< "\t\tExport name: '" << expt->name.str << "'" << endl << endl;
		}
		emit << "*/" << endl;
	} else {
		emit.comment("No WASM exports.");
		emit.ln();
	}
	debug("Code generation complete.\n");
}
string Disassembler::getEmittedCode() {
	return emit.getCode();
}
// Debug functions
void Disassembler::debug(string msg) {
	if (isDebug) {
		cerr << "wasmdec CodeGen: " << msg;
	}
}
void Disassembler::debugf(string msg) {
	if (isDebug) {
		cerr << msg;
	}
}
bool Disassembler::failed() {
	// TODO : Develop this function to support other code generation failures
	return parserFailed;
}
vector<char>* Disassembler::dumpMemory() {
	if (module.memory.exists && module.memory.imported) {
		for (const auto &seg : module.memory.segments) {
			// Push each raw byte from each segment into raw memory vector
			for (const char byte : seg.data) {
				rawMemory.push_back(byte);
			}
		}
		return &rawMemory;
	} else {
		return nullptr;
	}
}
vector<char>* Disassembler::dumpTable() {
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
		return &rawTable;
	} else {
		return nullptr;
	}
}
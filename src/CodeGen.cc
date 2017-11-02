#include "CodeGen.h"
using namespace wasmdec;
using namespace std;

CodeGenerator::CodeGenerator(vector<char>* inbin, bool useDebug, bool _emitExtraData) : binary((*inbin)), parser(module, binary, useDebug) {
	isDebug = useDebug;
	emitExtraData = _emitExtraData;
	debug("Parsing wasm binary...\n");
	// Attempt to parse binary via Binaryen's AST parser
	try {
		parser.read();
		parserFailed = false;
	} catch (wasm::ParseException& err) {
		cerr << "wasmdec: FAILED to parse wasm binary: " << endl;
		err.dump(cerr);
		cerr << endl;
		parserFailed = true;
		return;
	}
	debug("Parsed bin successfully.\n");
}
void CodeGenerator::gen() {
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
	if (parser.functions.size()) {
		emit.comment("WASM functions:");
		emit.ln();
		for (const auto &func : parser.functions) {
			if (emitExtraData) {
				// Emit information about the function as a comment
				emit << "/*" << endl
				<< "\tFunction '" << func->name << "'" << endl
				<< "\tLocal variables: " << func->vars.size() << endl
				<< "\tParameters: " << func->params.size() << endl
				<< "*/" << endl;
			}
			Context ctx = Context(func, &module);
			emit << Convert::getDecl(func) << Convert::getFuncBody(ctx, emitExtraData) << endl;
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
string CodeGenerator::getEmittedCode() {
	return emit.getCode();
}
// Debug functions
void CodeGenerator::debug(string msg) {
	if (isDebug) {
		cerr << "wasmdec CodeGen: " << msg;
	}
}
void CodeGenerator::debugf(string msg) {
	if (isDebug) {
		cerr << msg;
	}
}
bool CodeGenerator::failed() {
	// TODO : Develop this function to support other code generation failures
	return parserFailed;
}
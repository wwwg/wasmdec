#ifndef _CONVER_H
#include "Conversion.h"
#endif
using namespace std;
using namespace wasm;

string wdis::Convert::parseExpr(Module* mod, Function* func, Expression* ex, int depth) {
	string ret;
	if (ex->is<Block>()) {
		// Recursively parse blocks
		Block* blck = ex->cast<Block>();
		ret += getBlockBody(mod, func, blck, depth);
	} else if (ex->is<Binary>()) {
		// Binary operations, including conditionals and arithmetic
		Binary* spex = ex->cast<Binary>();
		string e1 = parseExpr(mod, func, spex->left, depth);
		string e2 = parseExpr(mod, func, spex->right, depth);
		string operation = getBinOperator(spex->op);
		ret += e1 + " " + operation + " " + e2;
	} else if (ex->is<GetLocal>()) {
		// Convert WASM local variable to C local variable
		GetLocal* spex = ex->cast<GetLocal>();
		ret += getLocal(spex->index);
	} else if (ex->is<Return>()) {
		Return* spex = ex->cast<Return>();
		if (spex->value) {
			// Insert expression as function return value
			ret += util::tab(depth) + "return ";
			ret += parseExpr(mod, func, spex->value, depth) + ";\n";
		} else {
			ret += "return;\n"; // For void functions
		}
	} else if (ex->is<If>()) {
		If* ife = ex->cast<If>();
		string cond = parseExpr(mod, func, ife->condition, depth);
		string trueBlock = parseExpr(mod, func, ife->ifTrue, depth);
		ret += util::tab(depth);
		ret += "if (" + cond + ") {\n";
		depth++;
		ret += util::tab(depth) + trueBlock;
		depth--;
		ret += "\n" + util::tab(depth) + "} ";
		if (ife->ifFalse) {
			// Insert else block
			string falseBlock = parseExpr(mod, func, ife->ifFalse, depth);
			ret += "else {\n";
			depth++;
			ret += util::tab(depth) + falseBlock + "\n";
			depth--;
			ret += util::tab(depth) + "}";
		} else {
			// No else statement
			ret += "// <No else block>\n";
		}
	} else if (ex->is<Const>()) {
		// Resolve constant's literal value to a syntactically valid C literal
		Literal* val = &(ex->cast<Const>()->value);
		ret += util::getLiteralValue(val);
	} else if (ex->is<Nop>()) {
		ret += util::tab(depth) + "// <Nop expression>\n"; // Nop expressions do nothing
	} else if (ex->is<GetGlobal>()) {
		// Global variable lookup
		ret += ex->cast<GetGlobal>()->name.str;
		// ret += "\n";
	} else if (ex->is<SetGlobal>()) {
		// Set global variable
		SetGlobal* gex = ex->cast<SetGlobal>();
		ret += util::tab(depth) + gex->name.str + " = ";
		// The value is an expression
		ret += parseExpr(mod, func, gex->value, depth) + ";\n";
	} else if (ex->is<Break>()) {
		Break* br = ex->cast<Break>();
		ret += util::tab(depth);
		if (br->condition) {
			// Conditional breaking
			ret += "if (" + parseExpr(mod, func, br->condition, depth) + ") break;";
		} else {
			// Literal breaking
			ret += "break;";
		}
		ret += "\n";
	} else if (ex->is<Call>()) {
		// Function call
		Call* fnCall = ex->cast<Call>();
		ret += getFName(fnCall->target) + parseOperandList(&(fnCall->operands), func, mod, depth);
	} else if (ex->is<CallImport>()) {
		// Imported function call
		CallImport* imCall = ex->cast<CallImport>();
		ret += "/* Import call */ ";
		ret += imCall->target.str + parseOperandList(&(imCall->operands), func, mod, depth);
	} else if (ex->is<Loop>()) {
		// TODO : Implement WASM loop routine conversions
	} else if (ex->is<Switch>()) {
		// TODO : Implement WASM switch routine conversions
	} else if (ex->is<CallIndirect>()) {
		// TODO : Implement CallIndirect expressions
	} else if (ex->is<SetLocal>()) {
		//
	} else if (ex->is<Load>()) {
		// TODO : Implement WASM address loading
	} else if (ex->is<Store>()) {
		// TODO : Implement WASM address storing
	} else if (ex->is<Unary>()) {
		// TODO : WASM unary operations
	} else if (ex->is<AtomicRMW>()) {
		// WASM currently has no support for atomics
		ret = "/* Atomic operation unsupported */\n";
	} else if (ex->is<AtomicCmpxchg>()) {
		// WASM currently has no support for atomics
		ret = "/* Atomic operation unsupported */\n";
	} else if (ex->is<Select>()) {
		// TODO : implement select expressions
	} else if (ex->is<Drop>()) {
		// TODO : implement drop expressions
	} else if (ex->is<Host>()) {
		// TODO : implement host expressions
	} else if (ex->is<Unreachable>()) {
		// Unreachable contains no information
		ret = "/* Unreachable */";
	}
	cout << "<Parsed>" << endl
	<< ret << endl
	<< "</Parsed>" << endl << endl;
	return ret;
}
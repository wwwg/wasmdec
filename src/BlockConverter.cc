#ifndef _CONVER_H
#include "Conversion.h"
#endif
using namespace std;
using namespace wasm;

string wdis::Convert::parseExpr(Module* mod, Expression* ex, int depth) {
	string ret;
	if (ex->is<Unary>()) {
		// TODO
	} else if (ex->is<Block>()) {
		// Recursively parse blocks
		Block* blck = ex->cast<Block>();
		ret += getBlockBody(mod, blck, depth);
	} else if (ex->is<Binary>()) {
		// Binary operations, including conditionals and arithmetic
		Binary* spex = ex->cast<Binary>();
		string e1 = parseExpr(mod, spex->left, depth);
		string e2 = parseExpr(mod, spex->right, depth);
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
			ret += parseExpr(mod, spex->value, depth) + ";\n";
		} else {
			ret += "return;\n"; // For void functions
		}
	} else if (ex->is<If>()) {
		If* ife = ex->cast<If>();
		string cond = parseExpr(mod, ife->condition, depth);
		string trueBlock = parseExpr(mod, ife->ifTrue, depth);
		ret += util::tab(depth);
		ret += "if (" + cond + ") {\n";
		depth++;
		ret += util::tab(depth) + trueBlock;
		depth--;
		ret += "\n" + util::tab(depth) + "} ";
		if (ife->ifFalse) {
			// Insert else block
			string falseBlock = parseExpr(mod, ife->ifFalse, depth);
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
		ret = "// <Nop expression>\n"; // Nop expressions do nothing
	} else if (ex->is<GetGlobal>()) {
		// Global variable lookup
		ret += ex->cast<GetGlobal>()->name.str;
		// ret += "\n";
	} else if (ex->is<SetGlobal>()) {
		// Set global variable
		SetGlobal* gex = ex->cast<SetGlobal>();
		ret += util::tab(depth) + gex->name.str + " = ";
		// The value is an expression
		ret += parseExpr(mod, gex->value, depth) + ";\n";
	} else if (ex->is<Break>()) {
		Break* br = ex->cast<Break>();
		ret += util::tab(depth);
		if (br->condition) {
			// Conditional breaking
			ret += "if (" + parseExpr(mod, br->condition, depth) + ") break;";
		} else {
			// Literal breaking
			ret += "break;";
		}
		ret += "\n";
	}
	cout << "<Start expression parse result>" << endl
	<< ret << endl
	<< "<End expression parse result>" << endl;
	return ret;
}
string wdis::Convert::getBlockBody(Module* mod, Block* blck, int depth) {
	// Stream all block expressions and components into a string
	stringstream s;
	depth++;
	for (auto& expr : blck->list) {
		s << parseExpr(mod, expr, depth);
	}
	depth--;
	return s.str();
}
string wdis::Convert::getFuncBody(Module* mod, Function* fn) {
	string fnBody;
	fnBody += " {\n";
	// Function bodies are block expressions
	fnBody += parseExpr(mod, fn->body, -1);
	fnBody += "}";
	return fnBody;
}
#include "Conversion.h"
using namespace std;
using namespace wasm;

string wdis::Convert::parseExpr(Context* ctx, Expression* ex, int depth) {
	string ret;
	if (ex->is<Block>()) {
		// Recursively parse blocks
		Block* blck = ex->cast<Block>();
		depth++;
		ret += getBlockBody(ctx, blck, depth);
		depth--;
	} else if (ex->is<Binary>()) {
		// Binary operations, including conditionals and arithmetic
		Binary* spex = ex->cast<Binary>();
		string e1 = parseExpr(ctx, spex->left, depth);
		string e2 = parseExpr(ctx, spex->right, depth);
		string operation = getBinOperator(spex->op);
		ret += e1 + " " + operation + " " + e2;
	} else if (ex->is<GetLocal>()) {
		// Convert WASM local variable to C local variable
		GetLocal* spex = ex->cast<GetLocal>();
		ret += getLocal(spex->index);
	} else if (ex->is<Return>()) {
		Return* spex = ex->cast<Return>();
		if (depth < 1) {
			ret += util::tab(1);
		} else {
			ret += util::tab(depth);
		}
		if (spex->value) {
			// Insert expression as function return value
			ret += "return ";
			ret += parseExpr(ctx, spex->value, depth) + ";\n";
		} else {
			ret += "return;\n"; // For void functions
		}
	} else if (ex->is<If>()) {
		If* ife = ex->cast<If>();
		string cond = parseExpr(ctx, ife->condition, depth);
		string trueBlock = parseExpr(ctx, ife->ifTrue, depth);
		ret += util::tab(depth);
		ret += "if (" + cond + ") {\n";
		ret += trueBlock;
		ret += "\n" + util::tab(depth) + "} ";
		if (ife->ifFalse) {
			// Insert else block
			string falseBlock = parseExpr(ctx, ife->ifFalse, depth);
			ret += "else {\n";
			ret += util::tab(depth) + falseBlock + "\n";
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
		ret += parseExpr(ctx, gex->value, depth) + ";\n";
	} else if (ex->is<Break>()) {
		Break* br = ex->cast<Break>();
		ret += util::tab(depth);
		if (br->condition) {
			// Conditional breaking
			ret += "if (" + parseExpr(ctx, br->condition, depth) + ") break;";
		} else {
			// Literal breaking
			ret += "break;";
		}
	} else if (ex->is<Call>()) {
		// Function call
		Call* fnCall = ex->cast<Call>();
		if (depth < 1) {
			ret += util::tab(1);
		} else {
			ret += util::tab(depth);
		}
		ret += getFName(fnCall->target) + parseOperandList(ctx, &(fnCall->operands), depth);
		ret += ";\n";
	} else if (ex->is<CallImport>()) {
		// Imported function call
		CallImport* imCall = ex->cast<CallImport>();
		// ret += "/* Import call */ ";
		if (depth < 1) {
			ret += util::tab(1);
		} else {
			ret += util::tab(depth);
		}
		ret += imCall->target.str + parseOperandList(ctx, &(imCall->operands), depth);
		ret += ";\n";
	} else if (ex->is<Loop>()) {
		Loop* lex = ex->cast<Loop>();
		ret += util::tab(depth);
		ret += "while (1) {";
		if (lex->name.str) {
			 ret += " // Loop name: '";
			 ret += lex->name.str;
			 ret += "'";
		}
		ret += "\n";
		depth -= 1;
		ret += parseExpr(ctx, lex->body, depth);
		ret += "\n";
		if (depth < 1) {
			ret += util::tab(1);
		} else {
			ret += util::tab(depth);
		}
		ret += "} " ;
		if (lex->name.str) {
			 ret += "// End of loop '";
			 ret += lex->name.str;
			 ret += "'";
		}
		ret += "\n";
	} else if (ex->is<Switch>()) {
		// TODO : Implement WASM switch routine conversions
	} else if (ex->is<CallIndirect>()) {
		// TODO : Implement CallIndirect expressions
	} else if (ex->is<SetLocal>()) {
		// Resolve variable's C name
		SetLocal* sl = ex->cast<SetLocal>();
		/*
		int idx = util::getLocalIndex(ctx->fn, sl->index);
		*/
		int idx = sl->index;
		ret += util::tab(depth);
		ret += getLocal((Index)idx);
		ret += " = ";
		// Resolve the value to be set
		ret += parseExpr(ctx, sl->value, depth);
		ret += ";\n";
	} else if (ex->is<Load>()) {
		// TODO : Implement WASM address loading
	} else if (ex->is<Store>()) {
		Store* sxp = ex->cast<Store>();
		string var = parseExpr(ctx, sxp->ptr, depth);
		string val = parseExpr(ctx, sxp->value, depth);
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
		Drop* dex = ex->cast<Drop>();
		ret += "/* Drop routine */\n";
		ret += parseExpr(ctx, dex->value, depth);
		ret += "/* End of drop routine */\n";
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
#include "Conversion.h"
using namespace std;
using namespace wasm;

string wasmdec::Convert::parseExpr(Context* ctx, Expression* ex) {
	string ret;
	if (ex->is<Block>()) {
		// Recursively parse blocks
		Block* blck = ex->cast<Block>();
		ctx->depth++;
		ret += getBlockBody(ctx, blck);
		ctx->depth--;
	} else if (ex->is<Binary>()) {
		// Binary operations, including conditionals and arithmetic
		Binary* spex = ex->cast<Binary>();
		ctx->lastExpr = ex;
		string e1 = parseExpr(ctx, spex->left);
		ctx->lastExpr = ex;
		string e2 = parseExpr(ctx, spex->right);
		ret += getBinOperator(e1, spex->op, e2);
	} else if (ex->is<GetLocal>()) {
		// Convert WASM local variable to C local variable
		GetLocal* spex = ex->cast<GetLocal>();
		ret += getLocal(spex->index);
	} else if (ex->is<Return>()) {
		Return* spex = ex->cast<Return>();
		if (ctx->depth < 1) {
			ret += util::tab(1);
		} else {
			ret += util::tab(ctx->depth);
		}
		if (spex->value) {
			// Insert expression as function return value
			ret += "return ";
			ctx->lastExpr = ex;
			ret += parseExpr(ctx, spex->value) + ";\n";
		} else {
			ret += "return;\n"; // For void functions
		}
	} else if (ex->is<If>()) {
		If* ife = ex->cast<If>();
		ctx->lastExpr = ex;
		ctx->isIfCondition = true;
		string cond = parseExpr(ctx, ife->condition);
		ctx->isIfCondition = false;
		ctx->lastExpr = ex;
		string trueBlock = parseExpr(ctx, ife->ifTrue);
		ret += util::tab(ctx->depth);
		ret += "if (" + cond + ") {\n";
		ret += trueBlock;
		ret += "\n" + util::tab(ctx->depth) + "} ";
		if (ife->ifFalse) {
			// Insert else block
			ctx->lastExpr = ex;
			string falseBlock = parseExpr(ctx, ife->ifFalse);
			ret += "else {\n";
			ret += util::tab(ctx->depth) + falseBlock + "\n";
			ret += util::tab(ctx->depth) + "}";
		} else {
			// No else statement
			ret += "// <No else block>\n";
		}
	} else if (ex->is<Const>()) {
		// Resolve constant's literal value to a syntactically valid C literal
		Literal* val = &(ex->cast<Const>()->value);
		ret += util::getLiteralValue(val);
	} else if (ex->is<Nop>()) {
		ret += util::tab(ctx->depth) + "// <Nop expression>\n"; // Nop expressions do nothing
	} else if (ex->is<GetGlobal>()) {
		// Global variable lookup
		ret += ex->cast<GetGlobal>()->name.str;
		// ret += "\n";
	} else if (ex->is<SetGlobal>()) {
		// Set global variable
		SetGlobal* gex = ex->cast<SetGlobal>();
		bool isInline = false;
		if (ctx->lastExpr) {
			if (ctx->isIfCondition) {
				isInline = true;
			}
		}
		bool isInPolyAssignment = ((ctx->lastExpr != nullptr)
								&& (ctx->lastExpr->is<SetLocal>()
								|| ctx->lastExpr->is<SetGlobal>()
								|| ctx->lastExpr->is<Store>()));

		ret += util::tab(ctx->depth) + gex->name.str + " = ";
		// The value is an expression
		ctx->lastExpr = ex;
		ret += parseExpr(ctx, gex->value);
		if (!isInline && !isInPolyAssignment && !ctx->isIfCondition) {
			ret += ";\n";
		}
	} else if (ex->is<Break>()) {
		Break* br = ex->cast<Break>();
		ret += util::tab(ctx->depth);
		if (br->condition) {
			// Conditional breaking
			ctx->lastExpr = ex;
			ret += "if (" + parseExpr(ctx, br->condition) + ") break;";
		} else {
			// Literal breaking
			ret += "break;";
		}
		if (br->value) {
			ctx->lastExpr = ex;
			string val = parseExpr(ctx, br->value);
			// TODO : parse break values
			// cout << "Break val: " << val << endl;
		}
	} else if (ex->is<Call>()) {
		// Function call
		Call* fnCall = ex->cast<Call>();
		if (ctx->depth < 1) {
			ret += util::tab(1);
		} else {
			ret += util::tab(ctx->depth);
		}
		ret += getFName(fnCall->target) + parseOperandList(ctx, &(fnCall->operands));
		ret += ";\n";
	} else if (ex->is<CallImport>()) {
		// Imported function call
		CallImport* imCall = ex->cast<CallImport>();
		// ret += "/* Import call */ ";
		if (ctx->depth < 1) {
			ret += util::tab(1);
		} else {
			ret += util::tab(ctx->depth);
		}
		ret += imCall->target.str + parseOperandList(ctx, &(imCall->operands));
		ret += ";\n";
	} else if (ex->is<Loop>()) {
		Loop* lex = ex->cast<Loop>();
		ret += util::tab(ctx->depth);
		ret += "while (1) {";
		if (lex->name.str) {
			 ret += " // Loop name: '";
			 ret += lex->name.str;
			 ret += "'";
		}
		ret += "\n";
		ctx->depth -= 1;
		ctx->lastExpr = ex;
		ret += parseExpr(ctx, lex->body);
		ret += "\n";
		if (ctx->depth < 1) {
			ret += util::tab(1);
		} else {
			ret += util::tab(ctx->depth);
		}
		ret += "} " ;
		if (lex->name.str) {
			 ret += "// End of loop '";
			 ret += lex->name.str;
			 ret += "'";
		}
		ret += "\n";
	} else if (ex->is<Switch>()) {
		/*
			how wasm switches work:

			switch (<topmost stack variable>) {
				case <index of body expression>:
					goto <body expression>
				default:
					<default value>
			}
		*/
		// cout << "switch!\n" << endl;
		Switch* sw = ex->cast<Switch>();
		// start of switch routine
		ret += util::tab(ctx->depth);
		ret += "switch (";
		ret += getLocal(ctx->lastSetLocal);
		ret += ") {\n";
		ctx->depth++;
		
		// routine body
		for (unsigned int i = 0; i < sw->targets.size(); ++i) {
			string sname = string(sw->targets[i].str);
			ret += util::tab(ctx->depth);
			ret += "case ";
			ret += to_string(i + 1);
			ret += ":\n";
			ctx->depth++;
			ret += util::tab(ctx->depth);
			ret += "goto ";
			ret += sname;
			ret += ";";
			ctx->depth--;
			ret += "\n";
		}
		// default
		const char* defaultName = sw->default_.str;
		if (defaultName != nullptr && strlen(defaultName)) {
			ret += util::tab(ctx->depth);
			ret += "default:\n";
			ctx->depth++;
			ret += util::tab(ctx->depth);
			ret += "goto ";
			ret += defaultName;
			ret += ";\n";
			ctx->depth--;
		}
		
		// end of switch routine
		ctx->depth--;
		ret += util::tab(ctx->depth);
		ret += "}\n";
	} else if (ex->is<CallIndirect>()) {
		CallIndirect* ci = ex->cast<CallIndirect>();
		ctx->lastExpr = ex;
		string _icall = parseExpr(ctx, ci->target);
		ret += "// Indirect call:\n";
		ret += "(" + _icall + ")";
		ret += parseOperandList(ctx, &(ci->operands));
		ret += "; \n";
	} else if (ex->is<SetLocal>()) {
		// Resolve variable's C name
		SetLocal* sl = ex->cast<SetLocal>();
		bool isInline = false;
		if (ctx->lastExpr) {
			if (ctx->isIfCondition) {
				isInline = true;
			}
		}
		bool isInPolyAssignment = ((ctx->lastExpr != nullptr)
								&& (ctx->lastExpr->is<SetLocal>()
								|| ctx->lastExpr->is<SetGlobal>()
								|| ctx->lastExpr->is<Store>()));
		/*
		int idx = util::getLocalIndex(ctx->fn, sl->index);
		*/
		int idx = sl->index;
		ctx->lastSetLocal = idx;
		if (!isInline) {
			if (!isInPolyAssignment) {
				ret += util::tab(ctx->depth);
			}
		}
		ret += getLocal((Index)idx);
		ret += " = ";
		// Resolve the value to be set
		bool valueIsAssignment = (sl->value->is<SetLocal>()
								|| sl->value->is<SetGlobal>()
								|| sl->value->is<Store>());
		ctx->lastExpr = ex;
		ret += parseExpr(ctx, sl->value);
		if (!isInline && !valueIsAssignment) {
			ret += ";\n";
		}
	} else if (ex->is<Load>()) {
		// Memory loading
		Load* lxp = ex->cast<Load>();
		ctx->lastExpr = ex;
		string var = parseExpr(ctx, lxp->ptr);
		ret += util::tab(ctx->depth);
		ret += var;
	} else if (ex->is<Store>()) {
		Store* sxp = ex->cast<Store>();
		ctx->lastExpr = ex;
		string var = parseExpr(ctx, sxp->ptr);
		ctx->lastExpr = ex;
		string val = parseExpr(ctx, sxp->value);

		bool valueIsAssignment = (sxp->value->is<SetLocal>()
								|| sxp->value->is<SetGlobal>()
								|| sxp->value->is<Store>());
		
		bool isInline = false;
		if (ctx->lastExpr) {
			if (ctx->isIfCondition) {
				isInline = true;
			}
		}
		bool isInPolyAssignment = ((ctx->lastExpr != nullptr)
								&& (ctx->lastExpr->is<SetLocal>()
								|| ctx->lastExpr->is<SetGlobal>()
								|| ctx->lastExpr->is<Store>()));

		if (!isInline) {
			if (!isInPolyAssignment) {
				ret += util::tab(ctx->depth);
			}
		}
		ret += var;
		ret += " = ";
		ret += val;
		if (!isInline) {
			if (!valueIsAssignment) {
				ret += "; \n";;
			}
		}
	} else if (ex->is<Unary>()) {
		Unary* uex = ex->cast<Unary>();
		ctx->lastExpr = ex;
		string unaryEx = parseExpr(ctx, uex->value);
		ret += getUnary(unaryEx, uex->op);
	} else if (ex->is<AtomicRMW>()) {
		// WASM currently has no support for atomics
		ret = "/* Atomic operation unsupported */\n";
	} else if (ex->is<AtomicCmpxchg>()) {
		// WASM currently has no support for atomics
		ret = "/* Atomic operation unsupported */\n";
	} else if (ex->is<Select>()) {
		// Select is the WASM equivalent of C's ternary operator.
		Select* slex = ex->cast<Select>();
		ctx->lastExpr = ex;
		string cond = parseExpr(ctx, slex->condition);
		ctx->lastExpr = ex;
		string ifTrue = parseExpr(ctx, slex->ifTrue);
		ctx->lastExpr = ex;
		string ifFalse = parseExpr(ctx, slex->ifFalse);
		ret += "(" + cond + ") ? (" + ifTrue + ") : (" + ifFalse + ");\n";
	} else if (ex->is<Drop>()) {
		Drop* dex = ex->cast<Drop>();
		ret += util::tab(1);
		ret += "/* Drop routine */\n";
		ctx->lastExpr = ex;
		ret += parseExpr(ctx, dex->value);
		ret += util::tab(1);
		ret += "/* End of drop routine */\n";
	} else if (ex->is<Host>()) {
		Host* hexp = ex->cast<Host>();
		string hoperands = parseOperandList(ctx, &(hexp->operands));
		string hfunc = getHostFunc(hexp->op);
		ret += "/* Host call */\n" + hfunc + hoperands;
	} else if (ex->is<Unreachable>()) {
		// Unreachable contains no information
		ret = "/* Unreachable */";
	}
	/*
	cout << "<Parsed>" << endl
	<< ret << endl
	<< "</Parsed>" << endl << endl;
	*/
	return ret;
}
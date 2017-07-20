#include "Conversion.h"
using namespace std;
using namespace wasm;

string wdis::Convert::parseExpr(Module* mod, Expression* ex) {
	string ret("");
	if (ex->is<Unary>()) {
		// TODO
	} else if (ex->is<Block>()) {
		Block* blck = ex->cast<Block>();
		ret += getBlockBody(mod, blck);
	} else if (ex->is<Binary>()) {
		Binary* spex = ex->cast<Binary>();
		string e1 = parseExpr(mod, spex->left);
		string e2 = parseExpr(mod, spex->right);
		string operation = getBinOperator(spex->op);
		ret += e1;
		ret += " ";
		ret += operation;
		ret += " ";
		ret += e2;
	} else if (ex->is<GetLocal>()) {
		GetLocal* spex = ex->cast<GetLocal>();
		ret += getLocal(spex->index);
	} else if (ex->is<Return>()) {
		Return* spex = ex->cast<Return>();
		if (spex->value) {
			ret += "return ";
			ret += parseExpr(mod, spex->value);
			ret += ";\n";
		} else {
			ret += "return;\n"; // For void functions
		}
	} else if (ex->is<If>()) {
		If* ife = ex->cast<If>();
		string cond = parseExpr(mod, ife->condition);
		string trueBlock = parseExpr(mod, ife->ifTrue);
		string falseBlock = parseExpr(mod, ife->ifFalse);
		ret += "if (";
		ret += cond;
		ret += ") {\n\t";
		ret += trueBlock;
		ret += "\n} else {\n\t";
		ret += falseBlock;
		ret += "\n}";
	} else if (ex->is<Const>()) {
		Const* cex = ex->cast<Const>();
		Literal val = cex->value;
		string stype = resolveType(val.type);
		string sval;
		int32_t conv_i32;
		int64_t conv_i64;
		float conv_f32;
		double conv_f64;
		switch (val.type) {
			case WasmType::none:
			case WasmType::unreachable:
				sval = "0";
				break;
			case WasmType::i32:
				conv_i32 = val.geti32();
				sval = to_string(conv_i32);
				break;
			case WasmType::i64:
				conv_i64 = val.geti64();
				sval = to_string(conv_i64);
				break;
			case WasmType::f32:
				conv_f32 = val.getf32();
				sval = to_string(conv_f32);
				break;
			case WasmType::f64:
				conv_f64 = val.getf64();
				sval = to_string(conv_f64);
				break;
		}
		ret += sval;
	}
	cout << "Parsed expr to '" << ret << "' ";
	return ret;
}
string wdis::Convert::getBlockBody(Module* mod, Block* blck) {
	stringstream s;
	for (auto& expr : blck->list) {
		s << parseExpr(mod, expr);
	}
	return s.str();
}
string wdis::Convert::getFuncBody(Module* mod, Function* fn) {
	stringstream s;
	s << " {\n\t";
	s << parseExpr(mod, fn->body);
	s << "}";
	return s.str();
}
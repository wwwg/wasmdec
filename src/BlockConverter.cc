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
		ret += getArg(spex->index);
	} else if (ex->is<Return>()) {
		Return* spex = ex->cast<Return>();
		ret += "return ";
		ret += parseExpr(mod, spex->value);
		ret += ";\n";
	} else if (ex->is<If>()) {
		If* ife = ex->cast<If>();
		string cond = parseExpr(mod, ex->condition);
		string trueBlock = parseExpr(mod, ex->ifTrue);
		string falseBlock = parseExpr(mod, ex->ifFalse);
		ret += "if (";
		ret += cond;
		ret += ") {\n\t";
		ret += trueBlock;
		ret += "\n} else {\n\t";
		ret += falseBlock;
		ret += "\n}";
	}
	cout << "Parsed expr to '" << ret << "'" << endl;
	return ret;
}
string wdis::Convert::getBlockBody(Module* mod, Block* blck) {
	stringstream s;
	for (auto& expr : blck->list) {
		cout << "Parse block body Expression\n";
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
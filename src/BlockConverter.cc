#include "Conversion.h"
using namespace std;
using namespace wasm;

string wdis::Convert::parseExpr(Module* mod, Expression* ex) {
	string ret("");
	if (ex->is<Unary>()) {
		cout << "Unary operation\n";
	} else if (ex->is<Block>()) {
		cout << "WASM block\n";
		Block* blck = ex->cast<Block>();
		ret += getBlockBody(mod, blck);
	} else if (ex->is<Binary>()) {
		cout << "Binary operation\n";
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
		cout << "Get local\n";
		GetLocal* spex = ex->cast<GetLocal>();
		ret += getArg(spex->index);
	} else if (ex->is<Return>()) {
		cout << "Return block\n";
		Return* spex = ex->cast<Return>();
		ret += "return ";
		ret += parseExpr(mod, spex->value);
		ret += ";\n";
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
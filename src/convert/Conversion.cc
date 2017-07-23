#include "Conversion.h"

string wasmdec::Convert::getFName(wasm::Name name) {
	// Convert WASM names to C function names
	return "fn_" + string(name.str);
}
string wasmdec::Convert::getLocal(wasm::Index argIdx) {
	// Convert WASM function locals to C variable names
	return "local_" + to_string((int)argIdx);
}
string wasmdec::Convert::voidCall(wasm::Function* fn) {
	// Call a void function
	return getFName(fn->name) + "();";
}
string wasmdec::Convert::getBinOperator(string e1, wasm::BinaryOp bop, string e2) { // TODO : Add more binary operations
	// Convert WASM binary operations to their respective C representation
	string op;
	switch (bop) {
		case AddInt32:
		case AddInt64:
		case AddFloat32:
		case AddFloat64:
			op = "+";
			return e1 + " " + op + " " + e2;
			break;
		case SubInt32:
		case SubInt64:
		case SubFloat32:
		case SubFloat64:
			op = "-";
			return e1 + " " + op + " " + e2;
			break;
		case XorInt64:
		case XorInt32:
			op = "^";
			return e1 + " " + op + " " + e2;
			break;
		case OrInt64:
		case OrInt32:
			op = "||"; return e1 + " " + op + " " + e2;
			break;
		case MulInt32:
		case MulInt64:
		case MulFloat32:
		case MulFloat64:
			op = "*"; return e1 + " " + op + " " + e2;
			break;
		case EqInt32:
		case EqInt64:
		case EqFloat32:
		case EqFloat64:
			op = "=="; return e1 + " " + op + " " + e2;
			break;
		case NeInt32:
		case NeInt64:
		case NeFloat32:
		case NeFloat64:
			op = "!="; return e1 + " " + op + " " + e2;
			break;
		case AndInt32:
		case AndInt64:
			op = "&&"; return e1 + " " + op + " " + e2;
			break;
		case LeSInt64:
		case LeSInt32:
		case LeUInt32:
		case LeFloat32:
		case LeFloat64:
		case LeUInt64:
			op = "<="; return e1 + " " + op + " " + e2;
			break;
		case LtUInt32:
		case LtSInt32:
		case LtSInt64:
		case LtFloat32:
		case LtFloat64:
			op = "<"; return e1 + " " + op + " " + e2;
			break;
		case DivSInt32:
		case DivUInt32:
		case DivSInt64:
		case DivUInt64:
		case DivFloat32:
		case DivFloat64:
			op = "/"; return e1 + " " + op + " " + e2;
			break;
		case GtSInt64:
		case GtUInt64:
		case GtFloat64:
		case GtFloat32:
		case GtSInt32:
		case GtUInt32:
		case LtUInt64:
			op = ">"; return e1 + " " + op + " " + e2;
			break;
		case GeSInt64:
		case GeSInt32:
		case GeFloat64:
		case GeFloat32:
		case GeUInt32:
		case GeUInt64:
			op = ">="; return e1 + " " + op + " " + e2;
			break;
		case CopySignFloat32:
		case CopySignFloat64:
			return "copysign(" + e1 + ", " + e2 + ")";
			break;
		case RemSInt64:
		case RemUInt64:
		case RemSInt32:
		case RemUInt32:
			op = "%"; return e1 + " " + op + " " + e2;
			break;
		case RotLInt64:
		case RotLInt32:
			return "_rotl(" + e1 + ", " + e2 + ")";
			break;
		case RotRInt32:
		case RotRInt64:
			return "_rotr(" + e1 + ", " + e2 + ")";
			break;
		case ShlInt32:
		case ShlInt64:
			op = "<<"; return e1 + " " + op + " " + e2;
			break;
		case ShrUInt32:
		case ShrSInt32:
		case ShrUInt64:
		case ShrSInt64:
			op = ">>"; return e1 + " " + op + " " + e2;
			break;
		case MinFloat32:
		case MinFloat64:
			return "MIN(" + e1 + ", " + e2 + ")";
			break;
		case MaxFloat32:
		case MaxFloat64:
			return "MAX(" + e1 + ", " + e2 + ")";
			break;
	}
	op = "/* Unsupported binary operator */"; // Operation unimplemented or an unknown enumeration
	return op;
}
string wasmdec::Convert::resolveType(wasm::WasmType typ) {
	// Resolve wasm::WasmType to a C type
	switch (typ) {
		case wasm::WasmType::none:
		case wasm::WasmType::unreachable:
			return "void";
			break;
		case wasm::WasmType::i32:
			return "int32_t";
			break;
		case wasm::WasmType::i64:
			return "int64_t";
			break;
		case wasm::WasmType::f32:
			return "float32_t";
			break;
		case wasm::WasmType::f64:
			return "float64_t";
			break;
	}
}
string wasmdec::Convert::getDecl(wasm::FunctionType* typ, string fname) {
	// Get a C function decloration from a FunctionType and name
	string ret = resolveType(typ->result); // Return type
	ret += " "; // Space between ret type and name
	ret += fname;
	ret += "("; // Argument list
	for (int i = 0; i < typ->params.size(); ++i) {
		ret += resolveType(typ->params.at(i));
		ret += " ";
		ret += getLocal(i);
		if (i != (typ->params.size() - 1)) {
			ret += ", ";
		}
	}
	ret += ")";
	return ret;
}
string wasmdec::Convert::getDecl(wasm::FunctionType* typ, wasm::Name fname) {
	// Overload to support WASM names
	string ret = resolveType(typ->result); // Return type
	ret += " "; // Space between ret type and name
	ret += fname.str;
	ret += "("; // Argument list
	for (int i = 0; i < typ->params.size(); ++i) {
		ret += resolveType(typ->params.at(i));
		ret += " ";
		ret += getLocal(i);
		if (i != (typ->params.size() - 1)) {
			ret += ", ";
		}
	}
	ret += ")";
	return ret;
}
string wasmdec::Convert::getDecl(wasm::Function* fn) {
	// Get C function decloration from WASM function
	string ret = resolveType(fn->result); // Return type
	ret += " "; // Space between ret type and name
	ret += getFName(fn->name); // name
	ret += "("; // Argument list
	for (int i = 0; i < fn->params.size(); ++i) {
		ret += resolveType(fn->params.at(i));
		ret += " ";
		ret += getLocal(i);
		if (i != (fn->params.size() - 1)) {
			// Only append comma if the argument list isn't finished
			ret += ", ";
		}
	}
	ret += ")";
	return ret;
}
string wasmdec::Convert::getDecl(wasm::Module* m, unique_ptr<wasm::Import>& i) {
	// Convert WASM imports to their respective C declorations as C externs
	string ret = "extern ";
	if (i->kind == wasm::ExternalKind::Function) {
		// Function
		wasm::FunctionType* ft = util::resolveFType(m, i->functionType); // Lookup module types for this function's type
		ret += getDecl(ft, i->name); // Append its decloration
	} else if (i->kind == wasm::ExternalKind::Global) {
		// Global import variable
		ret += resolveType(i->globalType);
		ret += " ";
		ret += i->name.str;
		ret += ";";
	} else if (i->kind == wasm::ExternalKind::Memory) {
		// WASM memory is just a giant char array
		ret += "const char* ";
		ret += i->name.str;
		ret += "; // <Imported memory>";
	} else if (i->kind == wasm::ExternalKind::Table) {
		// TODO: More advanced table functionality
		ret += "wasm_table_t ";
		ret += i->name.str;
		ret += "; // <Imported table>";
	}
	return ret;
}
string wasmdec::Convert::parseOperandList(Context* ctx, ExpressionList* list, int depth) {
	if (list->size()) {
		string ret = "(";
		for (int i = 0; i < list->size(); ++i) {
			Expression* operand = list->operator[](i);
			string soperand = Convert::parseExpr(ctx, operand, depth);
			ret += soperand;
			if (i != (list->size() - 1)) {
				// Only append comment if iterator is at the vector end
				ret += ", ";
			}
		}
		ret += ")";
		return ret;
	} else {
		// Void operand list, no arguments needed
		return "()";
	}
}
#include "Conversion.h"

string wasmdec::Convert::parseExpr(Context* ctx, wasm::Expression* e) {
	string ret;
	ret = wasmdec::parsers::expression(ctx, e);
	return ret;
}
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
			op = "|"; return e1 + " " + op + " " + e2;
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
			op = "&"; return e1 + " " + op + " " + e2;
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
string wasmdec::Convert::resolveType(wasm::Type typ) {
	// Resolve wasm::Type to a C type
	switch (typ) {
		case wasm::Type::none:
		case wasm::Type::unreachable:
			return "void";
			break;
		case wasm::Type::i32:
			return "int";
			break;
		case wasm::Type::i64:
			return "long";
			break;
		case wasm::Type::f32:
			return "float";
			break;
		case wasm::Type::f64:
			return "double";
			break;
	}
	return "void* /* Unknown type */";
}
string wasmdec::Convert::getDecl(wasm::FunctionType* typ, string fname) {
	// Get a C function decloration from a FunctionType and name
	string ret = resolveType(typ->result); // Return type
	ret += " "; // Space between ret type and name
	ret += fname;
	ret += "("; // Argument list
	for (unsigned int i = 0; i < typ->params.size(); ++i) {
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
	for (unsigned int i = 0; i < typ->params.size(); ++i) {
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
	for (unsigned int i = 0; i < fn->params.size(); ++i) {
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
string wasmdec::Convert::getDecl(wasm::Function* fn, string preface) {
	// Get C function decloration from WASM function
	string ret = resolveType(fn->result); // Return type
	ret += " "; // Space between ret type and name
	ret += preface; // function preface for decompiling multiple files
	ret += getFName(fn->name); // name
	ret += "("; // Argument list
	for (unsigned int i = 0; i < fn->params.size(); ++i) {
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
string wasmdec::Convert::parseOperandList(Context* ctx, ExpressionList* list) {
	if (list->size()) {
		string ret = "(";
		for (unsigned int i = 0; i < list->size(); ++i) {
			Expression* operand = list->operator[](i);
			string soperand = Convert::parseExpr(ctx, operand);
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
string wasmdec::Convert::getUnary(string exp, UnaryOp op) {
	switch (op) {
		case ClzInt32:
		case ClzInt64:
			return "__builtin_clz(" + exp + ")";
			break;
		case CtzInt32:
		case CtzInt64:
			return "__builtin_ctz(" + exp + ")";
			break;
		case PopcntInt32:
		case PopcntInt64:
			return "__builtin_popcount(" + exp + ")";
			break;
		case NegFloat32:
		case NegFloat64:
			return "-(" + exp + ")";
			break;
		case AbsFloat32:
		case AbsFloat64:
			return "abs(" + exp + ")";
			break;
		case CeilFloat32:
		case CeilFloat64:
			return "ceil(" + exp + ")";
			break;
		case FloorFloat32:
		case FloorFloat64:
			return "floor(" + exp + ")";
			break;
		case TruncFloat32:
		case TruncFloat64:
			return "trunc(" + exp + ")";
			break;
		case NearestFloat32:
		case NearestFloat64:
			return "fromfp(" + exp + ", FP_INT_TONEAREST) /* Round to nearest integer, ties to even */";
			break;
		case SqrtFloat32:
		case SqrtFloat64:
			return "sqrt(" + exp + ")";
			break;
		case EqZInt32: // Equals 0
		case EqZInt64:
			return exp + " == 0";
			break;
		case ExtendSInt32:
		case ExtendUInt32:
		case TruncSFloat32ToInt64:
		case TruncUFloat32ToInt64:
		case TruncSFloat64ToInt64:
		case TruncUFloat64ToInt64:
		case ReinterpretFloat64:
			return "(long)" + exp;
			break;
		case WrapInt64:
		case TruncSFloat32ToInt32:
		case TruncUFloat32ToInt32:
		case TruncSFloat64ToInt32:
		case TruncUFloat64ToInt32:
		case ReinterpretFloat32:
			return "(int)" + exp;
			break;
		case ConvertSInt32ToFloat32:
		case ConvertUInt32ToFloat32:
		case ConvertSInt64ToFloat32:
		case ConvertUInt64ToFloat32:
		case DemoteFloat64:
		case ReinterpretInt32:
			return "(float)" + exp;
			break;
		case ConvertSInt32ToFloat64:
		case ConvertUInt32ToFloat64:
		case ConvertSInt64ToFloat64:
		case ConvertUInt64ToFloat64:
		case PromoteFloat32:
		case ReinterpretInt64:
			return "(double)" + exp;
			break;
	}
	return "/* Unsupported unary operator */";
}
string wasmdec::Convert::getHostFunc(HostOp hop) {
	switch (hop) {
  /*
		case PageSize:
			return "host_get_page_size";
			break;
		case HasFeature:
			return "host_has_feature";
			break;
	*/
    case GrowMemory:
			return "host_grow_memory";
			break;
		case CurrentMemory:
			return "host_get_current_memory";
			break;
	}
	return "/* unknown host call */ host_unknown";
}
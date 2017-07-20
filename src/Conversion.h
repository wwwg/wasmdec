#include "wasm.h"
#include "wasm-binary.h"
#include "wasm-printing.h"
#include "wasm-s-parser.h"
#include "WasmUtils.h"
#pragma once

using namespace std;

namespace wdis {
	class Convert {
	public:
		static string getFName(wasm::Name name) {
			return "fn_" + string(name.str);
		}
		static string getVName(wasm::Name name) {
			return "v" + string(name.str);
		}
		static string getLocal(wasm::Index argIdx) {
			return "local_" + to_string((int)argIdx);
		}
		static string call(wasm::Function* fn) {
			return getFName(fn->name) + "();";
		}
		static string getBinOperator(BinaryOp op) { // TODO : Add more binary operations
			switch (op) {
				case AddInt32:
				case AddInt64:
				case AddFloat32:
				case AddFloat64:
					return "+";
					break;
				case SubInt32:
				case SubInt64:
				case SubFloat32:
				case SubFloat64:
					return "-";
					break;
				case XorInt64:
				case XorInt32:
					return "^";
					break;
				case OrInt64:
				case OrInt32:
					return "||";
					break;
				case MulInt32:
				case MulInt64:
				case MulFloat32:
				case MulFloat64:
					return "*";
					break;
				case EqInt32:
				case EqInt64:
				case EqFloat32:
				case EqFloat64:
					return "=="; // TODO: Check if this is actually correct
					break;
				case NeInt32:
				case NeInt64:
				case NeFloat32:
				case NeFloat64:
					return "!="; // TODO: Check if this is actually correct
					break;
				case AndInt32:
				case AndInt64:
					return "&&";
					break;
				case LeSInt64:
				case LeSInt32:
					return "<=";
					break;
				case LtUInt32:
				case LtSInt32:
				case LtSInt64:
				case LtFloat32:
				case LtFloat64:
					return "<";
					break;
				case DivSInt32:
				case DivUInt32:
				case DivSInt64:
				case DivUInt64:
				case DivFloat32:
				case DivFloat64:
					return "/";
					break;
				case GtSInt64:
				case GtUInt64:
				case GtFloat64:
				case GtFloat32:
					return ">";
					break;
				case GeSInt64:
				case GeSInt32:
				case GeFloat64:
					return ">=";
			}
			return "NONE";
		}
		static string resolveType(wasm::WasmType typ) {
			switch (typ) {
				case wasm::WasmType::none:
				case wasm::WasmType::unreachable: // TODO: Better handling of "unreachable"
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
		static string getDecl(wasm::FunctionType* typ, string fname) {
			string ret = resolveType(typ->result); // Return type
			ret += " "; // Space between ret type and name
			ret += fname;
			ret += "("; // Argument list
			for (int i = 0; i < typ->params.size(); ++i) {
				ret += resolveType(typ->params.at(i));
				ret += getLocal(i);
				if (i != (typ->params.size() - 1)) {
					ret += ", ";
				}
			}
			ret += ")";
			return ret;
		}
		static string getDecl(wasm::FunctionType* typ, wasm::Name fname) {
			string ret = resolveType(typ->result); // Return type
			ret += " "; // Space between ret type and name
			ret += fname.str;
			ret += "("; // Argument list
			for (int i = 0; i < typ->params.size(); ++i) {
				ret += resolveType(typ->params.at(i));
				ret += " arg";
				ret += to_string(i);
				if (i != (typ->params.size() - 1)) {
					ret += ", ";
				}
			}
			ret += ")";
			return ret;
		}
		static string getDecl(wasm::Function* fn) {
			string ret = resolveType(fn->result); // Return type
			ret += " "; // Space between ret type and name
			ret += getFName(fn->name);
			ret += "("; // Argument list
			for (int i = 0; i < fn->params.size(); ++i) {
				ret += resolveType(fn->params.at(i));
				ret += " arg";
				ret += to_string(i);
				if (i != (fn->params.size() - 1)) {
					ret += ", ";
				}
			}
			ret += ")";
			return ret;
		}
		static string getDecl(wasm::Module* m, unique_ptr<wasm::Import>& i) {
			string ret = "extern ";
			if (i->kind == wasm::ExternalKind::Function) {
				// Func
				wasm::FunctionType* ft = util::resolveFType(m, i->functionType); // Lookup module types for this function's type
				ret += getDecl(ft, i->name);
			} else if (i->kind == wasm::ExternalKind::Global) {
				// Global import variable
				ret += resolveType(i->globalType);
				ret += " ";
				ret += i->name.str;
			} else {
				cout << "WARN: Not resolving unsupported import kind" << endl;
			}
			ret += ";";
			return ret;
		}
		static string parseExpr(wasm::Module*, wasm::Expression*);
		static string getBlockBody(wasm::Module*, wasm::Block*);
		static string getFuncBody(wasm::Module*, wasm::Function*);
	};
} // namespace wdis
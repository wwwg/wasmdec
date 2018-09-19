#include "parser.h"
using namespace wasmdec;

string wasmdec::parsers::binary(Context* ctx, Expression* ex) {
	string ret;
	// Binary operations, including conditionals and arithmetic
	Binary* spex = ex->cast<Binary>();
	ctx->lastExpr = ex;
	ctx->functionLevelExpression = false;
	string e1 = parseExpr(ctx, spex->left);
	ctx->lastExpr = ex;
	ctx->functionLevelExpression = false;
	string e2 = parseExpr(ctx, spex->right);
	ret += getBinOperator(e1, spex->op, e2);
	return ret;
}
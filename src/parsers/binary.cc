#include "parser.h"
using namespace wasmdec;

string wasmdec::parsers::binary(Context* ctx, Expression* ex) {
	string ret;
	// Binary operations, including conditionals and arithmetic
	Binary* spex = ex->cast<Binary>();
	ctx->lastExpr = ex;
	ctx->functionLevelExpression = false;
	string e1 = Convert::parseExpr(ctx, spex->left);
	ctx->lastExpr = ex;
	ctx->functionLevelExpression = false;
	string e2 = Convert::parseExpr(ctx, spex->right);
	ret += Convert::getBinOperator(e1, spex->op, e2);
	return ret;
}
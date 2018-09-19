#include "parser.h"
using namespace wasmdec;

string wasmdec::parsers::_if(Context* ctx, Expression* ex) {
	string ret;
	If* ife = ex->cast<If>();
	ctx->lastExpr = ex;
	ctx->isIfCondition = true;
	ctx->functionLevelExpression = false;
	string cond = Convert::parseExpr(ctx, ife->condition);
	ctx->isIfCondition = false;
	ctx->lastExpr = ex;
	ctx->functionLevelExpression = false;
	string trueBlock = Convert::parseExpr(ctx, ife->ifTrue);
	ret += util::tab(ctx->depth);
	ret += "if (" + cond + ") {\n";
	ret += trueBlock;
	ret += "\n" + util::tab(ctx->depth) + "} ";
	if (ife->ifFalse) {
		// Insert else block
		ctx->lastExpr = ex;
		ctx->functionLevelExpression = false;
		string falseBlock = Convert::parseExpr(ctx, ife->ifFalse);
		ret += "else {\n";
		ret += util::tab(ctx->depth) + falseBlock + "\n";
		ret += util::tab(ctx->depth) + "}";
	} else {
		// No else statement
		ret += "// <No else block>\n";
	}
	return ret;
}
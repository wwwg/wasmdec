#include "parser.h"
using namespace std;

std::string wasmdec::parsers::expression(Context* ctx, Expression* ex) {
	if (ex->is<Block>()) {
		return wasmdec::parsers::block(ctx, ex);
	} else if (ex->is<Binary>()) {
		return wasmdec::parsers::binary(ctx, ex);
	} else if (ex->is<GetLocal>()) {
        return wasmdec::parsers::get_local(ctx, ex);
	} else if (ex->is<CallIndirect>()) {
		return wasmdec::parsers::call_indirect(ctx, ex);
	} else if (ex->is<SetLocal>()) {
		return wasmdec::parsers::set_local(ctx, ex);
	} else if (ex->is<Load>()) {
		return wasmdec::parsers::load(ctx, ex);
	} else if (ex->is<Store>()) {
		return wasmdec::parsers::store(ctx, ex);
	} else if (ex->is<Unary>()) {
		return wasmdec::parsers::unary(ctx, ex);
	} else if (ex->is<AtomicRMW>()) {
		return wasmdec::parsers::atomics(ctx, ex);
	} else if (ex->is<AtomicCmpxchg>()) {
		return wasmdec::parsers::atomics(ctx, ex);
	} else if (ex->is<Select>()) {
		return wasmdec::parsers::select(ctx, ex);
	} else if (ex->is<Drop>()) {
		return wasmdec::parsers::drop(ctx, ex);
	} else if (ex->is<Host>()) {
		return wasmdec::parsers::host(ctx, ex);
	} else if (ex->is<Unreachable>()) {
		return wasmdec::parsers::unreachable(ctx, ex);
	} else if (ex->is<SetGlobal>()) {
		return wasmdec::parsers::set_global(ctx, ex);
	} else if (ex->is<GetGlobal>()) {
		return wasmdec::parsers::get_global(ctx, ex);
	} else if (ex->is<Loop>()) {
		return wasmdec::parsers::loop(ctx, ex);
	} else if (ex->is<Switch>()) {
		return wasmdec::parsers::_switch(ctx, ex);
	} else if (ex->is<Call>()) {
		return wasmdec::parsers::call(ctx, ex);
	} else if (ex->is<If>()) {
		return wasmdec::parsers::_if(ctx, ex);
	} else if (ex->is<Nop>()) {
		return wasmdec::parsers::nop(ctx, ex);
	} else if (ex->is<If>()) {
		return wasmdec::parsers::_if(ctx, ex);
	} else if (ex->is<Const>()) {
		return wasmdec::parsers::_const(ctx, ex);
	} else if (ex->is<Return>()) {
		return wasmdec::parsers::_return(ctx, ex);
	} else if (ex->is<Break>()) {
		return wasmdec::parsers::_break(ctx, ex);
	}
	return "/* UNKNOWN EXPRESSION */";
}
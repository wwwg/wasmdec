#include "parser.h"
using namespace std;

string wasmdec::parsers::expression(Context* ctx, Expression* ex) {
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
	}
}
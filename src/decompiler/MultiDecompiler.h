#ifndef _MULTI_DECOMP_H
#define _MULTI_DECOMP_H

#include "Decompiler.h"
using namespace std;

namespace wasmdec {
	class MultiDecompiler {
	public:
		MultiDecompiler(vector<string>);
	protected:
		vector<Decompiler> decomps;
		vector<string> infiles;
	};
};

#endif // _MULTI_DECOMP_H
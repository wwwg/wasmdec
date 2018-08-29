#ifndef _MULTI_DECOMP_H
#define _MULTI_DECOMP_H

#include "Decompiler.h"
using namespace std;

namespace wasmdec {
	class MultiDecompiler {
	public:
		MultiDecompiler(vector<string>);
	protected:
		bool readFile(vector<char*>, string);
		bool failed;

		vector<Decompiler> decomps;
		vector<string> infiles;
		vector<vector<char>> rawFiles;
	};
};

#endif // _MULTI_DECOMP_H
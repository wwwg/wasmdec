#ifndef _MULTI_DECOMP_H
#define _MULTI_DECOMP_H

#include "Decompiler.h"
using namespace std;

namespace wasmdec {
	class MultiDecompiler {
	public:
		MultiDecompiler(vector<string>, DisasmConfig);
		string getOutput(void);
	protected:
		stringstream codeStream;
		bool readFile(vector<char>*, string);
		string getFileExt(string);
		DisasmMode getDisasmMode(string);

		bool failed;
		vector<string> infiles;
		vector<vector<char>> rawFiles;
	};
};

#endif // _MULTI_DECOMP_H
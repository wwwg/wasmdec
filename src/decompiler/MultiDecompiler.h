#ifndef _MULTI_DECOMP_H
#define _MULTI_DECOMP_H

#include "Decompiler.h"
using namespace std;

namespace wasmdec {
	class MultiDecompiler {
	public:
		MultiDecompiler(vector<string>, DisasmConfig);
		string getOutput(void);
		bool failed;
	protected:
		stringstream codeStream;
		bool readFile(vector<char>*, string);
		string getFileExt(string);
		DisasmMode getDisasmMode(string);

		vector<string> infiles;
		vector<vector<char>> rawFiles;
	};
};

#endif // _MULTI_DECOMP_H
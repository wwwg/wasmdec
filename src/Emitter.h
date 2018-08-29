#ifndef _wasmdec_EMITTER_H
#define _wasmdec_EMITTER_H

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <iterator>
using namespace std;

namespace wasmdec {
	class Emitter {
	public:
		Emitter();
		stringstream& operator<<(string);
		void comment(string);
		void preamble();
		void ln();
		string getCode();
	protected:
		stringstream str;
	};
} // namespace wasmdec

#endif // _wasmdec_EMITTER_H
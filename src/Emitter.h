#ifndef _WDIS_EMITTER_H
#define _WDIS_EMITTER_H

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <iterator>
using namespace std;

namespace wdis {
	class Emitter {
	public:
		Emitter();
		stringstream& operator<<(string);
		void comment(string);
		void ln();
		string getCode();
	protected:
		stringstream str;
	};
} // namespace wdis

#endif // _WDIS_EMITTER_H
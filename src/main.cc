#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <iterator>
#include "CodeGen.h"

using namespace std;
using namespace wdis;

vector<char> readFile(string path) {
	ifstream file(path);
	vector<char> vfile;
	if (!file.eof() && !file.fail()) {
	    file.seekg(0, ios_base::end);
	    streampos fileSize = file.tellg();
	    vfile.resize(fileSize);
	    file.seekg(0, ios_base::beg);
	    file.read(&vfile[0], fileSize);
	}
	return vfile;
}
void writeFile(string path, string data) {
	ofstream f(path);
	f << data;
	f.close();
}
int usage() {
	cout << "Usage:" << endl
	<< "wdis <infile> <outfile>" << endl;
	return 1;
}
int main(int argc, const char** argv) {
	// Temporary hack to allow custom inputs/outputs. I know this isn't secure, but it's just for testing
	if (argc != 3) {
		return usage();
	}
	string infile = string(argv[1]);
	string outfile = string(argv[2]);
	cout << "Decompiling wasm file " << infile << " to " << outfile << endl;

	auto vfile = readFile(infile);
	CodeGenerator generator(&vfile, true, true);
	generator.gen();
	auto res = generator.getEmittedCode();
	writeFile(outfile, res);
	return 0;
}
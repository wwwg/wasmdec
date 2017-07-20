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
	    file.seekg(0, std::ios_base::beg);
	    file.read(&vfile[0], fileSize);
	}
	return vfile;
}
void writeFile(string path, string data) {
	ofstream f(path);
	f << data;
	f.close();
}
int main(int argc, const char** argv) {
	auto vfile = readFile("samples/addTwo.wasm");
	CodeGenerator generator(&vfile, true);
	generator.gen();
	string res = generator.getEmittedCode();
	writeFile("samples/addTwo.c", res);
	return 0;
}
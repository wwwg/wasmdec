#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <iterator>
#include "CodeGen.h"

using namespace std;
using namespace wasmdec;

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
	<< "wasmdec {arguments}" << endl
	<< "Arguments:" << endl
	<< "\t -o / --out <outfile> : Path to output file" << endl
	<< "\t -i / --in <infile> : Path to input file" << endl
	<< "\t -d / --debug : Enable debug output" << endl
	<< "\t -e / --extra : Emit extra data into outfile" << endl;
	return 1;
}
int main(int argc, const char** argv) {
	string infile, outfile;
	bool enableDebugging = false;
	bool enableExtra = false;
	if (argc < 2) {
		cout << "Not enough arguments!" << endl;
		return usage();
	}
	for (int i = 0; i < argc; ++i) {
		string sarg = string(argv[i]);
		if (sarg == "-d" || sarg == "--debug") {
			enableDebugging = true;
		} else if (sarg == "-e" || sarg == "--extra") {
			enableExtra = true;
		} else if (sarg == "-o" || sarg == "--out") {
			int outnameIndex = i + 1;
			if (outnameIndex >= argc) {
				return usage(); // Invalid arguments
			}
			// Set output file
			outfile = string(argv[outnameIndex]);
		} else if (sarg == "-i" || sarg == "--in") {
			int innameIndex = i + 1;
			if (innameIndex >= argc) {
				return usage(); // Invalid arguments
			}
			// Set input file
			infile = string(argv[innameIndex]);
		}
	}
	if (!infile.length() || !outfile.length()) {
		return usage();
	}
	auto vfile = readFile(infile);
	CodeGenerator generator(&vfile, enableDebugging, enableExtra);
	generator.gen();
	auto res = generator.getEmittedCode();
	writeFile(outfile, res);
	return 0;
}
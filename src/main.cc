#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <iterator>
#include "CodeGen.h"

using namespace std;
using namespace wasmdec;

bool readFile(vector<char>* data, string path) {
	ifstream file(path);
	if (!file.eof() && !file.fail()) {
	    file.seekg(0, ios_base::end);
	    streampos fileSize = file.tellg();
	    data->resize(fileSize);
	    file.seekg(0, ios_base::beg);
	    file.read(&(data->operator[](0)), fileSize);
		return true;
	} else {
		return false;
	}
}
bool writeFile(string path, string data) {
	ofstream file(path);
	if (!file.eof() && !file.fail()) {
		file << data;
		file.close();
		return true;
	} else {
		return false;
	}
}
int usage() {
	cout << "Usage:" << endl
	<< "wasmdec {arguments}, where arguments is one of:" << endl
	<< "\t -o / --out <outfile> : Path to output file (Required)" << endl
	<< "\t -i / --in <infile> : Path to input file (Required)" << endl
	<< "\t -d / --debug : Enable debug output" << endl
	<< "\t -e / --extra : Emit extra data into outfile" << endl
	<< "\t -h / --help : Print usage information" << endl;
	return 1;
}
int main(int argc, const char** argv) {
	string infile, outfile;
	bool enableDebugging = false;
	bool enableExtra = false;
	if (argc == 2) {
		string argv1 = string(argv[1]);
		if (argv1 == "-h" || argv1 == "--help") return usage();
	}
	if (argc < 2) return usage();
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
	vector<char> vfile = vector<char>();
	bool rsuccess = readFile(&vfile, infile);
	if (!rsuccess) {
		cout << "wasmdec: failed to read file '" << infile << "'" << endl;
		return 1;
	}
	CodeGenerator generator(&vfile, enableDebugging, enableExtra);
	generator.gen();
	auto res = generator.getEmittedCode();
	bool wsuccess = writeFile(outfile, res);
	if (!wsuccess) {
		cout << "wasmdec: failed to write file '" << outfile << "'" << endl;
		return 1;
	}
	return 0;
}
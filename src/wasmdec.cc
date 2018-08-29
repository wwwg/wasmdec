#define __WASMDEC_VERSION "1.1.0"

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <iterator>

#include "cxxopts.hpp"
#include "decompiler/Decompiler.h"
using namespace cxxopts;

// legacy functions
// TODO : REMOVE THESE

int _usage_old() {
	cerr << "Usage:" << endl
	<< "wasmdec {arguments}, where arguments is one of:" << endl
	<< "\t -o / --out <outfile> : Path to output file (Required)" << endl
	<< "\t -i / --in <infile> : Path to input file (Required)" << endl
	<< "\t -d / --debug : Enable debug output" << endl
	<< "\t -e / --extra : Emit extra data into outfile" << endl
	<< "\t -m / --memdump : Dump the input file's memory to disk" << endl
	<< "\t -h / --help : Print usage information" << endl
	<< "\t -v / --version : Print the program's version" << endl;
	return 1;
}
int _usage_old(int optionalRetVal) {
	usage();
	return optionalRetVal;
}

// Global variables to be passed to the decompiler
bool debugging = false,
		extra = false,
		memdump = false;
string infile,
	outfile;

// Helper functions
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
string getFileExt(string fname) {
	string::size_type idx = fname.rfind('.');
	if(idx != string::npos) {
	    string extension = fname.substr(idx + 1);
	    return extension;
	} else {
	    return "";
	}
}
DisasmMode getDisasmMode(string infile) {
	// Convert file extension to disassembler mode
	string ext = getFileExt(infile);
	DisasmMode mode = DisasmMode::None;
	if (ext == "wasm") {
		return DisasmMode::Wasm;
	} else if (ext == "wast") {
		return DisasmMode::Wast;
	} else if (ext == "js") {
		return DisasmMode::AsmJs;
	} else {
		return DisasmMode::None;
	}
}
Decompiler getDecompiler(vector<char>* input) {
	DisasmConfig config(enableDebugging, enableExtra, mode);
	return Decompiler(config, input);
}
int printVersion() {
	cerr << "wasmdec v" << __WASMDEC_VERSION << endl;
	return 0;
}
void enableDebugging() {
	debugging = true;
}
void enableExtra() {
	extra = true;
}
void enableMemdump() {
	memdump = true;
}
void setOutfile(string _outf) {
	outfile = _outf;
}
void setInfile(string _inf) {
	infile = _inf;
}
int main(int argc, const char** argv) {
	Options opt("wasmdec", "WebAssembly to C decompiler");
	opt.add_options()
		("v,version", "Print wasmdec version")
		("d,debug", "Enable debug output")
		("m,memdump", "Dump memory instead of decompiling")
		("e,extra", "Output extra information to decompiled binary")
		("o,output", "Output C file", value<string>())
		;
	return 0;
}
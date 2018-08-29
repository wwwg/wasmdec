#include "MultiDecompiler.h"

// helper functions
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
	if (ext == "wasm") {
		return DisasmMode::Wasm;
	} else if (ext == "wast") {
		return DisasmMode::Wast;
	} else if (ext == "js") {
		return DisasmMode::AsmJs;
	} else {
		return DisasmMode::Wasm;
	}
}

MultiDecompiler::MultiDecompiler(vector<string> _infiles, DisasmConfig conf) {
	infiles = _infiles;
	// Read all the infiles
	for (unsigned int i = 0; i < infiles.size(); ++i) {
		vector<char> raw;
		bool didFail = readFile(&raw, infiles.at(i));
		if (didFail) {
			failed = true;
			break;
		}
		rawFiles.push_back(raw);
		// create config
		DisasmConfig thisConf = conf;
		thisConf.mode = getDisasmMode(infiles.at(i));
		// create compiler and add it to the vector
		Decompiler* d = new Decompiler(thisConf, &raw);
		decomps.push_back(d);
	}
}
bool MultiDecompiler::readFile(vector<char>* data, string path) {
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
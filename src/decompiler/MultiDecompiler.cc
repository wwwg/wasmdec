#include "MultiDecompiler.h"

// helper functions
string MultiDecompiler::getFileExt(string fname) {
	string::size_type idx = fname.rfind('.');
	if(idx != string::npos) {
	    string extension = fname.substr(idx + 1);
	    return extension;
	} else {
	    return "";
	}
}
string MultiDecompiler::getEverythingButFileExt(string a) {
	size_t l = a.find_last_of("."); 
	if (l == string::npos) return "";
	string r = a.substr(0, l); 
	return r;
}
DisasmMode MultiDecompiler::getDisasmMode(string infile) {
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

MultiDecompiler::MultiDecompiler(vector<string> _infiles, DisasmConfig conf) {
	infiles = _infiles;
	failed = false;
	// Read all the infiles
	for (unsigned int i = 0; i < infiles.size(); ++i) {
		vector<char> raw;
		if (!readFile(&raw, infiles.at(i))) {
			failed = true;
			break;
		}
		// create config
		DisasmConfig thisConf = conf;
		string fnPreface = getEverythingButFileExt(infiles.at(i));
		if (fnPreface == "")
			fnPreface = "WASMDEC_UNKNOWN_MODULE_";
		conf.fnPreface = fnPreface;

		if (i == 0) {
			thisConf.includePreamble = true;
		} else {
			thisConf.includePreamble = false;
		}
		thisConf.mode = getDisasmMode(infiles.at(i));
		// create decompiler
		Decompiler* d = new Decompiler(thisConf, raw);
		// do decompilation
		d->decompile();
		if (d->failed()) {
			failed = true;
			break;
		}
		if (i != 0)
			codeStream << endl << endl;

		codeStream << "// Module '" << infiles.at(i) << "':" << endl
			<< d->getEmittedCode();
	}
}
string MultiDecompiler::getOutput() {
	return codeStream.str();
}
#include "MultiDecompiler.h"

MultiDecompiler::MultiDecompiler(vector<string> _infiles) {
	infiles = _infiles;
	// Read all the infiles
	for (int i = 0; i < infiles.size(); ++i) {
		vector<char> raw;
		bool didFail = readFile(raw, infiles.at(i));
		if (didFail)
			fail = true;
		rawFiles.push_back(raw);
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
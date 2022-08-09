#include <iostream>

#include "FileInfo.hpp"

using namespace std;
using namespace nyx;

FileInfo::FileInfo(string fileName) : _fileName(fileName) {}

string FileInfo::getFileName() const
{
	return _fileName;
}

void FileInfo::addLine(string& line)
{
	_fileContent.push_back(line);
}

string FileInfo::getLine(unsigned int num) const
{
	if (num > _fileContent.size()) {
		cout << "[Error] Line not found !" << endl;
		exit(-1);
	}
	return _fileContent[num - 1];
}


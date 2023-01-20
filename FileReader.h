#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class FileReader
{

public:

	static string* readFile(string filename);
	static vector<string> readFileLines(string filename);

};

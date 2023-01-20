#include "FileReader.h"

using std::ifstream;
using std::istreambuf_iterator;

string* FileReader::readFile(string const filename)
{
	
	ifstream ifs = ifstream(filename);

	string* contents = new string(
		istreambuf_iterator<char>(ifs),
		istreambuf_iterator<char>()
	);

	return contents;

}

vector<string> FileReader::readFileLines(string filename)
{

	vector<string> lines = vector<string>();

	ifstream ifs = ifstream(filename);

	string line;
	while (std::getline(ifs, line))
		lines.push_back(line);

	ifs.close();

	return lines;

}

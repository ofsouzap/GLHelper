#pragma once

#include <exception>
#include <string>
#include <iostream>
#include <fstream>

#include "ImageData.h"

using std::exception;
using std::string;
using std::ifstream;

namespace GLHelper
{

	constexpr int BMP_HEADER_SIZE = 54;

	class FileNotBMPFileException : exception { };
	
	ImageData* readBMPImage(string filename);

}
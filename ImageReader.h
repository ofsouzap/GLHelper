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

	class ImageReader
	{

	public:

		class FileNotBMPFileException : exception { };

		static ImageData* readBMPImage(string filename);

	};

}
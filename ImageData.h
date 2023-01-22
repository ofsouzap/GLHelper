#pragma once

#include <string>

using std::string;

namespace GLHelper
{
	class ImageData
	{

		typedef int dimension_t;
		typedef unsigned char* data_t;

	private:

		dimension_t width;
		dimension_t height;
		data_t data;

	public:

		ImageData(string filename);
		~ImageData();

		dimension_t getWidth() const { return width; }
		dimension_t getHeight() const { return height; }
		data_t getData() const { return data; }

	};
}
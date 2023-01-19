#pragma once

namespace GLHelper
{
	class ImageData
	{

		typedef unsigned int dimension_t;
		typedef unsigned char* data_t;

	private:

		dimension_t width;
		dimension_t height;
		data_t data;

	public:

		ImageData(unsigned int width, unsigned int height, unsigned char* data) : width(width), height(height), data(data) { }

		dimension_t getWidth() const { return width; }
		dimension_t getHeight() const { return height; }
		data_t getData() const { return data; }

	};
}
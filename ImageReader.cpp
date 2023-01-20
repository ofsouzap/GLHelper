#include "ImageReader.h"

using namespace GLHelper;

// Created with help from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/
// File format reference: https://en.wikipedia.org/wiki/BMP_file_format

ImageData* ImageReader::readBMPImage(string filename)
{

	// Setup

	ImageData* img;

	char header[54];
	unsigned int dataPos, width, height, imageSize;
	unsigned char* data;

	// Open file

	FILE* file = fopen(filename.c_str(), "rb");

	// File checking

	// Check file header size
	if (fread(header, 1, BMP_HEADER_SIZE, file) != 54)
	{
		fclose(file);
		throw new FileNotBMPFileException();
	}

	// Check file signature
	if (header[0] != 'B' || header[1] != 'M')
	{
		fclose(file);
		throw new FileNotBMPFileException();
	}

	// Read information from header

	dataPos = *(int*)&(header[0x0A]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);
	imageSize = *(int*)&(header[0x22]);

	// Defaulting some information

	if (dataPos == 0) dataPos = BMP_HEADER_SIZE;
	if (imageSize == 0) imageSize = width * height * 3;

	// Read image data

	data = new unsigned char[imageSize];

	fread(data, 1, imageSize, file);

	// Close image

	fclose(file);

	// Create image object

	img = new ImageData(width, height, data);

	// Return image

	return img;

}

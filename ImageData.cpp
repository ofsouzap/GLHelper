#include "ImageData.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace GLHelper;

ImageData::ImageData(string filename)
{
	stbi_set_flip_vertically_on_load(true); // OpenGL has origin in bottom-left but stb_image.h has it at top-left so need to flip
	data = stbi_load(filename.c_str(), &width, &height, nullptr, 3);
}

ImageData::~ImageData()
{
	stbi_image_free(data);
}

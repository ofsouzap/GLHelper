#pragma once

#include <string>

#include <glad/gl.h>

#include "ImageData.h"

using std::string;

namespace GLHelper
{
	class Texture
	{

	private:

		GLuint texture;

	public:

		Texture(ImageData* image);

		static Texture* fromBMP(string filename);

		void bind();

	};
}
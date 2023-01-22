#pragma once

#include <string>
#include <vector>
#include <exception>

#include <glad/gl.h>

#include "SceneObject.h"
#include "FileReader.h"

using std::string;
using std::vector;
using std::exception;

namespace GLHelper
{

	class FileNotOBJFileException : exception { };

	class ModelReader
	{

	private:
		struct pos_t { float x, y, z; };
		struct uv_t { float u, v; };
		struct norm_t { float x, y, z; };

	public:
		static void readOBJModel(string filename, int* outVertCount, GLfloat** outPos, GLfloat** outUV, GLfloat** outNorm);

	};

}
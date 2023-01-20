#pragma once

#include <string>
#include <vector>

#include <linmath.h>
#include <glad/gl.h>

#include "FileReader.h"
#include "SceneObject.h"

using std::string;
using std::vector;

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
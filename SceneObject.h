#pragma once

#include <glad/gl.h>
#include <linmath.h>

#include "ShaderProgram.h"
#include "Texture.h"
#include "Camera.h"

namespace GLHelper
{
	class SceneObject
	{

	private:

		ShaderProgram* shader;

		int vertexCount;

		const GLfloat* pos;
		const GLfloat* col;
		const GLfloat* uv;

		GLuint vao;
		GLuint posBuf, colBuf, uvBuf;

		Texture* texture;

		bool hasPosData() const;
		bool hasColData() const;
		bool hasUVData() const;

		bool hasTexture() const;

	public:

		SceneObject(ShaderProgram* shader, int vertexCount, const GLfloat* pos, const GLfloat* col, const GLfloat* uv);

		void setTexture(Texture* texture);

		void draw(mat4x4 mvp) const;
		void draw(mat4x4 m, Camera* camera) const;

	};
}
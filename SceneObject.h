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

		GLuint vao;

		Texture* texture;

		bool hasTexture() const;

	public:

		SceneObject(ShaderProgram* shader, int vertexCount);

		void setTexture(Texture* texture);
		/// <summary>
		/// Adds an attribute to the object and gives it to the object's shader program.
		/// </summary>
		/// <param name="name">The name of the "in" attribute in the shader program</param>
		/// <param name="type">The type of the values</param>
		/// <param name="componentSize">The size of the data per component per vertex in bytes</param>
		/// <param name="components">The number of components of each value</param>
		/// <param name="data">A pointer to the data itself</param>
		void addAttrib(string name, GLenum type, GLint componentSize, GLint components, const void* data, GLenum usage = GL_STATIC_DRAW) const;

		void draw(mat4x4 m, Camera* camera) const;

	};
}
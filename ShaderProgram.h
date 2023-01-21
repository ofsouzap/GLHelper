#pragma once

#include <string>
#include <glad/gl.h>

using std::string;

namespace GLHelper
{
	class ShaderProgram
	{

	private:

		GLuint vertexShader, fragmentShader;
		GLuint program;

		static GLuint createVertexShader(const char* vertexShaderText);
		static GLuint createFragmentShader(const char* fragmentShaderText);
		static GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader);

		// TODO - cache fetched shader program attribute locations so that don't have to be fetched each frame

		GLint getAttribLocation(string name) const;
		GLint getUniformLocation(string name) const;

	public:

		ShaderProgram(string vertexShaderFilename, string fragmentShaderFilename);

		/// <summary>
		/// Binds vertex data provided from a data array to an "in" attribute in the shader program
		/// </summary>
		/// <param name="name">The name of the attribute in the shader program</param>
		/// <param name="size">The number of components of each value (eg. a vec3 has size 3)</param>
		/// <param name="type">The type of the values being provided (eg. GL_FLOAT)</param>
		/// <param name="stride">The number of bytes each value takes (eg. the stride for a vec3 would be sizeof(float) * 3)</param>
		void bindVertexData(string name, GLint size, GLenum type, GLsizei stride, GLboolean normalized = false) const;

		void setUniformMat4x4(string name, const GLfloat* value) const;
		void setUniformVec3(string name, const GLfloat* value) const;
		void setUniformVec3i(string name, const GLint* value) const;
		void setUniformVec2(string name, const GLfloat* value) const;
		void setUniformVec2i(string name, const GLint* value) const;
		void setUniformFloat(string name, const GLfloat* value) const;
		void setUniformInt(string name, const GLint* value) const;

		void useProgram() const;

	};
}
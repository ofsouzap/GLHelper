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

		GLint mvp, vPos, vCol, vUV;

		static GLuint createVertexShader(const char* vertexShaderText);
		static GLuint createFragmentShader(const char* fragmentShaderText);
		static GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader);

	public:

		ShaderProgram(string vertexShaderFilename, string fragmentShaderFilename);

		void bindPos();
		void bindCol();
		void bindUV();

		void usage_useProgram() const;
		void usage_provideMvp(const GLfloat* value) const;

	};
}
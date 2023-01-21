#include "ShaderProgram.h"

#include "FileReader.h"

using namespace GLHelper;

GLuint ShaderProgram::createVertexShader(const char* vertexShaderText)
{

	GLuint shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shader, 1, &vertexShaderText, NULL);
	glCompileShader(shader);

	return shader;

}

GLuint ShaderProgram::createFragmentShader(const char* fragmentShaderText)
{

	GLuint shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shader, 1, &fragmentShaderText, NULL);
	glCompileShader(shader);

	return shader;

}

GLuint ShaderProgram::createShaderProgram(GLuint vertexShader, GLuint fragmentShader)
{
	
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	return program;

}

GLint GLHelper::ShaderProgram::getAttribLocation(string name) const
{
	return glGetAttribLocation(program, name.c_str());
}

GLint ShaderProgram::getUniformLocation(string name) const
{
	return glGetUniformLocation(program, name.c_str());
}

ShaderProgram::ShaderProgram(string vertexShaderFilename, string fragmentShaderFilename)
{

	const char* vertexShaderText = FileReader::readFile(vertexShaderFilename)->c_str();
	const char* fragmentShaderText = FileReader::readFile(fragmentShaderFilename)->c_str();

	vertexShader = createVertexShader(vertexShaderText);
	fragmentShader = createFragmentShader(fragmentShaderText);
	program = createShaderProgram(vertexShader, fragmentShader);

}

void ShaderProgram::bindVertexData(string name, GLint size, GLenum type, GLsizei stride, GLboolean normalized) const
{

	GLint attrib = getAttribLocation(name);
	glEnableVertexAttribArray(attrib);
	glVertexAttribPointer(attrib, size, type, normalized, stride, (const void*)0);

}

void ShaderProgram::setUniformMat4x4(string name, const GLfloat* value) const
{

	GLint attrib = getUniformLocation(name);
	glUniformMatrix4fv(attrib, 1, GL_FALSE, value);

}

void ShaderProgram::useProgram() const
{
	glUseProgram(program);
}

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

ShaderProgram::ShaderProgram(string vertexShaderFilename, string fragmentShaderFilename)
{

	const char* vertexShaderText = FileReader::readFile(vertexShaderFilename)->c_str();
	const char* fragmentShaderText = FileReader::readFile(fragmentShaderFilename)->c_str();

	vertexShader = createVertexShader(vertexShaderText);
	fragmentShader = createFragmentShader(fragmentShaderText);
	program = createShaderProgram(vertexShader, fragmentShader);

	mvp = glGetUniformLocation(program, "mvp");
	vPos = glGetAttribLocation(program, "vPos");
	vCol = glGetAttribLocation(program, "vCol");
	vUV = glGetAttribLocation(program, "vUV");

}

void ShaderProgram::bindPos()
{

	const GLint size = 3;
	const GLenum type = GL_FLOAT;
	const GLsizei stride = sizeof(GLfloat) * size;
	const void* pointer = 0;

	glEnableVertexAttribArray(vPos);
	glVertexAttribPointer(vPos, size, type, GL_FALSE, stride, pointer);

}

void ShaderProgram::bindCol()
{

	const GLint size = 3;
	const GLenum type = GL_FLOAT;
	const GLsizei stride = sizeof(GLfloat) * size;
	const void* pointer = 0;

	glEnableVertexAttribArray(vCol);
	glVertexAttribPointer(vCol, size, type, GL_FALSE, stride, pointer);

}

void ShaderProgram::bindUV()
{

	const GLint size = 2;
	const GLenum type = GL_FLOAT;
	const GLsizei stride = sizeof(GLfloat) * size;
	const void* pointer = 0;

	glEnableVertexAttribArray(vUV);
	glVertexAttribPointer(vUV, size, type, GL_FALSE, stride, pointer);

}

void ShaderProgram::usage_useProgram() const
{
	glUseProgram(program);
}

void ShaderProgram::usage_provideMvp(const GLfloat* value) const
{
	glUniformMatrix4fv(mvp, 1, GL_FALSE, value);
}

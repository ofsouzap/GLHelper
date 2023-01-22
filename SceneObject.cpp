#include "SceneObject.h"

using namespace GLHelper;

bool SceneObject::hasTexture() const
{
	return texture != nullptr;
}

SceneObject::SceneObject(ShaderProgram* shader, int vertexCount) : shader(shader), vertexCount(vertexCount)
{

	// Default texture to null
	texture = nullptr;

	// Create and bind vertex array object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

}

void SceneObject::setTexture(Texture* texture)
{
	this->texture = texture;
}

void SceneObject::addAttrib(string name, GLenum type, GLint componentSize, GLint components, const void* data, GLenum usage) const
{

	int valSize = componentSize * components;
	GLsizei stride = valSize;
	GLint size = valSize * vertexCount;

	// Bind own VAO

	glBindVertexArray(vao);

	// Create and bind vertex buffer

	GLuint buf;
	glGenBuffers(1, &buf);
	glBindBuffer(GL_ARRAY_BUFFER, buf);

	// Provide buffer data

	glBufferData(GL_ARRAY_BUFFER, size, data, usage);

	// Add to shader program

	shader->bindVertexData(name, components, type, stride);

}

void SceneObject::draw(mat4x4 m, Camera* camera) const
{

	// Calculate MVP matrix

	mat4x4 mvp = camera->genMVP(m);

	// Calculate normal transformation matrix

	mat4x4 normM;
	normM = glm::transpose(glm::inverse(m));

	// Enable shader program and provide matrices

	shader->useProgram();
	shader->setUniformMat4x4("mvp", &mvp[0][0]);

	// Bind texture if provided

	if (hasTexture())
		texture->bind();

	// Draw object

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

}

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

const ShaderProgram* SceneObject::getShaderProgram() const
{
	return shader;
}

void SceneObject::draw(mat4x4 m, Camera* camera) const
{

	// Calculate MVP matrix

	mat4x4 mvp = camera->genMVP(m);

	// Calculate normal transformation matrix

	mat3x3 m3 = mat3x3(m);
	mat3x3 norm_m3 = glm::transpose(glm::inverse(m));
	mat4x4 norm_m = mat4x4(norm_m3);

	// Enable shader program and provide matrices

	shader->useProgram();
	shader->setUniformMat4x4("m", &m[0][0]);
	shader->setUniformMat4x4("mvp", &mvp[0][0]);
	shader->setUniformMat4x4("norm_m", &norm_m[0][0]);

	// Provide shader program other uniforms

	vec3 camera_pos = camera->getPosition();
	shader->setUniformVec3("wc_camera_pos", &camera_pos[0]);

	// Bind texture if provided

	if (hasTexture())
		texture->bind();

	// Draw object

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

}

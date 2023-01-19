#include "SceneObject.h"

using namespace GLHelper;

bool SceneObject::hasPosData() const
{
	return pos != nullptr;
}

bool SceneObject::hasColData() const
{
	return col != nullptr;
}

bool SceneObject::hasUVData() const
{
	return uv != nullptr;
}

bool SceneObject::hasTexture() const
{
	return texture != nullptr;
}

SceneObject::SceneObject(ShaderProgram* shader, int vertexCount, const GLfloat* pos, const GLfloat* col, const GLfloat* uv) : shader(shader), vertexCount(vertexCount), pos(pos), col(col), uv(uv)
{

	// Default texture to null
	texture = nullptr;

	// Create and bind vertex array object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create vertex buffers and set data (if provided)

	if (hasPosData())
	{
		glGenBuffers(1, &posBuf);
		glBindBuffer(GL_ARRAY_BUFFER, posBuf);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * vertexCount, pos, GL_STATIC_DRAW);
	}
	else posBuf = 0;

	if (hasColData())
	{
		glGenBuffers(1, &colBuf);
		glBindBuffer(GL_ARRAY_BUFFER, colBuf);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * vertexCount, col, GL_STATIC_DRAW);
	}
	else colBuf = 0;

	if (hasUVData())
	{
		glGenBuffers(1, &uvBuf);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuf);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * vertexCount, uv, GL_STATIC_DRAW);
	}
	else uvBuf = 0;

	// Bind data to shader (if provided)

	if (hasPosData())
	{
		glBindBuffer(GL_ARRAY_BUFFER, posBuf);
		shader->bindPos();
	}

	if (hasColData())
	{
		glBindBuffer(GL_ARRAY_BUFFER, colBuf);
		shader->bindCol();
	}

	if (hasUVData())
	{
		glBindBuffer(GL_ARRAY_BUFFER, uvBuf);
		shader->bindUV();
	}

}

void SceneObject::setTexture(Texture* texture)
{
	this->texture = texture;
}

void SceneObject::draw(mat4x4 mvp) const
{

	// Enable shader program and provide MVP
	shader->usage_useProgram();
	shader->usage_provideMvp((const GLfloat*)mvp);

	// Bind texture if provided
	if (hasTexture())
		texture->bind();

	// Draw object
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

}

void SceneObject::draw(mat4x4 m, Camera* camera) const
{

	mat4x4 mvp;
	camera->genMVP(mvp, m);

	// Enable shader program and provide MVP
	shader->usage_useProgram();
	shader->usage_provideMvp((const GLfloat*)mvp);

	// Bind texture if provided
	if (hasTexture())
		texture->bind();

	// Draw object
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

}

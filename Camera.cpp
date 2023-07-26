#include "Camera.h"

using namespace GLHelper;

Camera::Camera(float aspectRatio, float fov)
{

	this->aspectRatio = aspectRatio;
	this->fov = fov;

	camera_position = { 0.f, 0.f, 0.f };
	camera_angles = { 0.f, 0.f };

}

vec3 Camera::getPosition() const
{
	return camera_position;
}

Camera::angles Camera::getAngles() const
{
	return camera_angles;
}

float Camera::getFov() const
{
	return fov;
}

void Camera::setPosition(vec3 pos)
{
	camera_position = pos;
}

void Camera::setAngles(angles as)
{
	camera_angles = as;
}

void Camera::setFov(float fov)
{
	this->fov = fov;
}

void Camera::changePosition(vec3 v)
{
	camera_position = camera_position + v;
}

void Camera::changeFov(float x)
{
	fov += x;
}

mat4x4 Camera::genMVP(mat4x4 m) const
{

	// View matrix

	mat4x4 v;
	mat4x4 vRot, vPos;

	vPos = glm::identity<mat4x4>();
	vPos = glm::translate(vPos, -1.0f * camera_position);

	vRot = glm::identity<mat4x4>();
	vRot = glm::rotate(vRot, camera_angles.polar, glm::vec3(1, 0, 0));
	vRot = glm::rotate(vRot, camera_angles.azimuthal, glm::vec3(0, 1, 0));

	v = vRot * vPos;

	// Projection matrix

	mat4x4 p;
	p = glm::perspective(fov, aspectRatio, 0.1f, 100.f);

	// Combine and return

	return p * v * m;

}

#include "Camera.h"

using namespace GLHelper;

Camera::Camera(float aspectRatio, float fov)
{

	this->aspectRatio = aspectRatio;
	this->fov = fov;

	camera_position = { 0.f, 0.f, 0.f };
	camera_angles = { 0.f, 0.f };

}

Camera::position Camera::getPosition() const
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

void Camera::setPosition(position pos)
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

void Camera::genMVP(mat4x4 mvp, mat4x4 m) const
{

	// View matrix

	mat4x4 v;
	mat4x4 vRot, vPos;

	mat4x4_translate(vPos, -camera_position.x, -camera_position.y, -camera_position.z);

	mat4x4_identity(vRot);
	mat4x4_rotate_X(vRot, vRot, camera_angles.polar);
	mat4x4_rotate_Y(vRot, vRot, camera_angles.azimuthal);

	mat4x4_mul(v, vRot, vPos);

	// Projection matrix

	mat4x4 p;
	mat4x4_perspective(p, fov, aspectRatio, 0.1f, 100.f);

	// Combine

	mat4x4_mul(mvp, v, m);
	mat4x4_mul(mvp, p, mvp);

}

#pragma once

#include <glad/gl.h>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

using glm::mat4x4;

namespace GLHelper
{
	class Camera
	{

	public:
		struct position
		{
			float x, y, z;
		};
		struct angles
		{
			float polar, azimuthal;
		};

	private:

		float aspectRatio;

		position camera_position;
		angles camera_angles;
		float fov;

	public:

		Camera(float aspectRatio, float fov);

		position getPosition() const;
		angles getAngles() const;
		float getFov() const;

		void setPosition(position pos);
		void setAngles(angles as);
		void setFov(float fov);

		mat4x4 genMVP(mat4x4 m) const;

	};
}
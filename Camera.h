#pragma once

#include <glad/gl.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/ext/vector_common.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

using glm::vec3;
using glm::mat4x4;

namespace GLHelper
{
	class Camera
	{

	public:
		struct angles
		{
			float polar, azimuthal;
		};

	private:

		float aspectRatio;

		vec3 camera_position;
		angles camera_angles;
		float fov;

	public:

		Camera(float aspectRatio, float fov);

		vec3 getPosition() const;
		angles getAngles() const;
		float getFov() const;

		void setPosition(vec3 pos);
		void setAngles(angles as);
		void setFov(float fov);

		mat4x4 genMVP(mat4x4 m) const;

	};
}
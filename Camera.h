#pragma once

#include <glad/gl.h>
#include <linmath.h>

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

		void genMVP(mat4x4 mvp, mat4x4 m) const;

	};
}
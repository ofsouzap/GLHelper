#version 330

uniform mat4 mvp;

in vec3 vPos;
in vec2 vUV;

out vec2 uv;

void main()
{
	gl_Position = mvp * vec4(vPos, 1.0);
	uv = vUV;
}
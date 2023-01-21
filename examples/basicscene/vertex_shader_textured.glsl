#version 330

uniform mat4 mvp;

in vec3 oc_pos; // Position of the vertex in object space
in vec2 uv; // UV coordinate of the vertex

out vec2 frag_uv; // UV coordinate of a fragment

void main()
{
	gl_Position = mvp * vec4(oc_pos, 1.0);
	frag_uv = uv;
}
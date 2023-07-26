#version 330

uniform mat4 m;
uniform mat4 mvp;
uniform mat4 norm_m;

in vec3 oc_pos; // Position of the vertex in object space
in vec2 uv; // UV coordinate of the vertex
in vec3 oc_norm; // Normal of the vertex in object space

out vec3 wc_pos; // Position of a fragment in world space
out vec2 frag_uv; // UV coordinate of a fragment
out vec3 wc_norm; // Normal of a fragment in world space

void main()
{

	wc_pos = (m * vec4(oc_pos, 1.0)).xyz;
	gl_Position = mvp * vec4(oc_pos, 1.0);

	wc_norm = (norm_m * vec4(oc_norm, 1.0)).xyz;

	frag_uv = uv;

}
#version 330

uniform sampler2D textureSampler;
uniform vec3 wc_camera_pos; // Position of the camera in world space

in vec3 wc_pos; // Position of a fragment in world space
in vec2 frag_uv; // UV coordinate of a fragment
in vec3 wc_norm; // Normal of a fragment in world space

void main()
{

	// Have a constant sun light pointing in the direction (-1,-1,-1)

	vec3 light_dir = vec3(-1, -1, -1);

	// Get texture color from sampler

	vec3 tex_color = texture(textureSampler, frag_uv).rgb;

	// Calculate diffuse color multiplier (assume object only uses diffuse, no specular)

	vec3 N = normalize(wc_norm); // Normal
	vec3 L = -1 * light_dir; // Vector to light source

	float diffuse = dot(N, L);

	// Calculate final color

	gl_FragColor = vec4(tex_color * diffuse, 1.0);

}
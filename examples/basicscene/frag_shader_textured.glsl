#version 330

uniform sampler2D textureSampler;
uniform vec3 wc_camera_pos; // Position of the camera in world space
uniform vec3 wc_light_pos; // Position of the light source in world space

in vec3 wc_pos; // Position of a fragment in world space
in vec2 frag_uv; // UV coordinate of a fragment
in vec3 wc_norm; // Normal of a fragment in world space

void main()
{

	// Get texture color from sampler

	vec3 tex_color = texture(textureSampler, frag_uv).rgb;

	// Calculate diffuse color multiplier (assume object only uses diffuse, no specular)

	vec3 N = normalize(wc_norm); // Normal vector
	vec3 L = normalize(wc_light_pos - wc_pos); // Vector to light source

	float diffuse = dot(N, L);

	// Calculate final color

	gl_FragColor = vec4(tex_color * diffuse, 1.0);

}
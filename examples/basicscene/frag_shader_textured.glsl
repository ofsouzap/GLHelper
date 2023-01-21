#version 330

uniform sampler2D textureSampler;

in vec2 frag_uv;

void main()
{
	gl_FragColor = vec4(texture(textureSampler, frag_uv).rgb, 1.0);
}
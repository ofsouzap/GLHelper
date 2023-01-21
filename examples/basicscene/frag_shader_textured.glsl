#version 330

uniform sampler2D textureSampler;

in vec2 uv;

void main()
{
	gl_FragColor = vec4(texture(textureSampler, uv).rgb, 1.0);
}
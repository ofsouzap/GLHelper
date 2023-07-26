#version 330 core

uniform mat4 m;
uniform mat4 mvp;
uniform mat4 norm_m;

in vec3 oc_pos;
in vec3 oc_norm;
in vec2 uv;

out vec3 wc_pos;
out vec3 wc_norm;
out vec2 frag_uv;

void main()
{

    wc_pos = (m * vec4(oc_pos, 1.0)).xyz;
    wc_norm = (norm_m * vec4(oc_norm, 1.0)).xyz;

    gl_Position = mvp * vec4(oc_pos, 1.0);

    frag_uv = uv;

}

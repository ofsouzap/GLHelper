#version 330 core

uniform sampler2D textureSampler;
uniform vec3 wc_camera_pos;
uniform vec3 wc_light_pos;
uniform vec3 light_col_diff;
uniform vec3 light_col_spec;
uniform float diff_coeff;
uniform float spec_coeff;
uniform float roughness;

in vec3 wc_pos;
in vec3 wc_norm;
in vec2 frag_uv;

void main()
{

    // Texture sample

    vec3 tex_col = texture(textureSampler, frag_uv*50).rgb;

    // Diffuse and specular factor calculations

    float diff, spec;

    vec3 L = normalize(wc_light_pos - wc_pos);
    vec3 V = normalize(wc_camera_pos - wc_pos);
    vec3 N = normalize(wc_norm);

    diff = max(dot(L, N), 0);
    spec = max(pow(dot(L, V), roughness), 0);

    vec3 diff_col = diff * light_col_diff * diff_coeff;
    vec3 spec_col = spec * light_col_spec * spec_coeff;

    // Final color

    vec3 color = (diff_col * tex_col) + (spec_col * tex_col);

    // gl_FragColor = vec4(normalize(vec3(dot(L, V))), 1.0);
    // gl_FragColor = vec4(vec3(spec), 1.0);
    gl_FragColor = vec4(color, 1.0);

}

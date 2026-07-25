#version 330 core
in vec3 vertex_color;
in vec2 tex_pos_in;

out vec4 frag_color;

uniform sampler2D tex_sampler;

void main() {
    frag_color = texture(tex_sampler, tex_pos_in) * vec4(vertex_color, 1.0f);
}

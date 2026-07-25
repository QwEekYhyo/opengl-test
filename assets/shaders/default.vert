#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 tex_pos_in;

out vec3 vertex_color;
out vec3 tex_pos_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(pos, 1.0f);
    vertex_color = color;
    tex_pos_out = tex_pos_in;
}

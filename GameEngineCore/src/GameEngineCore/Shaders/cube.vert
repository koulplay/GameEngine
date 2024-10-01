#version 460
layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texture_cords;

out vec3 frag_pos;
out vec3 normal;
out vec2 texture_cords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(a_pos, 1.0);
    frag_pos = vec3(model * vec4(a_pos, 1.0f));
    normal = mat3(transpose(inverse(model))) * a_normal;
    texture_cords = a_texture_cords;
}
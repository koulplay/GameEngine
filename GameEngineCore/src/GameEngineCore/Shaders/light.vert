#version 460
layout(location = 0) in vec3 vertex_position;

uniform mat4 model_matrix;
uniform mat4 view_projection_matrix;

void main() {
	gl_Position = view_projection_matrix * model_matrix * vec4(vertex_position, 1.0);
}
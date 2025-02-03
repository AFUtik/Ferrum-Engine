#version 330 core

layout(location = 0) in vec3 v_pos;
layout(location = 1) in vec2 v_texCoord;

layout(location = 2) in mat4 v_model;
layout(location = 6) in vec2 v_texOffset;

out vec4 a_color;
out vec2 a_texCoord;

uniform mat4 projview;

void main() {
	a_texCoord = v_texCoord + v_texOffset;
	gl_Position = projview * v_model * vec4(v_pos, 1.0f);
}
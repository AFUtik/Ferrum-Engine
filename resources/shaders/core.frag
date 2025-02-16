#version 330 core

in vec2 a_texCoord;
out vec4 f_color;

uniform sampler2D u_texture0;

void main() {
	vec4 texColor = texture(u_texture0, a_texCoord);
	if(texColor.a == 0.0f)
        discard;
	f_color = texColor;
}
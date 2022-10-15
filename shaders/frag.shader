#version 330 core

in vec4 a_col;
in vec2 a_texCoord;
out vec4 f_col;

uniform sampler2D u_texture0;

void main()
{
	f_col = a_col * texture(u_texture0, a_texCoord);
}

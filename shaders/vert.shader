#version 330 core

layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec2 v_texCoord;

out vec4 a_col;
out vec2 a_texCoord;

uniform mat4 u_view_matrix;
uniform mat4 u_proj_matrix;

void main()
{
	a_col = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	a_texCoord = v_texCoord;
	gl_Position = u_proj_matrix * u_view_matrix * vec4(v_pos, 1.0f);
}

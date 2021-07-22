#version 330 core
out vec4 FragColour;

in vec3 v_col;

uniform sampler2D tex_sam1;

void main()
{
	FragColour = vec4(v_col, 1);
}

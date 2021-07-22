#version 330 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in int a_texref;

out vec3 v_col;

void main()
{
	int texref = a_texref;
	if (texref == 0) {
		v_col = vec3(1.0, 1.0, 1.0);
	} else if (texref == 1) {
		v_col = vec3(1.0, 0.0, 0.0);
	} else if (texref == 2) {
		v_col = vec3(1.0, 1.0, 0.0);
	} else if (texref == 3) {
		v_col = vec3(0.0, 1.0, 0.0);
	} else if (texref == 4) {
		v_col = vec3(0.0, 0.0, 1.0);
	}

	gl_Position = vec4(a_pos, 1.0f);


}

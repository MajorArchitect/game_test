#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "matvec.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define W_WIDTH 600
#define W_HEIGHT 400

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

struct s_entity *entity = NULL;
unsigned int entity_c = 0;

struct vbo_vert {
	vec3 vert;
	char texref;
};

int main()
{

	//Opengl stuff
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	GLFWwindow *window = glfwCreateWindow(W_WIDTH, W_HEIGHT, "Game",
		NULL, NULL);
	if (window == NULL) {
		printf("Could not create window\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialise GLAD\n");
		return -1;
	}
	glViewport(0, 0, W_WIDTH, W_HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetWindowAspectRatio(window, 4, 3);

	unsigned int shaderprog = mkshader("res/shad/w_vert.vs", "res/shad/w_frag.fs");
	if (shaderprog == 0) {
		printf("ERROR: mkshader returned zero.\n");
		exit(100);
	}

	glUseProgram(shaderprog);


	int vbo, vao;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindVertexArray(vao);

	struct vbo_vert data[] = {{0.0f, 0.0f, 0.0f, 0},
		{ 0.5f, -0.5f, 0.0f, 1},
		{ 0.5f,  0.5f, 0.0f, 2},
		{-0.5f,  0.5f, 0.0f, 3},
		{-0.5f, -0.5f, 0.0f, 4},
		{ 0.5f, -0.5f, 0.0f, 1}};

	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct vbo_vert), (void *)0);
	glVertexAttribPointer(1, 1, GL_BYTE, GL_FALSE, sizeof(struct vbo_vert), (void *)(sizeof(vec3)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//game loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        	glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

		glfwSwapBuffers(window);
	}
	glDeleteProgram(shaderprog);

	glfwTerminate();
	return 0;
}


void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

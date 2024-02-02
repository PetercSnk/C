#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "Shader.h"
#include "Renderer.h"

void framebuffer_size_callback(GLFWwindow* window, GLint width, GLint height);
void processInput(GLFWwindow* window);

int main() {
	// initialise GLFW
	glfwInit();
	// OpenGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// explicitly tell GLFW to use core profile, don't need backwards-compatable features
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// create window object
	GLFWwindow* window = glfwCreateWindow(800, 600, "TEST", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// initialise GLAD, manages function pointers for OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialise GLAD" << std::endl;
		return -1;
	}
	// tell OpenGL the location and size of rendering window
	glViewport(0, 0, 800, 600);
	// when window is resized
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	// test

	float positions[] = {
		-0.5f, -0.5f, 0.0f,	1.0f, 0.0f, 0.0f, // bottom left
		-0.5f,	0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // top left
		 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom right
		 0.5f,	0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // top right
	};

	unsigned int indices[] = {
		0, 1, 2,
		1, 2, 3
	};

	VAO vao;
	vao.bind();

	VBO vbo(24 * sizeof(float), positions);
	EBO ebo(6, indices);

	// position attributes
	vao.linkAttrib(vbo, 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	// color attributes
	vao.linkAttrib(vbo, 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

	vao.unbind();
	vbo.unbind();
	ebo.unbind();

	Renderer renderer;

	// create program object with vertex and fragment shader sources
	Shader shader("D:\\Repository\\C\\App\\App\\Resource Files\\Shaders\\default.vert", "D:\\Repository\\C\\App\\App\\Resource Files\\Shaders\\default.frag");
	// activate the program object, all shader and rendering calls will now use this program object


	// use wireframe polygons
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// keep running until we tell GLFW to stop
	while (!glfwWindowShouldClose(window)) {
		// input
		processInput(window);
		// render 
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		renderer.clear();
		renderer.draw(shader, vao, ebo);
		// swaps colour buffer, used to render during this render iteration and show output to screen
		glfwSwapBuffers(window);
		// checks for event triggers
		glfwPollEvents();
	}
	// de-allocate all resources
	vao.del();
	vbo.del();
	ebo.del();
	shader.del();
	glfwTerminate();
	return 0;
}

// callback function to resize rendering window
void framebuffer_size_callback(GLFWwindow* window, GLint width, GLint height) {
	glViewport(0, 0, width, height);
}

// check for key presses
void processInput(GLFWwindow* window) {
	// exit on escape key
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
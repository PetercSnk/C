#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VBO.h"
#include "EBO.h"
#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
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

	// 2d triangle
	float positions[] = {
		-0.5f, -0.5f, 0.0f,	1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.0f,  0.7f, 0.0f, 0.0f, 0.0f, 1.0f,
	};

	// rectangle
	float rectangle[] = {
		-0.5f,  0.5f, 0.0f, // top left
		 0.5f,  0.5f, 0.0f, // top right
		-0.5f, -0.5f, 0.0f, // bottom left
		 0.5f, -0.5f, 0.0f  // bottom right
	};

	unsigned int indices[] = {
		0, 1, 2,
		1, 2, 3
	};


	// generate and bind vertex array object, this stores the vertex attribute configuration and which VBO / EBO to use
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	VBO v(positions, 18 * sizeof(float));


	// specify how vertex data should be intpreted
	// position attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	// color attributes
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// enable the vertex attribute(s) with the vertex attribute location as its argument
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	v.unbind();
	glBindVertexArray(0);
	

	// create program object with vertex and fragment shader sources
	Shader shader("D:\\Repository\\C\\App\\App\\Resource Files\\Shaders\\default.vert", "D:\\Repository\\C\\App\\App\\Resource Files\\Shaders\\default.frag");
	// activate the program object, all shader and rendering calls will now use this program object


	// use wireframe polygons
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// keep running until we tell GLFW to stop
	while (!glfwWindowShouldClose(window)) {
		shader.activate();
		// check input
		processInput(window);
		// render commands

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/*float t = glfwgettime();
		float r = (sin(t));
		int color = glgetuniformlocation(shader_program, "color");
		gluniform4f(color, r, 1.0f, 1.0f, 1.0f);*/

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		// swaps colour buffer, used to render during this render iteration and show output to screen
		glfwSwapBuffers(window);
		// checks for event triggers
		glfwPollEvents();
	}
	// de-allocate all resources
	
	
	//glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
	v.del();
	shader.del();
	glfwTerminate();
	return 0;
}

// callback function to resize rendering window
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// check for key presses
void processInput(GLFWwindow* window) {
	// exit on escape key
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
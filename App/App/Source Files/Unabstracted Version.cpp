#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
static unsigned int create_shader(const char* vertex_shader_source, const char* fragment_shader_source);
static unsigned int compile_shader(unsigned int type, const char* source);

const char* vertex_shader_source =
	"#version 330 core\n"
	"layout (location = 0) in vec3 position;\n"
	"layout (location = 1) in vec3 in_color;\n"
	"out vec3 color;\n"
	"void main()\n"
	"{\n"
	"    gl_Position = vec4(position, 1.0);\n"
	"    color = in_color;\n"
	"}\0";

const char* fragment_shader_source =
	"#version 330 core\n"
	"out vec4 frag_color;\n"
	"in vec3 color;\n"
	"void main()\n"
	"{\n"
	"    frag_color = vec4(color, 1.0);\n"
	"}\0";

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

	unsigned int VAO, VBO;//, EBO;
	// generate and bind vertex array object, this stores the vertex attribute configuration and which VBO / EBO to use
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	// create unique buffer id for VBO and EBO
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);
	// bind VBO to GL_ARRAY_BUFFER and EBO to GL_ELEMENT_ARRAY, buffer calls made on GL_ will configure VBO or EBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// copy defined data into buffers memory
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// specify how vertex data should be intpreted
	// position attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	// color attributes
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// enable the vertex attribute(s) with the vertex attribute location as its argument
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	// unbind VBO and VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// create program object with vertex and fragment shader sources
	unsigned int shader_program = create_shader(vertex_shader_source, fragment_shader_source);
	// activate the program object, all shader and rendering calls will now use this program object
	glUseProgram(shader_program);

	// use wireframe polygons
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// keep running until we tell GLFW to stop
	while (!glfwWindowShouldClose(window)) {
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
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
	glDeleteProgram(shader_program);
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

static unsigned int create_shader(const char* vertex_shader_source, const char* fragment_shader_source) {
	// compile both vertex and fragment shaders
	unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex_shader_source);
	unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader_source);
	// create program, this returns an id reference to program object
	unsigned int shader_program = glCreateProgram();
	// attach compiled shaders to program object and link them
	glAttachShader(shader_program, vs);
	glAttachShader(shader_program, fs);
	glLinkProgram(shader_program);
	// check for linking errors
	int result;
	char info_log[512];
	// queries a program object, GL_LINK_STATUS returns GL_TRUE if the last link operation on shader_program was successful, and GL_FALSE otherwise
	glGetProgramiv(shader_program, GL_LINK_STATUS, &result);
	if (!result) {
		// returns the information log for program object
		glGetProgramInfoLog(shader_program, 512, NULL, info_log);
		std::cout << "LINKING FAILED\n" << info_log << std::endl;
	}
	// dont need shader objects after linking them to the program object
	glDeleteShader(vs);
	glDeleteShader(fs);
	return shader_program;
}

static unsigned int compile_shader(unsigned int type, const char* source) {
	// type defines what shader is created e.g. GL_VERTEX_SHADER or GL_FRAGMENT_SHADER, result is shader object referenced by an id
	unsigned int id = glCreateShader(type);
	// attach the shader source code to the shader object and compile
	glShaderSource(id, 1, &source, nullptr);
	glCompileShader(id);
	// check for compilation errors
	int result;
	char info_log[512];
	// queries a shader object, GL_COMPILE_STATUS returns GL_TRUE if the last compile operation on id was successful, and GL_FALSE otherwise
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (!result) {
		// returns the information log for a shader object
		glGetShaderInfoLog(id, 512, NULL, info_log);
		std::cout << "COMPILATION FAILED " << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << std::endl;
		std::cout << info_log << std::endl;
		// frees occupied memory, effectively undoes the effects of a call to glCreateShader
		glDeleteShader(id);
		return 0;
	}
	return id;
}

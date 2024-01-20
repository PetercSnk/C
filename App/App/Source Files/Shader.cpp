#include "Shader.h"

std::string read_binary_file(const char* path) {
	// open binary file and set read position to end of file
	std::ifstream input(path, std::ios::binary|std::ios::ate|std::ios::in);
	// check if opened successfully
	if (input.is_open()) {
		// placeholder for file content
		std::string content;
		// find size of input and resize content
		int size = input.tellg();
		content.resize(size);
		// go to start of input
		input.seekg(0, std::ios::beg);
		// read input as block
		input.read(&content[0], size);
		// close input file and return content
		input.close();
		return content;
	}
	else {
		perror("Failed to open file");
	}
}

static unsigned int create_shader(const char* vertex_shader, const char* fragment_shader) {
	// compile both vertex and fragment shaders
	unsigned int vs_id = compile_shader(GL_VERTEX_SHADER, vertex_shader);
	unsigned int fs_id = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);
	// create program, this returns an id reference to program object
	unsigned int shader_program = glCreateProgram();
	// attach compiled shaders to program object and link them
	glAttachShader(shader_program, vs_id);
	glAttachShader(shader_program, fs_id);
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
	glDeleteShader(vs_id);
	glDeleteShader(fs_id);
	return shader_program;
}

static unsigned int compile_shader(unsigned int type, const char* shader) {
	// type defines what shader is created e.g. GL_VERTEX_SHADER or GL_FRAGMENT_SHADER, result is shader object referenced by an id
	unsigned int id = glCreateShader(type);
	// attach the shader source code to the shader object and compile
	glShaderSource(id, 1, &shader, nullptr);
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

Shader::Shader(const char* vertex_path, const char* fragment_path) {
	std::string vertex_shader = read_binary_file(vertex_path);
	std::string fragment_shader = read_binary_file(fragment_path);
	const char* vertex_shader_cstr = vertex_shader.c_str();
	const char* fragment_shader_cstr = fragment_shader.c_str();
	shader_program = create_shader(vertex_shader_cstr, fragment_shader_cstr);
}

void Shader::activate() {
	glUseProgram(shader_program);
}

void Shader::del() {
	glDeleteProgram(shader_program);
}
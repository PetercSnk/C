#pragma once
#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <cerrno>
#include <string>

std::string read_binary_file(const char* path);
static GLuint create_shader(const char* vertex_shader, const char* fragment_shader);
static GLuint compile_shader(GLenum type, const char* shader);

class Shader {
public:
	// shader program identifier
	GLuint shader_program;
	// constructor reads and builds shaders
	Shader(const char* vertex_path, const char* fragment_path);
	// activates shader program
	void activate();
	// deletes shader program
	void del();
};
#endif
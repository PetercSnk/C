#pragma once
#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <cerrno>
#include <string>

// returns the contents of a binary file as a string 
std::string read_binary_file(const char* path);
// returns a program object with the specified shaders attached and linked
static GLuint create_shader(const char* vertex_shader, const char* fragment_shader);
// compiles a shader of type type and returns a reference value
static GLuint compile_shader(GLenum type, const char* shader);

class Shader {
public:
	// program object name
	GLuint shader_program;
	// constructor reads and builds shaders
	Shader(const char* vertex_path, const char* fragment_path);
	// binds program object
	void bind() const;
	// unbinds program object
	void unbind() const;
	// deletes program object and its contents
	void del();
};
#endif
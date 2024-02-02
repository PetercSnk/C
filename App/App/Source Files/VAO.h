#pragma once
#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h"

class VAO {
private:
	// vertex array object name
	GLuint id;
public:
	// constructor generates vertex array object
	VAO();
	// link a VBOs vertex data to this vertex array object
	void linkAttrib(VBO& VBO, GLuint index, GLuint size, GLenum type, GLboolean normalized, GLsizeiptr stride, GLvoid* offset);
	// binds vertex array object
	void bind() const;
	// unbinds vertex array object
	void unbind() const;
	// deletes vertex array object and its contents
	void del();
};
#endif
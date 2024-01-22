#pragma once
#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h"

class VAO {
private:
	GLuint id;
public:
	VAO();
	void linkAttrib(VBO& VBO, GLuint index, GLuint size, GLenum type, GLboolean normalized, GLsizeiptr stride, GLvoid* offset);
	void bind() const;
	void unbind() const;
	void del();
};
#endif
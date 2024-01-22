#pragma once
#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO {
private:
	GLuint id;
public:
	VBO(GLsizeiptr size, const GLfloat* vertices);
	void bind() const;
	void unbind() const;
	void del();
};
#endif
#pragma once
#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO {
private:
	// buffer object name
	GLuint id;
public:
	// constructor generates and binds buffer object, then copies vertices data into it
	VBO(GLsizeiptr size, const GLfloat* vertices);
	// binds buffer object
	void bind() const;
	// unbinds buffer object
	void unbind() const;
	// deletes buffer object and its contents
	void del();
};
#endif
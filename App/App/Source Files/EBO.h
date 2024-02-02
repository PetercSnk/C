#pragma once
#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

class EBO {
private:
	// number of indices in this buffer object
	GLuint count;
	// buffer object name
	GLuint id;
public:
	// constructor generates and binds buffer object, then copies indices data into it
	EBO(GLuint count, const GLuint* indices);
	// binds buffer object
	void bind() const;
	// unbinds buffer object
	void unbind() const;
	// deletes buffer object and its contents
	void del();
	// returns the number of indices stored in this buffer object
	GLuint get_count() const;
};
#endif
#pragma once
#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

class EBO {
private:
	GLuint count;
	GLuint id;
public:
	EBO(const GLuint* indices, GLuint count);
	void bind() const;
	void unbind() const;
	void del();
	GLuint get_count() const;
};
#endif
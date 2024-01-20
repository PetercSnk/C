#pragma once
#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO {
private:
	unsigned int id;
public:
	VBO(const float* vertices, unsigned int size);
	void bind() const;
	void unbind() const;
	void del() const;
};
#endif
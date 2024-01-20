#pragma once
#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

class EBO {
private:
	unsigned int count;
	unsigned int id;
public:
	EBO(const unsigned int* indices, unsigned int count);
	void bind() const;
	void unbind() const;
	void del() const;
	unsigned int get_count() const;
};
#endif
#pragma once
#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h"

class VAO {
public:
	unsigned int id;
	VAO();
	void link(VBO VBO, unsigned int layout);
	void bind();
	void unbind();
	void del();
};
#endif
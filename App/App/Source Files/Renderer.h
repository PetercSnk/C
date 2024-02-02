#pragma once
#ifndef RENDERER_CLASS_H
#define RENDERER_CLASS_H

#include <glad/glad.h>
#include "Shader.h"
#include "VAO.h"
#include "EBO.h"

class Renderer {
public:
	// renders the current VAO 
	void draw(const Shader& shader, const VAO& vao, const EBO& ebo) const;
	// clears buffer
	void clear();
};

#endif
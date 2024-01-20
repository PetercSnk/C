#include "VBO.h"

VBO::VBO(const float* vertices, unsigned int size) {
	// create unique buffer id for VBO
	glGenBuffers(1, &id);
	// bind VBO to GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, id);
	// copy defined data into buffers memory
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::bind() const {
	// bind VBO to GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VBO::unbind() const {
	// unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::del() const {
	// delete VBO
	glDeleteBuffers(1, &id);
}
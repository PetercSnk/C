#include "VBO.h"

// VBO constructor
VBO::VBO(GLsizeiptr size, const GLfloat* vertices) {
	// create unique buffer id for VBO
	glGenBuffers(1, &id);
	// bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, id);
	// copy defined data into buffers memory
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

// bind VBO
void VBO::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

// unbind VBO
void VBO::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// delete VBO
void VBO::del() {
	glDeleteBuffers(1, &id);
}
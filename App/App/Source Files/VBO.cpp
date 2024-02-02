#include "VBO.h"

// VBO constructor
VBO::VBO(GLsizeiptr size, const GLfloat* vertices) {
	// generate one buffer object name in id for this VBO instance
	glGenBuffers(1, &id);
	// bind buffer object to GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, id);
	// copy vertices data into the buffer object bound to GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

// bind buffer object to GL_ARRAY_BUFFER
void VBO::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

// binding zero will unbind the current buffer object
void VBO::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// delete buffer object and its contents
void VBO::del() {
	glDeleteBuffers(1, &id);
}
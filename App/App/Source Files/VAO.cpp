#include "VAO.h"

// constructor generates id for the VAO
VAO::VAO() {
	glGenVertexArrays(1, &id);
}

// links VBO attributes to the VAO
void VAO::linkAttrib(VBO& VBO, GLuint index, GLuint size, GLenum type, GLboolean normalized, GLsizeiptr stride, GLvoid* offset) {
	VBO.bind();
	// specify how vertex data should be intpreted
	glVertexAttribPointer(index, size, type, normalized, stride, offset);
	// enable the vertex attribute with the vertex attribute location as its argument
	glEnableVertexAttribArray(index);
	VBO.unbind();
}

// bind VAO
void VAO::bind() const {
	glBindVertexArray(id);
}

// unbind VAO
void VAO::unbind() const {
	glBindVertexArray(0);
}

// delete VAO
void VAO::del() {
	glDeleteVertexArrays(1, &id);
}


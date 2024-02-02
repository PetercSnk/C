#include "VAO.h"

// VAO constructor
VAO::VAO() {
	// generate one vertex array object name in id for this VAO instance
	glGenVertexArrays(1, &id);
}

// link a VBOs vertex data to this vertex array object
void VAO::linkAttrib(VBO& VBO, GLuint index, GLuint size, GLenum type, GLboolean normalized, GLsizeiptr stride, GLvoid* offset) {
	// bind the VBO whose vertices are to be defined
	VBO.bind();
	// define how the VBOs vertex data should be intpreted
	glVertexAttribPointer(index, size, type, normalized, stride, offset);
	// enable the vertex attribute array
	glEnableVertexAttribArray(index);
	// unbind the bound VBO
	VBO.unbind();
}

// bind the vertex array object with name id
void VAO::bind() const {
	glBindVertexArray(id);
}

// binding zero will break the existing vertex array object binding
void VAO::unbind() const {
	glBindVertexArray(0);
}

// delete vertex array object and its contents
void VAO::del() {
	glDeleteVertexArrays(1, &id);
}


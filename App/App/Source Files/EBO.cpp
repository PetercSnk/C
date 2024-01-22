#include "EBO.h"

EBO::EBO(const GLuint* indices, GLuint count) : 
	count(count) {
	// create unique buffer id for EBO
	glGenBuffers(1, &id);
	// bind EBO to GL_ELEMENT_ARRAY
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	// copy defined data into buffers memory
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), indices, GL_STATIC_DRAW);
}

// bind EBO
void EBO::bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

// unbind EBO
void EBO::unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// delete EBO
void EBO::del() {
	glDeleteBuffers(1, &id);
}

// get number of indices
GLuint EBO::get_count() const {
	return count;
}
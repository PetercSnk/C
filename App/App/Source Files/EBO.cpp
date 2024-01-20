#include "EBO.h"

EBO::EBO(const unsigned int* indices, unsigned int count) : 
	count(count) {
	// create unique buffer id for EBO
	glGenBuffers(1, &id);
	// bind EBO to GL_ELEMENT_ARRAY
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	// copy defined data into buffers memory
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

void EBO::bind() const {
	// bind EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void EBO::unbind() const {
	// unbind EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::del() const {
	// delete EBO
	glDeleteBuffers(1, &id);
}

unsigned int EBO::get_count() const {
	return count;
}
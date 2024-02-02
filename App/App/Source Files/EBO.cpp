#include "EBO.h"

// EBO constructor
EBO::EBO(GLuint count, const GLuint* indices) :
	// set this count to count
	count(count) {
	// generate one buffer object name in id for this EBO instance
	glGenBuffers(1, &id);
	// bind buffer object to GL_ELEMENT_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	// copy indices data into the buffer object bound to GL_ELEMENT_ARRAY_BUFFER
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), indices, GL_STATIC_DRAW);
}

// bind buffer object to GL_ELEMENT_ARRAY_BUFFER
void EBO::bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

// binding zero will unbind the current buffer object
void EBO::unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// delete buffer object and its contents
void EBO::del() {
	glDeleteBuffers(1, &id);
}

// get the total number of indices in this buffer object
GLuint EBO::get_count() const {
	return count;
}
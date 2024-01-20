#include "VAO.h"

VAO::VAO() {
	// generate VAO id
	glGenVertexArrays(1, &id);
}

void VAO::bind() {
	// bind VAO
	glBindVertexArray(id);
}

void VAO::unbind() {
	// unbind VAO
	glBindVertexArray(0);
}

void VAO::del() {
	// delete VAO
	glDeleteVertexArrays(1, &id);
}

void VAO::link(VBO& VBO, unsigned int layout) {

}
#include "Renderer.h"

void Renderer::draw(const Shader& shader, const VAO& vao, const EBO& ebo) const {
	// bind the shader to be used
	shader.bind();
	// bind the VAO to be used
	vao.bind();
	// renders whatever is bound to the VAO with the current shader program
	glDrawElements(GL_TRIANGLES, ebo.get_count(), GL_UNSIGNED_INT, 0);
}

// clears buffers to preset values
void Renderer::clear() {
	glClear(GL_COLOR_BUFFER_BIT);
}
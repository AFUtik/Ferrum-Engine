#include "Mesh.hpp"

#include <GL/glew.h>
#include <iostream>

Mesh::Mesh(VertexBuffer *data) : vertex_buffer(data){
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	/* VERTEX BUFFER */
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(
		GL_ARRAY_BUFFER, 
		sizeof(GLfloat) * vertex_buffer->vertices_size * VERTEX_SIZE, 
		vertex_buffer->vertex_arr, 
		GL_STATIC_DRAW
	);
	uint32_t offset = 0;
	uint32_t i = 0;
	while(ATTRIBUTES[i]) {
		const uint32_t &size = ATTRIBUTES[i];
		glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(GLfloat), (GLvoid*)(offset * sizeof(float)));
		glEnableVertexAttribArray(i);
		offset += size;
		i++;
	}
	
	/* EBO BUFFER */
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER, 
		vertex_buffer->indices_size * sizeof(GLuint), 
		vertex_buffer->index_arr, 
		GL_STATIC_DRAW
	);
	
	/* INSTANCE BUFFER */
	glGenBuffers(1, &ivbo);
	glBindBuffer(GL_ARRAY_BUFFER, ivbo);
	glBufferData(
		GL_ARRAY_BUFFER,
		instance_buffer_size * INSTANCE_MEMORY_SIZE_F, 
		nullptr, 
		GL_DYNAMIC_DRAW
	);
	for (int j = 0; j < 4; j++) {
    	glEnableVertexAttribArray(j + i);
    	glVertexAttribPointer(j + i, 4, GL_FLOAT, GL_FALSE, INSTANCE_MEMORY_SIZE_F, (void*)(sizeof(GLfloat) * 4 * j));
    	glVertexAttribDivisor(j + i, 1);
	}
	i+=4;
	glEnableVertexAttribArray(i);
	glVertexAttribPointer(i, 2, GL_FLOAT, GL_FALSE, INSTANCE_MEMORY_SIZE_F, (void*)(sizeof(GLfloat)*16));
	glVertexAttribDivisor(i, 1);

	glBindVertexArray(0);
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &ivbo);
}

void Mesh::updateInstanceBuffer(const size_t& size) {
	instance_buffer_size = size;
	glBindBuffer(GL_ARRAY_BUFFER, ivbo);
    glBufferData(GL_ARRAY_BUFFER, size * INSTANCE_MEMORY_SIZE_F, nullptr, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::updateInstanceBuffer(unsigned int index, unsigned int offset, const Instance &instance) {
	glBindBuffer(GL_ARRAY_BUFFER, ivbo);
	void* ptr = glMapBufferRange(GL_ARRAY_BUFFER, index * INSTANCE_MEMORY_SIZE_F, INSTANCE_MEMORY_SIZE_F,
	                             GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
	if (ptr) {
	    memcpy(ptr, instance.data + offset, INSTANCE_MEMORY_SIZE_F);
	    glUnmapBuffer(GL_ARRAY_BUFFER);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::draw(unsigned int primitive) {
	glBindVertexArray(vao);
	glDrawElementsInstanced(GL_TRIANGLES, vertex_buffer->indices_size, GL_UNSIGNED_INT, 0, instance_count);
	glBindVertexArray(0);
}
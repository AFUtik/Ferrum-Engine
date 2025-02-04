#include "Mesh.hpp"

#include <GL/glew.h>
#include <vector>
#include <iostream>

Mesh::Mesh(VertexBuffer *data) : m_vertexBufferData(data){

}

Mesh& Mesh::xyz(float x, float y, float z) {
	m_vertexBufferData->vertex_arr[buffer_index] = x;
	m_vertexBufferData->vertex_arr[buffer_index+1] = y;
	m_vertexBufferData->vertex_arr[buffer_index+2] = z;
	buffer_index+=3;
	return *this;
}

Mesh& Mesh::uv(float u, float v) {
	m_vertexBufferData->vertex_arr[buffer_index] = u;
	m_vertexBufferData->vertex_arr[buffer_index+1] = v;
	buffer_index+=2;
	return *this;
}

Mesh& Mesh::uv2(float u) {
	m_vertexBufferData->vertex_arr[buffer_index] = u;
	buffer_index++;
	return *this;
}

Mesh& Mesh::index(unsigned int i1, unsigned int i2, unsigned int i3) {
	m_vertexBufferData->index_arr[ind_index] = ind_offset+i1;
	m_vertexBufferData->index_arr[ind_index+1] = ind_offset+i2;
	m_vertexBufferData->index_arr[ind_index+2] = ind_offset+i3;
	ind_index+=3;
	return *this;
}

void Mesh::endIndex() {
	ind_offset=(buffer_index/m_vertexBufferData->vertex_size);
}

void Mesh::generate() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(
	GL_ARRAY_BUFFER, 
	sizeof(GLfloat) * m_vertexBufferData->vertex_count * m_vertexBufferData->vertex_size, 
	m_vertexBufferData->vertex_arr, 
	GL_STATIC_DRAW
	);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vertexBufferData->indices_size * sizeof(GLuint), m_vertexBufferData->index_arr, GL_STATIC_DRAW);

	int offset = 0;
	int i = 0;
	while(m_vertexBufferData->attributes_arr[i]) {
		int size = m_vertexBufferData->attributes_arr[i];
		glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, m_vertexBufferData->vertex_size * sizeof(GLfloat), (GLvoid*)(offset * sizeof(float)));
		glEnableVertexAttribArray(i);
		offset += size;
		i++;
	}
	
	glGenBuffers(1, &instance_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, instance_vbo);
	glBufferData(GL_ARRAY_BUFFER, instance_count * INSTANCE_MEMORY_SIZE, nullptr, GL_DYNAMIC_DRAW);
	for (int j = 0; j < 4; j++) {
    	glEnableVertexAttribArray(j + i);
    	glVertexAttribPointer(j + i, 4, GL_FLOAT, GL_FALSE, INSTANCE_MEMORY_SIZE, (void*)(sizeof(GLfloat) * 4 * j));
    	glVertexAttribDivisor(j + i, 1);
	}
	i+=4;
	glEnableVertexAttribArray(i);
	glVertexAttribPointer(i, 2, GL_FLOAT, GL_FALSE, INSTANCE_MEMORY_SIZE, (void*)(sizeof(GLfloat)*16));
	glVertexAttribDivisor(i, 1);

	glBindVertexArray(0);
}

void Mesh::updateInstanceBuffer(size_t size) {
	glBindBuffer(GL_ARRAY_BUFFER, instance_vbo);
    glBufferData(GL_ARRAY_BUFFER, size * INSTANCE_MEMORY_SIZE, nullptr, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::updateInstanceBuffer(int index, float* data) {
	glBindBuffer(GL_ARRAY_BUFFER, instance_vbo);
	void* ptr = glMapBufferRange(GL_ARRAY_BUFFER, index * INSTANCE_MEMORY_SIZE, INSTANCE_MEMORY_SIZE,
	                             GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
	if (ptr) {
	    memcpy(ptr, data, INSTANCE_MEMORY_SIZE);
	    glUnmapBuffer(GL_ARRAY_BUFFER);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::draw(unsigned int primitive) {
	glBindVertexArray(vao);
	glDrawElementsInstanced(GL_TRIANGLES, m_vertexBufferData->indices_size, GL_UNSIGNED_INT, 0, instance_count);
	glBindVertexArray(0);
}


void Mesh::setUV(float min_u, float max_u, float min_v, float max_v) {
	for(int i = 0; i < m_vertexBufferData->vertex_count; i++) {
		float &u = m_vertexBufferData->vertex_arr[3+i*m_vertexBufferData->vertex_size];
		float &v = m_vertexBufferData->vertex_arr[4+i*m_vertexBufferData->vertex_size];

		if(u==0.0f) u = min_u;
		else u = max_u;
		if(v==0.0f) v = min_v;
		else v = max_v;
	}
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &instance_vbo);
}

//void Mesh::add_vertex(float x, float y, float z, float u, float v) {
//	buffer[index]   = x;
//	buffer[index+1] = y;
//	buffer[index+2] = z;
//	buffer[index+3] = u;
//	buffer[index+4] = v;
//	index+=vertex_size;
//}

//void Mesh::generate() {
//	glGenVertexArrays(1, &vao);
//	glGenBuffers(1, &vbo);
//
//	glBindVertexArray(vao);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_size * vertices, buffer, GL_STATIC_DRAW);
//
//	// attributes
//	int offset = 0;
//	for (int i = 0; attrs[i]; i++) {
//		int size = attrs[i];
//		glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, vertex_size * sizeof(float), (GLvoid*)(offset * sizeof(float)));
//		glEnableVertexAttribArray(i);
//		offset += size;
//	}
//
//	glBindVertexArray(0);
//}

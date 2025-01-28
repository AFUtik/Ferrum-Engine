#include "Mesh.hpp"
#include <GL/glew.h>

//#include <iostream>

Mesh::Mesh(const VertexBufferDescriptor& data) {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.list_size * data.vertex_size, data.vertices_list, GL_STATIC_DRAW);

	// attributes
	int offset = 0;
	for (int i = 0; data.attributes_list[i]; i++) {
		int size = data.attributes_list[i];
		glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, data.vertex_size * sizeof(float), (GLvoid*)(offset * sizeof(float)));
		glEnableVertexAttribArray(i);
		offset += size;
	}

	glBindVertexArray(0);

	m_vertexBufferData = data;
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

void Mesh::draw(unsigned int primitive) {
	glBindVertexArray(vao);
	glDrawArrays(primitive, 0, m_vertexBufferData.list_size);
	glBindVertexArray(0);
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

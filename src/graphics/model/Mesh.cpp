#include "Mesh.hpp"
#include <GL/glew.h>

#include <iostream>

Mesh::Mesh(const VertexBufferDescriptor& data) {
	m_vertexBufferData = data;
}

void Mesh::generate() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(
	GL_ARRAY_BUFFER, 
	sizeof(float) * m_vertexBufferData.list_size * m_vertexBufferData.vertex_size, 
	m_vertexBufferData.vertices_list, 
	GL_STATIC_DRAW
	);

	// attributes
	int offset = 0;
	for (int i = 0; m_vertexBufferData.attributes_list[i]; i++) {
		int size = m_vertexBufferData.attributes_list[i];
		glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, m_vertexBufferData.vertex_size * sizeof(float), (GLvoid*)(offset * sizeof(float)));
		glEnableVertexAttribArray(i);
		offset += size;
	}

	glBindVertexArray(0);
}


void Mesh::draw(unsigned int primitive) {
	glBindVertexArray(vao);
	glDrawArrays(primitive, 0, m_vertexBufferData.list_size);
	glBindVertexArray(0);
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

void Mesh::setUV(float min_u, float max_u, float min_v, float max_v) {
	for(int i = 0; i < m_vertexBufferData.list_size; i++) {
		float &u = m_vertexBufferData.vertices_list[3+i*m_vertexBufferData.vertex_size];
		float &v = m_vertexBufferData.vertices_list[4+i*m_vertexBufferData.vertex_size];

		if(u==0.0f) u = min_u;
		else u = max_u;
		if(v==0.0f) v = min_v;
		else v = max_v;
	}
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

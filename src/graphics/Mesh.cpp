#include "Mesh.hpp"
#include <GL/glew.h>

Mesh::Mesh(size_t vertices, const int* attrs) : vertex_size(0), index(0), vertices(vertices) {
	for (int i = 0; attrs[i]; i++) {
		vertex_size += attrs[i];
	}
	buffer = new float[vertices*vertex_size];
}

void Mesh::add_vertex(int x, int y, int z, int u, int v) {
	buffer[index]   = x;
	buffer[index+1] = y;
	buffer[index+2] = z;
	buffer[index+3] = u;
	buffer[index+4] = v;
	index+=vertex_size;
}

void Mesh::generate() {
	int vertex_size = 0;
	for (int i = 0; attrs[i]; i++) {
		vertex_size += attrs[i];
	}

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_size * vertices, buffer, GL_STATIC_DRAW);

	// attributes
	int offset = 0;
	for (int i = 0; attrs[i]; i++) {
		int size = attrs[i];
		glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, vertex_size * sizeof(float), (GLvoid*)(offset * sizeof(float)));
		glEnableVertexAttribArray(i);
		offset += size;
	}

	glBindVertexArray(0);
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	delete[] buffer;
}

void Mesh::draw(unsigned int primitive) {
	glBindVertexArray(vao);
	glDrawArrays(primitive, 0, vertices);
	glBindVertexArray(0);
}
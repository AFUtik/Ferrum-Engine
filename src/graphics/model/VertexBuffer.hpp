#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

#include "VertexInfo.hpp"
#include <cstdint>

struct VertexBuffer {
    float *vertex_arr = nullptr;
	uint32_t vertices_size = 0;

	uint32_t *index_arr = nullptr;
	uint32_t indices_size = 0;

	VertexBuffer(const uint32_t &vertices_size, const uint32_t &indices_size) 
		: vertices_size(vertices_size), indices_size(indices_size) 
	{
		vertex_arr = new float[VERTEX_SIZE*vertices_size];
		index_arr = new uint32_t[indices_size];
	}
	VertexBuffer() {};

	~VertexBuffer() {
		delete[] vertex_arr;
		delete[] index_arr;
	}
};

#endif
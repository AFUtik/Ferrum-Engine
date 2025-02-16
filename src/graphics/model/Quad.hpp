#ifndef QUAD_HPP
#define QUAD_HPP

#include "Model.hpp"
#include <array>

class Quad : public Model {
private:
	std::array<float, QUAD_VERTEX_SIZE*VERTEX_SIZE> vertices = {
		 -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		 0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,
	};
	std::array<unsigned int, QUAD_INDEX_SIZE> indices = {
	    0, 1, 3,
		1, 2, 3
	};
public:
    Quad() : Model() {
		vertexBufferData = new VertexBuffer();

		vertexBufferData->vertex_arr = vertices.data();
		vertexBufferData->vertex_size = VERTEX_SIZE;
		vertexBufferData->vertex_count = QUAD_VERTEX_SIZE;
		
		vertexBufferData->attributes_arr = attrs;
		vertexBufferData->attributes_size = 3;

		vertexBufferData->index_arr = indices.data();
		vertexBufferData->indices_size = QUAD_INDEX_SIZE;
	};
};

#endif
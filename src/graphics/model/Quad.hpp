#ifndef QUAD_HPP
#define QUAD_HPP

#include "Model.hpp"

static float vertices[] = {
	 -0.5f,  -0.5f, 0.0f, 0.0f, 0.0f,
	 -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
	 0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,
};

static unsigned int indices[] = {
    0, 1, 3,
	1, 2, 3
};


class Quad : public Model {
public:
    Quad() : Model() {
		vertexBufferData = new VertexBuffer();

		vertexBufferData->vertex_arr = vertices;
		vertexBufferData->vertex_size = VERTEX_SIZE;
		vertexBufferData->vertex_count = 4;
		
		vertexBufferData->attributes_arr = attrs;
		vertexBufferData->attributes_size = 3;

		vertexBufferData->index_arr = indices;
		vertexBufferData->indices_size = SQUARE_INDEX_SIZE;
	};
};

#endif
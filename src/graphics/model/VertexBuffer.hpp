#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

class VertexBuffer {
public:
    float* vertex_arr = nullptr;
	unsigned int vertex_count = 0;
	unsigned int vertex_size = 0;

	unsigned int *attributes_arr = nullptr;
	unsigned int attributes_size = 0;

	unsigned int *index_arr = nullptr;
	unsigned int indices_size = 0;

	~VertexBuffer();
};

#endif
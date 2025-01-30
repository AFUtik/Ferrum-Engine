#ifndef VERTEXBUFFERDESCRIPTOR_HPP
#define VERTEXBUFFERDESCRIPTOR_HPP

class VertexBufferDescriptor {
public:
    float* vertices_list = nullptr;
	unsigned int vertex_size = 0;
	unsigned list_size = 0;

	unsigned int *attributes_list = nullptr;
	unsigned int attributes_list_size = 0;
};

#endif
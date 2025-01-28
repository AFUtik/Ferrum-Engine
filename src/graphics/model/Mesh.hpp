#ifndef MESH_HPP
#define MESH_HPP

#include <stdlib.h>
#include "../VertexBufferDescriptor.hpp"

class Mesh {
private:
	VertexBufferDescriptor m_vertexBufferData;
	unsigned int vao;
	unsigned int vbo;
public:
	Mesh(const VertexBufferDescriptor &data);
	~Mesh();

	void draw(unsigned int primitive);
};

#endif /* GRAPHICS_MESH_H_ */
#ifndef MESH_HPP
#define MESH_HPP

#include "../VertexBufferDescriptor.hpp"

class Mesh {
private:
	VertexBufferDescriptor m_vertexBufferData;
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
public:
	Mesh(const VertexBufferDescriptor &data);
	~Mesh();

	void generate();
	void setUV(float min_u, float min_v, float max_u, float max_v);
	void draw(unsigned int primitive);
};

#endif /* GRAPHICS_MESH_H_ */
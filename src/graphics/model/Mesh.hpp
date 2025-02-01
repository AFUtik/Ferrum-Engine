#ifndef MESH_HPP
#define MESH_HPP

#include <memory>
#include "VertexBuffer.hpp"

class Mesh {
private:
	std::unique_ptr<VertexBuffer> m_vertexBufferData;
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	unsigned int buffer_index = 0;
	unsigned int ind_index = 0;
	unsigned int ind_offset = 0;
public:
	Mesh(VertexBuffer *data);
	~Mesh();

	Mesh& xyz(float x, float y, float z);
	Mesh& uv(float u, float v);
	Mesh& uv2(float u);
	Mesh& index(unsigned int i1, unsigned int i2, unsigned int i3);
	void endIndex();

	void generate();
	void setUV(float min_u, float min_v, float max_u, float max_v);
	void draw(unsigned int primitive);
};

#endif /* GRAPHICS_MESH_H_ */
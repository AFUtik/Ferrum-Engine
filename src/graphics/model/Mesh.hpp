#ifndef MESH_HPP
#define MESH_HPP

#define INSTANCE_DATA_LENGTH (16+2) // MATRIX4X4 + VEC2 //
#define MAX_INSTANCES 2000

#include <memory>

#include "VertexBuffer.hpp"

class Mesh {
private:
	std::unique_ptr<VertexBuffer> m_vertexBufferData;
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	unsigned int instance_vbo;
	unsigned int instance_count = 0;
	unsigned int buffer_index = 0;
	unsigned int ind_index = 0;
	unsigned int ind_offset = 0;

	static constexpr size_t INSTANCE_MEMORY_SIZE = INSTANCE_DATA_LENGTH * sizeof(float);
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

	inline VertexBuffer* getVertexBuffer() {return m_vertexBufferData.get();}
	inline unsigned int& getInstancesAmount() {return instance_count;}

	void updateInstanceBuffer(int index, float* data);
	void updateInstanceBuffer(size_t size);
};

#endif /* GRAPHICS_MESH_H_ */
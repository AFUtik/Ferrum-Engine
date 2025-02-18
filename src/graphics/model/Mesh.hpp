#ifndef MESH_HPP
#define MESH_HPP

#define MAX_INSTANCES 2000

#include <memory>

#include "Instance.hpp"
#include "VertexBuffer.hpp"

enum InsntanceMemoryAllocation {
    LINEAR,
    EXPONENT_BASE_2,
    EXPONENT_BASE_10,
};

enum DrawType {
	STATIC_DRAW,
	DYNAMIC_DRAW,
	STREAM_DRAW
};

class Mesh {
private:
	std::unique_ptr<VertexBuffer> vertex_buffer;
	uint32_t vao;
	uint32_t vbo;
	uint32_t ebo;
	uint32_t ivbo;
	uint32_t ebo_draw_t  = STATIC_DRAW;
	uint32_t vbo_draw_t  = STATIC_DRAW;
	uint32_t ivbo_draw_t = DYNAMIC_DRAW;

	uint32_t instance_count = 1;
	uint32_t instance_buffer_size = 1;
	uint32_t instance_allocation = EXPONENT_BASE_2;
public:
	Mesh(VertexBuffer *data);
	~Mesh();

	void generate();
	void draw(unsigned int primitive);
	void setUV(float min_u, float min_v, float max_u, float max_v);

	void updateInstanceBuffer(unsigned int index, unsigned int offset, const Instance& instance);
	void updateInstanceBuffer(const size_t& size);
};

#endif /* GRAPHICS_MESH_H_ */
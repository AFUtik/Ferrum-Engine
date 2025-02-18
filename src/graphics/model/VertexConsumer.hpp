#ifndef VERTEXCONSUMER_HPP
#define VERTEXCONSUMER_HPP

struct VertexBuffer;

class VertexConsumer {
private:
    VertexBuffer* vertex_buffer;
    
    unsigned int ebo_index = 0;
	unsigned int ebo_offset = 0;
	
	unsigned int vbo_index = 0;
public:
    VertexConsumer(VertexBuffer* buffer) : vertex_buffer(buffer) {};

    VertexConsumer& xyz(float x, float y, float z);
	VertexConsumer& uv(float u, float v);
	VertexConsumer& uv2(float u);
    void replaceUV(float min_u, float min_v, float max_u, float max_v);

	VertexConsumer& index(unsigned int i1, unsigned int i2, unsigned int i3);
    void endIndex();
};

#endif
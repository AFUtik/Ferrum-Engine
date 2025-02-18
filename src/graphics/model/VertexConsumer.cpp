#include "VertexConsumer.hpp"
#include "VertexBuffer.hpp"

VertexConsumer& VertexConsumer::xyz(float x, float y, float z) {
	vertex_buffer->vertex_arr[vbo_index] = x;
	vertex_buffer->vertex_arr[vbo_index+1] = y;
	vertex_buffer->vertex_arr[vbo_index+2] = z;
	vbo_index+=3;
	return *this;
}

VertexConsumer& VertexConsumer::uv(float u, float v) {
	vertex_buffer->vertex_arr[vbo_index] = u;
	vertex_buffer->vertex_arr[vbo_index+1] = v;
	vbo_index+=2;
	return *this;
}

VertexConsumer& VertexConsumer::uv2(float u) {
	vertex_buffer->vertex_arr[vbo_index] = u;
	vbo_index++;
	return *this;
}

VertexConsumer& VertexConsumer::index(unsigned int i1, unsigned int i2, unsigned int i3) {
	vertex_buffer->index_arr[ebo_index] = ebo_offset+i1;
	vertex_buffer->index_arr[ebo_index+1] = ebo_offset+i2;
	vertex_buffer->index_arr[ebo_index+2] = ebo_offset+i3;
	ebo_index+=3;
	return *this;
}

void VertexConsumer::endIndex() {
	ebo_offset=vbo_index/VERTEX_SIZE;
}

void VertexConsumer::replaceUV(float min_u, float min_v, float max_u, float max_v) {
    for(int i = 0; i < vertex_buffer->vertices_size; i++) {
        float &u = vertex_buffer->vertex_arr[3+i*VERTEX_SIZE];
        float &v = vertex_buffer->vertex_arr[4+i*VERTEX_SIZE];
    
        if(u==0.0f) u = min_u;
        else u = max_u;
        if(v==0.0f) v = min_v;
        else v = max_v;
    }
}
#include "VertexBuffer.hpp"

VertexBuffer::~VertexBuffer() {
    delete[] vertex_arr;
    delete[] index_arr; 
}
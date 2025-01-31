#include "RenderChunk.hpp"

Mesh* RenderChunk::getMesh() {
    return mesh.get();
}

void RenderChunk::setNotDirty() {
    dirty = false;
}
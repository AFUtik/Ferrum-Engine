#include "RenderChunk.hpp"

Mesh* RenderChunk::getMesh() {
    return mesh.get();
}

void RenderChunk::setMesh(Mesh* mesh) {
    this->mesh = std::unique_ptr<Mesh>(mesh);
}

void RenderChunk::setNotDirty() {
    dirty = false;
}
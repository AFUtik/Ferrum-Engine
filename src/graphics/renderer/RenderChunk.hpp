#ifndef RENDERCHUNK_HPP
#define RENDERCHUNK_HPP

#include "../model/Mesh.hpp"
#include <memory>

class RenderChunk {
private:
    std::unique_ptr<Mesh> mesh;
    bool dirty;
public:
    RenderChunk(Mesh* mesh) : mesh(mesh) {};

    Mesh* getMesh();
    void setMesh(Mesh *mesh);
    void setNotDirty();
};

#endif
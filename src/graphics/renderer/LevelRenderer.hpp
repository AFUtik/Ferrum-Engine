#ifndef LEVELRENDERER_HPP
#define LEVELRENDERER_HPP

#include "ObjectRenderer.hpp"
#include "RenderCnunkInfo.hpp"
//#include <vector>

class GLTexture;
class Chunks;
class RenderChunkInfo;

class LevelRenderer : public ObjectRenderer {
private:
    std::unique_ptr<RenderChunkInfo> render_chunk_info;

    Chunks* chunks;
    
    Mesh* makeMesh(Chunk* chunk);
public:
    LevelRenderer(Chunks* chunks) : chunks(chunks), render_chunk_info(new RenderChunkInfo()) {};

    void render();
};

#endif
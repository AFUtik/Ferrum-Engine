#ifndef LEVELRENDERER_HPP
#define LEVELRENDERER_HPP

#include <set>
#include "ObjectRenderer.hpp"
#include "RenderCnunkInfo.hpp"
//#include <vector>

class Chunks;
class RenderChunkInfo;

class LevelRenderer {
private:
    ObjectRenderer* object_renderer;
    TextureManager* texture_m;
    Chunks* chunks;

    std::unique_ptr<RenderChunkInfo> render_chunk_info;

    Mesh* render(Chunk* chunk);
public:
    LevelRenderer(ObjectRenderer* obj_renderer, TextureManager* tex_m, Chunks* chunks) : 
    texture_m(tex_m), chunks(chunks), object_renderer(obj_renderer), render_chunk_info(new RenderChunkInfo()) {};

    void render();
};

#endif
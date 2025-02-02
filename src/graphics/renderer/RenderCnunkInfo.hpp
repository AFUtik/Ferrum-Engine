#ifndef RENDERCHUNKINFO_HPP
#define RENDERCHUNKINFO_HPP

#include "RenderChunk.hpp"
#include <map>

class Chunk;

class RenderChunkInfo {
private:
    std::map<Chunk*, std::unique_ptr<RenderChunk>> render_chunks;
public:
    RenderChunkInfo() {};

    RenderChunk* getRenderChunk(Chunk* chunk);

    void loadChunk(Chunk* chunk, RenderChunk* render_chunk);
    void unloadChunk(Chunk* chunk);
};

#endif
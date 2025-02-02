#include "../../game/level/Chunk.hpp"
#include "RenderCnunkInfo.hpp"

RenderChunk* RenderChunkInfo::getRenderChunk(Chunk* chunk) {
    return render_chunks[chunk].get();
}

void RenderChunkInfo::loadChunk(Chunk* chunk, RenderChunk* render_chunk) {
    render_chunks[chunk] = std::unique_ptr<RenderChunk>(render_chunk);
}

void RenderChunkInfo::unloadChunk(Chunk* chunk) {
    render_chunks[chunk].reset();
}
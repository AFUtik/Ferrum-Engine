#include "../../game/level/Chunk.hpp"
#include "RenderCnunkInfo.hpp"

RenderChunk* RenderChunkInfo::getRenderChunk(Chunk* chunk) {
    return render_chunks[chunk].get();
}

void RenderChunkInfo::loadChunk(Chunk* chunk, Mesh* mesh) {
    render_chunks[chunk] = std::make_unique<RenderChunk>(mesh);
}

void RenderChunkInfo::unloadChunk(Chunk* chunk) {
    render_chunks[chunk].reset();
}
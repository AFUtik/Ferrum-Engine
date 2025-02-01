#include "LevelRenderer.hpp"

#include "../texture/TextureManager.hpp"

#include "../../game/level/Tile.hpp"
#include "../../game/level/Chunk.hpp"
#include "../../game/level/Chunks.hpp"

#include "../model/VertexBuffer.hpp"
#include "../model/VertexInfo.hpp"

#include "glm/ext.hpp"
#include <iostream>

Mesh* LevelRenderer::render(Chunk* chunk) {
    VertexBuffer *vertexBuffer = new VertexBuffer();
    vertexBuffer->attributes_arr = attrs;
    vertexBuffer->attributes_size = 3;

    vertexBuffer->vertex_arr = new float[CHUNK_VOL*VERTEX_SIZE*4];
    vertexBuffer->vertex_count = CHUNK_VOL*4;
    vertexBuffer->vertex_count = VERTEX_SIZE;

    vertexBuffer->index_arr = new unsigned int[CHUNK_VOL*SQUARE_INDEX_SIZE];
    vertexBuffer->indices_size = CHUNK_VOL*SQUARE_INDEX_SIZE;

    TextureAtlas* texture_atlas = texture_m->getAtlas(3);
    Mesh* mesh = new Mesh(vertexBuffer);
    for(int y = 0; y < CHUNK_H; y++) {
        for(int x = 0; x < CHUNK_W; x++) {
            Tile& tile = chunk->tiles[(y*CHUNK_W)+x];
            if(tile.id==0) continue;

            TextureAtlasPos* uv_pos = texture_atlas->getAtlasPos(tile.id);

            mesh->xyz(x-0.5f, y-0.5f, 0.0f).uv(uv_pos->u1, uv_pos->v1);
            mesh->xyz(x-0.5f, y+0.5f, 0.0f).uv(uv_pos->u1, uv_pos->v2);
            mesh->xyz(x+0.5f, y+0.5f, 0.0f).uv(uv_pos->u2, uv_pos->v2);
            mesh->xyz(x+0.5f, y-0.5f, 0.0f).uv(uv_pos->u2, uv_pos->v1);
            mesh->index(0, 1, 3).index(1, 2, 3).endIndex();
        }
    }
    mesh->generate();
    return mesh;
}

void LevelRenderer::render() {
    texture_m->getGLTexture(3)->bind();
    for(size_t i = 0; i < chunks->volume; i++) {
        Chunk* chunk = chunks->chunks[i];

        RenderChunk* render_chunk = render_chunk_info->getRenderChunk(chunk);
        Mesh* mesh = nullptr;

        if(chunk->isDirty || render_chunk==nullptr) {
            mesh = render(chunk);
            render_chunk_info->loadChunk(chunk, mesh);
        } else {
            mesh = render_chunk->getMesh();
        }
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(chunk->x, chunk->y, 0.0f));
        object_renderer->render(mesh, transform);
    }
}
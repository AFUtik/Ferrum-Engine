#include "LevelRenderer.hpp"

#include "../texture/TextureManager.hpp"

#include "../../game/level/Tile.hpp"
#include "../../game/level/Chunk.hpp"
#include "../../game/level/Chunks.hpp"

#include "../model/VertexBufferDescriptor.hpp"

#include "glm/ext.hpp"
#include <iostream>

unsigned int attrs[] = {3, 2, 0};

Mesh* LevelRenderer::render(Chunk* chunk) {
    VertexBufferDescriptor vertexBuffer;
    vertexBuffer.attributes_list = attrs;
    vertexBuffer.vertex_size = 5;
    vertexBuffer.list_size = CHUNK_VOL*6;
    vertexBuffer.vertices_list = new float[CHUNK_VOL*5*6];

    TextureAtlas* texture_atlas = texture_m->getAtlas(3);
    Mesh* mesh = new Mesh(vertexBuffer);
    for(int y = 0; y < CHUNK_H; y++) {
        for(int x = 0; x < CHUNK_W; x++) {
            Tile& tile = chunk->tiles[(y*CHUNK_W)+x];
            TextureAtlasPos* uv_pos = texture_atlas->getAtlasPos(tile.id);

            mesh->xyz(x-0.5f, y-0.5f, 0.0f).uv(uv_pos->u1, uv_pos->v1);
            mesh->xyz(x+0.5f, y+0.5f, 0.0f).uv(uv_pos->u2, uv_pos->v2);
            mesh->xyz(x-0.5f, y+0.5, 0.0f).uv(uv_pos->u1, uv_pos->v2);
            mesh->xyz(x-0.5f, y-0.5f, 0.0f).uv(uv_pos->u1, uv_pos->v1);
            mesh->xyz(x+0.5f, y-0.5f, 0.0f).uv(uv_pos->u2, uv_pos->v1);
            mesh->xyz(x+0.5f, y+0.5f, 0.0f).uv(uv_pos->u2, uv_pos->v2);
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
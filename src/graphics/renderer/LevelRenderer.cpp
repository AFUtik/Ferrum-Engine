#include "LevelRenderer.hpp"

#include "../texture/Textures.hpp"
#include "../texture/TextureManager.hpp"
#include "../model/ModelManager.hpp"

#include "../../game/level/Tile.hpp"
#include "../../game/level/Chunk.hpp"
#include "../../game/level/Chunks.hpp"

#include "glm/ext.hpp"
#include <iostream>

Mesh* LevelRenderer::makeMesh(Chunk* chunk) {
    VertexBuffer *vertexBuffer = new VertexBuffer();
    vertexBuffer->attributes_arr = attrs;
    vertexBuffer->attributes_size = 3;

    vertexBuffer->vertex_arr = new float[CHUNK_VOL*VERTEX_SIZE*4];
    vertexBuffer->vertex_count = CHUNK_VOL*4;
    vertexBuffer->vertex_size = VERTEX_SIZE;

    vertexBuffer->index_arr = new unsigned int[CHUNK_VOL*SQUARE_INDEX_SIZE];
    vertexBuffer->indices_size = CHUNK_VOL*SQUARE_INDEX_SIZE;

    std::cout << "test chunk renderer mesh 1" << std::endl; 
    InstanceBuffer *instanceBuffer = new InstanceBuffer();
    std::cout << "test chunk renderer mesh 2" << std::endl; 
    instanceBuffer->mats.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(chunk->x, chunk->y, 0.0f)));
    std::cout << "test chunk renderer mesh 3" << std::endl; 

    Mesh* mesh = new Mesh(vertexBuffer, instanceBuffer);
    for(int y = 0; y < CHUNK_H; y++) {
        for(int x = 0; x < CHUNK_W; x++) {
            Tile& tile = chunk->tiles[(y*CHUNK_W)+x];
            if(tile.id==0) continue;

            TextureAtlasPos* uv_pos = model_m->getUnbakedModel(tile.id)->getUVPos();

            mesh->xyz(x-0.5f, y-0.5f, 0.0f).uv(uv_pos->u1, uv_pos->v1);
            mesh->xyz(x-0.5f, y+0.5f, 0.0f).uv(uv_pos->u1, uv_pos->v2);
            mesh->xyz(x+0.5f, y+0.5f, 0.0f).uv(uv_pos->u2, uv_pos->v2);
            mesh->xyz(x+0.5f, y-0.5f, 0.0f).uv(uv_pos->u2, uv_pos->v1);
            mesh->index(0, 1, 3).index(1, 2, 3).endIndex();
        }
    }
    std::cout << "test chunk renderer mesh 4" << std::endl; 
    mesh->generate();
    std::cout << "test chunk renderer mesh 5" << std::endl; 
    return mesh;
}

void LevelRenderer::render() {
    texture_m->getGLTexture(ALL_TEXTURES_ATLAS)->bind();
    for(size_t i = 0; i < chunks->volume; i++) {
        Chunk* chunk = chunks->chunks[i];

        RenderChunk* render_chunk = render_chunk_info->getRenderChunk(chunk);
        Mesh* mesh = nullptr;

        if(chunk->isDirty || render_chunk==nullptr) {
            std::cout << "test chunk renderer 1" << std::endl; 
            mesh = makeMesh(chunk);
            std::cout << "test chunk renderer 2" << std::endl; 

            RenderChunk* render_chunk = new RenderChunk(mesh);
            std::cout << "test chunk renderer 3" << std::endl; 

            render_chunk_info->loadChunk(chunk, render_chunk);
            std::cout << "test chunk renderer 4" << std::endl; 
        } else {
            mesh = render_chunk->getMesh();
        }
        object_renderer->render(mesh);
    }
}
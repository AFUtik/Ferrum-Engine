#include "Chunks.hpp"
#include "EntityManager.hpp"

#include "../graphics/ChunkRenderer.hpp"
#include "../graphics/EntityRenderer.hpp"
#include "../graphics/DrawContext.hpp"

#include "GameContext.hpp"

void GameContext::render(DrawContext* draw_context) {
    EntityRenderer* ent_renderer = draw_context->entity_renderer;
    

    ChunkRenderer* chunk_renderer = draw_context->chunk_renderer;

}

GameContext::~GameContext() {
    delete chunks;
    delete entity_manager;
}
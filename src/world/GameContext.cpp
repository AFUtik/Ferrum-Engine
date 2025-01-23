#include "Chunks.hpp"
#include "EntityManager.hpp"

#include "../graphics/ChunkRenderer.hpp"
#include "../graphics/EntityRenderer.hpp"
#include "../graphics/DrawContext.hpp"
#include "../graphics/Shader.hpp"

#include "GameContext.hpp"


void GameContext::render(DrawContext* draw_context) {
    EntityRenderer* ent_renderer = draw_context->entity_renderer;
    ent_renderer->render(entity_manager->registered_entities);

    ChunkRenderer* chunk_renderer = draw_context->chunk_renderer;
    chunk_renderer->render(entity_manager->registered_tiles);

}

void GameContext::draw(DrawContext* draw_context) {
    draw_context->shader->use

    draw_context->entity_renderer->draw(draw_context, entity_manager->entities);
    draw_context->chunk_renderer->draw(draw_context, entity_manager->chunks)
}

GameContext::~GameContext() {
    delete chunks;
    delete entity_manager;
}
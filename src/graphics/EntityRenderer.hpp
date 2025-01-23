#ifndef ENTITY_RENDERER_HPP
#define ENTITY_RENDERER_HPP

#include "Renderer.hpp"
#include <vector>

class Entity;
class DrawContext;

class EntityRenderer : public Renderer {
public:
    int max_render_entities = 256;
    void render(std::vector<Entity*> entities);

    void draw(DrawContext* draw_context, std::vector<Entity*> &entities);
};

#endif
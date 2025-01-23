#ifndef GAMECONTEXT_HPP
#define GAMECONTEXT_HPP

class DrawContext;
class EntityManager;
class Chunks;

class GameContext {
public:
    EntityManager* entity_manager;
    Chunks* chunks;

    void render(DrawContext* draw_context);

    GameContext();
    ~GameContext();
};

#endif
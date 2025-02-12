#pragma once

#include "graphics/ResourceManager.hpp"
#include "graphics/DrawContext.hpp"
#include "game/GameContext.hpp"

class FerrumEngine {
private:
    ResourceManager resource_manager;
    GameContext game_context;
    DrawContext draw_context;
public:
    FerrumEngine() : resource_manager(), game_context(&resource_manager), draw_context(&resource_manager) {}

    inline ResourceManager& getResourceManager() {
        return resource_manager;
    }
    inline GameContext& getGameContext() {
        return game_context;
    }
    inline DrawContext& getDrawContext() {
        return draw_context;
    }
};
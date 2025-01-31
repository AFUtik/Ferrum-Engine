#ifndef DRAWCONTEXT_HPP
#define DRAWCONTEXT_HPP

#include <string>
#include <vector>
#include <memory>

#include "../game/GameContext.hpp"

#include "Camera.hpp"
#include "Shader.hpp"

#include "ResourceManager.hpp"

#include "renderer/ObjectRenderer.hpp"
#include "renderer/EntityRenderer.hpp"
#include "renderer/LevelRenderer.hpp"
//class ChunkRenderer;


class DrawContext {
private:
    std::shared_ptr<ResourceManager> resource_m;

    std::unique_ptr<ObjectRenderer> object_renderer;
    std::unique_ptr<EntityRenderer> entity_renderer;
    std::unique_ptr<LevelRenderer> level_renderer;
    
    std::unique_ptr<Camera> camera;
    std::unique_ptr<Shader> shader;
public:
    DrawContext(ResourceManager* resource_m, GameContext* game_context);
    // virtual ~DrawContext();

    Camera* getCamera();

    void render();
};

#endif
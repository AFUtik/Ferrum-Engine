#ifndef DRAWCONTEXT_HPP
#define DRAWCONTEXT_HPP

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
    std::unique_ptr<Camera> camera;
    std::unique_ptr<Shader> shader;

    std::unique_ptr<ObjectRenderer> object_renderer;

    std::map<std::string, std::unique_ptr<ObjectRenderer>> renderers;
public:
    DrawContext(ResourceManager* resource_m, GameContext* game_context);

    Camera* getCamera();

    template<typename T>
    void registerRenderer(std::string location, T* renderer) {
        static_assert(std::is_base_of<ObjectRenderer, T>::value, "T must derive from ObjectRenderer class");
        if (!object_renderer) throw std::runtime_error("Error: кenderer is nullptr!");
        
        renderer->model_manager = object_renderer->model_manager;
        renderer->texture_manager = object_renderer->texture_manager;
        renderers.emplace(location, std::unique_ptr<T>(renderer));
    }

    void render();
};

#endif
#include "DrawContext.hpp"

#include "Shader.hpp"
#include "Camera.hpp"

#include <iostream>

#include <GLFW/glfw3.h>	

DrawContext::DrawContext(ResourceManager* resource_m, GameContext* game_context) : resource_m(resource_m), 
    camera(new Camera(glm::vec3(0.0f), 0.0f)) 
{
    shader = std::unique_ptr<Shader>(load_shader("resources/shaders/core.vert", "resources/shaders/core.frag"));
	if (shader == nullptr) {
		std::cerr << "failed to load shader" << std::endl;
	}

    TextureManager* tex_m = resource_m->getTextureManager();
    ModelManager* model_m = resource_m->getModelManager();

    object_renderer = std::make_unique<ObjectRenderer>(tex_m, model_m);

    //entity_renderer = std::make_unique<EntityRenderer>(obj_renderer, tex_m, model_m, game_context->getEntitySystem());
    //level_renderer = std::make_unique<LevelRenderer>(obj_renderer, tex_m, model_m, game_context->getChunks());
}

void DrawContext::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->use();
    shader->uniformMatrix("projview", camera->getOrthoProjview());

    for(auto&& [loc, renderer] : renderers) {
        renderer->render();
    }
}

Camera* DrawContext::getCamera() {
    return camera.get();
}


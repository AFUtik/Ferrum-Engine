#include "ResourceManager.hpp"
#include "renderer/EntityRenderer.hpp"
//#include "renderer/ChunkRenderer.hpp"
#include "../game/GameContext.hpp"
#include "DrawContext.hpp"


#include "Shader.hpp"
#include "Camera.hpp"

#include "../entity/EntitySystem.hpp"


#include <iostream>

#include <GLFW/glfw3.h>	

DrawContext::DrawContext(ResourceManager* resource_m, GameContext* game_context) : resource_m(resource_m), 
    camera(new Camera(glm::vec3(0.0f), 0.0f)) 
{
    shader = std::unique_ptr<Shader>(load_shader("resources/shaders/core.vert", "resources/shaders/core.frag"));
	if (shader == nullptr) {
		std::cerr << "failed to load shader" << std::endl;
	}

    ModelManager* model_m = resource_m->getModelManager();
    TextureManager* tex_m = resource_m->getTextureManager();
    ObjectRenderer* obj_renderer = new ObjectRenderer(shader.get());

    object_renderer = std::unique_ptr<ObjectRenderer>(obj_renderer);
    entity_renderer = std::make_unique<EntityRenderer>(obj_renderer, tex_m, model_m, game_context->getEntitySystem());
    level_renderer = std::make_unique<LevelRenderer>(obj_renderer, tex_m, game_context->getChunks());
}

void DrawContext::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->use();
    shader->uniformMatrix("projview", camera->getOrthoProjview());

    entity_renderer->render();
    level_renderer->render();

    //chunk_renderer->render(game_context);
}

Camera* DrawContext::getCamera() {
    return camera.get();
}


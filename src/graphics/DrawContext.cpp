#include "ResourceManager.hpp"
#include "renderer/EntityRenderer.hpp"
//#include "renderer/ChunkRenderer.hpp"
#include "DrawContext.hpp"


#include "Shader.hpp"
#include "Camera.hpp"

#include "../entity/EntitySystem.hpp"

#include "../game/GameContext.hpp"
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
    entity_renderer = std::make_unique<EntityRenderer>(model_m, game_context->getEntitySystem());

}

void DrawContext::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->use();
    shader->uniformMatrix("projview", camera->getOrthoProjview());

    entity_renderer->render(shader.get());

    //chunk_renderer->render(game_context);
}

Camera* DrawContext::getCamera() {
    return camera.get();
}


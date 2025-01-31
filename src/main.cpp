#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>	

#include "window/Window.hpp"
#include "window/Events.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "window/Context.hpp"

#include "physics/RigidBody.hpp"
#include "game/GameContext.hpp"
#include "entity/Entity.hpp"
#include "entity/PlayerEntity.hpp"
#include "entity/EntitySystem.hpp"
#include "graphics/DrawContext.hpp"
#include "graphics/Camera.hpp"
#include "graphics/ResourceManager.hpp"
#include "graphics/texture/TextureManager.hpp"
#include "graphics/model/BakedModel.hpp"
#include "graphics/model/ModelManager.hpp"
#include "graphics/model/EntityModel.hpp"

#include "graphics/texture/Texture.hpp"
#include "graphics/texture/TextureHandler.hpp"
#include "graphics/texture/TextureAtlas.hpp"
#include "graphics/texture/TextureAtlasGenerator.hpp"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

#pragma once

enum Textures {
	MISSING_TEXTURE,
	DIRT_TEXTURE,
	GRASS_TEXTURE,
	BASIC_ATLAS_TEXTURE
};

enum Models {
	PLAYER_ENTITY
};

int WIDTH = 1920;
int HEIGHT = 1080;

int main(int, char**){
    Window::init(WIDTH, HEIGHT, "Test Window", true);
	Events::init();

	ResourceManager* resource_m = new ResourceManager("E:/Cpp/FerrumEngine/resources/");

	std::cout << "test 1" << std::endl;

	TextureManager* texture_m = resource_m->getTextureManager();
	texture_m->changeTextureLocation("textures/tiles/");
	texture_m->loadTexture(MISSING_TEXTURE, "block1.png");
	texture_m->loadTexture(DIRT_TEXTURE, "block3.png");
	texture_m->loadTexture(GRASS_TEXTURE, "block2.png");
	texture_m->loadAtlas(BASIC_ATLAS_TEXTURE, {MISSING_TEXTURE, DIRT_TEXTURE, GRASS_TEXTURE});
	
	std::cout << "test 2" << std::endl;

	ModelManager* model_m = resource_m->getModelManager();
	model_m->bakeModel(EntityModel(), PLAYER_ENTITY, GRASS_TEXTURE, BASIC_ATLAS_TEXTURE);

	std::cout << "test 3" << std::endl;

	GameContext game_context(resource_m);
	DrawContext draw_context(resource_m, &game_context);

	std::cout << "test 4" << std::endl;

	Chunks* chunks = game_context.getChunks();
	chunks->set(3, 3);

	std::cout << "test 5" << std::endl;

	glClearColor(0.6f, 0.62f, 0.65f, 1);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(Window::window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

    //Camera* camera = new Camera(glm::vec3(0, 0, 1), glm::radians(90.0f));
	Camera* camera = draw_context.getCamera();
	camera->set_xyz(0.0f, 0.0f, 1.0f);

	camera->aspect = (float)320.0 / (float)180.0;
	camera->zNear = -1.0f;
	camera->zFar = 100.0f;
	camera->scale = 1.0f;
	camera->smooth_factor = 1.0f;

    Context* context = new Context();
	
	EntitySystem* ent_system = game_context.getEntitySystem();

	PlayerEntity* player = new PlayerEntity();
	RigidBody* body = player->getPhysicBody();

	ent_system->createEntity(player);

	std::cout << "test 6" << std::endl;

	while (!Window::isShouldClose()) {
        double currentTime = glfwGetTime();
        context->delta_time = currentTime - context->last_ticks;
        context->last_ticks = currentTime;

        float H = 0.016f;
        context->time_accu += context->delta_time;
		if(context->time_accu >= context->delta_time) {
			if(Events::is_scrolled_up() && camera->scale > 1) {
				camera->scale -= 1;
			} 
			if(Events::is_scrolled_down()) {
				camera->scale += 1;
			} 
			if (Events::jpressed(GLFW_KEY_ESCAPE)) {
				Window::setShouldClose(true);
			}
			if (Events::jpressed(GLFW_KEY_TAB)) {
				Events::toggle_cursor();
			}
			if (Events::pressed(GLFW_KEY_W)) {
				body->apply_direction(vec2(0.0f, 1.0f));
			}
			if (Events::pressed(GLFW_KEY_S)) {
				body->apply_direction(vec2(0.0f, -1.0f));
			}
			if (Events::pressed(GLFW_KEY_D)) {
				body->apply_direction(vec2(1.0f, 0.0f));
			}
			if (Events::pressed(GLFW_KEY_A)) {
				body->apply_direction(vec2(-1.0f, 0.0f));
			}
			if (Events::pressed(GLFW_KEY_0)) {
				camera->set_xyz(0, 0, 1);
			}
			if (Events::_cursor_locked) {
				camera->cur_y += -Events::deltaY / Window::height * 2;
				camera->cur_x += -Events::deltaX / Window::height * 2;

				if (camera->cur_y < -radians(89.0f)) {
					camera->cur_y = -radians(89.0f);
				}
				if (camera->cur_y > radians(89.0f)) {
					camera->cur_y = radians(89.0f);
				}

				camera->rotation = mat4(1.0f);
				camera->rotate(camera->cur_y, camera->cur_x, 0);
			}

			// IMGUI WINDOW // 
        	ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			ent_system->update(context->delta_time);
			draw_context.render();
			
        	ImGui::ShowDemoWindow();
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        	Window::swapBuffers();
			Events::pullEvents();
			context->time_accu -= context->delta_time;
		}
    }
	//Texture* texture = TextureAtlasGenerator::generateTextureAtlas(texture_m, 512, 512, 
	//{MISSING_TEXTURE, DIRT_TEXTURE, GRASS_TEXTURE}
	//)->getTexture();
	//save_texture_png("E:/Cpp/FerrumEngine/resources/textures/atlases/atlas.png", texture);
	Window::terminate();
    return 0;
}

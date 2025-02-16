#include <iostream>

#include "FerrumEngine.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>	

#include "graphics/window/Window.hpp"
#include "graphics/window/Events.hpp"
#include "graphics/window/Context.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/game-editor/ImguiGameEditor.hpp"

#include "physics/RigidBody.hpp"
#include "game/level/Tiles.hpp"
#include "game/entity/Entities.hpp"
#include "game/entity/Entity.hpp"
#include "game/entity/PlayerEntity.hpp"
#include "game/entity/EntitySystem.hpp"
#include "graphics/Camera.hpp"

#include "graphics/texture/TextureManager.hpp"

#include "graphics/model/BakedModel.hpp"
#include "graphics/model/ModelManager.hpp"
#include "graphics/model/Quad.hpp"
#include "graphics/renderer/EntityRenderer.hpp"

#include "utils/tilemap/TileMapper.hpp"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

#pragma once

int WIDTH = 1920;
int HEIGHT = 1080;

int main(int, char**){
    Window::init(WIDTH, HEIGHT, "Test Window", true);
	Events::init();

	GLint maxTextureSize;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
	TileMapper::usePadding(1);
	TileMapper::setMaxSize(maxTextureSize);
	TileMapper::setMinSize(64);

	std::cout << "test 1" << std::endl;
	// Ferrum Engine Initialization //
	ResourceManager::setLocation("E:/Cpp/FerrumEngine/resources/");
	FerrumEngine ferrum_engine;
	// Register Entity Renderer //
	ResourceManager& resource_m = ferrum_engine.getResourceManager();
	GameContext& game_context = ferrum_engine.getGameContext();
	DrawContext& draw_context = ferrum_engine.getDrawContext();

	EntitySystem* ent_system = game_context.getEntitySystem();
	draw_context.registerRenderer("entity_renderer", new EntityRenderer(ent_system));

	// Textures // 
	TextureManager* texture_m = resource_m.getTextureManager();
	texture_m->changeTextureLocation("textures/anim/");
	texture_m->loadBunchToGroup("animations.test", "animation_texture", {
		"Sprite-0002.png", "Sprite-0003.png", "Sprite-0004.png", "Sprite-0005.png", "Sprite-0006.png",
		"Sprite-0007.png", "Sprite-0008.png", "Sprite-0009.png", "Sprite-0010.png", "Sprite-0011.png"
	});
	texture_m->loadTilemapByGroup("animation_tilemap", "animations.test");

	texture_m->changeTextureLocation("textures/atlases/");
	texture_m->loadTextureToGroup("atlases.test", "voxels", "voxels.png");
	Atlas voxel_atlas("voxels", 32, 32, 4);
	texture_m->loadTilemap("voxels_tilemap", {voxel_atlas});


	// CREATING SPRITE ANIMATOR //
	//Tilemap* anim_tilemap = texture_m->getTilemap("animation_tilemap");
	//
	//SpriteAnimator* sprite_animator = new SpriteAnimator(anim_tilemap);
	//AnimSequence* anim_sequence = new AnimSequence("simle_sequence", 10, {
	//	0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f
	//});
	//sprite_animator->loadAnimSequence(anim_sequence, "animation_texture0");

	// MODEL CREATING AND ANIMATOR LOADING //
	ModelManager* model_m = resource_m.getModelManager();
	model_m->bakeModel(Quad(), "player", "voxels0", "voxels_tilemap");
	//model_m->loadAnimator("player", sprite_animator);

	std::cout << "test 5" << std::endl;

	glClearColor(0.6f, 0.62f, 0.65f, 1);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.IniFilename = nullptr; /* Disables adding imgui.ini files to a project */ 
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(Window::window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	ImguiGameEditor imgui_editor(&ferrum_engine);

	Camera* camera = draw_context.getCamera();
	camera->set_xyz(0.0f, 0.0f, 1.0f);

	camera->aspect = (float)320.0 / (float)180.0;
	camera->zNear = -1.0f;
	camera->zFar = 100.0f;
	camera->scale = 1.0f;
	camera->smooth_factor = 1.0f;

    Context* context = new Context();

	PlayerEntity* player = new PlayerEntity();
	RigidBody& body = player->getPhysicBody();
	body.position = glm::vec3(0.0f, 0.0f, 2.0f);
	body.pixel_perfect = true;
	camera->follow(body.pixel_position);
	ent_system->createEntity(player);

	//PlayerEntity* player2 = new PlayerEntity();
	//for(int i = 0; i < 1024; i++) {
	//	PlayerEntity *new_player = new PlayerEntity();
	//	RigidBody& body2 = new_player->getPhysicBody();
	//	//body2->pixel_perfect = true;
	//	body2.apply_direction(glm::linearRand(glm::vec2(-5.2f), glm::vec2(5.2f)));
	//	ent_system->createEntity(new_player);
	//}

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
				body.apply_direction(vec2(0.0f, 1.0f));
			}
			if (Events::pressed(GLFW_KEY_S)) {
				body.apply_direction(vec2(0.0f, -1.0f));
			}
			if (Events::pressed(GLFW_KEY_D)) {
				body.apply_direction(vec2(1.0f, 0.0f));
			}
			if (Events::pressed(GLFW_KEY_A)) {
				body.apply_direction(vec2(-1.0f, 0.0f));
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
			
			ent_system->update(H);
			draw_context.render(); 

			// IMGUI WINDOW // 
        	ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

        	imgui_editor.update();

        	//ImGui::ShowDemoWindow();
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//
        	Window::swapBuffers();
			Events::pullEvents();
			context->time_accu -= context->delta_time;
		}
    }
	Window::terminate();
    return 0;
}

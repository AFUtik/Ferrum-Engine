#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>	

#include "window/Window.hpp"
#include "window/Events.hpp"

#include "graphics/Renderer.hpp"
#include "graphics/Camera.hpp"
#include "graphics/Mesh.hpp"
#include "graphics/Texture.hpp"
#include "graphics/Shader.hpp"
#include "graphics/Texture_loader.hpp"

#include "physics/RigidBody.hpp"
#include "world/Player.hpp"
#include "world/Tile.hpp"
#include "world/Chunks.hpp"
#include "world/Chunk2d.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "window/Context.hpp"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

int WIDTH = 1920;
int HEIGHT = 1080;

int main(int, char**){
    Window::init(WIDTH, HEIGHT, "Test Window");
	Events::init();

    Shader* shader = load_shader("resources/shaders/core.vert", "resources/shaders/core.frag");
	if (shader == nullptr) {
		std::cerr << "failed to load shader" << std::endl;
		Window::terminate();
		return 1;
	}

	Texture* texture = load_texture("E:/Cpp/FerrumEngine/resources/block.png");
	if (texture == nullptr) {
		std::cerr << "failed to load texture" << std::endl;
		delete texture;
		Window::terminate();
		return 1;
	}

	Renderer renderer(1024 * 1024 * 4);
	Chunks* chunks = new Chunks(5, 5);
	
	for (size_t i = 0; i < chunks->volume; ++i) {
		renderer.render_chunk2d(chunks->chunks[i], (const Chunk2d**) chunks->chunks);
	}

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

    Camera* camera = new Camera(glm::vec3(0, 0, 1), glm::radians(90.0f));
	camera->aspect = (float)Window::width / (float)Window::height;
	camera->zNear = 0.1f;
	camera->zFar = 100.0f;
	camera->scale = 4.0f;

	Player* player = new Player();
	player->render();

	RigidBody* body = new RigidBody(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), 25.0f);
	player->rigid_body = body;

	camera->follow(body->position);

    Context* context = new Context();

	float speed = 10;
	while (!Window::isShouldClose()) {
        double currentTime = glfwGetTime();
        context->delta_time = currentTime - context->last_ticks;
        context->last_ticks = currentTime;

        float H = 0.016f;
        context->time_accu += context->delta_time;
		if (Events::jpressed(GLFW_KEY_ESCAPE)) {
			Window::setShouldClose(true);
		}
		if (Events::jpressed(GLFW_KEY_TAB)) {
			Events::toggle_cursor();
		}
		if(context->time_accu >= H) {
			if (Events::pressed(GLFW_KEY_W)) {
				body->apply_force(vec2(0.0f, 10.0f));
			}
			if (Events::pressed(GLFW_KEY_S)) {
				body->apply_force(vec2(0.0f, -10.0f));
			}
			if (Events::pressed(GLFW_KEY_D)) {
				body->apply_force(vec2(10.0f, 0.0f));
			}
			if (Events::pressed(GLFW_KEY_A)) {
				body->apply_force(vec2(-10.0f, 0.0f));
			}
			if (Events::pressed(GLFW_KEY_0)) {
				camera->set_xyz(0, 0, 1);
			}
			context->time_accu -= H;
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

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// IMGUI WINDOW // 
        //ImGui_ImplOpenGL3_NewFrame();
		//ImGui_ImplGlfw_NewFrame();
		//ImGui::NewFrame();

		shader->use();
		shader->uniformMatrix("projview", camera->getOrthoProjview());
		texture->bind();

		glm::mat4 model(1.0f);
		for (size_t i = 0; i < chunks->volume; i++) {
			Chunk2d* chunk = chunks->chunks[i];
			model = glm::translate(glm::mat4(1.0f), glm::vec3(chunk->x * CHUNK_W + 0.5f, chunk->y * CHUNK_H + 0.5f, 0.0f));
			shader->uniformMatrix("model", model);
			chunk->mesh->draw(GL_TRIANGLES);
		}
		
		body->update(H);
		shader->uniformMatrix("model", body->model_mat);
		player->mesh->draw(GL_TRIANGLES);
        
        //ImGui::ShowDemoWindow();
		//ImGui::Render();
		//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        Window::swapBuffers();
		Events::pullEvents();
    }

	delete texture;
	delete shader;

    delete camera;
    delete context;

	delete player;
	delete chunks;

    Window::terminate();
    return 0;
}

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>	

#include "window/Window.hpp"
#include "window/Events.hpp"

#include "graphics/Mesh.hpp"
#include "graphics/Texture.hpp"
#include "graphics/Shader.hpp"

int WIDTH = 1920;
int HEIGHT = 1080;

int main(int, char**){
    Window::init(WIDTH, HEIGHT, "Test Window");
	Events::init();

    //Shader* shader = load_shader("res/shaders/core.vert", "res/shaders/core.frag");
	//if (shader == nullptr) {
	//	std::cerr << "failed to load shader" << std::endl;
	//	Window::terminate();
	//	return 1;
	//}

	//Texture* texture = load_texture("E:/Cpp/VoxelEngine/res/images/block.png");
	//if (texture == nullptr) {
	//	std::cerr << "failed to load texture" << std::endl;
	//	delete texture;
	//	Window::terminate();
	//	return 1;
	//}

    glClearColor(0.6f, 0.62f, 0.65f, 1);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while (!Window::isShouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Window::swapBuffers();
		Events::pullEvents();
    }

    Window::terminate();
    return 0;
}

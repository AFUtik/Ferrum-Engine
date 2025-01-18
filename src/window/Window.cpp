#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.hpp"
#include "../graphics/Texture.hpp"
#include "../graphics/Texture_loader.hpp"

GLFWwindow* Window::window;
Texture* Window::iconTexture;
int Window::width = 0;
int Window::height = 0;

int Window::init(int width, int height, const char* title) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	iconTexture = load_texture("E:/Cpp/FerrumEngine/resources/icon.png");
	iconTexture->flipImageVertically();

	window = glfwCreateWindow(width, height, "simple window", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	GLFWimage icon;
	icon.width = iconTexture->width;
	icon.height = iconTexture->height;
	icon.pixels = iconTexture->image_data;  // Используйте загруженные пиксели

	glfwSetWindowIcon(window, 1, &icon);

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	glViewport(0, 0, width, height);
	Window::width = width;
	Window::height = height;
	return 0;
}

void Window::setCursorMode(int mode) {
	glfwSetInputMode(window, GLFW_CURSOR, mode);
}

void Window::terminate() {
	glfwTerminate();
	delete iconTexture;
}

bool Window::isShouldClose() {
	return glfwWindowShouldClose(window);
}

void Window::setShouldClose(bool flag) {
	glfwSetWindowShouldClose(window, flag);
}

void Window::swapBuffers() {
	glfwSwapBuffers(window);
}

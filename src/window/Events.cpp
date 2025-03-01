#include "Events.hpp"

#include <GLFW/glfw3.h>
#include <string.h>

bool* Events::_keys;
uint* Events::_frames;
uint Events::_current = 0;
float Events::deltaX = 0.0f;
float Events::deltaY = 0.0f;
float Events::x = 0.0f;
float Events::y = 0.0f;
double Events::x_scroll = 0.0f;
double Events::y_scroll = 0.0f;
bool Events::_cursor_locked = false;
bool Events::_cursor_started = false;

#define _MOUSE_BUTTONS 1024


// Origin -> https://github.com/MihailRis/VoxelEngine-Cpp/blob/main/src/window/Events.cpp

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
	if (Events::_cursor_started){
		Events::deltaX += xpos-Events::x;
		Events::deltaY += ypos-Events::y;
	}
	else {
		Events::_cursor_started = true;
	}
	Events::x = xpos;
	Events::y = ypos;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mode){
	if (action == GLFW_PRESS){
		Events::_keys[_MOUSE_BUTTONS+button] = true;
		Events::_frames[_MOUSE_BUTTONS+button] = Events::_current;
	}
	else if (action == GLFW_RELEASE){
		Events::_keys[_MOUSE_BUTTONS+button] = false;
		Events::_frames[_MOUSE_BUTTONS+button] = Events::_current;
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	Events::x_scroll = xoffset;
	Events::y_scroll = yoffset;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS){
		Events::_keys[key] = true;
		Events::_frames[key] = Events::_current;
	}
	else if (action == GLFW_RELEASE){
		Events::_keys[key] = false;
		Events::_frames[key] = Events::_current;
	}
}

int Events::init(){
	GLFWwindow* window = Window::window;
	_keys = new bool[1032];
	_frames = new uint[1032];

	memset(_keys, false, 1032*sizeof(bool));
	memset(_frames, 0, 1032*sizeof(uint));

	// Initializes each callback function //
	glfwSetKeyCallback(window, key_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback); 
	return 0;
}

bool Events::is_scrolled_up() {
	return Events::y_scroll > 0;
}

bool Events::is_scrolled_down() {
	return Events::y_scroll < 0;
}

bool Events::pressed(int keycode){
	if (keycode < 0 || keycode >= _MOUSE_BUTTONS)
		return false;
	return _keys[keycode];
}

bool Events::jpressed(int keycode){
	if (keycode < 0 || keycode >= _MOUSE_BUTTONS)
		return false;
	return _keys[keycode] && _frames[keycode] == _current;
}

bool Events::clicked(int button){
	int index = _MOUSE_BUTTONS+button;
	return _keys[index];
}

bool Events::jclicked(int button){
	int index = _MOUSE_BUTTONS+button;
	return _keys[index] && _frames[index] == _current;
}

void Events::toggle_cursor() {
	_cursor_locked = !_cursor_locked;
	Window::setCursorMode(_cursor_locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

void Events::pullEvents(){
	_current++;
	x_scroll = 0.0f;
	y_scroll = 0.0f;
	deltaX = 0.0f;
	deltaY = 0.0f;
	glfwPollEvents();
}

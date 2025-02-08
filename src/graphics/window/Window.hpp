#ifndef WINDOW_HPP_
#define WINDOW_HPP_

struct GLFWwindow;
class Texture;

class Window {
public:
	static int width;
	static int height;
	static GLFWwindow* window;
	static Texture* iconTexture;
	static int init(int width, int height, const char* title, bool vsync);
	static void terminate();

	static bool isShouldClose();
	static void setShouldClose(bool flag);
	static void swapBuffers();
	static void setCursorMode(int mode);
};

#endif

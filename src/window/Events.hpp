#ifndef EVENTS_HPP
#define EVENTS_HPP

#include "Window.hpp"

typedef unsigned int uint;

class Events {
public:
	static bool* _keys;
	static uint* _frames;
	static uint _current;
	static float deltaX;
	static float deltaY;
	static float x;
	static float y;
	static double x_scroll;
	static double y_scroll;
	static bool _cursor_locked;
	static bool _cursor_started;

	static int init();
	static void pullEvents();

	static bool is_scrolled_up();
	static bool is_scrolled_down();

	static bool pressed(int keycode);
	static bool jpressed(int keycode);

	static bool clicked(int button);
	static bool jclicked(int button);

	static void toggle_cursor();
};

#endif /* WINDOW_EVENTS_H_ */

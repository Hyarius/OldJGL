#include "jgl.h"

namespace jgl
{
	Window::Window(Widget* p_parent, Color p_back) : Widget(p_parent)
	{
		back = p_back;

		set_geometry(-1, -1);
	}

	void Window::set_color(Color p_color)
	{
		back = p_color;
	}

	void Window::render()
	{
		fill_rectangle(0, _viewport->area(), back, _viewport);
	}

	bool Window::handle_keyboard()
	{
		return(false);
	}

	bool Window::handle_mouse()
	{
		return(false);
	}
}
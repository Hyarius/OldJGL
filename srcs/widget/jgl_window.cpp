#include "jgl.h"

c_window::c_window(c_widget *p_parent, Color p_back) : c_widget(p_parent)
{
	back = p_back;

	set_geometry(-1, -1);
}

void c_window::set_color(Color p_color)
{
	back = p_color;
}

void c_window::render()
{
	fill_rectangle(0, _viewport->area(), back, _viewport);
}

bool c_window::handle_keyboard()
{
	return(false);
}

bool c_window::handle_mouse()
{
	return(false);
}

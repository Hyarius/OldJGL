#include "jgl.h"

c_frame::c_frame(c_widget *p_parent) : c_widget(p_parent)
{
	_box = w_box_component(this);
}

c_frame::~c_frame()
{

}

void c_frame::move(Vector2 delta)
{

}

void c_frame::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
{
	viewport()->set_viewport(viewport()->anchor() + 3, viewport()->area() - 6);
	_box.set_area(p_area);
	_box.set_anchor(p_anchor);
}

void c_frame::render()
{
	_box.render(_viewport);
}

bool c_frame::handle_mouse()
{
	return (false);
}

bool c_frame::handle_keyboard()
{
	return (false);
}

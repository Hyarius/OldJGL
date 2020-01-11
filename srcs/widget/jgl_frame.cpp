#include "jgl.h"

c_frame::c_frame(c_widget *p_parent) : c_widget(p_parent)
{
	_box = w_box_component(this);

	set_geometry(-1, -1);
}

c_frame::~c_frame()
{

}

void c_frame::move(Vector2 delta)
{
	_box.set_anchor(_box.anchor() + delta);
	_viewport->set_anchor(anchor() + delta);
}

void c_frame::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
{
	//viewport()->resize(p_anchor + _box.border(), p_area - _box.border() * 2);
	_box.set_area(p_area);
	_box.set_anchor(p_anchor);
}

void c_frame::render()
{
	if (is_active() == false)
		return ;

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

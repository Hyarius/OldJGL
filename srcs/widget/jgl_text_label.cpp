#include "jgl.h"

c_text_label::c_text_label(string p_text, c_widget *p_parent) : c_widget(p_parent)
{
	_box = w_box_component(this);
	_box.set_back(Color(0, 0, 0, 0));
	_box.set_front(Color(0, 0, 0, 0));
	_label = w_text_component(this, p_text);
}

c_text_label::~c_text_label()
{

}

void c_text_label::move(Vector2 delta)
{

}

void c_text_label::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
{
	_box.set_area(p_area);
	_box.set_anchor(p_anchor);
	_label.set_area(p_area - _box.border() * 4);
	_label.set_anchor(p_anchor + _box.border() * 2);
	_label.calc_text_size(_label.area());
}

void c_text_label::render()
{
	if (is_active() == false)
		return ;
	_box.render(_viewport);
	_label.render(_viewport);
}

bool c_text_label::handle_mouse()
{
	return (false);
}

bool c_text_label::handle_keyboard()
{
	return (false);
}

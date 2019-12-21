#include "jgl.h"

c_value_label::c_value_label(float p_value, c_widget *p_parent) : c_widget(p_parent)
{
	_box = w_box_component(this);
	_label = w_value_component(this, p_value);
}

c_value_label::~c_value_label()
{

}

void c_value_label::move(Vector2 delta)
{

}

void c_value_label::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
{
	_box.set_area(p_area);
	_box.set_anchor(p_anchor);
	_label.set_area(p_area - _box.border() * 4);
	_label.set_anchor(p_anchor + _box.border());
	_label.calc_text_size(_label.area());
}

void c_value_label::render()
{
	if (is_active() == false)
		return ;
	_box.render(_viewport);
	_label.render(_viewport);
}

bool c_value_label::handle_mouse()
{
	return (false);
}

bool c_value_label::handle_keyboard()
{
	return (false);
}

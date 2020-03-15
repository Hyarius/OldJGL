#include "jgl.h"

c_check_box::c_check_box(string p_label, bool p_state, c_widget *p_parent) : c_widget(p_parent)
{
	_box = w_box_component(this);
	_label = w_text_component(this, p_label);
	_label.set_align(alignment::centred);

	_check = w_check_component(this, p_state);
	_check.set_check(Color(70, 150, 255));

	set_geometry(-1, -1);
}

c_check_box::~c_check_box()
{

}

void c_check_box::move(Vector2 delta)
{
	_box.set_anchor(_box.anchor() + delta);
	_check.set_anchor(_check.anchor() + delta);
	_label.set_anchor(_label.anchor() + delta);
	_viewport->set_anchor(anchor() + delta);
}

void c_check_box::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
{
	//viewport()->resize(p_anchor, p_area);
	_box.set_area(p_area);
	_box.set_anchor(p_anchor);

	Vector2 check_area = p_area.y - _box.border() * 4;
	Vector2 check_pos = p_anchor + _box.border() * 2;

	Vector2 text_area;
	text_area.x = p_area.x - check_area.x - _box.border() * 5;
	text_area.y = p_area.y - _box.border() * 4;

	_label.set_area(text_area);
	_label.set_anchor(p_anchor + _box.border() * 3 + Vector2(check_area.x, 0.0f));
	_label.calc_text_size(_label.area());

	_check.set_area(check_area);
	_check.set_anchor(check_pos);
	_check.set_border((check_area.x / 8.0f > 1.0f ? static_cast<int>(check_area.x / 8.0f) : 1));
}

void c_check_box::render()
{
	if (is_active() == false)
		return ;
	_box.render(_viewport);
	_label.render(_viewport);
	_check.render(_viewport);
}

bool c_check_box::handle_mouse()
{
	if (g_mouse->get_button(mouse_button::left) == mouse_state::up && is_pointed(g_mouse->pos))
	{
		_check.set_state(!_check.state());
		return (true);
	}
	return (false);
}

bool c_check_box::handle_keyboard()
{
	return (false);
}

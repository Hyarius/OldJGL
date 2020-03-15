#include "jgl.h"

c_check_entry::c_check_entry(string p_entry, bool p_state, c_widget *p_parent) : c_widget(p_parent)
{
	_box = w_box_component(this);
	_entry = w_text_entry_component(this, p_entry);
	_entry.set_align(alignment::centred);

	_check = w_check_component(this, p_state);
	_check.set_check(Color(70, 150, 255));

	set_geometry(-1, -1);
}

c_check_entry::~c_check_entry()
{

}

void c_check_entry::move(Vector2 delta)
{
	_box.set_anchor(_box.anchor() + delta);
	_check.set_anchor(_check.anchor() + delta);
	_entry.set_anchor(_entry.anchor() + delta);
	_viewport->set_anchor(anchor() + delta);
}

void c_check_entry::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
{
	//viewport()->resize(p_anchor, p_area);
	_box.set_area(p_area);
	_box.set_anchor(p_anchor);

	Vector2 check_area = p_area.y - _box.border() * 4;
	Vector2 check_pos = p_anchor + _box.border() * 2;

	Vector2 text_area;
	text_area.x = p_area.x - check_area.x - _box.border() * 5;
	text_area.y = p_area.y - _box.border() * 4;

	_entry.set_area(text_area);
	_entry.set_anchor(p_anchor + _box.border() * 3 + Vector2(check_area.x, 0.0f));
	_entry.calc_text_size(_entry.area());

	_check.set_area(check_area);
	_check.set_anchor(check_pos);
	_check.set_border((check_area.x / 8.0f > 1.0f ? static_cast<int>(check_area.x / 8.0f) : 1));
}

void c_check_entry::render()
{
	if (is_active() == false)
		return ;

	cout << "Here" << endl;

	_box.render(_viewport);
	_entry.render(_viewport);
	_check.render(_viewport);
}

bool c_check_entry::handle_mouse()
{
	if (g_mouse->get_button(mouse_button::left) == mouse_state::up && is_pointed(g_mouse->pos))
	{
		if (_check.check(g_mouse->pos) == true)
			_check.set_state(!_check.state());
		return (true);
	}
	return (false);
}

bool c_check_entry::handle_keyboard()
{
	return (false);
}

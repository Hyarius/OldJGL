#include "jgl.h"

c_button::c_button(Funct p_funct, Data p_data, c_widget *p_parent) : c_widget(p_parent)
{
	_funct = p_funct;
	_data = p_data;
	_timer = 0;
	_timer_delta = 12;
	_delta = Color(50, 50, 50, 150);
	_repeat_click = false;

	_box = w_box_component(this);
	_text = w_text_component(this, "Click me !");
	_text.set_align(alignment::centred);
}

c_button::~c_button()
{

}

void c_button::move(Vector2 delta)
{
	_box.set_anchor(_box.anchor() + delta);
	_text.set_anchor(_text.anchor() + delta);
	_viewport->set_anchor(anchor() + delta);
}

void c_button::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
{
	_box.set_area(p_area);
	_box.set_anchor(p_anchor);
	_text.set_area(p_area - _box.border() * 4);
	_text.set_anchor(p_anchor + _box.border() * 2);
	_text.calc_text_size(_text.area());
}

void c_button::render()
{
	if (is_active() == false)
		return ;

	if (_timer > 0 && _timer--)
		_box.set_delta(Color(0, 0, 0, 150));
	else
		_box.set_delta(Color(0, 0, 0, 0));

	_box.render(_viewport);

	_text.render(_viewport);
}

bool c_button::handle_mouse()
{
	if (g_mouse->get_button(mouse_button::left) == mouse_state::up && is_pointed(g_mouse->pos))
	{
		if (_funct != nullptr)
			_funct(_data);
		return (true);
	}
	if (g_mouse->get_button(mouse_button::left) == mouse_state::down && is_pointed(g_mouse->pos))
	{
		if (_timer == 0 && _repeat_click == true && _funct != nullptr)
		{
			_funct(_data);
			_timer = _timer_delta;
			return (true);
		}

		if (_timer == 0)
			_timer = _timer_delta;
	}

	return (false);
}

bool c_button::handle_keyboard()
{
	return (false);
}

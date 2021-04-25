#include "jgl.h"

namespace jgl
{
	Button::Button(Funct p_funct, Data p_data, Widget* p_parent) : Widget(p_parent)
	{
		_funct = p_funct;
		_data = p_data;
		_timer = 0;
		_timer_delta = 12;
		_delta = Color(50, 50, 50, 150);
		_repeat_click = false;

		_box = w_box_component(this);
		_label = w_text_component("Click me !", this);
		_label.set_horizontal_alignment(Horizontal_alignment::centred);
		_label.set_vertical_alignment(Vertical_alignment::centred);

		set_geometry(-1, -1);
	}

	void Button::move(Vector2 delta)
	{
		_box.set_anchor(_box.anchor() + delta);
		_label.set_anchor(_label.anchor() + delta);
		_viewport->set_anchor(anchor() + delta);
	}

	void Button::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
	{
		_box.set_area(p_area);
		_box.set_anchor(0);
		_label.set_area(p_area - _box.border() * 2);
		_label.set_anchor(_box.border());
		_label.calc_text_size(_label.area());
	}

	void Button::render()
	{
		if (is_active() == false)
			return;

		_viewport->use();
		_box.render(_layer, _viewport);

		_label.render(_layer, _viewport);
	}

	void Button::update()
	{
		if (_timer > 0 && _timer--)
			_box.set_delta(Color(0, 0, 0, 150));
		else
			_box.set_delta(Color(0, 0, 0, 0));
	}

	bool Button::handle_mouse()
	{
		if (g_mouse->get_button(mouse_button::left) == mouse_state::release && is_pointed(g_mouse->pos))
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
			}

			if (_timer == 0)
				_timer = _timer_delta;

			return (true);
		}

		return (false);
	}

	bool Button::handle_keyboard()
	{
		return (false);
	}
}
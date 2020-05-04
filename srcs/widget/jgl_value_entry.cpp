#include "jgl.h"

namespace jgl
{
	Value_entry::Value_entry(float p_value, Widget* p_parent) : Widget(p_parent)
	{
		_box = w_box_component(this);
		_entry = w_value_entry_component(this, p_value);

		_select = false;
		_next_input = 0;
		_input_delay = 150;

		set_geometry(-1, -1);
		unselect();
	}

	Value_entry::~Value_entry()
	{

	}

	void Value_entry::move(Vector2 delta)
	{
		_box.set_anchor(_box.anchor() + delta);
		_entry.set_anchor(_entry.anchor() + delta);
		_viewport->set_anchor(anchor() + delta);
	}

	void Value_entry::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
	{
		//viewport()->resize(p_anchor, p_area);
		_box.set_area(p_area);
		_box.set_anchor(p_anchor);
		_entry.set_area(p_area - _box.border() * 4);
		_entry.set_anchor(p_anchor + _box.border() * 2);
		_entry.calc_text_size_height(_entry.area());
		_entry.calc_text_to_draw();
	}

	void Value_entry::render()
	{
		if (is_active() == false)
			return;
		_box.render(_viewport);
		_entry.render(_viewport);
	}

	bool Value_entry::handle_mouse()
	{
		if (g_mouse->get_button(mouse_button::left) == mouse_state::down)
			unselect();

		if (g_mouse->get_button(mouse_button::left) == mouse_state::up)
		{
			if (is_pointed(g_mouse->pos) == true)
			{
				select();
				return (true);
			}
		}
		return (false);
	}

	bool Value_entry::handle_keyboard()
	{
		if (selected() == false)
			return (false);

		if (g_keyboard->get_key(key::return_key) == key_state::pressed)
			unselect();
		else if (g_keyboard->get_key(key::key_pad_return_key) == key_state::pressed)
			unselect();
		else if (g_keyboard->get_key(key::left_arrow) == key_state::pressed)
			_entry.move_cursor(-1);
		else if (g_keyboard->get_key(key::right_arrow) == key_state::pressed)
			_entry.move_cursor(1);
		else if (g_keyboard->get_key(key::backspace) == key_state::pressed)
			_entry.remove_text();
		else if (g_keyboard->get_key(key::delete_key) == key_state::pressed)
			_entry.supp_text();

		if (g_application->event()->type == SDL_TEXTINPUT)
		{
			static Glyph last_char = '\0';
			Uint32 time = SDL_GetTicks();
			jgl::String text = g_application->event()->text.text;
			if (text[0] != last_char || time >= _next_input)
			{
				last_char = text[0];
				_entry.add_text(text);
				_next_input = time + _input_delay;
			}
		}

		return (false);
	}
}
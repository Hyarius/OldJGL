#include "jgl.h"

namespace jgl
{
	Text_entry::Text_entry(jgl::String p_text, Widget* p_parent) : Widget(p_parent)
	{
		_box = w_box_component(this);
		_entry = w_text_entry_component(p_text, this);

		_select = false;
		_next_input = 0;
		_input_delay = 1;

		set_geometry(-1, -1);
		unselect();
	}

	void Text_entry::move(Vector2 delta)
	{
		_box.set_anchor(_box.anchor() + delta);
		_entry.set_anchor(_entry.anchor() + delta);
		_viewport->set_anchor(anchor() + delta);
	}

	void Text_entry::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
	{
		_box.set_area(p_area);
		_box.set_anchor(0);
		_entry.set_area(p_area - _box.border() * 4);
		_entry.set_anchor(_box.border() * 2);
		_entry.calc_text_size_height(_entry.area());
		_entry.calc_text_to_draw();
	}

	void Text_entry::render()
	{
		if (is_active() == false)
			return;
		_viewport->use();
		_box.render(_layer, _viewport);
		_entry.render(_layer, _viewport);
	}

	bool Text_entry::handle_mouse()
	{
		if (g_mouse->get_button(mouse_button::left) == mouse_state::pressed)
			unselect();

		if (g_mouse->get_button(mouse_button::left) == mouse_state::release)
		{
			if (is_pointed(g_mouse->pos) == true)
			{
				select();
				return (true);
			}
		}
		return (false);
	}

	bool Text_entry::handle_keyboard()
	{
		if (selected() == false)
			return (false);

		static Uint32 ticks = 0;

		if (g_keyboard->get_key(key::return_key) == key_state::pressed ||
			g_keyboard->get_key(key::key_pad_return_key) == key_state::pressed)
			unselect();
		else if (g_keyboard->get_key(key::left_arrow) == key_state::down && ticks < SDL_GetTicks() && (ticks = SDL_GetTicks() + 100))
			_entry.move_cursor(-1);
		else if (g_keyboard->get_key(key::right_arrow) == key_state::down && ticks < SDL_GetTicks() && (ticks = SDL_GetTicks() + 100))
			_entry.move_cursor(1);
		else if (g_keyboard->get_key(key::backspace) == key_state::down && g_application->time() >= _next_input)
		{
			_entry.remove_text();
			_next_input = g_application->time() + _input_delay / 2;
		}
		else if (g_keyboard->get_key(key::delete_key) == key_state::down && g_application->time() >= _next_input)
		{
			_entry.supp_text();
			_next_input = g_application->time() + _input_delay / 2;
		}

		if (g_application->event()->type == SDL_TEXTINPUT)
		{
			static Glyph last_char = '\0';
			Glyph text = g_application->event()->text.text;
			if (text != last_char || g_application->time() >= _next_input)
			{
				last_char = text;
				_entry.add_text(text);
				_next_input = g_application->time() + _input_delay;
			}
		}

		return (false);
	}
}
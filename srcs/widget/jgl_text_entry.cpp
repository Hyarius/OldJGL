#include "jgl.h"

c_text_entry::c_text_entry(string p_text, c_widget *p_parent) : c_widget(p_parent)
{
	_box = w_box_component(this);
	_entry = w_text_entry_component(this, p_text);

	_select = false;
	_next_input = 0;
	_input_delay = 100;
}

c_text_entry::~c_text_entry()
{

}

void c_text_entry::move(Vector2 delta)
{

}

void c_text_entry::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
{
	_box.set_area(p_area);
	_box.set_anchor(p_anchor);
	_entry.set_area(p_area - _box.border() * 4);
	_entry.set_anchor(p_anchor + _box.border() * 2);
	_entry.calc_text_size_height(_entry.area());
	_entry.calc_text_to_draw();
}

void c_text_entry::render()
{
	if (is_active() == false)
		return ;
	_box.render(_viewport);
	_entry.render(_viewport);
}

bool c_text_entry::handle_mouse()
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

bool c_text_entry::handle_keyboard()
{
	if (selected() == false)
		return (false);

	if (g_keyboard->get_key(SDL_SCANCODE_RETURN))
	{
		unselect();
		g_keyboard->reset_key(SDL_SCANCODE_RETURN);
	}
	else if (g_keyboard->get_key(SDL_SCANCODE_KP_ENTER))
	{
		unselect();
		g_keyboard->reset_key(SDL_SCANCODE_KP_ENTER);
	}
	else if (g_keyboard->get_key(SDL_SCANCODE_LEFT))
	{
		_entry.move_cursor(-1);
		g_keyboard->reset_key(SDL_SCANCODE_LEFT);
	}
	else if (g_keyboard->get_key(SDL_SCANCODE_RIGHT))
	{
		_entry.move_cursor(1);
		g_keyboard->reset_key(SDL_SCANCODE_RIGHT);
	}
	else if (g_keyboard->get_key(SDL_SCANCODE_BACKSPACE))
	{
		_entry.remove_text();
		g_keyboard->reset_key(SDL_SCANCODE_BACKSPACE);
	}
	else if (g_keyboard->get_key(SDL_SCANCODE_DELETE))
	{
		_entry.supp_text();
		g_keyboard->reset_key(SDL_SCANCODE_DELETE);
	}

	if (g_application->event()->type == SDL_TEXTINPUT)
	{
		static char last_char = '\0';
		Uint32 time = SDL_GetTicks();
		if (g_application->event()->text.text[0] != last_char ||
			time >= _next_input)
		{
			string text = g_application->event()->text.text;
			string text_content;
			text_content = string(text.begin(), text.end());
			last_char = text_content[0];
			_entry.add_text(text_content);
			_next_input = time + _input_delay;
		}
	}

	return (false);
}

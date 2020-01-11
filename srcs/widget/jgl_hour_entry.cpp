#include "jgl.h"

c_hour_entry::c_hour_entry(float p_hour, float p_minute, c_widget *p_parent) : c_widget(p_parent)
{
	_box = w_box_component(this);
	_label = w_text_component(this, ":");
	_hour = w_value_entry_component(this, p_hour);
	_minute = w_value_entry_component(this, p_minute);

	_entry = nullptr;
	_selected = false;
	_next_input = 0;
	_input_delay = 100;

	set_geometry(-1, -1);
}

c_hour_entry::~c_hour_entry()
{

}

void c_hour_entry::move(Vector2 delta)
{
	_box.set_anchor(_box.anchor() + delta);
	_hour.set_anchor(_hour.anchor() + delta);
	_minute.set_anchor(_minute.anchor() + delta);
	_label.set_anchor(_label.anchor() + delta);
	_viewport->set_anchor(anchor() + delta);
}

void c_hour_entry::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
{
	//viewport()->resize(p_anchor, p_area);
	_box.set_area(p_area);
	_box.set_anchor(p_anchor);

	_label.set_area(p_area - _box.border() * 2);
	_label.set_anchor(p_anchor + _box.border());
	_label.set_align(alignment::centred);
	_label.calc_text_size(_label.area());

	Vector2 number_size = (p_area - _box.border() * 2) / Vector2(2, 1) - Vector2(_box.border() * 2, 0);
	Vector2 hour_pos = p_anchor + _box.border();
	Vector2 minute_pos = hour_pos + Vector2(number_size.x + _box.border() * 4, 0.0f);

	_hour.set_area(number_size);
	_hour.set_align(alignment::right);
	_hour.calc_text_size_height(_hour.area());
	_hour.calc_text_to_draw();
	_hour.set_anchor(hour_pos);

	_minute.set_area(number_size);
	//_minute.set_text("00");
	_minute.calc_text_size_height(_minute.area());
	_minute.calc_text_to_draw();
	_minute.set_anchor(minute_pos);

	round();
}

void c_hour_entry::render()
{
	if (is_active() == false)
		return ;

	_box.render(_viewport);
	_label.render(_viewport);

	_hour.render(_viewport);
	_minute.render(_viewport);
}

void c_hour_entry::round()
{
	_hour.set_value((int)(_hour.value()) % 24);
	_minute.set_value((int)(_minute.value()) % 60);

	while (_hour.text().size() < 2)
		_hour.set_text("0" + _hour.text());

	while (_minute.text().size() < 2)
		_minute.set_text("0" + _minute.text());

	_minute.set_cursor(0);
	_hour.set_cursor(0);
	_minute.calc_text_to_draw();
	_hour.calc_text_to_draw();
}

void c_hour_entry::unselect()
{
	_selected = false;
	_hour.set_selected(false);
	_minute.set_selected(false);

	round();

	_entry = nullptr;
}

void c_hour_entry::select()
{
	if (_hour.is_pointed(g_mouse->pos) == true)
	{
		_selected = true;
		_hour.set_selected(true);
		_entry = &_hour;
	}
	else if (_minute.is_pointed(g_mouse->pos) == true)
	{
		_selected = true;
		_minute.set_selected(true);
		_entry = &_minute;
	}
}

bool c_hour_entry::handle_mouse()
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

bool c_hour_entry::handle_keyboard()
{
	if (selected() == false || _entry == nullptr)
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
		if (_entry == &_minute && _entry->cursor() == 0)
		{
			_minute.set_selected(false);
			_hour.set_selected(true);
			_entry = &_hour;
			_entry->set_cursor(1);
		}
		else
			_entry->move_cursor(-1);
		g_keyboard->reset_key(SDL_SCANCODE_LEFT);
	}
	else if (g_keyboard->get_key(SDL_SCANCODE_RIGHT))
	{
		if (_entry == &_hour && _entry->cursor() == 1)
		{
			_hour.set_selected(false);
			_minute.set_selected(true);
			_entry = &_minute;
			_entry->set_cursor(0);
		}
		else
			_entry->move_cursor(1);

		g_keyboard->reset_key(SDL_SCANCODE_RIGHT);
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
			if (_entry == &_hour && _entry->cursor() == 1)
			{
				_entry->change_text(text_content);
				_hour.set_selected(false);
				_minute.set_selected(true);
				_entry = &_minute;
				_entry->set_cursor(0);
			}
			else
				_entry->change_text(text_content);
			_next_input = time + _input_delay;
		}
	}

	return (false);
}

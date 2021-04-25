#include "jgl.h"

namespace jgl
{
	w_entry_component::w_entry_component(jgl::String p_text, class Widget* p_owner) :
		w_component(p_owner), w_graphical_component(), w_textual_component()
	{
		_text = p_text;
		_cursor = 0;
		_text_to_draw = p_text;
		_cursor_to_draw = 0;
		_area = Vector2();
		_anchor = Vector2();
		_h_align = Horizontal_alignment::left;
		_v_align = Vertical_alignment::top;
		_size = 16;
		_color = text_color::black;
		_style = text_style::normal;
	}

	void 		w_entry_component::calc_text_to_draw()
	{
		_text_to_draw = "";
		_cursor_to_draw = 0;

		uint32_t i = _cursor;

		if (_text.empty() == false)
		{
			if (_cursor > 0)
			{
				while (i > 0 && calc_text_len(_text_to_draw + _text[i - 1], _size) < _area.x)
				{
					_text_to_draw.push_front(_text[i - 1]);
					i--;
				}
			}
			_cursor_to_draw = _cursor - i;
			if (_cursor < _text.size())
			{
				i = _cursor;
				while (i < _text.size() && calc_text_len(_text_to_draw + _text[i], _size) < _area.x)
				{
					_text_to_draw.push_back(_text[i]);
					i++;
				}
			}
		}
	}
	void w_entry_component::move_cursor(int delta)
	{
		if ((delta > 0 && _cursor < _text.size()) || (delta < 0 && _cursor > 0))
		{
			_cursor += delta;
			calc_text_to_draw();
		}
	}

	void w_entry_component::add_text(jgl::String new_text)
	{
		_text.insert(_cursor, new_text);
		_cursor += new_text.size();
		calc_text_to_draw();
	}

	void w_entry_component::change_text(jgl::String new_text)
	{
		for (uint32_t i = 0; i < new_text.size() && i + _cursor < _text.size(); i++)
			_text[_cursor + i] = new_text[i];

		_cursor++;
		calc_text_to_draw();
	}

	void w_entry_component::remove_text()
	{
		if (_cursor > 0 && _text.size() != 0)
		{
			_cursor -= 1;
			_text.erase(_cursor);
			calc_text_to_draw();
		}
	}

	void w_entry_component::supp_text()
	{
		if (_cursor < _text.size() && _text.size() != 0)
		{
			_text.erase(_cursor);
			calc_text_to_draw();
		}
	}

	void 		w_entry_component::render(const float layer, Viewport* viewport)
	{
		Vector2 pos = 0;

		if (_h_align == Horizontal_alignment::left)
		{
			pos.x = 0;
		}
		else if (_h_align == Horizontal_alignment::centred)
		{
			pos.x = _area.x / 2 - calc_text_len(_text_to_draw, _size) / 2.0f;
		}
		else if (_h_align == Horizontal_alignment::right)
		{
			pos.x = _area.x - calc_text_len(_text_to_draw, _size);
		}

		if (_v_align == Vertical_alignment::top)
		{
			pos.y = 0;
		}
		else if (_v_align == Vertical_alignment::centred)
		{
			pos.y = _area.y / 2.0f - _size / 2;
		}
		else if (_v_align == Vertical_alignment::bottom)
		{
			pos.y = _area.y - _size;
		}	

		pos += _anchor;

		if (_masked == true)
			draw_text(jgl::normalize_string("", jgl::Glyph('*'), _text_to_draw.size()), pos, _size, _outline, 1.0f, _color, _style, layer, viewport);
		else
			draw_text(_text_to_draw, pos - jgl::Vector2(0.0f, _size / 4.0f), _size, _outline, 1.0f, _color, _style, layer, viewport);

		pos.x += calc_text_len(_text_to_draw.substr(0, _cursor_to_draw), _size);

		if (_selected == true && (SDL_GetTicks() / 400) % 2 == 0)
			fill_rectangle(pos, Vector2(2, _size), Color(50, 50, 50), layer, viewport);
	}
}
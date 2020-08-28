#include "jgl.h"

namespace jgl
{
	w_text_component::w_text_component(jgl::String p_text, Widget* p_owner) :
		w_component(p_owner), w_graphical_component(), w_textual_component()
	{
		_text = p_text;
		_area = Vector2();
		_anchor = Vector2();
		_align = alignment::left;
		_size = 16;
		_color = text_color::black;
		_style = text_style::normal;
	}

	void w_text_component::resize(Vector2 p_anchor, Vector2 p_area)
	{
		set_anchor(p_anchor);
		set_area(p_area);
		calc_text_size(_area);
	}

	void w_text_component::render(Viewport* viewport)
	{
		Vector2 pos;

		if (_align == alignment::left)
		{
			pos.x = calc_text_len(_text, _size) / 2.0f;
			pos.y = _area.y / 2.0f;
		}
		else if (_align == alignment::centred)
		{
			pos = _area / 2;
		}
		else if (_align == alignment::right)
		{
			pos.x = _area.x - calc_text_len(_text, _size) / 2.0f;
			pos.y = _area.y / 2.0f;
		}
		pos += _anchor;
		draw_centred_text(_text, pos, _size, 0, 1.0f, _color, _style);
	}
}
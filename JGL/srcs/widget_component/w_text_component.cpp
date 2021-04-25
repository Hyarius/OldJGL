#include "jgl.h"

namespace jgl
{
	w_text_component::w_text_component(jgl::String p_text, Widget* p_owner) :
		w_component(p_owner), w_graphical_component(), w_textual_component()
	{
		_text = p_text;
		_masked = false;
		_area = Vector2();
		_anchor = Vector2();
		_h_align = Horizontal_alignment::left;
		_v_align = Vertical_alignment::top;
		_size = 16;
		_color = text_color::black;
		_style = text_style::normal;
	}

	void w_text_component::resize(Vector2 p_anchor, Vector2 p_area)
	{
		set_anchor(p_anchor);
		set_area(p_area);
	}

	void w_text_component::render(const float layer, Viewport* viewport)
	{
		Vector2 pos;

		viewport->use();

		if (_h_align == Horizontal_alignment::left)
		{
			pos.x = calc_text_len(_text, _size) / 2.0f;
		}
		else if (_h_align == Horizontal_alignment::centred)
		{
			pos.x = _area.x / 2;
		}
		else if (_h_align == Horizontal_alignment::right)
		{
			pos.x = _area.x - calc_text_len(_text, _size) / 2.0f;
		}

		if (_v_align == Vertical_alignment::top)
		{
			pos.y = _size / 2.0f;
		}
		else if (_v_align == Vertical_alignment::centred)
		{
			pos.y = _area.y / 2.0f;
		}
		else if (_v_align == Vertical_alignment::bottom)
		{
			pos.y = _area.y - (_size / 2);
		}

		pos += _anchor;
		if (_masked == true)
			draw_centred_text(jgl::normalize_string("", jgl::Glyph('*'), _text.size()), pos, _size, _outline, 1.0f, _color, _style, layer, viewport);
		else
			draw_centred_text(_text, pos, _size, _outline, 1.0f, _color, _style, layer, viewport);
	}
}
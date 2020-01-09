#include "jgl.h"

w_value_component::w_value_component(c_widget *p_owner, float p_value) :
		w_component(p_owner), w_graphical_component(), w_textual_component()
{
	_value = p_value;
	_precision = 3;
	_text = ftoa(_value, _precision);
	_anchor = Vector2();
	_area = Vector2();
	_align = alignment::left;
	_size = 16;
	_color = text_color::black;
	_style = text_style::normal;
}

void w_value_component::render(c_viewport *viewport)
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
	draw_centred_text(_text, pos + _anchor, _size, 0, _color, _style, viewport);
}

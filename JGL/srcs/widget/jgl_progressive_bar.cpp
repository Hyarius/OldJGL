#include "jgl.h"

namespace jgl
{
	Progressive_bar::Progressive_bar(float p_percent, Color p_color, Widget* p_parent) : Widget(p_parent)
	{
		_box = w_box_component(this);
		_print_value = true;
		_percent = p_percent / 100.0f;
		_color = p_color;
		_max_value = 0;
	}

	void Progressive_bar::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
	{
		_box.set_area(p_area);
		_box.set_anchor(p_anchor);
	}

	void Progressive_bar::render()
	{
		_box.render(_viewport);
		Vector2 size = Vector2((_box.area().x - _box.border() * 2), _box.area().y - _box.border() * 2 + 1);
		Vector2 edited_size = Vector2((_box.area().x - _box.border() * 2) * _percent, _box.area().y - _box.border() * 2 + 1);
		fill_rectangle(jgl::Vector2(0, -1) + _box.border(), edited_size, _color, _viewport);
		if (_print_value == true)
		{
			jgl::String tmp_text;
			if (_max_value == 0.0f)
			{
				tmp_text = jgl::itoa(static_cast<int>(_percent * 100));
			}
			else
			{
				tmp_text = jgl::itoa(static_cast<int>(_percent * _max_value)) + " / " + jgl::itoa(static_cast<int>(_max_value));
			}
			draw_centred_text(tmp_text, jgl::Vector2(0, -1) + _box.border() + size / 2, static_cast<uint32_t>(size.y / 1.3f), 0, 1.0f, jgl::text_color::black, jgl::text_style::normal, _viewport);
		}
	}

	void Progressive_bar::move(Vector2 delta)
	{
		_box.set_anchor(_box.anchor() + delta);
		_viewport->set_anchor(anchor() + delta);
	}
}

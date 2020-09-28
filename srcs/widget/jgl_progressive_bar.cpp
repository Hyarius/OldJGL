#include "jgl.h"

namespace jgl
{
	Progressive_bar::Progressive_bar(float p_percent, Color p_color, Widget* p_parent) : Widget(p_parent)
	{
		_box = w_box_component(this);
		_percent = p_percent / 100.0f;
		_color = p_color;
	}

	void Progressive_bar::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
	{
		_box.set_area(p_area);
		_box.set_anchor(p_anchor);
	}

	void Progressive_bar::render()
	{
		_box.render(_viewport);
		Vector2 size = Vector2((_box.area().x - _box.border() * 2) * _percent, _box.area().y - _box.border() * 2 + 1);
		fill_rectangle(jgl::Vector2(0, -1) + _box.border(), size, _color, _viewport);
	}

	void Progressive_bar::move(Vector2 delta)
	{
		_box.set_anchor(_box.anchor() + delta);
		_viewport->set_anchor(anchor() + delta);
	}
}

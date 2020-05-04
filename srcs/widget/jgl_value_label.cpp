#include "jgl.h"

namespace jgl
{
	Value_label::Value_label(float p_value, Widget* p_parent) : Widget(p_parent)
	{
		_box = w_box_component(this);
		_label = w_value_component(this, p_value);

		set_geometry(-1, -1);
	}

	Value_label::~Value_label()
	{

	}

	void Value_label::move(Vector2 delta)
	{
		_box.set_anchor(_box.anchor() + delta);
		_label.set_anchor(_label.anchor() + delta);
		_viewport->set_anchor(anchor() + delta);
	}

	void Value_label::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
	{
		//viewport()->resize(p_anchor, p_area);
		_box.set_area(p_area);
		_box.set_anchor(p_anchor);
		_label.set_area(p_area - _box.border() * 4);
		_label.set_anchor(p_anchor + _box.border());
		_label.calc_text_size(_label.area());
	}

	void Value_label::render()
	{
		if (is_active() == false)
			return;
		_box.render(_viewport);
		_label.render(_viewport);
	}

	bool Value_label::handle_mouse()
	{
		return (false);
	}

	bool Value_label::handle_keyboard()
	{
		return (false);
	}
}
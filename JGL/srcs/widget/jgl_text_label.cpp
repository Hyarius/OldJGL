#include "jgl.h"

namespace jgl
{
	Text_label::Text_label(jgl::String p_text, Widget* p_parent) : Widget(p_parent)
	{
		_box = w_box_component(this);
		_box.set_back(Color(0, 0, 0, 0));
		_box.set_front(Color(0, 0, 0, 0));
		_label = w_text_component(p_text, this);

		set_geometry(-1, -1);
	}

	void Text_label::move(Vector2 delta)
	{
		_box.set_anchor(_box.anchor() + delta);
		_label.set_anchor(_label.anchor() + delta);
		_viewport->set_anchor(anchor() + delta);
	}

	void Text_label::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
	{
		_viewport->resize(p_anchor, p_area);
		_box.set_area(p_area);
		_box.set_anchor(p_anchor);
		_label.set_area(p_area - _box.border() * 4);
		_label.set_anchor(p_anchor + _box.border() * 2);
		_label.calc_text_size(_label.area());
	}

	void Text_label::render()
	{
		if (is_active() == false)
			return;
		_box.render(_viewport);
		_label.render(_viewport);
	}

	bool Text_label::handle_mouse()
	{
		return (false);
	}

	bool Text_label::handle_keyboard()
	{
		return (false);
	}
}
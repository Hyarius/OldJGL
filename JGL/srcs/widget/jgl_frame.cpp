#include "jgl.h"

namespace jgl
{
	Frame::Frame(Widget* p_parent) : Widget(p_parent)
	{
		_box = w_box_component(this);

		set_geometry(-1, -1);
	}

	void Frame::move(Vector2 delta)
	{
		_box.set_anchor(_box.anchor() + delta);
		_viewport->set_anchor(anchor() + delta);
	}

	void Frame::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
	{
		_box.set_area(p_area);
		_box.set_anchor(0);
	}

	void Frame::render()
	{
		_viewport->use();
		_box.render(_layer, _viewport);
	}

	bool Frame::handle_mouse()
	{
		return (false);
	}

	bool Frame::handle_keyboard()
	{
		return (false);
	}
}
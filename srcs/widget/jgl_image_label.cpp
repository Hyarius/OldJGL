#include "jgl.h"

namespace jgl
{
	Image_label::Image_label(jgl::String path, Widget* p_parent) : Widget(p_parent)
	{
		_box = w_box_component(this);
		_box.set_back(Color(0, 0, 0, 0));
		_box.set_front(Color(0, 0, 0, 0));

		set_image(path);
		set_geometry(-1, -1);
	}

	Image_label::Image_label(Image* image, Widget* p_parent) : Widget(p_parent)
	{
		_box = w_box_component(this);
		_box.set_back(Color(0, 0, 0, 0));
		_box.set_front(Color(0, 0, 0, 0));

		set_image(image);
		set_geometry(-1, -1);
	}

	void Image_label::move(Vector2 delta)
	{
		_box.set_anchor(_box.anchor() + delta);
		_viewport->set_anchor(anchor() + delta);
	}

	void Image_label::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
	{
		//viewport()->resize(p_anchor, p_area);
		_box.set_area(p_area);
		_box.set_anchor(p_anchor);
	}

	void Image_label::render()
	{
		if (is_active() == false)
			return;
		_box.render(_viewport);
	}

	bool Image_label::handle_mouse()
	{
		return (false);
	}

	bool Image_label::handle_keyboard()
	{
		return (false);
	}
}

#include "jgl.h"

namespace jgl
{
	Sprite_label::Sprite_label(jgl::String path, jgl::Vector2 size, Widget* p_parent) : Widget(p_parent)
	{
		_box = w_box_component(this);
		_box.set_back(Color(0, 0, 0, 0));
		_box.set_front(Color(0, 0, 0, 0));
		_sprite_sheet = new Sprite_sheet(path, size);

		set_geometry(-1, -1);
	}

	Sprite_label::Sprite_label(jgl::Sprite_sheet* image, Widget* p_parent) : Widget(p_parent)
	{
		_box = w_box_component(this);
		_box.set_back(Color(0, 0, 0, 0));
		_box.set_front(Color(0, 0, 0, 0));

		_sprite_sheet = image;

		set_geometry(-1, -1);
	}

	void Sprite_label::move(Vector2 delta)
	{
		_box.set_anchor(_box.anchor() + delta);
		_viewport->set_anchor(anchor() + delta);
	}

	void Sprite_label::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
	{
		_viewport->resize(p_anchor, p_area);
		_box.set_area(p_area);
		_box.set_anchor(p_anchor);
	}

	void Sprite_label::render()
	{
		if (is_active() == false)
			return;
		_box.render(_viewport);
	}

	bool Sprite_label::handle_mouse()
	{
		return (false);
	}

	bool Sprite_label::handle_keyboard()
	{
		return (false);
	}
}

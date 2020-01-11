#include "jgl.h"

c_image_label::c_image_label(string path, c_widget *p_parent) : c_widget(p_parent)
{
	_box = w_box_component(this);
	_box.set_back(Color(0, 0, 0, 0));
	_box.set_front(Color(0, 0, 0, 0));

	set_image(path);
	set_geometry(-1, -1);
}

c_image_label::c_image_label(c_image *image, c_widget *p_parent) : c_widget(p_parent)
{
	_box = w_box_component(this);
	_box.set_back(Color(0, 0, 0, 0));
	_box.set_front(Color(0, 0, 0, 0));

	set_image(image);
	set_geometry(-1, -1);
}

c_image_label::c_image_label(c_tileset *image, c_widget *p_parent) : c_widget(p_parent)
{
	_box = w_box_component(this);
	_box.set_back(Color(0, 0, 0, 0));
	_box.set_front(Color(0, 0, 0, 0));

	set_image(image);
	set_geometry(-1, -1);
}

c_image_label::~c_image_label()
{

}

void c_image_label::move(Vector2 delta)
{
	_box.set_anchor(_box.anchor() + delta);
	_viewport->set_anchor(anchor() + delta);
}

void c_image_label::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
{
	//viewport()->resize(p_anchor, p_area);
	_box.set_area(p_area);
	_box.set_anchor(p_anchor);
}

void c_image_label::render()
{
	if (is_active() == false)
		return ;
	_box.render(_viewport);
}

bool c_image_label::handle_mouse()
{
	return (false);
}

bool c_image_label::handle_keyboard()
{
	return (false);
}

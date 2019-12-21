#include "jgl.h"

static void up_widget(Data data)
{
	c_vscroll_bar *bar = (data.acces<c_vscroll_bar *>(0));
	c_widget *parent = bar->parent();

	if (parent != nullptr)
	{
		for (size_t i = 0; i < parent->childrens().size(); i++)
			parent->childrens()[i]->move(Vector2(0, 10));
	}
}

static void down_widget(Data data)
{
	c_vscroll_bar *bar = (data.acces<c_vscroll_bar *>(0));
	c_widget *parent = bar->parent();

	if (parent != nullptr)
	{
		for (size_t i = 0; i < parent->childrens().size(); i++)
			parent->childrens()[i]->move(Vector2(0, -10));
	}
}

c_vscroll_bar::c_vscroll_bar(c_widget *p_parent) : c_widget(p_parent)
{
	viewport()->set_active(true);
	scroll_bar = new c_frame(this);
	scroll_bar->activate();

	up_button = new c_button(up_widget, this, this);
	up_button->text().set_text("^");
	up_button->set_repeat(true);
	up_button->set_timer_delta(3);
	up_button->activate();

	down_button = new c_button(down_widget, this, this);
	down_button->text().set_text("v");
	down_button->set_repeat(true);
	down_button->set_timer_delta(3);
	down_button->activate();
}

c_vscroll_bar::~c_vscroll_bar()
{

}

bool c_vscroll_bar::handle_mouse()
{
	return (false);
}

void c_vscroll_bar::move(Vector2 delta)
{

}

void c_vscroll_bar::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
{
	Vector2 button_size = Vector2(p_area.x, p_area.x);
	Vector2 scroll_size = Vector2(p_area.x, p_area.y - button_size.y * 2);
	Vector2 anchor[3] = {
		0,
		p_area - button_size,
		Vector2(0.0f, button_size.y)
	};

	up_button->set_geometry(anchor[0], button_size);
	down_button->set_geometry(anchor[1], button_size);
	scroll_bar->set_geometry(anchor[2], scroll_size);
}

void c_vscroll_bar::render()
{

}

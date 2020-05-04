#include "jgl.h"

namespace jgl
{
	static void up_widget(Data data)
	{
		Vscroll_bar* bar = (data.acces<Vscroll_bar*>(0));
		Widget* parent = bar->parent();

		if (parent != nullptr)
		{
			for (size_t i = 0; i < parent->childrens().size(); i++)
				parent->childrens()[i]->move(Vector2(0, 10));
		}
	}

	static void down_widget(Data data)
	{
		Vscroll_bar* bar = (data.acces<Vscroll_bar*>(0));
		Widget* parent = bar->parent();

		if (parent != nullptr)
		{
			for (size_t i = 0; i < parent->childrens().size(); i++)
				parent->childrens()[i]->move(Vector2(0, -10));
		}
	}

	Vscroll_bar::Vscroll_bar(Widget* p_parent) : Widget(p_parent)
	{
		viewport()->set_active(true);
		scroll_bar = new Frame(this);
		scroll_bar->activate();

		up_button = new Button(up_widget, this, this);
		up_button->set_text("^");
		up_button->set_repeat(true);
		up_button->set_timer_delta(3);
		up_button->activate();

		down_button = new Button(down_widget, this, this);
		down_button->set_text("v");
		down_button->set_repeat(true);
		down_button->set_timer_delta(3);
		down_button->activate();

		set_geometry(-1, -1);
	}

	Vscroll_bar::~Vscroll_bar()
	{

	}

	bool Vscroll_bar::handle_mouse()
	{
		if (parent() != nullptr && parent()->is_pointed(g_mouse->pos))
		{
			if (g_mouse->wheel > 0)
				for (int i = 0; i < 3; i++)
					up_widget(this);
			if (g_mouse->wheel < 0)
				for (int i = 0; i < 3; i++)
					down_widget(this);
		}
		return (false);
	}

	void Vscroll_bar::move(Vector2 delta)
	{

	}

	void Vscroll_bar::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
	{
		//viewport()->resize(p_anchor, p_area);
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

	void Vscroll_bar::render()
	{

	}
}
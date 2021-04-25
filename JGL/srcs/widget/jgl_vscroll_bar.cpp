#include "jgl.h"

namespace jgl
{
	static void up_widget(Data data)
	{
		Vscroll_bar* bar = (data.acces<Vscroll_bar*>(0));
		if (bar != nullptr && (bar->max_pos() == -1 || (bar->actual_pos().y < bar->max_pos().y)))
		{
			Vector2 delta = Vector2(0, 10);
			if (bar->max_pos() != -1 && bar->actual_pos().y + delta.y > bar->max_pos().y)
				delta.y = bar->max_pos().y - bar->actual_pos().y;
			Widget* parent = bar->parent();
			 
			if (parent != nullptr)
			{
				for (uint32_t i = 0; i < parent->childrens().size(); i++)
					parent->childrens()[i]->move(delta);
			}
			bar->move_pos(delta);
		}
	}

	static void down_widget(Data data)
	{
		Vscroll_bar* bar = (data.acces<Vscroll_bar*>(0));
		if (bar != nullptr && (bar->min_pos() == -1 || (bar->actual_pos().y > bar->min_pos().y)))
		{
			Vector2 delta = Vector2(0, -10);
			if (bar->min_pos() != -1 && bar->actual_pos().y + delta.y < bar->min_pos().y)
				delta.y = -bar->actual_pos().y;

			Widget* parent = bar->parent();

			if (parent != nullptr)
			{
				for (uint32_t i = 0; i < parent->childrens().size(); i++)
					parent->childrens()[i]->move(delta);
			}
			bar->move_pos(delta);
		}
	}

	Vscroll_bar::Vscroll_bar(Widget* p_parent) : Widget(p_parent)
	{
		scroll_bar = new Frame(this);
		scroll_bar->activate();

		_actual_pos = 0;
		_min_pos = -1;
		_max_pos = -1;

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

	void Vscroll_bar::move_pos(Vector2 delta)
	{
		_actual_pos += delta;
	}

	bool Vscroll_bar::handle_keyboard()
	{
		static uint32_t time = 0;

		if (parent() != nullptr && parent()->is_pointed(g_mouse->pos))
		{
			if (jgl::get_key(jgl::key::up_arrow) == jgl::key_state::down && time < g_application->time())
			{
				time = g_application->time() + 50;
				for (int i = 0; i < 3; i++)
					up_widget(this);
				return (true);
			}
			if (jgl::get_key(jgl::key::down_arrow) == jgl::key_state::down && time < g_application->time())
			{
				time = g_application->time() + 50;
				for (int i = 0; i < 3; i++)
					down_widget(this);
				return (true);
			}
		}
		return (false);
	}

	bool Vscroll_bar::handle_mouse()
	{
		if (parent() != nullptr && parent()->is_pointed(g_mouse->pos))
		{
			if (g_mouse->wheel > 0)
			{
				for (int i = 0; i < 3; i++)
					up_widget(this);
				return (true);
			}
			if (g_mouse->wheel < 0)
			{
				for (int i = 0; i < 3; i++)
					down_widget(this);
				return (true);
			}
		}
		return (false);
	}

	void Vscroll_bar::move(Vector2 delta)
	{

	}

	void Vscroll_bar::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
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

	void Vscroll_bar::render()
	{

	}
}
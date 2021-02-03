#include "jgl.h"

namespace jgl
{
	static void right_widget(Data data)
	{
		Hscroll_bar* bar = (data.acces<Hscroll_bar*>(0));
		if (bar != nullptr && (bar->max_pos() == -1 || (bar->actual_pos().x < bar->max_pos().x)))
		{
			Vector2 delta = Vector2(0, 10);
			if (bar->max_pos() != -1 && bar->actual_pos().x + delta.x > bar->max_pos().x)
				delta.x = bar->max_pos().x - bar->actual_pos().x;
			Widget* parent = bar->parent();

			if (parent != nullptr)
			{
				for (size_t i = 0; i < parent->childrens().size(); i++)
					parent->childrens()[i]->move(delta);
			}
			bar->move_pos(delta);
		}
	}

	static void left_widget(Data data)
	{
		Hscroll_bar* bar = (data.acces<Hscroll_bar*>(0));
		if (bar != nullptr && (bar->min_pos() == -1 || (bar->actual_pos().x > bar->min_pos().x)))
		{
			Vector2 delta = Vector2(0, -10);
			if (bar->min_pos() != -1 && bar->actual_pos().x + delta.x < bar->min_pos().x)
				delta.x = -bar->actual_pos().x;

			Widget* parent = bar->parent();

			if (parent != nullptr)
			{
				for (size_t i = 0; i < parent->childrens().size(); i++)
					parent->childrens()[i]->move(delta);
			}
			bar->move_pos(delta);
		}
	}

	Hscroll_bar::Hscroll_bar(Widget* p_parent) : Widget(p_parent)
	{
		scroll_bar = new Frame(this);
		scroll_bar->activate();

		_actual_pos = 0;
		_min_pos = -1;
		_max_pos = -1;

		right_button = new Button(right_widget, this, this);
		right_button->set_text(">");
		right_button->set_repeat(true);
		right_button->set_timer_delta(3);
		right_button->activate();

		left_button = new Button(left_widget, this, this);
		left_button->set_text("<");
		left_button->set_repeat(true);
		left_button->set_timer_delta(3);
		left_button->activate();

		set_geometry(-1, -1);
	}

	void Hscroll_bar::move_pos(Vector2 delta)
	{
		_actual_pos += delta;
	}
	
	bool Hscroll_bar::handle_keyboard()
	{
		static uint32_t time = 0;

		if (parent() != nullptr && parent()->is_pointed(g_mouse->pos))
		{
			if (jgl::get_key(jgl::key::left_arrow) == jgl::key_state::down && time < g_application->time())
			{
				time = g_application->time() + 50;
				for (int i = 0; i < 3; i++)
					left_widget(this);
				return (true);
			}
			if (jgl::get_key(jgl::key::right_arrow) == jgl::key_state::down && time < g_application->time())
			{
				time = g_application->time() + 50;
				for (int i = 0; i < 3; i++)
					right_widget(this);
				return (true);
			}
		}
		return (false);
	}

	bool Hscroll_bar::handle_mouse()
	{
		if (parent() != nullptr && parent()->is_pointed(g_mouse->pos))
		{
			if (g_mouse->wheel > 0)
			{
				for (int i = 0; i < 3; i++)
					right_widget(this);
				return (true);
			}
			if (g_mouse->wheel < 0)
			{
				for (int i = 0; i < 3; i++)
					left_widget(this);
				return (true);
			}
		}
		return (false);
	}

	void Hscroll_bar::move(Vector2 delta)
	{

	}

	void Hscroll_bar::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
	{
		_viewport->resize(p_anchor, p_area);
		Vector2 button_size = Vector2(p_area.y, p_area.y);
		Vector2 scroll_size = Vector2(p_area.x - button_size.x * 2, p_area.y);
		Vector2 anchor[3] = {
			0,
			p_area - button_size,
			Vector2(button_size.x, 0.0f)
		};

		left_button->set_geometry(anchor[0], button_size);
		right_button->set_geometry(anchor[1], button_size);
		scroll_bar->set_geometry(anchor[2], scroll_size);
	}

	void Hscroll_bar::render()
	{

	}
}
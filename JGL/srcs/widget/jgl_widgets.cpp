#include "jgl.h"


namespace jgl
{
	Widget::Widget(Widget* p_parent)
	{
		_childrens.clear();
		_parent = nullptr;
		set_parent(p_parent);
		_viewport = new Viewport();
		_viewport->set_owner(this);
		_activated = false;
		_frozen = false;
		_layer = -1;
		if (_parent != nullptr)
		{
			_layer = _parent->layer() + 1;
		}
	}

	void Widget::destroy_widget()
	{
		for (uint32_t i = 0; i < _childrens.size(); i++)
		{
			_childrens[i]->destroy_widget();
			delete _childrens[i];
		}
	}

	void Widget::remove_children(Widget* p_target)
	{
		auto it = find(_childrens.begin(), _childrens.end(), p_target);

		if (it != _childrens.end())
			_childrens.erase(it);
	}

	void Widget::set_geometry(Vector2 p_anchor, Vector2 p_area)
	{
		_viewport->resize(p_anchor, p_area);
		set_geometry_imp(p_anchor, p_area);
	}

	void Widget::set_parent(Widget* p_parent)
	{
		if (_parent != nullptr)
			_parent->remove_children(this);

		if (p_parent != nullptr)
			_parent = p_parent;
		else
			_parent = g_application->central_widget();

		if (_parent != nullptr)
			_parent->add_children(this);
	}

	bool Widget::handle_event()
	{
		if (is_active() == false || area() == -1 || is_frozen() == true)
			return (false);

		for (uint32_t i = 0; i < _childrens.size(); i++)
			if (_childrens[i]->handle_event() == true)
				return (true);

		bool key = handle_keyboard();
		bool mouse = handle_mouse();

		if (key == true || mouse == true)
			return (true);
		return (false);
	}

	bool Widget::is_pointed(Vector2 point)
	{
		Vector2 pos1, pos2;

		pos1 = anchor();

		pos2 = pos1 + _viewport->area();
		if (point.x < pos1.x || point.x > pos2.x || point.y < pos1.y || point.y > pos2.y)
			return (false);
		return (true);
	}

	void Widget::render_children()
	{
		if (is_active() == false)
			return;

		if (parent() != nullptr)
			parent()->viewport()->use();
		else
			g_application->viewport()->use();

		render();

		for (int i = 0; i < _childrens.size(); i++)
		{
			_childrens[i]->render_children();
		}
	}

	void Widget::update_children()
	{
		if (is_active() == false)
			return;

		update();

		for (uint32_t i = 0; i < _childrens.size(); i++)
		{
			if (_childrens[i]->is_frozen() == false)
				_childrens[i]->update_children();
		}
	}

	void Widget::quit_children()
	{
		if (is_active() == false)
			return;

		quit();

		for (uint32_t i = 0; i < _childrens.size(); i++)
		{
			_childrens[i]->quit_children();
		}
	}

	void Widget::raise()
	{
		_layer++;
	}

	void Widget::lower()
	{
		_layer--;
	}

	void Widget::set_layer(float index)
	{
		_layer = index;
	}
}
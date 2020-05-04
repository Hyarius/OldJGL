#include "jgl.h"


namespace jgl
{
	Widget::Widget(Widget* p_parent)
	{
		_childrens.clear();
		_parent = nullptr;
		set_parent(p_parent);
		_viewport = new Viewport();
		_activated = false;
	}

	Widget::~Widget()
	{
		if (_parent != nullptr)
			_parent->remove_children(this);

		for (size_t i = 0; i < _childrens.size(); i++)
		{
			delete _childrens[i];
		}
	}

	void Widget::remove_children(Widget* p_target)
	{
		std::vector<Widget*>::iterator it;

		it = find(_childrens.begin(), _childrens.end(), p_target);

		if (it != _childrens.end())
			_childrens.erase(it);
	}

	void Widget::set_geometry(Vector2 p_anchor, Vector2 p_area)
	{
		if (_parent == nullptr)
			_viewport->resize(p_anchor, p_area);
		else
			_viewport->resize(p_anchor + _parent->anchor(), p_area);

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
		if (is_active() == false || area() == -1)
			return (false);

		for (size_t i = 0; i < _childrens.size(); i++)
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

		pos1 = _viewport->anchor();

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
			g_application->viewport()->reset();

		render();

		for (size_t i = 0; i < _childrens.size(); i++)
		{
			_childrens[i]->render_children();
		}
	}

	void Widget::update_children()
	{
		if (is_active() == false)
			return;

		update();

		for (size_t i = 0; i < _childrens.size(); i++)
		{
			_childrens[i]->update_children();
		}
	}

	void Widget::quit_children()
	{
		if (is_active() == false)
			return;

		quit();

		for (size_t i = 0; i < _childrens.size(); i++)
		{
			_childrens[i]->quit_children();
		}
	}
}
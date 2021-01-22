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
	}

	void Widget::destroy_widget()
	{
		for (size_t i = 0; i < _childrens.size(); i++)
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

		for (int i = _childrens.size() - 1; i >= 0; i--)
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
			if (_childrens[i]->is_frozen() == false)
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
	void Widget::send_front()
	{
		if (_parent == nullptr)
			return;

		std::vector<Widget*>& children_list = _parent->childrens();

		if (children_list.size() <= 1)
			return;

		std::cout << "Send front " << this << " in fonction " << __FUNCTION__ << std::endl;
		for (size_t i = 0; i < children_list.size(); i++)
		{
			std::cout << "[" << i << "] " << children_list[i] << std::endl;
		}
		std::cout << std::endl;

		auto tmp = std::find(children_list.begin(), children_list.end(), this);
		children_list.erase(tmp);
		children_list.insert(children_list.begin(), this);

		for (size_t i = 0; i < children_list.size(); i++)
		{
			std::cout << "[" << i << "] " << children_list[i] << std::endl;
		}
		std::cout << std::endl;
	}

	void Widget::send_back()
	{
		if (_parent == nullptr)
			return;
		std::vector<Widget*>& children_list = _parent->childrens();

		auto tmp = std::find(children_list.begin(), children_list.end(), this);
		children_list.erase(tmp);
		children_list.insert(children_list.end(), this);
	}

	void Widget::raise()
	{
		if (_parent == nullptr)
			return;
		std::vector<Widget*>& children_list = _parent->childrens();

		auto tmp = std::find(children_list.begin(), children_list.end(), this);
		if (tmp == children_list.end() || *tmp == children_list.back())
			return;
		auto tmp2 = tmp + 1;
		jgl::Widget* other = *tmp2;
		*tmp2 = this;
		*tmp = *tmp2;
	}

	void Widget::lower()
	{
		if (_parent == nullptr)
			return;
		std::vector<Widget*>& children_list = _parent->childrens();

		auto tmp = std::find(children_list.begin(), children_list.end(), this);
		if (tmp == children_list.end() || tmp == children_list.begin())
			return;
		auto tmp2 = tmp - 1;
		jgl::Widget* other = *tmp2;
		*tmp2 = this;
		*tmp = *tmp2;
	}

	void Widget::set_layer(size_t index)
	{
		if (_parent == nullptr || _parent->childrens().size() >= index)
			return;
		std::vector<Widget*>& children_list = _parent->childrens();

		auto tmp = std::find(children_list.begin(), children_list.end(), this);
		if (tmp == children_list.end())
			return;
		jgl::Widget* other = children_list[index];
		children_list[index] = this;
		*tmp = other;
	}
}
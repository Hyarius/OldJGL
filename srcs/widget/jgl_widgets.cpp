#include "jgl.h"

using namespace std;

c_widget::c_widget(c_widget *p_parent)
{
	_childrens.clear();
	_parent = nullptr;
	set_parent(p_parent);
	_viewport = new c_viewport();
	_activated = false;
}

c_widget::~c_widget()
{
	if (_parent != nullptr)
		_parent->remove_children(this);

	for (size_t i = 0; i < _childrens.size(); i++)
	{
		delete _childrens[i];
	}
}

void c_widget::remove_children(c_widget *p_target)
{
	std::vector<c_widget *>::iterator it;

	it = find (_childrens.begin(), _childrens.end(), p_target);

  	if (it != _childrens.end())
    	_childrens.erase (it);
}

void c_widget::set_geometry(Vector2 p_anchor, Vector2 p_area)
{
	if (_parent == nullptr)
		_viewport->resize(p_anchor, p_area);
	else
		_viewport->resize(p_anchor + _parent->anchor(), p_area);

	set_geometry_imp(p_anchor, p_area);
}

void c_widget::set_parent(c_widget *p_parent)
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

bool c_widget::handle_event()
{
	if (is_active() == false)
		return (false);

	for (int i = _childrens.size() - 1; i >= 0; i--)
		if (_childrens[i]->handle_event() == true)
			return (true);

	bool key = handle_keyboard();
	bool mouse = handle_mouse();

	if (key == true || mouse == true)
		return (true);
	return (false);
}

bool c_widget::is_pointed(Vector2 point)
{
	c_widget *tmp;
	Vector2 pos1, pos2;

	pos1 = _viewport->anchor();

	pos2 = pos1 + _viewport->area();
	if (point.x < pos1.x || point.x > pos2.x || point.y < pos1.y || point.y > pos2.y)
		return (false);
	return (true);
}

void c_widget::render_children()
{
	if (is_active() == false)
		return ;

	render();

	if (_viewport->active() == true)
		_viewport->use();

	for (size_t i = 0; i < _childrens.size(); i++)
	{
		_childrens[i]->render_children();
	}

	if (_viewport->active() == true)
		_viewport->unuse();
}

void c_widget::update_children()
{
	if (is_active() == false)
		return ;

	//cout << "Here" << endl;
	update();

	for (size_t i = 0; i < _childrens.size(); i++)
	{
		_childrens[i]->update_children();
	}
}

void c_widget::quit_children()
{
	if (is_active() == false)
		return ;

	quit();

	for (size_t i = 0; i < _childrens.size(); i++)
	{
		_childrens[i]->quit_children();
	}
}

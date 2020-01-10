#include "jgl.h"

c_viewport::c_viewport(Color p_color, Vector2 p_anchor, Vector2 p_area)
{
	if (g_application == nullptr)
		g_application = new c_application("Main window");

	_active = false;
	_context = g_application->context();
	_background = p_color;

	set_viewport(p_anchor, p_area);
}

void c_viewport::set_viewport(Vector2 p_anchor, Vector2 p_area)
{
	_anchor = p_anchor;
	_area = p_area;

	if (_anchor == Vector2())
		_anchor = Vector2(0, 0);
	if (_area == Vector2())
		_area = g_application->size();
}

void c_viewport::resize(Vector2 p_anchor, Vector2 p_area)
{
	_anchor = p_anchor;
	_area = p_area;
}

void c_viewport::use()
{
	g_application->set_active_viewport(this);
	glViewport(static_cast<int>(_anchor.x), static_cast<int>(g_application->size().y - _anchor.y - _area.y),
	static_cast<int>(_area.x), static_cast<int>(_area.y));
}

void c_viewport::reset()
{
	g_application->reset_viewport();
}

void c_viewport::set_Color(Color p_color)
{
	//glClearColor((GLclampf)p_color.r, (GLclampf)p_color.g, (GLclampf)p_color.b, 0.0f);
	//SDL_SetRenderDrawColor(_renderer, Color.r * 255, Color.g * 255, Color.b * 255, Color.a * 255);
}

void c_viewport::clear()
{
	// use();
	// set_Color(_background);
	//glClear(GL_DEPTH_BUFFER_BIT);
}

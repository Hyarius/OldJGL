#include "jgl.h"

namespace jgl
{
	Viewport::Viewport(Color p_color, Vector2 p_anchor, Vector2 p_area)
	{
		if (g_application == nullptr)
			g_application = new Application("Main window");

		_active = false;
		_context = g_application->context();
		_background = p_color;

		set_viewport(p_anchor, p_area);
	}

	void Viewport::set_viewport(Vector2 p_anchor, Vector2 p_area)
	{
		_anchor = p_anchor;
		_area = p_area;

		if (_anchor == Vector2())
			_anchor = Vector2(0, 0);
		if (_area == Vector2())
			_area = g_application->size();
	}

	void Viewport::resize(Vector2 p_anchor, Vector2 p_area)
	{
		_anchor = p_anchor;
		_area = p_area;
	}

	void Viewport::use()
	{
		g_application->set_active_viewport(this);
		glClear(GL_DEPTH_BUFFER_BIT);
		glViewport(static_cast<int>(_anchor.x), static_cast<int>(g_application->size().y - _anchor.y - _area.y),
			static_cast<int>(_area.x), static_cast<int>(_area.y));
	}

	void Viewport::reset()
	{
		g_application->reset_viewport();
	}

	void Viewport::set_Color(Color p_color)
	{
		//glClearColor((GLclampf)p_color.r, (GLclampf)p_color.g, (GLclampf)p_color.b, 0.0f);
		//SDL_SetRenderDrawColor(_renderer, Color.r * 255, Color.g * 255, Color.b * 255, Color.a * 255);
	}

	void Viewport::clear()
	{
		// use();
		// set_Color(_background);
		//glClear(GL_DEPTH_BUFFER_BIT);
	}
}
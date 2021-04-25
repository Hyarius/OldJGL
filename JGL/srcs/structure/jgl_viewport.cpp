#include "jgl.h"

namespace jgl
{
	Viewport::Viewport(Color p_color, Vector2 p_anchor, Vector2 p_area, class jgl::Widget* p_owner)
	{
		if (g_application == nullptr)
			g_application = new Application("Main window");

		if (p_owner == nullptr)
			_owner = g_application->central_widget();
		else
			_owner = p_owner;

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

	void Viewport::use() const
	{
		if (g_application->active_viewport() == this)
			return;

		g_application->set_active_viewport(this);
		//glClear(GL_DEPTH_BUFFER_BIT);
		
		jgl::Vector2 pos, size;
		jgl::Vector2 tmp;

		size = _area;
		tmp = (_owner != nullptr ? _owner->anchor() : 0);
		pos = jgl::Vector2(tmp.x, g_application->size().y - _area.y - tmp.y);

		g_application->take_context_control();
		glViewport(static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(size.x), static_cast<int>(size.y));
		//glScissor(static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(size.x), static_cast<int>(size.y));
		g_application->release_context_control();
	}

	void Viewport::reset() const
	{
		g_application->reset_viewport();
	}

	void Viewport::set_Color(const Color p_color)
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

	const Vector2 Viewport::cumuled_anchor() const
	{
		if (_owner == nullptr)
			return(_anchor);
		return (_owner->anchor());
	}
}
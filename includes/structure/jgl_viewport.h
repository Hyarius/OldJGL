#ifndef JGL_VIEWPORT_H
#define JGL_VIEWPORT_H

#include "jgl_includes.h"
#include "jgl_vector.h"
#include "jgl_color.h"
#include "jgl_system.h"
#include "jgl_geometry.h"

namespace jgl
{
	class Viewport
	{
	protected:
		SDL_GLContext* _context;
		Color _background;
		bool _active;
		Vector2 _anchor;
		Vector2 _area;
		Rect _old_viewport;

	public:
		Viewport(Color p_color = Color(), Vector2 p_anchor = Vector2(), Vector2 p_size = Vector2());

		void set_anchor(Vector2 p_anchor) { _anchor = p_anchor; }
		void set_area(Vector2 p_area) { _area = p_area; }
		void set_viewport(Vector2 p_anchor = Vector2(), Vector2 p_area = Vector2());

		void set_active(bool p_active) { _active = p_active; }

		void resize(Vector2 p_anchor, Vector2 p_area);

		void set_background(Color p_color = Color(50, 50, 50)) { _background = p_color; }

		void use();
		void reset();

		void set_Color(Color Color);

		void clear();

		bool active() { return (_active); }
		Vector2& area() { return (_area); }
		Vector2& anchor() { return (_anchor); }
		SDL_GLContext* context() { return (_context); }
		Color background() { return (_background); }
	};
}

#endif

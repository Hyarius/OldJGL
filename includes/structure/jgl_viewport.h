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
		const class Widget* _owner;
		SDL_GLContext* _context;
		Color _background;
		bool _active;
		Vector2 _anchor;
		Vector2 _area;
		Rect _old_viewport;

	public:
		Viewport(Color p_color = Color(), Vector2 p_anchor = Vector2(), Vector2 p_size = Vector2(), class jgl::Widget *p_owner = nullptr);

		void set_owner(class Widget* p_owner) { _owner = p_owner; }
		void set_anchor(Vector2 p_anchor) { _anchor = p_anchor; }
		void set_area(Vector2 p_area) { _area = p_area; }
		void set_viewport(Vector2 p_anchor = Vector2(), Vector2 p_area = Vector2());

		void set_active(bool p_active) { _active = p_active; }

		void resize(Vector2 p_anchor, Vector2 p_area);

		void set_background(Color p_color = Color(50, 50, 50)) { _background = p_color; }

		void use() const;
		void reset() const;

		void set_Color(Color Color);

		void clear();

		const bool active() const { return (_active); }
		const Vector2 area() const  { return (_area); }
		const Vector2 anchor() const  { return (_anchor); }
		const Vector2 cumuled_anchor() const;
		const SDL_GLContext* context() const { return (_context); }
		const Color background() const { return (_background); }
	};
}

#endif

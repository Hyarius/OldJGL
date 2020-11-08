#ifndef C_WINDOW_H
#define C_WINDOW_H

#include "jgl_widgets.h"

namespace jgl
{
	class Window : public Widget
	{
	protected:
		Color back;

	public:
		Window(Widget* p_parent = NULL,
			Color p_back = Color(220, 220, 220));

		void set_color(Color p_color);
		void move(Vector2 delta) {};

		void set_geometry_imp(Vector2 p_anchor, Vector2 p_area) {}

		virtual void render();

		virtual bool handle_keyboard();

		virtual bool handle_mouse();
	};
}

#endif

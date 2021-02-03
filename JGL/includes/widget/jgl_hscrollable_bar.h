#ifndef JGL_HSCROLLABLE_BAR_H
#define JGL_HSCROLLABLE_BAR_H

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

namespace jgl
{
	class Hscroll_bar : public Widget
	{
	protected:
		Vector2 _actual_pos;
		Vector2 _min_pos;
		Vector2 _max_pos;
		Frame* scroll_bar;
		Button* left_button;
		Button* right_button;

	public:
		Hscroll_bar(Widget* p_parent);

		void set_min_pos(Vector2 p_min) { _min_pos = p_min; }
		void set_max_pos(Vector2 p_max) { _max_pos = p_max; }
		Vector2 actual_pos() { return (_actual_pos); }
		void move_pos(Vector2 delta);
		Vector2 min_pos() { return (_min_pos); }
		Vector2 max_pos() { return (_max_pos); }

		bool handle_keyboard();
		bool handle_mouse();
		void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);
		void move(Vector2 delta);
		void render();
	};
}
#endif
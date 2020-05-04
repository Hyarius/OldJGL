#ifndef JGL_VSCROLLABLE_BAR_H
#define JGL_VSCROLLABLE_BAR_H

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

namespace jgl
{
	class Vscroll_bar : public Widget
	{
	protected:
		Frame* scroll_bar;
		Button* up_button;
		Button* down_button;

	public:
		Vscroll_bar(Widget* p_parent);

		~Vscroll_bar();

		bool handle_mouse();
		void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);
		void move(Vector2 delta);
		void render();
	};
}
#endif

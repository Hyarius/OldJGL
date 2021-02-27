#ifndef JGL_TAB_H
#define JGL_TAB_H

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

namespace jgl
{
	class Tab : public Widget
	{
	protected:
		std::vector<Frame*> _tabs;
		std::vector<Button*> _buttons;

		Frame* tab_area;
		Frame* button_area;

	public:
		Tab(Widget* p_parent = nullptr);

		std::vector<Frame*> tabs() { return (_tabs); }
		std::vector<Button*> buttons() { return (_buttons); }

		Frame* add_tab(jgl::String p_name, int index = -1);
		void reset_size();
		void reset_tab();
		void reset_button();

		int border() { return (tab_area->border()); }

		void set_tab_name(uint32_t index, jgl::String new_name)
		{
			_buttons[index]->set_text(new_name);
		}

		void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);
		void move(Vector2 delta);

		void render();

		bool handle_mouse();

		bool handle_keyboard();
	};
}
#endif

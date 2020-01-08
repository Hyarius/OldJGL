#ifndef JGL_TAB_H
#define JGL_TAB_H

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

class c_tab : public c_widget
{
private:
	vector<c_frame *> _tabs;
	vector<c_button *> _buttons;

	c_frame *tab_area;
	c_frame *button_area;

public:
	c_tab(c_widget *p_parent = nullptr);

	vector<c_frame *> tabs(){return (_tabs);}
	vector<c_button *> buttons(){return (_buttons);}

	c_frame *add_tab(string p_name, int index = -1);
	void reset_size();
	void reset_tab();
	void reset_button();

	int border(){return (tab_area->border());}

	void set_tab_name(size_t index, string new_name)
			{_buttons[index]->set_text(new_name);}

	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);
	void move(Vector2 delta);

	void render();

	bool handle_mouse();

	bool handle_keyboard();
};

#endif

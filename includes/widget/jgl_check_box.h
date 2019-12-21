#ifndef JGL_CHECK_BOX_H
#define JGL_CHECK_BOX_H

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

class c_check_box : public c_widget
{
private:
	w_box_component _box;
	w_check_component _check;
	w_text_component _label;

public:
	c_check_box(string p_text = "- Value -", bool p_state = false, c_widget *p_parent = nullptr);
	~c_check_box();

	w_box_component &box(){return (_box);}
	w_check_component &check(){return (_check);}
	w_text_component &label(){return (_label);}
	void move(Vector2 delta);

	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);

	void render();

	bool handle_mouse();

	bool handle_keyboard();
};

#endif

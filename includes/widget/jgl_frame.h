#ifndef JGL_FRAME_H
#define JGL_FRAME_H

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

class c_frame : public c_widget
{
private:
	w_box_component _box;

public:
	c_frame(c_widget *p_parent = nullptr);

	~c_frame();

	w_box_component &box(){return (_box);}
	void move(Vector2 delta);

	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);

	void render();

	bool handle_mouse();

	bool handle_keyboard();
};

#endif

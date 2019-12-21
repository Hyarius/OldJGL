#ifndef JGL_VALUE_LABEL_H
#define JGL_VALUE_LABEL_H

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

class c_value_label : public c_widget
{
private:
	w_box_component _box;
	w_value_component _label;

public:
	c_value_label(float p_value = 0.0f, c_widget *p_parent = nullptr);
	~c_value_label();

	float value(){return (_label.value());}

	w_box_component &box(){return (_box);}
	w_value_component &label(){return (_label);}

	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);
	void move(Vector2 delta);

	void render();

	bool handle_mouse();

	bool handle_keyboard();
};

#endif

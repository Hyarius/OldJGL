#ifndef JGL_TEXT_LABEL_H
#define JGL_TEXT_LABEL_H

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

class c_text_label : public c_widget
{
private:
	w_box_component _box;
	w_text_component _label;

public:
	c_text_label(string p_text = "", c_widget *p_parent = nullptr);
	~c_text_label();

	string text(){return (_label.text());}

	w_box_component &box(){return (_box);}
	w_text_component &label(){return (_label);}

	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);
	void move(Vector2 delta);

	void render();

	bool handle_mouse();

	bool handle_keyboard();
};

#endif

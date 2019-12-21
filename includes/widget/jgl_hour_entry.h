#ifndef JGL_HOUR_ENTRY_H
#define JGL_HOUR_ENTRY_H

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

class c_hour_entry : public c_widget
{
private:
	w_box_component _box;
	w_text_component _label;
	w_value_entry_component _hour;
	w_value_entry_component _minute;

	w_value_entry_component *_entry;

	bool _selected;
	Uint32 _next_input;
	Uint32 _input_delay;

public:
	c_hour_entry(float p_hour = 12.0f, float p_minute = 0.0f, c_widget *p_parent = nullptr);

	~c_hour_entry();

	void select();
	void unselect();

	void round();

	int value(){return (_hour.value() * 60 + _minute.value());}

	bool selected(){return (_selected);}
	w_box_component &box(){return (_box);}
	w_text_component &label(){return (_label);}
	w_value_entry_component &hour(){return (_hour);}
	w_value_entry_component &minute(){return (_minute);}

	void set_selected(bool p_selected){_selected = p_selected;}
	void set_box(w_box_component new_box){_box = new_box;}
	void set_label(w_text_component new_label){_label = new_label;}
	void set_hour(w_value_entry_component new_hour){_hour = new_hour;}
	void set_minute(w_value_entry_component new_minute){_minute = new_minute;}


	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);
	void move(Vector2 delta);

	void render();

	bool handle_mouse();

	bool handle_keyboard();
};

#endif

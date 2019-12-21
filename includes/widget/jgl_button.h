#ifndef JGL_BUTTON_H
#define JGL_BUTTON_H

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

class c_button : public c_widget
{
private:
	w_box_component _box;
	w_text_component _text;

	Funct _funct;
	Color _delta;
	Data _data;
	int _timer;
	int _timer_delta;

	bool _repeat_click;

public:
	c_button(Funct p_funct = nullptr, Data p_data = nullptr, c_widget *p_parent = nullptr);
	~c_button();

	w_box_component &box(){return (_box);}
	w_text_component &text(){return (_text);}

	void set_action(Funct p_funct, Data p_data)
	{
		_funct = p_funct;
		_data = p_data;
	}

	void set_repeat(bool p_repeat){_repeat_click = p_repeat;}
	void set_funct(Funct p_funct){_funct = p_funct;}
	void set_data(Data p_data){_data = p_data;}
	void set_delta(Color p_delta){_delta = p_delta;}
	void move(Vector2 delta);
	void set_timer_delta(int p_timer_delta){_timer_delta = p_timer_delta;}

	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);

	void render();

	bool handle_mouse();

	bool handle_keyboard();
};

#endif

#ifndef JGL_BUTTON_H
#define JGL_BUTTON_H

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

class c_button : public c_widget
{
private:
	w_box_component _box;
	w_text_component _label;

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
	w_text_component &label(){return (_label);}

	// - box redirection function
	void set_tileset(c_tileset *p_tileset){_box.set_tileset(p_tileset);}
	void set_tileset(string path){_box.set_tileset(new c_tileset(path, 3));}
	void set_back(Color p_back){_box.set_back(p_back);}
	void set_front(Color p_front){_box.set_front(p_front);}
	void set_border(int p_border){_box.set_border(p_border);}
	c_tileset *tileset(){return (_box.tileset());}
	int border(){return (_box.border());}
	Color back(){return (_box.back());}
	Color front(){return (_box.front());}

	// - label redirection function
	void 		set_text(string p_text){_label.set_text(p_text);}
	void 		set_align(alignment p_align){_label.set_align(p_align);}
	void 		set_size(int p_size){_label.set_size(p_size);}
	void 		set_color(text_color p_color){_label.set_color(p_color);}
	void 		set_style(text_style p_style){_label.set_style(p_style);}
	string 		text(){return (_label.text());}
	alignment 	align(){return (_label.align());}
	int 		size(){return (_label.size());}
	text_color 	color(){return (_label.color());}
	text_style 	style(){return (_label.style());}

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

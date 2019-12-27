#ifndef JGL_CHECK_ENTRY_H
#define JGL_CHECK_ENTRY_H

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

class c_check_entry : public c_widget
{
private:
	w_box_component _box;
	w_check_component _check;
	w_text_entry_component _entry;

public:
	c_check_entry(string p_text = "- Value -", bool p_state = false, c_widget *p_parent = nullptr);
	~c_check_entry();

	w_box_component &box(){return (_box);}
	w_check_component &check(){return (_check);}
	w_text_entry_component &entry(){return (_entry);}

	// - box redirection function
	void set_tileset(c_tileset *p_tileset){_box.set_tileset(p_tileset);}
	void set_back(Color p_back){_box.set_back(p_back);}
	void set_front(Color p_front){_box.set_front(p_front);}
	void set_border(int p_border){_box.set_border(p_border);}
	c_tileset *tileset(){return (_box.tileset());}
	int border(){return (_box.border());}
	Color back(){return (_box.back());}
	Color front(){return (_box.front());}

	// - entry redirection function
	void 		set_text(string p_text){_entry.set_text(p_text);}
	void 		set_align(alignment p_align){_entry.set_align(p_align);}
	void 		set_size(int p_size){_entry.set_size(p_size);}
	void 		set_color(text_color p_color){_entry.set_color(p_color);}
	void 		set_style(text_style p_style){_entry.set_style(p_style);}
	string 		text(){return (_entry.text());}
	alignment 	align(){return (_entry.align());}
	int 		size(){return (_entry.size());}
	text_color 	color(){return (_entry.color());}
	text_style 	style(){return (_entry.style());}

		//Setter
	void set_state(bool p_state){_check.set_state(p_state);}
	void set_check_border(int p_border){_check.set_border(p_border);}
	void set_check_back(Color p_back){_check.set_back(p_back);}
	void set_check_front(Color p_front){_check.set_front(p_front);}
	void set_check_check(Color p_check){_check.set_check(p_check);}
	bool state(){return (_check.state());}
	int check_border(){return (_check.border());}
	Color check_back(){return (_check.back());}
	Color check_front(){return (_check.front());}
	Color check_check(){return (_check.check());}

	void move(Vector2 delta);

	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);

	void render();

	bool handle_mouse();

	bool handle_keyboard();
};

#endif

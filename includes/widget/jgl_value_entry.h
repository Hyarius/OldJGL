#ifndef JGL_VALUE_ENTRY
#define JGL_VALUE_ENTRY

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

class c_value_entry : public c_widget
{
private:
	w_box_component _box;
	w_value_entry_component _entry;

	bool _select;
	long _next_input;
	long _input_delay;

public:
	c_value_entry(float p_value = 0.001f, c_widget *p_parent = nullptr);
	~c_value_entry();

	w_box_component &box(){return (_box);}
	w_value_entry_component &entry(){return (_entry);}

	// - box redirection function
	void set_tileset(c_tileset *p_tileset){_box.set_tileset(p_tileset);}
	void set_tileset(string path){_box.set_tileset(new c_tileset(path, 3));}
	void set_image(c_tileset *p_image){_box.set_image(p_image);}
	void set_image(c_image *p_image){_box.set_image(new c_tileset(p_image));}
	void set_image(string path){_box.set_image(new c_tileset(path, 1));}
	void set_back(Color p_back){_box.set_back(p_back);}
	void set_front(Color p_front){_box.set_front(p_front);}
	void set_border(int p_border){_box.set_border(p_border);}
	void set_sprite(int p_sprite){_box.set_sprite(p_sprite);}
	void set_corner_size(size_t p_corner_size){_box.set_corner_size(p_corner_size);}
	int sprite(){return (_box.sprite());}
	size_t corner_size(){return (_box.corner_size());}
	c_tileset *tileset(){return (_box.tileset());}
	c_tileset *image(){return (_box.image());}
	int border(){return (_box.border());}
	Color back(){return (_box.back());}
	Color front(){return (_box.front());}

	void 		set_selected(bool p_selected){_entry.set_selected(p_selected);}
	void 		set_precision(int p_precision){_entry.set_precision(p_precision);}
	void 		set_text(string p_text){_entry.set_text(p_text);}
	void 		set_value(float p_value){_entry.set_value(p_value);}
	void 		set_cursor(int p_cursor){_entry.set_cursor(p_cursor);}
	bool		selected(){return (_entry.selected());}
	int			precision(){return (_entry.precision());}
	float 		value(){return (_entry.value());}
	string 		text(){return (_entry.text());}
	int 		cursor(){return (_entry.cursor());}

	void 		set_align(alignment p_align){_entry.set_align(p_align);}
	void 		set_size(int p_size){_entry.set_size(p_size);}
	void 		set_color(text_color p_color){_entry.set_color(p_color);}
	void 		set_style(text_style p_style){_entry.set_style(p_style);}

	alignment 	align(){return (_entry.align());}
	int 		size(){return (_entry.size());}
	text_color 	color(){return (_entry.color());}
	text_style 	style(){return (_entry.style());}

	void select(){_entry.set_selected(true);}
	void unselect(){_entry.set_selected(false);}

	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);
	void move(Vector2 delta);

	void render();

	bool handle_mouse();

	bool handle_keyboard();
};

#endif

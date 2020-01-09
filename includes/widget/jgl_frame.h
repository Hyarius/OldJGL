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

	void move(Vector2 delta);

	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);

	void render();

	bool handle_mouse();

	bool handle_keyboard();
};

#endif

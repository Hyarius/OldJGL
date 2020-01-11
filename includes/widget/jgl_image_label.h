#ifndef JGL_IMAGE_LABEL_H
#define JGL_IMAGE_LABEL_H

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

class c_image_label : public c_widget
{
private:
	w_box_component _box;

public:
	c_image_label(string path, c_widget *p_parent = nullptr);
	c_image_label(c_image *image = nullptr, c_widget *p_parent = nullptr);
	c_image_label(c_tileset *image, c_widget *p_parent = nullptr);
	~c_image_label();

	w_box_component &box(){return (_box);}

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
	int sprite(){return (_box.sprite());}
	c_tileset *tileset(){return (_box.tileset());}
	c_tileset *image(){return (_box.image());}
	int border(){return (_box.border());}
	Color back(){return (_box.back());}
	Color front(){return (_box.front());}

	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);
	void move(Vector2 delta);

	void render();

	bool handle_mouse();

	bool handle_keyboard();
};

#endif

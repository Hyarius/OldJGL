#ifndef JGL_TEXT_ENTRY
#define JGL_TEXT_ENTRY

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

class c_text_entry : public c_widget
{
private:
	w_box_component _box;
	w_text_entry_component _entry;

	bool _select;
	Uint32 _next_input;
	Uint32 _input_delay;

public:
	c_text_entry(string p_text = "", c_widget *p_parent = nullptr);
	~c_text_entry();

	string text(){return (_entry.text());}

	w_box_component &box(){return (_box);}
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

	void		set_text(string p_text){_entry.set_text(p_text);}
	void 		set_selected(bool p_selected){_entry.set_selected(p_selected);}
	bool		selected(){return (_entry.selected());}
	int 		cursor(){return (_entry.cursor());}

	void select(){_entry.set_selected(true);}
	void unselect(){_entry.set_selected(false);}

	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);
	void move(Vector2 delta);

	void render();

	bool handle_mouse();

	bool handle_keyboard();
};

#endif

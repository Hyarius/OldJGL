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

	void select(){_select = true;_entry.set_selected(true);}
	void unselect(){_select = false;_entry.set_selected(false);}
	bool selected(){return (_select);}

	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);
	void move(Vector2 delta);

	void render();

	bool handle_mouse();

	bool handle_keyboard();
};

#endif

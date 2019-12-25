#ifndef C_WIDGETS_H
#define C_WIDGETS_H

typedef 			void(*Funct)(Data);

using namespace std;

class c_widget
{
protected:
	c_widget *_parent;
	vector<c_widget *> _childrens;
	c_viewport *_viewport;
	bool _activated;

public:
	c_widget(c_widget *p_parent = nullptr);
	virtual ~c_widget();

	vector<c_widget *> childrens(){return (_childrens);}
	c_widget *parent(){return (_parent);}
	Vector2 area(){return (_viewport->area());}
	Vector2 anchor(){return (_viewport->anchor());}
	c_viewport *viewport(){return (_viewport);}

	bool is_active(){return (_activated);}
	bool is_pointed(Vector2 point);
	void activate(){_activated = true;}
	void desactivate(){_activated = false;}
	void set_active(bool new_state){_activated = new_state;}
	void set_parent(c_widget *p_parent);
	void add_children(c_widget *p_children){_childrens.push_back(p_children);}
	void remove_children(c_widget *p_target);
	bool handle_event();
	void update_children();
	void render_children();
	void quit_children();
	void set_anchor(Vector2 p_anchor){_viewport->set_anchor(p_anchor);}
	void set_area(Vector2 p_area){_viewport->set_area(p_area);}
	virtual void set_geometry(Vector2 p_anchor, Vector2 p_area);
	virtual void move(Vector2 delta){cout << "Warning : Need creation of a function void move(Vector2) in your new widget to allow scroll_bar to work on it" << endl;}

	virtual void quit(){};
	virtual void update(){};
	virtual bool handle_keyboard(){return (false);}
	virtual bool handle_mouse(){return (false);}

	virtual void set_geometry_imp(Vector2 p_anchor, Vector2 p_area) = 0;
	virtual void render() = 0;
};

#endif

#ifndef JGL_VSCROLLABLE_BAR_H
#define JGL_VSCROLLABLE_BAR_H

class c_vscroll_bar : public c_widget
{
private:
	c_frame *scroll_bar;
	c_button *up_button;
	c_button *down_button;

public:
	c_vscroll_bar(c_widget *p_parent);

	~c_vscroll_bar();

	bool handle_mouse();
	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);
	void move(Vector2 delta);
	void render();
};

#endif

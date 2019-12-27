#ifndef JGL_WIDGET_COMPONENT_H
#define JGL_WIDGET_COMPONENT_H

class w_component
{
protected:
	class c_widget *_owner;

	Vector2 _anchor;
	Vector2 _area;

public:
	w_component(class c_widget *p_owner);

	~w_component();

	void 		set_anchor(Vector2 p_anchor){_anchor = p_anchor;}
	void 		set_area(Vector2 p_area){_area = p_area;}
	void 		resize(Vector2 p_anchor, Vector2 p_area)
					{set_anchor(p_anchor);set_area(p_area);}
	Vector2 	anchor(){return (_anchor);}
	Vector2 	area(){return (_area);}
	Vector2		owner_anchor();

	bool is_pointed(Vector2 point);

	virtual void render(c_viewport *viewport = nullptr) = 0;
};

class w_graphical_component
{
protected:
	c_tileset *_tileset;
	Color _back;
	Color _front;
	int _border;

public:
	w_graphical_component();

	void set_tileset(c_tileset *p_tileset){_tileset = p_tileset;}
	void set_back(Color p_back){_back = p_back;}
	void set_front(Color p_front){_front = p_front;}
	void set_border(int p_border){_border = p_border;}

		//Getter
	c_tileset *tileset(){return (_tileset);}
	int border(){return (_border);}
	Color back(){return (_back);}
	Color front(){return (_front);}
};

class w_textual_component
{
protected:
	string _text;
	int _size;
	alignment _align;
	text_color _color;
	text_style _style;
public:

	w_textual_component();

	void 		set_text(string p_text){_text = p_text;}
	void 		set_align(alignment p_align){_align = p_align;}
	void 		set_size(int p_size){_size = p_size;}
	void 		set_color(text_color p_color){_color = p_color;}
	void 		set_style(text_style p_style){_style = p_style;}

	void 		calc_text_size(Vector2 area);
	void 		calc_text_size_height(Vector2 area);

	string 		text(){return (_text);}
	alignment 	align(){return (_align);}
	int 		size(){return (_size);}
	text_color 	color(){return (_color);}
	text_style 	style(){return (_style);}
};

class w_text_component : public w_component, public w_graphical_component, public w_textual_component
{
public:
	w_text_component(class c_widget *p_owner = nullptr, string p_text = "");

	void 		resize(Vector2 p_anchor, Vector2 p_area);

	void render(c_viewport *viewport = nullptr);
};

class w_check_component : public w_component, public w_graphical_component
{
protected:
	bool _state;
	Color _back;
	Color _front;
	Color _check;
	int _border;

public:
		//Constructor
	w_check_component(class c_widget *p_owner = nullptr, bool p_state = false);

		//Setter
	void set_state(bool p_state){_state = p_state;}
	void set_border(int p_border){_border = p_border;}
	void set_back(Color p_back){_back = p_back;}
	void set_front(Color p_front){_front = p_front;}
	void set_check(Color p_check){_check = p_check;}

		//Getter
	bool state(){return (_state);}
	int border(){return (_border);}
	Color back(){return (_back);}
	Color front(){return (_front);}
	Color check(){return (_check);}

	bool check(Vector2 point);

	void render(c_viewport *viewport = nullptr);

};

class w_box_component : public w_component, public w_graphical_component
{
protected:
	Color _delta;

public:
		//Constructor
	w_box_component(class c_widget *p_owner = nullptr);

		//Setter
	void set_delta(Color p_delta){_delta = p_delta;}

		//Getter
	Color delta(){return (_delta);}

	void render(c_viewport *viewport = nullptr);
};

class w_text_entry_component : public w_component, public w_graphical_component, public w_textual_component
{
protected:
	int _cursor;
	bool _selected;

	string _text_to_draw;
	int _cursor_to_draw;

public:
		//Constructor
	w_text_entry_component(class c_widget *p_owner = nullptr, string p_text = "");

		//Setter
	void		set_text(string new_text){ _text = new_text; _cursor = new_text.size(); calc_text_to_draw(); }
	void 		set_selected(bool p_selected){_selected = p_selected;}

		//Getter
	bool		selected(){return (_selected);}
	int 		cursor(){return (_cursor);}

	string 		text_to_draw(){return (_text_to_draw);}
	int 		cursor_to_draw(){return (_cursor_to_draw);}

	void 		resize(Vector2 p_anchor, Vector2 p_area)
		{set_anchor(p_anchor);set_area(p_area);calc_text_size_height(_area);}
	void 		calc_text_to_draw();
	void 		move_cursor(int delta);
	void 		add_text(string new_text);
	void 		change_text(string new_text);
	void 		remove_text();
	void 		supp_text();

	void 		render(c_viewport *viewport = nullptr);
};

class w_value_component : public w_component, public w_graphical_component, public w_textual_component
{
protected:
	float _value;
	int _precision;

public:
		//Constructor
	w_value_component(class c_widget *p_owner = nullptr, float p_value = 0.0f);

		//Setter
	void 		set_text(string p_text){_text = p_text;calc_value();}
	void 		set_value(float p_value){_value = p_value;calc_text();}
	void 		set_precision(int p_precision){_precision = p_precision;}
	void 		resize(Vector2 p_anchor, Vector2 p_area)
		{set_anchor(p_anchor);set_area(p_area);calc_text_size(_area);}
	void 		calc_value(){ _value = static_cast<float>(atof(_text.c_str()));}
	void 		calc_text(){ _text = ftoa(_value, _precision);}

		//Getter
	float		value(){return (_value);}
	int			precision(){return (_precision);}

	void render(c_viewport *viewport = nullptr);
};

class w_value_entry_component : public w_component, public w_graphical_component, public w_textual_component
{
protected:
	bool _selected;
	float _value;
	int _precision;
	int _cursor;

	string _text_to_draw;
	int _cursor_to_draw;

public:
		//Constructor
	w_value_entry_component(class c_widget *p_owner = nullptr, float p_value = 0.0f);

		//Setter
	void 		set_selected(bool p_selected){_selected = p_selected;}
	void 		set_precision(int p_precision){_precision = p_precision;}
	void 		set_text(string p_text){_text = p_text;calc_value();calc_text_to_draw();}
	void 		set_value(float p_value){_value = p_value;calc_text();calc_text_to_draw();}
	void 		set_cursor(int p_cursor){_cursor = p_cursor;}
	void 		resize(Vector2 p_anchor, Vector2 p_area)
		{set_anchor(p_anchor);set_area(p_area);calc_text_size_height(_area);calc_text_to_draw();}
	void 		calc_value(){ _value = static_cast<float>(atof(_text.c_str()));}
	void 		calc_text() { _text = ftoa(_value, _precision);}

		//Getter
	bool		selected(){return (_selected);}
	int			precision(){return (_precision);}
	float 		value(){return (_value);}
	string 		text(){return (_text);}
	int 		cursor(){return (_cursor);}
	string 		text_to_draw(){return (_text_to_draw);}
	int 		cursor_to_draw(){return (_cursor_to_draw);}

	void 		calc_text_to_draw();
	void 		move_cursor(int delta);
	void 		add_text(string new_text);
	void 		change_text(string new_text);
	void 		remove_text();
	void 		supp_text();

	void render(c_viewport *viewport = nullptr);
};

#endif

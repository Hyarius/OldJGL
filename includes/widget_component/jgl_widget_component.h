#ifndef JGL_WIDGET_COMPONENT_H
#define JGL_WIDGET_COMPONENT_H

namespace jgl
{
	class w_component
	{
	protected:
		class Widget* _owner;

		Vector2 _anchor;
		Vector2 _area;

	public:
		w_component(class Widget* p_owner);

		void 		set_anchor(Vector2 p_anchor) { _anchor = p_anchor; }
		void 		set_area(Vector2 p_area) { _area = p_area; }
		void 		resize(Vector2 p_anchor, Vector2 p_area)
		{
			set_anchor(p_anchor); set_area(p_area);
		}
		Vector2 	anchor() { return (_anchor); }
		Vector2 	area() { return (_area); }
		Vector2		owner_anchor();

		bool is_pointed(Vector2 point);

		virtual void render(Viewport* viewport = nullptr) = 0;
	};

	class w_graphical_component
	{
	protected:
		Sprite_sheet* _tileset;
		size_t _corner_size;

		Sprite_sheet* _image;
		int _sprite;

		Color _back;
		Color _front;
		int _border;

	public:
		w_graphical_component();

		void set_tileset(Sprite_sheet* p_tileset) { _tileset = p_tileset; }
		void set_image(Sprite_sheet* p_image) { _image = p_image; }
		void set_back(Color p_back) { _back = p_back; }
		void set_front(Color p_front) { _front = p_front; }
		void set_border(int p_border) { _border = p_border; }
		void set_sprite(int p_sprite) { _sprite = p_sprite; }
		void set_corner_size(size_t p_corner_size) { _corner_size = p_corner_size; }

		//Getter
		Sprite_sheet* tileset() { return (_tileset); }
		Sprite_sheet* image() { return (_image); }
		int border() { return (_border); }
		int sprite() { return (_sprite); }
		size_t corner_size() { return (_corner_size); }
		Color back() { return (_back); }
		Color front() { return (_front); }
	};

	class w_textual_component
	{
	protected:
		jgl::String _text;
		int _size;
		alignment _align;
		text_color _color;
		text_style _style;

	public:
		w_textual_component();

		void 		set_text(jgl::String p_text) { _text = p_text; }
		void 		set_align(alignment p_align) { _align = p_align; }
		void 		set_size(int p_size) { _size = p_size; }
		void 		set_color(text_color p_color) { _color = p_color; }
		void 		set_style(text_style p_style) { _style = p_style; }

		void 		calc_text_size(Vector2 area);
		void 		calc_text_size_height(Vector2 area);

		jgl::String 		text() { return (_text); }
		alignment 	align() { return (_align); }
		int 		size() { return (_size); }
		text_color 	color() { return (_color); }
		text_style 	style() { return (_style); }
	};

	class w_entry_component : public w_component, public w_graphical_component, public w_textual_component
	{
	protected:
		size_t _cursor;
		bool _selected;

		jgl::String _text_to_draw;
		size_t _cursor_to_draw;

	public:
		w_entry_component(jgl::String p_text = "", class Widget* p_owner = nullptr);
		void		set_text(jgl::String new_text) { _text = new_text; _cursor = new_text->size(); calc_text_to_draw(); }
		void 		set_selected(bool p_selected) { _selected = p_selected; }
		void		set_cursor(size_t p_cursor) { _cursor = p_cursor; }
		//Getter
		bool		selected() { return (_selected); }
		size_t 		cursor() { return (_cursor); }

		jgl::String 		text_to_draw() { return (_text_to_draw); }
		size_t 		cursor_to_draw() { return (_cursor_to_draw); }

		void 		resize(Vector2 p_anchor, Vector2 p_area)
		{
			set_anchor(p_anchor); set_area(p_area); calc_text_size_height(_area);
		}
		void 		calc_text_to_draw();
		void 		move_cursor(int delta);
		void 		add_text(jgl::String new_text);
		void 		change_text(jgl::String new_text);
		void 		remove_text();
		void 		supp_text();

		void 		render(Viewport* viewport = nullptr);
	};

	class w_text_component : public w_component, public w_graphical_component, public w_textual_component
	{
	public:
		w_text_component(jgl::String p_text = "", class Widget* p_owner = nullptr);

		void 		resize(Vector2 p_anchor, Vector2 p_area);

		void render(Viewport* viewport = nullptr);
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
		w_check_component(bool p_state = false, class Widget* p_owner = nullptr);

		//Setter
		void set_state(bool p_state) { _state = p_state; }
		void set_border(int p_border) { _border = p_border; }
		void set_back(Color p_back) { _back = p_back; }
		void set_front(Color p_front) { _front = p_front; }
		void set_check(Color p_check) { _check = p_check; }

		//Getter
		bool state() { return (_state); }
		int border() { return (_border); }
		Color back() { return (_back); }
		Color front() { return (_front); }
		Color check() { return (_check); }

		bool check(Vector2 point);

		void render(Viewport* viewport = nullptr);

	};

	class w_box_component : public w_component, public w_graphical_component
	{
	protected:
		Color _delta;

	public:
		//Constructor
		w_box_component(class Widget* p_owner = nullptr);

		//Setter
		void set_delta(Color p_delta) { _delta = p_delta; }

		//Getter
		Color delta() { return (_delta); }

		void render(Viewport* viewport = nullptr);
	};

	class w_text_entry_component : public w_entry_component
	{
	protected:
		size_t _cursor;
		bool _selected;

		jgl::String _text_to_draw;
		size_t _cursor_to_draw;

	public:
		w_text_entry_component(jgl::String p_text = "", class Widget* p_owner = nullptr);
	};

	template<typename T>
	class w_value_component : public w_component, public w_graphical_component, public w_textual_component
	{
	protected:
		T* _value_ptr = nullptr;
		T _value = 0;
		int _precision = 3;

	public:
		//Constructor
		w_value_component(class Widget* p_owner = nullptr) : w_component(p_owner), w_graphical_component(), w_textual_component()
		{
			_value_ptr = nullptr;
			_value = 0;
			_anchor = Vector2();
			_area = Vector2();
			_align = alignment::left;
			_size = 16;
			_color = text_color::black;
			_style = text_style::normal;
		}
		w_value_component(T p_value, class Widget* p_owner = nullptr) : w_value_component()
		{
			_value = p_value;
			calc_text();
		}
		w_value_component(T* p_value_ptr, class Widget* p_owner = nullptr) : w_value_component()
		{
			_value_ptr = p_value_ptr;
			calc_text();
		}

		//Setter
		void 		set_text(jgl::String p_text) { _text = p_text; calc_value(); }
		void 		set_value(T p_value) { _value = p_value; calc_text(); }
		void 		set_value(T* p_value) { _value = p_value; calc_text(); }
		void 		set_precision(int p_precision) { _precision = p_precision; }
		void 		resize(Vector2 p_anchor, Vector2 p_area)
		{
			set_anchor(p_anchor); set_area(p_area); calc_text_size(_area);
		}
		void 		calc_value() { _value = static_cast<T>(jgl::stof(_text)); }
		void 		calc_text() { if (_value_ptr != nullptr && *_value_ptr != _value) set_value(*_value_ptr); _text = ftoa(static_cast<float>(_value), _precision); }

		//Getter
		T*			value_ptr() { return (_value_ptr); }
		T			value() { if (_value_ptr != nullptr)return (*_value_ptr); return (_value); }
		int			precision() { return (_precision); }

		void render(Viewport* viewport = nullptr)
		{
			Vector2 pos;

			if (_value_ptr != nullptr && *_value_ptr != _value)
				set_value(*_value_ptr);

			if (_align == alignment::left)
			{
				pos.x = calc_text_len(_text, _size) / 2.0f;
				pos.y = _area.y / 2.0f;
			}
			else if (_align == alignment::centred)
			{
				pos = _area / 2;
			}
			else if (_align == alignment::right)
			{
				pos.x = _area.x - calc_text_len(_text, _size) / 2.0f;
				pos.y = _area.y / 2.0f;
			}
			draw_centred_text(_text, pos + _anchor, _size, 0, _color, _style, viewport);
		}
	};

	template<typename T>
	class w_value_entry_component : public w_entry_component
	{
	protected:
		bool _selected;
		T _value;
		T* _value_ptr;
		int _precision;
		size_t _cursor;

		jgl::String _text_to_draw;
		size_t _cursor_to_draw;

	public:
		//Constructor
		w_value_entry_component(class Widget* p_owner = nullptr)
		{
			_value_ptr = nullptr;
			_value = 0;
			_anchor = Vector2();
			_area = Vector2();
			_align = alignment::left;
			_size = 16;
			_color = text_color::black;
			_style = text_style::normal;
		}
		w_value_entry_component(T p_value, class Widget* p_owner = nullptr) : w_value_entry_component()
		{
			_value = p_value;
			set_precision(3);
			calc_text();
		}
		w_value_entry_component(T* p_value_ptr, class Widget* p_owner = nullptr) : w_value_entry_component()
		{
			_value_ptr = p_value_ptr;
			set_precision(3);
			calc_text();
		}

		//Setter
		void 		set_precision(int p_precision) { _precision = p_precision; }
		void 		set_text(jgl::String p_text) { _text = p_text; calc_value(); }
		void 		set_value(T p_value) { _value = p_value; calc_text(); }
		void 		set_value(T* p_value) { _value = p_value; calc_text(); }
		void 		calc_value() { _value = static_cast<T>(jgl::stof(_text)); }
		void 		calc_text() { if (_value_ptr != nullptr && *_value_ptr != _value) set_value(*_value_ptr); _text = ftoa(static_cast<float>(_value), _precision); }

		//Getter
		int			precision() { return (_precision); }
		T			value() { return (_value); }
		size_t		cursor() { return (_cursor); }
		bool		selected() { return (_selected); }

		void render(Viewport* viewport = nullptr)
		{
			Vector2 pos;

			if (_value_ptr != nullptr && *_value_ptr != _value)
				set_value(*_value_ptr);

			if (_align == alignment::left)
			{
				pos.x = calc_text_len(_text, _size) / 2.0f;
				pos.y = _area.y / 2.0f;
			}
			else if (_align == alignment::centred)
			{
				pos = _area / 2;
			}
			else if (_align == alignment::right)
			{
				pos.x = _area.x - calc_text_len(_text, _size) / 2.0f;
				pos.y = _area.y / 2.0f;
			}
			draw_centred_text(_text, pos + _anchor, _size, 0, _color, _style, viewport);
		}
	};
}

#endif

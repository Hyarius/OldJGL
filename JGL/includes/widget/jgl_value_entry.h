#ifndef JGL_VALUE_ENTRY
#define JGL_VALUE_ENTRY

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

namespace jgl
{
	template<typename T>
	class Value_entry : public Widget
	{
	protected:
		w_box_component _box;
		w_value_entry_component<T> _entry;

		bool _select;
		unsigned long _next_input;
		unsigned long _input_delay;

	public:
		Value_entry(Widget* p_parent = nullptr) : Widget(p_parent)
		{
			_box = w_box_component(this);
			_entry = w_value_entry_component<T>(static_cast<T>(0), this);

			_select = false;
			_next_input = 0;
			_input_delay = 150;

			set_geometry(-1, -1);
			unselect();
		}
		Value_entry(T p_value, Widget* p_parent = nullptr) : Value_entry(p_parent)
		{
			_entry = w_value_entry_component(p_value, this);
		}

		w_box_component& box() { return (_box); }
		w_value_entry_component<T>& entry() { return (_entry); }

		// - box redirection function
		void set_tileset(Sprite_sheet* p_tileset) { _box.set_tileset(p_tileset); }
		void set_tileset(jgl::String path) { _box.set_tileset(new Sprite_sheet(path, 3)); }
		void set_image(Sprite_sheet* p_image) { _box.set_image(p_image); }
		void set_image(Image* p_image) { _box.set_image(new Sprite_sheet(p_image)); }
		void set_image(jgl::String path) { _box.set_image(new Sprite_sheet(path, 1)); }
		void set_back(Color p_back) { _box.set_back(p_back); }
		void set_front(Color p_front) { _box.set_front(p_front); }
		void set_border(int p_border) { _box.set_border(p_border); }
		void set_sprite(int p_sprite) { _box.set_sprite(p_sprite); }
		void set_sprite(jgl::Vector2 p_sprite) { _box.set_sprite(p_sprite); }
		void set_corner_size(uint32_t p_corner_size) { _box.set_corner_size(p_corner_size); }
		jgl::Vector2 sprite() const { return (_box.sprite()); }
		uint32_t corner_size() { return (_box.corner_size()); }
		Sprite_sheet* tileset() { return (_box.tileset()); }
		Sprite_sheet* image() { return (_box.image()); }
		int border() { return (_box.border()); }
		Color back() { return (_box.back()); }
		Color front() { return (_box.front()); }

		void 		set_selected(bool p_selected) { _entry.set_selected(p_selected); }
		void 		set_precision(int p_precision) { _entry.set_precision(p_precision); }
		void 		set_text(jgl::String p_text) { _entry.set_text(p_text); }
		void 		set_value(T p_value) { _entry.set_value(p_value); }
		void 		set_value(T* p_value) { _entry.set_value(p_value); }
		void 		set_cursor(int p_cursor) { _entry.set_cursor(p_cursor); }
		bool		selected() { return (_entry.selected()); }
		int			precision() { return (_entry.precision()); }
		T 			value() { return (_entry.value()); }
		jgl::String text() { return (_entry.text()); }
		uint32_t 		cursor() { return (_entry.cursor()); }

		void 		set_align(alignment p_align) { _entry.set_align(p_align); }
		void 		set_size(int p_size) { _entry.set_size(p_size); }
		void 		set_color(text_color p_color) { _entry.set_color(p_color); }
		void 		set_style(text_style p_style) { _entry.set_style(p_style); }

		alignment 	align() { return (_entry.align()); }
		int 		size() { return (_entry.size()); }
		text_color 	color() { return (_entry.color()); }
		text_style 	style() { return (_entry.style()); }

		void select() { _entry.set_selected(true); }
		void unselect() { _entry.set_selected(false); }

		void set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
		{
			_box.set_area(p_area);
			_box.set_anchor(p_anchor);
			_entry.set_area(p_area - _box.border() * 4);
			_entry.set_anchor(p_anchor + _box.border() * 2);
			_entry.calc_text_size_height(_entry.area());
			_entry.calc_text_to_draw();
		}
		void move(Vector2 delta)
		{
			_box.set_anchor(_box.anchor() + delta);
			_entry.set_anchor(_entry.anchor() + delta);
			_viewport->set_anchor(anchor() + delta);
		}

		void render()
		{
			if (is_active() == false)
				return;
			_box.render(_viewport);
			_entry.render(_viewport);
		}

		bool handle_mouse()
		{
			if (g_mouse->get_button(mouse_button::left) == mouse_state::down)
				unselect();

			if (g_mouse->get_button(mouse_button::left) == mouse_state::up)
			{
				if (is_pointed(g_mouse->pos) == true)
				{
					select();
					return (true);
				}
			}
			return (false);
		}

		bool handle_keyboard()
		{
			if (selected() == false)
				return (false);

			if (g_keyboard->get_key(key::return_key) == key_state::pressed)
				unselect();
			else if (g_keyboard->get_key(key::key_pad_return_key) == key_state::pressed)
				unselect();
			else if (g_keyboard->get_key(key::left_arrow) == key_state::pressed)
				_entry.move_cursor(-1);
			else if (g_keyboard->get_key(key::right_arrow) == key_state::pressed)
				_entry.move_cursor(1);
			else if (g_keyboard->get_key(key::backspace) == key_state::pressed)
				_entry.remove_text();
			else if (g_keyboard->get_key(key::delete_key) == key_state::pressed)
				_entry.supp_text();

			if (g_application->event()->type == SDL_TEXTINPUT)
			{
				static Glyph last_char = '\0';
				Uint32 time = SDL_GetTicks();
				jgl::String text = g_application->event()->text.text;
				if (text[0] != last_char || time >= _next_input)
				{
					last_char = text[0];
					_entry.add_text(text);
					_next_input = time + _input_delay;
				}
			}

			return (false);
		}
	};
}
#endif

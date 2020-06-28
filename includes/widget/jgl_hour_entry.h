#ifndef JGL_HOUR_ENTRY_H
#define JGL_HOUR_ENTRY_H

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

namespace jgl
{
	class Hour_entry : public Widget
	{
	protected:
		w_box_component _box;
		w_text_component _label;
		w_value_entry_component<float> _hour;
		w_value_entry_component<float> _minute;

		w_value_entry_component<float>* _entry;

		bool _selected;
		Uint32 _next_input;
		Uint32 _input_delay;

	public:
		Hour_entry(float p_hour = 12.0f, float p_minute = 0.0f, Widget* p_parent = nullptr);

		void select();
		void unselect();

		void round();

		float value() { return (_hour.value() * 60 + _minute.value()); }

		bool selected() { return (_selected); }
		w_box_component& box() { return (_box); }
		w_text_component& label() { return (_label); }
		w_value_entry_component<float>& hour() { return (_hour); }
		w_value_entry_component<float>& minute() { return (_minute); }

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
		void set_corner_size(size_t p_corner_size) { _box.set_corner_size(p_corner_size); }
		int sprite() { return (_box.sprite()); }
		size_t corner_size() { return (_box.corner_size()); }
		Sprite_sheet* tileset() { return (_box.tileset()); }
		Sprite_sheet* image() { return (_box.image()); }
		int border() { return (_box.border()); }
		Color back() { return (_box.back()); }
		Color front() { return (_box.front()); }

		// - label redirection function
		void 		set_text(jgl::String p_text) { _label.set_text(p_text); }
		void 		set_align(alignment p_align) { _label.set_align(p_align); }
		void 		set_size(int p_size) { _label.set_size(p_size); }
		void 		set_color(text_color p_color) { _label.set_color(p_color); }
		void 		set_style(text_style p_style) { _label.set_style(p_style); }
		jgl::String text() { return (_label.text()); }
		alignment 	align() { return (_label.align()); }
		int 		size() { return (_label.size()); }
		text_color 	color() { return (_label.color()); }
		text_style 	style() { return (_label.style()); }

		void 		set_hour_selected(bool p_selected) { _hour.set_selected(p_selected); }
		void 		set_hour_precision(int p_precision) { _hour.set_precision(p_precision); }
		void 		set_hour_text(jgl::String p_text) { _hour.set_text(p_text); }
		void 		set_hour_value(float p_value) { _hour.set_value(p_value); }
		void 		set_hour_cursor(int p_cursor) { _hour.set_cursor(p_cursor); }
		bool		hour_selected() { return (_hour.selected()); }
		int			hour_precision() { return (_hour.precision()); }
		float 		hour_value() { return (_hour.value()); }
		jgl::String hour_text() { return (_hour.text()); }
		size_t 		hour_cursor() { return (_hour.cursor()); }

		void 		set_minute_selected(bool p_selected) { _minute.set_selected(p_selected); }
		void 		set_minute_precision(int p_precision) { _minute.set_precision(p_precision); }
		void 		set_minute_text(jgl::String p_text) { _minute.set_text(p_text); }
		void 		set_minute_value(float p_value) { _minute.set_value(p_value); }
		void 		set_minute_cursor(int p_cursor) { _minute.set_cursor(p_cursor); }
		bool		minute_selected() { return (_minute.selected()); }
		int			minute_precision() { return (_minute.precision()); }
		float 		minute_value() { return (_minute.value()); }
		jgl::String minute_text() { return (_minute.text()); }
		size_t 		minute_cursor() { return (_minute.cursor()); }

		void set_selected(bool p_selected) { _selected = p_selected; }
		void set_box(w_box_component new_box) { _box = new_box; }
		void set_label(w_text_component new_label) { _label = new_label; }
		void set_hour(w_value_entry_component<float> new_hour) { _hour = new_hour; }
		void set_minute(w_value_entry_component<float> new_minute) { _minute = new_minute; }


		void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);
		void move(Vector2 delta);

		void render();

		bool handle_mouse();

		bool handle_keyboard();
	};
}
#endif

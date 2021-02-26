#ifndef JGL_TEXT_ENTRY
#define JGL_TEXT_ENTRY

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

namespace jgl
{
	class Text_entry : public Widget
	{
	protected:
		w_box_component _box;
		w_text_entry_component _entry;

		bool _select;
		Uint32 _next_input;
		Uint32 _input_delay;

	public:
		Text_entry(jgl::String p_text = "", Widget* p_parent = nullptr);

		jgl::String text() { return (_entry.text()); }

		w_box_component& box() { return (_box); }
		w_text_entry_component& entry() { return (_entry); }


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
		void set_corner_size(size_t p_corner_size) { _box.set_corner_size(p_corner_size); }
		void set_masked(bool state) { _entry.set_masked(state); }
		jgl::Vector2 sprite() const { return (_box.sprite()); }
		size_t corner_size() { return (_box.corner_size()); }
		Sprite_sheet* tileset() { return (_box.tileset()); }
		Sprite_sheet* image() { return (_box.image()); }
		int border() { return (_box.border()); }
		Color back() { return (_box.back()); }
		Color front() { return (_box.front()); }

		void		set_text(jgl::String p_text) { _entry.set_text(p_text); }
		void 		set_selected(bool p_selected) { _entry.set_selected(p_selected); }
		bool		selected() { return (_entry.selected()); }
		size_t 		cursor() { return (_entry.cursor()); }

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

		void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);
		void move(Vector2 delta);

		void render();

		bool handle_mouse();

		bool handle_keyboard();
	};
}

#endif

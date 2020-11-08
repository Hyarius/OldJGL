#ifndef JGL_FRAME_H
#define JGL_FRAME_H

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

namespace jgl
{
	class Frame : public Widget
	{
	protected:
		w_box_component _box;

	public:
		Frame(Widget* p_parent = nullptr);

		w_box_component& box() { return (_box); }

		// - box redirection function
		void set_tileset(Sprite_sheet* p_tileset) { _box.set_tileset(p_tileset); }
		void set_tileset(jgl::String path) { _box.set_tileset(new Sprite_sheet(path, 3)); }
		void set_image(Sprite_sheet* p_image) { _box.set_image(p_image); }
		void set_image(Image* p_image) { _box.set_image(new Sprite_sheet(p_image, 1)); }
		void set_image(jgl::String path) { _box.set_image(new Sprite_sheet(path, 1)); }
		void set_back(Color p_back) { _box.set_back(p_back); }
		void set_front(Color p_front) { _box.set_front(p_front); }
		void set_border(int p_border) { _box.set_border(p_border); }
		void set_sprite(int p_sprite) { _box.set_sprite(p_sprite); }
		void set_sprite(jgl::Vector2 p_sprite) { _box.set_sprite(p_sprite); }
		void set_corner_size(size_t p_corner_size) { _box.set_corner_size(p_corner_size); }
		jgl::Vector2 sprite() const { return (_box.sprite()); }
		size_t corner_size() { return (_box.corner_size()); }
		Sprite_sheet* tileset() { return (_box.tileset()); }
		Sprite_sheet* image() { return (_box.image()); }
		int border() { return (_box.border()); }
		Color back() { return (_box.back()); }
		Color front() { return (_box.front()); }

		void move(Vector2 delta);

		void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);

		void render();

		bool handle_mouse();

		bool handle_keyboard();
	};
}
#endif

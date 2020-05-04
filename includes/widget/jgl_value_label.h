#ifndef JGL_VALUE_LABEL_H
#define JGL_VALUE_LABEL_H

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

namespace jgl
{
	class Value_label : public Widget
	{
	protected:
		w_box_component _box;
		w_value_component _label;

	public:
		Value_label(float p_value = 0.0f, Widget* p_parent = nullptr);
		~Value_label();

		float value() { return (_label.value()); }

		w_box_component& box() { return (_box); }
		w_value_component& label() { return (_label); }

		// - box redirection function
		void set_tileset(Tileset* p_tileset) { _box.set_tileset(p_tileset); }
		void set_tileset(jgl::String path) { _box.set_tileset(new Tileset(path, 3)); }
		void set_image(Tileset* p_image) { _box.set_image(p_image); }
		void set_image(Image* p_image) { _box.set_image(new Tileset(p_image)); }
		void set_image(jgl::String path) { _box.set_image(new Tileset(path, 1)); }
		void set_back(Color p_back) { _box.set_back(p_back); }
		void set_front(Color p_front) { _box.set_front(p_front); }
		void set_border(int p_border) { _box.set_border(p_border); }
		void set_sprite(int p_sprite) { _box.set_sprite(p_sprite); }
		void set_corner_size(size_t p_corner_size) { _box.set_corner_size(p_corner_size); }
		int sprite() { return (_box.sprite()); }
		size_t corner_size() { return (_box.corner_size()); }
		Tileset* tileset() { return (_box.tileset()); }
		Tileset* image() { return (_box.image()); }
		int border() { return (_box.border()); }
		Color back() { return (_box.back()); }
		Color front() { return (_box.front()); }

		void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);
		void move(Vector2 delta);

		void render();

		bool handle_mouse();

		bool handle_keyboard();
	};
}
#endif

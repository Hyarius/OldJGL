#ifndef JGL_VALUE_LABEL_H
#define JGL_VALUE_LABEL_H

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

namespace jgl
{
	template<typename T>
	class Value_label : public Widget
	{
	protected:
		w_box_component _box;
		w_value_component<T> _label;


	public:
		Value_label(T* p_value, Widget* p_parent = nullptr) : Widget(p_parent)
		{
			_box = w_box_component(this);
			_label = w_value_component<T>(p_value, this);

			set_geometry(-1, -1);
		}
		Value_label(T p_value, Widget* p_parent = nullptr) : Widget(p_parent)
		{
			_box = w_box_component(this);
			_label = w_value_component<T>(p_value, this);

			set_geometry(-1, -1);
		}

		T* value_ptr() { return (_label.value_ptr()); }
		T value() { return (_label.value()); }

		w_box_component& box() { return (_box); }
		w_value_component<T>& label() { return (_label); }

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
		jgl::Vector2 sprite() const { return (_box.sprite()); }
		size_t corner_size() { return (_box.corner_size()); }
		Sprite_sheet* tileset() { return (_box.tileset()); }
		Sprite_sheet* image() { return (_box.image()); }
		int border() { return (_box.border()); }
		Color back() { return (_box.back()); }
		Color front() { return (_box.front()); }

		void set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
		{
			//_viewport->resize(p_anchor, p_area);
			_box.set_area(p_area);
			_box.set_anchor(p_anchor);
			_label.set_area(p_area - _box.border() * 4);
			_label.set_anchor(p_anchor + _box.border());
			_label.calc_text_size(_label.area());
		}

		void move(Vector2 delta)
		{
			_box.set_anchor(_box.anchor() + delta);
			_label.set_anchor(_label.anchor() + delta);
			_viewport->set_anchor(anchor() + delta);
		}

		void render()
		{
			if (is_active() == false)
				return;
			_box.render(_viewport);
			_label.render(_viewport);
		}

		bool handle_mouse()
		{
			return (false);
		}

		bool handle_keyboard()
		{
			return (false);
		}
	};
}
#endif

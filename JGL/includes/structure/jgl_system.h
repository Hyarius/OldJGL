#ifndef JGL_SYSTEM_H
#define JGL_SYSTEM_H

#include "jgl_includes.h"
#include "jgl_vector.h"
#include "jgl_color.h"
#include "jgl_enum.h"

namespace jgl
{
	struct Mouse
	{
		Vector2 begin_pos;
		Vector2 old_pos;
		Vector2 pos;
		Vector2 rel_pos;
		float wheel;
		bool motion;
		mouse_state button[3];

		Mouse();
		void actualize_pos(int x, int y);
		void actualize_button(Uint32 mousestate);
		void actualize();
		mouse_state get_button(mouse_button type) const ;
		void place(Vector2 coord);
		void update(int p_time = 20);

		friend std::ostream& operator<<(std::ostream& os, const jgl::Mouse mouse)
		{
			jgl::String left = (mouse.get_button(jgl::mouse_button::left) == jgl::mouse_state::up ? "Up" : (mouse.get_button(jgl::mouse_button::left) == jgl::mouse_state::down ? "Down" : "Null"));
			jgl::String center = (mouse.get_button(jgl::mouse_button::center) == jgl::mouse_state::up ? "Up" : (mouse.get_button(jgl::mouse_button::center) == jgl::mouse_state::down ? "Down" : "Null"));
			jgl::String right = (mouse.get_button(jgl::mouse_button::right) == jgl::mouse_state::up ? "Up" : (mouse.get_button(jgl::mouse_button::right) == jgl::mouse_state::down ? "Down" : "Null"));
			os << "Left : " << left << "\n" << "Middle : " << center << "\n" << "Right : " << right;
			return os;
		}
	};

	struct Keyboard
	{
		key_state keys[150];
		char clicked;
		const Uint8* state;

		Keyboard();
		void actualize();
		const key_state get_key(const key key_type) const;
	};

	const key_state get_key(const key key_type);
	const mouse_state get_button(const mouse_button type);
	const Vector2 get_mouse_pos();
	const jgl::Unique_string& get_key_name(const key key_type);
}

extern jgl::Keyboard *g_keyboard;
extern jgl::Mouse *g_mouse;

#endif

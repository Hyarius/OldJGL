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
		mouse_state get_button(mouse_button type);
		void place(Vector2 coord);
		void update(int p_time = 20);
	};

	struct Keyboard
	{
		key_state keys[150];
		char clicked;
		const Uint8* state;

		Keyboard();
		void actualize();
		key_state get_key(key key_type);
		key_state get_key(size_t key_type) { return (get_key(static_cast<key>(key_type))); }
	};
}

extern jgl::Keyboard *g_keyboard;
extern jgl::Mouse *g_mouse;

jgl::String key_name(jgl::key type);
jgl::Keyboard *get_keyboard();
jgl::Mouse *get_mouse();

#endif

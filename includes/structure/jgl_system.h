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
}

extern jgl::Keyboard *g_keyboard;
extern jgl::Mouse *g_mouse;

#endif

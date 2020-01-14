#ifndef JGL_SYSTEM_H
#define JGL_SYSTEM_H

#include "jgl_includes.h"
#include "jgl_vector.h"
#include "jgl_color.h"
#include "jgl_enum.h"

struct Mouse
{
	Vector2 old_pos;
	Vector2 pos;
	Vector2 rel_pos;
	float wheel;
	int button[MOUSE_BUTTON];
	bool motion;

	Mouse();
	void actualize_mouse(SDL_Event *event = nullptr);
	mouse_state get_button(mouse_button type);
};

struct Keyboard
{
	char clicked;
	const Uint8	*state;

	Keyboard();
	key_state get_key(int scan_code);
	void reset_key(int scan_code);
};

extern Keyboard *g_keyboard;
extern Mouse *g_mouse;

mouse_state get_button(mouse_button type);
key_state get_key(int scan_code);
void reset_key(int scan_code);

#endif

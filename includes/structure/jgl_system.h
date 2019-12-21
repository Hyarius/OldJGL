#ifndef JGL_SYSTEM_H
#define JGL_SYSTEM_H

#include "jgl_includes.h"
#include "jgl_vector.h"
#include "jgl_color.h"
#include "jgl_enum.h"

typedef struct s_mouse
{
	Vector2 old_pos;
	Vector2 pos;
	Vector2 rel_pos;
	float wheel;
	int button[MOUSE_BUTTON];
	bool motion;

	s_mouse();
	void actualize_mouse(SDL_Event *event = nullptr);
	mouse_state get_button(mouse_button type);

}t_mouse;

typedef struct s_keyboard
{
	char clicked;
	const Uint8	*state;

	s_keyboard();
	int get_key(int scan_code);
	void reset_key(int scan_code);
}t_keyboard;

#endif

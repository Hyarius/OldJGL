#include "jgl.h"

Keyboard *g_keyboard;

Keyboard::Keyboard()
{
	state = SDL_GetKeyboardState(nullptr);
}

key_state Keyboard::get_key(int scan_code)
{
	int result = (state[scan_code] != 0 ? 1 : 0);
	return ((key_state)(result));
}

void Keyboard::reset_key(int scan_code)
{
	((Uint8	*)state)[scan_code] = 0;
}

Keyboard *get_keyboard()
{
	return (g_keyboard);
}

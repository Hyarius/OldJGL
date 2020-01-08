#include "jgl.h"

t_keyboard *g_keyboard;

s_keyboard::s_keyboard()
{
	state = SDL_GetKeyboardState(nullptr);
}

int s_keyboard::get_key(int scan_code)
{
	int result = (state[scan_code] != 0 ? 1 : 0);
	return (result);
}

void s_keyboard::reset_key(int scan_code)
{
	((Uint8	*)state)[scan_code] = 0;
}

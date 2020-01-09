#include "jgl.h"

Keyboard *g_keyboard;

Keyboard::Keyboard()
{
	state = SDL_GetKeyboardState(nullptr);
}

int Keyboard::get_key(int scan_code)
{
	int result = (state[scan_code] != 0 ? 1 : 0);
	return (result);
}

void Keyboard::reset_key(int scan_code)
{
	((Uint8	*)state)[scan_code] = 0;
}

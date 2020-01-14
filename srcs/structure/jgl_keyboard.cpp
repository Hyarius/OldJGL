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

key_state get_key(int scan_code){return (g_keyboard->get_key(scan_code));}
void reset_key(int scan_code){return (g_keyboard->reset_key(scan_code));}

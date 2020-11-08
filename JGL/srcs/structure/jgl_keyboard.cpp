#include "jgl.h"

jgl::Keyboard* g_keyboard;

namespace jgl
{

	Keyboard::Keyboard()
	{
		state = SDL_GetKeyboardState(nullptr);

		for (size_t i = 0; i < static_cast<size_t>(jgl::key::count); i++)
			keys[i] = key_state::up;
	}

	int converted_key[]{
		SDL_SCANCODE_A,
		SDL_SCANCODE_B,
		SDL_SCANCODE_C,
		SDL_SCANCODE_D,
		SDL_SCANCODE_E,
		SDL_SCANCODE_F,
		SDL_SCANCODE_G,
		SDL_SCANCODE_H,
		SDL_SCANCODE_I,
		SDL_SCANCODE_J,
		SDL_SCANCODE_K,
		SDL_SCANCODE_L,
		SDL_SCANCODE_M,
		SDL_SCANCODE_N,
		SDL_SCANCODE_O,
		SDL_SCANCODE_P,
		SDL_SCANCODE_Q,
		SDL_SCANCODE_R,
		SDL_SCANCODE_S,
		SDL_SCANCODE_T,
		SDL_SCANCODE_U,
		SDL_SCANCODE_V,
		SDL_SCANCODE_W,
		SDL_SCANCODE_X,
		SDL_SCANCODE_Y,
		SDL_SCANCODE_Z,
		SDL_SCANCODE_1,
		SDL_SCANCODE_2,
		SDL_SCANCODE_3,
		SDL_SCANCODE_4,
		SDL_SCANCODE_5,
		SDL_SCANCODE_6,
		SDL_SCANCODE_7,
		SDL_SCANCODE_8,
		SDL_SCANCODE_9,
		SDL_SCANCODE_0,
		SDL_SCANCODE_MINUS,
		SDL_SCANCODE_EQUALS,
		SDL_SCANCODE_KP_1,
		SDL_SCANCODE_KP_2,
		SDL_SCANCODE_KP_3,
		SDL_SCANCODE_KP_4,
		SDL_SCANCODE_KP_5,
		SDL_SCANCODE_KP_6,
		SDL_SCANCODE_KP_7,
		SDL_SCANCODE_KP_8,
		SDL_SCANCODE_KP_9,
		SDL_SCANCODE_KP_0,
		SDL_SCANCODE_F1,
		SDL_SCANCODE_F2,
		SDL_SCANCODE_F3,
		SDL_SCANCODE_F4,
		SDL_SCANCODE_F5,
		SDL_SCANCODE_F6,
		SDL_SCANCODE_F7,
		SDL_SCANCODE_F8,
		SDL_SCANCODE_F9,
		SDL_SCANCODE_F10,
		SDL_SCANCODE_F11,
		SDL_SCANCODE_F12,
		SDL_SCANCODE_UP,
		SDL_SCANCODE_DOWN,
		SDL_SCANCODE_LEFT,
		SDL_SCANCODE_RIGHT,
		SDL_SCANCODE_ESCAPE,
		SDL_SCANCODE_LALT,
		SDL_SCANCODE_RALT,
		SDL_SCANCODE_LCTRL,
		SDL_SCANCODE_RCTRL,
		SDL_SCANCODE_RETURN,
		SDL_SCANCODE_KP_ENTER,
		SDL_SCANCODE_BACKSPACE,
		SDL_SCANCODE_DELETE,
		SDL_SCANCODE_SPACE,
		SDL_SCANCODE_LSHIFT,
		SDL_SCANCODE_RSHIFT,
		SDL_SCANCODE_TAB,
		SDL_SCANCODE_GRAVE
	};

	jgl::Array<jgl::Unique_string> key_name_value = {
		"Key A",
		"key B",
		"key C",
		"key D",
		"key E",
		"key F",
		"key G",
		"key H",
		"key I",
		"key J",
		"key K",
		"key ",
		"key M",
		"key N",
		"key O",
		"key P",
		"key Q",
		"key R",
		"key S",
		"key T",
		"key U",
		"key V",
		"key W",
		"key X",
		"key Y",
		"key Z",
		"key 1",
		"key 2",
		"key 3",
		"key 4",
		"key 5",
		"key 6",
		"key 7",
		"key 8",
		"key 9",
		"key 0",
		"key MINUS",
		"key EQUALS",
		"key 1 via num pad",
		"key 2 via num pad",
		"key 3 via num pad",
		"key 4 via num pad",
		"key 5 via num pad",
		"key 6 via num pad",
		"key 7 via num pad",
		"key 8 via num pad",
		"key 9 via num pad",
		"key 0 via num pad",
		"key F1",
		"key F2",
		"key F3",
		"key F4",
		"key F5",
		"key F6",
		"key F7",
		"key F8",
		"key F9",
		"key F10",
		"key F11",
		"key F12",
		"key UP",
		"key DOWN",
		"key LEFT",
		"key RIGHT",
		"key ESCAPE",
		"key LALT",
		"key RALT",
		"key LCTR",
		"key RCTR",
		"key RETURN",
		"key KP_ENTER",
		"key BACKSPACE",
		"key DELETE",
		"key SPACE",
		"key LEFT SHIFT",
		"key TABULATION",
		"key RIGHT SHIFT",
		"key SQUARE"
	};

	void Keyboard::actualize()
	{
		size_t nb = static_cast<size_t>(key::count);
		for (size_t i = 0; i < nb; i++)
		{
			if (state[converted_key[i]] == 1) // La touche est pressée
			{
				if (keys[i] == key_state::up || keys[i] == key_state::release)
					keys[i] = key_state::pressed;
				else
					keys[i] = key_state::down;
			}
			else // La touche n'est pas pressée
			{
				if (keys[i] == key_state::down || keys[i] == key_state::pressed)
					keys[i] = key_state::release;
				else
					keys[i] = key_state::up;
			}
		}
	}

	const key_state Keyboard::get_key(const key key_type) const
	{
		return (keys[static_cast<size_t>(key_type)]);
	}


	const jgl::Unique_string& get_key_name(const key key_type)
	{
		return (key_name_value[static_cast<size_t>(key_type)]);
	}

	Keyboard* get_keyboard()
	{
		return (g_keyboard);
	}

	const jgl::Unique_string key_name(const key type)
	{
		return (key_name_value[static_cast<size_t>(type)]);
	}

	const key_state get_key(const key key_type)
	{
		return (g_keyboard->get_key(key_type));
	}
		
}
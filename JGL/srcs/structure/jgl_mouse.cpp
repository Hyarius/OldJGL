#include "jgl.h"

jgl::Mouse* g_mouse;

namespace jgl
{

	Mouse::Mouse()
	{
		int x, y;

		SDL_GetMouseState(&(x), &(y));
		pos = Vector2(x, y);
		old_pos = Vector2(x, y);
		rel_pos = Vector2(0, 0);
		wheel = 0.0f;
		motion = false;
		for (uint32_t i = 0; i < 3; i++)
			button[i] = mouse_state::up;
	}

	void		Mouse::actualize_pos(int x, int y)
	{
		old_pos = pos.floor();
		pos = Vector2(x, y).floor();

		if (old_pos.x != -1)
			rel_pos = pos - old_pos;

		if (g_application->poll_ret() != 0 && g_application->event()->type == SDL_MOUSEWHEEL)
			wheel = static_cast<float>(g_application->event()->wheel.y);
		else
			wheel = 0.0f;

		if (old_pos != Vector2())
			rel_pos = pos - old_pos;
	}

	Uint32 value_mouse_button[] = { SDL_BUTTON_RIGHT , SDL_BUTTON_LEFT , SDL_BUTTON_MIDDLE };

	void		Mouse::actualize_button(Uint32 mousestate)
	{
		uint32_t nb = static_cast<uint32_t>(mouse_button::count);
		for (uint32_t i = 0; i < nb; i++)
		{
			if (mousestate & SDL_BUTTON(value_mouse_button[i])) // Le bouton est pressé
			{
				if (button[i] == mouse_state::up || button[i] == mouse_state::release)
				{
					button[i] = mouse_state::pressed;
					begin_pos = pos;
					motion = false;
				}
				else
				{
					button[i] = mouse_state::down;
					if (point_in_rectangle(begin_pos, pos - 5, 10) == false && motion == false)
						motion = true;
				}
			}
			else // Le bouton n'est pas pressé
			{
				if (button[i] == mouse_state::down || button[i] == mouse_state::pressed)
				{
					button[i] = mouse_state::release;
				}
				else
				{
					button[i] = mouse_state::up;
					motion = false;
				}
			}
		}
	}

	void		Mouse::actualize()
	{
		int x, y;
		Uint32 mousestate;

		SDL_PumpEvents();
		mousestate = SDL_GetMouseState(&(x), &(y));

		actualize_pos(x, y);
		actualize_button(mousestate);
	}

	mouse_state			Mouse::get_button(mouse_button type) const
	{
		return (button[static_cast<int>(type)]);
	}

	void Mouse::place(Vector2 coord)
	{
		pos = coord.floor();
		old_pos = coord.floor();
		rel_pos = Vector2(0, 0).floor();
		SDL_WarpMouseInWindow(g_application->window(), static_cast<int>(coord.x), static_cast<int>(coord.y));
	}

	void Mouse::update(int p_time)
	{
		SDL_PollEvent(g_application->event());
		SDL_Delay(p_time);
		actualize();
	}

	Mouse* get_mouse()
	{
		return (g_mouse);
	}
	
	const mouse_state get_button(const mouse_button type)
	{
		return (g_mouse->get_button(type));
	}
	const Vector2 get_mouse_pos()
	{
		return (g_mouse->pos);
	}
}
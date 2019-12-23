#include "jgl.h"

t_mouse *g_mouse;

s_mouse::s_mouse()
{
	old_pos = Vector2();
	pos = Vector2();
	rel_pos = Vector2(0, 0);
	wheel = 0.0f;
	button[MOUSE_LEFT] = MOUSE_NULL;
	button[MOUSE_RIGHT] = MOUSE_NULL;
	button[MOUSE_MIDDLE] = MOUSE_NULL;
}

void		s_mouse::actualize_mouse(SDL_Event *event)
{
	int x, y;
	Uint32 mousestate;

	old_pos = pos;
	mousestate = SDL_GetMouseState(&(x), &(y));
	pos = Vector2(x, y);

	if (old_pos.x != -1)
		rel_pos = pos - old_pos;

	if (event != NULL && event->type == SDL_MOUSEWHEEL)
		wheel = event->wheel.y;
	else
		wheel = 0.0f;

	button[MOUSE_LEFT] = (mousestate & SDL_BUTTON(SDL_BUTTON_LEFT) ? MOUSE_DOWN : (button[MOUSE_LEFT] == MOUSE_DOWN ? MOUSE_UP : MOUSE_NULL));
	button[MOUSE_RIGHT] = (mousestate & SDL_BUTTON(SDL_BUTTON_RIGHT) ? MOUSE_DOWN : (button[MOUSE_RIGHT] == MOUSE_DOWN ? MOUSE_UP : MOUSE_NULL));
	button[MOUSE_MIDDLE] = (mousestate & SDL_BUTTON(SDL_BUTTON_MIDDLE) ? MOUSE_DOWN : (button[MOUSE_MIDDLE] == MOUSE_DOWN ? MOUSE_UP : MOUSE_NULL));

	if (old_pos != Vector2())
		rel_pos = pos - old_pos;

	if (rel_pos != Vector2(0, 0))
		motion = true;

	if (button[MOUSE_LEFT] == MOUSE_NULL && button[MOUSE_RIGHT] == MOUSE_NULL)
		motion = false;
}

mouse_state			s_mouse::get_button(mouse_button type)
{
	int value = static_cast<int>(type);
	mouse_state result = static_cast<mouse_state>(button[value]);
	//button[value] = static_cast<int>(mouse_state::null);
	return (result);
}

ostream& operator<<(ostream& os, const t_mouse& value)
{
	
}

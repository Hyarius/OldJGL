#include "jgl.h"

c_viewport::c_viewport(Color p_color, Vector2 p_anchor, Vector2 p_area)
{
	if (g_application == nullptr)
		g_application = new c_application("Main window");

	_active = false;
	_renderer = g_application->renderer();
	_background = p_color;

	set_viewport(p_anchor, p_area);
}

void c_viewport::set_viewport(Vector2 p_anchor, Vector2 p_area)
{
	_anchor = p_anchor;
	_area = p_area;

	if (_anchor == Vector2())
		_anchor = Vector2(0, 0);
	if (_area == Vector2())
		_area = g_application->size();
}

void c_viewport::resize(Vector2 p_anchor, Vector2 p_area)
{
	_anchor = p_anchor;
	_area = p_area;
}

void c_viewport::use()
{
	if (_area.x <= 0 || _area.y <= 0)
		return ;

	reset();
	SDL_Rect rect = {
			static_cast<int>(_anchor.x), static_cast<int>(_anchor.y),
			static_cast<int>(_area.x), static_cast<int>(_area.y)
		};

	SDL_RenderSetViewport(_renderer, &rect);
	set_active(true);
}

void c_viewport::reset()
{
	SDL_RenderSetViewport(_renderer, nullptr);
}

void c_viewport::set_Color(Color Color)
{
	SDL_SetRenderDrawColor(_renderer, Color.r * 255, Color.g * 255, Color.b * 255, Color.a * 255);
}

void c_viewport::clear()
{
	//use();
	set_Color(_background);

	SDL_Rect rect = {
			static_cast<int>(0), static_cast<int>(0),
			static_cast<int>(_area.x), static_cast<int>(_area.y)
		};
	SDL_RenderFillRect(_renderer, &rect);
}

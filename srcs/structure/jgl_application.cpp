#include "jgl.h"

c_application *g_application = nullptr;

c_application::c_application(string name, Vector2 p_size, Color p_color)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	srand(time(NULL));
	TTF_Init();

	_win_size = p_size;
	if (p_size.x <= 1 && p_size.y <= 1)
	{
		SDL_DisplayMode current;
		SDL_GetDesktopDisplayMode(0, &current);
		if (p_size == Vector2())
			_win_size = Vector2(current.w * 0.8f, current.h * 0.8f);
		else
			_win_size = Vector2(current.w * p_size.x, current.h * p_size.y);
	}

	string tmp = string(name.begin(), name.end());

	_window = SDL_CreateWindow(tmp.c_str(),
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		static_cast<int>(_win_size.x), static_cast<int>(_win_size.y), 0);

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);

	g_mouse = new t_mouse();
	g_keyboard = new t_keyboard();

	if (g_application == nullptr)
		select();

	_viewport = new c_viewport();

	_central_widget = nullptr;

	_central_widget = new c_window();
	_central_widget->set_geometry(Vector2(0, 0), _win_size);
	_central_widget->set_color(p_color);
	_central_widget->activate();


	SDL_StartTextInput();

}

void c_application::resize(Vector2 p_size)
{
	_win_size = p_size;

	SDL_SetWindowSize(_window, static_cast<int>(_win_size.x), static_cast<int>(_win_size.y));
	_central_widget->set_geometry(Vector2(0, 0), _win_size);
	SDL_SetWindowPosition(_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

SDL_Window *c_application::window()
{
	return (_window);
}

SDL_Renderer *c_application::renderer()
{
	return (_renderer);
}

SDL_Event *c_application::event()
{
	return (&_event);
}

c_window *c_application::central_widget()
{
	return (_central_widget);
}

void c_application::set_background(Color p_color)
{
	_central_widget->set_color(p_color);
}

Vector2 &c_application::size()
{
	return (_win_size);
}

void c_application::select()
{
	g_application = this;
}

void c_application::clear()
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
	SDL_RenderClear(_renderer);
	SDL_RenderSetViewport(_renderer, NULL);
}

void c_application::render()
{
	SDL_RenderPresent(_renderer);
}

void c_application::quit()
{
	play = false;
}

int c_application::run()
{
	int ret;
	play = true;

	while (play == true)
	{
		clear();

		//_central_widget->render();
		_central_widget->render_children();

		_central_widget->handle_event();

		_central_widget->update_children();

		render();

		SDL_RenderSetViewport(_renderer, NULL);

		ret = SDL_PollEvent(&_event);

		if (ret != 0)
		{
			if (_event.type == SDL_QUIT)
				quit();
		}

		g_mouse->actualize_mouse((ret == 0 ? nullptr : &_event));
	}

	_central_widget->quit_children();

	return (0);
}

#include "jgl.h"

c_image::c_image() : _surface(nullptr), _texture(nullptr) {}

c_image::c_image(string path)
{
	_surface = IMG_Load(path.c_str());

	if (_surface == nullptr)
		get_sdl_error();

	_size = Vector2(_surface->w, _surface->h);

	_texture = SDL_CreateTextureFromSurface(g_application->renderer(), _surface);
}

c_image::c_image(size_t width, size_t height, Color p_color)
{
	_surface = nullptr;

	_texture = SDL_CreateTexture(g_application->renderer(), SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, width, height);

	SDL_SetTextureBlendMode(_texture, SDL_BLENDMODE_BLEND);

	if (_texture == nullptr)
		get_sdl_error();

	_size = Vector2((int)width, (int)height);

	SDL_SetRenderTarget(g_application->renderer(), _texture);

	fill_rectangle(p_color, 0, _size);

	SDL_SetRenderTarget(g_application->renderer(), NULL);
}

c_image::c_image(SDL_Surface *p_surface)
{
	_surface = p_surface;
	if (_surface == nullptr)
		error_exit(1, "Surface send in c_image = NUL");

	_size = Vector2(_surface->w, _surface->h);

	_texture = SDL_CreateTextureFromSurface(g_application->renderer(), _surface);
}

void c_image::active()
{
	SDL_SetRenderTarget(g_application->renderer(), _texture);
}

void c_image::unactive()
{
	SDL_SetRenderTarget(g_application->renderer(), NULL);
}

void c_image::save(string file_path)
{
	SDL_Texture* old_target = SDL_GetRenderTarget(g_application->renderer());
    SDL_SetRenderTarget(g_application->renderer(), _texture);
    int width, height;
    SDL_QueryTexture(_texture, NULL, NULL, &width, &height);
    SDL_Surface* tmp_surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    SDL_RenderReadPixels(g_application->renderer(), NULL, tmp_surface->format->format, tmp_surface->pixels, tmp_surface->pitch);
    IMG_SavePNG(tmp_surface, file_path.c_str());
    SDL_FreeSurface(tmp_surface);
    SDL_SetRenderTarget(g_application->renderer(), old_target);
}

void c_image::draw(Vector2 pos, Vector2 size, c_viewport *viewport)
{
	if (viewport == nullptr)
		viewport = g_application->central_widget()->viewport();

	SDL_Rect dest = {
			static_cast<int>(pos.x), static_cast<int>(pos.y),
			static_cast<int>(size.x), static_cast<int>(size.y)
		};
	SDL_RenderCopyEx(viewport->renderer(), _texture, NULL, &dest, 0, NULL, SDL_FLIP_NONE);
}

SDL_Surface *c_image::surface(){ return (_surface); }

SDL_Texture	*c_image::texture(){ return (_texture); }

Vector2 &c_image::size(){ return (_size); }

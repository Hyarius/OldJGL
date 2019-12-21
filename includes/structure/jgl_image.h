#ifndef JGL_IMAGE_H
#define JGL_IMAGE_H

#include "jgl_includes.h"
#include "jgl_basics_functions.h"
#include "jgl_vector.h"
#include "jgl_color.h"
#include "jgl_system.h"

class				c_image
{
private:
	SDL_Surface	*_surface;
	SDL_Texture	*_texture;
	Vector2 _size;

public:
	c_image();
	c_image(string path);
	c_image(size_t width, size_t height, Color p_color);
	c_image(SDL_Surface *p__surface);

	void draw(Vector2 pos, Vector2 size, c_viewport *viewport = nullptr);

	void active();
	void unactive();
	void save(string file_path);

	SDL_Surface *surface();
	SDL_Texture	*texture();
	Vector2 &size();

};

#endif

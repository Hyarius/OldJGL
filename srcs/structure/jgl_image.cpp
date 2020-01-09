#include "jgl.h"

c_image::c_image() : _surface(nullptr), _texture_id(0) {}

void c_image::upload_texture()
{
	if (_surface->format->BytesPerPixel == 3)
	{
		_internal_format = GL_RGB;
		if (_surface->format->Rmask == 0xff)
			_format = GL_RGB;
		else
			_format = GL_BGR;
	}
	else if (_surface->format->BytesPerPixel == 4)
	{
		_internal_format = GL_RGBA;
		if (_surface->format->Rmask == 0xff)
			_format = GL_RGBA;
		else
			_format = GL_BGRA;
	}

	glGenTextures(1, &_texture_id);
	glBindTexture(GL_TEXTURE_2D, _texture_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, _internal_format, _surface->w,
				_surface->h, 0, _format,
				GL_UNSIGNED_BYTE, _surface->pixels);

	glBindTexture(GL_TEXTURE_2D, 0);
}

c_image::c_image(string path)
{
	_surface = IMG_Load(path.c_str());
	_size = Vector2(_surface->w, _surface->h);
	if (_surface == NULL)
		error_exit(1, "Can't load " + path + " file");

	upload_texture();
}

c_image::c_image(size_t width, size_t height, Color p_color)
{
	_surface = create_surface_color(p_color);
	_size = Vector2(static_cast<int>(width), static_cast<int>(height));
	if (_surface == NULL)
		error_exit(1, "Can't create a surface of color " + to_string((int)(p_color.r * 255)) + "/" + to_string((int)(p_color.g * 255)) + "/" + to_string((int)(p_color.b * 255)) + "/" + to_string((int)(p_color.a * 255)));

	upload_texture();
}

c_image::c_image(SDL_Surface *p_surface)
{
	_surface = p_surface;
	_size = Vector2(_surface->w, _surface->h);
	if (_surface == NULL)
		error_exit(1, "bouh");

	upload_texture();
}

void c_image::save(string file_path)
{
	// https://www.codeproject.com/Questions/655714/How-to-write-openGl-offscreen-data-in-to-JPG-image
}

void c_image::draw(Vector2 p_pos, Vector2 p_size, c_viewport *viewport)
{
	if (_surface != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, _texture_id);
		draw_image(p_pos, p_size);
	}
	else
	{
		draw_rectangle(p_pos, p_size, Color(0.2f, 0.2f, 0.2f));
		draw_rectangle(p_pos + 4, p_size - 8, Color(0.4f, 0.4f, 0.4f));
	}
}

#include "jgl.h"

namespace jgl
{
	Image::Image() : _path("unknow"), _surface(nullptr), _texture_id(0) {}

	void Image::upload_texture()
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

	Image::Image(jgl::String path)
	{
		_path = path;
		_surface = IMG_Load(path.std().c_str());
		if (_surface == NULL)
			error_exit(1, "Can't load an image from " + path + " file");
		_size = Vector2(_surface->w, _surface->h);

		upload_texture();
	}

	Image::Image(size_t width, size_t height, Color p_color)
	{
		_path = "unknow";
		_surface = create_surface_color(p_color);
		if (_surface == NULL)
			error_exit(1, "Can't create a surface of color " + std::to_string((int)(p_color.r * 255)) + "/" +
				std::to_string((int)(p_color.g * 255)) + "/" + std::to_string((int)(p_color.b * 255)) + "/" + std::to_string((int)(p_color.a * 255)));

		_size = Vector2(static_cast<int>(width), static_cast<int>(height));
		upload_texture();
	}

	Image::Image(SDL_Surface* p_surface)
	{
		_path = "unknow";
		_surface = p_surface;
		_size = Vector2(_surface->w, _surface->h);

		upload_texture();
	}
	
	Image::~Image()
	{
		_path.~String();
		if (_surface != nullptr)
		{
			SDL_FreeSurface(_surface);
			glDeleteTextures(1, &_texture_id);
		}

	}

	void Image::save(jgl::String file_path)
	{
		// https://www.codeproject.com/Questions/655714/How-to-write-openGl-offscreen-data-in-to-JPG-image
	}

	void Image::draw(const Vector2 p_pos, const Vector2 p_size, const float p_alpha, const Viewport* viewport) const
	{
		if (_surface != NULL)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _texture_id);
			draw_image(p_pos, p_size, p_alpha, viewport);
		}
		else
		{
			fill_rectangle(p_pos, p_size, Color(0.2f, 0.2f, 0.2f), viewport);
			fill_rectangle(p_pos + 4, p_size - 8, Color(0.4f, 0.4f, 0.4f), viewport);
		}
	}
}
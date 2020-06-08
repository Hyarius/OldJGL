#ifndef JGL_IMAGE_H
#define JGL_IMAGE_H

#include "jgl_includes.h"
#include "jgl_basics_functions.h"
#include "jgl_vector.h"
#include "jgl_color.h"
#include "jgl_system.h"

namespace jgl
{
	class				Image
	{
	protected:
		jgl::String _path;
		SDL_Surface* _surface;
		Vector2 _size;
		GLenum _format;
		GLint _internal_format;
		GLuint _texture_id;

	public:
		Image();
		Image(jgl::String path);
		Image(size_t width, size_t height, Color p_color);
		Image(SDL_Surface* p_surface);

		~Image();

		void draw(Vector2 p_pos, Vector2 p_size, float p_alpha = 1.0f, Viewport* viewport = nullptr);
		void upload_texture();
		void save(jgl::String file_path);

		jgl::String path() { return (_path); }
		SDL_Surface* surface() { return (_surface); }
		Vector2 size() { return (_size); }
		GLenum format() { return (_format); }
		GLint internal_format() { return (_internal_format); }
		GLuint texture_id() { return (_texture_id); }
	};
}
#endif

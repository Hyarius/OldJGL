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

		void draw(const Vector2 p_pos, const Vector2 p_size, const float p_alpha = 1.0f, const Viewport* viewport = nullptr) const ;
		void upload_texture();
		void save(jgl::String file_path);

		const jgl::String path() const { return (_path); }
		const SDL_Surface* surface() const { return (_surface); }
		const Vector2 size() const { return (_size); }
		const GLenum format() const { return (_format); }
		const GLint internal_format() const { return (_internal_format); }
		const GLuint texture_id() const { return (_texture_id); }
	};
}
#endif

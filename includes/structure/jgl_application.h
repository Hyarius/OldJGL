#ifndef JGL_APPLICATION_H
#define JGL_APPLICATION_H

#include "jgl_includes.h"
#include "jgl_vector.h"
#include "jgl_color.h"
#include "jgl_viewport.h"

extern std::string color_shader_vert;
extern std::string color_shader_frag;
extern std::string texture_shader_vert;
extern std::string texture_shader_frag;
extern std::string color_model_shader_vert;
extern std::string color_model_shader_frag;
extern std::string texture_model_shader_vert;
extern std::string texture_model_shader_frag;

namespace jgl
{
	class Application
	{
	protected:
		SDL_Window* _window;
		SDL_GLContext _context;
		Viewport* _viewport;
		Viewport* _active_viewport;
		Vector2 _size;

		GLuint _program_color;
		GLuint _program_texture;
		GLuint _program_color_model;
		GLuint _program_texture_model;

		GLuint _vertex_array;

		GLuint _vertex_buffer;
		GLuint _color_buffer;
		GLuint _texture_buffer;

		GLuint _matrix_colorID;
		GLuint _pos_colorID;
		GLuint _dir_light_colorID;
		GLuint _rot_colorID;

		GLuint _matrix_textureID;
		GLuint _pos_textureID;
		GLuint _rot_textureID;
		GLuint _dir_light_textureID;
		GLuint _texture_textureID;

		GLuint _alpha_textureID;

		GLuint _textureID;
		GLuint _alphaID;

		size_t _max_fps;
		float _fps_ratio;

		class Window* _central_widget;
		bool _play;
		SDL_Event _event;
		int _poll_ret;

	public:
		Application(jgl::String name, Vector2 p_size = Vector2(840, 680), Color p_color = Color(50, 50, 50));

		SDL_Window* window() { return (_window); }
		SDL_GLContext* context() { return (&_context); }
		Viewport* viewport() { return (_viewport); }
		Viewport* active_viewport() { return (_active_viewport); }
		Vector2 size() { return (_size); }
		GLuint program_color() { return (_program_color); }
		GLuint program_texture() { return (_program_texture); }
		GLuint program_color_model() { return (_program_color_model); }
		GLuint program_texture_model() { return (_program_texture_model); }
		GLuint vertex_array() { return (_vertex_array); }
		GLuint vertex_buffer() { return (_vertex_buffer); }
		GLuint color_buffer() { return (_color_buffer); }
		GLuint texture_buffer() { return (_texture_buffer); }

		GLuint textureID() { return (_textureID); }
		GLuint alphaID() { return (_alphaID); }

		GLuint matrix_colorID() { return (_matrix_colorID); }
		GLuint pos_colorID() { return (_pos_colorID); }
		GLuint dir_light_colorID() { return (_dir_light_colorID); }
		GLuint rot_colorID() { return (_rot_colorID); }

		GLuint matrix_textureID() { return (_matrix_textureID); }
		GLuint pos_textureID() { return (_pos_textureID); }
		GLuint rot_textureID() { return (_rot_textureID); }
		GLuint dir_light_textureID() { return (_dir_light_textureID); }
		GLuint texture_textureID() { return (_texture_textureID); }
		GLuint alpha_textureID() { return (_alpha_textureID); }

		size_t max_fps() { return (_max_fps); }
		float fps_ratio() { return (_fps_ratio); }
		int poll_ret() { return (_poll_ret); }
		class Widget* central_widget() { return ((Widget*)_central_widget); }
		bool play() { return (_play); }
		SDL_Event* event() { return (&_event); }

		void set_active_viewport(class Viewport* p_active_viewport) { if (p_active_viewport == nullptr)_active_viewport = _viewport; _active_viewport = p_active_viewport; }
		void set_max_fps(int p_max_fps) { _max_fps = p_max_fps; _fps_ratio = 60.0f / p_max_fps; }
		void set_fps_ratio(float p_ratio) { _fps_ratio = p_ratio; }
		void check_frame(bool draw = false);
		void reset_viewport() { _active_viewport = _viewport; _viewport->use(); }
		void set_font_path(jgl::String p_font_path);
		void quit();
		void set_background(Color p_color);
		void resize(Vector2 p_size);
		void select();
		void clear();
		void render();
		int run();
	};

	GLuint		load_shaders(
		std::string p_vertex_file_path,
		std::string p_fragment_file_path
	);
}

extern jgl::Application *g_application;

#endif

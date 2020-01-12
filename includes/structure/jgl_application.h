#ifndef JGL_APPLICATION_H
#define JGL_APPLICATION_H

#include "jgl_includes.h"
#include "jgl_vector.h"
#include "jgl_color.h"
#include "jgl_viewport.h"

extern string color_shader_vert;
extern string color_shader_frag;
extern string texture_shader_vert;
extern string texture_shader_frag;
extern string color_model_shader_vert;
extern string color_model_shader_frag;
extern string texture_model_shader_vert;
extern string texture_model_shader_frag;

class c_application
{
private:
	SDL_Window *_window;
	SDL_GLContext _context;
	c_viewport *_viewport;
	c_viewport *_active_viewport;
	Vector2 _size;

	GLuint _program_color;
	GLuint _program_sprite;
	GLuint _program_color_model;
	GLuint _program_sprite_model;

	GLuint _vertex_array;

	GLuint _vertex_buffer;
	GLuint _color_buffer;
	GLuint _texture_buffer;
	GLuint _alpha_buffer;

	GLuint _matrix_colorID;
	GLuint _matrix_textureID;

	GLuint _texture_textureID;
	GLuint _textureID;

	class c_window *_central_widget;
	bool _play;
	SDL_Event _event;

public:
	c_application(string name, Vector2 p_size = Vector2(), Color p_color = Color(50, 50, 50));

	SDL_Window *window(){return (_window);}
	SDL_GLContext *context(){return (&_context);}
	c_viewport *viewport(){return (_viewport);}
	c_viewport *active_viewport(){return (_active_viewport);}
	Vector2 size(){return (_size);}
	GLuint program_color(){return (_program_color);}
	GLuint program_sprite(){return (_program_sprite);}
	GLuint program_color_model(){return (_program_color_model);}
	GLuint program_sprite_model(){return (_program_sprite_model);}
	GLuint vertex_array(){return (_vertex_array);}
	GLuint vertex_buffer(){return (_vertex_buffer);}
	GLuint color_buffer(){return (_color_buffer);}
	GLuint texture_buffer(){return (_texture_buffer);}
	GLuint alpha_buffer(){return (_alpha_buffer);}
	GLuint textureID(){return (_textureID);}
	GLuint matrix_colorID(){return (_matrix_colorID);}
	GLuint matrix_textureID(){return (_matrix_textureID);}
	class c_window *central_widget(){return (_central_widget);}
	bool play(){return (_play);}
	SDL_Event *event(){return (&_event);}

	void set_active_viewport(class c_viewport *p_active_viewport){if (p_active_viewport == nullptr)_active_viewport = _viewport;_active_viewport = p_active_viewport;}
	void reset_viewport(){_active_viewport = _viewport;_viewport->use();}
	void set_font_path(string p_font_path);
	void quit();
	void set_background(Color p_color = Color(50, 50, 50));
	void resize(Vector2 p_size);
	void select();
	void clear();
	void render();
	int run();
};

GLuint		load_shaders(
				string p_vertex_file_path,
				string p_fragment_file_path
			);

#endif

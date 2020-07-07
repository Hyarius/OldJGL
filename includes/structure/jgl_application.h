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
		const Viewport* _active_viewport;
		Vector2 _size;

		GLuint _program_color;
		GLuint _program_texture;
		GLuint _program_color_model;
		GLuint _program_texture_model;

		std::vector<GLuint> _custom_program;

		GLuint _vertex_array;

		GLuint _vertex_buffer;
		GLuint _color_buffer;
		GLuint _texture_buffer;

		GLuint _pos_colorID;
		GLuint _rot_colorID;
		GLuint _size_colorID;
		GLuint _MVP_colorID;
		GLuint _view_matrix_colorID;
		GLuint _model_matrix_colorID;
		GLuint _alpha_colorID;
		GLuint _light_pos_colorID;
		GLuint _light_dir_colorID;
		GLuint _light_color_colorID;
		GLuint _camera_dir_colorID;
		GLuint _material_ka_colorID;
		GLuint _material_kd_colorID;
		GLuint _material_ks_colorID;
		GLuint _material_ke_colorID;
		GLuint _material_ns_colorID;
		GLuint _material_ni_colorID;
		GLuint _material_d_colorID;
		GLuint _material_illum_colorID;

		GLuint _pos_textureID;
		GLuint _rot_textureID;
		GLuint _size_textureID;
		GLuint _MVP_textureID;
		GLuint _view_matrix_textureID;
		GLuint _model_matrix_textureID;
		GLuint _alpha_textureID;
		GLuint _light_pos_textureID;
		GLuint _light_dir_textureID;
		GLuint _light_color_textureID;
		GLuint _camera_dir_textureID;
		GLuint _material_ka_textureID;
		GLuint _material_kd_textureID;
		GLuint _material_ks_textureID;
		GLuint _material_ke_textureID;
		GLuint _material_ns_textureID;
		GLuint _material_ni_textureID;
		GLuint _material_d_textureID;
		GLuint _material_illum_textureID;
		GLuint _material_ambiant_texture_textureID;
		GLuint _material_normal_texture_textureID;
		GLuint _material_diffuse_texture_textureID;
		GLuint _material_specular_texture_textureID;
		GLuint _material_specular_hight_light_textureID;
		GLuint _material_alpha_texture_textureID;
		GLuint _material_bump_texture_textureID;

		GLuint _textureID;
		GLuint _alphaID;

		size_t _max_fps;
		float _fps_ratio;

		class Window* _central_widget;
		bool _play;
		SDL_Event _event;
		int _poll_ret;

	public:
		Application(const jgl::String name, const Vector2 p_size = Vector2(840, 680), const Color p_color = Color(50, 50, 50));

		SDL_Window* window() { return (_window); }
		SDL_GLContext* context() { return (&_context); }
		const Viewport* viewport() { return (_viewport); }
		const Viewport* active_viewport() const { return (_active_viewport); }
		const Vector2 size() { return (_size); }
		const GLuint add_custom_shader(const jgl::String p_vertex_content, const jgl::String p_fragment_content);
		const GLuint get_custom_program(const size_t index);
		const GLuint get_custom_uniform(const GLuint p_program, const jgl::String p_param);

		const GLuint program_color() const { return (_program_color); }
		const GLuint program_texture() const { return (_program_texture); }
		const GLuint program_color_model() const { return (_program_color_model); }
		const GLuint program_texture_model() const { return (_program_texture_model); }
		const GLuint vertex_array() const { return (_vertex_array); }
		const GLuint vertex_buffer() const { return (_vertex_buffer); }
		const GLuint color_buffer() const { return (_color_buffer); }
		const GLuint texture_buffer() const { return (_texture_buffer); }

		const GLuint textureID() const { return (_textureID); }
		const GLuint alphaID() const { return (_alphaID); }

		const GLuint pos_colorID() const { return (_pos_colorID); }
		const GLuint rot_colorID() const { return (_rot_colorID); }
		const GLuint size_colorID() const { return (_size_colorID); }
		const GLuint MVP_colorID() const { return (_MVP_colorID); }
		const GLuint view_matrix_colorID() const { return (_view_matrix_colorID); }
		const GLuint model_matrix_colorID() const { return (_model_matrix_colorID); }
		const GLuint alpha_colorID() const { return (_alpha_colorID); }
		const GLuint light_pos_colorID() const { return (_light_pos_colorID); }
		const GLuint light_dir_colorID() const { return (_light_dir_colorID); }
		const GLuint light_color_colorID() const { return (_light_color_colorID); }
		const GLuint camera_dir_colorID() const { return (_camera_dir_colorID); }
		const GLuint material_ka_colorID() const { return (_material_ka_colorID); }
		const GLuint material_kd_colorID() const { return (_material_kd_colorID); }
		const GLuint material_ks_colorID() const { return (_material_ks_colorID); }
		const GLuint material_ke_colorID() const { return (_material_ke_colorID); }
		const GLuint material_ns_colorID() const { return (_material_ns_colorID); }
		const GLuint material_ni_colorID() const { return (_material_ni_colorID); }
		const GLuint material_d_colorID() const { return (_material_d_colorID); }
		const GLuint material_illum_colorID() const { return (_material_illum_colorID); }

		const GLuint pos_textureID() const { return (_pos_textureID); }
		const GLuint rot_textureID() const { return (_rot_textureID); }
		const GLuint size_textureID() const { return (_size_textureID); }
		const GLuint MVP_textureID() const { return (_MVP_textureID); }
		const GLuint view_matrix_textureID() const { return (_view_matrix_textureID); }
		const GLuint model_matrix_textureID() const { return (_model_matrix_textureID); }
		const GLuint alpha_textureID() const { return (_alpha_textureID); }
		const GLuint light_pos_textureID() const { return (_light_pos_textureID); }
		const GLuint light_dir_textureID() const { return (_light_dir_textureID); }
		const GLuint light_color_textureID() const { return (_light_color_textureID); }
		const GLuint camera_dir_textureID() const { return (_camera_dir_textureID); }
		const GLuint material_ka_textureID() const { return (_material_ka_textureID); }
		const GLuint material_kd_textureID() const { return (_material_kd_textureID); }
		const GLuint material_ks_textureID() const { return (_material_ks_textureID); }
		const GLuint material_ke_textureID() const { return (_material_ke_textureID); }
		const GLuint material_ns_textureID() const { return (_material_ns_textureID); }
		const GLuint material_ni_textureID() const { return (_material_ni_textureID); }
		const GLuint material_d_textureID() const { return (_material_d_textureID); }
		const GLuint material_illum_textureID() const { return (_material_illum_textureID); }
		const GLuint material_ambiant_texture_textureID() const { return (_material_ambiant_texture_textureID); }
		const GLuint material_normal_texture_textureID() const { return (_material_normal_texture_textureID); }
		const GLuint material_diffuse_texture_textureID() const { return (_material_diffuse_texture_textureID); }
		const GLuint material_specular_texture_textureID() const { return (_material_specular_texture_textureID); }
		const GLuint material_specular_hight_light_textureID() const { return (_material_specular_hight_light_textureID); }
		const GLuint material_alpha_texture_textureID() const { return (_material_alpha_texture_textureID); }
		const GLuint material_bump_texture_textureID() const { return (_material_bump_texture_textureID); }

		const size_t max_fps() const { return (_max_fps); }
		const float fps_ratio() const { return (_fps_ratio); }
		const int poll_ret() const { return (_poll_ret); }
		class Widget* central_widget() const { return ((Widget*)_central_widget); }
		const bool play() const { return (_play); }
		SDL_Event* event() { return (&_event); }

		void set_active_viewport(const class Viewport* p_active_viewport) { if (p_active_viewport == nullptr)_active_viewport = _viewport; else _active_viewport = p_active_viewport; }
		void set_max_fps(const int p_max_fps) { _max_fps = p_max_fps; _fps_ratio = 60.0f / p_max_fps; }
		void set_fps_ratio(const float p_ratio) { _fps_ratio = p_ratio; }
		void check_frame(const bool draw = false);
		void reset_viewport() { _active_viewport = _viewport; _viewport->use(); }
		void quit();
		void set_background(const Color p_color);
		void resize(const Vector2 p_size);
		void select();
		void clear();
		void render();
		int run();
	};

	GLuint		load_shaders(
		const std::string p_vertex_content,
		const std::string p_fragment_content
	);

	void start_jgl();
	void quit_jgl();
}


extern jgl::Application *g_application;

#endif

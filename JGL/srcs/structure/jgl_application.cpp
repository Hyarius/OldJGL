#include "jgl.h"

jgl::Application* g_application;
jgl::Perlin* g_perlin;

namespace jgl
{
	Application::Application(jgl::String name, Vector2 p_size, Color p_color, bool multithread) :
		_opengl_control_mutex()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

		_multithread = multithread;
		//check_sdl_error(__FILE__, __LINE__);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

		TTF_Init();

		//check_sdl_error(__FILE__, __LINE__);

		_size = p_size;
		if (p_size.x <= 1 && p_size.y <= 1)
		{
			SDL_DisplayMode current;
			SDL_GetDesktopDisplayMode(0, &current);

			//check_sdl_error(__FILE__, __LINE__);
			if (p_size == Vector2())
				_size = Vector2(current.w * 0.8f, current.h * 0.8f);
			else
				_size = Vector2(current.w * p_size.x, current.h * p_size.y);
		}

		//check_sdl_error(__FILE__, __LINE__);

		_window = SDL_CreateWindow(name->std().c_str(),
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			static_cast<int>(_size.x), static_cast<int>(_size.y),
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

		//check_sdl_error(__FILE__, __LINE__);

		if (_window == nullptr)
		{
			error_exit(1, "Error with window creation");
		}
		_context = SDL_GL_CreateContext(_window);

		//check_sdl_error(__FILE__, __LINE__);

		if (_context == nullptr)
		{
			error_exit(1, "Error with context creation");
		}

		SDL_WarpMouseInWindow(_window, static_cast<int>(_size.x / 2), static_cast<int>(_size.y / 2));

		glewExperimental = true;
		SDL_GL_MakeCurrent(_window, _context);
		int err = glewInit();
		if (err != GLEW_OK)
		{
			std::cout << "bug : " << glewGetErrorString(err) << std::endl;
			exit(1);
		}

		_background = p_color;

		glClearColor((GLclampf)p_color.r, (GLclampf)p_color.g, (GLclampf)p_color.b, 1.0f);

		glGenVertexArrays(1, &_vertex_array);

		glBindVertexArray(_vertex_array);

		_custom_program.clear();
		_program_color = load_shaders(color_shader_vert, color_shader_frag);
		_program_texture = load_shaders(texture_shader_vert, texture_shader_frag);
		_program_color_model = load_shaders(color_model_shader_vert, color_model_shader_frag);
		_program_texture_model = load_shaders(texture_model_shader_vert, texture_model_shader_frag);

		_color_simpleID = glGetUniformLocation(_program_color, "vertexColor");
		_textureID = glGetUniformLocation(_program_texture, "textureID");
		if (_textureID == -1)
			error_exit(1, "Error on _textureID");
		_alphaID = glGetUniformLocation(_program_texture, "alpha_value");
		if (_alphaID == -1)
			error_exit(1, "Error on _alphaID");


		_pos_colorID = glGetUniformLocation(_program_color_model, "pos");
		_rot_colorID = glGetUniformLocation(_program_color_model, "rot");
		_size_colorID = glGetUniformLocation(_program_color_model, "size");
		_MVP_colorID = glGetUniformLocation(_program_color_model, "MVP");
		_view_matrix_colorID = glGetUniformLocation(_program_color_model, "view_matrix");
		_model_matrix_colorID = glGetUniformLocation(_program_color_model, "model_matrix");
		_alpha_colorID = glGetUniformLocation(_program_color_model, "alpha");
		_light_pos_colorID = glGetUniformLocation(_program_color_model, "light_pos");
		_light_dir_colorID = glGetUniformLocation(_program_color_model, "light_dir");
		_light_color_colorID = glGetUniformLocation(_program_color_model, "light_color");
		_camera_dir_colorID = glGetUniformLocation(_program_color_model, "camera_dir");
		_material_ka_colorID = glGetUniformLocation(_program_color_model, "material_ka");
		_material_kd_colorID = glGetUniformLocation(_program_color_model, "material_kd");
		_material_ks_colorID = glGetUniformLocation(_program_color_model, "material_ks");
		_material_ke_colorID = glGetUniformLocation(_program_color_model, "material_ke");
		_material_ns_colorID = glGetUniformLocation(_program_color_model, "material_ns");
		_material_ni_colorID = glGetUniformLocation(_program_color_model, "material_ni");
		_material_d_colorID = glGetUniformLocation(_program_color_model, "material_d");
		_material_illum_colorID = glGetUniformLocation(_program_color_model, "material_illum");


		_pos_textureID = glGetUniformLocation(_program_texture_model, "pos");
		_rot_textureID = glGetUniformLocation(_program_texture_model, "rot");
		_uint32_textureID = glGetUniformLocation(_program_texture_model, "size");
		_MVP_textureID = glGetUniformLocation(_program_texture_model, "MVP");
		_view_matrix_textureID = glGetUniformLocation(_program_texture_model, "view_matrix");
		_model_matrix_textureID = glGetUniformLocation(_program_texture_model, "model_matrix");
		_alpha_textureID = glGetUniformLocation(_program_texture_model, "alpha");
		_light_pos_textureID = glGetUniformLocation(_program_texture_model, "light_pos");
		_light_dir_textureID = glGetUniformLocation(_program_texture_model, "light_dir");
		_light_color_textureID = glGetUniformLocation(_program_texture_model, "light_color");
		_camera_dir_textureID = glGetUniformLocation(_program_texture_model, "camera_dir");
		_material_ka_textureID = glGetUniformLocation(_program_texture_model, "material_ka");
		_material_kd_textureID = glGetUniformLocation(_program_texture_model, "material_kd");
		_material_ks_textureID = glGetUniformLocation(_program_texture_model, "material_ks");
		_material_ke_textureID = glGetUniformLocation(_program_texture_model, "material_ke");
		_material_ns_textureID = glGetUniformLocation(_program_texture_model, "material_ns");
		_material_ni_textureID = glGetUniformLocation(_program_texture_model, "material_ni");
		_material_d_textureID = glGetUniformLocation(_program_texture_model, "material_d");
		_material_illum_textureID = glGetUniformLocation(_program_texture_model, "material_illum");
		_material_ambiant_texture_textureID = glGetUniformLocation(_program_texture_model, "ambiant_texture");
		_material_normal_texture_textureID = glGetUniformLocation(_program_texture_model, "normal_texture");
		_material_diffuse_texture_textureID = glGetUniformLocation(_program_texture_model, "diffuse_texture");
		_material_specular_texture_textureID = glGetUniformLocation(_program_texture_model, "specular_texture");
		_material_specular_hight_light_textureID = glGetUniformLocation(_program_texture_model, "specular_hight_light");
		_material_alpha_texture_textureID = glGetUniformLocation(_program_texture_model, "alpha_texture");
		_material_bump_texture_textureID = glGetUniformLocation(_program_texture_model, "bump_texture");


		glGenTextures(1, &_textureID);
		glBindTexture(GL_TEXTURE_2D, _textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_BLEND);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glFrontFace(GL_CCW);

		//glEnable(GL_SCISSOR_TEST);

		glBindVertexArray(_vertex_array);

		glGenBuffers(1, &_vertex_buffer);
		glGenBuffers(1, &_color_buffer);
		glGenBuffers(1, &_texture_buffer);

		_input_refresh = 2400;
		_render_refresh = 1200;
		
		glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, static_cast<GLuint>(sizeof(GLfloat) * _size.x * _size.y * 3), NULL, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, _color_buffer);
		glBufferData(GL_ARRAY_BUFFER, static_cast<GLuint>(sizeof(GLfloat) * _size.x * _size.y * 4), NULL, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, _texture_buffer);
		glBufferData(GL_ARRAY_BUFFER, static_cast<GLuint>(sizeof(GLfloat) * _size.x * _size.y * 4), NULL, GL_DYNAMIC_DRAW);
	
		_play = true;
		_poll_ret = 0;
		_event = SDL_Event();

		if (g_application == nullptr)
			select();

		_viewport = new Viewport();
		_viewport->resize(Vector2(0, 0), _size);
		_active_viewport = _viewport;

		_central_widget = nullptr;

		_central_widget = new Window();
		_central_widget->set_geometry(Vector2(0, 0), _size);
		_central_widget->set_color(p_color);
		_central_widget->set_layer(1);
		_central_widget->activate();
		//_viewport->use();
		g_font_path = "";
		start_jgl();

		SDL_GL_SetSwapInterval(0);
		
		_main_thread = std::this_thread::get_id();
		_active_opengl_thread_id = std::this_thread::get_id();
	}

	void Application::take_context_control()
	{
		_opengl_control_mutex.lock();
		if (SDL_GL_MakeCurrent(_window, _context) != 0)
		{
			std::cout << "Error : " << SDL_GetError();
		}
	}

	void Application::release_context_control()
	{
		if (SDL_GL_MakeCurrent(NULL, NULL) != 0)
		{
			std::cout << "Error : " << SDL_GetError();
		}
		_opengl_control_mutex.unlock();
	}

	void Application::resize(Vector2 p_size)
	{
		_size = p_size;
		take_context_control();
		SDL_SetWindowSize(_window, static_cast<int>(_size.x), static_cast<int>(_size.y));
		_central_widget->set_geometry(Vector2(0, 0), _size);
		SDL_SetWindowPosition(_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
		release_context_control();
	}

	void Application::set_background(Color p_color)
	{
		_central_widget->set_color(p_color);
	}

	void Application::select()
	{
		g_application = this;
	}

	void Application::clear()
	{
		take_context_control();
		glClearColor(_background.r, _background.g, _background.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		release_context_control();
	}

	void Application::render()
	{
		take_context_control();
		SDL_GL_SwapWindow(_window);
		release_context_control();
	}

	void start_jgl()
	{
		if (SDL_WasInit(SDL_INIT_EVERYTHING) == SDL_FALSE)
		{
			SDL_Init(SDL_INIT_EVERYTHING);
			IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
			TTF_Init();
			SDL_StartTextInput();
		}
		srand(static_cast<unsigned int>(time(NULL)));
		g_perlin = new jgl::Perlin(rand());
		g_mouse = new Mouse();
		g_keyboard = new Keyboard();
	}

	void quit_jgl()
	{
		Mesh::delete_base_material();
		Material::delete_empty_texture();

		if (g_mouse != nullptr)
		{
			delete g_mouse;
			g_mouse = nullptr;
		}
		if (g_keyboard != nullptr)
		{
			delete g_keyboard;
			g_keyboard = nullptr;
		}
		if (g_perlin != nullptr)
		{
			delete g_perlin;
			g_perlin = nullptr;
		}
		delete_loaded_char();
	}

	double perlin_noise(double x, double y, double z)
	{
		return (g_perlin->noise(x, y, z));
	}

	void Application::quit()
	{
		_play = false;
		_central_widget->quit_children();

		delete _viewport;
		_central_widget->destroy_widget();
		delete _central_widget;
		_central_widget = nullptr;

		quit_jgl();
	}

	void Application::handle_input()
	{
		if (_central_widget != nullptr)
		{
			_central_widget->handle_event();
			_central_widget->update_children();
		}

		
	}

	void Application::handle_actualize()
	{
		take_context_control();
		_time = SDL_GetTicks();

		g_mouse->actualize();
		g_keyboard->actualize();
		release_context_control();
	}

	void Application::handle_render()
	{
		clear();

		if (_central_widget != nullptr)
			_central_widget->render_children();

		render();
	}

	void Application::run_input()
	{
		_play = true;

		while (_play == true)
		{
			handle_actualize();
			handle_input();
		}
	}

	std::thread Application::spawn_input_thread()
	{
		return (std::thread([this] {this->run_input(); }));
	}

	void Application::read_input()
	{
		take_context_control();
		_poll_ret = SDL_PollEvent(&_event);
		release_context_control();

		if (_poll_ret != 0)
		{
			if (_event.type == SDL_QUIT)
			{
				_play = false;
			}
		}
	}

	int Application::run()
	{
		if (_multithread == true)
		{
			std::thread input_thread = spawn_input_thread();

			while (_play == true)
			{
				read_input();
				handle_render();
			}

			input_thread.join();
		}
		else
		{
			while (_play == true)
			{
				read_input();
				handle_actualize();
				handle_input();
				handle_render();
			}
		}

		return (0);
	}

	const GLuint Application::add_custom_shader(jgl::String p_vertex_content, jgl::String p_fragment_content)
	{
		GLuint result = load_shaders(p_vertex_content->std(), p_fragment_content->std());
		_custom_program.push_back(result);

		return (result);
	}
	const GLuint Application::get_custom_program(uint32_t index)
	{
		if (index >= _custom_program.size())
			return (0);
		return (_custom_program[index]);
	}
	const GLuint Application::get_custom_uniform(GLuint p_program, jgl::String p_param)
	{
		return (glGetUniformLocation(p_program, p_param->std().c_str()));
	}
}

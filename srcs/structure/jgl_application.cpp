#include "jgl.h"

jgl::Application* g_application;

namespace jgl
{

	Application::Application(jgl::String name, Vector2 p_size, Color p_color)
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

		check_sdl_error(__FILE__, __LINE__);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

		srand(static_cast<unsigned int>(std::time(NULL)));
		TTF_Init();

		check_sdl_error(__FILE__, __LINE__);

		_size = p_size;
		if (p_size.x <= 1 && p_size.y <= 1)
		{
			SDL_DisplayMode current;
			SDL_GetDesktopDisplayMode(0, &current);

			check_sdl_error(__FILE__, __LINE__);
			if (p_size == Vector2())
				_size = Vector2(current.w * 0.8f, current.h * 0.8f);
			else
				_size = Vector2(current.w * p_size.x, current.h * p_size.y);
		}

		jgl::String tmp = name;

		check_sdl_error(__FILE__, __LINE__);

		_window = SDL_CreateWindow(tmp.std().c_str(),
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			static_cast<int>(_size.x), static_cast<int>(_size.y),
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

		check_sdl_error(__FILE__, __LINE__);
		if (_window == nullptr)
		{
			error_exit(1, "Error with window creation");
		}
		_context = SDL_GL_CreateContext(_window);

		check_sdl_error(__FILE__, __LINE__);
		if (_context == nullptr)
		{
			error_exit(1, "Error with context creation");
		}

		std::cout << "Graphical info :\n" << std::endl;
		std::cout << jgl::String((char*)(glGetString(GL_VENDOR))) + "\n" << std::endl;
		std::cout << jgl::String((char*)(glGetString(GL_RENDERER))) + "\n" << std::endl;
		std::cout << jgl::String((char*)(glGetString(GL_VERSION))) + "\n" << std::endl;
		std::cout << jgl::String((char*)(glGetString(GL_SHADING_LANGUAGE_VERSION))) + "\n" << std::endl;
		std::cout << "\n" << std::endl;

		//_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		//SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);

		SDL_WarpMouseInWindow(_window, static_cast<int>(_size.x / 2), static_cast<int>(_size.y / 2));

		_max_fps = 60;
		_fps_ratio = 1.0f;
		SDL_GL_MakeCurrent(_window,
			_context);
		int err = glewInit();
		if (err != GLEW_OK)
		{
			std::cout << "bug : " << glewGetErrorString(err) << std::endl;
			exit(1);
		}

		glClearColor((GLclampf)p_color.r, (GLclampf)p_color.g, (GLclampf)p_color.b, 1.0f);

		glGenVertexArrays(1, &_vertex_array);

		glBindVertexArray(_vertex_array);

		glGenBuffers(1, &_vertex_buffer);
		glGenBuffers(1, &_color_buffer);
		glGenBuffers(1, &_texture_buffer);

		_custom_program.clear();
		_program_color = load_shaders(color_shader_vert, color_shader_frag);
		_program_texture = load_shaders(texture_shader_vert, texture_shader_frag);
		_program_color_model = load_shaders(color_model_shader_vert, color_model_shader_frag);
		_program_texture_model = load_shaders(texture_model_shader_vert, texture_model_shader_frag);

		_textureID = glGetUniformLocation(_program_texture, "textureID");
		_alphaID = glGetUniformLocation(_program_texture, "alpha_value");

		_matrix_colorID = glGetUniformLocation(_program_color_model, "MVP");
		_pos_colorID = glGetUniformLocation(_program_color_model, "pos");
		_rot_colorID = glGetUniformLocation(_program_color_model, "rot");
		_dir_light_colorID = glGetUniformLocation(_program_color_model, "dir_light");

		_matrix_textureID = glGetUniformLocation(_program_texture_model, "MVP");
		_pos_textureID = glGetUniformLocation(_program_texture_model, "pos");
		_rot_textureID = glGetUniformLocation(_program_texture_model, "rot");
		_alpha_textureID = glGetUniformLocation(_program_texture_model, "alpha_value");
		_texture_textureID = glGetUniformLocation(_program_texture_model, "textureID");
		_dir_light_textureID = glGetUniformLocation(_program_texture_model, "dir_light");

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
		glFrontFace(GL_CW);

		glBindVertexArray(_vertex_array);
		glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, static_cast<GLuint>(sizeof(GLfloat) * _size.x * _size.y * 3), NULL, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, _color_buffer);
		glBufferData(GL_ARRAY_BUFFER, static_cast<GLuint>(sizeof(GLfloat) * _size.x * _size.y * 4), NULL, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, _texture_buffer);
		glBufferData(GL_ARRAY_BUFFER, static_cast<GLuint>(sizeof(GLfloat) * _size.x * _size.y * 4), NULL, GL_DYNAMIC_DRAW);

		_play = true;
		_poll_ret = 0;
		_event = SDL_Event();
		g_mouse = new Mouse();
		g_keyboard = new Keyboard();

		if (g_application == nullptr)
			select();

		_viewport = new Viewport();
		_viewport->resize(Vector2(0, 0), _size);
		_active_viewport = _viewport;

		_central_widget = nullptr;

		_central_widget = new Window();
		_central_widget->set_geometry(Vector2(0, 0), _size);
		_central_widget->set_color(p_color);
		_central_widget->activate();
		//_viewport->use();

		SDL_StartTextInput();
		//set_max_fps(6000);
		_time = SDL_GetTicks();
}

	void Application::resize(Vector2 p_size)
	{
		_size = p_size;

		SDL_SetWindowSize(_window, static_cast<int>(_size.x), static_cast<int>(_size.y));
		_central_widget->set_geometry(Vector2(0, 0), _size);
		SDL_SetWindowPosition(_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
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
		glClearColor(0, 0, 0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Application::render()
	{
		SDL_GL_SwapWindow(_window);
	}

	void Application::quit()
	{
		_play = false;
	}

	int Application::run()
	{
		_play = true;

		while (_play == true)
		{
			g_mouse->actualize();
			g_keyboard->actualize();

			clear();

			//_central_widget->render();

			_central_widget->render_children();

			_central_widget->handle_event();

			_central_widget->update_children();

			check_frame(true);

			render();

			//SDL_RenderSetViewport(_renderer, NULL);

			_poll_ret = SDL_PollEvent(&_event);

			if (_poll_ret != 0)
			{
				if (_event.type == SDL_QUIT)
					quit();
			}
		}

		_central_widget->quit_children();

		return (0);
	}

	GLuint Application::add_custom_shader(jgl::String p_vertex_content, jgl::String p_fragment_content)
	{
		GLuint result = load_shaders(p_vertex_content.std(), p_fragment_content.std());
		_custom_program.push_back(result);

		return (result);
	}
	GLuint Application::get_custom_program(size_t index)
	{
		if (index >= _custom_program.size())
			return (0);
		return (_custom_program[index]);
	}
	GLuint Application::get_custom_uniform(GLuint p_program, jgl::String p_param)
	{
		return (glGetUniformLocation(p_program, p_param.std().c_str()));
	}
}

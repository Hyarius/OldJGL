#include "jgl.h"

c_application *g_application = nullptr;

c_application::c_application(string name, Vector2 p_size, Color p_color)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

	srand(time(NULL));
	TTF_Init();

	_size = p_size;
	if (p_size.x <= 1 && p_size.y <= 1)
	{
		SDL_DisplayMode current;
		SDL_GetDesktopDisplayMode(0, &current);
		if (p_size == Vector2())
			_size = Vector2(current.w * 0.8f, current.h * 0.8f);
		else
			_size = Vector2(current.w * p_size.x, current.h * p_size.y);
	}

	string tmp = string(name.begin(), name.end());

	_window = SDL_CreateWindow(tmp.c_str(),
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		static_cast<int>(_size.x), static_cast<int>(_size.y), 0);

	_context = SDL_GL_CreateContext(_window);
	//_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);

	glClearColor((GLclampf)p_color.r, (GLclampf)p_color.g, (GLclampf)p_color.b, 1.0f);

	glGenVertexArrays(1, &_vertex_array);

	glBindVertexArray(_vertex_array);

	glGenBuffers(1, &_vertex_buffer);
	glGenBuffers(1, &_color_buffer);
	glGenBuffers(1, &_texture_buffer);
	glGenBuffers(1, &_alpha_buffer);

	_program_color = load_shaders(color_shader_vert, color_shader_frag);
	_program_sprite = load_shaders(texture_shader_vert, texture_shader_frag);
	_program_color_model = load_shaders(color_model_shader_vert, color_model_shader_frag);
	_program_sprite_model = load_shaders(texture_model_shader_vert, texture_model_shader_frag);

	_matrix_colorID = glGetUniformLocation(_program_color_model, "MVP");
	_matrix_textureID = glGetUniformLocation(_program_sprite_model, "MVP");

	glGenTextures(1, &_textureID);
	glBindTexture(GL_TEXTURE_2D, _textureID);

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glBindVertexArray(_vertex_array);
	glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _size.x * _size.y \
										* 3, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, _color_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _size.x * _size.y \
										* 4, NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, _texture_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _size.x * _size.y \
										* 4, NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, _alpha_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _size.x * _size.y \
										* 4, NULL, GL_DYNAMIC_DRAW);

	g_mouse = new Mouse();
	g_keyboard = new Keyboard();

	if (g_application == nullptr)
		select();

	_viewport = new c_viewport();
	_viewport->resize(Vector2(0, 0), _size);
	_active_viewport = _viewport;

	_central_widget = nullptr;

	_central_widget = new c_window();
	_central_widget->set_geometry(Vector2(0, 0), _size);
	_central_widget->set_color(p_color);
	_central_widget->activate();

	//_viewport->use();

	SDL_StartTextInput();

}

void c_application::resize(Vector2 p_size)
{
	_size = p_size;

	SDL_SetWindowSize(_window, static_cast<int>(_size.x), static_cast<int>(_size.y));
	_central_widget->set_geometry(Vector2(0, 0), _size);
	SDL_SetWindowPosition(_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void c_application::set_background(Color p_color)
{
	_central_widget->set_color(p_color);
}

void c_application::select()
{
	g_application = this;
}

void c_application::clear()
{
	glClearColor(0, 0, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void c_application::render()
{
	SDL_GL_SwapWindow(_window);
}

void c_application::quit()
{
	_play = false;
}

int c_application::run()
{
	int ret;
	_play = true;

	while (_play == true)
	{
		clear();

		//_central_widget->render();
		_central_widget->render_children();

		_central_widget->handle_event();

		_central_widget->update_children();

		render();

		//SDL_RenderSetViewport(_renderer, NULL);

		ret = SDL_PollEvent(&_event);

		if (ret != 0)
		{
			if (_event.type == SDL_QUIT)
				quit();
		}

		g_mouse->actualize_mouse((ret == 0 ? nullptr : &_event));
	}

	_central_widget->quit_children();

	return (0);
}

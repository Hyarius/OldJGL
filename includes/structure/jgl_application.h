#ifndef JGL_APPLICATION_H
#define JGL_APPLICATION_H

class c_application
{
private:
	SDL_Window *_window;
	SDL_Renderer *_renderer;
	c_viewport *_viewport;
	Vector2 _win_size;

	class c_window *_central_widget;
	bool play;
	SDL_Event _event;

public:
	c_application(string name, Vector2 p_size = Vector2(), Color p_color = Color(50, 50, 50));

	SDL_Window *window();

	SDL_Renderer *renderer();

	SDL_Event *event();

	c_viewport *viewport(){return (_viewport);}

	void quit();

	class c_window *central_widget();

	void set_background(Color p_color = Color(50, 50, 50));

	void resize(Vector2 p_size);

	Vector2 &size();

	void select();

	void clear();

	void render();

	int run();
};

#endif

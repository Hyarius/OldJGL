#include "jgl.h"

size_t			saved_fps = 0;
int				nb_frame;
int				beginsecond = 0;
int				frame_actual;
Uint32			framestart;

int				get_frame_state(int div)
{
	int value = (int)(((double)(nb_frame) / (double)(g_application->max_fps())) * div) % (div);
	return ((value == div ? div - 1 : value));
}

void c_application::check_frame(bool draw)
{
	Vector2			coord;
	static string	str = "FPS";
	static unsigned int	framedelay = 0;

	coord = Vector2(50, 50);
	if (saved_fps != g_application->max_fps())
	{
		saved_fps = g_application->max_fps();
		framedelay = 1000.0f / static_cast<float>(saved_fps);
	}
	frame_actual = SDL_GetTicks();
	if (draw == true)
		draw_text(str, coord, 12, 0, text_color::white);
	if (beginsecond == 0)
		beginsecond = frame_actual;
	if (frame_actual - beginsecond > 1000)
	{
		str = "FPS = " + to_string(nb_frame);
		_fps_ratio = 60.0f / nb_frame;
		nb_frame = 0;
		beginsecond = 0;
	}
	else
		nb_frame++;
	if (framedelay > frame_actual - framestart)
		SDL_Delay(framedelay - (frame_actual - framestart));
	framestart = SDL_GetTicks();
}

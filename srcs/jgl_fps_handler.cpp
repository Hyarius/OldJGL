#include "jgl.h"

size_t			print_fps = 0;
size_t			saved_fps = 0;
int				nb_frame;
int				beginsecond = 0;
Uint32			old_time = 0;

namespace jgl
{
	int				get_frame_state(int div)
	{
		int value = (int)(((double)(nb_frame) / (double)(g_application->max_fps())) * div) % (div);
		return ((value == div ? div - 1 : value));
	}

	void Application::check_frame(bool draw)
	{
		static unsigned int	framedelay = 0;

		if (saved_fps != g_application->max_fps())
		{
			saved_fps = g_application->max_fps();
			print_fps = saved_fps;
			framedelay = static_cast<unsigned int>(1000.0f / static_cast<float>(saved_fps));
		}
		_time = SDL_GetTicks();
		if (beginsecond == 0)
			beginsecond = _time;
		if (_time - beginsecond > 1000)
		{
			print_fps = nb_frame;
			_fps_ratio = 60.0f / nb_frame;
			nb_frame = 0;
			beginsecond = 0;
		}
		else
			nb_frame++;
		if (framedelay > _time - old_time)
			SDL_Delay(framedelay - (_time - old_time));
		old_time = _time;
	}
}
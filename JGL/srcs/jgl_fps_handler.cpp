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
		Uint32 tmp = g_application->time() % 1000;
		float ratio = static_cast<float>(tmp) / 1000.0f;
		return (static_cast<int>(ratio * div));
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
		int32_t delta = framedelay - (_time - old_time);
		if (delta > 0)
		{
			//SDL_Delay(delta);
		}
		old_time = _time + delta;
	}
}
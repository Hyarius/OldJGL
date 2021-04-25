#include "jgl.h"

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

	void Application::check_frame(bool draw) const
	{
		
	}
}
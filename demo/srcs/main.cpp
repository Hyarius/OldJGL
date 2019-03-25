#include "demo_graphical.h"

void change_stat(t_data data)
{
	bool *value = (bool *)(data.data[0]);

	if ((*value) == true)
		*value = false;
	else
		*value = true;
}

int main()
{
	charge_log_file("Graphical demo");
	window_initialisation("Graphical demonstration");
	write_in_log("Graphical info :\n");
	write_in_log(string((char *)(glGetString(GL_VENDOR))) + "\n");
	write_in_log(string((char *)(glGetString(GL_RENDERER))) + "\n");
	write_in_log(string((char *)(glGetString(GL_VERSION))) + "\n");
	write_in_log(string((char *)(glGetString(GL_SHADING_LANGUAGE_VERSION))) + "\n");
	SDL_Event event;
	t_gui gui = t_gui(30, 20);
	bool play = true;
	bool state = true;

	t_vect coord[4];
	coord[0] = t_vect(SCREEN_WEIGHT / 4, SCREEN_HEIGHT / 4);
	coord[1] = t_vect(SCREEN_WEIGHT / 4 * 3, SCREEN_HEIGHT / 4);
	coord[2] = t_vect(SCREEN_WEIGHT / 4, SCREEN_HEIGHT / 4 * 3);
	coord[3] = t_vect(SCREEN_WEIGHT / 4 * 3, SCREEN_HEIGHT / 4 * 3);

	t_vect delta[4];
	delta[0] = t_vect(0, 0);
	delta[1] = t_vect(0, 0);
	delta[2] = t_vect(0, 0);
	delta[3] = t_vect(0, 0);

	t_color color = t_color(1.0, 0.0, 0.0);
	t_color delta_color = t_color(0.0, 0.0, 0.0);

	gui.add(new s_button(new s_text_button(	"PAUSE", DARK_GREY, //text info
								gui.unit * t_vect(10, 0.2), gui.unit * t_vect(10, 1.5), 4, //object info
								t_color(0.8, 0.8, 0.8), t_color(0.6, 0.6, 0.6)),
								change_stat, t_data(1, &state)));

	int count = 60;

	while (play == true)
	{
		prepare_screen();

		draw_rectangle(coord[0], coord[1], coord[2], coord[3], color);

		draw_centred_text("Exemple of text printing", 15, t_vect(SCREEN_WEIGHT / 2, SCREEN_HEIGHT - 40), WHITE);

		gui.draw_self();

		render_screen(true);

		if (state == true)
		{
			if (count >= 60)
			{
				for (int i = 0; i < 4; i++)
				{
					int new_x = generate_nbr(0, SCREEN_WEIGHT);
					int new_y = generate_nbr(0, SCREEN_HEIGHT);
					t_vect tmp = t_vect(new_x, new_y);
					delta[i] = (tmp - coord[i]) / 60;
				}
				t_color tmp_color = t_color(generate_nbr(0, 255), generate_nbr(0, 255), generate_nbr(0, 255));
				delta_color = t_color((tmp_color.r - color.r) / 60.0, (tmp_color.g - color.g) / 60.0, (tmp_color.b - color.b) / 60.0);
				count = 0;
			}
			else
			{
				for (int i = 0; i < 4; i++)
				{
					coord[i] = coord[i] + delta[i];
				}
				color.r = color.r + delta_color.r;
				color.g = color.g + delta_color.g;
				color.b = color.b + delta_color.b;
				count++;
			}
		}

		if (SDL_PollEvent(&event) == 1)
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
				play = false;
			else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
				gui.click(&event);
		}
	}
	return (0);
}

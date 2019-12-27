#include "jgl.h"

vector<TTF_Font *>font;

size_t tmp_index = 0;
vector <vector <vector <vector <c_image *> > > > char_list;
SDL_Color color_tab[NB_COLOR] = {
	{39, 39, 39, 255},
	{240, 240, 240, 255},
	{135, 206, 250, 255},
	{30, 144, 255, 255},
	{0, 0, 139, 255},
	{221, 110, 110, 255},
	{165, 89, 89, 255},
	{110, 70, 70, 255},
	{170, 220, 115, 255},
	{89, 165, 89, 255},
	{30, 100, 60, 255},
	{127, 255, 212, 255},
	{64, 224, 208, 255},
	{0, 139, 139, 255},
	{175, 175, 175, 255},
	{86, 86, 86, 255},
	{56, 56, 56, 255},
	{255, 195, 0, 255},
	{255, 165, 0, 255},
	{255, 130, 0, 255},
	{255, 250, 205, 255},
	{255, 228, 181, 255},
	{255, 255, 0, 255},
	{186, 85, 211, 255},
	{138, 43, 226, 255},
	{130, 0, 130, 255}
};

SDL_Color			get_color(int i)
{
	if (i < 0 || i >= NB_COLOR)
		return (color_tab[0]);
	return (color_tab[i]);
}

TTF_Font *get_font(int size)
{
	if (size < 2)
		error_exit(1, "Can't load a font of size < 2");

	if (font.size() <= size)
		font.resize(size + 2);

	if (font[size] == nullptr)
	{
		font[size] = TTF_OpenFont(FONT_PATH, size);
		if (font[size] == nullptr)
			error_exit(1, "Can't load a font");
	}

	return (font[size]);
}

c_image				*get_char(char c, int size, text_color color, text_style type)
{
	if (size <= 0)
		return (nullptr);

	if (char_list.size() <= (size_t)size)
		char_list.resize((size_t)size + 2);
	if (char_list[size].size() <= (size_t)type)
		char_list[size].resize((size_t)type + 2);
	if (char_list[size][(size_t)type].size() <= (size_t)color)
		char_list[size][(size_t)type].resize((size_t)color + 2);
	if (char_list[size][(size_t)type][(size_t)color].size() <= (size_t)c)
		char_list[size][(size_t)type][(size_t)color].resize(c + 2);
	if (char_list[size][(size_t)type][(size_t)color][c] == nullptr)
	{
		SDL_Texture* old_target = SDL_GetRenderTarget(g_application->renderer());
	    SDL_SetRenderTarget(g_application->renderer(), NULL);

		TTF_Font *tmp = get_font((size_t)size);
		//
		TTF_SetFontStyle(tmp, (size_t)type);
		//
		char text[2];
		text[0] = c;
		text[1] = '\0';

		SDL_Surface *surface = TTF_RenderText_Blended(tmp, text, get_color((size_t)color));
		if (surface != nullptr)
			char_list[size][(size_t)type][(size_t)color][c] = new c_image(surface);
		else
			error_exit(1, "Error while creating the char " + string (1, c));

		TTF_SetFontStyle(tmp, static_cast<int>(text_style::normal));
	    SDL_SetRenderTarget(g_application->renderer(), old_target);
	}
	return (char_list[size][(size_t)type][(size_t)color][c]);
}

int				draw_text(string text, Vector2 coord, int size, text_color color, text_style type, c_viewport *viewport)
{
	c_image			*image;
	size_t			i = 0;
	Vector2			rel_coord;
	int				delta = 0;

	if (viewport == nullptr)
		viewport = g_application->central_widget()->viewport();

	if (size <= 2)
		return 0;

	while (i < text.length())
	{
		rel_coord = Vector2(coord.x + delta, coord.y);
		image = get_char(text[i], size, color, type);
		image->draw(rel_coord, image->size(), viewport);
		delta += image->size().x;

		i++;
	}
	return (delta);
}

int				max_char_in_box(int space, int size)
{
	int nb_char = 0;
	c_image			*image;
	int delta = 0;

	image = get_char('M', size);
	while (delta < space)
	{
		delta += image->size().x;
		nb_char++;
	}

	return (nb_char);
}

int				calc_text_len(string text, int size)
{
	c_image			*image;
	size_t			i = 0;
	int				delta = 0;

	while (i < text.length())
	{
		image = get_char(text[i], size);
		delta += image->size().x;

		i++;
	}
	return (delta);
}

int				draw_centred_text(string text, Vector2 coord, int size, text_color color, text_style type, c_viewport *viewport)
{
	if (viewport == nullptr)
		viewport = g_application->central_widget()->viewport();

	if (size <= 2)
		return 0;

	int x = calc_text_len(text, size);
	int y = get_char('M', size, color, type)->size().y;

	return (draw_text(text, Vector2(coord.x - x / 2, coord.y - y / 2), size, color, type, viewport));
}

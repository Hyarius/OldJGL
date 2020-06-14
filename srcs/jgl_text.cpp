#include "jgl.h"

jgl::String font_path = "";

std::vector<TTF_Font *> font;
std::vector<TTF_Font *> font_outline;

size_t tmp_index = 0;
std::vector <std::vector <std::vector <std::vector <std::map <size_t, jgl::Image *> > > > > char_list;

int text_compared_value[] = {
	0x80,
	0xE0,
	0xF0,
	0xF8
};

int text_result_value[] = {
	0,
	0xC0,
	0xE0,
	0xF0
};

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

namespace jgl
{
	void Application::set_font_path(jgl::String p_font_path)
	{
		font_path = p_font_path;
		font.clear();
		tmp_index = 0;
		for (size_t i = 0; i < char_list.size(); i++)
			for (size_t j = 0; j < char_list[i].size(); j++)
				for (size_t k = 0; k < char_list[i][j].size(); k++)
					char_list[i][j][k].clear();
	}

	SDL_Color			get_color(int i)
	{
		if (i < 0 || i >= NB_COLOR)
			return (color_tab[0]);
		return (color_tab[i]);
	}

	TTF_Font* get_font(size_t size)
	{
		if (size < 2)
			error_exit(1, "Can't load a font of size < 2");
		if (font_path == "")
			error_exit(1, "Can't load a font : no font file given");

		if (font.size() <= size)
			font.resize(size + 2);

		if (font[size] == nullptr)
		{
			font[size] = TTF_OpenFont(font_path.std().c_str(), static_cast<int>(size));
			if (font[size] == nullptr)
				error_exit(1, "Can't load a font");
		}

		return (font[size]);
	}

	TTF_Font* get_font_outline(size_t size)
	{
		if (size < 2)
			error_exit(1, "Can't load a font of size < 2");
		if (font_path == "")
			error_exit(1, "Can't load a font : no font file given");

		if (font_outline.size() <= size + 2)
			font_outline.resize(size + 2);

		if (font_outline[size] == nullptr)
		{
			font_outline[size] = TTF_OpenFont(font_path.std().c_str(), static_cast<int>(size));
			if (font_outline[size] == nullptr)
				error_exit(1, "Can't load a font");
		}

		return (font_outline[size]);
	}

	Image* get_string_image(jgl::String str, size_t size, size_t outline, text_color color, text_style style)
	{
		const char* text;

		TTF_Font* tmp = get_font(static_cast<size_t>(size));
		TTF_SetFontStyle(tmp, static_cast<int>(style));

		std::string tmp_str = str.std();
		text = tmp_str.c_str();

		SDL_Surface* surface = TTF_RenderUTF8_Blended(tmp, text, get_color(static_cast<size_t>(color)));

		if (outline > 0)
		{
			TTF_Font* tmp_outline = get_font_outline(static_cast<size_t>(size));
			TTF_SetFontStyle(tmp_outline, static_cast<int>(style));
			TTF_SetFontOutline(tmp_outline, outline);

			SDL_Surface* outline_surface = TTF_RenderUTF8_Blended(tmp_outline, text, get_color(static_cast<size_t>(text_color::black)));
			if (outline_surface == nullptr)
				error_exit(1, "Error while creating the outline for char ");
			SDL_Rect rect = { static_cast<int>(outline), static_cast<int>(outline), surface->w, surface->h };

			SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
			SDL_BlitSurface(surface, NULL, outline_surface, &rect);
			SDL_FreeSurface(surface);

			surface = outline_surface;

			TTF_SetFontStyle(tmp_outline, static_cast<int>(text_style::normal));
		}

		TTF_SetFontStyle(tmp, static_cast<int>(text_style::normal));

		if (surface == nullptr)
		{
			error_exit(1, "Can't create a text with the string : " + str);
			return (nullptr);
		}
		return (new Image(surface));
	}

	Image* get_char(Glyph c, size_t size, size_t outline, text_color color, text_style style)
	{
		const char *text;

		if (size <= 0 || c == '\0')
			return (nullptr);

		if (char_list.size() <= static_cast<size_t>(size))
			char_list.resize(static_cast<size_t>(size) + 2);
		if (char_list[size].size() <= static_cast<size_t>(style))
			char_list[size].resize(static_cast<size_t>(style) + 2);
		if (char_list[size][static_cast<size_t>(style)].size() <= static_cast<size_t>(color))
			char_list[size][static_cast<size_t>(style)].resize(static_cast<size_t>(color) + 2);
		if (char_list[size][static_cast<size_t>(style)][static_cast<size_t>(color)].size() <= outline)
			char_list[size][static_cast<size_t>(style)][static_cast<size_t>(color)].resize(outline + 1);
		if (char_list[size][static_cast<size_t>(style)][static_cast<size_t>(color)][outline].count(c.value()) == 0)
		{
			TTF_Font* tmp = get_font(static_cast<size_t>(size));
			//
			TTF_SetFontStyle(tmp, static_cast<int>(style));
			//
			text = c.content();

			SDL_Surface* surface = TTF_RenderUTF8_Blended(tmp, text, get_color(static_cast<size_t>(color)));
			if (outline > 0)
			{
				TTF_Font* tmp_outline = get_font_outline(static_cast<size_t>(size));
				TTF_SetFontStyle(tmp_outline, static_cast<int>(style));
				TTF_SetFontOutline(tmp_outline, outline);

				SDL_Surface* outline_surface = TTF_RenderUTF8_Blended(tmp_outline, text, get_color(static_cast<size_t>(text_color::black)));
				if (outline_surface == nullptr)
					error_exit(1, "Error while creating the outline for char ");
				SDL_Rect rect = { static_cast<int>(outline), static_cast<int>(outline), surface->w, surface->h };

				SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
				SDL_BlitSurface(surface, NULL, outline_surface, &rect);
				SDL_FreeSurface(surface);

				surface = outline_surface;

				TTF_SetFontStyle(tmp_outline, static_cast<int>(text_style::normal));
			}

			if (surface != nullptr)
				char_list[size][static_cast<size_t>(style)][static_cast<size_t>(color)][outline][c.value()] = new Image(surface);
			else
				error_exit(1, "Error while creating the char");

			TTF_SetFontStyle(tmp, static_cast<int>(text_style::normal));
		}
		return (char_list[size][static_cast<size_t>(style)][static_cast<size_t>(color)][outline][c.value()]);
	}

	int create_char_unicode(char* result, const char* base, size_t index)
	{
		unsigned char to_parse = base[index];
		int limit = 0;

		if ((to_parse & 0x80) == 0) //1 char len
		{
			limit = 1;
		}
		else if ((to_parse & 0xE0) == 0xC0) //2 chars len
		{
			limit = 2;
		}
		else if ((to_parse & 0xF0) == 0xE0) //3 chars len
		{
			limit = 3;
		}
		else if ((to_parse & 0xF8) == 0xF0) //4 chars len
		{
			limit = 4;
		}
		else // error
		{
			return (-1);
		}

		if (result == nullptr)
			return (limit);

		for (int j = 0; j < limit; j++)
			result[j] = base[index + j];
		result[limit] = 0;
		return (limit);
	}

	int				draw_text(jgl::String text, Vector2 coord, size_t size, size_t outline, text_color color, text_style style, Viewport* viewport)
	{
		Image* image;
		size_t			i = 0;
		Vector2			rel_coord;
		int				delta = 0;

		if (viewport == nullptr)
			viewport = g_application->central_widget()->viewport();

		if (size <= 2)
			return 0;

		while (i < text.size())
		{
			rel_coord = Vector2(coord.x + delta, coord.y);

			if (text[i] != '\0')
			{
				image = get_char(text[i], size, outline, color, style);

				image->draw(rel_coord, image->size(), 1.0f, viewport);
				delta += static_cast<int>(image->size().x);
			}
			i++;
		}
		return (delta);
	}

	int				max_char_in_box(int space, size_t size)
	{
		int nb_char = 0;
		Image* image;
		int delta = 0;

		image = get_char('M', size);
		while (delta < space)
		{
			delta += static_cast<int>(image->size().x);
			nb_char++;
		}

		return (nb_char);
	}

	int				calc_text_len(jgl::String text, size_t size)
	{
		Image* image;
		size_t			i = 0;
		int				delta = 0;

		while (i < text.size())
		{
			if (text[i] != '\0')
			{
				image = get_char(text[i], size);

				delta += static_cast<int>(image->size().x);
			}
			i++;
		}
		return (delta);
	}

	int				draw_centred_text(jgl::String text, Vector2 coord, size_t size, size_t outline, text_color color, text_style style, Viewport* viewport)
	{
		if (viewport == nullptr)
			viewport = g_application->central_widget()->viewport();

		if (size <= 2)
			return 0;

		int x = calc_text_len(text, size);
		int y = static_cast<int>(get_char('M', size, 0, color, style)->size().y);

		return (draw_text(text, Vector2(coord.x - x / 2, coord.y - y / 2), size, outline, color, style, viewport));
	}
}
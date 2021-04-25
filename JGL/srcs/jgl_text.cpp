#include "jgl.h"

std::vector<TTF_Font *> font;
std::vector<TTF_Font *> font_outline;

jgl::String g_font_path;

uint32_t tmp_index = 0;
std::vector<jgl::Image*> char_direct_list;
std::vector <std::vector <std::vector <std::vector <std::map <uint32_t, jgl::Image *> > > > > char_list;

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
	void set_font_path(const jgl::String p_font_path)
	{
		g_font_path = p_font_path.copy();
		font.clear();
		tmp_index = 0;
		for (uint32_t i = 0; i < char_list.size(); i++)
			for (uint32_t j = 0; j < char_list[i].size(); j++)
				for (uint32_t k = 0; k < char_list[i][j].size(); k++)
					char_list[i][j][k].clear();
	}

	SDL_Color			get_color(const int i)
	{
		if (i < 0 || i >= NB_COLOR)
			return (color_tab[0]);
		return (color_tab[i]);
	}

	TTF_Font* get_font(const uint32_t size)
	{
		if (size < 2)
			error_exit(1, "Can't load a font of size < 2");
		if (g_application == nullptr || g_font_path == "")
			error_exit(1, "Can't load a font : no font file given");

		if (font.size() <= size)
			font.resize(size + 2);

		if (font[size] == nullptr)
		{
			font[size] = TTF_OpenFont(g_font_path.std().c_str(), static_cast<int>(size));
			if (font[size] == nullptr)
				error_exit(1, "Can't load a font");
		}
		return (font[size]);
	}

	TTF_Font* get_font_outline(const uint32_t size)
	{
		g_application->take_context_control();
		if (size < 2)
			error_exit(1, "Can't load a font of size < 2");
		if (g_application == nullptr || g_font_path == "")
			error_exit(1, "Can't load a font : no font file given");

		if (font_outline.size() <= size + 2)
			font_outline.resize(size + 2);

		if (font_outline[size] == nullptr)
		{
			font_outline[size] = TTF_OpenFont(g_font_path.std().c_str(), static_cast<int>(size));
			if (font_outline[size] == nullptr)
				error_exit(1, "Can't load a font");
		}
		g_application->release_context_control();
		return (font_outline[size]);
	}

	Image* get_string_image(const jgl::String str, const uint32_t size, const uint32_t outline, const text_color color, const text_style style)
	{
		const char* text;

		TTF_Font* tmp = get_font(static_cast<uint32_t>(size));
		g_application->take_context_control();
		TTF_SetFontStyle(tmp, static_cast<int>(style));

		std::string tmp_str = str.std();
		text = tmp_str.c_str();

		SDL_Surface* surface = TTF_RenderUTF8_Blended(tmp, text, get_color(static_cast<uint32_t>(color)));

		if (outline > 0)
		{
			TTF_Font* tmp_outline = get_font_outline(static_cast<uint32_t>(size));
			TTF_SetFontStyle(tmp_outline, static_cast<int>(style));
			TTF_SetFontOutline(tmp_outline, outline);

			SDL_Surface* outline_surface = TTF_RenderUTF8_Blended(tmp_outline, text, get_color(static_cast<uint32_t>(text_color::black)));
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

		g_application->release_context_control();

		if (surface == nullptr)
		{
			error_exit(1, "Can't create a text with the string : " + str);
		}
		Image* result = new Image(surface);
		return (result);
	}

	Uint32 getpixel(SDL_Surface* surface, int x, int y)
	{
		int bpp = surface->format->BytesPerPixel;
		/* Here p is the address to the pixel we want to retrieve */
		Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;

		switch (bpp)
		{
		case 1:
			return *p;
			break;

		case 2:
			return *(Uint16*)p;
			break;

		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] << 16;
			break;

		case 4:
			return *(Uint32*)p;
			break;

		default:
			return 0;       /* shouldn't happen, but avoids warnings */
		}
	}

	Image* get_char(const Glyph c, const uint32_t size, const uint32_t outline, const text_color color, const text_style style)
	{
		static std::mutex global_mutex;
		const char *text;


		if (size <= 0 || c == '\0')
		{
			return (nullptr);
		}

		global_mutex.lock();

		if (char_list.size() <= size)
		{
			char_list.resize(size + 2);
		}
		if (char_list[size].size() <= static_cast<uint32_t>(style))
		{
			char_list[size].resize(static_cast<uint32_t>(style) + 2);
		}
		if (char_list[size][static_cast<uint32_t>(style)].size() <= static_cast<uint32_t>(color))
		{
			char_list[size][static_cast<uint32_t>(style)].resize(static_cast<uint32_t>(color) + 2);
		}
		if (char_list[size][static_cast<uint32_t>(style)][static_cast<uint32_t>(color)].size() <= outline)
		{
			char_list[size][static_cast<uint32_t>(style)][static_cast<uint32_t>(color)].resize(outline + 1);
		}
		global_mutex.unlock();

		if (char_list[size][static_cast<uint32_t>(style)][static_cast<uint32_t>(color)][outline].count(c.value()) == 0)
		{
			g_application->take_context_control();
			TTF_Font* tmp = get_font(static_cast<uint32_t>(size));
			//
			TTF_SetFontStyle(tmp, static_cast<int>(style));
			//
			text = c.content();

			SDL_Surface* surface = TTF_RenderUTF8_Blended(tmp, text, get_color(static_cast<uint32_t>(color)));
			if (outline > 0)
			{

				TTF_Font* tmp_outline = get_font_outline(static_cast<uint32_t>(size));
				TTF_SetFontStyle(tmp_outline, static_cast<int>(style));
				TTF_SetFontOutline(tmp_outline, outline);


				SDL_Surface* outline_surface = TTF_RenderUTF8_Blended(tmp_outline, text, get_color(static_cast<uint32_t>(text_color::black)));
				if (outline_surface == nullptr)
					error_exit(1, "Error while creating the outline for char ");
				SDL_Rect rect = { static_cast<int>(outline), static_cast<int>(outline), surface->w, surface->h };


				SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
				SDL_BlitSurface(surface, NULL, outline_surface, &rect);
				SDL_FreeSurface(surface);

				surface = outline_surface;


				TTF_SetFontStyle(tmp_outline, static_cast<int>(text_style::normal));

			}

			/*for (size_t j = 0; j < surface->h; j++)
			{
				for (size_t i = 0; i < surface->w; i++)
				{
					if ((getpixel(surface, i, j) & 2130706432) != 0)
						std::cout << ".";
					else
						std::cout << " ";
				}
				std::cout << std::endl;
			}*/

			g_application->release_context_control();
			if (surface != nullptr)
			{

				Image* tmp_image = new Image(surface);

				char_direct_list.push_back(tmp_image);

				global_mutex.lock();

				char_list[size][static_cast<uint32_t>(style)][static_cast<uint32_t>(color)][outline][c.value()] = tmp_image;

				global_mutex.unlock();

			}
			else
				error_exit(1, "Error while creating the char");


			TTF_SetFontStyle(tmp, static_cast<int>(text_style::normal));
		}
		return (char_list[size][static_cast<uint32_t>(style)][static_cast<uint32_t>(color)][outline][c.value()]);
	}

	int count_char_len(const char to_parse)
	{
		int limit = 0;

		if ((to_parse & 0x80) == 0)
			return (1);
		else if ((to_parse & 0xE0) == 0xC0)
			return (2);
		else if ((to_parse & 0xF0) == 0xE0)
			return (3);
		else if ((to_parse & 0xF8) == 0xF0)
			return (4);
		else
			return (-1);
	}

	int create_char_unicode(char* result, const char* base, const uint32_t index)
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

	int				draw_text(const jgl::String text, const Vector2 coord, const uint32_t size, const uint32_t outline, const float alpha, const text_color color, const text_style style, const float layer, const Viewport* viewport)
	{
		Image* image;
		uint32_t			i = 0;
		Vector2			rel_coord;
		int				delta = 0;

		if (size <= 2)
			return 0;

		while (i < text.size())
		{
			rel_coord = Vector2(coord.x + delta, coord.y);

			if (text[i] != '\0')
			{
				image = get_char(text[i], size, outline, color, style);

				image->draw(rel_coord, image->size(), alpha, layer, viewport);
				delta += static_cast<int>(image->size().x);
			}
			i++;
		}
		return (delta);
	}

	int				max_char_in_box(const int space, const uint32_t size)
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

	int				calc_text_len(const jgl::String text, const uint32_t size)
	{
		Image* image;
		uint32_t			i = 0;
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

	int				draw_centred_text(const jgl::String text, const Vector2 coord, const uint32_t size, const uint32_t outline, const float alpha, const text_color color, const text_style style, const float layer, const Viewport* viewport)
	{
		if (size <= 2)
			return 0;
		int x = calc_text_len(text, size);
		int y = static_cast<int>(get_char('M', size, 0, color, style)->size().y);

		int result = draw_text(text, Vector2(coord.x - x / 2, coord.y - y / 2), size, outline, alpha, color, style, layer, viewport);
		return (result);
	}

	void delete_loaded_char()
	{
		for (uint32_t i = 0; i < char_direct_list.size(); i++)
			delete char_direct_list[i];
	}
}
#ifndef JGL_TEXT_DEFINE_H
#define JGL_TEXT_DEFINE_H

#include "jgl_includes.h"
#include "jgl_image.h"

#define NB_SIZE			150
#define NB_COLOR		26

namespace jgl
{
	void clear_font_path();
	SDL_Color get_color(int i);
	TTF_Font* get_font(size_t size);
	TTF_Font* get_font_outline(size_t size);
	Image* get_string_image(jgl::String str, size_t size = 16, size_t outline = 0, text_color color = text_color::black, text_style style = text_style::normal);
	Image* get_char(Glyph c, size_t size = 16, size_t outline = 0, text_color color = text_color::black, text_style style = text_style::normal);
	int create_char_unicode(char* result, const char* base, size_t index);
	int draw_text(jgl::String text, Vector2 coord, size_t size = 16, size_t outline = 0, text_color color = text_color::black, text_style style = text_style::normal, Viewport* viewport = nullptr);
	int draw_centred_text(jgl::String text, Vector2 coord, size_t size = 16, size_t outline = 0, text_color color = text_color::black, text_style style = text_style::normal, Viewport* viewport = nullptr);
	int calc_text_len(jgl::String text, size_t size = 16);
	int	max_char_in_box(int space, size_t size = 16);
}
#endif

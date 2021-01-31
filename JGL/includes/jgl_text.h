#ifndef JGL_TEXT_DEFINE_H
#define JGL_TEXT_DEFINE_H

#include "jgl_includes.h"
#include "jgl_image.h"

extern jgl::String g_font_path;

#define NB_SIZE			150
#define NB_COLOR		26

namespace jgl
{
	void set_font_path(const jgl::String p_font_path);
	SDL_Color get_color(const int i);
	TTF_Font* get_font(const size_t size);
	TTF_Font* get_font_outline(const size_t size);
	Image* get_string_image(const jgl::String str, const size_t size = 16, const size_t outline = 0, const text_color color = text_color::black, const text_style style = text_style::normal);
	Image* get_char(const Glyph c, const size_t size = 16, const size_t outline = 0, const text_color color = text_color::black, const text_style style = text_style::normal);
	int count_char_len(const char to_parse);
	int create_char_unicode(char* result, const char* base, const size_t index);
	int draw_text(const jgl::String text, const Vector2 coord, const size_t size = 16, const size_t outline = 0, const float alpha = 1.0f, const text_color color = text_color::black, const text_style style = text_style::normal, const Viewport* viewport = nullptr);
	int draw_centred_text(const jgl::String text, const Vector2 coord, const size_t size = 16, const size_t outline = 0, const float alpha = 1.0f, const text_color color = text_color::black, const text_style style = text_style::normal, const Viewport* viewport = nullptr);
	int calc_text_len(const jgl::String text, const size_t size = 16);
	int	max_char_in_box(const int space, const size_t size = 16);
	void delete_loaded_char();
}
#endif

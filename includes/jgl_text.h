#ifndef JGL_TEXT_DEFINE_H
#define JGL_TEXT_DEFINE_H

#include "jgl_includes.h"
#include "jgl_image.h"

#define NB_SIZE			150
#define NB_COLOR		26

SDL_Color get_color(int i);
TTF_Font *get_font(size_t size);
c_image	*get_char(char c, size_t size = 16, int outline = 0, text_color color = text_color::black, text_style style = text_style::normal);
int draw_text(string text, Vector2 coord, size_t size = 16, int outline = 0, text_color color = text_color::black, text_style style = text_style::normal, c_viewport *viewport = nullptr);
int draw_centred_text(string text, Vector2 coord, size_t size = 16, int outline = 0, text_color color = text_color::black, text_style style = text_style::normal, c_viewport *viewport = nullptr);
int calc_text_len(string text, size_t size = 16);
int	max_char_in_box(int space, size_t size = 16);

#endif

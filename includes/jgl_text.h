#ifndef JGL_TEXT_DEFINE_H
#define JGL_TEXT_DEFINE_H

#include "jgl_includes.h"
#include "jgl_image.h"

#define NB_SIZE			150
#define NB_COLOR		26

SDL_Color get_color(int i);
TTF_Font *get_font(int size);
c_image	*get_char(char c, int size = 16, int outline = 0, text_color color = text_color::black, text_style type = text_style::normal);
int draw_text(string text, Vector2 coord, int size = 16, int outline = 0, text_color color = text_color::black, text_style type = text_style::normal, c_viewport *viewport = nullptr);
int draw_centred_text(string text, Vector2 coord, int size = 16, int outline = 0, text_color color = text_color::black, text_style type = text_style::normal, c_viewport *viewport = nullptr);
int calc_text_len(string text, int size = 16);
int	max_char_in_box(int space, int size = 16);

#endif

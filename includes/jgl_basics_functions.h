#ifndef JGL_BASICS_FUNCTIONS_H
#define JGL_BASICS_FUNCTIONS_H

#include "jgl_includes.h"

#include "jgl_vector.h"

namespace jgl
{
	void check_sdl_error(const jgl::String file, const int line);
	bool string_is_numeric(const jgl::String text);
	size_t count_word(const jgl::String& input, const jgl::String& delim);
	size_t count_word(const jgl::String& input, const jgl::Glyph& delim);
	size_t unique_count_word(const jgl::Unique_string& input, const jgl::Unique_string& delim);
	size_t count_word_len(const jgl::String& input, const jgl::String& delim, const size_t start);
	size_t count_word_len(const jgl::String& input, const jgl::Glyph& delim, const size_t start);
	size_t unique_count_word_len(const jgl::Unique_string& input, const jgl::Unique_string& delim, const size_t start);
	jgl::Array<jgl::String> strsplit(const jgl::String input, const jgl::String delim, const bool regroup = true);
	void strsplit(jgl::Array<jgl::String>& tab, const jgl::String input, const jgl::String delim, const bool regroup = true);
	jgl::Array<jgl::Unique_string> unique_strsplit(const jgl::Unique_string input, const jgl::Unique_string delim, const bool regroup);
	void unique_strsplit(jgl::Array<jgl::Unique_string>& tab, const jgl::Unique_string input, const jgl::Unique_string delim, const bool regroup);
	void error_exit(const int num, const jgl::String error);
	void error_exit(const int num, const char* str);
	void reverse(jgl::String& base);
	jgl::String itoa(const int x, const int d = -1);
	jgl::String ftoa(const float n, const int afterpoint = -1, const int lenght = -1);
	jgl::String ftoa(const double n, const int afterpoint = -1, const int lenght = -1);
	float stof(const jgl::String text);
	int stoi(const jgl::String text);
	jgl::String normalize_string(const jgl::String str, const jgl::Glyph c, const size_t size);
	jgl::String normalize_float(const float num, const int after_point, const jgl::Glyph c, const size_t size);
	bool is_middle(const float min, const float value, const float max);
	jgl::Array<jgl::Vector2> calc_line_2d(const float x1, const float y1, const float x2, const float y2);
	int generate_nbr(const int min, const int max);

	void remove_char(jgl::String& src, const jgl::String to_remove);

	template<typename K, typename V>
	K find_key(const std::map<K, V>& src_map, const V& value)
	{
		auto it = src_map.begin();

		while (it != src_map.end())
		{
			if (it->second == value)
			{
				break;
			}
			it++;
		}
		return (it->first);
	}

	template<typename K, typename V>
	bool map_contain(const std::map<K, V>& src_map, const K value)
	{
		return (src_map.count(value));
	}

	Pixel convert_screen_to_opengl(const Pixel source);
	SDL_Surface* create_surface_color(const Color p_color);
	float degree_to_radian(const float angle);
	float radian_to_degree(const float radian);
	float clamp_float(const float min, const float value, const float max);
	int clamp_int(const int min, const int value, const int max);
	bool point_in_rectangle(const jgl::Vector2 target, const jgl::Vector2 pos, const jgl::Vector2 size);
	jgl::Vector3 rotate_point(const jgl::Vector3 pos, const jgl::Vector3 center, const jgl::Vector3 axis, const float angle);
}
#endif

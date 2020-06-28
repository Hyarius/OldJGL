#ifndef JGL_BASICS_FUNCTIONS_H
#define JGL_BASICS_FUNCTIONS_H

#include "jgl_includes.h"

#include "jgl_vector.h"

namespace jgl
{
	void check_sdl_error(jgl::String file, int line);
	bool string_is_numeric(jgl::String text);
	jgl::Array<jgl::String> strsplit(jgl::String input, jgl::String delim, bool regroup = true);
	void strsplit(jgl::Array<jgl::String>& tab, jgl::String input, jgl::String delim, bool regroup = true);
	jgl::Array<jgl::Unique_string> unique_strsplit(jgl::Unique_string input, jgl::Unique_string delim, bool regroup);
	void unique_strsplit(jgl::Array<jgl::Unique_string>& tab, jgl::Unique_string input, jgl::Unique_string delim, bool regroup);
	void error_exit(int num, jgl::String error);
	void error_exit(int num, const char* str);
	void reverse(jgl::String& base);
	jgl::String itoa(int x, int d = -1);
	jgl::String ftoa(float n, int afterpoint = -1, int lenght = -1);
	jgl::String ftoa(double n, int afterpoint = -1, int lenght = -1);
	float stof(jgl::String text);
	int stoi(jgl::String text);
	jgl::String normalize_string(jgl::String str, jgl::Glyph c, size_t size);
	jgl::String normalize_float(float num, int after_point, jgl::Glyph c, size_t size);
	bool is_middle(float min, float value, float max);
	jgl::Array<jgl::Vector2> calc_line_2d(float x1, float y1, float x2, float y2);
	int generate_nbr(int min, int max);

	void remove_char(jgl::String& src, jgl::String to_remove);

	template<typename K, typename V>
	K find_key(std::map<K, V>& src_map, V& value)
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
	bool map_contain(std::map<K, V>& src_map, K value)
	{
		return (src_map.count(value));
	}

	Pixel convert_screen_to_opengl(Pixel source);
	SDL_Surface* create_surface_color(Color p_color);
	float degree_to_radian(float angle);
	float radian_to_degree(float radian);
	float clamp_float(float min, float value, float max);
	int clamp_int(int min, int value, int max);
	bool point_in_rectangle(jgl::Vector2 target, jgl::Vector2 pos, jgl::Vector2 size);
}
#endif

#ifndef JGL_BASICS_FUNCTIONS_H
#define JGL_BASICS_FUNCTIONS_H

#include "jgl_includes.h"

#include "jgl_vector.h"

using namespace std;

void check_sdl_error(const char *file, int line);
bool string_is_numeric(string text);
vector<string> strsplit(string input, string c);
void error_exit(int num, string error);
string ftoa(float n, int afterpoint = -1);
string ftoa(double n, int afterpoint = -1);
string normalize_string(string str, char c, size_t size);
string normalize_float(float num, size_t after_point, char c, size_t size);
bool is_middle(float a, float b, float c);
vector<Vector2> calc_line_2d(float x1, float y1, float x2, float y2);
int generate_nbr(int min, int max);

void remove_char(string &src, string to_remove);

template<typename K, typename V>
K find_key(map<K, V> &src_map, V &value)
{
	auto it = src_map.begin();

	while (it != src_map.end())
	{
		if(it->second == value)
		{
			break;
		}
		it++;
	}
	return (it->first);
}

template<typename K, typename V>
bool map_contain(map<K, V> &src_map, K value)
{
	for (auto it = src_map.begin(); it != src_map.end(); it++)
		if (it->first == value)
			return (true);
	return (false);
}

Pixel convert_screen_to_opengl(Vector2 source);
Pixel convert_screen_to_opengl(Pixel source);
SDL_Surface *create_surface_color(Color p_color);
float degree_to_radius(float angle);
float radius_to_degree(float radian);
float clamp_float(float min, float value, float max);
int clamp_int(int min, int value, int max);
#endif

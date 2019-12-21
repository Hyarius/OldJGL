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
string normalize_string(string str, char c, size_t size);
string normalize_float(float num, size_t after_point, char c, size_t size);
bool is_middle(float a, float b, float c);
string convert_hour_to_string(int hour, int minute);
string convert_hour_to_string(int minute);
string convert_time_to_string(float time);
string convert_hour_to_string(float time);
string convert_time_to_string_round(float time);
float convert_km_to_m(float base_dist);
float convert_m_to_km(float base_dist);
float convert_second_to_minute(float time);
float convert_minute_to_hour(float time);
float convert_second_to_hour(float time);
float convert_minute_to_second(float time);
float convert_hour_to_minute(float time);
float convert_hour_to_second(float time);
float convert_km_per_h_to_m_per_s(float base_speed);
float convert_km_per_h_to_m_per_s(float base_speed);
float convert_km_per_h_to_m_per_s(float base_speed);
float convert_m_per_s_to_km_per_h(float base_speed);
float convert_m_per_s2_to_km_per_h2(float base_acceleration);
float convert_km_per_h2_to_m_per_s2(float base_acceleration);
int convert_string_to_hour(string text);
int convert_int_to_hour(int hour, int minute);
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

#endif

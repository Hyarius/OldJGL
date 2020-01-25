#include "jgl.h"

using namespace std;

vector<string>		strsplit(string input, string delim)
{
	vector<string>	tab;
	string			word;
	int 			start = 0;
	int 			end = 0;

	tab = vector<string>();
	while (end != -1)
	{
		end = input.find(delim, start);
		word = input.substr(start, end - start);
		if (word.size() > 0)
			tab.insert(tab.end(), word);
		start = end + delim.size();
	}
	return (tab);
}

void check_sdl_error(const char *file, int line)
{
	vector<string>tab = strsplit(file, "\\");
	if (tab.size() == 1)
		vector<string>tab = strsplit(file, "/");
	string file_name = tab[tab.size() - 1];
	string text = SDL_GetError();
	if (text.size() != 0)
	{
		string error = file_name + " - line [" + to_string(line) + "] : " + text;
		error_exit(1, error);
	}
}

void				error_exit(int num, string error)
{
	cout << error << endl;
	exit(num);
}

string normalize_string(string str, char c, size_t size)
{
	string result;

	result = str;

	while (result.size() < size)
		result.insert(result.begin(), c);

	return (result);
}

string normalize_float(float num, size_t after_point, char c, size_t size)
{
	string result;

	result = ftoa(num, after_point);
	while (result.size() < size)
		result.insert(result.begin(), c);

	return (result);
}

void reverse(string &base)
{
    int i = 0, j = base.length() - 1, temp;
    while (i<j)
    {
        temp = base[i];
        base[i] = base[j];
        base[j] = temp;
        i++; j--;
    }
}

string intToStr(int x, int d)
{
	char c;
	string result;

    int i = 0;
    while (x)
    {
		c = (x % 10) + '0';
        result.push_back(c);
        x = x/10;
		i++;
    }

    while (i < d)
	{
		result.append("0");
		i++;
	}

	if (result.size() == 0)
		return ("0");

    reverse(result);

    return (result);
}

// Converts a floating point number to string.
string ftoa(float n, int afterpoint)
{
	ostringstream out;

	if (n > 0 || n < -1)
		afterpoint += 2;
    out << setprecision(afterpoint) << n;
    return out.str();
}
// Converts a floating point number to string.
string ftoa(double n, int afterpoint)
{
	ostringstream out;

	if (n > 0 || n < -1)
		afterpoint += 2;
    out << setprecision(afterpoint) << n;
    return out.str();
}

bool string_is_numeric(string text)
{
	return (text.find_first_not_of( "0123456789." ) == string::npos);
}

bool is_middle(float a, float b, float c)
{
	if (a > b)
		return (false);
	if (b > c)
		return (false);
	return (true);
}

void remove_char(string &src, string to_remove)
{
	string result;
	for (size_t i = 0; i < src.size(); i++)
	{
		char target = '\0';
		for (size_t j = 0; j < to_remove.size(); j++)
			if (to_remove[j] == src[i])
				target = to_remove[j];

		if (target == '\0')
			result.push_back(src[i]);
	}
	src = result;
}

vector<Vector2> 		calc_line_2d(float x1, float y1, float x2, float y2)
{
	vector<Vector2> result;
	const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
	if(steep)
	{
		swap(x1, y1);
		swap(x2, y2);
	}
	if(x1 > x2)
	{
		swap(x1, x2);
		swap(y1, y2);
	}

	float dx = x2 - x1;
	float dy = fabs(y2 - y1);

	float error = dx / 2.0f;
	int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;

	int maxX = (int)x2;

	for(int x=(int)x1; x<maxX; x++)
	{
		if(steep)
			result.push_back(Vector2(y,x));
		else
			result.push_back(Vector2(x,y));

		error -= dy;
		if(error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
	return (result);
}

int generate_nbr(int min, int max)
{
	return((rand() % (max - min)) + min);
}

Pixel				convert_screen_to_opengl(Vector2 source)
{
	return (convert_screen_to_opengl(Pixel(source)));
}

Pixel				convert_screen_to_opengl(Pixel source)
{
	float x = (source.x) / (g_application->active_viewport()->area().x / 2.0f) - 1.0f;
	float y = -((source.y) / (g_application->active_viewport()->area().y / 2.0f) - 1.0f);
	return (Pixel(x, y, 0.0f));
}

SDL_Surface			*create_surface_color(Color p_color)
{
	SDL_Surface		*surface;
	Uint32			rmask, gmask, bmask, amask;

	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	    rmask = 0xff000000;
	    gmask = 0x00ff0000;
	    bmask = 0x0000ff00;
	    amask = 0x000000ff;
	#else
	    rmask = 0x000000ff;
	    gmask = 0x0000ff00;
	    bmask = 0x00ff0000;
	    amask = 0xff000000;
	#endif

    surface = SDL_CreateRGBSurface(0, 1, 1, 32, rmask, gmask, bmask, amask);
	SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format,
		(Uint8)(p_color.r * 255), (Uint8)(p_color.g * 255),
		(Uint8)(p_color.b * 255), (Uint8)(p_color.a * 255)));

	return (surface);
}

float				degree_to_radius(float angle)
{
	return ((angle * M_PI) / 180.0f);
}

float				radius_to_degree(float radian)
{
	return ((radian * 180.0f) / M_PI);
}

float clamp_float(float min, float value, float max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

int clamp_int(int min, int value, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

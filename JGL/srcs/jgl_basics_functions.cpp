#include "jgl.h"

namespace jgl
{
	void debug_line_imp(char* file, char* function, int line)
	{
		std::cout << file << " in function " << function << " at line " << line << std::endl;
	}
	jgl::Vector2 compose_smaller(jgl::Vector2 first, jgl::Vector2 second)
	{
		float x = (first.x < second.x ? first.x : second.x);
		float y = (first.y < second.y ? first.y : second.y);

		return (jgl::Vector2(x, y));
	}
	jgl::Vector2 compose_biggest(jgl::Vector2 first, jgl::Vector2 second)
	{
		float x = (first.x > second.x ? first.x : second.x);
		float y = (first.y > second.y ? first.y : second.y);

		return (jgl::Vector2(x, y));
	}
	jgl::Vector3 compose_smaller(jgl::Vector3 first, jgl::Vector3 second)
	{
		float x = (first.x < second.x ? first.x : second.x);
		float y = (first.y < second.y ? first.y : second.y);
		float z = (first.z < second.z ? first.z : second.z);

		return (jgl::Vector3(x, y, z));
	}
	jgl::Vector3 compose_biggest(jgl::Vector3 first, jgl::Vector3 second)
	{
		float x = (first.x > second.x ? first.x : second.x);
		float y = (first.y > second.y ? first.y : second.y);
		float z = (first.z > second.z ? first.z : second.z);

		return (jgl::Vector3(x, y, z));
	}
	int floor(float value)
	{
		return (static_cast<int>(std::floor(value)));
	}
	int round(float value)
	{
		return (static_cast<int>(std::round(value)));
	}
	int ceil(float value)
	{
		return (static_cast<int>(std::ceil(value)));
	}
	uint32_t count_word(const jgl::String& input, const jgl::String& delim)
	{
		uint32_t tmp = input.size();
		uint32_t tmp2 = delim.size();
		uint32_t result = 1;

		for (uint32_t i = 0; i < tmp; i++)
		{
			if (input[i] == delim[0])
			{
				uint32_t j = 0;
				while (j < tmp2 &&
					i + j < tmp &&
					input[i + j] == delim[j])
					j++;
				if (j == tmp2)
					result++;
				i += j - 1;
			}
		}
		return (result);
	}
	uint32_t count_word(const jgl::String& input, const jgl::Glyph& delim)
	{
		uint32_t tmp = input.size();
		uint32_t result = 1;

		for (uint32_t i = 0; i < tmp; i++)
		{
			if (input[i].value() == delim.value())
				result++;
		}
		return (result);
	}
	uint32_t unique_count_word(const jgl::Unique_string& input, const jgl::Unique_string& delim)
	{
		uint32_t tmp = input.size();
		uint32_t tmp2 = delim.size();
		uint32_t result = 1;

		for (uint32_t i = 0; i < tmp; i++)
		{
			if (input[i] == delim[0])
			{
				uint32_t j = 0;
				while (j < tmp2 &&
					i + j < tmp &&
					input[i + j].value() == delim[j].value())
					j++;
				if (j == tmp2)
					result++;
				i += j - 1;
			}
		}
		return (result);
	}
	
	uint32_t count_word_len(const jgl::String& input, const jgl::Glyph& delim, const uint32_t start)
	{
		uint32_t tmp = input.size();
		uint32_t result = 0;

		for (result = start; result < tmp; result++)
		{
			if (input[result].value() == delim.value())
				return (result - start);
		}
		return (result - start);
	}

	uint32_t count_word_len(const jgl::String& input, const jgl::String& delim, const uint32_t start)
	{
		uint32_t tmp = input.size();
		uint32_t tmp2 = delim.size();
		uint32_t result = 0;

		for (result = start; result < tmp; result++)
		{
			if (input[result] == delim[0])
			{
				uint32_t j = 0;
				while (j < tmp2 &&
					result + j < tmp &&
					input[result + j].value() == delim[j].value())
					j++;
				if (j == tmp2)
					return (result - start);
				result += j - 1;
			}
		}
		return (result - start);
	}

	uint32_t unique_count_word_len(const jgl::Unique_string& input, const jgl::Unique_string& delim, const uint32_t start)
	{
		uint32_t tmp = input.size();
		uint32_t tmp2 = delim.size();
		uint32_t result = 0;

		for (result = start; result < tmp; result++)
		{
			if (input[result] == delim[0])
			{
				uint32_t j = 0;
				while (j < tmp2 &&
					result + j < tmp &&
					input[result + j].value() == delim[j].value())
					j++;
				if (j == tmp2)
					return (result - start);
				result += j - 1;
			}
		}
		return (result - start);
	}

	jgl::Array<jgl::String> strsplit(const jgl::String input, const jgl::String delim, const bool regroup)
	{
		jgl::Array<jgl::String>	tab(40);

		strsplit(tab, input, delim, regroup);

		return (tab);
	}

	void strsplit(jgl::Array<jgl::String>& tab, const jgl::String input, const jgl::String delim, const bool regroup)
	{
		uint32_t tmp = input.size();
		uint32_t tmp2 = delim.size();
		uint32_t index = 0;
		uint32_t nb_word = 0;
		uint32_t total_nb_word = count_word(input, delim);

		tab.resize(total_nb_word);
		for (uint32_t i = 0; i < total_nb_word; i++)
			tab[i].clear();
		while (index < tmp)
		{
			uint32_t word_len = count_word_len(input, delim, index);
			if (word_len != 0 || regroup == true)
			{
				input.substr(tab[nb_word], index, index + word_len);
				nb_word++;
			}
			index += word_len + tmp2;
		}
	}
	jgl::Array<jgl::Unique_string> unique_strsplit(const jgl::Unique_string input, const jgl::Unique_string c, const bool regroup)
	{
		jgl::Array<jgl::Unique_string> tab;

		unique_strsplit(tab, input, c, regroup);

		return (tab);
	}

	void unique_strsplit(jgl::Array<jgl::Unique_string>& tab, const jgl::Unique_string input, const jgl::Unique_string delim, const bool regroup)
	{
		uint32_t tmp = input.size();
		uint32_t tmp2 = delim.size();
		uint32_t index = 0;
		uint32_t nb_word = 0;
		tab.clear();

		tab.resize(unique_count_word(input, delim));
		while (index < tmp)
		{
			uint32_t word_len = unique_count_word_len(input, delim, index);
			if (word_len != 0 || regroup == true)
			{
				input.substr(tab[nb_word], index, index + word_len);
				nb_word++;
			}
			index += word_len + tmp2;
		}
	}

	void check_sdl_error(const jgl::String file, const int line)
	{
		jgl::String text = SDL_GetError();
		if (text.size() != 0)
		{
			jgl::Array<jgl::String>tab = file.split("\\");
			if (tab.size() == 1)
				tab = file.split("/");
			jgl::String file_name = tab[tab.size() - 1];
			error_exit(1, file_name + " - line [" + std::to_string(line) + "] : " + text);
		}
	}

	void				error_exit(const int num, const jgl::String error)
	{
		std::cout << error << std::endl;
		if (g_application != nullptr)
			g_application->quit();
		jgl::quit_jgl();
		exit(num);
	}

	void error_exit(const int num, const char* str)
	{
		std::cout << str << std::endl;
		if (g_application != nullptr)
			g_application->quit();
		else
			jgl::quit_jgl();
		exit(num);
	}

	jgl::String normalize_string(const jgl::String str, const jgl::Glyph c, const uint32_t size)
	{
		jgl::String result;

		result = str;

		while (result.size() < size)
			result.insert(0, c);

		return (result);
	}

	jgl::String normalize_float(const float num, const int after_point, const jgl::Glyph c, const uint32_t size)
	{
		jgl::String result;

		result = ftoa(num, after_point);
		while (result.size() < size)
			result.insert(0, c);

		return (result);
	}

	void reverse(jgl::String& base)
	{
		uint32_t i = 0, j = base.size() - 1;
		Glyph temp;
		while (i < j)
		{
			temp = base[i];
			base[i] = base[j];
			base[j] = temp;
			i++; j--;
		}
	}

	jgl::String itoa(const int x, const int d)
	{
		std::string result = std::to_string(x);
		uint32_t i = result.size();

		if (d > 0)
		{
			while (i < (uint32_t)d)
			{
				result.insert(0, " ");
				i++;
			}
		}

		return (jgl::String(result));
	}

	// Converts a floating point number tostring.
	jgl::String ftoa(const float n, const int afterpoint, const int length)
	{
		std::string text;
		std::stringstream out;
		int tmp = afterpoint;

		if (n > 0 || n < -1)
			tmp += 2;
		out << std::setprecision(tmp) << n;
		text = out.str();
		while (length != -1 && text.length() < static_cast<uint32_t>(length))
			text.insert(text.begin(), ' ');
		out.seekp(0);
		out << text;
		return jgl::String(out.str());
	}
	// Converts a floating point number tostring.
	jgl::String ftoa(const double n, const int afterpoint, const int length)
	{
		return (ftoa((float)n, afterpoint, length));
	}


	float stof(const jgl::String text)
	{
		const char* tmp = static_cast<jgl::String>(text).str();
		return (static_cast<float>(std::atof(tmp)));
	}
	int stoi(const jgl::String text)
	{
		const char* tmp = static_cast<jgl::String>(text).str();
		return (std::atoi(tmp));
	}

	bool string_is_numeric(const jgl::String text)
	{
		return (text->contain("0123456789."));
	}

	bool is_middle(const float min, const float value, const float max)
	{
		if (value < min)
			return (false);
		if (value >= max)
			return (false);
		return (true);
	}

	bool is_middle(const jgl::Vector2 min, const jgl::Vector2 value, const jgl::Vector2 max)
	{
		if (is_middle(min.x, value.x, max.x) == true && is_middle(min.y, value.y, max.y) == true)
			return (true);
		return (false);
	}

	void remove_char(jgl::String& src, const jgl::String to_remove)
	{
		jgl::String result;
		for (uint32_t i = 0; i < src.size(); i++)
		{
			Glyph target = '\0';
			for (uint32_t j = 0; j < to_remove.size(); j++)
				if (to_remove[j] == src[i])
					target = to_remove[j];

			if (target == '\0')
				result.push_back(src[i]);
		}
		src = result;
	}

	jgl::Array<Vector2> 		calc_line_2d(float x1, float y1, float x2, float y2)
	{
		jgl::Array<Vector2> result;
		const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
		if (steep)
		{
			std::swap(x1, y1);
			std::swap(x2, y2);
		}
		if (x1 > x2)
		{
			std::swap(x1, x2);
			std::swap(y1, y2);
		}

		float dx = x2 - x1;
		float dy = fabs(y2 - y1);

		float error = dx / 2.0f;
		int ystep = (y1 < y2) ? 1 : -1;
		int y = (int)y1;

		int maxX = (int)x2;

		for (int x = (int)x1; x < maxX; x++)
		{
			if (steep)
				result.push_back(Vector2(y, x));
			else
				result.push_back(Vector2(x, y));

			error -= dy;
			if (error < 0)
			{
				y += ystep;
				error += dx;
			}
		}
		return (result);
	}

	uint32_t generate_nbr_from_2D(long long seed, int x, int y)
	{
		uint32_t h = seed + x * 374761393 + y * 668265263; //all constants are prime
		h = (h ^ (h >> 13)) * 1274126177;
		return h ^ (h >> 16);
	}

	uint32_t generate_nbr(const int min, const int max)
	{
		return((rand() % (max - min)) + min);
	}

	Vector2				convert_screenV2_to_opengl(const Vector2 source)
	{
		if (g_application == nullptr)
			error_exit(1, "jgl::Application not created");
		float x = (source.x) / (g_application->active_viewport()->area().x / 2.0f) - 1.0f;
		float y = -((source.y) / (g_application->active_viewport()->area().y / 2.0f) - 1.0f);
		return (Vector2(x, y));
	}

	Vector3				convert_screen_to_opengl(const Vector2 source)
	{
		if (g_application == nullptr)
			error_exit(1, "jgl::Application not created");
		float x = (source.x) / (g_application->active_viewport()->area().x / 2.0f) - 1.0f;
		float y = -((source.y) / (g_application->active_viewport()->area().y / 2.0f) - 1.0f);
		return (Vector3(x, y, 0.0f));
	}

	Vector2				convert_opengl_to_screen(const Vector2 source)
	{
		if (g_application == nullptr)
			error_exit(1, "jgl::Application not created");
		float x = (source.x + 1.0f) * (g_application->active_viewport()->area().x / 2.0f);
		float y = (source.y - 1.0f) * (g_application->active_viewport()->area().y / -2.0f);
		return (Vector2(x, y));
	}

	Vector2				convert_opengl_to_screen(const Vector3 source)
	{
		if (g_application == nullptr)
			error_exit(1, "jgl::Application not created");
		float x = (source.x + 1.0f) * (g_application->active_viewport()->area().x / 2.0f);
		float y = (source.y - 1.0f) * (g_application->active_viewport()->area().y / -2.0f);
		return (Vector2(x, y));
	}

	SDL_Surface* create_surface_color(const Color p_color)
	{
		SDL_Surface* surface;
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

	float				degree_to_radian(const float angle)
	{
		return ((angle * static_cast<float>(M_PI)) / 180.0f);
	}

	float				radian_to_degree(const float radian)
	{
		return ((radian * 180.0f) / static_cast<float>(M_PI));
	}

	float clamp_float(const float min, const float value, const float max)
	{
		if (value < min)
			return (min);
		if (value > max)
			return (max);
		return (value);
	}

	int clamp_int(const int min, const int value, const int max)
	{
		if (value < min)
			return (min);
		if (value > max)
			return (max);
		return (value);
	}

	bool point_in_rectangle(const Vector2 target, const Vector2 pos, const Vector2 size)
	{
		if (target.x > pos.x&& target.x <= pos.x + size.x &&
			target.y > pos.y&& target.y <= pos.y + size.y)
			return (true);
		return (false);
	}

	jgl::Vector3 rotate_point(const jgl::Vector3 pos, const jgl::Vector3 center, const jgl::Vector3 axis, const float angle)
	{
		jgl::Vector3 result;
		jgl::Matrix4x4 rotation = jgl::Matrix4x4::matrix_custom_rotation(angle, axis);

		result = pos - center;
		result = rotation * result + center;
		return (result);
	}
}
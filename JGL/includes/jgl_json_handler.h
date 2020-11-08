#ifndef JGL_JSON_HANDLER_H
#define JGL_JSON_HANDLER_H

#include "jgl_data.h"

typedef 			void(*JSON_Funct)(std::fstream&, size_t, jgl::Data);

namespace jgl
{
	void json_add_line(std::fstream& file, const size_t tab, const jgl::String type_name, const jgl::String symbol);
	void json_add_line(std::fstream& file, const size_t tab, const jgl::String text);


	template <typename T>
	void json_add_vector(std::fstream& file, const size_t tab, const jgl::String type_name, const jgl::Array<T>& vector, const JSON_Funct p_funct, Data p_data)
	{
		Data data;

		json_add_line(file, tab, type_name, "[");
		for (size_t i = 0; i < vector.size(); i++)
		{
			data = p_data + Data(&(vector[i]));
			json_add_line(file, tab + 1, "{");

			if (p_funct != nullptr)
				p_funct(file, tab + 2, data);

			if (i != vector.size() - 1)
				json_add_line(file, tab + 1, "},");
			else
				json_add_line(file, tab + 1, "}");
		}
		json_add_line(file, tab, "],");
	}

	template <typename T, typename V>
	void json_add_map(std::fstream& file, const size_t tab, const jgl::String type_name, const std::map<T, V> map, const JSON_Funct p_funct, Data p_data)
	{
		if (map.size() == 0)
			return;

		Data data;
		auto final_iter = map.end();
		--final_iter;

		json_add_line(file, tab, type_name, "[");

		for (auto it = map.begin(); it != map.end(); it++)
		{
			data = p_data + Data(2, &(it->first), &(it->second));

			json_add_line(file, tab + 1, "{");

			if (p_funct != nullptr)
				p_funct(file, tab + 2, data);

			if (it != final_iter)
				json_add_line(file, tab + 1, "},");
			else
				json_add_line(file, tab + 1, "}");
		}
		json_add_line(file, tab, "],");
	}
}
#endif

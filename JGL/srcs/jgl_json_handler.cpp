#include "jgl.h"

namespace jgl
{
	void json_add_line(std::fstream& file, uint32_t tab, jgl::String type_name, jgl::String symbol)
	{
		jgl::String result = "";

		for (uint32_t i = 0; i < tab; i++)
			result += "\t";

		if (type_name != "")
			result += "\"" + type_name + "\":";

		result += symbol;

		write_on_file(file, type_name + ";" + result);
	}

	void json_add_line(std::fstream& file, uint32_t tab, jgl::String text)
	{
		jgl::String result("");

		for (uint32_t i = 0; i < tab; i++)
			result += "\t";

		result += text;

		write_on_file(file, result);
	}
}
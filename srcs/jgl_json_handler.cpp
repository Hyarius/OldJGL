#include "jgl.h"

void json_add_line(fstream &file, size_t tab, string type_name, string symbol)
{
	string result = "";

	for (size_t i = 0; i < tab; i++)
		result += "\t";

	if (type_name != "")
		result += "\"" + type_name + "\":";

	result += symbol;

	write_on_file(file, result);
}

void json_add_line(fstream &file, size_t tab, string text)
{
	string result = "";

	for (size_t i = 0; i < tab; i++)
		result += "\t";

	result += text;

	write_on_file(file, result);
}

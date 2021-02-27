#include "jgl.h"

std::fstream log_file;
int line;

#define _CRT_SECURE_NO_WARNINGS

namespace jgl
{
	void open_log_file(jgl::String path, jgl::String log_name)
	{
		jgl::String full_path = path + log_name + ".log";
		if (check_file_exist(full_path) == true)
		{
			for (int i = 1; check_file_exist(full_path) == true; i++)
				full_path = path + log_name + " (" + std::to_string(i) + ")" + ".log";
		}
		log_file.open(full_path.std().c_str(), std::ios_base::out);
		line = 0;

		jgl::String text = "=== " + log_name + " ===\n";
		log_file << text;
		uint32_t len = text.size() - 1;
		text.clear();
		for (uint32_t i = 0; i < len; i++)
			text.push_back('=');
		text.push_back('\n');
		log_file << text;
	}

	jgl::String get_file_info(jgl::String file_info, int line)
	{
		jgl::Array<jgl::String>tab = strsplit(file_info, "\\");
		if (tab.size() == 1)
			jgl::Array<jgl::String>tab = strsplit(file_info, "/");
		jgl::String file_name = tab[tab.size() - 1];
		return("[" + file_name + "][" + std::to_string(line) + "]");
	}

	void write_in_log(jgl::String msg)
	{
		if (log_file.fail())
			return;
		static jgl::String text;
		jgl::String text_line = std::to_string(line);
		while (text_line.size() < 5)
			text_line.push_front('0');
		text += (text.size() == 0 ? "[" + text_line + "] - " + msg : msg);
		if (msg.find('\n') == true)
		{
			log_file << text;
			text.clear();
			line++;
		}
	}
}
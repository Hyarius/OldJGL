#include "jgl.h"

fstream log_file;
int line;

void open_log_file(string path, string log_name)
{
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	std::ostringstream oss;
	oss << std::put_time(&tm, "-%d-%m-%Y");
	string str = oss.str();
	string full_path = path + log_name + str + ".log";
	if (check_file_exist(full_path) == true)
	{
		for (int i = 1; check_file_exist(full_path) == true; i++)
			full_path = path + log_name + str + " (" + to_string(i) + ")" + ".log";
	}
	log_file.open(full_path.c_str(), ios_base::out);
	line = 0;

	std::ostringstream oss2;
	oss2 << std::put_time(&tm, "%d-%m-%Y %Hh-%Mm-%Ss");
	str = oss2.str();
	string text = "=== " + log_name + " - " + str + " - ===\n";
	log_file << text;
	size_t len = text.length() - 1;
	text.clear();
	for (size_t i = 0; i < len; i++)
		text.append("=");
	text.append("\n");
	log_file << text;
}

string get_file_info(string file, int line)
{
	vector<string>tab = strsplit(file, "\\");
	if (tab.size() == 1)
		vector<string>tab = strsplit(file, "/");
	string file_name = tab[tab.size() - 1];
	return("[" + file_name + "][" + to_string(line) + "]");
}

void write_in_log(string msg)
{
	if (log_file.fail())
		return ;
	static string text;
	string text_line = to_string(line);
	while (text_line.size() < 5)
		text_line.insert(text_line.begin(), '0');
	text += (text.size() == 0 ? "[" + text_line + "] - " + msg : msg);
	if (msg.find('\n') != string::npos)
	{
		log_file << text;
		text.clear();
		line++;
	}
}

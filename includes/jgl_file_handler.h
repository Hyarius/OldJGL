#ifndef JGL_FILE_HANDLER_H
#define JGL_FILE_HANDLER_H

#ifdef _WIN32
#	define strtok_r strtok_s
#endif

fstream open_file(string path, ios_base::openmode mode = ios_base::in | ios_base::out);
string get_str(fstream &myfile);
vector<string> get_strsplit(fstream &myfile, const string c, int size);
vector<string> list_files(string path, string extension);
bool check_file_exist(string path);
bool copy_file(string src, string dest);
void write_on_file(string path, string text);
void rewrite_on_file(string path, string text);
void write_on_file(fstream &myfile, string text);

#endif

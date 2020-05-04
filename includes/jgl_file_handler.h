#ifndef JGL_FILE_HANDLER_H
#define JGL_FILE_HANDLER_H

#ifdef _WIN32
#	define strtok_r strtok_s
#endif

namespace jgl
{
	std::fstream open_file(jgl::String path, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out);
	jgl::String get_str(std::fstream& file);
	std::vector<jgl::String> get_strsplit(std::fstream& file, const jgl::String c, int size = -1);
	std::vector<jgl::String> list_files(jgl::String path, jgl::String extension);
	bool check_file_exist(jgl::String path);
	void copy_file(jgl::String src_path, jgl::String dest_path);
	void write_on_file(jgl::String path, jgl::String text);
	void rewrite_on_file(jgl::String path, jgl::String text);
	void write_on_file(std::fstream& file, jgl::String text);
}
#endif

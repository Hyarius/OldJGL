#ifndef JGL_FILE_HANDLER_H
#define JGL_FILE_HANDLER_H

#ifdef _WIN32
#	define strtok_r strtok_s
#endif

namespace jgl
{
	enum class File_type
	{
		file = DT_REG,
		directory = DT_DIR,
		block = DT_BLK,
		char_periph = DT_CHR,
		tube = DT_FIFO,
		link = DT_LNK,
		socked = DT_SOCK,
		error = DT_UNKNOWN,
		count
	};
	struct File
	{
		jgl::String path;
		jgl::String name;
		jgl::String extension;
		jgl::File_type type;

		File()
		{
			path = "";
			name = "";
			extension = "";
			type = File_type::error;
		}
		File(jgl::String p_path, jgl::String p_name, jgl::File_type p_type){
			std::vector<jgl::String> tmp;

			path = p_path;

			type = p_type;
			if (type == jgl::File_type::file)
			{
				tmp = strsplit(p_name, ".");
				name = tmp[0];
				if (tmp.size() >= 2)
					extension = "." + tmp[1];
			}
			else if (type == jgl::File_type::directory)
			{
				name = p_name;
				extension = "";
			}
		}
	};

	std::fstream open_file(jgl::String path, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out);
	jgl::String get_str(std::fstream& file);
	std::vector<jgl::String> get_strsplit(std::fstream& file, const jgl::String c, int size = -1);
	std::vector<jgl::File> list_files(jgl::String path, jgl::String extension = "*");
	bool check_file_exist(jgl::String path);
	void copy_file(jgl::String src_path, jgl::String dest_path);
	void write_on_file(jgl::String path, jgl::String text);
	void rewrite_on_file(jgl::String path, jgl::String text);
	void write_on_file(std::fstream& file, jgl::String text);
}

std::ostream& operator<<(std::ostream& os, jgl::File value);

#endif

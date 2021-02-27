#include "jgl.h"

namespace jgl
{
	std::fstream				open_file(jgl::String path, std::ios_base::openmode mode)
	{
		std::fstream file;
		file.open(path.std(), mode);
		if (file.fail() == true)
			error_exit(1, "Error while openning (" + path + ") file");
		return (file);
	}

	jgl::String					get_str(std::fstream& file)
	{
		std::string line;

		if (file.eof())
			return ("");
		std::getline(file, line);
		if (line.size() == 0)
			return ("");
		if (line[strlen((char*)line.c_str()) - 1] == L'\n')
			line[strlen((char*)line.c_str()) - 1] = L'\0';
		return (line);
	}

	jgl::Array<jgl::String>			get_strsplit(std::fstream& file, const jgl::String c, int size)
	{
		jgl::Array<jgl::String> tab;
		jgl::String line;

		line = get_str(file);
		if (line.size() == 0)
		{
			if (size != -1)
				error_exit(1, get_file_info(__FILE__, __LINE__) + " - Empty line in get_strsplit when espect a size");
			tab.resize(0);
			return (tab);
		}
		tab = strsplit(line, c, false);
		if (size != -1 && tab.size() != (uint32_t)size)
			error_exit(1, get_file_info(__FILE__, __LINE__) + " - Bad lenght in get_strsplit");
		return tab;
	}

	jgl::Array<jgl::File>		list_files(jgl::String path, jgl::String extension)
	{
		jgl::Array<jgl::File> files;
		jgl::String line;
		jgl::String test;
		dirent* dirent_ptr;
		DIR* dir = opendir(path.std().c_str());

		files.clear();
		if (dir == NULL)
			return (files);

		while ((dirent_ptr = readdir(dir)) != NULL)
		{
			jgl::String tmp_name = dirent_ptr->d_name;
			jgl::File tmp = jgl::File(path, tmp_name, static_cast<jgl::File_type>(dirent_ptr->d_type));
			if (extension == "*")
				files.push_back(tmp);
			else if ((tmp.type == jgl::File_type::file && tmp.extension == extension) ||
					(tmp.type == jgl::File_type::directory && tmp.name != "."))
				files.push_back(tmp);
		}
		closedir(dir);
		return files;
	}

	bool				check_file_exist(jgl::String path)
	{
		std::fstream file(path.std().c_str());
		return file.good();
	}

	void				copy_file(jgl::String src_path, jgl::String dest_path)
	{
		std::fstream source;
		std::fstream destination;

		source.open(src_path.std(), std::ios::binary);
		destination.open(dest_path.std(), std::ios::binary);

		source.seekg(0, std::ios::end);
		std::fstream::pos_type size = source.tellg();
		source.seekg(0);
		char* buffer = new char[static_cast<uint32_t>(size)];

		source.read(buffer, size);
		destination.write(buffer, size);
	}

	void				write_on_file(std::fstream& file, jgl::String text)
	{
		file << text << std::endl;
	}

	void				write_on_file(jgl::String path, jgl::String text)
	{
		std::fstream file;
		file.open(path.std().c_str(), std::ios::app);
		file << text << std::endl;
		file.close();
	}

	void				rewrite_on_file(jgl::String path, jgl::String text)
	{
		std::fstream file;
		file.open(path.std().c_str());
		file << text << std::endl;
		file.close();
	}
}
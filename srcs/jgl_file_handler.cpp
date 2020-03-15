#include "jgl.h"

fstream				open_file(string path, ios_base::openmode mode)
{
	fstream file;
	file.open(path, mode);
	if (mode & ios_base::out && file.fail())
		error_exit(1, "Error while creating a file at path : " + path);

	return (file);
}

string					get_str(fstream &file)
{
    string line;

	if (file.eof())
		return ("");
    getline(file, line);
	if (line.size() == 0)
		return ("");
    if (line[strlen((char *)line.c_str()) - 1] == '\n')
        line[strlen((char *)line.c_str()) - 1] = '\0';
    return (line);
}

vector<string>			get_strsplit(fstream &file, const string c, int size)
{
    vector<string> tab;
    string line;
    string saved_line;
    char	*word;
	char	*context = NULL;

    line = get_str(file);
	if (line == "")
	{
		if (size != -1)
			error_exit(1, get_file_info(__FILE__, __LINE__) + " - Empty line in get_strsplit when espect a size");
		tab.resize(0);
		return (tab);
	}
	saved_line = line;
    word = strtok_r((char *)(line.c_str()), c.c_str(), &context);
    while(word != NULL)
    {
        tab.push_back(word);
        word = strtok_r(NULL, c.c_str(), &context);
    }
	if (size != -1 && tab.size() != (size_t)size)
		error_exit(1, get_file_info(__FILE__, __LINE__) + " - Bad lenght in get_strsplit");
    return tab;
}

vector<string>		list_files(string path, string extension)
{
	vector<string> brut_files;
	vector<string> files;
	string line;
	string test;
	size_t i = 2;
	dirent *dirent_ptr;
	DIR *dir = opendir(path.c_str());

	if (dir == NULL)
		error_exit(1, get_file_info(__FILE__, __LINE__) + " - Folder " + path + " didn't exist");

	while ((dirent_ptr = readdir(dir)) != NULL)
	{
		string tmp = dirent_ptr->d_name;
		brut_files.insert(brut_files.end(), tmp);
	}
	while (i < brut_files.size())
	{
		if (brut_files[i].find(extension.c_str(), 0, extension.size()) != string::npos)
		{
			test = strsplit(brut_files[i], extension)[0];
			files.insert(files.end(), test);
		}
		i++;
	}
	return files;
}

bool				check_file_exist(string path)
{
	fstream file(path.c_str());
    return file.good();
}

void				copy_file(string src_path, string dest_path)
{
	fstream source;
	fstream destination;

	source.open(src_path, ios::binary);
	destination.open(dest_path, ios::binary);

	source.seekg(0, ios::end);
	fstream::pos_type size = source.tellg();
	source.seekg(0);
	char* buffer = new char[static_cast<size_t>(size)];

	source.read(buffer, size);
	destination.write(buffer, size);
}

void				write_on_file(fstream &file, string text)
{
	file << text << endl;
}

void				write_on_file(string path, string text)
{
	fstream file;
	file.open(path.c_str(), ios::app);
	file << text << endl;
	file.close();
}

void				rewrite_on_file(string path, string text)
{
	fstream file;
	file.open(path.c_str());
	file << text << endl;
	file.close();
}

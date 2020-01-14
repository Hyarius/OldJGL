## Fonction de gestion de fichier :  
- `fstream open_file(string path, ios_base::openmode mode = ios_base::in | ios_base::out)`  
	Retourne un fstream du fichier au chemin `path` suivant les modes decrit par `mode`.  


- `string get_str(fstream &file)`  
	Retourne la prochaine ligne du fichier `file`


- `vector<string> get_strsplit(fstream &file, const string c, int size)`  
	Retourne la prochaine ligne du fichier `file` decoupees en plusieurs strings, a chaque caractere `c` lu.


- `vector<string> list_files(string path, string extension)`  
	Liste les fichiers d'extension `extension` au chemin relatif ou absolu `path`.


- `bool check_file_exist(string path)`  
	Renvoi `true` si le fichier de chemin `path` existe, sinon renvoi `false`.


- `void copy_file(string src_path, string dest_path)`  
	Copie le contenu du fichier de chemin `src_path` dans le fichier `dest_path`.


- `void write_on_file(string path, string text)`  
	Ecrit la string `text` a la fin du fichier de chemin `path`.


- `void rewrite_on_file(string path, string text)`  
	Efface le contenu du fichier de chemin `path` et y ecrit la string `text`.


- `void write_on_file(fstream &file, string text)`  
	Ecrit dans le fichier `file` la string `text`


### Exemple d'utilisation

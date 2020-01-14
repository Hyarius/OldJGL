### Fonctions de sauvegarde de JSON :
- `void json_add_line(fstream &file, size_t tab, string type_name, string symbol)`  
	Ajoute au fichier `file` l'element de type `type_name` avec `tab` nombre de tabulation avant et avec comme valeur la string `symbol`.


- `void json_add_line(fstream &file, size_t tab, string text)`  
	Ajoute au fichier `file` la string `text` avec `tab` nombre de tabulation avant.


- `template <typename T> void json_add_vector(fstream &file, size_t tab, string type_name, vector<T> &vector, Funct p_funct, Data p_data)`  
	Lance le pointeur de fonction `p_funct` sur chaque element du vector `vector` avec comme parametre la [Data](.readme/data.md) `p_data` + l'element du vector.


- `template <typename T, typename V> void json_add_map(fstream &file, size_t tab, string type_name, map<T, V> map, Funct p_funct, Data p_data)`  
	Lance le pointeur de fonction `p_funct` sur chaque element de la map `vector` avec comme parametre la [Data](.readme/data.md) `p_data` + la clef et l'element de la map en question.

### Exemple d'utilisation

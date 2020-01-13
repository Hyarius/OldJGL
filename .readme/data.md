## Data : Conteneur de data
La structure Data est une structure permettant de stocker plusieurs donnees afin d'etre passe a travers des pointeurs de fonctions.  
Elle est principalement employee conjointement avec les [c_button](.readme/button.mb).  

### Methodes publiques :
- `Data(void *p_data = NULL)`  
	Construit une Data en lui donnant une addresse (Facultatif).


- `Data(int nb_param, ...)`  
	Construit une Data en lui donnant le nombre d'addresse qu'on lui donne dans les parametres variatiques.  
	Exemple : `Data param = Data(3, &value1, &value2, &value3);`


- `void operator = (void *p_data)`  
	Permet d'assigner a une Data un contenu.

- `void operator + (void *p_ptr)`  
	Ajoute au contenu de la Data le pointeur `p_ptr`.


- `Data operator + (const Data& delta)`  
	Ajoute au contenu de la Data le contenu d'une autre Data `delta`.


- `void operator += (void *p_ptr)`  
	Ajoute au contenu de la Data le pointeur `p_ptr`.


- `void operator += (const Data& delta)`  
	Ajoute au contenu de la Data le contenu d'une autre Data `delta`.


- `template <typename T> T acces(size_t index)`  
	Renvoi l'addresse numero `index` du Data, sous forme d'un pointeur de type T.


### Exemple d'utilisation

## C_BUTTON : Widget de bouton

La classe c_button est une classe permettant de lier un widget avec un pointeur de fonction de type `void (*Funct)(Data)` avec comme parametre le [Data](.readme/data.md) donne au c_button.

### Methodes publiques :

- `c_button(Funct p_funct = nullptr, Data p_data = nullptr, c_widget *p_parent = nullptr)`
	Construit un widget de type c_button en lui assignant ces interactions.  


- `w_box_component &box()`  
	Renvoi un reference sur le composant box du bouton.


- `w_text_component &label()`  
	Renvoi un reference sur le composant label du bouton.



#### - box redirection function
- `void set_tileset(c_tileset *p_tileset)` et `void set_tileset(string path)`  
	Defini l'apparence du widget grace a un tileset 3x3.


- `void set_corner_size(size_t p_corner_size)`  
	Defini la bordure du tileset 3x3.


- `size_t corner_size()`  
	Retourne la taille de la bordure texturée du widget


- `void set_image(c_tileset *p_image)`, `void set_image(c_image *p_image)` et `void set_image(string path)`  
	Defini l'image a afficher sur le widget etiree sur toute la surface du widget (L'image peut etre une portion de l'image totale).


- `void set_sprite(int p_sprite)`  
	Defini le sprite a afficher pour la variable image.


- `int sprite()`  
	Retourne la valeur sprite decrivant l'image a afficher a l'ecran.


- `void set_back(Color p_back)`  
	Defini la couleur de la bordure de la box.


- `void set_front(Color p_front)`  
	Defini la couleur de l'interieur de la box.


- `void set_border(int p_border)`  
	Defini la taille de la bordure de la box.


- `c_tileset *tileset()`  
	Retourne le tileset utilise pour la bordure texturee.


- `c_tileset *image()`  
	Retourne le tileset utilise dans l'image.


- `int border()`  
	Retourne la taille de la bordure.


- `Color back()`  
	Retourne la couleur de la bordure.


- `Color front()`  
	Retourne la couleur de l'interieur.

#### - label redirection function
- `void 		set_text(string p_text)`  
	Defini le texte a afficher.


- `void 		set_align(alignment p_align)`  
	Defini l'alignement du texte dans la zone qui lui est defini.


- `void 		set_size(int p_size)`  
	Defini la taille du texte.


- `void 		set_color(text_color p_color)`  
	Defini la couleur du texte.


- `void 		set_style(text_style p_style)`  
	Defini le style du texte.


- `string 		text()`  
	Retourne le texte affiche.


- `alignment 	align()`  
	Retourne l'alignement du texte.


- `int 		size()`  
	Retourne la taille du textte.


- `text_color 	color()`  
	Retourne la couleur du texte.


- `text_style 	style()`  
	Retourne le style du texte.


#### - Methode propre au bouton
- `void set_action(Funct p_funct, Data p_data)`  
	Defini le pointeur de fonction a utiliser en cas d'interaction avec le bouton.


- `void set_repeat(bool p_repeat)`  
	Defini si le bouton peut etre utiliser une seule fois par clic ou si l'action peut etre repetee.


- `void set_funct(Funct p_funct)`  
	Defini le pointeur de fonction a utiliser, sans modifier les parametres a lui envoyer.


- `void set_data(Data p_data)`  
	Defini les parametres a utiliser, sans modifier le pointeur de fonction.


- `void set_delta(Color p_delta)`  
	Defini la couleur a appliquer par dessus le bouton lors d'une interaction.


- `void set_timer_delta(int p_timer_delta)`  
	Defini le temps en frame durant lequel le bouton restera appuye.


### Exemple d'utilisation

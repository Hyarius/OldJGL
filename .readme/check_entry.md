## C_CHECK_BOX : Widget de selection

La classe c_check_box est une classe permettant de faire une case a cocher lie a une entree de texte.

### Methodes publiques :

- `c_check_box(string p_text = "- Value -", bool p_state = false, c_widget *p_parent = nullptr)`
	Construit un widget de type c_check_box en lui assignant son texte et son etat initial.  


- `w_box_component &box()`  
	Renvoi un reference sur le composant box du check_box_entry.


- `w_check_component &check()`
	Renvoi un reference sur le composant check du check_box_entry.


- `w_text_entry_component &entry()`  
	Renvoi un reference sur le composant entry du check_box_entry.



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
	Retourne la couleur de l'interieur .

#### - entry redirection function
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



#### - Check redirection function
- `void set_state(bool p_state)`  
	Defini l'etat de selection de la check_box.


- `void set_check_border(int p_border)`  
	Defini la taille de la bordure dans le w_check_component.


- `void set_check_back(Color p_back)`  
	Defini la couleur de la bordure du w_check_component.


- `void set_check_front(Color p_front)`  
	Defini la couleur de l'interieur du w_check_component.


- `void set_check_check(Color p_check)`  
	Defini la couleur du w_check_component lorsque selectionne.


- `bool state()`  
	Retourne l'etat du w_check_component.


- `int check_border()`  
	Retourne la taille de la bordure du w_check_component.


- `Color check_back()`  
	Retourne la couleur de la bordure du w_check_component.


- `Color check_front()`  
	Retourne la couleur de l'interieur du w_check_component.


- `Color check_check()`  
	Retourne la couleur du w_check_component lorsque selectionne.


### Exemple d'utilisation

## C_HOUR_ENTRY : Widget d'affichage et d'edition d'heure

La classe c_hour_entry est une classe permettant d'afficher et d'editer une heure sous forme d'affichage digitale.


### Methodes publiques :
- `c_hour_entry(float p_hour = 12.0f, float p_minute = 0.0f, c_widget *p_parent = nullptr)`  
	Construit une c_hour_entry avec comme heure affichee `p_hour`:`p_minute`.  


- `void select()`  
	Selectionne la partie heure ou la partie minute du c_hour_entry suivant la position de la souris.


- `void unselect()`  
	Deselectionne la c_hour_entry.


- `float value()`  
	Retourne l'heure stockee dans la c_hour_entry exprime en minute.


- `bool selected()`  
	Retourne `true` si la c_hour_entry est selectionnee, `false` si non.


- `w_box_component &box()`  
	Renvoi un reference sur le composant box du widget.  


- `w_text_component &label()`  
	Renvoi un reference sur le composant box du widget.


- `w_value_entry_component &hour()`  
	Renvoi un reference sur le composant hour du widget.


- `w_value_entry_component &minute()`  
	Renvoi un reference sur le composant minute du widget.


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
- `void set_text(string p_text)`  
	Defini le texte a afficher.


- `void set_align(alignment p_align)`  
	Defini l'alignement du texte dans la zone qui lui est defini.


- `void set_size(int p_size)`  
	Defini la taille du texte.


- `void set_color(text_color p_color)`  
	Defini la couleur du texte.


- `void set_style(text_style p_style)`  
	Defini le style du texte.


- `string text()`  
	Retourne le texte affiche.


- `alignment align()`  
	Retourne l'alignement du texte.


- `int size()`  
	Retourne la taille du textte.


- `text_color color()`  
	Retourne la couleur du texte.


- `text_style style()`  
	Retourne le style du texte.


#### - Fonctions propre aux c_hour_entry  
- `void set_hour_value(float p_value)` et `void set_minute_value(float p_value)`  
	Defini respectivement l'heure et les minutes du c_hour_entry.  


- `float hour_value()` et `float minute_value()`   
	Renvoi respectivement l'heure et les minutes du c_hour_entry sous forme de float.  


- `string hour_text()` et `string minute_text()`  
	Renvoi respectivement l'heure et les minutes du c_hour_entry sous forme de string.


### Exemple d'utilisation

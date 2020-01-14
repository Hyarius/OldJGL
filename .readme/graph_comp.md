## W_GRAPHICAL_COMPONENT : Composant de widget
w_graphical_component est une classe de type w_component pouvant etre utiliser dans un widget.
Cette classe sert a contenir les informations necessaires a l'affichage de la majorite des composants de base de la JGL.

### Methodes publiques :
- `void set_tileset(c_tileset *p_tileset)`  
	Defini l'apparence du widget grace a un tileset 3x3.


- `void set_corner_size(size_t p_corner_size)`  
	Defini la bordure du tileset 3x3.


- `size_t corner_size()`  
	Retourne la taille de la bordure texturée du widget


- `void set_image(c_tileset *p_image)`  
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




### Exemple d'utilisation

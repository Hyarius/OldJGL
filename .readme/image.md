## C_IMAGE : Structure d'image 2D
La structure c_image contient les informations necessaires a l'affichage d'une image a l'ecran.

### Methodes publiques :
- `c_image()`  
	Construit une c_image vierge, avec des parametres null.


- `c_image(string path)`  
	Construit une image a partir du fichier de chemin `path`.


- `c_image(size_t width, size_t height, Color p_color)`  
	Construit une image de taille `width`/`height` et de [couleur](color.md) `p_color`.


- `c_image(SDL_Surface *p_surface)`  
	Construit une image a partir d'une SDL_Surface \*.


- `void draw(Vector2 p_pos, Vector2 p_size, c_viewport *viewport = nullptr)`  
	Affiche l'image a l'ecran avec l'angle haut/gauche aux coordonnees `p_pos` et de taille `p_size`, dans le viewport `viewport`.


- `void save(string file_path)`  
	Sauvegarde l'image dans le fichier de chemin `path`.



- `SDL_Surface *surface()`  
	Renvoi la surface de l'image.


- `Vector2 size()`  
	Renvoi la taille en pixel de l'image.




### Exemple d'utilisation

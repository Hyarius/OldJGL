## Fonctions de dessins de formes
- `void draw_line(Vector2 p1, Vector2 p2, int width, Color p_color, c_viewport *viewport = nullptr)`  
	Affiche une ligne de [couleur](color.md) `p_color` entre les deux points decrits par `p1` et `p2` a l'interieur du viewport `viewport`.


- `void draw_point(Vector2 center, int width, Color p_color, c_viewport *viewport = nullptr)`  
	Affiche un point de taille `width` et de [couleur](color.md) `p_color` aux coordonnees decrites par `center` a l'interieur du viewport `viewport`.


- `void draw_rectangle(Vector2 p_tl, Vector2 p_tr, Vector2 p_dl, Vector2 p_dr, Color p_color, c_viewport *viewport = nullptr)`  
	Affiche le perimetre de [couleur](color.md) `p_color` d'un rectangle decrits par ces 4 sommets a l'interieur du viewport `viewport`.



- `void fill_rectangle(Vector2 p_tl, Vector2 p_tr, Vector2 p_dl, Vector2 p_dr, Color p_color, c_viewport *viewport = nullptr)`  
	Affiche un rectangle de [couleur](color.md) `p_color` decrits par ces 4 sommets a l'interieur du viewport `viewport`.


- `void draw_rectangle(Vector2 pos, Vector2 size, Color p_color, c_viewport *viewport = nullptr)`  
	Affiche le perimetre de [couleur](color.md) `p_color` d'un rectangle aux coordonnees decrites par `pos` et de taille `size` a l'interieur du viewport `viewport`.



- `void fill_rectangle(Vector2 pos, Vector2 size, Color p_color, c_viewport *viewport = nullptr)`  
	Affiche un rectangle de [couleur](color.md) `p_color` aux coordonnees decrites par `pos` et de taille `size` a l'interieur du viewport `viewport`.



- `void fill_centred_rectangle(Vector2 p_coord, Vector2 p_size, Color p_color, c_viewport *viewport = nullptr)`  
	Affiche le perimetre de [couleur](color.md) `p_color` d'un rectangle dont le centre est decrit par `pos` et de taille `size` a l'interieur du viewport `viewport`.


- `void draw_centred_rectangle(Vector2 p_coord, Vector2 p_size, Color p_color, c_viewport *viewport = nullptr)`  
	Affiche un rectangle de [couleur](color.md) `p_color` dont le centre est decrit par `pos` et de taille `size` a l'interieur du viewport `viewport`.




### Exemple d'utilisation

## Color : Structure decrivant une couleur
La structure Color contient 4 floats, decrivant une couleur RGBA.
Chaque valeur est stocke sous forme de gradient, exprime entre 0 et 1.

### Methodes publiques :
- `Color()`  
	Construit une couleur par default noire.


- `Color(float p_r, float p_g, float p_b, float p_a = 1.0f)`  
	Construit une couleur en prenant les valeurs passees en parametre.  
	La composante alpha est facultative, et sera concideree comme 1.0f si absente.


- `Color(unsigned char p_r, unsigned char p_g, unsigned char p_b, unsigned char p_a = 255)`  
	Construit une couleur en prenant les valeurs passees en parametre et en les divisant par 255.  
	La composante alpha est facultative, et sera concideree comme 1.0f si absente.


- `float *decompose()`  
	Retourne la couleur decomposee comme une suite de 4 floats.


### Operateur :
- `Color operator + (const Color& delta)`  
	Effectue un merge entre la couleur de base et celle passee en parametre.


### Exemple d'utilisation

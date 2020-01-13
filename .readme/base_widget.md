## C_WIDGET : Classe parente de tout les widgets

la classe c_widget est la classe abstraite de la JGL permettant d'inscrire une structure dans la fenetre

### Methodes publiques :

- `vector<c_widget *> childrens()`  
	Retourne la liste de tout les enfants du widget.


- `c_widget *parent()`  
	Retourne le widget parent.


- `Vector2 area()`  
	Retourne la taille du viewport du widget.


- `Vector2 anchor()`  
	Retourne la position du viewport du widget depuis l'angle haut/gauche du widget parent ou de la fenetre.


- `c_viewport *viewport()`  
	Retourne le viewport.


- `bool is_active()`  
	Retourne `true` si le widget est actuellement active sinon retourne `false`.


- `bool is_pointed(Vector2 point)`  
	Retourne `true` si la coordonnees `point` est a l'interieur du widget sinon retourne `false`.


- `void activate()`  
	Active le widget.


- `void desactivate()`  
	Desactive le widget.


- `void set_active(bool new_state)`  
	Defini l'etat d'activation du widget.


- `void set_parent(c_widget *p_parent)`  
	Defini le widget `p_parent` comme parent du widget.


- `void add_children(c_widget *p_children)`  
	Ajoute le widget `p_children` aux enfants du widget.


- `void remove_children(c_widget *p_target)`  
	Retire le widget `p_target` des enfants du widget.


- `void set_anchor(Vector2 p_anchor)`  
	Defini la position du coin haut/gauche du viewport vis a vis du coin haut/gauche du widget parent ou de la fenetre.


- `void set_area(Vector2 p_area)`  
	Defini la taille du viewport.


- `virtual void set_geometry(Vector2 p_anchor, Vector2 p_area)`  
	Defini la taille et la position du viewport et lance la methode `set_geometry_imp(Vector2 p_anchor, Vector2 p_area)` du widget.


### Methodes Abstraites :

- `void set_geometry_imp(Vector2 p_anchor, Vector2 p_area)`  
	Methode decrivant les modifications internes au widget en cas de redimmensionnement.


- `void render()`  
	Methode decrivant la methode a suivre pour afficher le widget a l'ecran.

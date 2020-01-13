## W_COMPONENT : Composant primaire des w_component
Le w_component est une classe de base des w_components, qui contient les informations concernant le proprietaire du composant, l'anchor ou la taille du composant.  
il s'agit d'une classe abstraite dont il faudra composer la fonction `void render(c_viewport *)` dans les enfants.  

### Methodes publiques :
- `w_component(class c_widget *p_owner)`  
	Construit un w_component en lui definisant les valeur par default pour l'anchor et la taille.


- `void set_anchor(Vector2 p_anchor)`  
	Defini l'anchor du composant.


- `void set_area(Vector2 p_area)`  
	Defini la taille du composant.


- `void resize(Vector2 p_anchor, Vector2 p_area)`  
	Defini la taille et l'anchor du composant.


- `Vector2	anchor()`  
	Renvoi l'anchor du composant.


- `Vector2	area()`  
	Renvoi la taille du composant.


- `bool is_pointed(Vector2 point)`  
	Renvoi `true` si la coordonnee dans `point` est a l'interieur du composant sinon renvoi `false`.



### Exemple d'utilisation

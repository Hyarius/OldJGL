## W_CHECK_COMPONENT : Composant de widget
Le w_check_component est une classe de type w_component pouvant etre utiliser dans un widget.  
Elle herite de la class [w_component](comp.md) et de la class [w_graphical_component](graph_comp.md) dont elle prendra les methodes.  
Cette classe permet d'afficher une zone de couleur, taille et position defini dans le w_check_component.

### Methodes publiques :
- `w_check_component(class c_widget *p_owner = nullptr, bool p_state = false)`  
	Cree le composant en lui definisant un proprietaire (Le widget dont il fera parti).

- `void set_state(bool p_state)`  
	Defini l'etat du composant.


- `void set_border(int p_border)`  
	Defini la taille de la bordure du composant.


- `void set_back(Color p_back)`  
	Defini la couleur de la bordure du composant.


- `void set_front(Color p_front)`  
	Defini la couleur de l'interieur du composant.


- `void set_check(Color p_check)`  
	Defini la couleur du composant lorsque selectionne.


- `bool state()`  
	Retourne l'etat du composant.


- `int border()`  
	Retourne la taille de la bordure du composant.


- `Color back()`  
	Retourne la couleur de la bordure du composant.


- `Color front()`  
	Retourne la couleur de l'interieur du composant.


- `Color check()`  
	Retourne la couleur du composant lorsque selectionne.


- `void render(c_viewport *viewport = nullptr)`
	Affiche le w_check_component a l'anchor defini dans la partie [w_component](comp.md)

### Exemple d'utilisation

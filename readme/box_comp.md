## W_BOX_COMPONENT : Composant de widget
Le w_box_component est une classe de type w_component pouvant etre utiliser dans un widget.  
Elle herite de la class [w_component](readme/comp.md) et de la class [w_graphical_component](readme/graph_comp.md) dont elle prendra les methodes.  
Cette classe permet d'afficher une zone de couleur, taille et position defini dans le w_box_component.

### Methodes publiques :
- `w_box_component(class c_widget *p_owner = nullptr)`  
	Cree le composant en lui definisant un proprietaire (Le widget dont il fera parti).

- `void set_delta(Color p_delta)`
	Defini une couleur a appliquer par dessus les couleurs du w_box_xomponent (Utile pour les interactions type bouton)  

- `Color delta()`  
	Retourne la couleur affichee par dessus le w_bow_component.  

- `void render(c_viewport *viewport = nullptr)`
	Affiche le w_box_component a l'anchor defini dans la partie [w_component](readme/comp.md)

### Exemple d'utilisation

`class myWidget : public c_widget
{
private:
	w_box_component _box;

public:
	c_frame(c_widget *p_parent = nullptr) : c_widget(p_parent)
	{
		//Initialisation du box_component avec comme proprietaire le myWidget
		_box = w_box_component(this);
	}

	w_box_component &box(){return (_box);}
	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
	{
		//Definition de l'area et de l'anchor via les methodes heritees du w_component
		_box.set_area(p_area);
		_box.set_anchor(p_anchor);
	}
	void render()
	{
		//Affichage du w_box_component sur le viewport herite du c_widget de myWidget
		_box.render(_viewport);
	}
};`

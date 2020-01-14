### JGL - Librairie graphique pour creation d'interfaces graphiques 2D/3D

***

## Instruction d'utilisation :
Telecharger la librairie et l'extraire.  
./make install  
./make  

Une fois la librarie compilee, le makefile vous aura donne un .a a lié a votre projet

Pour utiliser la librairie JGL, vous devez creer imperativement une [c_application](.readme/application.md) au lancement du programme afin de pouvoir utiliser les fonctions d'affichage graphique

***

## Contenu :  
# Fonctionnalite de base :  
- [Fonctions utilitaires](.readme/utils.md)  
	Un groupe de fonctions variees, contenant des fonctions de conversions, des fonctions de recherche, etc.

- [Affichage de formes primaires](.readme/primitive.md)  
	Fonctions permettant de dessiner des formes primitives en couleur (Cercle, point, line, rectangle).

- [Affichage de texte](.readme/draw_text.md)  
	Fonctions permettant de dessiner du texte a l'ecran.

- [Fonctions de manipulation de fichier](.readme/file.md)  
	Fonctions permettant de gerer le contenu d'un o/f/stream.

- [Fonctions de creation de json](.readme/json.md)  
	Fonctions permettant de creer un json.

- [Fonctions de manipulation de fichier de log](.readme/log.md)  
	Fonctions permettant de gerer le contenu d'un fichier de log.

- [Fonctions de gestion des evenements de souris et clavier](.readme/event.md)  
	Fonctions permettant de gerer les interactions de l'utilisateur via sa souris et son clavier.  

***

# Structure et classe

Classe :

- Gestionnaire de fenetre : [c_application](.readme/application.md)  
	La classe principale de la JGL : Elle contient la fenetre ainsi que tout les composants necessaire a l'affichage a l'ecran de cette derniere.

- Gestionnaire de camera pour les widgets 3D : TO DO  
	Une classe permettant d'afficher a l'ecran un c_mesh.

- Gestionnaire d'objet 3D : TO DO  
	Une classe permettant de stocker un objet 3D en vue de l'afficher via une camera.

- Gestionnaire d'image : [c_image](.readme/image.md)  
	Une classe permettant de charger une image en vue de l'afficher a l'ecran.

- Gestionnaire de tileset : [c_tileset](.readme/tileset.md)  
	Une classe permettant de charger un tileset en vue de l'afficher a l'ecran.

- Gestionnaire de graphique : [c_plot](.readme/plot.md)  
	Une classe permettant de creer des graphiques et de les sauvegarder sous format numerique.

- Gestionnaire de viewport : [c_viewport](.readme/viewport.md)  
	Une classe permettant de creer des zones d'affichage a l'ecran, afin de decouper l'ecran en zones independantes.

***

Structures :

- [Data](.readme/data.md)  
	Une structure de donnees permettant de stocker plusieurs objets. Est necessaire aux widgets boutons.

- [Color](.readme/color.md)  
	Une structure de donnees permettant de stocker les 4 composantes d'une couleur.

- [Uv](.readme/geometry.md)  
	Une structure de donnees permettant de stocker les 2 coordonees d'un point d'une texture.

- [Matrix](.readme/matrix.md)  
	Une structure de donnees permettant d'effectuer des calculs matriciels avec les [Vector4](.readme/vector.md).

- [Vector2](.readme/vector.md)  
	Une structure de donnees permettant de stocker une coordonnees en 2 dimensions.

- [Vector3](.readme/vector.md)  
	Une structure de donnees permettant de stocker une coordonnees en 3 dimensions.

- [Vector4](.readme/vector.md)  
	Une structure de donnees permettant de stocker une coordonnees en 4 dimensions.

***

## Systeme de widget :
Fonctionnement d'un [widget de base](.readme/base_widget.md) au sein de la JGL

Creation d'un widget custom : [Nouveau widget](.readme/new_widget.md)

***

# Widget de base :
- [c_button](.readme/button.md)  
	Un widget de bouton, pouvant lancer un pointeur de fonction en cas de clic de souris.

- [c_check_box](.readme/check_box.md)  
	Un widget pouvant etre selectionne ou deselectionner, avec un texte.

- [c_check_entry](.readme/check_entry.md)  
	Un widget pouvant etre selectionne ou deselectionner, avec une entree de texte.

- [c_frame](.readme/frame.md)  
	Une simple zone dans laquelle ajouter des widgets enfants.

- [c_hour_entry](.readme/hour_entry.md)  
	Un widget permettant d'inscrire une heure, dans une entree de texte.

- [c_image_label](.readme/image_label.md)  
	Un widget permettant d'afficher une image a l'ecran, pouvant etre animee.

- [c_tab](.readme/tab.md)  
	Un widget gerant un systeme de tabulation contenant chacune des widgets separes.

- [c_text_entry](.readme/text_entry.md)  
	Un widget d'entree de texte.

- [c_text_label](.readme/text_label.md)  
	Un widget permettant d'afficher un texte a l'ecran.

- [c_value_entry](.readme/value_entry.md)  
	Un widget disposant d'une entree de texte dans laquelle inscrire une valeur decimale.

- [c_value_label](.readme/value_label.md)  
	Un widget permettant d'afficher une valeur decimale a l'ecran

- [c_vscrollbar](.readme/scrollbar.md)  
	Un widget permettant de faire bouger les enfants du widget auquel il est lie via la mollette de la souris ou d'une interaction a l'ecran

# Composants de widget :  
Afin d'aider a la creation de nouveaux widgets, la JGL comporte une serie de w_component permettant d'effectuer l'affichage de base des widgets.


- [w_component](.readme/comp.md)  
	Composant primaire des composants de widget.  

- [w_graphical_component](.readme/graph_comp.md)  
	Composant secondaire des composants graphiques.  
	Contient les informations necessaires a l'affichage d'un composant graphique (les differentes couleurs, les textures a afficher).

- [w_box_component](.readme/box_comp.md)  
	Composant affichant un simple rectangle avec une bordure.

- [w_check_component](.readme/check_comp.md)  
	Composant affichant une boite, selectionnable.

- [w_text_component](.readme/text_comp.md)  
	Composant affichant un texte.

- [w_text_entry_component](.readme/text_entry_comp.md)  
	Composant affichant une entree de texte.

- [w_value_component](.readme/value_comp.md)  
	Composant affichant une valeur decimale.

- [w_value_entry_component](.readme/value_entry_comp.md)  
	Composant affichant une entree de valeur decimale.

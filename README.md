### JGL - Librairie graphique pour creation d'interfaces graphiques 2D/3D

***

##Instruction d'utilisation :
Telecharger la librairie et l'extraire.
make install
make

Une fois la librarie compilee, le makefile vous aura donne un .a a lié a votre projet

Pour utiliser la librairie JGL, vous devez creer imperativement une c_application au lancement du programme afin de pouvoir utiliser les fonctions d'affichage graphique
readme/new_widget.md

***

##Contenu :
# Fonctionnalite de base :

***

# Structure et classe

Classe :

- Gestionnaire de fenetre : [c_application](readme/application.md)  
	La classe principale de la JGL : Elle contient la fenetre ainsi que tout les composants necessaire a l'affichage a l'ecran de cette derniere.

- Gestionnaire de camera pour les widgets 3D : TO DO  
	Une classe permettant d'afficher a l'ecran un c_mesh.

- Gestionnaire d'objet 3D : TO DO  
	Une classe permettant de stocker un objet 3D en vue de l'afficher via une camera.

- Gestionnaire d'image : [c_image](readme/image.md)  
	Une classe permettant de charger une image en vue de l'afficher a l'ecran.

- Gestionnaire de tileset : [c_tileset](readme/tileset.md)  
	Une classe permettant de charger un tileset en vue de l'afficher a l'ecran.

- Gestionnaire de graphique : [c_plot](readme/plot.md)  
	Une classe permettant de creer des graphiques et de les sauvegarder sous format numerique.

- Gestionnaire de viewport : [c_viewport](readme/viewport.md)  
	Une classe permettant de creer des zones d'affichage a l'ecran, afin de decouper l'ecran en zones independantes.

***

Structures :

- [Data](readme/data.md)  
	Une structure de donnees permettant de stocker plusieurs objets. Est necessaire aux widgets boutons.

- [Color](readme/color.md)  
	Une structure de donnees permettant de stocker les 4 composantes d'une couleur.

- [Uv](readme/geometry.md)  
	Une structure de donnees permettant de stocker les 2 coordonees d'un point d'une texture.

- [Rect](readme/geometry.md)  
	Une structure de donnees permettant de stocker un rectangle

- [Matrix](readme/matrix.md)  
	Une structure de donnees permettant d'effectuer des calculs matriciels avec les [Vector4](readme/vector.md).

- [Vector2](readme/vector.md)  
	Une structure de donnees permettant de stocker une coordonnees en 2 dimensions.

- [Vector3](readme/vector.md)  
	Une structure de donnees permettant de stocker une coordonnees en 3 dimensions.

- [Vector4](readme/vector.md)  
	Une structure de donnees permettant de stocker une coordonnees en 4 dimensions.

- [Mouse](readme/event.md)  
	Une structure de donnees permettant d'acceder a l'etat de la souris.

- [Keyboard](readme/event.md)  
	Une structure de donnees permettant d'acceder a l'etat du clavier.

***

## Systeme de widget :
Fonctionnement d'un [widget de base](readme/base_widget.md) au sein de la JGL

Creation d'un widget custom : [Nouveau widget](readme/new_widget.md)

***

# Widget de base :
- [c_button](readme/button.mb)  
	Un widget de bouton, pouvant lancer un pointeur de fonction en cas de clic de souris.

- [c_check_box](readme/check_box.mb)  
	Un widget pouvant etre selectionne ou deselectionner, avec un texte.

- [c_check_entry](readme/check_entry.mb)  
	Un widget pouvant etre selectionne ou deselectionner, avec une entree de texte.

- [c_frame](readme/frame.mb)  
	Une simple zone dans laquelle ajouter des widgets enfants.

- [c_hour_entry](readme/hour_entry.mb)  
	Un widget permettant d'inscrire une heure, dans une entree de texte.

- [c_image_label](readme/image_label.mb)  
	Un widget permettant d'afficher une image a l'ecran, pouvant etre animee.

- [c_tab](readme/tab.mb)  
	Un widget gerant un systeme de tabulation contenant chacune des widgets separes.

- [c_text_entry](readme/text_entry.mb)  
	Un widget d'entree de texte.

- [c_text_label](readme/text_label.mb)  
	Un widget permettant d'afficher un texte a l'ecran.

- [c_value_entry](readme/value_entry.mb)  
	Un widget disposant d'une entree de texte dans laquelle inscrire une valeur decimale.

- [c_value_label](readme/value_label.mb)  
	Un widget permettant d'afficher une valeur decimale a l'ecran

- [c_vscrollbar](readme/scrollbar.mb)  
	Un widget permettant de faire bouger les enfants du widget auquel il est lie via la mollette de la souris ou d'une interaction a l'ecran

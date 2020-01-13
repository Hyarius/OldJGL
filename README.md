### JGL - Librairie graphique pour creation d'interfaces graphiques 2D/3D

##Instruction d'utilisation :
Telecharger la librairie et l'extraire.
make install
make

Une fois la librarie compilee, le makefile vous aura donne un .a a lié a votre projet

Pour utiliser la librairie JGL, vous devez creer imperativement une c_application au lancement du programme afin de pouvoir utiliser les fonctions d'affichage graphique
readme/new_widget.md

##Contenu :
# Fonctionnalite de base :

# Structure et classe
Gestionnaire de fenetre : [c_application](readme/application.md)

Gestionnaire de camera pour les widgets 3D : TO DO

Gestionnaire d'objet 3D : TO DO

Gestionnaire d'image : [c_image](readme/image.md)

Gestionnaire de tileset : [c_tileset](readme/tileset.md)

Gestionnaire de graphique : [c_plot](readme/plot.md)

Gestionnaire d'event sourie et clavier : [event](readme/event.md)

Gestionnaire de viewport : [c_viewport](readme/viewport.md)


Structures basiques :

⋅⋅*[Data](readme/data.md)

⋅⋅*[Color](readme/color.md)

⋅⋅*[Uv](readme/geometry.md)

⋅⋅*[Rect](readme/geometry.md)

⋅⋅*[Matrix](readme/matrix.md)

⋅⋅*[Vector2](readme/vector.md)

⋅⋅*[Vector3](readme/vector.md)

⋅⋅*[Vector4](readme/vector.md)


## Systeme de widget :
Fonctionnement d'un [widget de base](readme/base_widget.md) au sein de la JGL

Creation d'un widget custom : [Nouveau widget](readme/new_widget.md)

# Widget de base :
⋅⋅*widget [c_button](readme/button.mb)

⋅⋅*widget [c_check_box](readme/check_box.mb)

⋅⋅*widget [c_check_entry](readme/check_entry.mb)

⋅⋅*widget [c_frame](readme/frame.mb)

⋅⋅*widget [c_hour_entry](readme/hour_entry.mb)

⋅⋅*widget [c_image_label](readme/image_label.mb)

⋅⋅*widget [c_tab](readme/tab.mb)

⋅⋅*widget [c_text_entry](readme/text_entry.mb)

⋅⋅*widget [c_text_label](readme/text_label.mb)

⋅⋅*widget [c_value_entry](readme/value_entry.mb)

⋅⋅*widget [c_value_label](readme/value_label.mb)

⋅⋅*widget [c_vscrollbar](readme/vscrollbar.mb)
